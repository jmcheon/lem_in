#include "../../../includes/lem-in.h"

t_vertex_list	*multishot_add_one_path(t_route *route, t_graph_vertex *src, t_graph_vertex *des)
{
	t_graph_vertex	*v;
	t_graph_edge	*e;
	t_vertex_list	*curr_vertex_ptr;
	int	i;
	int	every = 1;
	int	size;

	v = src;
	e = NULL;
	curr_vertex_ptr = insert_vertex(route->multishot_paths, v->vertex);
	while (v->vertex != des->vertex)
	{
		i = 0;
		size = ft_lstsize(v->in_list);
		while (i < size)
		{
			e  = (t_graph_edge*)ft_lstfind_node(v->in_list, i)->content;
			if (e->flow > 0)
				break;
			i++;
		}
		if (every++ % 2 == 0)
			curr_vertex_ptr = insert_vertex(route->multishot_paths, e->u->vertex);
		v = e->u;
	}
	return curr_vertex_ptr;
}


void	multishot_add_all_paths(t_route *route, t_graph_vertex *start, t_graph_vertex *end)
{
	t_graph_edge 	*adj_edge;
	t_vertex_list	*end_vertex_ptr;
	t_vertex_list	*start_vertex_ptr;
	int	i = 0;
	int	size;

	size = ft_lstsize(end->in_list);

	if (route->multishot_paths->paths != NULL)
	{
		free_paths(route->multishot_paths->paths);
		init_paths(route->multishot_paths);
	}
	while (i < size)
	{
		adj_edge = (t_graph_edge*)ft_lstfind_node(end->in_list, i)->content;
		if (adj_edge->flow > 0)
		{
			end_vertex_ptr = insert_vertex(route->multishot_paths, end->vertex);
			start_vertex_ptr = multishot_add_one_path(route, adj_edge->u, start);
			start_vertex_ptr->next = end_vertex_ptr;
			end_vertex_ptr->prev = start_vertex_ptr;
			route->multishot_paths->num_paths++;
		}
		i++;
	}
}


void	multishot_edmonds_karp(t_route *route)
{
	t_list	*edge_list;
	t_graph_vertex *s;
	t_graph_vertex *t;
	int	prev_path_len;
	int	path_len;

	s = multishot_find_vertex(route->graph, route->start, OUT);
	t = multishot_find_vertex(route->graph, route->end, IN);
	prev_path_len = 0;
	while (1)
	{
		edge_list = multishot_bfs(route, s, t);
		if (ft_lstsize(edge_list) == 0 || !multishot_update_edge_flow(route, edge_list, route->end))
			break ;
		multishot_add_all_paths(route, s, t);
		path_len = ants_check_loop_len(route, route->multishot_paths);
		if (prev_path_len != 0 && (path_len < route->req))
		{
			route->multishot_paths->loop_len = path_len - 1;
			free_list_ptr(edge_list);
			return;
		}
		else if (prev_path_len != 0 &&  prev_path_len < path_len)
			break;
		prev_path_len = path_len;
		free_list_ptr(edge_list);
	}
	free_list_ptr(edge_list);
	route->multishot_paths->loop_len = prev_path_len - 1;
}

