/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:44:25 by sucho             #+#    #+#             */
/*   Updated: 2023/08/09 17:25:56 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int	edgeline_to_struct(char *line, t_list **node)
{
	t_edge	*tmp;
	char **split_tmp;

	if (line[0] == '#' && line[1] != '#')
		return PARSE_COMMENT;
	else if (check_split_count(line, '-') != 2)
		return false;
	split_tmp = ft_split(line, '-');
	// check when given node names are same
	if (split_tmp[0] == split_tmp[1])
		return false;
	tmp = (t_edge *)malloc(sizeof(t_edge));
	tmp->key = ft_strdup(split_tmp[0]);
	tmp->val = ft_strdup(split_tmp[1]);
	(*node)->content = tmp;
	free_2d(split_tmp);
	split_tmp = NULL;
	return PARSE_EDGE;
}

void	parse_check_edgeline(t_list **line_head, t_parse **parse)
{
	t_list	*tmp;
	int parse_status;

	tmp = (*parse)->edge_info_head;
	while ((*line_head) != NULL)
	{
		parse_status = edgeline_to_struct((*line_head)->content, &tmp);
		if (!parse_status)
		{
			ft_putstr_fd("Error in line ", STDOUT_FILENO);
			// ft_putnbr_fd(line_count, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(1);
		}
		else if (parse_status == PARSE_EDGE && tmp->content != NULL)
		{
			tmp->next = ft_lstnew(NULL);
			tmp = tmp->next;
		}
		(*line_head) = (*line_head)->next;
	}
}

int	nodeline_to_struct(char *line, int parse_status, t_list **node)
{
	t_node_xy *tmp;

	char **split_tmp;

	(void) parse_status;
	if (!parse_node_xy_check(line))
		return 0;
	tmp = (t_node_xy *)malloc(sizeof(t_node_xy));
	split_tmp = ft_split(line, ' ');
	tmp->name = ft_strdup(split_tmp[0]);
	tmp->x = ft_strdup(split_tmp[1]);
	tmp->y = ft_strdup(split_tmp[2]);
	tmp->node_type = parse_status;
	(*node)->content = tmp;
	free_2d(split_tmp);

	// printf("name:[%s] x:[%s] y:[%s]\n", tmp->name, tmp->x, tmp->y);
	return 1;
}

int	check_nodeline_status(char *line, int parse_status, t_list **node)
{
	if(check_split_count(line, '-') == 2)
		return PARSE_EDGE;
	// needs to handle when already start and end were read
	if (ft_strncmp(line, "##start", 7) == 0)
		return PARSE_XY_START;
	else if (ft_strncmp(line, "##end", 5) == 0)
		return PARSE_XY_END;
	else if (line[0] == '#' && line[1] != '#')
		return PARSE_COMMENT;

	else
	{
		if (check_split_count(line, ' ') != 3)
			return false;
		if (!nodeline_to_struct(line, parse_status, node))
			return false;
		parse_status = PARSE_XY;
	}
	return parse_status;
}

// line number keep? or no?
void	parse_check_nodeline(t_list **line_head, t_parse **parse)
{
	t_list	*tmp;
	int parse_status;
	// int	line_count;

	tmp = (*parse)->nodes_head;
	parse_status = 0;
	// line_count = 1;
	while ((*line_head) != NULL)
	{
		parse_status = check_nodeline_status((*line_head)->content, parse_status, &tmp);
		if (parse_status == PARSE_EDGE)
			break;
		else if (parse_status == PARSE_COMMENT)
			parse_status = PARSE_XY;
		else if (!parse_status)
		{
			printf("%s",(char *)(*line_head)->content);
			ft_putstr_fd("Error in line ?????????????", STDOUT_FILENO);
			// ft_putnbr_fd(line_count, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(1);
		}
		else if (parse_status == PARSE_XY && tmp->content != NULL)
		{
			tmp->next = ft_lstnew(NULL);
			tmp = tmp->next;
		}
		(*line_head) = (*line_head)->next;
		// line_count++;
	}
}

void	parse_check_antnum(t_list **line_head, t_parse **parse)
{
	if (!(0 < ft_atoi((*line_head)->content) && \
			ft_atoi((*line_head)->content) <= INT_MAX))
	{
		ft_putstr_fd("Error in first line: ant number is wrong \n", STDOUT_FILENO);
		exit(1);
	}
	(*parse)->ant_num = ft_atoi((*line_head)->content);
	(*line_head) = (*line_head)->next;
}
