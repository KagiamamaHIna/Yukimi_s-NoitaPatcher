#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <vector>
#include <string>

uintptr_t FindPattern(uintptr_t startAddress, uintptr_t searchSize, const char* signature);
uintptr_t FindPatternInModule(const char* moduleName, const char* signature);
uintptr_t ResolveRelativeAddress(uintptr_t address, int offset, int instructionSize);
void* FindFuncStart(void* func_body);

template<class MemFn>
void* FnToVoidp(MemFn memfn)
{
	return *(void**)&memfn;
}
