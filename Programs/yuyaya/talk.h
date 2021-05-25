#ifndef _TALK_H_
#define _TALK_H_

#include "extern.h"

#define TALK_NUM 6
#define MAX_PLAYER 2
#define MAX_ENEMY 2
#define MAX_TALK 50
#define MAX_CHAR 64
#define MAX_LINE 2

struct TALKDATA{
	int	talk_num,//会話枚数
		flag[MAX_TALK],
		Pimg[MAX_TALK][MAX_PLAYER],
		Eimg[MAX_TALK][MAX_ENEMY],
		Pimg_count[MAX_PLAYER],
		Eimg_count[MAX_ENEMY],
		Pactive[MAX_TALK][MAX_PLAYER],
		Eactive[MAX_TALK][MAX_ENEMY],
		Pactive_count[MAX_PLAYER],
		Eactive_count[MAX_ENEMY],
		Nimg,//ボスネーム
		Ncount,
		speak_color[MAX_TALK][MAX_LINE];
	char	speak[MAX_TALK][MAX_LINE][MAX_CHAR];
	bool	bName[MAX_TALK];//ボスネームを出す	
};

extern TALKDATA Talk[CHARA_NUM][TALK_NUM];

extern bool bTalk;//トーク中？
extern int TalkNum;//会話番号
extern int NowNum;//会話番号
extern int TalkCount;//大モトのカウント
extern int TalkCount2;//各会話ごとのカウント
extern int TalkCount3;//最後にひっこむカウント

extern void TLoad();
extern void TReset();
extern void TDraw();
extern void TMove(int chara, int i);
extern void TMake(int num);

#endif