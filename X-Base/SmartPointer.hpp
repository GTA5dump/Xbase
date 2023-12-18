#pragma once
#include "pch.h"

namespace std
{
	template <class t_>
	class soos_ptr {

	public:

		t_* operator-> () {
			return (t_*)p_base_class;
		}

		t_ operator* () {
			return *(t_*)p_base_class;
		}

		template<typename ...Args>
		soos_ptr(Args... args) : p_base_class(new t_(args...)) { };

		t_* get() { return p_base_class; }

		void reset() {
			//p_base_class->Release();
			delete this;
		}

	private:
		t_* p_base_class;
	};

	template<class t_, typename ...Args>
	inline soos_ptr<t_> make_soos(Args... args) {
		return soos_ptr<t_>(args...);
	}
}