# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjung-mo <cjung-mo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 02:01:35 by sucho             #+#    #+#              #
#    Updated: 2023/08/09 16:18:29 by cjung-mo         ###   ########.fr        #
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
							./srcs/queue.c \
							./srcs/edmonds-karp.c \
							./srcs/parse.c \
							./srcs/parse_reading.c \
							./srcs/parse_check.c \
							./srcs/parse_util.c \
							./srcs/graph_list.c

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
