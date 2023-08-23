/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 23:09:41 by sucho             #+#    #+#             */
/*   Updated: 2023/08/13 23:10:18 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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
		if (tmp->content != NULL)
		free(tmp->content);
		free(tmp);
	}
}

void free_node_xy(void *node)
{
    t_node_xy *node_xy = (t_node_xy *)node;
	if(node_xy == NULL)
		return ;
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
	if(edge == NULL)
		return ;
	if (edge->key != NULL)
    	free(edge->key);
	if (edge->val != NULL)
 	   free(edge->val);
    edge->key = NULL;
    edge->val = NULL;
	free(edge);
}

void free_ongoing_parse(t_list *lines_head, t_parse *parse)
{
	free_list(lines_head);
	ft_lstclear(&parse->nodes_head, free_node_xy);
	ft_lstclear(&parse->edge_info_head, free_edge);
	free(parse);
	exit(1);
}
