#include "OSF_CCONNECTION.h"
#include <detours.h>
#include <stdio.h>
#include "../Dump/Dump.h"


// Offset des méthodes dans RPCRT4.DLL (= AddresseDeLaMéthode - ImageBaseDeRpcRT4)
#if PATCHED == 0
// Version originale
#define OFFSET_SendBindPacket ((int) 0x2E85D)
#else
// Version patchée
#define OFFSET_SendBindPacket ((int) 0x00000) // Offset à trouver
#endif


// SendBindPacket
typedef int(__thiscall * SendBindPacket_Prototype) (OSF_CCONNECTION *, OSF_BINDING_HANDLE *, int, OSF_CCALL *, unsigned long, unsigned char, unsigned long, int, rpcconn_common **, unsigned int *, rpcconn_common *, unsigned int);
SendBindPacket_Prototype _SendBindPacket;

// SendBindPacket
int __fastcall SendBindPacketHook (
	OSF_CCONNECTION *pThis,
	void *_EDX, // Don't use
	OSF_BINDING_HANDLE *hBinding,
	int arg2,
	OSF_CCALL *ClientCall,
	unsigned long arg4,
	unsigned char arg5,
	unsigned long arg6,
	int arg7,
	rpcconn_common **RpcConnCommon1,
	unsigned int *arg9,
	rpcconn_common *RpcConnCommon2,
	unsigned int arg11
) {
	FILE *output = fopen("output.txt", "a+");
	if (output) {
		/*
		fprintf (output,
			"\n===== SendBindPacket =====\n"
			"OSF_CCONNECTION *pThis = %x\n"
			"OSF_BINDING_HANDLE *hBinding = %x\n"
			"int arg2 = %x\n"
			"OSF_CCALL *ClientCall = %x\n"
			"unsigned long arg4 = %x\n"
			"unsigned char arg5 = %x\n"
			"unsigned long arg6 = %x\n"
			"int arg7 = %x\n"
			"rpcconn_common **RpcConnCommon1 = %x (%x)\n"
			"unsigned int *arg9 = %x (%x)\n"
			"rpcconn_common *RpcConnCommon2 = %x\n"
			"unsigned int arg11 = %x\n",
			pThis, 
			hBinding, 
			arg2, 
			ClientCall, 
			arg4, 
			arg5, 
			arg6, 
			arg7, 
			RpcConnCommon1, (RpcConnCommon1) ? *RpcConnCommon1 : 0, 
			arg9, (arg9) ? *arg9 : 0, 
			RpcConnCommon2, arg11
		);

		fprintf(output, "\n\t===== OSF_BINDING_HANDLE =====\n\t");
		Dump(output, (unsigned char *)hBinding, 10 * 16, true);
		fprintf(output, "\n\t===== arg2 =====\n\t");
		Dump(output, (unsigned char *)arg2, 10 * 16, true);
		fprintf(output, "\n\t===== RpcConnCommon1 =====\n\t");
		Dump(output, (unsigned char *)RpcConnCommon1, 10 * 16, true);

		fclose(output);
		*/
	}

	return _SendBindPacket(pThis, hBinding, arg2, ClientCall, arg4, arg5, arg6, arg7, RpcConnCommon1, arg9, RpcConnCommon2, arg11);
}

void OSF_CCONNECTION_installHooks(HMODULE rpcrt4)
{
	// Récupération de l'adresse courante des méthodes
	_SendBindPacket = (SendBindPacket_Prototype)((DWORD)rpcrt4 + OFFSET_SendBindPacket);
	

	// On pose les hooks à partir d'ici
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&_SendBindPacket, SendBindPacketHook);
	DetourTransactionCommit();
}

void OSF_CCONNECTION_removeHooks()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&_SendBindPacket, SendBindPacketHook);
	DetourTransactionCommit();
}