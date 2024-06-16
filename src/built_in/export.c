#include "minishell.h"

static char *form_variable(char *name, char *value)
{
    char *temp = ft_strjoin(name, "=");
    char *str = ft_strjoin(temp, value);
    free(temp);
    return str;
}

static bool env_exists(t_tokens *head, const char *new_env, const char *env_value)
{
    while (head)
    {
        int pos = search_ops_in_str(head->str, '=');
        char *env_name = ft_substr(head->str, 0, pos);
        if (!ft_strcmp(new_env, env_name))
        {
            if (head->was_quoted)
                free(head->str);
            head->str = form_variable(env_name, env_value);
            head->was_quoted = 1;
            free(env_name);
            return true;
        }
        free(env_name);
        head = head->next;
    }
    return false;
}

static bool check_env_name(const char *name)
{
    if (ft_strlen(name) == 0 || name[0] == '$' || (name[0] >= '0' && name[0] <= '9'))
    {
        printf("Invalid environment variable name\n");
        return false;
    }
    return true;
}

void export(t_tokens *command_env)
{
    t_tokens *env_head = command_env;

    while (command_env && command_env->str)
    {
        if (ft_strchr(command_env->str, '='))
        {
            int pos = search_ops_in_str(command_env->str, '=');
            char *env_name = ft_substr(command_env->str, 0, pos);
            if (!check_env_name(env_name))
            {
                free(env_name);
                return;
            }
            char *env_value = ft_substr(command_env->str, pos + 1, ft_strlen(command_env->str) - pos - 1);
            if (!env_exists_update(env_head, env_name, env_value))
            {
                t_tokens *new_env = lstnew_env(form_variable(env_name, env_value), 1);
                lstadd_back_env(&command_env, new_env);
            }
            free(env_name);
            free(env_value);
        }
        command_env = command_env->next;
    }
}