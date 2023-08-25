/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:58:03 by sucho             #+#    #+#             */
/*   Updated: 2023/08/25 22:27:01 by cjung-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	free_list_ptr(t_list *head)
{
	t_list* tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	free_paths(t_list *paths)
{
	t_list *tmp;
	t_vertex_list *vertex_head;
	t_vertex_list *vertex_tmp;
	t_vertex_list *vertex_tmp_2;

	while (paths != NULL)
	{
		tmp = paths;
		vertex_tmp = tmp->content;
		vertex_head = vertex_tmp;
		vertex_tmp_2 = vertex_tmp;
		vertex_tmp = vertex_tmp->next;
		free(vertex_tmp_2);
		while (vertex_tmp != vertex_head)
		{
			vertex_tmp_2 = vertex_tmp;
			vertex_tmp = vertex_tmp->next;
			free(vertex_tmp_2);
		}
		paths = paths->next;
		free(tmp);
	}
}

void	free_vertices_edge_inout_lists(t_route *route)
{
	t_graph_vertex	*v;
	t_list	*temp;
	t_list	*temp2;

	(void)temp2;
	for (int i = 0; i < route->num_vertices; i++)
	{
		v = multishot_find_vertex(route->graph, i, IN);
		temp = v->in_list;
		while (temp != NULL)
		{
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
		temp = v->out_list;
		while (temp != NULL)
		{
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}

		v = multishot_find_vertex(route->graph, i, OUT);
		temp = v->in_list;
		while (temp != NULL)
		{
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
		temp = v->out_list;
		while (temp != NULL)
		{
			temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
	}
}

void	free_edges_lists(t_route *route)
{
	t_list	*temp;
	t_list	*temp2;

	temp = route->graph->edge_list;
	while (temp != NULL)
	{
		free(temp->content);
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	temp = route->graph->rev_edge_list;
	while (temp != NULL)
	{
		free(temp->content);
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}

void	free_vertices_inout_lists(t_route *route)
{
	t_list	*temp;
	t_list	*temp2;

	temp = route->graph->v_in_list;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		free(temp2->content);
		free(temp2);
	}
	temp = route->graph->v_out_list;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		free(temp2->content);
		free(temp2);
	}
}
