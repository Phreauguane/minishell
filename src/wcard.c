/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcard.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:18:02 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/05 15:28:53 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	verify(char *str, char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '*' && str[i] != file[j])
			return (0);
		if (str[i] == '*')
		{
			while (str[i] == '*')
				i++;
			while (file[j] != str[i])
			{
				if (!file[j])
					return (str[i] == '\0');
				j++;
			}
		}
		if (file[j])
			j++;
		if (str[i])
			i++;
	}
	return (file[j] == str[i]);
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
