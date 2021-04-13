/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimikim <jimikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:53:08 by jimikim           #+#    #+#             */
/*   Updated: 2021/04/14 07:18:19 by sangykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

char	g_full_char;
char	g_empty_char;
char	g_obstacle_char;
int		g_row_size;
int		g_col_szie;

int		ft_mv_nextline(int fd, int size);
int		ft_check_row_newline(char *file, int size);
void	ft_count_row_size(int fd);
int		ft_set_charset(char *file, int size);
int		ft_count_file_size(char *file);
char	*ft_push_array(int fd);
char	**ft_set_input_map(char *file, int size, char *keyboard_array);
int		ft_strlen(char *str);
int		ft_valid_row(char **map);
int		ft_valid_map(char **map);
int		ft_valid_charset(void);
char	**ft_valid_argv(char *file);
int		**ft_malloc_solve_map(void);
int		ft_min(int a, int b, int c);
int		**ft_input_solve_map(char **input_map, int *data_store);
char	**ft_solve_map(char **input_map);
void	ft_bsq_solution(char **input_map);
char	*ft_strdup(char *src);
void	ft_while_solve_map(int **r_map, char **input_map, int *data_store);
void	ft_set_global_charset(char *line, int i);
void	ft_set_charset_sidekick(char *line, char *charset);
char	*ft_push_array_keyboard(char *keyboard_array, int *i);

char	*malloc_for_keyboard(char *map_keyboard, int *i, char *checker);
int		get_3_simbols(int i, char *map_keyboard, char *checker);
void	get_col_size(char *m_kbd);
int		read_keyboard(char *map_keyboard);
int		ck_ex_ac1(char checker, int i);
int		ck_ex_ac2(int i, char *m);

int		ft_standard_read(char **map);

#endif
