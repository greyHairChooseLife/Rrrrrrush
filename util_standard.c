/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_standard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 04:11:33 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 08:05:21 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_standard_read(char **map)
{
	char	*map_key;
	int		i;
	int		temp;
	char	checker;

	map_key = NULL;
	map_key = malloc_for_keyboard(map_key, &i, &checker);
	get_col_size(map_key);
	if ((temp = read_keyboard(map_key)) == 1 ||
			(ck_ex_ac2(i, map_key) == 1) ||
				ck_ex_ac1(checker, i) == 1)
	{
		free(map_key);
		return (0);
	}
	if ((map = ft_set_input_map(map_key, 5, map_key)))
		ft_bsq_solution(map);
	free(map_key);
	return (1);
}
