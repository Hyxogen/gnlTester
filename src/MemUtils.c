//
// Created by Daan Meijer on 28/10/2021.
//

#include "MemUtils.h"
#include "LinkedList.h"
#include "Assert.h"
#include <stdlib.h>


static LinkedList *g_Allocated = NULL;
static int g_MallocFail = -1;

//TODO rename these functions to something like malloc_tracked
void *MallocTracked(size_t size) {
	void *ret;
	LinkedList *element;
	if (!g_MallocFail)
		return (NULL);
	else if (g_MallocFail > 0)
		g_MallocFail--;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	element = CreateElement(ret);
	ASSERT(element);
	AddBack(&g_Allocated, element);
	printf("Alloc %zu bytes!\n", size);
	return ret;
}

void FreeTracked(void *pointer) {
	RemoveElements(&g_Allocated, &BlockEqual, pointer);
	free(pointer);
}

int HasLeaks() {
	return (GetSize(g_Allocated));
}

void ClearLeakCheck() {
	ClearList(&g_Allocated);
}

t_bool BlockEqual(const void *blk1, const void *blk2) {
	const unsigned char *ptr1, *ptr2;

	ptr1 = blk1;
	ptr2 = blk2;
	return (ptr1 == ptr2);
}

void SetMallocFaiL(int n) {
	g_MallocFail = n;
}