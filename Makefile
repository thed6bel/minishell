# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 21:37:12 by thed6bel          #+#    #+#              #
#    Updated: 2023/06/13 14:59:32 by hucorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME			= minishell
CC				= gcc
FLAGS			= -Wall -Wextra -Werror
HOME			= $(shell echo $$HOME)

ifeq ($(shell uname -s), Linux)
	READLINE_LIB = -lreadline -lhistory
	READLINE_INC = -I /usr/include/readline
else
	READLINE_LIB = -lreadline -lhistory -L $(HOME)/.brew/opt/readline/lib
	READLINE_INC = -I $(HOME)/.brew/opt/readline/include
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS			=	builtin/export.c \
					builtin/unset.c \
					builtin/echo.c \
					builtin/cd_utils.c \
					builtin/cd_utils2.c \
					builtin/export_list.c \
					builtin/export_utils.c \
					builtin/cd.c \
					builtin/exit.c \
					builtin/env.c \
					builtin/pwd.c \
					src/env_utils.c \
					src/matrix_utils.c \
					src/signal.c \
					src/main.c \
					src/parse_args.c \
					src/get_params.c \
					src/error.c \
					src/expand.c \
					src/heredoc.c \
					src/exec_utils.c \
					src/exec.c \
					src/subsplit.c \
					src/fill_node.c \
					src/fill_node_utils.c \
					src/prompt.c \
					src/utils.c \
					src/env.c \
					src/strtrim.c \
					src/get_path.c \
						
OBJS			= $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o} $(READLINE_INC)

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}: ${OBJS} ${INCLUDES}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}with flags -Wall -Wextra -Werror..."
			@${MAKE} -s -C ./libft
			@${CC} ${FLAGS} $(OBJS) $(READLINE_LIB) ./libft/libft.a -g -fsanitize=address -o $(NAME)
			@echo "$(GREEN)$(NAME) created$(CLR_RMV) ✔️"

all:		${NAME}

clean:
			@${MAKE} -s -C ./libft fclean
			@${RM} ${OBJS}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

git:
		git add .
		git commit -m "$m"
		git push
		@ echo "$(BLUE)ALL is on your $(CYAN)GIT $(CLR_RMV)✔️"

.PHONY:	all clean fclean re git