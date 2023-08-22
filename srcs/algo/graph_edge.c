#include "../../includes/lem-in.h"

t_graph_edge *graph_find_edge(t_graph *g, int u, int v, int u_in)
{
	t_graph_vertex *vertex;
	t_graph_edge *out;
	int	i = 0;
	int	size;

	vertex = graph_find_vertex(g, u, u_in);
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

t_graph_edge	*graph_add_edge(t_graph *g, int u_vertex, int v_vertex, int u_in, int v_in, int capacity)
{
	t_graph_edge *edge;
	t_graph_vertex *u;
	t_graph_vertex *v;

	edge = (t_graph_edge*)malloc(sizeof(t_graph_edge));

	if (!edge)
		return NULL;
		//return -1;
	//printf("graph add edge, u_vertex:%d, v_vertex:%d\n", u_vertex, v_vertex);
	v = graph_find_vertex(g, u_vertex, u_in);
	u = graph_find_vertex(g, v_vertex, v_in);

	if (!u || !v)
	{
		printf("adding an edge error.\n");
		free(edge);
		return NULL;
		//return -1;
	}
	edge->u = u;
	edge->v = v;
	//printf("adding edge->u->vertex:%d, valid:%d\n", edge->u->vertex, edge->u->valid);
	//printf("adding edge->v->vertex:%d, valid:%d\n", edge->v->vertex, edge->v->valid);
	edge->valid = true;
	edge->flow = 0;
	edge->capacity = capacity;
	edge->reverse_edge = NULL;
	ft_lstadd_back(&u->out_list, ft_lstnew(edge));
	ft_lstadd_back(&v->in_list, ft_lstnew(edge));
	//return 1;
	return edge;
}

int	add_edges(t_graph *g, int u, int v, int u_in, int v_in)
{
	t_graph_vertex *src;
	t_graph_vertex *des;
	t_graph_edge *rev_edge;
	t_graph_edge *edge;

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
	edge = graph_add_edge(g, src->vertex, des->vertex, u_in, v_in, 1);
	rev_edge = graph_add_edge(g, des->vertex, src->vertex, v_in, u_in, 0);
	if (edge == NULL || rev_edge == NULL)
		return -1;

	rev_edge = graph_find_edge(g, u, v, u_in);
	/*
	if (!rev_edge)
		printf("\t rev edge found\n");
	else
		printf("\t rev edge not found\n");
	*/
	rev_edge->valid = false;


	edge->reverse_edge = rev_edge;//graph_find_edge(g, u, v, u_in);
	edge->reverse_edge->valid = false;
	rev_edge->reverse_edge = edge;//graph_find_edge(g, v, u, v_in);
	//printf("fini adding edges\n");
	return 1;
}

t_graph_edge *get_edge(t_graph_vertex *src, t_graph_vertex *des)
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

int	update_edge_flow(t_route *route, t_list *edge_list, int v)
{
	t_list *path;

	path = graph_edge_backtrack(route, edge_list, v);
	if (route->flags.debug)
		printf("\t\tbacktracking return\n");
	if (!path)
		return 0;
	free(path);

	return 1;
}

int	update_edge(t_route *route, t_graph_edge *edge)
{
	t_graph_edge *rev_edge;

	(void)route;
	//print_edge(route, );
	edge->flow += 1;
	rev_edge = get_edge(edge->v, edge->u);
	if (route->flags.debug)
	{
		printf("rev_e->u->vertex:%s_%s - rev_e->v->vertex:%s_%s\n", 
			route->node_map[rev_edge->u->vertex], sVertexTypeStrings[rev_edge->u->type], 
			route->node_map[rev_edge->v->vertex], sVertexTypeStrings[rev_edge->v->type]);
	}
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


void	save_flow_path(t_route *route, t_list **path, t_graph_vertex *src, t_graph_vertex *des)
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
			print_edges(route, v->in_list, FORWARD_PRINT);
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


t_list	*save_max_flow_paths(t_route *route, t_graph_vertex *start, t_graph_vertex *end, int max_flow)
{
	(void)max_flow;
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
			save_flow_path(route, &path, adj_edge->u, start);
			//print_all_paths(paths);
			if (route->flags.debug)
			{
				printf("selected current path:\n");
				print_one_path(route, path);
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

t_list *graph_edge_backtrack(t_route *route, t_list *edges, int v)
{
	t_list *path;
	t_graph_vertex *vertex;
	t_graph_edge *edge;
	int	i;

	//printf("\t\tbacktracking\n");
	edge = (t_graph_edge*)ft_lstlast(edges)->content;
	if (route->flags.debug)
	{
		printf("backtracking last edge->u->vertex:%s_%s - edge->v->vertex:%s_%s\n", 
			route->node_map[edge->u->vertex], sVertexTypeStrings[edge->u->type],
			route->node_map[edge->v->vertex], sVertexTypeStrings[edge->v->type]);
	}
	if (v != edge->v->vertex || !update_edge(route, edge))
		return NULL;
	vertex = edge->u;
	path = NULL;
	ft_lstadd_back(&path, ft_lstnew(edge->u));
	ft_lstadd_back(&path, ft_lstnew(edge->v));
	i = ft_lstsize(edges);
	if (route->flags.debug)
		printf("\t\tbacktracking edge_list size:%d\n", i);
	while (i--)
	{
		edge = (t_graph_edge*)ft_lstfind_node(edges, i)->content;
		if (route->flags.debug)
		{
			printf("backtracking %svertex:%s_%s, edge->v:%s_%s%s\n", RED,
				route->node_map[vertex->vertex], sVertexTypeStrings[vertex->type],
				route->node_map[edge->v->vertex], sVertexTypeStrings[edge->v->type], FIN);
		}
		//if (edge->v->vertex == vertex->vertex)
		if (edge->v->vertex == vertex->vertex && edge->v->type == vertex->type)
		{
			if (route->flags.debug)
			{
				printf("%svertex:%s_%s, edge->v:%s_%s%s\n", ORANGE,
					route->node_map[vertex->vertex], sVertexTypeStrings[vertex->type],
					route->node_map[edge->v->vertex], sVertexTypeStrings[edge->v->type], FIN);
			}
			if (update_edge(route, edge) < 0)
				return path;
			ft_lstadd_front(&path, ft_lstnew(edge->u));
			vertex = edge->u;
		}
	}
	return path;
}
