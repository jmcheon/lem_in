/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:07:32 by sucho             #+#    #+#             */
/*   Updated: 2023/08/08 12:59:21 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "./get_next_line/get_next_line_bonus.h"

// for perror
#include <stdio.h>

#define PARSE_XY 1
#define PARSE_XY_START 2
#define PARSE_XY_END 3

#define PARSE_EDGE 4
#define PARSE_COMMENTS 5

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
	t_list *nodes_head;
	t_list *edge_info_head;
}	t_parse;
/*
**	Parsing
*/

bool	parse_edge_check(char *line);
bool	parse_node_xy_check(char *line);
int		parse_check_line(char *line, int line_count, int parse_status,  t_list **node);
int		parse_check_edge_line(char *line, t_list **node);
void	parse_readlines(t_list *lines);
int		check_split_count(char *line, char delim);
int		parse_read_node(char *line, int parse_status, t_list **node);
