# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 10:03:05 by arigonza          #+#    #+#              #
#    Updated: 2024/08/22 12:08:03 by arigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := 

FLAGS := -Wall -Werror -Wextra -lreadline

FSANITIZE := -fsanitize=thread -g3

OBJDIR := obj

SRC =

OBJ = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))

$(OBJDIR)/%.o : src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "$(YELLOW)$(DEF_COLOR)"

$(OBJDIR) :
	@mkdir -p $(OBJDIR)

clean :
	@echo "$(YELLOW)Deleting all object files....$(DEF_COLOR)"
	@rm -rf $(OBJDIR)
	@echo "$(RED)All object files were deleteated...$(DEF_COLOR)"

fclean : clean
	@echo "$(YELLOW)Deleting executable files....$(DEF_COLOR)"
	@rm -f $(NAME)
	@echo "$(RED)All executable files has been deleted.$(DEF_COLOR)"
	
re : fclean all

norm :
	@echo "$(CYAN)Norminette src/$(GREEN)"
	@norminette src/
	@echo "$(CYAN)Norminette includes/$(GREEN)"
	@norminette includes/
	@echo "$(DEF_COLOR)"


# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m