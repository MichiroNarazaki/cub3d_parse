#ifndef CUB_H
# define CUB_H


#include "libft/includes/libft.h"
#include "get_next_line.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define cols 500
#define rows 500

typedef struct s_tex
{
	char *tex_n;
	char *tex_s;
	char *tex_w;
	char *tex_e;
}	t_tex;

typedef struct s_color
{
	int floor;
	int ceiling;
}	t_color;

typedef struct s_map
{
	char map[500][500];
	int h;
	int w;
}	t_map;

typedef struct s_res
{
	unsigned int x;
	unsigned int y;
}	t_res;

typedef struct s_parse
{
	t_tex tex;
	t_color color;
	t_map map;
	t_res res;
}	t_parse;


typedef struct s_start 
{
	int x;
	int y;
}	t_start;

int get_parse(t_parse *p);
int find_start(t_parse *p, int *x, int *y);
void map_init(t_parse *p,char **map);
int valid_map_main(t_parse *p, int x, int y);
int valid_map(t_parse *p);

#endif