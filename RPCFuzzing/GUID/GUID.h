#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <stdio.h>
#include "../main.h"

void DumpGuid(
	FILE *output,
	char *prefix,
	GUID *guid
);