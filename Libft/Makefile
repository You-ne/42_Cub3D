# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 21:03:36 by yotillar          #+#    #+#              #
#    Updated: 2020/02/04 21:06:38 by yotillar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INCLUDE = libft.h
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS =  ft_atoi.c \
       ft_itoa.c \
       ft_convert_base.c \
       ft_convert_base2.c \
       ft_calloc.c \
       ft_bzero.c \
       ft_memset.c \
       ft_memcpy.c \
       ft_memccpy.c \
       ft_memmove.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strlen.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strnstr.c \
       ft_strncmp.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_strmapi.c \
       ft_split.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putstr_fd.c \
       ft_putnbr_fd.c \
       ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_toupper.c \
       ft_tolower.c \

BONUS_SRCS = $(SRCS) ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	     ft_lstsize_bonus.c ft_lstlast_bonus.C ft_lstadd_back_bonus.c \
	     ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	     ft_lstmap_bonus.c \

OBJS = $(SRCS:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	ar -rcs $(NAME) $(OBJS) 
	ranlib $(NAME)

bonus:	$(BONUS_OBJ) $(INCLUDE)
	ar -rcs $(NAME) $(BONUS_OBJ)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

rebonus : fclean bonus

main: gcc $(CFLAGS) main.c libft.a
