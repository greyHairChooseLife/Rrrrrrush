#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int	g_file_size;
int	g_col_size;

void ft_set_charset(char *file)
{
	char *line;
	char result;
	int i;
	int fd;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return ;
	}
	if (!(line = malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return ;
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	g_full_char = line[i - 1];
	g_empty_char = line[i - 3];
	g_obstacle_char = line[i - 2];
}


void ft_mv_nextline(int fd)
{
	char *line;
	int i;

	i = 0;
	if (!(line = (char *)malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return ;
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	free(line);
}

int ft_count_row_size(char *file)
{
	char *line;
	int i;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	ft_mv_nextline(fd);
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

int ft_get_col(char *file)
{
	char *line;
	int i;
	int fd;
	int col_size;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (!(line = (char *)malloc(1025 * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	i = 0;
	col_size = 0;
	while (read(fd, &line[i], 1))
	{
		if ('0' <= line[i] && line[i] <= '9')
		{
			col_size *= 10;
			col_size += line[i] -'0';
		}
		else if (line[i] == g_empty_char)
			break;
		else
		{
			write(2, "Error\n", 6);
			return (0);
		}
		i++;
	}
	close(fd);
	free(line);
	return (col_size);
}

void ft_count_file_size(char *file)
{
	char c;
	int i;
	int fd;
	int size;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return ;
	}
	size = 0;
	while (read(fd, &c, 1))
		size++;
	close(fd);
	g_file_size = size;
}

int ft_valid_map(char *file)
{
	int i;
	int last_index;
	int fd;
	char *line;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	ft_mv_nextline(fd);
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	last_index = 0;
	while ((last_index = read(fd, &line[0], g_file_size)))
		line[last_index] = '\0';
	i = 0;
	while (line[i])
	{
		if ((line[i] != g_empty_char && line[i] != g_obstacle_char && line[i] != '\n'))
			return (0);
		i++;
	}
	close(fd);
	free(line);
	return (1);
}

int ft_check_row_newline(char *file)
{
	char *line;
	int i;
	int fd;
	int row_size;

	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	row_size = ft_count_row_size(file);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	while (read(fd, line, row_size))
	{
		if (line[row_size] != '\n')
			return (0);
	}
	close(fd);
	free(line);
	return (1);
}

int ft_get_next_row_size(char *file, int fd)
{
	char *line;
	int i;

	i = 0;
	if (!(line = (char *)malloc((g_file_size + 1) * sizeof(char))))
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
	free(line);
	return (i);
}

int ft_valid_row(char *file)
{
	int i;
	int j;
	int fd;
	int row_size;

	i = 0;
	j = 0;
	row_size = ft_count_row_size(file);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	ft_mv_nextline(fd);
	while (i < g_col_size)
	{
		j = ft_get_next_row_size(file, fd);
		printf("%d / %d \n", j, row_size);
		if (j != row_size)
			return (0);
		i++;
	}
	j = ft_get_next_row_size(file, fd);
	close(fd);
	return (j ? 0 : 1);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int row_size = ft_count_row_size("example_file");
	printf("row_size ? %d \n", row_size);
	ft_set_charset("example_file");
	printf("g_full : %c / g_empty : %c, g_obstacle : %c \n", g_full_char, g_empty_char, g_obstacle_char);
	g_col_size = ft_get_col("example_file");
	printf("col_size ? %d \n", g_col_size);
	ft_count_file_size("example_file");
	printf("g_file_size ? %d \n", g_file_size);
	printf("ft_valid_map ? %d \n", ft_valid_map("example_file"));
	printf("ft_check_row_newline ? %d \n", ft_check_row_newline("example_file"));
	printf("valid_col ? : %d \n", ft_valid_row("example_file"));
	return (0);
}
