/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_keyboard_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 03:08:51 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 07:55:05 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		g_col_size;

char	*malloc_for_keyboard(char *map_keyboard, int *i, char *checker)
{
	if (!(map_keyboard = (char *)malloc(sizeof(char) * 50001)))
		write(2, "malloc fail_Error\n", 18);
	read(0, map_keyboard, 50000);
	*i = get_3_simbols(*i, map_keyboard, checker);
	return (map_keyboard);
}

int		get_3_simbols(int i, char *map_keyboard, char *checker)
{
	i = 0;
	while (map_keyboard[i] != '\n')
		i++;
	*checker = map_keyboard[i - 4];
	g_empty_char = map_keyboard[i - 3];
	g_obstacle_char = map_keyboard[i - 2];
	g_full_char = map_keyboard[i - 1];
	return (i);
}

void	get_col_size(char *m_kbd)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (1 == 1)
	{
		if (m_kbd[i + 3] != '\n' && '0' <= m_kbd[i] && m_kbd[i] <= '9')
			temp = temp * 10 + m_kbd[i++] - '0';
		else
			break ;
	}
	g_col_size = temp;
}

int		read_keyboard(char *map_keyboard)
{
	int i;
	int temp;
	int temp2;

	i = 0;
	while (i < g_col_size)
	{
		temp = read(0, map_keyboard, 50000);
		map_keyboard += temp;
		i++;
		if (i == 1)
			temp2 = temp;
		if (i >= 2 && temp2 != temp)
		{
			write(2, "map error\n", 10);
			return (1);
		}
		if (temp == 1)
		{
			write(2, "map error\n", 10);
			return (1);
		}
	}
	g_row_size = temp - 1;
	return (temp);
}
