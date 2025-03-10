/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:11:26 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/03/09 23:25:29 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
#define MINITALK_BONUS_H

# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
#include<stdio.h>

# define PUR "\033[0;35m"
# define CY "\033[0;36m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"

// int			ft_atoi(const char *str);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

#endif