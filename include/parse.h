#ifndef PARSE_H
# define PARSE_H

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h> //sqrt() pow() hypot()
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

enum error_codes
{
	n_args,
	wrongfile,
	outofrange,
	id,
	memal
};

typedef struct s_jump_table
{
	char *id;
	void (*check_function)(char **);
} t_jump_table ;

// error_handling
void	check_value_range(char *str, double min, double max);
void	error_messages(int error_code);
void	check_file(char *file_name);
void	check_file_args(int fd);
void	*protec(void *ptr);

// check_filmset
void	check_ambient(char **str);
void	check_camera(char **str);
void	check_light(char **str);

// check_objects
void	check_cylinder(char **str);
void	check_sphere(char **str);
void	check_plane(char **str);

// string_utilities
void	free_dubarray(char **dubarray);
int		count_array(char **splitted);

#endif