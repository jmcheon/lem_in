#include "algo.h"

void	init_queue(t_queue* queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}

bool	is_empty(t_queue* queue)
{
	return queue->front == NULL;
}

void	enqueue(t_queue* queue, void* content)
{
	t_list*	new_node = (t_list*)malloc(sizeof(t_list));

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

void*	dequeue(t_queue* queue)
{
	if (is_empty(queue))
	{
		fprintf(stderr, "queue is empty, can't dequeue.\n");
		return NULL;
	}

	t_list* temp = queue->front;
	void*	content = temp->content;
	queue->front = temp->next;

	if (queue->front == NULL)
		queue->rear = NULL;

	free(temp);
	return content;
}

void	free_queue(t_queue* queue)
{
	while(!is_empty(queue))
		dequeue(queue);
}

int	main(void)
{
	t_queue	queue;

	init_queue(&queue);
 	enqueue(&queue, (void*)5);
    enqueue(&queue, (void*)10);
    enqueue(&queue, (void*)15);

    printf("Dequeued: %d\n", (int)dequeue(&queue));
    printf("Dequeued: %d\n", (int)dequeue(&queue));

    enqueue(&queue, (void*)20);

    printf("Dequeued: %d\n", (int)dequeue(&queue));
    printf("Dequeued: %d\n", (int)dequeue(&queue));

    free_queue(&queue);

	return (0);
}
