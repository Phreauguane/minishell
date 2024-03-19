/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:11:48 by larz              #+#    #+#             */
/*   Updated: 2024/03/19 15:01:21 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_tree(t_node **tree, char **envp)
{
	if (!tree || !(*tree))
		return ;
	if ((*tree)->type == TYPE_CMD)
		(*tree)->ppl = parse((*tree)->line, envp);
	parse_tree(&((*tree)->child_1), envp);
	parse_tree(&((*tree)->child_2), envp);
}

int	run_nodes(t_node **tree, char ***envp)
{
	int	out1;

	if (!tree || !(*tree))
		return (INT_MIN);
	if ((*tree)->type == TYPE_CMD)
		return (run_pipeline((*tree)->ppl, envp), g_exec);
	out1 = run_nodes(&((*tree)->child_1), envp);
	if ((out1 == 0 && (*tree)->type == TYPE_OPP_B)
		|| (out1 != 0 && (*tree)->type == TYPE_OPP_A))
		return (out1);
	return (run_nodes(&((*tree)->child_2), envp));
}

void	run_tree(t_node **tree, char ***envp)
{
	int	out;

	parse_tree(tree, *envp);
	out = run_nodes(tree, envp);
	if (out != INT_MIN)
		g_exec = out;
}
