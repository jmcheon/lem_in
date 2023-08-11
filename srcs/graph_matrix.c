/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:52:00 by sucho             #+#    #+#             */
/*   Updated: 2023/08/10 22:40:17 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../includes/algo.h"

void	graph_init(t_graph *graph)
{
	int	row;
	int	col;

	row = 0;
	graph->num_paths = 0;
	while (row < MAX_VERTICES)
	{
		col = 0;
		while (col < MAX_VERTICES)
		{
			graph->paths[row][col] = 0;
			col++;
		}
		row++;
	}
}

void	graph_insert_vertex(t_graph *graph, int n)
{
	(void)n;
	if (((graph->num_paths) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "overflow");
		return ;
	}
	graph->num_paths++;
}

void	graph_insert_edge(t_graph *graph, int start, int end)
{
	if (start >= graph->num_paths || end >= graph->num_paths)
	{
		printf("vertex key error");
		return ;
	}
	graph->paths[start][end] = 1;
	graph->paths[end][start] = 1;
}

void	graph_print(t_graph *graph)
{
	int	i;
	int	j;

	i = 0;
	while (i < graph->num_paths)
	{
		j = 0;
		while (j < graph->num_paths)
		{
			printf("%2d", (int) graph->paths[i][j]);
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
    for (int i = 0; i < g->num_paths; i++) {
        printf("node [%s index:(%d)]", node_map[i], i);
        for (int j = 0; j < g->num_paths; j++) {
            if (g->paths[i][j] == 1) {
                printf("->%d", j);
            }
        }
        printf("\n");
    }
}


t_graph	*parse_to_graph_matrix(t_parse *parse, t_route *route)
{
	// t_edge *tmp;
	t_graph	*g;

    // char **node_map;
	route->list_size = ft_lstsize(parse->nodes_head);
	route->node_map = init_nodes_mapping(route->list_size);
	node_map_to_array(parse->nodes_head, route->node_map);
	print_graph_mapping(route->list_size, route->node_map);
	/*
	**	---------------graph------------------------
	*/

	g = (t_graph *)malloc(sizeof(t_graph));
	graph_init(g);
	for (int i = 0; i < 4; i++)
		graph_insert_vertex(g, i);
	graph_insert_edges(g, parse->edge_info_head, route->node_map);
	printf("================\n");
	print_adjlist_matrix(g, route->node_map);
	printf("================\n");
	/*
	**	---------------graph------------------------
	*/
	route->start = 0;
	route->end = route->list_size - 1;
	route->num_vertices = g->num_paths;
	route->graph = g;
	return (g);
}


