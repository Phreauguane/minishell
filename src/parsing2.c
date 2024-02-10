/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:32:06 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 00:17:45 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_str_env(char limiter, char **str, char **start, char **envp)
{
	(*start)++;
	if (**start != limiter && **start)
	{
		check_env(start, str, envp);
		return (get_str_env(limiter, str, start, envp));
	}
	if (**start == limiter)
	{
		(*start)++;
		return (1);
	}
	return (0);
}

char	*get_word_env(char **s, char **envp)
{
	char	*word;

	word = NULL;
	while (ft_isspace(**s))
		(*s)++;
	while (**s)
	{
		if (**s == '\"')
		{
			get_str_env('\"', &word, s, envp);
			ft_printf("word : [%s]", word);
		}
		else if (**s == '\'')
			get_str('\'', &word, s);
		else if (**s == ' ')
		{
			(*s)++;
			return (word);
		}
		else if (**s == '\0' || **s == '>' || **s == '<' || **s == '|')
			return (word);
		else
		{
			check_env(s, &word, envp);
			(*s)++;
		}
	}
	return (word);
}

void	check_env(char **s, char **word, char **envp)
{
	char	*val;
	char	*var;

	var = NULL;
	if (**s != '$')
	{
		*word = str_addc(*word, **s);
		return ;
	}
	else if (*((*s) + 1) == '?')
		val = ft_itoa(g_exec);
	else
	{
		while (!ft_isspace(**s) && **s && **s != '\"' && **s != '\'')
		{
			(*s)++;
			var = str_addc(var, **s);
		}
		val = get_env_value(var, envp);
		free(var);
	}
	if (val)
		*word = str_adds(*word, val, ft_strlen(val));
	if (var == NULL)
		free(val);
}
