# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 14:22:47 by hucorrei          #+#    #+#              #
#    Updated: 2023/05/30 10:38:34 by hucorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS	= 	./src/

OBJS	= ${SRCS:.c=.o}

%.c%.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
CYAN 		= \033[1;36m
RM			= rm -rf

${NAME}:	${OBJS}
		@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
		@${MAKE} -C ./libft
		@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME}
		@echo "$(GREEN)$(NAME) created[0m ✔️"

build:
	gcc main.c env.c error.c exec.c expand.c fill_node.c get_params.c get_path.c heredoc.c matrix_utils.c parse_args.c strtrim.c subsplit.c utils.c builtin/unset.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c prompt.c libft/libft.a -lreadline -L /Users/hucorrei/.brew/opt/readline/lib -I /Users/hucorrei/.brew/opt/readline/include
#-g -fsanitize=address
	./a.out
# all:	${NAME}

clean:
		@${MAKE} -C ./libft clean
		@${RM} ${OBJS}
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:	clean
		@${RM} ${NAME}
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
		@${RM} ./libft/libft.a

re:		fclean all

git:
		git add .
		git commit -m "$m"
		git push

.PHONY:	all clean fclean re git
