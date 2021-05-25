#ifndef _ITEM_H_
#define _ITEM_H_

#include "extern.h"
#include "graph.h"

struct ITEMDATA{
	float	angle;
	int	img,
		count,
		x,
		y,
		type;
	bool	bExist;
};

extern list<ITEMDATA> Item;

extern void ILoad();
extern void IMake(int x,int y,int type,bool exist=false);
extern void IDraw();
extern void IMove(list<ITEMDATA>::iterator &it);

#endif