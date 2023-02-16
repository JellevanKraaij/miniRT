#include <parse.h>

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		error_messages(1);
	check_file(av[1]);
	fd = open(av[1], 'r');
	if (fd < 0)
		error_messages(2);
	check_file_args(fd);
}
