//
// Created by Daan Meijer on 28/10/2021.
//

#include "TestUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "Assert.h"
#include "MemUtils.h"
#include "ReadUtils.h"
#include "Logger.h"
#include "LinkedList.h"

static t_bool FileForEachLine(FILE *stream, int fd, t_bool (*check)(int, const char *)) {
	char *corr_str;
	size_t line_cap;
	ssize_t ret;

	corr_str = NULL;
	while (1) {
		ret = getline(&corr_str, &line_cap, stream);
		if (ret == -1)
			return (check(fd, NULL));
		else if (!check(fd, corr_str)) {
			free(corr_str);
			return (FALSE);
		}
	}
	return (TRUE);
}

/**
 * Checks if the next line of get_next_line equals corrNextStr
 *
 * @param fd
 * @param corrNextStr
 * @return TRUE if check passed
 */
static t_bool CheckNormal(int fd, const char *corrNextStr) {
	char *testNextStr;
	t_bool equal;

	testNextStr = get_next_line(fd);
	if (corrNextStr == NULL) {
		if (!testNextStr)
			return (TRUE);
		LogF("Expected end of file. Got:\n\"%s\"\n", testNextStr);
		return (FALSE);
	}
	if (!testNextStr) {
		LogF("Unexpected end of file. Expected:\n\"%s\"\n", corrNextStr);
		return (FALSE);
	}
	equal = !strcmp(testNextStr, corrNextStr); //CRASH HERE
	if (!equal)
		LogF("Expected:\"%s\"\nGot:\"%s\"\n", corrNextStr, testNextStr);
	FreeTracked(testNextStr);
	if (HasLeaks()) {
		LogF("Found leaks!\n");
		LogMemDump();
		return (FALSE);
	}
	return (equal);
}

/**
 * Checks if the next call of get_next_line with a malloc failure
 * has no leaks, and if the return value is correct
 *
 * @param fd
 * @param corrNextStr
 * @return TRUE if check passed
 */
static t_bool CheckMallocFail(int fd, const char *corrNextStr) {
	char *testNextStr;

	SetMallocFaiL(0);
	testNextStr = get_next_line(fd);
	if (corrNextStr)
		;
	if (testNextStr != NULL)
		return (FALSE);
	return (!HasLeaks());
}

/**
 * Checks if the next call of get_next_line with a read failure
 * has no leaks, and if the return value is correct
 *
 * @param fd
 * @param corrNextStr
 * @return TRUE if check passed
 */
static t_bool CheckReadFail(int fd, const char *corrNextStr) {
	char *testNextStr;

	SetReadFail(0);
	testNextStr = get_next_line(fd);
	if (corrNextStr)
		;
	if (testNextStr != NULL) {
		LogF("Expected null!\n");
		LogF("Got:\"%s\"\n", testNextStr);
		return (FALSE);
	}
	if (HasLeaks()) {
		LogF("Found leak!\n");
		LogMemDump();
		return (FALSE);
	}
	return (TRUE);
}

static t_bool RunTests(const char *file, t_bool (*check)(int, const char *)) {
	int test_fd;
	FILE *stream;
	t_bool ret;

	SetReadFail(-1);
	SetMallocFaiL(-1);
	test_fd = open(file, O_RDONLY);
	stream = fopen(file, "r");
	ASSERT((test_fd != -1) && (stream != NULL));
	ret = FileForEachLine(stream, test_fd, check);
	fclose(stream);
	close(test_fd);
	return (ret);
}

TestFile *CreateTestFile(const char *file) {
	TestFile *ret;

	ret = malloc(sizeof(TestFile));
	ret->m_FileDescriptor = open(file, O_RDONLY);
	ASSERT(ret->m_FileDescriptor >= 0);
	ret->m_Stream = fopen(file, "r");
	ASSERT(ret->m_Stream);
	ret->m_FileName = file;
	return (ret);
}

void DeleteTestFile(void *testFilePointer) {
	TestFile *testFile;

	testFile = testFilePointer;
	fclose(testFile->m_Stream);
	close(testFile->m_FileDescriptor);
	free(testFile);
}

static t_bool RunBonusTests(int file_count, char **files, t_bool (*check)(int, const char *)) {
	static LinkedList *fileList = NULL;
	LinkedList *current;
	LinkedList *last;
	TestFile *testFile;
	int should_return;
	char *corr_str;
	ssize_t func_ret;
	size_t line_size;

	should_return = file_count;
	corr_str = NULL;
	while (file_count) {
		AddBack(&fileList, CreateElement(CreateTestFile(*files)));
		files++;
		file_count--;
	}

	last = GetLastElement(fileList);
	last->m_Next = fileList;
	current = fileList;
	while (file_count < should_return) {
		testFile = current->m_Content;
		func_ret = getline(&corr_str, &line_size, testFile->m_Stream);
		if ((func_ret == -1) && (!check(testFile->m_FileDescriptor, NULL)))
			return (FALSE);
		else if ((func_ret != -1) && (!check(testFile->m_FileDescriptor, corr_str)))
			return (FALSE);
		if (func_ret == -1)
			file_count++;
		else
			file_count = 0;
		current = current->m_Next;
	}
	last->m_Next = NULL;
	ClearListWithElements(&fileList, &DeleteTestFile);
	return (TRUE);
}

t_bool TestFilesBonus(int file_count, char **files) {
	LogF("Starting bonus tests for files\n");
	return (RunBonusTests(file_count, files, &CheckNormal));
}

t_bool TestFileNormal(const char *file) {
	LogF("Starting normal tests for file \"%s\"\n", file);
	return (RunTests(file, &CheckNormal));
}

t_bool TestFileMallocFail(const char *file) {
	LogF("Starting tests with malloc fails for file \"%s\"\n", file);
	return (RunTests(file, &CheckMallocFail));
}

t_bool TestFileReadFail(const char *file) {
	LogF("Starting tests with read fails for file \"%s\"\n", file);
	return (RunTests(file, &CheckReadFail));
}