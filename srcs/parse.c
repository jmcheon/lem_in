/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:44:25 by sucho             #+#    #+#             */
/*   Updated: 2023/08/08 13:09:51 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

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

bool	parse_node_xy_check(char *line)
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
			printf("a - no digit:%c\n", node_tmp[1][i]);
			return false;
		}
		i++;
	}
	i = 0;
	while (node_tmp[2][i] != 0)
	{
		if (!ft_isdigit(node_tmp[2][i]))
		{
			printf("b - no digit:[%c]\n", node_tmp[2][i]);
			return false;
		}
		i++;
	}
	return true;
}

int	parse_check_line(char *line, int line_count, int parse_status, t_list **node)
{
	if (line_count == 1)
	{
		// needs atoi
		if (!(ft_strlen(line) == 1 && ft_isdigit(line[0])))
			return false;
		else
			parse_status =  PARSE_XY;
	}
	if (line_count > 1)
	{
		if (parse_status == PARSE_XY || parse_status == PARSE_XY_START || parse_status == PARSE_XY_END)
		{
			if(check_split_count(line, '-') == 2)
				return PARSE_EDGE;
			// needs to handle when already start and end were read
			else if (ft_strncmp(line, "##start", 7) == 0)
				return PARSE_XY_START;
			else if (ft_strncmp(line, "##end", 5) == 0)
				return PARSE_XY_END;
			else
				parse_status = PARSE_XY;

			if (parse_status == PARSE_XY || parse_status == PARSE_XY_START || parse_status == PARSE_XY_END)
			{
				if (check_split_count(line, ' ') != 3)
					return false;
				if (!parse_read_node(line, parse_status, node))
					return false;
			}
		}
		if (parse_status == PARSE_EDGE)
		{
			printf("parse_status:[%d]\t[%s]\n", parse_status, line);
			if (check_split_count(line, '-') != 2)
				return false;
		}

	}
	return parse_status;
}

int	parse_check_edge_line(char *line, t_list **node)
{
	t_edge	*tmp;
	char **split_tmp;

	if (check_split_count(line, '-') != 2)
		return false;

	split_tmp = ft_split(line, '-');
	// check when to given node names are same
	if (split_tmp[0] == split_tmp[1])
		return false;
	tmp = (t_edge *)malloc(sizeof(t_edge));
	tmp->key = split_tmp[0];
	tmp->val = split_tmp[1];
	(*node)->content = tmp;
	return true;
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
