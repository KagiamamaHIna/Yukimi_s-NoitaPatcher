#include "YNoitaPatcher/WorldInfo.h"

uint32_t FindGetCell() {
	uint32_t result = FindPatternInModule(nullptr, "75 0B ? ? ? ? ? ? ? ? ? ? 00 8B 00 81 E6 FF 01 00 00 C1 E6 09 81 E7 FF 01 00 00 0B F7 5F 8D 04 B0");
	if (result == 0) {
		return 0;
	}
	return (uint32_t)FindFuncStart((void*)result);
}
uint32_t FindRemoveCell() {
	uint32_t result = FindPatternInModule(nullptr, "8B ? 8D ? FF 6A 01 51 ? 8B ? FF 50 14");
	if (result == 0) {
		return 0;
	}
	return (uint32_t)FindFuncStart((void*)result);
}
uint32_t FindConstructCell() {
	uint32_t result = FindPatternInModule(nullptr, "6A 00 50 53 56 E8");
	if (result == 0) {
		return 0;
	}
	result += 0x5;
	return ResolveRelativeAddress(result, 1, 5);
}
uint32_t FindIsChunkLoaded() {
	uint32_t result = FindPatternInModule(nullptr, "F3 ? ? ? ? ? ? ? 8B C8 E8 ? ? ? ? 84 C0");
	if (result == 0) {
		return 0;
	}
	result += 0xA;
	return ResolveRelativeAddress(result, 1, 5);
}
uint32_t FindGetGameGlobal() {
	uint32_t result = FindPatternInModule(nullptr, "8B 40 48 8B 00 C1 E8 02 A8 01");
	if (result == 0) {
		return 0;
	}
	result -= 0x5;
	return ResolveRelativeAddress(result, 1, 5);
}
