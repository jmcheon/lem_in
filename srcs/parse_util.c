/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:52:20 by sucho             #+#    #+#             */
/*   Updated: 2023/08/08 18:24:03 by sucho            ###   ########.fr       */
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
		i++;
	return i;
}

// for debugging
void parse_result_print(t_parse *parse)
{
	t_list *tmp;
	tmp = parse->nodes_head;

	while (tmp != 0)
	{
		if (tmp->content == NULL)
			break;
		t_node_xy *node_tmp = tmp->content;

		printf("name:[%s] x:[%s], y:[%s], type:[%d]\n", node_tmp->name, node_tmp->x, node_tmp->y, node_tmp->node_type);
		tmp = tmp->next;
	}

	tmp = parse->edge_info_head;
	while (tmp != 0)
	{
		if (tmp->content == NULL)
			break;
		t_edge *node_tmp = tmp->content;

		printf("key:[%s], val:[%s]\n", node_tmp->key, node_tmp->val);
		tmp = tmp->next;
	}
}
