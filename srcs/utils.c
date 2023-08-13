/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:58:03 by sucho             #+#    #+#             */
/*   Updated: 2023/08/13 16:59:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void free_node_xy(void *node)
{
    t_node_xy *node_xy = (t_node_xy *)node;
    free(node_xy->name);
    free(node_xy->x);
    free(node_xy->y);
	node_xy->name = NULL;
	node_xy->x= NULL;
	node_xy->y= NULL;
	free(node_xy);
}

void free_edge(void *node)
{
    t_edge *edge = (t_edge *)node;
    free(edge->key);
    free(edge->val);
    edge->key = NULL;
    edge->val = NULL;
	free(edge);
}

void	free_linked_list(t_list **list_head)
{
	t_list *tmp;
	while((*list_head) != NULL)
	{
		tmp = (*list_head);
		(*list_head) = (*list_head)->next;
		free(tmp);
		tmp = NULL;
	}
}
