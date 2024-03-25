/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:13:06 by rmidou            #+#    #+#             */
/*   Updated: 2024/03/25 13:40:32 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*parse_command(char *str, int *i)
{
	char	*cmd;
	int		quotes;

	cmd = NULL;
	quotes = 0;
	if (!str[*i])
		return (exit_handler("Parsing error", NULL, 0, 2), NULL);
	skip_spaces(str, i);
	while (str[*i])
	{
		if (quotes == 0 && ((str[*i] == '&' && str[*i + 1] == '&')
				|| (str[*i] == '|' && str[*i + 1] == '|')))
			break ;
		if (quotes == 0 && str[*i] == ')')
			return (throw_parsing_error(NULL, ')'), NULL);
		if (str[*i] == '\"' && quotes == 0)
			quotes = 1;
		else if (str[*i] == '\'' && quotes == 0)
			quotes = 2;
		else if ((str[*i] == '\'' && quotes == 2)
			|| (str[*i] == '\"' && quotes == 1))
			quotes = 0;
		cmd = str_addc(cmd, str[(*i)++]);
	}
	return (cmd);
}

void	throw_parsing_error(char *err, char near)
{
	char	*s;

	s = str_adds(NULL, "Parsing error near token \'", 27);
	s = str_addc(s, near);
	s = str_addc(s, '\'');
	if (err)
		exit_handler(err, s, 0, 2);
	else
		exit_handler(s, NULL, 0, 2);
	free2(s);
}

t_node	*manage_parent(char	*cmd1, t_node *root, char *str, int *i)
{
	if (root->type == TYPE_OPP_B && !(root->prio) && (str[*i] == '&'
			&& str[*i + 1] == '&'))
		or(cmd1, root, str, i);
	else
	{
		root = create_parent(root, cmd1);
		(*i) += 2;
	}
	return (root);
}

void	run_input(const char *str, char ***envp)
{
	t_node	*tree;
	char	*s;

	s = (char *)str;
	tree = add_nodes(NULL, s, 0);
	run_tree(&tree, envp);
	free_tree(tree);
	free2((char *)str);
}
