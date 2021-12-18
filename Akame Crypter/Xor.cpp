#include "Includes.h"

void XOR(DWORD baseAddress, DWORD dwSize) {
	__asm {
		// Moving the base address of the memblock & adding the size of the memory block to the ECX register
		push eax
		push ecx
		mov ecx, baseAddress
		add ecx, dwSize
		mov eax, baseAddress
		
		// Decryption loop
		encryption:
		xor byte ptr ds : [eax], 0x7F // Xor the byte with 0x7F
			inc eax
			cmp eax, ecx
		jl encryption;

		pop ecx
		pop eax
	}
}