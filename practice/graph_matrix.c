#include <stdio.h>
#include <stdlib.h>


// https://velog.io/@kysung95/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0-C%EB%A1%9C-%EA%B7%B8%EB%9E%98%ED%94%84%EB%A5%BC-%EB%A7%8C%EB%93%A4%EC%9E%90
#define MAX_VERTICES 10

typedef struct s_graph
{
	int	n; // 실 정점의 개수
	int	matrix[MAX_VERTICES][MAX_VERTICES];
}				t_graph;

void	graph_init(t_graph *graph)
{
	int	row;
	int	col;

	row = 0;
	graph->n = 0;
	while (row < MAX_VERTICES)
	{
		col = 0;
		while (col < MAX_VERTICES)
		{
			graph->matrix[row][col] = 0;
			col++;
		}
		row++;
	}
}

void	graph_insert_vertex(t_graph *graph, int n)
{
	if (((graph->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "overflow");
		return ;
	}
	graph->n++;
}

void	graph_insert_edge(t_graph *graph, int start, int end)
{
	if (start >= graph->n || end >= graph->n)
	{
		printf("vertex key error");
		return ;
	}
	graph->matrix[start][end] = 1;
	graph->matrix[end][start] = 1;
}

void	graph_print(t_graph *graph)
{
	int	i;
	int	j;

	i = 0;
	while (i < graph->n)
	{
		j = 0;
		while (j < graph->n)
		{
			printf("%2d", graph->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(void)
{
	t_graph	*g;

	g = (t_graph *)malloc(sizeof(t_graph));
	graph_init(g);
	for (int i = 0; i < 4; i++)
	{
		graph_insert_vertex(g, i);
	}
	graph_insert_edge(g, 0, 1);
	graph_insert_edge(g, 0, 2);
	graph_insert_edge(g, 0, 3);
	graph_insert_edge(g, 1, 2);
	graph_insert_edge(g, 2, 3);
	graph_print(g);
}
