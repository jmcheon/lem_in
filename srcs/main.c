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

	
	if (ft_lstsize(route->oneshot_paths->paths) > 0)
		route->oneshot_paths->loop_len = ants_check_loop_len(route, route->oneshot_paths) - 1;

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

	parse = parsing();
	init_route(&route, parse);


	if (perform_oneshot(&route) == -1)
	{
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
		ft_putstr_fd("error", STDOUT_FILENO);
		exit(1);
	}

	if (route.req != -1 && route.req < route.oneshot_paths->loop_len)
	{
		multishot_add_vertices(&route);
		multishot_edmonds_karp(&route);

		if (route.oneshot_paths->loop_len < route.multishot_paths->loop_len)
		{
			t_path_len **elements = ants_distribute(route, route.oneshot_paths);
    		ants_print_frames(route, route.oneshot_paths, elements);
			for(int i = 0; i < route.oneshot_paths->num_paths; i++)
				free(elements[i]);
			free(elements);
		}
		else
		{
			t_path_len **elements = ants_distribute(route, route.multishot_paths);
    		ants_print_frames(route, route.multishot_paths, elements);
			for(int i = 0; i < route.multishot_paths->num_paths; i++)
				free(elements[i]);
			free(elements);
		}
		free_edges_lists(&route);
		free_vertices_edge_inout_lists(&route);
		free_vertices_inout_lists(&route);
	}
	else
	{
		t_path_len **elements = ants_distribute(route, route.oneshot_paths);
    	ants_print_frames(route, route.oneshot_paths, elements);
		for(int i = 0; i < route.oneshot_paths->num_paths; i++)
			free(elements[i]);
		free(elements);
	}
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
