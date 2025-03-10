/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:18:43 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/03/10 17:34:06 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	print_buff(char *buffer, int *buff_i, int *pid, int *res_byte)
{
	if (buffer[*buff_i - 1] == '\0')
		kill(*pid, SIGUSR1);
	else
		write(1, buffer, *res_byte);
	*buff_i = 0;
	clear_buffer(buffer);
	*res_byte = 0;
}

int	get_expected_bytes(char *c)
{
	if ((*c & 0x80) == 0x00)
		return (1);
	else if ((*c & 0xE0) == 0xC0)
		return (2);
	else if ((*c & 0xF0) == 0xE0)
		return (3);
	else if ((*c & 0xF8) == 0xF0)
		return (4);
	return (0);
}

void	process_message(char *buffer, int *buff_i, int *pid,
	int *expected_bytes)
{
	(*buff_i)++;
	if (*expected_bytes == 0)
		*expected_bytes = get_expected_bytes(&buffer[0]);
	if (*buff_i == *expected_bytes)
	{
		print_buff(buffer, buff_i, pid, expected_bytes);
	}
}

void	handel_sig(int sin, siginfo_t *info, void *context)
{
	static int	pid;
	static int	count_bit;
	static char	buffer[4];
	static int	buff_i;
	static int	expected_bytes;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid)
	{
		set_variabl(&pid, &count_bit, &buff_i, &expected_bytes);
		clear_buffer(buffer);
		pid = info->si_pid;
	}
	if (sin == SIGUSR1)
		buffer[buff_i] |= (1 << (count_bit % 8));
	count_bit++;
	if (count_bit % 8 == 0)
	{
		process_message(buffer, &buff_i, &pid, &expected_bytes);
		count_bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sin;
	int					pid;

	pid = getpid();
	ft_putstr_fd(CY "Server PID: \e[0m", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n" GRN "Waiting...\n" "\e[0m", 1);
	sin.sa_sigaction = handel_sig;
	sin.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sin, NULL);
	sigaction(SIGUSR2, &sin, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
