#include "GUID.h"

void DumpGuid (
	FILE *output,
	char *prefix,
	GUID *guid
) {
	int i;

	fprintf (output, "%sGUID.Data1 = 0x%8X | GUID.Data2 = 0x%4X | GUID.Data3 = 0x%4X | GUID.Data4 = {",
		prefix,
		guid->Data1,
		guid->Data2,
		guid->Data3
	);

	for (i = 0; i < sizeof(guid->Data4); i++) {
		fprintf(output, "0x%02X, ", guid->Data4[i]);
	}
	
fprintf(output, "}\n");
}