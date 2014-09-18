#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include "../main.h"
#include "../OSF_BINDING_HANDLE/OSF_BINDING_HANDLE.h"
#include "../OSF_CCALL/OSF_CCALL.h"
#include "../rpcconn_common/rpcconn_common.h"

typedef struct {
	DWORD *vftable;
} OSF_CCONNECTION;


void OSF_CCONNECTION_installHooks(HMODULE rpcrt4);
void OSF_CCONNECTION_removeHooks();