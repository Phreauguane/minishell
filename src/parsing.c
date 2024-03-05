/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:10:01 by larz              #+#    #+#             */
/*   Updated: 2024/03/05 15:58:14 by jde-meo          ###   ########.fr       */
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
	while (ft_isspace(**s))
		(*s)++;
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

void	read_data(t_pipeline **ppl, char **s, int *mode, char **envp)
{
	if (*mode == MODE_NEW_CMD)
	{
		get_last(*ppl)->cmd = get_word(s);
		*mode = MODE_CMD_PRM;
	}
	if (*mode == MODE_CMD_PRM)
		add_prm(&(get_last(*ppl)->prm), get_word_env(s, envp));
}

int	handle_parsing(t_pipeline **ppl, char **s, int *mode, char **envp)
{
	int	pipe_fd[2];
	
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '|')
	{
		if (*mode == MODE_NEW_CMD)
			exit_handler("parsing error near token |", NULL, 0, 2);
		pipe(pipe_fd);
		get_last(*ppl)->fd_out = pipe_fd[1];
		add_ppl(ppl);
		get_last(*ppl)->fd_in = pipe_fd[0];
		*mode = MODE_NEW_CMD;
		(*s)++;
	}
	if (**s == '>' && *(*s + 1) == '>')
		redirect_out_app(ppl, s, *mode);
	else if (**s == '>')
		redirect_out_normal(ppl, s, *mode);
	if (**s == '<' && *(*s + 1) == '<')
		heredoc(ppl, s, *mode);
	else if (**s == '<')
		redirect_in_normal(ppl, s, *mode);
	read_data(ppl, s, mode, envp);
	return (0);
}

t_pipeline	*parse(const char *str, char **envp)
{
	char		*s;
	char		*bk;
	t_pipeline	*ppl;
	int			mode;

	ppl = NULL;
	s = wildcard((char *)str, envp);
	bk = s;
	mode = MODE_NEW_CMD;
	add_ppl(&ppl);
	while (*s)
		handle_parsing(&ppl, &s, &mode, envp);
	free2(bk);
	return (ppl);
}
