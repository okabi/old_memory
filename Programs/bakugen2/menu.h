#ifndef _MENU_H_
#define _MENU_H_

#include "extern.h"
#include "graph.h"

extern list<EFFECTDATA> MeEffect;

extern int menu_count;
extern int title_carsol;
extern int select_re_count;
extern int select_re_count2;
extern int result_count;
extern int result_carsol;
extern int result2_count;
extern int result2_carsol;
extern int option_count;
extern int option_carsol;
extern int netsettingA_count;
extern int netsettingA_carsol[2];
extern int netsettingB_count;
extern int netsettingB_seleca;
extern int netsettingB_carsol[9];
extern int settingA_count;
extern int settingA_carsol;
extern int settingB_count;
extern int settingB_carsol[4];
extern bool settingB_flag[4];
extern int settingC_count;
extern int settingC_count2;
extern int settingC_carsol[3];

extern void MeLoad();
extern void MeMain();
extern void MeBackDraw();
extern void MeMenuDraw();
extern void MeMenuSelect();
extern void MeSelect_Replay();
extern void MeResult();
extern void MeResult2();
extern void MeOption();
extern void KeyToChar(int key,char *buffer);
extern void MeNetSettingA();
extern void MeNetSettingB();
extern void MeSettingA();
extern void MeSettingB();
extern void MeSettingC();
extern void MeEfMake(float x,float y,int img,int pattern);
extern void MeEfDraw();
extern void MeEfMove(list<EFFECTDATA>::iterator &it);


#endif