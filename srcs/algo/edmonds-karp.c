#include "../../includes/queue.h"
#include "../../includes/lem-in.h"

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

void print_paths_list(t_paths *paths)
{
	t_path_list *curr_ptr;
	int i;

	i = 0;
	while (i < paths->num_paths)
	{
		curr_ptr = paths->paths_list[i];
		printf("path %d - ", i + 1);
		if (curr_ptr != NULL)
		{
			printf("%d", curr_ptr->vertex);
			curr_ptr = curr_ptr->next;
		}
		while (curr_ptr != NULL)
		{
			printf(" <- %d", curr_ptr->vertex);
			curr_ptr = curr_ptr->next;
		}
		printf("\n");
		i++;
	}
	i = 0;
	while (i < paths->num_paths)
	{
		curr_ptr = paths->paths_list[i];
		while (curr_ptr->next != NULL)
			curr_ptr = curr_ptr->next;
		//printf("last vertex:%d\n", curr_ptr->vertex);


		printf("path %d - ", i + 1);
		if (curr_ptr != NULL)
		{
			printf("%d", curr_ptr->vertex);
			curr_ptr = curr_ptr->prev;
		}
		while (curr_ptr != NULL)
		{
			printf(" -> %d", curr_ptr->vertex);
			curr_ptr = curr_ptr->prev;
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

void	fill_capacity(t_graph* graph, int capacity[][MAX_VERTICES])
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

void	init_path(t_path_list* path)
{
	path->vertex = -1;
	path->count_ants = 0;
	path->next = NULL;
	path->prev = NULL;
}

void	init_paths(t_paths* paths)
{
	paths->num_paths = 0;
	ft_memset(paths->paths, 0, sizeof(paths->paths));
	for (int i = 0; i < MAX_VERTICES; ++i)
	{
		//init_path(paths->paths_list[i]);
		paths->paths_list[i] = NULL;
	}
}

void insert_next_parent(t_paths *paths, int v)
{
	// create a new node
	t_path_list *node_ptr = malloc(sizeof(t_path_list));
	t_path_list *curr_ptr;

	node_ptr->vertex= v;
	node_ptr->next = NULL;
	node_ptr->prev = NULL;

	// add new node to the end of the adjacency list for current path id
	if (paths->paths_list[paths->num_paths] == NULL)
	{
		paths->paths_list[paths->num_paths] = node_ptr;
	}
	else
	{
		curr_ptr = paths->paths_list[paths->num_paths];
		while (curr_ptr->next != NULL)
			curr_ptr = curr_ptr->next;
		curr_ptr->next = node_ptr;
		node_ptr->prev = curr_ptr;
	}
}

void	edmonds_karp(t_route* route, t_paths* paths, int* parent, int capacity[][MAX_VERTICES])
{
	// int	path_id = 0;

	while (bfs(route, parent, capacity) != -1)
	{
		int i = 0;
		for (int v = route->end; v != route->start; v = parent[v])
		{
			int u = parent[v];
			//printf("u, v = %d, %d\n", u, v);
			if (v == route->end)
			{
				paths->paths[paths->num_paths][i++] = v;
				insert_next_parent(paths, v);
			}
			paths->paths[paths->num_paths][i++] = u;
			insert_next_parent(paths, u);
			capacity[u][v] -= 1;
			capacity[v][u] += 1;
		}
		paths->num_paths++;
		// path_id++;
		// print_path(route, parent, path_id);
	}
}

void	init_route(t_route* route, t_parse* parse)
{
	route->num_ants = parse->num_ants;
	route->list_size = ft_lstsize(parse->nodes_head);
	route->node_map = node_map_to_array(parse->nodes_head);
	int	i = 0;
	while (i < route->list_size)
	{
		printf("[%s]\n", route->node_map[i]);
		i++;
	}

	// route->graph = parse_to_graph(parse, route);
	route->start = 0;
	route->end = route->list_size - 1;
	// route->num_vertices = route->graph->n;

	route->paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->paths);

}

void	destroy_route(t_route* route)
{
	(void)route;
}

