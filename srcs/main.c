#include "../includes/queue.h"
#include "../includes/lem-in.h"

int	main(void)
{
	t_parse	*parse;
	//t_paths	paths;
	t_route	route;

	int	capacity[MAX_VERTICES][MAX_VERTICES] = {0};
	int	temp[MAX_VERTICES][MAX_VERTICES] = {0};
	int	parent[MAX_VERTICES];

	parse = parsing();
	printf("parse result:\n");
	parse_result_print(parse);
	route.num_ants = parse->num_ants;
	route.graph = parse_to_graph(parse);

	/*
	**	create node map
	*/
	init_route(&route, parse);
	//init_paths(&paths);

	printf("number of vertices: %d\n", route.num_vertices);
	printf("start: (%d)\n", route.start);
	printf("end: (%d)\n", route.end);
	fill_capacity(route.graph, capacity);
	//print_capacity(capacity, route.num_vertices);

	/*
	**	edmonds-karp
	*/
	edmonds_karp(&route, route.paths, parent, capacity);
	int i = 0;
	while (i < (route.list_size))
	{
		printf("index: %d, str:[%s]\n", i, route.node_map[i]);
		i++;
	}
	//print_capacity(capacity, route.num_vertices);
	//printf("disjoin paths:\n");
	//print_paths(&route, &paths);

	/*
	**	create new temp capacity based on the updated capacity
	*/
	fill_capacity(route.graph, temp);
	for (int u = 0; u < route.num_vertices; ++u)
	{
		for (int v = 0; v < route.num_vertices; ++v)
		{
			if (capacity[u][v] == 1)
				temp[u][v] = 0;
		}
	}
	//print_capacity(temp, route.num_vertices);

	/*
	** run edmonds-karp with new temp capacity
	*/
	init_paths(route.paths);
	edmonds_karp(&route, route.paths, parent, temp);

	printf("\n\ndisjoin paths:\n");
	print_paths(&route, route.paths);
	print_paths_list(route.paths);
	t_path_len **elements =distribute_ant(route);
	for(int i = 0; i < route.paths->num_paths; i++)
		printf("elements - value: %d\t index:%d\tnum_ants:%d\n",
			elements[i]->value, elements[i]->index, elements[i]->num_ants);

	return (0);
}
