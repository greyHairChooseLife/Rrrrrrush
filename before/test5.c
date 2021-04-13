#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int	g_file_size;
int	g_col_size;

int ft_min(int a, int b, int c)
{
	return ((a < b && a < c) ? a : (b < c) ? b : c);
}

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
		else
			break;
		i++;
	}
	close(fd);
	col_size = (line[i] == g_empty_char) ? col_size : 0;
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
	while ((last_index = read(fd, line, g_file_size)))
		line[last_index] = 0;
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

int ft_valid_argv(char *file)
{
	// need return...for exception
	ft_set_charset(file);
	ft_count_file_size(file);
	if ((ft_count_row_size(file) < 1) || (ft_get_col(file) < 1))
	{
		write(2, "MAP ERROR\n", 10);
		return (0);
	}
	if (!(ft_valid_map(file)) || !(ft_check_row_newline(file)))
	{
		write(2, "MAP ERROR\n", 10);
		return (0);
	}
	if (!(ft_valid_row(file)))
	{
		write(2, "MAP ERROR\n", 10);
		return (0);
	}
	return (1);
}

char **ft_set_map(char *file, int col_size, int row_size)
{
	char **map;
	int i;
	int j;
	int return_read;
	int fd;

	i = 0;
	return_read = 0;
	fd = open(file, O_RDONLY);
	ft_mv_nextline(fd);
	if (!(map = (char **)malloc((col_size + 1) * sizeof(char *))))
		return (NULL);
	map[col_size] = 0;
	while (i < col_size)
	{
		if (!(map[i] = (char *)malloc((row_size + 1) * sizeof(char))))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < col_size)
	{
		while ((return_read = read(fd, map[i], row_size + 1) == -1))
				return (NULL);
		map[i][row_size] = 0;
		i++;
	}
	close(fd);
	return (map);
}

int **ft_make_map(int row_size, int col_size)
{
	int **int_map;
	int i;

	i = 0;
	if (!(int_map = (int **)malloc((col_size + 1) * sizeof(int *))))
		return (NULL);
	while (i < col_size)
	{
		if (!(int_map[i] = (int *)malloc((row_size + 1) * sizeof(int))))
			return (NULL);
		i++;
	}
	return (int_map);
}

int ft_bsq_size(char **map, int row_size, int col_size)
{
	int i;
	int j;
	int **result_map;
	int max_size;

	i = 0;
	max_size = 0;
	result_map = NULL;
	result_map = ft_make_map(row_size, col_size);
	while (i < col_size)
	{
		j = 0;
		while (j < row_size)
		{
			if (map[i][j] == g_obstacle_char)
				result_map[i][j] = 0;
			else if (i == 0 || j == 0)
				result_map[i][j] = 1;
			else
				result_map[i][j] = ft_min(result_map[i - 1][j], result_map[i][j - 1], result_map[i - 1][j - 1]) + 1;
			if (result_map[i][j] > max_size)
				max_size = result_map[i][j];
			j++;
		}
		i++;
	}
	free(result_map);
	return (max_size);
}

int ft_find_position(char **map, int row_size, int col_size, int length)
{
	int i;
	int j;
	int **int_map;
	int pos;
	int flag;

	i = 0;
	pos = 0;
	flag = 0;
	int_map = ft_make_map(row_size, col_size);
	while (i < col_size)
	{
		j = 0;
		while (j < row_size)
		{
			if (map[i][j] == g_obstacle_char)
				int_map[i][j] = 0;
			else if (i == 0 || j == 0)
				int_map[i][j] = 1;
			else
				int_map[i][j] = ft_min(int_map[i - 1][j], int_map[i][j - 1], int_map[i - 1][j - 1]) + 1;
			if (int_map[i][j] == length)
			{
				pos = i * row_size + j;
				flag = 1;
				break;
			}
			j++;
		}
		if (flag)
			break;
		i++;
	}
	free(int_map);
	return (pos);
}
					
char **ft_solve_map(char **map, int row_size, int col_size)
{
	int i;
	int j;
	int length;
	int pos;

	length = ft_bsq_size(map, row_size, col_size);
	pos = ft_find_position(map, row_size, col_size, length);
	i = (pos / row_size) - length + 1;
	while (i < (pos / row_size) + 1)
	{
		j = (pos % row_size) - length + 1;
		while (j < (pos % row_size) + 1)
		{
			map[i][j] = g_full_char;
			j++;
		}
		i++;
	}
	return (map);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void ft_bsq_solution(char *file)
{
	int fd;
	int i;
	int j;
	int row_size;
	int col_size;
	char **map;

	map = NULL;
	row_size = ft_count_row_size(file);
	col_size = ft_get_col(file);
	
	fd = open(file, O_RDONLY);
	if (fd != -1)
		map = ft_set_map(file, col_size, row_size);
	ft_solve_map(map, row_size, col_size);
	i = 0;
	while (i < col_size)
	{
		ft_putstr(map[i]);
		ft_putchar('\n');
		i++;
	}
	free(map);
	close(fd);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(*str++)
		i++;
	return (i);
}

int main(int argc, char *argv[])
{
	int i;
	int j;
	char *read_line;
	int read_line_size;
	int read_col_size;
	int read_row_size;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			if(ft_valid_argv(argv[i]))
				ft_bsq_solution(argv[i]);
			i++;
		}
	}
	else if (argc == 1)
	{
		// standard input...
		if (!(read_line = (char *)malloc(32768 * sizeof(char))))
			return (0);
		read(0, read_line, 32767);
		printf("read_line ? %s \n", read_line);
		read_line_size = ft_strlen(read_line);
		printf("line_size ? %d \n", read_line_size);
		g_full_char = read_line[read_line_size - 2];
		g_empty_char = read_line[read_line_size - 4];
		g_obstacle_char = read_line[read_line_size - 3];
		printf("full : %c / empty : %c / obstacle : %c \n", g_full_char, g_empty_char, g_obstacle_char);
		if (g_full_char == g_empty_char || g_full_char == g_obstacle_char || g_empty_char == g_obstacle_char)
		{
			write(2, "MAP ERROR\n", 10);
			return (0);
		}
		i = 0;
		read_col_size = 0;
		while (i < read_line_size - 4)
		{
			read_col_size *= 10;
			read_col_size += read_line[i] - '0';
			i++;
		}
		printf("while end line[i] ? %c \n", read_line[i]);
		printf("read_col_size ? %d \n", read_col_size);
		if (read_line[i] != g_empty_char)
		{
			write(2, "MAP ERROR\n", 10);
			return (0);
		}
		i = 0;

	}
	return (0);
}
