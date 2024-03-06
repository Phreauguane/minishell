/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcard.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:18:02 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/05 16:16:28 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	verify(char *str, char *file)
{
	while (*str)
	{
		if (*str != '*' && *str != *file)
			return (0);
		if (*str == '*')
		{
			while (*str == '*')
				str++;
			while (*file != *str)
			{
				if (!*file)
					return (*str == '\0');
				file++;
			}
		}
		if (*file)
			file++;
		if (*str)
			str++;
	}
	return (*file == *str);
}

char	*get_next_line_ls(char **s)
{
	char	*word;

	word = NULL;
	while (**s)
	{
		if (**s == '\0')
			return (word);
		else if (**s == '\n')
		{
			(*s)++;
			return (word);
		}
		else
		{
			word = str_addc(word, **s);
			(*s)++;
		}
	}
	return (word);
}

int	count_words(char *str)
{
	int		i;
	char	*s;
	char	*w;

	i = 0;
	s = str;
	while (s && *s)
	{
		w = get_next_line_ls(&s);
		free2(w);
		i++;
	}
	return (i);
}

char	**get_ls(char *prm, char **envp)
{
	int		size;
	char	*ls;
	char	*s;
	char	*word;
	char	**out;

	if (prm)
		ls = run_fullcmdprm(prm, "ls", envp);
	else
		ls = run_fullcmd("ls", envp);
	size = count_words(ls);
	out = malloc(sizeof(char *) * (size + 1));
	out[size] = NULL;
	size = 0;
	s = ls;
	while (*s)
	{
		word = get_next_line_ls(&s);
		out[size++] = word;
	}
	free2(ls);
	return (out);
}
