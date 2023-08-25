#include "../../includes/queue.h"

void	init_queue(t_queue* queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}

bool	is_empty(t_queue* queue)
{
	return (queue->front == NULL);
}

void	enqueue(t_queue* queue, int	content)
{
	t_int_list*	new_node = (t_int_list*)malloc(sizeof(t_int_list));

	if (!new_node)
	{
		fprintf(stderr, "malloc failed.\n");
		return ;
	}

	new_node->content = content;
	new_node->next = NULL;

	if (is_empty(queue))
		queue->front = new_node;
	else
		queue->rear->next = new_node;
	queue->rear = new_node;
}

int	dequeue(t_queue* queue)
{
	if (is_empty(queue))
	{
		fprintf(stderr, "queue is empty, can't dequeue.\n");
		return (-1);
	}

	t_int_list* temp = queue->front;
	int	content = temp->content;
	queue->front = temp->next;

	if (queue->front == NULL)
		queue->rear = NULL;

	free(temp);
	return (content);
}

void	free_queue(t_queue* queue)
{
	while(!is_empty(queue))
		dequeue(queue);
}

int	queue_test(void)
{
	t_queue	queue;
	int	inputs[5];

	for (int i = 0; i < 5; ++i)
		inputs[i] = i*5;

	init_queue(&queue);
 	enqueue(&queue, inputs[0]);
 	enqueue(&queue, inputs[1]);
 	enqueue(&queue, inputs[2]);

 	enqueue(&queue, inputs[3]);

    free_queue(&queue);

	return (0);
}
