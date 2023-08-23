/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:39:43 by sucho             #+#    #+#             */
/*   Updated: 2023/08/24 00:13:52 by sucho            ###   ########.fr       */
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
// link in reverse way
// void insert_edge(t_graph *g, int u, int v)
// {
// 	t_graph_node* node;
//     if(u>=g->n||v>=g->n){
//         fprintf(stderr,"vertex index error");
//         return;
//     }

// 	node = (t_graph_node *)malloc(sizeof(t_graph_node));
// 	node->vertex = v;
// 	node->link = g->adj_list[u];
// 	g->adj_list[u] = node;
// }

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

static void print_adjlist_list(t_graph *g)
{
	int i;
	// int j;

	i = 0;
	while (i < g->n)
	{
		t_graph_node *p = g->adj_list[i];
		printf("node [%d]", i);
		while (p != NULL)
		{
			printf("->%d", p->vertex);
			p = p->link;
		}
		printf("\n");
		i++;
	}
}

t_graph* parse_to_graph(t_parse *parse, t_route *route)
{
	t_graph *g;
	t_edge *tmp;
	t_list *edge_head;
	int edges_total_num;
	int edge_one;
	int edge_two;

	// print_graph_mapping(route->num_vertices, route->node_map);
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
	(void)print_adjlist_list;
	//  print_adjlist_list(g);
	return g;
}
