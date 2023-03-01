# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2023/03/01 14:14:02 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long
LIBFT		=	libft.a
CC			=	gcc
RM			=	rm -rf
MKDIR		=	mkdir -p
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

all:			
				$(MKDIR) $(OBJS_DIR)
				make libft
				make $(NAME)

bonus:			
				$(MKDIR) $(OBJS_DIR)
				make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(LIBFT_DIR)/$(LIBFT) $(OBJS) $(MLXFLAGS) -o $(NAME)

libft:
				make -C $(LIBFT_DIR)

clean:
				$(RM) $(OBJS_DIR)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all bonus libft clean fclean re