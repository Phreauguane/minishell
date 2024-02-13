/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:21:37 by larz              #+#    #+#             */
/*   Updated: 2024/02/13 13:37:13 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char *get_folder_name(char **envp)
{
    char    *home_dir;
	char	*path;

	home_dir = get_env_value("HOME", envp);
	path = get_env_value("PWD", envp);
	if (ft_strncmp(path, home_dir, ft_strlen(path)) == 0)
		return ("~");
	return (ft_strrchr(path, '/') + 1);
}

char	*get_input(char *input)
{
	char	*line;

	line = readline(input);
	free(input);
	return (line);
}

char	*build_input(char **envp)
{
	char		*out;
	char		*line;

	out = NULL;
	line = get_env_value("USER", envp);
	out = str_adds(out, BOLD_PURPLE"@", ft_strlen(BOLD_PURPLE"@"));
	out = str_adds(out, line, ft_strlen(line));
	out = str_adds(out, " "BOLD_CYAN, ft_strlen(" "BOLD_CYAN));
	line = get_folder_name(envp);
	out = str_adds(out, line, ft_strlen(line));
	line = run_git(envp);
	out = str_adds(out, line, ft_strlen(line));
	free(line);
    if (g_exec == 0)
	    out = str_adds(out, BOLD_GREEN" 8=> "CYAN, ft_strlen(BOLD_GREEN" 8=> "CYAN));
    else
	    out = str_adds(out, BOLD_RED" 8=> "CYAN, ft_strlen(BOLD_RED" 8=> "CYAN));
	return (out);
}
