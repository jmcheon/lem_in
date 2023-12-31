#include "../../includes/lem-in.h"

const char* sVertexTypeStrings[] = {
	"IN",
	"OUT",
};

void	set_all_vertices_valid(t_route *route, bool valid)
{
	t_list			*out_ptr;
	t_list			*in_ptr;

	out_ptr = route->graph->v_out_list;
	in_ptr = route->graph->v_in_list;
	for (int i = 0; i < route->num_vertices; i++)
	{
		((t_graph_vertex*)out_ptr->content)->valid = valid;
		out_ptr = out_ptr->next;
		((t_graph_vertex*)in_ptr->content)->valid = valid;
		in_ptr = in_ptr->next;
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

void	init_2d_int_array(int ***arr, int length)
{
	int i = 0;

	*arr = (int **)malloc(sizeof(int) * (length + 1));
	while (i < length)
	{
		(*arr)[i] = (int *)malloc(sizeof(int) * (length + 1));
		for (int j = 0; j <= length; j++)
			(*arr)[i][j] = '\0';
		i++;
	}
	(*arr)[i] = NULL;
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
	if (parse->req > 0)
		route->req = parse->req;
	else
		route->req = -1;
	route->num_ants = parse->num_ants;
	route->num_vertices = ft_lstsize(parse->nodes_head);
	route->node_map = node_map_to_array(parse->nodes_head);
	route->graph = parse_to_graph(parse, route);
	if (route->graph == NULL)
	{
		ft_lstclear(&parse->nodes_head, free_node_xy);
		ft_lstclear(&parse->edge_info_head, free_edge);
		free(route->node_map);
		free(parse);
		exit(1);
	}
	route->graph->v_in_list = NULL;
	route->graph->v_out_list = NULL;
	route->graph->edge_list = NULL;
	route->graph->rev_edge_list = NULL;
	route->distances = (int*)malloc(sizeof(int) * (route->num_vertices + 1));
	route->start = 0;
	route->end = route->num_vertices - 1;

	route->oneshot_paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->oneshot_paths);
	route->multishot_paths = (t_paths*)malloc(sizeof(t_paths));
	init_paths(route->multishot_paths);

	route->flags.debug = 0;
}
