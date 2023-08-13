/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:39:43 by sucho             #+#    #+#             */
/*   Updated: 2023/08/13 02:20:11 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

static void init(t_graph *graph)
{
	int v;

	graph->n = 0;
	v = 0;
	while (v < MAX_VERTICES)
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

static void insert_edge(t_graph *g, int u, int v)
{
	if (u >= g->n || v >= g->n)
	{
		printf("vertex index error\n");
		return;
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

t_graph* parse_to_graph(t_parse *parse)
{
	t_graph *g;
	t_edge *tmp;

    int list_size = ft_lstsize(parse->nodes_head);
    char **node_map;

	node_map = init_nodes_mapping(list_size);
	node_map_to_array(parse->nodes_head, node_map);
	// print_graph_mapping(list_size, node_map);

	g = (t_graph*)malloc(sizeof(t_graph));
	init(g);
	g->n = ft_lstsize(parse->nodes_head);

	t_list *list_tmp;
	list_tmp = parse->edge_info_head;
	for(int i = 0; i < ft_lstsize(parse->edge_info_head); i++)
	{
		tmp = list_tmp->content;
		insert_edge(g, node_find_index(node_map, tmp->key), node_find_index(node_map, tmp->val));
		insert_edge(g, node_find_index(node_map, tmp->val), node_find_index(node_map, tmp->key));
		list_tmp = list_tmp->next;
	}
	(void)print_adjlist_list;
	return g;
}
