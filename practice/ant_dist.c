/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 07:19:48 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 15:53:02 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_path_len
{
	int value;
	int index;
	int	num_ants;
} t_path_len;

// Function to swap two elements
void swap(t_path_len *a, t_path_len *b)
{
	t_path_len temp = *a;
	*a = *b;
	*b = temp;
}

int partition_asc(t_path_len arr[], int low, int high)
{
	int pivot = arr[high].value;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j].value < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int partition_desc(t_path_len arr[], int low, int high)
{
	int pivot = arr[high].value;
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j].value > pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

// Function to perform Quicksort
void quicksort(t_path_len arr[], int low, int high)
{
	if (low < high)
	{
		int pivotIndex = partition_desc(arr, low, high);
		quicksort(arr, low, pivotIndex - 1);
		quicksort(arr, pivotIndex + 1, high);
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr_b;

	ptr_b = (unsigned char *)b;
	while (len--)
		*ptr_b++ = (unsigned char)c;
	return (b);
}

int main()
{

	int ant_num = 9;
	int arr[] = {2, 8, 3};
	int n = sizeof(arr) / sizeof(arr[0]);

	t_path_len elements[n];

	for (int i = 0; i < n; i++)
	{
		elements[i].value = arr[i];
		elements[i].index = i;
	}

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", elements[i].value);
    }
    printf("\n");

	quicksort(elements, 0, n - 1);

    printf("Sorted array in descending order:\n");
    for (int i = 0; i < n; i++) {
        printf("%d (Index: %d) ", elements[i].value, elements[i].index);
    }
	printf("\n");

	int dist_begin = 0;
	for (int i = 0; i < n; i++)
	{
		int tmp = 0;
		for (int j = i + 1; j < n; j++)
			tmp += (elements[i].value - elements[j].value);
		printf("tmp:%d\n", tmp);
		printf("tmp2:%d \n", tmp + (n - i));
		if (tmp + (n - i) < ant_num )
		{
			dist_begin = i;
			break;
		}
	}
	printf("distribution begins from here: [%d]\n", dist_begin);

	int ant_num_temp = ant_num;
	int dist_len = n - dist_begin;

	int ant_dist[n];

	ft_memset(&ant_dist, 0, sizeof(ant_dist));

	printf("%d\n", dist_len);

	for (int i = n - 1; i > dist_begin; i--)
	{
		int dist = elements[i - 1].value - elements[i].value;
		ant_dist[i] += dist;
		ant_num_temp -= dist;
	}

	printf("ant_num_temp:[%d]\n",ant_num_temp);

	int ant_remainder = ant_num_temp % dist_len;
	printf("ant_num_temp:%d\tdist_len:%d\ttmp:%d\n", ant_num_temp, dist_len, ant_remainder);
	for(int i=n - 1; i >= dist_begin; i--)
	{
		ant_dist[i] += ant_num_temp / dist_len;
		printf("ant_dist[%d]:%d\t%d\n",i, ant_dist[i], ant_num_temp / n);
		if (ant_remainder != 0)
		{
			ant_dist[i] += 1;
			ant_remainder--;
		}
	}

	printf("=========================\n");

	for(int i = 0; i < n; i++)
		elements[i].num_ants = ant_dist[i];

	for(int i = 0; i < n; i++)
		printf("elements - value: %d\t index:%d\tnum_ants:%d\n", \
			elements[i].value, elements[i].index, elements[i].num_ants);

	return 0;
}
