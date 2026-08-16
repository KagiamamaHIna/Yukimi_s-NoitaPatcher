#include "YNoitaPatcher/PlatformWin.h"

uint32_t FindPlatformWin() {
	uint32_t result = FindPatternInModule(nullptr, "B9 ? ? ? ? ? ? ? ? ? AC 00 00 00 8B C8 8B 10");
	if (result == 0) {
		return 0;
	}
	result++;
	return *(uint32_t*)(result);
}
