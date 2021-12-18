#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


using namespace std;

// Functions
void XOR(DWORD baseAddress, DWORD dwSize);
void hexDump(void* addr, int len);