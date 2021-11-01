//
// Created by Daan Meijer on 28/10/2021.
//

#include "mem_utils.h"
#include "linkedlist.h"
#include "assert.h"
#include <stdlib.h>


static LinkedList *g_Allocated = NULL;

//static BlockInfo *CreateBlockInfo(void *pointer, size_t size) {
//    BlockInfo *ret;
//
//    ret = malloc(sizeof(BlockInfo));
//    if (!ret)
//        return (NULL);
//    ret->m_Pointer = pointer;
//    ret->m_Size = size;
//    return (ret);
//}

//TODO rename these functions to something like malloc_tracked
void *malloc_internal(size_t size) {
	void *ret;
	LinkedList *element;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	element = CreateElement(ret);
	Assert(element);
	AddBack(&g_Allocated, element);
	return ret;
}

void free_internal(void *pointer) {
	RemoveElements(&g_Allocated, &BlockEqual, pointer);
	free(pointer);
}

t_bool HasLeaks() {
	return (GetSize(g_Allocated));
}

t_bool BlockEqual(const void *blk1, const void *blk2) {
	const unsigned char *ptr1, *ptr2;

	ptr1 = blk1;
	ptr2 = blk2;
	return (ptr1 == ptr2);
}