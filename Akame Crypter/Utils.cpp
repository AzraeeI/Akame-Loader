#include "Includes.h"

void hexDump(void* addr, int len) {
	unsigned int i; // int i;
	unsigned char buff[17], * pc = (unsigned char*)addr;
	for (i = 0; i < len; i++) {
		if ((i % 16) == 0) {
			if (i != 0)
				printf(" %s\n", buff); // don't print the zeroth ASCII
			printf(" %04x ", i);
		}
	}
}