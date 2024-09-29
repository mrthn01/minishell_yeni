/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:08:18 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/29 15:52:45 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_exited(int status)
{
	return ((status & 0x7F) == 0);
}

int	ft_get_exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}
