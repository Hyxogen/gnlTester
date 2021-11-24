//
// Created by Daan Meijer on 28/10/2021.
//

#ifndef GNLTESTER_TEST_UTILS_H
#define GNLTESTER_TEST_UTILS_H

#include "../include/tester.h"
#include <stdio.h>

typedef struct S_TestFile {
	int m_FileDescriptor;
	FILE *m_Stream;
	const char *m_FileName;
} TestFile;

TestFile *CreateTestFile(const char *file);

void DeleteTestFile(void *testFilePointer);

t_bool TestFilesBonus(int file_count, char **files);

t_bool TestFileNormal(const char *file);

t_bool TestFileMallocFail(const char *file);

t_bool TestFileReadFail(const char *file);
#endif //GNLTESTER_TEST_UTILS_H
