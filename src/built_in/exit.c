#include "minishell.h"

static long long ft_atoll(const char *str)
{
    long long res = 0;
    int signal = 1;
    int i = 0;

    while (isspace((unsigned char)str[i]))
        i++;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            signal = -1;
        i++;
    }

    while (isdigit((unsigned char)str[i]))
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }

    return (res * signal);
}

static int streq(char *str1, char *str2)
{
    size_t i = 0;

    while (str1[i] || str2[i])
    {
        if (str1[i] != str2[i])
            return 0;
        i++;
    }

    return 1;
}

static int fits_in_longlong(char *str)
{
    long long out = 0;
    int c;

    if (strlen(str) > 20)
        return 0;

    if (streq("-9223372036854775808", str))
        return 1;

    if (*str == '-' || *str == '+')
        str++;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return 0;

        c = *str - '0';

        if (out > (LLONG_MAX - c) / 10)
            return 0;

        out = out * 10 + c;
        str++;
    }

    return 1;
}

static int is_digit_signal(char *str)
{
    while (*str)
    {
        if (!isdigit((unsigned char)*str) && *str != '-' && *str != '+')
            return 0;
        str++;
    }
    return 1;
}

int exit_terminal(t_commands *command)
{
    int size = lstsize_tokens(command->token, 0);

    if (size <= 2)
    {
        if (size == 2)
        {
            char *exit_str = command->token->next->str;

            if (is_digit_signal(exit_str) && fits_in_longlong(exit_str))
                g_exit_status = ft_atoll(exit_str);
            else
            {
                g_exit_status = 2;
                printf("exit\n%s\n", NAR);
                exit(g_exit_status);
            }
        }
        else
            g_exit_status = EXIT_SUCCESS;

        free_structs(command, 1);
        printf("exit\n");
        exit(g_exit_status);
    }

    g_exit_status = EXIT_FAILURE;
    return printf("%s\n", TMA);
}
