
#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"

// for perror
# include <stdio.h>

# define PARSE_XY 1
# define PARSE_XY_START 2
# define PARSE_XY_END 3
# define PARSE_EDGE 4
# define PARSE_COMMENT 5

/*
** for parsing
*/
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
	int num_ants;
	t_list *nodes_head;
	t_list *edge_info_head;
}	t_parse;

/*
** for parsing
*/


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
int		parse_check_nodeline(t_list **line_head, t_parse **parse);
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
void	free_node_xy(void *node);
void	free_edge(void *node);

#endif
