/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:13:49 by obouftou          #+#    #+#             */
/*   Updated: 2025/03/10 01:23:43 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	pid_check(char *pid_str)
{
	int	i;
	int	pid;

	i = 0;
	while (pid_str[i])
	{
		if (pid_str[i] < '0' || pid_str[i] > '9')
		{
			ft_putstr_fd("PID has non-digit chars.\n" "\e[0m", 2);
			return (0);
		}
		i++;
	}
	pid = atoi(pid_str);
	if (pid <= 0)
	{
		ft_putstr_fd("PID must be positive.\n" "\e[0m", 2);
		return (0);
	}
	return (pid);
}

void	send_signl(int pid, char x)
{
	int	sig;
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (x & (1 << bit))
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
		{
			ft_putstr_fd("Invalid PID. Signal failed.\n" "\e[0m", 2);
			exit(1);
		}
		usleep(500);
		bit++;
	}
}

void	print_done(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("Message DONE. \n" "\e[0m", 1);
}

int	main(int ac, char **av)
{
	int	pid;
	int	x;

	x = 0;
	if (ac == 3 && av[2][0] != '\0')
	{
		pid = atoi(av[1]);
		if (pid < 99999)
		{
			ft_putstr_fd( "Valid PID.\n" "\e[0m", 1);
			signal(SIGUSR1, print_done);
			while (av[2][x])
				send_signl(pid, av[2][x++]);
			send_signl(pid, '\0');
		}
		else
			ft_putstr_fd("Invalid PID. Signal failed.\n" "\e[0m", 2);
	}
	else
	{
		ft_putstr_fd( "Invalid args or empty msg.\n" "\e[0m", 2);
		ft_putstr_fd( "Usage: ./client [PID] [MSG]\n" "\e[0m", 2);
	}
	return (0);
}
