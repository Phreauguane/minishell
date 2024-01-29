/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:30:38 by larz              #+#    #+#             */
/*   Updated: 2024/01/29 18:12:58 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef	struct s_prm
{
	char			*str;
	struct s_prm	*next;
}	t_prm;


typedef struct s_command
{
	char	*cmd;
	t_prm	*prm;
	char	*dir;
	int		in;
	int		out;
}	t_command;

/*	PARSING.C	*/
t_command	parse(const char *str);

/*	PRM.C		*/
void	add_prm(t_prm **prms, char *prm);
void	free_prms(t_prm **prms);

#endif