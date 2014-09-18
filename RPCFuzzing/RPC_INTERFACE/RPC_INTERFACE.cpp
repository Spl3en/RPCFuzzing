#include "RPC_INTERFACE.h"
#include <stdio.h>

#include "../MIDL_INFORMATION/MIDL_INFORMATION.h"
#include "../RPC_SYNTAX_IDENTIFIER/RPC_SYNTAX_IDENTIFIER.h"
#include "../RPC_DISPATCH_TABLE/RPC_DISPATCH_TABLE.h"
#include "../Dump/Dump.h"

/*
	struct RPC_INTERFACE
	{
		int Length;
		RPC_SYNTAX_IDENTIFIER InterfaceSyntax;
		RPC_SYNTAX_IDENTIFIER TransferSyntax;
		RPC_DISPATCH_TABLE * DispatchTable;
		__int16 RpcProtseqEndpointCount;
		int RpcProtseqEndpoint;
		__int16 DefaultManagerEpv;
		int InterpreterInfo;
	};
*/

typedef enum {
	RPC_SERVER_INTERFACE_Length = 0,
	RPC_SERVER_INTERFACE_InterfaceSyntax,
	RPC_SERVER_INTERFACE_TransferSyntax,
	RPC_SERVER_INTERFACE_DispatchTable,
	RPC_SERVER_INTERFACE_RpcProtseqEndpointCount,
	RPC_SERVER_INTERFACE_RpcProtseqEndpoint,
	RPC_SERVER_INTERFACE_DefaultManagerEpv,
	RPC_SERVER_INTERFACE_InterpreterInfo,
} RPC_SERVER_INTERFACE_FIELD;

static StructField structure [] = {
	{ "Length", sizeof(int)},
	{ "InterfaceSyntax", sizeof(RPC_SYNTAX_IDENTIFIER) },
	{ "TransferSyntax", sizeof(RPC_SYNTAX_IDENTIFIER) },
	{ "DispatchTable", sizeof(RPC_DISPATCH_TABLE *) },
	{ "RpcProtseqEndpointCount", sizeof(__int16)},
	{ "RpcProtseqEndpoint", sizeof(int)},
	{ "DefaultManagerEpv", sizeof(__int16)},
	{ "InterpreterInfo", sizeof(MIDL_INFORMATION *)},
};

void DumpRpcServerInterface (
	FILE *output,
	char *prefix,
	RPC_INTERFACE *pRpcServerInterface,
	int ProcNum
) {
	int field;
	int pos = 0;
	char *nextPrefix = (char *)malloc(strlen(prefix) + strlen("\t") + 1);
	sprintf(nextPrefix, "%s\t", prefix);

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField(output, prefix, &structure[field], pRpcServerInterface, &pos);
	
		switch (field) {
			case RPC_SERVER_INTERFACE_InterpreterInfo:
				DumpMidlInformation(output, nextPrefix, pRpcServerInterface->InterpreterInfo, ProcNum);
			break;
			
			case RPC_SERVER_INTERFACE_InterfaceSyntax:
				DumpRpcSyntaxIdentifier(output, nextPrefix, &pRpcServerInterface->InterfaceSyntax);
			break;

			case RPC_SERVER_INTERFACE_TransferSyntax:
				DumpRpcSyntaxIdentifier(output, nextPrefix, &pRpcServerInterface->TransferSyntax);
			break;

			case RPC_SERVER_INTERFACE_DispatchTable:
				DumpRpcDispatchTable(output, nextPrefix, (RPC_DISPATCH_TABLE *) pRpcServerInterface->DispatchTable);
			break;
		}
	}

	// Cleaning
	free(nextPrefix);
}