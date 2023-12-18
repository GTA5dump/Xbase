#pragma once
#include "pch.h"
#include "pattern_scan.hpp"
#include "Utility.hpp"
#include "core.h"
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

#define ResolveRVA(base,rva) (( (uint8_t*)base) +rva)

namespace Hook
{
	inline DWORD exp_handler(PEXCEPTION_POINTERS exp)
	{
		return exp->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION
			? EXCEPTION_EXECUTE_HANDLER
			: EXCEPTION_CONTINUE_SEARCH;
	}

	class Detour
	{
	public:
		inline explicit Detour(void *target, void *detour, std::string name) : m_target(target), m_detour(detour), m_name(name)
		{
			if (found_pointer()) {
				patch_jmp();
				MH_CreateHook(m_target, m_detour, &m_original);				
			}
			else
				throw std::runtime_error("Failed to find Pointer");
		};

		inline ~Detour() { 
			disable(); 
			unhook(); 
		};


		inline void patch_jmp() {

			__try {
				auto ptr = ptr_manage(m_target);
				while (ptr.as<std::uint8_t&>() == 0xE9)
					ptr = ptr.add(1).rip();
				m_target = ptr.as<void*>();
			}
			__except (exp_handler(GetExceptionInformation())) {
				[this]()
				{
					throw std::runtime_error(fmt::format("Failed to fix hook address for '0x{:X}'", m_target));
				}();
			}
		}

		inline void unhook() {
			m_target != nullptr ? MH_RemoveHook(m_target) : throw std::runtime_error(fmt::format("Cant Unhook: {}", m_target));
		}

		inline bool enable() {
			MH_STATUS status = MH_EnableHook(m_target);
			if (status == MH_OK) { LOG_INFO("Created {} Hook", m_name); return true; }
			else return false;
		}

		inline void disable() { 
			MH_DisableHook(m_target); 
		}

		template <typename T>
		inline T get_original() {
			return static_cast<T>(m_original);
		}

		inline bool found_pointer() { 
			return m_target != nullptr; 
		}

	private:
		void *m_target{};
		void *m_detour{};
		void *m_original{};
		std::string m_name{};
	};




	class VMT
	{
	public:
		inline explicit VMT(void* obj, std::size_t num_funcs, std::string name) :
			m_object(static_cast<void***>(obj)),
			m_num_funcs(num_funcs + 1),
			m_original_table(*m_object),
			m_new_table(std::make_unique<void*[]>(m_num_funcs)),
			m_name(name)
		{
			std::copy_n(m_original_table - 1, m_num_funcs, m_new_table.get());
		}

		inline bool hook(std::size_t index, void* func) {
			m_new_table[index + 1] = func; 
			return false;
		}

		inline void unhook(std::size_t index) {
			m_new_table[index + 1] = m_original_table[index];
		}

		template <typename T>
		inline T get_original(std::size_t index) {
			return static_cast<T>(m_original_table[index]);
		}

		inline bool enable() {
			*m_object = m_new_table.get() + 1;
			return false;
		}

		inline void disable() {
			*m_object = m_original_table;
		}

	private:
		void*** m_object;
		std::size_t m_num_funcs;
		void** m_original_table;
		std::unique_ptr<void*[]> m_new_table;	
		std::string m_name;
	};




	class MemoryProtect
	{
	public:
		inline MemoryProtect(void* Address, size_t Size, DWORD ProtectionFlags) {
			m_Address = Address;
			m_Size = Size;
			m_Flags = ProtectionFlags;
			Protect(m_Address, m_Size, m_Flags);
		}
		inline ~MemoryProtect() {
			Protect(m_Address, m_Size, m_OldProtection);
		}
	private:
		inline bool Protect(void* Address, size_t Size, DWORD ProtectionFlags) {
			return VirtualProtect(Address, Size, ProtectionFlags, &m_OldProtection);
		}
		void* m_Address;
		size_t m_Size;
		DWORD m_Flags;
		DWORD m_OldProtection;
	};




	class IAT
	{
	public:
		inline IAT() : m_Hooked(false)
		{ }

		inline IAT(const char* LibraryName, const char* SrcFunc, uint8_t* Dest, const char* Module = "") {
			m_hkLibraryName = LibraryName;
			m_hkSrcFunc = SrcFunc;
			m_hkModuleName = Module;
			m_hkDest = Dest;
		}

		inline ~IAT() {
			if (m_Hooked) {
				unhook();
			}
		}

		inline bool enable() {
			PIMAGE_THUNK_DATA Thunk;
			if (!FindIATFunc(m_hkLibraryName.c_str(), m_hkSrcFunc.c_str(), &Thunk, m_hkModuleName.c_str())) return false;
			MemoryProtect Protector(Thunk, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE);
			m_pIATFuncOrig = (void*)Thunk->u1.Function;
			Thunk->u1.Function = (uintptr_t)m_hkDest;
			m_Hooked = true;
			return true;
		}

		inline void unhook() {
			PIMAGE_THUNK_DATA Thunk;
			if (!FindIATFunc(m_hkLibraryName.c_str(), m_hkSrcFunc.c_str(), &Thunk)) return;
			MemoryProtect Protector(Thunk, sizeof(ULONG_PTR), PAGE_EXECUTE_READWRITE);
			Thunk->u1.Function = (ULONG_PTR)m_pIATFuncOrig;
			m_Hooked = false;
		}

		inline void hook(const char* LibraryName, const char* SrcFunc, uint8_t* Dest, const char* Module) {
			m_hkLibraryName = LibraryName;
			m_hkSrcFunc = SrcFunc;
			m_hkModuleName = Module;
			m_hkDest = Dest;
		}

		template<typename T>
		T get_original() {
			return (T)m_pIATFuncOrig;
		}

	private:
		inline bool FindIATFunc(const char* LibraryName, const char* FuncName, PIMAGE_THUNK_DATA* pFuncThunkOut, const char* Module = "") {
			bool UseModuleName = true;
			if (Module == NULL || Module[0] == '\0') UseModuleName = false;
			HINSTANCE hInst = GetModuleHandleA(UseModuleName ? Module : NULL);
			if (!hInst) return false;
			ULONG Sz;
			PIMAGE_IMPORT_DESCRIPTOR pImports = (PIMAGE_IMPORT_DESCRIPTOR)
				ImageDirectoryEntryToDataEx(hInst, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &Sz, nullptr);
			for (uint_fast16_t i = 0; pImports[i].Characteristics != 0; i++) {
				char* _ModuleName = (char*)ResolveRVA(hInst, pImports[i].Name);
				if (_stricmp(_ModuleName, LibraryName) != 0)
					continue;
				PIMAGE_THUNK_DATA pOriginalThunk = (PIMAGE_THUNK_DATA)
					ResolveRVA(hInst, pImports[i].OriginalFirstThunk);
				PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)
					ResolveRVA(hInst, pImports[i].FirstThunk);
				if (!pOriginalThunk) return false;
				for (; pOriginalThunk->u1.Function != NULL; pOriginalThunk++, pThunk++) {
					if (IMAGE_SNAP_BY_ORDINAL(pOriginalThunk->u1.Ordinal)) continue;
					PIMAGE_IMPORT_BY_NAME pImport = (PIMAGE_IMPORT_BY_NAME)
						ResolveRVA(hInst, pOriginalThunk->u1.AddressOfData);
					if (_stricmp(FuncName, pImport->Name) != 0)
						continue;
					*pFuncThunkOut = pThunk;
					return true;
				}
			}
			return false;
		}
		std::string m_hkSrcFunc;
		std::string m_hkLibraryName;
		std::string m_hkModuleName;
		uint8_t* m_hkDest;
		void* m_pIATFuncOrig;
		bool m_Hooked;
	};
}