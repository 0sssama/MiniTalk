/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:59:17 by olabrahm          #+#    #+#             */
/*   Updated: 2021/11/26 23:11:05 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_send_char(char c, int pid)
{
	int	bit;
	int	i;
	int	signal;

	i = 7;
	while (i >= 0)
	{
		bit = c & (1 << i);
		signal = SIGUSR1;
		if (bit == 0)
			signal = SIGUSR2;
		if (kill(pid, signal) != 0)
			return (-1);
		usleep(500);
		i--;
	}
	return (0);
}

static void	handle_response(int sig)
{
	if (sig != 30)
	{
		ft_printf("An error occurred.\n");
		exit(-1);
	}
	else
	{
		ft_printf("Sent successfully.\n");
		exit(0);
	}
}

static int	ft_send_str(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_send_char(str[i++], pid) != 0)
			return (-1);
	}
	if (ft_send_char(str[i], pid) != 0)
		return (-1);
	signal(SIGUSR1, handle_response);
	pause();
	return (0);
}

static int	ft_atoi(const char *str)
{
	size_t	i;
	int		output;
	int		negative;

	i = 0;
	output = 0;
	negative = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		negative *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		output = (output * 10) + (str[i++] - 48);
	return (output * negative);
}

int	main(int ac, char **av)
{
	int		pid;
	char	*message;

	if (ac != 3)
	{
		ft_printf("Usage : ./client [PID] [MESSAGE]\n");
		return (-1);
	}
	pid = ft_atoi(av[1]);
	message = av[2];
	if (kill(pid, 0) != 0)
	{
		ft_printf("Invalid PID.\n");
		return (-1);
	}
	ft_send_str(message, pid);
	return (0);
}
