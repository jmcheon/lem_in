/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:59:05 by sucho             #+#    #+#             */
/*   Updated: 2023/08/14 16:35:00 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTS_H
# define ANTS_H

typedef struct s_path_len
{
	int value;
	int index;
	int	num_ants;
} t_path_len;

/*
**	ants_quicksort.c
*/
void swap(t_path_len **a, t_path_len **b);
// not used, just for reference
int partition_asc(t_path_len **arr, int low, int high);
int partition_desc(t_path_len **arr, int low, int high);
void quicksort(t_path_len **arr, int low, int high);


/*
**	ants_dist.c
*/
void ants_dist_fillin(int *ant_dist, t_path_len **elements, t_route route, int dist_begin);
int	ants_find_dist_begin(t_path_len **elements, int num_paths, int num_ants);
t_path_len **ants_init_elements(t_route route, int num_paths);
t_path_len **ants_distribute(t_route route);

#endif
