/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_print_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:36:46 by sucho             #+#    #+#             */
/*   Updated: 2023/08/14 16:39:16 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"
void	pass_ants_to_nodes(t_ants_print **test, int total_used_path, int start, int end)
{
	for (int i = 0; i < total_used_path; i++)
	{
		for(int j = start; j <= end; j++)
		{
			if (test[i][j].node_name != NULL)
			{
				// printf("[%s] ", test[i][j].node_name);
				test[i][j].ant_current++;
			}
		}
	}
}

void	print_one_frame(t_ants_print **test, int total_used_path, int longest_path)
{
	for (int i = 0; i < total_used_path; i++)
	{
		for(int j = 0; j <= longest_path; j++)
		{
			if (test[i][j].node_name != NULL && \
				test[i][j].ant_current <= test[i][j].ant_max &&\
				test[i][j].ant_current != 0)
				printf("L%d-%s ", test[i][j].ant_current, test[i][j].node_name);
		}
	}
}

void print_frames(t_route route, t_path_len **elements)
{
	int longest_path = 0;
	int total_used_path = 0;
	for(int i = 0; i < route.paths->num_paths; i++)
	{
		if (elements[i]->num_ants > 0)
		{
			if (longest_path < elements[i]->value)
				longest_path = elements[i]->value;
			total_used_path++;
		}
	}
	// printf("longest_path:%d total_used_path:%d\n", longest_path, total_used_path);

	t_ants_print **test;
	test = (t_ants_print **)malloc(sizeof(t_ants_print *) * (total_used_path +1));
	if (!test)
		return ;
	int i = 0;
	while (i < total_used_path)
	{
		test[i] = (t_ants_print *)malloc(sizeof(t_ants_print) * (longest_path + 1));
		for (int j = 0; j <= longest_path; j++)
			test[i][j].node_name = NULL;
		ft_memset(test[i], '\0', sizeof(test[i]));
		i++;
	}
	// test[i] = NULL;


	i = 0;
	while (i < total_used_path)
	{
		// printf("[%d]", (route.paths->num_paths - total_used_path) + i);
		t_vertex_list *one_path = ft_lstfind_node(route.paths->paths, elements[(route.paths->num_paths - total_used_path) + i]->index)->content;
		while (one_path != NULL)
		{
			if (one_path->next == NULL)
				break;
			one_path = one_path->next;
		}
		// int begin = longest_path - elements[i]->value;
		int begin = 0;
		one_path = one_path->prev;
		// printf("begin:%d\ti:%d\n", begin, i);
		while (one_path != NULL)
		{
			// needs to change
			test[i][begin].node_name = route.node_map[one_path->vertex];
			test[i][begin].ant_max = elements[(route.paths->num_paths - total_used_path) + i]->num_ants;
			test[i][begin].ant_current = 0;
			// printf("%d ",one_path->vertex);
			begin++;
			one_path = one_path->prev;
		}
		// printf("\n");
		i++;
	}

	// printf("================================\n");
	// i = 0;
	// while (i < total_used_path)
	// {
	// 	int j = 0;
	// 	while (j < longest_path)
	// 	{
	// 		if (test[i][j].node_name == NULL)
	// 			printf("[null] ");
	// 		else
	// 			printf("[%s] ",test[i][j].node_name);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// printf("================================\n");

	int loop = 0;
	for(int i = route.paths->num_paths - total_used_path ; i < route.paths->num_paths; i++)
	{
		if (loop < elements[i]->value + elements[i]->num_ants)
			loop = elements[i]->value + elements[i]->num_ants;
	}
	// printf("loop:%d\n", loop);

	for(int i = 0; i < (loop - 1); i++)
	{
		if (i < longest_path)
		{
			// printf("begin:%d end:%d\n", 0, i);
			pass_ants_to_nodes(test, total_used_path, 0, i);
		}
		// else if (loop - i < longest_path)
		// {
		// 	// printf("begin:%d end:%d\n", i - (loop - longest_path), longest_path);
		// 	// for checking
		// 	// printf("another condition:%d\n", i - (loop - longest_path));
		// 	pass_ants_to_nodes(test, route, i - (loop - longest_path), longest_path, false);
		// }
		else
		{
			// printf("begin:%d end:%d\n", 0, longest_path);
			pass_ants_to_nodes(test, total_used_path, 0, longest_path);
		}

		print_one_frame(test, total_used_path, longest_path);
		printf("\n");
	}

	i = 0;
	while (i < total_used_path)
	{
		free(test[i]);
		i++;
	}
	free(test);

}
