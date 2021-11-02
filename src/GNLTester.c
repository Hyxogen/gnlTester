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
#include "../../get_next_line.h"
#include "TestUtils.h"
#include "MemUtils.h"
#include "Logger.h"


/*
 * No arguments will run tests for invalid fd
 *
 * TODO Make benchmark tests (and timeouts)
 * TODO Make logging system
 */
int main(int argc, char **argv) {
	int ret;

	LogStart();
	LogF("------Starting tests for BUFFER_SIZE:%d argc:%d, argv[1]:\"%s\"------\n", BUFFER_SIZE, argc, argv[1]);
	ret = 0;
	if (argc > 2) {
		LogF("Received incorrect number of arguments!\n");
		printf("Incorrect arguments. Usage: ./gnlTester [file]\n");
		LogStop();
		return (-1);
	} else if (argc == 2) {
		ClearLeakCheck();
		if (!TestFileNormal(argv[1]))
			ret |= 0b0000001;
		LogF("Completed normal tests\n");
		if (HasLeaks())
			ret |= 0b0000010;
		ClearLeakCheck();
		if (!TestFileMallocFail(argv[1]))
			ret |= 0b0000100;
		LogF("Completed tests with malloc fails\n");
		ClearLeakCheck();
		if (!TestFileReadFail(argv[1]))
			ret |= 0b0001000;
		LogF("Completed tests with read fails\n");
		if (!ret)
			printf("Passed tests!\n");
		else
			printf("Failed tests!\n");
		LogF("------Completed all tests------");
		LogStop();
		return (ret);
	}
	LogStop();
	return (ret);
}
