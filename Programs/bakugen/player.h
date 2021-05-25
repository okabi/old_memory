#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "extern.h"
#include "para.h"
#include "graph.h"

struct ZAHYODATA{
	int	x,
		y,
		direction,//最初の移動方向。-1:不動 0:上 1:下 2:左 3:右
		priority,
		num;
	bool	bBomb;
};

class CLASS_PLAYER{
friend class CLASS_PARA;
private:
	float	x,
		y,
		bx,
		by,
		atari_x[2],
		atari_y[2],
		speed,
		large;
	int	up,
		down,
		left,
		right,
		bomb,
		spell,
		condition,//-1:そもそもいない 0:生存 1:死亡処理 2:みそ 3:みそ復帰処理 4:死亡
		bomb_max,
		power,
		gage,
		gage_max,
		gage_per,
		gage_count,
		spell_count,
		death_count,
		reborn_count,
		muteki_count,
		hit,
		hit_count,
		flash,
		img_count,
		img[PLAYER_CHIP_NUM],
		img_num,
		control_num,
		i_hanyou[8];
public:
	float	d_hanyou[8];
	char	spell_name[64];
	int	level,
		bomb_num,//画面上に出ているボム数
		chara,
		victory;
	bool	bSpbomb,
		bKickbomb,
		bMove,
		bMan;
	CLASS_PLAYER();
	int player_num;
	void control();
	void miso_control();
	void replay_control();
	void draw();
	void gage_plus(int);
	void atari_map(int bomb,int spell,int up,int down,int left,int right);
	void get_xy(float*,float*);
	int get_condition();
	void change_condition(int);
	int get_hit();
	int get_spell_count();
	int get_muteki_count();
	int get_direction();
	int get_chara();
	int get_power();
	void power_plus(int=1);
	void bomb_max_plus(int=1);
	void gage_count_plus(int);
	void hit_plus(int=1);
	void death_function();
	void reborn_function();
	void make(float,float,int,bool);
	void AI_Record(vector<ZAHYODATA> &it,int c_num=2);
	void AI(int*,int*,int*,int*,int*,int*);
	void AI_Last(int*,int*,int*,int*,int*,int*);
	void AI_Miso(int*,int*,int*,int*,int*,int*);
	int Search(int,int);
	void replay_main();
};

extern CLASS_PLAYER Player[PLAYER_NUM];

extern void PLoad();
extern void PMain();


#endif