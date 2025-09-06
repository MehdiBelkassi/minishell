/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:21:13 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/26 18:42:22 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "par.h"

void	init_shell(t_env **env_list, char **envp)
{
	*env_list = build_env_list(envp);
	rl_catch_signals = 0;
	setup_signals();
}

int	handle_input(char **cmd, t_env *env_list)
{
	*cmd = readline("minishell$ ");
	if (g_signal == SIGINT)
	{
		env_list->exit_status = 1;
		g_signal = 0;
	}
	if (*cmd == NULL)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if ((*cmd)[0] == '\0' || is_all_whitespace(*cmd))
	{
		free(*cmd);
		return (-1);
	}
	return (1);
}

char	**prepare_tokens(char *cmd, t_env *env_list)
{
	char	*cmd_trimmed;
	char	**str_tokens;

	add_history(cmd);
	cmd_trimmed = ft_strtrim(cmd, " ");
	free(cmd);
	str_tokens = ft_token(cmd_trimmed, env_list);
	free(cmd_trimmed);
	return (str_tokens);
}

int	process_tokens(char **str_tokens, t_env *env)
{
	t_token	*token_list;
	t_tree	*tree;

	token_list = convert_tokens(str_tokens, env);
	if (!token_list)
	{
		env->exit_status = 0;
		return (0);
	}
	if (!check_ambiguous(token_list))
	{
		env->exit_status = 1;
		free_token_list(token_list);
		return (0);
	}
	tree = parse_tokens(token_list, NULL, env, env->exit_status);
	free_token_list(token_list);
	execute_tree(tree, env);
	free_tree(tree);
	return (1);
}

int	main(int arc, char **arv, char **envp)
{
	char	*cmd;
	char	**str_tokens;
	t_env	*env_list;
	int		input_status;

	(void)arc;
	(void)arv;
	init_shell(&env_list, envp);
	while (1)
	{
		input_status = handle_input(&cmd, env_list);
		if (input_status == 0)
			cleanup_and_exit(env_list, cmd);
		if (input_status == -1)
			continue ;
		str_tokens = prepare_tokens(cmd, env_list);
		if (!str_tokens)
			continue ;
		process_tokens(str_tokens, env_list);
		free_array(str_tokens);
	}
	cleanup_and_exit(env_list, cmd);
}
