#include "../../includes/lem-in.h"

int min_distance_vertex(int* visited, int* distances, int size)
{
    int min_distance = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < size; v++)
	{
        if (!visited[v] && distances[v] <= min_distance)
		{
            min_distance = distances[v];
            min_index = v;
        }
    }

    return min_index;
}

void	dijkstra(t_route* route)
{
    int size = route->graph->n;
	int *distances = route->distances;
    int	visited[size];

	//printf("size:%d\n", size);
    for (int i = 0; i < size; i++)
	{
        distances[i] = INT_MAX;
        visited[i] = 0;
    }
    distances[route->start] = 0;

    for (int count = 0; count < size - 1; count++)
	{
        int u = min_distance_vertex(visited, distances, size);
        visited[u] = 1;
        t_graph_node* temp_node = route->graph->adj_list[u];

        while (temp_node != NULL)
		{
            int v = temp_node->vertex;
            if (!visited[v] && distances[u] != INT_MAX && distances[u] + 1 < distances[v])
			{
                distances[v] = distances[u] + 1;
            }
            temp_node = temp_node->link;
        }
    }

/*
    printf("Vertex\t Distance from start\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t\t%d\n", i, distances[i]);
    }
	*/
}
