/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_utils.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: skuznets <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/22 19:51:59 by skuznets		  #+#	#+#			 */
/*   Updated: 2024/07/26 18:17:07 by skuznets		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../so_long.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (0);
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (*s == (char)c)
// 		return ((char *)s);
// 	return (0);
// }


// char	*concat_strings(const char *s1, const char *s2)
// {
// 	char	*result;
// 	int		i;
// 	int		k;

// 	i = 0;
// 	k = 0;
// 	result = malloc(strlen(s1) + strlen(s2) + 1);
// 	if (!result)
// 		return (NULL);
// 	while (s1[k])
// 		result[i++] = s1[k++];
// 	k = 0;
// 	while (s2[k])
// 		result[i++] = s2[k++];
// 	result[i] = '\0';
// 	return (result);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*result;

// 	if (!s1)
// 	{
// 		s1 = malloc(sizeof(char));
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	if (!s2)
// 	{
// 		free(s1);
// 		return (NULL);
// 	}
// 	result = concat_strings(s1, s2);
// 	free(s1);
// 	return (result);
// }

// int	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_substr(char *s, int start, int len)
// {
// 	char	*str;
// 	int		i;
// 	int		k;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	k = 0;
// 	if (ft_strlen((char *)s) < len)
// 		len = ft_strlen((char *)s);
// 	str = (char *)malloc(sizeof(*s) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		if (i >= start && k < len)
// 		{
// 			str[k] = s[i];
// 			k++;
// 		}
// 		i++;
// 	}
// 	str[k] = '\0';
// 	return (str);
// }
