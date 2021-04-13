#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int		g_file_size;

char	ft_empty_char(char *str)
{
	char	*line;
	char	result;
	int		i;
	int		fd;

	i = 0;
	fd = open(str, O_RDONLY);
	if (!(line = malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	result = line[i - 3];
	free(line);
	close(fd);
	return (result);
}

char	ft_obstacle_char(char *str)
{
	char	*line;
	char	result;
	int		i;
	int		fd;

	i = 0;
	fd = open(str, O_RDONLY);
	if (!(line = malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	result = line[i - 2];
	free(line);
	close(fd);
	return (result);
}

char	ft_full_char(char *str)
{
	char	*line;
	char	result;
	int		i;
	int		fd;

	i = 0;
	fd = open(str, O_RDONLY);
	if (!(line = malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	result = line[i - 1];
	free(line);
	close(fd);
	return (result);
}

int		ft_count_col(char *str)
{
	char	*line;
	int		result;
	int		i;
	int		fd;

	i = 0;
	fd = open(str, O_RDONLY);
	if (!(line = malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	result = 0;
	while (read(fd, &line[i], 1))
	{
		if (line[i] != g_empty_char)
		{
			result *= 10;
			result += line[i] - '0';
		}
		else
			break;
		i++;
	}
	free(line);
	close(fd);
	return (result);
}

int		ft_count_file(char *str)
{
	char	*line;
	int		i;
	int		fd;
	int		size;

	fd = open(str, O_RDONLY);
	if (!(line = malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	size = 0;
	while (read(fd, &line[i], 1))
		size++;
	close(fd);
	free(line);
	return (size);
}

void	ft_mv_next_line(int fd)
{
	char	*line;
	int		i;

	i = 0;
	if (!(line = (char *)malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return ;
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	free(line);
}

int		ft_valid_map(char *str)
{
	int		i;
	int		last_index;
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	ft_mv_next_line(fd);
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	last_index = 0;
	while (last_index = read(fd, &line[0], g_file_size));
	line[last_index] = 0;
	while (line[i])
	{
		if ((line[i] == g_empty_char || line[i] == g_obstacle_char || line[i] == 0))
			return (0);
		i++;
	}
	close(fd);
	free(line);
	return (1);
}

int		ft_count_row_size(char *str)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(str, O_RDONLY);
	ft_mv_next_line(fd);
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	i = 0;
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	close(fd);
	free(line);
	return (i);
}

int		ft_get_col(char *str)
{
	char	*line;
	int		i;
	int		fd;
	int		col_size;

	fd = open(str, O_RDONLY);
	if (!(line = (char *)malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	i = 0;
	while (read(fd, &line[i], 1))
	{
		if (line[i] != g_empty_char)
		{
			row_size *= 10;
			row_size += line[i] - '0';
		}
		else
			break ;
	}
	close(fd);
	free(line);
	return (col_size);
}

int		ft_check_row_newline(char *str)
{
	char	*line;
	int		i;
	int		fd;
	int		last_index;
	int		row_size;

	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	row_size = ft_count_row_size(str);
	fd = open(str, O_RDONLY);
	while ((last_index = read(fd, line, row_size)))
	{
		if (line[last_index - 1] != '\n')
			return (0);
	}
	close(fd);
	free(line);
	return (1);
}

int		ft_get_next_col(char *str, int fd)
{
	char	*line;
	int		i;
	
	j = 0;
	if (!(line = (char *)malloc((g_size_file + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	free(line);
	return (i + 1);
}

int		ft_valid_row(char *str)
{
	int	i;
	int	j;
	int	fd;
	int	row_size;
	int col_size;

	i = 0;
	j = 0;
	fd = open(str, O_RDONLY);
	row_size = ft_count_row_size(str);
	col_size = ft_get_col(str);
	ft_mv_nextline(fd);
	while (i < col_size)
	{
		j = ft_get_next_col(str, fd);
		if (j != row_size)
			return (0);
		i++;
	}
	close(fd);
	return (1);
}

int		main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	printf("empty : %c \n", ft_empty_char("example_file"));
	g_empty_char = ft_empty_char("example_file");
	printf("obstacle : %c \n", ft_obstacle_char("example_file"));
	g_obstacle_char = ft_obstacle_char("example_file");
	printf("full : %c \n", ft_full_char("example_file"));
	g_full_char = ft_full_char("example_file");
	int col = ft_count_col("example_file");
	printf("col : %d \n", col);
	g_file_size = ft_count_file("example_file");
	printf("file size ? %d \n", g_file_size);
	return (0);
}
