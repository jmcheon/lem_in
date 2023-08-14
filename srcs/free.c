/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:58:03 by sucho             #+#    #+#             */
/*   Updated: 2023/08/14 04:02:19 by sucho            ###   ########.fr       */
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
