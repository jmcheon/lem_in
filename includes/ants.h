/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:59:05 by sucho             #+#    #+#             */
/*   Updated: 2023/08/23 16:39:52 by sucho            ###   ########.fr       */
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

typedef struct s_ants_print
{
	char *node_name;
	int	ant_max;
	int ant_current;
}	t_ants_print;

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

/*
**	ants_print_frame.c
*/
void	ants_pass_to_matrix(t_ants_print **test, int total_used_path, int start, int end, int *ant_index, int total_ants);
void	ants_print_oneframe(t_ants_print **test, int total_used_path, int longest_path);
void	ants_setup_prints_strt(t_ants_print **matrix, t_path_len **elements, t_route route, int total_used);
t_ants_print	**ants_init_ants_print(int longest, int total_used);

void	ants_print_frames(t_route route, t_path_len **elements);

/*
**	ants_print_frame.c
*/
int	ants_check_loop_len(t_route *route, t_list *paths);
t_path_len	**ants_init_elements2(t_list *paths, int num_paths);
void	ants_setup_elements2(t_path_len **elements, t_list *paths);
void	ants_dist_fillin2(int *ant_dist, t_path_len **elements, int paths_num, int dist_begin, int num_ants);

#endif
