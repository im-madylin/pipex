# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 13:49:22 by hahlee            #+#    #+#              #
#    Updated: 2023/01/03 15:25:17 by hahlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -I /usr/local/include -L libft -L /usr/local/lib/ -lft

OUTDIR	= out/
SRCS	= pipex_bonus.c child_process_bonus.c utils_bonus.c ready_to_execve_bonus.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS	= $(SRCS:%.c=$(OUTDIR)%.o)

all : $(NAME)

bonus : $(NAME)

$(OUTDIR):
	mkdir $@
	mkdir $@/gnl

$(NAME) : $(OBJS)
	$(MAKE) -j -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

clean :
	$(MAKE) -j -C libft clean
	$(RM) -r $(OUTDIR)

fclean : clean
	$(MAKE) -j -C libft fclean
	$(RM) -r $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

$(OBJS): $(OUTDIR)%.o: %.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re
