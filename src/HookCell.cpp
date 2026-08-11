#include "YNoitaPatcher/HookCell.h"

/*
EnableCellUpdate(enabled)
CLiquidCell vtable 要跳过第一个C7
C7 ? ? 00 00 00 00 89 ? ? 8B ? ? 89 ? ? 8B ? ? C7 ? ? ? ? ? C7 ? ? 03 00 00 00
CGasCell vtable 往后查出现的第一个C7开头的指令
89 ? 20 8B ? 10 89 ? 24
CFireCell vtable 往后查出现的第一个C7开头的指令
8B 45 10 ? ? ? ? ? ? ? ? ? C7 ? 20 00 00 00 00 C6 ? 24 01
CSoildCell vtable 往前查出现的第一个C7开头的指令
C7 ? 58 01 00 00 00 C7 ? 5C 00 00 00 00 66 ? ? 60 00 01
*/

uint32_t FindCLiquidCellVtable() {
	uint32_t result = FindPatternInModule(nullptr, "C7 ? ? 00 00 00 00 89 ? ? 8B ? ? 89 ? ? 8B ? ? C7 ? ? ? ? ? C7 ? ? 03 00 00 00");
	if (result == 0) {
		return 0;
	}
	result += 0x13 + 2;//指令偏移+偏移MOV指令取MOV里的参数
	return *(uint32_t*)(result);
}

uint32_t FindCGasCellVtable() {
	uint32_t result = FindPatternInModule(nullptr, "89 ? 20 8B ? 10 89 ? 24");
	if (result == 0) {
		return 0;
	}
	result = FindPattern(result, 50, "C7 ? ? ? ? ?");
	if (result == 0) {
		return 0;
	}
	result += 2;
	return *(uint32_t*)(result);
}

uint32_t FindCFireCellVtable() {
	uint32_t result = FindPatternInModule(nullptr, "8B 45 10 ? ? ? ? ? ? ? ? ? C7 ? 20 00 00 00 00 C6 ? 24 01");
	if (result == 0) {
		return 0;
	}
	result = FindPattern(result, 12, "C7 ? ? ? ? ?");
	if (result == 0) {
		return 0;
	}
	result += 2;
	return *(uint32_t*)(result);
}

uint32_t FindCSoildCellVtable() {
	uint32_t temp = FindPatternInModule(nullptr, "C7 ? 58 01 00 00 00 C7 ? 5C 00 00 00 00 66 ? ? 60 00 01");
	if (temp == 0) {
		return 0;
	}
	temp--;
	uint8_t* ptr = (uint8_t*)temp;
	for (size_t i = 0; i < 50; i++) {
		if (*ptr == 0xC7) {
			uint32_t result = (uint32_t)ptr;
			result += 2;
			return *(uint32_t*)(result);
		}
		ptr--;
	}
	return 0;
}
using CellUpdate = void* (__thiscall*)(void* cell, void* unk, bool unk_flag, void* grid_world, void* cell2);

CellUpdate CLiquidCellUpdate;
CellUpdate CGasCellUpdate;
CellUpdate CFireCellUpdate;
CellUpdate CSoildCellUpdate;

bool DisableCellUpdate = false;

struct CellHooks {
	void* __thiscall HookCLiquidCellUpdate(void* unk, bool unk_flag, void* grid_world, void* cell2) {
		if (DisableCellUpdate) {
			return nullptr;
		}
		return CLiquidCellUpdate(this, unk, unk_flag, grid_world, cell2);
	}
	void* __thiscall HookCGasCellUpdate(void* unk, bool unk_flag, void* grid_world, void* cell2) {
		if (DisableCellUpdate) {
			return nullptr;
		}
		return CGasCellUpdate(this, unk, unk_flag, grid_world, cell2);
	}
	void* __thiscall HookCFireCellUpdate(void* unk, bool unk_flag, void* grid_world, void* cell2) {
		if (DisableCellUpdate) {
			return nullptr;
		}
		return CFireCellUpdate(this, unk, unk_flag, grid_world, cell2);
	}
	void* __thiscall HookCSoildCellUpdate(void* unk, bool unk_flag, void* grid_world, void* cell2) {
		if (DisableCellUpdate) {
			return nullptr;
		}
		return CSoildCellUpdate(this, unk, unk_flag, grid_world, cell2);
	}
};

void HookCellInit() {
	uint32_t CLiquidCellVtable = FindCLiquidCellVtable();
	if (CLiquidCellVtable == 0) {
		std::cerr << "CLiquidCellVtable is nullptr\n";
		return;
	}
	uint32_t CGasCellVtable = FindCGasCellVtable();
	if (CGasCellVtable == 0) {
		std::cerr << "CGasCellVtable is nullptr\n";
		return;
	}
	uint32_t CFireCellVtable = FindCFireCellVtable();
	if (CFireCellVtable == 0) {
		std::cerr << "CFireCellVtable is nullptr\n";
		return;
	}
	uint32_t CSoildCellVtable = FindCSoildCellVtable();
	if (CSoildCellVtable == 0) {
		std::cerr << "CSoildCellVtable is nullptr\n";
		return;
	}
	//Hook CellUpdate
	size_t offset = 21 * sizeof(void*);
	LPVOID* tempFn = *reinterpret_cast<LPVOID**>(CLiquidCellVtable + offset);
	MH_CreateHook(tempFn, FnToVoidp(&CellHooks::HookCLiquidCellUpdate), reinterpret_cast<LPVOID*>(&CLiquidCellUpdate));
	MH_EnableHook(tempFn);

	tempFn = *reinterpret_cast<LPVOID**>(CGasCellVtable + offset);
	MH_CreateHook(tempFn, FnToVoidp(&CellHooks::HookCGasCellUpdate), reinterpret_cast<LPVOID*>(&CGasCellUpdate));
	MH_EnableHook(tempFn);

	tempFn = *reinterpret_cast<LPVOID**>(CFireCellVtable + offset);
	MH_CreateHook(tempFn, FnToVoidp(&CellHooks::HookCFireCellUpdate), reinterpret_cast<LPVOID*>(&CFireCellUpdate));
	MH_EnableHook(tempFn);

	tempFn = *reinterpret_cast<LPVOID**>(CSoildCellVtable + offset);
	MH_CreateHook(tempFn, FnToVoidp(&CellHooks::HookCSoildCellUpdate), reinterpret_cast<LPVOID*>(&CSoildCellUpdate));
	MH_EnableHook(tempFn);

}

bool EnableCellUpdate(bool enabled) {
	if (CLiquidCellUpdate == nullptr) {
		std::cerr << "no init\n";
		return false;
	}
	DisableCellUpdate = !enabled;
	return true;
}
