/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:38 by larz              #+#    #+#             */
/*   Updated: 2024/03/25 12:26:49 by jde-meo          ###   ########.fr       */
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
# include <limits.h>

/*	PARSING STATES				*/
# define MODE_NEW_CMD 1
# define MODE_CMD_PRM 2

/*	REDIRECTION TYPES			*/
# define RDR_OUT_APP 		1
# define RDR_OUT_NEW 		2
# define RDR_IN_NORMAL 		3
# define RDR_IN_HEREDOC 	4

/*	COLOR CODES					*/
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

/*	COMMAND HISTORY FILE		*/
# define HISTORY_FILE	".history"

/*	PARSING STATE ERROR CODES	*/
# define NO_ERROR			0
# define ERROR_NO_CMD		1
# define ERROR_INVALID_CMD	2
# define ERROR_PARSING		3

/*	BINARY TREE NODE TYPES		*/
# define TYPE_UNDEF	0
# define TYPE_CMD	1
# define TYPE_OPP_A	2
# define TYPE_OPP_B	3

/*	BINARY TREE FLAGS			*/
# define NO_PRIORITY	0
# define PRIORITY		1

/*	GLOBAL VQRIABLES			*/
/*		LAST COMMAND EXIT STATUS*/
extern int	g_exec;
/*		STDIN BACKUP			*/
extern int	g_stdin;

/*	COMMAND PARAMS STRUCTURE	*/
typedef struct s_prm
{
	char			*str;
	struct s_prm	*next;
}	t_prm;

/*	PIPELINE STRUCTURE			*/
typedef struct s_pipeline
{
	char				*cmd;
	t_prm				*prm;
	pid_t				pid;
	int					fd_in;
	int					fd_out;
	int					error;
	struct s_pipeline	*next;
}	t_pipeline;

/*	BINARY TREE STRUCTURE		*/
typedef struct s_node
{
	char			*line;
	t_pipeline		*ppl;
	int				type;
	int				prio;
	int				error;
	struct s_node	*child_1;
	struct s_node	*child_2;
	struct s_node	*parent;
}	t_node;

/*	MAIN.C			*/
void		exit_handler(char *msg, char *details, int free_msg, int code);
int			exit_minishell(int out);

/*	SIG.C			*/
void		handler(int sig);
void		config(char **envp);
int			check_input(char *line);

/*	PARSING.C		*/
char		*get_word_env(char **s, char **envp);
char		*get_word(char **s);
int			get_str(char limiter, char **str, char **start);
t_pipeline	*parse(const char *str, char **envp);

/*	PARSING2.C		*/
void		check_env(char **s, char **word, char **envp);

/*	PIPE.C*/
void		create_pipe(t_pipeline **ppl, char **s, int *mode);
int			verif_pipeline(t_pipeline **ppl, char **envp);

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
char		**build_prms(t_pipeline *ppl);
char		*get_exec(char *cmd, char **envp);

/*	RUN.C			*/
void		run(t_pipeline *ppl, char ***envp);
void		run_pipeline(t_pipeline **ppl, char ***envp);
char		*run_cmd(char *cmd, char **envp);
char		*run_fullcmd(char *cmd, char **envp);
char		*run_fullcmdprm(char *dir, char *cmd, char **envp);

/*	RUN_BUILTIN.C	*/
int			run_builtin(t_pipeline *ppl, char ***envp);
void		free2(void *ptr);
int			is_builtin(t_pipeline *ppl);

/*	INPUT.C			*/
char		*build_input(char **envp);
char		*get_input(char *input);

/*	REDIRECT.C		*/
void		redirect_out_app(t_pipeline **ppl, char **s);
void		redirect_out_normal(t_pipeline **ppl, char **s);
void		redirect_in_normal(t_pipeline **ppl, char **s);

/*  HEREDOC.C   	*/
void		heredoc(t_pipeline **ppl, char **s);

/*	EXIT.C			*/
void		exit_builtin(t_pipeline *ppl);

/*  ENV.C       	*/
char		*get_env_value(char *var, char **envp);
void		set_env_value(char *var, char *value, char **envp);
int			env(char **envp);
void		update_shlvl(char **envp);
int			find_var(char *var, char **envp);

/*  CD.C        	*/
int			cd(t_pipeline *ppl, char **envp);

/*	HISTORY.C		*/
void		history(char *input);
void		open_history(char **envp);
void		cleanup_history(void);

/*	ECHO.C			*/
int			echo(t_pipeline *ppl);

/*	PWD.C			*/
void		run_raw(t_pipeline *ppl, char **envp);
int			pwd(char **envp);

/*	EXPORT.C		*/
int			export(t_pipeline *ppl, char ***envp);
char		**dup_envp(char **envp);

/*	UNSET.C			*/
int			unset(t_pipeline *ppl, char **envp);
void		print_pipeline(t_pipeline *ppl);

/*	GIT.C			*/
char		*run_git(char **envp);
void		execute2(t_pipeline *ppl, char **envp);
void		run2(t_pipeline *ppl, int *stat, char **envp);

/*	WCARD.C			*/
char		**get_ls(char *prm, char **envp);
int			count_words(char *str);
char		*get_next_line_ls(char **s);
int			verify(char *str, char *file);

/*	WCARD2.C		*/
char		*wildcard(char *str, char **envp);
void		run3(t_pipeline *ppl, int *stat, char **envp);

/*	WCARD3.C			*/
char		*wildcard_word(char *str, char **envp);

/*	WCARD4.C			*/
int			verify_first(char *first, char *dir);
char		**get_ls_verif(char *first, char **envp);

/*	TREE.C				*/
t_node		*add_nodes(t_node *root, char *str, int i);
t_node		*read_node(char *str, int *i);
void		add_child(t_node *root, t_node *child);
char		*get_line_inside(char *str, int *i);
void		skip_spaces(char *str, int *i);
void		printTreePreorder(t_node *root);

/*	TREE2.C				*/
t_node		*createnode(void);
void		free_tree(t_node *root);
t_node		*create_parent(t_node *child, char *line);
void		or(char *cmd2, t_node *root, char *str, int *i);
t_node		*create_node(char *cmd);

/*	TREE3.C				*/
char		*parse_command(char *str, int *i);
t_node		*manage_parent(char	*cmd1, t_node *root, char *str, int *i);
void		throw_parsing_error(char *err, char near);
/*	
	Takes the line input, creates the corresponding binary tree
	runs it and frees all allocated memory
*/
void		run_input(const char *str, char ***envp);

/*	RUN_TREE.C			*/
int			parse_tree(t_node **tree, char **envp);
int			run_nodes(t_node **tree, char ***envp);
void		run_tree(t_node **tree, char ***envp);

#endif