#include "../includes/algo.h"

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

void	dequeue(t_queue* queue)
{
	if (is_empty(queue))
	{
		fprintf(stderr, "queue is empty, can't dequeue.\n");
		return ;
	}

	t_list* temp = queue->front;
	printf("dequeue:%d\n", *(int*)temp->content);
	// void*	content = (void*)malloc(sizeof(temp->content));
	queue->front = temp->next;

	if (queue->front == NULL)
		queue->rear = NULL;

	free(temp);
	// return content;
}

void	free_queue(t_queue* queue)
{
	while(!is_empty(queue))
		dequeue(queue);
}

int	dequeue_test(void)
{
	t_queue	queue;
	void*	inputs[5];

	for (int i = 0; i < 5; ++i)
	{
		inputs[i] = (void*)malloc(sizeof(int));
		*(int*)inputs[i] = i*5;
	}

	init_queue(&queue);
 	enqueue(&queue, inputs[0]);
 	enqueue(&queue, inputs[1]);
 	enqueue(&queue, inputs[2]);

    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
 	enqueue(&queue, inputs[3]);

	dequeue(&queue);

    free_queue(&queue);
	for (int i = 0; i < 5; ++i)
		free(inputs[i]);

	return (0);
}
