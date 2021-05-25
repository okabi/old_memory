#ifndef _MAP_H_
#define _MAP_H_

#include "extern.h"
#include "graph.h"

#define MAP_NUM 6
#define LARGE_X 19
#define LARGE_Y 13


struct GRAND_MAPDATA{
	int	img_ground[2],
		img_wall[2],
		img_block[2],
		block_num,
		item_num[ITEM_GRAPH_NUM];
	char	name[64];
};

struct MAPDATA{
	int	field[LARGE_X][LARGE_Y],// -6~-3:�����\��n(-2-P�ɂ��N��) -2:���e 0:�ʉ߉\ 1:�� 2:�u���b�N 3:�A�C�e��
		type;
	
};

extern GRAND_MAPDATA MapData[MAP_NUM];
extern MAPDATA Map;

extern void MLoad();
extern void MDraw();
extern void M1Event();
extern void M2Event();
extern void M5Event();

#endif