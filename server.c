/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:01:11 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/12 16:23:08 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	g_msg = {NULL, 0, 0};

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp_dest;
	const unsigned char	*tmp_src;
	size_t				i;

	if (!dest && !src)
		return (0);
	tmp_dest = (unsigned char *)dest;
	tmp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		tmp_dest[i] = tmp_src[i];
		i++;
	}
	return (dest);
}

static void	print_data(t_print_type type)
{
	if (type == PRINT_MESSAGE)
	{
		ft_putstr_fd(GREEN "Message: " RESET, 1);
		ft_putstr_fd(g_msg.str, 1);
		ft_putstr_fd("\n", 1);
		free(g_msg.str);
		g_msg.str = NULL;
		g_msg.len = 0;
	}
	else if (type == PRINT_PID)
	{
		ft_putstr_fd(GOLD "Server PID: " RESET, 1);
		ft_putnbr_fd(getpid(), 1);
		ft_putstr_fd("\n", 1);
	}
}

static void	append_char_to_message(char c)
{
	char	*new_message;

	new_message = (char *)malloc(sizeof(char) * (g_msg.len + 2));
	if (!new_message)
	{
		free(g_msg.str);
		g_msg.str = NULL;
		if (kill(g_msg.remote_pid, SIGUSR2) == -1)
			ft_putstr_fd(RED ERR_CLIENT_NOTIF RESET, 2);
		error_exit(ERR_MEMORY, EXIT_FAILURE);
	}
	if (g_msg.str)
	{
		ft_memcpy(new_message, g_msg.str, g_msg.len);
		free(g_msg.str);
	}
	new_message[g_msg.len] = c;
	new_message[g_msg.len + 1] = '\0';
	g_msg.str = new_message;
	g_msg.len++;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	state[3] = {0, 0, 0};

	(void)context;
	g_msg.remote_pid = info->si_pid;
	if (sig == SIGUSR1)
		state[CURRENT_BYTE] |= (1 << state[BIT_INDEX]);
	else if (sig != SIGUSR2)
		return ;
	state[BIT_INDEX]++;
	if (state[BIT_INDEX] == 8)
	{
		append_char_to_message(state[CURRENT_BYTE]);
		if (state[CURRENT_BYTE] == '\0')
		{
			state[MESSAGE_SIZE] = 0;
			print_data(PRINT_MESSAGE);
		}
		state[BIT_INDEX] = 0;
		state[CURRENT_BYTE] = 0;
	}
	if (kill(g_msg.remote_pid, SIGUSR1) == -1)
		error_exit(ERR_ACK_FAIL CLIENT_WAIT_MSG, EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa;

	g_msg.str = (char *)malloc(sizeof(char));
	if (!g_msg.str)
		error_exit(ERR_MEMORY, EXIT_FAILURE);
	g_msg.str[0] = '\0';
	set_sig(&sa, handle_signal);
	print_data(PRINT_PID);
	while (1)
		pause();
	if (g_msg.str)
		free(g_msg.str);
	return (0);
}
