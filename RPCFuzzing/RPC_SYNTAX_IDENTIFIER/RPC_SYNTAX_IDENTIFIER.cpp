#include "RPC_SYNTAX_IDENTIFIER.h"
#include <stdio.h>

#include "../GUID/GUID.h"
#include "../RPC_VERSION/RPC_VERSION.h"
#include "../Dump/Dump.h"

/*
	struct RPC_VERSION {
		ushort MajorVersion;
		ushort MinorVersion;
	}

	typedef struct _GUID {
		DWORD Data1;
		WORD  Data2;
		WORD  Data3;
		BYTE  Data4[8];
	} GUID;

	struct RPC_SYNTAX_IDENTIFIER {
		GUID        SyntaxGUID;
		RPC_VERSION SyntaxVersion;
	}
*/

typedef enum {
	RPC_SYNTAX_IDENTIFIER_SyntaxGUID,
	RPC_SYNTAX_IDENTIFIER_SyntaxVersion,
} RPC_SYNTAX_IDENTIFIER_FIELD;

static StructField structure[] = {
	{ "GUID", sizeof(GUID) },
	{ "Version", sizeof(RPC_VERSION)},
};

void DumpRpcSyntaxIdentifier (
	FILE *output,
	char *prefix,
	RPC_SYNTAX_IDENTIFIER *pRpcSyntaxIdentifier
	) {
	int field;
	int pos = 0;
	char *nextPrefix = (char *)malloc(strlen(prefix) + strlen("\"t") + 1);
	sprintf(nextPrefix, "%s\t", prefix);

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField(output, prefix, &structure[field], pRpcSyntaxIdentifier, &pos);

		switch (field) {
			case RPC_SYNTAX_IDENTIFIER_SyntaxGUID:
				DumpGuid (output, nextPrefix, &pRpcSyntaxIdentifier->SyntaxGUID);
			break;

			case RPC_SYNTAX_IDENTIFIER_SyntaxVersion:
				DumpRpcVersion (output, nextPrefix, &pRpcSyntaxIdentifier->SyntaxVersion);
			break;
		}
	}

	// Cleaning
	free(nextPrefix);
}