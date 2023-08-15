#include "../../includes/queue.h"

void	init_priority_queue(t_priority_queue* queue)
{
	queue->front = NULL;
}

bool	priority_queue_empty(t_priority_queue* queue)
{
	return (queue->front == NULL);
}

void	en_priority_queue(t_priority_queue* queue, int content, int distance)
{
	t_int_list*	new_node = (t_int_list*)malloc(sizeof(t_int_list));

	if (!new_node)
	{
		fprintf(stderr, "malloc failed.\n");
		return ;
	}

	new_node->content = content;
	new_node->distance = distance;
	new_node->next = NULL;

	if (priority_queue_empty(queue) || distance < queue->front->distance)
	{
		new_node->next = queue->front;
		queue->front = new_node;
	}
	else
	{
		t_int_list *curr_queue_ptr = queue->front;
		while (curr_queue_ptr->next && curr_queue_ptr->next->distance <= distance)
			curr_queue_ptr = curr_queue_ptr->next;
		new_node->next = curr_queue_ptr->next;
		curr_queue_ptr->next = new_node;
	}
	// printf("enqueued: %d\n", content);
}

int	de_priority_queue(t_priority_queue* queue)
{
	if (priority_queue_empty(queue))
	{
		fprintf(stderr, "queue is empty, can't dequeue.\n");
		return (-1);
	}

	t_int_list* temp = queue->front;
	int	content = temp->content;
	queue->front = temp->next;

	free(temp);
	//printf("dequeued: %d\n", content);
	return (content);
}

void	free_priority_queue(t_priority_queue* queue)
{
	while(!priority_queue_empty(queue))
		de_priority_queue(queue);
}
