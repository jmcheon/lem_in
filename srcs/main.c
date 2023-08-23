#include "../includes/queue.h"
#include "../includes/lem-in.h"

int	perform_oneshot(t_route *route)
{
	int **capacity;
	int	**temp;
	int	*parent;

	dijkstra(route);

	capacity = (int **)malloc(sizeof(int*) * (route->num_vertices + 1));
	temp = (int **)malloc(sizeof(int*) * (route->num_vertices + 1));
	int i = 0;
	while (i < route->num_vertices)
	{
		capacity[i] = (int *)malloc(sizeof(int) * (route->num_vertices + 1));
		for (int j = 0; j <= route->num_vertices; j++)
			capacity[i][j] = '\0';
		temp[i] = (int *)malloc(sizeof(int) * (route->num_vertices + 1));
		temp[i][route->num_vertices] = '\0';
		i++;
	}
	capacity[i] = NULL;
	temp[i] = NULL;


	fill_capacity(route->graph, capacity);
	init_int_array(&parent, route->num_vertices, -1);
	oneshot_edmonds_karp(route, parent, capacity, oneshot_bfs);

	fill_capacity(route->graph, temp);
	for (int u = 0; u < route->num_vertices; ++u)
	{
		for (int v = 0; v < route->num_vertices; ++v)
		{
			if (capacity[u][v] == 1)
				temp[u][v] = 0;
		}
	}
	free_paths(route->oneshot_paths->paths);
	init_paths(route->oneshot_paths);
	free(parent);
	init_int_array(&parent, route->num_vertices, -1);
	oneshot_edmonds_karp(route, parent, temp, oneshot_bfs_with_weights);
	fill_capacity(route->graph, capacity);
	route->oneshot_paths->loop_len = ants_check_loop_len(route, route->oneshot_paths) - 2;

 	for (int u = 0; u < route->num_vertices; ++u)
	{
 		free(temp[u]);
 		free(capacity[u]);
	}
 	free(temp);
 	free(capacity);
	free(parent);

	return (route->oneshot_paths->loop_len);
}

int main(void)
{
	t_parse	*parse;
	t_route	route;
	t_list	*paths;



	parse = parsing();
	init_route(&route, parse);


	printf("testing:%d\n", perform_oneshot(&route));

	if (route.flags.debug)
	{
		int i = 0;

		while (i < (route.num_vertices))
		{
			printf("index: %d, str:[%s]\n", i, route.node_map[i]);
			i++;
		}
	}

	multishot_add_vertices(&route);
	//multishot_print_edge_forward_travel(&route);
	//multishot_print_vertex_lists(&route);
	(void)paths;
	// paths = multishot_edmonds_karp(&route);
	multishot_edmonds_karp(&route);
	//printf("%d\n", ((t_vertex_list*)ft_lstlast(route.multishot_paths->paths)->content)->vertex);
	//multishot_print_all_paths(&route, paths, 0);
	//printf("\t\tmax flow path:%d\n", ft_lstsize(paths));
	/*
	printf("v_in_list size:%d, v_out_list size:%d\n", ft_lstsize(route.graph->v_in_list), ft_lstsize(route.graph->v_out_list));
	printf("edge_list size:%d, rev_edge_list size:%d\n", ft_lstsize(route.graph->edge_list), ft_lstsize(route.graph->rev_edge_list));
	*/

	printf("oneshot\n\tnum_paths:%d\tdist_begin:%d\tloop_len:%d\n", route.oneshot_paths->num_paths, route.oneshot_paths->dist_begin, route.oneshot_paths->loop_len);
	printf("multishot\n\tnum_paths:%d\tdist_begin:%d\tloop_len:%d\n", route.multishot_paths->num_paths, route.multishot_paths->dist_begin, route.multishot_paths->loop_len);

	// t_path_len **elements = ants_distribute(route);
	if (route.oneshot_paths->loop_len < route.multishot_paths->loop_len)
	{
		t_path_len **elements = ants_distribute(route, route.oneshot_paths);
    	//ants_print_frames(route, route.oneshot_paths, elements);
		printf("oneshot win: %d(one) < %d(multi)\n", route.oneshot_paths->loop_len, route.multishot_paths->loop_len);
		for(int i = 0; i < route.oneshot_paths->num_paths; i++)
			free(elements[i]);
		free(elements);
	}
	else
	{
		t_path_len **elements = ants_distribute(route, route.multishot_paths);
    	//ants_print_frames(route, route.multishot_paths, elements);
		printf("multishot win: %d(multi) < %d(one)\n", route.multishot_paths->loop_len, route.oneshot_paths->loop_len);
		for(int i = 0; i < route.multishot_paths->num_paths; i++)
			free(elements[i]);
		free(elements);
	}
	// for(int i = 0; elements[i] != NULL; i++)
	// 	printf("value:%d\tindex:%d\tnum_ants%d\n",elements[i]->value, elements[i]->index, elements[i]->num_ants);


    // ants_print_frames(route, elements);

	// int total_length = 0;
	// for(int i = 0; i < route.oneshot_paths->num_paths; i++)
	// {
	//  	printf("elements - value: %d\t index:%d\tnum_ants:%d\n",
	//  		elements[i]->value, elements[i]->index, elements[i]->num_ants);
	// 	total_length += elements[i]->value;
	// }
	// printf("total_length:%d\n", total_length);


	//ft_lstclear(&route.graph->v_in_list, free);
	//free_vertices(&route);
	free_edges_lists(&route);
	free_vertices_edge_inout_lists(&route);
	free_vertices_inout_lists(&route);



	ft_lstclear(&parse->nodes_head, free_node_xy);
	ft_lstclear(&parse->edge_info_head, free_edge);
	// free_graph
	free_graph(route.graph);
	free(route.graph);

	//free paths
	free_paths(route.oneshot_paths->paths);
	free(route.oneshot_paths);
	free_paths(route.multishot_paths->paths);
	free(route.multishot_paths);
	free(route.distances);

	free(route.node_map);
	free(parse);

	return 0;
}
