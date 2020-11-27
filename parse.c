#include "cub.h"

#define R 0
#define NO 1
#define SO 2
#define WE 3
#define EA 4
#define S 5
#define F 6
#define C 7
#define MAP 8

int get_res(t_parse *p, char *str) //str==数字 数字
{
	int i;

	i = 0;
	while (!ft_isdigit((int)str[i]))
		i++;
	p->res.x = ft_atoi(str + i);
	i += ft_count_digit(p->res.x);
	p->res.y = ft_atoi(str + i);
	return 0;
}

int finish_parse(char *str, int fd)
{
	free(str);
	close(fd);
	return -1;
}

int is_res(char *str)
{
	int i;

	i = 0;
	while (ft_isspace((int)str[i]))
		i++;
	if (str[i] == 'R')
		return 1;
	else
		return 0;
}

int is_tex(char *str)
{
	int i;

	i = 0;
	while (ft_isspace((int)str[i]))
		i++;
	if (str[i] == 'N' && str[i + 1] == 'O')
		return 1;
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return 1;
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return 1;
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return 1;
	else
		return 0;
}

int res_process(int *check, char *str, int fd, t_parse *p)
{
	if (check[R] != 0) //2回来たらエラー判定
	{
		ft_putstr("ERROR : Double config of R\n");
		return (finish_parse(str, fd));
	}
	if (get_res(p, str) == -1)
	{
		ft_putstr("ERROR : The line has wrong number\n");
		return (finish_parse(str, fd));
	}
	check[0] = 1;
	return 0;
}

int get_tex(t_parse *p, char *str) //index==0
{
	char *dir;

	while (ft_isspace((int)(*str)))
		str++;
	dir = str;
	str += 2;						//NO,SO,WE,EA
	while (ft_isspace((int)(*str))) //pathになるまでstrを進める
		str++;
	if (dir[0] == 'N' && dir[1] == 'O')
		p->tex.tex_n = ft_strdup(str);
	else if (dir[0] == 'S' && dir[1] == 'O')
		p->tex.tex_s = ft_strdup(str);
	else if (dir[0] == 'W' && dir[1] == 'E')
		p->tex.tex_w = ft_strdup(str);
	else if (dir[0] == 'E' && dir[1] == 'A')
		p->tex.tex_e = ft_strdup(str);
	else
		return (-1);
	return 0;
}

int get_color(t_parse *p, char *str, int F_or_C) //*str == C(F)
{
	int r;
	int g;
	int b;

	while (!ft_isdigit((int)*str))
		str++;
	r = ft_atoi(str);
	str += ft_count_digit(r);
	while (!ft_isdigit((int)*str))
		str++;
	g = ft_atoi(str);
	str += ft_count_digit(g);
	while (!ft_isdigit((int)*str))
		str++;
	b = ft_atoi(str);
	if (F_or_C == F)
		p->color.floor = r * 256 * 256 + g * 256 + b;
	else if (F_or_C == C)
		p->color.ceiling = r * 256 * 256 + g * 256 + b;
	return 0;
}

int switch_index(char *str)
{
	while (ft_isspace((int)*str))
		str++;
	if (str[0] == 'N' && str[1] == 'O')
		return NO;
	else if (str[0] == 'S' && str[1] == 'O')
		return SO;
	else if (str[0] == 'W' && str[1] == 'E')
		return WE;
	else if (str[0] == 'E' && str[1] == 'A')
	{
		return EA;
	}
	else
		return (-1);
}

int tex_process(int *check, char *str, int fd, t_parse *p)
{
	int index;

	if ((index = switch_index(str)) == -1)
	{
		ft_putstr("ERROR : Bad config of TEX initial\n");
		return (finish_parse(str, fd));
	}
	if (check[index] != 0) //2回来たらエラー判定
	{
		ft_putstr("ERROR : Double config of TEX\n");
		return (finish_parse(str, fd));
	}
	if (get_tex(p, str) == -1)
	{
		ft_putstr("ERROR : The line has bad value\n");
		return (finish_parse(str, fd));
	}
	check[index] = 1;
	return 0;
}

int color_process(int *check, char *str, int fd, t_parse *p)
{
	int index;
	int i;

	i = 0;
	/*F or C 判別*/
	while (ft_isspace((int)str[i]))
		i++;
	if (str[i] == 'F')
		index = F;
	else if (str[i] == 'C')
		index = C;
	else
	{
		ft_putstr("ERROR : Bad config of color initial\n");
		return (finish_parse(str, fd));
	}
	if (check[index] != 0) //2回来たらエラー判定
	{
		ft_putstr("ERROR : Double config of color\n");
		return (finish_parse(str, fd));
	}
	if (get_color(p, &str[i], index) == -1)
	{
		ft_putstr("ERROR : The line has bad value\n");
		return (finish_parse(str, fd));
	}
	check[index] = 1;
	return 0;
}

int is_color(char *str)
{
	int i;

	i = 0;
	while (ft_isspace((int)str[i]))
		i++;
	if (str[i] == 'F' || str[i] == 'C')
		return 1;
	return 0;
}

char *map_process(int *check, char *str, int fd, t_parse *p)
{
	int w;
	int h;
	int r;

	r = 2;
	h = 0;
	p->map.w = 0;
	while (r > 0 && h < rows)
	{
		if (r != 2) //rが2(初期値だったらすでにstrが読み込んであるので)
		{
			if ((r = get_next_line(fd, &str)) == -1)
				return NULL;
		}
		w = 0;
		while (str[w] && w < cols)
		{
			p->map.map[h][w] = str[w];
			w++;
		}
		if (w == rows) //whileをw<colsで抜けたら
		{
			ft_putstr("ERROR : The Map width is 500+\n");
			return NULL;
		}
		if (p->map.w < w)
			p->map.w = w;
		if (r != 0) //0の時最後なのでfreeは関数を出た後に実行される
			free(str);
		if (r == 2)
			r = 1;
		h++;
	}
	if (h == rows)
	{
		ft_putstr("ERROR : The Map width is 500+\n");
		return NULL;
	}
	p->map.h = h;
	return str;
}

int is_map(char *str)
{
	int i;

	i = 0;
	while (ft_isspace((int)str[i]))
		i++;
	if (str[i] == '1')
		return 1;
	return 0;
}

int is_all_symbol(int *check)
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (check[i] != 1)
			return -1;
		i++;
	}
	return 0;
}

int get_parse(t_parse *p) //bad=-1 good=0
{
	char *str;
	int i;
	int fd;
	int r;
	char *cub_file = "easy.cub";
	int check[9];

	i = 0;
	while (i < 9)
		check[i++] = 0;
	fd = open(cub_file, O_RDONLY);
	r = 1;
	while (r > 0)
	{
		if ((r = get_next_line(fd, &str)) == -1)
			break;
		if (is_res(str) == 1)
		{
			if (res_process(check, str, fd, p) == -1)
				return -1;
		}
		else if (is_tex(str) == 1)
		{
			if (tex_process(check, str, fd, p) == -1)
				return -1;
		}
		else if (is_color(str) == 1)
		{
			if (color_process(check, str, fd, p) == -1)
				return -1;
		}
		else if (is_map(str) == 1)
		{
			if (!(str = map_process(check, str, fd, p)))
				return -1;
		}
		free(str);
	}
	close(fd);
	return (is_all_symbol(check));
}
