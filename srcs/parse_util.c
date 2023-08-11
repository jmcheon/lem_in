/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:52:20 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 16:58:24 by cjung-mo         ###   ########.fr       */
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
	free_2d(tmp);
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

void		free_2d(char **ptr)
{
	int		i;

	i = 0;
	while (*(ptr + i))
		free(*(ptr + i++));
	free(ptr);
}

void	free_list(t_list *head)
{
	t_list* tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}
