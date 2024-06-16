#include "minishell.h"

static int has_content(char *str, int ipos, int fpos)
{
    while (++ipos < fpos)
    {
        if (!isquote(str[ipos]))
            return 1;
    }
    return 0;
}

int is_option(char *str)
{
    int i = 0;

    while (isquote(str[i]))
        i++;

    if (str[i] == '-' && !has_content(str, 0, i))
    {
        if (has_content(str, i, ft_strlen(str)))
            return 1;
        i++;
    }

    return 0;
}


int is_pipe(char *str)
{
    return *str == '|';
}


int is_redirect(char *str, int was_quoted)
{
    if (was_quoted)
        return 0;

    return !ft_strcmp(str, "<") || !ft_strcmp(str, ">") || !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>");
}
