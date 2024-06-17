CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 -Wpedantic -I./includes #-fsanitize=address
RM = rm -rf
LIBFT = ./libft/libft.a
VPATH = src src/parser src/utils src/parser/token src/parser/commands src/parser/env_list\
		src/bins src/built_in src/built_in/echo	src/built_in/export src/parser/env src/pipe\
		src/redir

UTILS = utils utils2 utils3
TOKEN = create_token_list def_token_types token_utils
COMMANDS = create_commands_list create_commands_list_utils
PARSER = parser parser_utils parser_utils2 parser_utils3
ENV = create_env_list
BINS = check_bins check_bins_utils signal_handler signal_handler_utils
BUILTINS = echo export check_builtins env cd unset exit
PIPE = pipe
REDIR = redir
MAIN = main free_structs

SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(TOKEN))\
		$(addsuffix .c, $(COMMANDS))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(ENV))\
		$(addsuffix .c, $(BINS))\
		$(addsuffix .c, $(BUILTINS))\
		$(addsuffix .c, $(PIPE))\
		$(addsuffix .c, $(REDIR))\
		$(addsuffix .c, $(MAIN))\

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	clear

$(NAME): $(OBJ_DIR) $(OBJS)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

run: re
	./minishell

.PHONY: all clean fclean re run