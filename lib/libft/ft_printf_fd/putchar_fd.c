/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:21:35 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/17 07:59:22 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	putchar_fd(int fd, char c, int *counter)
{
	write(fd, &c, 1);
	(*counter)++;
}
