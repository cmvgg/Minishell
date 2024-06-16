#include "minishell.h"

char **fill_ops(void)
{
    char **ops = (char **)malloc(sizeof(char *) * 5);
    if (!ops)
        return NULL;

    ops[0] = ">";
    ops[1] = "<";
    ops[2] = ">>";
    ops[3] = "<<";
    ops[4] = NULL;

    return ops;
}

char **fill_env_matrix(t_env *env)
{
    int i = 0;
    int size = env_len(env);
    char **envp = (char **)malloc(sizeof(char *) * (size + 1));
    if (!envp)
        return NULL;

    envp[size] = NULL;

    while (env && i < size)
    {
        envp[i] = ft_strdup(env->str);
        if (!envp[i])
        {
            while (i >= 0)
                free(envp[i--]);
            free(envp);
            return NULL;
        }
        env = env->next;
        i++;
    }

    return envp;
}

char **fill_args(t_tokens *token)
{
    int i = 0;
    int size = lstsize_tokens(token, 1);
    char **args = (char **)malloc(sizeof(char *) * (size + 1));
    if (!args)
        return NULL;

    args[size] = NULL;
    t_tokens *previous = NULL;

    while (token && i < size)
    {
        if (!is_redirect(token->str, token->was_quoted) &&
            (!previous || !is_redirect(previous->str, previous->was_quoted)))
        {
            args[i] = ft_strdup(token->str);
            if (!args[i])
            {
                while (i >= 0)
                    free(args[i--]);
                free(args);
                return NULL;
            }
            i++;
        }
        previous = token;
        token = token->next;
    }

    return args;
}

int is_accepted(t_tokens *token)
{
    if (!ft_strcmp(token->str, "$?") && token->type == COMMAND)
        return 0;
    return 1;
}

int is_bin(char *str)
{
    if (str[0] == '.' || !ft_strncmp(str, "./bin", 5))
        return 1;
    return 0;
}
