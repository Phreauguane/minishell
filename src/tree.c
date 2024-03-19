/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:34:38 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/19 15:34:59 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node *createNode()
{
	t_node *newNode;

	newNode = (t_node *)malloc(sizeof(t_node));
	if (newNode == NULL)
	{
		ft_printf("Erreur d'allocation de mémoire\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(newNode, sizeof(t_node));
	return (newNode);
}

void freeTree(t_node *root)
{
	if (root == NULL)
		return;
	freeTree(root->child_1);
	freeTree(root->child_2);
	free(root);
}

void printTreePreorder(t_node *root)
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

t_node	*create_parent(t_node *child, char *line)
{
	child->parent = createNode();
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
	ft_printf("c2 c2 : %s\n", root->child_2->child_2->line);
}

t_node	*create_node(char *cmd)
{
	t_node *node;

	node = createNode();
	node->type = TYPE_CMD;
	node->line = cmd;
	return (node);
}

char	*parse_command(char *str, int *i)
{
	char	*cmd;
	int		quotes;

	cmd = NULL;
	quotes = 0;
	while (str[*i + 1])
	{
		if (quotes != 1 && ((str[*i] == '&' && str[*i + 1] == '&') || (str[*i] == '|' && str[*i + 1] == '|')))
			break;
		if (str[*i] == '"' && quotes == 0)
			quotes = 1;
		else if (str[*i] == '"' && quotes == 1)
			quotes = 0;
		if (cmd != NULL || !ft_isspace(str[*i]))
			cmd = str_addc(cmd, str[*i]);
		(*i)++;
    }
	if ((str[*i] != '|' && str[*i] != '&') && !ft_isspace(str[*i]))
		cmd = str_addc(cmd, str[*i]);
	return (cmd);
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

t_node	*manage_parent(char	*cmd1, t_node *root, char *str, int *i)
{
	if(root->type == TYPE_OPP_B && !(root->prio) && (str[*i] == '&' && str[*i + 1] == '&'))
		or(cmd1, root, str, i);
	else
	{
		root = create_parent(root, cmd1);
		(*i) += 2;
	}
	return (root);
}

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
	if (str[*i] != '(')
		return (NULL);
	(*i)++;
	while (str[*i] != ')')
	{
		if (str[*i] == '(')
		{
			out = get_line_inside(str, i);
			line = str_addc(line, '(');
			line = str_adds(line, out, ft_strlen(out));
			line = str_addc(line, ')');
		}
		else
		{
			line = str_addc(line, str[*i]);
			(*i)++;
		}
	}
	(*i)++;
	return (line);	
}

t_node	*create_child_tree(char *str, int *i)
{
	(void)str;
	(void)i;
	return (NULL);
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
		child->prio = PRIORITY;
		skip_spaces(str, i);
	}
	else
		child = create_node(parse_command(str, i));
	ft_printf("read node : %s\n", child->line);
	return (child);
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

int mainnnnn(int ac, char **av)
{
	t_node	*root;

	if (ac < 2)
		return (0);
	root = NULL;
	root = add_nodes(root, av[1], 0);
	ft_printf("Parcours préfixe de l'arbre binaire:\n");
	printTreePreorder(root);
	printf("\n");
	freeTree(root);
	return 0;
}
