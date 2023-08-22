#include "../../includes/lem-in.h"

void	print_edge_forward_travel(t_route *route)
{
	t_graph_edge	*e;

	//e = graph_find_edge(route->graph, route->start, route->graph->adj_list[0]->vertex, 0);
	//e = graph_find_edge(route->graph, route->start, 0, 1);
	//printf("%d\n", route->graph->adj_list[0]->vertex);
	//while (v->vertex != route->end)
	{
		//printf("e->v->vertex:%d\n", e->v->vertex);
		//printf("e->u->vertex:%d\n", e->u->vertex);
		//v = e->v;
	}
	for (int i = 0; i < route->num_vertices; i++)
	{
		for (int j = 0; j < route->num_vertices; j++)
		{
			e = graph_find_edge(route->graph, i, j, 1);
			if (e != NULL)
			{
				//printf("(e->u->vertex, e->v->vertex): (%d, %d)\n", e->u->vertex, e->v->vertex);
				printf("(e->u->vertex, e->v->vertex): (%s_%s, %s_%s) %d, %d\n", 
					route->node_map[e->u->vertex], sVertexTypeStrings[e->u->type], 
					route->node_map[e->v->vertex], sVertexTypeStrings[e->v->type], 
					e->u->valid, e->v->valid);
			}
		}
		printf("\n");
	}
}

void	print_vertex_lists(t_route *route)
{
	t_graph_vertex	*v;

	/*
	v = graph_find_vertex(route->graph, route->start, 0);
	printf("v->vertex:%d\n", v->vertex);

	//printf("v->in_list:%d\n", ((t_graph_vertex*)v->in_list->content)->vertex);
	print_one_path(v->in_list);
	print_one_path(v->out_list);
	printf("\n%d_in\n", v->vertex);
	print_edges(route, v->in_list);
	*/
	for (int i = 0; i < route->num_vertices; i++)
	{
		v = graph_find_vertex(route->graph, i, 0);
		//printf("\n%d_in\n", v->vertex);
		printf("\n\n\n%s_in->in\n", route->node_map[v->vertex]);
		print_edges(route, v->in_list, REVERSE_PRINT);
		printf("%s_in->out\n", route->node_map[v->vertex]);
		print_edges(route, v->out_list, REVERSE_PRINT);

		v = graph_find_vertex(route->graph, i, 1);
		//printf("%d_out\n", v->vertex);
		printf("\n%s_out->in\n", route->node_map[v->vertex]);
		print_edges(route, v->in_list, REVERSE_PRINT);
		printf("%s_out->out\n", route->node_map[v->vertex]);
		print_edges(route, v->out_list, REVERSE_PRINT);
	}
}

void	print_edge(t_route *route, void *data)
{
	t_graph_edge	*temp;
	t_edge_attr		*attr;

	temp = data;
	attr = temp->attr;
	printf("[%d]:%s_%s -> [%d]:%s_%s\t valid = %d, flow = %d, capacity = %d\n",
		temp->u->vertex, route->node_map[temp->u->vertex], sVertexTypeStrings[temp->u->type], 
		temp->v->vertex, route->node_map[temp->v->vertex], sVertexTypeStrings[temp->v->type],
		temp->valid, attr->flow, attr->capacity);
}


void	print_edges(t_route *route, t_list *lst, int reverse)
{
	int	size;

	size = ft_lstsize(lst);
	printf("%sStart printing connected edges... size:%s%d\n", BLUE, FIN, size);

	for (int i = 0; i < size; i++)
	{
		print_edge(route, ft_lstfind_node(lst, i)->content);
	}

	if (reverse)
	{
		printf("%s========================reverse edge=======================%s\n", YELLOW, FIN);
		for (int j = 0; j < size; j++)
		{
			print_edge(route, ((t_edge_attr*)((t_graph_edge*)ft_lstfind_node(lst, j)->content)->attr)->reverse_edge);
		}
	}
	printf("\n");
}

void	print_all_paths(t_route *route, t_list *paths)
{
	t_list	*path;

	while (paths != NULL)
	{
		path = (t_list*)paths->content;
		print_one_path(route, path);
		paths = paths->next;
	}
}

void	print_one_path(t_route *route, t_list *path)
{
	int	path_size;

	path_size = ft_lstsize(path);
	printf("path_size:%d\n", path_size);
	while (path != NULL)
	{
		if (path->next)
			//printf("%d -> ", ((t_graph_vertex*)path->content)->vertex);
			printf("%s -> ", route->node_map[((t_graph_vertex*)path->content)->vertex]);
		else
			//printf("%d\n", ((t_graph_vertex*)path->content)->vertex);
			printf("%s\n", route->node_map[((t_graph_vertex*)path->content)->vertex]);
		path = path->next;
	}
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
