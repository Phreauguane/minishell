/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:00:51 by rmidou            #+#    #+#             */
/*   Updated: 2024/03/20 18:51:55 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_spaces(char *str, int *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
}

char	*get_line_inside(char *str, int *i)
{
	char	*line;
	char	*out;

	line = NULL;
	skip_spaces(str, i);
	if (str[*i] != '(' || ++(*i) < 0)
		return (NULL);
	while (str[*i] != ')' && str[*i])
	{
		if (str[*i] == '(')
		{
			out = get_line_inside(str, i);
			line = str_addc(str_adds(str_addc(line, '('), out, 
				ft_strlen(out)), ')');
			free2(out);
		}
		else
			line = str_addc(line, str[(*i)++]);
	}
	if (str[*i])
		return (line);
	free2(line);
	return ((*i)++, NULL);
}

t_node	*read_node(char *str, int *i)
{
	t_node	*child;
	char	*cmd;

	child = NULL;
	cmd = get_line_inside(str, i);
	if (cmd)
	{
		child = add_nodes(child, cmd, 0);
		free2(cmd);
		child->prio = PRIORITY;
		skip_spaces(str, i);
	}
	else
		child = create_node(parse_command(str, i));
	return (child);
}

void	add_child(t_node *root, t_node *child)
{
	if (root->child_1 == NULL && child != NULL)
	{
		root->child_1 = child;
		root->child_1->parent = root;
	}
	else if (root->child_2 == NULL && child != NULL)
	{
		root->child_2 = child;
		root->child_2->parent = root;
	}
}

t_node	*add_nodes(t_node *root, char *str, int i)
{
	t_node	*child;
	char	*cmd;

	child = read_node(str, &i);
	if (!root)
		root = child;
	else
		add_child(root, child);
	cmd = NULL;
	if (str[i] && str[i + 1])
	{
		cmd = str_addc(cmd, str[i]);
		cmd = str_addc(cmd, str[i + 1]);
		root = manage_parent(cmd, root, str, &i);
	}
	if (str[i] && str[i + 1])
		return (add_nodes(root, str, i));
	else
		return (root);
}

void	printTreePreorder(t_node *root)
{
	if (root && root->child_1)
	{
		ft_printf("\t{%s}\n", root->line);
		if (root->child_1)
			ft_printf("{%s}>child_1 = \'%s\'\n", root->line, root->child_1->line);
		if (root->child_2)
			ft_printf("{%s}>child_2 = \'%s\'\n", root->line, root->child_2->line);
		printTreePreorder(root->child_1);
		printTreePreorder(root->child_2);
	}
}
