#pragma once
#include "YNoitaPatcher/detail/MemoryPattern.h"
#include "YNoitaPatcher/detail/auto/YNoitaPatcher_export.h"

extern "C" {
	YNOITAPATCHER_EXPORT uint32_t FindGetCell();
	YNOITAPATCHER_EXPORT uint32_t FindRemoveCell();
	YNOITAPATCHER_EXPORT uint32_t FindConstructCell();
	YNOITAPATCHER_EXPORT uint32_t FindIsChunkLoaded();
	YNOITAPATCHER_EXPORT uint32_t FindGetGameGlobal();
}
