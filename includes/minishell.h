/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:38 by larz              #+#    #+#             */
/*   Updated: 2024/01/30 17:55:42 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define STATE_CMD 0
# define STATE_PRM 1
# define STATE_RDR 2
# define STATE_PIP 3
# define STATE_FIL 4

# define RDR_IN			0
# define RDR_OUT		1
# define RDR_APPEND		2
# define RDR_HERE_DOC	3

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

#endif