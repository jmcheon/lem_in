#include "../../includes/lem-in.h"

int	graph_iter_edges(t_parray *arr, t_parray *queue, t_graph_vertex *t, int queue_index)
{
	t_graph_edge	*edge;
	t_graph_vertex	*vertex;
	int	i = 0;

	vertex = (t_graph_vertex*)ft_lstfind_node(queue->data_list, queue_index)->content;
	while (i < vertex->out.len)
	{
		edge = (t_graph_edge*)ft_lstfind_node(vertex->out.data_list, i)->content;
		if (!edge)
			return -1;
		if (edge->valid && edge->v->valid)
		{
			edge->v->valid = false;
			ft_lstadd_back(&arr->data_list, ft_lstnew(edge));
			ft_lstadd_back(&queue->data_list, ft_lstnew(edge->v));
			vertex = (t_graph_vertex*)ft_lstfind_node(queue->data_list, queue_index)->content;
			if (t && edge->v->vertex == t->vertex)
				return 1;
		}
		i++;
	}
	return 0;
}

void	graph_bfs_loop(t_parray *arr, t_graph_vertex *s, t_graph_vertex *t)
{
	t_parray	queue;
	t_graph_vertex	*v;
	int		i = 0;

	printf("test1-1\n");
	parr_init(&queue);
	s->valid = false;
	ft_lstadd_back(&queue.data_list, ft_lstnew(s));
	while (i < queue.len)
	{
		v = (t_graph_vertex*)ft_lstfind_node(queue.data_list, i)->content;
		v->valid = false;
		if (graph_iter_edges(arr, &queue, t, i))
		{
			//free(queue);
			return;
		}
		i++;
	}
	//free(queue);
	return;
}

void	graph_veretx_valid()
{
}

t_parray *graph_bfs(t_graph *g, t_graph_vertex *s, t_graph_vertex *t)
{
	t_parray	*ret;

	(void)g;
	printf("test0-1\n");
	if (s == NULL)
	{
		printf("test1-1 s==NULL\n");
		return NULL;
	}
	printf("test1-1\n");
	ret = (t_parray*)malloc(sizeof(t_parray));
	//parr_init(ret); 
	graph_bfs_loop(ret, s, t);
	return ret;
}
