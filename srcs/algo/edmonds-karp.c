#include "../../includes/queue.h"
#include "../../includes/lem-in.h"

int bfs(t_route* route, int* parent, int **capacity)
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
				{
					free_queue(&queue);
					return (1);
				}
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

void print_path_node(void *data)
{
	t_vertex_list *curr_paths_ptr;

	curr_paths_ptr = (t_vertex_list*)data;
	if (curr_paths_ptr != NULL)
		printf(" <- %d", curr_paths_ptr->vertex);
}

void print_paths_list(t_paths *paths)
{
	t_vertex_list	*curr_path_ptr;
	t_list			*curr_list_ptr;
	int i;

	curr_list_ptr = paths->paths;
	//ft_lstiter(curr_list_ptr, print_path_node);
	//for (int i = 0; i < paths->num_pahts; ++i)
	i = 0;
	while (curr_list_ptr != NULL)
	{
		//ft_lstiter(curr_list_ptr, print_path_node);
		curr_path_ptr = (t_vertex_list*)curr_list_ptr->content;
		printf("path %d - ", i + 1);
		if (curr_path_ptr != NULL)
		{
			printf("%d", curr_path_ptr->vertex);
			curr_path_ptr = curr_path_ptr->next;
		}
		while (curr_path_ptr != NULL)
		{
			printf(" <- %d", curr_path_ptr->vertex);
			curr_path_ptr = curr_path_ptr->next;
		}
		printf("\n");
		curr_list_ptr = curr_list_ptr->next;
		i++;
	}
	printf("i:%d\n", i);
	return ;
	/*
	int i;

	i = 0;
	while (i < paths->num_paths)
	{
		curr_ptr = paths->paths[i];
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
		curr_ptr = paths->paths[i];
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
	*/
}

void	fill_capacity(t_graph* graph, int **capacity)
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

void	print_capacity(int **capacity, int n)
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

void	init_path(t_vertex_list* path)
{
	path->vertex = -1;
	path->count_ants = 0;
	path->next = NULL;
	path->prev = NULL;
}

void	init_paths(t_paths* paths)
{
	//paths->paths = ft_lstnew(NULL);
	paths->paths = NULL;
	paths->num_paths = 0;
}

void insert_next_list_node(t_paths *paths, int end)
{
	t_vertex_list *path_ptr;

 	path_ptr = (t_vertex_list*)malloc(sizeof(t_vertex_list));
	path_ptr->vertex= end;
	path_ptr->next = NULL;
	path_ptr->prev = NULL;
	printf("end:%d\n", end);

	ft_lstadd_back(&paths->paths, ft_lstnew(path_ptr));
}

void insert_next_parent(t_paths *paths, int v)
{
	t_vertex_list	*new_path_ptr;
	t_vertex_list	*curr_path_ptr;
	t_list			*curr_list_ptr;

 	new_path_ptr = (t_vertex_list*)malloc(sizeof(t_vertex_list));
	if (new_path_ptr == NULL)
	{
		printf("malloc error\n");
		return ;
	}

	new_path_ptr->vertex= v;
	new_path_ptr->next = NULL;
	new_path_ptr->prev = NULL;

	curr_list_ptr = ft_lstfind_node(paths->paths, paths->num_paths);
	// adding t_list node
	if (curr_list_ptr == NULL)
	{
		// printf("list node for path id:%d not found!\n", paths->num_paths);
		//insert_next_list_node(paths, v);
		ft_lstadd_back(&paths->paths, ft_lstnew(new_path_ptr));
		// printf("\tinsertion vertex:%d to path id:%d finished\n\n", v, paths->num_paths);
	}
	// adding t_vertex_list vertex
	else// if (curr_list_ptr != NULL)
	{
		curr_list_ptr = ft_lstfind_node(paths->paths, paths->num_paths);
		// if (curr_list_ptr)
		// 	printf("list node for path id:%d FOUND!\n", paths->num_paths);
		// if (curr_list_ptr->content != NULL)
		// 	printf("currnet vertext:%d, new vertex:%d\n", ((t_vertex_list*)curr_list_ptr->content)->vertex, v);
		curr_path_ptr = (t_vertex_list*)curr_list_ptr->content; //paths->paths[paths->num_paths];
		// if (curr_path_ptr == NULL)
		// {
		// 	printf("path id:%d head not found\n", paths->num_paths);
		// 	//curr_list_ptr->content = new_path_ptr;
		// }
		// else
		// {
			while (curr_path_ptr->next != NULL)
				curr_path_ptr = curr_path_ptr->next;
			curr_path_ptr->next = new_path_ptr;
			new_path_ptr->prev = curr_path_ptr;
		// }
		// printf("\tinsertion vertex:%d to path id:%d finished\n\n", v, paths->num_paths);
	}
	/*
	if (ft_lstfind_node(paths->paths, paths->num_paths))
	{
		printf("creating a list node for path id:%d...\n", paths->num_paths);
		ft_lstadd_back(&paths->paths, ft_lstnew(path_ptr));
	}
	else
		printf("list node for path id:%d not found.\n", paths->num_paths);
		*/
}

/*
void insert_next_parent(t_paths *paths, int v)
{
	// create a new node
	t_vertex_list *node_ptr = malloc(sizeof(t_vertex_list));
	//t_vertex_list *curr_ptr;

	node_ptr->vertex= v;
	node_ptr->next = NULL;
	node_ptr->prev = NULL;

	// add new node to the end of the adjacency list for current path id
	if (ft_lstfind_node(paths->paths, paths->num_paths))
		printf("yes\n");
	if (paths->paths[paths->num_paths] == NULL)
	{
		paths->paths[paths->num_paths] = node_ptr;
	}
	else
	{
		curr_ptr = paths->paths[paths->num_paths];
		while (curr_ptr->next != NULL)
			curr_ptr = curr_ptr->next;
		curr_ptr->next = node_ptr;
		node_ptr->prev = curr_ptr;
	}
}
	*/

void	edmonds_karp(t_route* route, t_paths* paths, int* parent, int **capacity)
{
	// int	path_id = 0;

	while (bfs(route, parent, capacity) != -1)
	{
		for (int v = route->end; v != route->start; v = parent[v])
		{
			int u = parent[v];
			//printf("u, v = %d, %d\n", u, v);
			if (v == route->end)
				insert_next_parent(paths, v);
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
	route->num_vertices = ft_lstsize(parse->nodes_head);
	route->node_map = node_map_to_array(parse->nodes_head);
	// int	i = 0;
	// while (i < route->num_vertices)
	// {
	// 	// printf("[%s]\n", route->node_map[i]);
	// 	i++;
	// }
	route->graph = parse_to_graph(parse, route);
	if (route->graph == NULL)
	{
		ft_lstclear(&parse->nodes_head, free_node_xy);
		ft_lstclear(&parse->edge_info_head, free_edge);
		free(route->node_map);
		// free_graph(route->graph);
		free(parse);
		printf("leaks\n");
		exit(1);
	}
	route->start = 0;
	route->end = route->num_vertices - 1;

	route->paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->paths);

}

void	destroy_route(t_route* route)
{
	(void)route;
}

