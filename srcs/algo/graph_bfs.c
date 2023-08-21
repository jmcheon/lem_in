#include "../../includes/lem-in.h"

static int lem_print_edge(void *data, int i)
{
	t_graph_edge	*tmp;
	// t_edge_attr		*attr;

	tmp = data;
	// attr = tmp->attr;
	printf("%-10d -> %-10d\n",
		tmp->u->vertex, tmp->v->vertex);
	return ((int)i);
}


static void	print_edges(t_list *lst)
{
	int	size;

	size = ft_lstsize(lst);
	printf("start printing edges... size:%d\n", size);

	for (int j = 0; j < size; j++)
	{
		lem_print_edge(ft_lstfind_node(lst, j)->content, j);
		// print("data[%d]:%s\n", j, ((char *)parray->data[j]));
	}
}

static void	print_edges_list(t_list *lst)
{
	printf("start printing edges... size:%d\n", ft_lstsize(lst));

	for (int j = 0; j < ft_lstsize(lst); j++)
	{
		lem_print_edge(ft_lstfind_node(lst, j)->content, j);
		// print("data[%d]:%s\n", j, ((char *)parray->data[j]));
	}
}
//int	graph_iter_edges(t_parray *arr, t_parray *queue, t_graph_vertex *t, int queue_index)
int	graph_iter_edges(t_list *arr, t_list *queue, t_graph_vertex *t, int queue_index)
{
	t_graph_edge	*edge;
	t_graph_vertex	*vertex;
	int	i = 0;
	int	size;

	//vertex = (t_graph_vertex*)ft_lstfind_node(queue->data_list, queue_index)->content;
	vertex = (t_graph_vertex*)ft_lstfind_node(queue, queue_index)->content;
	size = ft_lstsize(vertex->out_list);
	printf("vertex->out_list size:%d\n", ft_lstsize(vertex->out_list));
	//print_edges(&vertex->out);
	print_edges(vertex->out_list);
	(void)print_edges;
	print_edges_list(vertex->out_list);
	//while (i < vertex->out.len)
	while (i < size)
	{
		//edge = (t_graph_edge*)ft_lstfind_node(vertex->out.data_list, i)->content;
		edge = (t_graph_edge*)ft_lstfind_node(vertex->out_list, i)->content;
		if (!edge)
			return -1;
		printf("edge->valid:%d, edge->v->valid:%d\n", edge->valid, edge->v->valid);
		if (edge->valid && edge->v->valid)
		{
			edge->v->valid = false;
			//ft_lstadd_back(&arr->data_list, ft_lstnew(edge));
			ft_lstadd_back(&arr, ft_lstnew(edge));
			//ft_lstadd_back(&queue->data_list, ft_lstnew(edge->v));
			ft_lstadd_back(&queue, ft_lstnew(edge->v));
			printf("queue->size:%d\n", ft_lstsize(queue));
			//vertex = (t_graph_vertex*)ft_lstfind_node(queue->data_list, queue_index)->content;
			vertex = (t_graph_vertex*)ft_lstfind_node(queue, queue_index)->content;
			if (t && edge->v->vertex == t->vertex)
				return 1;
		}
		i++;
	}
	return 0;
}

//void	graph_bfs_loop(t_parray *arr, t_graph_vertex *s, t_graph_vertex *t)
void	graph_bfs_loop(t_list *arr, t_graph_vertex *s, t_graph_vertex *t)
{
	//t_parray	queue;
	t_list	*queue;
	t_graph_vertex	*v;
	int		i = 0;

	//parr_init(&queue);
	queue = NULL;
	s->valid = false;
	//ft_lstadd_back(&queue.data_list, ft_lstnew(s));
	ft_lstadd_back(&queue, ft_lstnew(s));
	//queue.len++;
	//printf("queue.len:%d\n", queue.len);
	printf("queue size:%d\n", ft_lstsize(queue));
	//while (i < queue.len)
	while (i < ft_lstsize(queue))
	{
		//v = (t_graph_vertex*)ft_lstfind_node(queue.data_list, i)->content;
		v = (t_graph_vertex*)ft_lstfind_node(queue, i)->content;
		printf("v->valid:%d\n", v->valid);
		v->valid = false;
		//if (graph_iter_edges(arr, &queue, t, i))
		if (graph_iter_edges(arr, queue, t, i))
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

t_list *graph_bfs(t_graph *g, t_graph_vertex *s, t_graph_vertex *t)
{
	//t_parray	*ret;
	t_list	*ret;

	(void)g;
	if (s == NULL)
	{
		printf("test1-1 s==NULL\n");
		return NULL;
	}
	//ret = (t_parray*)malloc(sizeof(t_parray));
	//parr_init(ret); 
	ret = NULL;
	graph_bfs_loop(ret, s, t);
	for (int i = 0; i < g->n; i++)
	{
		//ft_lstiter(g->v_in_list, graph_vertex_valid);
	}
	return ret;
}
