/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:48:24 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 13:53:52 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	history(char *input)
{
    int            i;
    int            fd;

    i = 0;
    fd = open(HISTORY_FILE, O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
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

void	open_history()
{
    int        fd;
    char    *line;
	char	*l;

    using_history();
    fd = open(HISTORY_FILE, O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
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
