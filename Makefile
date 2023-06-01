# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thed6bel <thed6bel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 14:22:47 by hucorrei          #+#    #+#              #
#    Updated: 2023/06/01 17:36:53 by thed6bel         ###   ########.fr        #
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

SRCS	= 	main.c \
			env.c \
			env_utils.c \
			error.c \
			exec.c \
			exec_utils.c \
			expand.c \
			fill_node.c \
			get_params.c \
			get_path.c \
			heredoc.c \
			matrix_utils.c \
			parse_args.c \
			strtrim.c \
			subsplit.c \
			utils.c \
			prompt.c \
			signal.c \
			builtin/unset.c \
			builtin/cd.c \
			builtin/cd_utils.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_utils.c \
			builtin/export_list.c \
			builtin/pwd.c
			

OBJS	= ${SRCS:.c=.o}

ifeq ($(CURRENT_USER),hucorrei)
	READLINE_LIB = -lreadline -lhistory -L /Users/hucorrei/.brew/opt/readline/lib
	READLINE_INC = -I /Users/hucorrei/.brew/opt/readline/include
else
	READLINE_LIB = -lreadline -lhistory -L /Users/lowathar/.brew/opt/readline/lib
	READLINE_INC = -I /Users/lowathar/.brew/opt/readline/include
endif

%.c%.o:
	${CC} ${FLAGS} -I $(READLINE_INC) -c $< -o ${<:.c=.o}

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
		@${CC} ${CFLAGS} ${OBJS} $(READLINE_LIB) ./libft/libft.a -o ${NAME}
		@echo "$(GREEN)$(NAME) created[0m ✔️"

build:
	gcc main.c env.c error.c exec.c expand.c fill_node.c get_params.c get_path.c heredoc.c matrix_utils.c parse_args.c strtrim.c subsplit.c utils.c builtin/unset.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/export_utils.c builtin/export_list.c builtin/pwd.c prompt.c signal.c env_utils.c exec_utils.c builtin/cd_utils.c libft/libft.a -lreadline -L /Users/lowathar/.brew/opt/readline/lib -I /Users/lowathar/.brew/opt/readline/include -g -fsanitize=address

all:	${NAME}

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
