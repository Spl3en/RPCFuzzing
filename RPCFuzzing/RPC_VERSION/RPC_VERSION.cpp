#include "RPC_VERSION.h"
#include "../Dump/Dump.h"

/*
	typedef struct _RPC_VERSION { 
		unsigned short MajorVersion; 
		unsigned short MinorVersion; 
	} RPC_VERSION;
*/

typedef enum {
	RPC_VERSION_MajorVersion = 0,
	RPC_VERSION_MinorVersion,
} GUID_FIELD;

static StructField structure[] = {
	{ "MajorVersion", sizeof(unsigned short) },
	{ "MinorVersion", sizeof(unsigned short) },
};

void DumpRpcVersion (
	FILE *output,
	char *prefix,
	RPC_VERSION *pRpcVersion
) {	
	int field;
	int pos = 0;

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField (output, prefix, &structure[field], pRpcVersion, &pos);
	}
}