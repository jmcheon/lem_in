/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:39:43 by sucho             #+#    #+#             */
/*   Updated: 2023/08/09 20:01:37 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

#define MAX_VERTICES 50

typedef struct s_graph_node
{
	int vertex;
	struct s_graph_node *link;
} t_graph_node;

typedef struct s_graph_type
{
	int n;
	t_graph_node *adj_list[MAX_VERTICES];
} t_graph_type;

void init(t_graph_type *graph)
{
	int v;

	graph->n = 0;
	v = 0;
	while (v < MAX_VERTICES)
	{
		graph->adj_list[v] = NULL;
		v++;
	}
}

void insert_vertex(t_graph_type *g, int v)
{
	(void)v;

	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "overflow");
		return;
	}
	g->n++;
}

// link in reverse way
// void insert_edge(t_graph_type *g, int u, int v)
// {
// 	t_graph_node* node;
//     if(u>=g->n||v>=g->n){
//         fprintf(stderr,"vertex index error");
//         return;
//     }

// 	node = (t_graph_node *)malloc(sizeof(t_graph_node));
// 	node->vertex = v;
// 	node->link = g->adj_list[u];
// 	g->adj_list[u] = node;
// }

void insert_edge(t_graph_type *g, int u, int v)
{
	if (u >= g->n || v >= g->n)
	{
		printf("vertex index error\n");
		return;
	}

	// create a new edge node
	t_graph_node *new_edge = malloc(sizeof(t_graph_node));
	new_edge->vertex = v;
	new_edge->link = NULL;

	// add new edge node to the end of the adjacency list for vertex u
	if (g->adj_list[u] == NULL)
	{
		g->adj_list[u] = new_edge;
	}
	else
	{
		t_graph_node *curr = g->adj_list[u];
		while (curr->link != NULL)
		{
			curr = curr->link;
		}
		curr->link = new_edge;
	}
}

void print_adj_list(t_graph_type *g)
{
	int i;
	// int j;

	i = 0;
	while (i < g->n)
	{
		t_graph_node *p = g->adj_list[i];
		printf("node [%d]", i);
		while (p != NULL)
		{
			printf("->%d", p->vertex);
			p = p->link;
		}
		printf("\n");
		i++;
	}
}

static void	swap_start_end(char **node_map, char *start, char *end, int array_len)
{
	int i;
	char *str_tmp;

	i = 0;
	while (i < array_len)
	{
		if (ft_strncmp(node_map[i], start, ft_strlen(start)) == 0)
		{
			str_tmp = node_map[0];
			node_map[0] = start;
			node_map[i] = str_tmp;
		}

		i++;
	}
	i = 0;
	while (i < array_len)
	{
		if (ft_strncmp(node_map[i], end, ft_strlen(end)) == 0)
		{
			str_tmp = node_map[array_len - 1];
			node_map[array_len - 1] = end;
			node_map[i] = str_tmp;
		}
		i++;
	}
}

void node_map_to_array(t_list *nodes_head, char **node_map)
{
	int i;
	t_node_xy *tmp;
	char *start;
	char *end;

	start = NULL;
	end = NULL;
	i = 0;
	while (nodes_head != 0)
	{
		if (nodes_head->content == NULL)
			break;
		tmp = nodes_head->content;
		node_map[i] = tmp->name;
		if (tmp->node_type == PARSE_XY_START)
			start = tmp->name;
		else if (tmp->node_type == PARSE_XY_END)
			end = tmp->name;
		i++;
		nodes_head = nodes_head->next;
	}
	swap_start_end(node_map, start, end, i);
}

int	node_find_index(char **node_array, char *node_name)
{
	int i;

	i = 0;
	(void) node_name;
	while (node_array[i] != NULL)
	{
		if (ft_strncmp(node_array[i], node_name, ft_strlen(node_name)) == 0)
		// {
			// printf("node_array:[%s]\n", node_array[i]);
			break ;
		// }
		i++;
	}
	return i;
}


void parse_to_graph(t_parse *parse)
{
	t_graph_type *g;
	t_edge *tmp;

    int list_size = ft_lstsize(parse->nodes_head) - 1;
    char **node_map;


	node_map = (char **)malloc(sizeof(char *) * (list_size + 1));

	int i = 0;
	while (i < list_size)
	{
		node_map[i] = (char *)malloc(sizeof(char *) + 1);
		i++;
	}
	node_map[i] = NULL;


	node_map[list_size] = NULL;
	node_map_to_array(parse->nodes_head, node_map);

	i = 0;
	while (i < (list_size - 1))
	{
		printf("index: %d, str:[%s]\n", i, node_map[i]);
		i++;
	}

	g = (t_graph_type*)malloc(sizeof(t_graph_type));
	init(g);
	for(int i=0 ; i< ft_lstsize(parse->nodes_head) - 1; i++)
	    insert_vertex(g,i);

	t_list *list_tmp;
	list_tmp = parse->edge_info_head;
	for(int i = 0; i < ft_lstsize(parse->edge_info_head) - 1; i++)
	{
		if(list_tmp->content == NULL)
			break;
		tmp = list_tmp->content;
		insert_edge(g, node_find_index(node_map, tmp->key), node_find_index(node_map, tmp->val));
		insert_edge(g, node_find_index(node_map, tmp->val), node_find_index(node_map, tmp->key));
		list_tmp = list_tmp->next;

	}

	// 	parse->edge_info_head = parse->edge_info_head->next;
	// }
	// insert_edge(g,0,1);
	// insert_edge(g,1,0);
	// insert_edge(g,0,2);
	// insert_edge(g,2,0);
	// insert_edge(g,0,3);
	// insert_edge(g,3,0);
	// insert_edge(g,1,2);
	// insert_edge(g,2,1);
	// insert_edge(g,2,3);
	// insert_edge(g,3,2);
	print_adj_list(g);

	// free(g);
}
