#include "../../../includes/lem-in.h"

void	multishot_add_one_path(t_route *route, t_list **path, t_graph_vertex *src, t_graph_vertex *des)
{
	t_graph_vertex	*v;
	t_graph_edge	*e;
	int	i;
	int	every = 1;
	int	size;

	v = src;
	e = NULL;
	ft_lstadd_back(path, ft_lstnew(v));
	while (v->vertex != des->vertex)
	{
		i = 0;
		size = ft_lstsize(v->in_list);
		//printf("size:%d, v->vertex:%d, des->vertex:%d\n", size, v->vertex, des->vertex);
		if (route->flags.debug)
			multishot_print_edges(route, v->in_list, FORWARD_PRINT);
		while (i < size)
		{
			if (route->flags.debug)
				printf("i:%d < size:%d\n", i, size);
			e  = (t_graph_edge*)ft_lstfind_node(v->in_list, i)->content;
			if (e->flow > 0)
			{
				if (route->flags.debug)
					printf("e->u->vertex:%d-e->v->vertex:%d' flow:%d, break;\n", e->u->vertex, e->v->vertex, e->flow);
				break;
			}
			i++;
		}
		if (every++ % 2 == 0)
		{
			//printf("adding e->u->vertex:%d\n",e->u->vertex);
			if (route->flags.debug)
				printf("%sadding e->u->vertex:%s%s\n", GREEN, FIN, route->node_map[e->u->vertex]);
			ft_lstadd_back(path, ft_lstnew(e->u));
		}
		if (route->flags.debug)
			printf("v = e->u:%d\n",e->u->vertex);
		v = e->u;
	}
}


t_list	*multishot_add_all_paths(t_route *route, t_graph_vertex *start, t_graph_vertex *end)
{
	(void)route;
	t_list	*paths;
	t_list	*path;
	t_graph_edge *adj_edge;
	int	i = 0;
	int	size;

	paths = NULL;
	path = NULL;
	size = ft_lstsize(end->in_list);

	while (i < size)
	{
		adj_edge = (t_graph_edge*)ft_lstfind_node(end->in_list, i)->content;
		//printf("adj_edge->u->vertex:%d\n", adj_edge->u->vertex);
		if (adj_edge->flow > 0)
		{
			ft_lstadd_back(&path, ft_lstnew(end));
			multishot_add_one_path(route, &path, adj_edge->u, start);
			//multishot_print_all_paths(paths);
			if (route->flags.debug)
			{
				printf("selected current path:\n");
				multishot_print_one_path(route, path, 1);
			}
			ft_lstadd_back(&paths, ft_lstnew(path));
			path = NULL;
			if (route->flags.debug)
				printf("\t\t\t\t\t paths size:%d\n", ft_lstsize(paths));
		}
		i++;
	}
	return paths;
}


t_list	*multishot_edmonds_karp(t_route *route)
{
	t_list	*edge_list;
	t_list	*paths;
	t_list	*prev_paths;
	t_graph_vertex *s;
	t_graph_vertex *t;

	paths = NULL;
	prev_paths = NULL;
	s = multishot_find_vertex(route->graph, route->start, OUT);
	t = multishot_find_vertex(route->graph, route->end, IN);
	while (1)
	{
		edge_list = multishot_bfs(route, s, t);
		if (route->flags.debug)
			printf("edge_list->size:%d\n", ft_lstsize(edge_list));
		if (ft_lstsize(edge_list) == 0 || !multishot_update_edge_flow(route, edge_list, route->end))
			break ;
		paths = multishot_add_all_paths(route, s, t);
		multishot_print_all_paths(route, paths, SIZE_PRINT);
		printf("\t\tmax flow path:%d\n", ft_lstsize(paths));
		prev_paths = paths;
		(void)paths;
	}
	return prev_paths;
}
