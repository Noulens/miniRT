NAME		=	miniRT

NAME_B		=	miniRT_bonus

VPATH		=	srcs

INCLDIR		=	$(addsuffix /include, .) $(LIBS)

LIBS		=	libft/ mlx_linux/

LIB_PATH	= 	libft/

MLX_PATH	=	mlx_linux/

BUILDIR		=	build

BUILDIR_B	=	build_b

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
												vector3_algo.c		\
												vector3_calcule.c	\
												vector3.c			\
												matrix4.c			\
												matrix4_2.c			\
												inverse_matrix.c	\
												math_utils.c)		\
					$(addprefix interaction/,	interaction.c		\
												interaction_2.c		\
												interaction_3.c		\
												interaction_4.c		\
												debug_win_utils.c	\
												debug_win.c			\
												debug_win_obj.c		\
												interaction_5.c		\
												copy_paste.c		\
												generatertfile.c	\
           										generatefile2.c)	\
					$(addprefix render/,		render.c			\
												windows_rend.c		\
												build_ray.c			\
												shader_common.c		\
												shader.c			\
												intersection.c		\
												intersection_pl.c	\
												inter_cyl_2.c		\
												hit_normal.c)		\
					$(addprefix tools/,			rgb_utils.c			\
												rgb_convert.c		\
												range_check.c		\
												lst_tools.c			\
												lst_tools_lights.c)	\
				)

SRCS_B		=	$(addprefix srcs/,									\
												main.c				\
					$(addprefix parsing/,		parser.c			\
												parse_type.c		\
												parser_utils.c		\
												parser_utils2.c		\
												parse_obj.c			\
												parse_obj_utils.c	\
												cone_bonus.c)		\
					$(addprefix init/,			init.c)				\
					$(addprefix destroy/,		des_mlx.c)			\
					$(addprefix math/,			vector3_simple.c	\
												vector3.c			\
												vector3_calcule.c	\
												vector3_algo.c		\
												matrix4.c			\
												matrix4_2.c			\
												inverse_matrix.c	\
												math_utils.c)		\
					$(addprefix interaction/,	interaction.c		\
												interaction_2.c		\
												interaction_3.c		\
												interaction_4.c		\
												interaction_5.c		\
												debug_win_obj.c		\
												debug_win_utils.c	\
												debug_win.c			\
												adjust_cone_bonus.c	\
												copy_paste.c		\
												generatertfile.c	\
												generatefile2.c)	\
					$(addprefix render/,		render.c			\
												windows_rend.c		\
												build_ray.c			\
												shader_common.c		\
												shader_bonus.c		\
												intersection.c		\
												intersection_pl.c	\
												inter_co_bonus.c	\
												inter_cyl_2.c		\
                                                hit_normal.c		\
                                                hit_normal_bonus.c)	\
					$(addprefix tools/,			rgb_utils.c			\
												rgb_convert.c		\
												range_check.c		\
												lst_tools.c			\
												lst_tools_lights.c)	\
				)


OBJ			=	$(SRCS:%.c=$(BUILDIR)/%.o)

OBJ_B		=	$(SRCS_B:%.c=$(BUILDIR_B)/%.o)

CFLAGS		=	-Wall -Wextra -Werror -g -O3

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

ifeq (bonus, $(filter bonus,$(MAKECMDGOALS)))
	DEFINE	=	-D BONUS=1
else ifeq (rebonus, $(filter rebonus,$(MAKECMDGOALS)))
	DEFINE	=	-D BONUS=1
else ifeq (lcb, $(filter lcb,$(MAKECMDGOALS)))
	DEFINE	=	-D BONUS=1
else
	DEFINE	=	-D BONUS=0
endif

.PHONY:	all bonus clean fclean re

##.SILENT:

all:			subsystem $(NAME)

bonus:			subsystem $(NAME_B)

subsystem: # Make the libft first then the minilibx
				@make -C $(LIB_PATH) all
				@make -C $(MLX_PATH) all


$(BUILDIR)/%.o:	%.c
				@mkdir -p build/ $(addprefix build/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				@$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(BUILDIR_B)/%.o:	%.c
				@mkdir -p build_b/ $(addprefix build_b/, $(SRCS_DIR))
				@ printf "$(YELLOW)Compiling $@ and generating .o files...$(DEFAULT)\n"
				@$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -c $< -o $@
				@ printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)

$(NAME_B):		$(OBJ_B)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -o $@ $^ $(LDFLAGS)
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

$(NAME):		$(OBJ)
				@ printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				$(CC) $(CFLAGS) $(DEFINE) $(INCFLAGS) -o $@ $^ $(LDFLAGS)
				@ printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

clean:
				@printf "$(YELLOW)Deleting object files...$(DEFAULT)\n"
				@$(RM) $(OBJ) $(OBJ_B)
				@make -C $(LIB_PATH) clean
				@make -C $(MLX_PATH) clean
				@printf "$(DELPREV)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME) $(BUILDIR_B) $(NAME_B)
				@make -C $(LIB_PATH) fclean
				@printf "$(DELPREV)Build directory and binary deleted\n"

re:				fclean
				@$(MAKE) -s all

rebonus:		fclean
				$(MAKE) -s bonus

lc:				all
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT ./scenes/shading.rt

lcb:			bonus
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT_bonus ./scenes/shading.rt

norm:
			norminette ./srcs ./libft ./include