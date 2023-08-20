/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:01:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/20 04:38:01 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	export_print(int argc, char **argv, char **envp)
{
	 char **ptr_env;
	 ptr_env = envp;
	 while (*ptr_env)
	 {
	 	printf("%s\n", *ptr_env);
	 	ptr_env++;
	 }
	return (0);
}

int export_add(int argc, char ** argv, char **envp) 
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

int blt_export(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return (export_print(argc, argv, envp));
	else
		return (export_add(argc, argv, evnp));
}
