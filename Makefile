# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 03:01:07 by olabrahm          #+#    #+#              #
#    Updated: 2021/12/13 19:06:13 by olabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
AR=ar rc
FLAGS=-Wall -Werror -Wextra
PRINTF_FILENAMES=	ft_printf ft_char_in_set ft_conversion ft_putnbr_uns \
				ft_print_hexa ft_print_addr ft_putchar ft_putstr \
				ft_putnbr
PRINTF_FILES=$(addprefix ft_printf/src/, $(PRINTF_FILENAMES))
PRINTF_OBJS=$(PRINTF_FILES:=.o)
PRINTF_INCLUDES=ft_printf/
PRINTF_LIB=libftprintf.a
CLIENT_SERVER=client server
LIBFT_NAME=libft.a
LIBFT_FUNCS=	ft_atoi ft_strdup ft_strlen ft_isdigit
LIBFT_FILES=$(addprefix libft/, $(LIBFT_FUNCS))
LIBFT_OBJS=$(LIBFT_FILES:=.o)
LIBFT_INCLUDES=libft/

all: $(PRINTF_LIB) $(CLIENT_SERVER)

$(PRINTF_LIB): $(PRINTF_OBJS)
	$(AR) $(PRINTF_LIB) $(PRINTF_OBJS)

$(LIBFT_NAME): $(LIBFT_OBJS)
	$(AR) $(LIBFT_NAME) $(LIBFT_OBJS)

$(CLIENT_SERVER): $(PRINTF_LIB) $(LIBFT_NAME)
	$(CC) $(FLAGS) $(LIBFT_NAME) $(PRINTF_LIB) client.c -o client
	$(CC) $(FLAGS) $(LIBFT_NAME) $(PRINTF_LIB) server.c -o server

%.o: %.c
	$(CC) $(FLAGS) -I $(PRINTF_INCLUDES) -I $(LIBFT_INCLUDES) -c $? -o $@

clean:
	rm -rf $(PRINTF_OBJS)
	rm -rf $(LIBFT_OBJS)

fclean: clean
	rm -rf $(PRINTF_LIB)
	rm -rf $(LIBFT_NAME)
	rm -rf $(CLIENT_SERVER)

re: fclean all