/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:51:59 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 20:08:45 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

char *ft_strjoin(char *s1, char *s2)
{
    int		i;
	int		k;
    char	*str;

    if (!s1) {
        s1 = malloc(sizeof(char));
        if (!s1) return NULL;
        s1[0] = '\0';
    }
    if (s2 == NULL) {
        free(s1);
        return NULL;
    }
    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1); // Удален лишний +1
    if (!str)
	{
        free(s1);  // Утечка исправлена
        return NULL;
    }
	k = 0;
	i = 0;
	while (s1[k])
		str[i++] = s1[k++];
	k = 0;
	while (s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		k;

	if (!s)
		return (0);
	i = 0;
	k = 0;
	if (ft_strlen((char *)s) < len)
		len = ft_strlen((char *)s);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && k < len)
		{
			str[k] = s[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}
