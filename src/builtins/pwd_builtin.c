/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:01:51 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/06/25 08:58:58 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_node *current)
{
	char	cwd[STR_LIMIT];

	(void)current;
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
