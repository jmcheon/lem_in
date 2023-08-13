/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:23:39 by sucho             #+#    #+#             */
/*   Updated: 2023/08/13 23:02:00 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

bool	duplicates_check(t_parse *parse)
{
	bool result;

	result = true;
	if (!check_duplicate_nodes(parse->nodes_head, compare_nodename))
	{
		perror("duplicates node found");
		// ft_putchar_fd('\n', STDOUT_FILENO);
		result = false;
	}

	if (!check_duplicate_nodes(parse->edge_info_head, compare_edge))
	{
		ft_putstr_fd("duplicates edge found", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		result = false;
	}
	return result;
}

void parse_readlines(t_list *lines)
{
	char *tmp_read;
	t_list *tmp;

	tmp_read = get_next_line(STDIN_FILENO);
	lines->content = ft_strtrim(tmp_read, "\n");
	free(tmp_read);
	tmp_read = NULL;
	tmp_read = get_next_line(STDIN_FILENO);
	while (ft_strlen(tmp_read) > 0)
	{
		tmp = ft_lstnew(ft_strtrim(tmp_read, "\n"));
		free(tmp_read);
		ft_lstadd_back(&lines, tmp);
		tmp_read = get_next_line(STDIN_FILENO);
		if (!tmp_read)
			break;
	}
}


int		check_start_and_end(t_list *nodes)
{
	int check;

	check = 0;
	while(nodes != NULL)
	{
		t_node_xy *tmp;
		tmp = (t_node_xy*) nodes->content;
		if (tmp->node_type == PARSE_XY_START || tmp->node_type == PARSE_XY_END)
			check += tmp->node_type;
		nodes = nodes->next;
	}
	if (check != (PARSE_XY_START + PARSE_XY_END))
	{
		printf("error with start and end of nodes\n");
		return (0);
	}
	return (1);
}

t_parse	*parsing()
{
	t_list	*lines;
	t_list	*lines_head;
	t_parse *ret;

	ret = init_parse_struct();
	lines = ft_lstnew(NULL);
	parse_readlines(lines);
	lines_head = lines;
	parse_check_antnum(&lines, &ret);
	if (!parse_check_nodeline(&lines, &ret))
		free_ongoing_parse(lines_head, ret);
	if (!check_start_and_end(ret->nodes_head))
		free_ongoing_parse(lines_head, ret);
	if (!parse_check_edgeline(&lines, &ret))
		free_ongoing_parse(lines_head, ret);
	free_list(lines_head);
	if(!duplicates_check(ret))
		exit(1);
	return ret;
}
