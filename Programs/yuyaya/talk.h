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
	int	talk_num,//��b����
		flag[MAX_TALK],
		Pimg[MAX_TALK][MAX_PLAYER],
		Eimg[MAX_TALK][MAX_ENEMY],
		Pimg_count[MAX_PLAYER],
		Eimg_count[MAX_ENEMY],
		Pactive[MAX_TALK][MAX_PLAYER],
		Eactive[MAX_TALK][MAX_ENEMY],
		Pactive_count[MAX_PLAYER],
		Eactive_count[MAX_ENEMY],
		Nimg,//�{�X�l�[��
		Ncount,
		speak_color[MAX_TALK][MAX_LINE];
	char	speak[MAX_TALK][MAX_LINE][MAX_CHAR];
	bool	bName[MAX_TALK];//�{�X�l�[�����o��	
};

extern TALKDATA Talk[CHARA_NUM][TALK_NUM];

extern bool bTalk;//�g�[�N���H
extern int TalkNum;//��b�ԍ�
extern int NowNum;//��b�ԍ�
extern int TalkCount;//�僂�g�̃J�E���g
extern int TalkCount2;//�e��b���Ƃ̃J�E���g
extern int TalkCount3;//�Ō�ɂЂ����ރJ�E���g

extern void TLoad();
extern void TReset();
extern void TDraw();
extern void TMove(int chara, int i);
extern void TMake(int num);

#endif