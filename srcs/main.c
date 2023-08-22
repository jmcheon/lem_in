#include "../includes/queue.h"
#include "../includes/lem-in.h"

// void print_frames(t_route route, t_path_len **elements)
// {
// 	int longest_path = 0;
// 	int total_used_path = 0;
// 	for(int i = 0; i < route.paths->num_paths; i++)
// 	{
// 		if (elements[i]->num_ants > 0)
// 		{
// 			if (longest_path < elements[i]->value)
// 				longest_path = elements[i]->value;
// 			total_used_path++;
// 		}
// 	}
// 	// printf("longest_path:%d total_used_path:%d\n", longest_path, total_used_path);

// 	t_ants_print **test;
// 	test = (t_ants_print **)malloc(sizeof(t_ants_print *) * (total_used_path +1));
// 	if (!test)
// 		return ;
// 	int i = 0;
// 	while (i < total_used_path)
// 	{
// 		test[i] = (t_ants_print *)malloc(sizeof(t_ants_print) * (longest_path + 1));
// 		for (int j = 0; j <= longest_path; j++)
// 			test[i][j].node_name = NULL;
// 		ft_memset(test[i], '\0', sizeof(test[i]));
// 		i++;
// 	}
// 	// test[i] = NULL;


// 	i = 0;
// 	while (i < total_used_path)
// 	{
// 		// printf("[%d]", (route.paths->num_paths - total_used_path) + i);
// 		t_vertex_list *one_path = ft_lstfind_node(route.paths->paths, elements[(route.paths->num_paths - total_used_path) + i]->index)->content;
// 		while (one_path != NULL)
// 		{
// 			if (one_path->next == NULL)
// 				break;
// 			one_path = one_path->next;
// 		}
// 		// int begin = longest_path - elements[i]->value;
// 		int begin = 0;
// 		one_path = one_path->prev;
// 		// printf("begin:%d\ti:%d\n", begin, i);
// 		while (one_path != NULL)
// 		{
// 			// needs to change
// 			test[i][begin].node_name = route.node_map[one_path->vertex];
// 			test[i][begin].ant_max = elements[(route.paths->num_paths - total_used_path) + i]->num_ants;
// 			test[i][begin].ant_current = 0;
// 			// printf("%d ",one_path->vertex);
// 			begin++;
// 			one_path = one_path->prev;
// 		}
// 		// printf("\n");
// 		i++;
// 	}

// 	// printf("================================\n");
// 	// i = 0;
// 	// while (i < total_used_path)
// 	// {
// 	// 	int j = 0;
// 	// 	while (j < longest_path)
// 	// 	{
// 	// 		if (test[i][j].node_name == NULL)
// 	// 			printf("[null] ");
// 	// 		else
// 	// 			printf("[%s] ",test[i][j].node_name);
// 	// 		j++;
// 	// 	}
// 	// 	printf("\n");
// 	// 	i++;
// 	// }
// 	// printf("================================\n");

// 	int loop = 0;
// 	for(int i = route.paths->num_paths - total_used_path ; i < route.paths->num_paths; i++)
// 	{
// 		if (loop < elements[i]->value + elements[i]->num_ants)
// 			loop = elements[i]->value + elements[i]->num_ants;
// 	}
// 	// printf("loop:%d\n", loop);

// 	for(int i = 0; i < (loop - 1); i++)
// 	{
// 		if (i < longest_path)
// 		{
// 			// printf("begin:%d end:%d\n", 0, i);
// 			ants_pass_to_matrix(test, total_used_path, 0, i);
// 		}
// 		// else if (loop - i < longest_path)
// 		// {
// 		// 	// printf("begin:%d end:%d\n", i - (loop - longest_path), longest_path);
// 		// 	// for checking
// 		// 	// printf("another condition:%d\n", i - (loop - longest_path));
// 		// 	ants_pass_to_matrix(test, route, i - (loop - longest_path), longest_path, false);
// 		// }
// 		else
// 		{
// 			// printf("begin:%d end:%d\n", 0, longest_path);
// 			ants_pass_to_matrix(test, total_used_path, 0, longest_path);
// 		}

// 		ants_print_oneframe(test, total_used_path, longest_path);
// 		printf("\n");
// 	}

// 	i = 0;
// 	while (i < total_used_path)
// 	{
// 		free(test[i]);
// 		i++;
// 	}
// 	free(test);

// }

// void    init_paths_ants(t_paths_ants* paths_ants, int num_paths)
// {
//     printf("num_paths:%d\n", num_paths);
//     paths_ants->paths_ants = (t_ants**)malloc(sizeof(t_ants*) * (num_paths + 1));
//     //for (int i = 0; i < num_paths; ++i)
//     //	paths_ants->paths_ants[i] = (t_ants*)malloc(sizeof(t_ants) * (elements[i].num_ants + 1));
// }

// void    init_ants(t_ants* ants, t_path_len **elements, int num_paths)
// {
// 	(void)elements;
//     printf("num_paths:%d\n", num_paths);
//     ants->movements_list = (t_vertex_list**)malloc(sizeof(t_vertex_list*) * (num_paths + 1));
//     for (int i = 0; i < num_paths; ++i)
//     	ants->movements_list[i] = (t_vertex_list*)malloc(sizeof(t_vertex_list) * (elements[i]->num_ants + 1));
// }

/*
void	print_ant_movement(t_route *route, int num_ants)
{
	t_vertex_list *curr;
	(void)num_ants;

	//for(int i = 0; i < route->paths->num_paths; i++)
    {
		int i = 0;
		curr = route->paths->paths[i];
		//printf("forward\n");
        while (curr->next != NULL)
		{
			//printf("%d\n", curr->vertex);
            curr = curr->next;
		}
		//curr = route->paths->paths[i];
		printf("backard\n");
        while (curr->prev != NULL)
		{
            curr = curr->prev;
			printf("%d\n", curr->vertex);
		}
        while (curr->prev != NULL)
        {
            curr = curr->prev;
			printf("%dL%d-%s", num_ants, ++curr->count_ants, route->node_map[curr->vertex]);
			if (curr->prev != NULL)// && num_ants != curr->count_ants)
				printf("\n");
			else
				printf(" ");
        }
    }
}
*/

/*
void    print_test(t_route *route, t_path_len *elements)
{
    printf("\n\n==================print test=====================\n\n");

	t_paths_ants paths_ants;
	t_path_list *curr;
	int	max_num_ants = 0;
	int k, l, num_ants, max_moves;

    init_paths_ants(&paths_ants, route->paths->num_paths);
	for(int i = 0; i < route->paths->num_paths; ++i)
    {
		if (max_num_ants < elements[i]->num_ants)
			max_num_ants = elements[i]->num_ants;
	}
	printf("max num ants:%d\n\n", max_num_ants);
	for(int i = 0; i < route->paths->num_paths; ++i)
	{
		t_ants ants;

		curr = route->paths->paths_list[i];
    	init_ants(&ants, elements, route->paths->num_paths);
        while (curr->next != NULL)
            curr = curr->next;
    	for (int j = 0; j < elements[i]->num_ants; ++j)
			ants.movements_list[j] = curr;
		paths_ants.paths_ants[i] = &ants;

		num_ants = elements[i]->num_ants;
		max_moves = num_ants + elements[i]->value - 1;
		for (k = 0; k < max_moves; k++)
		{
			ants.movements_list[j] = route->paths->paths[i];
    	}
	}
    //for (int i = 0; i < max_num_ants; ++i)
		//print_ant_movement(route, elements[0]->num_ants--);

	//print_ant_movement(route, elements[0]->num_ants--);
	//for(int i = 0; i < route->paths->num_paths; ++i)
	{
		//move_ant(route, paths_ants.paths_ants[i]->movements_list[0], 1);
	}

	return ;
}
	*/

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

int	max_flow_edmonds_karp(t_route *route, int start, int end)
{
	int	flow = 0;
	t_list	*edge_list;
	t_list	*paths;
	t_graph_vertex *s;
	t_graph_vertex *t;
	t_graph_edge	*e;
	int i = 1;

	(void)i;
	(void)e;
	s = graph_find_vertex(route->graph, start, 0);
	t = graph_find_vertex(route->graph, end, 1);
	while (1)
	{
		edge_list = graph_bfs(route, s, t);
		//printf("test0\n");
		//printf("edge_list->size:%d\n", ft_lstsize(edge_list));
		if (ft_lstsize(edge_list) == 0 || !update_edge_flow(edge_list, end))
			break ;
		flow++;
		paths = save_max_flow_paths(s, t, flow);
		print_all_paths(paths);
		printf("\t\tmax flow path:%d\n", ft_lstsize(paths));
		//e = graph_find_edge(route->graph, 6, 4, 1);
		//printf("\t\t\t\te->u->vertex:%d\n", e->u->vertex);
		i--;
	}
	return flow;
}

int main(void)
{
	t_parse	*parse;
	t_route	route;
	
	parse = parsing();
	init_route(&route, parse);
	int i = 0;
	while (i < (route.num_vertices))
	{
		printf("index: %d, str:[%s]\n", i, route.node_map[i]);
		i++;
	}
	
	add_vertices(&route);
	//print_edge_forward_travel(&route);
	//print_vertex_lists(&route);
	max_flow_edmonds_karp(&route, route.start, route.end);

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
