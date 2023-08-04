/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bimatrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:15:30 by johmatos          #+#    #+#             */
/*   Updated: 2023/03/29 22:48:36 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_whitespace(char c)
{
	return (
		c == '\n' 
		|| c == '\t' 
		|| c == '\r' 
		|| c == '\v'
		|| c == ' '
	);
}
