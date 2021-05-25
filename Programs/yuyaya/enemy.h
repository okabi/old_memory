#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "extern.h"

struct ENEMYDATA{
	float	x,
		y,
		back_x,
		back_y,
		speed,
		large,
		angle,
		move_x,
		move_y,
		atari,
		f_hanyou[8];
	int     flash,
		life,
		max_life,
		soten,
		img,
		count,
		move_pattern,
		shot_pattern,
		i_hanyou[8];
	bool	bDe,
		bBlend,
		bBomb,//ワシはボムで殺されたんじゃ
		bDamage,
		bNoDamage,
		bAtari,//当たり判定が存在するか
		bDelete;//一度でも画面内に入ったか？
};

extern list<ENEMYDATA> Enemy;

struct ESHOTDATA{
	float	x,
		y,
		speed,
		f_speed,
		large,
		angle,
		move_x,
		move_y,
		atari,
		kasuri,
		f_hanyou[8];
	int     flash,
		soten,
		life,
		late,
		img,
		f_count,
		count,
		pattern,
		i_hanyou[8];
	bool	bBlend,
		bDe,
		bMove,//敵弾消しの効果受けてる？
		bHyper,//一度でもハイパー効果受けたか？
		bGraze,
		bDeNow,//デリートなう
		bDelete;//一度でも画面内に入ったか？
};

extern list<ESHOTDATA> EShot;

struct ELASERDATA{
	float	x[2][6],//一次 0:実線 1:予告線　二次 0:左上 1:右上 2:右下 3:左下 4:根元中心 5:先端中心
		y[2][6],
		angle,
		speed,
		max_size,
		to_x,
		to_y,
		size[2],//0:実際 1:予告
		length[2],//0:実際 1:予告
		f_hanyou[8];
	int     flash,
		img,
		count,
		late,
		pattern,
		spe_count,
		i_hanyou[8];
	bool	bDraw,//予告線を描画するか？
		bDelete;
};

extern list<ELASERDATA> ELaser;

struct ESLASERDATA{
	float	base_x,//根元
		base_y,
		//↓直線レーザー専用
		edge_x[2],//根元と先端
		edge_y[2],
		//↑直線レーザー専用
		//↓へにょりレーザー専用
		x[LASER_ELEMENT_NUM],
		y[LASER_ELEMENT_NUM],
		//↑へにょりレーザー専用
		angle,
		speed,
		move_x,
		move_y,
		size,//太さ
		length[2],//直線専用。長さ。0:現在の長さ 1:最大の長さ
		f_hanyou[8];
	int     type,//0:直線レーザー 1:へにょりレーザー
		flash,
		img,
		count,
		pattern,
		i_hanyou[8];
	bool	bEff,
		bDelete;
};

extern list<ESLASERDATA> ESLaser;

extern float Lto_x;
extern float Lto_y;
extern int Lspe_count;
extern float ang_plus;
extern int Prank;

extern void EReset();
extern void EDraw();
extern void EMove(list<ENEMYDATA>::iterator &it);
extern void EShotS(list<ENEMYDATA>::iterator &it);
extern void EMake(float x,float y,int life,int img,int move_pattern,int shot_pattern);
extern void ESDraw();
extern void ESMove(list<ESHOTDATA>::iterator &it);
extern void ESMake(float x,float y,float angle,float speed,int img,bool blend=false,int pattern=0,int late=0,float f_speed=0,int f_count=0,bool eff=true,float hanyou=0);
extern void ESNWay(float x,float y,float tox,float toy,float angle,int num,float speed,int img,bool blend=false,int pattern=0,int late=0,float f_speed=0,int f_count=0,bool eff=true);
extern void ELDraw();
extern void ELMove(list<ELASERDATA>::iterator &it);
extern void ELMake(float x,float y,float size,float angle,float speed,int img,int pattern,int late);
extern void ESLDraw();
extern void ESL1Move(list<ESLASERDATA>::iterator &it);
extern void ESL2Move(list<ESLASERDATA>::iterator &it);
extern void ESL1Make(float x, float y, float size, float length, float angle, float speed, int img, int pattern=0);
extern void ESL2Make(float x, float y, float size, float angle, float speed,int img, int pattern);

#endif