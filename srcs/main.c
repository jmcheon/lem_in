/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/07 20:27:47 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int	check_split_count(char *line, char delim)
{
	char **tmp;
	int i;

	i = 0;
	tmp = ft_split(line, delim);
	while (tmp[i] != NULL)
	{
		i++;
	}
	return i;
}
bool	parse_edge_check(char *line)
{
	char **node_tmp;
	int split_count;

	split_count = 0;
	node_tmp = ft_split(line, '-');
	while (node_tmp[split_count] != NULL)
	{
		split_count++;
	}
	if (split_count != 2)
		return false;
	return true;
}

bool	parse_node_xy(char *line)
{
	char **node_tmp;
	int split_count;

	node_tmp = ft_split(line, ' ');
	split_count = 0;
	while (node_tmp[split_count] != NULL)
	{
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
			printf("ano digit:%c\n", node_tmp[1][i]);
			return false;
		}
		i++;
	}
	i = 0;
	while (node_tmp[2][i] != 0)
	{
		if (!ft_isdigit(node_tmp[2][i]))
		{
			printf("bno digit:[%c]\n", node_tmp[2][i]);
			return false;
		}
		i++;
	}
	return true;
}

int	parse_check_line(char *line, int line_count, int parse_status)
{
	if (line_count == 1)
	{
		if (!(ft_strlen(line) == 1 && ft_isdigit(line[0])))
			return false;
		else
			parse_status =  PARSE_XY;
	}
	if (line_count > 1)
	{
		printf("parse_status:[%d]\t[%s]\n",parse_status, line);
		if (parse_status == PARSE_XY || parse_status == PARSE_XY_START || parse_status == PARSE_XY_END)
		{
			if(check_split_count(line, '-') == 2)
				return PARSE_EDGE;

			if (ft_strncmp(line, "##start", 7) == 0)
				parse_status = PARSE_XY_START;
			else if (ft_strncmp(line, "##end", 5) == 0)
			{
				parse_status = PARSE_XY_END;
			}
			else
				parse_status = PARSE_XY;

		}
		else if (parse_status == PARSE_EDGE)
		{
			if (check_split_count(line, '-') != 2)
				return false;
		}
	}
	return parse_status;
}

void	parse_readlines(t_list *lines)
{
	char *tmp_read;
	t_list *tmp;

	tmp_read = get_next_line(STDIN_FILENO);
	lines->content = ft_strtrim(tmp_read, "\n");
	tmp_read = get_next_line(STDIN_FILENO);
	while (ft_strlen(tmp_read) > 0)
	{
		tmp = ft_lstnew(ft_strtrim(tmp_read, "\n"));
		ft_lstadd_back(&lines, tmp);
		tmp_read = get_next_line(STDIN_FILENO);
		if (!tmp_read)
			break;
	}
}

int main(void)
{

	t_list	*lines;
	int	line_count;
	int parse_status;

	lines = ft_lstnew(NULL);
	parse_readlines(lines);

	line_count = 1;
	parse_status = 0;
	(void) line_count;
	(void)parse_status;
	while (lines != NULL)
	{
		parse_status = parse_check_line(lines->content, line_count, parse_status);
		printf("[%s]\n", (char *)lines->content);
		if (!parse_status)
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
