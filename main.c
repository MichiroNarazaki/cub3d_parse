#include "cub.h"

int main()
{
	t_parse p;
	int i;
	int x;
	int y;
// int ret;

	if(get_parse(&p) ==-1)
	{
		ft_putstr("ERROR : .cub file is bad setting\n");		
		return -1;
	}
	printf("p.res.x : %d  p.res.y :%d\n", p.res.x, p.res.y);
	printf("e: %s\n", p.tex.tex_e);
	printf("n: %s\n", p.tex.tex_n);
	printf("w: %s\n", p.tex.tex_w);
	printf("s: %s\n", p.tex.tex_s);
	printf("F : %x\n", p.color.floor);
	printf("C : %x\n", p.color.ceiling);

	i = 0;
	printf("\n------MAP-----\n");
	while (p.map.map[i][0])
	{
		printf("%s\n", p.map.map[i]);
		i++;
	}
	printf("\n------MAP-----\n");

	if(valid_map(&p) == -1)
		ft_putstr("ERROR : Map is bad value\n");
	else
		ft_putstr("SUCCESS : The Map is valid \n");
	
	i = 0;
	printf("\n------MAP-----\n");
	while (p.map.map[i][0])
	{
		printf("%s\n", p.map.map[i]);
		i++;
	}
	printf("\n------MAP-----\n");
	return 0;
}
