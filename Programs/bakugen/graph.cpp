#include "graph.h"

int gPlayer[PLAYER_GRAPH_NUM][PLAYER_CHIP_NUM];
int gItem[ITEM_GRAPH_NUM];
int gFace[FACE_GRAPH_NUM];
int gNumber[NUMBER_GRAPH_NUM];
int gBack[BACK_GRAPH_NUM];
int gMap[MAP_GRAPH_NUM][3];
int gBomb[BOMB_GRAPH_NUM][PLAYER_NUM];
int gShot[SHOT_GRAPH_NUMA][SHOT_GRAPH_NUMB];
int gSpell[SPELL_GRAPH_NUM];
int gEffect[EFFECT_GRAPH_NUM];
int gExplosion;
int gEnemy;
int gAscii[ASCII_NUM];
int gMenuBack;
int gMenu[MENU_GRAPH_NUM];
int gSnap;//スナップショット

int font_default;
int font_time;

int GLoad();

int GLoad(){
	try{
		font_default = CreateFontToHandle(NULL,14,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		font_time = CreateFontToHandle(NULL,18,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		const int GRA = 2;
		int gra[GRA];
		char fi[128];
		SetTransColor(0,0,0);
		for(int i=0;i<GRA;i++){
			wsprintf(fi , "data/img/dot/%d.png" , i);
			if( (gra[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<PLAYER_GRAPH_NUM;i++){
			for(int a=0;a<PLAYER_CHIP_NUM;a++){
				switch(i){
					case REIMU:
						gPlayer[i][a] = DerivationGraph(24*(a%3), 32*(a/3), 24, 32, gra[0]);
						break;
					case MARISA:
						gPlayer[i][a] = DerivationGraph(72+24*(a%3), 32*(a/3), 24, 32, gra[0]);
						break;
					case SAKUYA:
						gPlayer[i][a] = DerivationGraph(144+24*(a%3), 32*(a/3), 24, 32, gra[0]);
						break;
					case REMILIA:
						gPlayer[i][a] = DerivationGraph(24*(a%3), 32*(a/3), 24, 32, gra[1]);
						break;
					case FRANDRE:
						gPlayer[i][a] = DerivationGraph(72+24*(a%3), 32*(a/3), 24, 32, gra[1]);
						break;
				}
			}
		}
		for(int i=0;i<ITEM_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/item/%d.png" , i);
			if( (gItem[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<FACE_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/face/%d.jpg" , i);
			if( (gFace[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<NUMBER_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/number/%d.png" , i);
			if( (gNumber[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<BACK_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/back/%d.jpg" , i);
			if( (gBack[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<MAP_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/map/%d-0.png" , i);
			if( (gMap[i][0] = LoadGraph(fi)) == -1)	throw(fi);
			wsprintf(fi , "data/img/map/%d-1.png" , i);
			if( (gMap[i][1] = LoadGraph(fi)) == -1)	throw(fi);
			wsprintf(fi , "data/img/map/%d-2.png" , i);
			if( (gMap[i][2] = LoadGraph(fi)) == -1)	throw(fi);
		}
                for(int i=0;i<BOMB_GRAPH_NUM;i++){
			for(int a=0;a<PLAYER_NUM;a++){
				wsprintf(fi , "data/img/bomb/%d-%d.png" , i,a);
				if( (gBomb[i][a] = LoadGraph(fi)) == -1)	throw(fi);
			}
		}
		wsprintf(fi , "data/img/bomb/explosion.png");
		if( (gExplosion = LoadGraph(fi)) == -1)	throw(fi);
		wsprintf(fi , "data/img/dot/enemy.png");
		if( (gEnemy = LoadGraph(fi)) == -1)	throw(fi);
		int sgra[SHOT_GRAPH_NUMA];
		for(int i=0;i<SHOT_GRAPH_NUMA;i++){
			wsprintf(fi , "data/img/shot/%d.png" , i);
			if( (sgra[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<SHOT_GRAPH_NUMA;i++){
			for(int a=0;a<SHOT_GRAPH_NUMB;a++){
				if(i==0)	gShot[i][a] = DerivationGraph(20*a, 0, 20, 20, sgra[i]);
				if(i==1)	gShot[i][a] = DerivationGraph(18*a, 0, 18, 14, sgra[i]);
			}
		}
		for(int i=0;i<SPELL_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/spell/%d.png" , i);
			if( (gSpell[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<EFFECT_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/effect/%d.png" , i);
			if( (gEffect[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<ASCII_NUM;i++){
			wsprintf(fi , "data/img/ascii/%d.png" , i);
			if( (gAscii[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		wsprintf(fi , "data/img/menu/0.png");
		if( (gMenuBack = LoadGraph(fi)) == -1)	throw(fi);
		for(int i=0;i<MENU_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/menu/%d.png" , i+1);
			if( (gMenu[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		gSnap = MakeGraph(640,480);
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つからない\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}

	return 0;
}