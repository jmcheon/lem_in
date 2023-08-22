
#ifndef ALGO_H
# define ALGO_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"
# include "./queue.h"
# include "./parse.h"
# include "./util.h"

# define REVERSE_PRINT 1
# define FORWARD_PRINT 0

extern const char* sVertexTypeStrings[];

typedef enum VertexType 
{
	IN=0,
	OUT
} VertexType;

typedef struct s_graph_vertex
{
	int vertex;
	VertexType	type;
	t_list	*in_list;
	t_list	*out_list;
	bool		valid;
}	t_graph_vertex;

typedef struct s_graph_edge
{
	t_graph_vertex	*u;
	t_graph_vertex	*v;
	bool			valid;
	int				flow;
	int				capacity;
	struct s_graph_edge	*reverse_edge;
}	t_graph_edge;

typedef struct s_flags
{
	bool	verbose;
	bool	debug;
} t_flags;

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
	t_flags	flags;
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
int			graph_iter_edges(t_route *route, t_list **ret, t_list **queue, t_graph_vertex *t, int queue_index);
void		graph_bfs_loop(t_route *route, t_list **ret, t_graph_vertex *s, t_graph_vertex *t);
t_list		*graph_bfs(t_route *route, t_graph_vertex *s, t_graph_vertex *t);
/*
**	graph_edge.c
*/
int				add_edges(t_graph *g, int u, int v, int u_in, int v_in);
t_graph_edge	*graph_add_edge(t_graph *g, int u_vertex, int v_vertex, int u_in, int v_in, int capacity);
t_graph_edge	*graph_find_edge(t_graph *g, int u, int v, int u_in);

int				update_edge_flow(t_route *route, t_list *edge_list, int v);
int				update_edge(t_route *route, t_graph_edge *edge);
t_graph_edge 	*get_edge(t_graph_vertex *src, t_graph_vertex *des);
t_list 			*graph_edge_backtrack(t_route *route, t_list *edges, int v);

t_list			*save_max_flow_paths(t_route *route, t_graph_vertex *start, t_graph_vertex *end, int max_flow);

/*
**	graph_vertex.c
*/
void			add_vertices(t_route *route);
void			graph_vertex_valid(void *content);
t_graph_vertex	*graph_add_vertex(int v, VertexType type);
t_graph_vertex 	*graph_find_vertex(t_graph *g, int v, int in);

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
void	print_vertex_lists(t_route *route);
void	print_edge_forward_travel(t_route *route);
void	print_edge(t_route *route, void *data);
void	print_edges(t_route *route, t_list *lst, int reverse);
void	print_all_paths(t_route *route, t_list *paths, int print_paths);
void	print_one_path(t_route *route, t_list *path, int print_paths);

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
