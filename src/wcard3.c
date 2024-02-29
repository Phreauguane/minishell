/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcard3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:41:36 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/29 19:22:38 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_ls(char **first, char **scd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			break;
		*first = str_addc(*first, str[i]);
		i++;
	}
	if (str[i])
		i++;
	while(str[i])
	{
		*scd = str_addc(*scd, str[i]);
		i++;
	}
	ft_printf("[%s / %s]\n", *first, *scd);
}

char	**get_lsprm(char *dir,char **envp)
{
	int		size;
	char	*dir2;
	char	*ls;
	char	*s;
	char	*word;
	char	**out;

	dir2 = ft_strdup(dir);
	dir2 = str_addc(dir2, '/');
	ls = run_fullcmdprm(dir2, "ls", envp);
	free(dir2);
	size = count_words(ls);
	out = malloc(sizeof(char *) * (size + 1));
	out[size] = NULL;
	size = 0;
	s = ls;
	while (s && *s)
	{
		word = get_next_line_ls(&s);
		out[size++] = word;
	}
	free(ls);
	return (out);
}

char	*wildcard_word3(char *str, char **envp, char *dir)
{
	char	**tab;
	char	**bk;
	char	*out;

	if (ft_strchr(str, '*') == NULL)
		return (str);
	out = NULL;
	tab = get_lsprm(dir, envp);
	bk = tab;
	while (*tab)
	{
		if (verify(str, *tab))
		{
			out = str_adds(out, dir, ft_strlen(dir));
			out = str_adds(str_addc(out, '/'), *tab, ft_strlen(*tab));
			if (*(tab + 1))
				out = str_addc(out, ' ');
		}
		tab++;
	}
	ft_free_split(bk);
	return (out);
}

char	*wildcard_word2(char **tab, char *first, char *scd, char **envp)
{
	char	*out;
	char	*temp;

	out = NULL;
	while (*tab)
	{
		if (verify(first, *tab))
		{
			if (scd == NULL)
				out = str_adds(out, *tab, ft_strlen(*tab));
			else
			{
				temp = wildcard_word3(scd, envp, *tab);
				if (temp)
					out = str_adds(out, temp, ft_strlen(temp));
				if (temp)
					free(temp);
			}
			if (*(tab + 1))
					out = str_addc(out, ' ');
		}
		tab++;
	}
	return (out);
}

char	*wildcard_word(char *str, char **envp)
{
	char	**tab;
	char	**bk;
	char	*out;
	char	*first;
	char	*scd;

	first = NULL;
	scd = NULL;
	if (ft_strchr(str, '*') == NULL)
		return (str);
	parse_ls(&first, &scd, str);
	tab = get_ls(envp);
	bk = tab;
	out = wildcard_word2(tab, first, scd, envp);
	if (!out)
		return (str);
	if (str)
		free(str);
	ft_free_split(bk);
	return (out);
}
