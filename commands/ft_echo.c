/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:55:33 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/21 14:28:32 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_option_n(char *str, int i)
{
	if (str[i] == 'n')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] != 'n' && str[i] != '\0')
			return (false);
		return (true);
	}
	else
		return (false);
}

int	ft_check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		if (ft_check_option_n(str, ++i) == true)
			return (1);
		if (str[i] != '\0')
			return (0);
	}
	return (0);
}

void	ft_print(char **str, int i, int flag)
{
	int	j;

	j = i;
	while (str[j])
	{
		printf("%s", str[j]);
		if (str[j + 1])
			printf(" ");
		j++;
	}
	if (flag == 0 || str[i] == NULL)
		printf("\n");
}

// echo command
void	ft_echo(char **str)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (str[1] != NULL)
	{
		if (str[1][0] == '\0')
			i++;
		else
		{
			flag = ft_check_option(str[i]);
			if (flag == 1)
				i++;
		}
	}
	ft_print(str, i, flag);
}
