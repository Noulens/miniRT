# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 18:31:22 by tnoulens          #+#    #+#              #
#    Updated: 2022/12/19 11:38:31 by hyunah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

VPATH		=	srcs

INCLDIR		=	$(addsuffix /include, .) $(LIBS)

LIBS		=	libft/ mlx_linux/

LIB_PATH	= 	libft/

MLX_PATH	=	mlx_linux/

BUILDIR		=	build

SRCS_DIR	=	init/		\
				destroy/	\
				math/	\
				interaction/ \
				render \

SRCS		=							main.c		\
				$(addprefix init/,			init.c)		\
				$(addprefix destroy/,		des_mlx.c)	\
				$(addprefix math/,			vector_simple.c) \
				$(addprefix math/,			vector.c)	\
				$(addprefix interaction/,	interaction.c)	\
				$(addprefix render/,		render.c)	\

OBJ			=	$(SRCS:%.c=$(BUILDIR)/%.o)

CFLAGS		=	-Wall -Wextra -Werror -g -O3
LDFLAGS		=	$(LIB_PATH)libft.a -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# Run 'make re MODE=fsanitize' to run fsanitize.
MODE	= none
ifeq ($(MODE), fsanitize)
	CFLAGS	+= -fsanitize=thread -g3
endif

CC			=	cc

INCFLAGS	=	$(addprefix -I , $(INCLDIR))

RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)

# FG COLORS
DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C

# DISPLAY
HEAD_SIZE	=	32
NAME_SIZE	=	$(shell NAME='$(NAME)'; printf "$${\#NAME}")
PAD_WIDTH	=	$(shell printf "$$((($(HEAD_SIZE) - $(NAME_SIZE)) / 2))")
PAD_PREC	=	$(shell printf "$$(($(PAD_WIDTH) / 2))")
PAD_CHAR	=	\*
PAD_STR		=	$(shell printf '$(PAD_CHAR)%.0s' {1..$(PAD_WIDTH)})
LEFT_PAD	=	$(shell printf '%-*.*s' $(PAD_WIDTH) $(PAD_PREC) $(PAD_STR))
RIGHT_PAD	=	$(shell printf '%*.*s' $$(($(PAD_WIDTH) + $(NAME_SIZE) % 2)) $(PAD_PREC) $(PAD_STR))
BODY_WIDTH	=	$(shell printf "$$(($(HEAD_SIZE) - 1))")

#######
#Rules#
#######

.PHONY:	all bonus clean fclean re

.SILENT:

all:			subsystem $(NAME)

subsystem: # Make the libft first then the minilibx
				@make -C $(LIB_PATH) all
				@make -C $(MLX_PATH) all

$(BUILDIR)/%.o:	%.c
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)


$(NAME):		$(OBJ)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				@$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^ $(LDFLAGS)
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

clean:
				@printf "$(YELLOW)Deleting object files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@make -C $(LIB_PATH) clean
				@make -C $(MLX_PATH) clean
				@printf "$(DELPREV)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME)
				@make -C $(LIB_PATH) fclean
				@printf "$(DELPREV)Build directory and binary deleted\n"

re:				fclean
				@$(MAKE) -s all

lc:			all
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT

norm:
			norminette ./srcs ./libft ./include