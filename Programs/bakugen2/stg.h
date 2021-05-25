#ifndef _STG_H_
#define _STG_H_

#include "extern.h"
#include "graph.h"

#define ENEMY_PATTERN_MAX 6

struct ENEMYDATA{
	float	x,
		y,
		atari,
		large,
		f_hanyou[4];
	int	img,
		count,
		flash,
		level,
		type,
		i_hanyou[4];
	bool	bExist,
		bShotend;
};

struct SHOTDATA{
	float	x,
		y,
		atari,
		speed,
		move_x,
		move_y,
		angle,
		f_hanyou[4];
	int	img,
		type,
		count,
		flash,
		late,
		max_late,
		pattern,
		i_hanyou[4];
};

extern ENEMYDATA Enemy;
extern list<SHOTDATA> Shot;

extern void StMain();
extern void StLoad();
extern void EnMake();
extern void EnDraw();
extern void EnMove();
extern void EnShot0();
extern void EnShot1();
extern void EnShot2();
extern void EnShot3();
extern void EnShot4();
extern void EnShot5();
extern void EnShot6();
extern void ShMake(float x,float y,float angle,float speed,int img,int type,int pattern,int late);
extern void ShDraw();
extern void ShMove(list<SHOTDATA>::iterator &it);

#endif