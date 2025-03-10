/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:10:37 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/03/10 21:44:10 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handel_sig(int sig, siginfo_t *siga_info, void *oldact)
{
	static char c = 0;
	static int bit = 0;
	static pid_t last_pid = 0;
	(void)oldact;

	if(last_pid != 0 && last_pid != siga_info->si_pid)
	{
		c = 0;
		bit = 0;
		last_pid = 0;
	}
	last_pid = siga_info->si_pid;

	if(sig == SIGUSR1)
			c = (c << 1 | 0);
	else if(sig == SIGUSR2)
			c = (c << 1) | 1;
		bit++;
	if(bit == 8)
	{
		write (1, &c, 1);
		bit = 0;
		c  = 0;
	}

}
int main()
{
	struct sigaction siga;
	
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = SA_SIGINFO;
	siga.sa_sigaction = handel_sig;
	
	int pid = getpid();
	ft_putstr_fd(CY "Server PID: \e[0m", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n" GRN "Waiting...\n" "\e[0m", 1);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while (1)
		pause();
}
// int main()
// {
//     struct sigaction siga;

//     int pid = getpid();
//     siga.sa_sigaction = handel_sig;
//     siga.sa_flags = SA_SIGINFO;
//     printf("%d\n", pid);
//     //  sigemptyset(&siga.sa_mask);
//     sigaction(SIGUSR1, &siga, NULL);
//     sigaction(SIGUSR2, &siga, NULL);
//     while(1)
//         pause();
// }