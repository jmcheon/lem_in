#include "../../../includes/lem-in.h"

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

t_vertex_list	*insert_vertex(t_paths *paths, int v)
{
	t_vertex_list	*new_path_ptr;
	t_vertex_list	*curr_vertex_ptr;
	t_list			*curr_list_ptr;

 	new_path_ptr = (t_vertex_list*)malloc(sizeof(t_vertex_list));
	if (new_path_ptr == NULL)
	{
		ft_putstr_fd("malloc error\n", STDOUT_FILENO);
		return NULL;
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
	return new_path_ptr;
}

void	oneshot_edmonds_karp(t_route* route, int *parent, int **capacity, int (*f)(t_route*, int*, int**))
{
	t_vertex_list	*end_vertex_ptr;
	t_vertex_list	*start_vertex_ptr;

	start_vertex_ptr = NULL;
	end_vertex_ptr = NULL;
	while (f(route, parent, capacity) != -1)
	{
		for (int v = route->end; v != route->start; v = parent[v])
		{
			int u = parent[v];
			//printf("u, v = %d, %d\n", u, v);
			if (v == route->end)
				end_vertex_ptr = insert_vertex(route->oneshot_paths, v);
			start_vertex_ptr = insert_vertex(route->oneshot_paths, u);
			capacity[u][v] -= 1;
			capacity[v][u] += 1;
		}
		start_vertex_ptr->next = end_vertex_ptr;
		end_vertex_ptr->prev = start_vertex_ptr;
		route->oneshot_paths->num_paths++;
	}
}
