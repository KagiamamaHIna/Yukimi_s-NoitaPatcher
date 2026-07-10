#define NOMINMAX

#include <iostream>
#include <Windows.h>

#include "MinHook.h"
#include "NVFSPatcher/detail/auto/NVFSPatcher_export.h"
#include "NVFSPatcher/NVFS.h"

extern "C" {
	NVFSPATCHER_EXPORT void NVFSMHInit() {
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


