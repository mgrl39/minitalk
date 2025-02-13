/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:27:47 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/12 19:53:44 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_state_index
{
	CURRENT_BIT = 0,
	CURRENT_CHAR,
}	t_state_index;

typedef enum e_signal_state_index
{
	MESSAGE_SIZE,
	CURRENT_BYTE,
	BIT_INDEX
}	t_signal_state_index;

typedef enum e_print_type
{
	PRINT_MESSAGE,
	PRINT_PID
}	t_print_type;

typedef enum e_data_type
{
	DATA_STRING,
	DATA_NUMBER
}	t_data_type;

typedef struct s_msg
{
	char	*str;
	int		len;
	int		remote_pid;
}	t_msg;

typedef void	(*t_handler)(int, siginfo_t *, void *);

void	error_exit(const char *message, int exit_code);
void	set_sig(struct sigaction *sa, t_handler handler);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
int		ft_atoi(const char *nptr);

# define RESET	"\033[0m"
# define RED	"\033[38;5;203m"
# define GOLD	"\033[38;5;220m"
# define GREEN	"\033[38;5;120m"

# define ERR_SIG			"Error: sigaction.\n"
# define ERR_SIGNAL			"Error: failed to send signal.\n"
# define ERR_MEMORY			"Error: memory allocation failed.\n"
# define ERR_INVALID_PID	"Error: invalid PID.\n"
# define ERR_USAGE			"Usage: ./client PID message.\n"
# define ERR_SERVER_FAIL	"Error: the server encountered a critical error.\n"
# define ERR_ACK_FAIL		"Error sending ACK to client.\n"
# define ERR_CLIENT_NOTIF	"Error notifying client about server failure.\n"
# define CLIENT_WAIT_MSG "The client will remain waiting indefinitely.\n"

#endif
