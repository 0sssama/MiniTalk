/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:23:29 by olabrahm          #+#    #+#             */
/*   Updated: 2021/12/15 00:08:13 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// ft_confirm : Bare with me, I'm a useless function. :(
static void	ft_confirm(int sig)
{
	(void) sig;
	usleep(200);
	return ;
}

static int	ft_send_char(unsigned char c, int pid)
{
	int	bit;
	int	i;
	int	sig;

	i = 7;
	while (i >= 0)
	{
		bit = c & (1 << i);
		sig = SIGUSR1;
		if (bit == 0)
			sig = SIGUSR2;
		if (kill(pid, sig) != 0)
			return (-1);
		signal(SIGUSR1, ft_confirm);
		pause();
		i--;
	}
	return (0);
}

static int	ft_free_return(char *msg, void *freeable)
{
	ft_printf("%s\n", msg);
	free(freeable);
	return (-1);
}

static int	ft_send_str(unsigned char *message, int pid)
{
	int	i;

	i = 0;
	while (message[i])
	{
		if (ft_send_char(message[i++], pid) != 0)
			return (-1);
	}
	if (ft_send_char(0, pid) != 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	unsigned char	*message;
	int				pid;

	if (ac != 3)
		return (ft_free_return("Usage : ./client [PID] [MESSAGE]", NULL));
	pid = ft_atoi(av[1]);
	message = (unsigned char *) ft_strdup(av[2]);
	if (!message)
		return (ft_free_return("Memory error.", NULL));
	if (kill(pid, 0) != 0)
		return (ft_free_return("Invalid PID.", message));
	if (ft_send_str(message, pid) != 0)
		return (ft_free_return("An error occurred.", message));
	else
	{
		ft_printf("Sent successfully.\n");
		free(message);
		return (0);
	}
}
