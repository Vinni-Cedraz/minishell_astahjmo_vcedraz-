/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recipeWord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astaroth <astaroth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:02:32 by astaroth          #+#    #+#             */
/*   Updated: 2023/05/18 16:10:03 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_word_recipe(t_tokens state)

{
	static int	transictions[3] = {1, 1, -1};

	return (transictions[state]);
}
