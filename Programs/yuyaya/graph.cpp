#include "graph.h"

int gAscii[ASCII_NUM];
int gMenuBack;
int gMenuBack2;
int gMenu[MENU_GRAPH_NUM];
int gTitle[TITLE_GRAPH_NUM];
int gLevel[LEVEL_GRAPH_NUM];
int gLogo[LOGO_GRAPH_NUM];
int gSystem[SYSTEM_GRAPH_NUM];
int gPlayer[PLAYER_GRAPH_NUM];
int gHit[HIT_GRAPH_NUM];
int gHit2[HIT2_GRAPH_NUM];
int gScore[SCORE_GRAPH_NUM];
int gPShot[PCHARA_NUM][PSHOT_GRAPH_NUM];
int gEffect[EFFECT_GRAPH_NUM];
int gEffect2[EFFECT2_GRAPH_NUM];
int gEnemy[ENEMY_GRAPH_NUM];
int gPauseG[PAUSE_GRAPH_NUM];
int gBack[BACK_GRAPH_NUM];
int gBack2[BACK2_GRAPH_NUM];
int gBoss[BOSS_GRAPH_NUM];
int gBossName[BOSSNAME_GRAPH_NUM];
int gEShot[ESHOT_GRAPH_NUM];
int gEShot2[ESHOT2_GRAPH_NUM];
int gItem[ITEM_GRAPH_NUM];
int gCatin[CATIN_GRAPH_NUM];
int gSpell[SPELL_GRAPH_NUM];
int gModel[MODEL_GRAPH_NUM];
int gLaser[LASER_GRAPH_NUM][LASER_ELEMENT_NUM];
int gGage;
int gSnap;//スナップショット
int gPause;//ポーズ
int gPause2;//ポーズ

int GLoad();

int GLoad(){
	int co = GetNowCount();
	try{
		char fi[128];
		SetTransColor(0,0,0);
		for(int i=0;i<ASCII_NUM;i++){
			wsprintf(fi , "data/img/ascii/%d.png" , i);
			if( (gAscii[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		wsprintf(fi , "data/img/title/back.jpg");
		if( (gMenuBack = LoadGraph(fi)) == -1)	throw(fi);
		wsprintf(fi , "data/img/title/back2.jpg");
		if( (gMenuBack2 = LoadGraph(fi)) == -1)	throw(fi);
		for(int i=0;i<BACK_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/back/%d.jpg" , i);
			if( (gBack[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<BACK2_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/back/%d.png" , i);
			if( (gBack2[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<MENU_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/title/%d.png" , i);
			if( (gMenu[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<TITLE_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/title/t%d.png" , i);
			if( (gTitle[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<LEVEL_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/level/%d.png" , i);
			if( (gLevel[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<LOGO_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/logo/%d.png" , i);
			if( (gLogo[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<SYSTEM_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/system/%d.png" , i);
			if( (gSystem[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		const int PGRANUM = 7;
		int Pgra[PGRANUM];
		for(int i=0;i<PGRANUM;i++){
			wsprintf(fi , "data/img/player/%d.png" , i);
			if( (Pgra[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<PLAYER_GRAPH_NUM;i++){
			if(i==0)	gPlayer[i] = DerivationGraph(10, 6, 28, 42, Pgra[0]);
			if(i==1)	gPlayer[i] = DerivationGraph(10, 52, 28, 42, Pgra[0]);
			if(i==2)	gPlayer[i] = DerivationGraph(10, 100, 28, 42, Pgra[0]);
			if(i==3)	gPlayer[i] = DerivationGraph(0, 159, 20, 20, Pgra[0]);
			if(i==4)	gPlayer[i] = DerivationGraph(26, 130, 12, 12, Pgra[1]);
			if(i==5)	gPlayer[i] = DerivationGraph(66, 106, 60, 60, Pgra[1]);
			if(i==6)	gPlayer[i] = DerivationGraph(132, 108, 56, 56, Pgra[1]);
			if(i>=7){
				int nN = (i-7)/3 + 2;
				int nn = (i-7)%3;
				if(nN==2)	gPlayer[i] = DerivationGraph(32*nn, 0, 32, 42, Pgra[nN]);
				else if(nN==3)	gPlayer[i] = DerivationGraph(32*nn, 0, 32, 48, Pgra[nN]);
				else if(nN==4)	gPlayer[i] = DerivationGraph(32*nn, 0, 32, 46, Pgra[nN]);
				else if(nN==5)	gPlayer[i] = DerivationGraph(48*nn, 0, 48, 36, Pgra[nN]);
				else if(nN==6)	gPlayer[i] = DerivationGraph(32*nn, 0, 32, 48, Pgra[nN]);
			}
		}
		for(int i=0;i<HIT_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/hit/%d.png" , i);
			if( (gHit[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<HIT2_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/hit/%da.png" , i);
			if( (gHit2[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<SCORE_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/score/%d.png" , i);
			if( (gScore[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int j=0;j<PCHARA_NUM;j++){
			for(int i=0;i<PSHOT_GRAPH_NUM;i++){
				if(j>=3 && i>=PSHOT_GRAPH_NUM-2)	break;	
				wsprintf(fi , "data/img/shot/%d/%d.png" , j, i);
				if( (gPShot[j][i] = LoadGraph(fi)) == -1)	throw(fi);
			}
		}
		for(int i=0;i<EFFECT_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/effect/%d.png" , i);
			if( (gEffect[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<EFFECT2_GRAPH_NUM;i++){
			if(i==0)	gEffect2[i] = DerivationGraph(0, 24, 32, 32, Pgra[1]);
			if(i==1)	gEffect2[i] = DerivationGraph(32, 24, 32, 32, Pgra[1]);
			if(i==2)	gEffect2[i] = DerivationGraph(0, 0, 24, 24, Pgra[1]);
		}
		for(int i=0;i<ENEMY_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/enemy/%d.png" , i);
			if( (gEnemy[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<PAUSE_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/pause/%d.png" , i);
			if( (gPauseG[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<BOSS_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/boss/%d.png" , i);
			if( (gBoss[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<BOSSNAME_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/boss/n%d.png" , i);
			if( (gBossName[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		int Egra[2];
		for(int i=0;i<2;i++){
			wsprintf(fi , "data/img/shot/shot%d.png" , i);
			if( (Egra[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<19;i++){
			for(int a=0;a<8;a++){
				if(i==0)	gEShot[8*i+a] = DerivationGraph(0+12*a, 0, 12, 12, Egra[0]);
				if(i==1)	gEShot[8*i+a] = DerivationGraph(0+18*a, 12, 18, 18, Egra[0]);
				if(i==2)	gEShot[8*i+a] = DerivationGraph(0+20*a, 30, 20, 20, Egra[0]);
				if(i==3)	gEShot[8*i+a] = DerivationGraph(0+30*a, 50, 30, 30, Egra[0]);
				if(i==4)	gEShot[8*i+a] = DerivationGraph(0+10*a, 80, 10, 20, Egra[0]);
				if(i==5)	gEShot[8*i+a] = DerivationGraph(0+12*a, 100, 12, 18, Egra[0]);
				if(i==6)	gEShot[8*i+a] = DerivationGraph(0+12*a, 118, 12, 20, Egra[0]);
				if(i==7)	gEShot[8*i+a] = DerivationGraph(0+12*a, 138, 12, 20, Egra[0]);
				if(i==8)	gEShot[8*i+a] = DerivationGraph(0+18*a, 158, 18, 28, Egra[0]);
				if(i==9)	gEShot[8*i+a] = DerivationGraph(0+14*a, 186, 14, 22, Egra[0]);
				if(i==10)	gEShot[8*i+a] = DerivationGraph(0+18*a, 208, 18, 16, Egra[0]);
				if(i==11)	gEShot[8*i+a] = DerivationGraph(0+16*a, 224, 16, 18, Egra[0]);
				if(i==12)	gEShot[8*i+a] = DerivationGraph(0+20*a, 242, 20, 18, Egra[0]);
				if(i==13)	gEShot[8*i+a] = DerivationGraph(0+30*a, 260, 30, 30, Egra[0]);
				if(i==14)	gEShot[8*i+a] = DerivationGraph(0+20*a, 318, 20, 20, Egra[0]);
				if(i==15)	gEShot[8*i+a] = DerivationGraph(0+32*a, 338, 32, 32, Egra[0]);
				if(i==16)	gEShot[8*i+a] = DerivationGraph(0+22*a, 370, 22, 28, Egra[0]);
				if(i==17)	gEShot[8*i+a] = DerivationGraph(0+22*a, 398, 22, 32, Egra[0]);
				if(i==18)	gEShot[8*i+a] = DerivationGraph(0+64*a, 192, 64, 64, Egra[1]);
			}
		}
		for(int i=0;i<2;i++){
			for(int a=0;a<6;a++){
				gEShot2[6*i+a] = DerivationGraph(0+48*a, 30+48*i, 48, 48, Egra[1]);
			}
		}
		for(int i=0;i<ITEM_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/item/%d.png" , i);
			if( (gItem[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<CATIN_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/catin/%d.png" , i);
			if( (gCatin[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<SPELL_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/spell/%d.png" , i);
			if( (gSpell[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<MODEL_GRAPH_NUM;i++){
			wsprintf(fi , "data/img/back/model/%d/models/model.mv1" , i);
			if( (gModel[i] = MV1LoadModel(fi)) == -1)	throw(fi);
		}
		int Lgra;
		wsprintf(fi , "data/img/shot/1.png");
		if( (Lgra = LoadGraph(fi)) == -1)	throw(fi);
		for(int i=0;i<LASER_GRAPH_NUM;i++){
			for(int j=0;j<LASER_ELEMENT_NUM;j++){
				gLaser[i][j] = DerivationGraph(8*i, j, 8, 1, Lgra);
			}
		}
		wsprintf(fi , "data/img/gage.png");
		if( (gGage = LoadGraph(fi)) == -1)	throw(fi);
		gSnap = MakeGraph(640,480);
		gPause = MakeGraph(420,460);
		gPause2 = MakeGraph(84,92);
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
	char mes[128];
	sprintf(mes, "GLoad: %d ms", GetNowCount()-co);
	WriteLog(mes);

	return 0;
}