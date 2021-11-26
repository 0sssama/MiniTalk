/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:03:17 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/26 23:14:42 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_transmission	g_current;

static void	ft_check_pids(int pid1, int pid2)
{
	if (pid1 == -1)
		pid1 = pid2;
	else if (pid1 != pid2)
	{
		ft_printf("\nBit loss detected. Bye.\n");
		exit(-1);
	}
}

static void	handle_bit(int signal, siginfo_t *info, void *context)
{
	static int	i;
	int			bin;

	(void) context;
	ft_check_pids(g_current.sender_pid, info->si_pid);
	if (i <= 7)
	{
		if (signal == 31)
			bin = 0;
		if (signal == 30)
			bin = 1;
		g_current.byte = g_current.byte | bin;
		if (i != 7)
		{
			g_current.byte = g_current.byte << 1;
			i++;
		}
		else
			i = 0;
	}
}

static int	ft_receive_char(void)
{
	struct sigaction	action;
	int					i;
	int					received_byte;

	i = 7;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_bit;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	while (i >= 0)
	{
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
		pause();
		i--;
	}
	received_byte = g_current.byte;
	g_current.byte = 0b00000000;
	return (received_byte);
}

static void	ft_receive_str(void)
{
	char	current_char;

	current_char = ft_receive_char();
	while (current_char)
	{
		ft_printf("%c", current_char);
		current_char = ft_receive_char();
	}
	ft_printf("\n");
	usleep(600);
	if (kill(g_current.sender_pid, SIGUSR1) != 0)
	{
		ft_printf("\nAn error occurred. :( Is the client process still alive?\n");
		exit(-1);
	}
	g_current.sender_pid = -1;
}

int	main(void)
{
	ft_printf("Server PID : %d\n", getpid());
	g_current.sender_pid = -1;
	while (1)
		ft_receive_str();
}
