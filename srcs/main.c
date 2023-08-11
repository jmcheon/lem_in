/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:02:52 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 03:50:00 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../includes/algo.h"

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

void	init_paths(t_graph* paths)
{
	paths->num_paths = 0;
	ft_memset(paths->paths, 0, sizeof(paths->paths));
}

int main(void)
{
	t_parse *parse;
	t_graph	*graph;
	t_route	route;
	t_graph	paths;

	int	capacity[MAX_VERTICES][MAX_VERTICES] = {0};
	int	parent[MAX_VERTICES];
	(void)parent;

	init_paths(&paths);
	parse = parsing();
	parse_result_print(parse);
	printf("=======matrix ver=============\n");
	graph = parse_to_graph_matrix(parse, &route);

	printf("number of vertices: %d\n", route.num_vertices);
	printf("start: (%d)\n", route.start);
	printf("end: (%d)\n", route.end);
	//same as print capacity
	fill_capacity(graph, capacity);
	print_capacity(capacity, route.num_vertices);


	bfs(&route, parent, capacity);
	// edmonds_karp(&route, &paths, parent, capacity);
	// printf("=======graph ver=============\n");
	// parse_to_graph(parse);

	// ft_lstclear(&parse->nodes_head, free_node_xy);
	// // free_linked_list(&parse->nodes_head);
	// ft_lstclear(&parse->edge_info_head, free_edge);
	// // free_linked_list(&parse->edge_info_head);
	// free(parse);




	ft_putstr_fd("lem-in\n", STDOUT_FILENO);
	return (0);
}

