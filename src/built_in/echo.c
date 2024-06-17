#include "minishell.h"

static void print_all(t_tokens *token)
{
    t_tokens previous_token = *token;

    while (token) {
        if (token->str && !is_redirect(token->str, token->was_quoted) &&
            !is_redirect(previous_token.str, previous_token.was_quoted)) {
            printf("%s", token->str);
        }
        if (token->next && token->next->str) {
            printf(" ");
        }
        previous_token = *token;
        token = token->next;
    }
}

int print(t_tokens *token)
{
    bool flag = true;

    if (token == NULL) {
        return printf("\n");
    }

    if (token->type == OPTION && !ft_strcmp(token->str, "-n")) {
        flag = false;
        token = token->next;
    }

    print_all(token);

    if (flag) {
        printf("\n");
    }

    return 1;
}