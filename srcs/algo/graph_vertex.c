#include "../../includes/lem-in.h"

void parr_init(t_parray *arr)
{
	arr->data_list = NULL;
	arr->len = 0;
}

t_graph_vertex *graph_find_vertex(t_graph *g, int v)
{
	t_graph_vertex *temp;
	t_graph_node *curr_ptr;

	printf("graph_find_vertex finding v:%d\n", v);
	for (int i = 0; i < g->n; i++)
	{
		g->adj_list
	}
	curr_ptr = g->adj_list[v];
	if (curr_ptr == NULL)
		printf("curr_ptr == NULL\n");
	while (curr_ptr->link != NULL)
	{
		printf("curr_ptr->vertex:%d\n", curr_ptr->vertex);
		if (curr_ptr->vertex == v)
		{
			temp = (t_graph_vertex*)malloc(sizeof(t_graph_vertex));
			temp->vertex = v;
			return temp;
		}
		curr_ptr = curr_ptr->link;
	}
	return (NULL);
}

int graph_add_vertex(t_graph *g, int v, void *attr)
{
	t_graph_vertex *vertex;

	(void)g;
	vertex = (t_graph_vertex*)malloc(sizeof(t_graph_vertex));
	if (!vertex)
		return -1;
	vertex->vertex = v;
	parr_init(&vertex->in);
	parr_init(&vertex->out);
	vertex->attr = attr;
	return 1;
}

void	split_vertex(t_graph *g, void *data, int v)
{
	/*
	t_graph_vertex *vertex;
	t_vertex_attr *in_vertex_attr;
	t_vertex_attr *out_vertex_attr;
	*/
	(void)data;
	add_edges(g, v, v);
}

