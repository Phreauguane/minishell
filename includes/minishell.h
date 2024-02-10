/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:38 by larz              #+#    #+#             */
/*   Updated: 2024/02/10 18:47:49 by jde-meo          ###   ########.fr       */
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
# include <errno.h>

# define MODE_NEW_CMD 1
# define MODE_CMD_PRM 2

# define RDR_OUT_APP 		1
# define RDR_OUT_NEW 		2
# define RDR_IN_NORMAL 		3
# define RDR_IN_HEREDOC 	4

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

extern int   g_exec;

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
    int					error;
	struct s_pipeline	*next;
}	t_pipeline;

/*	MAIN.C		*/
void		exit_handler(char *msg, char *details, int free_msg, int code);

/*	PARSING.C	*/
char		*get_word(char **s);
t_pipeline	*parse(const char *str);

/*	PRM.C		*/
void		add_prm(t_prm **prms, char *prm);
void		free_prms(t_prm **prms);

/*	PIPELINE.C	*/
t_pipeline	*add_ppl(t_pipeline **ppl);
void		free_cmd(t_pipeline *ppl);
void		free_ppl(t_pipeline **ppl);
t_pipeline	*get_last(t_pipeline *ppl);

/*	EXECUTE.C	*/
void		execute(t_pipeline *ppl, char **envp);

/*	RUN.C		*/
void 		run(t_pipeline *ppl, char **envp);
void        run_pipeline(t_pipeline *ppl, int stdin_bk, char **envp);
char		*run_cmd(char *cmd, char **envp);

/*	INPUT.C		*/
char 		*build_input(char **envp);

/*	REDIRECT.C	*/
void		redirect_out_app(t_pipeline **ppl, char **s, int mode);
void		redirect_out_normal(t_pipeline **ppl, char **s, int mode);
void		redirect_in_normal(t_pipeline **ppl, char **s, int mode);

/*  HEREDOC.C   */
void    	heredoc(t_pipeline **ppl, char **s, int mode);

/*  ENV.C       */
char        *get_env_value(char *var, char **envp);
void		set_env_value(char *var, char *value, char **envp);

/*  CD.C        */
int			cd(t_pipeline *ppl, char **envp);

#endif