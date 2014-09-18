#pragma once
#pragma comment(lib, "detours.lib")

// Utils
#define sizeof_array(array) \
	((int)(sizeof(array) / sizeof(*(array))))

typedef struct {
	char *name;
	int size;
} StructField;


#define PATCHED 0