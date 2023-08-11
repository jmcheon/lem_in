/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 07:19:48 by sucho             #+#    #+#             */
/*   Updated: 2023/08/11 08:03:46 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_path_len
{
	int value;
	int index;
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

	int ant_num = 5;
	int arr[] = {2, 3};
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
		if (elements[i].value >= ant_num)
		{
			dist_begin = i;
			break;
		}
	}
	printf("distribution begins from here:[%d]\n", dist_begin);

	int ant_num_temp = ant_num;
	int dist_len = n - dist_begin;
	int ant_dist[dist_len];

	ft_memset(&ant_dist, 0, dist_len);

	for (int i = 1; i < dist_len ; i++)
	{
		printf("hello\n");
		ant_dist[i] = elements[dist_begin + i - 1].value - elements[dist_begin + i].value;
		ant_num_temp -= ant_dist[i];
		printf("ant_dist[%d]:%d\n",i, ant_dist[i]);
	}

	printf("ant_num_temp:[%d]\n",ant_num_temp);
	printf("ant_num_dist:[%d] remainder:[%d]\n",ant_num_temp / n, ant_num_temp % n);

	for(int i = 0; i < n; i++)
	{
		printf("ant_dist[%d]:%d\n",i, ant_dist[i]);
	}

	int tmp = ant_num_temp % n;
	for(int i=n - 1; i >= 0; i--)
	{
		ant_dist[i] += ant_num_temp / n;
		printf("ant_dist[%d]:%d\t%d\n",i, ant_dist[i], ant_num_temp / n);
		if (tmp != 0)
		{
			ant_dist[i] += 1;
			tmp--;
		}
	}

	for(int i = 0; i < n; i++)
	{
		printf("ant_dist[%d]:%d\n",i, ant_dist[i]);
	}

	return 0;
}
