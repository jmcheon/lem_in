#include "../../../includes/lem-in.h"

int oneshot_bfs_with_weights(t_route* route, int* parent, int **capacity)
{
	int	visited[route->num_vertices];
    int dist[route->num_vertices];
	t_queue	queue;

	//ft_memset(visited, 0, sizeof(visited));

    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    //print_array(parent, route->num_vertices);
    //reset_parent_array(route, &parent);

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
			//printf("current vertex: %d\n", v);
			//printf("node's vertex: %d\n", v);
			if (!visited[v] && capacity[u][v] > 0)
			{
                //printf("dist[%d]:%d, weights[%d][%d]:%d, dist[%d]:%d\n", u, dist[u], u, v, weights[u][v], v, dist[v]);
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

				//printf("parent: ");
				//print_array(parent, route->num_vertices);
			//printf("visited:");
			//print_array(visited, route->num_vertices);
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
			//int potential_distance = route->distances[u] + 1;
			/*
			if (potential_distance < route->distances[v])
			{
				route->distances[v] = potential_distance;
				enqueue_with_priority(&queue, v, potential_distance);
			}
			*/
        	// Check if v is at a distance of one edge from u and capacity is available
			//if (!visited[v] && capacity[u][v] > 0 && route->distances[v] == route->distances[u] + 1)
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

	//ft_memset(visited, 0, sizeof(visited));

    for (int i = 0; i < route->num_vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    //print_array(parent, route->num_vertices);
    //reset_parent_array(route, &parent);

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
			//printf("node's vertex: %d\n", v);
			//printf("v: %d, u:%d\n", v, u);
			//printf("distance[%d]: %d, diatance[%d]:%d\n", v, route->paths->distances[v], u, route->paths->distances[u]);
			if (!visited[v] && capacity[u][v] > 0)// && route->paths->distances[v] > route->paths->distances[u])
			{
				//printf("current vertex: %d, parent:%d\n", v, u);
			    parent[v] = u;
			    if (v == route->end)
			    {
			    	free_queue(&queue);
			    	return (1);
			    }

				//printf("parent: ");
				//print_array(parent, route->num_vertices);
			//printf("visited:");
			//print_array(visited, route->num_vertices);
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
}
