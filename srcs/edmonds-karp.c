#include "../includes/algo.h"
#include "../includes/lem-in.h"

int	bfs(int start, int end, int* parent, t_graph_type* graph, int capacity[][MAX_VERTICES])
{
	int	n = graph->n;
	int	visited[n];
	t_queue	queue;

	ft_memset(visited, 0, sizeof(visited));
	visited[start] = 1;
	init_queue(&queue);
	enqueue(&queue, start);

	while (!is_empty(&queue))
	{
		//printf("queue is not empty.. checking..\n");
		int u = dequeue(&queue);

		for (t_graph_node* node = graph->adj_list[u]; node != NULL; node = node->link)
		{
			printf("visited:");
			print_array(visited, n);
			int v = node->vertex;
			//printf("node's vertex: %d\n", v);
			if (!visited[v] && capacity[u][v] > 0)
			{
				parent[v] = u;
				printf("parent: ");
				print_array(parent, n);
				visited[v] = 1;
				if (v == end)
					return (1);
				enqueue(&queue, v);
			}
		}
	}
	return (-1);
}

void	print_path(int start, int end, int* parent, char** node_map, int path_id)
{
	int	v;

	if (parent[end] == -1)
	{
		printf("path %d: not found.\n", path_id);
		return ;
	}

	printf("path %d: %s", path_id, node_map[end]);
	v = end;
	while (v != start)
	{
		v = parent[v];
		//printf("<- %d", v);
		printf("<- %s", node_map[v]);
	}
	printf("\n");
}

void	fill_capacity(t_graph_type* graph, int capacity[][MAX_VERTICES])
{
	for (int u = 0; u < graph->n; ++u)
	{
		t_graph_node* node = graph->adj_list[u];
		while (node != NULL)
		{
			int v = node->vertex;
			capacity[u][v] = 1;
			capacity[v][u] = 1;
			node = node->link;
		}
	}
}

void	print_capacity(int capacity[][MAX_VERTICES], int n)
{
	for (int u = 0; u < n; ++u)
	{
		for (int v = 0; v < n; ++v)
			printf("%d ", capacity[u][v]);
		printf("\n");
	}
}

void	print_array(int *parent, int n)
{
	for (int u = 0; u < n; ++u)
	{
		printf("%d ", parent[u]);
	}
	printf("\n\n");
}

int	main(void)
{
	t_parse	*parse;
	t_graph_type*	graph;
	int		list_size;
	char**	node_map;

	int start, end;
	int	n;
	int	max_flow = 0;
	int	capacity[MAX_VERTICES][MAX_VERTICES] = {0};
	int	parent[MAX_VERTICES];

	parse = parsing();
	printf("parse result:\n");
	parse_result_print(parse);
	graph = parse_to_graph(parse);
	list_size = ft_lstsize(parse->nodes_head);
	node_map = (char**)malloc(sizeof(char*) * list_size);
	node_map[list_size] = NULL;
	node_map_to_array(parse->nodes_head, node_map);


	print_adj_list(graph);
	n = graph->n;
	start = 0; //ft_atoi(node_map[0]);
	end = list_size - 2; //ft_atoi(node_map[list_size - 2]);

	printf("number of vertices: %d\n", n);
	printf("start: (%d)\n", start);
	printf("end: (%d)\n", end);
	fill_capacity(graph, capacity);
	print_capacity(capacity, n);

	while (bfs(start, end, parent, graph, capacity) != -1)
	{
		int	path_flow = INT_MAX;

		for (int v = end; v != start; v = parent[v])
		{
			int u = parent[v];
			path_flow = (capacity[u][v] < path_flow) ? capacity[u][v] : path_flow;
		}


		for (int v = end; v != start; v = parent[v])
		{
			int u = parent[v];
			capacity[u][v] -= path_flow;
			capacity[v][u] += path_flow;
		}
		max_flow += path_flow;
		print_path(start, end, parent, node_map, max_flow);
	}
	print_path(start, end, parent, node_map, max_flow);
	return (0);
}
