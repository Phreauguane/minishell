/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:38 by larz              #+#    #+#             */
/*   Updated: 2024/02/06 18:53:37 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define STATE_CMD 0
# define STATE_PRM 1
# define STATE_RDR 2
# define STATE_PIP 3
# define STATE_FIL 4
# define RDR_IN			0
# define RDR_OUT		1
# define RDR_APPEND		2
# define RDR_HERE_DOC	3

# define DEF 			"\001\e\033[0m\002"
# define RED 			"\001\e\033[0;31m\002"
# define GREEN 			"\001\e\033[0;32m\002"
# define YELLOW 		"\001\e\033[0;33m\002"
# define BLUE 			"\001\e\033[0;34m\002"
# define PURPLE 		"\001\e\033[0;35m\002"
# define CYAN 			"\001\e\033[0;36m\002"
# define WHITE 			"\001\e\033[0;37m\002"
# define BOLD_RED 		"\001\e\033[1;31m\002"
# define BOLD_GREEN 	"\001\e\033[1;32m\002"
# define BOLD_YELLOW 	"\001\e\033[1;33m\002"
# define BOLD_BLUE 		"\001\e\033[1;34m\002"
# define BOLD_PURPLE 	"\001\e\033[1;35m\002"
# define BOLD_CYAN 		"\001\e\033[1;36m\002"
# define BOLD_WHITE 	"\001\e\033[1;37m\002"

typedef	struct s_prm
{
	char			*str;
	struct s_prm	*next;
}	t_prm;

typedef struct s_pipeline
{
	char				*cmd;
	t_prm				*prm;
	int					fd_in;
	int					fd_out;
	struct s_pipeline	*next;
}	t_pipeline;

/*	PARSING.C	*/
t_pipeline	*parse(const char *str);

/*	PRM.C		*/
void		add_prm(t_prm **prms, char *prm);
void		free_prms(t_prm **prms);

/*	PIPELINE.C	*/
t_pipeline	*add_ppl(t_pipeline **ppl);
void		free_ppl(t_pipeline **ppl);
t_pipeline	*get_last(t_pipeline *ppl);

/*	EXECUTE.C	*/
void		execute(t_pipeline **ppl, char **envp);

/*	RUN.C		*/
int 		run(t_pipeline **ppl, char **envp);

/*	INPUT.C		*/
char 		*build_input(char **envp);

#endif