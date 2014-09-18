#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include "../main.h"

void DumpRpcMessage(
	FILE *output,
	char *prefix,
	RPC_MESSAGE *pRpcMessage
);