/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:17:16 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/13 23:22:02 by jimikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int		ft_min(int a, int b, int c)
{
	int result;

	result = 0;
	result = a < b ? a : b;
	result = result < c ? result : c;
	return (result);
}

char	*ft_strdup(char *src)
{
	int		size;
	char	*dest;
	int		i;

	i = 0;
	size = ft_strlen(src);
	if (!(dest = (char *)malloc((i + 1) * sizeof(char))))
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i - 1] = '\0';
	return (dest);
}
