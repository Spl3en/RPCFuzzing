#include "RPC_MESSAGE.h"
#include <stdio.h>

#include "../RPC_INTERFACE/RPC_INTERFACE.h"
#include "../RPC_SYNTAX_IDENTIFIER/RPC_SYNTAX_IDENTIFIER.h"
#include "../Dump/Dump.h"

/*
	typedef struct _RPC_MESSAGE {
	  RPC_BINDING_HANDLE     Handle;
	  unsigned long          DataRepresentation;
	  void                   *Buffer;
	  unsigned int           BufferLength;
	  unsigned int           ProcNum;
	  PRPC_SYNTAX_IDENTIFIER TransferSyntax;
	  void                   *RpcInterfaceInformation; // RPC_INTERFACE *
	  void                   *ReservedForRuntime;
	  RPC_MGR_EPV            *ManagerEpv;
	  void                   *ImportContext;
	  unsigned long          RpcFlags;
	} RPC_MESSAGE, *PRPC_MESSAGE;
*/


typedef enum {
	RPC_MESSAGE_Handle = 0,
	RPC_MESSAGE_DataRepresentation,
	RPC_MESSAGE_Buffer,
	RPC_MESSAGE_BufferLength,
	RPC_MESSAGE_ProcNum,
	RPC_MESSAGE_TransferSyntax,
	RPC_MESSAGE_RpcInterfaceInformation,
	RPC_MESSAGE_ReservedForRuntime,
	RPC_MESSAGE_ManagerEpv,
	RPC_MESSAGE_ImportContext,
	RPC_MESSAGE_RpcFlags
} RPC_MESSAGE_FIELD;


static StructField structure[] = {
	{ "Handle", sizeof(RPC_BINDING_HANDLE) },
	{ "DataRepresentation", sizeof(unsigned long) },
	{ "Buffer", sizeof(void *) },
	{ "BufferLength", sizeof(unsigned int) },
	{ "ProcNum", sizeof(unsigned int) },
	{ "TransferSyntax", sizeof(PRPC_SYNTAX_IDENTIFIER) },
	{ "RpcInterfaceInformation", sizeof(RPC_INTERFACE *) },
	{ "ReservedForRuntime", sizeof(void *) },
	{ "ManagerEpv", sizeof(RPC_MGR_EPV *) },
	{ "ImportContext", sizeof(unsigned long) },
	{ "RpcFlags", sizeof(MIDL_INFORMATION *) },
};


void DumpRpcMessage (
	FILE *output,
	char *prefix,
	RPC_MESSAGE *pRpcMessage
	) {
	int field;
	int pos = 0;
	char *nextPrefix = (char *) malloc(strlen(prefix) + strlen("\t") + 1);
	sprintf(nextPrefix, "%s\t", prefix);

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField(output, prefix, &structure[field], pRpcMessage, &pos);

		switch (field) {
			case RPC_MESSAGE_RpcInterfaceInformation:
				DumpRpcServerInterface(output, nextPrefix, (RPC_INTERFACE *)pRpcMessage->RpcInterfaceInformation, pRpcMessage->ProcNum);
			break;

			case RPC_MESSAGE_TransferSyntax:
				DumpRpcSyntaxIdentifier(output, nextPrefix, (RPC_SYNTAX_IDENTIFIER *)pRpcMessage->TransferSyntax);
			break;

			case RPC_MESSAGE_Buffer:
				Dump(output, nextPrefix, (unsigned char *) pRpcMessage->Buffer, pRpcMessage->BufferLength, false);
			break;
		}
	}

	// Cleaning
	free(nextPrefix);
}