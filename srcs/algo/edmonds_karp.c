#include "../../includes/lem-in.h"

int bfs_with_priority(t_route* route, int* parent, int **capacity)
{
	int	visited[route->num_vertices];
	t_priority_queue	queue;

    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

	visited[route->start] = 1;
	init_priority_queue(&queue);
	enqueue_with_priority(&queue, route->start, 0);

	while (!priority_queue_empty(&queue))
	{
		int u = dequeue_with_priority(&queue);

		visited[u] = 1;
		//t_graph_node *neighbor = route->graph->adj_list[u];
		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			int v = node->vertex;
			int potential_distance = route->distances[u] + 1;
			if (potential_distance < route->distances[v])
			{
				route->distances[v] = potential_distance;
				enqueue_with_priority(&queue, v, potential_distance);
			}

			if (!visited[v] && capacity[u][v] > 0)
			{
			    parent[v] = u;
			    if (v == route->end)
			    {
			    	free_priority_queue(&queue);
			    	return (1);
			    }
				enqueue_with_priority(&queue, v, 0);
			}
		}
	}
	return (-1);
}


int bfs(t_route* route, int* parent, int **capacity)
{
	int	visited[route->num_vertices];
	t_queue	queue;

	//ft_memset(visited, 0, sizeof(visited));

    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    //print_array(parent, route->num_vertices);
    //reset_parent_array(route, &parent);

	visited[route->start] = 1;
	init_queue(&queue);
	enqueue(&queue, route->start);

	while (!is_empty(&queue))
	{
		int u = dequeue(&queue);

		visited[u] = 1;
		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			int v = node->vertex;
			//printf("node's vertex: %d\n", v);
			//printf("v: %d, u:%d\n", v, u);
			//printf("distance[%d]: %d, diatance[%d]:%d\n", v, route->paths->distances[v], u, route->paths->distances[u]);
			if (!visited[v] && capacity[u][v] > 0)// && route->paths->distances[v] > route->paths->distances[u])
			{
				//printf("current vertex: %d, parent:%d\n", v, u);
			    parent[v] = u;
			    if (v == route->end)
			    {
			    	free_queue(&queue);
			    	return (1);
			    }

				//printf("parent: ");
				//print_array(parent, route->num_vertices);
			//printf("visited:");
			//print_array(visited, route->num_vertices);
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
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
			//capacity[v][u] = 1;
			node = node->link;
		}
	}
}

void insert_next_parent(t_paths *paths, int v)
{
	t_vertex_list	*new_path_ptr;
	t_vertex_list	*curr_vertex_ptr;
	t_list			*curr_list_ptr;

 	new_path_ptr = (t_vertex_list*)malloc(sizeof(t_vertex_list));
	if (new_path_ptr == NULL)
	{
		ft_putstr_fd("malloc error\n", STDOUT_FILENO);
		return ;
	}

	init_vertex_list(new_path_ptr, v);

	curr_list_ptr = ft_lstfind_node(paths->paths, paths->num_paths);
	// adding t_list node
	if (curr_list_ptr == NULL)
	{
		// printf("list node for path id:%d not found!\n", paths->num_paths);
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
		curr_vertex_ptr = (t_vertex_list*)curr_list_ptr->content; //paths->paths[paths->num_paths];
		// if (curr_vertex_ptr == NULL)
		// {
		// 	printf("path id:%d head not found\n", paths->num_paths);
		// 	//curr_list_ptr->content = new_path_ptr;
		// }
		// else
		// {
			while (curr_vertex_ptr->next != NULL)
				curr_vertex_ptr = curr_vertex_ptr->next;
			curr_vertex_ptr->next = new_path_ptr;
			new_path_ptr->prev = curr_vertex_ptr;
			new_path_ptr->length = curr_vertex_ptr->length + 1;
		// }
		// printf("\tinsertion vertex:%d to path id:%d finished\n\n", v, paths->num_paths);
	}
}

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

t_graph_node	*find_next_shortest_vertex(t_route *route, t_graph_node *curr_graph_ptr)
{
	int	curr_distance = 0;
	int	next_distance = INT_MAX;

	while (curr_graph_ptr)
	{
		curr_distance = route->distances[curr_graph_ptr->vertex];
		next_distance = route->distances[curr_graph_ptr->link->vertex];
		if (curr_distance > next_distance)
			return curr_graph_ptr->link;
			//find_next_shortest_vertex(route, curr_graph_ptr->link);
		curr_graph_ptr = curr_graph_ptr->link;
	}
	return curr_graph_ptr;
}

int	find_shortest_path(t_route *route, t_vertex_list *curr_vertex_ptr, int passed_vertices)
{
	t_graph_node *curr_graph_ptr;
	t_graph_node *shortest_path_node;
	int prev_vertex;
	int	next_vertex;
	int	curr_path_length = 0;
	int	shortest_path_length = INT_MAX;

	//(route->graph->adj_list[vertex_ptr->vertex]);
	(void)route;
	prev_vertex = curr_vertex_ptr->prev->vertex;
	next_vertex = curr_vertex_ptr->next->vertex;
	curr_graph_ptr = route->graph->adj_list[curr_vertex_ptr->vertex];
	shortest_path_node = curr_graph_ptr;

	printf("perv vertex:%d\n", prev_vertex);
	printf("next vertex:%d\n", next_vertex);

	while (curr_graph_ptr)
	{
		if (curr_graph_ptr->vertex != prev_vertex && curr_graph_ptr->vertex != next_vertex)
		{
			curr_path_length = route->distances[curr_graph_ptr->vertex] + passed_vertices;
			if (shortest_path_length > curr_path_length)
			{
				shortest_path_length = curr_path_length;
				shortest_path_node = curr_graph_ptr;
			}
			//printf("curr graph vertex:%d-dist:%d\n", curr_graph_ptr->vertex, route->paths->distances[curr_graph_ptr->vertex]);
			printf("curr graph vertex:%d\n", curr_graph_ptr->vertex);
			printf("curr graph dist:%d\n", route->distances[curr_graph_ptr->vertex]);
			printf("curr path length:%d\n", curr_path_length);
		}
		curr_graph_ptr = curr_graph_ptr->link;
	}
	return shortest_path_node->vertex;
}

void	find_path(t_route *route)
{
	//t_graph_node	*curr_graph_ptr;
	t_list			*curr_list_ptr;
	t_vertex_list	*curr_vertex_ptr;
	int		num_edges;
	int		curr_vertex;
	int		curr_path = 0;
	int		passed_vertices;
	int		curr_path_length;
	int		shortest_path_length;
	int visited[route->num_vertices];

	ft_memset(visited, 0, sizeof(visited));
	curr_list_ptr = route->paths->paths;
	//while (curr_graph_ptr->link != NULL)
	//	curr_graph_ptr = find_next_shortest_vertex(route, curr_graph_ptr);
	while (curr_list_ptr != NULL)
	{
		curr_vertex_ptr = ((t_vertex_list*)curr_list_ptr->content)->next;
		curr_path_length = 0;
		passed_vertices = 1;
		shortest_path_length = INT_MAX;
		while (curr_vertex_ptr && curr_vertex_ptr->next != NULL)
		{
			curr_vertex = curr_vertex_ptr->vertex;
			visited[curr_vertex] = 1;
			num_edges = lstsize(route->graph->adj_list[curr_vertex_ptr->vertex]);
			if (num_edges > 2 && curr_vertex_ptr->next->next)
			{
				curr_path_length = route->distances[find_shortest_path(route, curr_vertex_ptr, passed_vertices + 1)] + passed_vertices + 1;
				if (shortest_path_length > curr_path_length)
					shortest_path_length = curr_path_length;
				printf("num of edges at curr vertex-%d : %d\n", curr_vertex, num_edges);
			}
			//printf("%d-", curr_vertex_ptr->vertex);
			curr_vertex_ptr = curr_vertex_ptr->next;
			passed_vertices++;
		}
		printf("\n");
		curr_list_ptr = curr_list_ptr->next;
		curr_path++;
		printf("\tshortest_path_length:%d for path id:%d\n", shortest_path_length, curr_path);
	}
}

void	optimize(t_route *route)
{
	t_list			*curr_list_ptr;
	int		curr_path = 0;
	int		visited[route->num_vertices];

	ft_memset(visited, 0, sizeof(visited));
	visited[route->end] = 1;
	curr_list_ptr = route->paths->paths;

	while (curr_list_ptr != NULL)
	{
		find_path(route);
		curr_list_ptr = curr_list_ptr->next;
		curr_path++;
	}
}
