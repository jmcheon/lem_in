/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:25:42 by sucho             #+#    #+#             */
/*   Updated: 2023/08/08 14:28:28 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


int compare_nodename(void *content1, void *content2)
{
	int diff;
	t_node_xy *node_1;
	t_node_xy *node_2;

	node_1 = (t_node_xy *)content1;
	node_2 = (t_node_xy *)content2;
	// printf("node1:[%s] node2:[%s]\n", node_1->name, node_2->name);
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
	(void)f;
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
