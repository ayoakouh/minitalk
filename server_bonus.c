/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:41:49 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/03/08 17:02:49 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk_bonus.h"

void	reset_vars(unsigned char *c, int *bit, int *buffer_i, pid_t *last_pid)
{
	*c = 0;
	*bit = 0;
	*buffer_i = 0;
	*last_pid = 0;
}

void	process_signal(int sig, unsigned char *c, int *bit)
{
	if (sig == SIGUSR1)
		*c = (*c << 1 | 0);
	else if (sig == SIGUSR2)
		*c = (*c << 1) | 1;
	(*bit)++;
}
void print_buffer(char *buffer, int *buffer_i, int pid)
{
    int i;

    i = 0;
    while(i < *buffer_i)
    {
        ft_putchar_fd(buffer[i], 1);
        i++;
    }
    if (buffer[*buffer_i - 1] == '\0')
        kill(pid, SIGUSR1);
    *buffer_i = 0;
}





void	handel_sig(int sig, siginfo_t *siga_info, void *oldact)
{
	static char				buffer[4] = {0};
	static int				buffer_i = 0;
	static unsigned char	c = 0;
	static int				bit = 0;
	static pid_t			last_pid = 0;

	(void)oldact;
	if (last_pid != 0 && last_pid != siga_info->si_pid)
    {
		reset_vars(&c, &bit, &buffer_i, &last_pid);
        buffer[0] = 0;
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;
    }
	last_pid = siga_info->si_pid;
	process_signal(sig, &c, &bit);
	if (bit == 8)
	{
		buffer[buffer_i++] = c;
		bit = 0;
		c = 0;
		if (buffer_i == 4 || buffer[buffer_i - 1] == '\0')
			print_buffer(buffer, &buffer_i, last_pid);
	}
}




// void handel_sig(int sig, siginfo_t *siga_info, void *oldact)
// {
//     static char buffer[4] = {0};
//     static int buffer_i = 0;
//     static unsigned char c = 0;
//     static int bit = 0;
//     static pid_t last_pid = 0;
//     (void)oldact;

//     if(last_pid != 0 && last_pid != siga_info->si_pid)
//     {
//         reset_vars(&c, &bit, &buffer_i, &last_pid);
//         buffer[0] = 0;
//         buffer[1] = 0;
//         buffer[2] = 0;
//         buffer[3] = 0;
//     }
//     last_pid = siga_info->si_pid;
//     // process_signal(sig, &c, &bit);
//     if(sig == SIGUSR1)
//             c = (c << 1);
//     else if(sig == SIGUSR2)
//             c = (c << 1) | 1;
//         bit++;
//     if(bit == 8)
//     {
//         buffer[buffer_i++] = c;
//         // bit = 0;
//         // c  = 0;
//         // if (buffer_i == 4 || buffer[buffer_i - 1] == '\0')
//         // {
//             print_buffer(buffer, &buffer_i, last_pid);
//         buffer[0] = 0;
//         buffer[1] = 0;
//         buffer[2] = 0;
//         buffer[3] = 0;           
//         // }
//     }
// }
void	reset_buffer(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		buffer[i] = 0;
		i++;
	}
}

int main()
{
    struct sigaction siga;
    int pid = getpid();
    ft_putstr_fd(CY "Server PID: \e[0m", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n" GRN "Waiting...\n" "\e[0m", 1);
    sigemptyset(&siga.sa_mask);
    siga.sa_flags = SA_SIGINFO;
    siga.sa_sigaction = handel_sig;

    sigaction(SIGUSR1, &siga, NULL);
    sigaction(SIGUSR2, &siga, NULL);  
    while(1)
        pause();
}