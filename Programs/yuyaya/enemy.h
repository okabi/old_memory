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
		bBomb,//���V�̓{���ŎE���ꂽ�񂶂�
		bDamage,
		bNoDamage,
		bAtari,//�����蔻�肪���݂��邩
		bDelete;//��x�ł���ʓ��ɓ��������H
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
		bMove,//�G�e�����̌��ʎ󂯂Ă�H
		bHyper,//��x�ł��n�C�p�[���ʎ󂯂����H
		bGraze,
		bDeNow,//�f���[�g�Ȃ�
		bDelete;//��x�ł���ʓ��ɓ��������H
};

extern list<ESHOTDATA> EShot;

struct ELASERDATA{
	float	x[2][6],//�ꎟ 0:���� 1:�\�����@�� 0:���� 1:�E�� 2:�E�� 3:���� 4:�������S 5:��[���S
		y[2][6],
		angle,
		speed,
		max_size,
		to_x,
		to_y,
		size[2],//0:���� 1:�\��
		length[2],//0:���� 1:�\��
		f_hanyou[8];
	int     flash,
		img,
		count,
		late,
		pattern,
		spe_count,
		i_hanyou[8];
	bool	bDraw,//�\������`�悷�邩�H
		bDelete;
};

extern list<ELASERDATA> ELaser;

struct ESLASERDATA{
	float	base_x,//����
		base_y,
		//���������[�U�[��p
		edge_x[2],//�����Ɛ�[
		edge_y[2],
		//���������[�U�[��p
		//���ւɂ�背�[�U�[��p
		x[LASER_ELEMENT_NUM],
		y[LASER_ELEMENT_NUM],
		//���ւɂ�背�[�U�[��p
		angle,
		speed,
		move_x,
		move_y,
		size,//����
		length[2],//������p�B�����B0:���݂̒��� 1:�ő�̒���
		f_hanyou[8];
	int     type,//0:�������[�U�[ 1:�ւɂ�背�[�U�[
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