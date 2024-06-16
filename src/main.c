#include "minishell.h"

long long g_exit_status = 0;

int check_line(char *line)
{
    int i;
    int pos;

    if (!line)
    {
        printf("exit\n");
        exit(g_exit_status);
    }
    
    i = -1;
    pos = search_ops_in_str(line, "|");
    if (pos != -1)
    {
        while (++i < pos)
            if (line[i] != ' ' && line[i] != '\t')
                return (1);
        printf("%s\n", EPARSE);
        return (0);
    }
    return (1);
}

char *check_double_pipes(char *line)
{
    int i;
    char *new_line;

    i = -1;
    while (line[++i])
    {
        if (line[i] == '|' && (line[i - 1] == '|' || line[i + 1] == '|'))
        {
            new_line = ft_substr(line, 0, i);
            add_history(line);
            free(line);
            return (new_line);
        }
    }
    add_history(line);
    return (ft_strtrim(line, " "));
}

int main(int argc, char **argv, char **envp)
{
    int fd;
    char *line;
    t_env *env;

    (void)argv; 
    handle_global_signals();
    
    if (argc == 1)
    {
        fd = dup(STDIN_FILENO);
        env = init_env(envp);
        
        while (1)
        {
            dup2(fd, STDIN_FILENO);
            line = readline(PROMPT);
            
            if (!check_line(line) || crazy(line))
                continue;
            
            line = check_double_pipes(line);
            
            if (ft_strlen(line))
                pipe_commands(line, env);
            
            free(line); 
        }
    }
    else
    {
        printf("Error: Too many arguments!\n"); // Mensaje de error si se proporcionan demasiados argumentos
    }
    
    return (0);
}
