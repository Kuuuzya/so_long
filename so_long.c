/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:35:13 by skuznets          #+#    #+#             */
/*   Updated: 2024/07/21 16:48:12 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	check_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strcmp(extension, ".ber") != 0)
	{
		ft_printf("%s", "Error: Wrong file extension\n");
		exit(1);
	}
}

void	check_file(char *filename)
{
	int		fd;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		exit(1);
	}
	check_extension(filename);
	if (read(fd, buffer, 1) < 1)
	{
		ft_printf("%s", "Error: File is empty\n", 21);
		exit(1);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("%s", "Error: Wrong number of arguments\n", 33);
		exit(1);
	}
	check_file(argv[1]);
	// Call your GNL function here
	return (0);
}
