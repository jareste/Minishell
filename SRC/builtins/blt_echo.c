# include <minishell.h>

int blt_echo(int argc, char** argv)
{
	int i;
	int first;

	first = 1;
	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == 'n')
		i++;	
	while (i < argc)
	{
		if (!first)
		{
			ft_printf(" ");
			first = 0;
		}
		ft_printf("%s", argv[i]);
		i++;
	}
	if (argv[1][0] != '-' && argv[1][1] != 'n')
		ft_printf("\n");
		
	return (0);

}
