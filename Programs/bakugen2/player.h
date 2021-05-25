#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "extern.h"
#include "para.h"
#include "graph.h"
#include "map.h"

#define ILLUSION_NUM 20

struct ZAHYODATA{
	int	x,
		y,
		direction,//�ŏ��̈ړ������B-1:�s�� 0:�� 1:�� 2:�� 3:�E
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
		ai_x,
		ai_y;
	int	up,
		down,
		left,
		right,
		bomb,
		spell,
		condition,//-1:�����������Ȃ� 0:���� 1:���S���� 2:�݂� 3:�݂����A���� 4:���S
		bomb_max,
		power,
		gage,
		gage_max,
		gage_count,
		spell_count,
		death_count,
		reborn_count,
		muteki_count,
		AI_count,
		hit,
		hit_count,
		img_count,
		img[PLAYER_CHIP_NUM],
		img_num,
		control_num,
		i_hanyou[8];
public:
	float	reborn[4];
	float	large,
		d_hanyou[8];
	char	spell_name[3][64],
		special[64];//�A�C�e���u�X�y���J�[�h�v�擾��
	int	level,
		gage_per,
		flash,
		dokuro_count,
		dokuro_death_count,
		illusion_flash,//�D�܉�
		spell_level,
		draw_level,
		bomb_num,//��ʏ�ɏo�Ă���{����
		chara,
		color,
		victory;
	unsigned int	dokuro;
	bool	bAtariPlayer[4],//�v���C���[�Ƃ̓����蔻��
		bIllusion,
		bSpbomb,
		bKickbomb,
		bMove,
		bMan,
		bFirstDeath,
		bTime,//���X�y�J�p
		bCamo,//�I�v�e�B�J���J���t���[�W��
		bBouga,//�S�䋽
		bSumizome,//�n���̍�
		bRudo;//���h�r���p
	int	AI_value[LARGE_X][LARGE_Y],
		AI_bomb[LARGE_X][LARGE_Y],//1:���v�����ǔ����͗���
		AI_map[LARGE_X][LARGE_Y];
	CLASS_PLAYER();
	int player_num;
	void control();
	void miso_control();
	void hangon_control();
	void replay_control();
	void draw();
	void gage_plus(int);
	void atari_map(int bomb,int spell,int up,int down,int left,int right);
	void set_xy(float,float);
	void get_xy(float*,float*);
	void get_key(int*,int*);
	int get_condition();
	void change_condition(int,int=1);
	int get_bomb();
	int get_hit();
	int get_spell_count();
	void set_spell_count(int);
	int get_muteki_count();
	void set_muteki_count(int);
	int get_direction();
	int get_chara();
	int get_power();
	float get_speed();
	void add_speed(float);
	void power_plus(int=1);
	void bomb_max_plus(int=1);
	void gage_count_plus(int);
	void hit_plus(int=1);
	void hit_reset();
	void level_plus(int=1);
	void death_function();
	void reborn_function();
	void make(float,float,int,int,bool,int pnum=-1);
	void AI_Record(vector<ZAHYODATA> &it,int c_num=2);
	void AI(int*,int*,int*,int*,int*,int*);
	/*
	void AI(int*,int*,int*,int*,int*,int*);
	void AIFunction(int[LARGE_X][LARGE_Y]);
	int AI_Function2(int,int,int[LARGE_X][LARGE_Y]);
	*/
	void AI_Last(int*,int*,int*,int*,int*,int*);
	void AI_Miso(int*,int*,int*,int*,int*,int*);
	int Search(int,int);
	void replay_main();
};

extern CLASS_PLAYER Player[PLAYER_NUM];
extern CLASS_PLAYER Illusion[ILLUSION_NUM];

extern void PLoad();
extern void PMain();


#endif