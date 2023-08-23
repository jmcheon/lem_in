/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_quicksort2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:58:26 by sucho             #+#    #+#             */
/*   Updated: 2023/08/24 00:05:48 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-in.h"
void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_desc2(int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] > pivot)
        {
            i++;
            swap2(&arr[i], &arr[j]);
        }
    }
    swap2(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort_int_array(int *arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition_desc2(arr, low, high);
        quicksort_int_array(arr, low, pivotIndex - 1);
        quicksort_int_array(arr, pivotIndex + 1, high);
    }
}
