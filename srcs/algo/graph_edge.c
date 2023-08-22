#include "../../includes/lem-in.h"

/*
int	parr_add_back(t_parray *arr, void *data)
{
	if (!arr)
		return -1;
	ft_lstadd_back(&arr->data_list, ft_lstnew(data));

	//printf("\nv:%d\n", ((t_graph_edge*)arr->data_list->content)->u->vertex);
	arr->len++;
	return 1;
}
*/
t_graph_edge *graph_find_edge(t_graph *g, int u, int v, int u_in)
{
	t_graph_vertex *vertex;
	t_graph_edge *out;
	int	i = 0;
	int	size;

	vertex = graph_find_vertex(g, u, u_in);
	//while (i < vertex->out.len)
	size = ft_lstsize(vertex->out_list);
	while (i < size)
	{
		//out = (t_graph_edge*)ft_lstfind_node(vertex->out.data_list, i)->content;
		out = (t_graph_edge*)ft_lstfind_node(vertex->out_list, i)->content;
		if (out->v->vertex == v)
			return (out);
		i++;
	}
	return NULL;
}

int	graph_add_edge(t_graph *g, int u_vertex, int v_vertex, int u_in, int v_in, void *attr)
{
	t_graph_edge *edge;
	t_graph_vertex *u;
	t_graph_vertex *v;

	edge = (t_graph_edge*)malloc(sizeof(t_graph_edge));

	if (!edge)
		return -1;
	//printf("graph add edge, u_vertex:%d, v_vertex:%d\n", u_vertex, v_vertex);
	v = graph_find_vertex(g, u_vertex, u_in);
	u = graph_find_vertex(g, v_vertex, v_in);

	if (!u || !v)
	{
		printf("adding an edge error.\n");
		free(edge);
		return -1;
	}
	edge->u = u;
	edge->v = v;
	//printf("adding edge->u->vertex:%d, valid:%d\n", edge->u->vertex, edge->u->valid);
	//printf("adding edge->v->vertex:%d, valid:%d\n", edge->v->vertex, edge->v->valid);
	edge->valid = true;
	edge->attr = attr;
	//parr_add_back(&u->out, edge);
	//printf("parr add back\n");
	//parr_add_back(&v->in, edge);
	//printf("v->in.len:%d\n", v->in.len);
	ft_lstadd_back(&u->out_list, ft_lstnew(edge));
	ft_lstadd_back(&v->in_list, ft_lstnew(edge));
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

int	add_edges(t_graph *g, int u, int v, int u_in, int v_in)
{
	t_edge_attr *edge_attr;
	t_edge_attr *rev_edge_attr;
	t_graph_vertex *src;
	t_graph_vertex *des;
	t_graph_edge *rev_edge;

	//printf("add_edges u:%d, v:%d\n", u, v);
	src = graph_find_vertex(g, u, u_in);
	des = graph_find_vertex(g, v, v_in);

	/*
	if (src == NULL)
		printf("src == null\n");
	else
		printf("src->vertex:%d\n", src->vertex);
	if (des== NULL)
		printf("des == null\n");
	else
		printf("des->vertex:%d\n", des->vertex);
	*/

	edge_attr = init_edge_attr(1);
	rev_edge_attr = init_edge_attr(0);
	if (!edge_attr || !rev_edge_attr)
		return -1;
	if (graph_add_edge(g, src->vertex, des->vertex, u_in, v_in, edge_attr) == -1
		|| graph_add_edge(g, des->vertex, src->vertex, v_in, u_in, rev_edge_attr) == -1)
		return -1;
	rev_edge = graph_find_edge(g, u, v, u_in);
	/*
	if (!rev_edge)
		printf("\t rev edge found\n");
	else
		printf("\t rev edge not found\n");
	*/
	rev_edge->valid = false;


	edge_attr->reverse_edge = graph_find_edge(g, u, v, u_in);
	edge_attr->reverse_edge->valid = false;
	rev_edge_attr->reverse_edge = graph_find_edge(g, v, u, v_in);
	//printf("fini adding edges\n");
	return 1;
}

t_graph_edge *get_edge(t_graph_vertex *src, t_graph_vertex *des)
{
	t_graph_edge *edge;
	int	i = 0;
	int	size;

	size = ft_lstsize(src->out_list);
	//while (i < src->out.len)
	while (i < size)
	{
		//edge = (t_graph_edge*)ft_lstfind_node(src->out.data_list, i)->content;
		edge = (t_graph_edge*)ft_lstfind_node(src->out_list, i)->content;
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
	int	size;

	(void)edge;
	(void)g;
	size = ft_lstsize(vertex->in_list);
	//while (i < vertex->in.len)
	while (i < size)
	{

		i++;
		//edge = (t_graph_edge*)ft_lstfind_node(vertex->in.data_list, i)->content;
		edge = (t_graph_edge*)ft_lstfind_node(vertex->in_list, i)->content;
		//add_edges(g, edge->u->vertex, edge->v->vertex);
	}
}

int	update_edge_flow(t_list *edge_list, int v)
{
	t_list *path;

	path = graph_edge_backtrack(edge_list, v);
	printf("\t\tbacktracking return\n");
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


void	save_flow_path(t_list **path, t_graph_vertex *src, t_graph_vertex *des)
{
	t_graph_vertex	*v;
	t_graph_edge	*e;
	int	i;
	int	every = 1;
	int	size;

	v = src;
	e = NULL;
	ft_lstadd_back(path, ft_lstnew(src));
	while (v->vertex != des->vertex)
	{
		i = 0;
		size = ft_lstsize(v->in_list);
		//printf("size:%d, v->vertex:%d, des->vertex:%d\n", size, v->vertex, des->vertex);
		while (i < size)
		{
			//printf("i:%d < size:%d\n", i, size);
			e  = (t_graph_edge*)ft_lstfind_node(v->in_list, i)->content;
			//printf("e->flow:%d\n", ((t_edge_attr*)e->attr)->flow);
			if (((t_edge_attr*)e->attr)->flow > 0)
			{
				//printf("break;\n");
				break;
			}
			//printf("ef\n");
			i++;
		}
		if (every++ % 2 == 0)
		{
			//printf("adding e->u to path\n");
			//printf("adding e->u->vertex:%d\n",e->u->vertex);
			ft_lstadd_back(path, ft_lstnew(e->u));
		}
		//printf("e->u->vertex:%d\n",e->u->vertex);
		//printf("src = e->u\n");
		v = e->u;
	}
}


t_list	*save_max_flow_paths(t_graph_vertex *start, t_graph_vertex *end, int max_flow)
{
	(void)max_flow;
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
		if (((t_edge_attr*)adj_edge->attr)->flow > 0)
		{
			//ft_lstadd_back(&path->data_list, ft_lstnew(((t_vertex_attr*)end->attr)->org));
			ft_lstadd_back(&path, ft_lstnew(end));
			save_flow_path(&path, adj_edge->u, start);
			//print_all_paths(paths);
			//print_one_path(path);
			ft_lstadd_back(&paths, ft_lstnew(path));
			path = NULL;
			printf("\t\t\t\t\t paths size:%d\n", ft_lstsize(paths));
		}
		i++;
	}
	//return NULL;
	return paths;
}

t_list *graph_edge_backtrack(t_list *edges, int v)
{
	t_list *path;
	t_graph_vertex *vertex;
	t_graph_edge *edge;
	int	i;

	printf("\t\tbacktracking\n");
	edge = (t_graph_edge*)ft_lstlast(edges)->content;
	if (v != edge->v->vertex || !update_edge(edge))
		return NULL;
	vertex = edge->u;
	path = NULL;
	ft_lstadd_back(&path, ft_lstnew(edge->u));
	ft_lstadd_back(&path, ft_lstnew(edge->v));
	printf("\t\tbacktracking test\n");
	i = ft_lstsize(edges);
	while (i--)
	{
		edge = (t_graph_edge*)ft_lstfind_node(edges, i)->content;
		if (edge->v->vertex == vertex->vertex)
		{
			if (update_edge(edge) < 0)
				return path;
			ft_lstadd_front(&path, ft_lstnew(edge->u));
			vertex = edge->u;
		}
	}
	return path;
}
