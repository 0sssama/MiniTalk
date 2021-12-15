/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:28:39 by olabrahm          #+#    #+#             */
/*   Updated: 2021/12/15 00:06:13 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_transmission	g_current;

static void	ft_handle_bit(int signal, siginfo_t *info, void *context)
{
	static int	i;
	int			bin;

	(void) context;
	if (g_current.pid == -1)
		g_current.pid = info->si_pid;
	if (i <= 7)
	{
		bin = signal == SIGUSR1;
		g_current.byte = g_current.byte | bin;
		if (i != 7)
		{
			g_current.byte = g_current.byte << 1;
			i++;
		}
		else
			i = 0;
	}
	usleep(100);
	if (kill(g_current.pid, SIGUSR1) != 0)
		ft_printf("\n[CLIENT] Client process dead.\n");
}

static unsigned char	ft_receive_char(void)
{
	struct sigaction	action;
	int					i;

	i = 7;
	g_current.byte = 0b00000000;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_handle_bit;
	while (i >= 0)
	{
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
		pause();
		i--;
	}
	return (g_current.byte);
}

static void	ft_receive_str(void)
{
	unsigned char	c;

	c = ft_receive_char();
	while (c)
	{
		ft_printf("%c", c);
		c = ft_receive_char();
	}
	ft_printf("\n");
}

int	main(void)
{
	ft_printf("[SERVER] Pid : %d\n", getpid());
	while (1)
	{
		g_current.pid = -1;
		ft_receive_str();
	}
}
