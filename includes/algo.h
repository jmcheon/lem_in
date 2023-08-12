
#ifndef ALGO_H
# define ALGO_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"
# include "./queue.h"
# include "./parse.h"

#define MAX_VERTICES 10

typedef struct s_graph_node {
	int vertex;
	struct s_graph_node *link;
}	t_graph_node;

// typedef struct s_graph{
// 	int	n;
// 	t_graph_node *adj_list[MAX_VERTICES];
// }	t_graph;

typedef struct s_graph
{
	int	n; // 실 정점의 개수
	int	matrix[MAX_VERTICES][MAX_VERTICES];
}				t_graph;


typedef struct s_paths
{
	t_int_list *paths_list[MAX_VERTICES];
	int	paths[MAX_VERTICES][MAX_VERTICES];
	int	num_paths;
} t_paths;

typedef struct s_route
{
	t_graph	*graph;
	t_paths	*paths;
    int start;
    int end;
    int num_vertices;
	int	num_ants;

    int list_size;
    char	**node_map;
} t_route;

/*
**	edmonds-karp.c
*/
void	print_path(t_route* route, int* parent, int path_id);
int		bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES]);
void	edmonds_karp(t_route* route, t_paths* paths, int* parent, int capacity[][MAX_VERTICES]);
void	fill_capacity(t_graph* paths, int capacity[][MAX_VERTICES]);
void	print_capacity(int capacity[][MAX_VERTICES], int n);
void	print_paths(t_route* route, t_paths* paths);
void	init_route(t_route* route, t_parse* parse);
void	init_paths(t_paths* paths);
void 	print_paths_list(t_paths *paths);
void	print_array(int *parent, int n);


/*
**	graph_list.c
*/

t_graph	*parse_to_graph(t_parse *parse);

/*
**	graph_matrix.c
*/

t_graph	*parse_to_graph(t_parse *parse);
void	graph_print(t_graph *graph);




/*
**	graph_util.c
*/
void node_map_to_array(t_list *nodes_head, char **node_map);
int	node_find_index(char **node_array, char *node_name);
void	print_graph_mapping(int list_size, char **node_map);
char **init_nodes_mapping(int list_size);



#endif
