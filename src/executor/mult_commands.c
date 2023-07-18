/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:14:51 by johmatos          #+#    #+#             */
/*   Updated: 2023/07/18 20:51:09 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

static int	dup2_and_close(int fd, int clone)
{
	int	a;

	a = dup2(fd, clone);
	close(fd);
	return (a);
}

static void	main_routine(int *bkp_fd, int *count, int *pipes_fds)
{
	(*count)++;
	*bkp_fd = dup(pipes_fds[0]);
	close_pipe_fds(pipes_fds);
}

void	child_routine(t_node *cmds, int count)
{
	t_io			*cmd;
	t_fn_built_exec	**exec;
	t_tokens		builtin_idx;

	cmd = command_hook(count);
	exec = get_built_func_arr();
	builtin_idx = is_builtin(cmds->str);
	if (cmd->input > 2)
		cmd->input = dup2_and_close(cmd->input, STDIN_FILENO);
	if (cmd->output > 2)
		cmd->output = dup2_and_close(cmd->output, STDOUT_FILENO);
	if (builtin_idx != T_INVALID)
		exec[builtin_idx](cmds);
	else
		exec_command(cmds);
	free_cmds_arr(getter_data()->cmds->arr_cmds);
	free_cmds(getter_data()->cmds);
	free_all(getter_data());
	exit(0);
}

void	mult_command(t_node **cmds)
{
	int		fds[2];
	int		bkp_fd;
	int		cmd_count;
	pid_t	pid;
	t_io	*stdio;

	stdio = getter_stdio();
	cmd_count = 0;
	bkp_fd = STDIN_FILENO;
	while (cmds[cmd_count])
	{
		pipe(fds);
		pid = fork();
		if (pid == CHILD_PROCESS)
		{
			if (bkp_fd != 0)
				stdio->input = dup2_and_close(bkp_fd, STDIN_FILENO);
			close(fds[0]);
			if (cmd_count != getter_data()->cmds->idx)
				stdio->output = dup2_and_close(fds[1], STDOUT_FILENO);
			child_routine(cmds[cmd_count], cmd_count);
		}
		main_routine(&bkp_fd, &cmd_count, fds);
	}
	wait_all_child(bkp_fd);
}
