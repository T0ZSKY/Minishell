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
SRCS = ./srcs/main/main.c

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

ALL_SRCS = $(SRCS)

OBJS = $(ALL_SRCS:.c=.o)

CC = gcc
CFLAGS =

YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m
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

%.o: %.c
	@echo "$(YELLOW)📝 Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilation of $< finished$(RESET)"

# Cleaning rules
clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	rm -f $(OBJS)
	@echo "$(RED)🧹 Cleaning libft objects...$(RESET)"
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)🧼 Removing executable...$(RESET)"
	rm -f $(NAME)
	@echo "$(RED)🧼 Cleaning libft archive...$(RESET)"
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
