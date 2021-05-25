#ifndef _BOSS_H_
#define _BOSS_H_

#include "extern.h"

#define ATARI_NUM 8
#define ATACK_NUMA 16
#define ATACK_NUMB 8
#define SPELL_NUM 56
#define NAME_NUM 64
#define BACK_JIMG_NUM 2
#define BACK_PIMG_NUM 4
#define CATIN_IMG_NUM 4

extern int BGcount;//BossGage
extern int BGcount2;
extern int BGcount3;
extern int BossCount;//ボス戦カウントダウン
extern int SpBackCount;
extern int SpNum;//現在発動中
extern int NmBonus;
extern int SpBonus;
extern int SpBonusRate;
extern int GetSpBonus;
extern int GetSpBonusCount;
extern bool bSun;//コア・オブ・ザ・セカンドサン

struct ATARIDATA{
	float	x,//中心からの距離
		y,
		large;
};

struct ATACKDATA{
	int	life,
		defence,
		pattern,
		red,
		green,
		blue,
		count;
	bool	bSpell;//スペルカードなの？
};

struct BOSSDATA{
	float	x,
		y,
		to_x,
		to_y,
		large,
		angle,
		mrate_x,
		mrate_y,
		f_hanyou[8];
	ATARIDATA	atari[ATARI_NUM];
	ATACKDATA	atack[ATACK_NUMA][ATACK_NUMB];
	int     flash,
		atari_num,
		ship,
		now_numA,
		now_numB,
		life,
		max_life,
		defence,//ゲージの見た目の減りが緩やかになるだけ。ゲージが何分の一になるか
		soten,
		img,
		img_count,
		count,
		muteki_count,
		death_count,
		move_count,
		pattern,
		i_hanyou[8];
	bool	bDelete,//一度でも画面内に入った？
		bDeath,
		bSpell,
		bDamage,
		bBlend,
		bMuteki,
		bAtari;//当たり判定が存在するか
};

extern list<BOSSDATA> Boss;

struct SPELLDATA{
	int	level,
		bonus,
		back_Jimg[BACK_JIMG_NUM],
		back_Pimg[BACK_PIMG_NUM],
		back_type,	
		catin_img[CATIN_IMG_NUM],
		catin_type;	
	char	name[NAME_NUM];
};

extern SPELLDATA Spell[SPELL_NUM];

extern void BReset();
extern void SpBackDraw();
extern void SpDraw();
extern void BDraw();
extern void BMove(list<BOSSDATA>::iterator &it);
extern void BTalkMove(list<BOSSDATA>::iterator &it);
extern void BToMove(list<BOSSDATA>::iterator &it,float tox,float toy,int time);
extern void BMake(float x,float y,int img,int ship,ATACKDATA Patack[ATACK_NUMA][ATACK_NUMB]);
extern void BDrawGage();
extern void SpLoad();

#endif