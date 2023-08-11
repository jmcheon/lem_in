#include "../includes/algo.h"
#include "../includes/lem-in.h"

int bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES])
{
	int	n = route->graph->n;
	int	visited[n];
	t_queue	queue;

	ft_memset(visited, 0, sizeof(visited));
	visited[route->start] = 1;
	init_queue(&queue);
	enqueue(&queue, route->start);


	while (!is_empty(&queue))
	{
		int u = dequeue(&queue);

		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			//printf("visited:");
			//print_array(visited, n);
			int v = node->vertex;
			//printf("current vertex: %d\n", v);
			//printf("node's vertex: %d\n", v);
			if (!visited[v] && capacity[u][v] > 0)
			{
				parent[v] = u;
				//printf("parent: ");
				//print_array(parent, n);
				visited[v] = 1;
				if (v == route->end)
					return (1);
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
}

void	print_path(t_route* route, int* parent, int path_id)
{
	int	v;

	if (parent[route->end] == -1)
	{
		printf("path %d: not found.\n", path_id);
		return ;
	}

	printf("path %d - [%d]:%s", path_id, route->end, route->node_map[route->end]);
	v = route->end;
	while (v != route->start)
	{
		v = parent[v];
		printf("<- [%d]:%s", v, route->node_map[v]);
	}
	printf("\n");
}

void	print_paths(t_route* route, t_paths* paths)
{
	for (int i = 0; i < paths->num_paths; ++i)
	{
		int path[MAX_VERTICES];
		int path_len = 0;

		for (int j = 0; j < route->num_vertices; ++j)
		{
			if (paths->paths[i][j] != 0)
			{
				//printf("%d ", paths->paths[i][j]);
				path[path_len++] = paths->paths[i][j];
			}
		}
		//printf("path_len:%d\n", path_len);
		printf("path %d - [%d]:%s", i + 1, route->end, route->node_map[route->end]);
		for (int j = 0; j < path_len; ++j)
		{
			if (path[j] != route->start && path[j] != route->end)
				printf(" <- [%d]:%s", path[j], route->node_map[path[j]]);
		}
		printf(" <- [%d]:%s\n", route->start, route->node_map[route->start]);
	}
}

void	fill_capacity(t_graph_type* graph, int capacity[][MAX_VERTICES])
{
	for (int u = 0; u < graph->n; ++u)
	{
		t_graph_node* node = graph->adj_list[u];
		while (node != NULL)
		{
			int v = node->vertex;
			capacity[u][v] = 1;
			capacity[v][u] = 1;
			node = node->link;
		}
	}
}

void	print_capacity(int capacity[][MAX_VERTICES], int n)
{
	printf("\nprint capacity:\n\n");
	for (int u = 0; u < n; ++u)
	{
		for (int v = 0; v < n; ++v)
			printf("%d ", capacity[u][v]);
		printf("\n");
	}
}

void	print_array(int *parent, int n)
{
	for (int u = 0; u < n; ++u)
		printf("%d ", parent[u]);
	printf("\n\n");
}

void	init_paths(t_paths* paths)
{
	paths->num_paths = 0;
	ft_memset(paths->paths, 0, sizeof(paths->paths));
}

void	edmonds_karp(t_route* route, t_paths* paths, int* parent, int capacity[][MAX_VERTICES])
{
	int	path_id = 0;

	while (bfs(route, parent, capacity) != -1)
	{
		int i = 0;
		for (int v = route->end; v != route->start; v = parent[v])
		{
			int u = parent[v];
			//printf("u, v = %d, %d\n", u, v);
			paths->paths[paths->num_paths][i++] = u;
			capacity[u][v] -= 1;
			capacity[v][u] += 1;
		}
		paths->num_paths++;
		path_id++;
		print_path(route, parent, path_id);
	}
}

int	main(void)
{
	t_parse	*parse;
	t_paths	paths;
	t_route	route;

	int	capacity[MAX_VERTICES][MAX_VERTICES] = {0};
	int	temp[MAX_VERTICES][MAX_VERTICES] = {0};
	int	parent[MAX_VERTICES];

	init_paths(&paths);
	parse = parsing();
	printf("parse result:\n");
	parse_result_print(parse);
	route.graph = parse_to_graph(parse);

	/*
	**	create node map
	*/
	route.list_size = ft_lstsize(parse->nodes_head) - 1;
	route.node_map = (char **)malloc(sizeof(char *) * (route.list_size + 1));

	int i = 0;
	while (i < route.list_size)
	{
		route.node_map[i] = (char *)malloc(sizeof(char *) + 1);
		i++;
	}
	route.node_map[route.list_size] = NULL;
	node_map_to_array(parse->nodes_head, route.node_map);

	route.start = 0;
	route.end = route.list_size - 1;
	route.num_vertices = route.graph->n;

	printf("number of vertices: %d\n", route.num_vertices);
	printf("start: (%d)\n", route.start);
	printf("end: (%d)\n", route.end);
	fill_capacity(route.graph, capacity);
	print_capacity(capacity, route.num_vertices);

	/*
	**	edmonds-karp
	*/
	edmonds_karp(&route, &paths, parent, capacity);
	i = 0;
	while (i < (route.list_size - 1))
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
	init_paths(&paths);
	edmonds_karp(&route, &paths, parent, temp);

	printf("\n\ndisjoin paths:\n");
	print_paths(&route, &paths);
	return (0);
}
