#include "minishell.h"

char	*get_variable(char *str, int *pos)
{
	char	*variable;
	int		i = (*pos) + 1;
	int		n = 0;

	while (str[i] != '$' && str[i] != '=' && str[i] != ASPAS
		&& str[i] != PLICAS && str[i] != ' ' && str[i])
	{
		n++;
		i++;
	}
	(*pos) = i - 1;
	variable = ft_substr(str, *pos - n + 1, n);
	return (variable);
}

char	*search_variable(char *command, int *pos, t_env *env)
{
	char	*value;

	if (isquote(command[(*pos) + 1]) && command[(*pos) + 2] != '$'
		&& command[(*pos) + 2] != '\0')
		value = NULL;
	else if (command[(*pos) + 1] == '?')
	{
		(*pos) += 1;
		value = ft_itoa(g_exit_status);
	}
	else if (!ft_isalnum(command[(*pos) + 1]))
		value = "$";
	else
	{
		char *var_name = get_variable(command, pos);
		value = env_value(var_name, env);
		free(var_name);
	}
	(*pos) += 1;
	return (value);
}

char	*add_chars(char *expanding_str, char *str, int pos, int start)
{
	char	*new_str;
	char	*temp = ft_substr(str, start, pos);

	if (!expanding_str)
		return (temp);

	new_str = ft_strjoin(expanding_str, temp);
	if (ft_strcmp(expanding_str, "$"))
		free(expanding_str);
	free(temp);

	return (new_str);
}

char	*if_variable(char *new_str, t_commands *command, int *start, int *i)
{
	new_str = process_variable(command->token->str, i, new_str, command->env);
	(*start) = (*i);
	(*i)--;

	return (new_str);
}

char	*if_quotes(char *new_str, t_commands *command, int *start, int *i)
{
	char	*handling = quote_handler(command->token->str, i, (*i) + 1, command->env);

	search_for_redirs(command);

	if (!handling)
		return (new_str);

	char	*temp = new_str;
	new_str = ft_strjoin(temp, handling);

	if (temp && ft_strcmp(temp, "$"))
		free(temp);

	if (handling && ft_strcmp(handling, "$"))
		free(handling);

	(*start) = (*i);

	if (command->token->str[(*i) + 1])
		(*start)++;

	return (new_str);
}
