/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/09 20:38:11 by sucho            ###   ########.fr       */
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

int main(void)
{

	t_parse *parse;

	parse = parsing();

	parse_result_print(parse);
	// parse_to_graph(parse);
	ft_putstr_fd("lem-in\n", STDOUT_FILENO);

	t_list *tmp;

	tmp = parse->nodes_head;
	int i  = 0;
	while (tmp != NULL)
	{
		if (tmp->content == NULL)
			break;
		free_node_xy(tmp->content);
		tmp = tmp->next;
		i++;
	}

	while(parse->nodes_head != NULL)
	{
		tmp = parse->nodes_head;
		parse->nodes_head = parse->nodes_head->next;
		free(tmp);
	}

	tmp = parse->edge_info_head;
	i  = 0;
	while (tmp != NULL)
	{
		if (tmp->content == NULL)
			break;
		free_edge(tmp->content);
		tmp = tmp->next;
		i++;
	}
	while(parse->edge_info_head != NULL)
	{
		tmp = parse->edge_info_head;
		parse->edge_info_head = parse->edge_info_head->next;
		free(tmp);
	}
	ft_lstclear(&parse->nodes_head, NULL);
	ft_lstclear(&parse->edge_info_head, NULL);
	free(parse);
	printf("%d\n", i);


	// free(parse);

	return (0);
}

