/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:32:06 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 20:24:00 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_word_env(char **s, char **envp)
{
	char	*word;

	word = NULL;
	while (ft_isspace(**s))
		(*s)++;
	while (!ft_isspace(**s) && **s)
		check_env(s, &word, envp);
	return (word);
}

void	add_exec_status(char **s, char **word)
{
	char	*val;

	(*s) += 2;
	val = ft_itoa(g_exec);
	*word = str_adds(*word, val, ft_strlen(val));
	free(val);
}

void	add_env_var(char **s, char **word, char **envp)
{
	char	*var;
	char	*val;

	var = NULL;
	(*s)++;
	while (!ft_isspace(**s) && **s && **s != '\"' && **s != '\''
		&& **s != '/')
	{
		var = str_addc(var, **s);
		(*s)++;
	}
	val = get_env_value(var, envp);
	*word = str_adds(*word, val, ft_strlen(val));
	free(var);
}

void	add_str(char **s, char **word, char **envp, char lim)
{
	(*s)++;
	while (**s && **s != lim)
	{
		if (**s == '$' && *(*s + 1) == '?' && lim =='\"')
			add_exec_status(s, word);
		else if (**s == '$' && lim =='\"')
			add_env_var(s, word, envp);
		else if (**s != lim)
			*word = str_addc(*word, *((*s)++));
	}
	if (**s == lim)
		(*s)++;
}

void	check_env(char **s, char **word, char **envp)
{
	if (**s == '$' && *(*s + 1) == '?')
		add_exec_status(s, word);
	else if (**s == '$')
		add_env_var(s, word, envp);
	else if (**s == '\'' || **s == '\"')
		add_str(s, word, envp, **s);
	else
		*word = str_addc(*word, *((*s)++));
}
