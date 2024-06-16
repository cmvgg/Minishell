#include "minishell.h"

static void handle_signal(int sig)
{
    if (sig == SIGINT)
	{
        g_exit_status = 130;
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void handle_cmd_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
}

void handle_global_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
}

int get_exit_status(void)
{
    return g_exit_status;
}

void reset_exit_status(void)
{
    g_exit_status = 0;
}