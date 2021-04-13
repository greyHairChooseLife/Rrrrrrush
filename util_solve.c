/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:42:22 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 08:09:06 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int		g_row_size;
int		g_col_size;

char	*ft_push_array(int fd)
{
	char	*array;
	int		i;

	if (!(array = malloc((g_row_size + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (read(fd, &array[i], 1))
	{
		if (array[i] == '\n')
		{
			array[i] = 0;
			break ;
		}
		i++;
	}
	return (array);
}

int		**ft_malloc_solve_map(void)
{
	int	i;
	int	**resolve_map;

	i = 0;
	if (!(resolve_map = (int **)malloc((g_col_size + 1) * sizeof(int *))))
		return (0);
	while (i < g_col_size)
	{
		if (!(resolve_map[i] = (int *)malloc((g_row_size + 1) * sizeof(int))))
			return (0);
		i++;
	}
	return (resolve_map);
}

int		**ft_input_solve_map(char **input_map, int *data_store)
{
	int	max_size;
	int	**r_map;

	max_size = 0;
	if (!(r_map = ft_malloc_solve_map()))
		return (0);
	data_store[0] = 0;
	data_store[1] = 0;
	ft_while_solve_map(r_map, input_map, data_store);
	return (r_map);
}

char	**ft_solve_map(char **input_map)
{
	int	i;
	int	j;
	int	**resolve_map;
	int	data_store[3];

	resolve_map = ft_input_solve_map(input_map, data_store);
	i = 0;
	j = 0;
	if (g_row_size != 0)
	{
		i = (data_store[1] / g_row_size) - data_store[0] + 1;
		while (i < (data_store[1] / g_row_size) + 1)
		{
			j = (data_store[1] % g_row_size) - data_store[0] + 1;
			while (j < (data_store[1] % g_row_size) + 1)
			{
				input_map[i][j] = g_full_char;
				j++;
			}
			i++;
		}
	}
	return (input_map);
}

void	ft_bsq_solution(char **input_map)
{
	char	**map;
	int		i;
	int		j;

	map = ft_solve_map(input_map);
	i = 0;
	j = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			write(1, &input_map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
