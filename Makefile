# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 03:01:07 by olabrahm          #+#    #+#              #
#    Updated: 2021/11/26 03:10:20 by olabrahm         ###   ########.fr        #
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

all: $(PRINTF_LIB) $(CLIENT_SERVER)

$(PRINTF_LIB): $(PRINTF_OBJS)
	$(AR) $(PRINTF_LIB) $(PRINTF_OBJS)

$(CLIENT_SERVER): client.c server.c
	$(CC) $(FLAGS) -I $(PRINTF_INCLUDES) client.c $(PRINTF_LIB) -o client
	$(CC) $(FLAGS) -I $(PRINTF_INCLUDES) server.c $(PRINTF_LIB) -o server

%.o: %.c
	$(CC) $(FLAGS) -I $(PRINTF_INCLUDES) -c $? -o $@

clean:
	rm -rf $(PRINTF_OBJS)

fclean: clean
	rm -rf $(PRINTF_LIB)
	rm -rf $(CLIENT_SERVER)

re: fclean all