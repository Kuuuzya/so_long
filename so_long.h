#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	check_file(char *filename);

//libft functions and ft_printf
int		ft_printf(const char *format, ...);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
#endif