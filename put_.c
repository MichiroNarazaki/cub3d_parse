#include "cub.h"

int ft_putchar(char c)
{
	return (write(1,&c,1));
}
int ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}