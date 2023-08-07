# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 02:01:35 by sucho             #+#    #+#              #
#    Updated: 2023/08/07 07:27:04 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	lem-in
LIBFT					=	libft.a

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror -O3
RM						=	rm -f

INCLUDES_PATH			=	./includes/
LIBFT_PATH				=	./libft/

INCS					=	-I${INCLUDES_PATH} -I${LIBFT_PATH}

INCLIB					=	-L${LIBFT_PATH} -lft

SRCS					=	./includes/get_next_line/get_next_line_bonus.c \
							./includes/get_next_line/get_next_line_utils_bonus.c \
							./srcs/main.c \

OBJS					=	${SRCS:.c=.o}

.c.o:
							${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 						$(NAME)

${NAME}:					${OBJS}
							make bonus -C ${LIBFT_PATH}
							$(CC) $(CFLAGS) ${INCS} ${INCLIB} -o $(NAME) $(OBJS)

clean:
							$(MAKE) -C $(LIBFT_PATH) clean
							rm -f $(OBJS)

fclean: 					clean
							$(MAKE) -C $(LIBFT_PATH) fclean
							rm -f $(NAME)

re: 						fclean all

.PHONY: 					all clean fclean re
