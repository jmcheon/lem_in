/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:58:03 by sucho             #+#    #+#             */
/*   Updated: 2023/08/22 22:20:13 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

// void	free_list(t_list *head)
// {
// 	t_list* tmp;
// 	while (head != NULL)
// 	{
// 		tmp = head;
// 		head = head->next;
// 		free(tmp->content);
// 		free(tmp);
// 	}
// }


void	free_paths(t_list *paths)
{
	t_list *tmp;
	t_vertex_list *vertex_tmp;
	t_vertex_list *vertex_tmp_2;

	while (paths != NULL)
	{
		tmp = paths;
		vertex_tmp = tmp->content;
		while (vertex_tmp != NULL)
		{
			vertex_tmp_2 = vertex_tmp;
			vertex_tmp = vertex_tmp->next;
			free(vertex_tmp_2);
		}
		paths = paths->next;
		free(tmp);
	}
}

void	free_graph_edges(t_list *edges)
{
	t_list *tmp;

	while (edges != NULL)
	{
		tmp = edges;
		free((t_graph_edge*)tmp->content);
		edges = edges->next;
		free(tmp);
	}
}

void	free_edges_vertices(t_route *route)
{
	t_graph_vertex	*v;
	t_graph_vertex	*v2;
	t_list	*temp;
	int	size;

	for (int m = 0; m < route->num_vertices; m++)
	{
		v = graph_find_vertex(route->graph, m, IN);
		v2 = graph_find_vertex(route->graph, m, OUT);
		//printf("v->vertex:%d\n", v->vertex);

		size = ft_lstsize(v->in_list);
		for (int i = 0; i < size; i++)
		{
			temp = ft_lstfind_node(v->in_list, i);
			free(((t_graph_edge*)temp->content)->reverse_edge);
			free(temp->content);
			free(temp);
		}
		size = ft_lstsize(v->out_list);
		for (int i = 0; i < size; i++)
		{
			temp = ft_lstfind_node(v->out_list, i);
			free(((t_graph_edge*)temp->content)->reverse_edge);
			free(temp->content);
			free(temp);
		}
		size = ft_lstsize(v2->in_list);
		for (int i = 0; i < size; i++)
		{
			temp = ft_lstfind_node(v2->in_list, i);
			free(((t_graph_edge*)temp->content)->reverse_edge);
			free(temp->content);
			free(temp);
		}
		size = ft_lstsize(v2->out_list);
		for (int i = 0; i < size; i++)
		{
			temp = ft_lstfind_node(v2->out_list, i);
			free(((t_graph_edge*)temp->content)->reverse_edge);
			free(temp->content);
			free(temp);
		}
		free(v);
		free(v2);
	}
}
