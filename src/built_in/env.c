#include "minishell.h"

int env(t_env *env, int flag)
{
    t_env *current = env;

    while (current)
    {
        if (flag)
            printf("declare -x ");
        printf("%s\n", current->str);
        current = current->next;
    }

    return 1;
}

char *env_value(char *str, t_env *env)
{
    t_env *current = env;
    char *value = NULL;

    while (current)
    {
        int pos = search_ops_in_str(current->str, '=');
        char *env_name = ft_substr(current->str, 0, pos);

        if (!ft_strcmp(str, env_name))
        {
            value = ft_strtrim(ft_strchr(current->str, '='), "=");
            free(env_name);
            break;
        }

        free(env_name);
        current = current->next;
    }

    return value;
}
