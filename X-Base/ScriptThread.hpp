#pragma once
#include "pch.h"
#include "datatypes.hpp"
#include "Utility.hpp"

class game_script 
{
public:
	game_script(_func function, std::string name) : m_func(function),
		m_script_fiber(nullptr), m_main_fiber(nullptr), m_name(name)
	{
		m_script_fiber = CreateFiber(0, [](void* m_fiber_handle) {
			(static_cast<game_script*>(m_fiber_handle))->func_tick();
		}, this);
	}
	void yield(DWORD ms = 0, bool operating = true) {
		if (operating) {
			HUD::SET_TEXT_FONT(7);
			HUD::SET_TEXT_SCALE(0.0f, 1.0f);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_WRAP(0.0f, 1.0f);
			HUD::SET_TEXT_CENTRE(1);
			HUD::SET_TEXT_OUTLINE();
			HUD::SET_TEXT_RIGHT_JUSTIFY(0);
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Please Wait...");
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(0.5f, 0.5f, 0);
		}
		wakeAt = GetTickCount() + ms;
		SwitchToFiber(m_main_fiber);
	}
	void fiber_tick() {
		if (m_main_fiber == nullptr) m_main_fiber = ConvertThreadToFiber(nullptr);
		if (GetTickCount() < wakeAt) return;
		if (m_script_fiber) SwitchToFiber(m_script_fiber);
	}
	static game_script* get_current_script() {
		return reinterpret_cast<game_script*>(GetFiberData());
	}
	void func_tick() {
		__try
		{
			[this]()
			{
				try
				{
					m_func();
				}
				catch (std::exception const &ex)
				{
					auto ex_class = typeid(ex).name() + 6;
					LOG_INFO("Exception {}: {} in {} Thread", ex_class, ex.what(), m_name);
				}
				catch (...)
				{
					LOG_INFO("Unknown C++ Exception in {} Thread", m_name);
				}
			}();
		}
		__except (Hook::exp_handler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
		{
			LOG_INFO("Exception in {} Thread", m_name);
		}
		LOG_INFO("{} Thread finished", m_name);
		for (;;) yield(0, 0);
	}
private:
	void* m_script_fiber;
	void* m_main_fiber;
	_func m_func;
	std::string m_name;
	DWORD wakeAt;
};


class script_manager 
{
public:
	script_manager() 
	{ }
	~script_manager()
	{ }
	void add(std::unique_ptr<game_script> ptr, std::string name) {
		std::lock_guard<std::mutex> lock(m_mutex);
		mScripts.push_back(std::make_pair(name, std::move(ptr)));
		LOG_INFO("Created {} Thread", name);
	}
	void remove(std::string name) {
		static int i = 0;
		for (auto it = mScripts.begin(); it != mScripts.end(); ++it) {
			if (it->first == name)
				mScripts.erase(it);
			i++;
		}
		LOG_INFO("Deleted {} Thread", name);
	}
	void remove_all() {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (mScripts.size() > 0) {
			mScripts.clear();
		}
	}
	void tick() {
		//std::lock_guard<std::mutex> lock(m_mutex);
		for (auto& scripts : mScripts) {
			scripts.second->fiber_tick();
		}
	}

private:
	std::vector<std::pair<std::string, std::unique_ptr<game_script>>> mScripts;
	std::mutex m_mutex;
};

class CallbackThread
{
public:
	CallbackThread() = default;
	~CallbackThread() = default;

	struct CallbackScript
	{
		Function failure;
		Function success;
		std::function<bool()> done;
		bool native;
		CallbackScript(Function failure1, Function success1, std::function<bool()> done1, bool native1)
			: native(native1), failure(failure1), success(success1), done(done1)
		{ }
	};

	inline void AddNativeScript(Function failure, Function success, std::function<bool()> done) {
		m_script_list.push_back(std::make_unique<CallbackScript>(failure, success, done, 1));
	}
	inline void AddD3DScript(Function failure, Function success, std::function<bool()> done) {
		m_script_list.push_back(std::make_unique<CallbackScript>(failure, success, done, 0));
	}
	inline void ExecuteNative(Function function) {
		AddNativeScript([]() -> void {}, function, []() -> bool { return true; });
	}
	inline void ExecuteD3D(Function function) {
		AddD3DScript([]() -> void {}, function, []() -> bool { return true; });
	}

	inline void tickNative() {
		for (auto it = m_script_list.begin(); it != m_script_list.end(); ++it) {
			auto&& call = *it;
			if (call->native) {
				if ((call->done)()) {
					call->success();
					it = m_script_list.erase(it);
				}
				else {
					call->failure();
				}
			}
		}
	}
	inline void tickD3D() {
		for (auto it = m_script_list.begin(); it != m_script_list.end(); ++it) {
			auto&& call = *it;
			if (!(call->native)) {
				if ((call->done)()) {
					call->success();
					it = m_script_list.erase(it);
				}
				else {
					call->failure();
				}
			}
		}
	}

private:
	std::vector<std::unique_ptr<CallbackScript>> m_script_list;
};

inline std::unique_ptr<CallbackThread> g_callbackThread;
inline std::unique_ptr<script_manager> g_scriptThread;