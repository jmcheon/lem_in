#ifndef QUEUE_H
# define QUEUE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_int_list
{
	int		content;
	struct s_int_list	*next;
}	t_int_list;

typedef struct s_queue
{
	t_int_list	*front;
	t_int_list	*rear;
} t_queue;

/*
**	queue.c
*/
void	init_queue(t_queue *queue);
bool	is_empty(t_queue *queue);
void	enqueue(t_queue *queue, int	content);
int		dequeue(t_queue *queue);
void	free_queue(t_queue *queue);

#endif
