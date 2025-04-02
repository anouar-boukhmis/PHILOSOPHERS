#include "philo.h"


long    ft_atoi(char *str)
{
    int i;
    long result;

    i = 0;
    result  = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if(str[i] == '+')
        i++;
    if (!(str[i] >= '0' && str[i] <= '9'))
        return(-1);
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        if (result > INT_MAX)
            return (-1);
        i++;
    }
    return(result);
}
int test_parsing(char **av)
{
    int i;
    int result;

    i = 1;
    while (av[i])
    {
        if(ft_atoi(av[i]) < 0)
        {
            write(2, "Invalid Arguments\n", 19);
            return(-1);
        }
        i++;
    }
    return (0);
}