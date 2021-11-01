/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 10:01:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/28 13:15:51 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include <string.h>

t_bool check_string(const char *str, const char *expected) {
	if (!str)
		return (!expected);
	return (!strcmp(expected, str));
}
