/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:25:18 by prranges          #+#    #+#             */
/*   Updated: 2021/09/13 13:25:21 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	error_quit(char *s, char programm)
{
	if (s)
		free(s);
	if (programm == 'c')
		ft_putstr_fd("client: Error\n", 2);
	if (programm == 's')
		ft_putstr_fd("server: Error\n", 2);
	exit(EXIT_FAILURE);
}

int	check_pid(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

char	*add_char(char c)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * 2);
	if (!res)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	return (res);
}

char	*str_add_char(char *s, char c)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		res = add_char(c);
	else
	{
		i = -1;
		res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
		if (!res)
		{
			free(s);
			return (NULL);
		}
		while (s[++i])
			res[i] = s[i];
	}
	free(s);
	res[i] = c;
	res[++i] = '\0';
	return (res);
}
