#ifndef _BOMB_H_
#define _BOMB_H_

#include "extern.h"
#include "graph.h"

struct BOMBDATA{
	float	angle,
		large,
		speed,
		fx,
		fy,
		f_hanyou[8];
	int	img,
		count,
		flash,
		x,
		y,
		power,
		type,
		direction,//-1:なし 0:上 1:下 2:左 3:右
		who,//誰のボムで起爆した？
		pattern,//1:貫通 2~5:誘導ボム
		timer,//紫スペル
		i_hanyou[8];
	bool	bRenbaku,
		bExplosion,
		bDelete,
		bYukari;
};

struct EXPDATA{
	int	type,
		count,
		x,
		y,
		flash,
		x_length[2],//-1の場合は円形
		y_length[2],
		power,
		pattern;
	float	now_power,
		per_power;
};

extern list<BOMBDATA> Bomb;
extern list<EXPDATA> Exp;

extern void BLoad();
extern void BMake(int x,int y,int type,int power,int img=0,int pattern=0,int timer=180,bool renbaku=true);
extern void BDraw();
extern void BMove(list<BOMBDATA>::iterator &it);
extern void EMake(int x,int y,int type,int power,int pattern,int who,bool renbaku=true);
extern int ELength(int x,int y,int power,int pattern,int *x_lengthA,int *x_lengthB,int *y_lengthA,int *y_lengthB,bool flag);
extern void EDraw();
extern void EMove(list<EXPDATA>::iterator &it);

#endif