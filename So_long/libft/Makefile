# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 18:36:11 by schuah            #+#    #+#              #
#    Updated: 2023/03/01 14:19:50 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				=	gcc
AR				=	ar rcs
HEADER			=	-I libft.h
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -rf
MKDIR			=	mkdir -p
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/
PRINTF_DIR		=	printf/
SRC_FILES		=	ft_isalpha \
					ft_isdigit \
					ft_isalnum \
					ft_isascii \
					ft_isprint \
					ft_strlen \
					ft_memset \
					ft_bzero \
					ft_memcpy \
					ft_memmove \
					ft_strlcpy \
					ft_strlcat \
					ft_toupper \
					ft_tolower \
					ft_strchr \
					ft_strrchr \
					ft_strncmp \
					ft_memchr \
					ft_memcmp \
					ft_strnstr \
					ft_atoi \
					ft_calloc\
					ft_strdup \
					ft_substr \
					ft_strjoin \
					ft_strtrim \
					ft_split \
					ft_itoa \
					ft_strmapi \
					ft_striteri \
					ft_putchar_fd \
					ft_putstr_fd \
					ft_putendl_fd \
					ft_putnbr_fd \
					ft_lstnew \
					ft_lstadd_front \
					ft_lstsize \
					ft_lstlast \
					ft_lstadd_back \
					ft_lstdelone \
					ft_lstclear \
					ft_lstiter \
					ft_lstmap \
					ft_printf \
					ft_printf_flags \
					ft_printn_with_flags \
					ft_printun_with_flags \
					ft_printh_with_flags \
					ft_printp_with_flags \
					ft_prints_with_flags \
					get_next_line \
					get_next_line_utils \
					ft_quicksort \
					ft_swap \
					ft_isspace \
					ft_ultoa_base \
					ft_uitoa_base \
					ft_uitoa
SRCS 			= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 			= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

all:				
					$(MKDIR) $(OBJS_DIR)
					make $(NAME)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c | $(OBJSF)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJS)
					$(AR) $(NAME) $(OBJS)

clean:
					$(RM) $(OBJS_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re