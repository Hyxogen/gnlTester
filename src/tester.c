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
#include "test_utils.h"


/*
 * No arguments will run tests for invalid fd
 */
int main(int argc, char **argv) {
	if (argc > 2) {
		printf("Incorrect arguments. Usage: ./gnlTster [file]\n");
		return (-1);
	} else if (argc == 2) {
		if (test_file(argv[1]))
			printf("Passed tests!\n");
		else
			printf("Failed tests\n");
		return (0);
	}
	return (0);
}