#ifndef ALGO_H
#define ALGO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./lem-in.h"

typedef struct s_queue
{
	t_list*	front;
	t_list*	rear;

} t_queue;

int bfs(int start, int end, int* parent, t_graph_type* graph, int capacity[][MAX_VERTICES]);

#endif
