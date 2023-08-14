# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 02:01:35 by sucho             #+#    #+#              #
#    Updated: 2023/08/14 02:26:08 by sucho            ###   ########.fr        #
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
							./srcs/algo/edmonds-karp.c \
							./srcs/algo/graph_list.c \
							./srcs/algo/graph_util.c \
							./srcs/algo/queue.c \
							./srcs/main.c \
							./srcs/ant_dist.c \
							./srcs/utils.c

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
