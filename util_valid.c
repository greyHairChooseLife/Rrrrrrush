/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:58:00 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 02:05:37 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	g_empty_char;
char	g_obstacle_char;
char	g_full_char;
int		g_row_size;
int		g_col_size;

int		ft_check_row_newline(char *file, int size)
{
	char	*line;
	int		fd;

	if (!(line = (char *)malloc((size + 1) * sizeof(char))))
		return (0);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	ft_mv_nextline(fd, size);
	while (read(fd, line, g_row_size + 1))
	{
		if (line[g_row_size] != '\n')
			return (0);
	}
	close(fd);
	free(line);
	return (1);
}

int		ft_valid_row(char **map)
{
	int	i;
	int	before_size;

	i = 1;
	before_size = ft_strlen(map[0]);
	while (map[i])
	{
		if (before_size != ft_strlen(map[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_valid_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			if (!(map[i][j] == g_empty_char || map[i][j] == g_obstacle_char ||
						map[i][j] == '\n' || map[i][j] == 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_valid_charset(void)
{
	if ((g_empty_char == g_full_char ||
				g_empty_char == g_obstacle_char ||
				g_full_char == g_obstacle_char))
		return (0);
	if (!(32 <= g_empty_char || g_empty_char == 127))
		return (0);
	if (!(32 <= g_full_char || g_full_char == 127))
		return (0);
	if (!(32 <= g_obstacle_char || g_obstacle_char == 127))
		return (0);
	return (1);
}

char	**ft_valid_argv(char *file)
{
	int		file_size;
	int		col_size;
	char	**map;

	map = NULL;
	if (!(file_size = ft_count_file_size(file)) ||
			!(col_size = ft_set_charset(file, file_size)) ||
			!(ft_check_row_newline(file, file_size)) ||
			!(map = ft_set_input_map(file, file_size, NULL)))
	{
		write(2, "map error\n", 10);
		return (0);
	}
	if (!ft_valid_map(map) || !ft_valid_row(map) ||
			!ft_valid_charset() || g_col_size < 1 || g_row_size < 2)
	{
		write(2, "map error\n", 10);
		return (0);
	}
	return (map);
}
