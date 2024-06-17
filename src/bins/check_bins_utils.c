#include "minishell.h"

char **get_path(t_env *env)
{
    char *value;
    char **path;

    value = env_value("PATH", env);
    if (value)
	{
        path = ft_split(value, ':');
        free(value);
        return path;
    }
    return NULL;
}

char *get_bin_path(char *path, char *str)
{
    char *bin_path;
    char *small_bin_path;

    if (!path || !str) {
        return NULL;
    }
    small_bin_path = ft_strjoin(path, "/");
    if (!small_bin_path) {
        free(path);
        return NULL;
    }
    bin_path = ft_strjoin(small_bin_path, str);
    free(small_bin_path);
    free(path);
    return bin_path;
}

void check_heredoc(t_tokens *token)
{
    int fd;

    while (token)
	{
        if (!token->skip && token->type == HEREDOC && token->next) {
            heredoc_while(token->next->str);
            fd = open("/tmp/1", O_RDONLY, 0644);
            if (fd != -1) {
                dup2(fd, STDIN_FILENO);
                unlink("/tmp/1");
                close(fd);
            }
            token->skip = 1;
        }
        token = token->next;
    }
}

void execute_cicle(char *delim_line)
{
    int fd;
    ssize_t output;
    char buff[4095 + 1];

    if (!delim_line)
	{
        return;
    }

    handle_signal_redir();
    write(STDOUT_FILENO, "> ", 2);

    fd = open("/tmp/1", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
        perror("open");
        return;
    }

    output = read(STDIN_FILENO, buff, 4095);
    while (output > 0)
	{
        handle_signal_redir();
        buff[output] = '\0';
        if (ft_strcmp(buff, delim_line) == 0)
            break;
        ft_putstr_fd(buff, fd);
        write(STDOUT_FILENO, "> ", 2);
        output = read(STDIN_FILENO, buff, 4095);
    }

    if (output == -1)
        perror("read");

    close(fd);
}
