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
	if (corrNextStr == NULL)
		return (testNextStr == NULL);
	if (!testNextStr) {
		printf("Unexpected EOF!\n");
		return (FALSE);
	}
	equal = !strcmp(testNextStr, corrNextStr); //CRASH HERE
	if (!equal)
		printf("Expected:\"%s\"\nGot:\"%s\"\n", corrNextStr, testNextStr);
	FreeTracked(testNextStr);
	if (HasLeaks()) {
		printf("Leaks!\n");
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
static t_bool CheckFail(int fd, const char *corrNextStr) {
	char *testNextStr;

	SetMallocFaiL(1);
	testNextStr = get_next_line(fd);
	if (corrNextStr)
		;
	if (testNextStr != NULL)
		return (FALSE);
	return (!HasLeaks());
}

t_bool TestFileNormal(const char *file) {
	int test_fd;
	FILE *stream;
	t_bool ret;

	test_fd = open(file, O_RDONLY);
	stream = fopen(file, "r");
	ASSERT((test_fd != -1) && (stream != NULL));
	ret = FileForEachLine(stream, test_fd, &CheckNormal);
	fclose(stream);
	close(test_fd);
	return (ret);
}

t_bool TestFileFail(const char *file) {
	int test_fd;
	FILE *stream;
	t_bool ret;

	test_fd = open(file, O_RDONLY);
	stream = fopen(file, "r");
	ASSERT((test_fd != -1) && (stream != NULL));
	ret = FileForEachLine(stream, test_fd, &CheckFail);
	fclose(stream);
	close(test_fd);
	return (ret);
}