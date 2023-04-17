/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:37:17 by johmatos          #+#    #+#             */
/*   Updated: 2023/04/17 18:51:09 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_execute(int fd[], char *delimiter)
{
	char	*switcher;
	char	*tmp;
	char	*buf;
	int		state;

	signal(SIGINT, SIG_DFL);
	state = 0;
	buf = get_next_line(0);
	state = check_unclosed_quotes(buf, delimiter);
	while (state != 1)
	{
		tmp = get_next_line(0);
		switcher = ft_interpol("%s%s", buf, tmp);
		free(buf);
		free(tmp);
		buf = switcher;
		state = check_unclosed_quotes(buf, delimiter);
	}
	write(fd[1], buf, ft_strlen(buf));
	free(buf);
	exit(1);
}

//TODO: Make the read process dynamic
char	*main_process(int fd[], pid_t pid, char *line)
{
	int		status;
	char	*str;
	char	*buff[1024];

	close(fd[1]);
	waitpid(pid, &status, 0);
	memset(buff, 0, 1024);
	read(fd[0], buff, 1024);
	str = ft_interpol("%s%s", line, buff);
	close(fd[0]);
	return (str);
}

char	*here_doc(char	*line, char *quote)
{
	int		fd[2];
	pid_t	pid;
	char	*str;

	if (pipe(fd) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		free(line);
		child_execute(fd, quote);
	}
	else
		str = main_process(fd, pid, line);
	free(str);
	return (str);
}
