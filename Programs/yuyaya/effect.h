#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "extern.h"

struct EFFECTDATA{
	float	x,
		y,
		large,
		angle,
		speed,
		move_x,
		move_y,
		f_hanyou[8];
	int     flash,
		red,
		green,
		blue,
		img,
		count,
		spe_count,
		pattern,
		num,
		i_hanyou[8];
	bool	bBlend,
		bDelete;//消えます、消えます
};

extern list<EFFECTDATA> Effect;
extern list<EFFECTDATA> Effect2;//自機の下
extern list<EFFECTDATA> Effect3;//敵弾の上

struct ITEMDATA{
	float	x,
		y,
		large,
		angle,
		speed,
		move_x,
		move_y,
		atari;
	int     flash,
		img,
		count,
		soten,
		bound_num,
		pattern;
	bool	bKira,
		bDelete;//一度でも画面内に入ったか？
};

extern list<ITEMDATA> Item;

extern void EfReset();
extern void EfDraw();
extern void EfMove(list<EFFECTDATA>::iterator &it);
extern void EfMake(float x,float y,int img,int pattern,int spe_count=1,float angle=0);
extern void EfDraw2();
extern void EfMove2(list<EFFECTDATA>::iterator &it);
extern void EfMake2(float x,float y,int num,int pattern,float angle=0,bool bBlend=false);
extern void EfDraw3();
extern void EfMove3(list<EFFECTDATA>::iterator &it);
extern void EfMake3(float x,float y,int pattern,float angle=0);
extern void IDraw();
extern void IMove(list<ITEMDATA>::iterator &it);
extern void IMake(float x,float y,int img,int late=0);

#endif