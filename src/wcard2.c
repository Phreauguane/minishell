/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcard2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:51:10 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/29 19:44:46 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_word_ls(char **s)
{
	char	*word;
	char	lim;

	word = NULL;
	lim = '\0';
	while (ft_isspace(**s))
		(*s)++;
	while (**s)
	{
		if (lim == **s)
			lim = '\0';
		else if (**s == '\'' || **s == '\"')
			lim = **s;
		if (**s == ' ')
		{
			(*s)++;
			return (word);
		}
		word = str_addc(word, **s);
		(*s)++;
	}
	return (word);
}

void	run3(t_pipeline *ppl, int *stat, char **envp)
{
	int		stat1;
	int		stderr_bk;
	pid_t	child1;

	stderr_bk = dup(STDERR_FILENO);
	child1 = fork();
	if (child1 < 0)
		return ;
	if (child1 == 0)
		execute2(ppl, envp);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	waitpid(child1, &stat1, 0);
	dup2(stderr_bk, STDERR_FILENO);
    *stat = stat1;
}

char	*wildcard(char *line, char **envp)
{
	char	*out;
	char	*wcard;
	char	*word;
	char	*s;
	
	out = NULL;
	s = line;
	while (*s)
	{
		word = get_word_ls(&s);
		if (out && word)
			out = str_addc(out, ' ');
		wcard = wildcard_word(word, envp);
		if (!wcard)
			continue ;
		out = str_adds(out, wcard, ft_strlen(wcard));
		free(wcard);
	}
	return (out);
}
