#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include "../main.h"

void DumpRpcVersion(
	FILE *output,
	char *prefix,
	RPC_VERSION *pRpcVersion
);