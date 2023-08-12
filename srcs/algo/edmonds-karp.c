#include "../../includes/queue.h"
#include "../../includes/lem-in.h"

int bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES])
{
	int n = route->graph->n;
	int visited[n];
	t_queue queue;
	printf("%d\n", n);
	ft_memset(visited, 0, sizeof(visited));
	visited[route->start] = 1;
	init_queue(&queue);
	enqueue(&queue, route->start);

	while (!is_empty(&queue))
	{
		int u = dequeue(&queue);

		for (int v =0; v < n; v++)
		{
			// printf("visited:");
			print_array(visited, n);
			// printf("current vertex: %d\n", v);
			// printf("node's vertex: %d\n", v);
			if (!visited[v] && capacity[u][v] > 0)
			{
				parent[v] = u;
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

void print_paths_list(t_paths *paths)
{
	int i;

	i = 0;
	while (i < paths->num_paths)
	{
		t_int_list *curr = paths->paths_list[i];
		printf("path %d - ", i + 1);
		if (curr != NULL)
		{
			printf("%d", curr->content);
			curr = curr->next;
		}
		while (curr != NULL)
		{
			printf(" <- %d", curr->content);
			curr = curr->next;
		}
		printf("\n");
		i++;
	}
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

void	fill_capacity(t_graph *graph, int capacity[][MAX_VERTICES])
{
	for (int u = 0; u < graph->n; ++u)
	{
		for (int v = 0; v < graph->n; ++v)
		{
			if (graph->matrix[u][v] == 1)
				capacity[u][v] = 1;
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
	for (int i = 0; i < MAX_VERTICES; ++i)
		paths->paths_list[i] = NULL;
}

void insert_next_parent(t_paths *paths, int v)
{
	// create a new node
	t_int_list *new_node = malloc(sizeof(t_int_list));
	new_node->content = v;
	new_node->next = NULL;

	// add new node to the end of the adjacency list for current path id
	if (paths->paths_list[paths->num_paths] == NULL)
	{
		paths->paths_list[paths->num_paths] = new_node;
	}
	else
	{
		t_int_list *curr = paths->paths_list[paths->num_paths];
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_node;
	}
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

void	init_route(t_route* route, t_parse* parse)
{
	route->list_size = ft_lstsize(parse->nodes_head);
	route->node_map = (char **)malloc(sizeof(char *) * (route->list_size + 1));

	int i = 0;
	while (i < route->list_size)
	{
		route->node_map[i] = (char *)malloc(sizeof(char *) + 1);
		i++;
	}
	route->node_map[route->list_size] = NULL;
	node_map_to_array(parse->nodes_head, route->node_map);

	route->start = 0;
	route->end = route->list_size - 1;
	route->num_vertices = route->graph->n;

	route->paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->paths);
}

void	destroy_route(t_route* route)
{
	(void)route;
}

