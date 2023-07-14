/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:44:31 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/06/25 09:07:24 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	increase_number_of_envs(void);
static int	is_valid_env_name_err(char *env);
static int	check_strlen(char *new_env);
static int	overwrite_env(char *new_env);

void	export_builtin(t_node *current)
{
	t_databus	*data;

	if (!is_valid_syntax(current))
		return ;
	current = current->next;
	if (!current)
		no_arguments_export_builtin(current);
	data = getter_data();
	while (current && current->next)
	{
		current = current->next;
		if (current->token != T_WORD)
			current = current->next;
		if (!is_valid_env_name_err(current->str))
			break ;
		else if (overwrite_env(current->str))
			continue ;
		if (!increase_number_of_envs())
			return ;
		if (!check_strlen(current->str))
			return ;
		ft_strlcpy(data->env[data->number_of_envs - 1], current->str,
			ft_strlen(current->str) + 1);
	}
}

static int	is_valid_env_name_err(char *env)
{
	if (!env || (!ft_isalpha(*env) && *env != '_'))
	{
		ft_putstr_fd("minishell: export:", 1);
		ft_putstr_fd(" not a valid identifier\n", 2);
		getter_data()->exit_status = 1;
		return (0);
	}
	env++;
	while (*env != '\0' && *env != '=')
	{
		if (!ft_isalnum(*env) && *env != '_')
		{
			ft_putstr_fd("minishell: export:", 1);
			ft_putstr_fd(" not a valid identifier\n", 2);
			getter_data()->exit_status = 1;
			return (0);
		}
		env++;
	}
	return (1);
}

static int	increase_number_of_envs(void)
{
	t_databus	*data;

	data = getter_data();
	if ((data->number_of_envs + 1) == ENVS_LIMIT)
	{
		ft_printf("minishell: too many environment variables\n");
		getter_data()->exit_status = 1;
		return (0);
	}
	data->number_of_envs++;
	return (1);
}

static int	check_strlen(char *new_env)
{
	int	len;

	len = ft_strlen(new_env) + 1;
	if (len >= STR_LIMIT)
	{
		ft_putstr_fd("minishell: export:", 2);
		ft_putstr_fd(new_env, 2);
		ft_putstr_fd(": error: variable is too long.\n", 2);
		getter_data()->exit_status = 1;
		return (FALSE);
	}
	return (TRUE);
}

static int	overwrite_env(char *new_env)
{
	int			i;
	t_databus	*data;

	i = 0;
	data = getter_data();
	while (i < data->number_of_envs)
	{
		if (names_are_equal(data->env[i], new_env)
			&& is_being_initialized(new_env))
			return (ft_strlcpy(data->env[i], new_env, ft_strlen(new_env) + 1));
		i++;
	}
	return (FALSE);
}
