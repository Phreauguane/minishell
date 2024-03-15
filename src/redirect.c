/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:09:27 by larz              #+#    #+#             */
/*   Updated: 2024/03/13 11:43:25 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_out_app(t_pipeline **ppl, char **s, int mode)
{
	char	*word;
	
	(*s) += 2;
	word = get_word(s);
	if (get_last(*ppl)->fd_out != 1)
		close(get_last(*ppl)->fd_out);
	get_last(*ppl)->fd_out = open(word, O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	if (get_last(*ppl)->fd_out < 0)
		exit_handler(word, "error while opening/creating file", 1, 1);
	free2(word);
}

void	redirect_out_normal(t_pipeline **ppl, char **s, int mode)
{
	char	*word;
	
	(*s)++;
	word = get_word(s);
	if (get_last(*ppl)->fd_out != 1)
		close(get_last(*ppl)->fd_out);
	get_last(*ppl)->fd_out = open(word, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
	if (get_last(*ppl)->fd_out < 0)
		exit_handler(word, "error while opening/creating file", 1, 1);
	free2(word);
}

void	redirect_in_normal(t_pipeline **ppl, char **s, int mode)
{
	char	*word;

	(*s)++;
	word = get_word(s);
	if (get_last(*ppl)->fd_in != 0)
		close(get_last(*ppl)->fd_in);
	get_last(*ppl)->fd_in = open(word, O_RDONLY);
	if (get_last(*ppl)->fd_in < 0)
		exit_handler(word, "No such file or directory", 1, 1);
	free2(word);
}
