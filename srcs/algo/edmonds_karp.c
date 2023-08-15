#include "../../includes/lem-in.h"

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
			//printf("current vertex: %d\n", v);
			//printf("node's vertex: %d\n", v);
			if (!visited[v] && capacity[u][v] > 0)
			{
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
	t_vertex_list	*curr_path_ptr;
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

/*
void	optimize(t_route *route)
{
	t_list			*curr_list_ptr;
	t_vertex_list	*curr_path_ptr;
	int				weights;

	curr_list_ptr = route->paths->paths;

	while (curr_list_ptr != NULL)
	{
		curr_path_ptr = (t_vertex_list)curr_list_ptr->content;
		weights = 0;
		while (curr_path_ptr != NULL)
		{
			if (route->graph->adj_list[])
			weights++;
			curr_path_ptr->vertex
			curr_path_ptr = curr_path_ptr->next;
		}
		curr_list_ptr = curr_list_ptr->next;
	}
}
*/
