#include "minshell.h"

void free_tokens(t_tokens *token)
{
    t_tokens *node;
    
    while (token)
    {
        node = token;
        token = token->next;
        
        if (node->str && ft_strcmp(node->str, "$") != 0)
            free(node->str);
        
        free(node);
    }
}

void free_env(t_env *env)
{
    t_env *node;
    
    while (env)
    {
        node = env;
        env = env->next;
        
        if (node->was_added)
            free(node->str);
        
        free(node);
    }
}

void free_structs(t_commands *commands, int flag)
{
    t_commands *node;
    int size = lstsize_commands(commands);
    
    while (commands)
    {
        node = commands;
        commands = commands->next;
        
        free_tokens(node->token);
        if (flag)
            free_env(node->env);
        
        free(node);
    }
}
