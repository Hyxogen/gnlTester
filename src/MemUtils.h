//
// Created by Daan Meijer on 28/10/2021.
//

#ifndef GNLTESTER_MEM_UTILS_H
#define GNLTESTER_MEM_UTILS_H

#include <wchar.h>
#include "../include/tester.h"

typedef struct S_BlockInfo {
	void *m_Pointer;
	size_t m_Size;
} BlockInfo;

void *MallocTracked(size_t size);

void FreeTracked(void *pointer);

void LogPointer(const void *pointer);

void LogMemDump();

void ClearLeakCheck();

int HasLeaks();

//TODO rename to something more appropriate like pointer equal
t_bool PointerEqual(const void *blk1, const void *blk2);

//Sets malloc to fail on the n'th time of using it. Set to -1 to never fail
void SetMallocFaiL(int n);

#endif //GNLTESTER_MEM_UTILS_H
