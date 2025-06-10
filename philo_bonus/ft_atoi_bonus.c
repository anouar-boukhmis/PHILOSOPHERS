#include "philo_bonus.h"


long    ft_atoi1(char *str)
{
    int i;
    long result;

    i = 0;
    result  = 0;

    if (!str)
        return(-1);
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if(str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        if (result > INT_MAX)
            return (-1);
        i++;
    }
    if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
        return(-1);
    return(result);
}

int test_parsing(char **av, int ac)
{
    int i;

    i = 1;
    if (ac < 5 || ac > 6)
    {
        write(2, "Invalid Arguments\n", 19);
        return(-1);
    }
    while (av[i])
    {
        if(ft_atoi(av[i]) < 0 || ft_atoi(av[i]) > INT_MAX)
        {
            write(2, "Invalid Arguments\n", 19);
            return(-1);
        }
        i++;
    }
    return (0);
}
