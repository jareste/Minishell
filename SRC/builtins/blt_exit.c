#include <minishell.h>

int check_digits(char *num)
{
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (0);
		num++;
	}
	return (1);
}

void blt_exit(int argc, char **argv)
{
	unsigned	char ret;
	char		negative;
	char		*num;

	if (argc == 1)
		exit (0); // TODO must return $?
	if (argc != 2)
	{	
		ret = -1;
		exit(ret);
	}
	negative = argv[1][0] == '-';
	num = argv[1] + negative;
	if (!check_digits(num))
	{
		ret = -1;
		exit(ret);
	}
	ret = 0;
	while (*num)
	{
		ret *= 10;
		ret += *num - '0';
		num++;
	}
	if (negative)
		ret *= -1;
	exit(ret);
}
