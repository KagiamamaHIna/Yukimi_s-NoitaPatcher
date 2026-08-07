#pragma once
#include "YNoitaPatcher/detail/MemoryPattern.h"
#include "YNoitaPatcher/detail/auto/YNoitaPatcher_export.h"

/*
ModListInit fn: 6A 0C 68 ? ? ? ? 8D 8D 88 FE FF FF C6 ? ? ? E8 ? ? ? ?
仅仅只是在函数体内
用于进一步搜索，比如定位开头的一个全局变量
*/

extern "C" {
	YNOITAPATCHER_EXPORT uint32_t NVFSFindVFSystem();
	YNOITAPATCHER_EXPORT uint32_t NVFSFindModFileAddVFS();
	YNOITAPATCHER_EXPORT uint32_t NVFSFindModDiskFileDevice();
	YNOITAPATCHER_EXPORT uint32_t NVFSUnknownVFS();
}
