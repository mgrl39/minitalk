/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:01:07 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/12 16:24:00 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	g_msg = {NULL, 0, 0};

static void	send_next_bit_of_message(void)
{
	static int	state[2] = {0, 0};
	int			signal;

	if (state[CURRENT_CHAR] > g_msg.len)
		exit(EXIT_SUCCESS);
	if (g_msg.str[state[CURRENT_CHAR]] & (1 << state[CURRENT_BIT]++))
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(g_msg.remote_pid, signal) == -1)
		error_exit(ERR_SIGNAL, EXIT_FAILURE);
	if (state[CURRENT_BIT] == 8)
	{
		state[CURRENT_CHAR]++;
		state[CURRENT_BIT] = 0;
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		send_next_bit_of_message();
	else if (sig == SIGUSR2)
		error_exit(ERR_SERVER_FAIL, EXIT_FAILURE);
}

static void	init_data(char *argv[])
{
	g_msg.str = argv[2];
	while (g_msg.str[g_msg.len] != '\0')
		g_msg.len++;
	g_msg.remote_pid = ft_atoi(argv[1]);
	if (g_msg.remote_pid <= 0)
		error_exit(ERR_INVALID_PID, EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	if (argc != 3)
		error_exit(ERR_USAGE, EXIT_FAILURE);
	init_data(argv);
	set_sig(&sa, handle_signal);
	send_next_bit_of_message();
	while (1)
		pause();
	return (0);
}
