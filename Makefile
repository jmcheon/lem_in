# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 02:01:35 by sucho             #+#    #+#              #
#    Updated: 2023/08/26 00:56:14 by cjung-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	lem-in
LIBFT					=	libft.a

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror -O3 -g
RM						=	rm -f

INCLUDES_PATH			=	./includes/
LIBFT_PATH				=	./libft/

INCS					=	-I${INCLUDES_PATH} -I${LIBFT_PATH}

INCLIB					=	-L${LIBFT_PATH} -lft

SRCS					=	./includes/get_next_line/get_next_line_bonus.c \
							./includes/get_next_line/get_next_line_utils_bonus.c \
							./srcs/parse/parse.c \
							./srcs/parse/parse_reading.c \
							./srcs/parse/parse_check.c \
							./srcs/parse/parse_util.c \
							./srcs/parse/parse_free.c \
							./srcs/algo/multishot/multishot_edge.c \
							./srcs/algo/multishot/multishot_vertex.c \
							./srcs/algo/multishot/multishot_bfs.c \
							./srcs/algo/multishot/multishot_edmonds_karp.c \
							./srcs/algo/oneshot/oneshot_edmonds_karp.c \
							./srcs/algo/oneshot/oneshot_bfs.c \
							./srcs/algo/disjoint_path.c \
							./srcs/algo/init_funcs.c \
							./srcs/algo/queue.c \
							./srcs/algo/priority_queue.c \
							./srcs/algo/graph_list.c \
							./srcs/algo/graph_util.c \
							./srcs/ants/ants_dist_util.c \
							./srcs/ants/ants_dist.c \
							./srcs/ants/ants_quicksort.c \
							./srcs/ants/ants_quicksort2.c \
							./srcs/ants/ants_print_frame.c \
							./srcs/free.c \
							./srcs/main.c

OBJS					=	${SRCS:.c=.o}

.c.o:
							${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 						$(NAME)

${NAME}:					${OBJS}
							make bonus -C ${LIBFT_PATH}
							$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ${INCS} ${INCLIB}

clean:
							$(MAKE) -C $(LIBFT_PATH) clean
							rm -f $(OBJS)

fclean: 					clean
							$(MAKE) -C $(LIBFT_PATH) fclean
							rm -f $(NAME)

re: 						fclean all

.PHONY: 					all clean fclean re
