/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dist2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:19:38 by sucho             #+#    #+#             */
/*   Updated: 2023/08/22 21:31:47 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

void	ants_setup_elements2(t_path_len **elements, t_list *paths)
{
	t_list *paths_head;
	t_list *onepath_head;
	int i;
	int j;

	paths_head = paths;
	// onepath_head = (t_vertex_list*)paths_head->content;
	i = 0;
	while (paths_head != NULL)
	{
		elements[i]->index = i;
		j = 0;
		onepath_head = (t_list*)paths_head->content;

		while(onepath_head != NULL)
		{
			j++;
			// printf("vertex:%d\n", onepath_head->vertex);
			onepath_head = onepath_head->next;
		}
		// printf("j:%d\n",j);
		elements[i]->value = j; // start and end
		elements[i]->num_ants = 0;
		i++;
		paths_head = paths_head->next;
	}

}

t_path_len	**ants_init_elements2(t_list *paths, int num_paths)
{
	t_path_len **ret;

	ret = (t_path_len**)malloc(sizeof(t_path_len*) * (num_paths + 1));
	int i = 0;
	while (i < num_paths)
	{
		ret[i] = (t_path_len*)malloc(sizeof(t_path_len));
		i++;
	}
	ret[i] = NULL;
	ants_setup_elements2(ret, paths);

	return (ret);
}

void	ants_distribute_2(t_route *route, t_list *paths)
{
	t_path_len **elements;

	(void)route;
	int paths_num = ft_lstsize(paths);
	printf("paths_num: %d\n", paths_num);

	elements = ants_init_elements2(paths, paths_num);

	(void)elements;

    printf("Original array:\n");
    for (int i = 0; i < paths_num; i++) {
        printf("%d ", elements[i]->value);
    }
    printf("\n");
	quicksort(elements, 0, paths_num - 1);
	printf("Sorted array in descending order:\n");
    for (int i = 0; i < paths_num; i++) {
        printf("%d (Index: %d) ", elements[i]->value, elements[i]->index);
    }
	printf("\n");


	int dist_begin;
	dist_begin = ants_find_dist_begin(elements, \
								paths_num, route->num_ants);
	printf("distribution begins from here: [%d]\n", dist_begin);
	// elements = ants_init_elements2(route, )

}
