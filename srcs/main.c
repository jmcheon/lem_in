/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/07 18:32:23 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


bool	parse_check_line(char *line, int line_count)
{
	char **node_tmp;
	int	split_count;

	if (line_count == 1 && !(ft_strlen(line) == 2 && ft_isdigit(line[0])))
	{
		// ft_putnbr_fd(ft_strlen(line), STDOUT_FILENO);
		// ft_putnbr_fd(line_count, STDOUT_FILENO);
		// ft_putstr_fd(line, STDOUT_FILENO);
		return false;
	}
	else if (line_count > 1)
	{
		node_tmp = ft_split(line, ' ');
		split_count = 0;
		while (node_tmp[split_count] != NULL)
		{
			// printf("%s ", node_tmp[split_count]);
			split_count++;
		}
		// printf("%d\n", split_count);
		if (split_count != 3)
			return false;
		int i = 0;
		// needs to use atoi
		while (node_tmp[1][i] != 0)
		{
			if (!ft_isdigit(node_tmp[1][i]))
			{
				printf("no digit:%c\n", node_tmp[1][i]);
				return false;
			}
			i++;
		}
		i = 0;
		while (node_tmp[2][i] != 0)
		{
			if (!ft_isdigit(node_tmp[2][i]))
			{
				printf("no digit:%c\n", node_tmp[2][i]);
				return false;
			}
			i++;
		}
	}
	// node and xy coordinates
	// 	split 3
	// verticies
	// 	split with '-'

	// ft_putstr_fd(line, STDOUT_FILENO);
	return true;
}

void	parse_readlines(t_list *lines)
{
	char *tmp_read;
	t_list *tmp;

	tmp_read = get_next_line(STDIN_FILENO);
	lines->content = tmp_read;
	tmp_read = get_next_line(STDIN_FILENO);
	while (ft_strlen(tmp_read) > 0)
	{
		if (ft_strncmp(tmp_read, "\n", 1) == 0)
			break;
		tmp = ft_lstnew(tmp_read);
		ft_lstadd_back(&lines, tmp);
		// printf("%s\n", tmp_read);
		tmp_read = get_next_line(STDIN_FILENO);
	}
}

int main(void)
{

	t_list	*lines;
	int	line_count;

	lines = ft_lstnew(NULL);
	parse_readlines(lines);

	line_count = 1;
	while (lines != NULL)
	{
		if (!parse_check_line(lines->content, line_count))
		{
			ft_putstr_fd("Error in line ", STDOUT_FILENO);
			ft_putnbr_fd(line_count, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(1);
		}
		lines = lines->next;
		line_count++;
	}

	ft_putstr_fd("lem-in\n", STDOUT_FILENO);

	return (0);
}
