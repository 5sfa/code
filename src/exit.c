/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:11:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/25 16:04:09 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <limits.h>

int	is_numeric(const char *str)
{
	if (*str && (*str == '+' || *str == '-'))
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

// void	exit_command(char **argv, int *exit_status)
// {
// 	if (argv[1])
// 	{
// 		if (!is_numeric(argv[1]))
// 		{
// 			ft_printf("exit\n");
// 			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", argv[1]);
// 			//free
// 			exit(255);
// 		}
// 		else if (argv[2])
// 		{
// 			ft_printf("exit\n");
// 			ft_printf_fd(2, "minishell: exit: too many arguments\n");
// 			*exit_status = 1;
// 		}
// 		else
// 		{
// 			ft_printf("exit\n");
// 			exit(ft_atoi(argv[1]));
// 		}
// 	}
// 	else
// 	{
// 		ft_printf("exit\n");
// 		exit(0);
// 	}
// }

static char	*queue_to_str(t_queue_char *q)
{
	int 						i;
	char						*path;
	struct s_queue_node_char	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	path = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (q->front)
		path[i++] = dequeue_char(q);
	path[i] = '\0';
	return (path);
}

void	exit_command(char **argv, int *exit_status)
{
	int				i;
	t_queue_char	q;
	char			*str;
	char			tok;

	if (argv[1])
	{
		init_queue_char(&q);
		str = argv[1];
		i = 0;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				tok = str[i];
				i++;
				while (str[i] && str[i] != tok)
				{
					enqueue_char(&q, str[i]);
					i++;
				}
				if (str[i] == tok)
					i++;
			}
			else
			{
				enqueue_char(&q, str[i]);
				i++;
			}
		}
		char *arg = queue_to_str(&q);
		if (!is_numeric(arg))
		{
			ft_printf("exit\n");
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", arg);
			free(arg);
			//free
			exit(255);
		}
		else if (argv[2])
		{
			ft_printf("exit\n");
			ft_printf_fd(2, "minishell: exit: too many arguments\n");
			*exit_status = 1;
		}
		else
		{
			// ft_printf("exit\n");
			// long long exit_code = atoll(arg);
			// free(arg);
			// exit(exit_code);

			ft_printf("exit\n");
			char *endptr;
			long long exit_code = strtoll(arg, &endptr, 10);

			// Check for overflow and underflow
			if ((exit_code == LLONG_MAX && errno == ERANGE) ||
				(exit_code == LLONG_MIN && errno == ERANGE))
			{
				ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", arg);
				free(arg);
				exit(255);
			}

			free(arg);
			exit(exit_code);
		}
	}
	else
	{
		ft_printf("exit\n");
		exit(0);
	}
}
