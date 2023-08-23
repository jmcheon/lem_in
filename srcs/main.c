#include "../includes/queue.h"
#include "../includes/lem-in.h"

// int	main2(void)
// {
// 	t_parse	*parse;
// 	// t_paths	paths;
// 	t_route	route;

// 	int **capacity;
// 	int	**temp;
// 	int	*parent;

// 	parse = parsing();
// 	// printf("parse result:\n");
// 	// parse_result_print(parse);

// 	/*
// 	**	create node map
// 	*/
// 	init_route(&route, parse);
// 	// init_paths(&paths);

// 	dijkstra(&route);
// /*
// 	modified_dijkstra1(&route);
//     disjoint_path(&route, weights);
// 	printf("disjoin paths:\n");
// 	oneshot_print_paths_list(&route);

// 	free_paths(route.paths->paths);
// 	init_route(&route, parse);
// 	*/
// 	//init_paths(route.paths);

// 	capacity = (int **)malloc(sizeof(int*) * (route.num_vertices + 1));
// 	int i = 0;
// 	while (i < route.num_vertices)
// 	{
// 		capacity[i] = (int *)malloc(sizeof(int) * (route.num_vertices + 1));
// 		for (int j = 0; j <= route.num_vertices; j++)
// 			capacity[i][j] = '\0';
// 		// capacity[i][route.num_vertices] = '\0';
// 		i++;
// 	}
// 	capacity[i] = NULL;


// 	// printf("number of vertices: %d\n", route.num_vertices);
// 	// printf("start: (%d)\n", route.start);
// 	// printf("end: (%d)\n", route.end);
// 	fill_capacity(route.graph, capacity);
// 	//printf("\ncapacity");
// 	//print_2d_array(capacity, route.num_vertices);

// 	// /*
// 	// **	edmonds-karp
// 	// */
// 	// parent = (int *)malloc(sizeof(int) * (route.num_vertices));
// 	init_int_array(&parent, route.num_vertices, -1);
// 	oneshot_edmonds_karp(&route, route.oneshot_paths, parent, capacity);
// 	/*
// 	i = 0;
// 	while (i < (route.num_vertices))
// 	{
// 		printf("index: %d, str:[%s]\n", i, route.node_map[i]);
// 		i++;
// 	}
// 	*/
// 	/*
// 	printf("\naf ek capacity");
// 	print_2d_array(capacity, route.num_vertices);
// 	printf("disjoin paths:\n");
// 	oneshot_print_paths_list(&route);
// 	*/

// 	// /*
// 	// **	create new temp capacity based on the updated capacity
// 	// */
// 	temp = (int **)malloc(sizeof(int*) * (route.num_vertices + 1));
// 	i = 0;
// 	while (i < route.num_vertices)
// 	{
// 		temp[i] = (int *)malloc(sizeof(int) * (route.num_vertices + 1));
// 		temp[i][route.num_vertices] = '\0';
// 		i++;
// 	}
// 	temp[i] = NULL;

// 	fill_capacity(route.graph, temp);
// 	for (int u = 0; u < route.num_vertices; ++u)
// 	{
// 		for (int v = 0; v < route.num_vertices; ++v)
// 		{
// 			if (capacity[u][v] == 1)
// 				temp[u][v] = 0;
// 		}
// 	}
// 	/*
// 	printf("\ntemp");
// 	print_2d_array(temp, route.num_vertices);
// 	*/

// 	// /*
// 	// ** run edmonds-karp with new temp capacity
// 	// */
// 	/*
// 	free_paths(route.paths->paths);
// 	init_paths(route.paths);
// 	free(parent);
// 	init_int_array(&parent, route.num_vertices, -1);
// 	edmonds_karp_with_weights(&route, route.paths, parent, temp);
// 	*/
// 	//printf("ek disjoin paths:\n");
// 	//oneshot_print_paths_list(&route);
// 	/*
// 	printf("\naf ek temp");
// 	print_2d_array(temp, route.num_vertices);
// 	*/

// 	fill_capacity(route.graph, capacity);
// 	for (int u = 0; u < route.num_vertices; ++u)
// 	{
// 		for (int v = 0; v < route.num_vertices; ++v)
// 		{
// 			if (temp[u][v] == 1)
// 				capacity[u][v] = 0;
// 		}
// 	}
// 	/*
// 	free_paths(route.paths->paths);
// 	init_paths(route.paths);
// 	free(parent);
// 	init_int_array(&parent, route.num_vertices, -1);
// 	oneshot_edmonds_karp(&route, route.paths, parent, capacity);
// 	*/
// 	//optimize(&route);

// 	//t_path_len **elements = ants_distribute(route);
//     //ants_print_frames(route, elements);
// 	t_path_len **elements = ants_distribute(route);
// 	// for(int i = 0; elements[i] != NULL; i++)
// 	// 	printf("value:%d\tindex:%d\tnum_ants%d\n",elements[i]->value, elements[i]->index, elements[i]->num_ants);


//     ants_print_frames(route, elements);

// 	int total_length = 0;
// 	for(int i = 0; i < route.oneshot_paths->num_paths; i++)
// 	{
// 	 	printf("elements - value: %d\t index:%d\tnum_ants:%d\n",
// 	 		elements[i]->value, elements[i]->index, elements[i]->num_ants);
// 		total_length += elements[i]->value;
// 	}
// 	printf("total_length:%d\n", total_length);


// 	for (int u = 0; u < route.num_vertices; ++u)
// 		free(temp[u]);
// 	free(temp);

// 	for(int i = 0; i < route.oneshot_paths->num_paths; i++)
// 		free(elements[i]);
// 	free(elements);

// 	// // free(route.paths);
// 	ft_lstclear(&parse->nodes_head, free_node_xy);
// 	ft_lstclear(&parse->edge_info_head, free_edge);
// 	// free_graph
// 	free_graph(route.graph);
// 	free(route.graph);

// 	//free paths
// 	free_paths(route.oneshot_paths->paths);
// 	//free_paths_list(route.paths);
// 	free(route.oneshot_paths);
// 	free(route.distances);



// 	free(route.node_map);
// 	free(parse);
// 	free(parent);

// 	i = 0;
// 	while (i < route.num_vertices)
// 	{
// 		free(capacity[i]);
// 		i++;
// 	}
// 	free(capacity);

// 	// free(route.node_map);
//     // print_frames(route, elements);

// 	return (0);
// }

int	perform_oneshot(t_route *route)
{
	int **capacity;
	int	**temp;
	int	*parent;

	dijkstra(route);

	capacity = (int **)malloc(sizeof(int*) * (route->num_vertices + 1));
	int i = 0;
	while (i < route->num_vertices)
	{
		capacity[i] = (int *)malloc(sizeof(int) * (route->num_vertices + 1));
		for (int j = 0; j <= route->num_vertices; j++)
			capacity[i][j] = '\0';
		// capacity[i][route->num_vertices] = '\0';
		i++;
	}
	capacity[i] = NULL;


	fill_capacity(route->graph, capacity);
	init_int_array(&parent, route->num_vertices, -1);
	oneshot_edmonds_karp(route, parent, capacity, oneshot_bfs);
	temp = (int **)malloc(sizeof(int*) * (route->num_vertices + 1));
	i = 0;
	while (i < route->num_vertices)
	{
		temp[i] = (int *)malloc(sizeof(int) * (route->num_vertices + 1));
		temp[i][route->num_vertices] = '\0';
		i++;
	}
	temp[i] = NULL;

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
	printf("v_in_list size:%d, v_out_list size:%d\n", ft_lstsize(route.graph->v_in_list), ft_lstsize(route.graph->v_out_list));
	printf("edge_list size:%d, rev_edge_list size:%d\n", ft_lstsize(route.graph->edge_list), ft_lstsize(route.graph->rev_edge_list));

	printf("oneshot\n\tnum_paths:%d\tdist_begin:%d\tloop_len:%d\n", route.oneshot_paths->num_paths, route.oneshot_paths->dist_begin, route.oneshot_paths->loop_len);
	printf("multishot\n\tnum_paths:%d\tdist_begin:%d\tloop_len:%d\n", route.multishot_paths->num_paths, route.multishot_paths->dist_begin, route.multishot_paths->loop_len);

	// t_path_len **elements = ants_distribute(route);
	if (route.oneshot_paths->loop_len < route.multishot_paths->loop_len)
	{
		t_path_len **elements = ants_distribute(route, route.oneshot_paths);
    	ants_print_frames(route, route.oneshot_paths, elements);
		printf("oneshot win: %d(one) < %d(multi)\n", route.oneshot_paths->loop_len, route.multishot_paths->loop_len);
	}
	else
	{
		t_path_len **elements = ants_distribute(route, route.multishot_paths);
    	ants_print_frames(route, route.multishot_paths, elements);
		printf("multishot win: %d(multi) < %d(one)\n", route.multishot_paths->loop_len, route.oneshot_paths->loop_len);
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
	free_vertices_inout_lists(&route);
	//free_vertices_edge_inout_lists(&route);


	// for(int i = 0; i < route.oneshot_paths->num_paths; i++)
	// 	free(elements[i]);
	// free(elements);

	ft_lstclear(&parse->nodes_head, free_node_xy);
	ft_lstclear(&parse->edge_info_head, free_edge);
	// free_graph
	free_graph(route.graph);
	free(route.graph);

	//free paths
	free_paths(route.oneshot_paths->paths);
	free(route.oneshot_paths);
	free(route.distances);

	free(route.node_map);
	free(parse);

	return 0;
}
