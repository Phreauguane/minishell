/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:38 by larz              #+#    #+#             */
/*   Updated: 2024/02/11 22:36:51 by jde-meo          ###   ########.fr       */
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
# define BOLD_BLACK 	"\001\e\033[1;30m\002"
# define COLOR			"\001\e\033[38;2;255;153;153m\002"
# define BG_GREEN		"\001\e\033[48;2;0;200;0m\002"
# define BG_RED			"\001\e\033[48;2;200;70;0m\002"
# define FG_GREEN		"\001\e\033[38;2;0;200;0m\002"
# define FG_RED			"\001\e\033[38;2;200;70;0m\002"

# define HISTORY_FILE	".history"

extern int	g_exec;
extern int	g_stdin;

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

/*	MAIN.C			*/
void		exit_handler(char *msg, char *details, int free_msg, int code);

/*	PARSING.C		*/
char		*get_word_env(char **s, char **envp);
char		*get_word(char **s);
int			get_str(char limiter, char **str, char **start);
t_pipeline	*parse(const char *str, char **envp);

/*	PARSING2.C		*/
void		check_env(char **s, char **word, char **envp);

/*	PRM.C			*/
void		add_prm(t_prm **prms, char *prm);
void		free_prms(t_prm **prms);

/*	PIPELINE.C		*/
t_pipeline	*add_ppl(t_pipeline **ppl);
void		free_cmd(t_pipeline *ppl);
void		free_ppl(t_pipeline **ppl);
t_pipeline	*get_last(t_pipeline *ppl);

/*	EXECUTE.C		*/
void		execute(t_pipeline *ppl, char **envp);
char    	**build_prms(t_pipeline *ppl);
char		*get_exec(char *cmd, char **envp);

/*	RUN.C			*/
void 		run(t_pipeline *ppl, char ***envp);
void        run_pipeline(t_pipeline *ppl, char ***envp);
char		*run_cmd(char *cmd, char **envp);

/*	RUN_BUILTIN.C	*/
int			run_builtin(t_pipeline *ppl, char ***envp);

/*	INPUT.C			*/
char 		*build_input(char **envp);

/*	REDIRECT.C		*/
void		redirect_out_app(t_pipeline **ppl, char **s, int mode);
void		redirect_out_normal(t_pipeline **ppl, char **s, int mode);
void		redirect_in_normal(t_pipeline **ppl, char **s, int mode);

/*  HEREDOC.C   	*/
void    	heredoc(t_pipeline **ppl, char **s, int mode);

/*  ENV.C       	*/
char        *get_env_value(char *var, char **envp);
void		set_env_value(char *var, char *value, char **envp);
int			env(char **envp);
void		update_shlvl(char **envp);
int			find_var(char *var, char **envp);

/*  CD.C        	*/
int			cd(t_pipeline *ppl, char **envp);

/*	HISTORY.C		*/
void		history(char *input);
void		open_history(char **envp);
void		cleanup_history();

/*	ECHO.C			*/
int			echo(t_pipeline *ppl);

/*	PWD.C			*/
void		run_raw(t_pipeline *ppl, char **envp);
int			pwd(char **envp);

/*	EXPORT.C		*/
int			export(t_pipeline *ppl, char ***envp);
char		**dup_envp(char **envp);

/*	GIT.C			*/
char    	*run_git(char **envp);

#endif