/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wcard4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:56:51 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/05 15:15:26 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	verify_first(char *first, char *dir)
{
	if (!verify(first, dir))
		return (0);
	if (strncmp(dir, "..", 3) == 0)
		return (strncmp(first, "..", 3) == 0);
	if (strncmp(dir, ".", 2) == 0)
		return (strncmp(first, ".", 2) == 0);
	return (verify(first, dir));
}

char	**get_ls_verif(char *first, char **envp)
{
	if (first[0] == '.')
		return (get_ls("-a", envp));
	return (get_ls(NULL, envp));
}