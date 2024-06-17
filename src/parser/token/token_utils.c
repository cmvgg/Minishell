#include "minishell.h"

static int red_count(char *str, int c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == c)
            count++;
    }

    return count;
}

t_TokenType which_red(char *str)
{
    int count_gt = red_count(str, '>');
    int count_lt = red_count(str, '<');

    if (count_gt == 1)
        return RED_OUT;
    if (count_lt == 1)
        return RED_IN;
    if (count_gt == 2 && count_lt == 0)
        return APPEND_OUT;
    if (count_lt == 2 && count_gt == 0)
        return HEREDOC;

    return ERRO;
}

void free_tokens_list(t_tokens *token)
{
    t_tokens *temp;

    while (token)
    {
        temp = token;
        token = token->next;
        if (temp->str)
        {
            free(temp->str);
        }
        free(temp);
    }
}
