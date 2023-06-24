/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:46:33 by johmatos          #+#    #+#             */
/*   Updated: 2023/06/24 15:00:42 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	open_heredoc(t_node *node, int *fds, int *status)
{
	int		aux;

	aux = 0;
	while (node != NULL && *status != 2)
	{
		if (node->token == T_PIPE)
			aux++;
		if (node->token == T_HERE_DOC)
		{
			if (fds[aux])
				close(fds[aux]);
			fds[aux] = here_doc(status, node->next->str);
		}
		node = node->next;
	}
}

int	*getter_heredoc_fd(void)
{
	static int	heredoc_fds[MAX_FD] = {0};

	return (heredoc_fds);
}

int	init_heredoc(t_node *node)
{
	int		*heredoc_fd;
	int		status;

	heredoc_fd = getter_heredoc_fd();
	status = 0;
	ft_bzero(heredoc_fd, MAX_FD);
	open_heredoc(node, heredoc_fd, &status);
	return (status);
}
