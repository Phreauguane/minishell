/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:48:24 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 22:00:45 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*g_dir;

void	history(char *input)
{
    int            i;
    int            fd;

    i = 0;
	if (!input)
		return ;
    fd = open(g_dir, O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd < 0)
    {
        ft_printf("Error opening file.\n");
        return ;
    }
    HIST_ENTRY **hist_list = history_list();
    while (hist_list && hist_list[i] && hist_list[i + 1])
        i++;
    if ((!hist_list || ft_strncmp(input, hist_list[i]->line, 
		ft_strlen(input) + ft_strlen(hist_list[i]->line)) != 0)
		&& ft_strlen(input) > 1)
    {
        write(fd, input, ft_strlen(input));
        write(fd, "\n", 1);
        add_history(input);
    }
    close(fd);
}

void	save_dir(char **envp)
{
	char	*wd;

	wd = run_cmd("pwd", envp);
	g_dir = str_adds(NULL, wd, ft_strlen(wd) - 1);
	g_dir = str_addc(g_dir, '/');
	g_dir = str_adds(g_dir, HISTORY_FILE, ft_strlen(HISTORY_FILE));
}

void	open_history(char **envp)
{
    int        fd;
    char    *line;
	char	*l;

    using_history();
	save_dir(envp);
    fd = open(g_dir, O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd < 0)
		ft_printf("Error opening file.\n");
	line = (char *)1;
    while(line && fd >= 0)
    {
        line = get_next_line(fd);
        if (line)
		{
			l = str_adds(NULL, line, ft_strlen(line) - 1);
            add_history(l);
            free(line);
			free(l);
		}
    }
	if (fd >= 0)
	    close(fd);
}

void	cleanup_history()
{
	clear_history();
	free(g_dir);
}