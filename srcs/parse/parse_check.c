/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:25:42 by sucho             #+#    #+#             */
/*   Updated: 2023/08/13 23:12:32 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int compare_nodename(void *content1, void *content2)
{
	int diff;
	t_node_xy *node_1;
	t_node_xy *node_2;

	node_1 = (t_node_xy *)content1;
	node_2 = (t_node_xy *)content2;
	diff = ft_strncmp(node_1->name, node_2->name, ft_strlen(node_1->name));
	if (diff == 0)
		return (1);
	else
		return (0);
}

int compare_edge(void *content1, void *content2)
{
	int diff_key;
	int diff_val;

	t_edge *edge_1;
	t_edge *edge_2;

	edge_1 = (t_edge *)content1;
	edge_2 = (t_edge *)content2;
	diff_key = ft_strncmp(edge_1->key, edge_2->key, ft_strlen(edge_1->key));
	diff_val = ft_strncmp(edge_1->val, edge_2->val, ft_strlen(edge_1->val));
	if (diff_key == 0 && diff_val == 0)
		return (1);
	else
		return (0);

}

int check_duplicate_nodes(t_list *nodes_head, int (*f)(void*, void*))
{
	t_list *tmp;

	tmp = nodes_head;
	while(tmp != NULL)
	{
		t_list *other = tmp->next;
		// there'll be always 'number of nodes + 1' linked list nodes.
		if (tmp->content == NULL)
			break;
		while (other != NULL)
		{
			// there'll be always 'number of nodes + 1' linked list nodes.
			if (other->content == NULL)
				break;
			if (f(tmp->content, other->content))
				return (0);
			other = other->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

bool	parse_node_xy_check(char *line)
{
	char **node_tmp;
	int split_count;
	int i;
	bool ret;

	ret = true;
	node_tmp = ft_split(line, ' ');
	split_count = 0;
	while (node_tmp[split_count] != NULL)
		split_count++;
	if (split_count != 3)
	{
		free_2d(node_tmp);
		return false;
	}
	i = 0;
	// needs to use atoi
	while (node_tmp[1][i] != 0)
	{
		if (!ft_isdigit(node_tmp[1][i]))
		{
			printf("a - no digit:%c\n", node_tmp[1][i]);
			ret = false;
		}
		i++;
	}
	i = 0;
	while (node_tmp[2][i] != 0)
	{
		if (!ft_isdigit(node_tmp[2][i]))
		{
			printf("b - no digit:[%c]\n", node_tmp[2][i]);
			ret = false;
		}
		i++;
	}
	free_2d(node_tmp);
	return ret;
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
