#include "cub.h"

int around_is(t_parse *p, int x, int y)
{
	int ret;

	ret = 0;
	if (!(p->map.map[y][x - 1] == '0' || p->map.map[y][x - 1] == '1' || p->map.map[y][x - 1] == 'p'))
		ret = -1;
	if (!(p->map.map[y][x + 1] == '0' || p->map.map[y][x + 1] == '1' || p->map.map[y][x + 1] == 'p'))
		ret = -1;
	if (!(p->map.map[y - 1][x] == '0' || p->map.map[y - 1][x] == '1' || p->map.map[y - 1][x] == 'p'))
		ret = -1;
	if (!(p->map.map[y + 1][x] == '0' || p->map.map[y + 1][x] == '1' || p->map.map[y + 1][x] == 'p'))
		ret = -1;
	return ret; //0 : ok -1 : no
}

int valid_map_main(t_parse *p, int x, int y)
{
	int ret; //1のままif文に引っかからずreturnされる=まわりに0がない=周りは壁のみ

	ret = 0;
	if (!(0 < x && x < p->map.w && 0 < y && y < p->map.h) && !p->map.map[y][x])
		return -1;				  //だめ
	if (around_is(p, x, y) == -1) //aroundがnullならreturn -1
		return -1;
	if (p->map.map[y][x - 1] == '0')
	{
		p->map.map[y][x - 1] = 'p';
		if ((ret = valid_map_main(p, x - 1, y)) == -1)
			return -1;
	}
	if (p->map.map[y][x + 1] == '0')
	{
		p->map.map[y][x + 1] = 'p';
		if ((ret = valid_map_main(p, x + 1, y)) == -1)
			return -1;
	}
	if (p->map.map[y - 1][x] == '0')
	{
		p->map.map[y - 1][x] = 'p';
		if ((ret = valid_map_main(p, x, y - 1)) == -1)
			return -1;
	}
	if (p->map.map[y + 1][x] == '0')
	{
		p->map.map[y + 1][x] = 'p';
		if ((ret = valid_map_main(p, x, y + 1)) == -1)
			return -1;
	}
	return ret; //1:良い -1:ダメ
}

int valid_map(t_parse *p)
{
	int w;
	int h;
	// char **tmp;
	int start_x;
	int start_y;

	if (find_start(p, &start_x, &start_y) == -1)
	{
		ft_putstr("ERROR : The map has no start position\n");
		return -1;
	}

	p->map.map[start_y][start_x] = 'p';
	return (valid_map_main(p, start_x, start_y));
}