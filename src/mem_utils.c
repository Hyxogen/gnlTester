//
// Created by Daan Meijer on 28/10/2021.
//

#include "mem_utils.h"

void* malloc_internal(size_t size)
{
	void* (*libc_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");
	printf("Allocating for size:%zu\n", size);
	return libc_malloc(size);
}

void free_internal(void* pointer)
{
    void (*libc_free)(void*) = dlsym(RTLD_NEXT, "free");
    printf("Freeing!\n");
    libc_free(pointer);
}