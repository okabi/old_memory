#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "extern.h"
enum eTYPE{
	SMALL=0, MEDIUM, MEDIUM2, BIG, NEEDLE, RICE, ICE, ZAYAKU, OVAL, KUNAI, UROKO, FUDA, MONEY, BFLY, SSTAR, STAR, KATANA, KNIFE, VERYBIG
};
enum eCOLOR{
	RED=0, ORANGE, YELLOW, GREEN, WATER, BLUE, PURPLE, GRAY
};
enum eCOLOR2{//verybig専用
	BRED=0, BPURPLE, BORANGE, BGREEN, BYELLOW, BWATER, BBLUE, BGRAY
};
#define FRED -1
#define FBLUE -2

#define ESHOT(type,color) (8*(type)+(color))
#define ASCII_NUM 45
#define MENU_GRAPH_NUM 9
#define TITLE_GRAPH_NUM 5
#define LEVEL_GRAPH_NUM 36
#define LOGO_GRAPH_NUM 19
#define SYSTEM_GRAPH_NUM 21
#define HIT_GRAPH_NUM 11
#define HIT2_GRAPH_NUM 11
#define SCORE_GRAPH_NUM 13
#define PLAYER_GRAPH_NUM 22
#define PCHARA_NUM 6
#define PSHOT_GRAPH_NUM 8
#define EFFECT_GRAPH_NUM 19
#define EFFECT2_GRAPH_NUM 3
#define ENEMY_GRAPH_NUM 25
#define PAUSE_GRAPH_NUM 30
#define BACK_GRAPH_NUM 6
#define BACK2_GRAPH_NUM 18
#define BOSS_GRAPH_NUM 6
#define BOSSNAME_GRAPH_NUM 9
#define ESHOT_GRAPH_NUM 19*8
#define ESHOT2_GRAPH_NUM 2*6
#define ITEM_GRAPH_NUM 6
#define CATIN_GRAPH_NUM 39
#define SPELL_GRAPH_NUM 10
#define MODEL_GRAPH_NUM 1
#define LASER_GRAPH_NUM 8
#define LASER_ELEMENT_NUM 32


extern int gAscii[ASCII_NUM];
extern int gMenuBack;
extern int gMenuBack2;
extern int gMenu[MENU_GRAPH_NUM];
extern int gTitle[TITLE_GRAPH_NUM];
extern int gLevel[LEVEL_GRAPH_NUM];
extern int gLogo[LOGO_GRAPH_NUM];
extern int gSystem[SYSTEM_GRAPH_NUM];
extern int gPlayer[PLAYER_GRAPH_NUM];
extern int gHit[HIT_GRAPH_NUM];
extern int gHit2[HIT2_GRAPH_NUM];
extern int gScore[SCORE_GRAPH_NUM];
extern int gPShot[PCHARA_NUM][PSHOT_GRAPH_NUM];
extern int gEffect[EFFECT_GRAPH_NUM];
extern int gEffect2[EFFECT2_GRAPH_NUM];
extern int gEnemy[ENEMY_GRAPH_NUM];
extern int gPauseG[PAUSE_GRAPH_NUM];
extern int gBack[BACK_GRAPH_NUM];
extern int gBack2[BACK2_GRAPH_NUM];
extern int gBoss[BOSS_GRAPH_NUM];
extern int gBossName[BOSSNAME_GRAPH_NUM];
extern int gEShot[ESHOT_GRAPH_NUM];
extern int gEShot2[ESHOT2_GRAPH_NUM];
extern int gItem[ITEM_GRAPH_NUM];
extern int gCatin[CATIN_GRAPH_NUM];
extern int gSpell[SPELL_GRAPH_NUM];
extern int gModel[MODEL_GRAPH_NUM];
extern int gLaser[LASER_GRAPH_NUM][LASER_ELEMENT_NUM];
extern int gGage;
extern int gSnap;//スナップショット
extern int gPause;//ポーズ
extern int gPause2;//ポーズ

extern int GLoad();


#endif