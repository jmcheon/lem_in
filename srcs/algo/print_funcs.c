#include "../../includes/lem-in.h"

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

void print_paths_list(t_route *route)
{
	t_vertex_list	*curr_vertex_ptr;
	t_list			*curr_list_ptr;
	int i;

	curr_list_ptr = route->paths->paths;
	//ft_lstiter(curr_list_ptr, print_path_node);
	//for (int i = 0; i < paths->num_pahts; ++i)
	i = 0;
	while (curr_list_ptr != NULL)
	{
		//ft_lstiter(curr_list_ptr, print_path_node);
		curr_vertex_ptr = (t_vertex_list*)curr_list_ptr->content;
		printf("path %d - ", i + 1);
		if (curr_vertex_ptr != NULL)
		{
			printf("[%d](%d):%s", curr_vertex_ptr->vertex, curr_vertex_ptr->length, route->node_map[curr_vertex_ptr->vertex]);
			curr_vertex_ptr = curr_vertex_ptr->next;
		}
		while (curr_vertex_ptr != NULL)
		{
			printf(" <- [%d](%d):%s", curr_vertex_ptr->vertex, curr_vertex_ptr->length, route->node_map[curr_vertex_ptr->vertex]);
			//printf(" <- [%d]:%s", curr_vertex_ptr->vertex, route->node_map[curr_vertex_ptr->vertex]);
			curr_vertex_ptr = curr_vertex_ptr->next;
		}
		printf("\n");
		curr_list_ptr = curr_list_ptr->next;
		i++;
	}
	//printf("i:%d\n", i);
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

void	print_2d_array(int **array, int size)
{
	printf("\nprint 2d array:\n\n");
	for (int u = 0; u < size; ++u)
	{
		for (int v = 0; v < size; ++v)
			printf("%d ", array[u][v]);
		printf("\n");
	}
}

void	print_array(int *array, int size)
{
	for (int u = 0; u < size; ++u)
		printf("%d ", array[u]);
	printf("\n\n");
}
