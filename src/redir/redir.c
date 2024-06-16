#include "minishell.h"

int files_exist(t_tokens *token)
{
    t_tokens *head = token;
    int res = 1;
    int fd;

    while (token)
    {
        if (token->type == RED_IN && token->next)
        {
            fd = open(token->next->str, O_RDONLY, 0644);
            if (fd < 0)
            {
                res = 0;
                if (!token->skip)
                    printf("%s: %s\n", token->next->str, UNKNOWN);
                token->skip = 1;
                break;
            }
            close(fd); // Close the file descriptor after opening
        }
        token = token->next;
    }
    return res;
}

void heredoc_while(char *delim)
{
    int temp;
    char *delim_line;
    pid_t pid;

    handle_cmd_signals();
    pid = fork();
    if (pid == 0)
    {
        delim_line = ft_strjoin(delim, "\n");
        execute_cicle(delim_line); // Assuming execute_cicle handles the heredoc operation
        free(delim_line);
        exit(g_exit_status);
    }
    waitpid(pid, &temp, 0);
    g_exit_status = temp >> 8;
}

static void out(t_TokenType type, char *output_file)
{
    int fd;

    if (type == APPEND_OUT)
        fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void in(char *input_file)
{
    int fd = open(input_file, O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    dup2(fd, STDIN_FILENO);
    close(fd);
}

int handle_redir(t_tokens *token)
{
    t_TokenType type;

    check_heredoc(token);
    if (!files_exist(token))
        return 0;

    while (token)
    {
        if (is_redirect(token->str, token->was_quoted))
        {
            type = token->type;
            if (type == APPEND_OUT || type == RED_OUT)
                out(type, token->next->str);
            else if (type == RED_IN)
                in(token->next->str);
        }
        token = token->next;
    }
    return 1;
}

