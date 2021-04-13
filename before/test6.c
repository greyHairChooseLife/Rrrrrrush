#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

# define BUF_SIZE 32768

#include <stdio.h>

char g_full_char;
char g_empty_char;
char g_obstacle_char;
int g_row_size;
int g_col_size;

int ft_mv_nextline(int fd, int size)
{
	char *line;
	int i;

	i = 0;
	if (!(line = (char *)malloc((size + 1) * sizeof(char))))
	{
		write(2, "MAP ERROR\n", 10);
		return (0);
	}
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	free(line);
	return (1);
}

int	ft_check_row_newline(char *file, int size)
{
	char *line;
	int i;
	int fd;

	if (!(line = (char *)malloc((size + 1) * sizeof(char))))
		return (0);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	ft_mv_nextline(fd, size);
	while (read(fd, line, g_row_size + 1))
	{
		if (line[g_row_size] != '\n')
			return (0);
	}
	close(fd);
	free(line);
	return (1);
}

void ft_count_row_size(int fd)
{
	char c;
	int i;

	i = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		i++;
	}
	g_row_size = i;
}

int ft_set_charset(char *file, int size)
{
	char *line;
	int i;
	int fd;
	int result;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if (!(line = malloc((size + 1) * sizeof(char))))
		return (0);
	while (read(fd, &line[i], 1))
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	g_empty_char = line[i - 3];
	g_obstacle_char = line[i - 2];
	g_full_char = line[i - 1];
	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] != g_empty_char && '0' <= line[i] && line[i] <= '9')
		{
			result *= 10;
			result += line[i] - '0';
		}
		else
			break ;
		i++;
	}
	g_col_size = result;
	ft_count_row_size(fd);
	close(fd);
	return ((line[i] == g_empty_char && line[i + 1] == g_obstacle_char && line[i + 2] == g_full_char) ? 1 : 0);
}

int ft_count_file_size(char *file)
{
	char c;
	int i;
	int fd;
	int size;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	size = 0;
	while (read(fd, &c, 1))
		size++;
	close(fd);
	return (size);
}

char *ft_push_array(int fd, int size)
{
	char *array;
	int i;

	if (!(array = malloc((g_row_size + 1) * sizeof(char))))
		return (0);
	i = 0;	
	while (read(fd, &array[i], 1))
	{
		if (array[i] == '\n')
		{
			array[i] = 0;
			break ;
		}
		i++;
	}
	return (array);
}

char **ft_set_input_map(char *file, int size)
{
	int fd;
	int i;
	char **map;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "MAP ERROR\n", 10);
		return (0);
	}
	map = NULL;
	i = 0;
	if (!(map = (char **)malloc((g_col_size + 1) * sizeof(char *))))
		return (0);
	ft_mv_nextline(fd, size);
	while (i < g_col_size)
		map[i++] = ft_push_array(fd, size);
	close(fd);
	return (map);
}	

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int ft_valid_row(char **map)
{
	int i;
	int before_size;

	i = 1;
	before_size = ft_strlen(map[0]);
	while (map[i])
	{
		if (before_size != ft_strlen(map[i]))
			return (0);
		i++;
	}
	return (1);
}

int ft_valid_map(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			if (!(map[i][j] == g_empty_char || map[i][j] == g_obstacle_char || map[i][j] == '\n' || map[i][j] == 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int ft_valid_charset(void)
{
	if ((g_empty_char == g_full_char || g_empty_char == g_obstacle_char || g_full_char == g_obstacle_char))
		return (0);
	if (!(32 <= g_empty_char || g_empty_char == 127))
		return (0);
	if (!(32 <= g_full_char || g_full_char == 127))
		return (0);
	if (!(32 <= g_obstacle_char || g_obstacle_char == 127))
		return (0);
	return (1);
}

char **ft_valid_argv(char *file)
{
	int file_size;
	int col_size;
	char **map;

	if(!(file_size = ft_count_file_size(file)) ||
			!(col_size = ft_set_charset(file, file_size)))
	{
		write(2, "map error\n", 10);
		return (0);
	}
	ft_check_row_newline(file, file_size);
	if (!(ft_check_row_newline(file, file_size)))
	{
		write(2, "map error\n", 10);
		return (0);
	}
	map = NULL;
	if (!(map = ft_set_input_map(file, file_size)))
	{
		write(2, "map error\n", 10);
		return (0);
	}
	if (!ft_valid_map(map) || !ft_valid_row(map) || !ft_valid_charset() || g_col_size < 1 || g_row_size < 2)
	{
		write(2, "map error\n", 10);
		return (0);
	}
	return (map);
}

int **ft_malloc_solve_map(char **input_map)
{
	int i;
	int j;
	int **resolve_map;

	i = 0;
	if (!(resolve_map = (int **)malloc((g_col_size + 1) * sizeof(int *))))
		return (0);
	while (i < g_col_size)
	{
		if (!(resolve_map[i] = (int *)malloc((g_row_size + 1) * sizeof(int))))
			return (0);
		i++;
	}
	return (resolve_map);
}

int ft_min(int a, int b, int c)
{
	return ((a < b && a < c) ? a : (b < c) ? b : c);
}

int **ft_input_solve_map(char **input_map, int *data_store)
{
	int i;
	int j;
	int max_size;
	int pos;
	int **resolve_map;
	
	max_size = 0;
	if (!(resolve_map = ft_malloc_solve_map(input_map)))
		return (0);
	i = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			if (input_map[i][j] == g_obstacle_char)
				resolve_map[i][j] = 0;
			else if (i == 0 || j == 0)
				resolve_map[i][j] = 1;
			else
				resolve_map[i][j] = ft_min(resolve_map[i - 1][j], resolve_map[i][j - 1], resolve_map[i - 1][j - 1]) + 1;
			if (resolve_map[i][j] > max_size)
			{
				max_size = resolve_map[i][j];
				pos = i * g_row_size + j;
				data_store[0] = max_size;
				data_store[1] = pos;
			}
			j++;
		}
		i++;
	}
	return (resolve_map);
}

char **ft_solve_map(char **input_map)
{
	int i;
	int j;
	int **resolve_map;
	int length;
	int pos;
	int data_store[3];

	resolve_map = ft_input_solve_map(input_map, data_store);
	i = 0;
	j = 0;
	length = data_store[0];
	pos = data_store[1];
	i = (data_store[1] / g_row_size) - data_store[0] + 1;
	while (i < (data_store[1] / g_row_size) + 1)
	{
		j = (data_store[1] % g_row_size) - data_store[0] + 1;
		while (j < (data_store[1] % g_row_size) + 1)
		{
			input_map[i][j] = g_full_char;
			j++;
		}
		i++;
	}
	return (input_map);
}

void ft_bsq_solution(char **input_map)
{
	int fd;
	int i;
	int j;
	char **map;

	map = ft_solve_map(input_map);
	i = 0;
	j = 0;
	while (i < g_col_size)
	{
		j = 0;
		while (j < g_row_size)
		{
			write(1, &input_map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

char *ft_strdup(char *src)
{
	int size;
	char *dest;
	int i;

	i = 0;
	size = ft_strlen(src);
	if (!(dest = (char *)malloc((i + 1) * sizeof(char))))
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i - 1] = '\0';
	return (dest);
}

int main(int argc, char *argv[])
{
	int i;
	int read_row_size;
	char **map;
	char *read_line;
	int result; // col_size dummy input
	int row_size; // row_size dummy input

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			if((map = ft_valid_argv(argv[i++])))
				ft_bsq_solution(map);
			if (i != argc)
				write(1, "\n", 1);
		}
	}
	else if (argc == 1)
	{
		if (!(read_line = (char *)malloc(50001 * sizeof(char))))
			return (0);
		read(0, read_line, 50000);
		printf("%s \n", read_line);
		read_row_size = ft_strlen(read_line);
		g_empty_char = read_line[read_row_size - 4];
		g_obstacle_char = read_line[read_row_size - 3];
		g_full_char = read_line[read_row_size - 2];
		i = 0;
		if(!ft_valid_charset())
		{
			write(2, "map error\n", 10);
			return (0);
		}
		while (read_line[i])
		{
			if (read_line[i] != g_empty_char && '0' <= read_line[i] && read_line[i] <= '9')
			{
				result *= 10;
				result += read_line[i] - '0';
			}
			else
				break;
			i++;
		}
		if (read_line[i] == read_line[i + 1])
		{
			write(2, "map error\n", 10);
			return (0);
		}
		g_col_size = result;
		if (read_line[i] != g_empty_char)
		{
			write(2, "map error\n", 10);
			return (0);
		}
		i = 0;
		if (!(map = (char **)malloc((g_col_size + 1) * sizeof(char *))))
		{
			write(2, "map error\n", 10);
			return (0);
		}
		while (i < g_col_size)
		{
			read(0, read_line, 50000);
			row_size = ft_strlen(read_line);
			map[i] = ft_strdup( read_line);
			i++;
		}
		g_row_size = row_size;
		int x = ft_valid_row(map);
		int y = ft_valid_map(map);
		printf("x : %d y : %d \n", x, y);
		if (!ft_valid_row(map) || !ft_valid_map(map))
		{
			write(2, "map error\n", 10);
			return (0);
		}
		ft_bsq_solution(map);
	}
	return (0);
}
