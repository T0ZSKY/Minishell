# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 23:56:39 by tomlimon          #+#    #+#              #
#    Updated: 2025/02/19 23:16:58 by tomlimon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Détection du système d'exploitation
UNAME_S := $(shell uname -s)

# changement en fonction de l'os je supprime a la fin
ifeq ($(UNAME_S),Darwin)  # Si c'est macOS
    READLINE = -I/opt/homebrew/opt/readline/include \
               -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(UNAME_S),Linux)  # Si c'est Linux
    READLINE = -I/usr/include/readline \
               -L/usr/lib/x86_64-linux-gnu -lreadline
else
    $(error Unsupported OS)
endif

NAME = minishell
SRCS = ./srcs/main/main.c \
		./srcs/parser/lexer.c ./srcs/executor/utils.c ./srcs/parser/parser.c ./srcs/parser/quote.c\
		./srcs/executor/builtins/echo.c ./srcs/executor/builtins/echo_utils.c ./srcs/executor/builtins/cd.c ./srcs/executor/builtins/export.c\
		./srcs/executor/builtins/export_utils.c ./srcs/executor/builtins/pwd.c ./srcs/executor/builtins/env.c\
		./srcs/executor/builtins/exit.c ./srcs/executor/builtins/unset.c ./srcs/executor/builtins/echo_utils2.c\
		./srcs/executor/executor.c ./srcs/parser/utils.c\
		./srcs/utils/utils.c ./srcs/utils/find_path.c ./srcs/utils/shlvl.c ./srcs/utils/ascii.c\
		./srcs/signals/signals.c ./srcs/utils/splitfou.c ./srcs/utils/utils_path.c\
		./srcs/executor/pipes.c ./srcs/executor/redirections.c ./srcs/executor/redirection_utils.c \
		./srcs/executor/builtins/cd_utils.c ./srcs/parser/quote_utils.c

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0;34m
RED = \033[0;31m

# Compilation rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Compiling $(NAME)... 🚀$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)🔨 Compiling libft... 🚀$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)📝 Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilation of $< finished$(RESET)"

# Cleaning rules
clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Cleaning libft objects...$(RESET)"
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)🧼 Removing executable...$(RESET)"
	rm -f $(NAME)
	@echo "$(RED)🧼 Cleaning libft archive...$(RESET)"
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
