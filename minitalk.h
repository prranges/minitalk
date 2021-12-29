/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:56:00 by prranges          #+#    #+#             */
/*   Updated: 2021/09/02 15:56:01 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

int		error_quit(char *s, char programm);
int		check_pid(char *argv);
char	*str_add_char(char *s, char c);

#endif
