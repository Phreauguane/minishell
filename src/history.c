/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:48:24 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/10 21:51:30 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int history(char *input)
{
	static int	setup;
	int			i;

	i = 0;
	if (setup != 69)
		using_history();
	if (setup != 69)
		setup = 69;
	HIST_ENTRY **hist_list = history_list();
	while (hist_list && hist_list[i] && hist_list[i + 1])
		i++;
	if (!hist_list || ft_strncmp(input, hist_list[i]->line, ft_strlen(input)) != 0)
		add_history(input);
	return 0;
}