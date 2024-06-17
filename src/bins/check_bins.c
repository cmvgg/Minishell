#include "minishell.h"

int env_len(t_env *env)
{
    int count;
	
	count = 0;
    while (env)
	{
        count++;
        env = env->next;
    }
    return count;
}

static int is_executable(char *bin_path, struct stat f)
{
    int result = 0;
    
    if ((f.st_mode & S_IFMT) == S_IFREG) {
        if (f.st_mode & S_IXUSR) {
            result = 1;
        } else {
            printf("Permission denied: %s\n", bin_path);
            result = -1;
        }
    }
    
    free(bin_path);
    return result;
}

int check_bins(t_tokens *token, t_env *env)
{
    int i = 0;
    char *bin_path;
    char **path;
    struct stat f;

    path = get_path(env);
    if (!path) {
        return 0;
    }

    while (path[i])
	{
        bin_path = get_bin_path(path[i], token->str);
        if (lstat(bin_path, &f) == -1) {
            free(bin_path);
        } else {
            int exec_status = is_executable(bin_path, f);
            if (exec_status == 1) {
                while (path[i]) {
                    free(path[i]);
                    i++;
                }
                free(path);
                return run_cmd(bin_path, token, env, 1);
            } else if (exec_status == -1) {
                while (path[i]) {
                    free(path[i]);
                    i++;
                }
                free(path);
                return 0;
            }
        }
        i++;
    }

    i = 0;
    while (path[i]) {
        free(path[i]);
        i++;
    }
    free(path);
    return 0;
}

static int free_values(char *bin_path, char **args, char **env_matrix, int flag)
{
    int i = 0;

    if (flag) {
        free(bin_path);
    }

    while (args[i])
	{
        free(args[i]);
        i++;
    }
    free(args);

    i = 0;
    while (env_matrix[i])
	{
        free(env_matrix[i]);
        i++;
    }
    free(env_matrix);

    return 1;
}

int run_cmd(char *bin_path, t_tokens *token, t_env *env, int flag)
{
    char **args;
    char **env_matrix;

    args = fill_args(token);
    env_matrix = fill_env_matrix(env);
    execve(bin_path, args, env_matrix);

    return free_values(bin_path, args, env_matrix, flag);
}