/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:10:23 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/03/08 03:10:29 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
void send_bit(char c, int pid)
{
    int i = 7;
    while(i >= 0)
    {
        if(((c >> i) & 1) == 0)
                kill(pid, SIGUSR1);
        else
                kill(pid, SIGUSR2);
            i--;
            usleep(100);
    }
}

int main(int ac, char **av)
{
    int i;
    int pid;
    
    if (ac != 3)
        return(write(2, "Error: Usage ./client [server_pid] [message]\n", 45), 1);
    i = 0;
    pid = atoi(av[1]);
    if (pid < 100 || pid > MAX_PID)
    {
        return (write(2, "Error: Invalid PID range\n", 25), 1);
    }
    i = 0;
    while(av[2][i])
    {
        send_bit(av[2][i], pid);
        usleep(500);
        i++;
    }
    // send_bit('\0', pid);
    return 0;
}

// int main(int ac, char **av)
// {
//     int i = 0;
//     int j = 0;
//     int pid  = atoi(av[1]);
//     if (ac != 3 || pid < 100 || pid > MAX_PID) 
//         return (write(2, "Error\n", 6), 1);
//     while(av[2][i])
//     {
//         send_bit(av[2][i], pid);
//         usleep(500);
//         i++;
//     }
// }