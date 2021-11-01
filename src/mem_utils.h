//
// Created by Daan Meijer on 28/10/2021.
//

#ifndef GNLTESTER_MEM_UTILS_H
#define GNLTESTER_MEM_UTILS_H

#include <wchar.h>
#include "../include/tester.h"

void malloc(size_t size);
t_bool hasLeaks();
void clearLeakCheck();

#endif //GNLTESTER_MEM_UTILS_H
