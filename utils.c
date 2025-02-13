/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:03:59 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/12 14:24:22 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	set_sig(struct sigaction *sa, void (*handler)(int, siginfo_t *, void *))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handler;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		error_exit(ERR_SIG, EXIT_FAILURE);
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		error_exit(ERR_SIG, EXIT_FAILURE);
}

void	error_exit(const char *message, int exit_code)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd(RESET, 2);
	exit(exit_code);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;

	if (nb == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (nb < 0)
	{
		ft_putstr_fd("-", fd);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		mult;

	i = 0;
	res = 0;
	mult = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			mult = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
		res = res * 10 + (nptr[i++] - 48);
	return (res * mult);
}
