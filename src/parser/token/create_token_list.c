#include "minishell.h"

t_TokenType token_type(char *str, int flag, int was_quoted)
{
    if (is_option(str))
        return OPTION;

    if (is_pipe(str))
        return PIPE;

    if (is_redirect(str, was_quoted))
        return which_red(str);

    if (flag)
        return COMMAND;

    return ARG;
}

t_tokens *lstnew_token(char *str, t_TokenType type)
{
    t_tokens *node = malloc(sizeof(t_tokens));
    if (!node)
        return NULL;

    node->was_quoted = 0;
    node->skip = 0;
    node->str = str;
    node->type = type;
    node->next = NULL;
    return node;
}

static t_tokens *lstlast_token(t_tokens *lst)
{
    if (!lst)
        return NULL;

    while (lst->next)
        lst = lst->next;

    return lst;
}

void lstadd_back_token(t_tokens **lst, t_tokens *new)
{
    if (!new)
        return;

    if (!*lst)
    {
        *lst = new;
        return;
    }

    t_tokens *tail = lstlast_token(*lst);
    tail->next = new;
}

t_tokens *token_list(char *line)
{
    char *trimmed_line = ft_strtrim(line, " ");
    if (!trimmed_line)
        return NULL;

    char **splitted = ft_split(trimmed_line, ' ');
    free(trimmed_line);

    if (!splitted)
    {
        free(line);
        return NULL;
    }

    t_tokens *head = NULL;
    //t_tokens *current_node = NULL;
    int i = 0;

    while (splitted[i])
    {
        t_TokenType type = i == 0 ? token_type(splitted[i], 1, 0) : token_type(splitted[i], 0, 0);
        t_tokens *node = lstnew_token(splitted[i], type);
        if (!node)
        {
            free_tokens_list(head);
            free(splitted);
            free(line);
            return NULL;
        }

        lstadd_back_token(&head, node);
        if (!head)
            head = node;

        //current_node = node;
        i++;
    }

    free(splitted);
    free(line);
    return head;
}
