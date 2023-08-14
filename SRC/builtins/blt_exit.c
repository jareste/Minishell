#include <minishell.h>

void stde_print(char *str)
{
	write(2, str, ft_strlen(str));
}

int check_digits(char *_num)
{
	char *num;

	num = _num + (*_num == '-');
	while (*num)
	{
		if (*num < '0' || *num > '9')
		{
			stde_print("exit: ");
			stde_print(_num);
			stde_print(": numeric argument required");
			return (0);
		}
		num++;
	}
	return (1);
}

int	blt_exit(int argc, char **argv)
{
	unsigned	char ret;
	char		negative;
	char		*num;

	if (argc == 1)
		return(0); // TODO must return $?
	if (!check_digits(argv[1]) || argc != 2)
	{
		ret = -1;
		return(ret);
	}
	negative = argv[1][0] == '-';
	num = argv[1] + negative;
	ret = 0;
	while (*num)
	{
		ret *= 10;
		ret += *num - '0';
		num++;
	}
	if (negative)
		ret *= -1;
	return (ret);
	 
}
