#ifndef _EXTERN_H_
#define _EXTERN_H_

#include "bgm.h"

#define C_KEY_NUM 256
#define C_PAD_NUM 16
#define PAD_A 4
#define PAD_B 5
#define PAD_C 6
#define PAD_X 7
#define PAD_Y 8
#define PAD_Z 9
#define PAD_L 10
#define PAD_R 11
#define PAD_START 12
#define PAD_M 13
#define PAD_UP 3
#define PAD_DOWN 0
#define PAD_LEFT 1
#define PAD_RIGHT 2
#define X_ZAHYO_TO_NUM(a) (int)(((a)-16)/32)
#define X_NUM_TO_ZAHYO(a) (16+32*(a))
#define Y_ZAHYO_TO_NUM(a) (int)(((a)-64)/32)
#define Y_NUM_TO_ZAHYO(a) (64+32*(a))
#define CENTER_X 320.0
#define CENTER_Y 260.0
#define REPLAY_ELEMENT_NUM 100000
#define REPLAY_NUM 20

extern int c_key[C_KEY_NUM];
extern int c_pad[4][C_PAD_NUM];
extern int rand_seed;
extern int Gcount;//死亡カウント
extern int Rcount;
extern int Rcount2;
extern int Pcount;//ポーズカウント
extern float shake_x;
extern float shake_y;
extern bool bTimeStop;
extern bool bSecondSun;

extern bool replay_play;//リプレイ再生か？
extern int replay_play_num;//何番のリプレイ再生か？
extern int replay_count;//リプレイ保存要素
struct REPLAYDATA{
	int	element_num,
		player[4],//キャラクター
		rand_seed,
		year,
		month,
		day,
		hour[2],//始まりと終わり
		minute[2],
		second[2],
		match,//試合数
		matchnum,
		matchtime,
		stage,
		bgm;		
	bool	bMan[4],
		exist;
	unsigned char replay_element[REPLAY_ELEMENT_NUM][4];
};
extern REPLAYDATA Replay[REPLAY_NUM];
extern REPLAYDATA SReplay;
extern int repeat;
extern int repeat_max;

enum SCENE{
	GAME=0,TITLE,SELECT_REPLAY,OPTION,KEYCONFIG,SETTINGA,SETTINGB,SETTINGC,END
};
extern SCENE scene;

extern void SShake(int type, float level);
extern void SCheckPlayTime();
extern int SSave();
extern void SLoad();
extern void SSaveReset();
extern void CheckPushKey();
extern void Fps();
extern void SnapShot();
extern int get_rand(int max);
extern float Radian(float d, int flag);
extern void crypt(void* data,unsigned int size,unsigned char code);
extern void DrawSt(float x,float y,int color,int tocolor,int font,char message[256]);
extern int draw_string(float x,float y,int num,char *buffer);
extern void change_scene(SCENE change);
extern void GameLoad();

struct SAVEDATA{
	int	Key_Bomb[4],
		Key_Spell[4],
		Key_Pause[4],
		Key_Type[4],
		Bgm,
		Sound,
		MatchNum,
		MatchTime,
		PlayCount,
		PlayTime;
};

extern SAVEDATA SAVE;


#include "effect.h"

#endif