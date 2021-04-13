#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *g_line;
char *g_sep;
int *g_eof;
char **g_set_map;
t_map *g_read_map;

typedef struct t_map
{
	char *str;
	int length;
	struct s_map *next;
}		t_map;

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	ft_min(int a, int b, int c)
{
	return ((a < b && a < c) ? a : (b < c) ? b : c);
}

char	*ft_read_line(int fd)
{
	int i;

	i = 0;
	while ((read(fd, &g_line[i], 1)))
	{
		g_eof = 0;
		if (i == 1024)
		{
			write(2, "Error\n", 6);
			return (0);
		}
		if (g_line[i] == '\n')
		{
			g_line[i] = 0;
			break;
		}
		i++;
	}
	return (g_line);
}

t_map *ft_make_map(char *str, int length)
{
	t_map *result;

	if (!(result = (t_map *)malloc(sizeof(t_map))))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	result->str = str;
	result->length = length;
	result->next = 0;
	return (result);
}

void	ft_set_dict(char *str)
{
	t_map *tmp;

	if (!g_read_map)
	{
		if(!(g_read_map = ft_make_map(str, ft_strlen(str))))
		{
			write(2, "Error\n", 6);
			return ;
		}
		else
		{
			if (!(g_dict = ft_make_map(str, ft_strlen(str))))
			{
				write(2, "Error\n", 6);
				return ;
			}
			g_dict->next = tmp;
		}
	}
}

void	ft_read_map(char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error\n", 6);
		close(fd);
		return ;
	}
	if (!(g_sep = ft_read_line(fd)))
	{
		write(2, "Error\n", 6);
		close(fd);
		return ;
	}
	while ((g_line = ft_read_line(fd)))
	{
		if (g_eof++)
			break ;
		if (!*g_line)
		{
			write(2, "Error\n", 6);
			break ;
		}
		ft_set_line(g_line);
	}
	close(fd);
}



int main(int argc, char *argv[])
{
	int i;
	int fd;

	g_line = malloc(1025 * sizeof(char));
	g_sep = malloc(1025 * sizeof(char));
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{

	return (0);
}
