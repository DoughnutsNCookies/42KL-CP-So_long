# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/08/06 15:28:15 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long
LIBFT		=	libft.a
ARRC		=	ar rcs
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -Imlx
MLXFLAGS	=	-L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
SRCS_FILES	=	sl_main_bonus \
				sl_hook_bonus \
				sl_enemy_bonus \
				sl_mapget_bonus \
				sl_window_bonus \
				sl_player_bonus \
				sl_helper_bonus \
				sl_mapcheck_bonus \
				sl_mapdisplay_bonus
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR	=	srcs/
LIBFT_DIR	=	libft
OBJS_DIR	=	objs/

all:			$(NAME)

bonus:			$(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		mkdir_objs create_libft $(OBJS)
				$(CC) $(CFLAGS) $(LIBFT_DIR)/$(LIBFT) $(SRCS) $(MLXFLAGS) -o $(NAME)

create_libft:
				make -C $(LIBFT_DIR)
				cp $(LIBFT_DIR)/$(LIBFT) .
				mv $(LIBFT) $(NAME)

mkdir_objs:
				mkdir -p $(OBJS_DIR)

clean:
				rm -rf $(OBJS_DIR)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				rm -rf $(NAME)

re:				fclean all