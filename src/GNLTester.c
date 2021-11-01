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


/*
 * No arguments will run tests for invalid fd
 */
int main(int argc, char **argv) {
	int ret;

	ret = 0;
	if (argc > 2) {
		printf("Incorrect arguments. Usage: ./gnlTster [file]\n");
		return (-1);
	} else if (argc == 2) {
		if (!TestFileNormal(argv[1]))
			ret |= 0b0000001;
		if (HasLeaks())
			ret |= 0b0000010;
		ClearLeakCheck();
		if (!TestFileFail(argv[1]))
			ret |= 0b0000100;
		//TODO check for memory leaks if malloc fails in between
		if (!ret)
			printf("Passed tests!\n");
		else
			printf("Failed tests!\n");
		return (ret);
	}
	return (ret);
}
