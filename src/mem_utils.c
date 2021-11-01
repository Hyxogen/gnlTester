//
// Created by Daan Meijer on 28/10/2021.
//

#include "mem_utils.h"
#include <dlfcn.h>

void malloc(size_t size)
{
	void ((void*)(*libc_malloc))(size_t) = dlsym("malloc");
}