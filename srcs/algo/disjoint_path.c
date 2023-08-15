#include "../../includes/lem-in.h"

int min_distance_vertex(bool visited[], int distances[], int size)
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

void construct_path(int prev[], int vertex, t_vertex_list** path)
{
    if (vertex == -1)
        return;

    construct_path(prev, prev[vertex], path);

    t_vertex_list *new_vertex = (t_vertex_list *)malloc(sizeof(t_vertex_list));
    new_vertex->vertex = vertex;
    new_vertex->next = NULL;
    new_vertex->prev = *path;

    if (*path != NULL)
    {
        (*path)->next = new_vertex;
    }
    *path = new_vertex;
}


void construct_path1(t_route *route, int prev[], int vertex, t_vertex_list** path)
{
	printf("constructing path\n");
    if (prev[vertex] == -1)
    {
        t_vertex_list *new_vertex = (t_vertex_list *)malloc(sizeof(t_vertex_list));
        new_vertex->vertex = vertex;
        new_vertex->next = NULL;
        new_vertex->prev = *path;

        if (*path != NULL)
        {
            (*path)->next = new_vertex;
        }
        *path = new_vertex;
        return;
    }

    construct_path1(route, prev, prev[vertex], path);
    construct_path1(route, prev, vertex, path);
}

t_vertex_list *modified_dijkstra(t_route *route, int source, int destination)
{
    t_graph *graph = route->graph;
    int size = graph->n;
    int *distances = (int *)malloc(size * sizeof(int));
    int *prev = (int *)malloc(size * sizeof(int));
    bool *visited = (bool *)malloc(size * sizeof(bool));

    for (int i = 0; i < size; i++)
    {
        distances[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    distances[source] = 0;

    for (int count = 0; count < size - 1; count++)
    {
        int u = min_distance_vertex(visited, distances, size);
        visited[u] = true;
        t_graph_node *temp_node = graph->adj_list[u];

        while (temp_node != NULL)
        {
            int v = temp_node->vertex;
			printf("temp node vertex:%d\n", v);
            if (!visited[v] && distances[u] != INT_MAX && distances[u] + 1 < distances[v])
            {
                distances[v] = distances[u] + 1;
                prev[v] = u;
            }
            temp_node = temp_node->link;
        }
    }
    t_vertex_list *shortest_path = NULL;
    construct_path(prev, destination, &shortest_path);

    free(distances);
    free(prev);
    free(visited);

    return shortest_path;

}

void remove_edge(t_graph *graph, int start, int end)
{
    t_graph_node* temp = graph->adj_list[start];
    t_graph_node* prev = NULL;
    while (temp != NULL)
	{
        if (temp->vertex == end)
		{
            if (prev == NULL)
                graph->adj_list[start] = temp->link;
            else
                prev->link = temp->link;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->link;
    }
}

void remove_edges_in_path(t_graph *graph, t_vertex_list *path)
{
    t_vertex_list *current = path;
    while(current->next != NULL)
    {
        remove_edge(graph, current->vertex, current->next->vertex);
        current = current->next;
    }
}



void print_path2(t_route * route, int prev[], int vertex)
{
    if (prev[vertex] == -1) 
    {
        printf("%d ", vertex);
        return;
    }

    print_path2(route, prev, prev[vertex]);
    printf("%d ", vertex);
}

void modified_dijkstra1(t_route* route)
{
    t_graph* graph = route->graph;
    int size = graph->n;
    int distances[size];
    int prev[size];
    bool visited[size];

    // Initialize distance and visited arrays, and prev array for reconstruction
    for (int i = 0; i < size; i++)
    {
        distances[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    distances[route->start] = 0;

    for (int count = 0; count < size - 1; count++)
    {
        int u = min_distance_vertex(visited, distances, size);
        visited[u] = true;
        t_graph_node* temp_node = graph->adj_list[u];

        while (temp_node != NULL)
        {
            int v = temp_node->vertex;
            if (!visited[v] && distances[u] != INT_MAX && distances[u] + 1 < distances[v])
			{
                distances[v] = distances[u] + 1;
                prev[v] = u; // update prev array to store the path
            }
            temp_node = temp_node->link;
        }
    }

    printf("Starting vertex: %d\n", route->start);
    for (int i = 0; i < size; i++)
    {
        if (i != route->start)
        {
            printf("Shortest path to vertex %d: ", i);
            print_path2(route, prev, i);
            printf("\n");
            remove_edge(graph, prev[i], i); // remove the edges after printing the path
        }
    }
    printf("\n");
}


void	dijkstra(t_route* route)
{
    int size = route->graph->n;
	int *distances = route->paths->distances;
    bool visited[size];

	//printf("size:%d\n", size);
    for (int i = 0; i < size; i++)
	{
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[route->start] = 0;

    for (int count = 0; count < size - 1; count++)
	{
        int u = min_distance_vertex(visited, distances, size);
        visited[u] = true;
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

    printf("Vertex\t Distance from start\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t\t%d\n", i, distances[i]);
    }
}


void	dijkstra1(t_route *route, int **weights, int *parent, int *dist)
{
	int visited[route->num_vertices];

	for (int i = 0; i < route->num_vertices; i++)
	{
		visited[i] = 0;
		dist[i] = INT_MAX;
		parent[i] = -1;
	}

	dist[route->start] = 0;

	for (int i = 0; i < route->num_vertices - 1; i++)
	{
		int u = -1;

		for (int j = 0; j < route->num_vertices; j++)
		{
			if (!visited[j] && (u == -1 || dist[j] < dist[u]))
				u = j;
		}
		visited[u] = 1;

		for (t_graph_node* node = route->graph->adj_list[u]; node != NULL; node = node->link)
		{
			int v = node->vertex;

			if (!visited[v] && dist[u] != INT_MAX && dist[u] + weights[u][v] < dist[v])
			{
				dist[v] = dist[u] + weights[u][v];
				parent[v] = u;
			}
		}
	}
}

void	remove_path(t_route *route, int *parent)
{
	for (int v = route->end; v != route->start; v = parent[v])
	{
		int u = parent[v];
		t_graph_node *node = route->graph->adj_list[u];

		if (node->vertex == v)
			route->graph->adj_list[u] = node->link;
		else
		{
			t_graph_node *prev = node;
			node = node->link;

			while (node != NULL && node->vertex != v)
			{
				prev = node;
				node = node->link;
			}
			if (node != NULL)
				prev->link = node->link;
		}
		free(node);
	}
}

void	append_path(t_paths *paths, int *parent, int end)
{
	insert_next_parent(paths, end);

	int node_id = parent[end];

	while (node_id != -1)
	{
		//printf("node_id:%d\n", node_id);
		insert_next_parent(paths, node_id);
		node_id = parent[node_id];
	}
	paths->num_paths++;
}
/*
void	disjoint_path(t_route *route, int **weights)
{
	int parent[route->num_vertices];
	int dist[route->num_vertices];
	bool path_found = true;
	
	while (path_found)
	{
		//print_array(dist, route->num_vertices);
		dijkstra(route, weights, parent, dist);

		if (dist[route->end] == INT_MAX)
		{
			//printf("path not found\n");
			path_found = false;
		}
		else
		{
			//printf("path FOUND\n");
			append_path(route->paths, parent, route->end);
			//for (int v = route->end; v != route->start; v = parent[v])
			//{
			//	int u = parent[v];
			//	if (v == route->end)
			//		append_path(route->paths, parent, v);
			//	append_path(route->paths, parent, u);
			//}
			//route->paths->num_paths++;
			remove_path(route, parent);
		}
	}
}
*/
