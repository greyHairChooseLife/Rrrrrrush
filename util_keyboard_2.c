/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_keyboard_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 03:19:50 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 07:50:24 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ck_ex_ac1(char checker, int i)
{
	if (i < 4 || g_empty_char < 32 || g_obstacle_char < 32 || g_full_char < 32)
	{
		write(2, "map error\n", 10);
		return (1);
	}
	if (checker > 57 || checker < 48)
	{
		write(2, "map error\n", 10);
		return (1);
	}
	return (0);
}

int		ck_ex_ac2(int i, char *m)
{
	i = 0;
	if (g_empty_char == g_obstacle_char ||
			g_empty_char == g_full_char ||
			g_obstacle_char == g_full_char)
	{
		write(2, "map error\n", 10);
		return (1);
	}
	while (m[i] != '\n')
		i++;
	while (m[i] != '\0')
	{
		if (m[i] != g_empty_char && m[i] != g_obstacle_char && m[i] != '\n')
		{
			write(2, "map error\n", 10);
			return (1);
		}
		i++;
	}
	return (0);
}
