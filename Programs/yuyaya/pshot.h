#ifndef _PSHOT_H_
#define _PSHOT_H_

#include "extern.h"

#define BOMB_NUM 30 //残像の数

struct PSHOTDATA{
	float	x,
		y,
		speed,
		large,
		angle,
		move_x,
		move_y,
		atari;
	int     life,
		flash,
		atack,
		img,
		count,
		pattern;
	bool	bBlend,
		bDelete;//一度でも画面内に入ったか？
};

extern list<PSHOTDATA> PShot;

struct PLASERDATA{
	float	x[2],//0:根元 1:先端
		y[2],
		length,
		large;
	int     flash,
		atack,
		img,
		count,
		delete_count;
	bool	bBlend,
		bDelete;//消滅判定
};

extern list<PLASERDATA> PLaser;

struct BOMBDATA{
	float	x,
		y,
		zx[BOMB_NUM],
		zy[BOMB_NUM],
		large,
		angle,
		speed,
		move_x,
		move_y,
		atari;
	int     flash,
		atack,
		img,
		count;
	bool	bDelete,
		bAuto;
};

extern list<BOMBDATA> Bomb;

extern void PSReset();
extern void PSDraw();
extern void PSMove(list<PSHOTDATA>::iterator &it);
extern void PSMake(float x,float y,float speed, float angle,int img,int pattern,int atack);
extern void PLDraw();
extern void PLMove(list<PLASERDATA>::iterator &it);
extern void PLMake(int img,int atack);
extern void PBDraw();
extern void PBMove(list<BOMBDATA>::iterator &it);
extern void PBMake(float x,float y,float angle,int img,int atack,bool au=false);

#endif