#pragma once
#include "YNoitaPatcher/detail/MemoryPattern.h"
#include "YNoitaPatcher/detail/auto/YNoitaPatcher_export.h"
#include "MinHook.h"

void HookCellInit();
extern "C" {
	YNOITAPATCHER_EXPORT bool EnableCellUpdate(bool enabled);
}
