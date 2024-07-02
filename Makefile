
CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g -I./includes #-fsanitize=leak,address
RM = rm -rf
LIBFT = ./libft/libft.a
VPATH = src src/parser src/utils src/parser/token src/parser/commands src/parser/env_list\
		src/bins src/builtins src/builtins/echo	src/builtins/export src/parser/env src/pipe\
		src/redir

UTILS = utils utils2 utils3
TOKEN = create_token_list def_token_types token_utils
COMMANDS = create_commands_list create_commands_list_utils create_commands_list_utils2
PARSER = parser parser_utils parser_utils2 parser_utils3 parser_utils4
ENV = create_env_list
BINS = check_bins check_bins_utils signal_handler signal_handler2
BUILTINS = check_builtins env cd unset exit
ECHO = echo
EXPORT = export
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
		$(addsuffix .c, $(ECHO))\
		$(addsuffix .c, $(EXPORT))\
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

valf: re
	valgrind  -s --leak-check=full --show-leak-kinds=all ./minishell  

val:  re
	valgrind -s ./minishell

PHONY: all clean fclean re run

.SILENT:
