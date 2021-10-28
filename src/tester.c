/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 09:52:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/28 13:15:45 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/tester.h"
#include "checker.h"
#include "../../get_next_line.h"

static t_bool
	test_file_internal(int test_fd, FILE* stream)
{
	char    *test_ret;
	char    *corr_ret;
	size_t  line_cap;
	ssize_t getline_ret;

	test_ret = NULL;
	corr_ret = NULL;
	line_cap = 0;
	while (1)
	{
		test_ret = get_next_line(test_fd);
		getline_ret = getline(&corr_ret, &line_cap, stream);
		if ((getline_ret == -1) && !test_ret)
			return (TRUE);
		else if (!check_string(test_ret, corr_ret))
		{
			free(test_ret);
			free(corr_ret);
			return (FALSE);
		}
		if (!test_ret)
			break ;
		free(test_ret);
	}
	return (TRUE);
}

static t_bool
	test_file(const char *file)
{
	int     test_fd;
	FILE    *stream;

	test_fd = open(file, O_RDONLY);
	stream = fopen(file, "r");
	if ((test_fd == -1) || (stream == NULL))
	{
		raise(SIGTRAP);
		return (FALSE);
	}
	return (test_file_internal(test_fd, stream));
}

/*
 * No arguments will run tests for invalid fd
 */
int
	main(int argc, char **argv)
{
	if (argc > 2)
	{
		printf("Incorrect arguments. Usage: ./gnlTster [file]\n");
		return (-1);
	}
	return (0);
}
