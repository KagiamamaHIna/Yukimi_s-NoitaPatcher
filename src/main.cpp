#define NOMINMAX

#include <iostream>
#include <Windows.h>

#include "MinHook.h"
#include "YNoitaPatcher/detail/auto/YNoitaPatcher_export.h"
#include "YNoitaPatcher/NVFS.h"

extern "C" {
	YNOITAPATCHER_EXPORT void YNPMHInit() {
		MH_Initialize();
	}
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
	{
		switch (fdwReason) {
		case DLL_PROCESS_DETACH:
			MH_Uninitialize();
			break;
		}

		return TRUE;  // Successful DLL_PROCESS_ATTACH.
	}
}


