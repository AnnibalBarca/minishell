/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:04:33 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/10 16:23:16 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i])
		i++;
	dup = ft_malloc(sizeof(char) * i + 1, g_signal.node);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	char	*tab;

// 	tab = ft_strdup("123");
// 	printf("%s", tab);
// }
