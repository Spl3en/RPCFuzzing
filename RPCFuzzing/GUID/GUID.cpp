#include "GUID.h"
#include "../Dump/Dump.h"

/*
	typedef struct _GUID {
		DWORD Data1;
		WORD  Data2;
		WORD  Data3;
		BYTE  Data4[8];
	} GUID;
*/

typedef enum {
	GUID_Data1 = 0,
	GUID_Data2,
	GUID_Data3,
	GUID_Data4,
} GUID_FIELD;

static StructField structure[] = {
	{ "Data1", sizeof(DWORD) },
	{ "Data2", sizeof(WORD) },
	{ "Data3", sizeof(WORD) },
	{ "Data4", sizeof(BYTE[8])},
};

void DumpGuid (
	FILE *output,
	char *prefix,
	GUID *pGuid
) {
	int i;
	int field;
	int pos = 0;

	for (field = 0; field < sizeof_array(structure); field++) {
		DumpField(output, prefix, &structure[field], pGuid, &pos);

		switch (field) {
			case GUID_Data4:
				fprintf(output, "%s\t       `-> ", prefix);
				for (i = 0; i < sizeof(pGuid->Data4); i++) {
					fprintf(output, "0x%02X", pGuid->Data4[i]);
					if (i != sizeof(pGuid->Data4) - 1) {
						fprintf(output, ", ");
					}
				}
				fprintf(output, "\n");
			break;
		}
	}
}