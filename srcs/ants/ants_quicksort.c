/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_quicksort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:58:26 by sucho             #+#    #+#             */
/*   Updated: 2023/08/14 16:05:46 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"

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

void quicksort(t_path_len **arr, int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partition_desc(arr, low, high);
		quicksort(arr, low, pivotIndex - 1);
		quicksort(arr, pivotIndex + 1, high);
	}
}
