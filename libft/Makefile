# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 16:14:21 by hahlee            #+#    #+#              #
#    Updated: 2022/10/10 16:46:05 by hahlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -c -Wall -Wextra -Werror

FUNC_SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_realloc.c ft_indexof.c
BONUS_SRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS		= $(FUNC_SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all : $(NAME)

bonus : $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $< -o $@

ifeq (, $(findstring bonus, $(MAKECMDGOALS)))
$(NAME) : $(OBJS)
	ar -cr $@ $^
else
$(NAME) : $(OBJS) $(BONUS_OBJS)
	ar -cr $@ $^
endif

clean :
		rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
