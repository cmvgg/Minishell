#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"


int main(int argc, char **argv)
{
    int f = 0;
    int j = 0;
    int quote = 0;

    if(argv[j][f] == 34)
    {
        quote++;
        f++;
        while(argv[j][f])
        {
            if(argv[j][f] == 34)
            {
                quote--;
                break ;
            }
            f++;
        }
    }
    if(argv[j][f] == 34)
    {
        f++;
        quote++;
        while(argv[j][f])
        {
            if(argv[j][f] == 34)
            {
                quote--;
                break ;
            }
            f++;
        }
    }
    printf("es: %d\n", quote);
    return (0);
}
