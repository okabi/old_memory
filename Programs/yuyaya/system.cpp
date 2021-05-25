#include "system.h"
#include "menu.h"
#include "pshot.h"
#include "enemy.h"
#include "effect.h"
#include "boss.h"
#include "talk.h"

bool bRG;//マジギレ補正をかけるか？
bool bES;//ハイパーゲージ速度補正をかけるか？
int Scount;
int Scount_all;//全体を通したステージカウント
int Pcount;//ポーズカウント
int Pcarsol[2];
int Pscene;
int Pcount2;
int Pcount3;
int PNowcount;
int Ccount;//ステージクリア時
int Ccount2;//オールクリア時
int Ccount3;
int Ecount;
float BackX;
float BackY;
float BackZ;
int GageCount;
int FunctionCount;
int SpellCount;//スペカ発動してからのカウント
NPART NowPart;//ステージのどの部分？
int MissN;
int BombN;
int Dcount;

PLAYERDATA Player[PLAYER_NUM];
OPTIONDATA Option[OPTION_NUM];
list<BACKDATA> BEffect;

void RSave(int num, bool save);
void RLoad();
void RMain(int *up, int *down, int *left, int *right, int *shot, int *bomb, int *slow, int *skip, int *pause, bool flag);
void PLoad();
void PReset();
void GetData();
void GetData2();
void Smain();
void add_score(unsigned int add);
void add_gage(int add);
void add_stress_gage(int add);
void add_soten(int add);
void PDraw();
void PMove(int i);
void ODraw();
void OMove(int i);
void SBack();
void SESDelete(int flag,float x,float y);
void SAtari();
void SBEfDraw();
void SBEfMove(list<BACKDATA>::iterator &it);
void SBEfMake(float x,float y,float z,int pattern);
void DrawGage();
int Loo(int rank0, int rank10);
int Per(int rank0, int rank10);


void RSave(int num, bool save){
//リプレイ情報の保存
	unsigned int score[2] = {0,0};
	for(int i=0;i<STAGE_NUM;i++){
		score[0] += SScore.stage_allscore[i][0];
		score[1] += SScore.stage_allscore[i][1];
		if(score[1]>=10000000){
			score[0] += score[1]/10000000;
			score[1] -= score[1]/10000000*10000000;
		}
		for(int j=0;j<2;j++){
			SReplay.score[i][j] = score[j]; 
		}
	}
	SReplay.stage = SScore.end_stage;
	SReplay.level = Player[0].level;
	SReplay.chara = Player[0].chara;
	SReplay.con_num = SScore.con_num;
	SReplay.rank = SScore.rank[STAGE_NUM];
	DATEDATA D;
	GetDateTime(&D);
	SReplay.year = D.Year;
	SReplay.month = D.Mon;
	SReplay.date = D.Day;
	SReplay.slowrate = SScore.slowrate;
	
	Replay[num] = SReplay;
	
	if(save==true){
		int Element = SReplay.element_num;
		crypt(&SReplay,sizeof(REPLAYDATA),0xF7);
		char name[64];
		wsprintf(name , "replay");
		if(PathIsDirectory(name)==false){
			CreateDirectory(name,NULL);
		}
		wsprintf(name , "replay/goog_%02d.rpy",num+1);
		FILE *fp;
		if((fp=fopen(name,"wb")) == NULL){
			char message[128];
			wsprintf(message , "リプレイの保存に何故だか失敗");
			MessageBox( 	NULL,
				message,
				"Error",
				MB_OK | 
				MB_ICONSTOP |
				MB_TOPMOST);
			return;
		}	
		fwrite(&SReplay,sizeof(REPLAYDATA)-5*REPLAY_ELEMENT_NUM,1,fp);
		for(int i=0;i<Element;i++){
			fputc(SReplay.replay_element[i],fp);
		}
		fwrite(&SReplay.replay_count[0],4*Element,1,fp);
		fclose(fp);
		crypt(&SReplay,sizeof(REPLAYDATA),0xF7);
	}

	return;
}

void RLoad(){
//リプレイ情報の初期化
	replay_count = 0;
	before_key = 0;
	Kcount = 0;
	if(replay_play==false){
		SReplay.version = VERSION;
		SReplay.element_num = 0;
		SReplay.exist = true;
		for(int i=0;i<REPLAY_ELEMENT_NUM;i++){
			SReplay.replay_element[i] = 0;
			SReplay.replay_count[i] = 65535;
		}
		for(int i=0;i<STAGE_NUM;i++){
			for(int j=0;j<2;j++)	SReplay.score[i][j] = 0;
			SReplay.rand_seed[i] = rand_seed;
			SReplay.ship[i] = 0;
			SReplay.bomb[i] = 0;
			SReplay.first_bomb[i] = 0;
			SReplay.spcard[i] = 0;
			SReplay.stress_gage[i] = 0;
			SReplay.hyper_rank[i] = 0;
			SReplay.hyper_gage[i] = 0;
			SReplay.hyper_count[i] = 0;
			SReplay.s_exist[i] = false;
		}
		SReplay.stage = 1;
		SReplay.level = Player[0].level;
		SReplay.chara = Player[0].chara;
		SReplay.con_num = 0;
		SReplay.rank = 0;
		SReplay.year = 2011;
		SReplay.month = 1;
		SReplay.date = 1;
		SReplay.slowrate = 0;
		for(int i=0;i<USER_NAME_NUM+1;i++){
			SReplay.name[i] = SAVE.LastName[i];
		}
	}

	return;
}

void RMain(int *up, int *down, int *left, int *right, int *shot, int *bomb, int *slow, int *skip, int *pause, bool flag){
//ポーズ中以外は常に全ての動作前に作動させること。リプレイ再生処理もここ
	if(replay_play==false){
		int iup,idown,ileft,iright,ishot,ibomb,islow,iskip,ipause;
		GetInput(&iup,&idown,&ileft,&iright,&ishot,&ibomb,&islow,&iskip,&ipause);
		unsigned char input=0;
		if(iup>0)	input += 1;
		if(idown>0)	input += 2;
		if(ileft>0)	input += 4;
		if(iright>0)	input += 8;
		if(ishot>0)	input += 16;
		if(ibomb>0)	input += 32;
		if(islow>0)	input += 64;
		if(iskip>0)	input += 128;
		
		if(Scount==0 || input!=before_key){
			if(Scount>0 && SReplay.element_num+1<REPLAY_ELEMENT_NUM){
				SReplay.replay_count[SReplay.element_num] = Kcount;
				SReplay.element_num++;
				SReplay.replay_element[SReplay.element_num] = input;
			}
			else if(SReplay.element_num+1<REPLAY_ELEMENT_NUM){
				SReplay.replay_element[SReplay.element_num] = input;
			}
			Kcount = 0;
			before_key = input;
		}
		Kcount++;
	}
	else{
		if(flag==true){
			if(SReplay.replay_count[replay_count]==Kcount){
				replay_count++;
				Kcount = 0;
			}
			Kcount++;
			unsigned char input = SReplay.replay_element[replay_count];
			if(input&1)	Eup++;
			else		Eup = 0;
			if(input&2)	Edown++;
			else		Edown = 0;
			if(input&4)	Eleft++;
			else		Eleft = 0;
			if(input&8)	Eright++;
			else		Eright = 0;
			if(input&16)	Eshot++;
			else		Eshot = 0;
			if(input&32)	Ebomb++;
			else		Ebomb = 0;
			if(input&64)	Eslow++;
			else		Eslow = 0;
			if(input&128)	Eskip++;
			else		Eskip = 0;
		}
		*up = Eup;
		*down = Edown;
		*left = Eleft;
		*right = Eright;
		*shot = Eshot;
		*bomb = Ebomb;
		*slow = Eslow;
		*skip = Eskip;
	}

	return;
}

void PlLoad(){
	for(int i=0;i<PLAYER_NUM;i++){
		//セレクトレベルでやる	if(replay_play==false)	Player[i].level = SAVE.Level;
		//セレクトキャラでやる	if(replay_play==false)	Player[i].chara = SAVE.Chara;
		Player[i].hiscore[0] = SAVE.Score[Player[i].level][Player[i].chara][0].score[0];
		Player[i].hiscore[1] = SAVE.Score[Player[i].level][Player[i].chara][0].score[1];
		Player[i].score[0] = 0;
		Player[i].score[1] = 0;
		Player[i].score2[0] = 0;
		Player[i].score2[1] = 0;
		if(Player[i].chara%3==0)	Player[i].speed = 6.0;
		else if(Player[i].chara%3==1)	Player[i].speed = 8.0;
		else if(Player[i].chara%3==2)	Player[i].speed = 4.5;
		Player[i].large = 1.0;
		Player[i].angle = 0.0;
		Player[i].atari = 2.0;
		Player[i].hi_cont_num = SAVE.Score[Player[i].level][Player[i].chara][0].con_num;
		if(Player[i].level==IMPOSSIBLE && Player[i].stage>=0){
			Player[i].first_ship = 0;
			if(Player[i].chara<=2){
				Player[i].first_bomb = 3;
				Player[i].hyper_gage = MAX_GAGE;
			}
			else{
				Player[i].first_bomb = 1;
				Player[i].hyper_gage = 0;
			}
		}
		else if(title_carsol==2){
			Player[i].first_ship = 8;
			if(Player[i].chara<=2){
				Player[i].first_bomb = 3;
				if(Player[i].stage>=0)	Player[i].hyper_gage = MAX_GAGE;
				else			Player[i].hyper_gage = 0;
			}
			else{
				Player[i].hyper_gage = 0;
				Player[i].first_bomb = 3;
			}
		}
		else{
			Player[i].first_ship = SAVE.Ship;
			Player[i].first_bomb = SAVE.Bomb;
			Player[i].hyper_gage = 0;
		}
		Player[i].ship_num = Player[i].first_ship;
		Player[i].bomb_num = Player[i].first_bomb;
		//if(Player[i].chara>=3 && Player[i].bomb_num>Player[i].first_bomb)	Player[i].bomb_num = Player[i].first_bomb;	
		Player[i].spcard = 0;
		Player[i].kill_num = 0;
		for(int j=0;j<3;j++)	Player[i].item_num[j] = 0;
		Player[i].stress_gage = 0;
		Player[i].hyper_rank = 0;
		Player[i].stress_count = 0;
		Player[i].hyper_count = 0;
		if(Player[i].level==IMPOSSIBLE){
			Player[i].first_bomb = 3;
		}
	}

	for(int i=0;i<2;i++){
		SScore.score[i] = 0;
		for(int j=0;j<STAGE_NUM;j++){
			SScore.stage_allscore[j][i] = 0;
			for(int a=0;a<STAGE_SCORE_NUM;a++)	SScore.stage_score[j][a][i] = 0;
		}
	}
	SScore.end_stage = Player[0].stage;
	SScore.gameper = 0;
	SScore.slowrate = 0;
	SScore.con_num = 0;
	SScore.miss_num = 0;
	SScore.bomb_num = 0;
	SScore.hyper_num = 0;
	SScore.spell_num = 0;
	for(int i=0;i<STAGE_NUM+1;i++){
		SScore.rank[i] = 0; 
		SScore.Rplaytime[i] = 0;
		SScore.Vplaytime[i] = 0;
		SScore.enemy_num[i] = 0;
		SScore.enemyshot_num[i] = 0;
		for(int j=0;j<3;j++)	SScore.item_num[j][i] = 0;
		SScore.max_soten[i] = 0;
		SScore.max_hit[i] = 0;
	}
	for(int i=0;i<SPELL_NUM;i++)		SScore.score_spcard[i] = 0;
	for(int i=0;i<USER_NAME_NUM;i++)	SScore.name[i] = SAVE.LastName[i];
	DATEDATA D;
	GetDateTime(&D);
	for(int i=0;i<2;i++){
		SScore.year[i] = D.Year;
		SScore.month[i] = D.Mon;
		SScore.date[i] = D.Day;
		SScore.hour[i] = D.Hour;
		SScore.minute[i] = D.Min;
		SScore.second[i] = D.Sec;
	}
	SScore.first_ship = SAVE.Ship;
	SScore.first_bomb = SAVE.Bomb;
	STCount = GetNowCount();

	return;
}

void PLoad(){
//STG開始時ロード。ステージ値－１はメニューで決める
	if(replay_play==true){
		Player[0].level = SReplay.level;
		Player[0].chara = SReplay.chara;
	}
	Ccount3 = 0;
	Scount_all = 0;
	PlLoad();
	for(int i=0;i<PLAYER_NUM;i++){
		Player[i].cont_num = 0;
	}
	for(int i=0;i<OPTION_NUM;i++){
		Option[i].large = 1.0;
	}
	RLoad(); 
	PReset();
	SScore.start_stage = Player[0].stage;

	return;
}

void GetData(){
//オールクリア時の、スコアデータの取得。
	SScore.end_stage = Player[0].stage;
	if(NowPart==BOSS)	SScore.gameper = (Player[0].stage-1)*200 + 120 + 80.0*(float)BOSSERASENUM/(float)STCOUNT[Player[0].stage-1][1];//実際は1/10
	else			SScore.gameper = (Player[0].stage-1)*200 + 120.0*(float)Scount/(float)STCOUNT[Player[0].stage-1][0];//実際は1/10
	SScore.con_num = Player[0].cont_num;
	SScore.slowrate = 1000.0*(float)SScore.Rplaytime[STAGE_NUM]/(float)SScore.Vplaytime[STAGE_NUM] - 1000.0;
	if(SScore.slowrate>=1000)	SScore.slowrate = 999;	
	else if(SScore.slowrate<0)	SScore.slowrate = 0;	
	DATEDATA D;
	GetDateTime(&D);
	SScore.year[1] = D.Year;
	SScore.month[1] = D.Mon;
	SScore.date[1] = D.Day;
	SScore.hour[1] = D.Hour;
	SScore.minute[1] = D.Min;
	SScore.second[1] = D.Sec;

	if(title_carsol==2){
		SScore.rank[STAGE_NUM] = SScore.rank[Player[0].stage-1];
	}
	else{
		SScore.rank[STAGE_NUM] = 0;
		int num = Player[0].stage;
		if(num>STAGE_NUM)	num = STAGE_NUM;
		for(int i=0;i<STAGE_NUM;i++){
			SScore.rank[STAGE_NUM] += SScore.rank[i];
		}
		SScore.rank[STAGE_NUM] /= num;
	}

	return;
}

void GetData2(){
//ステージクリア時の、スコアデータの取得。
	int rate=0,comp=0,point=0;
	switch(Player[0].stage){
		case 1:	
			comp = SScore.stage_allscore[Player[0].stage-1][0];
			if(Player[0].level==EASY || Player[0].level==BABY){
				if(Player[0].chara<=2)	rate = 8;//８億点
				else 			rate = 8;//８億点
			}
			else if(Player[0].level==NORMAL){
				if(Player[0].chara<=2)	rate = 16;//１６億点
				else 			rate = 16;//１６億点
			}
			else if(Player[0].level==HARD){
				if(Player[0].chara<=2)	rate = 24;//２４億点
				else 			rate = 24;//２４億点
			}
			else if(Player[0].level==LUNATIC || Player[0].level==IMPOSSIBLE){
				if(Player[0].chara<=2)	rate = 32;//３２億点
				else 			rate = 32;//３２億点
			}
			point = 1000.0*(float)comp/(float)rate;
			if(point>1000)	point = 1000;
			if(MissN<1)		point += (1-MissN)*1000;
			if(BombN==0)		point += 1000;
			else if(BombN<3)	point += (3-BombN)*333;
			point /= 3;
			SScore.rank[Player[0].stage-1] = point;
			break;
		case 2:	
			comp = SScore.stage_allscore[Player[0].stage-1][0];
			if(Player[0].level==EASY || Player[0].level==BABY){
				if(Player[0].chara<=2)	rate = 50;//５０億点
				else 			rate = 50;//５０億点
			}
			else if(Player[0].level==NORMAL){
				if(Player[0].chara<=2)	rate = 100;//１００億点
				else 			rate = 100;//１００億点
			}
			else if(Player[0].level==HARD){
				if(Player[0].chara<=2)	rate = 150;//１５０億点
				else 			rate = 150;//１５０億点
			}
			else if(Player[0].level==LUNATIC || Player[0].level==IMPOSSIBLE){
				if(Player[0].chara<=2)	rate = 200;//２００億点
				else 			rate = 200;//２００億点
			}
			point = 1000.0*(float)comp/(float)rate;
			if(point>1000)	point = 1000;
			if(MissN<1)		point += (1-MissN)*1000;
			if(BombN<5)		point += (5-BombN)*200;
			point /= 3;
			SScore.rank[Player[0].stage-1] = point;
			break;
		case 3:	
			comp = SScore.stage_allscore[Player[0].stage-1][0];
			if(Player[0].level==EASY || Player[0].level==BABY){
				if(Player[0].chara<=2)	rate = 350;//３５０億点
				else 			rate = 350;//３５０億点
			}
			else if(Player[0].level==NORMAL){
				if(Player[0].chara<=2)	rate = 700;//７００億点
				else 			rate = 700;//７００億点
			}
			else if(Player[0].level==HARD){
				if(Player[0].chara<=2)	rate = 1050;//１０５０億点
				else 			rate = 1050;//１０５０億点
			}
			else if(Player[0].level==LUNATIC || Player[0].level==IMPOSSIBLE){
				if(Player[0].chara<=2)	rate = 1400;//１４００億点
				else 			rate = 1400;//１４００億点
			}
			point = 1000.0*(float)comp/(float)rate;
			if(point>1000)	point = 1000;
			if(MissN<2)		point += (2-MissN)*500;
			if(BombN<5)		point += (5-BombN)*200;
			point /= 3;
			SScore.rank[Player[0].stage-1] = point;
			break;
	}
	SScore.Rplaytime[Player[0].stage-1] = 60*(GetNowCount()-NOCount-CKCount)/1000;
	SScore.Vplaytime[Player[0].stage-1] = Scount;
	SScore.Rplaytime[STAGE_NUM] += SScore.Rplaytime[Player[0].stage-1];
	SScore.Vplaytime[STAGE_NUM] += SScore.Vplaytime[Player[0].stage-1];
	CKCount = 0;
	if(replay_play==false && Ccount>0){
		if(Player[0].stage>SAVE.Stage)	SAVE.Stage = Player[0].stage;
	}

	return;
}

void PlReset(){
	for(int i=0;i<PLAYER_NUM;i++){
		Player[i].soten = 0;
		Player[i].soten2 = 0;
		Player[i].hit = 0;
		Player[i].hit2 = 0;
		Player[i].hit2_count = 0;
		Player[i].laser_count = 0;
		Player[i].aura_count = 0;
		Player[i].rate_soten = 0;
		Player[i].hit_gage = 0;
		Player[i].x = CENTER_X;
		Player[i].y = 420;
		Player[i].flash = 255;
		Player[i].plus_hit = 0;
		Player[i].plus_hit_count = 0;
		Player[i].slow_count = 0;
		Player[i].miss_count = 0;
		Player[i].death_count = 0;
		Player[i].muteki_count = 120;
		Player[i].img_num = 0;
		Player[i].count = 0;
		Player[i].up = 0;
		Player[i].down = 0;
		Player[i].left = 0;
		Player[i].right = 0;
		Player[i].shot = 0;
		Player[i].bomb = 0;
		Player[i].slow = 0;
		Player[i].skip = 0;
		Player[i].total_hit = 0;
		Player[i].hyper_count2 = 0;
		Player[i].stress_count = 0;
		Player[i].graze_count = 0;
	}
	for(int i=0;i<OPTION_NUM;i++){
		Option[i].x = CENTER_X;
		Option[i].y = 420;
		Option[i].angle = 0;
		Option[i].ro = 0;
		Option[i].ro_angle = 0;
		Option[i].flash = 255;
		Option[i].count = 0;
	}
	NOCount = GetNowCount();

	return;
}

void PReset(){
//一面ごとにロード
	bRG = false;
	bES = false;
	for(int i=0;i<8;i++){
		i_hanyou[0] = 0;
	}
	Eup = 0;
	Edown = 0;
	Eleft = 0;
	Eright = 0;
	Eshot = 0;
	Ebomb = 0;
	Eslow = 0;
	Eskip = 0;
	Epause = 0;
	
	bShake = false;
	
	Ecount = 0;
	BEffect.clear();
	PSReset();
	EReset();
	EfReset();
	BReset();
	TReset();
	Dcount = 0;
	Scount = 0;
	Pcount = 0;
	PNowcount = 0;
	CKCount = 0;
	Pcarsol[0] = 0;
	Pcarsol[1] = 0;
	Pscene = 0;
	Pcount2 = 0;
	Pcount3 = 0;
	Ccount = 0;
	Ccount2 = 0;
	BackX = 0;
	BackY = 0;
	BackZ = 0;
	GageCount = 0;
	FunctionCount = 0;
	SpellCount = 0;
	NowPart = EARLY;
	BOSSERASENUM = 0;
	MissN = 0;
	BombN = 0;
	PlReset();
	for(int i=0;i<PLAYER_NUM;i++){
		Player[i].stage++;
		Player[i].before_score[0] = Player[0].score2[0];
		Player[i].before_score[1] = Player[0].score2[1];
	}
	
	if(replay_play==false){
		SReplay.s_exist[Player[0].stage-1] = true;
		SReplay.element_num++;
		SReplay.start_count[Player[0].stage-1] = SReplay.element_num;
		SReplay.rand_seed[Player[0].stage-1] = rand_seed;
		SReplay.ship[Player[0].stage-1] = Player[0].ship_num;
		SReplay.bomb[Player[0].stage-1] = Player[0].bomb_num;
		SReplay.first_bomb[Player[0].stage-1] = Player[0].first_bomb;
		SReplay.spcard[Player[0].stage-1] = Player[0].spcard;
		SReplay.stress_gage[Player[0].stage-1] = Player[0].stress_gage;
		SReplay.hyper_rank[Player[0].stage-1] = Player[0].hyper_rank;
		SReplay.hyper_gage[Player[0].stage-1] = Player[0].hyper_gage;
		SReplay.hyper_count[Player[0].stage-1] = Player[0].hyper_count;
	}
	else{
		Player[0].level = SReplay.level;
		Player[0].chara = SReplay.chara;
		replay_count = SReplay.start_count[Player[0].stage-1];
		rand_seed = SReplay.rand_seed[Player[0].stage-1];
		Player[0].ship_num = SReplay.ship[Player[0].stage-1];
		Player[0].bomb_num = SReplay.bomb[Player[0].stage-1];
		Player[0].first_bomb = SReplay.first_bomb[Player[0].stage-1];
		Player[0].spcard = SReplay.spcard[Player[0].stage-1];
		Player[0].stress_gage = SReplay.stress_gage[Player[0].stage-1];
		Player[0].hyper_rank = SReplay.hyper_rank[Player[0].stage-1];
		Player[0].hyper_gage = SReplay.hyper_gage[Player[0].stage-1];
		Player[0].hyper_count = SReplay.hyper_count[Player[0].stage-1];
		if(Player[0].stage-2>=0){
			Player[0].score[0] = SReplay.score[Player[0].stage-2][0];
			Player[0].score2[0] = SReplay.score[Player[0].stage-2][0];
			Player[0].score[1] = SReplay.score[Player[0].stage-2][1];
			Player[0].score2[1] = SReplay.score[Player[0].stage-2][1];
		}
		for(int i=0;i<PLAYER_NUM;i++){
			Player[i].before_score[0] = Player[0].score2[0];
			Player[i].before_score[1] = Player[0].score2[1];
		}
	}

	if(Player[0].stage==0)		MuPlayBgm(1);
	else if(Player[0].stage==1)	MuPlayBgm(2);
	else if(Player[0].stage==2)	MuPlayBgm(4);
	else if(Player[0].stage==3)	MuPlayBgm(6);
	else if(Player[0].stage==4)	MuPlayBgm(8);
	else if(Player[0].stage==5)	MuPlayBgm(14);
	
	return;
}

void Smain(){
	static int BEup,BEdown,BEleft,BEright,BEshot,BEbomb,BEslow,BEskip;

	if(Pcount>0){
		int up,down,left,right,shot,bomb,slow,skip,pause;
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(Pcount==1){
			DrawExtendGraph(0,0,84,92,gPause,FALSE);
			GetDrawScreenGraph(0,0,84,92,gPause2);
		}
		DrawExtendGraph(10,10,430,470,gPause2,FALSE);
 		if(Pcount<20)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.0*Pcount);
 		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
		DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
		float plus;
		if(Pcount<20){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Pcount);
			plus = 0.5*pow(Pcount-20,2);
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			plus = 0;
		}
		if(Player[0].ship_num>=0&&Player[0].count>0)	DrawRotaGraphF(CENTER_X+plus,180,1.0,0,gPauseG[0],TRUE);
		else						DrawRotaGraphF(CENTER_X+plus,180,1.0,0,gPauseG[7],TRUE);
		for(int i=0;i<3;i++){
			float red = 170+80*sin(Radian(Pcount+70*i,TRUE));
			float green = 170+80*sin(Radian(Pcount+70*i,TRUE));
			float blue = 255;
			if(Pcarsol[0] != i){
				red /= 3;
				green /= 3;
				blue /= 3;
			}
			SetDrawBright(red,green,blue);
			if((Player[0].ship_num<0||Player[0].count==0) && i==0)	DrawGraphF(CENTER_X-85-pow(-1,i)*plus,220+35*i,gPauseG[8],TRUE);
			else					DrawGraphF(CENTER_X-85-pow(-1,i)*plus,220+35*i,gPauseG[2+i],TRUE);
		}
		SetDrawBright(255,255,255);
		if(Pscene==1){
 			if(Pcount2<20)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Pcount2);
 			else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			float plus2;
			if(Pcount2<20)	plus2 = 0.5*pow(Pcount2-20,2);
			else		plus2 = 0;
			DrawRotaGraphF(CENTER_X+85+plus2,330,1.0,0,gPauseG[1],TRUE);
			for(int i=0;i<2;i++){
				float red = 170+80*sin(Radian(Pcount2+70*i,TRUE));
				float green = 170+80*sin(Radian(Pcount2+70*i,TRUE));
				float blue = 255;
				if(Pcarsol[1] != i){
					red /= 3;
					green /= 3;
					blue /= 3;
				}
				SetDrawBright(red,green,blue);
				DrawGraphF(CENTER_X+60-pow(-1,i)*plus2,350+32*i,gPauseG[5+i],TRUE);
			}
			SetDrawBright(255,255,255);
			Pcount2++;
		}
		
		if(Pscene==0 && Pcount>=20){
			int CARSOL_NUM = 3;
			if(up==1 || (up>0&&up%10==0)){
				PlaySound(0);
				Pcarsol[0] = (Pcarsol[0]+CARSOL_NUM-1)%CARSOL_NUM;
			}
			else if(down==1 || (down>0&&down%10==0)){
				PlaySound(0);
				Pcarsol[0] = (Pcarsol[0]+CARSOL_NUM+1)%CARSOL_NUM;
			}
			if(shot==1){
				PlaySound(1);
				if(Pcarsol[0]==0){
					if(Player[0].ship_num<0){
						PlLoad();
						PlReset();
						Player[0].muteki_count = 240;
						if(Player[0].cont_num<9)	Player[0].cont_num++;
						add_gage(MAX_GAGE);
					}
					Pcount = 20;
					Pscene = 2;
				}
				else if(Pcarsol[0]==1 || Pcarsol[0]==2){
					Pcount2 = 0;
					Pcarsol[1] = 1;
					Pscene = 1;
				}
			}
			else if(Player[0].ship_num>=0&&(bomb==1 || pause==1)){
				PlaySound(2);
				Pcount = 20;
				Pscene = 2;
			}
		}
		else if(Pscene==1 && Pcount2>=20){
			int CARSOL_NUM = 2;
			if(up==1 || (up>0&&up%10==0)){
				PlaySound(0);
				Pcarsol[1] = (Pcarsol[1]+CARSOL_NUM-1)%CARSOL_NUM;
			}
			else if(down==1 || (down>0&&down%10==0)){
				PlaySound(0);
				Pcarsol[1] = (Pcarsol[1]+CARSOL_NUM+1)%CARSOL_NUM;
			}
			if(shot==1){
				if(Pcarsol[1]==0){
					PlaySound(1);
					Pcount3 = 0;
					Pscene = 3;
				}
				else if(Pcarsol[1]==1){
					PlaySound(2);
					Pscene = 0;
				}
			}
			else if(bomb==1 || pause==1){
				PlaySound(2);
				Pscene = 0;
			}
		}
		
		if(Pscene!=2)	Pcount++;
		else		Pcount--;
		if(Pcount==0){
			Eup = BEup;
			Edown = BEdown;
			Eleft = BEleft;
			Eright = BEright;
			Eshot = BEshot;
			Ebomb = BEbomb;
			Eslow = BEslow;
			Eskip = BEskip;
			CKCount += (GetNowCount() - PNowcount);
			DeleteGraph(gPause);
			DeleteGraph(gPause2);
			gPause = MakeGraph(420,460);
			gPause2 = MakeGraph(84,92);
			MuReturnBgm();
		}	
	}
	if(Pcount==0 && Ccount==0){
		SBack();
		SpBackDraw();
		EfDraw2();
		EDraw();
		BDraw();
		IDraw();
		PSDraw();
		PLDraw();
		PBDraw();
		ODraw();
		PDraw();
		EfDraw();
		ELDraw();
		ESLDraw();
		ESDraw();
		EfDraw3();
		DrawGage();
		BDrawGage();
		SAtari();
		TDraw();
		SpDraw();
		if(GetSkip() && bDemo==false){
			if(Ccount3>0){
				float rate = 0.13*pow(60-Ccount3,2);
				DrawGraph(10,10-rate,gPause,FALSE);
				Ccount3--;
				if(Ccount3==0){
					DeleteGraph(gPause);
					gPause = MakeGraph(420,460);
				}
			}
			
			if(Player[0].stage<=2 && Player[0].stage!=0){
				int img_num = 0;
				if(Player[0].stage==1)		img_num = 1;
				else if(Player[0].stage==2)	img_num = 5;
				
				if(Scount<60){}
				else if(Scount<120){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-60));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[0], TRUE, FALSE);
				}
				else if(Scount<240){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[0], TRUE, FALSE);
				}
				else if(Scount<300){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(Scount-240));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[0], TRUE, FALSE);
				}
				if(Scount<60){}
				else if(Scount<120){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-60));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}
				else if(Scount<240){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}
				else if(Scount<300){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(Scount-240));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}		
			}
			else if(Player[0].stage==3){
				int img_num = 13;
				
				if(Scount<1600){}
				else if(Scount<1660){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-1600));
					DrawRotaGraphF(CENTER_X, 100, 1.1, 0, gBack2[0], TRUE, FALSE);
				}
				else if(Scount<1840){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawRotaGraphF(CENTER_X, 100, 1.1, 0, gBack2[0], TRUE, FALSE);
				}
				else if(Scount<1900){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(Scount-1840));
					DrawRotaGraphF(CENTER_X, 100, 1.1, 0, gBack2[0], TRUE, FALSE);
				}
				if(Scount<1600){}
				else if(Scount<1660){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-1600));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}
				else if(Scount<1840){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}
				else if(Scount<1900){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(Scount-1840));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}		
			}
			else if(Player[0].stage==4){
				int img_num = 17;
				
				if(Scount<1600){}
				else if(Scount<1660){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-1600));
					DrawRotaGraphF(CENTER_X, 100, 1.1, 0, gBack2[0], TRUE, FALSE);
				}
				else if(Scount<1840){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawRotaGraphF(CENTER_X, 100, 1.1, 0, gBack2[0], TRUE, FALSE);
				}
				else if(Scount<1900){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(Scount-1840));
					DrawRotaGraphF(CENTER_X, 100, 1.1, 0, gBack2[0], TRUE, FALSE);
				}
				if(Scount<1600){}
				else if(Scount<1660){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-1600));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}
				else if(Scount<1840){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}
				else if(Scount<1900){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(Scount-1840));
					DrawRotaGraphF(CENTER_X, 100, 1.0, 0, gBack2[img_num], TRUE, FALSE);
				}		
			}
		}
		if(bDemo==true){
			char mes[16];
			for(int i=0;i<16;i++)	mes[i] = '\0';
			sprintf(mes, "DEMO PLAY");
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50+205.0*fabs(sin(Radian(Scount,TRUE))));
			SetDrawBright(255,255,150);
			draw_string(CENTER_X-50,CENTER_Y-8,16,mes);
			SetDrawBright(255,255,255);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		if(bShake==false){
			shake_x = 0;
			shake_y = 0;
		}
		else	bShake = false;
	}
       	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	if(GetSkip()){
		DrawGraph(0,0,gSystem[0],TRUE);
		DrawGraph(440,60,gSystem[1],TRUE);
		DrawGraph(440,85,gSystem[2],TRUE);
		DrawGraph(440,130,gSystem[3],TRUE);
		if(Player[0].chara<=2)	DrawGraph(440,155,gSystem[4],TRUE);
		else			DrawGraph(440,155,gSystem[18],TRUE);
	}
	
	if(Player[0].score2[0]<Player[0].score[0]){
		Player[0].score2[0]++;
		Player[0].score2[1] = 0;
	}
	if(Player[0].score2[1]<Player[0].score[1]){
		Player[0].score2[1] += 1;
		if(Player[0].score2[1]+10<Player[0].score[1])		Player[0].score2[1] += 10;
		if(Player[0].score2[1]+100<Player[0].score[1])		Player[0].score2[1] += 100;
		if(Player[0].score2[1]+1000<Player[0].score[1])		Player[0].score2[1] += 1000;
		if(Player[0].score2[1]+10000<Player[0].score[1])	Player[0].score2[1] += 10000;
		if(Player[0].score2[1]+100000<Player[0].score[1])	Player[0].score2[1] += 100000;
		if(Player[0].score2[1]+1000000<Player[0].score[1])	Player[0].score2[1] += 1000000;
	}
	if(Player[0].hiscore[0]<Player[0].score2[0]){
		Player[0].hiscore[0] = Player[0].score2[0];
		Player[0].hiscore[1] = Player[0].score2[1];
		Player[0].hi_cont_num = Player[0].cont_num;
	}
	else if(Player[0].hiscore[0]==Player[0].score2[0] && Player[0].hiscore[1]<Player[0].score2[1]){
		Player[0].hiscore[1] = Player[0].score2[1];
		Player[0].hi_cont_num = Player[0].cont_num;
	}
	if(Player[0].hiscore[0]==0){
		if(Player[0].hiscore[1]!=0)	draw_score(488+11*5, 62, Player[0].hiscore[1], 7, false);
		draw_score(488+11*12, 62, Player[0].hi_cont_num, 1, true);
	}
	else{
		draw_score(488, 62, Player[0].hiscore[0], 5, false);
		draw_score(488+11*5, 62, Player[0].hiscore[1], 7, true);
		draw_score(488+11*12, 62, Player[0].hi_cont_num, 1, true);
	}
	if(Player[0].score2[0]==0){
		if(Player[0].score2[1]!=0)	draw_score(488+11*5, 87, Player[0].score2[1], 7, false);
		draw_score(488+11*12, 87, Player[0].cont_num, 1, true);
	}
	else{
		draw_score(488, 87, Player[0].score2[0], 5, false);
		draw_score(488+11*5, 87, Player[0].score2[1], 7, true);
		draw_score(488+11*12, 87, Player[0].cont_num, 1, true);
	}
	for(int i=0;i<8;i++){
		if(i<Player[0].ship_num)	SetDrawBright(255,150,150);
		else				SetDrawBright(20,20,20);
		if(GetSkip())	DrawGraph(510+15*i,132,gSystem[5],TRUE);
	}
	int maxnum = Player[0].first_bomb;
	if(Player[0].level==IMPOSSIBLE)	maxnum = 1;
	if(Player[0].chara<=2)	maxnum = 8;
	for(int i=0;i<maxnum;i++){
		if(i<Player[0].bomb_num)	SetDrawBright(150,255,150);
		else				SetDrawBright(20,20,20);
		if(GetSkip())	DrawGraph(510+15*i,157,gSystem[5],TRUE);
	}
	SetDrawBright(255,255,255);
	//難易度描画↓
	int sx,sy;
	if(Player[0].level<=LUNATIC)	GetGraphSize(gSystem[6+Player[0].level],&sx,&sy);
	else 				GetGraphSize(gSystem[10+Player[0].level],&sx,&sy);
	if(Scount_all<180){
		if(Scount_all%10<5)	SetDrawBright(50,50,50);
		else			SetDrawBright(255,255,255);
		if(GetSkip()){
			if(Player[0].level<=LUNATIC)	DrawGraph(CENTER_X-sx/2,20,gSystem[6+Player[0].level],TRUE);
			else				DrawGraph(CENTER_X-sx/2,20,gSystem[10+Player[0].level],TRUE);
		}
	}
	else if(Scount_all<200){
		if(GetSkip()){
			if(Player[0].level<=LUNATIC)	DrawExtendGraph(CENTER_X-sx/2, 20+(float)(Scount_all-180)*sy/40.0, CENTER_X+sx/2, 20+sy-(float)(Scount_all-180)*sy/40.0, gSystem[6+Player[0].level], TRUE);
			else				DrawExtendGraph(CENTER_X-sx/2, 20+(float)(Scount_all-180)*sy/40.0, CENTER_X+sx/2, 20+sy-(float)(Scount_all-180)*sy/40.0, gSystem[10+Player[0].level], TRUE);
		}
	}
	else if(Scount_all<220){
		if(GetSkip()){
			if(Player[0].level<=LUNATIC)	DrawExtendGraph(535-sx/2, 20+(float)(220-Scount_all)*sy/40.0, 535+sx/2, 20+sy-(float)(220-Scount_all)*sy/40.0, gSystem[6+Player[0].level], TRUE);
			else				DrawExtendGraph(535-sx/2, 20+(float)(220-Scount_all)*sy/40.0, 535+sx/2, 20+sy-(float)(220-Scount_all)*sy/40.0, gSystem[10+Player[0].level], TRUE);
		}
	}
	else{
		if(GetSkip()){
			if(Player[0].level<=LUNATIC)	DrawGraph(535-sx/2,20,gSystem[6+Player[0].level],TRUE);
			else				DrawGraph(535-sx/2,20,gSystem[10+Player[0].level],TRUE);
		}
	}
	SetDrawBright(255,255,255);
		
	if(Scount_all<40){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-6.375*Scount_all);
		DrawBox(0,0,640,480,0,TRUE);
	}
	//難易度描画↑

	//エクステンド
	//イージー：１億・１０億・５０億・１００億
	//ノーマル：１０億・５０億・１００億・２００億
	//ハード：１０億・１００億・２００億・５００億
	//ルナティック：１０億・１００億・５００億・１０００億
	int level = Player[0].level;
	if(level==BABY)	level = EASY;
	else if(level==IMPOSSIBLE)	level = LUNATIC;
	bool flag = false;
	if(level==EASY){
		if(Player[0].before_score[0]<1 && Player[0].score2[0]>=1)		flag = true;
		else if(Player[0].before_score[0]<10 && Player[0].score2[0]>=10)	flag = true;
		else if(Player[0].before_score[0]<50 && Player[0].score2[0]>=50)	flag = true;
		else if(Player[0].before_score[0]<100 && Player[0].score2[0]>=100)	flag = true;
	}
	else if(level==NORMAL){
		if(Player[0].before_score[0]<10 && Player[0].score2[0]>=10)		flag = true;
		else if(Player[0].before_score[0]<50 && Player[0].score2[0]>=50)	flag = true;
		else if(Player[0].before_score[0]<100 && Player[0].score2[0]>=100)	flag = true;
		else if(Player[0].before_score[0]<200 && Player[0].score2[0]>=200)	flag = true;
	}
	else if(level==HARD){
		if(Player[0].before_score[0]<10 && Player[0].score2[0]>=10)		flag = true;
		else if(Player[0].before_score[0]<100 && Player[0].score2[0]>=100)	flag = true;
		else if(Player[0].before_score[0]<200 && Player[0].score2[0]>=200)	flag = true;
		else if(Player[0].before_score[0]<500 && Player[0].score2[0]>=500)	flag = true;
	}
	else if(level==LUNATIC){
		if(Player[0].before_score[0]<10 && Player[0].score2[0]>=10)		flag = true;
		else if(Player[0].before_score[0]<100 && Player[0].score2[0]>=100)	flag = true;
		else if(Player[0].before_score[0]<500 && Player[0].score2[0]>=500)	flag = true;
		else if(Player[0].before_score[0]<1000 && Player[0].score2[0]>=1000)	flag = true;
	}
	if(flag==true && Player[0].level!=IMPOSSIBLE){
		if(Player[0].ship_num<8)	Player[0].ship_num++;
		else if(Player[0].bomb_num<8)	Player[0].bomb_num++;
		PlaySound(30);
		Ecount = 1;
	}
	
	if(Ecount>0){
		int gx,gy;
		GetGraphSize(gSystem[11], &gx, &gy);
		float y = 40;
		if(GetSkip()){
			if(Ecount<20){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawExtendGraphF(CENTER_X-gx/2.0, y-gy/2.0/20.0*Ecount, CENTER_X+gx/2.0, y+gy/2.0/20.0*Ecount, gSystem[11], TRUE);
			}
			else if(Ecount<120){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawExtendGraphF(CENTER_X-gx/2.0, y-gy/2.0, CENTER_X+gx/2.0, y+gy/2.0, gSystem[11], TRUE);
			}
			else if(Ecount<170){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(170-Ecount));
				DrawExtendGraphF(CENTER_X-gx/2.0, y-gy/2.0, CENTER_X+gx/2.0, y+gy/2.0, gSystem[11], TRUE);
			}
			else	Ecount = -1;
		}
		Ecount++;
	}

	Player[0].before_score[0] = Player[0].score2[0];
	Player[0].before_score[1] = Player[0].score2[1];

	//↓ステージクリア
	if(Ccount>0){
		if(Ccount==1){
			GetDrawScreenGraph(10,10,430,470,gPause);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawGraph(10,10,gPause,TRUE);
		if(Ccount<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.0*Ccount);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(10,10,430,470,0,TRUE);
		if(Ccount>=60){
			int total_hit = Player[0].total_hit;
			int max_hit = SScore.max_hit[Player[0].stage-1];
			if(total_hit>99999)	total_hit = 99999;
			if(max_hit>99999)	max_hit = 99999;
			int special_bonus = 0;
			if(MissN==0 && BombN==0)	special_bonus = 20000000*(Player[0].stage);
			else if(MissN==0)		special_bonus = 10000000*(Player[0].stage);
			unsigned int total = total_hit*100 + max_hit*10000 + special_bonus;
			float bai = 1.0;
			if(Player[0].level==EASY)		bai = 0.5;
			else if(Player[0].level==NORMAL)	bai = 1.0;
			else if(Player[0].level==HARD)		bai = 1.5;
			else if(Player[0].level==LUNATIC)	bai = 2.0;
			else if(Player[0].level==BABY)		bai = 0.5;
			else if(Player[0].level==IMPOSSIBLE)	bai = 2.0;
			else if(Player[0].level==EXTRA)		bai = 3.0;
			total *= bai;
			total /= 10;
			total *= 10;
			if(Ccount==60){
				add_score(total);
				GetData2();
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			float x = 50;
			float y = 100;
			char message[6][128];
			for(int i=0;i<6;i++){
				for(int j=0;j<128;j++){
					message[i][j] = '\0';
				}
			}
			if(Player[0].level==EXTRA)		sprintf(message[0], "EXTRA  CLEAR!!");
			else if(Player[0].stage==STAGE_NUM)	sprintf(message[0], "ALL  CLEAR!!");
			else					sprintf(message[0], "STAGE %d  CLEAR!!", Player[0].stage);
			sprintf(message[1], "HIT BONUS  %d*100", total_hit);
			sprintf(message[2], "MAXHIT BONUS  %d*10000", max_hit);
			if(special_bonus==20000000*(Player[0].stage))		sprintf(message[3], "NOMISS NOBOMB BONUS!!  %d", special_bonus);
			else if(special_bonus==10000000*(Player[0].stage))	sprintf(message[3], "NOMISS BONUS!  %d", special_bonus);
			sprintf(message[4], "LEVEL BONUS  *%.1f", bai);
			sprintf(message[5], "TOTAL  %d", total);
			for(int i=0;i<6;i++){
				if(i==0){
					SetDrawBright(255,255,100);
					y = 100;
				}
				else if(i<3){
					SetDrawBright(255,255,255);
					y = 120 + 20*i;
				}
				else if(i==3){
					SetDrawBright(255,100,100);
					y = 130 + 20*i;
				}
				else if(i==4){
					SetDrawBright(255,255,255);
					y = 140 + 20*i;
				}
				else if(i==5){
					SetDrawBright(200,255,200);
					y = 150 + 20*i;
				}
				draw_string(x, y, 128, message[i]);
			}
		}
		SetDrawBright(255,255,255);
		
		if(Ccount<180)	MuChangeVolumeBgm(255*SAVE.Bgm*0.01*(float)(180-Ccount)/180.0);
		else if(Ccount==180){
			MuStopBgm();
			MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
		}
		
		//↓オールクリア
		if(Ccount2>0){
			if(Ccount2<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ccount2);
			else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);			
			if(Ccount2==180){
				DeleteGraph(gPause);
				gPause = MakeGraph(420,460);
				if(replay_play==false){
					GetData();
					//タイトルに戻るやインポッシブル後にも、同じように初期化してる部分ある
					scene = NAMEENTRY;
					ne_count = 0;
					ne_count2 = 0;
					ne_count3 = 0;
					ne_count4 = 0;
					ne_scene = 0;
					ne_carsol = 0;
					ne_carsol2 = 0;
				}
				else{
					MuPlayBgm(0);
					scene = TITLE;
				}
			}
			Ccount2++;
		}
		//↑オールクリア
		else if(Ccount>=180 && Player[0].score[0]==Player[0].score2[0] && Player[0].score[1]==Player[0].score2[1]){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			if(shot==1 || pause==1){
				SReplay.element_num++;//次のステージの開始カウントに進む
				if((Player[0].level<=IMPOSSIBLE && Player[0].stage==3) || title_carsol==2 || (SReplay.s_exist[Player[0].stage]==false && replay_play==true)){
					Ccount2 = 1;
				}
				else if(Player[0].level==EXTRA && Player[0].stage==1){
					Ccount2 = 1;
				}
				else{
					if(replay_play==false)	PReset();
					else{
						int sca = Scount_all;
						PLoad();
						Scount_all = sca;
					}
					Ccount3 = 60;//次のステージへ
					return;
				}
			}
		}		
		
		Ccount++;
	}
	//↑ステージクリア
	if(bDemo==true && Dcount==0){
		int up,down,left,right,shot,bomb,slow,skip,pause;
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause, false);
		bool flag = false;
		if(Player[0].stage==1 && Scount==4500)		flag = true;
		else if(Player[0].stage==2 && Scount==5100)	flag = true;
		else if(Player[0].stage==3 && Scount==11100)	flag = true;
		else if(pause>0)		flag = true;
		if(flag==true){
			Dcount = 1;
		}
	}
	if(Dcount>0){
		MuChangeVolumeBgm(255*SAVE.Bgm*0.01*(float)(120-Dcount)/120.0);
		MuChangeVolumeSound(255*SAVE.Sound*0.01*(float)(120-Dcount)/120.0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Dcount);
		DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(Dcount==120){
			MuPlayBgm(0);
			MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
			MuChangeVolumeSound(255*SAVE.Sound*0.01);
			for(int i=0;i<SOUND_NUM;i++){
				SoundFlag[i] = 0;
			}
			Mcount3 = 0;
			scene = TITLE;
		}
		Dcount++;
	}
	if(Pcount==0 && Ccount==0){
		Scount_all++;
		Scount++;
		
		int up,down,left,right,shot,bomb,slow,skip,pause;
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
	        if(bDemo==false && Scount>=90 && Ccount==0 && (pause==1 || Player[0].ship_num<0)){
			if(replay_play==true&&Player[0].ship_num<0){
				MuPlayBgm(0);
				scene = TITLE;
			}
			else{			
				BEup = Eup;
				BEdown = Edown;
				BEleft = Eleft;
				BEright = Eright;
				BEshot = Eshot;
				BEbomb = Ebomb;
				BEslow = Eslow;
				BEskip = Eskip;
				MuPauseBgm();
				if(Player[0].ship_num>=0)	PlaySound(5);
				GetDrawScreenGraph(10,10,430,470,gPause);
				Pcarsol[0] = 0;
				Pcarsol[1] = 0;
				Pscene = 0;
				Pcount2 = 0;
				Pcount3 = 0;
				Pcount++;
				PNowcount = GetNowCount();
			}
		}
	}
	else if(Pscene==3){
 		if(Pcount3<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Pcount3);
 		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawBox(0,0,640,480,0,TRUE);
		if(Pcount3==30){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int size = GetDrawStringWidth(nowloading,14);
			DrawString(640-size,480-12,nowloading,GetColor(255,255,255));			
			ScreenFlip();
			MuStopBgm();
			DeleteGraph(gPause);
			DeleteGraph(gPause2);
			gPause = MakeGraph(420,460);
			gPause2 = MakeGraph(84,92);
			if(Pcarsol[0]==1){
				if(Player[0].ship_num<0){
					MuStopBgm();
					GetData2();
					GetData();
					//オールクリア後やインポッシブル後にも、同じように初期化してる部分ある
					scene = NAMEENTRY;
					ne_count = 0;
					ne_count2 = 0;
					ne_count3 = 0;
					ne_count4 = 0;
					ne_scene = 0;
					ne_carsol = 0;
					ne_carsol2 = 0;
				}
				else{
					MuPlayBgm(0);
					scene = TITLE;
				}
			}
			else{
				for(int i=0;i<PLAYER_NUM;i++){
					Player[i].stage = SScore.start_stage-1;
				}
				PLoad();
			}
		}
		Pcount3++;
	}
	
	return;
}

void add_score(unsigned int add){
	add /= 10;
	int n = add / 10000000;
	add -= n * 10000000;
	Player[0].score[1] += add;
	SScore.stage_allscore[Player[0].stage-1][1] += add;
	SScore.stage_score[Player[0].stage-1][NowPart][1] += add;
	if(Player[0].score[1]>=10000000){
		Player[0].score[0]++;
		Player[0].score[1] -= 10000000;
	}
	if(SScore.stage_allscore[Player[0].stage-1][1]>=10000000){
		SScore.stage_allscore[Player[0].stage-1][0]++;
		SScore.stage_allscore[Player[0].stage-1][1] -= 10000000;
	}
	if(SScore.stage_score[Player[0].stage-1][NowPart][1]>=10000000){
		SScore.stage_score[Player[0].stage-1][NowPart][0]++;
		SScore.stage_score[Player[0].stage-1][NowPart][1] -= 10000000;
	}
	if(Player[0].score[0]+n<100000){
		Player[0].score[0] += n;
	}
	else{
		Player[0].score[0] = 99999;
		Player[0].score[1] = 9999999;
	}
	if(SScore.stage_allscore[Player[0].stage-1][0]+n<100000){
		SScore.stage_allscore[Player[0].stage-1][0] += n;
	}
	else{
		SScore.stage_allscore[Player[0].stage-1][0] = 99999;
		SScore.stage_allscore[Player[0].stage-1][1] = 9999999;
	}
	if(SScore.stage_score[Player[0].stage-1][NowPart][0]+n<100000){
		SScore.stage_score[Player[0].stage-1][NowPart][0] += n;
	}
	else{
		SScore.stage_score[Player[0].stage-1][NowPart][0] = 99999;
		SScore.stage_score[Player[0].stage-1][NowPart][1] = 9999999;
	}
	return;
}

void add_gage(int add){
	if(Player[0].level==IMPOSSIBLE)	add = (float)add * 7.0;
	if(Player[0].stage==0)		add = (float)add * 2.0;
	if(Player[0].hyper_gage==MAX_GAGE && add>=0){
	
	}
	else{
		if(Player[0].chara>=3 && Player[0].stress_gage>=MAJIGIRE && add>0)	add *= 2.0;
		else if(Player[0].chara>=3 && add>0)	add = add/2 + 1;
		if(add>=0){
			if(Player[0].hyper_gage+add<MAX_GAGE){
				Player[0].hyper_gage += add;
			}
			else{
				Player[0].hyper_gage = MAX_GAGE;
				if(Player[0].chara<=2 || (Player[0].bomb_num==0&&Player[0].hyper_count==0)){
					PlaySound(9);
					for(int i=0;i<6;i++){
						float angle = Radian(60*i,TRUE);
						EfMake(Player[0].x+20*cos(angle), Player[0].y+20*sin(angle), 2, 10, 60*i);
					}
				}
				if(Player[0].chara>=3 && Player[0].hyper_count==0){
					//PDrawにも同じ処理
					if((Player[0].bomb_num<3&&Player[0].level!=IMPOSSIBLE) || Player[0].bomb_num<1){
						PlaySound(26);
						Player[0].bomb_num++;
						Player[0].hyper_gage = 0;
					}		
				}
			}
		}
		else{
			if(Player[0].hyper_gage+add>0){
				Player[0].hyper_gage += add;
			}
			else{
				Player[0].hyper_gage = 0;
			}
		}
	}
	
	return;
}

void add_stress_gage(int add){
	if(Player[0].chara<=2)	return;
	if(Player[0].stress_gage==MAX_STRESS_GAGE && add>=0){
	
	}
	else{
		if(add>=0){
			if(Player[0].stress_gage+add<MAX_STRESS_GAGE){
				Player[0].stress_gage += add;
			}
			else{
				Player[0].stress_gage = MAX_STRESS_GAGE;
			}
		}
		else{
			if(Player[0].stress_gage+add>0){
				Player[0].stress_gage += add;
			}
			else{
				Player[0].stress_gage = 0;
			}
		}
	}
	
	return;
}

void add_soten(int add){
	if(add>=0){
		float bai = 1.0;
		if((Player[0].chara<=2 && Player[0].hyper_gage==MAX_GAGE) || (Player[0].chara>=3 && Player[0].stress_gage>=MAJIGIRE)){
			if(Player[0].chara<=2 || Player[0].hyper_count==0){
				if(Player[0].hit<500)		bai = 1.5;
				else if(Player[0].hit<1000)	bai = 2.0;
				else if(Player[0].hit<2000)	bai = 2.5;
				else if(Player[0].hit<3000)	bai = 3.0;
				else if(Player[0].hit<4000)	bai = 3.5;
				else if(Player[0].hit<5000)	bai = 4.0;
				else if(Player[0].hit<7500)	bai = 5.0;
				else if(Player[0].hit<10000)	bai = 6.0;
				else if(Player[0].hit<12500)	bai = 7.0;
				else if(Player[0].hit<15000)	bai = 8.0;
				else if(Player[0].hit<17500)	bai = 9.0;
				else if(Player[0].hit<20000)	bai = 10.0;
				else				bai = 11.0;
			}
		}
		add *= bai;
		if(Player[0].soten+add<99999999){
			Player[0].soten += add;
		}
		else{
			Player[0].soten = 99999999;
		}
	}
	else{
		if(Player[0].soten+add>0){
			Player[0].soten += add;
		}
		else{
			Player[0].soten = 0;
		}
	}
	if(Player[0].soten>SScore.max_soten[Player[0].stage-1]){
		SScore.max_soten[Player[0].stage-1] = Player[0].soten;
		if(Player[0].soten>SScore.max_soten[STAGE_NUM])	SScore.max_soten[STAGE_NUM] = Player[0].soten;	
	}
	
	return;
}

void PDraw(){
	for(int i=0;i<PLAYER_NUM;i++){
		PMove(i);
		if(Player[i].miss_count>0){
			Player[i].miss_count--;
			if(Player[i].miss_count==0){
				if(Player[i].hit>0){
					if(Player[i].hit2==0){
						Player[i].hit2 = Player[i].hit;
						Player[i].soten2 = Player[i].soten;
						Player[i].hit2_count = 120;
					}
					Player[i].hit = 0;
					Player[i].soten = 0;
				}
				if(Player[i].chara<=2 && Player[i].bomb_num>0){
					Player[i].bomb_num--;
					SScore.bomb_num++;
					BombN++;
					if(SpBackCount>60){
						SpBonus = 0;
						NmBonus = 0;
					}
					Player[i].muteki_count = 120;
					PlaySound(11);
					PBMake(Player[i].x, Player[i].y, 0.0, 6, 1, true);
					for(int a=0;a<12;a++)	PBMake(Player[i].x, Player[i].y, 30.0*a, 7, 1, true);
				}
				else{
					SScore.miss_num++;
					MissN++;
					if(SpBackCount>60){
						SpBonus = 0;
						NmBonus = 0;
					}
					Player[i].spcard = 0;
					Player[i].death_count = 100;
					Player[i].hyper_count = 0;
					Player[i].hyper_rank -= 3;
					if(Player[i].hyper_rank<0)	Player[i].hyper_rank = 0;
					Player[i].shot = 0;
					add_stress_gage(-MAX_STRESS_GAGE);
				}
			}
		}
		if(Player[i].death_count>0){
			if(Player[i].death_count==100){
				EfMake(Player[i].x, Player[i].y, 5, 5);
				Player[i].flash = 0;
				for(list<ITEMDATA>::iterator it=Item.begin(); it!=Item.end(); ++it){
					if((*it).pattern!=3)	(*it).pattern = 0;
				}
			}
			else if(Player[i].death_count>60){}
			else if(Player[i].death_count==60){
				Player[i].muteki_count = 300;
				if(Player[i].stage!=0)	Player[i].ship_num--;
				if(Player[i].ship_num<0){
					if(Player[i].level==IMPOSSIBLE){
						MuStopBgm();
						GetData2();
						GetData();
						//オールクリア後や何かにも、同じように初期化してる部分ある
						scene = NAMEENTRY;
						ne_count = 0;
						ne_count2 = 0;
						ne_count3 = 0;
						ne_count4 = 0;
						ne_scene = 0;
						ne_carsol = 0;
						ne_carsol2 = 0;
					}
				}
				else{
					if(Player[i].chara<=2){
						Player[i].bomb_num = Player[i].first_bomb;
						add_gage(MAX_GAGE);
					}
					else{
						int num = Player[i].bomb_num;
						Player[i].bomb_num = Player[i].first_bomb;
						if(Player[i].bomb_num>Player[i].first_bomb)	Player[i].bomb_num = Player[i].first_bomb;
						if(num!=Player[i].bomb_num)	PlaySound(26);
					}
				}
			}
			else{
				Player[i].flash = 255;
			}
			if(Player[i].death_count>0){
				for(list<ESHOTDATA>::iterator eit=EShot.begin(); eit!=EShot.end(); ++eit){
					float sx = Player[i].x - (*eit).x;
					float sy = Player[i].y - (*eit).y;
					float sq = sqrt(sx*sx+sy*sy);
					float ha = 16.0*(100-Player[i].death_count);
					if(sq<ha){
						EfMake((*eit).x, (*eit).y, (*eit).img, 9);
						eit = EShot.erase(eit);
						eit--;
						continue;			
					}
				}
				if(Player[i].death_count<60)	SESDelete(5);
			}
			if(Player[i].chara==0)	Player[i].img_num = 0;
			else			Player[i].img_num = 7 + 3*(Player[i].chara-1);
			Player[i].x = CENTER_X;
			Player[i].y = 420 + 2.0*Player[i].death_count;
			Player[i].death_count--;
		}
		SetDrawBright(255,255,255);
		if(Player[i].slow_count>0){
			if(PLaser.size()==0)	SetDrawBright(255,255,255);
			else{
				if(Player[i].hyper_count==0){
					if(Player[i].chara>=3 && Player[i].stress_gage>=MAJIGIRE)	SetDrawBright(255,150,150);
					else	SetDrawBright(255,200,150);
				}
				else{
					if(Player[i].chara==0)		SetDrawBright(255,100,255);
					else if(Player[i].chara==1)	SetDrawBright(150,150,255);
					else if(Player[i].chara==2)	SetDrawBright(100,100,255);
					else if(Player[i].chara==3)	SetDrawBright(255,100,100);
					else if(Player[i].chara==4)	SetDrawBright(255,255,100);
					else if(Player[i].chara==5)	SetDrawBright(100,255,100);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,7.5*Player[i].slow_count);
			if(GetSkip()){
				if(Player[i].hyper_count==0)	DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, 0.030*Player[i].slow_count, Radian(4*Player[i].count,TRUE), gEffect[1], TRUE, FALSE);
				else				DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, 0.050*Player[i].slow_count, Radian(4*Player[i].count,TRUE), gEffect[1], TRUE, FALSE);
			}
			
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Player[i].slow_count);
			SetDrawBright(255,255,255);
			if(GetSkip()){
				DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, 3.0-0.1*Player[i].slow_count, Radian(2*Player[i].count,TRUE), gPlayer[5], TRUE, FALSE);
				DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, 3.0-0.1*Player[i].slow_count, Radian(-2*Player[i].count,TRUE), gPlayer[6], TRUE, FALSE);
			}
		}
		
		if(Player[i].chara>=3 && bTalk==false){
			if(Player[i].graze_count==0)	add_stress_gage(-MAX_STRESS_GAGE/1000);
			if(Player[i].graze_count>0)	Player[i].graze_count--;
		}
		if(Player[i].chara>=3 && Player[i].hyper_gage==MAX_GAGE && Player[0].hyper_count==0){
 			//add_gageにも同じ処理
			if(Player[0].bomb_num==0){
				PlaySound(9);
				for(int i=0;i<6;i++){
					float angle = Radian(60*i,TRUE);
					EfMake(Player[0].x+20*cos(angle), Player[0].y+20*sin(angle), 2, 10, 60*i);
				}
			}
			if((Player[0].bomb_num<3&&Player[0].level!=IMPOSSIBLE) || Player[0].bomb_num<1){
				PlaySound(26);
				Player[i].bomb_num++;
				Player[i].hyper_gage = 0;
			}		
		}
		if(Player[i].hyper_count>0){
			/*
			if(SpBackCount>60){
				SpBonus = 0;
				NmBonus = 0;
				Player[i].spcard = 0;
			}
			*/
			SetDrawBlendMode(DX_BLENDMODE_ADD,150);
			float large = 0.0;
			if(Player[i].hyper_count>9800)	large = 0.01 * (10000-Player[i].hyper_count);
			else				large = 0.0002 * Player[i].hyper_count;
			int img_num = 0;
			if(Player[i].chara>0)	img_num = 12 + Player[i].chara;
			if(GetSkip())	DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, large, Radian(12*Player[i].count,TRUE), gEffect[img_num], TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			int size = 18*draw_hit(0,0,Player[i].hyper_count,2);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
			SetDrawBright(255,255,255);
			draw_hit(Player[i].x-size/2,Player[i].y+20,Player[i].hyper_count,2);
			if(Player[i].hyper_count2>0){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
				size = 18*draw_hit(0,0,Player[i].hyper_rank,3);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
				if(Player[i].hyper_count2<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,5*Player[i].hyper_count2);
				draw_hit(Player[i].x-size/2,Player[i].y-50,Player[i].hyper_rank,3);
				Player[i].hyper_count2--;		
			}
			if(bTalk==false){
				bool bEfOn = false;
				if(Player[i].chara<=2){
					Player[i].hyper_count -= 11;
					if(Player[i].hyper_count>11*30 && Player[i].hyper_count<11*90)	bEfOn = true;
				}
				else{
					Player[i].hyper_count -= 22;
					if(Player[i].hyper_count>22*30 && Player[i].hyper_count<22*90)	bEfOn = true;
				}
				if(bEfOn==true){
					EfMake(Player[0].x, Player[0].y, 9, 16, 0, get_rand(360));
					EfMake(Player[0].x, Player[0].y, 9, 17, 0, get_rand(360));
				}
				if(Player[i].hyper_count<0){
					EfMake(Player[0].x, Player[0].y, 1, 18);
					SESDelete(1, Player[i].x, Player[i].y);
					Player[i].hit_gage = MAX_HIT_GAGE;
					Player[i].hyper_count = 0;
					Player[i].muteki_count = 120;
				}
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Player[i].flash);
		if(Player[i].muteki_count>0){
			if(Player[i].muteki_count%6<4)	SetDrawBright(50,50,255);
			Player[i].muteki_count--;
		}
		if(GetSkip())	DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, Player[i].large, Player[i].angle, gPlayer[Player[i].img_num], TRUE, FALSE);

		SetDrawBright(255,255,255);
		if(Player[i].slow_count>0){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Player[i].slow_count);
			if(GetSkip())	DrawRotaGraphF(Player[i].x+shake_x, Player[i].y+shake_y, 1.0, Radian(3*Player[i].count,TRUE), gPlayer[4], TRUE, FALSE);
		}
		if(Player[i].hit_gage>0 && Player[i].hit>0){
			if(bTalk==false){
				if(Boss.size()==0)	Player[i].hit_gage -= 7;
				else{
					Player[i].hit_gage -= 1;
				}
				if(Player[i].hit_gage<0)	Player[i].hit_gage = 0;
				if(Player[i].hit_gage==0){
					if(Player[i].hyper_gage>0 && (Player[i].chara>=3 || Player[i].hyper_gage<MAX_GAGE) && Player[i].hyper_count==0){
						if(Boss.size()==0){
							if(Player[i].rate_soten==0){
								if(Player[i].hit>6)	Player[i].rate_soten = Player[i].soten / (Player[i].hit/7);
							}
							if(Player[i].hit>7)	Player[i].hit -= 7;
							else			Player[i].hit = 1;
							add_soten(-Player[i].rate_soten);
							add_gage(-420);
							Player[i].hit_gage = 7;
						}
						else{
							if(Player[i].rate_soten==0){
								if(Player[i].hit>0)	Player[i].rate_soten = Player[i].soten / Player[i].hit;
							}
							if(Player[i].hit>1)	Player[i].hit -= 1;
							else			Player[i].hit = 1;
							add_soten(-Player[i].rate_soten);
							add_gage(-60);
							Player[i].hit_gage = 1;
						}
					}
					if(Player[i].hyper_gage==0 || (Player[i].chara<=2&&Player[i].hyper_gage==MAX_GAGE) || Player[i].hit==1 || Player[i].hyper_count>0){
						if(Player[i].hit2==0){
							Player[i].hit2 = Player[i].hit;
							Player[i].soten2 = Player[i].soten;
							Player[i].hit2_count = 120;
						}
						Player[i].hit = 0;
						Player[i].soten = 0;
					}
				}
				else{
					Player[i].rate_soten = 0;
				}
			}
		}
		else	Player[i].rate_soten = 0;
		if(Player[i].hit==0)	Player[i].hit_gage = 0;

		if(Player[i].hit>SScore.max_hit[Player[i].stage-1]){
			SScore.max_hit[Player[i].stage-1] = Player[i].hit;
			if(Player[i].hit>SScore.max_hit[STAGE_NUM])	SScore.max_hit[STAGE_NUM] = Player[i].hit;	
		}
		
		if(Player[i].ship_num>8)	Player[i].ship_num = 8;
		if(Player[i].chara<=2 && Player[i].bomb_num>8)	Player[i].bomb_num = 8;
		if(Player[i].chara>=3 && Player[i].bomb_num>Player[i].first_bomb)	Player[i].bomb_num = Player[i].first_bomb;

		Player[i].count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void PMove(int i){
	int up,down,left,right,shot,bomb,slow,skip,pause;
	if(replay_play==false){
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
		RMain();
	}
	else{
		bomb = Player[i].bomb;
		RMain(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause,true);
		Player[i].bomb = bomb;
	}
	
	if(Player[i].miss_count==0 && Player[i].death_count==0){
		if(bSun==true){
			list<BOSSDATA>::iterator bit = Boss.begin();
			float sx = (*bit).x - Player[i].x;
			float sy = (*bit).y - Player[i].y;
			float d = sqrt(sx*sx+sy*sy);
			float sp = 0;
			switch((*bit).i_hanyou[0]){
				case 0:	sp = 0.5;	break;	
				case 1:	sp = 0.7;	break;	
				case 2:	sp = 1.0;	break;	
				case 3:	sp = 1.3;	break;	
			}
			if(d!=0){			
				Player[i].x += sp*sx/d;
				Player[i].y += sp*sy/d;
			}
		}
		float speed = Player[i].speed;
		if(slow>0){
			if(Player[i].slow_count<20)	Player[i].slow_count++;
			if(Player[i].chara%3==0)	speed = 2.0;
			else if(Player[i].chara%3==1)	speed = 3.0;
			else if(Player[i].chara%3==2)	speed = 1.5;
		}
		else{
			if(Player[i].slow_count>0)	Player[i].slow_count--;
		}
       	
		float root = sqrt(2.0);
		if(up>0&&left>0){
			Player[i].x -= speed / root;
			Player[i].y -= speed / root;
		}
		else if(down>0&&left>0){
			Player[i].x -= speed / root;
			Player[i].y += speed / root;
		}
		else if(up>0&&right>0){
			Player[i].x += speed / root;
			Player[i].y -= speed / root;
		}
		else if(down>0&&right>0){
			Player[i].x += speed / root;
			Player[i].y += speed / root;
		}
		else if(up>0)	Player[i].y -= speed;
		else if(down>0)	Player[i].y += speed;
		else if(left>0)	Player[i].x -= speed;
		else if(right>0)Player[i].x += speed;
       	
		if(Player[i].chara==0){
			if(left>0)	Player[i].img_num = 1;
			else if(right>0)Player[i].img_num = 2;
			else		Player[i].img_num = 0;		
		}
		else{
			if(left>0)	Player[i].img_num = 8+3*(Player[i].chara-1);
			else if(right>0)Player[i].img_num = 9+3*(Player[i].chara-1);
			else		Player[i].img_num = 7+3*(Player[i].chara-1);		
		}       	

		if(Player[i].x<24)	Player[i].x = 24;
		if(Player[i].y<31)	Player[i].y = 31;
		if(Player[i].x>416)	Player[i].x = 416;
		if(Player[i].y>446)	Player[i].y = 446;
		
		if(shot>0 && bTalk==false){
			if(Player[i].shot==0)	Player[i].shot = 24;
		}
		if(Player[i].shot>0){
			if(bTalk==false){
				if(slow==0 && Player[i].slow_count<10){
					if(Player[i].shot%4==0){
						for(int a=0;a<4;a++){
							if(Player[i].chara%3==2)	PSMake(Player[i].x-30+20*a, Player[i].y, 20.0, -90.0, 0, 0, 3);
							else				PSMake(Player[i].x-30+20*a, Player[i].y, 20.0, -90.0, 0, 0, 1);
						}
					}
					if(Player[i].chara%3==0){	
						if(Player[i].shot%2==0){
							PlaySound(4);
							if(Player[i].chara>=3 && Player[i].stress_gage>=MAJIGIRE){
								for(int a=0;a<4;a++)	PSMake(Option[a].x, Option[a].y, 30.0, -95.0+abs(20-Player[i].count%40), 1, 0, 1);
								for(int a=4;a<8;a++)	PSMake(Option[a].x, Option[a].y, 30.0, 255.0+abs(20-Player[i].count%40), 1, 0, 1);
							}
							else{
								for(int a=0;a<4;a++)	PSMake(Option[a].x, Option[a].y, 30.0, -85.0, 1, 0, 1);
								for(int a=4;a<8;a++)	PSMake(Option[a].x, Option[a].y, 30.0, 265.0, 1, 0, 1);
							}
						}
					}
					else if(Player[i].chara%3==1){	
						if(Player[i].shot%2==0){
							PlaySound(4);
							if(Player[i].chara>=3 && Player[i].stress_gage>=MAJIGIRE){
								for(int a=0;a<8;a++)	PSMake(Option[a].x, Option[a].y, 30.0, -100.0+abs(20-Player[i].count%40), 1, 0, 2);
							}
							else{
								for(int a=0;a<8;a++)	PSMake(Option[a].x, Option[a].y, 30.0, -90.0, 1, 0, 2);
							}
						}
					}
					else if(Player[i].chara%3==2){	
						if(Player[i].shot%3==0){
							PlaySound(4);
							if(Player[i].chara>=3 && Player[i].stress_gage>=MAJIGIRE){
								PSMake(Option[0].x, Option[0].y, 30.0, -110.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[4].x, Option[4].y, 30.0, -90.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[1].x, Option[1].y, 30.0, -85.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[2].x, Option[2].y, 30.0, -85.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[3].x, Option[3].y, 30.0, -85.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[5].x, Option[5].y, 30.0, -115.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[6].x, Option[6].y, 30.0, -115.0+abs(20-Player[i].count%40), 1, 0, 3);
								PSMake(Option[7].x, Option[7].y, 30.0, -115.0+abs(20-Player[i].count%40), 1, 0, 3);
							}
							else{
								PSMake(Option[0].x, Option[0].y, 30.0, -100.0, 1, 0, 3);
								PSMake(Option[4].x, Option[4].y, 30.0, -80.0, 1, 0, 3);
								PSMake(Option[1].x, Option[1].y, 30.0, -75.0, 1, 0, 3);
								PSMake(Option[2].x, Option[2].y, 30.0, -75.0, 1, 0, 3);
								PSMake(Option[3].x, Option[3].y, 30.0, -75.0, 1, 0, 3);
								PSMake(Option[5].x, Option[5].y, 30.0, -105.0, 1, 0, 3);
								PSMake(Option[6].x, Option[6].y, 30.0, -105.0, 1, 0, 3);
								PSMake(Option[7].x, Option[7].y, 30.0, -105.0, 1, 0, 3);
							}
						}
					}
				}
				else{
					if(Player[i].shot>0){
						PlaySound(4);
						if(Player[i].chara%3==0)	PLMake(2,5);
						else if(Player[i].chara%3==1)	PLMake(2,6);
						else if(Player[i].chara%3==2)	PLMake(2,4);
					}
				}
			}
			Player[i].shot--;
		}
	}
	if(Player[i].death_count==0 && bomb==1 && bTalk==false){
		/*
		if(Player[i].chara>=3 && Player[i].hyper_count>0 && Player[i].muteki_count<60){
			Player[i].hyper_count = 1;
		}
		else*/ 
		if(Player[i].hyper_count==0 && Bomb.size()==0 &&
		   ((Player[i].chara<=2 && Player[i].hyper_gage==MAX_GAGE) ||
		   (Player[i].chara>=3 && Player[i].bomb_num>0))){
			/*
			if(SpBackCount>60){
				SpBonus = 0;
				NmBonus = 0;
			}
			*/
			SScore.hyper_num++;
			if(Player[i].chara<=2){
				Player[i].hyper_gage = 0;
				if(Player[i].hyper_rank<10)	Player[i].hyper_rank++;
			}
			else{
				Player[i].bomb_num--;
				if(Player[i].hyper_rank<20)	Player[i].hyper_rank++;
			}
			Player[i].hit_gage = MAX_HIT_GAGE;
			Player[i].hyper_count = 10000;
			Player[i].hyper_count2 = 90;
			Player[i].muteki_count = 120;
			PlaySound(12);
			PlaySound(13);
			Player[i].miss_count = 0;
		}
		else if(Player[i].chara<=2 && Player[i].bomb_num>0 && Bomb.size()==0){
			if(Player[i].hit>0){
				if(Player[i].hit2==0){
					Player[i].hit2 = Player[i].hit;
					Player[i].soten2 = Player[i].soten;
					Player[i].hit2_count = 120;
				}
				Player[i].hit = 0;
				Player[i].soten = 0;
			}
			Player[i].bomb_num--;
			if(SpBackCount>60){
				SpBonus = 0;
				NmBonus = 0;
			}
			SScore.bomb_num++;
			BombN++;
			Player[i].muteki_count = 300;
			PlaySound(10);
			PlaySound(11);
			float x = Player[i].x;
			float y = Player[i].y;
			if(x>CENTER_X+100)	x = CENTER_X+100;
			if(x<CENTER_X-100)	x = CENTER_X-100;
			if(y>CENTER_Y+50)	y = CENTER_Y+50;
			if(y<CENTER_Y-150)	y = CENTER_Y-150;
			PBMake(x, y, 0.0, 6, 2);
			for(int a=0;a<12;a++)	PBMake(x, y, 30.0*a, 7, 3);
			Player[i].miss_count = 0;
			Player[0].hyper_rank -= 2;
			if(Player[i].hyper_rank<0)	Player[i].hyper_rank = 0;
		}
	}
	
	return;
}

void ODraw(){
	for(int i=0;i<OPTION_NUM;i++){
		OMove(i);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Option[i].flash);
		if(GetSkip())	DrawRotaGraphF(Option[i].x+shake_x, Option[i].y+shake_y, Option[i].large, Option[i].angle, gPlayer[3], TRUE, FALSE);

		Option[i].count++;
	}
	
	return;
}

void OMove(int i){
	if(Player[0].chara%3==0){
		float max_ro;
		if(i==0||i==4)		max_ro = 60.0;
		else if(i==1||i==5)	max_ro = 40.0;
		else if(i==2||i==6)	max_ro = 40.0;
		else if(i==3||i==7)	max_ro = 30.0;
		if(Player[0].slow_count<10)	max_ro = max_ro*(float)(10-Player[0].slow_count)/10.0;
		else				max_ro = 0;
		if(i==0)	Option[i].ro_angle = 10.0;
		else if(i==1)	Option[i].ro_angle = 60.0;
		else if(i==2)	Option[i].ro_angle = -10.0;
		else if(i==3)	Option[i].ro_angle = -70.0;
		else if(i==4)	Option[i].ro_angle = 170.0;
		else if(i==5)	Option[i].ro_angle = 120.0;
		else if(i==6)	Option[i].ro_angle = 190.0;
		else if(i==7)	Option[i].ro_angle = 250.0;
		if(Option[i].count<10)	Option[i].ro = Option[i].count*max_ro/10;
		else			Option[i].ro = max_ro;
		Option[i].x = Player[0].x + Option[i].ro * cos(Radian(Option[i].ro_angle,TRUE));
		Option[i].y = Player[0].y + Option[i].ro * sin(Radian(Option[i].ro_angle,TRUE));
	}
	else if(Player[0].chara%3==1){
		float max_ro,rx,ry,round;
		if(i<4){
			max_ro = -30.0;
			rx = 45.0;
			ry = 15.0;
			round = 90.0*i + 3.0*Option[i].count;
		}
		else{
			max_ro = 30.0;
			rx = 25.0;
			ry = 15.0;
			round = 90.0*i + 2.0*Option[i].count;
		}
		if(Player[0].slow_count<10){
			max_ro = max_ro*(float)(10-Player[0].slow_count)/10.0;
			rx = rx*(float)(10-Player[0].slow_count)/10.0;
			ry = ry*(float)(10-Player[0].slow_count)/10.0;
		}
		else{
			max_ro = 0;
			rx = 0;
			ry = 0;
		}
		if(Option[i].count<10){
			Option[i].ro = Option[i].count*max_ro/10;
			rx = rx*(float)(Option[i].count)/10.0;
			ry = ry*(float)(Option[i].count)/10.0;
		}
		else{
			Option[i].ro = max_ro;
		}
		Option[i].x = Player[0].x + rx * cos(Radian(round,TRUE));
		Option[i].y = Player[0].y + Option[i].ro + ry * sin(Radian(round,TRUE));
	}
	else if(Player[0].chara%3==2){
		float max_ro;
		if(i==0||i==4)		max_ro = 30.0;
		else if(i==1||i==5)	max_ro = 30.0;
		else if(i==2||i==6)	max_ro = 50.0;
		else if(i==3||i==7)	max_ro = 70.0;
		if(Player[0].slow_count<10)	max_ro = max_ro*(float)(10-Player[0].slow_count)/10.0;
		else				max_ro = 0;
		if(i==0)	Option[i].ro_angle = -135.0;
		else if(i==1)	Option[i].ro_angle = 20.0;
		else if(i==2)	Option[i].ro_angle = 20.0;
		else if(i==3)	Option[i].ro_angle = 20.0;
		else if(i==4)	Option[i].ro_angle = -45.0;
		else if(i==5)	Option[i].ro_angle = 160.0;
		else if(i==6)	Option[i].ro_angle = 160.0;
		else if(i==7)	Option[i].ro_angle = 160.0;
		if(Option[i].count<10)	Option[i].ro = Option[i].count*max_ro/10;
		else			Option[i].ro = max_ro;
		Option[i].x = Player[0].x + Option[i].ro * cos(Radian(Option[i].ro_angle,TRUE));
		Option[i].y = Player[0].y + Option[i].ro * sin(Radian(Option[i].ro_angle,TRUE));
	}

	Option[i].angle += Radian(3.0,TRUE);	
		
	return;
}

void SBack(){
	list<BOSSDATA>::iterator bit = Boss.begin();
	int SBC = SpBackCount;
	if(Boss.size()==0 || (*bit).bSpell==false)	SpBackCount = 0;
	if(SpBackCount>=50)	return;

	int flashb=255;
	if(SpBackCount<50)	flashb = 255-5.1*SpBackCount;
	SetDrawBright(flashb, flashb, flashb);

	if(Player[0].stage==1 || Player[0].stage==0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		int sx,sy;
		GetGraphSize(gBack[0],&sx,&sy);
		
		BackY = Scount*2.0/3.0;
		if(BackY>sy-470)	BackY = sy-470;
		if(GetSkip())	DrawGraph(10+shake_x, 480-sy+BackY+shake_y, gBack[0], FALSE);
	}
	else if(Player[0].stage==2){
		SetCameraScreenCenter(CENTER_X, -150);
		if(Scount<300)		SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,-300), VGet(CENTER_X,CENTER_Y+3*Scount,0));
		else if(Scount<4000)	SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,-300), VGet(CENTER_X,CENTER_Y+900,0));
		else if(Scount<5440)	SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X+120*sin(Radian((Scount-4000)/2.0,TRUE)),CENTER_Y,-300), VGet(CENTER_X,CENTER_Y+900,0));
		else if(Scount<5530)	SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X+250*sin(Radian((Scount-4000)/2.0,TRUE)),CENTER_Y,-300-200.0*sin(Radian(Scount-5440,TRUE))), VGet(CENTER_X,CENTER_Y+900-4*(Scount-5440),0));
		else			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X+250*sin(Radian((Scount-4000)/2.0,TRUE)),CENTER_Y,-500), VGet(CENTER_X,CENTER_Y+540,0));
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		int sx,sy;
		GetGraphSize(gBack2[3],&sx,&sy);
		if(Scount<5500)		BackY = Scount;
		else			BackY = 5500 + (Scount-5500)*2.0;
		if(GetSkip()){
			for(int i=0;i<4;i++){
				for(int j=-2;j<3;j++){
					VERTEX3D Vertex[6];
					for(int a=0;a<6;a++){
						Vertex[a].norm = VGet(0, 0, -1);
						Vertex[a].spc = GetColorU8(0, 0, 0, 0);
						Vertex[a].su = 0;
						Vertex[a].sv = 0;
					}
					Vertex[0].pos = VGet(sx*j, sy*(i+1)-(int)BackY%sy, 0);
					Vertex[0].dif = GetColorU8(255, 255, 255, 255);
					Vertex[0].u = 0.0f;
					Vertex[0].v = 1.0f;
					Vertex[1].pos = VGet(sx*(j+1), sy*(i+1)-(int)BackY%sy, 0);
					Vertex[1].dif = GetColorU8(255, 255, 255, 255);
					Vertex[1].u = 1.0f;
					Vertex[1].v = 1.0f;
					Vertex[2].pos = VGet(sx*j, sy*i-(int)BackY%sy, 0);
					Vertex[2].dif = GetColorU8(255, 255, 255, 255);
					Vertex[2].u = 0.0f;
					Vertex[2].v = 0.0f;
					Vertex[3].pos = VGet(sx*(j+1), sy*i-(int)BackY%sy, 0);
					Vertex[3].dif = GetColorU8(255, 255, 255, 255);
					Vertex[3].u = 1.0f;
					Vertex[3].v = 0.0f;
					Vertex[4].pos = VGet(sx*j, sy*i-(int)BackY%sy, 0);
					Vertex[4].dif = GetColorU8(255, 255, 255, 255);
					Vertex[4].u = 0.0f;
					Vertex[4].v = 0.0f;
					Vertex[5].pos = VGet(sx*(j+1), sy*(i+1)-(int)BackY%sy, 0);
					Vertex[5].dif = GetColorU8(255, 255, 255, 255);
					Vertex[5].u = 1.0f;
					Vertex[5].v = 1.0f;
					int img = 3;
					if(j%2==1)	img = 8;
					DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_ADD,100);
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					VERTEX3D Vertex[6];
					for(int a=0;a<6;a++){
						Vertex[a].norm = VGet(0, 0, -1);
						Vertex[a].spc = GetColorU8(0, 0, 0, 0);
						Vertex[a].su = 0;
						Vertex[a].sv = 0;
					}
					Vertex[0].pos = VGet(sx/2*j, sy*(i+1)-(int)BackY%sy, -80+40*(j%2));
					Vertex[0].dif = GetColorU8(255, 255, 255, 255);
					Vertex[0].u = 0.0f;
					Vertex[0].v = 1.0f;
					Vertex[1].pos = VGet(sx/2*(j+1), sy*(i+1)-(int)BackY%sy, -80+40*(j%2));
					Vertex[1].dif = GetColorU8(255, 255, 255, 255);
					Vertex[1].u = 1.0f;
					Vertex[1].v = 1.0f;
					Vertex[2].pos = VGet(sx/2*j, sy*i-(int)BackY%sy, -80+40*(j%2));
					Vertex[2].dif = GetColorU8(255, 255, 255, 255);
					Vertex[2].u = 0.0f;
					Vertex[2].v = 0.0f;
					Vertex[3].pos = VGet(sx/2*(j+1), sy*i-(int)BackY%sy, -80+40*(j%2));
					Vertex[3].dif = GetColorU8(255, 255, 255, 255);
					Vertex[3].u = 1.0f;
					Vertex[3].v = 0.0f;
					Vertex[4].pos = VGet(sx/2*j, sy*i-(int)BackY%sy, -80+40*(j%2));
					Vertex[4].dif = GetColorU8(255, 255, 255, 255);
					Vertex[4].u = 0.0f;
					Vertex[4].v = 0.0f;
					Vertex[5].pos = VGet(sx/2*(j+1), sy*(i+1)-(int)BackY%sy, -80+40*(j%2));
					Vertex[5].dif = GetColorU8(255, 255, 255, 255);
					Vertex[5].u = 1.0f;
					Vertex[5].v = 1.0f;
					int img = 6;
					if(j%2==1)	img = 7;
					DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
				}
			}
		}
		if(BEffect.size()==0 && NowPart>=MIDBOSS && SpBackCount==49){
			for(int i=0;i<200;i++){
				SBEfMake(10+get_rand(420), 10+get_rand(460), -100-get_rand(100), 0);
			}
		}
	}
	else if(Player[0].stage==3){
		static float mx,my,mz;
		if(Scount<7860 || Scount>14100)		SetCameraScreenCenter(CENTER_X, -150);
		else			SetCameraScreenCenter(CENTER_X, CENTER_Y);
		if(Scount<1600){
			BackZ = -1000;
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
		}
		else if(Scount<=2000){
			BackZ = -1000+700.0*sin(Radian(90.0*(Scount-1600)/400.0,TRUE));
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
		}
		else if(Scount<3080){}
		else if(Scount<=3200){
			if(Scount<=3140){
				float per = (Scount-3080)/60.0;
				BackZ = -300+150.0*per;
				float plus = 1000.0-1000.0*per;
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(0, 1.0, 0.0));
			}
			else{
				float per = Radian(90.0*(Scount-3140)/60.0,TRUE);
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,0), VGet(1.0-1.0*cos(per), 1.0-1.0*sin(per), 0.0));
			}
			/*
			float per = sin(Radian(90.0*(Scount-3080)/120.0,TRUE));
			BackZ = -300+150.0*per;
			float plus = 1000.0-1000.0*per;
			SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(1.0*per, 1.0-1.0*per, 0.0));
			*/
		}
		else if(Scount<6200){}
		else if(Scount<=6320){
			if(Scount<=6260){
				float per = Radian(90.0*(Scount-6200)/60.0,TRUE);
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,0), VGet(1.0*cos(per), -1.0*per, 0.0));
			}
			else{
				float per = (Scount-6260)/60.0;
				BackZ = -150-150.0*per;
				float plus = -1500.0*per;
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(0, -1.0, 0.0));
			}
			/*
			float per = sin(Radian(90.0*(Scount-6200)/120.0,TRUE));
			BackZ = -150-150.0*per;
			float plus = -1500.0*per;
			SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(1.0-1.0*per, -1.0*per, 0.0));
			*/
		}
		else if(Scount<7800){}
		else if(Scount<7860){
			SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y-1500,-11.1*(Scount-7800)), VGet(0.0, -1.0, 0.0));
		}
		else if(Scount==7860){
			BackX = 0;
			BackY = 0;
			BackZ = 0;
			BEffect.clear();
			for(int i=0;i<300;i++){
				float x = get_rand(480);
				float y = get_rand(1000);
				float z = get_rand(3000);
				SBEfMake(x, y, z, 2);
			}
			for(int i=0;i<250;i++){
				float x = get_rand(480);
				float y = get_rand(1500);
				float z = get_rand(3000);
				SBEfMake(x, y, z, 3);
			}
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,1000));
		}
		else if(Scount<14000){}
		else if(Scount<14100){
			BackZ += 5.0;
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,1000));
		}
		else if(Scount<14240){
			if(Scount==14100){
				for(list<BACKDATA>::iterator it=BEffect.begin(); it!=BEffect.end(); ++it){
					(*it).bDelete = true;
				}
			}
			BackX = 0;
			BackY = 1000+(Scount-14100)*0.01;
			if(BackY>2000)	BackY = 2000;
			BackZ = -1000+700.0*sin(Radian(90.0*(Scount-14100)/140.0,TRUE));
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
		}
		else{
			/*
			static int ffllaagg = 0;
			static float aangle = 0;
			if(Scount==14240){
				ffllaagg = 0;
				aangle = 0;
			}
			if(SpBackCount==49)	ffllaagg = 1;
			if(ffllaagg==1){
				float X = CENTER_X + 100.0*cos(Radian(aangle,TRUE));
				float Y = CENTER_Y + 1000 + 100.0*sin(Radian(aangle,TRUE));
				SetCameraPositionAndTarget_UpVecY(VGet(X,Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
				aangle += 1.0;
			}
			*/		
		}
		
		if(Scount<3080){
			BackY = Scount/2;
		}
		else if(Scount<3200){
			static float per;
			if(Scount==3080)	per = (1725-BackY)/60.0;
			if(Scount<3140)	BackY += per;
		}
		else if(Scount<6200){
			BackX += 1.0;
		}
		else if(Scount<6320){}
		else if(Scount<7800){
			static float per;
			if(Scount==6320)	per = (BackY-1400)/1480.0;
			BackY -= per;
			BackX -= 1.9;
		}
		else if(Scount<7860){
			BackX -= 2.0;
			BackY -= 2.0;
			BackZ -= 5.0;
		}
		else{}
		if(GetSkip()){
			if(Scount<7900 || Scount>=14100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				//DrawBox(10,10,430,470,GetColor(200,200,255),TRUE);
				DrawRotaGraphF(CENTER_X,CENTER_Y,2.0,0,gBack2[14],FALSE,FALSE);
				int sx,sy;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				GetGraphSize(gBack2[9],&sx,&sy);
				for(int i=-1;i<6;i++){
					for(int j=-2;j<3;j++){
						VERTEX3D Vertex[6];
						for(int a=0;a<6;a++){
							Vertex[a].norm = VGet(0, 0, -1);
							Vertex[a].spc = GetColorU8(0, 0, 0, 0);
							Vertex[a].su = 0;
							Vertex[a].sv = 0;
						}
						Vertex[0].pos = VGet(sx*j-(int)BackX%sx, sy*(i+1)-(int)BackY%sy, 0);
						Vertex[0].dif = GetColorU8(255, 255, 255, 255);
						Vertex[0].u = 0.0f;
						Vertex[0].v = 1.0f;
						Vertex[1].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)BackY%sy, 0);
						Vertex[1].dif = GetColorU8(255, 255, 255, 255);
						Vertex[1].u = 1.0f;
						Vertex[1].v = 1.0f;
						Vertex[2].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)BackY%sy, 0);
						Vertex[2].dif = GetColorU8(255, 255, 255, 255);
						Vertex[2].u = 0.0f;
						Vertex[2].v = 0.0f;
						Vertex[3].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*i-(int)BackY%sy, 0);
						Vertex[3].dif = GetColorU8(255, 255, 255, 255);
						Vertex[3].u = 1.0f;
						Vertex[3].v = 0.0f;
						Vertex[4].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)BackY%sy, 0);
						Vertex[4].dif = GetColorU8(255, 255, 255, 255);
						Vertex[4].u = 0.0f;
						Vertex[4].v = 0.0f;
						Vertex[5].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)BackY%sy, 0);
						Vertex[5].dif = GetColorU8(255, 255, 255, 255);
						Vertex[5].u = 1.0f;
						Vertex[5].v = 1.0f;
						int img = 9;
						DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				GetGraphSize(gBack2[10],&sx,&sy);
				sx /= 10;
				sy /= 1;
				float train_y[3];
				train_y[0] = 1150-(int)BackY;
				train_y[1] = 1900-(int)BackY;
				train_y[2] = 2000-(int)BackY;
				for(int i=0;i<3;i++){
					for(int j=-2;j<3;j++){
						VERTEX3D Vertex[6];
						for(int a=0;a<6;a++){
							Vertex[a].norm = VGet(0, 0, -1);
							Vertex[a].spc = GetColorU8(0, 0, 0, 0);
							Vertex[a].su = 0;
							Vertex[a].sv = 0;
						}
						Vertex[0].pos = VGet(sy*(j+1)-(int)BackX%sy, train_y[i]+sx*1, -1);
						Vertex[0].dif = GetColorU8(255, 255, 255, 255);
						Vertex[0].u = 0.0f;
						Vertex[0].v = 0.5f;
						Vertex[1].pos = VGet(sy*(j+1)-(int)BackX%sy, train_y[i]+sx*0, -1);
						Vertex[1].dif = GetColorU8(255, 255, 255, 255);
						Vertex[1].u = 0.5f;
						Vertex[1].v = 0.5f;
						Vertex[2].pos = VGet(sy*j-(int)BackX%sy, train_y[i]+sx*1, -1);
						Vertex[2].dif = GetColorU8(255, 255, 255, 255);
						Vertex[2].u = 0.0f;
						Vertex[2].v = 0.0f;
						Vertex[3].pos = VGet(sy*j-(int)BackX%sy, train_y[i]+sx*0, -1);
						Vertex[3].dif = GetColorU8(255, 255, 255, 255);
						Vertex[3].u = 0.5f;
						Vertex[3].v = 0.0f;
						Vertex[4].pos = VGet(sy*j-(int)BackX%sy, train_y[i]+sx*1, -1);
						Vertex[4].dif = GetColorU8(255, 255, 255, 255);
						Vertex[4].u = 0.0f;
						Vertex[4].v = 0.0f;
						Vertex[5].pos = VGet(sy*(j+1)-(int)BackX%sy, train_y[i]+sx*0, -1);
						Vertex[5].dif = GetColorU8(255, 255, 255, 255);
						Vertex[5].u = 0.5f;
						Vertex[5].v = 0.5f;
						int img = 10;
						DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
					}
				}
				for(int i=0;i<1;i++){
					if(i==0){
						mx = CENTER_X+100-(int)BackX;
						my = train_y[0]+200;
						mz = 0;
						MV1SetPosition(gModel[i], VGet(mx,my,mz));
						MV1SetScale(gModel[i], VGet(0.2f, 0.2f, 0.2f));
						MV1SetRotationXYZ(gModel[i], VGet(Radian(-90,TRUE), 0, Radian(75,TRUE)));
						MV1DrawModel(gModel[i]);
					}
				}
				if(Scount<1400)		SetDrawBlendMode(DX_BLENDMODE_ADD,0);
				else if(Scount<1900)	SetDrawBlendMode(DX_BLENDMODE_ADD,0.25*(Scount-1400));
				else			SetDrawBlendMode(DX_BLENDMODE_ADD,125);
				GetGraphSize(gBack2[9],&sx,&sy);
				for(int i=-1;i<6;i++){
					for(int j=-2;j<3;j++){
						VERTEX3D Vertex[6];
						for(int a=0;a<6;a++){
							Vertex[a].norm = VGet(0, 0, -1);
							Vertex[a].spc = GetColorU8(0, 0, 0, 0);
							Vertex[a].su = 0;
							Vertex[a].sv = 0;
						}
						Vertex[0].pos = VGet(sx*j-(int)BackX%sx, sy*(i+1)-(int)Scount*4%sy, -5);
						Vertex[0].dif = GetColorU8(255, 255, 255, 255);
						Vertex[0].u = 0.0f;
						Vertex[0].v = 1.0f;
						Vertex[1].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)Scount*4%sy, -5);
						Vertex[1].dif = GetColorU8(255, 255, 255, 255);
						Vertex[1].u = 1.0f;
						Vertex[1].v = 1.0f;
						Vertex[2].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)Scount*4%sy, -5);
						Vertex[2].dif = GetColorU8(255, 255, 255, 255);
						Vertex[2].u = 0.0f;
						Vertex[2].v = 0.0f;
						Vertex[3].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*i-(int)Scount*4%sy, -5);
						Vertex[3].dif = GetColorU8(255, 255, 255, 255);
						Vertex[3].u = 1.0f;
						Vertex[3].v = 0.0f;
						Vertex[4].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)Scount*4%sy, -5);
						Vertex[4].dif = GetColorU8(255, 255, 255, 255);
						Vertex[4].u = 0.0f;
						Vertex[4].v = 0.0f;
						Vertex[5].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)Scount*4%sy, -5);
						Vertex[5].dif = GetColorU8(255, 255, 255, 255);
						Vertex[5].u = 1.0f;
						Vertex[5].v = 1.0f;
						int img = 9;
						DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
					}
				}
			}
			else if(Scount<14100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
				DrawRotaGraphF(CENTER_X,CENTER_Y,2.0,Radian(Scount,TRUE),gBack2[15],FALSE,FALSE);
			}
		}
		SetDrawBright(255, 255, 255);
		SBEfDraw();	
		if(GetSkip()){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);			
			DrawBox(0,0,640,480,0,TRUE);
			if(Scount<7800){}
			else if(Scount<7860){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-7800));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<7920){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<8040){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(8040-Scount));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<14000){}
			else if(Scount<14060){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-14000));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<14120){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<14240){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(14240-Scount));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
		}
		if(BEffect.size()==0){
			for(int i=0;i<100;i++){
				SBEfMake(10+get_rand(420), 10+get_rand(460), BackZ+200-get_rand(100), 1);
			}
		}
	}
	else if(Player[0].stage==4){
		static float mx,my,mz;
		if(Scount<7860 || Scount>14100)		SetCameraScreenCenter(CENTER_X, -150);
		else			SetCameraScreenCenter(CENTER_X, CENTER_Y);
		if(Scount<1600){
			BackZ = -1000;
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
		}
		else if(Scount<=2000){
			BackZ = -1000+700.0*sin(Radian(90.0*(Scount-1600)/400.0,TRUE));
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
		}
		else if(Scount<3080){}
		else if(Scount<=3200){
			if(Scount<=3140){
				float per = (Scount-3080)/60.0;
				BackZ = -300+150.0*per;
				float plus = 1000.0-1000.0*per;
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(0, 1.0, 0.0));
			}
			else{
				float per = Radian(90.0*(Scount-3140)/60.0,TRUE);
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,0), VGet(1.0-1.0*cos(per), 1.0-1.0*sin(per), 0.0));
			}
			/*
			float per = sin(Radian(90.0*(Scount-3080)/120.0,TRUE));
			BackZ = -300+150.0*per;
			float plus = 1000.0-1000.0*per;
			SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(1.0*per, 1.0-1.0*per, 0.0));
			*/
		}
		else if(Scount<6200){}
		else if(Scount<=6320){
			if(Scount<=6260){
				float per = Radian(90.0*(Scount-6200)/60.0,TRUE);
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,0), VGet(1.0*cos(per), -1.0*per, 0.0));
			}
			else{
				float per = (Scount-6260)/60.0;
				BackZ = -150-150.0*per;
				float plus = -1500.0*per;
				SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(0, -1.0, 0.0));
			}
			/*
			float per = sin(Radian(90.0*(Scount-6200)/120.0,TRUE));
			BackZ = -150-150.0*per;
			float plus = -1500.0*per;
			SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+plus,0), VGet(1.0-1.0*per, -1.0*per, 0.0));
			*/
		}
		else if(Scount<7800){}
		else if(Scount<7860){
			SetCameraPositionAndTargetAndUpVec(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y-1500,-11.1*(Scount-7800)), VGet(0.0, -1.0, 0.0));
		}
		else if(Scount==7860){
			BackX = 0;
			BackY = 0;
			BackZ = 0;
			BEffect.clear();
			for(int i=0;i<300;i++){
				float x = get_rand(480);
				float y = get_rand(1000);
				float z = get_rand(3000);
				SBEfMake(x, y, z, 2);
			}
			for(int i=0;i<250;i++){
				float x = get_rand(480);
				float y = get_rand(1500);
				float z = get_rand(3000);
				SBEfMake(x, y, z, 3);
			}
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,1000));
		}
		else if(Scount<14000){}
		else if(Scount<14100){
			BackZ += 5.0;
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y,1000));
		}
		else if(Scount<14240){
			if(Scount==14100){
				for(list<BACKDATA>::iterator it=BEffect.begin(); it!=BEffect.end(); ++it){
					(*it).bDelete = true;
				}
			}
			BackX = 0;
			BackY = 1000+(Scount-14100)*0.01;
			if(BackY>2000)	BackY = 2000;
			BackZ = -1000+700.0*sin(Radian(90.0*(Scount-14100)/140.0,TRUE));
			SetCameraPositionAndTarget_UpVecY(VGet(CENTER_X,CENTER_Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
		}
		else{
			/*
			static int ffllaagg = 0;
			static float aangle = 0;
			if(Scount==14240){
				ffllaagg = 0;
				aangle = 0;
			}
			if(SpBackCount==49)	ffllaagg = 1;
			if(ffllaagg==1){
				float X = CENTER_X + 100.0*cos(Radian(aangle,TRUE));
				float Y = CENTER_Y + 1000 + 100.0*sin(Radian(aangle,TRUE));
				SetCameraPositionAndTarget_UpVecY(VGet(X,Y,BackZ), VGet(CENTER_X,CENTER_Y+1000,0));
				aangle += 1.0;
			}
			*/		
		}
		
		if(Scount<3080){
			BackY = Scount/2;
		}
		else if(Scount<3200){
			static float per;
			if(Scount==3080)	per = (1725-BackY)/60.0;
			if(Scount<3140)	BackY += per;
		}
		else if(Scount<6200){
			BackX += 1.0;
		}
		else if(Scount<6320){}
		else if(Scount<7800){
			static float per;
			if(Scount==6320)	per = (BackY-1400)/1480.0;
			BackY -= per;
			BackX -= 1.9;
		}
		else if(Scount<7860){
			BackX -= 2.0;
			BackY -= 2.0;
			BackZ -= 5.0;
		}
		else{}
		if(GetSkip()){
			if(Scount<7900 || Scount>=14100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				//DrawBox(10,10,430,470,GetColor(200,200,255),TRUE);
				DrawRotaGraphF(CENTER_X,CENTER_Y,2.0,0,gBack2[14],FALSE,FALSE);
				int sx,sy;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				GetGraphSize(gBack2[9],&sx,&sy);
				for(int i=-1;i<6;i++){
					for(int j=-2;j<3;j++){
						VERTEX3D Vertex[6];
						for(int a=0;a<6;a++){
							Vertex[a].norm = VGet(0, 0, -1);
							Vertex[a].spc = GetColorU8(0, 0, 0, 0);
							Vertex[a].su = 0;
							Vertex[a].sv = 0;
						}
						Vertex[0].pos = VGet(sx*j-(int)BackX%sx, sy*(i+1)-(int)BackY%sy, 0);
						Vertex[0].dif = GetColorU8(255, 255, 255, 255);
						Vertex[0].u = 0.0f;
						Vertex[0].v = 1.0f;
						Vertex[1].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)BackY%sy, 0);
						Vertex[1].dif = GetColorU8(255, 255, 255, 255);
						Vertex[1].u = 1.0f;
						Vertex[1].v = 1.0f;
						Vertex[2].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)BackY%sy, 0);
						Vertex[2].dif = GetColorU8(255, 255, 255, 255);
						Vertex[2].u = 0.0f;
						Vertex[2].v = 0.0f;
						Vertex[3].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*i-(int)BackY%sy, 0);
						Vertex[3].dif = GetColorU8(255, 255, 255, 255);
						Vertex[3].u = 1.0f;
						Vertex[3].v = 0.0f;
						Vertex[4].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)BackY%sy, 0);
						Vertex[4].dif = GetColorU8(255, 255, 255, 255);
						Vertex[4].u = 0.0f;
						Vertex[4].v = 0.0f;
						Vertex[5].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)BackY%sy, 0);
						Vertex[5].dif = GetColorU8(255, 255, 255, 255);
						Vertex[5].u = 1.0f;
						Vertex[5].v = 1.0f;
						int img = 9;
						DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				GetGraphSize(gBack2[10],&sx,&sy);
				sx /= 10;
				sy /= 1;
				float train_y[3];
				train_y[0] = 1150-(int)BackY;
				train_y[1] = 1900-(int)BackY;
				train_y[2] = 2000-(int)BackY;
				for(int i=0;i<3;i++){
					for(int j=-2;j<3;j++){
						VERTEX3D Vertex[6];
						for(int a=0;a<6;a++){
							Vertex[a].norm = VGet(0, 0, -1);
							Vertex[a].spc = GetColorU8(0, 0, 0, 0);
							Vertex[a].su = 0;
							Vertex[a].sv = 0;
						}
						Vertex[0].pos = VGet(sy*(j+1)-(int)BackX%sy, train_y[i]+sx*1, -1);
						Vertex[0].dif = GetColorU8(255, 255, 255, 255);
						Vertex[0].u = 0.0f;
						Vertex[0].v = 0.5f;
						Vertex[1].pos = VGet(sy*(j+1)-(int)BackX%sy, train_y[i]+sx*0, -1);
						Vertex[1].dif = GetColorU8(255, 255, 255, 255);
						Vertex[1].u = 0.5f;
						Vertex[1].v = 0.5f;
						Vertex[2].pos = VGet(sy*j-(int)BackX%sy, train_y[i]+sx*1, -1);
						Vertex[2].dif = GetColorU8(255, 255, 255, 255);
						Vertex[2].u = 0.0f;
						Vertex[2].v = 0.0f;
						Vertex[3].pos = VGet(sy*j-(int)BackX%sy, train_y[i]+sx*0, -1);
						Vertex[3].dif = GetColorU8(255, 255, 255, 255);
						Vertex[3].u = 0.5f;
						Vertex[3].v = 0.0f;
						Vertex[4].pos = VGet(sy*j-(int)BackX%sy, train_y[i]+sx*1, -1);
						Vertex[4].dif = GetColorU8(255, 255, 255, 255);
						Vertex[4].u = 0.0f;
						Vertex[4].v = 0.0f;
						Vertex[5].pos = VGet(sy*(j+1)-(int)BackX%sy, train_y[i]+sx*0, -1);
						Vertex[5].dif = GetColorU8(255, 255, 255, 255);
						Vertex[5].u = 0.5f;
						Vertex[5].v = 0.5f;
						int img = 10;
						DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
					}
				}
				for(int i=0;i<1;i++){
					if(i==0){
						mx = CENTER_X+100-(int)BackX;
						my = train_y[0]+200;
						mz = 0;
						MV1SetPosition(gModel[i], VGet(mx,my,mz));
						MV1SetScale(gModel[i], VGet(0.2f, 0.2f, 0.2f));
						MV1SetRotationXYZ(gModel[i], VGet(Radian(-90,TRUE), 0, Radian(75,TRUE)));
						MV1DrawModel(gModel[i]);
					}
				}
				if(Scount<1400)		SetDrawBlendMode(DX_BLENDMODE_ADD,0);
				else if(Scount<1900)	SetDrawBlendMode(DX_BLENDMODE_ADD,0.25*(Scount-1400));
				else			SetDrawBlendMode(DX_BLENDMODE_ADD,125);
				GetGraphSize(gBack2[9],&sx,&sy);
				for(int i=-1;i<6;i++){
					for(int j=-2;j<3;j++){
						VERTEX3D Vertex[6];
						for(int a=0;a<6;a++){
							Vertex[a].norm = VGet(0, 0, -1);
							Vertex[a].spc = GetColorU8(0, 0, 0, 0);
							Vertex[a].su = 0;
							Vertex[a].sv = 0;
						}
						Vertex[0].pos = VGet(sx*j-(int)BackX%sx, sy*(i+1)-(int)Scount*4%sy, -5);
						Vertex[0].dif = GetColorU8(255, 255, 255, 255);
						Vertex[0].u = 0.0f;
						Vertex[0].v = 1.0f;
						Vertex[1].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)Scount*4%sy, -5);
						Vertex[1].dif = GetColorU8(255, 255, 255, 255);
						Vertex[1].u = 1.0f;
						Vertex[1].v = 1.0f;
						Vertex[2].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)Scount*4%sy, -5);
						Vertex[2].dif = GetColorU8(255, 255, 255, 255);
						Vertex[2].u = 0.0f;
						Vertex[2].v = 0.0f;
						Vertex[3].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*i-(int)Scount*4%sy, -5);
						Vertex[3].dif = GetColorU8(255, 255, 255, 255);
						Vertex[3].u = 1.0f;
						Vertex[3].v = 0.0f;
						Vertex[4].pos = VGet(sx*j-(int)BackX%sx, sy*i-(int)Scount*4%sy, -5);
						Vertex[4].dif = GetColorU8(255, 255, 255, 255);
						Vertex[4].u = 0.0f;
						Vertex[4].v = 0.0f;
						Vertex[5].pos = VGet(sx*(j+1)-(int)BackX%sx, sy*(i+1)-(int)Scount*4%sy, -5);
						Vertex[5].dif = GetColorU8(255, 255, 255, 255);
						Vertex[5].u = 1.0f;
						Vertex[5].v = 1.0f;
						int img = 9;
						DrawPolygon3D(Vertex, 2, gBack2[img], TRUE);
					}
				}
			}
			else if(Scount<14100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
				DrawRotaGraphF(CENTER_X,CENTER_Y,2.0,Radian(Scount,TRUE),gBack2[15],FALSE,FALSE);
			}
		}
		SetDrawBright(255, 255, 255);
		SBEfDraw();	
		if(GetSkip()){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);			
			DrawBox(0,0,640,480,0,TRUE);
			if(Scount<7800){}
			else if(Scount<7860){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-7800));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<7920){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<8040){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(8040-Scount));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<14000){}
			else if(Scount<14060){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Scount-14000));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<14120){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
			else if(Scount<14240){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(14240-Scount));			
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			}
		}
		if(BEffect.size()==0){
			for(int i=0;i<100;i++){
				SBEfMake(10+get_rand(420), 10+get_rand(460), BackZ+200-get_rand(100), 1);
			}
		}
	}
	SetDrawBright(255, 255, 255);
	if(Player[0].stage!=3 && Player[0].stage!=4)	SBEfDraw();
	if(Scount<120){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-2.125*Scount);
		DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
	}
	SpBackCount = SBC;

	return;
}

void SBEfMake(float x, float y, float z, int pattern){
	if(BEffect.size()==512){}
	else{
		BACKDATA P;
		P.x = x;
		P.y = y;
		P.z = z;
		P.speed = 0;
		P.move_x = 0;
		P.move_y = 0;
		P.move_z = 0;
		P.large = 1.0;
		P.angle = 0;
		P.img = -1;
		P.flash = 255;
		P.count = 0;
		P.red = 255;
		P.green = 255;
		P.blue = 255;
		P.pattern = pattern;
		P.bBlend = true;
		P.bDelete = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}
	
		BEffect.push_back(P);
	}
	
	return;
}

void SBEfDraw(){
	for(list<BACKDATA>::iterator it=BEffect.begin(); it!=BEffect.end(); ++it){
		SBEfMove(it);
		if((*it).bDelete==true){
			it = BEffect.erase(it);
			it--;
			continue;			
		}
		if(SpBackCount>0){
			float flashb=1.0;
			if(SpBackCount<50)	flashb = 1.0-0.02*SpBackCount;
			if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash*flashb);
			else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash*flashb);
		}
		else{
			if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		}
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		if(GetSkip()){
			if((*it).img>=0){
				int gx,gy;
				GetGraphSize((*it).img, &gx, &gy);
				float sx = gx/2.0;
				float sy = gy/2.0;
				float l = sqrt(sx*sx+sy*sy);
				VERTEX3D Vertex[6];
				for(int a=0;a<6;a++){
					Vertex[a].norm = VGet(0, 0, -1);
					Vertex[a].spc = GetColorU8(0, 0, 0, 0);
					Vertex[a].su = 0;
					Vertex[a].sv = 0;
				}
				Vertex[0].pos = VGet((*it).x+(*it).large*cos(Radian(135,TRUE)+(*it).angle), (*it).y+(*it).large*sin(Radian(135,TRUE)+(*it).angle), (*it).z);
				Vertex[0].dif = GetColorU8(255, 255, 255, 255);
				Vertex[0].u = 0.0f;
				Vertex[0].v = 1.0f;
				Vertex[1].pos = VGet((*it).x+(*it).large*cos(Radian(45,TRUE)+(*it).angle), (*it).y+(*it).large*sin(Radian(45,TRUE)+(*it).angle), (*it).z);
				Vertex[1].dif = GetColorU8(255, 255, 255, 255);
				Vertex[1].u = 1.0f;
				Vertex[1].v = 1.0f;
				Vertex[2].pos = VGet((*it).x+(*it).large*cos(Radian(225,TRUE)+(*it).angle), (*it).y+(*it).large*sin(Radian(225,TRUE)+(*it).angle), (*it).z);
				Vertex[2].dif = GetColorU8(255, 255, 255, 255);
				Vertex[2].u = 0.0f;
				Vertex[2].v = 0.0f;
				Vertex[3].pos = VGet((*it).x+(*it).large*cos(Radian(-45,TRUE)+(*it).angle), (*it).y+(*it).large*sin(Radian(-45,TRUE)+(*it).angle), (*it).z);
				Vertex[3].dif = GetColorU8(255, 255, 255, 255);
				Vertex[3].u = 1.0f;
				Vertex[3].v = 0.0f;
				Vertex[4].pos = VGet((*it).x+(*it).large*cos(Radian(225,TRUE)+(*it).angle), (*it).y+(*it).large*sin(Radian(225,TRUE)+(*it).angle), (*it).z);
				Vertex[4].dif = GetColorU8(255, 255, 255, 255);
				Vertex[4].u = 0.0f;
				Vertex[4].v = 0.0f;
				Vertex[5].pos = VGet((*it).x+(*it).large*cos(Radian(45,TRUE)+(*it).angle), (*it).y+(*it).large*sin(Radian(45,TRUE)+(*it).angle), (*it).z);
				Vertex[5].dif = GetColorU8(255, 255, 255, 255);
				Vertex[5].u = 1.0f;
				Vertex[5].v = 1.0f;
				DrawPolygon3D(Vertex, 2, (*it).img, TRUE);
			}
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void SBEfMove(list<BACKDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;

	if(p==0){//ステージ２モミジ
		if(c==0){
			(*it).large = 10.0;
			(*it).img = gEffect[9];
			(*it).flash = 0;
			(*it).speed = 1.0+0.1*get_rand(20);
			(*it).angle = Radian(get_rand(360),TRUE);
			(*it).move_z = 1.0;
			if(get_rand(1)==0){
				(*it).red = 255;
				(*it).green = 100;
				(*it).blue = 100;
			}
			else{
				(*it).red = 255;
				(*it).green = 255;
				(*it).blue = 100;
			}
			(*it).f_hanyou[0] = 1 + get_rand(7);
			if(get_rand(1)==0)	(*it).f_hanyou[0] *= -1;
			(*it).f_hanyou[1] = BackY;
		}
		(*it).y -= (BackY - (*it).f_hanyou[1])/2.0;
		(*it).f_hanyou[1] = BackY;
		if(c<51)	(*it).flash += 5;
		if((*it).z>-50){
			(*it).flash -= 9;
			if((*it).flash<0){
				(*it).x = 10 + get_rand(420);
				(*it).y = 10 + get_rand(460);
				(*it).z = -100 - get_rand(100);
				(*it).count = -1;
			}
		}
		(*it).angle += Radian((*it).f_hanyou[0],TRUE);
	}
	else if(p==1){//ステージ３雪
		if(c==0){
			(*it).large = 10.0;
			(*it).img = gBack2[11];
			(*it).flash = 0;
			(*it).speed = 0.5+0.1*get_rand(10);
			(*it).angle = Radian(get_rand(360),TRUE);
			(*it).move_z = 1.0;
			(*it).f_hanyou[0] = 1 + get_rand(2);
			if(get_rand(1)==0)	(*it).f_hanyou[0] *= -1;
			(*it).f_hanyou[1] = BackY;
		}
		(*it).y -= (BackY - (*it).f_hanyou[1])/2.0;
		(*it).f_hanyou[1] = BackY;
		if(c<30)	(*it).flash += 5;
		if((*it).z>-10){
			(*it).flash -= 5;
			if((*it).flash<0){
				(*it).x = 10 + get_rand(420);
				(*it).y = 10 + get_rand(460);
				(*it).z = BackZ + 200 - get_rand(100);
				(*it).count = -1;
			}
		}
		(*it).angle += Radian((*it).f_hanyou[0],TRUE);
	}
	else if(p==2){//ステージ３雲
		if(c==0){
			(*it).large = 150.0;
			if(get_rand(1)==0)	(*it).img = gBack2[6];
			else			(*it).img = gBack2[7];
			(*it).flash = 255;
			(*it).speed = 10.0+0.1*get_rand(200);
			(*it).angle = Radian(get_rand(360),TRUE);
			(*it).move_z = -1.0;
			(*it).flash = 0;
		}
		if((*it).flash<255)	(*it).flash += 5;
		if((*it).z<-1000){
			(*it).x = get_rand(1500);
			(*it).y = get_rand(480);
			(*it).z = 2000+get_rand(1000);
			(*it).count = -1;
			(*it).flash = 0;
		}
	}
	else if(p==3){//ステージ３桜
		if(c==0){
			(*it).large = 30.0;
			(*it).img = gBack2[12];
			(*it).flash = 255;
			(*it).speed = 15.0+0.1*get_rand(200);
			(*it).angle = Radian(get_rand(360),TRUE);
			(*it).move_z = -1.0;
			(*it).f_hanyou[0] = 1 + get_rand(2);
			if(get_rand(1)==0)	(*it).f_hanyou[0] *= -1;
			(*it).flash = 0;
		}
		if((*it).flash<255)	(*it).flash += 5;
		if((*it).z<-1000){
			(*it).x = get_rand(1500);
			(*it).y = get_rand(480);
			(*it).z = 2000+get_rand(1000);
			(*it).count = -1;
			(*it).flash = 0;
		}
		(*it).angle += Radian((*it).f_hanyou[0],TRUE);
	}

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;
	(*it).z += (*it).speed * (*it).move_z;
	
	return;
}

void SESDelete(int flag,float sx, float sy){
//5:プレイヤー死亡時
	list<BOSSDATA>::iterator bit = Boss.begin();
	if(flag==2){
		if(Boss.size()==0 || ((*bit).pattern>=44&&(*bit).pattern<=47&&SpBackCount>0) || ((*bit).pattern>=0&&(*bit).pattern<=1&&SpBackCount==0))	flag = 2;
		else			flag = 4;
		/*
		if(Player[0].stage==1)		flag = 2;
		else if(Player[0].stage==2)	flag = 4;
		else if(Player[0].stage==3 && Boss.size()==0)	flag = 2;
		else if(Player[0].stage==3 && Boss.size()>0)	flag = 4;
		*/
		for(list<EFFECTDATA>::iterator it=Effect3.begin(); it!=Effect3.end(); ++it){
			it = Effect3.erase(it);
			it--;
			continue;			
		}
		for(list<EFFECTDATA>::iterator it=Effect.begin(); it!=Effect.end(); ++it){
			if((*it).pattern==13){
				it = Effect.erase(it);
				it--;
				continue;			
			}
		}
	}

	int total=0;
	if(flag==3 || flag==4){
		for(list<ENEMYDATA>::iterator eit=Enemy.begin(); eit!=Enemy.end(); ++eit){
			EfMake((*eit).x, (*eit).y, 3, 4);
			eit = Enemy.erase(eit);
			eit--;
			continue;			
		}
	}
	for(list<ESHOTDATA>::iterator eit=EShot.begin(); eit!=EShot.end(); ++eit){
		float dx = (*eit).x-sx;
		float dy = (*eit).y-sy;
		float d = sqrt(dx*dx+dy*dy);
		int late = d/7.5;
		if(flag==0 || flag==3 || flag==5){
			EfMake((*eit).x, (*eit).y, (*eit).img, 9);
			eit = EShot.erase(eit);
			eit--;
			continue;
		}
		else if(flag==1){
			EfMake((*eit).x, (*eit).y, (*eit).img, 9); 
			IMake((*eit).x, (*eit).y, 0, late);
			eit = EShot.erase(eit);
			eit--;
			continue;
		}
		else if(flag==2 || flag==4){
			EfMake((*eit).x, (*eit).y, (*eit).img, 9);
			int item = 0;
			if(Boss.size()>0){
				if(Player[0].spcard==1)		item = 1;
				else if(Player[0].spcard==2)	item = 2;
			}
			else{
				if(Player[0].hyper_count>0)	item = 2;
				//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
			} 
			IMake((*eit).x, (*eit).y, item, late);
			total++;
			eit = EShot.erase(eit);
			eit--;
			continue;
		}
	}
	for(list<ELASERDATA>::iterator eit=ELaser.begin(); eit!=ELaser.end(); ++eit){
		if((*eit).length[0]>=1)	(*eit).bDraw = false;
		if(flag==0 || flag==3){
			for(int i=0;i<(*eit).length[0]/16;i++){
				float x = (*eit).x[0][4] + 16*i*cos(Radian((*eit).angle,TRUE));
				float y = (*eit).y[0][4] + 16*i*sin(Radian((*eit).angle,TRUE));
				EfMake(x, y, (*eit).img, 9);
			}
			eit = ELaser.erase(eit);
			eit--;
			continue;
		}
		else if(flag==5){
			for(int i=0;i<(*eit).length[0]/16;i++){
				float x = (*eit).x[0][4] + 16*i*cos(Radian((*eit).angle,TRUE));
				float y = (*eit).y[0][4] + 16*i*sin(Radian((*eit).angle,TRUE));
				EfMake(x, y, (*eit).img, 9);
			}
			(*eit).length[0] = 0;
			(*eit).length[1] = 0;
		}
		else if(flag==1){
			for(int i=0;i<(*eit).length[0]/16;i++){
				float x = (*eit).x[0][4] + 16*i*cos(Radian((*eit).angle,TRUE));
				float y = (*eit).y[0][4] + 16*i*sin(Radian((*eit).angle,TRUE));
				float dx = x-sx;
				float dy = y-sy;
				float d = sqrt(dx*dx+dy*dy);
				int late = d/7.5;
				EfMake(x, y, (*eit).img, 9);
				if(y>0){
					int item = 0;
					if(Boss.size()>0){
						if(Player[0].spcard==1)		item = 1;
						else if(Player[0].spcard==2)	item = 2;
					}
					else{
						if(Player[0].hyper_count>0)	item = 2;
						//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
					} 
					IMake(x, y, item, late);
				}
			}
			(*eit).length[0] = 0;
			(*eit).length[1] = 0;
		}
		else if(flag==2 || flag==4){
			for(int i=0;i<(*eit).length[0]/16;i++){
				float x = (*eit).x[0][4] + 16*i*cos(Radian((*eit).angle,TRUE));
				float y = (*eit).y[0][4] + 16*i*sin(Radian((*eit).angle,TRUE));
				float dx = x-sx;
				float dy = y-sy;
				float d = sqrt(dx*dx+dy*dy);
				int late = d/7.5;
				EfMake(x, y, (*eit).img, 9);
				if(y>0){
					int item = 0;
					if(Boss.size()>0){
						if(Player[0].spcard==1)		item = 1;
						else if(Player[0].spcard==2)	item = 2;
					}
					else{
						if(Player[0].hyper_count>0)	item = 2;
						//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
					} 
					IMake(x, y, item, late);
				}
				total++;
			}
			eit = ELaser.erase(eit);
			eit--;
			continue;
		}
	}
	for(list<ESLASERDATA>::iterator eit=ESLaser.begin(); eit!=ESLaser.end(); ++eit){
		if((*eit).type==0){
			int loop;
			if((*eit).length[0]>(*eit).length[1])	loop = (*eit).length[1];
			else					loop = (*eit).length[0];
			if(flag==0 || flag==3 || flag==5){
				for(int i=0;i<loop/16;i++){
					float x = (*eit).edge_x[0] + 16*i*cos((*eit).angle);
					float y = (*eit).edge_y[0] + 16*i*sin((*eit).angle);
					EfMake(x, y, ESHOT(MEDIUM,(*eit).img%8), 9);
				}
				eit = ESLaser.erase(eit);
				eit--;
				continue;
			}
			else if(flag==1){
				for(int i=0;i<loop/16;i++){
					float x = (*eit).edge_x[0] + 16*i*cos((*eit).angle);
					float y = (*eit).edge_y[0] + 16*i*sin((*eit).angle);
					float dx = x-sx;
					float dy = y-sy;
					float d = sqrt(dx*dx+dy*dy);
					int late = d/7.5;
					EfMake(x, y, ESHOT(MEDIUM,(*eit).img%8), 9);
					if(y>0){
						int item = 0;
						if(Boss.size()>0){
							if(Player[0].spcard==1)		item = 1;
							else if(Player[0].spcard==2)	item = 2;
						}
						else{
							if(Player[0].hyper_count>0)	item = 2;
							//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
						} 
						IMake(x, y, item, late);
					}
				}
				eit = ESLaser.erase(eit);
				eit--;
				continue;
			}
			else if(flag==2 || flag==4){
				for(int i=0;i<loop/16;i++){
					float x = (*eit).edge_x[0] + 16*i*cos((*eit).angle);
					float y = (*eit).edge_y[0] + 16*i*sin((*eit).angle);
					float dx = x-sx;
					float dy = y-sy;
					float d = sqrt(dx*dx+dy*dy);
					int late = d/7.5;
					EfMake(x, y, ESHOT(MEDIUM,(*eit).img%8), 9);
					if(y>0){
						int item = 0;
						if(Boss.size()>0){
							if(Player[0].spcard==1)		item = 1;
							else if(Player[0].spcard==2)	item = 2;
						}
						else{
							if(Player[0].hyper_count>0)	item = 2;
							//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
						} 
						IMake(x, y, item, late);
					}
					total++;
				}
				eit = ESLaser.erase(eit);
				eit--;
				continue;
			}
		}
		else if((*eit).type==1){
			if(flag==0 || flag==3 || flag==5){
				for(int i=0;i<LASER_ELEMENT_NUM-1&&i<(*eit).count;i++){
					float x = (*eit).x[i];
					float y = (*eit).y[i];
					EfMake(x, y, ESHOT(MEDIUM,(*eit).img%8), 9);
				}
				eit = ESLaser.erase(eit);
				eit--;
				continue;
			}
			else if(flag==1){
				for(int i=0;i<LASER_ELEMENT_NUM-1&&i<(*eit).count;i++){
					float x = (*eit).x[i];
					float y = (*eit).y[i];
					float dx = x-sx;
					float dy = y-sy;
					float d = sqrt(dx*dx+dy*dy);
					int late = d/7.5;
					EfMake(x, y, ESHOT(MEDIUM,(*eit).img%8), 9);
					if(y>0){
						int item = 0;
						if(Boss.size()>0){
							if(Player[0].spcard==1)		item = 1;
							else if(Player[0].spcard==2)	item = 2;
						}
						else{
							if(Player[0].hyper_count>0)	item = 2;
							//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
						} 
						IMake(x, y, item, late);
					}
				}
				eit = ESLaser.erase(eit);
				eit--;
				continue;
			}
			else if(flag==2 || flag==4){
				for(int i=0;i<LASER_ELEMENT_NUM-1&&i<(*eit).count;i++){
					float x = (*eit).x[i];
					float y = (*eit).y[i];
					float dx = x-sx;
					float dy = y-sy;
					float d = sqrt(dx*dx+dy*dy);
					int late = d/7.5;
					EfMake(x, y, ESHOT(MEDIUM,(*eit).img%8), 9);
					if(y>0){
						int item = 0;
						if(Boss.size()>0){
							if(Player[0].spcard==1)		item = 1;
							else if(Player[0].spcard==2)	item = 2;
						}
						else{
							if(Player[0].hyper_count>0)	item = 2;
							//else if(Player[0].chara>=3 && Player[0].stress_gage>MAJIGIRE)	item = 1;
						} 
						IMake(x, y, item, late);
					}
					total++;
				}
				eit = ESLaser.erase(eit);
				eit--;
				continue;
			}
		}
	}
	if(flag==2 || flag==4){
		Player[0].hit += total;
		for(int i=0;i<total;i++){
			add_score(Player[0].soten/100);
		}
		Player[0].total_hit += total;
		Player[0].hit_gage = MAX_HIT_GAGE;
		Player[0].plus_hit = total;
		Player[0].plus_hit_count = 0;
	}
	return;
}

void SAtari(){
	list<BOSSDATA>::iterator bit = Boss.begin();
	for(list<ENEMYDATA>::iterator eit=Enemy.begin(); eit!=Enemy.end(); ++eit){
		if((*eit).move_pattern==6 || (*eit).move_pattern==7 || ((*eit).move_pattern>=27 && (*eit).move_pattern<=29) || (*eit).img==-1)	continue;
		//オーラと敵
		for(int i=0;i<PLAYER_NUM;i++){
			if((*eit).life<=0)	break;
			if(PLaser.size()==0)	break;
			float ssx = Player[i].x - (*eit).x;
			float ssy = Player[i].y - (*eit).y;
			float sq = sqrt(ssx*ssx+ssy*ssy);
			float ha =  (*eit).atari + 2.4*Player[0].slow_count;
			if(Player[0].hyper_count>0)	ha =  (*eit).atari + 4.0*Player[0].slow_count;
			if(sq<ha){
				(*eit).bDamage = true;
				add_score(10);
				if(Player[0].hyper_count==0)	EfMake((*eit).x, (*eit).y, 2, 1);
				else				EfMake((*eit).x, (*eit).y, 2, 3);
				if((*eit).bDelete==true && (*eit).bNoDamage==false){
					if((*eit).move_pattern>=37 && (*eit).move_pattern<=40){
						list<BOSSDATA>::iterator bit = Boss.begin();
						if(Player[0].hyper_count==0)	(*bit).life -= 10.0;
						else				(*bit).life -= 15.0;
					}
					if(Player[0].hyper_count==0)	(*eit).life -= 10.0;
					else				(*eit).life -= 15.0;
				}
				if(Player[0].hyper_count>0 && Player[0].hit_gage<MAX_HIT_GAGE/2)	Player[0].hit_gage = MAX_HIT_GAGE/2;
				else if(Player[0].hyper_count==0 && Player[0].hit_gage<MAX_HIT_GAGE/4)	Player[0].hit_gage = MAX_HIT_GAGE/4;
				bool bOK = false;
				if(Player[0].chara<=2 || Player[0].stress_gage<MAJIGIRE){
					if((Player[0].hyper_count==0&&Player[0].aura_count%10==0) || (Player[0].hyper_count>0&&Player[0].aura_count%2==0))	bOK = true;
				}
				else{
					if((Player[0].hyper_count==0&&Player[0].aura_count%5==0) || (Player[0].hyper_count>0&&Player[0].aura_count%1==0))	bOK = true;
				}
				if(bOK==true){
					if(Player[0].hyper_count>0)	IMake(Player[0].x, Player[0].y, 0);
					Player[0].hit++;
					Player[0].total_hit++;
					add_soten(1);
					add_score(Player[0].soten/100);
				}
				if(Player[0].hyper_count==0)	add_gage(30);
				else				add_gage(120);
				Player[0].aura_count++;
			}
		}
		if((*eit).bDelete==true){
			//自弾と敵
			for(list<PSHOTDATA>::iterator pit=PShot.begin(); pit!=PShot.end(); ++pit){
				if((*eit).life<=0)	break;
				float sx = (*pit).x - (*eit).x;
				float sy = (*pit).y - (*eit).y;
				float sq = sqrt(sx*sx+sy*sy);
				if(sq<(*pit).atari+(*eit).atari){
					(*eit).bDamage = true;
					if(Player[0].hyper_count==0)	EfMake((*pit).x, (*pit).y, 2, 0);
					else				EfMake((*pit).x, (*pit).y, 2, 2);
					if((*eit).bNoDamage==false){
						if((*eit).move_pattern>=37 && (*eit).move_pattern<=40){
							list<BOSSDATA>::iterator bit = Boss.begin();
							if(Player[0].hyper_count==0)	(*bit).life -= (*pit).atack;
							else				(*bit).life -= 2*(*pit).atack;
						}
						if(Player[0].hyper_count==0)	(*eit).life -= (*pit).atack;
						else				(*eit).life -= 2*(*pit).atack;
					}
					add_score(10);
					pit = PShot.erase(pit);
					pit--;
					continue;			
				}
			}
		}
		for(list<PLASERDATA>::iterator pit=PLaser.begin(); pit!=PLaser.end(); ++pit){
			//レーザーと敵
			if((*eit).life<=0)	break;
			float sq = fabs((*eit).x-(*pit).x[0]);
			float ha =  (*eit).atari + 1.5*(*pit).large;
			if(sq<=ha && (*pit).y[1]<(*eit).y && (*eit).y<(*pit).y[0]){
				(*eit).bDamage = true;
				add_score(10);
				if((*eit).bDelete==true && (*eit).bNoDamage==false){
					if((*eit).move_pattern>=37 && (*eit).move_pattern<=40){
						list<BOSSDATA>::iterator bit = Boss.begin();
						if(Player[0].hyper_count==0)	(*bit).life -= (*pit).atack;
						else				(*bit).life -= 2*(*pit).atack;
					}
					if(Player[0].hyper_count==0)	(*eit).life -= (*pit).atack;
					else				(*eit).life -= 2*(*pit).atack;
				}
				if((*eit).life>4){
					for(int j=0;j<3;j++){
						if(Player[0].hyper_count==0)	EfMake((*pit).x[1], (*pit).y[1], 2, 1);
						else				EfMake((*pit).x[1], (*pit).y[1], 2, 3);
					}
					(*pit).length = (*pit).y[0]-(*eit).y;
					(*pit).y[1] = (*eit).y;
					if(Player[0].hyper_count>0 && Player[0].hit_gage<MAX_HIT_GAGE/2)	Player[0].hit_gage = MAX_HIT_GAGE/2;
					else if(Player[0].hyper_count==0 && Player[0].hit_gage<MAX_HIT_GAGE/4)	Player[0].hit_gage = MAX_HIT_GAGE/4;
				}
				else{
					for(int j=0;j<3;j++){
						if(Player[0].hyper_count==0)	EfMake((*eit).x, (*eit).y, 2, 1);
						else				EfMake((*eit).x, (*eit).y, 2, 3);
					}
				}
				bool bOK = false;
				if(Player[0].chara<=2 || Player[0].stress_gage<MAJIGIRE){
					if((Player[0].hyper_count==0&&Player[0].laser_count%20==0) || (Player[0].hyper_count>0&&Player[0].laser_count%6==0))	bOK = true;
				}
				else{
					if((Player[0].hyper_count==0&&Player[0].laser_count%10==0) || (Player[0].hyper_count>0&&Player[0].laser_count%3==0))	bOK = true;
				}
				if(bOK==true){
					if(Player[0].hyper_count>0)	IMake((*pit).x[1], (*pit).y[1], 0);
					Player[0].hit++;
					Player[0].total_hit++;
					add_soten(1);
					add_score(Player[0].soten);
				}
				if(Player[0].hyper_count==0)	add_gage(1);
				else				add_gage(4);
				Player[0].laser_count++;
			}
		}
		for(list<BOMBDATA>::iterator pit=Bomb.begin(); pit!=Bomb.end(); ++pit){
			//ボムと敵
			if((*eit).life<=0)	break;
			float ssx = (*pit).x - (*eit).x;
			float ssy = (*pit).y - (*eit).y;
			float sq = sqrt(ssx*ssx+ssy*ssy);
			float ha =  (*eit).atari + (*pit).atari;
			if(sq<=ha){
				(*eit).bDamage = true;
				EfMake((*eit).x, (*eit).y, 2, 0);
				if((*eit).bDelete==true && (*eit).bNoDamage==false){
					if((*eit).move_pattern>=37 && (*eit).move_pattern<=40){
						list<BOSSDATA>::iterator bit = Boss.begin();
						(*bit).life -= (*pit).atack;
					}
					(*eit).life -= (*pit).atack;
				}
			}
			if((*eit).life<=0)	(*eit).bBomb = true;
		}
		//敵と敵
		for(list<ENEMYDATA>::iterator nit=Enemy.begin(); nit!=Enemy.end(); ++nit){
			if((*eit).life<=0)	break;
			if((*eit).img==18||(*eit).img==1||!((*eit).bAtari==false&&(*nit).img==18))	continue;
			float ssx = (*nit).x - (*eit).x;
			float ssy = (*nit).y - (*eit).y;
			float sq = sqrt(ssx*ssx+ssy*ssy);
			float ha =  2.0*(*eit).atari + 2.0*(*nit).atari;
			if(sq<ha){
				(*eit).life = 0;
				(*eit).bBomb = true;
			}
		}
		if((*eit).life<=0){
			//敵様ご臨終
			PlaySound(8);
			if((*eit).bBomb==false){
				SScore.enemy_num[Player[0].stage-1]++;
				SScore.enemy_num[STAGE_NUM]++;
				Player[0].hit_gage = MAX_HIT_GAGE;
				Player[0].hit++;
				Player[0].total_hit++;
				if(Player[0].hyper_count==0)	add_gage(300);
				add_soten((*eit).soten);
				add_score(Player[0].soten);
				if(Player[0].chara>=3/* && Player[0].hyper_count==0*/){
					if(Player[0].stress_gage>=MAJIGIRE){
						if((*eit).img==5 || (*eit).img==6 || (*eit).img==10 || (*eit).img==11 || (*eit).img==17 || (*eit).img==18 || (*eit).img==23)	SESDelete(2, (*eit).x, (*eit).y);
					}
				}
			}
			EfMake((*eit).x, (*eit).y, 3, 4);
			if((*eit).img==6){
				int ggx,ggy;
				GetGraphSize(gEnemy[(*eit).img], &ggx, &ggy);
				for(int i=0;i<10;i++)	IMake((*eit).x-ggx/2+get_rand(ggx), (*eit).y-ggy/2+get_rand(ggy), 3);			
			}
			else if((*eit).img==3){
				SESDelete(2, (*eit).x, (*eit).y);
			}
			if((*eit).move_pattern==4 || (*eit).move_pattern==23 || (*eit).move_pattern==24){
				for(int i=0;i<30;i++){
					EMake((*eit).x, (*eit).y, 2, 14, 5, 7);
				}
			}
			if(((*eit).shot_pattern>=25 && (*eit).shot_pattern<=27) || (*eit).shot_pattern==31 || (*eit).shot_pattern==32){//3面毛玉
				bES = true;
				bRG = true;		
				if((*eit).shot_pattern==25){
					int level = Player[0].level;
					if(level==BABY)	level = NORMAL;
					if(level==EASY){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 4, 6.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 1.0, 180);				
					}
					else if(level==NORMAL){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 6, 6.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 1.0, 180);				
					}
					else if(level==HARD){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 6, 6.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 1.0, 180);				
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 6, 1.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 0.0, 0, false);				
					}
					else if(level==LUNATIC){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 10, 8.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 1.0, 180);				
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 10, 1.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 0.0, 0, false);				
					}
					else if(level==IMPOSSIBLE){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 10, 10.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 1.0, 180);				
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 2.0, 10, 1.0, ESHOT(MEDIUM2,BLUE), false, 0, 10, 0.0, 0, false);				
					}
				}
				else if((*eit).shot_pattern==26 || (*eit).shot_pattern==27){
					int level = Player[0].level;
					if(level==BABY)	level = NORMAL;
					if(level==EASY){
						for(int i=0;i<5;i++){
							bool flag = false;
							if(i==0)	flag = true;
							ang_plus = 20.0 * (i-2);
							if((*eit).shot_pattern==27)	ang_plus *= -1;
							ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 0.0, 1, 2.0+0.4*i, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
						ang_plus = 0;
					}
					else if(level==NORMAL){
						for(int i=0;i<6;i++){
							bool flag = false;
							if(i==0)	flag = true;
							ang_plus = 15.0 * (i-2);
							if((*eit).shot_pattern==27)	ang_plus *= -1;
							ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 0.0, 1, 2.5+0.4*i, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
						ang_plus = 0;
					}
					else if(level==HARD){
						for(int i=0;i<10;i++){
							bool flag = false;
							if(i==0)	flag = true;
							ang_plus = 10.0 * (i-3);
							if((*eit).shot_pattern==27)	ang_plus *= -1;
							ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 10.0, 1, 3.0+0.4*i, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
						ang_plus = 0;
					}
					else if(level==LUNATIC){
						for(int i=0;i<12;i++){
							bool flag = false;
							if(i==0)	flag = true;
							ang_plus = 8.0 * (i-5);
							if((*eit).shot_pattern==27)	ang_plus *= -1;
							ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 10.0, 1, 3.0+0.4*i, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
						ang_plus = 0;
					}
					else if(level==IMPOSSIBLE){
						for(int i=0;i<20;i++){
							bool flag = false;
							if(i==0)	flag = true;
							ang_plus = 5.0 * (i-5);
							if((*eit).shot_pattern==27)	ang_plus *= -1;
							ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 8.0, 1, 4.0+0.4*i, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
						ang_plus = 0;
					}
				}
				else if((*eit).shot_pattern==31){
					int level = Player[0].level;
					if(level==BABY)	level = NORMAL;
					if(level==EASY){
						for(int i=0;i<10;i++){
							float d = 32.0;
							float angle = Radian(36.0*i,TRUE);
							ESNWay((*eit).x+d*cos(angle), (*eit).y+d*sin(angle), Player[0].x, Player[0].y, 0.0, 1, 3.0, ESHOT(MEDIUM2,RED), false, 0, 10+3*i);				
						}
					}
					else if(level==NORMAL){
						for(int i=0;i<15;i++){
							float d = 32.0;
							float angle = Radian(24.0*i,TRUE);
							ESNWay((*eit).x+d*cos(angle), (*eit).y+d*sin(angle), Player[0].x, Player[0].y, 0.0, 1, 4.0, ESHOT(MEDIUM2,RED), false, 0, 10+3*i);				
						}
					}
					else if(level==HARD){
						for(int i=0;i<20;i++){
							float d = 32.0;
							float angle = Radian(18.0*i,TRUE);
							ESNWay((*eit).x+d*cos(angle), (*eit).y+d*sin(angle), Player[0].x, Player[0].y, 0.0, 1, 5.0, ESHOT(MEDIUM2,RED), false, 0, 10+3*i);				
						}
					}
					else if(level==LUNATIC){
						for(int i=0;i<20;i++){
							float d = 32.0;
							float angle = Radian(18.0*i,TRUE);
							ESNWay((*eit).x+d*cos(angle), (*eit).y+d*sin(angle), Player[0].x, Player[0].y, 5.0, 2, 5.0, ESHOT(MEDIUM2,RED), false, 0, 10+3*i);				
						}
					}
					else if(level==IMPOSSIBLE){
						for(int i=0;i<20;i++){
							float d = 32.0;
							float angle = Radian(18.0*i,TRUE);
							ESNWay((*eit).x+d*cos(angle), (*eit).y+d*sin(angle), Player[0].x, Player[0].y, 20.0, 3, 5.0, ESHOT(MEDIUM2,RED), false, 0, 10+4*i);				
						}
					}
				}
				else if((*eit).shot_pattern==32){
					bRG = false;		
					int level = Player[0].level;
					if(level==BABY)	level = NORMAL;
					if(level==EASY){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 36.0, 10, 2.0, ESHOT(RICE,BLUE), false, 32, 10);				
					}
					else if(level==NORMAL){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 24.0, 15, 3.0, ESHOT(RICE,BLUE), false, 32, 10);				
					}
					else if(level==HARD){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 24.0, 15, 3.0, ESHOT(RICE,BLUE), false, 32, 10);				
					}
					else if(level==LUNATIC){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 24.0, 15, 5.0, ESHOT(RICE,BLUE), false, 32, 10);				
					}
					else if(level==IMPOSSIBLE){
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 24.0, 15, 3.0, ESHOT(RICE,BLUE), false, 32, 10);				
						ESNWay((*eit).x, (*eit).y, Player[0].x, Player[0].y, 24.0, 15, 5.0, ESHOT(RICE,BLUE), false, 32, 10);				
					}
				}
			}
			bES = false;
			bRG = false;		

			eit = Enemy.erase(eit);
			eit--;
			continue;			
		}
		for(int i=0;i<PLAYER_NUM;i++){
			//自機様ご臨終
			if(Player[i].miss_count>0 || Player[i].death_count>0 || Player[i].muteki_count>0 || ((*eit).bAtari==false&&Player[i].level!=BABY))	continue;
			float sx = Player[i].x - (*eit).x;
			float sy = Player[i].y - (*eit).y;
			float sq = sqrt(sx*sx+sy*sy);
			float ha = Player[i].atari + (*eit).atari;
			if(sq<ha+20 && Player[i].level==BABY){
				SScore.enemy_num[Player[0].stage-1]++;
				SScore.enemy_num[STAGE_NUM]++;
				Player[0].hit_gage = MAX_HIT_GAGE;
				Player[0].hit++;
				Player[0].total_hit++;
				if(Player[0].hyper_count==0)	add_gage(300);
				add_soten((*eit).soten);
				add_score(Player[0].soten);

				PlaySound(29);
				EfMake2((*eit).x, (*eit).y, gEnemy[(*eit).img], 2, 0.1*get_rand(3600));
				eit = Enemy.erase(eit);
				eit--;
				break;			
			}
			else if(sq<ha){
				PlaySound(3);
				Player[i].miss_count = 8;
			}
		}
	}
	for(list<BOSSDATA>::iterator eit=Boss.begin(); eit!=Boss.end(); ++eit){
		list<BOSSDATA>::iterator bit=Boss.begin();
		for(int i=0;i<(*eit).atari_num;i++){
			//オーラとボス
			for(int i=0;i<PLAYER_NUM;i++){
				if(PLaser.size()==0)	break;
				float ssx = Player[i].x - ((*eit).x+(*eit).atari[i].x);
				float ssy = Player[i].y - ((*eit).y+(*eit).atari[i].y);
				float sq = sqrt(ssx*ssx+ssy*ssy);
				float ha =  (*eit).atari[i].large + 2.4*Player[0].slow_count;
				if(Player[0].hyper_count>0)	ha =  (*eit).atari[i].large + 4.0*Player[0].slow_count;
				if(sq<ha){
					(*eit).bDamage = true;
					(*bit).bDamage = true;
					add_score(10);
					if(Player[0].hyper_count==0)	EfMake((*eit).x+(*eit).atari[i].x, (*eit).y+(*eit).atari[i].y, 2, 1);
					else				EfMake((*eit).x+(*eit).atari[i].x, (*eit).y+(*eit).atari[i].y, 2, 3);
					if((*eit).bMuteki==false && (*eit).muteki_count==0 && (*eit).bDelete==true && (*eit).count>60){
						if(Player[0].hyper_count==0)	(*bit).life -= 10.0;
						else				(*bit).life -= 15.0;
					}
					if(Player[0].hyper_count>0 && Player[0].hit_gage<MAX_HIT_GAGE/2)	Player[0].hit_gage = MAX_HIT_GAGE/2;
					else if(Player[0].hyper_count==0 && Player[0].hit_gage<MAX_HIT_GAGE/4)	Player[0].hit_gage = MAX_HIT_GAGE/4;
					bool bOK = false;
					if(Player[0].chara<=2 || Player[0].stress_gage<MAJIGIRE){
						if((Player[0].hyper_count==0&&Player[0].aura_count%10==0) || (Player[0].hyper_count>0&&Player[0].aura_count%2==0))	bOK = true;
					}
					else{
						if((Player[0].hyper_count==0&&Player[0].aura_count%5==0) || (Player[0].hyper_count>0&&Player[0].aura_count%1==0))	bOK = true;
					}
					if(bOK==true){
						if(Player[0].hyper_count>0){
							//IMake(Player[0].x, Player[0].y, 0);
							IMake((*eit).x, (*eit).y, 0);
						}
						Player[0].hit++;
						Player[0].total_hit++;
						//add_soten((*eit).soten);
						add_soten(1);
						add_score(Player[0].soten/100);
					}
					if(Player[0].hyper_count==0)	add_gage(30);
					else				add_gage(120);
					Player[0].aura_count++;
				}
			}
			if((*eit).bDelete==true && (*bit).life>0 && (*eit).bAtari==true){
				//自弾とボス
				for(list<PSHOTDATA>::iterator pit=PShot.begin(); pit!=PShot.end(); ++pit){
					float sx = (*pit).x - (*eit).x;
					float sy = (*pit).y - (*eit).y;
					float sq = sqrt(sx*sx+sy*sy);
					if(sq<(*pit).atari+(*eit).atari[i].large){
						(*eit).bDamage = true;
						(*bit).bDamage = true;
						if(Player[0].hyper_count==0)	EfMake((*pit).x, (*pit).y, 2, 0);
						else				EfMake((*pit).x, (*pit).y, 2, 2);
						if((*eit).bMuteki==false && (*eit).muteki_count==0 && (*eit).count>60){
							if(Player[0].hyper_count==0)	(*bit).life -= (*pit).atack;
							else				(*bit).life -= 2*(*pit).atack;
						}
						add_score(10);
						pit = PShot.erase(pit);
						pit--;
						continue;			
					}
				}
			}
			for(list<PLASERDATA>::iterator pit=PLaser.begin(); pit!=PLaser.end(); ++pit){
				//レーザーとボス
				float sq = fabs((*eit).x+(*eit).atari[i].x-(*pit).x[0]);
				float ha =  (*eit).atari[i].large + 1.5*(*pit).large;
				if(sq<=ha && (*pit).y[1]<(*eit).y+(*eit).atari[i].y && (*eit).y+(*eit).atari[i].y<(*pit).y[0]){
					(*eit).bDamage = true;
					(*bit).bDamage = true;
					add_score(10);
					if((*eit).bMuteki==false && (*eit).muteki_count==0 && (*eit).bDelete==true && (*eit).count>60){
						if(Player[0].hyper_count==0)	(*bit).life -= (*pit).atack;
						else				(*bit).life -= 2*(*pit).atack;
					}
					for(int j=0;j<3;j++){
						if(Player[0].hyper_count==0)	EfMake((*pit).x[1], (*pit).y[1], 2, 1);
						else				EfMake((*pit).x[1], (*pit).y[1], 2, 3);
					}
					(*pit).length = (*pit).y[0]-((*eit).y+(*eit).atari[i].y);
					(*pit).y[1] = (*eit).y+(*eit).atari[i].y;
					if(Player[0].hyper_count>0 && Player[0].hit_gage<MAX_HIT_GAGE/2)	Player[0].hit_gage = MAX_HIT_GAGE/2;
					else if(Player[0].hyper_count==0 && Player[0].hit_gage<MAX_HIT_GAGE/4)	Player[0].hit_gage = MAX_HIT_GAGE/4;
					bool bOK = false;
					if(Player[0].chara<=2 || Player[0].stress_gage<MAJIGIRE){
						if((Player[0].hyper_count==0&&Player[0].laser_count%20==0) || (Player[0].hyper_count>0&&Player[0].laser_count%6==0))	bOK = true;
					}
					else{
						if((Player[0].hyper_count==0&&Player[0].laser_count%10==0) || (Player[0].hyper_count>0&&Player[0].laser_count%3==0))	bOK = true;
					}
					if(bOK==true){
						if(Player[0].hyper_count>0)	IMake((*pit).x[1], (*pit).y[1], 0);
						Player[0].hit++;
						Player[0].total_hit++;
						add_soten((*eit).soten);
						add_score(Player[0].soten);
					}
					if(Player[0].hyper_count==0)	add_gage(30);
					else				add_gage(60);
					Player[0].laser_count++;
				}
			}
			for(list<BOMBDATA>::iterator pit=Bomb.begin(); pit!=Bomb.end(); ++pit){
				//ボムとボス
				float ssx = (*pit).x - ((*eit).x+(*eit).atari[i].x);
				float ssy = (*pit).y - ((*eit).y+(*eit).atari[i].y);
				float sq = sqrt(ssx*ssx+ssy*ssy);
				float ha =  (*eit).atari[i].large + (*pit).atari;
				if(sq<=ha){
					(*eit).bDamage = true;
					(*bit).bDamage = true;
					EfMake((*eit).x+(*eit).atari[i].x, (*eit).y+(*eit).atari[i].y, 2, 0);
					if((*eit).bMuteki==false && (*eit).muteki_count==0 && (*eit).bDelete==true && (*eit).count>60)	(*bit).life -= (*pit).atack;
				}
			}
			if((*bit).life<=0 && (*eit).death_count==0){
				//ボス様ご臨終
				int bossn = 0;
				bSun = false;
				for(list<EFFECTDATA>::iterator it=Effect.begin(); it!=Effect.end(); ++it){
					if((*it).pattern==14){
						it = Effect.erase(it);
						it--;
						continue;					
					}
				}
				for(list<BOSSDATA>::iterator ait=Boss.begin();ait!=Boss.end();++ait){
					(*ait).life = 0;
					bossn++;
					if(bossn!=1){
						EfMake((*ait).x, (*ait).y, 3, 4);
						ait = Boss.erase(ait);
						ait--;
						continue;			
					}
				}
				if(NowPart==BOSS)	BOSSERASENUM++;
				if((*bit).bSpell==true && SpBonus>0 && BossCount>0){
					PlaySound(26);
					Player[0].spcard = 2;
					add_score(SpBonus);
					GetSpBonus = SpBonus;
					GetSpBonusCount = 1;
					SScore.spell_num++;
					SScore.score_spcard[SpNum] = SpBonus;					
					if(replay_play==false){
						if(Player[0].level!=BABY && Player[0].level!=IMPOSSIBLE)	SAVE.SpGet[Player[0].chara][SpNum]++;					
					}
				}
				else if((*bit).bSpell==false && NmBonus>0 && BossCount>0){
					Player[0].spcard = 1;
				}
				else{
					Player[0].spcard = 0;
				}
				SpBackCount = 0;
				if((*bit).now_numB+1<ATACK_NUMB && (*bit).atack[(*bit).now_numA][(*bit).now_numB+1].life>0){
					EfMake((*bit).x, (*bit).y, 5, 5);
					SESDelete(2, (*bit).x, (*bit).y);
					(*bit).now_numB++;
					(*bit).life = (*bit).atack[(*bit).now_numA][(*bit).now_numB].life;
					(*bit).max_life = (*bit).atack[(*bit).now_numA][(*bit).now_numB].life;
					(*bit).defence = (*bit).atack[(*bit).now_numA][(*bit).now_numB].defence;
					(*bit).pattern = (*bit).atack[(*bit).now_numA][(*bit).now_numB].pattern;
					(*bit).count = 0;
					(*bit).move_count = 0;
					(*bit).bSpell = (*bit).atack[(*bit).now_numA][(*bit).now_numB].bSpell;
					if((*bit).bSpell==false&&BossCount>0)	PlaySound(18);
					SpNum = (*bit).pattern;
					SpellCount = 0;
					BossCount = (*bit).atack[(*bit).now_numA][(*bit).now_numB].count*60;
					for(int i=0;i<8;i++){
						(*bit).f_hanyou[i] = 0;
						(*bit).i_hanyou[i] = 0;
					}
				}
				else if((*bit).now_numA+1<ATACK_NUMA && (*bit).atack[(*bit).now_numA+1][0].life>0){
					BGcount3 = 0;
					int ggx,ggy;
					GetGraphSize(gBoss[(*bit).img], &ggx, &ggy);
					for(int i=0;i<20;i++)	IMake((*bit).x-ggx/2+get_rand(ggx), (*bit).y-ggy/2+get_rand(ggy), 3);			
					EfMake((*bit).x, (*bit).y, 5, 5);
					SESDelete(2, (*bit).x, (*bit).y);
					(*bit).ship--;
					(*bit).now_numA++;
					(*bit).now_numB = 0;
					(*bit).life = (*bit).atack[(*bit).now_numA][(*bit).now_numB].life;
					(*bit).max_life = (*bit).atack[(*bit).now_numA][(*bit).now_numB].life;
					(*bit).defence = (*bit).atack[(*bit).now_numA][(*bit).now_numB].defence;
					(*bit).pattern = (*bit).atack[(*bit).now_numA][(*bit).now_numB].pattern;
					(*bit).count = 0;
					(*bit).move_count = 0;
					(*bit).bSpell = (*bit).atack[(*bit).now_numA][(*bit).now_numB].bSpell;
					if((*bit).bSpell==false&&BossCount>0)	PlaySound(18);
					SpNum = (*bit).pattern;
					SpellCount = 0;
					BossCount = (*bit).atack[(*bit).now_numA][(*bit).now_numB].count*60;
					for(int i=0;i<8;i++){
						(*bit).f_hanyou[i] = 0;
						(*bit).i_hanyou[i] = 0;
					}
				}
				else{
					(*bit).life = 0;
				}
				goto LABEL_A;
			}
			else if((*bit).life<=0){
				(*bit).life = 0;
				SpBackCount = 0;
				goto LABEL_A;
			}
			bool out = false;
			for(int i=0;i<PLAYER_NUM;i++){
				//自機様ご臨終
				if((*eit).life<=0 || (*eit).bAtari==false || bTalk==true)	break;
				if(Player[i].miss_count>0 || Player[i].death_count>0 || Player[i].muteki_count>0 || (*eit).bAtari==false)	continue;
				float sx = Player[i].x - ((*eit).x+(*eit).atari[i].x);
				float sy = Player[i].y - ((*eit).y+(*eit).atari[i].y);
				float sq = sqrt(sx*sx+sy*sy);
				float ha = Player[i].atari + (*eit).atari[i].large;
				if(sq<ha+20 && Player[i].level==BABY){
					PlaySound(29);
					(*eit).life = 0;
					EfMake2((*eit).x, (*eit).y, gBoss[(*eit).img], 3, 0.1*get_rand(3600));
					if((*eit).img==1)	TMake(1);
					else if((*eit).img==4)	TMake(3);
					else if((*eit).img==5)	TMake(5);
					if((*bit).life<=0){
						SpellCount = 0;
						SpBackCount = 0;
					}
					eit = Boss.erase(eit);
					eit--;
					out = true;
					break;			
				}
				else if(sq<ha){
					PlaySound(3);
					Player[i].miss_count = 8;
				}
			}
			if(out==false){
				if((*eit).bDamage==true)	break;
			}
		}
	}
LABEL_A:
	for(list<ESHOTDATA>::iterator eit=EShot.begin(); eit!=EShot.end(); ++eit){
		if((*eit).count<0 || (*eit).bMove==true)	continue;
		bool bDe = false, out = false;
		for(int i=0;i<PLAYER_NUM;i++){
			//自機様ご臨終
			if(Player[i].miss_count>0 || Player[i].death_count>0)	continue;
			float sx = Player[i].x - (*eit).x;
			float sy = Player[i].y - (*eit).y;
			float sq = sqrt(sx*sx+sy*sy);
			float ha = Player[i].atari + (*eit).atari;
			if(Player[0].chara>=3 && (*eit).bGraze==false && sq<(*eit).kasuri){
				(*eit).bGraze = true;
				Player[0].graze_count = 60;
				if(Boss.size()==0)	add_stress_gage(MAX_STRESS_GAGE/100);
				else			add_stress_gage(MAX_STRESS_GAGE/200);
				PlaySound(34);
				EfMake((*eit).x, (*eit).y, 2, 15);
			}
			if(sq<ha+20 && Player[i].level==BABY){
				SScore.enemyshot_num[Player[0].stage-1]++;
				SScore.enemyshot_num[STAGE_NUM]++;
				Player[0].hit_gage = MAX_HIT_GAGE;
				Player[0].hit++;
				Player[0].total_hit++;
				add_soten((*eit).soten);
				add_score(Player[0].soten/10);

				PlaySound(29);
				if((*eit).img<0)	EfMake2((*eit).x, (*eit).y, gEShot2[-6*((*eit).img+1)+(*eit).count/2%6], 2, Radian(Atan2((*eit).move_y,(*eit).move_x),FALSE)+180,(*eit).bBlend);
				else			EfMake2((*eit).x, (*eit).y, gEShot[(*eit).img], 2, Radian(Atan2((*eit).move_y,(*eit).move_x),FALSE)+180,(*eit).bBlend);
				eit = EShot.erase(eit);
				eit--;
				out = true;
				break;			
			}
			else if(sq<ha){
				if(Player[i].muteki_count==0){
					PlaySound(3);
					Player[i].miss_count = 8;
				}
				bDe = true;
				break;
			}
		}
		if(out==true)	continue;
		if(bDe==true){
			EfMake((*eit).x, (*eit).y, (*eit).img, 9);
			eit = EShot.erase(eit);
			eit--;
			continue;			
		}
		if(Player[0].hyper_count>0 && (*eit).bDelete==true){
			bool bD = false;
			for(list<PSHOTDATA>::iterator pit=PShot.begin(); pit!=PShot.end(); ++pit){
				//敵弾様ご臨終
				float sx = (*pit).x - (*eit).x;
				float sy = (*pit).y - (*eit).y;
				float sq = sqrt(sx*sx+sy*sy);
				if(sq<(*pit).atari+(*eit).atari){
					//(*eit).bMove = true;
					if(BossCount==0 || (*bit).bSpell==false){
						if(Player[0].hyper_count==0)	EfMake((*pit).x, (*pit).y, 2, 0);
						else				EfMake((*pit).x, (*pit).y, 2, 2);
						(*pit).life --;
						(*eit).life --;
						add_score(10);
					}
					else{
						//IMake((*eit).x, (*eit).y, 0);
					}
					if((*pit).life<=0){
						pit = PShot.erase(pit);
						pit--;
					}
					if((*eit).life<=0){
						bD = true;
						break;
					}
					break;			
				}
			}
			if(bD==true && (*eit).bHyper==false){
				SScore.enemyshot_num[Player[0].stage-1]++;
				SScore.enemyshot_num[STAGE_NUM]++;
				//Player[0].hit_gage = MAX_HIT_GAGE;
				Player[0].hit_gage += MAX_HIT_GAGE/20;
				if(Player[0].hit_gage>MAX_HIT_GAGE)	Player[0].hit_gage = MAX_HIT_GAGE;
				if(Player[0].chara<=2){
					Player[0].hit++;
					Player[0].total_hit++;
					add_soten((*eit).soten);
					add_score(Player[0].soten/100);
				}
				EfMake((*eit).x, (*eit).y, (*eit).img, 9);
				IMake((*eit).x, (*eit).y, 0);
				(*eit).bHyper = true;
				eit = EShot.erase(eit);
				eit--;
				continue;			
			}
		}
	}
	for(list<ELASERDATA>::iterator eit=ELaser.begin(); eit!=ELaser.end(); ++eit){
		//オーラとレーザー
		for(int i=0;i<PLAYER_NUM;i++){
			if(PLaser.size()==0)	break;
			int loop = (*eit).length[0]/1;
			for(int j=0;j<loop;j+=5){
				float atari = (*eit).size[0]*0.2;
				if((float)j/(float)loop<0.2){
					atari *= 5.0*(float)j/(float)loop;
				}
				else if((float)(loop-j)/(float)loop<0.2){
					atari *= 5.0*(float)(loop-j)/(float)loop;
				}
				float ex = (*eit).x[0][4] + j*cos(Radian((*eit).angle,TRUE));
				float ey = (*eit).y[0][4] + j*sin(Radian((*eit).angle,TRUE));
				float ssx = Player[i].x - ex;
				float ssy = Player[i].y - ey;
				float sq = sqrt(ssx*ssx+ssy*ssy);
				float ha =  atari + 2.4*Player[0].slow_count;
				if(Player[0].hyper_count>0)	ha =  atari*1.4 + 4.0*Player[0].slow_count;
				if(sq<ha){
					add_score(10);
					(*eit).length[0] = j*1.0;
					(*eit).length[1] = j*1.0;
					if(Player[0].hyper_count==0)	EfMake(ex, ey, 2, 1);
					else				EfMake(ex, ey, 2, 3);
					if(Player[0].hyper_count>0 && Player[0].hit_gage<MAX_HIT_GAGE/2)	Player[0].hit_gage = MAX_HIT_GAGE/2;
					else if(Player[0].hyper_count==0 && Player[0].hit_gage<MAX_HIT_GAGE/4)	Player[0].hit_gage = MAX_HIT_GAGE/4;
					bool bOK = false;
					if(Player[0].chara<=2 || Player[0].stress_gage<MAJIGIRE){
						if((Player[0].hyper_count==0&&Player[0].aura_count%10==0) || (Player[0].hyper_count>0&&Player[0].aura_count%2==0))	bOK = true;
					}
					else{
						if((Player[0].hyper_count==0&&Player[0].aura_count%5==0) || (Player[0].hyper_count>0&&Player[0].aura_count%1==0))	bOK = true;
					}
					if(bOK==true){
						if(Player[0].hyper_count>0)	IMake(ex, ey, 0);
						Player[0].hit++;
						Player[0].total_hit++;
						add_soten(1);
						add_score(Player[0].soten/100);
					}
					/*
					if(Player[0].hyper_count==0)	add_gage(15);
					else				add_gage(60);
					*/
					if(Player[0].hyper_count==0)	add_gage(5);
					else				add_gage(10);
					Player[0].aura_count++;
					EfMake(ex, ey, (*eit).img, 9); 
					(*eit).bDraw = false;
					break;
				}
			}
		}
		for(list<PLASERDATA>::iterator pit=PLaser.begin(); pit!=PLaser.end(); ++pit){
			//レーザー干渉レーザー
			int loop = (*eit).length[0]/1;
			for(int j=0;j<loop;j+=5){
				float ex = (*eit).x[0][4] + j*cos(Radian((*eit).angle,TRUE));
				float ey = (*eit).y[0][4] + j*sin(Radian((*eit).angle,TRUE));
				float sq = fabs(ex-(*pit).x[0]);
				float ha = (*pit).large;
				if(sq<ha && (*pit).y[1]<ey && ey<(*pit).y[0]){
					add_score(10);
					for(int j=0;j<3;j++){
						if(Player[0].hyper_count==0)	EfMake(ex, ey, 2, 1);
						else				EfMake(ex, ey, 2, 3);
					}
					(*eit).length[0] = j*1.0;
					(*eit).length[1] = j*1.0;
					if(Player[0].hyper_count>0 && Player[0].hit_gage<MAX_HIT_GAGE/2)	Player[0].hit_gage = MAX_HIT_GAGE/2;
					else if(Player[0].hyper_count==0 && Player[0].hit_gage<MAX_HIT_GAGE/4)	Player[0].hit_gage = MAX_HIT_GAGE/4;
					bool bOK = false;
					if(Player[0].chara<=2 || Player[0].stress_gage<MAJIGIRE){
						if((Player[0].hyper_count==0&&Player[0].laser_count%20==0) || (Player[0].hyper_count>0&&Player[0].laser_count%6==0))	bOK = true;
					}
					else{
						if((Player[0].hyper_count==0&&Player[0].laser_count%10==0) || (Player[0].hyper_count>0&&Player[0].laser_count%3==0))	bOK = true;
					}
					if(bOK==true){
						if(Player[0].hyper_count>0)	IMake(ex, ey, 0);
						Player[0].hit++;
						Player[0].total_hit++;
						add_soten(1);
						add_score(Player[0].soten/100);
					}
					if(Player[0].hyper_count==0)	add_gage(1);
					else				add_gage(2);//8);
					Player[0].laser_count++;
					EfMake(ex, ey, (*eit).img, 9); 
					(*eit).bDraw = false;
					break;
				}
			}
		}
		bool bDe = false;
		for(int i=0;i<PLAYER_NUM;i++){
			//自機様レーザーにて没
			if(Player[i].miss_count>0 || Player[i].death_count>0 || Player[i].level==BABY)	continue;
			int loop = (*eit).length[0]/1;
			for(int j=0;j<loop;j+=8){
				float atari = (*eit).size[0]*0.2;
				if((float)j/(float)loop<0.2){
					atari *= 8.0*(float)j/(float)loop;
				}
				else if((float)(loop-j)/(float)loop<0.2){
					atari *= 8.0*(float)(loop-j)/(float)loop;
				}
				float ex = (*eit).x[0][4] + j*cos(Radian((*eit).angle,TRUE));
				float ey = (*eit).y[0][4] + j*sin(Radian((*eit).angle,TRUE));
				float sx = Player[i].x - ex;
				float sy = Player[i].y - ey;
				float sq = sqrt(sx*sx+sy*sy);
				float ha = Player[i].atari + atari;
				if(sq<ha){
					EfMake(ex, ey, (*eit).img, 9);
					if(Player[i].muteki_count==0){
						PlaySound(3);
						Player[i].miss_count = 8;
					}
					bDe = true;
					break;
				}
			}
			if(bDe==true)	break;
		}
	}
	for(list<ESLASERDATA>::iterator eit=ESLaser.begin(); eit!=ESLaser.end(); ++eit){
		for(int i=0;i<PLAYER_NUM;i++){
			//自機様へにょりレーザーにて没
			if(Player[i].miss_count>0 || Player[i].death_count>0 || Player[i].level==BABY)	continue;
			if((*eit).type==0){
				int loop;
				if((*eit).length[0]>(*eit).length[1])	loop = (*eit).length[1];
				else					loop = (*eit).length[0];
				for(int j=0;j<loop;j+=8){
					float atari = (*eit).size*0.2;
					if((float)j/(float)loop<0.2){
						atari *= 8.0*(float)j/(float)loop;
					}
					else if((float)(loop-j)/(float)loop<0.2){
						atari *= 8.0*(float)(loop-j)/(float)loop;
					}
					float ex = (*eit).edge_x[0] + j*cos((*eit).angle);
					float ey = (*eit).edge_y[0] + j*sin((*eit).angle);
					float sx = Player[i].x - ex;
					float sy = Player[i].y - ey;
					float sq = sqrt(sx*sx+sy*sy);
					float ha = Player[i].atari + atari;
					if(sq<ha){
						EfMake(ex, ey, (*eit).img, 9);
						if(Player[i].muteki_count==0){
							PlaySound(3);
							Player[i].miss_count = 8;
						}
						break;
					}
				}
			}
			if((*eit).type==1){
				bool end = false;
				for(int j=0;j<LASER_ELEMENT_NUM-1&&j<(*eit).count;j++){
					float dx = (*eit).x[j] - (*eit).x[j+1];
					float dy = (*eit).y[j] - (*eit).y[j+1];
					float d = sqrt(dx*dx+dy*dy);
					int loop = d/8.0 + 1;
					float num = Radian(90.0/(float)(LASER_ELEMENT_NUM/2.0)*fabs(j-LASER_ELEMENT_NUM/2.0), TRUE);
					float size = (*eit).size * cos(num);
					for(int a=0;a<loop;a++){
						float ex = (*eit).x[j+1] + 5.0*a*dx/d;
						float ey = (*eit).y[j+1] + 5.0*a*dy/d;
						float sx = Player[i].x - ex;
						float sy = Player[i].y - ey;
						float sq = sqrt(sx*sx+sy*sy);
						float ha = Player[i].atari + size;
						if(sq<ha){
							EfMake(ex, ey, (*eit).img, 9);
							if(Player[i].muteki_count==0){
								PlaySound(3);
								Player[i].miss_count = 8;
							}
							end = true;
							break;
						}
					}
					if(end==true)	break;
				}
			}
		}
	}
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].miss_count>0 || Player[i].death_count>0)	continue;
		for(list<ITEMDATA>::iterator it=Item.begin(); it!=Item.end(); ++it){
			if((*it).count<0)	continue;
			float sx = Player[i].x - (*it).x;
			float sy = Player[i].y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			float ha = Player[i].atari + (*it).atari;
			if(sq<ha && ((*it).img!=0||(*it).count>40)){
				PlaySound(14);
				if((*it).img==0 || (*it).img==1 || (*it).img==2){
					SScore.item_num[(*it).img][Player[0].stage-1]++;
					SScore.item_num[(*it).img][STAGE_NUM]++;
					Player[0].graze_count = 60;
					//add_soten((*it).soten);
					int add = Player[0].soten/pow(10,2-(*it).img);
					add_score(add);
					//if(Player[0].hit>0)	EfMake2(Player[0].x, Player[0].y, add/10*10, 0);
				}
				else if((*it).img==3){
					if(Player[0].hyper_gage==MAX_GAGE){
						add_score(1000000);
						EfMake2(Player[0].x, Player[0].y, 1000000, 1);
					}
					else{
						add_score(100000);
						add_gage(500);
						EfMake2(Player[0].x, Player[0].y, 100000, 1);
					}
				}
				else if((*it).img==4){
					if((Player[0].chara<=2 && Player[0].bomb_num<8) || (Player[0].chara>=3 && ((Player[0].bomb_num<3&&Player[0].level!=IMPOSSIBLE) || Player[0].bomb_num<1))){
						PlaySound(26);
						Player[0].bomb_num++;
					}
				}
				else if((*it).img==5){
					bool flag = false;
					if(Player[0].ship_num<8){
						Player[0].ship_num++;
						flag = true;
					}
					else if((Player[0].chara<=2 && Player[0].bomb_num<8) || (Player[0].chara>=3 && ((Player[0].bomb_num<3&&Player[0].level!=IMPOSSIBLE) || Player[0].bomb_num<1))){
						Player[0].bomb_num++;
						flag = true;
					}
					if(flag==true){
						PlaySound(30);
						Ecount = 1;
					}
				}
				it = Item.erase(it);
				it--;
				continue;
			}
			else if(sq<200.0 && (*it).pattern!=3){
				(*it).pattern = 1;
			}
		}
	}

	return;
}

void DrawGage(){
	float plus = 0.5*pow(GageCount-20,2);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	SetDrawBright(255, 255, 255);
	if(Player[0].hit2==0){
		if(Player[0].plus_hit>0){
			Player[0].plus_hit_count++;
			if(Player[0].plus_hit_count<90){
				if(Player[0].plus_hit_count<60){
					SetDrawBright(100, 255, 100);
					draw_hit(30-plus, 125, Player[0].plus_hit, 0);			
				}
				else if(Player[0].plus_hit_count<90){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(90-Player[0].plus_hit_count));
					SetDrawBright(100, 255, 100);
					draw_hit(30-plus, 80+0.05*pow((Player[0].plus_hit_count-60)-30,2), Player[0].plus_hit, 0);			
				}
			}
			else{
				Player[0].plus_hit = 0;
				Player[0].plus_hit_count = 0;
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawBright(255, 255, 255);
		if(Player[0].rate_soten>0)	SetDrawBright(150, 150, 255);
		draw_hit(30-plus, 80, Player[0].hit, 0);
		if(GetSkip())	DrawGraphF(30-plus, 50, gScore[10], TRUE);
		draw_score(41-plus, 50, Player[0].soten, 0, false);
	}
	else{
		float xplus = 0;
		if(Player[0].hit2_count<60)	xplus = 4*(60-Player[0].hit2_count);
		draw_hit(30-plus-xplus, 80, Player[0].hit2, 0);
		if(Player[0].hit2_count>=100)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(120-Player[0].hit2_count));
		draw_hit(30-plus-xplus, 80, Player[0].hit2, 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(GetSkip())	DrawGraphF(30-plus-xplus, 50, gScore[10], TRUE);
		draw_score(41-plus-xplus, 50, Player[0].soten2, 0, false);
		if(Player[0].hit2_count>=100)	SetDrawBright(255, 255-12*(120-Player[0].hit2_count), 255-12*(120-Player[0].hit2_count));
		else				SetDrawBright(255, 15, 15);
		if(GetSkip())	DrawGraphF(30-plus-xplus, 50, gScore[10], TRUE);
		draw_score(41-plus-xplus, 50, Player[0].soten2, 0, false);

		Player[0].hit2_count--;
		if(Player[0].hit2_count==0)	Player[0].hit2 = 0;
	}
	SetDrawBright(255-255*(float)Player[0].hit_gage/(float)MAX_HIT_GAGE, 255*(float)Player[0].hit_gage/(float)MAX_HIT_GAGE, 50);
	if(GetSkip())	DrawExtendGraph(10-plus, 100-60.0*(float)Player[0].hit_gage/MAX_HIT_GAGE, 30-plus, 100, gGage, FALSE);
	SetDrawBright(255, 255, 255);
	DrawBox(10-plus, 40, 30-plus, 100, GetColor(255,255,255), FALSE);

	if(Player[0].hyper_gage<MAX_GAGE)	SetDrawBright(255, 255, 255);
	else{
		if(Player[0].count%9<3)		SetDrawBright(255, 255, 50);
		else if(Player[0].count%9<6)	SetDrawBright(255, 50, 50);
		else				SetDrawBright(255, 255, 255);
	}
	if(GetSkip())	DrawExtendGraph(10-plus, 110, 10.0+120.0*(float)Player[0].hyper_gage/(float)MAX_GAGE-plus, 118, gGage, FALSE);
	SetDrawBright(255, 255, 255);
	DrawBox(10-plus, 110, 130-plus, 118, GetColor(255,255,255), FALSE);

	if(Player[0].hyper_gage<MAX_GAGE)	SetDrawBright(255, 255, 255);
	else{
		if(Player[0].count%9<3)		SetDrawBright(255, 255, 50);
		else if(Player[0].count%9<6)	SetDrawBright(255, 50, 50);
		else				SetDrawBright(255, 255, 255);
	}
	if(GetSkip())	DrawExtendGraph(10-plus, 110, 10.0+120.0*(float)Player[0].hyper_gage/(float)MAX_GAGE-plus, 118, gGage, FALSE);
	SetDrawBright(255, 255, 255);
	DrawBox(10-plus, 110, 130-plus, 118, GetColor(255,255,255), FALSE);	

	if(Player[0].chara>=3){
		if(Player[0].stress_gage<MAJIGIRE){
			if(Player[0].stress_count>0)	Player[0].stress_count--;
		}
		else{
			if(Player[0].stress_count<30)	Player[0].stress_count++;
		}
		SetDrawBright(75+6.0*Player[0].stress_count, 75, 255-6.0*Player[0].stress_count);
		if(GetSkip())	DrawExtendGraph(10-plus, 120, 10.0+150.0*(float)Player[0].stress_gage/(float)MAX_STRESS_GAGE-plus, 128, gGage, FALSE);
		SetDrawBright(255, 255, 255);
		DrawBox(10-plus, 120, 160-plus, 128, GetColor(255,255,255), FALSE);
	}

	if(Player[0].x<CENTER_X && Player[0].y<190){
		if(GageCount>0)	GageCount--;
	}
	else if(GageCount<20)	GageCount++;
	
	return;
}

int Loo(int rank0, int rank20){
	int r = Prank;
	if(Player[0].hyper_count>0)	Prank = 20;
	float up = (float)(rank0-rank20)/21.0*(float)(21-Prank);
	int iup = up;
	if(up-0.0001>iup)	iup++;
	int value = rank20 + iup;
	Prank = r;

	return value;
}

int Per(int rank0, int rank20){//弾を撃つ敵の割合
	int r = Prank;
	if(Player[0].hyper_count>0)	Prank = 20;
	float up = (float)(rank20-rank0)/21.0*(float)Prank;
	int iup = up;
	if(up-0.0001>iup)	iup++;
	int value = rank0 + iup;
	Prank = r;

	return value;
}