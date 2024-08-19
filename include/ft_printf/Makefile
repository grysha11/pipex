# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 19:50:36 by hzakharc          #+#    #+#              #
#    Updated: 2024/08/01 21:00:19 by hzakharc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	ft_printf.c ft_printf_util.c
LIBFTDIR	= 	../libft/

LIBFT		= 	$(LIBFTDIR)libft.a
OBJS		= 	$(SRCS:.c=.o)

CC			= 	cc
RM			= 	@rm -rf
CCFLAGS		= 	-Wall -Werror -Wextra -I.

NAME		= 	libftprintf.a

%.o:			%.c
				@$(CC) $(CCFLAGS) -c $< -o $@

all:			$(NAME)
				
$(NAME):		$(OBJS)
				@make -sC ${LIBFTDIR}
				@ar rcs $(NAME) $(LIBFT) $(OBJS)

clean:
				$(RM) $(OBJS)
				@make --no-print-directory -C $(LIBFTDIR) clean

fclean:			clean
				$(RM) $(NAME)
				@make --no-print-directory -C $(LIBFTDIR) fclean

re:				fclean all

.PHONY:			all clean fclean re
