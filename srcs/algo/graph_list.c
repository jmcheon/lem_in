/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:39:43 by sucho             #+#    #+#             */
/*   Updated: 2023/08/25 22:32:04 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

int	lstsize(t_graph_node *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->link;
		size++;
	}
	return (size);
}

static void init(t_graph *graph, int num_vertices)
{
	int v;

	graph->n = num_vertices;
	v = 0;
	graph->adj_list = (t_graph_node **)malloc(sizeof(t_graph_node *) * (num_vertices));
	while (v < num_vertices)
	{
		graph->adj_list[v] = NULL;
		v++;
	}

}

static int insert_edge(t_graph *g, int u, int v)
{
	if (u >= g->n || v >= g->n)
	{
		ft_putstr_fd("vertex index error\n", STDOUT_FILENO);
		return 0;
	}

	// create a new edge node
	t_graph_node *new_edge = malloc(sizeof(t_graph_node));
	new_edge->vertex = v;
	new_edge->link = NULL;

	// add new edge node to the end of the adjacency list for vertex u
	if (g->adj_list[u] == NULL)
	{
		g->adj_list[u] = new_edge;
	}
	else
	{
		t_graph_node *curr = g->adj_list[u];
		while (curr->link != NULL)
			curr = curr->link;
		curr->link = new_edge;
	}
	return (1);
}

t_graph* parse_to_graph(t_parse *parse, t_route *route)
{
	t_graph *g;
	t_edge *tmp;
	t_list *edge_head;
	int edges_total_num;
	int edge_one;
	int edge_two;

	g = (t_graph*)malloc(sizeof(t_graph));
	init(g, route->num_vertices);
	edge_head = parse->edge_info_head;
	edges_total_num = ft_lstsize(parse->edge_info_head);
	for(int i = 0; i < edges_total_num; i++)
	{
		tmp = edge_head->content;
		edge_one = node_find_index(route->node_map, tmp->key, route->num_vertices);
		edge_two = node_find_index(route->node_map, tmp->val, route->num_vertices);
		if (edge_one < 0 || edge_two < 0)
		{
			free_graph(g);
			free(g);
			return (NULL);
		}
		if (!insert_edge(g, edge_one, edge_two))
		{
			free_graph(g);
			free(g);
			return (NULL);
		}
		if (!insert_edge(g, edge_two, edge_one))
		{
			free_graph(g);
			free(g);
			return (NULL);
		}
		edge_head = edge_head->next;
	}
	return g;
}
