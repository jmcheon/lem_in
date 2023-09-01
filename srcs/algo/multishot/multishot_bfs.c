#include "../../../includes/lem-in.h"

int	multishot_iterate_edges(t_route *route, t_list **ret, t_list **queue, t_graph_vertex *t, int queue_index)
{
	t_graph_edge	*edge;
	t_graph_vertex	*vertex;
	int	i = 0;
	int	size;

	(void)route;
	vertex = (t_graph_vertex*)ft_lstfind_node(*queue, queue_index)->content;
	size = ft_lstsize(vertex->out_list);

	while (i < size)
	{
		edge = (t_graph_edge*)ft_lstfind_node(vertex->out_list, i)->content;
		if (!edge)
			return -1;
		if (edge->valid && edge->v->valid)
		{

			edge->v->valid = false;
			ft_lstadd_back(ret, ft_lstnew(edge));

			ft_lstadd_back(queue, ft_lstnew(edge->v));

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
	free_list_ptr(queue);
	return ret;
}
