/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:10:01 by larz              #+#    #+#             */
/*   Updated: 2024/01/30 18:03:34 by jde-meo          ###   ########.fr       */
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
	int			state;
	char		*word;
	int			rdr;

	ppl = NULL;
	state = STATE_CMD;
	rdr = -1;
	s = (char *)str;
	add_ppl(&ppl)->cmd = get_word(&s);
	while (*s)
	{
		word = get_word(&s);
		if (word == NULL)
		{
			if (*s == '|')
				state = STATE_PIP;
			if (*s == '<' && *(s + 1) == '<')
				rdr = RDR_HERE_DOC;
			else if (*s == '<')
				rdr = RDR_IN;
			if (*s == '>' && *(s + 1) == '>')
				rdr = RDR_APPEND;
			else if (*s == '>')
				rdr = RDR_OUT;
		}
		else
		{
			if (state == STATE_CMD || state == STATE_PRM)
			{
				state = STATE_PRM;
				add_prm(&(get_last(ppl)->prm), word);
			}
			if (state == STATE_FIL)
			{
				state = STATE_PRM;
			}
			if (state == STATE_RDR)
			{
				state = STATE_FIL;
			}
			if (state == STATE_PIP)
			{
				state = STATE_CMD;
			}
		}
	}
	return (ppl);
}
