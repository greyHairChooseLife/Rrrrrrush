/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 00:20:30 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 05:07:20 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char *argv[])
{
	char	**map;
	int		i;

	i = 1;
	map = NULL;
	if (argc > 1)
	{
		while (i < argc)
		{
			if ((map = ft_valid_argv(argv[i++])))
				ft_bsq_solution(map);
			if (i != argc)
				write(1, "\n", 1);
		}
	}
	else
		ft_standard_read(map);
	i = 0;
	/*
	while (map[i])
		free(map[i++]);
		*/
	return (0);
}
