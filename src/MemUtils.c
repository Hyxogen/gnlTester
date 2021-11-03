//
// Created by Daan Meijer on 28/10/2021.
//

#include "MemUtils.h"
#include "LinkedList.h"
#include "Assert.h"
#include <stdlib.h>
#include "Logger.h"

static LinkedList *g_Allocated = NULL;
static int g_MallocFail = -1;

void *MallocTracked(size_t size) {
	void *ret;
	LinkedList *element;
	if (!g_MallocFail) {
		g_MallocFail--;
		return (NULL);
	} else if (g_MallocFail > 0)
		g_MallocFail--;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	element = CreateElement(ret);
	ASSERT(element);
	AddBack(&g_Allocated, element);
	LogF("Alloc %p size %zu\n", ret, size);
	return ret;
}

void FreeTracked(void *pointer) {
	RemoveElements(&g_Allocated, &PointerEqual, pointer);
	free(pointer);
}

void LogPointer(const void *pointer) {
	LogF("Pointer:%p\n", pointer);
}

void LogMemDump() {
	LogF("------Allocated heap memory(%zu)------\n", GetSize(g_Allocated));
	ForEachElement(g_Allocated, &LogPointer);
	LogF("------------------------------------\n");
}

int HasLeaks() {
	return (GetSize(g_Allocated));
}

void ClearLeakCheck() {
	LogF("Clearing leak check\n");
	ClearList(&g_Allocated);
}

t_bool PointerEqual(const void *blk1, const void *blk2) {
	const unsigned char *ptr1, *ptr2;

	ptr1 = blk1;
	ptr2 = blk2;
	return (ptr1 == ptr2);
}

void SetMallocFaiL(int n) {
	g_MallocFail = n;
}