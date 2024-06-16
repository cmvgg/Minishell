#include "minishell.h"

static void unset_env(t_tokens *token, t_env *env)
{
    t_env *prev = NULL;
    t_env *curr = env;
    size_t var_len = ft_strlen(token->str);

    while (curr && token->str)
    {
        if (!ft_strncmp(token->str, curr->str, var_len))
        {
            if (!prev)
                env = curr->next;  // Actualiza el inicio de la lista si el nodo a eliminar es el primero
            else
                prev->next = curr->next;  // Conecta el nodo anterior al siguiente nodo, saltando el actual

            if (curr->was_added)
                free(curr->str);  // Libera la cadena del nodo si fue agregada
            free(curr);  // Libera el nodo

            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

int unset(t_tokens *token, t_env *env)
{
    t_env *head = env;

    if (!token->next)
        return printf("not enough arguments\n");

    token = token->next;
    while (token)
    {
        env = head;
        unset_env(token, env);
        token = token->next;
    }

    env = head;
    return 1;
}
