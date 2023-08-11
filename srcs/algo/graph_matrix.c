/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:53:22 by sucho             #+#    #+#             */
/*   Updated: 2023/08/12 00:10:35 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

static void init(t_graph *graph)
{
	int row;
	int col;

	row = 0;
	graph->n = 0;
	while (row < MAX_VERTICES)
	{
		col = 0;
		while (col < MAX_VERTICES)
		{
			graph->matrix[row][col] = 0;
			col++;
		}
		row++;
	}
}

static void insert_edge(t_graph *graph, int start, int end)
{
	if (start >= graph->n || end >= graph->n)
	{
		printf("vertex key error");
		return;
	}
	graph->matrix[start][end] = 1;
	graph->matrix[end][start] = 1;
}

void graph_print(t_graph *graph)
{
	int i;
	int j;

	i = 0;
	while (i < graph->n)
	{
		j = 0;
		while (j < graph->n)
		{
			printf("%2d", graph->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static void print_adjlist_matrix(t_graph *graph) {
    for (int i = 0; i < graph->n; i++) {
        printf("Adjacency list for node %d: ", i);

        for (int j = 0; j < graph->n; j++) {
            if (graph->matrix[i][j] == 1) {
                printf("%d ", j);
            }
        }

        printf("\n");
    }
}


t_graph *parse_to_graph(t_parse *parse)
{
	t_graph *g;
	t_edge *tmp;

	int list_size = ft_lstsize(parse->nodes_head);
	char **node_map;

	node_map = init_nodes_mapping(list_size);
	node_map_to_array(parse->nodes_head, node_map);
	print_graph_mapping(list_size, node_map);

	g = (t_graph *)malloc(sizeof(t_graph));
	init(g);

	g->n = list_size;

	t_list *list_tmp;
	list_tmp = parse->edge_info_head;
	for(int i = 0; i < ft_lstsize(parse->edge_info_head); i++)
	{
		tmp = list_tmp->content;
		insert_edge(g, node_find_index(node_map, tmp->key), node_find_index(node_map, tmp->val));
		list_tmp = list_tmp->next;
	}
	graph_print(g);
	print_adjlist_matrix(g);

	return (g);
}
