#pragma once

#include "../main.h"

#include <stdio.h>


void Dump(
	FILE *output,
	char *prefix,
	unsigned char *data,
	int size,
	bool isBigEndian
);

void DumpField(
	FILE *output,
	char *prefix,
	StructField *field,
	void *data,
	int *pos
);