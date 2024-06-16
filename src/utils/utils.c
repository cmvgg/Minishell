#include "minishell.h"

int lstsize_tokens(t_tokens *token, int filter)
{
    int count = 0;
    t_tokens *previous = NULL;

    while (token)
    {
        if (filter)
        {
            if (!is_redirect(token->str, token->was_quoted) &&
                (!previous || !is_redirect(previous->str, previous->was_quoted)))
            {
                count++;
            }
            previous = token;
        }
        else
        {
            count++;
        }
        token = token->next;
    }
    return count;
}

int has_empty_pipe(char **splitted)
{
    int i = 0, j = 0;
    int flag;

    while (splitted[i])
    {
        flag = 0;
        j = 0;
        while (splitted[i][j])
        {
            if (splitted[i][j] != ' ')
            {
                flag = 1;
                break;
            }
            j++;
        }
        if (!flag)
        {
            i = -1;
            while (splitted[++i])
                free(splitted[i]);
            free(splitted);
            return 1;
        }
        i++;
    }
    return 0;
}

int search_ops_in_str(char *s1, char *s2)
{
    int i = 0;

    while (s1[i])
    {
        if (s1[i] && s1[i] == s2[0])
        {
            if (ft_strlen(s2) > 1)
            {
                if (s1[i + 1] == s2[1])
                    return i;
                i++;
            }
            else
            {
                if (s1[i + 1] != s2[0])
                    return i;
                i++;
            }
        }
        i++;
    }
    return -1;
}

void change_flag(bool *flag)
{
    *flag = !*flag;
}
