#ifndef __EXTERN_H__
#define __EXTERN_H__

#include "DxLib.h"
#include <math.h>
#include <list.h>
#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
#define PI 3.1415926535897932384626433832795
#define CENTER_X 211
#define CENTER_Y 236.5
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


//######  �O���[�o���ϐ�  ######
int edge;//�e�̋���
int edge_flash;//�e�̖��邳
int start_rand;//�V���[�e�B���O�X�^�[�g���̃����_����l
float fps;
float frame;
//##############################

//######  �O���[�o���֐�  ######
void starts();
float Radian(float,int);
int get_rand(int);
void DrawStringEdge(float,float,int,int,char*,int=255,int=0);
void crypt(void* data,unsigned int size,unsigned char code);

void starts(){//�N�����̃t���X�N���[�����[�h�ύX
        int flag;
        flag=MessageBox(
                NULL ,
                TEXT("�t���X�N���[�����[�h�ŋN�����܂����H\n\n�������u�͂��v") ,
                TEXT("�����剝��") , 
                MB_YESNO | MB_ICONQUESTION );
        if(flag==IDNO)
                ChangeWindowMode( TRUE );
}

inline int get_rand(int max){
//0~max�܂ł̗������擾
	start_rand ++;
	SRand(start_rand);
	int rand = GetRand(max);
	return rand;
}

inline float Radian(float d, int flag){
//TRUE:�x�����W�A���ϊ��AFALSE:���W�A�����x�ϊ�
	float degree;
	if(flag==TRUE) degree = d / 180 * PI;
	else degree = d * 180 / PI;
	
	return degree;		
}

inline void DrawStringEdge(float x,float y,int color,int font,char *message, int flash, int color2){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,edge_flash);
	DrawStringToHandle(x+edge,y+edge,message,0,font);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
	DrawStringToHandle(x,y,message,color,font,color2);
	return;
}

void crypt(void* data,unsigned int size,unsigned char code){
	unsigned char* ch = (unsigned char*)data;
	unsigned char* ch_end = ch + size;
	int count = 1;
	while(ch<ch_end){
		*ch ^= code*count;
		ch++;
		count++;
	}
	return;
}

#endif