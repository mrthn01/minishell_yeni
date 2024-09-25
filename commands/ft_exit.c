/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:57:32 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/23 14:49:35 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit command
void	ft_exit(char **str)
{
	int		total_len;
	
	total_len = ft_strlen_adjusted(str);
	if (total_len <= 3)
		exit(EXIT_SUCCESS);
	else
		printf("exit: too many arguments\n");
}
