/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:06 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/23 14:29:48 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd command
void	ft_cd(char **str)
{
	char	*directory;
	int		total_len;
	
	total_len = ft_strlen_adjusted(str);
	if (total_len < 2)
		directory = getenv("HOME");
	else
		directory = str[1];
	printf("Success\n");
	if (chdir(directory) != 0)
		printf("cd: no such file or directory");
}
