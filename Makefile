# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/01 16:07:45 by mcuenca-          #+#    #+#              #
#    Updated: 2025/11/14 13:47:51 by mcuenca-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Wextra -Werror -g -Iinclude #-fsanitize=address #-lpthread

HEADER= include/philo.h

SRCS_DIR= src
SRCS= src/main.c \
	  src/pthreads.c \
	  src/monitoring.c \
	  src/routine.c

UTILS_DIR= src/utils
UTILS= src/utils/ft_isspace.c \
	   src/utils/ft_isdigit.c \
	   src/utils/ft_memset.c \
	   src/utils/ft_bzero.c \
	   src/utils/ft_calloc.c \
	   src/utils/ft_atoi.c \
	   src/utils/philo_clean_mng.c \
	   src/utils/philo_utils.c

OBJS_DIR= obj_philo
OBJS= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o) \
	$(UTILS:$(UTILS_DIR)/%.c=$(OBJS_DIR)/%.o)

NAME= philo

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(UTILS_DIR)/%.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	if [ -d $(OBJS_DIR) ]; then rm -df $(OBJS_DIR); fi

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean rea fclean all
