#ifndef _EXTERN_H_
#define _EXTERN_H_

#include "bgm.h"

#define DUMMY 0
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
#define PROFILE_NUM 50
#define MAX_NAME 41
#define MAX_LOG 128

extern bool bOnline;
extern char LOG[MAX_LOG];
extern int c_key[C_KEY_NUM];
extern int c_pad[4][C_PAD_NUM];
extern int rand_seed;
extern int Gcount;//���S�J�E���g
extern int Rcount;
extern int Rcount2;
extern int Pcount;//�|�[�Y�J�E���g
extern float shake_x;
extern float shake_y;
extern int HangonType;//�������v���C���[
extern int HangonLife;
extern int TimeStopType;//0:���b�p�[ 1:���h�r�� 2:�E�l
extern bool bTimeStop;
extern bool bSecondSun;
extern bool bIceStream;
extern bool bTreasure;
extern int TreasureCount;
extern bool bYukari;//���X�y�J
extern bool bAICheck;
extern int Hanten;//���X�y�J
extern int MapFlash;//�D�܉؃X�y�J

extern bool replay_play;//���v���C�Đ����H
extern int replay_play_num;//���Ԃ̃��v���C�Đ����H
extern int replay_count;//���v���C�ۑ��v�f
struct REPLAYDATA{
	int	element_num,
		player[4],//�L�����N�^�[
		player_color[4],//�V�K
		start_count[100],//�V�K
		winner[100],//�V�K
		last_winner,//�V�K
		rand_seed,
		year,
		month,
		day,
		hour[2],//�n�܂�ƏI���
		minute[2],
		second[2],
		match,//������
		matchnum,
		matchtime,
		stage,
		bgm[2];		
	bool	bMan[4],
		exist;
	char	name[4][MAX_NAME];//�V�K
	unsigned char replay_element[REPLAY_ELEMENT_NUM][4];
};
extern REPLAYDATA Replay[REPLAY_NUM];
extern REPLAYDATA SReplay;
extern int repeat;
extern int repeat_max;

enum SCENE{
	GAME=0,TITLE,SELECT_REPLAY,RESULT,RESULT2,OPTION,KEYCONFIG,SETTINGA,SETTINGB,SETTINGC,NETSETTINGA,NETSETTINGB,END
};
extern SCENE scene;

extern void WriteLog(char log[]);
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
extern float Atan2(float y, float x);
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
		User[4],
		Bgm,
		Sound,
		MatchNum,
		MatchTime,
		PlayCount,
		PlayTime;
};

extern SAVEDATA SAVE;

struct PROFILEDATA{
	int	ID,
		rate,
		max_rate,
		match_num,
		win_num,
		lose_num[3],
		playtime,
		death_average,
		first_death_num,
		sadon_match_num,
		sadon_num,
		kill_num,
		miso_kill_num,
		killme_num,
		death_num,
		danmaku_num,
		max_renbaku,
		chara_num[12],
		player_match_num[PROFILE_NUM],
		player_win_num[PROFILE_NUM],
		player_lose_num[PROFILE_NUM],
		player_ID[PROFILE_NUM],
		player_name[PROFILE_NUM][MAX_NAME];
	char	name[MAX_NAME];
	bool	exist;
};

extern PROFILEDATA Profile[PROFILE_NUM];


#include "effect.h"

#endif