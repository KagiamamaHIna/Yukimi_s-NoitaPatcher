#pragma once
#include "YNoitaPatcher/detail/MemoryPattern.h"
#include "YNoitaPatcher/detail/auto/YNoitaPatcher_export.h"
#include "MinHook.h"

void HookCellInit();
extern "C" {
	YNOITAPATCHER_EXPORT uint32_t FindCLiquidCellVtable();
	YNOITAPATCHER_EXPORT uint32_t FindCGasCellVtable();
	YNOITAPATCHER_EXPORT uint32_t FindCFireCellVtable();
	YNOITAPATCHER_EXPORT uint32_t FindCSoildCellVtable();
	YNOITAPATCHER_EXPORT bool EnableCellUpdate(bool enabled);
}
