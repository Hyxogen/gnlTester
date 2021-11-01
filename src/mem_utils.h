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

void *malloc_internal(size_t size);

void free_internal(void *pointer);

void ClearLeakCheck();

t_bool HasLeaks();

t_bool BlockEqual(const void *blk1, const void *blk2);
#endif //GNLTESTER_MEM_UTILS_H
