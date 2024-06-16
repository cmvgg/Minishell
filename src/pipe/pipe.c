#include "minishell.h"

void parent(int fd_in, int count_pipes)
{
    for (int i = 0; i < count_pipes; ++i)
    {
        wait(NULL);
    }
    close(fd_in);
}

void close_write_read(int *pipes)
{
    close(pipes[0]);
    close(pipes[1]);
}

void children(t_commands *commands, int fd_in, int count_pipes)
{
    int pipes[2];
    pid_t pid;

    for (int i = 0; i < count_pipes; ++i)
    {
        pipe(pipes);
        pid = fork();
        if (pid == 0)
        {
            if (i != 0)
                dup2(fd_in, STDIN_FILENO);
            if (i != count_pipes - 1)
                dup2(pipes[1], STDOUT_FILENO);
            close_write_read(pipes);
            close(fd_in);
            parser(commands);
            exit(g_exit_status);
        }
        dup2(pipes[0], fd_in);
        close_write_read(pipes);
        commands = commands->next;
    }
}

void open_pipe(t_commands *commands)
{
    int count_pipes = lstsize_commands(commands);

    if (count_pipes > 1)
    {
        int fd_in = dup(STDIN_FILENO);
        children(commands, fd_in, count_pipes);
        parent(fd_in, count_pipes);
    }
    else
    {
        parser(commands);
    }
}
