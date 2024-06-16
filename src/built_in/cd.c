#include "minishell.h"

void update_oldpwd(char *dir, t_env *env)
{
    t_env *head = env;
    while (env)
    {
        int pos = search_ops_in_str(env->str, '=');
        char *env_name = ft_substr(env->str, 0, pos);
        
        if (!ft_strcmp(env_name, "OLDPWD"))
        {
            if (env->was_added)
                free(env->str);
            env->str = form_variable(env_name, dir);
            env->was_added = 1;
            break;
        }
        
        free(env_name);
        env = env->next;
    }
    env = head;
}

void update_pwds(char *oldpwd, t_env *env)
{
    t_env *head = env;
    char value[PATH_MAX];
    char *pwd = ft_strdup(getcwd(value, PATH_MAX));
    
    while (env)
    {
        int pos = search_ops_in_str(env->str, '=');
        char *env_name = ft_substr(env->str, 0, pos);
        
        if (!ft_strcmp(env_name, "PWD"))
        {
            if (env->was_added)
                free(env->str);
            env->str = form_variable(env_name, pwd);
            env->was_added = 1;
            break;
        }
        
        free(env_name);
        env = env->next;
    }
    
    free(pwd);
    env = head; // Restaurar el puntero original
    update_oldpwd(oldpwd, env);
}

int change_dir(t_tokens *token, t_env *env)
{
    char value[PATH_MAX];
    char *dir = NULL;
    char *oldpwd = getcwd(value, PATH_MAX);
    
    if (!token->next || (token->next->str && !ft_strcmp(token->next->str, "~")))
        dir = env_value("HOME", env);
    else if (token->next->str && !ft_strcmp(token->next->str, "-"))
    {
        dir = env_value("OLDPWD", env);
        printf("%s\n", dir); // Se imprime el directorio anterior
    }
    else if (token->next->str)
        dir = ft_strdup(token->next->str);
    
    if (dir && chdir(dir))
    {
        g_exit_status = 1;
        printf("%s\n", "Unknown directory"); // Mensaje de error personalizado
    }
    else
        update_pwds(ft_strdup(oldpwd), env);
	if (dir)
		free(dir);
    return 1;
}