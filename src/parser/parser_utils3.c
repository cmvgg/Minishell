#include "minishell.h"

int check_syntax(t_tokens *token)
{
    t_TokenType type = token->type;
    t_TokenType type_next;

    if (type == 9)
        return 0;

    if (type >= 5 && type <= 8)
    {
        if (!token->next)
            return 0;

        type_next = token->next->type;
        if (type_next >= 5 && type_next <= 8)
            return 0;
    }

    return 1;
}

int check_redir(t_commands *command)
{
    t_tokens *head = command->token;
    t_tokens *current = head;

    while (current)
    {
        if (!current->was_quoted && !check_syntax(current))
        {
            command->token = head;
            return 0;
        }
        current = current->next;
    }

    command->token = head;
    return 1;
}

int has_in_out(t_commands *command, t_tokens *head)
{
    char *str = command->token->str;
    int len = ft_strlen(str);

    if (!has_open_quotes(str, len) && ft_strnstr(str, "<>", len))
    {
        command->token = head;
        printf("%s\n", SE);
        return 1;
    }

    return 0;
}

void search_for_redirs(t_commands *command)
{
    char **ops = fill_ops();
    t_tokens *token = command->token;

    while (token)
    {
        for (int i = 0; ops[i]; ++i)
        {
            if (ft_strnstr(token->str, ops[i], ft_strlen(token->str)))
            {
                token->was_quoted = 1;
                break;
            }
        }
        token = token->next;
    }

    free(ops);
}

int function(t_commands *command)
{
    t_tokens *token = command->token;

    if (!search_ops_in_str(token->str, ".") || !search_ops_in_str(token->str, "/"))
    {
        if (!is_bin(token->str))
            exit(g_exit_status);

        return run_cmd(token->str, token, command->env, 0);
    }

    if (lstsize_tokens(token, 1) != lstsize_tokens(token, 0))
    {
        if (!handle_redir(token))
        {
            exit(g_exit_status);
            return 1;
        }
    }

    if (!is_redirect(token->str, token->was_quoted))
    {
        if (!check_builtins(command) && !check_bins(token, command->env))
            return 0;
    }

    exit(g_exit_status);
    return 1;
}



int has_open_quotes(const char *str, int len)
{
    int i = 0;
    bool in_single_quote = false;
    bool in_double_quote = false;

    while (i < len)
    {
        if (str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
        }
        else if (str[i] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
        }
        i++;
    }

    return (in_single_quote || in_double_quote);
}