/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_etc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:23:22 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 02:57:10 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		g_row_size;
int		g_col_size;
char	g_obstacle_char;
char	g_empty_char;

int		ft_mv_nextline(int fd, int size)
{
	char	*line;
	int		i;

	i = 0;
	if (!(line = (char *)malloc((size + 1) * sizeof(char))))
		return (0);
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	free(line);
	return (1);
}

void	ft_while_solve_map(int **r_map, char **input_map, int *data_store)
{
	int i;
	int j;

	i = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			if (input_map[i][j] == g_obstacle_char)
				r_map[i][j] = 0;
			else if (i == 0 || j == 0)
				r_map[i][j] = 1;
			else
				r_map[i][j] = ft_min(r_map[i - 1][j],
						r_map[i][j - 1], r_map[i - 1][j - 1]) + 1;
			if (r_map[i][j] > data_store[0])
			{
				data_store[0] = r_map[i][j];
				data_store[1] = i * g_row_size + j;
			}
			j++;
		}
		i++;
	}
}

void	ft_set_global_charset(char *line, int i)
{
	g_empty_char = line[i - 3];
	g_obstacle_char = line[i - 2];
	g_full_char = line[i - 1];
}

void	ft_set_charset_sidekick(char *line, char *charset)
{
	int	i;
	int result;

	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] != g_empty_char &&
				'0' <= line[i] && line[i] <= '9')
			result = result * 10 + line[i] - '0';
		else
			break ;
		i++;
	}
	g_col_size = result;
	charset[0] = line[i];
	charset[1] = line[i + 1];
	charset[2] = line[i + 2];
}
