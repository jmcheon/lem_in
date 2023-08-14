#include "../../includes/lem-in.h"

void	dijkstra(t_route *route, int **weights, int *parent, int *dist)
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
