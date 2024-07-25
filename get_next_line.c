/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:50:31 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/25 15:39:41 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_read(int fd, char *buf, char *str)
{
	int	r;

	r = 1;
	while (ft_strchr(str, '\n') == 0 && r != 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(buf);
			free(str);
			return (0);
		}
		buf[r] = '\0';
		if (!str)
			str = ft_substr(buf, 0, r);
		else
			str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_remain(char	*str)
{
	char	*rem;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	rem = ft_substr(str, i, ft_strlen(str));
	free(str);
	return (rem);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	i++;
	line = ft_substr(str, 0, i);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*current_line;
	char			*buf;
	static char		*str;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	str = ft_read(fd, buf, str);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = 0;
		return (NULL);
	}
	current_line = ft_line(str);
	str = ft_remain(str);
	return (current_line);
}
