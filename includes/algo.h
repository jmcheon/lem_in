
#ifndef ALGO_H
# define ALGO_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"
# include "./queue.h"
# include "./parse.h"

#define MAX_VERTICES 50

typedef struct s_graph_node {
	int vertex;
	struct s_graph_node *link;
}	t_graph_node;

typedef struct s_graph{
	int	n;
	t_graph_node **adj_list;
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
**	edmonds_karp.c
*/
void	reset_parent_array(t_route *route, int **parent);
void	init_parent_array(t_route *route, int **parent);

int bfs(t_route* route, int* parent, int **capacity);
void	edmonds_karp(t_route* route, t_paths* paths, int* parent, int **capacity);
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

t_vertex_list *modified_dijkstra(t_route *route, int source, int destination);
void	modified_dijkstra1(t_route* route);
void	remove_edges_in_path(t_graph *graph, t_vertex_list *path);

void	dijkstra(t_route *route);
void	dijkstra1(t_route *route, int **weights, int *parent, int *dist);
void	remove_path(t_route *route, int *parent);
void	append_path(t_paths *paths, int *parent, int end);
void	disjoint_path(t_route *route, int **weights);

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
