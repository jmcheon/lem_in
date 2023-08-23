#include "../includes/queue.h"
#include "../includes/lem-in.h"

void	reset_parent_array(t_route *route, int **parent)
{
	for (int i = 0; i < route->num_vertices; i++)
		(*parent)[i] = -1;
}

void	init_parent_array(t_route *route, int **parent)
{
	*parent = (int *)malloc(sizeof(int) * (route->num_vertices));
	reset_parent_array(route, parent);
}

int	main2(void)
{
	t_parse	*parse;
	// t_paths	paths;
	t_route	route;

	int **capacity;
	int	**temp;
	int	*parent;

	parse = parsing();
	// printf("parse result:\n");
	// parse_result_print(parse);

	/*
	**	create node map
	*/
	init_route(&route, parse);
	// init_paths(&paths);

	dijkstra(&route);
/*
	modified_dijkstra1(&route);
    disjoint_path(&route, weights);
	printf("disjoin paths:\n");
	print_paths_list(&route);

	free_paths(route.paths->paths);
	init_route(&route, parse);
	*/
	//init_paths(route.paths);

	capacity = (int **)malloc(sizeof(int*) * (route.num_vertices + 1));
	int i = 0;
	while (i < route.num_vertices)
	{
		capacity[i] = (int *)malloc(sizeof(int) * (route.num_vertices + 1));
		for (int j = 0; j <= route.num_vertices; j++)
			capacity[i][j] = '\0';
		// capacity[i][route.num_vertices] = '\0';
		i++;
	}
	capacity[i] = NULL;


	// printf("number of vertices: %d\n", route.num_vertices);
	// printf("start: (%d)\n", route.start);
	// printf("end: (%d)\n", route.end);
	fill_capacity(route.graph, capacity);
	//printf("\ncapacity");
	//print_2d_array(capacity, route.num_vertices);

	// /*
	// **	edmonds-karp
	// */
	// parent = (int *)malloc(sizeof(int) * (route.num_vertices));
	init_parent_array(&route, &parent);
	edmonds_karp(&route, route.paths, parent, capacity);
	/*
	i = 0;
	while (i < (route.num_vertices))
	{
		printf("index: %d, str:[%s]\n", i, route.node_map[i]);
		i++;
	}
	*/
	/*
	printf("\naf ek capacity");
	print_2d_array(capacity, route.num_vertices);
	printf("disjoin paths:\n");
	print_paths_list(&route);
	*/

	// /*
	// **	create new temp capacity based on the updated capacity
	// */
	temp = (int **)malloc(sizeof(int*) * (route.num_vertices + 1));
	i = 0;
	while (i < route.num_vertices)
	{
		temp[i] = (int *)malloc(sizeof(int) * (route.num_vertices + 1));
		temp[i][route.num_vertices] = '\0';
		i++;
	}
	temp[i] = NULL;

	fill_capacity(route.graph, temp);
	for (int u = 0; u < route.num_vertices; ++u)
	{
		for (int v = 0; v < route.num_vertices; ++v)
		{
			if (capacity[u][v] == 1)
				temp[u][v] = 0;
		}
	}
	/*
	printf("\ntemp");
	print_2d_array(temp, route.num_vertices);
	*/

	// /*
	// ** run edmonds-karp with new temp capacity
	// */
	/*
	free_paths(route.paths->paths);
	init_paths(route.paths);
	free(parent);
	init_parent_array(&route, &parent);
	edmonds_karp_with_weights(&route, route.paths, parent, temp);
	*/
	//printf("ek disjoin paths:\n");
	//print_paths_list(&route);
	/*
	printf("\naf ek temp");
	print_2d_array(temp, route.num_vertices);
	*/

	fill_capacity(route.graph, capacity);
	for (int u = 0; u < route.num_vertices; ++u)
	{
		for (int v = 0; v < route.num_vertices; ++v)
		{
			if (temp[u][v] == 1)
				capacity[u][v] = 0;
		}
	}
	/*
	free_paths(route.paths->paths);
	init_paths(route.paths);
	free(parent);
	init_parent_array(&route, &parent);
	edmonds_karp(&route, route.paths, parent, capacity);
	*/
	//optimize(&route);

	//t_path_len **elements = ants_distribute(route);
    //ants_print_frames(route, elements);
	t_path_len **elements = ants_distribute(route);
	// for(int i = 0; elements[i] != NULL; i++)
	// 	printf("value:%d\tindex:%d\tnum_ants%d\n",elements[i]->value, elements[i]->index, elements[i]->num_ants);


    ants_print_frames(route, elements);

	int total_length = 0;
	for(int i = 0; i < route.paths->num_paths; i++)
	{
	 	printf("elements - value: %d\t index:%d\tnum_ants:%d\n",
	 		elements[i]->value, elements[i]->index, elements[i]->num_ants);
		total_length += elements[i]->value;
	}
	printf("total_length:%d\n", total_length);


	for (int u = 0; u < route.num_vertices; ++u)
		free(temp[u]);
	free(temp);

	for(int i = 0; i < route.paths->num_paths; i++)
		free(elements[i]);
	free(elements);

	// // free(route.paths);
	ft_lstclear(&parse->nodes_head, free_node_xy);
	ft_lstclear(&parse->edge_info_head, free_edge);
	// free_graph
	free_graph(route.graph);
	free(route.graph);

	//free paths
	free_paths(route.paths->paths);
	//free_paths_list(route.paths);
	free(route.paths);
	free(route.distances);



	free(route.node_map);
	free(parse);
	free(parent);

	i = 0;
	while (i < route.num_vertices)
	{
		free(capacity[i]);
		i++;
	}
	free(capacity);

	// free(route.node_map);
    // print_frames(route, elements);

	return (0);
}

void	print_cur_path(void *content)
{
	t_graph_vertex *curr_vertex_ptr;

	curr_vertex_ptr = (t_graph_vertex*)content;
	printf("%d -> ", curr_vertex_ptr->vertex);
}

t_list	*max_flow_edmonds_karp(t_route *route, int start, int end)
{
	int	flow = 0;
	t_list	*edge_list;
	t_list	*paths;
	t_list	*prev_paths;
	t_graph_vertex *s;
	t_graph_vertex *t;
	t_graph_edge	*e;
	int prev_path_len;
	int i = 0;

	(void)i;
	(void)e;
	paths = NULL;
	prev_paths = NULL;
	s = graph_find_vertex(route->graph, start, 1);
	t = graph_find_vertex(route->graph, end, 0);
	prev_path_len = 0;
	while (1)
	{
		edge_list = graph_bfs(route, s, t);
		if (route->flags.debug)
			printf("edge_list->size:%d\n", ft_lstsize(edge_list));
		if (ft_lstsize(edge_list) == 0 || !update_edge_flow(route, edge_list, end))
			break ;
		flow++;
		paths = save_max_flow_paths(route, s, t, flow);
		printf("-----------\n");
		if (prev_path_len != 0 && prev_path_len < ants_check_loop_len(route, paths))
		{
			printf("========0000000============\n");
			printf("path_len:%d\n",prev_path_len - 2);
			printf("========0000000============\n");
			break;
		}
		print_all_paths(route, paths, 0);
		printf("-----------\n");
		if (route->flags.debug)
		{
			printf("\t\tmax flow path:%d\n", ft_lstsize(paths));
		}
		prev_path_len = ants_check_loop_len(route,paths);
		prev_paths = paths;
		(void)paths;
		//e = graph_find_edge(route->graph, 6, 4, 1);
		//printf("\t\t\t\te->u->vertex:%d\n", e->u->vertex);
		i++;
	}
	return prev_paths;
}

int main(void)
{
	t_parse	*parse;
	t_route	route;
	t_list	*paths;

	parse = parsing();
	init_route(&route, parse);
	if (route.flags.debug)
	{
		int i = 0;

		while (i < (route.num_vertices))
		{
			printf("index: %d, str:[%s]\n", i, route.node_map[i]);
			i++;
		}
	}

	add_vertices(&route);
	//print_edge_forward_travel(&route);
	//print_vertex_lists(&route);
	paths = max_flow_edmonds_karp(&route, route.start, route.end);
	print_all_paths(&route, paths, 0);
	printf("\t\tmax flow path:%d\n", ft_lstsize(paths));

	t_path_len **elements = ants_distribute(route);
	// for(int i = 0; elements[i] != NULL; i++)
	// 	printf("value:%d\tindex:%d\tnum_ants%d\n",elements[i]->value, elements[i]->index, elements[i]->num_ants);


    ants_print_frames(route, elements);

	int total_length = 0;
	for(int i = 0; i < route.paths->num_paths; i++)
	{
	 	printf("elements - value: %d\t index:%d\tnum_ants:%d\n",
	 		elements[i]->value, elements[i]->index, elements[i]->num_ants);
		total_length += elements[i]->value;
	}
	printf("total_length:%d\n", total_length);


	//ft_lstclear(&route.graph->v_in_list, free);


	for(int i = 0; i < route.paths->num_paths; i++)
		free(elements[i]);
	free(elements);

	ft_lstclear(&parse->nodes_head, free_node_xy);
	ft_lstclear(&parse->edge_info_head, free_edge);
	// free_graph
	free_graph(route.graph);
	free(route.graph);

	//free paths
	free_paths(route.paths->paths);
	free(route.paths);
	free(route.distances);

	free(route.node_map);
	free(parse);

	return 0;
}
