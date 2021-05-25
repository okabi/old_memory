#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "extern.h"

#define PLAYER_NUM 4
#define PLAYER_GRAPH_NUM 12
#define PLAYER_COLOR_NUM 4
#define PLAYER_CHIP_NUM 12
enum{
	REIMU=0,MARISA,SAKUYA,REMILIA,FRANDRE,YOUMU,YUYUKO,YUKARI,REISEN,NITORI,SANAE,UTUHO
};
#define ITEM_GRAPH_NUM 12
#define FACE_GRAPH_NUM 12
#define NUMBER_GRAPH_NUM 10
#define BACK_GRAPH_NUM 1
#define MAP_GRAPH_NUM 6
#define BOMB_GRAPH_NUM 3
#define SHOT_GRAPH_NUMA 3
#define SHOT_GRAPH_NUMB 8
#define SPELL_GRAPH_NUM 4
#define EFFECT_GRAPH_NUM 8
#define ASCII_NUM 45
#define MENU_GRAPH_NUM 7

extern int gPlayer[PLAYER_GRAPH_NUM][PLAYER_COLOR_NUM][PLAYER_CHIP_NUM];
extern int gItem[ITEM_GRAPH_NUM];
extern int gFace[FACE_GRAPH_NUM];
extern int gNumber[NUMBER_GRAPH_NUM];
extern int gBack[BACK_GRAPH_NUM];
extern int gMap[MAP_GRAPH_NUM][3];
extern int gBomb[BOMB_GRAPH_NUM][PLAYER_NUM];
extern int gShot[SHOT_GRAPH_NUMA][SHOT_GRAPH_NUMB];
extern int gSpell[SPELL_GRAPH_NUM];
extern int gEffect[EFFECT_GRAPH_NUM];
extern int gExplosion;
extern int gEnemy;
extern int gAscii[ASCII_NUM];
extern int gMenuBack;
extern int gMenu[MENU_GRAPH_NUM];
extern int gSnap;//スナップショット

extern int font_default;
extern int font_time;

extern int GLoad();


#endif