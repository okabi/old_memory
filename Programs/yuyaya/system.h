#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "extern.h"

#define PLAYER_NUM 1
#define OPTION_NUM 8
#define MAX_GAGE 100000
#define MAX_HIT_GAGE 420
#define MAX_STRESS_GAGE 10000
#define MAJIGIRE 6000

enum NPART{
	EARLY=0,MIDBOSS,LATER,BOSS,MIDBOSS2,MIDDLE
};

extern bool bRG;//マジギレ補正をかけるか？
extern bool bES;//ハイパーゲージ速度補正をかけるか？
extern int Scount;
extern int Scount_all;//全体を通したステージカウント
extern int Pcount;//ポーズカウント
extern int Pcarsol[2];
extern int Pscene;
extern int Pcount2;
extern int Pcount3;
extern int PNowcount;
extern int Ccount;//ステージクリア時
extern int Ccount2;//オールクリア時
extern int Ccount3;
extern int Ecount;
extern float BackX;
extern float BackY;
extern float BackZ;
extern int GageCount;
extern int FunctionCount;
extern int SpellCount;//スペカ発動してからのカウント
extern NPART NowPart;//ステージのどの部分？
extern int MissN;
extern int BombN;

struct PLAYERDATA{
	unsigned int	hiscore[2],
			score[2],//みかけのスコアの1/10。0:1億~999億　1:0~1000万
			score2[2],//スコアドラム
			before_score[2];
	float	x,
		y,
		speed,
		large,
		angle,
		atari;
	int	first_ship,
		first_bomb,
		total_hit,//各ステージ
		stage,
		level,
		chara,//new
		flash,
		plus_hit,
		plus_hit_count,
		miss_count,
		death_count,
		muteki_count,
		slow_count,
		img_num,
		hi_cont_num,
		cont_num,//continue_num
		count,
		up,
		down,
		left,
		right,
		shot,
		bomb,
		slow,
		skip,
		ship_num,
		bomb_num,
		soten,
		soten2,
		hit,
		hit2,
		hit2_count,
		laser_count,
		aura_count,
		rate_soten,
		kill_num,
		item_num[3],//new
		spcard,//new
		stress_gage,//0~10000 new
		stress_count,//new
		hyper_rank,
		hyper_gage,//0~10000
		hit_gage,//0~MAX_HIT_GAGE
		hyper_count,
		hyper_count2,//ハイパーランク表示用
		graze_count;//new
};

struct OPTIONDATA{
	float	x,
		y,
		large,
		angle,
		ro,
		ro_angle;
	int	flash,
		count;
};

struct BACKDATA{
	float	x,
		y,
		z,
		speed,
		move_x,
		move_y,
		move_z,
		large,
		angle,
		f_hanyou[8];
	int	img,
		flash,
		count,
		red,
		green,
		blue,
		pattern,
		i_hanyou[8];
	bool	bBlend,
		bDelete;
};

extern PLAYERDATA Player[PLAYER_NUM];
extern OPTIONDATA Option[OPTION_NUM];
extern list<BACKDATA> BEffect;

extern void RSave(int num, bool save);
extern void RLoad();
extern void RMain(int *up=NULL, int *down=NULL, int *left=NULL, int *right=NULL, int *shot=NULL, int *bomb=NULL, int *slow=NULL, int *skip=NULL, int *pause=NULL, bool flag=false);
extern void PLoad();
extern void PReset();
extern void GetData();
extern void GetData2();
extern void Smain();
extern void add_score(unsigned int add);
extern void add_gage(int add);
extern void add_stress_gage(int add);
extern void add_soten(int add);
extern void PDraw();
extern void PMove(int i);
extern void ODraw();
extern void OMove(int i);
extern void SBack();
extern void SBEfDraw();
extern void SBEfMove(list<BACKDATA>::iterator &it);
extern void SBEfMake(float x,float y,float z,int pattern);
extern void SESDelete(int flag,float x=0,float y=0);
extern void SAtari();
extern void DrawGage();
extern int Loo(int rank0, int rank10);
extern int Per(int rank0, int rank10);

#endif