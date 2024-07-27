/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:38:17 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/27 13:38:21 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	*ft_read(int fd, char *buf, char *str)
{
	int		r;
	char	*temp;

	r = 1;
	while (!ft_strchr(str, '\n') && r != 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(str);
			return (NULL);
		}
		buf[r] = '\0';
		if (!str)
		{
			str = ft_substr(buf, 0, r);
		}
		else
		{
			temp = ft_strjoin(str, buf);
			str = temp;
		}
	}
	return (str);
}

char	*ft_remain(char *str)
{
	char	*rem;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	rem = ft_substr(str, i, ft_strlen(str) - i);
	free(str);
	return (rem);
}

char	*ft_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	return (ft_substr(str, 0, i));
}

char	*get_next_line(int fd)
{
	char		*current_line;
	char		*buf;
	static char	*str;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (BUFFER_SIZE < 1 || fd < 0 || !buf)
		return (NULL);
	str = ft_read(fd, buf, str);
	free(buf);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = (NULL);
		return (NULL);
	}
	current_line = ft_line(str);
	str = ft_remain(str);
	return (current_line);
}
