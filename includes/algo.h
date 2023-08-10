#ifndef ALGO_H
#define ALGO_H

#include "lem-in.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 10

typedef struct s_queue_list
{
	int		content;
	struct s_queue_list*	next;
}	t_queue_list;

typedef struct s_queue
{
	t_queue_list*	front;
	t_queue_list*	rear;
} t_queue;

typedef struct s_path
{
    int path[MAX_VERTICES];
    int id;
} t_path;

typedef struct s_paths
{
  int   paths[MAX_VERTICES][MAX_VERTICES];
  int   num_paths;
} t_paths;


/*
**	queue.c
*/
void	init_queue(t_queue* queue);
bool	is_empty(t_queue* queue);
void	enqueue(t_queue* queue, int	content);
int		dequeue(t_queue* queue);
void	free_queue(t_queue* queue);


int disjoint_bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES], t_paths* paths);
//int disjoint_bfs(int start, int end, int* parent, t_graph_type* graph, int capacity[][MAX_VERTICES], t_paths* paths);
//int bfs(int start, int end, int* parent, t_graph_type* graph, int capacity[][MAX_VERTICES]);
int bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES]);
//void	print_path(int start, int end, int* parent, char** node_map, int path_id);
void	print_path(t_route* route, int* parent, int path_id);
void	print_array(int *parent, int n);

#endif
