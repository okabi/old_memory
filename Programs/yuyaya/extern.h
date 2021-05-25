#ifndef _EXTERN_H_
#define _EXTERN_H_

#include "bgm.h"
#include "graph.h"
#include "system.h"
#include "boss.h"

#define VERSION 141
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
#define CENTER_X 220.0
#define CENTER_Y 240.0
#define REPLAY_ELEMENT_NUM 300000
#define REPLAY_NUM 20
#define DEMO_NUM 3
#define DEMO_TIME 900
#define LEVEL_NUM 7
#define CHARA_NUM 6
#define SCORE_NUM 10
#define STAGE_SCORE_NUM 6
#define STAGE_NUM 5
#define USER_NAME_NUM 8

extern int Eup;
extern int Edown;
extern int Eleft;
extern int Eright;
extern int Eshot;
extern int Ebomb;
extern int Eslow;
extern int Eskip;
extern int Epause;
extern int Sloop;
extern int LOOP;

extern bool bShake;


extern ATACKDATA atack[ATACK_NUMA][ATACK_NUMB];

extern int c_key[C_KEY_NUM];
extern int c_pad[C_PAD_NUM];
extern int rand_seed;
extern float shake_x;
extern float shake_y;
extern int SoundFlag[SOUND_NUM];
extern char nowloading[32];

extern bool replay_play;//���v���C�Đ����H
extern int replay_play_num;//���Ԃ̃��v���C�Đ����H
extern int replay_count;//���v���C�ۑ��v�f
struct REPLAYDATA{
	int	version;
	unsigned int score[STAGE_NUM][2];
	int	start_count[STAGE_NUM],
		rand_seed[STAGE_NUM],
		stage,
		level,
		chara,//new
		con_num,
		rank,
		year,
		month,
		date,
		slowrate,
		ship[STAGE_NUM],
		bomb[STAGE_NUM],
		first_bomb[STAGE_NUM],
		spcard[STAGE_NUM],//�A���X�y�J�Q�b�g�� new
		stress_gage[STAGE_NUM],//new
		hyper_rank[STAGE_NUM],//new
		hyper_gage[STAGE_NUM],
		hyper_count[STAGE_NUM];
	char name[USER_NAME_NUM+1];
	int	element_num;
	bool	exist,
		s_exist[STAGE_NUM];
	unsigned char replay_element[REPLAY_ELEMENT_NUM];
	int replay_count[REPLAY_ELEMENT_NUM];
};
extern REPLAYDATA Demo[DEMO_NUM];
extern REPLAYDATA Replay[REPLAY_NUM];
extern REPLAYDATA SReplay;
extern unsigned char before_key;//���O�̃L�[����
extern int Kcount;//���̃L�[���͂������Ă�t���[����


extern int default_font;
extern int talk_font;
extern int spell_font;
extern int tuto_font;

enum SCENE{
	GAME=0,TITLE,REPLAY,RESULT,OPTION,SELECT_LEVEL,SELECT_PLAYER,NAMEENTRY,END
};
extern SCENE scene;

enum LEVEL{
	EASY=0,NORMAL,HARD,LUNATIC,BABY,IMPOSSIBLE,EXTRA,LASTWORD
};

extern void WriteLog(char log[]);
extern bool GetSkip();
extern void GetInput(int *up, int *down, int *left, int *right, int *shot, int *bomb, int *slow, int *skip, int *pause, bool flag=false);
extern void PlaySound(int i);
extern void SoundEffect();
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
extern int get_length(int num,char *buffer);
extern int draw_score(float x,float y,unsigned int num,int limit,bool zero);
extern int draw_hit(float x,float y,int num,int img);
extern int draw_spell(float x,float y,int num);

struct SCOREDATA{
	unsigned int	score[2],
			stage_allscore[STAGE_NUM][2],
			stage_score[STAGE_NUM][STAGE_SCORE_NUM][2];
	int	start_stage,
		end_stage,//STAGE_NUM+1�ŃI�[���N���A�ASTAGE_NUM+2�Ő^�{�X�N���A�ASTAGE_NUM+3�ŗ��{�X�N���A
		gameper,
		slowrate,
		con_num,
		miss_num,
		bomb_num,
		hyper_num,
		spell_num,
		rank[STAGE_NUM+1],
		year[2],
		month[2],
		date[2],
		hour[2],
		minute[2],
		second[2],
		root[STAGE_NUM+1],//�\���[�g�A�����[�g			
		Rplaytime[STAGE_NUM+1],			
		Vplaytime[STAGE_NUM+1],
		enemyshot_num[STAGE_NUM+1],			
		enemy_num[STAGE_NUM+1],			
		item_num[3][STAGE_NUM+1],//new
		max_soten[STAGE_NUM+1],
		max_hit[STAGE_NUM+1],
		score_spcard[SPELL_NUM],
		first_ship,
		first_bomb;
	char	name[USER_NAME_NUM+1];
};

struct SAVEDATA{
	int	Version;
	char	LastName[USER_NAME_NUM+1];
	int	Key_Shot,
		Key_Bomb,
		Key_Slow,
		Key_Skip,
		Key_Pause,
		Bgm,
		Sound,
		Ship,
		Bomb,
		Level,
		Chara,
		Stage,//�ǂ��܂ŃN���A�������H
		PlayCount[LEVEL_NUM],
		PlayTime[LEVEL_NUM+1],
		SpGet[CHARA_NUM][SPELL_NUM],
		SpChallenge[CHARA_NUM][SPELL_NUM];
	bool	Extra,
		Practice,
		Baby,
		Impossible;
	SCOREDATA Score[LEVEL_NUM][CHARA_NUM][SCORE_NUM];
};

extern SAVEDATA SAVE;
extern SCOREDATA SScore;//���v���C�L�^�p
extern int STCount;//�X�^�[�g���̃E�B���h�E�Y�N������̃J�E���g
extern int NOCount;//�O��^�C�}�[���~�߂��n�_�̃E�B���h�E�Y�N������̃J�E���g
extern int CKCount;//�~�σJ�E���g
extern int STCOUNT[STAGE_NUM][2];//0:�X�e�[�W�̑S�H���J�E���g�� 1:�{�X��̑���̃��C�t���i�S�U�����j
extern int BOSSERASENUM;//�{�X��|������
extern int i_hanyou[8];

#endif