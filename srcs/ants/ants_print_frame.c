/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_print_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:36:46 by sucho             #+#    #+#             */
/*   Updated: 2023/08/14 22:06:23 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"
void	ants_pass_to_matrix(t_ants_print **test, int total_used_path, int start, int end)
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

void	ants_print_oneframe(t_ants_print **test, int total_used_path, int longest_path)
{
	for (int i = 0; i < total_used_path; i++)
	{
		for(int j = 0; j <= longest_path; j++)
		{
			if (test[i][j].node_name != NULL && \
				test[i][j].ant_current <= test[i][j].ant_max &&\
				test[i][j].ant_current != 0)
			{
				ft_putchar_fd('L', STDOUT_FILENO);
				ft_putnbr_fd(test[i][j].ant_current, STDOUT_FILENO);
				ft_putchar_fd('-', STDOUT_FILENO);
				ft_putstr_fd(test[i][j].node_name, STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}
		}
	}
}

void	ants_setup_prints_strt(t_ants_print **matrix, t_path_len **elements, t_route route, int total_used)
{
	int	i = 0;
	while (i < total_used)
	{
		// printf("[%d]", (route.paths->num_paths - total_used_path) + i);
		t_vertex_list *one_path = ft_lstfind_node(route.paths->paths, elements[(route.paths->num_paths - total_used) + i]->index)->content;
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
			matrix[i][begin].node_name = route.node_map[one_path->vertex];
			matrix[i][begin].ant_max = elements[(route.paths->num_paths - total_used) + i]->num_ants;
			matrix[i][begin].ant_current = 0;
			// printf("%d ",one_path->vertex);
			begin++;
			one_path = one_path->prev;
		}
		// printf("\n");
		i++;
	}

}

t_ants_print	**ants_init_ants_print(int longest, int total_used)
{
	t_ants_print **test;
	test = (t_ants_print **)malloc(sizeof(t_ants_print *) * (total_used +1));
	if (!test)
		exit(1);
	int i = 0;
	while (i < total_used)
	{
		test[i] = (t_ants_print *)malloc(sizeof(t_ants_print) * (longest + 1));
		for (int j = 0; j <= longest; j++)
			test[i][j].node_name = NULL;
		ft_memset(test[i], '\0', sizeof(test[i]));
		i++;
	}
	test[i] = NULL;
	return (test);
}

void	ants_set_path_vars(t_route route, t_path_len **elements, int *longest, int *total_used)
{
	for(int i = 0; i < route.paths->num_paths; i++)
	{
		if (elements[i]->num_ants > 0)
		{
			if (*longest < elements[i]->value)
				*longest = elements[i]->value;
			(*total_used)++;
		}
	}
}

void ants_print_frames(t_route route, t_path_len **elements)
{
	t_ants_print **ants_print_matrix;
	int longest_path;
	int total_used_path;

	longest_path = 0;
	total_used_path = 0;
	ants_set_path_vars(route, elements, &longest_path, &total_used_path);

	// printf("longest_path:%d total_used_path:%d\n", longest_path, total_used_path);


	ants_print_matrix = ants_init_ants_print(longest_path, total_used_path);
	ants_setup_prints_strt(ants_print_matrix, elements, route, total_used_path);

	// int	i = 0;
	// while (i < total_used_path)
	// {
	// 	// printf("[%d]", (route.paths->num_paths - total_used_path) + i);
	// 	t_vertex_list *one_path = ft_lstfind_node(route.paths->paths, elements[(route.paths->num_paths - total_used_path) + i]->index)->content;
	// 	while (one_path != NULL)
	// 	{
	// 		if (one_path->next == NULL)
	// 			break;
	// 		one_path = one_path->next;
	// 	}
	// 	// int begin = longest_path - elements[i]->value;
	// 	int begin = 0;
	// 	one_path = one_path->prev;
	// 	// printf("begin:%d\ti:%d\n", begin, i);
	// 	while (one_path != NULL)
	// 	{
	// 		// needs to change
	// 		ants_print_matrix[i][begin].node_name = route.node_map[one_path->vertex];
	// 		ants_print_matrix[i][begin].ant_max = elements[(route.paths->num_paths - total_used_path) + i]->num_ants;
	// 		ants_print_matrix[i][begin].ant_current = 0;
	// 		// printf("%d ",one_path->vertex);
	// 		begin++;
	// 		one_path = one_path->prev;
	// 	}
	// 	// printf("\n");
	// 	i++;
	// }

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
			ants_pass_to_matrix(ants_print_matrix, total_used_path, 0, i);
		}
		// else if (loop - i < longest_path)
		// {
		// 	// printf("begin:%d end:%d\n", i - (loop - longest_path), longest_path);
		// 	// for checking
		// 	// printf("another condition:%d\n", i - (loop - longest_path));
		// 	ants_pass_to_matrix(test, route, i - (loop - longest_path), longest_path, false);
		// }
		else
		{
			// printf("begin:%d end:%d\n", 0, longest_path);
			ants_pass_to_matrix(ants_print_matrix, total_used_path, 0, longest_path);
		}

		ants_print_oneframe(ants_print_matrix, total_used_path, longest_path);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}

	int i = 0;
	while (i < total_used_path)
	{
		free(ants_print_matrix[i]);
		i++;
	}
	free(ants_print_matrix);

}
