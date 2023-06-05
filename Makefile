# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hucorrei <hucorrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 14:22:47 by hucorrei          #+#    #+#              #
#    Updated: 2023/06/05 09:13:48 by hucorrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME			= minishell
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= minishell.h
CURRENT_USER	= $(shell whoami)
CURRENT_FOLDER	= $(shell pwd)

ifeq ($(CURRENT_USER),hucorrei)
	READLINE_LIB = -lreadline -lhistory -L /Users/hucorrei/.brew/opt/readline/lib
	READLINE_INC = -I /Users/hucorrei/.brew/opt/readline/include
else
	READLINE_LIB = -lreadline -lhistory -L /Users/lowathar/.brew/opt/readline/lib
	READLINE_INC = -I /Users/lowathar/.brew/opt/readline/include
endif

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
			builtin/cd_utils2.c \
			builtin/echo.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/export.c \
			builtin/export_utils.c \
			builtin/export_list.c \
			builtin/pwd.c
			

OBJS	= ${SRCS:.c=.o}

%.o: %.c
	${CC} -Wall -Wextra -Werror -I ${INCLUDES} $(READLINE_INC) -c $< -o $@

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
CYAN 		= \033[1;36m
RM			= rm -rf

all:	${NAME}

${NAME}:	${OBJS} ${INCLUDES}
		@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
		@${MAKE} -C ./libft
		@${CC} ${CFLAGS} $(READLINE_LIB) -L ./libft -l ft -o $(NAME) $(OBJS)
		@echo "$(GREEN)$(NAME) created[0m ✔️"

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