#include "minishell.h"

static void adding_new_token(t_tokens *token, int pos, char *op)
{
    char *original_str;
    t_tokens *new_token, *next;

    if (ft_strlen(token->str) <= ft_strlen(op))
        return;

    original_str = ft_strdup(token->str);
    next = token->next;

    if (search_content(original_str, op, 0))
        handle_content_before(token, pos, op, original_str);

    if (search_content(original_str, op, 1))
    {
        new_token = handle_content_after(original_str, pos, op, token);
        new_token->next = next;
    }

    free(original_str);
}

static void check_tokens(t_tokens *token)
{
    char **ops = fill_ops();
    int i;

    while (token)
    {
        if (!token->was_quoted && token->str)
        {
            i = -1;
            while (ops[++i])
            {
                if (search_ops_in_str(token->str, ops[i]) > -1)
                {
                    adding_new_token(token, search_ops_in_str(token->str, ops[i]), ops[i]);
                    break;
                }
            }
        }
        token = token->next;
    }

    free(ops);
}

int process_tokens(t_commands *command)
{
    int temp;
    pid_t pid;
    t_tokens *head = command->token;

    if (!check_redir(command))
    {
        command->token = head;
        printf("%s\n", SE);
        return 1;
    }

    if (!check(command))
    {
        pid = fork();
        handle_cmd_signals();

        if (pid == 0)
            return function(command);

        waitpid(pid, &temp, 0);
        g_exit_status = temp >> 8;
        handle_global_signals();
    }

    command->token = head;
    return 1;
}

void parser(t_commands *command)
{
    t_tokens *head = command->token;

    while (command->token)
    {
        if (has_in_out(command, head))
            return;

        if (has_open_quotes(command->token->str, ft_strlen(command->token->str)))
        {
            g_exit_status = 2;
            command->token = head;
            printf("%s\n", EPROMPT);
            return;
        }

        command->token->str = process_argument(command);
        command->token = command->token->next;
    }

    command->token = head;
    check_tokens(head);

    if (!check_redir(command))
    {
        printf("%s\n", SE);
        return;
    }

    if (!process_tokens(command))
    {
        printf("%s\n", CNF);
        exit(g_exit_status);
    }
}
