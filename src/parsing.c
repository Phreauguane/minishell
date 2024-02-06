/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:10:01 by larz              #+#    #+#             */
/*   Updated: 2024/02/06 16:52:20 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_str(char limiter, char **str, char **start)
{
	(*start)++;
	if (**start != limiter && **start)
	{
		*str = str_addc(*str, **start);
		return (get_str(limiter, str, start));
	}
	if (**start == limiter)
	{
		(*start)++;
		return (1);
	}
	return (0);
}

char	*get_word(char **s)
{
	char	*word;

	word = NULL;
	while (**s)
	{
		if (**s == '\"')
			get_str('\"', &word, s);
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
			word = str_addc(word, **s);
			(*s)++;
		}
	}
	return (word);
}

t_pipeline	*parse(const char *str)
{
	char		*s;
	t_pipeline	*ppl;

	ppl = NULL;
	s = (char *)str;
	add_ppl(&ppl)->cmd = get_word(&s);
	while (*s)
		add_prm(&(get_last(ppl)->prm), get_word(&s));
	return (ppl);
}
