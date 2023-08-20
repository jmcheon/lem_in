#include "../../includes/lem-in.h"

int	parr_add_back(t_parray *arr, void *data)
{
	if (!arr)
		return -1;
	ft_lstadd_back(&arr->data_list, ft_lstnew(data));
	arr->len++;
	return 1;
}

t_graph_edge *graph_find_edge(t_graph *g, int u, int v)
{
	t_graph_vertex *vertex;
	t_graph_edge *out;
	int	i = 0;

	vertex = graph_find_vertex(g, u);
	while (i < vertex->out.len)
	{
		out = (t_graph_edge*)ft_lstfind_node(vertex->out.data_list, i)->content;
		if (out->v->vertex == v)
			return (out);
		i++;
	}
	return NULL;
}

int	graph_add_edge(t_graph *g, int u, int v, void *attr)
{
	t_graph_edge *edge;
	t_graph_vertex *in_vertex;
	t_graph_vertex *out_vertex;

	edge = (t_graph_edge*)malloc(sizeof(t_graph_edge));

	if (!edge)
		return -1;
	in_vertex = graph_find_vertex(g, u);
	out_vertex = graph_find_vertex(g, v);

	if (!in_vertex || !out_vertex)
	{
		printf("adding an edge error.\n");
		free(edge);
		return -1;
	}
	edge->u = in_vertex;
	edge->v = out_vertex;
	//edge->valid = True;
	edge->attr = attr;
	parr_add_back(&in_vertex->out, edge);
	parr_add_back(&out_vertex->in, edge);
	return 1;
}

t_edge_attr *init_edge_attr(int capacity)
{
	t_edge_attr *attr;

	attr = (t_edge_attr*)malloc(sizeof(t_edge_attr));
	if (!attr)
		return NULL;
	attr->flow = 0;
	attr->capacity = capacity;
	attr->reverse_edge = NULL;
	return attr;
}

int	add_edges(t_graph *g, int u, int v)
{
	t_edge_attr *edge_attr;
	t_edge_attr *rev_edge_attr;
	t_graph_vertex *out_vertex;
	t_graph_vertex *in_vertex;
	t_graph_edge *rev_edge;


	out_vertex = graph_find_vertex(g, u);
	in_vertex = graph_find_vertex(g, v);

	edge_attr = init_edge_attr(1);
	rev_edge_attr = init_edge_attr(0);
	if (!edge_attr || !rev_edge_attr)
		return -1;
	if (graph_add_edge(g, out_vertex->vertex, in_vertex->vertex, edge_attr) == -1
		|| graph_add_edge(g, in_vertex->vertex, out_vertex->vertex, rev_edge_attr) == -1)
		return -1;
	rev_edge = graph_find_edge(g, v, u);
	rev_edge->valid = false;
	edge_attr->reverse_edge = graph_find_edge(g, v, u);
	edge_attr->reverse_edge->valid = false;
	rev_edge_attr->reverse_edge = graph_find_edge(g, u, v);
	return 1;
}

t_graph_edge *get_edge(t_graph_vertex *src, t_graph_vertex *des)
{
	t_graph_edge *edge;
	int	i = 0;

	while (i < src->out.len)
	{
		edge = (t_graph_edge*)ft_lstfind_node(src->out.data_list, i)->content;
		if (edge->v->vertex == des->vertex)
			return edge;
		i++;
	}
	return NULL;
}

void	split_edge(t_graph *g, t_graph_vertex *vertex, int v)
{
	(void)v;
	t_graph_edge *edge;
	int i = 0;

	while (i < vertex->in.len)
	{

		i++;
		edge = (t_graph_edge*)ft_lstfind_node(vertex->in.data_list, i)->content;
		add_edges(g, edge->u->vertex, edge->v->vertex);
	}
}

int	update_edge_flow(t_parray *edge_list, int v)
{
	t_parray *path;

	path = graph_edge_backtrack(edge_list, v);
	if (!path)
		return 0;
	free(path);
	return 1;
}

int	update_edge(t_graph_edge *edge)
{
	t_graph_edge *rev_edge;

	((t_edge_attr*)edge->attr)->flow += 1;
	rev_edge = get_edge(edge->v, edge->u);
	((t_edge_attr*)rev_edge->attr)->flow -= 1;
	if (((t_edge_attr*)edge->attr)->flow < ((t_edge_attr*)edge->attr)->capacity)
		edge->valid = 1;
	else
		edge->valid = 0;
	if (((t_edge_attr*)rev_edge->attr)->flow < ((t_edge_attr*)rev_edge->attr)->capacity)
		rev_edge->valid = 1;
	else
		rev_edge->valid = 0;
	return 1;
}

t_parray	*save_max_flow_paths(t_graph_vertex *start, t_graph_vertex *end, int max_flow)
{
	(void)start;
	(void)end;
	(void)max_flow;
	t_parray *paths;
	t_parray *path;
	t_graph_edge *adj_edge;
	int	i = 0;

	(void)paths;
	(void)path;
	//parr_init(path);
	while (i < end->in.len)
	{
		adj_edge = (t_graph_edge*)ft_lstfind_node(end->in.data_list, i)->content;
		if (((t_edge_attr*)adj_edge->attr)->flow > 0)
		{
			//ft_lstadd_back(&path->data_list, ft_lstnew(((t_vertex_attr*)end->attr)->org));
		}
		i++;
	}
	return NULL;
	//return paths;
}

t_parray *graph_edge_backtrack(t_parray *edges, int v)
{
	t_parray *path;
	t_graph_vertex *vertex;
	t_graph_edge *edge;
	int	i;

	edge = (t_graph_edge*)ft_lstlast(edges->data_list)->content;
	if (v != edge->v->vertex || !update_edge(edge))
		return NULL;
	path = (t_parray*)malloc(sizeof(t_parray) * edges->len);
	vertex = edge->u;
	ft_lstadd_back(&path->data_list, ft_lstnew(edge->u));
	ft_lstadd_back(&path->data_list, ft_lstnew(edge->v));
	i = edges->len;
	while (i--)
	{
		edge = (t_graph_edge*)ft_lstfind_node(edges->data_list, i)->content;
		if (edge->v->vertex == vertex->vertex)
		{
			if (update_edge(edge) < 0)
				return path;
			ft_lstadd_front(&path->data_list, ft_lstnew(edge->u));
			vertex = edge->u;
		}
	}
	return path;
}
