#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

#include "./OSF_CCONNECTION/OSF_CCONNECTION.h"
#include "./Ndr/Ndr.h"

void onAttach ()
{
	HMODULE rpcrt4;

	// Get RPCRT4.dll base address
	if ((rpcrt4 = GetModuleHandle ("rpcrt4.dll")) == NULL) {
		MessageBox(NULL, "RPCRT4.dll not found !\n", "!", 0);
		return;
	}

	// Install hooks
	OSF_CCONNECTION_installHooks(rpcrt4);
	Ndr_installHooks(rpcrt4);
}

void onDetach()
{
	// Remove hooks
	OSF_CCONNECTION_removeHooks();
	Ndr_removeHooks();
}

bool WINAPI DllMain (HMODULE dll, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			onAttach();
		break;

		case DLL_PROCESS_DETACH:
			onDetach();
		break;
	}

	return true;
}
