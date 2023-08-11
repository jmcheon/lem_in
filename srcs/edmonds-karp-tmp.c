/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds-karp-tmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:35:14 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 04:58:42 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"
#include "../includes/algo.h"

void	print_path(t_route* route, int* parent, int path_id)
{
	int	v;

	if (parent[route->end] == -1)
	{
		printf("path %d: not found.\n", path_id);
		return ;
	}

	printf("path %d - [%d]:%s", path_id, route->end, route->node_map[route->end]);
	v = route->end;
	while (v != route->start)
	{
		v = parent[v];
		printf("<- [%d]:%s", v, route->node_map[v]);
	}
	printf("\n");
}

void	print_array(int *parent, int n)
{
	for (int u = 0; u < n; ++u)
		printf("%d ", parent[u]);
	printf("\n\n");
}

int bfs(t_route* route, int* parent, int capacity[][MAX_VERTICES])
{
	int n = route->graph->num_paths;
	int visited[n];
	t_queue queue;
	printf("%d\n", n);
	ft_memset(visited, 0, sizeof(visited));
	visited[route->start] = 1;
	init_queue(&queue);
	enqueue(&queue, route->start);

	while (!is_empty(&queue))
	{
		int u = dequeue(&queue);

		for (int v =0; v < n; v++)
		{
			// printf("visited:");
			// print_array(visited, n);
			// printf("current vertex: %d\n", v);
			// printf("node's vertex: %d\n", v);
			if (!visited[v] && capacity[u][v] > 0)
			{
				parent[v] = u;
				// printf("parent: ");
				// print_array(parent, n);
				visited[v] = 1;
				if (v == route->end)
					return (1);
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
}

void	edmonds_karp(t_route* route, t_graph* paths, int* parent, int capacity[][MAX_VERTICES])
{
	int	path_id = 0;

	while (bfs(route, parent, capacity) != -1)
	{
		int i = 0;
		for (int v = route->end; v != route->start; v = parent[v])
		{
			int u = parent[v];
			//printf("u, v = %d, %d\n", u, v);
			paths->paths[paths->num_paths][i++] = u;
			capacity[u][v] -= 1;
			capacity[v][u] += 1;
		}
		paths->num_paths++;
		path_id++;
		print_path(route, parent, path_id);
	}
}

void	fill_capacity(t_graph *graph, int capacity[][MAX_VERTICES])
{
	for (int u = 0; u < graph->num_paths; ++u)
	{
		for (int v = 0; v < graph->num_paths; ++v)
		{
			if (graph->paths[u][v] == 1)
				capacity[u][v] = 1;
		}
	}
}


void	print_capacity(int capacity[][MAX_VERTICES], int n)
{
	printf("\nprint capacity:\n\n");
	for (int u = 0; u < n; ++u)
	{
		for (int v = 0; v < n; ++v)
			printf("%d ", capacity[u][v]);
		printf("\n");
	}
}


void	print_paths(t_route* route, t_graph* paths)
{
	for (int i = 0; i < paths->num_paths; ++i)
	{
		int path[MAX_VERTICES];
		int path_len = 0;

		for (int j = 0; j < route->num_vertices; ++j)
		{
			if (paths->paths[i][j] != 0)
			{
				//printf("%d ", paths->paths[i][j]);
				path[path_len++] = paths->paths[i][j];
			}
		}
		//printf("path_len:%d\n", path_len);
		printf("path %d - [%d]:%s", i + 1, route->end, route->node_map[route->end]);
		for (int j = 0; j < path_len; ++j)
		{
			if (path[j] != route->start && path[j] != route->end)
				printf(" <- [%d]:%s", path[j], route->node_map[path[j]]);
		}
		printf(" <- [%d]:%s\n", route->start, route->node_map[route->start]);
	}
}
