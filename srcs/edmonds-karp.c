#include "../includes/algo.h"
#include "../includes/lem-in.h"

int disjoint_bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES], t_paths* paths)
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
		//printf("queue is not empty.. checking..\n");
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
				int skip = 0;
				for (int i = 0; i < paths->num_paths; ++i)
				{
					int path[MAX_VERTICES];
					int path_len = 0;
					
					for (int j = 0; j < MAX_VERTICES; ++j)
					{
						if (paths->paths[i][j] != 0)
							path[path_len++] = paths->paths[i][j];
					}
					for (int j = 0; j < path_len; ++j)
					{
						if (paths->paths[i][j] == v && path[j] != route->start && path[j] != route->end)
						{
							skip = 1;
							break;
						}
					}
					//if (paths->paths[i][v] == 1 && v != route->start && v != route->end)
				}
				if (!skip)
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
	}
	return (-1);
}


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
		//printf("queue is not empty.. checking..\n");
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
		
		for (int j = 0; j < MAX_VERTICES; ++j)
		{
			if (paths->paths[i][j] != 0)
				path[path_len++] = paths->paths[i][j];
		}
		printf("path %d - [%d]:%s", i + 1, route->end, route->node_map[route->end]);
		for (int j = 0; j < path_len; ++j)
		{
			if (path[j] != route->start && path[j] != route->end)
				printf("<- [%d]:%s", path[j], route->node_map[path[j]]);
		}
		
		printf("<- [%d]:%s\n", route->start, route->node_map[route->start]);
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
			(void)capacity;
			capacity[u][v] = 1;
			capacity[v][u] = 1;
			node = node->link;
		}
	}
}

void	print_capacity(int capacity[][MAX_VERTICES], int n)
{
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
	{
		printf("%d ", parent[u]);
	}
	printf("\n\n");
}

int	main(void)
{
	t_parse	*parse;
	t_paths	paths;
	t_route	route;

	int	max_flow = 0;
	int	capacity[MAX_VERTICES][MAX_VERTICES] = {0};
	int	parent[MAX_VERTICES];

	paths.num_paths = 0;
	ft_memset(paths.paths, 0, sizeof(paths.paths));
	parse = parsing();
	printf("parse result:\n");
	parse_result_print(parse);
	route.graph = parse_to_graph(parse);

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

	//while (disjoint_bfs(&route, parent, capacity, &paths) != -1)
	while (bfs(&route, parent, capacity) != -1)
	{
		int	path_flow = INT_MAX;

		for (int v = route.end; v != route.start; v = parent[v])
		{
			int u = parent[v];
			path_flow = (capacity[u][v] < path_flow) ? capacity[u][v] : path_flow;
		}


		int i = 0;
		for (int v = route.end; v != route.start; v = parent[v])
		{
			int u = parent[v];
			printf("u, v = %d, %d\n", u, v);
			paths.paths[paths.num_paths][i++] = u;
			//paths.paths[paths.num_paths][v] = 1;
			capacity[u][v] -= path_flow;
			capacity[v][u] += path_flow;
		}
		paths.num_paths++;
		max_flow += path_flow;
		print_path(&route, parent, max_flow);
	}
	i = 0;
	while (i < (route.list_size - 1))
	{
		printf("index: %d, str:[%s]\n", i, route.node_map[i]);
		i++;
	}
	print_capacity(capacity, route.num_vertices);
	printf("disjoin paths:\n");
	print_paths(&route, &paths);
	return (0);
}
