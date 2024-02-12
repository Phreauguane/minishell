/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:05:31 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/12 17:58:58 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    *ft_last_word(char *line)
{
    int        i;

    i = ft_strlen(line) - 2;
	line[ft_strlen(line) - 1] = '\0';
    while (i >= 0 && line[i] && line[i] != ' ')
		i--;
    return (line + i + 1);
}

void	run_git2(char *last_word, int lines, char **line)
{
	*line = str_adds(*line, " "BOLD_BLUE, ft_strlen(" "BOLD_BLUE));
	*line = str_adds(*line, last_word, ft_strlen(last_word));
	free(last_word);
	if (lines == 4)
        *line = str_adds(*line, BOLD_BLACK""BG_GREEN"✓ "DEF,
            ft_strlen(BOLD_BLACK""BG_GREEN"✓ "DEF));
    else
        *line = str_adds(*line, BOLD_BLACK""BG_RED"✗ "DEF,
            ft_strlen(BOLD_BLACK""BG_RED"✗ "DEF));
}

static void	execute2(t_pipeline *ppl, char **envp)
{
	char	**cmd_args;
	char	*exec;
	int		pp[2];
	int		ex;

	pipe(pp);
	dup2(pp[1], STDERR_FILENO);
	close(pp[0]);
	close(pp[1]);
	dup2(ppl->fd_in, STDIN_FILENO);
	dup2(ppl->fd_out, STDOUT_FILENO);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	if (ppl->cmd == NULL)
		exit(0);
	cmd_args = build_prms(ppl);
	exec = get_exec(ppl->cmd, envp);
	ex = execve(exec, cmd_args, envp);
	ft_printf("minishell: %s: %s\n", exec, strerror(errno));
	exit(ex);
}

static void	run2(t_pipeline *ppl, int *stat, char **envp)
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
	free_ppl(&ppl);
	dup2(stderr_bk, STDERR_FILENO);
    *stat = stat1;
}

char    *run_git(char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];
	char		*line;
	int			i;
	char		*last_word;

	ppl = NULL;
	pipe(pipe_fd);
	add_ppl(&ppl)->cmd = str_adds(NULL, "git", 3);
	add_prm(&(ppl->prm), str_adds(NULL, "status", 6));
	ppl->fd_out = pipe_fd[1];
	run2(ppl, &i, envp);
	if (i != 0)
		return (str_addc(NULL, '\0'));
	i = 0;
	line = get_next_line(pipe_fd[0]);
	last_word = ft_strdup(ft_last_word(line));
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(pipe_fd[0]);
	}
	run_git2(last_word, i, &line);
	return (line);
}
