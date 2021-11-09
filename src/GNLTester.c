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
#include "ProfilingUtils.h"


/*
 * No arguments will run tests for invalid fd
 *
 * TODO Make benchmark tests (and timeouts)
 * TODO Add capability to check who called malloc (for checking for leaks)
 * TODO fix bonus checks
 */
int main(int argc, char **argv) {
	int ret;

	LogStart();
	LogF("------Starting tests for BUFFER_SIZE:%d argc:%d, argv[1]:\"%s\"------\n", BUFFER_SIZE, argc, argv[1]);
	ret = 0;
	if (argc > 2) {
		ClearLeakCheck();
		if (!TestFilesBonus(argc - 1, argv + 1))
			ret |= 0b0001000;
		LogF("Completed bonus tests!\n");
	} else if (argc == 2) {
#ifdef TEST_MANDATORY
#ifdef TESTER_PROFILER_ENABLE
		StartProfiler();
		ClearProfilerData();
#endif
		ClearLeakCheck();
		if (!TestFileNormal(argv[1]))
			ret |= 0b0000001;
		LogF("Completed normal tests\n\n");
		#ifdef TESTER_PROFILER_ENABLE
		StopProfiler();
		LogProfileData();
#endif
#endif
#ifdef TEST_MALLOC_FAIL
		ClearLeakCheck();
		if (!TestFileMallocFail(argv[1]))
			ret |= 0b0000010;
		LogF("Completed tests with malloc fails\n\n");
#endif
#ifdef TEST_READ_FAIL
		ClearLeakCheck();
		if (!TestFileReadFail(argv[1]))
			ret |= 0b0000100;
		LogF("Completed tests with read fails\n\n");
#endif
	}
	LogStop();
	LogF("------Completed all tests------\n");
	return (ret);
}
