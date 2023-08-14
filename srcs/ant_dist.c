/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 07:19:48 by sucho             #+#    #+#             */
/*   Updated: 2023/08/13 02:21:49 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"


// Function to swap two elements
void swap(t_path_len **a, t_path_len **b)
{
	t_path_len *temp = *a;
	*a = *b;
	*b = temp;
}

int partition_asc(t_path_len **arr, int low, int high)
{
	int pivot = arr[high]->value;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j]->value < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int partition_desc(t_path_len **arr, int low, int high)
{
	int pivot = arr[high]->value;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j]->value > pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

// Function to perform Quicksort
void quicksort(t_path_len **arr, int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partition_desc(arr, low, high);
		quicksort(arr, low, pivotIndex - 1);
		quicksort(arr, pivotIndex + 1, high);
	}
}

int	ft_intlen(int *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

t_path_len **distribute_ant(t_route route)
{
	// printf("num_paths:%d\tant_num:%d\n", route.paths->num_paths, route.num_ants);

	t_path_len **elements;

	elements = (t_path_len**)malloc(sizeof(t_path_len*) * (route.paths->num_paths + 1));

	int i = 0;
	while (i < route.paths->num_paths)
	{
		elements[i] = (t_path_len*)malloc(sizeof(t_path_len));
		i++;
	}
	elements[i] = NULL;

	i =0;
	while (i < route.paths->num_paths)
	{
		elements[i]->index = i;
		elements[i]->value = ft_intlen(route.paths->paths[i]); // start and end
		elements[i]->num_ants = 0;
		i++;
	}



    // printf("Original array:\n");
    // for (int i = 0; i < route.paths->num_paths; i++) {
    //     printf("%d ", elements[i]->value);
    // }
    // printf("\n");

	quicksort(elements, 0, route.paths->num_paths - 1);

    // printf("Sorted array in descending order:\n");
    // for (int i = 0; i < route.paths->num_paths; i++) {
    //     printf("%d (Index: %d) ", elements[i]->value, elements[i]->index);
    // }
	// printf("\n");

	int dist_begin = 0;
	for (int i = 0; i < route.paths->num_paths; i++)
	{
		int tmp = 0;
		for (int j = i + 1; j < route.paths->num_paths; j++)
			tmp += (elements[i]->value - elements[j]->value);
		// printf("tmp:%d\n", tmp);
		// printf("tmp2:%d \n", tmp + (route.paths->num_paths - i));
		if (tmp + (route.paths->num_paths - i) < route.num_ants)
		{
			dist_begin = i;
			break;
		}
	}
	// printf("distribution begins from here: [%d]\n", dist_begin);

	int ant_num_temp = route.num_ants;
	int dist_len = route.paths->num_paths - dist_begin;

	int ant_dist[route.paths->num_paths];

	ft_memset(&ant_dist, 0, sizeof(ant_dist));

	// printf("%d\n", dist_len);

	for (int i = route.paths->num_paths - 1; i > dist_begin; i--)
	{
		int dist = elements[i - 1]->value - elements[i]->value;
		ant_dist[i] += dist;
		ant_num_temp -= dist;
	}

	// printf("ant_num_temp:[%d]\n",ant_num_temp);

	int ant_remainder = ant_num_temp % dist_len;
	// printf("ant_num_temp:%d\tdist_len:%d\ttmp:%d\n", ant_num_temp, dist_len, ant_remainder);
	for(int i= route.paths->num_paths - 1; i >= dist_begin; i--)
	{
		ant_dist[i] += ant_num_temp / dist_len;
		// printf("ant_dist[%d]:%d\t%d\n",i, ant_dist[i], ant_num_temp / route.paths->num_paths);
		if (ant_remainder != 0)
		{
			ant_dist[i] += 1;
			ant_remainder--;
		}
	}

	// printf("=========================\n");

	for(int i = 0; i < route.paths->num_paths; i++)
		elements[i]->num_ants = ant_dist[i];
	return (elements);

}
