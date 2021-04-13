/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:26:09 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 02:34:10 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int		g_row_size;
int		g_col_size;

void	ft_count_row_size(int fd)
{
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		i++;
	}
	g_row_size = i;
}

int		ft_set_charset(char *file, int size)
{
	char	*line;
	int		i;
	int		fd;
	char	charset[4];

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if (!(line = malloc((size + 1) * sizeof(char))))
		return (0);
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	ft_set_global_charset(line, i);
	ft_count_row_size(fd);
	ft_set_charset_sidekick(line, charset);
	close(fd);
	free(line);
	if (charset[0] == g_empty_char && charset[1] == g_obstacle_char &&
			charset[2] == g_full_char)
		return (1);
	return (0);
}

int		ft_count_file_size(char *file)
{
	char	c;
	int		fd;
	int		size;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	size = 0;
	while (read(fd, &c, 1))
		size++;
	close(fd);
	return (size);
}

char	*ft_push_array_keyboard(char *keyboard_array, int *i)
{
	if (*i == 0)
		return (keyboard_array);
	keyboard_array += *i * g_row_size;
	while (*keyboard_array != '\0')
	{
		if (*keyboard_array == '\n')
		{
			*keyboard_array = 0;
			break ;
		}
		keyboard_array++;
	}
	keyboard_array++;
	return (keyboard_array);
}

char	**ft_set_input_map(char *file, int size, char *keyboard_array)
{
	int		fd;
	int		i;
	char	**map;

	map = NULL;
	i = 0;
	if (!(map = (char **)malloc((g_col_size + 1) * sizeof(char *))))
		return (0);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		while (i < g_col_size)
			map[i++] = ft_push_array_keyboard(keyboard_array, &i);
		return (map);
	}
	ft_mv_nextline(fd, size);
	while (i < g_col_size)
		map[i++] = ft_push_array(fd);
	close(fd);
	return (map);
}
