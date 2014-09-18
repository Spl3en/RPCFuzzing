#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#include <RpcdceP.h> // for RPC_MESSAGE structure definition
#include "../main.h"


void Ndr_installHooks(HMODULE rpcrt4);
void Ndr_removeHooks();
