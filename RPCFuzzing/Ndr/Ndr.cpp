#include "Ndr.h"
#include <detours.h>
#include <stdio.h>
#include "../Dump/Dump.h"
#include "../RPC_MESSAGE/RPC_MESSAGE.h"


// Offset des méthodes dans RPCRT4.DLL (= AddresseDeLaMéthode - ImageBaseDeRpcRT4)
#if PATCHED == 0
// Version originale
#define OFFSET_NdrAsyncServerCall ((int) 0x94A1C)
#else
// Version patchée
#define OFFSET_NdrAsyncServerCall ((int) 0x00000) // Offset à trouver
#endif


// NdrAsyncServerCall
typedef void(__stdcall * NdrAsyncServerCall_Prototype) (RPC_MESSAGE *pRpcMsg);
NdrAsyncServerCall_Prototype _NdrAsyncServerCall;


// NdrAsyncServerCall
void __stdcall NdrAsyncServerCallHook (
	RPC_MESSAGE *pRpcMsg
) {
	FILE *output = fopen("output.txt", "a+");
	if (output) {
		fprintf(output, "\n===== NdrAsyncServerCall =====\n");
		DumpRpcMessage(output, " ", pRpcMsg);
		fclose(output);
	}

	return _NdrAsyncServerCall (pRpcMsg);
}


void Ndr_installHooks(HMODULE rpcrt4)
{
	// Récupération de l'adresse courante des méthodes
	_NdrAsyncServerCall = (NdrAsyncServerCall_Prototype) ((DWORD) rpcrt4 + OFFSET_NdrAsyncServerCall);

	// On pose les hooks à partir d'ici
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&_NdrAsyncServerCall, NdrAsyncServerCallHook);
	DetourTransactionCommit();
}


void Ndr_removeHooks ()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&_NdrAsyncServerCall, NdrAsyncServerCallHook);
	DetourTransactionCommit();
}