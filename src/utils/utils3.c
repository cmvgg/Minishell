#include "minishell.h"

int crazy(char *line)
{
    if (!line)
        return 0;

    int result = 0;
    
    if (!ft_strcmp(line, "crazy"))
    {
        printf("\nCrazy? I was crazy once\n");
        printf("They locked me in a room, a rubber room\n");
        printf("A rubber room with rats, and rats make me crazy\n\n");
        result = 1;
    }

    return result;
}
