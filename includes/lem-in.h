/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:07:32 by sucho             #+#    #+#             */
/*   Updated: 2023/08/12 10:23:58 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"
# include "./queue.h"
# include "./algo.h"
# include "./parse.h"

// for perror
# include <stdio.h>

# define PARSE_XY 1
# define PARSE_XY_START 2
# define PARSE_XY_END 3
# define PARSE_EDGE 4
# define PARSE_COMMENT 5

/*
** for ant
*/

typedef struct s_path_len
{
	int value;
	int index;
	int	num_ants;
} t_path_len;

/*
** for ant
*/


/*
**	ant_dist.c
*/

// void	swap(t_path_len *a, t_path_len *b);
// int		partition_asc(t_path_len arr[], int low, int high);
// int		partition_desc(t_path_len arr[], int low, int high);
// void	quicksort(t_path_len arr[], int low, int high);
t_path_len **distribute_ant(t_route route);

#endif
