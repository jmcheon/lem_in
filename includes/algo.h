
#ifndef ALGO_H
# define ALGO_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"
# include "./queue.h"
# include "./parse.h"

#define MAX_VERTICES 50

typedef struct s_parray
{
	//void	**data;
	t_list	*data_list;
	int		len;
}	t_parray;

typedef struct s_graph_vertex
{
	int vertex;
	t_list	*in_list;
	t_list	*out_list;
	//int		in_list_length;
	//int		out_list_length;
	t_parray	in;
	t_parray	out;
	bool		valid;
	//void		*attr;
}	t_graph_vertex;

typedef struct s_graph_edge
{
	t_graph_vertex	*u;
	t_graph_vertex	*v;
	bool			valid;
	int				flow;
	int				capacity;
	struct s_graph_edge	*reverse_edge;
	void			*attr;
}	t_graph_edge;

typedef struct s_vertex_attr
{
	char			*name;
	int				value;
	t_graph_vertex	*org;
}	t_vertex_attr;

typedef struct s_edge_attr
{
	int	flow;
	int	capacity;
	t_graph_edge	*reverse_edge;
}	t_edge_attr;

///////////////////////////////

typedef struct s_graph_node 
{
	int vertex;
	struct s_graph_node *link;
}	t_graph_node;

typedef struct s_graph
{
	int	n;
	t_graph_node **adj_list;
	t_list	*v_in_list;
	t_list	*v_out_list;
}	t_graph;

typedef struct s_vertex_list
{
	int	    vertex;
	int		length;
	struct s_vertex_list	*next;
	struct s_vertex_list	*prev;
}	t_vertex_list;

typedef struct s_paths
{
	t_list *paths;
	int	num_paths;
} t_paths;

typedef struct s_route
{
	t_graph	*graph;
	t_paths	*paths;
	int	*distances;
    int start;
    int end;
    int num_vertices;
	//int	num_edges;
	int	num_ants;

    char	**node_map;
} t_route;

/*
**	graph_bfs.c
*/
int			graph_iter_edges(t_parray *arr, t_list *queue, t_graph_vertex *t, int queue_index);
//int			graph_iter_edges(t_parray *arr, t_parray *queue, t_graph_vertex *t, int queue_index);
void		graph_bfs_loop(t_parray *arr, t_graph_vertex *s, t_graph_vertex *t);
t_parray 	*graph_bfs(t_graph *g, t_graph_vertex *s, t_graph_vertex *t);
/*
**	graph_edge.c
*/
int				parr_add_back(t_parray *arr, void *data);
int				graph_add_edge(t_graph *g, int u_vertex, int v_vertex, int u_in, int v_in, void *attr);
int				add_edges(t_graph *g, int u, int v, int u_in, int v_in);
int				update_edge_flow(t_parray *edge_list, int v);
int				update_edge(t_graph_edge *edge);
void			split_edge(t_graph *g, t_graph_vertex *vertex, int v);
t_graph_edge	*graph_find_edge(t_graph *g, int u, int v, int u_in);
t_edge_attr		*init_edge_attr(int capacity);
t_graph_edge 	*get_edge(t_graph_vertex *src, t_graph_vertex *des);
t_parray		*save_max_flow_paths(t_graph_vertex *start, t_graph_vertex *end, int max_flow);
t_parray 		*graph_edge_backtrack(t_parray *edges, int v);

/*
**	graph_vertex.c
*/
t_graph_vertex	*graph_add_vertex(int v);
void			parr_init(t_parray *arr);
void			add_vertices(t_graph *g);
t_graph_vertex 	*graph_find_vertex(t_graph *g, int v, int in);
void			graph_vertex_valid(void *content);

/*
**	edmonds_karp.c
*/
void	reset_parent_array(t_route *route, int **parent);
void	init_parent_array(t_route *route, int **parent);

int bfs(t_route* route, int* parent, int **capacity);
int bfs_with_weights(t_route* route, int* parent, int **capacity);
void	edmonds_karp(t_route* route, t_paths* paths, int* parent, int **capacity);
void	edmonds_karp_with_weights(t_route* route, t_paths* paths, int* parent, int **capacity);
void	fill_capacity(t_graph*paths, int **capacity);
void	insert_next_parent(t_paths *paths, int v);
void	optimize(t_route *route);

/*
**	init_funcs.c
*/
void	init_route(t_route* route, t_parse* parse);
void	init_vertex_list(t_vertex_list* path, int v);
void	init_paths(t_paths* paths);


/*
**	print_funcs.c
*/
void	print_path(t_route* route, int* parent, int path_id);
void	print_paths(t_route* route, t_paths* paths);
void	print_paths_list(t_route *route);
void	print_2d_array(int **array, int size);
void	print_array(int *array, int size);


/*
** disjoin_path.c
*/

void	dijkstra(t_route *route);

/*
**	graph_list.c
*/

t_graph	*parse_to_graph(t_parse *parse, t_route *route);
int	lstsize(t_graph_node *lst);



/*
**	graph_util.c
*/
char **node_map_to_array(t_list *nodes_head);
int	node_find_index(char **node_array, char *node_name, int node_array_len);
void	print_graph_mapping(int list_size, char **node_map);
char **init_nodes_mapping(int list_size);
void	free_graph(t_graph *g);
void	free_paths_list(t_paths *paths);




#endif
