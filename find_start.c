#include "cub.h"

int find_start(t_parse *p, int *x, int *y)
{
	int i;
	int w;
	int h;
	int check;//初期値1　スタートポジションの数を数える

	check = 0;
	h = 0;
	while (h < p->map.h)
	{
		w = 0;
		while (w < p->map.w)
		{
			if (p->map.map[h][w] == 'N' || p->map.map[h][w] == 'S' || p->map.map[h][w] == 'W' || p->map.map[h][w] == 'E')
			{
				*y = h;
				*x = w;
				check++;
			}
			w++;
		}
		h++;
	}
	if(check != 1)
		return -1;
	return 0;
}