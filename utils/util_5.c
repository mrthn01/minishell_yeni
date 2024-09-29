/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melcuman <melcuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:04:32 by sebasari          #+#    #+#             */
/*   Updated: 2024/09/29 17:51:41 by melcuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_word_count(char *s, char c)
{
	size_t	num;
	char	*str;

	num = 0;
	while (*s)
	{
		if (ft_is_quotes_there_index(*s))
		{
			str = s;
			s += ft_find_next_q(0, str) + 1;
			num++;
		}
		else if (*s != c)
		{
			++num;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (num);
}

char	**ft_split_adjusted(char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	while (*s)
	{
		if (ft_is_quotes_there_index(*s))
			ret[i++] = ft_handle_q(&s);
		else if (*s == c)
		{
			s++;
			continue ;
		}
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len != 0)
			ret[i++] = ft_substr(s, 0, len);
		s += len;
	}
	ret[i] = NULL;
	return (ret);
}

char	*ft_handle_q(char **s)
{
	int		size;
	char	*str;
	char	*str_1;

	str = (*s);
	size = ft_find_next_q(0, str) + 1;
	if (size == 0)
		return (NULL);
	(*s) += size;
	str_1 = ft_substr(str, 0, size);
	return (str_1);
}

int	ft_token_counter(char **str)
{
	int	i;
	int	token_num;

	i = 0;
	token_num = 0;
	while (str[i])
	{
		if (strncmp(str[i], "|", ft_strlen(str[i])) == 0)
			token_num++;
		i++;
	}
	return (token_num + 1);
}

char	*ft_str_join2(char *str)
{
	char	*str_new;
	int		i;
	int		len;
	int		j;

	len = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] == '/')
			break ;
		i++;
	}
	j = i;
	while (str[i++])
		len++;
	i = j;
	j = 0;
	str_new = malloc(sizeof(char) * (len + 1));
	while (str[i])
		str_new[j++] = str[i++];
	return (str_new);
}
