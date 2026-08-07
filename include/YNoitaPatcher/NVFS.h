#pragma once
#include "YNoitaPatcher/detail/MemoryPattern.h"
#include "YNoitaPatcher/detail/auto/YNoitaPatcher_export.h"

extern "C" {
	YNOITAPATCHER_EXPORT uint32_t NVFSFindVFSystem();
	YNOITAPATCHER_EXPORT uint32_t NVFSFindModFileAddVFS();
	YNOITAPATCHER_EXPORT uint32_t NVFSFindModDiskFileDevice();
	YNOITAPATCHER_EXPORT uint32_t NVFSUnknownVFS();
}
