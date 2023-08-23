#include "../../includes/lem-in.h"

const char* sVertexTypeStrings[] = {
	"IN",
	"OUT",
};

void	set_all_vertices_valid(t_route *route, bool valid)
{
	t_list			*curr_ptr;

	curr_ptr = route->graph->v_out_list;
	while (curr_ptr != NULL)
	{
		((t_graph_vertex*)curr_ptr->content)->valid = valid;
		curr_ptr = curr_ptr->next;
	}
	curr_ptr = route->graph->v_in_list;
	while (curr_ptr != NULL)
	{
		((t_graph_vertex*)curr_ptr->content)->valid = valid;
		curr_ptr = curr_ptr->next;
	}
}

void	reset_int_array(int **arr, int length, int value)
{
	for (int i = 0; i < length; i++)
		(*arr)[i] = value;
}

void	init_int_array(int **arr, int length, int value)
{
	*arr = (int *)malloc(sizeof(int) * (length));
	reset_int_array(arr, length, value);
}

void	init_vertex_list(t_vertex_list *path, int v)
{
	path->vertex = v;
	path->length = 0;
	path->next = NULL;
	path->prev = NULL;
}

void	init_paths(t_paths* paths)
{
	paths->paths = NULL;
	paths->num_paths = 0;
	paths->dist_begin = -1;
	paths->loop_len = -1;
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
	route->graph->v_in_list = NULL;
	route->graph->v_out_list = NULL;
	route->distances = (int*)malloc(sizeof(int) * (route->num_vertices + 1));
	route->start = 0;
	route->end = route->num_vertices - 1;

	route->oneshot_paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->oneshot_paths);
	route->multishot_paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->multishot_paths);

	route->flags.debug = 0;
}
