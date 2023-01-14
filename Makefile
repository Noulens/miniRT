# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 18:31:22 by tnoulens          #+#    #+#              #
#    Updated: 2023/01/13 13:56:11 by hyunah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

VPATH		=	srcs

INCLDIR		=	$(addsuffix /include, .) $(LIBS)

LIBS		=	libft/ mlx_linux/

LIB_PATH	= 	libft/

MLX_PATH	=	mlx_linux/

BUILDIR		=	build

SRCS_DIR	=	$(sort $(dir $(wildcard ./srcs/*/)))

SRCS		=	$(addprefix srcs/,									\
												main.c				\
					$(addprefix parsing/,		parser.c			\
												parse_type.c		\
												parser_utils.c		\
												parser_utils2.c		\
												parse_obj.c			\
												parse_obj_utils.c)	\
					$(addprefix init/,			init.c)				\
					$(addprefix destroy/,		des_mlx.c)			\
					$(addprefix math/,			vector3_simple.c	\
												vector3.c			\
												matrix4.c			\
												matrix4_2.c			\
												math_utils.c)		\
					$(addprefix interaction/,	interaction.c		\
												interaction_2.c		\
												rotation.c)			\
					$(addprefix render/,		render.c			\
												windows_rend.c		\
												shader.c		\
												intersection.c)		\
					$(addprefix tools/,			rgb_utils.c			\
												rgb_convert.c		\
												range_check.c		\
												lst_tools.c)		\
				)

SRCS_B		=	$(addprefix srcs/,									\
												main.c				\
					$(addprefix parsing/,		parser.c			\
												parse_type.c		\
												parser_utils.c		\
												parser_utils2.c		\
												parse_obj.c			\
												parse_obj_utils.c)	\
					$(addprefix init/,			init.c)				\
					$(addprefix destroy/,		des_mlx.c)			\
					$(addprefix math/,			vector3_simple.c	\
												vector3.c			\
												matrix4.c			\
												matrix4_2.c			\
												math_utils.c)		\
					$(addprefix interaction/,	interaction.c		\
												interaction_2.c		\
												rotation.c)			\
					$(addprefix render/,		render.c			\
												windows_rend.c		\
												shader.c		\
												intersection.c)		\
					$(addprefix tools/,			rgb_utils.c			\
												rgb_convert.c		\
												range_check.c		\
												lst_tools.c)		\
				)

OBJ			=	$(SRCS:%.c=$(BUILDIR)/%.o)

OBJ_B		=	$(SRCS_B:%.c=$(BUILDIR)/%.o)

CFLAGS		=	-Wall -Wextra -Werror -g -O3

CFLAGS_B	=	-Wall -Wextra -Werror -g -O3 -D BONUS=1

LDFLAGS		=	$(LIB_PATH)libft.a -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

CC			=	cc

INCFLAGS	=	$(addprefix -I , $(INCLDIR))

RM			=	/bin/rm -rf

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

bonus:			subsystem $(NAME_BONUS)

subsystem: # Make the libft first then the minilibx
				@make -C $(LIB_PATH) all
				@make -C $(MLX_PATH) all

$(BUILDIR)/%.o:	%.c
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME_BONUS):	$(OBJ_B)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				@$(CC) $(CFLAGS_B) $(INCFLAGS) -o $@ $^ $(LDFLAGS)
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"


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

lc:				all
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT ./scenes/shading.rt

norm:
			norminette ./srcs ./libft ./include