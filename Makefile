# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 15:37:55 by a79856            #+#    #+#              #
#    Updated: 2022/01/31 15:37:56 by a79856           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NONE = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 #-fsanitize=thread -g
RM = rm -rf

NAME = philo
NAME_BONUS = philo_bonus

OBJDIR = ./obj/
OBJDIR_BONUS = ./obj/bonus/
HEADERDIR = ./includes/

SRCDIR = ./src/philo/
SRCS = life.c main.c philo.c putstr.c time.c utils.c
OBJ = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
HEADER = $(addprefix $(HEADERDIR), philosophers.h)

SRC_BONUS_DIR = ./src/philo_bonus/
SRCS_BONUS = main.c philo.c putstr.c life.c time.c utils.c
OBJ_BONUS = $(addprefix $(OBJDIR_BONUS), $(SRCS_BONUS:.c=.o))
HEADER_BONUS = $(addprefix $(HEADERDIR), philo.h)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(OBJ_UTILS) $(HEADER) $(HEADER_UTILS)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_UTILS) -o $@
	@echo "$(PURPLE) $(NAME) has been created $(NONE)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJDIR_BONUS) $(OBJ_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $@
	@echo "$(PURPLE) $(NAME_BONUS) has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_BONUS):
	mkdir -p $(OBJDIR_BONUS)

############################
##   philo compilation    ##
############################

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) $(HEADER_UTILS) Makefile
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for philo has been created $(NONE)"

############################
##   utils compilation    ##
############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.c $(HEADER_UTILS) Makefile
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for utils has been created $(NONE)"

#################################
##   philo bonus compilation   ##
#################################

$(OBJ_BONUS): $(OBJDIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c $(HEADER_BONUS) Makefile
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for philo_bonus has been created $(NONE)"

clean:
	$(RM) $(OBJDIR)
	@echo "$(RED) $(OBJDIR) has been deleted $(NONE)"

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED) $(NAME) has been deleted $(NONE)"

re:	fclean all

.PHONY: all clean fclean re bonus
