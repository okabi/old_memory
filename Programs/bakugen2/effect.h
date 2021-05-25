#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "extern.h"
#include "graph.h"

struct EFFECTDATA{
	float	x,
		y,
		angle,
		large,
		move_x,
		move_y,
		speed,
		f_hanyou[8];
	int	img,
		count,
		flash,
		pattern,
		red,
		green,
		blue,
		i_hanyou[8];
	bool	bDelete,
		bBlend;
};

extern list<EFFECTDATA> Effect;
extern list<EFFECTDATA> BackEffect;

extern void EfLoad();
extern void EfMake(float x,float y,int img,int pattern);
extern void EfDraw();
extern void EfMove(list<EFFECTDATA>::iterator &it);
extern void BEfMake(float x,float y,int img,int pattern);
extern void BEfDraw();
extern void BEfMove(list<EFFECTDATA>::iterator &it);

#endif