#include "../../../includes/lem-in.h"

t_graph_vertex *multishot_find_vertex(t_graph *g, int v, int in)
{
	if (in == IN)
		return (t_graph_vertex*)ft_lstfind_node(g->v_in_list, v)->content;
	else
		return (t_graph_vertex*)ft_lstfind_node(g->v_out_list, v)->content;
}

t_graph_vertex	*multishot_init_vertex(int v, VertexType type)
{
	t_graph_vertex *vertex;

	vertex = (t_graph_vertex*)malloc(sizeof(t_graph_vertex));
	if (!vertex)
		return NULL;
	vertex->vertex = v;
	vertex->type = type;
	vertex->valid = true;
	vertex->in_list = NULL;
	vertex->out_list = NULL;
	return vertex;
}

void	multishot_add_vertices(t_route *route)
{
	t_graph_node	*curr_ptr;

	for (int i = 0; i < route->num_vertices; i++)
	{
		ft_lstadd_back(&route->graph->v_in_list, ft_lstnew(multishot_init_vertex(i, IN)));
		ft_lstadd_back(&route->graph->v_out_list, ft_lstnew(multishot_init_vertex(i, OUT)));
		multishot_add_edges(route->graph, i, i, OUT, IN);
	}
	for (int i = 0; i < route->num_vertices; i++)
	{
		curr_ptr = route->graph->adj_list[i];
		while (curr_ptr !=NULL)
		{
			multishot_add_edges(route->graph, curr_ptr->vertex, i, IN, OUT);
			curr_ptr = curr_ptr->link;
		}
	}
}

