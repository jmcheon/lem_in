/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:07:32 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 04:58:27 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"

// for perror
# include <stdio.h>

# define PARSE_XY 1
# define PARSE_XY_START 2
# define PARSE_XY_END 3

# define PARSE_EDGE 4
# define PARSE_COMMENT 5

# define MAX_VERTICES 10

typedef struct s_node_xy
{
	char *name;
	//temporary, needs to change x,y to number variables;
	char *x;
	char *y;
	int node_type;
}	t_node_xy;

typedef struct s_edge
{
	char *key;
	char *val;
}	t_edge;

typedef struct	s_parse
{
	int ant_num;
	t_list *nodes_head;
	t_list *edge_info_head;
}	t_parse;

typedef struct s_graph_node {
	int vertex;
	struct s_graph_node *link;
}	t_graph_node;

typedef struct s_graph_type{
	int	n;
	t_graph_node *adj_list[MAX_VERTICES];
}	t_graph_type;


typedef struct s_graph
{
	int	num_paths; // 실 정점의 개수
	int	paths[MAX_VERTICES][MAX_VERTICES];
}				t_graph;

typedef struct s_route
{
	t_graph*	graph;
    int start;
    int end;
    int num_vertices;

    int list_size;
    char**  node_map;
} t_route;

/*
**	parse_check.c
*/
int		compare_nodename(void *content1, void *content2);
int		compare_edge(void *content1, void *content2);
int		check_duplicate_nodes(t_list *nodes_head, int (*f)(void*, void*));
bool	parse_node_xy_check(char *line);

/*
**	parse_reading.c
*/
int		edgeline_to_struct(char *line, t_list **node);
void	parse_check_edgeline(t_list **line_head, t_parse **parse);
int		nodeline_to_struct(char *line, int parse_status, t_list **node);
int		check_nodeline_status(char *line, int parse_status, t_list **node);
void	parse_check_nodeline(t_list **line_head, t_parse **parse);
void	parse_check_antnum(t_list **line_head, t_parse **parse);

/*
**	parse.c
*/
bool	duplicate_node_check(t_parse *parse);
void	parse_readlines(t_list *lines);
t_parse	*init_parse_struct(void);
t_parse	*parsing();


/*
**	parse_util.c
*/
int		check_split_count(char *line, char delim);
// for debugging
void	parse_result_print(t_parse *parse);
void	free_2d(char **ptr);
void	free_list(t_list *head);




/*
**	graph_list.c
*/

void	parse_to_graph(t_parse *parse);


/*
**	graph_matrix.c
*/

t_graph	*parse_to_graph_matrix(t_parse *parse, t_route *route);
void	graph_print(t_graph *graph);

/*
**	graph_util.c
*/
void node_map_to_array(t_list *nodes_head, char **node_map);
int	node_find_index(char **node_array, char *node_name);
void	print_graph_mapping(int list_size, char **node_map);
char **init_nodes_mapping(int list_size);

/*
**	edmonds-karp-tmp.c
*/
void	print_path(t_route* route, int* parent, int path_id);
int		bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES]);
void	edmonds_karp(t_route* route, t_graph* paths, int* parent, int capacity[][MAX_VERTICES]);
void	fill_capacity(t_graph *graph, int capacity[][MAX_VERTICES]);
void	print_capacity(int capacity[][MAX_VERTICES], int n);
void	print_paths(t_route* route, t_graph* paths);


#endif
