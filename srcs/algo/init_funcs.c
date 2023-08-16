#include "../../includes/lem-in.h"

void	init_vertex_list(t_vertex_list *path, int v)
{
	path->vertex = v;
	path->length = 0;
	path->next = NULL;
	path->prev = NULL;
}

void	init_paths(t_paths* paths)
{
	//paths->paths = ft_lstnew(NULL);
	paths->paths = NULL;
	paths->num_paths = 0;
}

void	init_route(t_route* route, t_parse* parse)
{
	route->num_ants = parse->num_ants;
	route->num_vertices = ft_lstsize(parse->nodes_head);
	//printf("num_vertices:%d\n", route->num_vertices);
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
		exit(1);
	}
	route->distances = (int*)malloc(sizeof(int) * (route->num_vertices + 1));
	route->start = 0;
	route->end = route->num_vertices - 1;

	route->paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->paths);
}
