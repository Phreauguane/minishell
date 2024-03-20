/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:08:17 by rmidou            #+#    #+#             */
/*   Updated: 2024/03/20 18:34:14 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*createnode(void)
{
	t_node	*newnode;

	newnode = malloc(sizeof(t_node));
	if (newnode == NULL)
		exit_minishell(0);
	ft_bzero(newnode, sizeof(t_node));
	return (newnode);
}

void	free_tree(t_node *root)
{
	if (root == NULL)
		return ;
	free_tree(root->child_1);
	free_tree(root->child_2);
	free_ppl(&(root->ppl));
	free2(root->line);
	free2(root);
}

t_node	*create_parent(t_node *child, char *line)
{
	child->parent = createnode();
	if (line[0] == '&')
		child->parent->type = TYPE_OPP_A;
	else
		child->parent->type = TYPE_OPP_B;
	child->parent->line = line;
	child->parent->child_1 = child;
	return (child->parent);
}

void	or(char *cmd2, t_node *root, char *str, int *i)
{
	t_node	*temp;

	temp = root->child_2;
	root->child_2 = create_parent(temp, cmd2);
	root->child_2->parent = root;
	(*i) += 2;
	add_child(root->child_2, read_node(str, i));
}

t_node	*create_node(char *cmd)
{
	t_node	*node;

	node = createnode();
	node->type = TYPE_CMD;
	node->line = cmd;
	if (!cmd)
		node->error = 1;
	return (node);
}
