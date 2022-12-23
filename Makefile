# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 13:49:22 by hahlee            #+#    #+#              #
#    Updated: 2022/12/23 14:23:25 by hahlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -I /usr/local/include -L libft -L /usr/local/lib/ -lft

OUTDIR	= out/
MANDATORY_OUTDIR = out/pipex_mandatory
SRCS	= pipex.c utils.c
OBJS	= $(SRCS:%.c=$(OUTDIR)%.o)

all : $(NAME)

$(OUTDIR):
	mkdir $@

$(NAME) : $(OBJS)
	$(MAKE) -j -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
$(MANDATORY_OUTDIR):
	mkdir $@

clean :
	$(MAKE) -j -C libft clean
	$(RM) -r $(OUTDIR)

fclean : clean
	$(MAKE) -j -C libft fclean
	$(RM) -r $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

$(OBJS): $(OUTDIR)%.o: %.c | $(OUTDIR) $(MANDATORY_OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re
