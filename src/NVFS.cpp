#include "NVFSPatcher/NVFS.h"

/*
VFSystem obj: 8B 9D ? ? ? ? 8D 85 ? ? ? ? 50 51 FF B5 ? ? ? ? 8D 85
在赋值到全局变量的操作里
*/
uint32_t NVFSFindVFSystem() {
	uint32_t result = FindPatternInModule(nullptr, "8B 9D ? ? ? ? 8D 85 ? ? ? ? 50 51 FF B5 ? ? ? ? 8D 85");
	if (result == 0) {
		return 0;
	}
	result += 0x2C + 2;//指令偏移+偏移MOV指令取MOV里的参数
	return *(uint32_t*)(result);
}

/*
ModFileAddVFS fn: 33 C9 FF B5 ? ? ? ? 8B 95 ? ? ? ? 50 8D 45
在调用这个的一个序列里
*/
uint32_t NVFSFindModFileAddVFS() {
	uint32_t result = FindPatternInModule(nullptr, "33 C9 FF B5 ? ? ? ? 8B 95 ? ? ? ? 50 8D 45");
	if (result == 0) {
		return 0;
	}
	result += 0x1B;//指令偏移到CALL指令的位置
	return ResolveRelativeAddress(result, 1, 5);
}

/*
ModDiskFileDevice fn: 8D 45 ? 89 8D ? ? ? ? 89 8D ? ? ? ? 8B CE 50 E8
在调用这个的一个序列里
*/
uint32_t NVFSFindModDiskFileDevice() {
	uint32_t result = FindPatternInModule(nullptr, "8D 45 ? 89 8D ? ? ? ? 89 8D ? ? ? ? 8B CE 50 E8");
	if (result == 0) {
		return 0;
	}
	result += 0x12;//指令偏移到CALL指令的位置
	return ResolveRelativeAddress(result, 1, 5);
}
/*
NVFSUnknownVFS obj: 68 ? ? ? ? 68 ? ? ? ? 89 85 ? ? ? ? 89 85 ? ? ? ? E8 ? ? ? ? 8B C8 E8 ? ? ? ? A1
在一段赋值与调用序列里
*/
uint32_t NVFSUnknownVFS() {
	uint32_t result = FindPatternInModule(nullptr, "68 ? ? ? ? 68 ? ? ? ? 89 85 ? ? ? ? 89 85 ? ? ? ? E8 ? ? ? ? 8B C8 E8 ? ? ? ? A1");
	if (result == 0) {
		return 0;
	}
	result += 0x22 + 1;//指令偏移+偏移MOV指令取MOV里的参数
	return *(uint32_t*)(result);
}
