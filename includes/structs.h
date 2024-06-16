#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "shell pequeno 🐚> "
# define EPARSE "parse error near '|'"
# define CPARSE "parse error near '{}'"
# define NAI "not a valid identifier"
# define SE "syntax error"
# define EPROMPT "unclosed quotes"
# define CNF "command not found"
# define TMA "too many arguments"
# define NAR "numeric argument required"
# define UNKNOWN "no such file or directory"
# define PD "permission denied"
# define FF "fork failed to create a new process"
# define PF "pipe failed to create a new process"
# define ASPAS 34
# define PLICAS 39
# define ERROR -1

typedef enum t_TokenType
{
	SETTING,
	COMMAND,
	OPTION,
	PIPE,
	ARG,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND_OUT,
	ERRO
}			t_TokenType;

typedef struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_TokenType			type;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env
{
	int					was_added;
	char				*str;
	struct s_env		*next;
}						t_env;

typedef struct s_commands
{
	t_env				*env;
	t_tokens			*token;
	int					index;
	struct s_commands	*next;
}						t_commands;

#endif