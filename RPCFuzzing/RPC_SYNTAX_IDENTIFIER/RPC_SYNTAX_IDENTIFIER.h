#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include "../main.h"

void DumpRpcSyntaxIdentifier(
	FILE *output,
	char *prefix,
	RPC_SYNTAX_IDENTIFIER *pRpcSyntaxIdentifier
);