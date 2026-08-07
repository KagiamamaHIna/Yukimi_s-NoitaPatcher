#include "YNoitaPatcher/detail/MemoryPattern.h"

// 将两字符的十六进制字符串转换为字节
#define NVFS_INRANGE(x,a,b)  (x >= a && x <= b)
#define NVFS_getBits( x )    (NVFS_INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (NVFS_INRANGE(x,'0','9') ? x - '0' : 0))
#define NVFS_getByte( x )    (NVFS_getBits(x[0]) << 4 | NVFS_getBits(x[1]))

// ==========================================
// 核心扫描函数：在指定内存范围内查找 IDA 风格特征码
// ==========================================
uintptr_t FindPattern(uintptr_t startAddress, uintptr_t searchSize, const char* signature) {
	const char* pat = signature;
	uintptr_t firstMatch = 0;

	for (uintptr_t pCur = startAddress; pCur < startAddress + searchSize; pCur++) {
		if (!*pat) return firstMatch; // 匹配完成

		// 如果是通配符 '?'，跳过当前字节的比较
		if (*pat == '\?' || *(uint8_t*)pCur == NVFS_getByte(pat)) {
			if (!firstMatch) firstMatch = pCur; // 记录第一次匹配的起点

			if (!pat[2]) return firstMatch; // 如果是最后一个字符，直接返回

			// 如果当前是 '?' 或者 '??'，处理指针偏移
			if (*pat == '\?') {
				pat += (*(pat + 1) == '\?' ? 3 : 2); // 处理 '??' 或 '?'
			}
			else {
				pat += 3; // 处理普通十六进制字符(例如 "A1 ")
			}
		}
		else {
			// 匹配失败，回溯重置
			pat = signature;
			firstMatch = 0;
		}
	}
	return 0; // 没找到
}

// ==========================================
// 获取模块基址并扫描模块全空间
// ==========================================
uintptr_t FindPatternInModule(const char* moduleName, const char* signature) {
	HMODULE hModule = GetModuleHandleA(moduleName);
	if (!hModule) return 0;

	MODULEINFO modInfo = { 0 };
	// 获取模块在内存中的大小
	if (GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO))) {
		uintptr_t baseAddress = (uintptr_t)modInfo.lpBaseOfDll;
		uintptr_t sizeOfImage = modInfo.SizeOfImage;

		return FindPattern(baseAddress, sizeOfImage, signature);
	}
	return 0;
}

// address: 特征码匹配到的指令地址
// offset: 相对偏移在指令中的字节位置（例如 call 指令中偏移在第 1 字节）
// instructionSize: 整条指令的长度（例如 call 是 5 个字节）
uintptr_t ResolveRelativeAddress(uintptr_t address, int offset, int instructionSize) {
	if (!address) return 0;
	// 读取相对偏移量（4字节有符号整数）
	int32_t relativeOffset = *(int32_t*)(address + offset);
	// 真实地址 = 当前指令地址 + 指令长度 + 相对偏移量
	return address + instructionSize + relativeOffset;
}
