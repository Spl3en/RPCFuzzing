#include "MIDL_INFORMATION.h"

#include "../RPC_DISPATCH_TABLE/RPC_DISPATCH_TABLE.h"
#include "../Dump/Dump.h"

/*
	typedef struct {
		void * pStubDesc;
		void * ServerRoutineTable;
		
	} MIDL_INFORMATION, *PMIDL_INFORMATION;
*/

typedef enum {
	MIDL_INFORMATION_pStubDesc,
	MIDL_INFORMATION_ServerRoutineTable
} MIDL_INFORMATION_FIELD;

static StructField structure[] = {
	{ "pStubDesc", sizeof(void *)},
	{ "ServerRoutineTable", sizeof(void *)},
};

void DumpMidlInformation (
	FILE *output,
	char *prefix,
	MIDL_INFORMATION *pMidlInformation,
	int ProcNum
) {
	int field;
	int pos = 0;

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField(output, prefix, &structure[field], pMidlInformation, &pos);

		switch (field) {
			case MIDL_INFORMATION_ServerRoutineTable:
				fprintf(output, "%s\tServerFunc called = 0x%08X\n", prefix, *(int *)((int)(pMidlInformation->ServerRoutineTable) + 4 * ProcNum));
			break;
		}
	}
}