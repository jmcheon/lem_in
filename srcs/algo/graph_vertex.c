#include "../../includes/lem-in.h"

/*
void parr_init(t_parray *arr)
{
	arr->data_list = NULL;
	arr->len = 0;
}
*/
void	print_vertex_content(void *content)
{
	printf("v:%d\n", ((t_graph_vertex*)content)->vertex);
}

t_graph_vertex *graph_find_vertex(t_graph *g, int v, int in)
{

	//printf("graph_find_vertex finding v:%d-%d\n", v, in);
	/*
	t_graph_vertex	*vertex;
	printf("start printing v in list\n");
	ft_lstiter(g->v_in_list, print_vertex_content);
	printf("start printing v out list\n");
	ft_lstiter(g->v_out_list, print_vertex_content);
	*/
	if (in == 0)
		return (t_graph_vertex*)ft_lstfind_node(g->v_in_list, v)->content;
	else
		return (t_graph_vertex*)ft_lstfind_node(g->v_out_list, v)->content;
/*
	t_graph_vertex *temp;
	t_graph_node *curr_ptr;
	curr_ptr = g->adj_list[v];
	if (curr_ptr != NULL)
	{
		temp = (t_graph_vertex*)malloc(sizeof(t_graph_vertex));
		temp->vertex = v;
		return temp;
	}
	return NULL;
*/
}

t_graph_vertex	*graph_add_vertex(int v)
{
	t_graph_vertex *vertex;

	vertex = (t_graph_vertex*)malloc(sizeof(t_graph_vertex));
	if (!vertex)
		return NULL;
	vertex->vertex = v;
	vertex->valid = true;
	vertex->in_list = NULL;
	vertex->out_list = NULL;
	return vertex;
}

void	graph_vertex_valid(void *content)
{
	t_graph_vertex	*v;

	v = (t_graph_vertex*)content;
	v->valid = true;
}

void	add_vertices(t_route *route)
{
	t_graph_vertex	*v;
	t_graph_edge	*e;
	t_graph_node	*curr_ptr;
	int	size;

	(void)e;
	for (int i = 0; i < route->num_vertices; i++)
	{
		//v = graph_add_vertex(i);
		//printf("adding vertex:%d valid:%d\n", v->vertex, v->valid);
		ft_lstadd_back(&route->graph->v_in_list, ft_lstnew(graph_add_vertex(i)));
		ft_lstadd_back(&route->graph->v_out_list, ft_lstnew(graph_add_vertex(i)));
		add_edges(route->graph, i, i, 1, 0);
	}
	for (int i = 0; i < route->num_vertices; i++)
	{
		curr_ptr = route->graph->adj_list[i];
		while (curr_ptr !=NULL)
		{
			//printf("i:%d, curr_ptr->vertex:%d\n", i, curr_ptr->vertex);
			add_edges(route->graph, curr_ptr->vertex, i, 0, 1);
			//add_edges(route->graph, i, curr_ptr->vertex, 1, 0);
			curr_ptr = curr_ptr->link;
		}
	}

	for (int i = 0; i < route->num_vertices; i++)
	{
		v = graph_find_vertex(route->graph, i, 0);
		curr_ptr = route->graph->adj_list[i];
		//printf("split edge v->vertex:%d, v->in_list.size:%d\n", v->vertex, ft_lstsize(v->in_list));
		//printf("split edge v->vertex:%d, v->out_list.size:%d\n", v->vertex, ft_lstsize(v->out_list));
		size = ft_lstsize(v->in_list);
		for (int j = 0; j < size; j++)
		{
			//e = (t_graph_edge*)ft_lstfind_node(v->in.data_list, j)->content;
			e = (t_graph_edge*)ft_lstfind_node(v->in_list, j)->content;
			//add_edges(g, e->u->vertex, e->v->vertex);
		}
	}
}

