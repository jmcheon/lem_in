#include "../../../includes/lem-in.h"

t_graph_edge *multishot_find_edge(t_graph *g, int u, int v, int u_in)
{
	t_graph_vertex *vertex;
	t_graph_edge *out;
	int	i = 0;
	int	size;

	vertex = multishot_find_vertex(g, u, u_in);
	size = ft_lstsize(vertex->out_list);
	while (i < size)
	{
		out = (t_graph_edge*)ft_lstfind_node(vertex->out_list, i)->content;
		if (out->v->vertex == v)
			return (out);
		i++;
	}
	return NULL;
}

t_graph_edge	*multishot_init_edge(t_graph *g, int u_vertex, int v_vertex, int u_in, int v_in, int capacity)
{
	t_graph_edge *edge;
	t_graph_vertex *u;
	t_graph_vertex *v;

	edge = (t_graph_edge*)malloc(sizeof(t_graph_edge));

	if (!edge)
		return NULL;
	v = multishot_find_vertex(g, u_vertex, u_in);
	u = multishot_find_vertex(g, v_vertex, v_in);

	if (!u || !v)
	{
		ft_putstr_fd("adding an edge error.\n", STDOUT_FILENO);
		free(edge);
		return NULL;
	}
	edge->u = u;
	edge->v = v;
	edge->valid = true;
	edge->flow = 0;
	edge->capacity = capacity;
	edge->reverse_edge = NULL;
	ft_lstadd_back(&u->out_list, ft_lstnew(edge));
	ft_lstadd_back(&v->in_list, ft_lstnew(edge));
	return edge;
}

int	multishot_add_edges(t_graph *g, int u_vertex, int v_vertex, int u_in, int v_in)
{
	t_graph_vertex *u;
	t_graph_vertex *v;
	t_graph_edge *rev_edge;
	t_graph_edge *edge;

	u = multishot_find_vertex(g, u_vertex, u_in);
	v = multishot_find_vertex(g, v_vertex, v_in);

	edge = multishot_init_edge(g, u->vertex, v->vertex, u_in, v_in, 1);
	rev_edge = multishot_init_edge(g, v->vertex, u->vertex, v_in, u_in, 0);
	if (edge == NULL || rev_edge == NULL)
		return -1;

	rev_edge = multishot_find_edge(g, u_vertex, v_vertex, u_in);
	rev_edge->valid = false;

	edge->reverse_edge = rev_edge;
	edge->reverse_edge->valid = false;
	rev_edge->reverse_edge = edge;
	ft_lstadd_back(&g->edge_list, ft_lstnew(edge));
	ft_lstadd_back(&g->rev_edge_list, ft_lstnew(rev_edge));
	return 1;
}

t_graph_edge *multishot_get_edge(t_graph_vertex *src, t_graph_vertex *des)
{
	t_graph_edge *edge;
	int	i = 0;
	int	size;

	size = ft_lstsize(src->out_list);
	while (i < size)
	{
		edge = (t_graph_edge*)ft_lstfind_node(src->out_list, i)->content;
		if (edge->v->vertex == des->vertex)
			return edge;
		i++;
	}
	return NULL;
}

int	multishot_update_edge_flow(t_route *route, t_list *edge_list, int v)
{
	t_list *path;

	path = multishot_backtrack_edges(route, edge_list, v);
	if (!path)
		return 0;
	free_list_ptr(path);

	return 1;
}

int	multishot_update_edge(t_route *route, t_graph_edge *edge)
{
	t_graph_edge *rev_edge;

	(void)route;
	edge->flow += 1;
	rev_edge = multishot_get_edge(edge->v, edge->u);

	rev_edge->flow -= 1;
	if (edge->flow < edge->capacity)
		edge->valid = 1;
	else
		edge->valid = 0;
	if (rev_edge->flow < rev_edge->capacity)
		rev_edge->valid = 1;
	else
		rev_edge->valid = 0;
	return 1;
}


t_list *multishot_backtrack_edges(t_route *route, t_list *edges, int v)
{
	t_list *path;
	t_graph_vertex *vertex;
	t_graph_edge *edge;
	int	i;

	edge = (t_graph_edge*)ft_lstlast(edges)->content;

	if (v != edge->v->vertex || !multishot_update_edge(route, edge))
		return NULL;
	vertex = edge->u;
	path = NULL;
	ft_lstadd_back(&path, ft_lstnew(edge->u));
	ft_lstadd_back(&path, ft_lstnew(edge->v));
	i = ft_lstsize(edges);

	while (i--)
	{
		edge = (t_graph_edge*)ft_lstfind_node(edges, i)->content;
	
		if (edge->v->vertex == vertex->vertex && edge->v->type == vertex->type)
		{
			if (multishot_update_edge(route, edge) < 0)
				return path;
			ft_lstadd_front(&path, ft_lstnew(edge->u));
			vertex = edge->u;
		}
	}
	return path;
}
