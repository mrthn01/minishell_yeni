/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:08:18 by murathanelc       #+#    #+#             */
/*   Updated: 2024/09/21 18:16:34 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	WIFEXITED -> ft_is_exited
	WEXITSTATUS -> ft_get_exit_status
	WIFSIGNALED -> ft_is_signaled
	WTERMSIG -> ft_get_term_signal
*/


// Alt 7 bit sıfırsa, çocuk süreç başarı ile sonlanmış demektir
int	ft_is_exited(int status)
{
	return ((status & 0x7F) == 0);
}

// çıkıs kodunu elde etmek için 8 biti kaydır
int	ft_get_exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}

// Eğer alt 7 bit sıfır değilse, sinyal ile sonlanmıştır
int	ft_is_signaled(int status)
{
	return ((status & 0x7F) != 0 && (status & 0x7F) != 0x7F);
}

// Sonlandırılan sinyal numarası alt 7 bitten elde edilir
int	ft_get_term_signal(int status)
{
	return (status & 0x7F);
}
