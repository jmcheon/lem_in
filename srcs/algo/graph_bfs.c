#include "../../includes/lem-in.h"

int	graph_iter_edges(t_route *route, t_list **ret, t_list **queue, t_graph_vertex *t, int queue_index)
{
	t_graph_edge	*edge;
	t_graph_vertex	*vertex;
	int	i = 0;
	int	size;

	vertex = (t_graph_vertex*)ft_lstfind_node(*queue, queue_index)->content;
	size = ft_lstsize(vertex->out_list);

	printf("v->out\n");
	print_edges(route, vertex->out_list, REVERSE_PRINT);
	(void)route;
	(void)print_edges;
	//printf("iter edge size:%d\n", size);
	while (i < size)
	{
		edge = (t_graph_edge*)ft_lstfind_node(vertex->out_list, i)->content;
		if (!edge)
			return -1;
		//printf("edge->valid:%d, edge->v->valid:%d\n", edge->valid, edge->v->valid);
		if (edge->valid && edge->v->valid)
		{
			edge->v->valid = false;
			ft_lstadd_back(ret, ft_lstnew(edge));
			//printf("edge->v->vertex:%d\n", edge->v->vertex);
			ft_lstadd_back(queue, ft_lstnew(edge->v));
			//printf("queue->size:%d\n", ft_lstsize(queue));
			vertex = (t_graph_vertex*)ft_lstfind_node(*queue, queue_index)->content;
			if (t && edge->v->vertex == t->vertex)
				return 1;
		}
		i++;
	}
	return 0;
}

void	graph_bfs_loop(t_route *route, t_list **ret, t_graph_vertex *s, t_graph_vertex *t)
{
	t_list	*queue;
	t_graph_vertex	*v;
	int		i = 0;

	queue = NULL;
	s->valid = false;
	ft_lstadd_back(&queue, ft_lstnew(s));
	//printf("bfs loop queue size:%d\n", ft_lstsize(queue));
	while (i < ft_lstsize(queue))
	{
		v = (t_graph_vertex*)ft_lstfind_node(queue, i)->content;
		//printf("loop queue->size:%d\n", ft_lstsize(queue));
		//printf("v->valid:%d\n", v->valid);
		v->valid = false;
		//if (graph_iter_edges(arr, &queue, t, i))
		if (graph_iter_edges(route, ret, &queue, t, i))
		{
			//free(queue);
			return;
		}
		i++;
	}
	//free(queue);
	return;
}

void	graph_veretx_valid(void *content)
{
	t_graph_vertex	*v;

	v = (t_graph_vertex*)content;
	v->valid = true;
}

t_list *graph_bfs(t_route *route, t_graph_vertex *s, t_graph_vertex *t)
{
	t_list	*ret;
	t_list	*curr_ptr;
	t_graph_vertex	*curr_vertex_ptr;

	(void)curr_vertex_ptr;
	if (s == NULL)
	{
		printf("test1-1 s==NULL\n");
		return NULL;
	}
	ret = NULL;
	graph_bfs_loop(route, &ret, s, t);
	//printf("af graph bfs loop ret size:%d\n", ft_lstsize(ret));
	curr_ptr = route->graph->v_out_list;
	while (curr_ptr != NULL)
	{
		curr_vertex_ptr = (t_graph_vertex*)curr_ptr->content;
		//if (i != curr_vertex_ptr->vertex)
		((t_graph_vertex*)curr_ptr->content)->valid = true;
		//printf("v out:%d, v->valid:%d\n", curr_vertex_ptr->vertex, curr_vertex_ptr->valid);
		curr_ptr = curr_ptr->next;
	}
	curr_ptr = route->graph->v_in_list;
	while (curr_ptr != NULL)
	{
		curr_vertex_ptr = (t_graph_vertex*)curr_ptr->content;
		//if (i != curr_vertex_ptr->vertex)
		((t_graph_vertex*)curr_ptr->content)->valid = true;
		//printf("v in:%d, v->valid:%d\n", curr_vertex_ptr->vertex, curr_vertex_ptr->valid);
		curr_ptr = curr_ptr->next;
	}
	return ret;
}
