#include <parse.h>

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		error_messages(n_args);
	check_file(av[1]);
	fd = open(av[1], 'r');
	if (fd < 0)
		error_messages(wrongfile);
	check_file_args(fd);
	
}
