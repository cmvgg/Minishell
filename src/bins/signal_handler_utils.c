#include "minishell.h"

static int g_exit_status = 0;

static void handle_signal_redirs(int sig)
{
    if (sig == SIGINT) {
        g_exit_status = 130;
        exit(g_exit_status);
    }
}

void handle_signal_redir(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_signal_redirs;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGINT, &sa, NULL);
}