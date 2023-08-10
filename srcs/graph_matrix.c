/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:52:00 by sucho             #+#    #+#             */
/*   Updated: 2023/08/10 21:35:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	graph_init(t_graph *graph)
{
	int	row;
	int	col;

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

void	graph_insert_vertex(t_graph *graph, int n)
{
	(void)n;
	if (((graph->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "overflow");
		return ;
	}
	graph->n++;
}

void	graph_insert_edge(t_graph *graph, int start, int end)
{
	if (start >= graph->n || end >= graph->n)
	{
		printf("vertex key error");
		return ;
	}
	graph->matrix[start][end] = 1;
	graph->matrix[end][start] = 1;
}

void	graph_print(t_graph *graph)
{
	int	i;
	int	j;

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

void	graph_insert_edges(t_graph *g, t_list *edge_info_head, char **node_map)
{
	t_list *list_tmp;
	t_edge *tmp;
	list_tmp = edge_info_head;
	for(int i = 0; i < ft_lstsize(edge_info_head); i++)
	{
		tmp = list_tmp->content;
		graph_insert_edge(g, node_find_index(node_map, tmp->key), node_find_index(node_map, tmp->val));
		list_tmp = list_tmp->next;

	}
}

void print_adjlist_matrix(t_graph *g, char **node_map) {
    for (int i = 0; i < g->n; i++) {
        printf("node [%s index:(%d)]", node_map[i], i);
        for (int j = 0; j < g->n; j++) {
            if (g->matrix[i][j] == 1) {
                printf("->%d", j);
            }
        }
        printf("\n");
    }
}


void	parse_to_graph_matrix(t_parse *parse)
{
	// t_edge *tmp;
	t_graph	*g;

    int list_size = ft_lstsize(parse->nodes_head);
    char **node_map;

	node_map = init_nodes_mapping(list_size);
	node_map_to_array(parse->nodes_head, node_map);
	print_graph_mapping(list_size, node_map);

	g = (t_graph *)malloc(sizeof(t_graph));
	graph_init(g);
	for (int i = 0; i < 4; i++)
		graph_insert_vertex(g, i);
	graph_insert_edges(g, parse->edge_info_head, node_map);
	graph_print(g);
	printf("================\n");
	print_adjlist_matrix(g, node_map);
}


