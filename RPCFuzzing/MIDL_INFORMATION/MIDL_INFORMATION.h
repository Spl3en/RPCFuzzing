#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include "../main.h"

typedef struct {
	void * pStubDesc;
	void * ServerRoutineTable;
	
} MIDL_INFORMATION, *PMIDL_INFORMATION;

void DumpMidlInformation(
	FILE *output,
	char *prefix,
	MIDL_INFORMATION *pMidlInformation,
	int procNum
);