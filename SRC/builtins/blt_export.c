int	export_print(int argc, char **argv, t_env *envp)
{
	return (0);
}

int export_add(int argc, char ** argv, t_env *envp) 
{
	size_t eqi;

	while (*argv)
	{
		if (envp)
			envp = get_env_last(envp);
			envp->next = calloc(sizeof(t_env), 1);

		eqi = ft_ichar(*argv, '=') 
		curr->key = ft_strndup(*argv, eqi, '=');
		curr->val = ft_strdup(*argv + eqi + 1);
		argv++;
	}
	

}

int blt_export(int argc, char **argv, t_env *envp)
{
	if (argc == 1)
		return (export_print(argc, argv, envp));
	else
		return (export_add(argc, argv, evnp));
}
