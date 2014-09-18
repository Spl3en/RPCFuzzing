#include "Dump.h"


void DumpField (
	FILE *output,
	char *prefix,
	StructField *field,
	void *data,
	int *pos
) {
	int bytePos = 0;

	fprintf(output, "%s0x%-5x %s (%d) : ", prefix, *pos, field->name, field->size);
	if (field->size <= 4) {
		fprintf(output, "0x");
		
		// Little Endian
		for (bytePos = field->size - 1; bytePos >= 0; bytePos--) {
			fprintf(output, "%02X", ((unsigned char *)data)[(*pos) + bytePos]);
		}
	}
	fprintf(output, "\n");

	*pos = (*pos) + field->size;
}


// Dump dans un fichier un certain nombre d'octets d'une structure passée en paramètre
void Dump (
	FILE *output, 
	char *prefix,
	unsigned char *data,
	int size,
	bool isBigEndian
) {
	int i, j, pos = 0;

	if (isBigEndian) {
		while (true) {
			fprintf(output, "%s", prefix);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (pos + 1 > size) {
						fprintf(output, "\n");
						return;
					}

					fprintf(output, "%02X", ((unsigned char *)data)[pos++]);
				}
				fprintf(output, " ");
			}
			fprintf(output, "\n");
		}
	}
	else {
		bool overflowed = false;

		while (!overflowed) {
			fprintf(output, "%s", prefix);
			for (i = 0; i < 4; i++) {
				if (pos >= size) {
					fprintf(output, "\n");
					return;
				}
				for (j = 3; j >= 0; j--) {
					if (pos + j < size) {
						fprintf(output, "%02X", ((unsigned char *)data)[pos+j]);
					}
				}
				fprintf(output, " ");
				pos += 4;
			}
			fprintf(output, "\n");
		}
	}
}

