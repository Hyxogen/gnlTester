//
// Created by Daan Meijer on 28/10/2021.
//

#include "test_utils.h"
#include "checker.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

static t_bool test_file_internal(int test_fd, FILE *stream) {
	char *test_ret;
	char *corr_ret;
	size_t line_cap;
	ssize_t getline_ret;

	test_ret = NULL;
	corr_ret = NULL;
	line_cap = 0;
	while (1) {
		test_ret = get_next_line(test_fd);
		getline_ret = getline(&corr_ret, &line_cap, stream);
		if ((getline_ret == -1) && !test_ret)
			return (TRUE);
		else if (getline_ret == -1)
			return (FALSE);
		else if (!check_string(test_ret, corr_ret)) {
			free(test_ret);
			free(corr_ret);
			return (FALSE);
		}
		if (!test_ret)
			break;
		free(test_ret);
	}
	return (TRUE);
}

t_bool test_file(const char *file) {
	int test_fd;
	FILE *stream;

	test_fd = open(file, O_RDONLY);
	stream = fopen(file, "r");
	if ((test_fd == -1) || (stream == NULL)) {
		raise(SIGTRAP);
		return (FALSE);
	}
	return (test_file_internal(test_fd, stream));
}