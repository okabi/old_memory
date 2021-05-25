#ifndef _MENU_H_
#define _MENU_H_

#include "extern.h"

#define MEF_NUM 100
#define YUYAYA_NUM 50
#define TITLE_NUM 7
#define OP_NUM 13
#define SL_NUM 4
#define SLP_NUM 6

extern bool bDemo;
extern int DemoNum;
extern int commandA;
extern int commandB;
extern int Mcount;
extern int Mcount2;
extern int Mcount3;
extern int title_carsol;
extern int op_count;
extern int op_carsol;
extern int sl_count;
extern int sl_count2;
extern int sl_count3;
extern int slp_count;
extern int slp_count2;
extern int slp_count3;
extern int sl_stage;
extern int rp_count;
extern int rp_count2;
extern int rp_count3;
extern int rp_scene;
extern int rp_carsol;
extern int rp_carsol2;
extern int rs_count;
extern int rs_count2;
extern int rs_count3;
extern int rs_level;
extern int rs_chara;
extern int rs_scene;
extern int rs_carsol;
extern int ne_count;
extern int ne_count2;
extern int ne_count3;
extern int ne_count4;
extern int ne_carsol;
extern int ne_carsol2;
extern int ne_scene;
extern int now_tate;
extern int now_yoko;
extern int now_num;//ì¸óÕÇ≥ÇÍÇƒÇ¢ÇÈï∂éöóÒî‘çÜ
struct LOGODATA{
	float	x,
		y,
		angle,
		speed,
		accel,
		move_x,
		move_y;
};
extern LOGODATA Logo[LOGO_GRAPH_NUM];

struct MEFDATA{
	float	x,
		y,
		speed,
		large,
		move_x,
		move_y;
	int	count,
		red,
		green,
		blue;
};
extern MEFDATA MEf[MEF_NUM];

struct MENUDATA{
	float	x,
		y,
		speed,
		accel;
	int	count;
};
extern MENUDATA Menu[TITLE_NUM];

struct YUYAYADATA{
	float	x,
		y,
		move_x,
		move_y,
		accel;
};
extern YUYAYADATA Yuyaya[YUYAYA_NUM];


extern void MeLoad();
extern void MeMain();
extern void MeBack();
extern void MeTitle();
extern void MeReplay();
extern void MeDrawReplay(float y, float plus, int entry, int only=-1);
extern void MeResult();
extern void MeOption();
extern void MeSelectLevel();
extern void MeSelectPlayer();
extern void MeNameEntry();
extern void MeDrawRanking(float y,int level, int chara, float plus,int entry=-1);
extern bool MeInputName(float y, float plus, char buffer[USER_NAME_NUM], bool bInput);


#endif