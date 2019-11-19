# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 16:06:00 by fmallist          #+#    #+#              #
#    Updated: 2019/11/12 21:55:55 by fmallist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFTA = libft.a
SRCS = buffer_mgmt.c ft_printf.c fill_options.c itoa_base_buff.c handle_overflow_buffer.c get_integer.c handle_integers.c \
		itoa_base_extra_funcs.c itoa_base_buff_u.c handle_unsigned.c get_unsigned.c
OBJ = $(SRCS:.c=.o)
LIBDIR = libft/
LIBNAME = libft/libft.a
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) 
	@make -C $(LIBDIR)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@make -C $(LIBDIR) clean
	@echo OBJECTS FILES HAS BEEN DELETED.

test:
	@gcc *.c -L libft -lft -o test

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBDIR) fclean
	@echo OBJECT FILES AND EXECUTABLE HAS BEEN DELETED.

re: fclean all
