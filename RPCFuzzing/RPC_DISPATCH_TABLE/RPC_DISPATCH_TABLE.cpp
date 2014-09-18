#include "RPC_DISPATCH_TABLE.h"
#include "../Dump/Dump.h"

/*
	typedef struct {
		unsigned int DispatchTableCount;
		RPC_DISPATCH_FUNCTION __RPC_FAR * DispatchTable;
		LONG_PTR                          Reserved;
	} RPC_DISPATCH_TABLE, __RPC_FAR * PRPC_DISPATCH_TABLE;
*/

typedef enum {
	GUID_DispatchTableCount = 0,
	GUID_DispatchTable,
	GUID_Reserved,
} GUID_FIELD;

static StructField structure[] = {
	{ "DispatchTableCount", sizeof(unsigned int) },
	{ "DispatchTable", sizeof(RPC_DISPATCH_FUNCTION *) },
	{ "Reserved", sizeof(LONG_PTR) },
};

void DumpRpcDispatchTable(
	FILE *output,
	char *prefix,
	RPC_DISPATCH_TABLE *pDispatchTable
) {
	int field;
	int pos = 0;

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField(output, prefix, &structure[field], pDispatchTable, &pos);
	}
}