#include "../../../includes/lem-in.h"

int oneshot_bfs_with_weights(t_route* route, int* parent, int **capacity)
{
	int	visited[route->num_vertices];
    int dist[route->num_vertices];
	t_queue	queue;


    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

	visited[route->start] = 1;
    dist[route->start] = 0;
	init_queue(&queue);
	enqueue(&queue, route->start);

	while (!is_empty(&queue))
	{
		int u = dequeue(&queue);

		visited[u] = 1;
		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			int v = node->vertex;
			if (!visited[v] && capacity[u][v] > 0)
			{
                int new_dist = dist[u] + capacity[u][v];

                if (new_dist < dist[v])
                {
                    dist[v] = new_dist;
				    parent[v] = u;
				    if (v == route->end)
				    {
				    	free_queue(&queue);
				    	return (1);
				    }

                }
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
}

int oneshot_bfs_with_priority(t_route* route, int* parent, int **capacity)
{
	int	visited[route->num_vertices];
	t_priority_queue	queue;

    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

	visited[route->start] = 1;
	init_priority_queue(&queue);
	enqueue_with_priority(&queue, route->start, route->distances[route->start]);

	while (!priority_queue_empty(&queue))
	{
		int u = dequeue_with_priority(&queue);

		visited[u] = 1;

		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			int v = node->vertex;
			if (!visited[v] && capacity[u][v] > 0)
			{
			    parent[v] = u;
			    if (v == route->end)
			    {
			    	free_priority_queue(&queue);
			    	return (1);
			    }
				enqueue_with_priority(&queue, v, route->distances[v]);
			}
		}
	}
	return (-1);
}


int oneshot_bfs(t_route* route, int* parent, int **capacity)
{
	int	visited[route->num_vertices];
	t_queue	queue;


    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
	visited[route->start] = 1;
	init_queue(&queue);
	enqueue(&queue, route->start);

	while (!is_empty(&queue))
	{
		int u = dequeue(&queue);

		visited[u] = 1;
		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			int v = node->vertex;
			if (!visited[v] && capacity[u][v] > 0)
			{
			    parent[v] = u;
			    if (v == route->end)
			    {
			    	free_queue(&queue);
			    	return (1);
			    }
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
}
