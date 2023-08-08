#ifndef ALGO_H
#define ALGO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_queue
{
	t_list*	front;
	t_list*	rear;

} t_queue;

#endif
