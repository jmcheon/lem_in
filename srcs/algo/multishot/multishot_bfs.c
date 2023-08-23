#include "../../../includes/lem-in.h"

int	multishot_iterate_edges(t_route *route, t_list **ret, t_list **queue, t_graph_vertex *t, int queue_index)
{
	t_graph_edge	*edge;
	t_graph_vertex	*vertex;
	int	i = 0;
	int	size;

	vertex = (t_graph_vertex*)ft_lstfind_node(*queue, queue_index)->content;
	size = ft_lstsize(vertex->out_list);

	(void)route;
	//printf("iter edge size:%d\n", size);
	while (i < size)
	{
		edge = (t_graph_edge*)ft_lstfind_node(vertex->out_list, i)->content;
		if (!edge)
			return -1;
		//printf("edge->valid:%d, edge->v->valid:%d\n", edge->valid, edge->v->valid);
		if (edge->valid && edge->v->valid)
		{
			if (route->flags.debug)
			{
				printf("%sPrinting v->out_list%s\n", YELLOW, FIN);
				multishot_print_edges(route, vertex->out_list, FORWARD_PRINT);
			}
			/*
			printf("%se->valid:%d, e->v->valid:%d\n", PINK, edge->valid, edge->v->valid);
			printf("adding current edge(edge->v:%s_%s) to edge_list...%s\n", 
				route->node_map[edge->v->vertex], sVertexTypeStrings[edge->v->type], FIN);
			*/
			edge->v->valid = false;
			ft_lstadd_back(ret, ft_lstnew(edge));

			if (route->flags.debug)
			{
				printf("edge->u->vertex:%s_%s - edge->v->vertex:%s_%s\n", 
					route->node_map[edge->u->vertex], sVertexTypeStrings[edge->u->type],
					route->node_map[edge->v->vertex], sVertexTypeStrings[edge->v->type]);
			}
			ft_lstadd_back(queue, ft_lstnew(edge->v));
			if (route->flags.debug)
			{
				printf("queue->size:%d added edge->v->vertex:%s_%s\n\n", 
					ft_lstsize(*queue),
					route->node_map[edge->v->vertex], sVertexTypeStrings[edge->v->type]);
			}
			vertex = (t_graph_vertex*)ft_lstfind_node(*queue, queue_index)->content;
			if (t && edge->v->vertex == t->vertex)
				return 1;
		}
		i++;
	}
	return 0;
}

t_list *multishot_bfs(t_route *route, t_graph_vertex *s, t_graph_vertex *t)
{
	t_list	*ret;
	t_list	*queue;
	t_graph_vertex	*v;
	int		i = 0;

	if (s == NULL)
		return NULL;
	ret = NULL;
	queue = NULL;
	s->valid = false;
	ft_lstadd_back(&queue, ft_lstnew(s));
	while (i < ft_lstsize(queue))
	{
		v = (t_graph_vertex*)ft_lstfind_node(queue, i)->content;
		v->valid = false;
		if (multishot_iterate_edges(route, &ret, &queue, t, i))
			break ;
		i++;
	}
	set_all_vertices_valid(route, true);
	//printf("af graph oneshot_bfs loop ret size:%d\n", ft_lstsize(ret));
	free_list_ptr(queue);
	return ret;
}
