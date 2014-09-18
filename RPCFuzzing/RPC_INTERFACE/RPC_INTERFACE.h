#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include "../main.h"
#include "../MIDL_INFORMATION/MIDL_INFORMATION.h"


typedef struct _RPC_INTERFACE
{
	int Length;
	RPC_SYNTAX_IDENTIFIER InterfaceSyntax;
	RPC_SYNTAX_IDENTIFIER TransferSyntax;
	int DispatchTable;
	__int16 RpcProtseqEndpointCount;
	int RpcProtseqEndpoint;
	__int16 DefaultManagerEpv;
	MIDL_INFORMATION * InterpreterInfo;

} RPC_INTERFACE, *PRPC_INTERFACE;


void DumpRpcServerInterface(
	FILE *output,
	char *prefix,
	RPC_INTERFACE *pRpcServerInterface,
	int procNum
);