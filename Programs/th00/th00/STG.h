#ifndef __STG_H__
#define __STG_H__

#include "extern.h"
#include "bgm.h"

/*================================
	当たり判定について
　自機と敵機　　　SEn_Draw()
  自弾と敵機　　　SEn_Draw()
  自機と敵弾　　　SEs_Draw()
  ボムと敵弾　　　SEs_Draw()
  自機とアイテム　SIt_Draw()
  死亡時の余韻　　SPl_Death()
  自弾とボス　　　SPs_Draw()
  ボムとボス　　　SBos_Draw()
  自機とボス　　　SBos_Draw()
==================================*/
#define ATARI_NUM 2
#define HANYOU_NUM 8
#define PLAYER_IMG_NUM 4
#define ENEMY_IMG_COUNT_NUM 2
#define ENEMY_IMG_NUM 16
#define BOSS_MOVE_COUNT_NUM 2
#define BOSS_IMG_NUM 32
#define GRA_BACK_NUM 6
#define GRA_TITLE_NUM 8
#define GRA_OPTION_NUM 6
#define GRA_CONFIG_NUM 5
#define GRA_T_NUMBER_NUM 11
#define GRA_LEVEL_NUM 5
#define GRA_PLAYER_NUM 4
#define GRA_WEAPON_NUM 4
#define GRA_MENU_NUM 6
#define GRA_NUMBER_NUM 12
#define GRA_SIDE_NUM 14
#define SPELL_NAME_NUM 64
#define SPELL_TIMES_NUM 2
#define SCORE_STAGE_NUM 7
#define SCORE_NAME_NUM 8
#define LEVEL_SCORE_NUM 10
#define LEVEL_LEVEL_NUM 5
#define OPTION_NUM 4
#define T_EFFECT_NUM 50
#define SPELL_NUM 114
#define GRA_REIMU_NUM 3
#define GRA_MARISA_NUM 3
#define GRA_SHOT_REIMU_NUM 3
#define GRA_SHOT_MARISA_NUM 3
#define GRA_FAIRY_NUM_A 3
#define GRA_FAIRY_NUM_B 16
#define GRA_BIG_FAIRY_NUM 8
#define GRA_KEDAMA_NUM 3
#define GRA_CROW_NUM 8
#define GRA_E_SHOT_NUM 58
#define GRA_E_SHOT2_NUM 20
#define GRA_ITEM_NUM 6
#define GRA_STAGE_TITLE_NUM 4
#define GRA_STAGE_TITLE_NUM2 8
#define GRA_MUSIC_TITLE_NUM 11
#define GRA_BOSS_NAME_NUM 4
#define GRA_BOSS_NUM_A 4
#define GRA_BOSS_NUM_B 32
#define GRA_CATIN_NUM 4
#define GRA_SPELL_BACK_NUM 3
#define GRA_LASER_NUM 4
#define GRA_ENDING_NUM 1
#define REPLAY_ELEMENT_NUM 300000
#define REPLAY_FPS_NUM 5000
#define REPLAY_NUM 15
#define DIRECTOR_REPLAY_NUM 6
#define ZANZOU_NUM 20

//列挙
enum SCENE{
	TITLE,
	REPLAY,
	RESULT,
	MUSIC_ROOM,
	OPTION,
	KEY_CONFIG,
	SELECT_LEVEL,
	SELECT_PLAYER,
	SELECT_WEAPON,
	SHOOTING,
	ENDING,
	STAFFROLE,
	ENDSCORE,
	END	
};

//構造体・変数宣言
struct PLAYERDATA{
	float 	x,
		y,
		atari_x[ATARI_NUM],
		atari_y[ATARI_NUM],
		speed,
		large,
		d_hanyou[HANYOU_NUM];
	int	life,
		count,
		slow,
		miss,
		death,
		nodamage,
		img[PLAYER_IMG_NUM],
		img_x,
		img_y,
		img_num,
		flash,
		type,
		i_hanyou[HANYOU_NUM];
	bool	b_slow,
		b_control;
};
struct P_SHOTDATA{
	float 	x,
		y,
		atari_x[ATARI_NUM],
		atari_y[ATARI_NUM],
		move_x,
		move_y,
		angle,
		speed,
		large,
		d_hanyou[HANYOU_NUM];
	int	atack,
		count,
		flash,
		img,
		img_x,
		img_y,
		pattern,
		i_hanyou[HANYOU_NUM];		
};
struct BOMBDATA{
	float 	x,
		y,
		large,
		angle,
		d_hanyou[HANYOU_NUM];
	int	life,
		atack,
		count,
		flash,
		img,
		img_x,
		img_y,
		i_hanyou[HANYOU_NUM];		
};
struct OPTIONDATA{
	float 	x,
		y,
		angle,
		speed,
		large,
		d_hanyou[HANYOU_NUM];
	int	count,
		flash,
		img,
		img_x,
		img_y,
		pattern,
		i_hanyou[HANYOU_NUM];		
};
struct E_SHOTDATA{
	float 	x,
		y,
		atari_x[ATARI_NUM],
		atari_y[ATARI_NUM],
		move_x,
		move_y,
		angle,
		speed,
		large,
		f_speed,
		d_hanyou[HANYOU_NUM];
	int	effect,
		late,
		max_late,
		count,
		flash,
		img,
		img_x,
		img_y,
		pattern,
		dele_flag,
		f_count,
		i_hanyou[HANYOU_NUM];
	bool	graze,
		b_atari,
		debug_AI;		
};
struct ENEMYDATA{
	float	x,
		y,
		atari_x[ATARI_NUM],
		atari_y[ATARI_NUM],
		move_x,
		move_y,
		speed,
		large,
		angle,
		d_hanyou[HANYOU_NUM];
	int	life,
		count,
		img_count[ENEMY_IMG_COUNT_NUM],
		flash,
		img[ENEMY_IMG_NUM],
		img_x,
		img_y,
		img_num,
		move_pattern,
		shot_pattern,
		item_pattern,
		i_hanyou[HANYOU_NUM];
	bool	b_atari;
};
struct BOSSDATA{
	int	atari_x[ATARI_NUM],
		atari_y[ATARI_NUM];
	float 	x,
		y,
		move_x,
		move_y,
		angle,
		speed,
		large,
		d_hanyou[HANYOU_NUM];
	int	exist,
		gage_exist,
		zanki,
		life,
		life2,
		max_life,//通常攻撃のライフ
		spell_life,//スペルカードのライフ
		defence,
		damage,
		spell_num,
		move_count[BOSS_MOVE_COUNT_NUM],
		count,
		countdown,
		flash,
		img[BOSS_IMG_NUM],
		img_x,
		img_y,
		img_num,
		img_count,
		pattern,//0:スイカ 1:文 2:紫
		move_pattern,
		shot_pattern,
		item_pattern,
		i_hanyou[HANYOU_NUM];
	bool	b_atari,
		b_zanzou,
		b_muteki;
};
struct ITEMDATA{
	float 	x,
		y,
		atari_x[ATARI_NUM],
		atari_y[ATARI_NUM],
		move_x,
		move_y,
		angle,
		speed,
		large,
		d_hanyou[HANYOU_NUM];
	int	count,
		flash,
		img,
		img_x,
		img_y,
		pattern,
		i_hanyou[HANYOU_NUM];		
};
struct GAMEDATA{
	unsigned int	hiscore,
			score,
			score2;
	int	title_carsol,
		con_times,
		power,
		maxpoint,
		point,
		nextpoint,
		count,
		game_count,
		stage,
		stage_score[SCORE_STAGE_NUM],
		stage_graze[SCORE_STAGE_NUM],
		stage_point[SCORE_STAGE_NUM],
		stage_count[SCORE_STAGE_NUM],
		spell_mode,
		spell_getflag,
		spell_count,
		spell_bonus,
		spell_bonus_rate,
		spell_bonus_ratecount,
		getspell_count,
		getspell_point,
		extend_count,
		shake_count,
		demo_flag,
		demo_count,
		max_count,
		max_sign,
		before_max,
		i_hanyou[HANYOU_NUM];
	unsigned short	graze;
	SCENE scene;
	int	gra_back[GRA_BACK_NUM],
		gra_flame,
		gra_title_back,
		gra_title[GRA_TITLE_NUM],
		gra_option[GRA_OPTION_NUM],
		gra_config[GRA_CONFIG_NUM],
		gra_t_number[GRA_T_NUMBER_NUM],
		gra_t_effect,
		gra_level[GRA_LEVEL_NUM],
		gra_player[GRA_PLAYER_NUM],
		gra_weapon[GRA_WEAPON_NUM],
		gra_menu[GRA_MENU_NUM],
		gra_number[GRA_NUMBER_NUM],
		gra_side[GRA_SIDE_NUM];
	int	Shot,
		Bomb,
		Slow,
		Skip;
	float	zanzou_x[ZANZOU_NUM],
		zanzou_y[ZANZOU_NUM];
	bool	skip;//弾幕結界
};
struct SPELLDATA{
	int	count,
		defence,
		life,
		Level;
	char	name[SPELL_NAME_NUM];
};
struct SPELLSAVEDATA{
	int	get_times[SPELL_TIMES_NUM][SPELL_TIMES_NUM],
		challenge_times[SPELL_TIMES_NUM][SPELL_TIMES_NUM];
};
struct SCOREDATA{
	unsigned int score;
	unsigned int s_score[SCORE_STAGE_NUM];
	unsigned int s_time[SCORE_STAGE_NUM];
	unsigned int time;//総合クリアタイム
	char stage;//到達ステージ数
	char name[SCORE_NAME_NUM];
	unsigned int year;
	char month;
	char date;
	char hour,
	     minute,
	     second;
};
struct LEVELDATA{
	SCOREDATA score[LEVEL_SCORE_NUM];
};
struct REIMU_ADATA{
	LEVELDATA level[LEVEL_LEVEL_NUM];
};
struct REIMU_BDATA{
	LEVELDATA level[LEVEL_LEVEL_NUM];
};
struct MARISA_ADATA{
	LEVELDATA level[LEVEL_LEVEL_NUM];
};
struct MARISA_BDATA{
	LEVELDATA level[LEVEL_LEVEL_NUM];
};
struct SAVEDATA{
	REIMU_ADATA ReimuA;
	REIMU_BDATA ReimuB;
	MARISA_ADATA MarisaA;
	MARISA_BDATA MarisaB;	
	int	Key_Shot,
		Key_Bomb,
		Key_Slow,
		Key_Skip,
		Key_Pause,
		Chara,
		Weapon,
		Graphic,
		BGM,
		Sound,
		Level,
		PlayTime,
		Practice,
		BgmFlag[BGM_NUM];
	SPELLSAVEDATA Spell[SPELL_NUM];
};
struct T_EFFECTDATA{
	double	x,
		y,
		move_x,
		large,
		speed;
};
struct EFFECTDATA{
	float	x,
		y,
		move_x,
		move_y,
		large,
		angle,
		speed,
		d_hanyou[HANYOU_NUM];
	int	count,
		img,
		flash,
		pattern,
		i_hanyou[HANYOU_NUM];
};
struct REPLAYDATA{
	int 	start_count[SCORE_STAGE_NUM];
	unsigned int	score,
			start_score[SCORE_STAGE_NUM],
			end_score[SCORE_STAGE_NUM];
	char		start_player[SCORE_STAGE_NUM],
			start_power[SCORE_STAGE_NUM];
	unsigned short	start_graze[SCORE_STAGE_NUM],
			start_point[SCORE_STAGE_NUM];
	unsigned int	start_max[SCORE_STAGE_NUM];
	unsigned char	exist[SCORE_STAGE_NUM];
	int	start_random[SCORE_STAGE_NUM];
	char stage;//到達ステージ数
	char name[SCORE_NAME_NUM];
	unsigned short year;
	char month;
	char date;
	char hour,
	     minute,
	     second;
	char level,
	     chara,
	     weapon;
	int element_num;
	unsigned char	replay[REPLAY_ELEMENT_NUM];
	unsigned char	fps[REPLAY_FPS_NUM];
};
struct TALKDATA{
	int	count,
		scene,
		carsol;
	bool	b_control;
};
struct LASER_SHOTDATA{
	float 	x,
		y,
		d_hanyou[HANYOU_NUM];
	int	flash,
		count,
		pattern,
		i_hanyou[HANYOU_NUM];
};
struct LASERDATA{
	float	x,
		y,
		angle,
		speed,
		length,
		d_hanyou[HANYOU_NUM];
	int	count,
		graze_count,
		pattern,
		img,
		img_x,
		img_y,
		late,
		effect,
		i_hanyou[HANYOU_NUM];
	list<LASER_SHOTDATA> Shot;
	bool	atari;		
};
struct ENDINGDATA{
	int	count,
		scene,
		fadein,
		end_scene,
		img[GRA_ENDING_NUM];
};

int c_key[C_KEY_NUM];
int c_pad[C_PAD_NUM];
 
int gra_reimu[GRA_REIMU_NUM];
int gra_marisa[GRA_MARISA_NUM];
int gra_shot_reimu[GRA_SHOT_REIMU_NUM];
int gra_shot_marisa[GRA_SHOT_MARISA_NUM];
int gra_option;
int gra_atari;
int gra_bomb;
int gra_fairy[GRA_FAIRY_NUM_A][GRA_FAIRY_NUM_B];
int gra_big_fairy[GRA_BIG_FAIRY_NUM];
int gra_kedama[GRA_KEDAMA_NUM];
int gra_crow[GRA_CROW_NUM];
int gra_e_shot[GRA_E_SHOT_NUM];
int gra_e_shot2[GRA_E_SHOT2_NUM];//蝶弾などの薄くする部分
int gra_circle;
int gra_item[GRA_ITEM_NUM];
int gra_stage_title[GRA_STAGE_TITLE_NUM2];
int gra_music_title[GRA_MUSIC_TITLE_NUM];
int gra_boss_name[GRA_BOSS_NAME_NUM];
int gra_boss[GRA_BOSS_NUM_A][GRA_BOSS_NUM_B];
int gra_enemymark;
int gra_catin[GRA_CATIN_NUM];
int gra_borderoflife;
int gra_spell_back[GRA_SPELL_BACK_NUM];
int gra_laser[GRA_LASER_NUM];
int gra_bullet_effect;
int gra_graze_effect;
int ResultFont;
int ResultFont2;
int MusicFont;
int MusicFont2;
int PointFont;//点アイテム取得時
int PauseFont;
int SpellFont;
int MessageFont;
int ReplayFont;
int SpellBonusFont;
int GetSpellBonusFont;
int EndingFont;
int SRFont;
int SoundFlag[SOUND_NUM];

int GameScene;//道中？ボス？リザルト？
int ResultCount;
int SkipCount;//リプレイ鑑賞時のスキップ

int main_loop;
int loop_count;
int main_draw;
bool FlagSlow;

static int shake_x;
static int shake_y;
static int before_count;//以前シェイクがあったカウント
static int music_count;
static int Pause;
static int PauseGra;
static int start_stage;//最初からやり直しの際のやり直しステージ
static int start_life;//最初からやり直しの際の初期残機
static int start_power;//最初からやり直しの際の初期パワー
static int GameOver;
static int debug_muteki;
static int debug_nobullet;
static int debug_AI;
static int ReplayCount;
static int ScoreCount;
static int ScoreReplayCount;
static int PlayerControlFlag;//0:通常 1:リプレイ 2:ディレクタリプレイ
static int repnum;
static unsigned int s_time[SCORE_STAGE_NUM];

static PLAYERDATA Player;
static list<P_SHOTDATA> P_Shot;
static BOMBDATA Bomb;
static OPTIONDATA Option[OPTION_NUM];
static list<E_SHOTDATA> E_Shot;
static list<ENEMYDATA> Enemy;
static BOSSDATA Boss;
static GAMEDATA Game; 
static list<ITEMDATA> Item;
static SAVEDATA SAVE;
static T_EFFECTDATA T_Effect[T_EFFECT_NUM]; 
static list<EFFECTDATA> Effect;
static SPELLDATA Spell[SPELL_NUM];
static REPLAYDATA Replay[REPLAY_NUM];
static REPLAYDATA Director_Replay[DIRECTOR_REPLAY_NUM];
static REPLAYDATA SReplay;
static TALKDATA Talk;
static list<LASERDATA> Laser;
static ENDINGDATA Ending;

//関数プロトタイプ宣言
void DebugStage();
void Stage1();
void Stage2();
void Stage3();
void Stage4();
void Stage5();
void Stage6();
void Stage7();

void CheckPushKey();
void SnapShot();
void Fps();
void FpsDraw();
void DrawNumber(float,float,int,unsigned int);
void DrawNumber2(float,float,int,unsigned int);
void Debug();
int SSave();
void SSaveReset();
void SCheckPlayTime();
void SMe_Load();
void SMe_ChangeScene(SCENE);
void SMe_Title();
void SMe_SelectLevel();
void SMe_SelectPlayer();
void SMe_SelectWeapon();
void SMe_Option();
void SMe_KeyConfig();
void SMe_Replay();
void SMe_Result();
void SMe_MusicRoom();
void SMe_Effect();
void Smain();
void SPlaySound(int);
void SSoundEffect();
void SLoad();
void SReset();
void SShake(int,int);
void SBa_Load();
void SBa_Reset();
void SBa_Draw();
void SBa_Normal();
void SBa_Spell(int flash);
void SRe_Load();
void SRe_Main();
void SSc_Load();
void SSc_Reset();
void SSc_Reset2();
void SSc_Draw();
void SSc_SaveScore();
void SSc_Demo();
void SSc_AddScore(int);
void SPl_Load();
void SPl_Reset();
void SPl_Main();
void SPl_Draw();
void SPl_AI();
void SPl_Control();
void SPl_Pause();
void SPl_Miss();
void SPl_Death();
void SPs_Load();
void SPs_Reset();
void SPs_Main();
void SPs_Draw();
void SPs_Make(float,float,float,float,int,int,int=0);
void SPs_Move(list<P_SHOTDATA>::iterator &);
void SBom_Load();
void SBom_Reset();
void SBom_Draw();
void SBom_Make(float,float);
void SBom_Move();
void SEn_Load();
void SEn_Reset();
void SEn_Main();
void SEn_Draw();
void SEn_Make(float,float,int,int,int,int,int);
void SEn_Move(list<ENEMYDATA>::iterator &);
void SEn_Shot(list<ENEMYDATA>::iterator &);
void SEn_Item(list<ENEMYDATA>::iterator &);
void SEs_Load();
void SEs_Reset();
void SEs_Main();
void SEs_Draw();
void SEs_Make(float,float,float,float,int,int,float=0,int=0,int=0,int=0);
void SEs_NWay(float,float,float,int,float,int,int,float=0,float=0,int=0,int=0,int=0);
void SEs_Move(list<E_SHOTDATA>::iterator &);
void SLas_Load();
void SLas_Reset();
void SLas_Main();
void SLas_Draw();
void SLas_Make(float,float,float,float,int,int,int=0,int=0);
void SLas_ShotMake(list<LASERDATA>::iterator &);
void SLas_Move(list<LASERDATA>::iterator &);
void SBos_Load();
void SBos_Reset();
void SBos_Main();
void SBos_Draw();
void SBos_DeleteBullet(int);
void SBos_Make(float,float,int,int,int,int,int,int,int,int=0);
void SBos_Move();
void SBos_MoveTo(float,float,int);
void SBos_Shot();
void SBos_Item();
void SSp_Load();
void SSp_Move();
void SSp_Shot();
void SSp_Draw();
void SIt_Load();
void SIt_Reset();
void SIt_Main();
void SIt_Draw();
void SIt_Make(float,float,float,int,int=0);
void SIt_Move(list<ITEMDATA>::iterator &);
void SEf_Load();
void SEf_Reset();
void SEf_Draw();
void SEf_Make(float,float,int,int=0,int=0);
void SEf_Move(list<EFFECTDATA>::iterator &);
void STa_Reset();
void STa_Draw();
void SEnd_Load();
void SEnd_Reset();
void SEnd_Draw();
void SEnd_Reimu();
void SEnd_Marisa();
void SEnd_Main();
void SSR_Main();
void SSR_Draw();

//関数
inline void CheckPushKey(){
//何フレームの間ボタンが押されているか。0は押されていない。
	try{
		char check[C_KEY_NUM];
		GetHitKeyStateAll(check);
		for(int i=0;i<C_KEY_NUM;i++){
			if(i>=C_KEY_NUM)	throw(1);
			if(check[i]==1)	c_key[i]++;
			else		c_key[i] = 0; 
		}
		int key = GetJoypadInputState(DX_INPUT_PAD1);
		for(int i=0;i<14;i++){
			int a = 1;
			for(int b=0;b<i;b++){	a *= 2;	}
			if(i>=C_PAD_NUM)	throw(2);
			if(key&a)	c_pad[i]++;
			else		c_pad[i] = 0; 
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:CheckPushKey\nキー指定番号が異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	
	return;
}

inline void SnapShot(){
	if(c_key[KEY_INPUT_P]==1){
		char path[128];
		wsprintf(path , "snapshot");
		if(PathIsDirectory(path)==false){
			CreateDirectory(path,NULL);
		}
		for(int i=0;i<999;i++){
			wsprintf(path , "snapshot/th00_%03d.bmp",i+1);
			if(PathFileExists(path)==false){
				break;
			}
		}
		SaveDrawScreen(0,0,640,480,path);
	}
	return;
}

inline void Fps(){
	static float ZeroCount = 0;
	static float count = frame;
	static int fps2;
		if(ZeroCount!=0){
			float wait = ZeroCount+1000.0/frame*count-1.0-GetNowCount();
			if(wait>0){
				if(Config.fps==0)	Sleep(wait);
			}
		}
	if(count==frame){
		int zero = ZeroCount;
		ZeroCount = GetNowCount();
		fps = 1000.0 / ((GetNowCount()-zero)/frame);
		fps2 = GetNowCount() - zero;
		count = 1;
	}
	else{
		count++;
	}
	
	return;
}
inline void FpsDraw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int color = GetColor(255,255,255);
	if(fps<50/(Config.drawmode+1)){
		color = GetColor(100,100,255);
	}
	if(fps>0.09){
		if(Config.drawmode==1)	DrawFormatString(560,455,color,"描画回数1/2");
		if(Config.drawmode==2)	DrawFormatString(560,455,color,"描画回数1/3");
		DrawFormatString(570,465,color,"FPS %.1f",fps/(Config.drawmode+1));
	}
	return;
}
inline void DrawNumber(float x,float y,int times,unsigned int num){
//(x,y)にtimes桁でnumを表示 0表示あり
	try{
		unsigned int dummy = num;
		for(unsigned int i=0;i<times;i++){
			unsigned int bai = 1;
			for(unsigned int b=0;b<times-i-1;b++){
				bai *= 10;
			}
			unsigned int ans = dummy / bai;
			dummy -= ans * bai;
			if(ans>9)	ans = 9;
			if(ans<0||ans>=GRA_NUMBER_NUM)	throw(1);
			DrawGraphF(x+12*i,y,Game.gra_number[ans],TRUE);
		}
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:DrawNumber\n表示数字が異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
}

inline void DrawNumber2(float x,float y,int times,unsigned int num){
//(x,y)にtimes桁でnumを表示 左詰
	try{
		unsigned int dummy = num;
		bool flag = false;
		for(unsigned int i=0,a=0;i<times;i++){
			unsigned int bai = 1;
			for(unsigned int b=0;b<times-i-1;b++){
				bai *= 10;
			}
			unsigned int ans = dummy / bai;
			dummy -= ans * bai;
			if(ans>9){
					ans = 9;
			}
			if(ans>0){
				flag = true;
				if(ans<0||ans>=GRA_NUMBER_NUM)	throw(1);
				DrawGraphF(x+12*a,y,Game.gra_number[ans],TRUE);
				a++;
			}
			else if(flag==true||i==times-1){
				if(ans<0||ans>=GRA_NUMBER_NUM)	throw(1);
				DrawGraphF(x+12*a,y,Game.gra_number[ans],TRUE);
				a++;
			}
		}
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:DrawNumber2\n表示数字が異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void Debug(){
	if(c_key[KEY_INPUT_U]%3==1&&Game.power<80)	Game.power ++;
	if(c_key[KEY_INPUT_M]%3==1&&0<Game.power)	Game.power --;
	if(c_key[KEY_INPUT_D]==1){
		debug_muteki ++;
 		debug_muteki = debug_muteki%2;
	}
	if(c_key[KEY_INPUT_N]==1){
		debug_nobullet ++;
 		debug_nobullet = debug_nobullet%2;
	}
	if(c_key[KEY_INPUT_A]==1){
		debug_AI ++;
 		debug_AI = debug_AI%2;
	}
	if(c_key[KEY_INPUT_B]==1){
		Boss.life = 0;
	}
	//if(c_key[KEY_INPUT_RCONTROL]>=1)frame = 30;
	//else				frame = 60;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	if(debug_muteki==1)	DrawFormatString(500,440,GetColor(255,255,255),"プレイヤー無敵デバッグ");
	if(debug_nobullet==1)	DrawFormatString(500,430,GetColor(255,255,255),"ノーブリットモード");
	if(debug_AI==1)		DrawFormatString(500,420,GetColor(255,255,255),"AIモード");
	DrawFormatString(500,450,GetColor(255,255,255),"count:%d",Game.count);
	SAVE.Practice = 6;
	//DrawFormatString(50,50,GetColor(255,255,255),"b_zanzou:%d",Boss.b_zanzou);
	//DrawFormatString(50,60,GetColor(255,255,255),"exst:%d",Boss.gage_exist);
	return;
}

int SSave(){
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	char *name = "th00score.dat";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "データの初期化に失敗");
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
		return 1;
	}
	fwrite(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	
	fclose(fp);
	
	return 0;
}

void SSaveReset(){
	try{
		SAVE.Graphic = true;
		SAVE.BGM = 100;
		SAVE.Sound = 100;
		SAVE.Key_Shot = PAD_A;
		SAVE.Key_Bomb = PAD_B;
		SAVE.Key_Slow = PAD_Z;
		SAVE.Key_Skip = PAD_L;
		SAVE.Key_Pause = PAD_START;
		SAVE.Level = 1;
		SAVE.Chara = 0;
		SAVE.Weapon = 0;
		SAVE.PlayTime = 0;
		SAVE.Practice = 1;
		for(int i=0;i<SPELL_NUM;i++){
			for(int a=0;a<SPELL_TIMES_NUM;a++){
				for(int b=0;b<SPELL_TIMES_NUM;b++){
					SAVE.Spell[i].get_times[a][b] = 0;
					SAVE.Spell[i].challenge_times[a][b] = 0;
				}
			}
		}
		for(int i=0;i<LEVEL_LEVEL_NUM;i++){
			for(int a=0;a<LEVEL_SCORE_NUM;a++){
				SAVE.ReimuA.level[i].score[a].score = 10000000-a*1000000;
				wsprintf(SAVE.ReimuA.level[i].score[a].name , "--------");
				SAVE.ReimuA.level[i].score[a].month = 1;
				SAVE.ReimuA.level[i].score[a].date = 1;
				SAVE.ReimuA.level[i].score[a].year = 2009;
				SAVE.ReimuA.level[i].score[a].hour = 0;
				SAVE.ReimuA.level[i].score[a].minute = 0;
				SAVE.ReimuA.level[i].score[a].second = 0;
				SAVE.ReimuA.level[i].score[a].time = 0;
				SAVE.ReimuA.level[i].score[a].stage = '1';
				for(int b=0;b<SCORE_STAGE_NUM;b++){
					SAVE.ReimuA.level[i].score[a].s_time[b] = 0;
					SAVE.ReimuA.level[i].score[a].s_score[b] = 0;
				}
				SAVE.ReimuB.level[i].score[a].score = 10000000-a*1000000;
				wsprintf(SAVE.ReimuB.level[i].score[a].name , "--------");
				SAVE.ReimuB.level[i].score[a].month = 1;
				SAVE.ReimuB.level[i].score[a].date = 1;
				SAVE.ReimuB.level[i].score[a].year = 2009;
				SAVE.ReimuB.level[i].score[a].hour = 0;
				SAVE.ReimuB.level[i].score[a].minute = 0;
				SAVE.ReimuB.level[i].score[a].second = 0;
				SAVE.ReimuB.level[i].score[a].time = 0;
				SAVE.ReimuB.level[i].score[a].stage = '1';
				for(int b=0;b<SCORE_STAGE_NUM;b++){
					SAVE.ReimuB.level[i].score[a].s_time[b] = 0;
					SAVE.ReimuB.level[i].score[a].s_score[b] = 0;
				}
				SAVE.MarisaA.level[i].score[a].score = 10000000-a*1000000;
				wsprintf(SAVE.MarisaA.level[i].score[a].name , "--------");
				SAVE.MarisaA.level[i].score[a].month = 1;
				SAVE.MarisaA.level[i].score[a].date = 1;
				SAVE.MarisaA.level[i].score[a].year = 2009;
				SAVE.MarisaA.level[i].score[a].hour = 0;
				SAVE.MarisaA.level[i].score[a].minute = 0;
				SAVE.MarisaA.level[i].score[a].second = 0;
				SAVE.MarisaA.level[i].score[a].time = 0;
				SAVE.MarisaA.level[i].score[a].stage = '1';
				for(int b=0;b<SCORE_STAGE_NUM;b++){
					SAVE.MarisaA.level[i].score[a].s_time[b] = 0;
					SAVE.MarisaA.level[i].score[a].s_score[b] = 0;
				}
				SAVE.MarisaB.level[i].score[a].score = 10000000-a*1000000;
				wsprintf(SAVE.MarisaB.level[i].score[a].name , "--------");
				SAVE.MarisaB.level[i].score[a].month = 1;
				SAVE.MarisaB.level[i].score[a].date = 1;
				SAVE.MarisaB.level[i].score[a].year = 2009;
				SAVE.MarisaB.level[i].score[a].hour = 0;
				SAVE.MarisaB.level[i].score[a].minute = 0;
				SAVE.MarisaB.level[i].score[a].second = 0;
				SAVE.MarisaB.level[i].score[a].time = 0;
				SAVE.MarisaB.level[i].score[a].stage = '1';
				for(int b=0;b<SCORE_STAGE_NUM;b++){
					SAVE.MarisaB.level[i].score[a].s_time[b] = 0;
					SAVE.MarisaB.level[i].score[a].s_score[b] = 0;
				}
			}
		}
		for(int i=0;i<BGM_NUM;i++){
			SAVE.BgmFlag[i] = 0;
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SSaveReset\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	char *name = "th00score.dat";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "データの初期化に失敗");
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
		return;
	}
	
	fwrite(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	
	fclose(fp);
	return;
}

void SCheckPlayTime(){
	DATEDATA D;
	static int time = 0;
	GetDateTime(&D);
	if(D.Sec!=time){
		time = D.Sec;
		SAVE.PlayTime++;
	}
	if(SAVE.PlayTime>356399){
		SAVE.PlayTime = 356399;
	}
	/*
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int color = GetColor(255,255,255);
	DrawFormatString(550,445,color,"Time %d",SAVE.PlayTime);
	*/

	return;
}

void SMe_Load(){
	try{
		ResultFont = CreateFontToHandle("ＭＳ ゴシック",16,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		ResultFont2 = CreateFontToHandle("ＭＳ ゴシック",14,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		MusicFont = CreateFontToHandle("ＭＳ ゴシック",14,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		MusicFont2 = CreateFontToHandle("ＭＳ ゴシック",15,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		PointFont = CreateFontToHandle("MS UI Gothic",8,2,DX_FONTTYPE_ANTIALIASING_EDGE);
		PauseFont = CreateFontToHandle("AR P隷書体M",20,3,DX_FONTTYPE_ANTIALIASING_EDGE);
		SpellFont = CreateFontToHandle("ＭＳ Ｐゴシック",15,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
		MessageFont = CreateFontToHandle("ＭＳ Ｐゴシック",14,4,DX_FONTTYPE_ANTIALIASING_EDGE);
		ReplayFont = CreateFontToHandle("HG創英角ｺﾞｼｯｸUB",15,3,DX_FONTTYPE_ANTIALIASING_EDGE);
		SpellBonusFont = CreateFontToHandle("MS UI Gothic",10,8,DX_FONTTYPE_EDGE);
		GetSpellBonusFont = CreateFontToHandle("AR P新藝体U",16,5,DX_FONTTYPE_ANTIALIASING_EDGE);
		EndingFont = CreateFontToHandle("ＭＳ Ｐゴシック",18,4,DX_FONTTYPE_ANTIALIASING_EDGE);
		SRFont = CreateFontToHandle("ＭＳ Ｐゴシック",20,4,DX_FONTTYPE_ANTIALIASING_EDGE);
		for(int i=0;i<T_EFFECT_NUM;i++){
			T_Effect[i].x = get_rand(640);
			T_Effect[i].y = get_rand(480);
			T_Effect[i].move_x = 0.5*sin(Radian(get_rand(360),TRUE));
			T_Effect[i].large = 0.1+0.01*get_rand(40);
			T_Effect[i].speed = 0.5+0.01*get_rand(50);
		}
		try{
			char fi[128];
			wsprintf(fi , "data/img/back/title.jpg");
			if( (Game.gra_title_back = LoadGraph(fi)) == -1)	throw(fi);
			SetTransColor(0,0,0);
			for(int i=0;i<GRA_TITLE_NUM;i++){
				if(i==7){
					wsprintf(fi , "data/img/font/title/%d.png" , i+1);
					SetTransColor(255,255,255);
				}
				else{
					wsprintf(fi , "data/img/font/title/%d.png" , i+1);
					SetTransColor(0,0,0);
				}
				if( (Game.gra_title[i] = LoadGraph(fi)) == -1)	throw(fi);
			}
			SetTransColor(0,0,0);
			for(int i=0;i<GRA_OPTION_NUM;i++){
				wsprintf(fi , "data/img/font/option/%d.png" , i+1);
				if( (Game.gra_option[i] = LoadGraph(fi)) == -1)	throw(fi);
			}
			for(int i=0;i<GRA_T_NUMBER_NUM;i++){
				if(i<10)	wsprintf(fi , "data/img/font/t_number/t%d.png" , i);
				else		wsprintf(fi , "data/img/font/t_number/percent.png");
				if((Game.gra_t_number[i]=LoadGraph(fi)) == -1)		throw(fi);
			}
			for(int i=0;i<GRA_CONFIG_NUM;i++){
				wsprintf(fi , "data/img/font/keyconfig/%d.png" , i+1);
				if((Game.gra_config[i]=LoadGraph(fi)) == -1)	throw(fi);
			}
			SetTransColor(0,0,0);
			wsprintf(fi , "data/img/back/efe.png");
			if((Game.gra_t_effect=LoadGraph(fi)) == -1)	throw(fi);
			for(int i=0;i<GRA_LEVEL_NUM;i++){
				wsprintf(fi , "data/img/level/%d.jpg" , i+1);
				if((Game.gra_level[i]=LoadGraph(fi)) == -1)	throw(fi);
			}
			for(int i=0;i<GRA_PLAYER_NUM;i++){
				wsprintf(fi , "data/img/font/player/%d.png" , i+1);
				SetTransColor(0,0,0);
				if((Game.gra_player[i]=LoadGraph(fi)) == -1)	throw(fi);
			}
			SetTransColor(0,0,0);
			for(int i=0;i<GRA_WEAPON_NUM;i++){
				wsprintf(fi , "data/img/font/player/%d.png" , i+5);
				if((Game.gra_weapon[i]=LoadGraph(fi)) == -1)	throw(fi);
			}
			for(int i=0;i<GRA_MENU_NUM;i++){
				wsprintf(fi , "data/img/font/menu/%d.png" , i+1);
				if((Game.gra_menu[i]=LoadGraph(fi)) == -1)	throw(fi);
			}
		}
		catch(char *file){
			char message[128];
			wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
			MessageBox( 	NULL,
				message,
				"Error",
				MB_OK | 
				MB_ICONSTOP |
				MB_TOPMOST);
	
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_Load\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	return;

}

void SMe_ChangeScene(SCENE s){
	if(Game.scene!=s){
		Game.scene = s;
		Game.game_count = -1;
	}
	return;
}

void SMe_Title(){
	try{
		if(Game.game_count==0){
			SMu_PlayBgm(0);
			SAVE.BgmFlag[0]++;
			PlayerControlFlag = 0;
			SSave();	
                        /*
			Game.stage = 3;
			SEnd_Reset();
			SMe_ChangeScene(ENDING);
			*/
		}
		if(Game.game_count==1200){
			repnum = 5;
			SAVE.Level = Director_Replay[repnum].level;
			SAVE.Chara = Director_Replay[repnum].chara;
			SAVE.Weapon = Director_Replay[repnum].weapon;
			Game.stage = 1;
			start_stage = 1;
			start_life = Director_Replay[repnum].start_player[start_stage-1];
			start_power = Director_Replay[repnum].start_power[start_stage-1];
			Game.con_times = 0;
			PlayerControlFlag = 2;
			SReset();
			SSc_Reset();
			SSc_Reset2();
			Game.demo_flag = 1;
			SMe_ChangeScene(SHOOTING);
		}
		SetDrawBright(100,100,255);
		DrawGraph(0,0,Game.gra_title_back,TRUE);
		static int count;
		int number = 7;
		double e_s;
		double e_r;
		bool control = false;
		if(Game.game_count<25){
			e_s = 0.04 * Game.game_count;
			e_r = Radian(260+4.0*Game.game_count,TRUE);
			count = 0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,10.2*Game.game_count);
		}
		else{
			e_s = 1.00;
			e_r = 0;
			control = true;
			count++;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		}
		SetDrawBright(255,255,255);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawGraph(40,40,Game.gra_title[7],FALSE);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		for(int i=0;i<7;i++){
			if(i%2==0){
				e_r *= -1;
			}
			int efe = 0;
			SetDrawBright(150,150,150);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,170);
			if(Game.title_carsol%number==i){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				efe = 5;
				SetDrawBright(255,210-abs(90-(count+90)%180),210-abs(90-(count+90)%180));
			}
			int x,y;
			if(i<0||i>=GRA_TITLE_NUM)	throw(1);
			GetGraphSize(Game.gra_title[i],&x,&y);
			DrawRotaGraphF(420-efe+x/2-8*i,240+y/2+25*i,e_s,e_r,Game.gra_title[i],TRUE);
		}
       	
		if(control==true){	
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				Game.title_carsol ++;
				Game.title_carsol = Game.title_carsol%number;
				count = 0;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				Game.title_carsol --;
				count = 0;
				if(Game.title_carsol<0){
					Game.title_carsol += number;
				}
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				Game.title_carsol = Game.title_carsol % number;
				if(Game.title_carsol%number==0)SMe_ChangeScene(SELECT_LEVEL);
				else if(Game.title_carsol%number==1)SMe_ChangeScene(SELECT_LEVEL);
				else if(Game.title_carsol%number==2)SMe_ChangeScene(REPLAY);
				else if(Game.title_carsol%number==3)SMe_ChangeScene(RESULT);
				else if(Game.title_carsol%number==4)SMe_ChangeScene(MUSIC_ROOM);
				else if(Game.title_carsol%number==5)SMe_ChangeScene(OPTION);
				else if(Game.title_carsol%number==6){
					SMe_ChangeScene(END);
					Sleep(500);			
				}
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				if(Game.title_carsol%number==6){
					SMe_ChangeScene(END);
					Sleep(500);			
				}
				Game.title_carsol = 6;		
			}
		}	
		SetDrawBright(255,255,255);
		SMe_Effect();
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_Title\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
}
      	
void SMe_SelectLevel(){
	try{
		SetDrawBright(100,100,255);
		DrawGraph(0,0,Game.gra_title_back,TRUE);
		int number = 4;
		double e_s;
		double e_r;
		bool control = false;
		if(Game.game_count<25){
			e_s = 0.04 * Game.game_count;
			e_r = Radian(260+4.0*Game.game_count,TRUE);
		}
		else{
			e_s = 1.00;
			e_r = 0;
			control = true;
		}
		if(SAVE.Level<4||Game.title_carsol%7==1){
			for(int i=0;i<number;i++){
				if(i%2==0){
					e_r *= -1;
				}
				SetDrawBright(40,40,40);
				int efe = 0;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(SAVE.Level%number==i){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					efe = 5;
					SetDrawBright(255,255,255);
				}
				int x,y;
				if(i<0||i>=GRA_LEVEL_NUM)	throw(1);
				GetGraphSize(Game.gra_level[i],&x,&y);
				DrawRotaGraphF(320-efe+x/2-70*i,15+y/2+110*i,e_s,e_r,Game.gra_level[i],TRUE);
			}
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int efe = 5;
			SetDrawBright(255,255,255);
			int x,y;
			GetGraphSize(Game.gra_level[4],&x,&y);
			DrawRotaGraphF(320,240,e_s,e_r,Game.gra_level[4],TRUE);
		}
       	
		if(control==true){	
			if(SAVE.Level<4){
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					SAVE.Level ++;
					SAVE.Level = SAVE.Level%number;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					SAVE.Level --;
					if(SAVE.Level<0){
						SAVE.Level += number;
					}
				}
			}
			else if(Game.title_carsol%7==1)	SAVE.Level = 0;
			if(Game.title_carsol%7==0){	
				if(c_key[KEY_INPUT_LEFT]==1 || c_key[KEY_INPUT_RIGHT]==1 || c_pad[PAD_LEFT]==1 || c_pad[PAD_RIGHT]==1){
					SPlaySound(7);
					if(SAVE.Level<4)	SAVE.Level = 4;
					else			SAVE.Level = 1;
				}
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				SMe_ChangeScene(SELECT_PLAYER);
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				SMe_ChangeScene(TITLE);
			}
		}	
		SetDrawBright(255,255,255);
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_SelectLevel\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SMe_SelectPlayer(){
	try{
		SetDrawBright(100,100,255);
		DrawGraph(0,0,Game.gra_title_back,TRUE);
		int number = 2;
		double e_s;
		double e_r;
		double e_f;
		bool control = false;
		if(Game.game_count<40)	e_f = 0.025 * Game.game_count;
		else			e_f = 1;
		if(Game.game_count<25){
			e_s = 0.04 * Game.game_count;
			e_r = Radian(260+4.0*Game.game_count,TRUE);
		}
		else{
			e_s = 1.00;
			e_r = 0;
			control = true;
		}
		for(int i=0;i<number;i++){
			if(i%2==0){
				e_r *= -1;
			}
			SetDrawBright(40,40,40);
			int efe = 0;
			if(SAVE.Chara%number==i){
				efe = 5;
				SetDrawBright(255,255,255);
			}
			int x,y;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255*e_f);
			if(i+2<0||i+2>=GRA_PLAYER_NUM)	throw(1);
			GetGraphSize(Game.gra_player[i+2],&x,&y);
			DrawRotaGraphF(210+270*i+efe,406-y/2,1.0,0,Game.gra_player[i+2],TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i<0||i>=GRA_PLAYER_NUM)	throw(2);
			GetGraphSize(Game.gra_player[i],&x,&y);
			DrawRotaGraphF(160+400*i+efe,320,e_s,e_r,Game.gra_player[i],TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255*e_s);
		SetDrawBright(255,255,255);
		int x,y;
		if(SAVE.Level<0||SAVE.Level>=GRA_LEVEL_NUM)	throw(3);
		GetGraphSize(Game.gra_level[SAVE.Level],&x,&y);
		DrawRotaGraphF(100,400,0.5,0,Game.gra_level[SAVE.Level],TRUE);
       	
		if(control==true){	
			if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
				if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
					c_key[KEY_INPUT_RIGHT] = 21;
					c_pad[PAD_RIGHT] = 21;
				}
				SPlaySound(7);
				SAVE.Chara ++;
			}	
			else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
				if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
					c_key[KEY_INPUT_LEFT] = 21;
					c_pad[PAD_LEFT] = 21;
				}
				SPlaySound(7);
				SAVE.Chara --;
				if(SAVE.Chara<0){
					SAVE.Chara += number;
				}
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				SAVE.Chara = SAVE.Chara%number;
				start_stage = 0;
				SMe_ChangeScene(SELECT_WEAPON);
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				SMe_ChangeScene(SELECT_LEVEL);
			}
		}	
		SetDrawBright(255,255,255);
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_SelectPlayer\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SMe_SelectWeapon(){
	try{
		SetDrawBright(100,100,255);
		DrawGraph(0,0,Game.gra_title_back,TRUE);
		int number = 2;
		double e_s;
		double e_r;
		bool control = false;
		if(Game.game_count<25){
			e_s = 0.04 * Game.game_count;
			e_r = Radian(260+4.0*Game.game_count,TRUE);
		}
		else{
			e_s = 1.00;
			e_r = 0;
			control = true;
		}
		for(int i=0;i<number;i++){
			if(i%2==0){
				e_r *= -1;
			}
			SetDrawBright(40,40,40);
			int efe = 0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(SAVE.Weapon%number==i){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				efe = 5;
				SetDrawBright(255,255,255);
			}
			int plus=0;
			if(SAVE.Chara==1)	plus = 2;
			int x,y;
			if(i+plus<0||i+plus>=GRA_WEAPON_NUM)	throw(1);
			GetGraphSize(Game.gra_weapon[i+plus],&x,&y);
			DrawRotaGraphF(480+efe,200+150*i,e_s,e_r,Game.gra_weapon[i+plus],TRUE);
		}
		SetDrawBright(255,255,255);
		int x,y;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255*e_s);
		if(SAVE.Chara+2<0||SAVE.Chara+2>=GRA_PLAYER_NUM)	throw(2);
		GetGraphSize(Game.gra_player[SAVE.Chara],&x,&y);
		DrawRotaGraphF(120,350-y/2,0.8,0,Game.gra_player[SAVE.Chara+2],TRUE);
		if(SAVE.Chara<0||SAVE.Chara>=GRA_PLAYER_NUM)	throw(3);
		DrawRotaGraphF(120,300,0.8,0,Game.gra_player[SAVE.Chara],TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(SAVE.Level<0||SAVE.Level>=GRA_LEVEL_NUM)	throw(4);
		DrawRotaGraphF(100,400,0.5,0,Game.gra_level[SAVE.Level],TRUE);

		if(Game.title_carsol==1){
			char message[32];
			wsprintf(message , "← Stage %d →" ,start_stage+1);
			int size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
			DrawFormatStringToHandle(320-size/2,400,GetColor(255,255,0),ResultFont2,message);
		}
		       	
		if(control==true){	
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				SAVE.Weapon ++;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				SAVE.Weapon --;
				if(SAVE.Weapon<0){
					SAVE.Weapon += number;
				}
			}
			if(Game.title_carsol==1){
				int st = SAVE.Practice;
				if(SAVE.Level==0&&st>3)	SAVE.Practice = 3;	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					start_stage ++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					start_stage --;
					if(start_stage<0){
						start_stage += SAVE.Practice;
					}
				}
				start_stage = start_stage % SAVE.Practice;
				if(SAVE.Level==0&&st>3)	SAVE.Practice = st;
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				SReset();
				SAVE.Weapon = SAVE.Weapon%number;
				start_stage += 1;
				if(Game.title_carsol==0){
					if(SAVE.Level<4)	start_stage = 1;
					else			start_stage = 7;
					Player.life = 2;
					Game.power = 80;
					if(start_stage==1||start_stage==7)	Game.power = 0;
				}
				if(Game.title_carsol==1){
					Player.life = 8;
					Game.power = 80;
					if(start_stage==1)	Game.power = 0;
				}
				Game.stage = start_stage;
				start_life = Player.life;
				start_power = Game.power;
				Game.con_times = 0;
				SReset();
				SSc_Reset();
				SSc_Reset2();
				SMe_ChangeScene(SHOOTING);
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				SMe_ChangeScene(SELECT_PLAYER);
			}
		}	
		SetDrawBright(255,255,255);
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_SelectWeapon\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SMe_Option(){
	try{
		SetDrawBright(100,100,255);
		DrawGraph(0,0,Game.gra_title_back,TRUE);
		static int carsol = 0;
		static int count;
		int number = 6;
		double e_s;
		double e_r;
		bool control = false;
		if(Game.game_count<25){
			if(carsol%number==number-1)	carsol = 0;
			e_s = 0.04 * Game.game_count;
			e_r = Radian(260+4.0*Game.game_count,TRUE);
			count = 0;
		}
		else{
			e_s = 1.00;
			e_r = 0;
			control = true;
			count++;
		}
		for(int i=0;i<6;i++){
			if(i%2==0){
				e_r *= -1;
			}
			SetDrawBright(150,150,150);
			int efe = 0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,170);
			if(carsol%number==i){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				efe = 5;
				SetDrawBright(255,210-abs(90-(count+90)%180),210-abs(90-(count+90)%180));
			}
			if(i<3){
				int x,y;
				if(i<0||i>=GRA_OPTION_NUM)	throw(1);
				GetGraphSize(Game.gra_option[i],&x,&y);
				DrawRotaGraphF(370-efe+x/2,220+y/2+28*i,e_s,e_r,Game.gra_option[i],TRUE);
			}
			else if(i<5){
				int x,y;
				if(i+1<0||i+1>=GRA_OPTION_NUM)	throw(2);
				GetGraphSize(Game.gra_option[i+1],&x,&y);
				DrawRotaGraphF(370-efe+x/2,220+y/2+28*i,e_s,e_r,Game.gra_option[i+1],TRUE);
			}
			else if(i==5){
				int x,y;
				if(6>=GRA_TITLE_NUM)	throw(3);
				GetGraphSize(Game.gra_title[6],&x,&y);
				DrawRotaGraphF(370-efe+x/2,220+y/2+28*(i+1),e_s,e_r,Game.gra_title[6],TRUE);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
			if(carsol%number==i)SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			switch(i){
				case 0:
					int x,y;
					bool flag;
					SetDrawBright(255,150,150);
					char a[3];
					a[0] = SAVE.BGM / 100;
					a[1] = (SAVE.BGM-a[0]*100) / 10;
					a[2] = SAVE.BGM-a[0]*100-a[1]*10;
					if(0>=GRA_T_NUMBER_NUM)	throw(4);
					GetGraphSize(Game.gra_t_number[0],&x,&y);
					flag = false;
					for(int b=0;b<3;b++){
						if(a[b]>0 || flag==true || b==2){
							flag = true;
							if(a[b]<0||a[b]>=GRA_T_NUMBER_NUM)	throw(5);
							DrawRotaGraphF(480+x/2+x*b,220+y/2+28*i,e_s,e_r,Game.gra_t_number[a[b]],TRUE);
						}
					}
					if(10>=GRA_T_NUMBER_NUM)	throw(6);
					DrawRotaGraphF(485+x/2+x*3,220+y/2+28*i,e_s,e_r,Game.gra_t_number[10],TRUE);
					break;
				case 1:
					SetDrawBright(255,150,150);
					a[0] = SAVE.Sound / 100;
					a[1] = (SAVE.Sound-a[0]*100) / 10;
					a[2] = SAVE.Sound-a[0]*100-a[1]*10;
					if(0>=GRA_T_NUMBER_NUM)	throw(7);
					GetGraphSize(Game.gra_t_number[0],&x,&y);
					flag = false;
					for(int b=0;b<3;b++){
						if(a[b]>0 || flag==true || b==2){
							flag = true;
							if(a[b]<0||a[b]>=GRA_T_NUMBER_NUM)	throw(8);
							DrawRotaGraphF(480+x/2+x*b,220+y/2+28*i,e_s,e_r,Game.gra_t_number[a[b]],TRUE);
						}
					}
					if(10>=GRA_T_NUMBER_NUM)	throw(9);
					DrawRotaGraphF(485+x/2+x*3,220+y/2+28*i,e_s,e_r,Game.gra_t_number[10],TRUE);
					break;
				case 2:
					SetDrawBright(255,255,255);
					if(SAVE.Graphic==true)	SetDrawBright(255,150,150);
					if(6>=GRA_T_NUMBER_NUM)	throw(10);
					GetGraphSize(Game.gra_t_number[6],&x,&y);
					if(3>=GRA_T_NUMBER_NUM)	throw(11);
					DrawRotaGraphF(480+x/2,220+y/2+28*i,e_s,e_r,Game.gra_t_number[3],TRUE);
					if(2>=GRA_T_NUMBER_NUM)	throw(12);
					DrawRotaGraphF(480+x/2+x,220+y/2+28*i,e_s,e_r,Game.gra_t_number[2],TRUE);
					if(3>=GRA_OPTION_NUM)	throw(13);
					DrawRotaGraphF(490+x/2+x*2,220+y/2+28*i,e_s,e_r,Game.gra_option[3],TRUE);
					SetDrawBright(255,255,255);
					if(SAVE.Graphic==false)	SetDrawBright(255,150,150);
					if(1>=GRA_T_NUMBER_NUM)	throw(14);
					DrawRotaGraphF(560+x/2,220+y/2+28*i,e_s,e_r,Game.gra_t_number[1],TRUE);
					if(6>=GRA_T_NUMBER_NUM)	throw(15);
					DrawRotaGraphF(560+x/2+x,220+y/2+28*i,e_s,e_r,Game.gra_t_number[6],TRUE);
					if(3>=GRA_OPTION_NUM)	throw(16);
					DrawRotaGraphF(570+x/2+x*2,220+y/2+28*i,e_s,e_r,Game.gra_option[3],TRUE);
					break;
			}
		}

		if(control==true){
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				carsol ++;
				count = 0;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				carsol --;
				count = 0;
				if(carsol<0){
					carsol += number;
				}
			}	
			else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
				if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
					c_key[KEY_INPUT_LEFT] = 21;
					c_pad[PAD_LEFT] = 21;
				}
				if(carsol%number==0 && SAVE.BGM>0){
					SPlaySound(7);
					SAVE.BGM -= 5;
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
				}
				else if(carsol%number==1 && SAVE.Sound>0){
					SPlaySound(7);
					SAVE.Sound -= 5;
					SMu_ChangeVolumeSound(255*SAVE.Sound*0.01);
				}
				else if(carsol%number==2 && SAVE.Graphic==false){
					SPlaySound(7);
					SAVE.Graphic = true;
				}
			}
			else if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
				if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
					c_key[KEY_INPUT_RIGHT] = 21;
					c_pad[PAD_RIGHT] = 21;
				}
				if(carsol%number==0 && SAVE.BGM<100){
					SPlaySound(7);
					SAVE.BGM += 5;
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
				}
				else if(carsol%number==1 && SAVE.Sound<100){
					SPlaySound(7);
					SAVE.Sound += 5;
					SMu_ChangeVolumeSound(255*SAVE.Sound*0.01);
				}
				else if(carsol%number==2 && SAVE.Graphic==true){
					SPlaySound(7);
					SAVE.Graphic = false;
				}
			}
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				int ans = carsol%number;
				if(ans==3 || ans==4 || ans==5){
					SPlaySound(5);
				}
				if(carsol%number==3)	SMe_ChangeScene(KEY_CONFIG);
				if(carsol%number==4){
					SAVE.BGM = 100;
					SAVE.Sound = 100;
					SAVE.Graphic = true;			
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
					SMu_ChangeVolumeSound(255*SAVE.Sound*0.01);
				}
				if(carsol%number==5)	SMe_ChangeScene(TITLE);
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				if(carsol%number==5)	SMe_ChangeScene(TITLE);
				carsol = 5;		
			}
		}	
		SetDrawBright(255,255,255);
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_Option\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SMe_KeyConfig(){
	try{
		SetDrawBright(100,100,255);
		DrawGraph(0,0,Game.gra_title_back,TRUE);
		static int carsol = 0;
		static int count;
		int number = 7;
		double e_s;
		double e_r;
		bool control = false;
		if(Game.game_count<25){
			if(carsol%number==number-1)	carsol = 0;
			e_s = 0.04 * Game.game_count;
			e_r = Radian(260+4.0*Game.game_count,TRUE);
			count = 0;
		}
		else{
			e_s = 1.00;
			e_r = 0;
			control = true;
			count++;
		}
		for(int i=0;i<7;i++){
			if(i%2==0){
				e_r *= -1;
			}
			SetDrawBright(150,150,150);
			int efe = 0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,170);
			if(carsol%number==i){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				efe = 5;
				SetDrawBright(255,210-abs(90-(count+90)%180),210-abs(90-(count+90)%180));
			}
			if(i<5){
				int x,y;
				if(i<0||i>=GRA_CONFIG_NUM)	throw(1);
				GetGraphSize(Game.gra_config[i],&x,&y);
				DrawRotaGraphF(370-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_config[i],TRUE);
			}
			else if(i==5){
				int x,y;
				if(5>=GRA_OPTION_NUM)	throw(2);
				GetGraphSize(Game.gra_option[5],&x,&y);
				DrawRotaGraphF(370-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_option[5],TRUE);
			}
			else{
				int x,y;
				if(6>=GRA_TITLE_NUM)	throw(3);
				GetGraphSize(Game.gra_title[6],&x,&y);
				DrawRotaGraphF(370-efe+x/2,220+y/2+28*i,e_s,e_r,Game.gra_title[6],TRUE);
			}
			if(i<5){
				int check;
				switch(i){
					case 0:	check = SAVE.Key_Shot;	break;
					case 1:	check = SAVE.Key_Bomb;	break;
					case 2:	check = SAVE.Key_Slow;	break;
					case 3:	check = SAVE.Key_Skip;	break;
					case 4:	check = SAVE.Key_Pause;	break;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
				SetDrawBright(150,150,150);
				if(carsol%number==i){
					SetDrawBright(255,150,150);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				}
				int x,y;
				if(0>=GRA_T_NUMBER_NUM)	throw(4);
				GetGraphSize(Game.gra_t_number[0],&x,&y);
				if(check!=PAD_M)	DrawRotaGraphF(530-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[0],TRUE);
				else			DrawRotaGraphF(530-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[1],TRUE);
				if(check==PAD_A)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[1],TRUE);
				if(check==PAD_B)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[2],TRUE);
				if(check==PAD_C)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[3],TRUE);
				if(check==PAD_X)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[4],TRUE);
				if(check==PAD_Y)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[5],TRUE);
				if(check==PAD_Z)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[6],TRUE);
				if(check==PAD_L)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[7],TRUE);
				if(check==PAD_R)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[8],TRUE);
				if(check==PAD_START)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[9],TRUE);
				if(check==PAD_M)	DrawRotaGraphF(549-efe+x/2,210+y/2+28*i,e_s,e_r,Game.gra_t_number[0],TRUE);
			}
		}
       	
		if(control==true){	
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				carsol ++;
				count = 0;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				carsol --;
				count = 0;
				if(carsol<0){
					carsol += number;
				}
			}
			bool flag = false;
			if(carsol%number<5){	
				for(int i=4;i<14;i++){
					if(c_pad[i]==1){
						SPlaySound(5);
						int ca = carsol%number;
						if(ca==0)SAVE.Key_Shot = i;
						if(ca==1)SAVE.Key_Bomb = i;
						if(ca==2)SAVE.Key_Slow = i;
						if(ca==3)SAVE.Key_Skip = i;
						if(ca==4)SAVE.Key_Pause = i;
						flag = true;
						break;
					}
				}
			}
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				if(carsol%number==5 || carsol%number==6){
					SPlaySound(5);
				}
				if(carsol%number==5){
					SAVE.Key_Shot = PAD_A;
					SAVE.Key_Bomb = PAD_B;
					SAVE.Key_Slow = PAD_Z;
					SAVE.Key_Skip = PAD_L;
					SAVE.Key_Pause = PAD_START;
				}
				else if(carsol%number==6)SMe_ChangeScene(OPTION);
			}
			else if(flag==false&&(c_key[KEY_INPUT_X]==1||c_pad[SAVE.Key_Bomb]==1)){
				SPlaySound(6);
				if(carsol%number==6)SMe_ChangeScene(OPTION);
				carsol = 6;		
			}
		}	
		SetDrawBright(255,255,255);
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMe_KeyConfig\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SMe_Replay(){
	SetDrawBright(100,100,255);
	DrawGraph(0,0,Game.gra_title_back,TRUE);
	SetDrawBright(255,255,255);
	int bright=120;
	int bright_e=180;
	static int efe_count;
	if(Game.game_count==0)	efe_count = 0;
	static int carsol;
	static int stage_carsol;
	int stage = 7;//リプレイ選択後ステージ選択にて
	if(efe_count<30)	bright = 4*efe_count;
	if(efe_count<60)	bright_e = 3*efe_count;
	efe_count++;
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,bright);
	DrawBox(0,0,640,480,0,TRUE);
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,bright_e);
	for(int i=0;i<50;i++){
		DrawRotaGraphF(T_Effect[i].x, T_Effect[i].y, T_Effect[i].large, 0, Game.gra_t_effect, TRUE, FALSE);
	}
	bool control = false;
	static bool change = true;
	static bool scene = true;//true:ユーザー false:ディレクター
	static int select;//0:リプレイ選択 1:ステージ選択
	int effect = 0;
	int effect2 = 255;
	if(Game.game_count==0){
		efe_count = 0;
		scene = true;
		select = 0;
	}
	if(change==false){
		if(Game.game_count<20){
			effect = 320-Game.game_count*16;
		}
		else{
			control = true;
		}
	}
	else{
		if(Game.game_count<20){
			effect2 = 12.75*Game.game_count;
		}
		else{
			control = true;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,effect2);
	if(select==0){
		int color = GetColor(255,255,255);
		char message[128];
		if(scene==true){
			for(int i=0;i<REPLAY_NUM;i++){
				int st_size = 18;
				int y = 120;
				if(Replay[i].month!=0){
					char me[3],le[7],ne[7];
					switch(Replay[i].level){
						case 0:	wsprintf(le, "Easy   ");	break;
						case 1:	wsprintf(le, "Normal ");	break;
						case 2:	wsprintf(le, "Hard   ");	break;
						case 3:	wsprintf(le, "Lunatic");	break;
						case 4:	wsprintf(le, "Extra  ");	break;
					}
					if(Replay[i].chara==0&&Replay[i].weapon==0)	wsprintf(ne, "ReimuA ");
					if(Replay[i].chara==0&&Replay[i].weapon==1)	wsprintf(ne, "ReimuB ");
					if(Replay[i].chara==1&&Replay[i].weapon==0)	wsprintf(ne, "MarisaA");
					if(Replay[i].chara==1&&Replay[i].weapon==1)	wsprintf(ne, "MarisaB");
					if(Replay[i].stage<=54)		wsprintf(me, "St%c",Replay[i].stage);
					else if(Replay[i].stage==55)	wsprintf(me, "Ex ");
					else			wsprintf(me, "All");
					wsprintf(message , "No%2d %s  %s %s %s %02d/%02d" ,
							i+1,
							Replay[i].name,
							ne,
							le,
							me,
							Replay[i].month,
							Replay[i].date );
					int size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
					if(carsol==i)	color = GetColor(255,255,0);
					else		color = GetColor(255,255,255);
					y = 120;
					DrawFormatStringToHandle(320-size/2,y+st_size*i,color,ResultFont2,message);
				}
				else{
					wsprintf(message , "No%2d --------  ------- ------- --- --/--" ,i+1);
					int size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
					if(carsol==i)	color = GetColor(255,255,0);
					else			color = GetColor(255,255,255);
					DrawFormatStringToHandle(320-size/2,y+st_size*i,color,ResultFont2,message);
				}
			}
		}
		else{
			for(int i=0;i<DIRECTOR_REPLAY_NUM-1;i++){
				int st_size = 18;
				int y = 120;
				int size;
				char me[3],le[7],ne[7];
				switch(Director_Replay[i].level){
					case 0:	wsprintf(le, "Easy   ");	break;
					case 1:	wsprintf(le, "Normal ");	break;
					case 2:	wsprintf(le, "Hard   ");	break;
					case 3:	wsprintf(le, "Lunatic");	break;
					case 4:	wsprintf(le, "Extra  ");	break;
				}
				if(Director_Replay[i].chara==0&&Director_Replay[i].weapon==0)	wsprintf(ne, "ReimuA ");
				if(Director_Replay[i].chara==0&&Director_Replay[i].weapon==1)	wsprintf(ne, "ReimuB ");
				if(Director_Replay[i].chara==1&&Director_Replay[i].weapon==0)	wsprintf(ne, "MarisaA");
				if(Director_Replay[i].chara==1&&Director_Replay[i].weapon==1)	wsprintf(ne, "MarisaB");
				if(Director_Replay[i].stage<=54)	wsprintf(me, "St%c",Director_Replay[i].stage);
				else if(Director_Replay[i].stage==55)	wsprintf(me, "Ex ");
				else					wsprintf(me, "All");
				wsprintf(message , "No%2d %s  %s %s %s %02d/%02d" ,
						i+1,
						Director_Replay[i].name,
						ne,
						le,
						me,
						Director_Replay[i].month,
						Director_Replay[i].date );
				size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
				if(carsol==i)	color = GetColor(255,255,0);
				else		color = GetColor(255,255,255);
				DrawFormatStringToHandle(320-size/2,y+st_size*i,color,ResultFont2,message);
			}
		}
	}
	else{
		if(scene==true){
			char me[3],le[7],ne[7];
			char message[64];
			int st_size = 18;
			int y = 120;
			int size;
			int color;
			switch(Replay[carsol].level){
				case 0:	wsprintf(le, "Easy   ");	break;
				case 1:	wsprintf(le, "Normal ");	break;
				case 2:	wsprintf(le, "Hard   ");	break;
				case 3:	wsprintf(le, "Lunatic");	break;
				case 4:	wsprintf(le, "Extra");		break;
			}
			if(Replay[carsol].chara==0&&Replay[carsol].weapon==0)	wsprintf(ne, "ReimuA ");
			if(Replay[carsol].chara==0&&Replay[carsol].weapon==1)	wsprintf(ne, "ReimuB ");
			if(Replay[carsol].chara==1&&Replay[carsol].weapon==0)	wsprintf(ne, "MarisaA");
			if(Replay[carsol].chara==1&&Replay[carsol].weapon==1)	wsprintf(ne, "MarisaB");
			if(Replay[carsol].stage<=57)	wsprintf(me, "St%c",Replay[carsol].stage);
			else				wsprintf(me, "All");
			wsprintf(message , "No%2d %s  %s %s %s %02d/%02d" ,
					carsol+1,
					Replay[carsol].name,
					ne,
					le,
					me,
					Replay[carsol].month,
					Replay[carsol].date );
			size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
			color = GetColor(255,255,255);
			DrawFormatStringToHandle(320-size/2,220,color,ResultFont2,message);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			wsprintf(message , "Stage 0  9999999999");
			size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
			DrawBox(310-size/2,280,330+size/2,280+st_size*8,GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			for(int i=0;i<7;i++){
				if(stage_carsol==i)	color = GetColor(255,255,0);
				else			color = GetColor(255,255,255);
				if(i<6){
					if(Replay[carsol].exist[i]==1)	wsprintf(message , "Stage %d  %10u",i+1,Replay[carsol].end_score[i]);
					else				wsprintf(message , "Stage %d  ----------",i+1);
				}
				else{
					if(Replay[carsol].exist[i]==1)	wsprintf(message , "Extra    %10u",Replay[carsol].end_score[i]);
					else				wsprintf(message , "Extra    ----------");
				}
				DrawFormatStringToHandle(320-size/2,280+st_size/2+i*st_size,color,ResultFont2,message);
			}
		}
		else{
			char me[3],le[7],ne[7];
			char message[64];
			int st_size = 18;
			int y = 120;
			int size;
			int color;
			switch(Director_Replay[carsol].level){
				case 0:	wsprintf(le, "Easy   ");	break;
				case 1:	wsprintf(le, "Normal ");	break;
				case 2:	wsprintf(le, "Hard   ");	break;
				case 3:	wsprintf(le, "Lunatic");	break;
				case 4:	wsprintf(le, "Extra");		break;
			}
			if(Director_Replay[carsol].chara==0&&Director_Replay[carsol].weapon==0)	wsprintf(ne, "ReimuA ");
			if(Director_Replay[carsol].chara==0&&Director_Replay[carsol].weapon==1)	wsprintf(ne, "ReimuB ");
			if(Director_Replay[carsol].chara==1&&Director_Replay[carsol].weapon==0)	wsprintf(ne, "MarisaA");
			if(Director_Replay[carsol].chara==1&&Director_Replay[carsol].weapon==1)	wsprintf(ne, "MarisaB");
			if(Director_Replay[carsol].stage<=57)	wsprintf(me, "St%c",Director_Replay[carsol].stage);
			else				wsprintf(me, "All");
			wsprintf(message , "No%2d %s  %s %s %s %02d/%02d" ,
					carsol+1,
					Director_Replay[carsol].name,
					ne,
					le,
					me,
					Director_Replay[carsol].month,
					Director_Replay[carsol].date );
			size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
			color = GetColor(255,255,255);
			DrawFormatStringToHandle(320-size/2,220,color,ResultFont2,message);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			wsprintf(message , "Stage 0  9999999999");
			size = GetDrawFormatStringWidthToHandle(ResultFont2, message);
			DrawBox(310-size/2,280,330+size/2,280+st_size*8,GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			for(int i=0;i<7;i++){
				if(stage_carsol==i)	color = GetColor(255,255,0);
				else			color = GetColor(255,255,255);
				if(i<6){
					if(Director_Replay[carsol].exist[i]==1)	wsprintf(message , "Stage %d  %10u",i+1,Director_Replay[carsol].end_score[i]);
					else					wsprintf(message , "Stage %d  ----------",i+1);
				}
				else{
					if(Director_Replay[carsol].exist[i]==1)	wsprintf(message , "Extra    %10u",Director_Replay[carsol].end_score[i]);
					else					wsprintf(message , "Extra    ----------");
				}
				DrawFormatStringToHandle(320-size/2,280+st_size/2+i*st_size,color,ResultFont2,message);
			}
		}
	}
	if(control==true){
		if(select==0){
			if(c_key[KEY_INPUT_LEFT]%20==1 || c_pad[PAD_LEFT]%20==1){
				if(c_key[KEY_INPUT_LEFT]==21 || c_pad[PAD_LEFT]==21){
					c_key[KEY_INPUT_LEFT] = 1;
					c_pad[PAD_LEFT] = 1;
				}
				SPlaySound(7);
				scene = (scene+1)%2;
				change = false;
				Game.game_count = 0;
				carsol = 0;
			}	
			else if(c_key[KEY_INPUT_RIGHT]%20==1 || c_pad[PAD_RIGHT]%20==1){
				if(c_key[KEY_INPUT_RIGHT]==21 || c_pad[PAD_RIGHT]==21){
					c_key[KEY_INPUT_RIGHT] = 1;
					c_pad[PAD_RIGHT] = 1;
				}
				SPlaySound(7);
				scene = (scene+1)%2;
				change = false;
				Game.game_count = 0;
				carsol = 0;
			}
		}	
		if(c_key[KEY_INPUT_DOWN]%20==1 || c_pad[PAD_DOWN]%20==1){
			if(c_key[KEY_INPUT_DOWN]==21 || c_pad[PAD_DOWN]==21){
				c_key[KEY_INPUT_DOWN] = 1;
				c_pad[PAD_DOWN] = 1;
			}
			SPlaySound(7);
			if(select==0){
				carsol ++;
				if(scene==true)	carsol = carsol%REPLAY_NUM;
				else		carsol = carsol%(DIRECTOR_REPLAY_NUM-1);
			}
			else{
				stage_carsol ++;
				stage_carsol = stage_carsol%stage;
			}
		}	
		else if(c_key[KEY_INPUT_UP]%20==1 || c_pad[PAD_UP]%20==1){
			if(c_key[KEY_INPUT_UP]==21 || c_pad[PAD_UP]==21){
				c_key[KEY_INPUT_UP] = 1;
				c_pad[PAD_UP] = 1;
			}
			SPlaySound(7);
			if(select==0){
				carsol --;
				if(carsol<0){
					if(scene==true)	carsol += REPLAY_NUM;
					else		carsol += DIRECTOR_REPLAY_NUM-1;
				}
			}
			else{
				stage_carsol --;
				if(stage_carsol<0)	stage_carsol += stage;
			}
		}	
		if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
			SPlaySound(5);
			if(select==0){
				if(Replay[carsol].month!=0||scene==false){
					select = 1;
					stage_carsol = 0;
				}
			}
			else{
				repnum = carsol;
				if(scene==true&&Replay[repnum].exist[stage_carsol]==1){
					SAVE.Level = Replay[repnum].level;
					SAVE.Chara = Replay[repnum].chara;
					SAVE.Weapon = Replay[repnum].weapon;
					Game.stage = stage_carsol+1;
					start_stage = stage_carsol+1;
					start_life = Replay[repnum].start_player[start_stage-1];
					start_power = Replay[repnum].start_power[start_stage-1];
					Game.con_times = 0;
					PlayerControlFlag = 1;
					SReset();
					SSc_Reset();
					SSc_Reset2();
					SMe_ChangeScene(SHOOTING);
				}
				else if(scene==false&&Director_Replay[repnum].exist[stage_carsol]==1){
					SAVE.Level = Director_Replay[repnum].level;
					SAVE.Chara = Director_Replay[repnum].chara;
					SAVE.Weapon = Director_Replay[repnum].weapon;
					Game.stage = stage_carsol+1;
					start_stage = stage_carsol+1;
					start_life = Director_Replay[repnum].start_player[start_stage-1];
					start_power = Director_Replay[repnum].start_power[start_stage-1];
					Game.con_times = 0;
					PlayerControlFlag = 2;
					SReset();
					SSc_Reset();
					SSc_Reset2();
					SMe_ChangeScene(SHOOTING);
				}
			}
		}
		else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
			SPlaySound(6);
			change = true;
			if(select==0)	SMe_ChangeScene(TITLE);
			else		select = 0;
		}
	}
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	SMe_Effect();
	return;
}

void SMe_Result(){
	SetDrawBright(100,100,255);
	DrawGraph(0,0,Game.gra_title_back,TRUE);
	SetDrawBright(255,255,255);
	int bright=120;
	int bright_e=180;
	static int efe_count;
	if(Game.game_count==0)	efe_count = 0;
	if(efe_count<30)	bright = 4*efe_count;
	if(efe_count<60)	bright_e = 3*efe_count;
	efe_count++;
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,bright);
	DrawBox(0,0,640,480,0,TRUE);
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,bright_e);
	for(int i=0;i<50;i++){
		DrawRotaGraphF(T_Effect[i].x, T_Effect[i].y, T_Effect[i].large, 0, Game.gra_t_effect, TRUE, FALSE);
	}
	static int level = 1;
	static int chara = 0;
	static int side = 0;
	static int spell_chara = 0;
	int spell_chara_num = 4;
	int side_num = 13;
	bool control = false;
	static bool change = true;//true:レベル false:キャラの変更
	int effect = 0;
	int effect2 = 255;
	if(change==false){
		if(Game.game_count<20){
			effect = 320-Game.game_count*16;
		}
		else{
			control = true;
		}
	}
	else{
		if(Game.game_count<20){
			effect2 = 12.75*Game.game_count;
		}
		else{
			control = true;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,effect2);
	int color = GetColor(255,255,255);
	char message[128];
	int color2;
	if(side==0){
		switch(level%5){
			case 0:
				 color2 = GetColor(0,255,0);
				wsprintf(message , "Easy");
				break;
			case 1:
				 color2 = GetColor(0,0,255);
				wsprintf(message , "Normal");
				break;
			case 2:
				 color2 = GetColor(255,0,0);
				wsprintf(message , "Hard");
				break;
			case 3:
				 color2 = GetColor(255,0,200);
				wsprintf(message , "Lunatic");
				break;
			case 4:
				 color2 = GetColor(255,200,0);
				wsprintf(message , "Extra");
				break;
		}
		DrawStringEdge(10,80,color,ResultFont,message,effect2,color2);
		if(chara%2==0){
			color = GetColor(255,200,200);
			wsprintf(message , "博麗 霊夢（Ａ）");
			int size = GetDrawFormatStringWidthToHandle(ResultFont,message);
			DrawStringEdge(160-size/2+effect,100,color,ResultFont,message,effect2);
			wsprintf(message , "博麗 霊夢（Ｂ）");
			size = GetDrawFormatStringWidthToHandle(ResultFont,message);
			DrawStringEdge(480-size/2+effect,100,color,ResultFont,message,effect2);
			color = GetColor(255,255,255);
			for(int i=0;i<10;i++){
				wsprintf(message , " %d.%-8s%11u(%c)",i+1,SAVE.ReimuA.level[level%5].score[i].name,SAVE.ReimuA.level[level%5].score[i].score,SAVE.ReimuA.level[level%5].score[i].stage);
				if(i==9)	wsprintf(message , "%d.%-8s%11u(%c)",i+1,SAVE.ReimuA.level[level%5].score[i].name,SAVE.ReimuA.level[level%5].score[i].score,SAVE.ReimuA.level[level%5].score[i].stage);
				size = GetDrawFormatStringWidthToHandle(ResultFont2,message);
				DrawStringEdge(160-size/2+effect,130+18*i,color,ResultFont2,message,effect2);
			}
			for(int i=0;i<10;i++){
				wsprintf(message , " %d.%-8s%11u(%c)",i+1,SAVE.ReimuB.level[level%5].score[i].name,SAVE.ReimuB.level[level%5].score[i].score,SAVE.ReimuB.level[level%5].score[i].stage);
				if(i==9)	wsprintf(message , "%d.%-8s%11u(%c)",i+1,SAVE.ReimuB.level[level%5].score[i].name,SAVE.ReimuB.level[level%5].score[i].score,SAVE.ReimuB.level[level%5].score[i].stage);
				size = GetDrawFormatStringWidthToHandle(ResultFont2,message);
				DrawStringEdge(480-size/2+effect,130+18*i,color,ResultFont2,message,effect2);
			}
		}
		else{
			color = GetColor(200,200,255);
			wsprintf(message , "霧雨 魔理沙（Ａ）");
			int size = GetDrawFormatStringWidthToHandle(ResultFont,message);
			DrawStringEdge(160-size/2+effect,100,color,ResultFont,message,effect2);
			wsprintf(message , "霧雨 魔理沙（Ｂ）");
			size = GetDrawFormatStringWidthToHandle(ResultFont,message);
			DrawStringEdge(480-size/2+effect,100,color,ResultFont,message,effect2);
			color = GetColor(255,255,255);
			for(int i=0;i<10;i++){
				wsprintf(message , " %d.%-8s%11u(%c)",i+1,SAVE.MarisaA.level[level%5].score[i].name,SAVE.MarisaA.level[level%5].score[i].score,SAVE.MarisaA.level[level%5].score[i].stage);
				if(i==9)	wsprintf(message , "%d.%-8s%11u(%c)",i+1,SAVE.MarisaA.level[level%5].score[i].name,SAVE.MarisaA.level[level%5].score[i].score,SAVE.MarisaA.level[level%5].score[i].stage);
				size = GetDrawFormatStringWidthToHandle(ResultFont2,message);
				DrawStringEdge(160-size/2+effect,130+18*i,color,ResultFont2,message,effect2);
			}
			for(int i=0;i<10;i++){
				wsprintf(message , " %d.%-8s%11u(%c)",i+1,SAVE.MarisaB.level[level%5].score[i].name,SAVE.MarisaB.level[level%5].score[i].score,SAVE.MarisaB.level[level%5].score[i].stage);
				if(i==9)	wsprintf(message , "%d.%-8s%11u(%c)",i+1,SAVE.MarisaB.level[level%5].score[i].name,SAVE.MarisaB.level[level%5].score[i].score,SAVE.MarisaB.level[level%5].score[i].stage);
				size = GetDrawFormatStringWidthToHandle(ResultFont2,message);
				DrawStringEdge(480-size/2+effect,130+18*i,color,ResultFont2,message,effect2);
			}
		}
	}
	else{
		if(spell_chara<2)	color = GetColor(255,200,200);
		else			color = GetColor(200,200,255);
		switch(spell_chara){
			case 0:	wsprintf(message , "博麗 霊夢（完全追尾型）");	break;
			case 1:	wsprintf(message , "博麗 霊夢（前方集中型）");	break;
			case 2:	wsprintf(message , "霧雨 魔理沙（前方貫通型）");	break;
			case 3:	wsprintf(message , "霧雨 魔理沙（前方特殊型）");	break;
		}
		//int size = GetDrawFormatStringWidthToHandle(ResultFont,message);
		DrawStringEdge(10,80,color,ResultFont,message,effect2);
		int get_num = 0,cha_num = 0;
		for(int i=0;i<SPELL_NUM;i++){
			if(SAVE.Spell[i].get_times[spell_chara/2][spell_chara%2]>0)	get_num++;
			if(SAVE.Spell[i].challenge_times[spell_chara/2][spell_chara%2]>0)	cha_num++;
		}
		color = GetColor(255,255,255);
		wsprintf(message , "挑戦:%03d/114　%d％　　取得:%03d/114　%d％",cha_num,cha_num*100/114,get_num,get_num*100/114);
		int size = GetDrawFormatStringWidthToHandle(ResultFont,message);
		DrawStringEdge(620-size,100,color,ResultFont,message,effect2);
		for(int i=0;i<10&&10*(side-1)+i<SPELL_NUM;i++){
			if(SAVE.Spell[10*(side-1)+i].get_times[spell_chara/2][spell_chara%2]>0)		color = GetColor(255,255,255);
			else		color = GetColor(100,100,100);
			int basesize = GetDrawFormatStringWidthToHandle(ResultFont2,"No.005 魑魅「デモンズパンデモニウム -Easy-」 (E) 999 / 999");
			int basesize2 = GetDrawFormatStringWidthToHandle(ResultFont2,"No.005 ");
			int basesize3 = GetDrawFormatStringWidthToHandle(ResultFont2,"No.005 魑魅「デモンズパンデモニウム -Easy-」 ");
			int basesize4 = GetDrawFormatStringWidthToHandle(ResultFont2,"No.005 魑魅「デモンズパンデモニウム -Easy-」 (E) ");
			wsprintf(message , "No.%03d",10*(side-1)+i+1);
			DrawStringEdge(320-basesize/2+effect,130+18*i,color,ResultFont2,message,effect2);
			if(SAVE.Spell[10*(side-1)+i].challenge_times[spell_chara/2][spell_chara%2]>0)	wsprintf(message , "%s",Spell[10*(side-1)+i].name);
			else	wsprintf(message , "---------------------");
			DrawStringEdge(320-basesize/2+basesize2+effect,130+18*i,color,ResultFont2,message,effect2);
			char level;
			switch(Spell[10*(side-1)+i].Level){
				case 0:	level = 'E';	break;
				case 1:	level = 'N';	break;
				case 2:	level = 'H';	break;
				case 3:	level = 'L';	break;
				case 4:	level = 'X';	break;
			}
			wsprintf(message , "(%c)",level);
			DrawStringEdge(320-basesize/2+basesize3+effect,130+18*i,color,ResultFont2,message,effect2);
			if(SAVE.Spell[10*(side-1)+i].challenge_times[spell_chara/2][spell_chara%2]>0)	wsprintf(message , "%03d / %03d",SAVE.Spell[10*(side-1)+i].get_times[spell_chara/2][spell_chara%2],SAVE.Spell[10*(side-1)+i].challenge_times[spell_chara/2][spell_chara%2]);
			else	wsprintf(message , "--- / ---");
			DrawStringEdge(320-basesize/2+basesize4+effect,130+18*i,color,ResultFont2,message,effect2);
		}
		color = GetColor(255,255,255);
	}	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int hour = SAVE.PlayTime/3600;
	int minute = (SAVE.PlayTime-hour*3600)/60;
	int second = SAVE.PlayTime-hour*3600-minute*60;
	wsprintf(message , "プレイ時間 %02d:%02d:%02d",hour,minute,second);
	int size = GetDrawFormatStringWidthToHandle(ResultFont,message);
	DrawStringEdge(320-size/2,340,color,ResultFont2,message);
	wsprintf(message , "←→ キャラクター変更");
	DrawStringEdge(100,375,color,ResultFont2,message);
	wsprintf(message , "↑↓ 難易度変更");
	DrawStringEdge(100,395,color,ResultFont2,message);
	wsprintf(message , "Shot ハイスコア / スペルカード");
	DrawStringEdge(100,415,color,ResultFont2,message);
	wsprintf(message , "Bomb タイトルに戻る");
	DrawStringEdge(100,435,color,ResultFont2,message);
	
	if(control==true){
		if(c_key[KEY_INPUT_DOWN]%20==1 || c_pad[PAD_DOWN]%20==1){
			if(c_key[KEY_INPUT_DOWN]==21 || c_pad[PAD_DOWN]==21){
				c_key[KEY_INPUT_DOWN] = 1;
				c_pad[PAD_DOWN] = 1;
			}
			if(side==0){
				SPlaySound(7);
				level ++;
				change = true;
				Game.game_count = 0;
			}
		}	
		else if(c_key[KEY_INPUT_UP]%20==1 || c_pad[PAD_UP]%20==1){
			if(c_key[KEY_INPUT_UP]==21 || c_pad[PAD_UP]==21){
				c_key[KEY_INPUT_UP] = 1;
				c_pad[PAD_UP] = 1;
			}
			if(side==0){
				SPlaySound(7);
				level --;
				if(level<0)	level += 5;
				change = true;
				Game.game_count = 0;
			}
		}	
		else if(c_key[KEY_INPUT_LEFT]%20==1 || c_pad[PAD_LEFT]%20==1){
			if(c_key[KEY_INPUT_LEFT]==21 || c_pad[PAD_LEFT]==21){
				c_key[KEY_INPUT_LEFT] = 1;
				c_pad[PAD_LEFT] = 1;
			}
			SPlaySound(7);
			if(side==0){
				chara --;
				if(chara<0)	chara += 2;
			}
			else{
				spell_chara --;
				if(spell_chara<0)	spell_chara += spell_chara_num;
			}
			change = false;
			Game.game_count = 0;
		}	
		else if(c_key[KEY_INPUT_RIGHT]%20==1 || c_pad[PAD_RIGHT]%20==1){
			if(c_key[KEY_INPUT_RIGHT]==21 || c_pad[PAD_RIGHT]==21){
				c_key[KEY_INPUT_RIGHT] = 1;
				c_pad[PAD_RIGHT] = 1;
			}
			SPlaySound(7);
			if(side==0){
				chara ++;
			}
			else{
				spell_chara++;
				spell_chara = spell_chara%spell_chara_num;
			}
			change = false;
			Game.game_count = 0;
		}	
		if(c_key[KEY_INPUT_Z]==1 || c_pad[SAVE.Key_Shot]==1 || c_key[KEY_INPUT_RETURN]==1){
			SPlaySound(5);
			change = true;
			side ++;
			side = side%side_num;
		}
		else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
			SPlaySound(6);
			change = true;
			SMe_ChangeScene(TITLE);
		}
		/*
		if(c_key[KEY_INPUT_D]==1){
			FILE *fp;
			if((fp=fopen("score.txt","w")) == NULL){
				return;
			}
			DATEDATA D;
			GetDateTime(&D);
			char str[256];
			wsprintf(str , "#東方大往生 詳細スコア\n#TimeStamp: %04d/%02d/%02d %02d:%02d:%02d\n\n",D.Year,D.Mon,D.Day,D.Hour,D.Min,D.Sec);
			fputs(str,fp);
			int hour = SAVE.PlayTime/3600;
			int minute = (SAVE.PlayTime - hour*3600)/60;
			int second = SAVE.PlayTime - hour*3600 - minute*60;
			wsprintf(str , "総プレイ時間: %02d:%02d:%02d\n\n",hour,minute,second);
			fputs(str,fp);
			for(int a=0;a<4;a++){
				switch(a){
					case 0:	wsprintf(str , "■Easy\n");
						break;
					case 1:	wsprintf(str , "\n\n\n\n■Normal\n");
						break;
					case 2:	wsprintf(str , "\n\n\n\n■Hard\n");
						break;
					case 3:	wsprintf(str , "\n\n\n\n■Lunatic\n");
						break;
				}
				fputs(str,fp);
				for(int b=0;b<4;b++){
					switch(b){
						case 0:	wsprintf(str , "\t□博麗霊夢（ホーミング）");
							break;
						case 1:	wsprintf(str , "\n\n\t□博麗霊夢（ニードル）");
							break;
						case 2:	wsprintf(str , "\n\n\t□霧雨魔理沙（レーザー）");
							break;
						case 3:	wsprintf(str , "\n\n\t□霧雨魔理沙（トリックナイフ）");
							break;
					}
					fputs(str,fp);
					for(int i=0;i<10;i++){
						wsprintf(str , "\n\n\t　　No.%d\n",i+1);
						fputs(str,fp);
						int time;//プレイ時間表記用
						switch(b){
							case 0:
								time = SAVE.ReimuA.level[a].score[i].time/3600;
								wsprintf(str , "\t\t　　ネーム: %s\n\t\tプレイ日時: %04d/%02d/%02d %02d:%02d:%02d\n\t\t　　進行度: Stage %c\n\t\t　　　得点: %d\n\t\tプレイ時間: %d分%d秒 \n\n",
										SAVE.ReimuA.level[a].score[i].name,
										SAVE.ReimuA.level[a].score[i].year,
										SAVE.ReimuA.level[a].score[i].month,
										SAVE.ReimuA.level[a].score[i].date,
										SAVE.ReimuA.level[a].score[i].hour,
										SAVE.ReimuA.level[a].score[i].minute,
										SAVE.ReimuA.level[a].score[i].second,
										SAVE.ReimuA.level[a].score[i].stage,
										SAVE.ReimuA.level[a].score[i].score,
										time,
										(SAVE.ReimuA.level[a].score[i].time/60)%60);
								fputs(str,fp);
								if(a<=5){
									for(int c=0;c<3;c++){
										wsprintf(str , "\t\tステージ%d 得点: %d\n",
												c+1,
												SAVE.ReimuA.level[a].score[i].s_score[c]);
										fputs(str,fp);
										int ti = SAVE.ReimuA.level[a].score[i].s_time[c]/3600;
										wsprintf(str , "\t\t　　　　  時間: %d分%02d秒\n",
												ti,
												(SAVE.ReimuA.level[a].score[i].s_time[c]/60)%60);
										fputs(str,fp);
									}
								}
								break;
							case 1:
								time = SAVE.ReimuB.level[a].score[i].time/3600;
								wsprintf(str , "\t\t　　ネーム: %s\n\t\tプレイ日時: %04d/%02d/%02d %02d:%02d:%02d\n\t\t　　進行度: Stage %c\n\t\t　　　得点: %d\n\t\tプレイ時間: %d分%d秒 \n\n",
										SAVE.ReimuB.level[a].score[i].name,
										SAVE.ReimuB.level[a].score[i].year,
										SAVE.ReimuB.level[a].score[i].month,
										SAVE.ReimuB.level[a].score[i].date,
										SAVE.ReimuB.level[a].score[i].hour,
										SAVE.ReimuB.level[a].score[i].minute,
										SAVE.ReimuB.level[a].score[i].second,
										SAVE.ReimuB.level[a].score[i].stage,
										SAVE.ReimuB.level[a].score[i].score,
										time,
										(SAVE.ReimuB.level[a].score[i].time/60)%60);
								fputs(str,fp);
								if(a<=5){
									for(int c=0;c<3;c++){
										wsprintf(str , "\t\tステージ%d 得点: %d\n",
												c+1,
												SAVE.ReimuB.level[a].score[i].s_score[c]);
										fputs(str,fp);
										int ti = SAVE.ReimuB.level[a].score[i].s_time[c]/3600;
										wsprintf(str , "\t\t　　　　  時間: %d分%02d秒\n",
												ti,
												(SAVE.ReimuB.level[a].score[i].s_time[c]/60)%60);
										fputs(str,fp);
									}
								}
								break;
							case 2:
								time = SAVE.MarisaA.level[a].score[i].time/3600;
								wsprintf(str , "\t\t　　ネーム: %s\n\t\tプレイ日時: %04d/%02d/%02d %02d:%02d:%02d\n\t\t　　進行度: Stage %c\n\t\t　　　得点: %d\n\t\tプレイ時間: %d分%d秒 \n\n",
										SAVE.MarisaA.level[a].score[i].name,
										SAVE.MarisaA.level[a].score[i].year,
										SAVE.MarisaA.level[a].score[i].month,
										SAVE.MarisaA.level[a].score[i].date,
										SAVE.MarisaA.level[a].score[i].hour,
										SAVE.MarisaA.level[a].score[i].minute,
										SAVE.MarisaA.level[a].score[i].second,
										SAVE.MarisaA.level[a].score[i].stage,
										SAVE.MarisaA.level[a].score[i].score,
										time,
										(SAVE.MarisaA.level[a].score[i].time-60*time)/60);
								fputs(str,fp);
								if(a<=5){
									for(int c=0;c<3;c++){
										wsprintf(str , "\t\tステージ%d 得点: %d\n",
												c+1,
												SAVE.MarisaA.level[a].score[i].s_score[c]);
										fputs(str,fp);
										int ti = SAVE.MarisaA.level[a].score[i].s_time[c]/3600;
										wsprintf(str , "\t\t　　　　  時間: %d分%02d秒\n",
												ti,
												(SAVE.MarisaA.level[a].score[i].s_time[c]-60*ti)/60);
										fputs(str,fp);
									}
								}
								break;
							case 3:
								time = SAVE.MarisaB.level[a].score[i].time/3600;
								wsprintf(str , "\t\t　　ネーム: %s\n\t\tプレイ日時: %04d/%02d/%02d %02d:%02d:%02d\n\t\t　　進行度: Stage %c\n\t\t　　　得点: %d\n\t\tプレイ時間: %d分%d秒 \n\n",
										SAVE.MarisaB.level[a].score[i].name,
										SAVE.MarisaB.level[a].score[i].year,
										SAVE.MarisaB.level[a].score[i].month,
										SAVE.MarisaB.level[a].score[i].date,
										SAVE.MarisaB.level[a].score[i].hour,
										SAVE.MarisaB.level[a].score[i].minute,
										SAVE.MarisaB.level[a].score[i].second,
										SAVE.MarisaB.level[a].score[i].stage,
										SAVE.MarisaB.level[a].score[i].score,
										time,
										(SAVE.MarisaB.level[a].score[i].time-60*time)/60);
								fputs(str,fp);
								if(a<=5){
									for(int c=0;c<3;c++){
										wsprintf(str , "\t\tステージ%d 得点: %d\n",
												c+1,
												SAVE.MarisaB.level[a].score[i].s_score[c]);
										fputs(str,fp);
										int ti = SAVE.MarisaB.level[a].score[i].s_time[c]/3600;
										wsprintf(str , "\t\t　　　　  時間: %d分%02d秒\n",
												ti,
												(SAVE.MarisaB.level[a].score[i].s_time[c]-60*ti)/60);
										fputs(str,fp);
									}
								}
								break;
						}
					}
				}
			}
			wsprintf(str , "\n#End of File");
			fputs(str,fp);
			fclose(fp);
		}
		*/
	}
	SMe_Effect();
	return;
}

void SMe_MusicRoom(){
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	SetDrawBright(100,100,255);
	DrawGraph(0,0,Game.gra_title_back,TRUE);
	SetDrawBright(255,255,255);
	int bright=120;
	int bright_e=180;
	if(Game.game_count<30)	bright = 4*Game.game_count;
	if(Game.game_count<60)	bright_e = 3*Game.game_count;
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,bright);
	DrawBox(0,0,640,480,0,TRUE);
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,bright_e);
	for(int i=0;i<50;i++){
		DrawRotaGraphF(T_Effect[i].x, T_Effect[i].y, T_Effect[i].large, 0, Game.gra_t_effect, TRUE, FALSE);
	}
	static int carsol = 0;
	static int count;
	static int now_carsol;
	static bool PlayFlag = false;
	int number = BGM_NUM;
	if(Game.game_count==0){
		carsol = 0;
		now_carsol = 0;
	}
	for(int i=0;i<number;i++){
		char message[64];
		int color = GetColor(255,255,255);
		int color2 = GetColor(0,0,0);
 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		if(carsol%number==i){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			color2 = GetColor(100,100,0);
		}
		if(SAVE.BgmFlag[i]>0){
			switch(i){
				case 0:	wsprintf(message , " 1.衛星カフェテラス");		break;
				case 1:	wsprintf(message , " 2.月面ツアーへようこそ");		break;
				case 2:	wsprintf(message , " 3.呑んべぇのレムリア");		break;
				case 3:	wsprintf(message , " 4.Demystify Feast");		break;
				case 4:	wsprintf(message , " 5.Ｇ　Ｆｒｅｅ");			break;
				case 5:	wsprintf(message , " 6.ネクロファンタジア");		break;
				case 6:	wsprintf(message , " 7.御伽の国の鬼が島　～ Missing Power");	break;
				case 7:	wsprintf(message , " 8.風神少女");	break;
				case 8:	wsprintf(message , " 9.ネクロファンタジア");	break;
				case 9:	wsprintf(message , "10.ボーダーオブディメンション");	break;
				case 10:wsprintf(message , "11.向こう側の月");	break;
				case 11:wsprintf(message , "12.幽玄の槭樹 ～ Eternal Dream");	break;
				case 12:wsprintf(message , "13.妖々跋扈　～ Speed Fox！");	break;
				case 13:wsprintf(message , "14.アンノウンＸ　～ Unfound Adventure");	break;
			}
		}
		else{
			wsprintf(message , "%2d.？？？？？？？？",i+1);
		}
		DrawStringToHandle(50,100+18*i,message,color,MusicFont,color2);
	}
	int base_y = 390;
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,200);
	DrawBox(40,base_y-10,600,460,0,TRUE);
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	if(SAVE.BgmFlag[now_carsol]>0){
		switch(now_carsol){
			case 0:
				DrawStringToHandle(60,base_y,"♪衛星カフェテラス",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　タイトル画面のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 大空魔術 ～ Magical Astronomyより",GetColor(255,255,255),MusicFont2);
				break;
			case 1:
				DrawStringToHandle(60,base_y,"♪月面ツアーへようこそ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　ステージ１のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 大空魔術 ～ Magical Astronomyより",GetColor(255,255,255),MusicFont2);
				break;
			case 2:
				DrawStringToHandle(60,base_y,"♪呑んべぇのレムリア",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　伊吹 萃香・射命丸 文（１・２ボス）のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 黄昏酒場～Uwabami Breakers～より",GetColor(255,255,255),MusicFont2);
				break;
			case 3:
				DrawStringToHandle(60,base_y,"♪Demystify Feast",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　ステージ２のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 大空魔術 ～ Magical Astronomyより",GetColor(255,255,255),MusicFont2);
				break;
			case 4:
				DrawStringToHandle(60,base_y,"♪Ｇ　Ｆｒｅｅ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　ステージ３のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 大空魔術 ～ Magical Astronomyより",GetColor(255,255,255),MusicFont2);
				break;
			case 5:
				DrawStringToHandle(60,base_y,"♪ネクロファンタジア",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　八雲 紫（３ボス）のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 大空魔術 ～ Magical Astronomyより",GetColor(255,255,255),MusicFont2);
				break;
			case 6:
				DrawStringToHandle(60,base_y,"♪御伽の国の鬼が島　～ Missing Power",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　伊吹 萃香（４ボス）のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　東方萃夢想より",GetColor(255,255,255),MusicFont2);
				break;
			case 7:
				DrawStringToHandle(60,base_y,"♪風神少女",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　射命丸 文（５ボス）のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　東方文花帖より",GetColor(255,255,255),MusicFont2);
				break;
			case 8:
				DrawStringToHandle(60,base_y,"♪ネクロファンタジア",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　八雲 紫（６ボス）のテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　東方妖々夢より",GetColor(255,255,255),MusicFont2);
				break;
			case 9:
				DrawStringToHandle(60,base_y,"♪ボーダーオブディメンション",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　ラストスペルのテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:おかび　原曲：ネクロファンタジア",GetColor(255,255,255),MusicFont2);
				break;
			case 10:
				DrawStringToHandle(60,base_y,"♪向こう側の月",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　エンディングのテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 大空魔術 ～ Magical Astronomyより",GetColor(255,255,255),MusicFont2);
				break;
			case 11:
				DrawStringToHandle(60,base_y,"♪幽玄の槭樹 ～ Eternal Dream",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　スタッフロールのテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 夢違科学世紀より",GetColor(255,255,255),MusicFont2);
				break;
			case 12:
				DrawStringToHandle(60,base_y,"♪妖々跋扈　～ Speed Fox！",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　エクストラステージのテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 東方妖々夢(例大祭１ver)より",GetColor(255,255,255),MusicFont2);
				break;
			case 13:
				DrawStringToHandle(60,base_y,"♪アンノウンＸ　～ Unfound Adventure",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　四季映姫・ヤマザナドゥのテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 東方非想天則より",GetColor(255,255,255),MusicFont2);
				break;
			case 15:
				DrawStringToHandle(60,base_y,"♪プレイヤーズスコア",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*1,"　ゲームオーバーのテーマ",GetColor(255,255,255),MusicFont2);
				DrawStringToHandle(60,base_y+20*2,"　作曲者:ＺＵＮ　 東方風神録より",GetColor(255,255,255),MusicFont2);
				break;
		}
	}
	else{
		DrawStringToHandle(60,base_y,"※この曲はゲーム本編で未再生です※",GetColor(255,255,255),MusicFont2);
		DrawStringToHandle(60,base_y+20*1,"　もう一度決定キーを押すと曲を再生させます",GetColor(255,255,255),MusicFont2);
		DrawStringToHandle(60,base_y+20*2,"　（曲の情報は表示しません）",GetColor(255,255,255),MusicFont2);
	}
	if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
		if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
			c_key[KEY_INPUT_DOWN] = 21;
			c_pad[PAD_DOWN] = 21;
		}
		SPlaySound(7);
		carsol ++;
		carsol = carsol%number;
		count = 0;
		PlayFlag = false;
	}	
	else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
		if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
			c_key[KEY_INPUT_UP] = 21;
			c_pad[PAD_UP] = 21;
		}
		SPlaySound(7);
		carsol --;
		count = 0;
		if(carsol<0){
			carsol += number;
		}
		PlayFlag = false;
	}	
	if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
		if(SAVE.BgmFlag[carsol%number]>0)	PlayFlag = true;
		if(PlayFlag==true)			SMu_PlayBgm(carsol%number);
		PlayFlag = false;
		if(SAVE.BgmFlag[carsol%number]==0)	PlayFlag = true;
		now_carsol = carsol%number;
	}
	else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
		SPlaySound(6);
		SMe_ChangeScene(TITLE);
	}
	
	SMe_Effect();
	return;
}

void SMe_Effect(){
	for(int i=0;i<50;i++){
		T_Effect[i].x += T_Effect[i].move_x;
		T_Effect[i].y += T_Effect[i].speed;
		if(T_Effect[i].x<-15||T_Effect[i].x>655||T_Effect[i].y>495){
			T_Effect[i].x = get_rand(640);
			T_Effect[i].y = -15;
			T_Effect[i].move_x = 0.5*sin(Radian(get_rand(360),TRUE));
			T_Effect[i].large = 0.1+0.01*get_rand(40);
			T_Effect[i].speed = 0.5+0.01*get_rand(50);
		}
	}
	return;
}

void Smain(){
	try{
		if(Pause==0&&ResultCount<60){
			if(Boss.countdown>0&&Boss.exist==1&&Boss.life<=0){
				if(Game.stage==1&&GameScene==0&&Boss.gage_exist==0&&Boss.count<15)	SShake(0,10);
			}
			if(Game.shake_count>0){
				SShake(0,10);
				Game.shake_count--;
			}
			if(Game.count<2){
				for(int i=0;i<256;i++){
					if(i<0||i>=C_KEY_NUM)	throw(1);
					c_key[i] = 0;
				}
				int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
				for(int i=0;i<14;i++){
					c_pad[i] = 0; 
				}
			}
			switch(Game.stage){
				case 0:	DebugStage();	break;
				case 1:	Stage1();	break;
				case 2:	Stage2();	break;
				case 3:	Stage3();	break;
				case 4:	Stage4();	break;
				case 5:	Stage5();	break;
				case 6:	Stage6();	break;
				case 7:	Stage7();	break;
			}
			SPs_Main();
			SIt_Main();
			SBos_Main();
			SEn_Main();
			SEs_Main();
			SLas_Main();
			SPl_Main();
			SBa_Draw();
			SPs_Draw();
			SIt_Draw();
			SPl_Draw();
			SBos_Draw();
			SEn_Draw();
			SEs_Draw();
			SLas_Draw();
			SEf_Draw();
			SBom_Draw();
			SSp_Draw();
			int flash;
			if(Player.slow>0){
				if(Player.slow<5)	flash = 51.0*Player.slow;
				else			flash = 255;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
				DrawRotaGraphF(Player.x+shake_x, Player.y+shake_y, 1.0, Radian(3*Player.count,TRUE), gra_atari, TRUE, FALSE);
				//DrawBox(Player.atari_x[0],Player.atari_y[0],Player.atari_x[1],Player.atari_y[1],0,TRUE);
			}
			shake_x = 0;
			shake_y = 0;
			if(Game.count==0){
				if(SAVE.Chara==0)	Player.speed = 3.5;
				else			Player.speed = 4.0;
			}
			//if(120<Game.count%180)	SShake(0,10);
			music_count++;
			Game.count++;
			if(Game.stage==3 && ((GameScene==1&&Talk.scene>=3)||(ResultCount>0)) && Talk.carsol==0){
				Talk.count -= 170;
				if(ResultCount==0&&Talk.count<120){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Talk.count);
				}
				else{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				}
				int r = 2.0*Talk.count;
				if(ResultCount>0)	r = 400;
				DrawOval(CENTER_X,CENTER_Y,250,r,GetColor(255,255,255),TRUE);
				Talk.count += 170;	
			}
			if(Talk.count>0){
				STa_Draw();
			}
		}
		SSc_Draw();
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:Smain\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SPlaySound(int i){
	if(i==5)	SMu_PlaySound(i);
	else		SoundFlag[i] = 1;
	return;
}

void SSoundEffect(){
	for(int i=0;i<SOUND_NUM;i++){
		if(SoundFlag[i]==1)	SMu_PlaySound(i);
		SoundFlag[i] = 0;
	}
	return;
}
 
void SLoad(){
	char *name = "th00score.dat";
	FILE *fp;
	if((fp=fopen(name,"rb")) == NULL){
		SSaveReset();
		fp=fopen(name,"rb");
	}
	
	fread(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	if(SAVE.Graphic==true)	SetGraphMode(640,480,32);//SetGraphDataShavedMode(DX_SHAVEDMODE_DITHER);
	else			SetGraphMode(640,480,16);//SetGraphDataShavedMode(DX_SHAVEDMODE_NONE);
	
	fclose(fp);
	SetDXArchiveExtension("dat");
	ChangeFontType(DX_FONTTYPE_EDGE);
        SetFontSize(10);
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	ChangeFont("MS UI Gothic");
 	char message[32];
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	wsprintf(message , "Now Loading...");
	int size = GetDrawStringWidth(message,14);
	DrawString(640-size,480-12,message,GetColor(255,255,255));			
	ScreenFlip();
	edge = 2;
	edge_flash = 255;
	name = "th00.cfg";
	if((fp=fopen(name,"rb")) == NULL){
		fclose(fp);
		goto LABEL_A;
	}
	fread(&Config,sizeof(CONFIGDATA),1,fp);
	
	fclose(fp);
LABEL_A:
	for(int i=0;i<SOUND_NUM;i++){
		SoundFlag[i] = 0;
	}
	ConfigCount = 0;
	Game.title_carsol = 0;	
	SRe_Load();
	SMe_Load();
	SMu_Load();
	SMu_ChangeVolumeSound(255*SAVE.Sound*0.01);
	SBa_Load();
	SSc_Load();
	SPl_Load();
	SPs_Load();
	SBom_Load();
	SEn_Load();
	SEs_Load();
	SLas_Load();
	SBos_Load();
	SSp_Load();
	SIt_Load();
	SEf_Load();
	SEnd_Load();
	Game.game_count = 0;
	Game.demo_flag = 0;
	Game.scene = TITLE;
	/*
		Game.scene = ENDING;
		Game.con_times = 0;
		Game.score = 30000000;
		Game.stage = 6;
	*/
	SkipCount = 0;
	fps = 0;
	frame = 60;
	return;
}

void SReset(){
	try{
		for(int i=0;i<256;i++){
			if(i<0||i>=C_KEY_NUM)	throw(1);
			c_key[i] = 0;
		}
		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		for(int i=0;i<14;i++){
			c_pad[i] = 0; 
		}
		Game.Shot = 0;
		Game.Bomb = 0;
		Game.Slow = 0;
		Game.Skip = 0;
		for(int i=0;i<HANYOU_NUM;i++){
			Game.i_hanyou[i] = 0;
		}
		SBa_Reset();
		SPl_Reset();
		SPs_Reset();
		SBom_Reset();
		SEn_Reset();
		SEs_Reset();
		SLas_Reset();
		SBos_Reset();
		SIt_Reset();
		SEf_Reset();
		STa_Reset();
		FlagSlow = false;
		shake_x = 0;
		shake_y = 0;
		before_count = 0;
		Game.count = 0;
		Game.spell_mode = 0;
		Game.spell_count = 0;
		Game.getspell_count = 0;
		Game.extend_count = 0;
		Game.shake_count = 0;
		Game.demo_count = 0;
		Game.max_count = 0;
		Game.max_sign = 0;
		Game.before_max = 0;
		GameScene = 0;
		Pause = 0;
		GameOver = 0;
		Game.skip = false;
		switch(Game.stage){
			case 1:	SMu_PlayBgm(1);	music_count = 0;	SAVE.BgmFlag[1]++;	break;
			case 2:	SMu_PlayBgm(3);	music_count = 0;	SAVE.BgmFlag[3]++;	break;
			case 3:	SMu_PlayBgm(4);	music_count = 0;	SAVE.BgmFlag[4]++;	break;
			case 4:	SMu_PlayBgm(1);	music_count = 0;	SAVE.BgmFlag[1]++;	break;
			case 5:	SMu_PlayBgm(3);	music_count = 0;	SAVE.BgmFlag[3]++;	break;
			case 6:	SMu_PlayBgm(4);	music_count = 0;	SAVE.BgmFlag[4]++;	break;
			case 7:	SMu_PlayBgm(12);music_count = 0;	SAVE.BgmFlag[12]++;	break;
		}
		SSc_Reset2();
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SReset\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SShake(int type, int level){
	static int count;
	if(before_count!=Game.count-1)	count = 0;
	if(type==0){//全体
		shake_x = level * sin(Radian(50*count,TRUE));
		shake_y = level * sin(Radian(70*count,TRUE));
	}
	else if(type==1){//x軸
		shake_x = level * sin(Radian(50*count,TRUE));
	}
	else if(type==2){//y軸
		shake_y = level * sin(Radian(70*count,TRUE));
	}
	before_count = Game.count;
	count++;
	return;
}

void SBa_Load(){
	try{
		char fi[128];
		for(int i=0;i<GRA_BACK_NUM;i++){
			SetTransColor(0,0,0);
			wsprintf(fi , "data/img/back/%d.png" , i+1);
			if(i==4)	wsprintf(fi , "data/img/back/%d.jpg" , i+1);
			if( (Game.gra_back[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<4;i++){
			SetTransColor(0,0,0);
			wsprintf(fi , "data/img/catin/%d.png" , i+1);
			if(i<0||i>=GRA_CATIN_NUM)	throw(2);
			if( (gra_catin[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		SetTransColor(0,0,0);
		wsprintf(fi , "data/img/catin/string.png");
		if( (gra_borderoflife = LoadGraph(fi)) == -1)	throw(fi);
		for(int i=0;i<GRA_SPELL_BACK_NUM;i++){
			SetTransColor(0,0,0);
			wsprintf(fi , "data/img/back/spell/%d.jpg" , i+1);
			if( (gra_spell_back[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SBa_Load\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
	return;
}

void SBa_Reset(){
	return;
}

void SBa_Draw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SBa_Normal();
	int spell_flash=255;
	if(Game.spell_count>0){
		if(Game.spell_count<50)	spell_flash = 5.1 * Game.spell_count;
		SBa_Spell(spell_flash);
		if(Game.spell_count<120){
			if(Game.spell_count<30)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Game.spell_count);
			else if(Game.spell_count<90)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			else				SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(120-Game.spell_count));
			int x,y;
			GetGraphSize(gra_borderoflife,&x,&y);
			if(loop_count==0){
				for(int i=0;i<8;i++){
					DrawRotaGraphF(130+shake_x, -200+3*Game.spell_count%(int)(x*0.8)+(x*0.8)*i+shake_y, 0.8, Radian(90,TRUE), gra_borderoflife, FALSE, FALSE);
				}
				for(int i=0;i<6;i++){
					DrawRotaGraphF(-200+3*Game.spell_count%x+i*x+shake_x, 350+shake_y, 1.0, 0, gra_borderoflife, FALSE, FALSE);
				}
			}
		}
		if(!(Game.stage==6&&Boss.i_hanyou[6]==1)){
			if(Game.spell_count<20){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(loop_count==0)	DrawRotaGraphF(CENTER_X+30+50*(20-Game.spell_count)+shake_x, CENTER_Y-30-50*(20-Game.spell_count)+shake_y, 1.0, 0, gra_catin[Boss.pattern], TRUE, FALSE);
			}
			else if(Game.spell_count<80){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(loop_count==0)	DrawRotaGraphF(CENTER_X+30-(Game.spell_count-20)+shake_x, CENTER_Y-30+(Game.spell_count-20)+shake_y, 1.0, 0, gra_catin[Boss.pattern], TRUE, FALSE);
			}
			else if(Game.spell_count<100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(loop_count==0)	DrawRotaGraphF(CENTER_X-30-30*(Game.spell_count-80)+shake_x, CENTER_Y+30+50*(Game.spell_count-80)+shake_y, 1.0, 0, gra_catin[Boss.pattern], TRUE, FALSE);
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	return;
}

void SBa_Normal(){
	int c = Game.count;
	static int Ba_x;
	static int Ba_x2;
	static int Ba_y;
	static int Ba_count;
	static float z = -150;
	static int z_count;
	static float Cloud_x[100];
	static float Cloud_y[100];
	static float Cloud_speed[100];
	switch(Game.stage){
		case 1:
			if(c==0){
				z = -150;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
			}
			//1500まで徐々に明るく
			//1600～1630一気に明るく
			//1630～1690ちょっと暗めに戻す→ここから徐々に上昇
			//1660～3000まで雑魚
			//3000から中ボス（背景は左にスライドしだす）
			//3820からサビ
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			for(int i=0;i<10;i++){
				for(int a=0;a<10;a++){
					if(c<=3000)	DrawGraph3D(-144+96*i+shake_x,-256+128*a-64*(i%2)-(Game.count%128)+shake_y,z,Game.gra_back[0],FALSE);
					else		DrawGraph3D(-144+96*i-0.2*(Ba_x%960)+shake_x,-256+128*a-64*(i%2)-(Ba_count%128)+shake_y,z,Game.gra_back[0],FALSE);
				}
			}
			if(c<1500){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,200-0.13*c);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
			}
			else if(c<1600){
      	
			}
			else if(c<1630){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8*(c-1600));
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(255,255,255),TRUE);
			}
			else if(c<1660){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,240-8*(c-1630));
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(255,255,255),TRUE);
				z += 0.2;
			}
			else if(c<1690){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,4*(c-1660));
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				z += 0.2;
			}
			else if(c<3000){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				z += 0.2;
			}
			else if(c<3750){
				if(c==3000)	Ba_count = Game.count;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				Ba_x += 5;
				Ba_x2 = Ba_x%960;
			}
			else{
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				static int x_count;
				if(c==3750){
					x_count = 0;
				}
				Ba_x2 = Ba_x%960+400*sin(Radian(x_count,TRUE));
				x_count++;
				Ba_count += 2;
				
			}
			break;
		case 2:	
			//1000まで前奏
			//1350までタイトル
			//5300中ボス登場
			//5400中ボス
			if(c==0){
				z = 0;
				z_count = 0;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
			}
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,85);
			for(int i=0;i<3;i++){
				if(c<1300){
					DrawGraph3D(CENTER_X+shake_x,CENTER_Y+896*i-(4*Game.count%896)+shake_y,z,Game.gra_back[1],FALSE);
					DrawGraph3D(CENTER_X+shake_x+10,CENTER_Y+896*i-(4*Game.count%896)+shake_y+10,z,Game.gra_back[1],FALSE);
					DrawGraph3D(CENTER_X+shake_x-10,CENTER_Y+896*i-(4*Game.count%896)+shake_y-10,z,Game.gra_back[1],FALSE);
				}
				else if(c<5300){
					for(int a=0;a<2;a++){
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x+10,CENTER_Y+896*i-(4*Game.count%896)+shake_y+10,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x,CENTER_Y+896*i-(4*Game.count%896)+shake_y,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x-10,CENTER_Y+896*i-(4*Game.count%896)+shake_y-10,z,Game.gra_back[1],FALSE);
					}
					if(Game.count%2==0)	Ba_x ++;
				}
				else{
					for(int a=0;a<2;a++){
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x+10,CENTER_Y+Ba_y+896*i+shake_y+10,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x,CENTER_Y+Ba_y+896*i+shake_y,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x-10,CENTER_Y+Ba_y+896*i+shake_y-10,z,Game.gra_back[1],FALSE);
					}
					if(Game.count%2==0)	Ba_x ++;
				}
			}
			if(c<1250){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
				DrawBox(0,0,640,480,0,TRUE);
			}
			else if(c<1350){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150-(c-1250));
				DrawBox(0,0,640,480,0,TRUE);
			}
			else if(c<5300){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);
				DrawBox(0,0,640,480,0,TRUE);
				z = 100*sin(Radian(z_count,TRUE));
				if(Game.count%2==0)	z_count++;
				if(c==5299)	Ba_y = -(4*Game.count%896);
			}
			else if(c<5400){
				Ba_y = (Ba_y-4-(c-5300)/25)%896;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,50-(c-5300)/4);
				DrawBox(0,0,640,480,0,TRUE);
				z = 100*sin(Radian(z_count,TRUE));
				z_count++;
			}
			else{
				Ba_y = (Ba_y-8)%896;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,25);
				DrawBox(0,0,640,480,0,TRUE);
				z = 100*sin(Radian(z_count,TRUE));
				z_count++;
			}
			break;
		case 3:	
			if(c==0){
				z = 0;
				z_count = 0;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
			}
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(Game.i_hanyou[0]==0){
				for(int i=0;i<5;i++){
					int y = -224+224*i-(Game.count/2%224)+shake_y;
					DrawGraph3D(CENTER_X+shake_x,y,z,Game.gra_back[2],FALSE);
					DrawGraph3D(CENTER_X+shake_x-320,y,z,Game.gra_back[2],FALSE);
					DrawGraph3D(CENTER_X+shake_x+320,y,z,Game.gra_back[2],FALSE);
				}
			}
			else if(Game.i_hanyou[0]==1){
				SetDrawBright(100,100,100);
				DrawGraph3D(CENTER_X+shake_x,CENTER_Y+shake_y,z,Game.gra_back[3],FALSE);
				SetDrawBright(255,255,255);
			}
			if(Game.i_hanyou[1]>0){
				int flash = 0;
				if(Game.i_hanyou[1]<60){
					flash = 4.25 * Game.i_hanyou[1];
				}
				else if(Game.i_hanyou[1]<120){
					flash = 255;
					Game.i_hanyou[0] = 1;
				}
				else if(Game.i_hanyou[1]<240){
					flash = 2.125 * (240-Game.i_hanyou[1]);
				}
				if(Game.i_hanyou[1]>=60){
					z = 50*sin(Radian(z_count,TRUE));
					z_count++;
		 		}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
				Game.i_hanyou[1] ++;
			}
			break;
		case 4:
			if(c==0){
				z = -150;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
			}
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			for(int i=0;i<10;i++){
				for(int a=0;a<10;a++){
					if(c<=3000)	DrawGraph3D(-144+96*i+shake_x,-256+128*a-64*(i%2)-(Game.count%128)+shake_y,z,Game.gra_back[0],FALSE);
					else		DrawGraph3D(-144+96*i-0.2*(Ba_x%960)+shake_x,-256+128*a-64*(i%2)-(Ba_count%128)+shake_y,z,Game.gra_back[0],FALSE);
				}
			}
			if(c<1500){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,200-0.13*c);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
			}
			else if(c<1600){
      	
			}
			else if(c<1630){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8*(c-1600));
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(255,255,255),TRUE);
			}
			else if(c<1660){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,240-8*(c-1630));
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(255,255,255),TRUE);
				z += 0.2;
			}
			else if(c<1690){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,4*(c-1660));
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				z += 0.2;
			}
			else if(c<3000){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				z += 0.2;
			}
			else if(c<3750){
				if(c==3000)	Ba_count = Game.count;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				Ba_x += 5;
				Ba_x2 = Ba_x%960;
			}
			else{
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				DrawBox(0+shake_x,0+shake_y,450,480,GetColor(0,0,0),TRUE);
				static int x_count;
				if(c==3750){
					x_count = 0;
				}
				Ba_x2 = Ba_x%960+400*sin(Radian(x_count,TRUE));
				x_count++;
				Ba_count += 2;
				
			}
			break;
		case 5:	
			if(c==0){
				z = 0;
				z_count = 0;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
			}
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,85);
			for(int i=0;i<3;i++){
				if(c<1300){
					DrawGraph3D(CENTER_X+shake_x,CENTER_Y+896*i-(4*Game.count%896)+shake_y,z,Game.gra_back[1],FALSE);
					DrawGraph3D(CENTER_X+shake_x+10,CENTER_Y+896*i-(4*Game.count%896)+shake_y+10,z,Game.gra_back[1],FALSE);
					DrawGraph3D(CENTER_X+shake_x-10,CENTER_Y+896*i-(4*Game.count%896)+shake_y-10,z,Game.gra_back[1],FALSE);
				}
				else if(c<5300){
					for(int a=0;a<2;a++){
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x+10,CENTER_Y+896*i-(4*Game.count%896)+shake_y+10,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x,CENTER_Y+896*i-(4*Game.count%896)+shake_y,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x-10,CENTER_Y+896*i-(4*Game.count%896)+shake_y-10,z,Game.gra_back[1],FALSE);
					}
					if(Game.count%2==0)	Ba_x ++;
				}
				else{
					for(int a=0;a<2;a++){
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x+10,CENTER_Y+Ba_y+896*i+shake_y+10,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x,CENTER_Y+Ba_y+896*i+shake_y,z,Game.gra_back[1],FALSE);
						DrawGraph3D(576*a+CENTER_X-(1*Ba_x%576)+shake_x-10,CENTER_Y+Ba_y+896*i+shake_y-10,z,Game.gra_back[1],FALSE);
					}
					if(Game.count%2==0)	Ba_x ++;
				}
			}
			if(c<1250){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
				DrawBox(0,0,640,480,0,TRUE);
			}
			else if(c<1350){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150-(c-1250));
				DrawBox(0,0,640,480,0,TRUE);
			}
			else if(c<5300){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);
				DrawBox(0,0,640,480,0,TRUE);
				z = 100*sin(Radian(z_count,TRUE));
				if(Game.count%2==0)	z_count++;
				if(c==5299)	Ba_y = -(4*Game.count%896);
			}
			else if(c<5400){
				Ba_y = (Ba_y-4-(c-5300)/25)%896;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,50-(c-5300)/4);
				DrawBox(0,0,640,480,0,TRUE);
				z = 100*sin(Radian(z_count,TRUE));
				z_count++;
			}
			else{
				Ba_y = (Ba_y-8)%896;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,25);
				DrawBox(0,0,640,480,0,TRUE);
				z = 100*sin(Radian(z_count,TRUE));
				z_count++;
			}
			break;
		case 6:	
			if(c==0){
				z = 0;
				z_count = 0;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
			}
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(Game.i_hanyou[0]==0){
				for(int i=0;i<5;i++){
					int y = -224+224*i-(Game.count/2%224)+shake_y;
					DrawGraph3D(CENTER_X+shake_x,y,z,Game.gra_back[2],FALSE);
					DrawGraph3D(CENTER_X+shake_x-320,y,z,Game.gra_back[2],FALSE);
					DrawGraph3D(CENTER_X+shake_x+320,y,z,Game.gra_back[2],FALSE);
				}
			}
			else if(Game.i_hanyou[0]==1){
				SetDrawBright(100,100,100);
				DrawGraph3D(CENTER_X+shake_x,CENTER_Y+shake_y,z,Game.gra_back[3],FALSE);
				SetDrawBright(255,255,255);
			}
			if(Game.i_hanyou[1]>0){
				int flash = 0;
				if(Game.i_hanyou[1]<60){
					flash = 4.25 * Game.i_hanyou[1];
				}
				else if(Game.i_hanyou[1]<120){
					flash = 255;
					Game.i_hanyou[0] = 1;
				}
				else if(Game.i_hanyou[1]<240){
					flash = 2.125 * (240-Game.i_hanyou[1]);
				}
				if(Game.i_hanyou[1]>=60){
					z = 50*sin(Radian(z_count,TRUE));
					z_count++;
		 		}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
				Game.i_hanyou[1] ++;
			}
			break;
		case 7:	
			if(c==0){
				z = -50;
				z_count = 0;
				Ba_x = 0;
				Ba_x2 = 0;
				Ba_y = 0;
				Ba_count = 0;
				for(int i=0;i<100;i++){
					Cloud_x[i] = get_rand(CENTER_X*2);
					Cloud_y[i] = get_rand(CENTER_Y*2);
					Cloud_speed[i] = 1.0+0.01*get_rand(600);
				}
			}
			for(int i=0;i<100;i++){
				Cloud_y[i] += Cloud_speed[i];
				if(Cloud_y[i]>480+128){
					Cloud_x[i] = get_rand(CENTER_X*2);
					Cloud_y[i] = -128;
					Cloud_speed[i] = 1.0+0.01*get_rand(600);
				}
			}
			if(c<7500)	z += 0.01;
			int flashA,red,green,blue;
			if(c<850){
				flashA = 80;
				red = 50;
				green = 50;
				blue = 50;
			}
			else if(c<970){
				flashA = 80;
				red = 50+(c-850);
				green = 50+(c-850);
				blue = 50+(c-850);
			}
			else if(c<1580){
				flashA = 80;
				red = 170;
				green = 170;
				blue = 170;
			}
			else if(c<1750){
				flashA = 80+(c-1580);
				red = 170;
				green = 170;
				blue = 170;
			}
			else{
				flashA = 250;
				red = 170;
				green = 170;
				blue = 170;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,flashA);
			DrawGraph3D(CENTER_X+shake_x,CENTER_Y+shake_y,z,Game.gra_back[4],FALSE);
			SetDrawBright(red,green,blue);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
			for(int i=0;i<100;i++){
				DrawRotaGraphF(Cloud_x[i]+shake_x,Cloud_y[i]+shake_y,1.0,0,Game.gra_back[5],TRUE,FALSE);	
			}
			SetDrawBright(255,255,255);
			
			break;
	}
	return;
}

void SBa_Spell(int flash){
	if(Boss.pattern==0){
		SetDrawBright(160,160,160);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
		DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y+shake_y, 1.0, 0, gra_spell_back[0], TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash-150);
		DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y+shake_y, 1.0+abs(1.0*sin(Radian(1.0*Game.count,TRUE))), Radian(10*sin(Radian(0.5*Game.count,TRUE)),TRUE), gra_spell_back[0], TRUE, FALSE);
	}
	if(Boss.pattern==1){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
		SetDrawBright(255,100,255-abs(3*Boss.count%125-250));
		for(int i=0;i<2;i++){
			DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y-959*i+5*Game.count%959+shake_y, 1.0, 0, gra_spell_back[1], TRUE, FALSE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash-150);
		SetDrawBright(255,100,255-abs(2*Boss.count%300-150));
		for(int i=0;i<2;i++){
			DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y-959*i+2*Game.count%959+shake_y, 1.0, 0, gra_spell_back[1], TRUE, FALSE);
		}
	}
	if(Boss.pattern==2 || Boss.pattern==3){
		SetDrawBright(180,180,180);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
		DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y+shake_y, 1.5, Radian(1.0*Game.count,TRUE), gra_spell_back[2], TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash-70);
		DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y+shake_y, 1.5, Radian(-1.0*Game.count,TRUE), gra_spell_back[2], TRUE, FALSE);
	}
	SetDrawBright(255,255,255);
	return;
}

void SRe_Load(){
	for(int i=0;i<DIRECTOR_REPLAY_NUM;i++){
		char name[64];
		wsprintf(name ,"data/replay/th00_%02d.rpy",i+1);
		FILE *fp;
		if((fp=fopen(name,"rb")) == NULL){
			char message[128];
			wsprintf(message , "ERROR1:SRe_Load\nディレクターリプレイが存在しない");
			MessageBox( NULL,
				message,
				"Error",
				MB_OK | 
				MB_ICONSTOP |
				MB_TOPMOST);
			fclose(fp);
			break;
		}
		
		fread(&Director_Replay[i],sizeof(REPLAYDATA)-REPLAY_ELEMENT_NUM-REPLAY_FPS_NUM,1,fp);
		crypt(&Director_Replay[i],sizeof(REPLAYDATA),0xF7);
		int Element = Director_Replay[i].element_num;
		crypt(&Director_Replay[i],sizeof(REPLAYDATA),0xF7);
		for(int a=0;a<Element;a++){
			Director_Replay[i].replay[a] = fgetc(fp);
		}
		for(int a=0;a<Element/60;a++){
			Director_Replay[i].fps[a] = fgetc(fp);
		}
		crypt(&Director_Replay[i],sizeof(REPLAYDATA),0xF7);
		fclose(fp);
	}
	char path[128];
	wsprintf(path , "replay");
	if(PathIsDirectory(path)==false){
		for(int i=0;i<REPLAY_NUM;i++){
			Replay[i].score = 0;
			Replay[i].stage = '1';
			wsprintf(Replay[i].name ,"--------");
			Replay[i].month = 0;
			Replay[i].date = 0;
		}
		return;
	}
	for(int i=0;i<REPLAY_NUM;i++){
		char name[64];
		wsprintf(name ,"replay/th00_%02d.rpy",i+1);
		FILE *fp;
		if((fp=fopen(name,"rb")) == NULL){
			Replay[i].score = 0;
			Replay[i].stage = '1';
			wsprintf(Replay[i].name ,"--------");
			Replay[i].month = 0;
			Replay[i].date = 0;
			fclose(fp);
			continue;
		}
		
		fread(&Replay[i],sizeof(REPLAYDATA)-REPLAY_ELEMENT_NUM-REPLAY_FPS_NUM,1,fp);
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		int Element = Replay[i].element_num;
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		for(int a=0;a<Element;a++){
			Replay[i].replay[a] = fgetc(fp);
		}
		for(int a=0;a<Element/60;a++){
			Replay[i].fps[a] = fgetc(fp);
		}
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		
		fclose(fp);
	}
	return;	
}

void SRe_Main(){
	//ボタン押下状況の保存
	int REPLAY = 0;
	if(Game.Shot>0)	REPLAY += 1;
	if(Game.Bomb>0)	REPLAY += 2;
	if(Game.Slow>0)	REPLAY += 4;
	if(Game.Skip>0)	REPLAY += 8;
	if(c_key[KEY_INPUT_UP]>0||c_pad[PAD_UP]>0)	REPLAY += 16;
	if(c_key[KEY_INPUT_DOWN]>0||c_pad[PAD_DOWN]>0)	REPLAY += 32;
	if(c_key[KEY_INPUT_LEFT]>0||c_pad[PAD_LEFT]>0)	REPLAY += 64;
	if(c_key[KEY_INPUT_RIGHT]>0||c_pad[PAD_RIGHT]>0)	REPLAY += 128;
	SReplay.replay[ReplayCount] = REPLAY;
	if(ReplayCount%60==0){
		SReplay.fps[ReplayCount/60] = fps;
	}
	ReplayCount++;
	SReplay.element_num++;
	
	return;
}

void SSc_Load(){
	try{
		char fi[128];
		SetTransColor(0,0,0);
		wsprintf(fi , "data/img/back/flame.png");
		if( (Game.gra_flame = LoadGraph(fi)) == -1)	throw(fi);
		SetTransColor(0,0,0);
		for(int i=0;i<12;i++){
			wsprintf(fi , "data/img/font/number/%d.png" , i);
			if(i<0||i>=GRA_NUMBER_NUM)	throw(1);
			if( (Game.gra_number[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<GRA_SIDE_NUM;i++){
			wsprintf(fi , "data/img/font/side/%d.png" , i+1);
			if( (Game.gra_side[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<7;i++){
			wsprintf(fi , "data/img/back/stage/%d.png" , i+1);
			if(i<0||i>=GRA_TITLE_NUM)	throw(3);
			if( (gra_stage_title[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		wsprintf(fi , "data/img/back/stage/label.jpg");
		if( (gra_stage_title[7] = LoadGraph(fi)) == -1)	throw(fi);
		for(int i=0;i<GRA_MUSIC_TITLE_NUM;i++){
			wsprintf(fi , "data/img/back/stage/m%d.png" , i+1);
			if( (gra_music_title[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<4;i++){
			wsprintf(fi , "data/img/back/stage/e%d.png" , i+1);
			if(i<0||i>=GRA_BOSS_NAME_NUM)	throw(6);
			if( (gra_boss_name[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		wsprintf(fi , "data/img/dot/boss/5.png");
		if( (gra_enemymark = LoadGraph(fi)) == -1)	throw(fi);
		wsprintf(fi , "data/img/dot/effect.png");
		SetTransColor(0,0,0);
		if( (gra_bullet_effect = LoadGraph(fi)) == -1)	throw(fi);
		wsprintf(fi , "data/img/dot/graze.png");
		if( (gra_graze_effect = LoadGraph(fi)) == -1)	throw(fi);
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SSc_Load\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
	return;
}

void SSc_Reset(){
	//ゲーム開始時のリセット
	//リプレイ関係処理もここでしている
	try{
		ResultCount = 0;
		if(SAVE.Chara==0&&SAVE.Weapon==0)	Game.hiscore = SAVE.ReimuA.level[SAVE.Level].score[0].score;
		if(SAVE.Chara==0&&SAVE.Weapon==1)	Game.hiscore = SAVE.ReimuB.level[SAVE.Level].score[0].score;
		if(SAVE.Chara==1&&SAVE.Weapon==0)	Game.hiscore = SAVE.MarisaA.level[SAVE.Level].score[0].score;
		if(SAVE.Chara==1&&SAVE.Weapon==1)	Game.hiscore = SAVE.MarisaB.level[SAVE.Level].score[0].score;
		Game.score = 0;
		Game.score2 = 0;
		//プレイヤー残機・パワーはSelect関数にて決定（本編とプラクティスで初期値が違うから）
		Game.graze = 0;
		Game.point = 0;
		if(SAVE.Level<4)	Game.nextpoint = 50;
		else			Game.nextpoint = 100;
		switch(SAVE.Level){
			case 0:	Game.maxpoint = 10000;	break;
			case 1:	Game.maxpoint = 50000;	break;
			case 2:	Game.maxpoint = 100000;	break;
			case 3:	Game.maxpoint = 200000;	break;
			case 4:	Game.maxpoint = 500000;	break;
		}
		for(int i=0;i<SCORE_NAME_NUM;i++){
			SReplay.name[i] = ' ';
		}
		for(int i=0;i<SCORE_STAGE_NUM;i++){
			SReplay.exist[i] = 0;
			SReplay.start_score[i] = 0;
			SReplay.end_score[i] = 0;
			SReplay.start_player[i] = 0;
			SReplay.start_power[i] = 0;
			SReplay.start_graze[i] = 0;
			SReplay.start_max[i] = 0;
			SReplay.start_point[i] = 0;
			SReplay.start_random[i] = 0;
			Game.stage_score[i] = 0;
			Game.stage_graze[i] = 0;
			Game.stage_point[i] = 0;
			Game.stage_count[i] = 0;
			s_time[i] = 0;
		}
		for(int i=0;i<REPLAY_ELEMENT_NUM;i++){
			SReplay.replay[i] = '\n';
		}
		for(int i=0;i<REPLAY_FPS_NUM;i++){
			SReplay.fps[i] = '\n';
		}
		SReplay.score = 0;
		SReplay.stage = 0;
		SReplay.year = 0;
		SReplay.month = 0;
		SReplay.date = 0;
		SReplay.hour = 0;
		SReplay.minute = 0;
		SReplay.second = 0;
		SReplay.level = SAVE.Level;
		SReplay.chara = SAVE.Chara;
		SReplay.weapon = SAVE.Weapon;
		SReplay.element_num = 0;
		ReplayCount = 0;
		ScoreCount = 0;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SSc_Reset\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
	return;
}

void SSc_Reset2(){
	//ステージごとのリセット
	SReplay.exist[Game.stage-1] = 1;
	SReplay.start_score[Game.stage-1] = Game.score;
	SReplay.start_count[Game.stage-1] = ReplayCount;
	SReplay.start_player[Game.stage-1] = Player.life;
	SReplay.start_power[Game.stage-1] = Game.power;
	SReplay.start_graze[Game.stage-1] = Game.graze;
	SReplay.start_max[Game.stage-1] = Game.maxpoint;
	SReplay.start_point[Game.stage-1] = Game.point;
	SReplay.start_random[Game.stage-1] = start_rand;
	if(PlayerControlFlag==1){
		ReplayCount = Replay[repnum].start_count[Game.stage-1];		
		Game.score = Replay[repnum].start_score[Game.stage-1];
		Game.score2 = Replay[repnum].start_score[Game.stage-1];
		Player.life = Replay[repnum].start_player[Game.stage-1];
		Game.power = Replay[repnum].start_power[Game.stage-1];
		Game.graze = Replay[repnum].start_graze[Game.stage-1];
		Game.maxpoint = Replay[repnum].start_max[Game.stage-1];
		Game.point = Replay[repnum].start_point[Game.stage-1];
		start_rand = Replay[repnum].start_random[Game.stage-1];
		int time = 0;
		for(int i=0;i<SCORE_STAGE_NUM-1&&i<Game.stage-1;i++){
			s_time[i] = Replay[repnum].start_count[i+1]-1;
			s_time[i] -= time;
			time = Replay[repnum].start_count[i+1]-1;
		}
	}
	if(PlayerControlFlag==2){
		ReplayCount = Director_Replay[repnum].start_count[Game.stage-1];		
		Game.score = Director_Replay[repnum].start_score[Game.stage-1];
		Game.score2 = Director_Replay[repnum].start_score[Game.stage-1];
		Player.life = Director_Replay[repnum].start_player[Game.stage-1];
		Game.power = Director_Replay[repnum].start_power[Game.stage-1];
		Game.graze = Director_Replay[repnum].start_graze[Game.stage-1];
		Game.maxpoint = Director_Replay[repnum].start_max[Game.stage-1];
		Game.point = Director_Replay[repnum].start_point[Game.stage-1];
		start_rand = Director_Replay[repnum].start_random[Game.stage-1];
		int time = 0;
		for(int i=0;i<SCORE_STAGE_NUM-1&&i<Game.stage-1;i++){
			s_time[i] = Director_Replay[repnum].start_count[i+1]-1;
			s_time[i] -= time;
			time = Director_Replay[repnum].start_count[i+1]-1;
		}
	}
	s_time[Game.stage-1] = 0;
	return;
}

void SSc_Draw(){
	int fadein = 0;
	if(Game.before_max!=Game.maxpoint&&Game.count>1){
		for(int i=1;i<200;i++){
			int point = 50000*i;
			if(Game.before_max<point&&Game.maxpoint>=point){
				Game.max_count = 1;
				Game.max_sign = point;
				SPlaySound(4);
			}
		}
	}
	Game.before_max = Game.maxpoint;
	if(SAVE.Level<4){
		for(int i=0;i<1;){
			if(Game.point>=Game.nextpoint){
				switch(Game.nextpoint){
					case 50:	Game.nextpoint = 100;	break;
					case 100:	Game.nextpoint = 200;	break;
					case 200:	Game.nextpoint = 350;	break;
					case 350:	Game.nextpoint = 500;	break;
					case 500:	Game.nextpoint = 700;	break;
					case 700:	Game.nextpoint = 900;	break;
					case 900:	Game.nextpoint = 1100;	break;
					case 1100:	Game.nextpoint = 1200;	break;
					case 1200:	Game.nextpoint = 1300;	break;
					case 1300:	Game.nextpoint = 1400;	break;
					case 1400:	Game.nextpoint = 1500;	break;
					case 1500:	Game.nextpoint = 9999;	break;
					case 9999:	Game.nextpoint = 9999;	break;
				}
			}
			else{
				i = 1;
			}
		}
	}
	else{
		for(int i=0;i<1;){
			if(Game.point>=Game.nextpoint){
				switch(Game.nextpoint){
					case 100:	Game.nextpoint = 200;	break;
					case 200:	Game.nextpoint = 400;	break;
					case 400:	Game.nextpoint = 600;	break;
					case 600:	Game.nextpoint = 800;	break;
					case 800:	Game.nextpoint = 1000;	break;
					case 1000:	Game.nextpoint = 9999;	break;
					case 9999:	Game.nextpoint = 9999;	break;
				}
			}
			else{
				i = 1;
			}
		}
	}
	if(Game.getspell_count>0){
		int color,size;
		char message[64];
		if(Game.getspell_point>0){
			if(Game.getspell_count<20){
 				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Game.getspell_count);
				wsprintf(message , "Got SpellCard Bonus!!");
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(255,0,0);
				DrawStringToHandle(CENTER_X-size/2,100-2*Game.getspell_count,message,GetColor(255,255,255),GetSpellBonusFont,color);			
				wsprintf(message , "%d",Game.getspell_point);
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(0,0,255);
				DrawStringToHandle(CENTER_X-size/2,120-2*Game.getspell_count,message,GetColor(255,255,255),GetSpellBonusFont,color);			
			}
			else if(Game.getspell_count<180){
 				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				wsprintf(message , "Got SpellCard Bonus!!");
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(255,0,0);
				DrawStringToHandle(CENTER_X-size/2,60,message,GetColor(255,255,255),GetSpellBonusFont,color);			
				wsprintf(message , "%d",Game.getspell_point);
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(0,0,255);
				DrawStringToHandle(CENTER_X-size/2,80,message,GetColor(255,255,255),GetSpellBonusFont,color);			
			}
			else if(Game.getspell_count<200){
 				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(200-Game.getspell_count));
				wsprintf(message , "Got SpellCard Bonus!!");
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(255,0,0);
				DrawStringToHandle(CENTER_X-size/2,60,message,GetColor(255,255,255),GetSpellBonusFont,color);			
				wsprintf(message , "%d",Game.getspell_point);
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(0,0,255);
				DrawStringToHandle(CENTER_X-size/2,80,message,GetColor(255,255,255),GetSpellBonusFont,color);			
			}
		}
		else{
			if(Game.getspell_count<20){
 				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Game.getspell_count);
				wsprintf(message , "Bonus Failed...");
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(0,0,0);
				DrawStringToHandle(CENTER_X-size/2,100-2*Game.getspell_count,message,GetColor(255,255,255),GetSpellBonusFont,color);			
			}
			else if(Game.getspell_count<180){
 				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				wsprintf(message , "Bonus Failed...");
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(0,0,0);
				DrawStringToHandle(CENTER_X-size/2,60,message,GetColor(255,255,255),GetSpellBonusFont,color);			
			}
			else if(Game.getspell_count<200){
 				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(200-Game.getspell_count));
				wsprintf(message , "Bonus Failed...");
				size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
				color = GetColor(0,0,0);
				DrawStringToHandle(CENTER_X-size/2,60,message,GetColor(255,255,255),GetSpellBonusFont,color);			
			}
		} 
		Game.getspell_count++;
		if(Game.getspell_count>=200){
			Game.getspell_count = 0;
		}
	}
	if(Game.extend_count>0){
		int color,size;
		char message[64];
		if(Game.extend_count<20){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Game.extend_count);
			wsprintf(message , "Extend!");
			size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
			color = GetColor(255,255,0);
			DrawStringToHandle(CENTER_X-size/2,100-2*Game.extend_count,message,GetColor(255,255,255),GetSpellBonusFont,color);			
		}
		else if(Game.extend_count<180){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			wsprintf(message , "Extend!");
			size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
			color = GetColor(255,255,0);
			DrawStringToHandle(CENTER_X-size/2,60,message,GetColor(255,255,255),GetSpellBonusFont,color);			
		}
		else if(Game.extend_count<200){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(200-Game.extend_count));
			wsprintf(message , "Extend!");
			size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
			color = GetColor(255,255,0);
			DrawStringToHandle(CENTER_X-size/2,60,message,GetColor(255,255,255),GetSpellBonusFont,color);			
		}
		Game.extend_count++;
		if(Game.extend_count>=200){
			Game.extend_count = 0;
		}
	}
	if(Game.max_count>0){
		int color,size;
		char message[64];
		if(Game.max_count<20){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Game.max_count);
			wsprintf(message , "Max %d !!",Game.max_sign);
			size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
			color = GetColor(0,255,0);
			DrawStringToHandle(CENTER_X-size/2-5*(20-Game.max_count),100,message,GetColor(255,255,255),GetSpellBonusFont,color);			
		}
		else if(Game.max_count<180){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			wsprintf(message , "Max %d !!",Game.max_sign);
			size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
			color = GetColor(0,255,0);
			DrawStringToHandle(CENTER_X-size/2,100,message,GetColor(255,255,255),GetSpellBonusFont,color);			
		}
		else if(Game.max_count<200){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(200-Game.max_count));
			wsprintf(message , "Max %d !!",Game.max_sign);
			size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
			color = GetColor(0,255,0);
			DrawStringToHandle(CENTER_X-size/2,100,message,GetColor(255,255,255),GetSpellBonusFont,color);			
		}
		Game.max_count++;
		if(Game.max_count>=200){
			Game.max_count = 0;
		}
	}
	if(Pause==0){
		int c = Game.count;
		if(Boss.gage_exist==1){
 			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int red=0,white=0;
			if(Game.spell_mode==0){
				int max = Boss.max_life+Boss.spell_life;
				if(Boss.life2<max)				Boss.life2 += max/60;
				if(Boss.life2>Boss.life+Boss.spell_life)	Boss.life2 = Boss.life+Boss.spell_life;
				if(Boss.life2<Boss.spell_life)	red = 300*((float)Boss.life2/(float)max);
				else				red = 300*((float)Boss.spell_life/(float)max);
				white = 300*((float)Boss.life2/(float)max);
			}
			else if(Game.spell_mode==1){
				int max = Boss.max_life+Boss.spell_life;
				if(Boss.life2<max)			Boss.life2 += max/60;
				if(Boss.life2>Boss.life)	Boss.life2 = Boss.life;
				red = 300*((float)Boss.life2/(float)max);
				white = 0;
			}
			if(loop_count==0){
				DrawLine(30,24,30+white,24,GetColor(255,255,255),TRUE);
				DrawLine(30,25,30+white,25,GetColor(255,255,255),TRUE);
				DrawLine(30,24,30+red,24,GetColor(255,150,150),TRUE);
				DrawLine(30,25,30+red,25,GetColor(255,150,150),TRUE);
				DrawLine(30,26,30+white,26,GetColor(0,0,0));
			}
			int time = Boss.countdown/60;
			int t2 = Boss.countdown%60;
			if(time<=10){
				SetDrawBright(255,50,50);
			}
			if(time<=11&&t2==0)	SPlaySound(16);
			if(time>99)		DrawNumber2(375,20,2,99);
			else if(time>=10)	DrawNumber2(375,20,2,time);
			else{
				DrawNumber2(375+12,20,2,time);
			}
			SetDrawBright(255,255,255);
			if(Boss.pattern<4)	DrawGraph(30,30,gra_boss_name[Boss.pattern],TRUE);
			SetDrawBright(100,255,100);
			for(int i=0;i<Boss.zanki;i++){
				DrawGraph(30+12*i,45,Game.gra_side[6],TRUE);
			}
			SetDrawBright(255,255,255);
			if(Game.skip==false)	Boss.countdown--;
			if(Boss.countdown==0){
				Game.spell_getflag = 2;
			}
		}
		if(loop_count==0){	
			switch(Game.stage){
				case 1: //900～1500　ステージタイトル表示
					if(c<900){}
					else if(c<950){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-900));
						DrawGraphF(120,0+1*(c-900),gra_stage_title[7],FALSE);	
					}
					else if(c<1350){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.2*(c-950),gra_stage_title[7],FALSE);				
					}
					else if(c<1400){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1350));
						DrawGraphF(120,50+80+1*(c-1350),gra_stage_title[7],FALSE);	
					}
					if(c<930){}
					else if(c<980){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-930));
						DrawGraphF(210-1*(c-930),120,gra_stage_title[0],TRUE);	
					}
					else if(c<1380){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(160-0.2*(c-980),120,gra_stage_title[0],TRUE);				
					}
					else if(c<1430){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1380));
						DrawGraphF(80-1*(c-1380),120,gra_stage_title[0],TRUE);	
					}
					break;
				case 2: //900～1350　ステージタイトル表示
					if(c<900){}
					else if(c<950){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-900));
						DrawGraphF(120,0+1*(c-900),gra_stage_title[7],FALSE);	
					}
					else if(c<1250){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.25*(c-950),gra_stage_title[7],FALSE);				
					}
					else if(c<1300){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1250));
						DrawGraphF(120,50+75+1*(c-1250),gra_stage_title[7],FALSE);	
					}
					if(c<930){}
					else if(c<980){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-930));
						DrawGraphF(200-1*(c-930),120,gra_stage_title[1],TRUE);	
					}
					else if(c<1280){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(150-0.25*(c-980),120,gra_stage_title[1],TRUE);				
					}
					else if(c<1330){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1280));
						DrawGraphF(75-1*(c-1280),120,gra_stage_title[1],TRUE);	
					}
					break;
				case 3: // 400～700　ステージタイトル表示
					if(c<400){}
					else if(c<450){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-400));
						DrawGraphF(120,0+1*(c-400),gra_stage_title[7],FALSE);	
					}
					else if(c<650){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.375*(c-450),gra_stage_title[7],FALSE);				
					}
					else if(c<700){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-650));
						DrawGraphF(120,50+75+1*(c-650),gra_stage_title[7],FALSE);	
					}
					if(c<430){}
					else if(c<480){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-430));
						DrawGraphF(200-1*(c-430),120,gra_stage_title[2],TRUE);	
					}
					else if(c<680){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(150-0.375*(c-480),120,gra_stage_title[2],TRUE);				
					}
					else if(c<730){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-680));
						DrawGraphF(75-1*(c-680),120,gra_stage_title[2],TRUE);	
					}
					break;
				case 4: //900～1500　ステージタイトル表示
					if(c<900){}
					else if(c<950){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-900));
						DrawGraphF(120,0+1*(c-900),gra_stage_title[7],FALSE);	
					}
					else if(c<1350){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.2*(c-950),gra_stage_title[7],FALSE);				
					}
					else if(c<1400){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1350));
						DrawGraphF(120,50+80+1*(c-1350),gra_stage_title[7],FALSE);	
					}
					if(c<930){}
					else if(c<980){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-930));
						DrawGraphF(180-1*(c-930),120,gra_stage_title[3],TRUE);	
					}
					else if(c<1380){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(130-0.2*(c-980),120,gra_stage_title[3],TRUE);				
					}
					else if(c<1430){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1380));
						DrawGraphF(50-1*(c-1380),120,gra_stage_title[3],TRUE);	
					}
					break;
				case 5: //900～1350　ステージタイトル表示
					if(c<900){}
					else if(c<950){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-900));
						DrawGraphF(120,0+1*(c-900),gra_stage_title[7],FALSE);	
					}
					else if(c<1250){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.25*(c-950),gra_stage_title[7],FALSE);				
					}
					else if(c<1300){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1250));
						DrawGraphF(120,50+75+1*(c-1250),gra_stage_title[7],FALSE);	
					}
					if(c<930){}
					else if(c<980){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-930));
						DrawGraphF(200-1*(c-930),120,gra_stage_title[4],TRUE);	
					}
					else if(c<1280){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(150-0.25*(c-980),120,gra_stage_title[4],TRUE);				
					}
					else if(c<1330){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1280));
						DrawGraphF(75-1*(c-1280),120,gra_stage_title[4],TRUE);	
					}
					break;
				case 6: // 400～700　ステージタイトル表示
					if(c<400){}
					else if(c<450){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-400));
						DrawGraphF(120,0+1*(c-400),gra_stage_title[7],FALSE);	
					}
					else if(c<650){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.375*(c-450),gra_stage_title[7],FALSE);				
					}
					else if(c<700){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-650));
						DrawGraphF(120,50+75+1*(c-650),gra_stage_title[7],FALSE);	
					}
					if(c<430){}
					else if(c<480){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-430));
						DrawGraphF(200-1*(c-430),120,gra_stage_title[5],TRUE);	
					}
					else if(c<680){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(150-0.375*(c-480),120,gra_stage_title[5],TRUE);				
					}
					else if(c<730){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-680));
						DrawGraphF(75-1*(c-680),120,gra_stage_title[5],TRUE);	
					}
					break;
				case 7: // 850～1450　ステージタイトル表示
					c+=50;
					if(c<900){}
					else if(c<950){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-900));
						DrawGraphF(120,0+1*(c-900),gra_stage_title[7],FALSE);	
					}
					else if(c<1350){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(120,50+0.2*(c-950),gra_stage_title[7],FALSE);				
					}
					else if(c<1400){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1350));
						DrawGraphF(120,50+80+1*(c-1350),gra_stage_title[7],FALSE);	
					}
					if(c<930){}
					else if(c<980){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*(c-930));
						DrawGraphF(210-1*(c-930),120,gra_stage_title[6],TRUE);	
					}
					else if(c<1380){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						DrawGraphF(160-0.2*(c-980),120,gra_stage_title[6],TRUE);				
					}
					else if(c<1430){
 						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(c-1380));
						DrawGraphF(80-1*(c-1380),120,gra_stage_title[6],TRUE);	
					}
					c-=50;
					break;
			}
			bool flag = false;
			if(now_playing>=12){
				flag = true;
				now_playing -= 2;
			}
			if(music_count<60){
				int x,y;
				GetGraphSize(gra_music_title[now_playing-1],&x,&y);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawGraphF(405-x+2*(60-music_count),440,gra_music_title[now_playing-1],TRUE);	
			}
			else if(music_count<120){
				int x,y;
				GetGraphSize(gra_music_title[now_playing-1],&x,&y);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawGraphF(405-x,440,gra_music_title[now_playing-1],TRUE);	
			}
			else if(music_count<170){
				int x,y;
				GetGraphSize(gra_music_title[now_playing-1],&x,&y);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-5.1*(music_count-120));
				DrawGraphF(405-x,440,gra_music_title[now_playing-1],TRUE);	
			}
			if(flag==true)	now_playing += 2;
		}
	}
	if(Game.demo_flag==1){}
	else if(ResultCount==0)	SPl_Pause();
	else{
		if(ResultCount<60){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*ResultCount);
			SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01*(60-ResultCount)/60);
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(ResultCount<340)	SMu_ChangeVolumeBgm(0);
		}
		DrawBox(0,0,640,480,0,TRUE);
		if(ResultCount>=100&&(ResultCount<=280 || (ResultCount<=400&&Talk.carsol==1))){
			if(ResultCount==100){
				SPlaySound(11);
				s_time[Game.stage-1] = Game.count;
			}
			if(ResultCount<130)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(ResultCount-100));
			else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int bonus = 0;
			if(Talk.carsol==0){
				char message[128];
				wsprintf(message , "Stage %d Clear!",Game.stage);
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				bonus = 0;
				float levelbonus;
				char lb[4];
				for(int i=0;i<8;i++){
					int y = 120;
					int st_size = 15;
					int color = GetColor(255,255,255);
					switch(i){
						case 0:	wsprintf(message , "  StageBonus %d * 10000 = %d",Game.stage,Game.stage*10000);
							bonus += Game.stage*10000;
							break;
						case 1:	wsprintf(message , "+ PowerBonus %d * 20 = %d",Game.power,Game.power*20);
							bonus += Game.power*20;
							break;
						case 2:	wsprintf(message , "+ GrazeBonus %d * 10 = %d",Game.stage_graze[Game.stage],Game.stage_graze[Game.stage]*10);
							bonus += Game.stage_graze[Game.stage]*10;
							break;
						case 3:	wsprintf(message , "* PointBonus %d",Game.stage_point[Game.stage]);
							y += 10;
							color = GetColor(255,255,150);
							bonus *= Game.stage_point[Game.stage];
							break;
						case 4:	if(SAVE.Level==0){
								levelbonus = 0.5;
								wsprintf(lb , "0.5");
							}
							if(SAVE.Level==1){
								levelbonus = 1.0;
								wsprintf(lb , "1.0");
							}
							if(SAVE.Level==2){
								levelbonus = 1.2;
								wsprintf(lb , "1.2");
							}
							if(SAVE.Level==3){
								levelbonus = 1.5;
								wsprintf(lb , "1.5");
							}
							wsprintf(message , "* LevelBonus %s",lb);
							y += 10;
							color = GetColor(255,150,150);
							bonus *= levelbonus;
							bonus /= 10;
							bonus *= 10;
							break;
						case 5:	wsprintf(message , "TotalBonus %d",bonus);
							y += 30;
							color = GetColor(255,255,50);
							break;
						case 6:	int t[3];
							t[0] = s_time[Game.stage-1] / 3600;
							t[1] = (s_time[Game.stage-1]-t[0]*3600)/60;
							t[2] = (s_time[Game.stage-1]-t[0]*3600-t[1]*60)*1.67;
							wsprintf(message , "　プレイ時間 %2d分%02d秒%02d",t[0],t[1],t[2]);
							y += 60;
							color = GetColor(255,255,255);
							break;
						case 7:	int playtime = 0;
							for(int a=0;a<SCORE_STAGE_NUM;a++){
								playtime += s_time[a];
							}
							t[0] = playtime / 3600;
							t[1] = (playtime-t[0]*3600)/60;
							t[2] = (playtime-t[0]*3600-t[1]*60)*1.67;
							wsprintf(message , "総プレイ時間 %2d分%02d秒%02d",t[0],t[1],t[2]);
							y += 60;
							color = GetColor(255,255,255);
							break;
					}
					DrawFormatStringToHandle(50,y+st_size*i,color,ReplayFont,message);
				}
			}
			else if(Talk.carsol==1){
				char message[128];
				wsprintf(message , "All Clear!");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				bonus = 0;
				float levelbonus;
				char lb[4];
				for(int i=0;i<10;i++){
					int y = 120;
					int st_size = 15;
					int color = GetColor(255,255,255);
					switch(i){
						case 0:	wsprintf(message , "  StageBonus %d * 10000 = %d",Game.stage,Game.stage*10000);
							bonus += Game.stage*10000;
							break;
						case 1:	wsprintf(message , "+ PowerBonus %d * 20 = %d",Game.power,Game.power*20);
							bonus += Game.power*20;
							break;
						case 2:	wsprintf(message , "+ GrazeBonus %d * 10 = %d",Game.stage_graze[Game.stage],Game.stage_graze[Game.stage]*10);
							bonus += Game.stage_graze[Game.stage]*10;
							break;
						case 3:	wsprintf(message , "* PointBonus %d",Game.stage_point[Game.stage]);
							y += 10;
							color = GetColor(255,255,150);
							bonus *= Game.stage_point[Game.stage];
							break;
						case 4:	if(SAVE.Level==0){
								levelbonus = 0.5;
								wsprintf(lb , "0.5");
							}
							if(SAVE.Level==1){
								levelbonus = 1.0;
								wsprintf(lb , "1.0");
							}
							if(SAVE.Level==2){
								levelbonus = 1.2;
								wsprintf(lb , "1.2");
							}
							if(SAVE.Level==3){
								levelbonus = 1.5;
								wsprintf(lb , "1.5");
							}
							if(SAVE.Level==4){
								levelbonus = 2.0;
								wsprintf(lb , "2.0");
							}
							wsprintf(message , "* LevelBonus %s",lb);
							y += 10;
							color = GetColor(255,150,150);
							bonus *= levelbonus;
							bonus /= 10;
							bonus *= 10;
							break;
						case 5:	wsprintf(message , "+ PlayerBonus %d * 10M = %d",Player.life,Player.life * 10000000);
							bonus += Player.life * 10000000;
							y += 20;
							color = GetColor(255,255,50);
							break;
						case 6:	wsprintf(message , "+ MaxBonus %d * 100 = %d",Game.maxpoint,Game.maxpoint * 100);
							bonus += Game.maxpoint * 100;
							y += 20;
							color = GetColor(255,255,50);
							break;
						case 7:	wsprintf(message , "TotalBonus %d",bonus);
							y += 30;
							color = GetColor(255,255,50);
							break;
						case 8:	int t[3];
							t[0] = s_time[Game.stage-1] / 3600;
							t[1] = (s_time[Game.stage-1]-t[0]*3600)/60;
							t[2] = (s_time[Game.stage-1]-t[0]*3600-t[1]*60)*1.67;
							wsprintf(message , "　プレイ時間 %2d分%02d秒%02d",t[0],t[1],t[2]);
							y += 60;
							color = GetColor(255,255,255);
							break;
						case 9:	int playtime = 0;
							for(int a=0;a<SCORE_STAGE_NUM;a++){
								playtime += s_time[a];
							}
							t[0] = playtime / 3600;
							t[1] = (playtime-t[0]*3600)/60;
							t[2] = (playtime-t[0]*3600-t[1]*60)*1.67;
							wsprintf(message , "総プレイ時間 %2d分%02d秒%02d",t[0],t[1],t[2]);
							y += 60;
							color = GetColor(255,255,255);
							break;
					}
					DrawFormatStringToHandle(50,y+st_size*i,color,ReplayFont,message);
				}
			}
			if(ResultCount==100){
				SSc_AddScore(bonus);
				Game.stage_score[Game.stage-1] = Game.score;
				SReplay.end_score[Game.stage-1] = Game.score;
			}
			if(ResultCount==220){
				ResultCount --;
				if(c_key[KEY_INPUT_Z]==1||c_pad[SAVE.Key_Shot]==1){
					if(Game.score==Game.score2){
						ResultCount++;
					}
				}
			}
		}
		if(ResultCount>220){
			if(Talk.carsol==1){//オールクリア時
				fadein = 2.125*(ResultCount-220);
				if(ResultCount>340){
					fadein = 255;
				}
				if(ResultCount==400){
					if(SAVE.Practice<Game.stage)	SAVE.Practice = Game.stage;
					if(Game.title_carsol==0&&Game.stage!=7){
						SEnd_Reset();
						SMe_ChangeScene(ENDING);
					}
					else if(Game.title_carsol==0&&Game.stage==7){
						SMe_ChangeScene(STAFFROLE);
						SMu_ChangeVolumeBgm(0);
					}
					else{
						SMu_StopBgm();
						SMe_ChangeScene(TITLE);
					}
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
				}
			}
			else{
				if(ResultCount<=340){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(ResultCount-220));
					if(ResultCount>280){
						SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					}
					DrawBox(0,0,640,480,0,TRUE);
					if(ResultCount==340){
						if(SAVE.Practice<Game.stage)	SAVE.Practice = Game.stage;
						if(Game.stage<6&&(PlayerControlFlag==0||(PlayerControlFlag==1&&Replay[repnum].exist[Game.stage]==1)||(PlayerControlFlag==2&&Director_Replay[repnum].exist[Game.stage]==1))&&Game.title_carsol!=1){
							SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
							Game.stage++;
							SReset();
							ResultCount = -1;
						}
						else{
							SSc_SaveScore();
							ResultCount --;
						}
					}
				}
				else{
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(370-ResultCount));
					DrawBox(0,0,640,480,0,TRUE);
					if(ResultCount==370){
						ResultCount = -1;
					}
				}				
			}
		}
		ResultCount++;
	}
	if(Game.demo_flag==1)	SSc_Demo();
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	DrawGraph(0,0,Game.gra_flame,TRUE);
	if(Boss.exist==1 && Boss.x>10 && Boss.x<410){
		if(Boss.life<3000*((100.0-(float)Boss.defence)/100.0))		SetDrawBlendMode(DX_BLENDMODE_ALPHA,50.0*(Boss.count%5));
		else if(Boss.life<4000*((100.0-(float)Boss.defence)/100.0))	SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(Boss.count%20));
		else if(Boss.life<6000*((100.0-(float)Boss.defence)/100.0))	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(Boss.count%30));
		DrawGraphF(Boss.x-18.5,462,gra_enemymark,FALSE);
	}
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int x,y;
	if(SAVE.Level<4){
		GetGraphSize(Game.gra_side[7+SAVE.Level],&x,&y);
		DrawGraphF(525-x/2,25,Game.gra_side[7+SAVE.Level],TRUE);	
	}
	else{
		GetGraphSize(Game.gra_side[13],&x,&y);
		DrawGraphF(525-x/2,25,Game.gra_side[13],TRUE);	
	}
	for(int i=0;i<2;i++){
		GetGraphSize(Game.gra_side[i],&x,&y);
		DrawGraphF(470-x,65+20*i,Game.gra_side[i],TRUE);
	}
	for(int i=0;i<2;i++){
		GetGraphSize(Game.gra_side[2+i],&x,&y);
		DrawGraphF(470-x,120+20*i,Game.gra_side[2+i],TRUE);
	}
	for(int i=0;i<2;i++){
		GetGraphSize(Game.gra_side[4+i],&x,&y);
		DrawGraphF(470-x,170+20*i,Game.gra_side[4+i],TRUE);
	}
	GetGraphSize(Game.gra_side[12],&x,&y);
	DrawGraphF(470-x,220,Game.gra_side[12],TRUE);
	if(Game.score>=10&&Game.score2<=Game.score-10)		Game.score2 += 10;
	else if(Game.score>=1&&Game.score2<=Game.score-1)		Game.score2 += 1;
	if(Game.score>=100&&Game.score2<Game.score-100)		Game.score2 += 100;
	if(Game.score>=1000&&Game.score2<Game.score-1000)		Game.score2 += 1000;
	if(Game.score>=10000&&Game.score2<Game.score-10000)	Game.score2 += 10000;
	if(Game.score>=100000&&Game.score2<Game.score-100000)	Game.score2 += 100000;
	if(Game.score>=1000000&&Game.score2<Game.score-1000000)	Game.score2 += 1000000;
	if(Game.hiscore<Game.score2)		Game.hiscore = Game.score2;
	if(Game.hiscore<1000000000)	DrawNumber(492,66,9,Game.hiscore);
	else				DrawNumber(480,66,10,Game.hiscore);
	//DrawNumber2(492,66,9,E_Shot.size());
	if(Game.score2<1000000000)	DrawNumber(492,86,9,Game.score2);
	else				DrawNumber(480,86,10,Game.score2);
	for(int i=0;i<Player.life;i++){
		DrawGraphF(492+14*i,121,Game.gra_side[6],TRUE);
	}
	int powernum[3];
	powernum[0] = Game.power/20;
	powernum[1] = Game.power/2%10;
	powernum[2] = Game.power%2*5;
	DrawNumber(492+12*0,141,1,powernum[0]);
	DrawGraphF(492+12*1,141,Game.gra_number[10],TRUE);
	DrawNumber(492+12*2,141,1,powernum[1]);
	DrawNumber(492+12*3,141,1,powernum[2]);
	DrawNumber2(492,171,6,Game.graze);
	DrawNumber2(492,191,7,Game.maxpoint);
	int times = 1;
	if(Game.point>=1000)	times = 4;
	else if(Game.point>=100)times = 3;
	else if(Game.point>=10)	times = 2;
	DrawNumber2(492,221,4,Game.point);
	DrawGraphF(492+12*times+2,221,Game.gra_number[11],TRUE);
	DrawNumber2(492+12*times+16,221,4,Game.nextpoint);
	DrawGraphF(440,250,Game.gra_side[11],TRUE);
	if(PlayerControlFlag==1){
		int string = 0;
		if(Replay[repnum].fps[ReplayCount/60]>=10)	string = 1;
		if(Replay[repnum].fps[ReplayCount/60]>=100)	string = 2;
		if(Replay[repnum].fps[ReplayCount/60]<50)	SetDrawBright(100,100,255);
		DrawNumber2(390-12*string,440,3,Replay[repnum].fps[ReplayCount/60]);
	}
	if(PlayerControlFlag==2){
		int string = 0;
		if(Director_Replay[repnum].fps[ReplayCount/60]>=10)	string = 1;
		if(Director_Replay[repnum].fps[ReplayCount/60]>=100)	string = 2;
		if(Director_Replay[repnum].fps[ReplayCount/60]<50)	SetDrawBright(100,100,255);
		DrawNumber2(390-12*string,440,3,Director_Replay[repnum].fps[ReplayCount/60]);
	}
	SetDrawBright(255,255,255);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,fadein);
	DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
	
	return;
}

void SSc_SaveScore(){
//クリア時
	static int carsol;
	static int scx;
	static int scy;
	int x_num = 13;
	int y_num = 5;
	static int rank = 100;
	static int name_place;
	static int replay_place;
	if(Pause==0){
		GameOver++;
		SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
		SMu_StopBgm();
		Pause++;
		carsol = 0;
		rank = 100;
		char fi[128];
		wsprintf(fi , "data/bgm/BGM/16.mp3");
		PlayMusic(fi,DX_PLAYTYPE_LOOP);
		SMu_ChangeVolumeBgm(255*volume*0.01);
				if(PlayerControlFlag!=0){
					SetFrequencySoundMem(-1,BGM[now_playing]);
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
					DeleteGraph(PauseGra);
					Pause = 0;
					SMu_StopBgm();
					SMe_ChangeScene(TITLE);		
					return;
				}
				Pause++;
				scx = 0;
				scy = 0;
				name_place = 0;
				replay_place = 0;
				ScoreReplayCount = 0;
				SReplay.score = Game.score;
				SReplay.end_score[Game.stage-1] = Game.score;
				switch(Game.stage){
					case 1:	SReplay.stage = '1';	break;
					case 2:	SReplay.stage = '2';	break;
					case 3:	SReplay.stage = '3';	break;
					case 4:	SReplay.stage = '4';	break;
					case 5:	SReplay.stage = '5';	break;
					case 6:	SReplay.stage = '6';	break;
					case 7:	SReplay.stage = '1';	break;
				}
				if((Game.stage==6||Game.stage==7) && Talk.carsol==1)	SReplay.stage = 'C';
				DATEDATA D;
				GetDateTime(&D);
				SReplay.year = D.Year;
				SReplay.month = D.Mon;
				SReplay.date = D.Day;
				SReplay.hour = D.Hour;
				SReplay.minute = D.Min;
				SReplay.second = D.Sec;
				SReplay.level = SAVE.Level;
				SReplay.chara = SAVE.Chara;
				SReplay.weapon = SAVE.Weapon;
				if(Game.title_carsol==1){
					ScoreReplayCount = 1;
					return;
				}
				if(SAVE.Chara==0&&SAVE.Weapon==0){
					for(int i=0;i<10;i++){
						if(SAVE.ReimuA.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.ReimuA.level[SAVE.Level].score[a].score = SAVE.ReimuA.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.ReimuA.level[SAVE.Level].score[a].name[i] = SAVE.ReimuA.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.ReimuA.level[SAVE.Level].score[a].score = SAVE.ReimuA.level[SAVE.Level].score[a-1].score;
							SAVE.ReimuA.level[SAVE.Level].score[a].time = SAVE.ReimuA.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.ReimuA.level[SAVE.Level].score[a].s_score[i] = SAVE.ReimuA.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.ReimuA.level[SAVE.Level].score[a].s_time[i] = SAVE.ReimuA.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.ReimuA.level[SAVE.Level].score[a].stage = SAVE.ReimuA.level[SAVE.Level].score[a-1].stage;
							SAVE.ReimuA.level[SAVE.Level].score[a].year = SAVE.ReimuA.level[SAVE.Level].score[a-1].year;
							SAVE.ReimuA.level[SAVE.Level].score[a].month = SAVE.ReimuA.level[SAVE.Level].score[a-1].month;
							SAVE.ReimuA.level[SAVE.Level].score[a].date = SAVE.ReimuA.level[SAVE.Level].score[a-1].date;
							SAVE.ReimuA.level[SAVE.Level].score[a].hour = SAVE.ReimuA.level[SAVE.Level].score[a-1].hour;
							SAVE.ReimuA.level[SAVE.Level].score[a].minute = SAVE.ReimuA.level[SAVE.Level].score[a-1].minute;
							SAVE.ReimuA.level[SAVE.Level].score[a].second = SAVE.ReimuA.level[SAVE.Level].score[a-1].second;
						}
						SAVE.ReimuA.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.ReimuA.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.ReimuA.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.ReimuA.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.ReimuA.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.ReimuA.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.ReimuA.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						if((Game.stage==6||Game.stage==7) && Talk.carsol==1)	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = 'C';
						DATEDATA D;
						GetDateTime(&D);
						SAVE.ReimuA.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.ReimuA.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.ReimuA.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.ReimuA.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.ReimuA.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.ReimuA.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
					else{
						ScoreReplayCount = 1;
					}
				}
				if(SAVE.Chara==0&&SAVE.Weapon==1){
					for(int i=0;i<10;i++){
						if(SAVE.ReimuB.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.ReimuB.level[SAVE.Level].score[a].score = SAVE.ReimuB.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.ReimuB.level[SAVE.Level].score[a].name[i] = SAVE.ReimuB.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.ReimuB.level[SAVE.Level].score[a].score = SAVE.ReimuB.level[SAVE.Level].score[a-1].score;
							SAVE.ReimuB.level[SAVE.Level].score[a].time = SAVE.ReimuB.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.ReimuB.level[SAVE.Level].score[a].s_score[i] = SAVE.ReimuB.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.ReimuB.level[SAVE.Level].score[a].s_time[i] = SAVE.ReimuB.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.ReimuB.level[SAVE.Level].score[a].stage = SAVE.ReimuB.level[SAVE.Level].score[a-1].stage;
							SAVE.ReimuB.level[SAVE.Level].score[a].year = SAVE.ReimuB.level[SAVE.Level].score[a-1].year;
							SAVE.ReimuB.level[SAVE.Level].score[a].month = SAVE.ReimuB.level[SAVE.Level].score[a-1].month;
							SAVE.ReimuB.level[SAVE.Level].score[a].date = SAVE.ReimuB.level[SAVE.Level].score[a-1].date;
							SAVE.ReimuB.level[SAVE.Level].score[a].hour = SAVE.ReimuB.level[SAVE.Level].score[a-1].hour;
							SAVE.ReimuB.level[SAVE.Level].score[a].minute = SAVE.ReimuB.level[SAVE.Level].score[a-1].minute;
							SAVE.ReimuB.level[SAVE.Level].score[a].second = SAVE.ReimuB.level[SAVE.Level].score[a-1].second;
						}
						SAVE.ReimuB.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.ReimuB.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.ReimuB.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.ReimuB.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.ReimuB.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.ReimuB.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.ReimuB.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						if((Game.stage==6||Game.stage==7) && Talk.carsol==1)	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = 'C';
						DATEDATA D;
						GetDateTime(&D);
						SAVE.ReimuB.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.ReimuB.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.ReimuB.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.ReimuB.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.ReimuB.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.ReimuB.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
				if(SAVE.Chara==1&&SAVE.Weapon==0){
					for(int i=0;i<10;i++){
						if(SAVE.MarisaA.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.MarisaA.level[SAVE.Level].score[a].score = SAVE.MarisaA.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.MarisaA.level[SAVE.Level].score[a].name[i] = SAVE.MarisaA.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.MarisaA.level[SAVE.Level].score[a].score = SAVE.MarisaA.level[SAVE.Level].score[a-1].score;
							SAVE.MarisaA.level[SAVE.Level].score[a].time = SAVE.MarisaA.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.MarisaA.level[SAVE.Level].score[a].s_score[i] = SAVE.MarisaA.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.MarisaA.level[SAVE.Level].score[a].s_time[i] = SAVE.MarisaA.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.MarisaA.level[SAVE.Level].score[a].stage = SAVE.MarisaA.level[SAVE.Level].score[a-1].stage;
							SAVE.MarisaA.level[SAVE.Level].score[a].year = SAVE.MarisaA.level[SAVE.Level].score[a-1].year;
							SAVE.MarisaA.level[SAVE.Level].score[a].month = SAVE.MarisaA.level[SAVE.Level].score[a-1].month;
							SAVE.MarisaA.level[SAVE.Level].score[a].date = SAVE.MarisaA.level[SAVE.Level].score[a-1].date;
							SAVE.MarisaA.level[SAVE.Level].score[a].hour = SAVE.MarisaA.level[SAVE.Level].score[a-1].hour;
							SAVE.MarisaA.level[SAVE.Level].score[a].minute = SAVE.MarisaA.level[SAVE.Level].score[a-1].minute;
							SAVE.MarisaA.level[SAVE.Level].score[a].second = SAVE.MarisaA.level[SAVE.Level].score[a-1].second;
						}
						SAVE.MarisaA.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.MarisaA.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.MarisaA.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.MarisaA.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.MarisaA.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.MarisaA.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.MarisaA.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						if((Game.stage==6||Game.stage==7) && Talk.carsol==1)	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = 'C';
						DATEDATA D;
						GetDateTime(&D);
						SAVE.MarisaA.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.MarisaA.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.MarisaA.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.MarisaA.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.MarisaA.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.MarisaA.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
				if(SAVE.Chara==1&&SAVE.Weapon==1){
					for(int i=0;i<10;i++){
						if(SAVE.MarisaB.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.MarisaB.level[SAVE.Level].score[a].score = SAVE.MarisaB.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.MarisaB.level[SAVE.Level].score[a].name[i] = SAVE.MarisaB.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.MarisaB.level[SAVE.Level].score[a].score = SAVE.MarisaB.level[SAVE.Level].score[a-1].score;
							SAVE.MarisaB.level[SAVE.Level].score[a].time = SAVE.MarisaB.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.MarisaB.level[SAVE.Level].score[a].s_score[i] = SAVE.MarisaB.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.MarisaB.level[SAVE.Level].score[a].s_time[i] = SAVE.MarisaB.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.MarisaB.level[SAVE.Level].score[a].stage = SAVE.MarisaB.level[SAVE.Level].score[a-1].stage;
							SAVE.MarisaB.level[SAVE.Level].score[a].year = SAVE.MarisaB.level[SAVE.Level].score[a-1].year;
							SAVE.MarisaB.level[SAVE.Level].score[a].month = SAVE.MarisaB.level[SAVE.Level].score[a-1].month;
							SAVE.MarisaB.level[SAVE.Level].score[a].date = SAVE.MarisaB.level[SAVE.Level].score[a-1].date;
							SAVE.MarisaB.level[SAVE.Level].score[a].hour = SAVE.MarisaB.level[SAVE.Level].score[a-1].hour;
							SAVE.MarisaB.level[SAVE.Level].score[a].minute = SAVE.MarisaB.level[SAVE.Level].score[a-1].minute;
							SAVE.MarisaB.level[SAVE.Level].score[a].second = SAVE.MarisaB.level[SAVE.Level].score[a-1].second;
						}
						SAVE.MarisaB.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.MarisaB.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.MarisaB.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.MarisaB.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.MarisaB.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.MarisaB.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.MarisaB.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						if((Game.stage==6||Game.stage==7) && Talk.carsol==1)	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = 'C';
						DATEDATA D;
						GetDateTime(&D);
						SAVE.MarisaB.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.MarisaB.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.MarisaB.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.MarisaB.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.MarisaB.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.MarisaB.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
	}
	if(GameOver>0){
		if(ScoreCount>0){
			//ネーム入力処理+ScoreCountを0にする処理
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int color;
			if(SAVE.Chara==0&&SAVE.Weapon==0){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.ReimuA.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.ReimuA.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].name,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].month,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreCount = 0;
						ScoreReplayCount = 1;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.ReimuA.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.ReimuA.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			if(SAVE.Chara==0&&SAVE.Weapon==1){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.ReimuB.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.ReimuB.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].name,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].month,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreReplayCount = 1;
						ScoreCount = 0;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.ReimuB.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.ReimuB.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			if(SAVE.Chara==1&&SAVE.Weapon==0){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.MarisaA.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.MarisaA.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].name,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].month,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreCount = 0;
						ScoreReplayCount = 1;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.MarisaA.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.MarisaA.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			if(SAVE.Chara==1&&SAVE.Weapon==1){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.MarisaB.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.MarisaB.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].name,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].month,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreReplayCount = 1;
						ScoreCount = 0;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.MarisaB.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.MarisaB.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
		}
		if(ScoreReplayCount==1){
			name_place = 0;
			scx = 0;
			scy = 0;
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "Save Your Replay");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
			for(int i=0;i<REPLAY_NUM;i++){
				int y = 120;
				int st_size = 15;
				int color;
				if(Replay[i].month!=0){
					char me[3],le[7],ne[7];
					switch(Replay[i].level){
						case 0:	wsprintf(le, "Easy   ");	break;
						case 1:	wsprintf(le, "Normal ");	break;
						case 2:	wsprintf(le, "Hard   ");	break;
						case 3:	wsprintf(le, "Lunatic");	break;
						case 4:	wsprintf(le, "Extra  ");	break;
					}
					if(Replay[i].chara==0&&Replay[i].weapon==0)	wsprintf(ne, "ReimuA ");
					if(Replay[i].chara==0&&Replay[i].weapon==1)	wsprintf(ne, "ReimuB ");
					if(Replay[i].chara==1&&Replay[i].weapon==0)	wsprintf(ne, "MarisaA");
					if(Replay[i].chara==1&&Replay[i].weapon==1)	wsprintf(ne, "MarisaB");
					if(Replay[i].stage<=57)	wsprintf(me, "St%c",Replay[i].stage);
					else			wsprintf(me, "All");
					wsprintf(message , "%2d %s  %s %s %s %02d/%02d" ,
							i+1,
							Replay[i].name,
							ne,
							le,
							me,
							Replay[i].month,
							Replay[i].date );
					size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					if(replay_place==i)	color = GetColor(255,255,0);
					else			color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
				else{
					wsprintf(message , "%2d --------  ------- ------- --- --/--" ,i+1);
					size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					if(replay_place==i)	color = GetColor(255,255,0);
					else			color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
			}
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				replay_place ++;
				replay_place = replay_place%REPLAY_NUM;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				replay_place --;
				if(replay_place<0)	replay_place += REPLAY_NUM;
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				ScoreReplayCount = 2;
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				ScoreReplayCount = 0;
				SMu_StopBgm();
				SMe_ChangeScene(TITLE);
			}
		}
		else if(ScoreReplayCount==2){
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "Save Your Replay");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
			int y = 120;
			int st_size = 15;
			int color;
			char me[3];
			if(SReplay.stage<=57)	wsprintf(me, "St%c",SReplay.stage);
			wsprintf(message , "No%2d %s %10u %s %02d/%02d" ,
						replay_place+1,
						SReplay.name,
						SReplay.score,
						me,
						SReplay.month,
						SReplay.date);
			size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
			color = GetColor(255,255,0);
			DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*4,color,ReplayFont,message);
			int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
			int base_y = 320;
			int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
			for(int i=0;i<y_num;i++){
				for(int a=0;a<x_num;a++){
					int num = i*x_num+a;
					if(scx==a&&scy==i)	color = GetColor(255,255,0);
					else		color = GetColor(255,255,255);
					if(num<26){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
					}
					else if(num<52){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
					}
					else if(num<62){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
					}
					else if(num==62){}
					else if(num==63){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
					}
					else if(num==64){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
					}
				}
			}
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				scy ++;
				scy = scy%y_num;
				if(scx==10&&scy==4)	scy=0;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				scy --;
				if(scy<0)	scy += y_num;
				if(scx==10&&scy==4)	scy--;
			}	
			if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
				if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
					c_key[KEY_INPUT_RIGHT] = 21;
					c_pad[PAD_RIGHT] = 21;
				}
				SPlaySound(7);
				scx ++;
				scx = scx%x_num;
				if(scx==10&&scy==4)	scx++;
			}	
			else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
				if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
					c_key[KEY_INPUT_LEFT] = 21;
					c_pad[PAD_LEFT] = 21;
				}
				SPlaySound(7);
				scx --;
				if(scx<0)	scx += x_num;
				if(scx==10&&scy==4)	scx--;
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				int num = scy*x_num+scx;
				char string[2];
				if(num<26){
					wsprintf(string , "%c ",num+65);
				}
				else if(num<52){
					wsprintf(string , "%c ",num+71);
				}
				else if(num<62){
					wsprintf(string , "%c ",num-4);
				}
				else if(num==62){}
				else if(num==63){
					string[0] = ' ';
				}
				else if(num==64){
					ScoreReplayCount = 0;
					Replay[replay_place] = SReplay;
					//リプレイ保存処理
					int Element = Replay[replay_place].element_num;
					crypt(&Replay[replay_place],sizeof(REPLAYDATA),0xF7);
					char name[64];
					wsprintf(name , "replay");
					if(PathIsDirectory(name)==false){
						CreateDirectory(name,NULL);
					}
					wsprintf(name , "replay/th00_%02d.rpy",replay_place+1);
					FILE *fp;
					if((fp=fopen(name,"wb")) == NULL){
						char message[128];
						wsprintf(message , "Warning!\nリプレイの保存に失敗");
						MessageBox( 	NULL,
							message,
							"Error",
							MB_OK | 
							MB_ICONSTOP |
							MB_TOPMOST);
						return;
					}	
					fwrite(&Replay[replay_place],sizeof(REPLAYDATA)-REPLAY_ELEMENT_NUM-REPLAY_FPS_NUM,1,fp);
					for(int i=0;i<Element;i++){
						fputc(Replay[replay_place].replay[i],fp);
					}
					for(int i=0;i<Element/60;i++){
						fputc(Replay[replay_place].fps[i],fp);
					}
					fclose(fp);
					crypt(&Replay[replay_place],sizeof(REPLAYDATA),0xF7);
					SMu_StopBgm();
					SMe_ChangeScene(TITLE);
				}
				if(name_place==8)	name_place--;
				SReplay.name[name_place] = string[0];
				if(name_place<8)	name_place++;
				if(name_place==8){
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				if(name_place==0)	ScoreReplayCount = 1;
				else			name_place--;
				SReplay.name[name_place] = ' ';
			}
			else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
				SPlaySound(6);
				scx = x_num-1;
				scy = y_num-1;
			}
		}
	}
	return;
}

void SSc_Demo(){
	if(Game.count%60<30){}
	else{
 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		char message[128];
		wsprintf(message , "Demonstration");
		int size = GetDrawFormatStringWidthToHandle(GetSpellBonusFont,message);
		int color = GetColor(255,0,255);
		DrawStringToHandle(CENTER_X-size/2,CENTER_Y,message,GetColor(255,255,255),GetSpellBonusFont,color);			
	}
	if(c_key[KEY_INPUT_RETURN]==1||c_key[KEY_INPUT_ESCAPE]==1||c_pad[SAVE.Key_Pause]==1||Game.count==4500){
		if(Game.demo_count==0)	Game.demo_count = 1;
	}
	if(Game.demo_count>0){
 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Game.demo_count);
		DrawBox(0,0,640,480,0,TRUE);
		SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01*(120-Game.demo_count)/120);
		if(Game.demo_count==120){
			Game.demo_flag = 0;
			SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
			SMu_StopBgm();
			SMe_ChangeScene(TITLE);
		}		
		Game.demo_count++;
	}
	return;
}

void SSc_AddScore(int add){
	if(add < 4294967296-1-Game.score){
		Game.score += add;
	}
	else{
		Game.score = 4294967296-1;
	}
	return;
}

void SPl_Load(){
	try{
		char fi[128];
		SetTransColor(0,0,0);
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/dot/reimu/%d.png" , i+1);
			if(i<0||i>=GRA_REIMU_NUM)	throw(1);
			if( (gra_reimu[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/dot/marisa/%d.png" , i+1);
			if(i<0||i>=GRA_MARISA_NUM)	throw(2);
			if( (gra_marisa[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		SetTransColor(0,0,0);
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/shot/reimu/%d.png" , i+1);
			if(i<0||i>=GRA_SHOT_REIMU_NUM)	throw(3);
			if( (gra_shot_reimu[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/shot/marisa/%d.png" , i+1);
			SetTransColor(0,0,0);
			if(i<0||i>=GRA_SHOT_MARISA_NUM)	throw(4);
			if( (gra_shot_marisa[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<1;i++){
			wsprintf(fi , "data/img/dot/reimu/option.png");
			SetTransColor(0,0,0);
			if( (gra_option = LoadGraph(fi)) == -1)	throw(fi);
		}
		wsprintf(fi , "data/img/dot/reimu/atari_a.png");
		SetTransColor(0,0,0);
		if( (gra_atari = LoadGraph(fi)) == -1)	throw(fi);
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SPl_Load\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
	return;
}

void SPl_Reset(){
	try{
		Player.x = CENTER_X;
		Player.y = 420;
		for(int i=0;i<ATARI_NUM;i++){
			Player.atari_x[i] = Player.x;
			Player.atari_y[i] = Player.y;
		}
		Player.flash = 255;
		Player.large = 1;
		Player.count = 0;
		Player.miss = 0;
		Player.death = 0;
		Player.nodamage = 90;
		Player.b_control = true;
		if(SAVE.Chara==0){
			Player.speed = 3.5;
			for(int i=0;i<3;i++){
				if(i<0||i>=GRA_REIMU_NUM||i>=PLAYER_IMG_NUM)	throw(1);
				Player.img[i] = gra_reimu[i];
			}
		}
		else{
			Player.speed = 4.0;
			for(int i=0;i<3;i++){
				if(i<0||i>=GRA_MARISA_NUM||i>=PLAYER_IMG_NUM)	throw(2);
				Player.img[i] = gra_marisa[i];
			}
		}
		GetGraphSize(Player.img[0],&Player.img_x,&Player.img_y);
		for(int i=0;i<4;i++){
			Option[i].flash = 0;
			Option[i].img = gra_option;
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SPl_Reset\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
	return;
}

void SPl_AI(){
	/*==================================
	　18通り
	  1 2 3
	  4 0 5
	  6 7 8
	  ①muteki<30かつ、敵・敵弾・ボス・レーザーに当たるなら評価０
	  ②pri:3敵がいるとき、最初の敵のx座標、一番低いところにいる敵のy座標+70に合わせに行く
	  ③アイテムがあるとき、一番低いところにあるアイテムが
	  　　y<300のとき 　上部回収しに行く pri:2
	      y>=300のとき  プレイヤーが真ん中より下なら普通回収、それ以外なら上部回収 pri:3
	  ④ボスがいるとき、ボスの座標に合わせに行く pri:3
	  ⑤基本、CENTER_Xとy=300 pri:1
	  ⑥ミスったら即ボム
	  ⑦アイテムが半径50以内にある（pattern0,2)なら低速 pri:2
	  ⑧トークカウントが0より大きいと、スキップ
	  ⑨敵かボスがいたらショット
	*///================================
	int number = 18;
	char pattern[18];
	int shot=0,bomb=0,slow=0,skip=0,up=0,down=0,left=0,right=0;
	for(int i=0;i<number;i++){
		pattern[i] = 0;
	}
	if(1){
		int max_y = -120;
		for(list<ENEMYDATA>::iterator it=Enemy.begin();it!=Enemy.end();it++){
			if(max_y<(*it).y)	max_y = (*it).y;
			if(it==Enemy.begin() && Player.x<(*it).x-5){
				for(int a=0;a<2;a++){
					pattern[3+9*a] += 3;
					pattern[5+9*a] += 3;
					pattern[8+9*a] += 3;
				}
			}
			else if(it==Enemy.begin() && Player.x>(*it).x+5){
				for(int a=0;a<2;a++){
					pattern[1+9*a] += 3;
					pattern[4+9*a] += 3;
					pattern[6+9*a] += 3;
				}
			}
			else if(it==Enemy.begin()){
			}
		}
		if(max_y!=-120){
			if(max_y+120>Player.y){
				for(int a=0;a<2;a++){
					pattern[6+9*a] += 3;
					pattern[7+9*a] += 3;
					pattern[8+9*a] += 3;
				}
			}
		}
		//↑ここまで敵をサーチ		
		int to_x = CENTER_X;
		max_y = -120;
		for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
			if(max_y<(*it).y&&((*it).pattern==0||(*it).pattern==2)){
				to_x = (*it).x;
				max_y = (*it).y;
			}
		}
		if(max_y!=-120){
			if(Player.x<to_x-5){
				for(int a=0;a<2;a++){
					pattern[3+9*a] += 2;
					pattern[5+9*a] += 2;
					pattern[8+9*a] += 2;
				}
			}
			else if(Player.x>to_x+5){
				for(int a=0;a<2;a++){
					pattern[1+9*a] += 2;
					pattern[4+9*a] += 2;
					pattern[6+9*a] += 2;
				}
			}
			else{
				for(int a=0;a<2;a++){
					pattern[0+9*a] += 1;
				}
			}
			if(max_y<300||Player.y>=CENTER_Y){
				for(int a=0;a<2;a++){
					pattern[1+9*a] += 3;
					pattern[2+9*a] += 3;
					pattern[3+9*a] += 3;
				}
			}
			else{
				if(Player.y<90){
				
				}
				else if(Player.y<CENTER_Y){
					for(int a=0;a<2;a++){
						pattern[1+9*a] += 2;
						pattern[2+9*a] += 2;
						pattern[3+9*a] += 2;
					}
				}
				else if(Player.y<max_y){
					for(int a=0;a<2;a++){
						pattern[6+9*a] += 2;
						pattern[7+9*a] += 2;
						pattern[8+9*a] += 2;
					}
					for(int a=0;a<9;a++){
						pattern[9+a] += 1;
					}
				}
				else if(Player.y-20>max_y){
					for(int a=0;a<2;a++){
						pattern[1+9*a] += 2;
						pattern[2+9*a] += 2;
						pattern[3+9*a] += 2;
					}
				}
			}
		}
/*		//↑ここまでアイテムをサーチ		
		if(Boss.exist>0 && Player.x<Boss.x-5){
			for(int a=0;a<2;a++){
				pattern[3+9*a] += 4;
				pattern[5+9*a] += 4;
				pattern[8+9*a] += 4;
			}
		}
		else if(Boss.exist>0 && Player.x>Boss.x+5){
			for(int a=0;a<2;a++){
				pattern[1+9*a] += 4;
				pattern[4+9*a] += 4;
				pattern[6+9*a] += 4;
			}
		}
		else if(Boss.exist>0){
		}
		//↑ここまでボスをサーチ		
		if(Player.x<CENTER_X-10){
			for(int a=0;a<2;a++){
				pattern[3+9*a] += 2;
				pattern[5+9*a] += 2;
				pattern[8+9*a] += 2;
			}
		}
		else if(Player.x>CENTER_X+10){
			for(int a=0;a<2;a++){
				pattern[1+9*a] += 2;
				pattern[4+9*a] += 2;
				pattern[6+9*a] += 2;
			}
		}
		else{
			for(int a=0;a<2;a++){
				pattern[0+9*a] += 1;
			}
		}
		if(Player.y<290){
			for(int a=0;a<2;a++){
				pattern[6+9*a] += 2;
				pattern[7+9*a] += 2;
				pattern[8+9*a] += 2;
			}
		}
		else if(Player.y>300){
			for(int a=0;a<2;a++){
				pattern[1+9*a] += 2;
				pattern[2+9*a] += 2;
				pattern[3+9*a] += 2;
			}
		}
		else{
			for(int a=0;a<2;a++){
				pattern[0+9*a] += 1;
			}
		}
		//↑基本サーチ*/
	}
	for(int i=0;i<number;i++){
		float x = Player.x;
		float y = Player.y;
		float speed;
		float root = sin(Radian(45,TRUE));
		float atari_x[2],atari_y[2];
		if(SAVE.Chara==0)	speed = 3.5;
		else			speed = 4.0;
		if(i>=number/2)		speed -= 2.0;
		switch(i%(number/2)){
			case 0:	x += 0;
				y += 0;
				break;
			case 1:	x -= speed*root;
				y -= speed*root;
				break;
			case 2:	x += 0;
				y -= speed;
				break;
			case 3:	x += speed*root;
				y -= speed*root;
				break;
			case 4:	x -= speed;
				y += 0;
				break;
			case 5:	x += speed;
				y += 0;
				break;
			case 6:	x -= speed*root;
				y += speed*root;
				break;
			case 7:	x += 0;
				y += speed;
				break;
			case 8:	x += speed*root;
				y += speed*root;
				break;
		}
		//当たり判定取得
		float large = 2;
		if(SAVE.Chara==0)	large = 1;
		atari_x[0] = x-large;
		atari_x[1] = x+large;
		atari_y[0] = y-large;
		atari_y[1] = y+large;
		if(Player.nodamage<30){
			for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
				if((*it).debug_AI==true){
					if(atari_x[0]<(*it).atari_x[1] &&
					   atari_x[1]>(*it).atari_x[0] &&
					   atari_y[0]<(*it).atari_y[1] &&
					   atari_y[1]>(*it).atari_y[0]){
						pattern[i] = -1;	
						break;
					}
				}		
			}
			for(list<ENEMYDATA>::iterator it=Enemy.begin();it!=Enemy.end();it++){
				if(atari_x[0]<(*it).atari_x[1] &&
				   atari_x[1]>(*it).atari_x[0] &&
				   atari_y[0]<(*it).atari_y[1] &&
				   atari_y[1]>(*it).atari_y[0]){
					pattern[i] = -1;	
					break;
				}		
			}
			for(list<LASERDATA>::iterator it=Laser.begin();it!=Laser.end();it++){
				while((*it).angle>360)	(*it).angle-=360;
				while((*it).angle<0)	(*it).angle+=360;
				float sx = x - (*it).x;
				float sy = y - (*it).y;
				float sq = sqrt(sx*sx+sy*sy);
				int flag = 0;
				if(sin(Radian((*it).angle,TRUE))>=0 && y>=(*it).y)	flag ++;
				else if(sin(Radian((*it).angle,TRUE))<0 && y<(*it).y)	flag ++;
				if(cos(Radian((*it).angle,TRUE))>=0 && x>=(*it).x)	flag ++;
				else if(cos(Radian((*it).angle,TRUE))<0 && x<(*it).x)	flag ++;
				if((*it).atari==true&&sq<(*it).speed*(*it).count&&flag==2){
					float d;
					if((*it).angle==90||(*it).angle==270)		d = abs((*it).x - x);
					else if((*it).angle==0||(*it).angle==180)	d = abs((*it).y - y);
					else						d = abs(tan(Radian((*it).angle,TRUE))*(x-(*it).x) - (y-(*it).y)) / sqrt(pow(tan(Radian((*it).angle,TRUE)),2)+1);
				if(d<(*it).img_x/2){
						pattern[i] = -1;
					}
				}
			}
			if(atari_x[0]<Boss.atari_x[1] &&
			   atari_x[1]>Boss.atari_x[0] &&
			   atari_y[0]<Boss.atari_y[1] &&
			   atari_y[1]>Boss.atari_y[0]){
				pattern[i] = -1;	
			}
		}
		//↑ここまで死に判定
	}
	int select = 0;
	int priority = -1;
	for(int i=0;i<number;i++){
		if(priority<pattern[i]){
			select = i;
			priority = pattern[i];
		}
	}
	if(select>=9)	slow = 1;
	if(Enemy.size()>0||Boss.exist>0)	shot = 1;
	if(Player.miss>0)	bomb = 1;
	if(Talk.count>0)	skip = 1;
	if(select==1 || select==2 || select==3)	up = 1;
	if(select==6 || select==7 || select==8)	down = 1;
	if(select==1 || select==4 || select==6)	left = 1;
	if(select==3 || select==5 || select==8)	right = 1;

		static int pad[C_PAD_NUM];
		for(int i=0;i<C_KEY_NUM;i++){
			if(i!=KEY_INPUT_ESCAPE&&i!=KEY_INPUT_P)	c_key[i] = 0;
		}
		for(int i=0;i<C_PAD_NUM;i++){
			if(i!=SAVE.Key_Pause)	c_pad[i] = pad[i];
		}
		if(shot==1)	c_pad[SAVE.Key_Shot]++;
		else		c_pad[SAVE.Key_Shot] = 0;
		if(bomb==1)	c_pad[SAVE.Key_Bomb]++;
		else		c_pad[SAVE.Key_Bomb] = 0;
		if(slow==1)	c_pad[SAVE.Key_Slow]++;
		else		c_pad[SAVE.Key_Slow] = 0;
		if(skip==1)	c_pad[SAVE.Key_Skip]++;
		else		c_pad[SAVE.Key_Skip] = 0;
		if(up==1)	c_pad[PAD_UP]++;
		else		c_pad[PAD_UP] = 0;
		if(down==1)	c_pad[PAD_DOWN]++;
		else		c_pad[PAD_DOWN] = 0;
		if(left==1)	c_pad[PAD_LEFT]++;
		else		c_pad[PAD_LEFT] = 0;
		if(right==1)	c_pad[PAD_RIGHT]++;
		else		c_pad[PAD_RIGHT] = 0;

	return;
}

void SPl_Main(){
		static int pad[C_PAD_NUM];
		if(PlayerControlFlag==1){
			for(int i=0;i<C_KEY_NUM;i++){
				if(i!=KEY_INPUT_ESCAPE&&i!=KEY_INPUT_P)	c_key[i] = 0;
			}
			for(int i=0;i<C_PAD_NUM;i++){
				if(i!=SAVE.Key_Pause)	c_pad[i] = pad[i];
			}
			int key = Replay[repnum].replay[ReplayCount];
			if(key&1)	c_pad[SAVE.Key_Shot]++;
			else		c_pad[SAVE.Key_Shot] = 0;
			if(key&2)	c_pad[SAVE.Key_Bomb]++;
			else		c_pad[SAVE.Key_Bomb] = 0;
			if(key&4)	c_pad[SAVE.Key_Slow]++;
			else		c_pad[SAVE.Key_Slow] = 0;
			if(key&8)	c_pad[SAVE.Key_Skip]++;
			else		c_pad[SAVE.Key_Skip] = 0;
			if(key&16)	c_pad[PAD_UP]++;
			else		c_pad[PAD_UP] = 0;
			if(key&32)	c_pad[PAD_DOWN]++;
			else		c_pad[PAD_DOWN] = 0;
			if(key&64)	c_pad[PAD_LEFT]++;
			else		c_pad[PAD_LEFT] = 0;
			if(key&128)	c_pad[PAD_RIGHT]++;
			else		c_pad[PAD_RIGHT] = 0;
		}
		if(PlayerControlFlag==2){
			for(int i=0;i<C_KEY_NUM;i++){
				if(i!=KEY_INPUT_ESCAPE&&i!=KEY_INPUT_P)	c_key[i] = 0;
			}
			for(int i=0;i<C_PAD_NUM;i++){
				if(i!=SAVE.Key_Pause)	c_pad[i] = pad[i];
			}
			int key = Director_Replay[repnum].replay[ReplayCount];
			if(key&1)	c_pad[SAVE.Key_Shot]++;
			else		c_pad[SAVE.Key_Shot] = 0;
			if(key&2)	c_pad[SAVE.Key_Bomb]++;
			else		c_pad[SAVE.Key_Bomb] = 0;
			if(key&4)	c_pad[SAVE.Key_Slow]++;
			else		c_pad[SAVE.Key_Slow] = 0;
			if(key&8)	c_pad[SAVE.Key_Skip]++;
			else		c_pad[SAVE.Key_Skip] = 0;
			if(key&16)	c_pad[PAD_UP]++;
			else		c_pad[PAD_UP] = 0;
			if(key&32)	c_pad[PAD_DOWN]++;
			else		c_pad[PAD_DOWN] = 0;
			if(key&64)	c_pad[PAD_LEFT]++;
			else		c_pad[PAD_LEFT] = 0;
			if(key&128)	c_pad[PAD_RIGHT]++;
			else		c_pad[PAD_RIGHT] = 0;
		}
		//if(debug_AI==true)	SPl_AI();		
		if(c_pad[SAVE.Key_Shot]>0||c_key[KEY_INPUT_Z]>0)	Game.Shot++;
		else	Game.Shot = 0;
		if(c_pad[SAVE.Key_Bomb]>0||c_key[KEY_INPUT_X]>0)	Game.Bomb++;
		else	Game.Bomb = 0;
		if(c_pad[SAVE.Key_Slow]>0||c_key[KEY_INPUT_LSHIFT]>0||c_key[KEY_INPUT_RSHIFT]>0)	Game.Slow++;
		else	Game.Slow = 0;
		if(c_pad[SAVE.Key_Skip]>0||c_key[KEY_INPUT_LCONTROL]>0||c_key[KEY_INPUT_RCONTROL]>0)	Game.Skip++;
		else	Game.Skip = 0;

	if(Player.death>0)	SPl_Death();
	else if(Player.miss>0)	SPl_Miss();
	else			SPl_Control();
   	SRe_Main();
	if(PlayerControlFlag!=0){
		for(int i=0;i<C_PAD_NUM;i++){
			if(i!=SAVE.Key_Pause)	pad[i] = c_pad[i];
		}
	}		
	return;
}

void SPl_Draw(){
	for(int i=0;i<Game.power/20&&i<4;i++){
		if(Option[i].count>0){
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,Option[i].flash);
			if(loop_count==0)	DrawRotaGraphF(Option[i].x+shake_x, Option[i].y+shake_y, Option[i].large, Radian(Option[i].angle,TRUE), Option[i].img, TRUE, FALSE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,Player.flash);
	if(Player.nodamage>0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-25*(3*Player.nodamage%10));
		Player.nodamage--;
		if(debug_muteki==0&&Boss.spell_num>=95&&Boss.spell_num<=97&&Boss.gage_exist==1&&Boss.count>=120&&SAVE.Level==3){
			Game.skip = true;
		}
		else	Game.skip = false;
	}
	else{
		Game.skip = false;
	}		
	if(loop_count==0)	DrawRotaGraphF(Player.x+shake_x, Player.y+shake_y, Player.large, 0, Player.img[Player.img_num], TRUE, FALSE);
	Player.count++;
	//当たり判定弾は総合描画関数にて描画
	/*
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	DrawFormatString(50,50,GetColor(255,255,255),"P.x:%f",Player.x);
	DrawFormatString(50,60,GetColor(255,255,255),"P.y:%f",Player.y);
	DrawFormatString(50,70,GetColor(255,255,255),"P.flash:%d",Player.flash);
	*/
	return;
}

void SPl_Control(){
	try{
		static unsigned int SlowCount = 0;//スローでいる時間
		static float spread_x[40];
		static float spread_y[40];
		int num = 40;//スプレッドの判定数
		bool bMove = false;//スプレッド用。動いたか
		float x_limit[2];//プレイヤーx座標限界値
		float y_limit[2];//プレイヤーy座標限界値
		x_limit[0] = 40;
		x_limit[1] = 380;
		y_limit[0] = 35;
		y_limit[1] = 440;
		float root = sin(Radian(45,TRUE));//ルート２
		if(Game.count==0){
			for(int i=0;i<num;i++){
				spread_x[i] = Player.x;
				spread_y[i] = Player.y;
			}
			SlowCount = 0;
		}
		if(Game.Slow>0){
	       	 	if(Player.b_slow==false){
				Player.speed -= 2;
			}
			SlowCount++;
			Player.slow++;
			Player.b_slow = true;
		}
		else if(Player.b_slow==true){
			Player.speed += 2;
			Player.slow--;
			Player.b_slow = false;
		}
		else{
			if(SlowCount>0)	SlowCount--;
			if(Player.slow>5)	Player.slow = 5;
			if(Player.slow>0)	Player.slow--;
		}
       	
		char naname = 0;//斜め入力判定
		Player.img_num = 0;
		bool bSp = false;//スプレッドの斜め判定
		if(c_pad[PAD_DOWN]>0 || c_key[KEY_INPUT_DOWN]>0){
			Player.y += Player.speed;
			if(Player.b_slow==true && Player.y<=y_limit[1]){
				for(int i=0;i<num;i++){
					spread_y[i] += Player.speed;
				}
				bSp = true;
			}
			naname = 1;
			bMove = true;
		}
		else if(c_pad[PAD_UP]>0 || c_key[KEY_INPUT_UP]>0){
			Player.y -= Player.speed;
			if(Player.b_slow==true && Player.y>=x_limit[0]){
				for(int i=0;i<num;i++){
					spread_y[i] -= Player.speed;
				}
				bSp = true;
			}
			naname = 2;
			bMove = true;
		}
		if(c_pad[PAD_LEFT]>0 || c_key[KEY_INPUT_LEFT]>0){
			switch(naname){
				case 0:
					Player.x -= Player.speed;
					if(Player.b_slow==true && Player.x>=x_limit[0]){
						for(int i=0;i<num;i++){
							spread_x[i] -= Player.speed;
						}
					}
					break;
				case 1:
					Player.x -= Player.speed * root;
					if(Player.b_slow==true){
						for(int i=0;i<num;i++){
							if(Player.x>=x_limit[0])	spread_x[i] -= Player.speed * root;
							if(bSp==true)	spread_y[i] -= Player.speed - Player.speed*root;
						}
					}
					Player.y -= Player.speed - Player.speed*root;
					break;
				case 2:
					Player.x -= Player.speed * root;
					if(Player.b_slow==true){
						for(int i=0;i<num;i++){
							if(Player.x>=x_limit[0])	spread_x[i] -= Player.speed * root;
							if(bSp==true)	spread_y[i] += Player.speed - Player.speed*root;
						}
					}
					Player.y += Player.speed - Player.speed*root;
					break;
			}
			Player.img_num = 2;
			bMove = true;
			if(7>=HANYOU_NUM)	throw(1);
			if(Player.b_slow==false&&Player.d_hanyou[7]>-60)	Player.d_hanyou[7] -= 2;
		}
		else if(c_pad[PAD_RIGHT]>0 || c_key[KEY_INPUT_RIGHT]>0){
			switch(naname){
				case 0:
					Player.x += Player.speed;
					if(Player.b_slow==true && Player.x<=x_limit[1]){
						for(int i=0;i<num;i++){
							spread_x[i] += Player.speed;
						}
					}
					break;
				case 1:
					Player.x += Player.speed * root;
					Player.y -= Player.speed - Player.speed*root;
					if(Player.b_slow==true){
						for(int i=0;i<num;i++){
							if(Player.x<=x_limit[1])	spread_x[i] += Player.speed * root;
							if(bSp==true)	spread_y[i] -= Player.speed - Player.speed*root;
						}
					}
					break;
				case 2:
					Player.x += Player.speed * root;
					Player.y += Player.speed - Player.speed*root;
					if(Player.b_slow==true){
						for(int i=0;i<num;i++){
							if(Player.x<=x_limit[1])	spread_x[i] += Player.speed * root;
							if(bSp==true)	spread_y[i] += Player.speed - Player.speed*root;
						}
					}
					break;
			}
			Player.img_num = 1;
			bMove = true;
			if(7>=HANYOU_NUM)	throw(2);
			if(Player.b_slow==false&&Player.d_hanyou[7]<60)		Player.d_hanyou[7] += 2;
		}
		else{
			if(7>=HANYOU_NUM)	throw(3);
			if(Player.b_slow==false&&Player.d_hanyou[7]<0)		Player.d_hanyou[7] += 2;
			if(Player.b_slow==false&&Player.d_hanyou[7]>0)		Player.d_hanyou[7] -= 2;
		}
		if(Player.x<x_limit[0])		Player.x = x_limit[0];
		if(Player.x>x_limit[1])		Player.x = x_limit[1];
		if(Player.y<y_limit[0])		Player.y = y_limit[0];
		if(Player.y>y_limit[1])		Player.y = y_limit[1];
       	
		//当たり判定取得
		float large = 2;
		if(SAVE.Chara==0)	large = 1;
		Player.atari_x[0] = Player.x-large;
		Player.atari_x[1] = Player.x+large;
		Player.atari_y[0] = Player.y-large;
		Player.atari_y[1] = Player.y+large;
		if(debug_muteki==1){
			Player.nodamage = 2;
		}
		if(bMove==true){
			if(Player.b_slow==false){
				spread_x[0] = Player.x;
				spread_y[0] = Player.y;
				for(int i=0;i<num-1;i++){
					if(num-i-1<0||num-i-1>=num)	throw(4);
					spread_x[num-i-1] = spread_x[num-i-2];
					spread_y[num-i-1] = spread_y[num-i-2];
				}
			}
		}
		//オプション########################
		int limit = Game.power/20;//オプションの数
		for(int i=0;i<limit&&i<4;i++){
			if(i<0||i>=OPTION_NUM)	throw(5);
			if(Option[i].count == 0){
				if(Game.count!=0)	SPlaySound(14);
				else{
					Option[i].count = 30;
				}
			}			
			if(Option[i].count<30){
				Option[i].large = 4 - 0.1 * Option[i].count;
				Option[i].flash = 45 + 7 * Option[i].count;
			}
			else{		
				Option[i].large = 1;
				Option[i].flash = 255;
			}
			Option[i].angle += 6;
			if(SAVE.Chara==0){
				if(SAVE.Weapon==0){
					switch(limit){
						case 1:
							Option[i].x = Player.x;
							Option[i].y = Player.y - Player.img_y/2 - 15;
							break;
						case 2:
							Option[i].x = Player.x - Player.img_x/2 -5 + (Player.img_x+10) * i;
							Option[i].y = Player.y - 34;
							break;
						case 3:
							if(i<2){
								Option[i].x = Player.x - Player.img_x/2 -5 + (Player.img_x+10) * i;
								Option[i].y = Player.y - 34;
							}
							else{
								Option[i].x = Player.x;
								Option[i].y = Player.y - Player.img_y/2 - 15;
							}
							break;
						case 4:
							if(i<2){
								Option[i].x = Player.x - Player.img_x/2 -5 + (Player.img_x+10) * i;
								Option[i].y = Player.y - 34;
							}
							else{
								Option[i].x = Player.x - Player.img_x/2 -19 + (Player.img_x+38)*(i-2);
								Option[i].y = Player.y - 20;
							}
							break;
					}
					float sx = Player.x - Option[i].x;
					float sy = Player.y - Option[i].y;
					float sq = sqrt(sx*sx+sy*sy);
					float move_x = sx / sq;
					float move_y = sy / sq;
					if(SlowCount<10){
						Option[i].x += 8*SlowCount * move_x;
						Option[i].y += 8*SlowCount * move_y;
					}
					else{
						Option[i].x += 80 * move_x;
						Option[i].y += 80 * move_y;
						SlowCount = 10;
					}
				}
				else{
					float l;
					if(SlowCount<5)	l = 6*SlowCount;
					else{
						l = 30;
						SlowCount = 5;
					}
					Option[i].x = Player.x + (60-l)*1.0*cos(Radian(4*Player.count+i*(360/limit),TRUE));
					Option[i].y = Player.y + (60-l)*0.6*sin(Radian(4*Player.count+i*(360/limit),TRUE));
				}
			}
			else{
				if(SAVE.Weapon==0){
					switch(limit){
						case 1:
							Option[i].x = Player.x;
							Option[i].y = Player.y - Player.img_y/2 - 15;
							break;
						case 2:
							Option[i].x = Player.x - Player.img_x/2 + (Player.img_x) * i;
							Option[i].y = Player.y - 34;
							break;
						case 3:
							if(i<2){
								Option[i].x = Player.x - Player.img_x/2 + (Player.img_x) * i;
								Option[i].y = Player.y - 34;
							}
							else{
								Option[i].x = Player.x;
								Option[i].y = Player.y - Player.img_y/2 - 15;
							}
							break;
						default:
							if(i<2){
								Option[i].x = Player.x - Player.img_x/2 +4 + (Player.img_x-8) * i;
								Option[i].y = Player.y - 34;
							}
							else{
								Option[i].x = Player.x - Player.img_x/2 -18 + (Player.img_x+36)*(i-2);
								Option[i].y = Player.y - 20;
							}
							break;
					}
					float sx = Player.x - Option[i].x;
					float sy = Player.y - Option[i].y;
					float sq = sqrt(sx*sx+sy*sy);
					float move_x = sx / sq;
					float move_y = sy / sq;
					if(SlowCount<10){
						Option[i].x += 2*SlowCount * move_x;
						Option[i].y += 2*SlowCount * move_y;
					}
					else{
						Option[i].x += 20 * move_x;
						Option[i].y += 20 * move_y;
						SlowCount = 10;
					}
				}
				else{
					Option[i].x = spread_x[(i+1)*(num/4)-1];
					Option[i].y = spread_y[(i+1)*(num/4)-1];
				}		
			}
			Option[i].count++;
		}
		for(int i=limit;i<4;i++){
			if(i<0||i>=OPTION_NUM)	throw(6);
			Option[i].count = 0;
		}
		if(Player.b_control==true){
			//ショット########################
			if(Game.Shot%3==1){
				SPlaySound(22);
				int p = 50 - 5*(Game.power/20);
				for(int i=0;i<2;i++){
					if(SAVE.Chara==0)	SPs_Make(Player.x-11+22*i,Player.y+20, 270, 20.0, gra_shot_reimu[0], p);	
					else			SPs_Make(Player.x-11+22*i,Player.y+20, 270, 20.0, gra_shot_marisa[0], p);	
				}
			}
			if(SAVE.Chara==0&&SAVE.Weapon==0){
			if(Game.Shot%8==1){
					for(int i=0;i<limit&&i<4;i++){
						SPs_Make(Option[i].x,Option[i].y, 270, 8.0, gra_shot_reimu[1], 20, 1);
					}
				}
			}
			if(SAVE.Chara==0&&SAVE.Weapon==1){
				if(Game.Shot%3==1){
					for(int i=0;i<limit&&i<4;i++){
						SPs_Make(Option[i].x,Option[i].y, 270, 20.0, gra_shot_reimu[2], 55);
					}
				}
			}
			if(SAVE.Chara==1&&SAVE.Weapon==0){
				if(Game.Shot>=1){
				for(int i=0;i<limit&&i<4;i++){
						SPs_Make(Option[i].x,Option[i].y-240, 270, 0.0, gra_shot_marisa[1], 1, 2);
					}
				}
			}
			if(SAVE.Chara==1&&SAVE.Weapon==1){
				if(Game.Shot%7==1){
					for(int i=0;i<limit&&i<4;i++){
						for(int a=0;a<3;a++){
							SPs_Make(Option[i].x,Option[i].y, 260+Player.d_hanyou[7]+10*a, 10.0, gra_shot_marisa[2], 20, 3);
						}
					}
				}
			}
       		
			if(Game.power>=20&&Bomb.life==0&&(Game.Bomb==1)){
				SPlaySound(13);
				Game.power -= 20;
				SBom_Make(Player.x,Player.y);
				Player.nodamage = 300;
				if(Boss.spell_num!=124)	Game.spell_getflag = 1;
			}
		}
		return;
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SPl_Control\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
}

void SPl_Pause(){
	//兼ゲームオーバー
	static int carsol;
	static int scx;
	static int scy;
	int x_num = 13;
	int y_num = 5;
	static int rank = 100;
	static int name_place;
	static int replay_place;
	if(GameOver==0&&Player.life<0){
		GameOver++;
		SetFrequencySoundMem(100,BGM[now_playing]);
		SMu_ChangeVolumeBgm(1);
		Pause++;
		carsol = 0;
		rank = 100;
	 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DeleteGraph(PauseGra);
		PauseGra = MakeGraph(640,480);
		GetDrawScreenGraph(0,0,640,480,PauseGra);
		/*DrawExtendGraph(0,0,320,240,PauseGra,FALSE);
		PauseGra = MakeGraph(320,240);
		GetDrawScreenGraph(0,0,320,240,PauseGra);
		*/
		char fi[128];
		wsprintf(fi , "data/bgm/BGM/16.mp3");
		PlayMusic(fi,DX_PLAYTYPE_LOOP);
		SMu_ChangeVolumeBgm(255*volume*0.01);
	}
	if(GameOver>0){
	 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawBright(255,220,180);
		DrawExtendGraph(0,0,640,480,PauseGra,FALSE);
		SetDrawBright(255,255,255);
		if(Pause<30){
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,6*Pause);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
			Pause++;
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Pause);
			char message[128];
			wsprintf(message , "満身創痍！");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2-3*(30-Pause),CENTER_Y-10,GetColor(255,150,150),PauseFont,message);
		}
		else if(Pause==30){
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "満身創痍！");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,CENTER_Y-10,GetColor(255,150,150),PauseFont,message);
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				if(PlayerControlFlag!=0){
					SetFrequencySoundMem(-1,BGM[now_playing]);
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
					DeleteGraph(PauseGra);
					Pause = 0;
					SMu_StopBgm();
					SMe_ChangeScene(TITLE);		
					return;
				}
				Pause++;
				scx = 0;
				scy = 0;
				name_place = 0;
				replay_place = 0;
				ScoreReplayCount = 0;
				SReplay.score = Game.score;
				SReplay.end_score[Game.stage-1] = Game.score;
				switch(Game.stage){
					case 1:	SReplay.stage = '1';	break;
					case 2:	SReplay.stage = '2';	break;
					case 3:	SReplay.stage = '3';	break;
					case 4:	SReplay.stage = '4';	break;
					case 5:	SReplay.stage = '5';	break;
					case 6:	SReplay.stage = '6';	break;
					case 7:	SReplay.stage = '1';	break;
				}
				DATEDATA D;
				GetDateTime(&D);
				SReplay.year = D.Year;
				SReplay.month = D.Mon;
				SReplay.date = D.Day;
				SReplay.hour = D.Hour;
				SReplay.minute = D.Min;
				SReplay.second = D.Sec;
				SReplay.level = SAVE.Level;
				SReplay.chara = SAVE.Chara;
				SReplay.weapon = SAVE.Weapon;
				if(Game.title_carsol==1){
					return;
				}
				if(SAVE.Chara==0&&SAVE.Weapon==0){
					for(int i=0;i<10;i++){
						if(SAVE.ReimuA.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.ReimuA.level[SAVE.Level].score[a].score = SAVE.ReimuA.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.ReimuA.level[SAVE.Level].score[a].name[i] = SAVE.ReimuA.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.ReimuA.level[SAVE.Level].score[a].score = SAVE.ReimuA.level[SAVE.Level].score[a-1].score;
							SAVE.ReimuA.level[SAVE.Level].score[a].time = SAVE.ReimuA.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.ReimuA.level[SAVE.Level].score[a].s_score[i] = SAVE.ReimuA.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.ReimuA.level[SAVE.Level].score[a].s_time[i] = SAVE.ReimuA.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.ReimuA.level[SAVE.Level].score[a].stage = SAVE.ReimuA.level[SAVE.Level].score[a-1].stage;
							SAVE.ReimuA.level[SAVE.Level].score[a].year = SAVE.ReimuA.level[SAVE.Level].score[a-1].year;
							SAVE.ReimuA.level[SAVE.Level].score[a].month = SAVE.ReimuA.level[SAVE.Level].score[a-1].month;
							SAVE.ReimuA.level[SAVE.Level].score[a].date = SAVE.ReimuA.level[SAVE.Level].score[a-1].date;
							SAVE.ReimuA.level[SAVE.Level].score[a].hour = SAVE.ReimuA.level[SAVE.Level].score[a-1].hour;
							SAVE.ReimuA.level[SAVE.Level].score[a].minute = SAVE.ReimuA.level[SAVE.Level].score[a-1].minute;
							SAVE.ReimuA.level[SAVE.Level].score[a].second = SAVE.ReimuA.level[SAVE.Level].score[a-1].second;
						}
						SAVE.ReimuA.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.ReimuA.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.ReimuA.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.ReimuA.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.ReimuA.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.ReimuA.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.ReimuA.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.ReimuA.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						DATEDATA D;
						GetDateTime(&D);
						SAVE.ReimuA.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.ReimuA.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.ReimuA.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.ReimuA.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.ReimuA.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.ReimuA.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
				if(SAVE.Chara==0&&SAVE.Weapon==1){
					for(int i=0;i<10;i++){
						if(SAVE.ReimuB.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.ReimuB.level[SAVE.Level].score[a].score = SAVE.ReimuB.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.ReimuB.level[SAVE.Level].score[a].name[i] = SAVE.ReimuB.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.ReimuB.level[SAVE.Level].score[a].score = SAVE.ReimuB.level[SAVE.Level].score[a-1].score;
							SAVE.ReimuB.level[SAVE.Level].score[a].time = SAVE.ReimuB.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.ReimuB.level[SAVE.Level].score[a].s_score[i] = SAVE.ReimuB.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.ReimuB.level[SAVE.Level].score[a].s_time[i] = SAVE.ReimuB.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.ReimuB.level[SAVE.Level].score[a].stage = SAVE.ReimuB.level[SAVE.Level].score[a-1].stage;
							SAVE.ReimuB.level[SAVE.Level].score[a].year = SAVE.ReimuB.level[SAVE.Level].score[a-1].year;
							SAVE.ReimuB.level[SAVE.Level].score[a].month = SAVE.ReimuB.level[SAVE.Level].score[a-1].month;
							SAVE.ReimuB.level[SAVE.Level].score[a].date = SAVE.ReimuB.level[SAVE.Level].score[a-1].date;
							SAVE.ReimuB.level[SAVE.Level].score[a].hour = SAVE.ReimuB.level[SAVE.Level].score[a-1].hour;
							SAVE.ReimuB.level[SAVE.Level].score[a].minute = SAVE.ReimuB.level[SAVE.Level].score[a-1].minute;
							SAVE.ReimuB.level[SAVE.Level].score[a].second = SAVE.ReimuB.level[SAVE.Level].score[a-1].second;
						}
						SAVE.ReimuB.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.ReimuB.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.ReimuB.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.ReimuB.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.ReimuB.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.ReimuB.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.ReimuB.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.ReimuB.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						DATEDATA D;
						GetDateTime(&D);
						SAVE.ReimuB.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.ReimuB.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.ReimuB.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.ReimuB.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.ReimuB.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.ReimuB.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
				if(SAVE.Chara==1&&SAVE.Weapon==0){
					for(int i=0;i<10;i++){
						if(SAVE.MarisaA.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.MarisaA.level[SAVE.Level].score[a].score = SAVE.MarisaA.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.MarisaA.level[SAVE.Level].score[a].name[i] = SAVE.MarisaA.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.MarisaA.level[SAVE.Level].score[a].score = SAVE.MarisaA.level[SAVE.Level].score[a-1].score;
							SAVE.MarisaA.level[SAVE.Level].score[a].time = SAVE.MarisaA.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.MarisaA.level[SAVE.Level].score[a].s_score[i] = SAVE.MarisaA.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.MarisaA.level[SAVE.Level].score[a].s_time[i] = SAVE.MarisaA.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.MarisaA.level[SAVE.Level].score[a].stage = SAVE.MarisaA.level[SAVE.Level].score[a-1].stage;
							SAVE.MarisaA.level[SAVE.Level].score[a].year = SAVE.MarisaA.level[SAVE.Level].score[a-1].year;
							SAVE.MarisaA.level[SAVE.Level].score[a].month = SAVE.MarisaA.level[SAVE.Level].score[a-1].month;
							SAVE.MarisaA.level[SAVE.Level].score[a].date = SAVE.MarisaA.level[SAVE.Level].score[a-1].date;
							SAVE.MarisaA.level[SAVE.Level].score[a].hour = SAVE.MarisaA.level[SAVE.Level].score[a-1].hour;
							SAVE.MarisaA.level[SAVE.Level].score[a].minute = SAVE.MarisaA.level[SAVE.Level].score[a-1].minute;
							SAVE.MarisaA.level[SAVE.Level].score[a].second = SAVE.MarisaA.level[SAVE.Level].score[a-1].second;
						}
						SAVE.MarisaA.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.MarisaA.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.MarisaA.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.MarisaA.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.MarisaA.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.MarisaA.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.MarisaA.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.MarisaA.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						DATEDATA D;
						GetDateTime(&D);
						SAVE.MarisaA.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.MarisaA.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.MarisaA.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.MarisaA.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.MarisaA.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.MarisaA.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
				if(SAVE.Chara==1&&SAVE.Weapon==1){
					for(int i=0;i<10;i++){
						if(SAVE.MarisaB.level[SAVE.Level].score[i].score<=Game.score){
							rank = i;
							break;
						}
					}
					if(rank<10){
						Game.stage_score[Game.stage-1] = Game.score;
						Game.stage_graze[Game.stage-1] = Game.graze;
						Game.stage_point[Game.stage-1] = Game.point;
						for(int i=0;i<Game.stage-1;i++){
							Game.stage_score[Game.stage-1] -= Game.stage_score[i];
							Game.stage_graze[Game.stage-1] -= Game.stage_graze[i];
							Game.stage_point[Game.stage-1] -= Game.stage_point[i];
						}
						Game.stage_count[Game.stage-1] = Game.count;
						for(int a=9;a>rank;a--){
							SAVE.MarisaB.level[SAVE.Level].score[a].score = SAVE.MarisaB.level[SAVE.Level].score[a-1].score;
							for(int i=0;i<SCORE_NAME_NUM;i++){
								SAVE.MarisaB.level[SAVE.Level].score[a].name[i] = SAVE.MarisaB.level[SAVE.Level].score[a-1].name[i];
							}
							SAVE.MarisaB.level[SAVE.Level].score[a].score = SAVE.MarisaB.level[SAVE.Level].score[a-1].score;
							SAVE.MarisaB.level[SAVE.Level].score[a].time = SAVE.MarisaB.level[SAVE.Level].score[a-1].time;
							for(int i=0;i<Game.stage;i++){
								SAVE.MarisaB.level[SAVE.Level].score[a].s_score[i] = SAVE.MarisaB.level[SAVE.Level].score[a-1].s_score[i];
								SAVE.MarisaB.level[SAVE.Level].score[a].s_time[i] = SAVE.MarisaB.level[SAVE.Level].score[a-1].s_time[i];
							}
							SAVE.MarisaB.level[SAVE.Level].score[a].stage = SAVE.MarisaB.level[SAVE.Level].score[a-1].stage;
							SAVE.MarisaB.level[SAVE.Level].score[a].year = SAVE.MarisaB.level[SAVE.Level].score[a-1].year;
							SAVE.MarisaB.level[SAVE.Level].score[a].month = SAVE.MarisaB.level[SAVE.Level].score[a-1].month;
							SAVE.MarisaB.level[SAVE.Level].score[a].date = SAVE.MarisaB.level[SAVE.Level].score[a-1].date;
							SAVE.MarisaB.level[SAVE.Level].score[a].hour = SAVE.MarisaB.level[SAVE.Level].score[a-1].hour;
							SAVE.MarisaB.level[SAVE.Level].score[a].minute = SAVE.MarisaB.level[SAVE.Level].score[a-1].minute;
							SAVE.MarisaB.level[SAVE.Level].score[a].second = SAVE.MarisaB.level[SAVE.Level].score[a-1].second;
						}
						SAVE.MarisaB.level[SAVE.Level].score[rank].score = Game.score;
						for(int i=0;i<SCORE_NAME_NUM;i++){
							SAVE.MarisaB.level[SAVE.Level].score[rank].name[i] = ' ';
						}
						SAVE.MarisaB.level[SAVE.Level].score[rank].score = Game.score;
						SAVE.MarisaB.level[SAVE.Level].score[rank].time = 0;
						for(int i=0;i<Game.stage;i++){
							SAVE.MarisaB.level[SAVE.Level].score[rank].s_score[i] = Game.stage_score[i];
							SAVE.MarisaB.level[SAVE.Level].score[rank].s_time[i] = Game.stage_count[i];
							SAVE.MarisaB.level[SAVE.Level].score[rank].time += Game.stage_count[i];
						}
						switch(Game.stage){
							case 1:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '1';	break;
							case 2:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '2';	break;
							case 3:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '3';	break;
							case 4:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '4';	break;
							case 5:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '5';	break;
							case 6:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '6';	break;
							case 7:	SAVE.MarisaB.level[SAVE.Level].score[rank].stage = '1';	break;
						}
						DATEDATA D;
						GetDateTime(&D);
						SAVE.MarisaB.level[SAVE.Level].score[rank].year = D.Year;
						SAVE.MarisaB.level[SAVE.Level].score[rank].month = D.Mon;
						SAVE.MarisaB.level[SAVE.Level].score[rank].date = D.Day;
						SAVE.MarisaB.level[SAVE.Level].score[rank].hour = D.Hour;
						SAVE.MarisaB.level[SAVE.Level].score[rank].minute = D.Min;
						SAVE.MarisaB.level[SAVE.Level].score[rank].second = D.Sec;
						ScoreCount = 1;
					}
				}
			}
		}
		else if(ScoreCount>0){
			//ネーム入力処理+ScoreCountを0にする処理
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int color;
			if(SAVE.Chara==0&&SAVE.Weapon==0){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.ReimuA.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.ReimuA.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].name,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].month,
								SAVE.ReimuA.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreCount = 0;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.ReimuA.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.ReimuA.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			if(SAVE.Chara==0&&SAVE.Weapon==1){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.ReimuB.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.ReimuB.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].name,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].month,
								SAVE.ReimuB.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreCount = 0;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.ReimuB.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.ReimuB.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			if(SAVE.Chara==1&&SAVE.Weapon==0){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.MarisaA.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.MarisaA.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].name,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].month,
								SAVE.MarisaA.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreCount = 0;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.MarisaA.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.MarisaA.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			if(SAVE.Chara==1&&SAVE.Weapon==1){
				char message[128];
				wsprintf(message , "Score Ranking");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
				int y = 100;
				int st_size = 15;
				for(int i=1;i<11;i++){
					if(i>0){
						char me[6];
						if(SAVE.MarisaB.level[SAVE.Level].score[i-1].stage<=57)	wsprintf(me, "Stage%c",SAVE.MarisaB.level[SAVE.Level].score[i-1].stage);
						else							wsprintf(me, "All   ");
						wsprintf(message , "%2d. %s %10u %s %02d/%02d" ,
								i,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].name,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].score,
								me,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].month,
								SAVE.MarisaB.level[SAVE.Level].score[i-1].date );
						size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					}
					if(rank==i-1)	color = GetColor(255,255,50);
					else		color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
				int base_y = 320;
				int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
				for(int i=0;i<y_num;i++){
					for(int a=0;a<x_num;a++){
						int num = i*x_num+a;
						if(scx==a&&scy==i)	color = GetColor(255,255,0);
						else		color = GetColor(255,255,255);
						if(num<26){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
						}
						else if(num<52){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
						}
						else if(num<62){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
						}
						else if(num==62){}
						else if(num==63){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
						}
						else if(num==64){
							DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
						}
					}
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					scy ++;
					scy = scy%y_num;
					if(scx==10&&scy==4)	scy=0;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					scy --;
					if(scy<0)	scy += y_num;
					if(scx==10&&scy==4)	scy--;
				}	
				if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
					if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
						c_key[KEY_INPUT_RIGHT] = 21;
						c_pad[PAD_RIGHT] = 21;
					}
					SPlaySound(7);
					scx ++;
					scx = scx%x_num;
					if(scx==10&&scy==4)	scx++;
				}	
				else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
					if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
						c_key[KEY_INPUT_LEFT] = 21;
						c_pad[PAD_LEFT] = 21;
					}
					SPlaySound(7);
					scx --;
					if(scx<0)	scx += x_num;
					if(scx==10&&scy==4)	scx--;
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					int num = scy*x_num+scx;
					char string[2];
					if(num<26){
						wsprintf(string , "%c ",num+65);
					}
					else if(num<52){
						wsprintf(string , "%c ",num+71);
					}
					else if(num<62){
						wsprintf(string , "%c ",num-4);
					}
					else if(num==62){}
					else if(num==63){
						string[0] = ' ';
					}
					else if(num==64){
						ScoreCount = 0;
						return;
					}
					if(name_place==8)	name_place--;
					SAVE.MarisaB.level[SAVE.Level].score[rank].name[name_place] = string[0];
					if(name_place<8)	name_place++;
					if(name_place==8){
						scx = x_num-1;
						scy = y_num-1;
					}
				}
				else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SPlaySound(6);
					if(name_place>0)	name_place--;
					SAVE.MarisaB.level[SAVE.Level].score[rank].name[name_place] = ' ';
				}
				else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
					SPlaySound(6);
					scx = x_num-1;
					scy = y_num-1;
				}
			}
		}
		else if(ScoreReplayCount==1){
			name_place = 0;
			scx = 0;
			scy = 0;
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "Save Your Replay");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
			for(int i=0;i<REPLAY_NUM;i++){
				int y = 120;
				int st_size = 15;
				int color;
				if(Replay[i].month!=0){
					char me[3],le[7],ne[7];
					switch(Replay[i].level){
						case 0:	wsprintf(le, "Easy   ");	break;
						case 1:	wsprintf(le, "Normal ");	break;
						case 2:	wsprintf(le, "Hard   ");	break;
						case 3:	wsprintf(le, "Lunatic");	break;
						case 4:	wsprintf(le, "Extra  ");	break;
					}
					if(Replay[i].chara==0&&Replay[i].weapon==0)	wsprintf(ne, "ReimuA ");
					if(Replay[i].chara==0&&Replay[i].weapon==1)	wsprintf(ne, "ReimuB ");
					if(Replay[i].chara==1&&Replay[i].weapon==0)	wsprintf(ne, "MarisaA");
					if(Replay[i].chara==1&&Replay[i].weapon==1)	wsprintf(ne, "MarisaB");
					if(Replay[i].stage<=57)	wsprintf(me, "St%c",Replay[i].stage);
					else			wsprintf(me, "All");
					wsprintf(message , "%2d %s  %s %s %s %02d/%02d" ,
							i+1,
							Replay[i].name,
							ne,
							le,
							me,
							Replay[i].month,
							Replay[i].date );
					size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					if(replay_place==i)	color = GetColor(255,255,0);
					else			color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
				else{
					wsprintf(message , "%2d --------  ------- ------- --- --/--" ,i+1);
					size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
					if(replay_place==i)	color = GetColor(255,255,0);
					else			color = GetColor(255,255,255);
					DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*i,color,ReplayFont,message);
				}
			}
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				replay_place ++;
				replay_place = replay_place%REPLAY_NUM;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				replay_place --;
				if(replay_place<0)	replay_place += REPLAY_NUM;
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				ScoreReplayCount = 2;
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				ScoreReplayCount = 0;
			}
		}
		else if(ScoreReplayCount==2){
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "Save Your Replay");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,90,GetColor(255,255,150),PauseFont,message);
			int y = 120;
			int st_size = 15;
			int color;
			char me[3];
			if(SReplay.stage<=57)	wsprintf(me, "St%c",SReplay.stage);
			wsprintf(message , "No%2d %s %10u %s %02d/%02d" ,
						replay_place+1,
						SReplay.name,
						SReplay.score,
						me,
						SReplay.month,
						SReplay.date);
			size = GetDrawFormatStringWidthToHandle(ReplayFont, message);
			color = GetColor(255,255,0);
			DrawFormatStringToHandle(CENTER_X-size/2,y+st_size*4,color,ReplayFont,message);
			int base_x = CENTER_X - GetDrawFormatStringWidthToHandle(ReplayFont, "A B C D E F G H I J K L M  ")/2;
			int base_y = 320;
			int size_base = GetDrawFormatStringWidthToHandle(ReplayFont, "AA");
			for(int i=0;i<y_num;i++){
				for(int a=0;a<x_num;a++){
					int num = i*x_num+a;
					if(scx==a&&scy==i)	color = GetColor(255,255,0);
					else		color = GetColor(255,255,255);
					if(num<26){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+65);
					}
					else if(num<52){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num+71);
					}
					else if(num<62){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"%c",num-4);
					}
					else if(num==62){}
					else if(num==63){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"_");
					}
					else if(num==64){
						DrawFormatStringToHandle(base_x+size_base*a,base_y+st_size*i,color,ReplayFont,"End");
					}
				}
			}
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				scy ++;
				scy = scy%y_num;
				if(scx==10&&scy==4)	scy=0;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				scy --;
				if(scy<0)	scy += y_num;
				if(scx==10&&scy==4)	scy--;
			}	
			if((c_key[KEY_INPUT_RIGHT]%10==1&&c_key[KEY_INPUT_RIGHT]!=11) || (c_pad[PAD_RIGHT]%10==1&&c_pad[PAD_RIGHT]!=11)){
				if(c_key[KEY_INPUT_RIGHT]==31 || c_pad[PAD_RIGHT]==31){
					c_key[KEY_INPUT_RIGHT] = 21;
					c_pad[PAD_RIGHT] = 21;
				}
				SPlaySound(7);
				scx ++;
				scx = scx%x_num;
				if(scx==10&&scy==4)	scx++;
			}	
			else if((c_key[KEY_INPUT_LEFT]%10==1&&c_key[KEY_INPUT_LEFT]!=11) || (c_pad[PAD_LEFT]%10==1&&c_pad[PAD_LEFT]!=11)){
				if(c_key[KEY_INPUT_LEFT]==31 || c_pad[PAD_LEFT]==31){
					c_key[KEY_INPUT_LEFT] = 21;
					c_pad[PAD_LEFT] = 21;
				}
				SPlaySound(7);
				scx --;
				if(scx<0)	scx += x_num;
				if(scx==10&&scy==4)	scx--;
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				int num = scy*x_num+scx;
				char string[2];
				if(num<26){
					wsprintf(string , "%c ",num+65);
				}
				else if(num<52){
					wsprintf(string , "%c ",num+71);
				}
				else if(num<62){
					wsprintf(string , "%c ",num-4);
				}
				else if(num==62){}
				else if(num==63){
					string[0] = ' ';
				}
				else if(num==64){
					ScoreReplayCount = 0;
					Replay[replay_place] = SReplay;
					//リプレイ保存処理
					int Element = Replay[replay_place].element_num;
					crypt(&Replay[replay_place],sizeof(REPLAYDATA),0xF7);
					char name[64];
					wsprintf(name , "replay");
					if(PathIsDirectory(name)==false){
						CreateDirectory(name,NULL);
					}
					wsprintf(name , "replay/th00_%02d.rpy",replay_place+1);
					FILE *fp;
					if((fp=fopen(name,"wb")) == NULL){
						char message[128];
						wsprintf(message , "Warning!\nリプレイの保存に失敗");
						MessageBox( 	NULL,
							message,
							"Error",
							MB_OK | 
							MB_ICONSTOP |
							MB_TOPMOST);
						return;
					}	
					fwrite(&Replay[replay_place],sizeof(REPLAYDATA)-REPLAY_ELEMENT_NUM-REPLAY_FPS_NUM,1,fp);
					for(int i=0;i<Element;i++){
						fputc(Replay[replay_place].replay[i],fp);
					}
					for(int i=0;i<Element/60;i++){
						fputc(Replay[replay_place].fps[i],fp);
					}
					fclose(fp);
					crypt(&Replay[replay_place],sizeof(REPLAYDATA),0xF7);
					return;
				}
				if(name_place==8)	name_place--;
				SReplay.name[name_place] = string[0];
				if(name_place<8)	name_place++;
				if(name_place==8){
					scx = x_num-1;
					scy = y_num-1;
				}
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				if(name_place==0)	ScoreReplayCount = 1;
				else			name_place--;
				SReplay.name[name_place] = ' ';
			}
			else if(c_key[KEY_INPUT_ESCAPE]==1 || c_pad[SAVE.Key_Pause]==1){
				SPlaySound(6);
				scx = x_num-1;
				scy = y_num-1;
			}
		}
		else if(Pause<60){
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "満身創痍！");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,CENTER_Y-10-2.55*(Pause-30),GetColor(255,150,150),PauseFont,message);
			for(int i=0;i<4;i++){
				switch(i){
					case 0:	wsprintf(message , "コンティニューする");	break;
					case 1:	wsprintf(message , "タイトル画面に戻る");	break;
					case 2:	wsprintf(message , "リプレイを保存する");	break;
					case 3:	wsprintf(message , "最初からやり直す");		break;
				}
	 			SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				if(carsol==i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawFormatStringToHandle(-30+5*(Pause-30),210+30*i,GetColor(255,255,255),PauseFont,message);
			}
			Pause++;
		}
		else{
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
			DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			char message[128];
			wsprintf(message , "満身創痍！");
			int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
			DrawFormatStringToHandle(CENTER_X-size/2,150,GetColor(255,150,150),PauseFont,message);
			for(int i=0;i<4;i++){
				switch(i){
					case 0:	wsprintf(message , "コンティニューする");	break;
					case 1:	wsprintf(message , "タイトル画面に戻る");	break;
					case 2:	wsprintf(message , "リプレイを保存する");	break;
					case 3:	wsprintf(message , "最初からやり直す");		break;
				}
	 			SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
				if(carsol==i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawFormatStringToHandle(120,210+30*i,GetColor(255,255,255),PauseFont,message);
			}
			if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
				if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
					c_key[KEY_INPUT_DOWN] = 21;
					c_pad[PAD_DOWN] = 21;
				}
				SPlaySound(7);
				carsol ++;
				carsol = carsol%4;
			}	
			else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
				if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
					c_key[KEY_INPUT_UP] = 21;
					c_pad[PAD_UP] = 21;
				}
				SPlaySound(7);
				carsol --;
				if(carsol<0){
					carsol += 4;
				}
			}	
			if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
				SPlaySound(5);
				if(carsol!=2){
					SetFrequencySoundMem(-1,BGM[now_playing]);
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
					DeleteGraph(PauseGra);
					Pause = 0;
				}
				if(carsol==0){
					SMu_StopBgm();
					SSc_Reset();
					SReset();
					Player.life = start_life;
					if(Game.con_times<9&&(Game.stage!=1&&Game.stage!=7)){
						Game.con_times++; 
						Game.power = 40;
					}
					else{
						Game.power = 0;
					}
					Game.score = Game.con_times;
					Game.score2 = Game.con_times;
					SSc_Reset2();
				}
				else if(carsol==1){
					SMu_StopBgm();
					SMe_ChangeScene(TITLE);
				}
				else if(carsol==2){
					ScoreReplayCount = 1;
					Pause = 31;
					replay_place = 0;
				}
				else if(carsol==3){
					Game.stage = start_stage;
					SMu_StopBgm();
					SSc_Reset();
					SReset();
					Player.life = start_life;
					Game.power = start_power;
					Game.con_times = 0;
				}
			}
			else if(c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
				SPlaySound(6);
				carsol = 1;
			}
		}
	}
	else if(Pause>=0){
		if(Pause==0&&(c_pad[SAVE.Key_Pause]==1||c_key[KEY_INPUT_ESCAPE]==1)){
			SPlaySound(15);
			SetFrequencySoundMem(100,BGM[now_playing]);
			SMu_ChangeVolumeBgm(1);
			Pause++;
			carsol = 0;
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			PauseGra = MakeGraph(640,480);
			GetDrawScreenGraph(0,0,640,480,PauseGra);
			/*DrawExtendGraph(0,0,320,240,PauseGra,FALSE);
			PauseGra = MakeGraph(320,240);
			GetDrawScreenGraph(0,0,320,240,PauseGra);
			*/
		}
		if(Pause>0){
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			SetDrawBright(255,220,180);
			DrawExtendGraph(0,0,640,480,PauseGra,FALSE);
			SetDrawBright(255,255,255);
			if(Pause<30){
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,6*Pause);
				DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
				Pause++;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Pause);
				char message[128];
				wsprintf(message , "一時停止");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2-3*(30-Pause),150,GetColor(255,150,150),PauseFont,message);
				DrawFormatStringToHandle(-30+5*Pause,210,GetColor(255,255,255),PauseFont,"ゲームを継続する");
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,4*Pause);
				DrawFormatStringToHandle(-30+5*Pause,240,GetColor(255,255,255),PauseFont,"タイトル画面に戻る");
				DrawFormatStringToHandle(-30+5*Pause,270,GetColor(255,255,255),PauseFont,"最初からやり直す");
			}
			else{
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
				DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
				Pause++;
		 		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				char message[128];
				wsprintf(message , "一時停止");
				int size = GetDrawFormatStringWidthToHandle(PauseFont, message);
				DrawFormatStringToHandle(CENTER_X-size/2,150,GetColor(255,150,150),PauseFont,message);
				for(int i=0;i<3;i++){
					switch(i){
						case 0:	wsprintf(message , "ゲームを継続する");		break;
						case 1:	wsprintf(message , "タイトル画面に戻る");	break;
						case 2:	wsprintf(message , "最初からやり直す");		break;
					}
		 			SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
					if(carsol==i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
					DrawFormatStringToHandle(120,210+30*i,GetColor(255,255,255),PauseFont,message);
				}
				if((c_key[KEY_INPUT_DOWN]%10==1&&c_key[KEY_INPUT_DOWN]!=11) || (c_pad[PAD_DOWN]%10==1&&c_pad[PAD_DOWN]!=11)){
					if(c_key[KEY_INPUT_DOWN]==31 || c_pad[PAD_DOWN]==31){
						c_key[KEY_INPUT_DOWN] = 21;
						c_pad[PAD_DOWN] = 21;
					}
					SPlaySound(7);
					carsol ++;
					carsol = carsol%3;
				}	
				else if((c_key[KEY_INPUT_UP]%10==1&&c_key[KEY_INPUT_UP]!=11) || (c_pad[PAD_UP]%10==1&&c_pad[PAD_UP]!=11)){
					if(c_key[KEY_INPUT_UP]==31 || c_pad[PAD_UP]==31){
						c_key[KEY_INPUT_UP] = 21;
						c_pad[PAD_UP] = 21;
					}
					SPlaySound(7);
					carsol --;
					if(carsol<0){
						carsol += 3;
					}
				}	
				if(c_key[KEY_INPUT_Z]==1||c_key[KEY_INPUT_RETURN]==1 || c_pad[SAVE.Key_Shot]==1){
					SPlaySound(5);
					SetFrequencySoundMem(-1,BGM[now_playing]);
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
					DeleteGraph(PauseGra);
					Pause = 0;
					if(carsol==0){}
					else if(carsol==1){
						SMu_StopBgm();
						SMe_ChangeScene(TITLE);
					}
					else if(carsol==2){
						Game.stage = start_stage;
						Player.life = start_life;
						Game.power = start_power;
						Game.con_times = 0;
						SMu_StopBgm();
						SSc_Reset();
						SReset();
					}
				}
				if(c_pad[SAVE.Key_Pause]==1||c_key[KEY_INPUT_ESCAPE]==1||c_key[KEY_INPUT_X]==1 || c_pad[SAVE.Key_Bomb]==1){
					SetFrequencySoundMem(-1,BGM[now_playing]);
					SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
					DeleteGraph(PauseGra);
					Pause = 0;
				}
			}
		}
	}
	return;
}

void SPl_Miss(){
	Player.miss--;
	int cp = c_pad[SAVE.Key_Bomb];
	int ck = c_key[KEY_INPUT_X];
	if(Game.power>=20&&Bomb.life==0&&(cp==1 || ck==1)){
		SPlaySound(13);
		Game.power -= 20;
		SBom_Make(Player.x,Player.y);
		Player.nodamage = 240;
		Player.miss = 0;
		if(Boss.spell_num!=104)	Game.spell_getflag = 1;
	}
	else if(Player.miss==0){
		Player.death = 100;
		Player.miss = 1;
		Game.spell_getflag = 1;
	}
	return;
}

void SPl_Death(){
	if(Player.death==100){
		SEf_Make(Player.x,Player.y,1);
		float sx = CENTER_X - Player.x;
		float sy = 0 - Player.y;
		float angle = Radian(atan2(sy,sx),FALSE)-30;
		for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
			if((*it).pattern==1||(*it).pattern==3){
				(*it).pattern = 0;
				(*it).move_x = 0;
				(*it).move_y = -1;
				(*it).count = 0;
			}
		}
		for(int i=0;i<7;i++){
			int img = 0;
			if(i%2==1)	img = 2;
			SIt_Make(Player.x,Player.y,angle+10*i,gra_item[img],2);
		}
		Game.power = 0;
		Player.flash = 0;
		int first;
		switch(SAVE.Level){
			case 0:	first = 10000;	break;
			case 1:	first = 50000;	break;
			case 2:	first = 100000;	break;
			case 3:	first = 200000;	break;
			case 4:	first = 500000;	break;
		}
		int minus = (Game.maxpoint - first)/100;
		minus *= 10;
		Game.maxpoint -= minus;
	}
	if(60<Player.death&&Player.death<=100){
		float length = 12*(100-Player.death);
		for(list<ENEMYDATA>::iterator it=Enemy.begin();it!=Enemy.end();it++){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			if(sq<length&&(*it).b_atari==true&&(*it).img[0]!=gra_circle){
				(*it).life -= 50;
			}
		}
		for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			if(sq<length&&(*it).dele_flag==0 && !(Boss.spell_num>=95&&Boss.spell_num<=97)){
				SEf_Make((*it).x,(*it).y,2,(*it).img);
				it = E_Shot.erase(it);
				it--;
				continue;
			}
		}
		if(Boss.exist==1){
			float sx = Player.x - Boss.x;
			float sy = Player.y - Boss.y;
			float sq = sqrt(sx*sx+sy*sy);
			if(sq<length){
				Boss.damage += 50;
			}
		}
	}
	if(Player.death==60){
		Player.life --;
		Player.img_num = 0;
		Player.x = CENTER_X;
		Player.y = 480;
		if(Player.life<0)	Player.y = 550;
		Player.flash = 255;
		Player.nodamage = 260;
	}
	if(Player.death<60){
		Player.y -= 1;
	}
	Player.death --;
	if(Player.death==0){
		Player.miss = 0;
	}
	float large = 2;
	if(SAVE.Chara==0)	large = 1;
	Player.atari_x[0] = Player.x-large;
	Player.atari_x[1] = Player.x+large;
	Player.atari_y[0] = Player.y-large;
	Player.atari_y[1] = Player.y+large;
	return;
}

void SPs_Load(){
	try{
		char fi[128];
		SetTransColor(0,0,0);
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/shot/reimu/%d.png" , i+1);
			if( (gra_shot_reimu[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<3;i++){
			SetTransColor(0,0,0);
			wsprintf(fi , "data/img/shot/marisa/%d.png" , i+1);
			if( (gra_shot_marisa[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SPs_Reset(){
	P_Shot.clear();
	return;
}

void SPs_Main(){
	for(list<P_SHOTDATA>::iterator it=P_Shot.begin();it!=P_Shot.end();it++){
		SPs_Move(it);
		if((*it).pattern==2&&(*it).count==6){
			it = P_Shot.erase(it);
			it--;
			continue;
		}
		if((*it).x<0-(*it).img_x/2 || (*it).x>450+(*it).img_x/2 || (*it).y<0-(*it).img_y/2 || (*it).y>480+(*it).img_y/2){
			it = P_Shot.erase(it);
			it--;
			continue;
		}
	}                                               
	
	return;
}

void SPs_Draw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for(list<P_SHOTDATA>::iterator it=P_Shot.begin();it!=P_Shot.end();it++){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		if((*it).count<10){
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			SetDrawBright(255,150,255);
		}
		if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle, (*it).img, TRUE, FALSE);
		(*it).count++;
		if(Boss.exist==1&&Boss.b_atari==true){
			if((*it).atari_x[0]<Boss.atari_x[1] &&
			   (*it).atari_x[1]>Boss.atari_x[0] &&
			   (*it).atari_y[0]<Boss.atari_y[1] &&
			   (*it).atari_y[1]>Boss.atari_y[0]){
				Boss.damage += (*it).atack;
				if((*it).img!=gra_shot_marisa[1]){
					SEf_Make((*it).x,(*it).y,7);
				}
				else{
					if((*it).count<=1)	SEf_Make(Boss.x,Boss.y,7);
				}
				if((*it).img!=gra_shot_marisa[1]){
					SSc_AddScore(10);
					it = P_Shot.erase(it);
					it--;
					continue;
				}
				else if((*it).count==3){
					SSc_AddScore(10);
				}
			}
		}
		//DrawBox((*it).atari_x[0],(*it).atari_y[0],(*it).atari_x[1],(*it).atari_y[1],GetColor(255,255,255),TRUE);
		if((*it).count==10)	(*it).atack /= 2;
		SetDrawBright(255,255,255);
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	
	return;
}

void SPs_Make(float x,float y,float angle,float speed,int img,int atack,int pattern){
	P_SHOTDATA P;
	P.x = x;
	P.y = y;
	for(int i=0;i<ATARI_NUM;i++){
		P.atari_x[i] = x;
		P.atari_y[i] = y;
	}
	P.move_x = cos(Radian(angle,TRUE));
	P.move_y = sin(Radian(angle,TRUE));
	P.speed = speed;
	P.angle = atan2(P.move_y,P.move_x)+1.57;
	P.img = img;
	P.atack = atack*2;
	P.pattern = pattern;
	P.count = 0;
	P.flash = 180;
	GetGraphSize(P.img,&P.img_x,&P.img_y);
	P.large = 1.0;
	for(int i=0;i<HANYOU_NUM;i++){
		P.i_hanyou[i] = 0;
		P.d_hanyou[i] = 0;
	}
	
	P_Shot.push_back(P);
	return;
}

void SPs_Move(list<P_SHOTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	
	if(p==1){
		if(Boss.exist==1&&Boss.b_atari==true){
			float sx = Boss.x - (*it).x;
			float sy = Boss.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			(*it).move_x = sx/sq;
			(*it).move_y = sy/sq;
		}
		else{
			for(list<ENEMYDATA>::iterator eit=Enemy.begin();eit!=Enemy.end();eit++){
				if(((*eit).img[0]!=gra_circle&&(*eit).img[0]!=gra_boss[2][21]) ||(*eit).b_atari==true){
					float sx = (*eit).x - (*it).x;
					float sy = (*eit).y - (*it).y;
					float sq = sqrt(sx*sx+sy*sy);
					(*it).move_x = sx/sq;
					(*it).move_y = sy/sq;
					break;
				}
			}
		}
	}
	else if(p==2){
		(*it).flash = 20;
		(*it).angle = 1.57;
	}
	else if(p==3){
		if((*it).x<20&&(*it).move_x<0){
			(*it).move_x *= -1;
		}
		if((*it).x>400&&(*it).move_x>0){
			(*it).move_x *= -1;
		}
	}
	
	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).angle = atan2((*it).move_y,(*it).move_x)+1.57;
	(*it).atari_x[0] = (*it).x - (*it).img_x/2;
	(*it).atari_x[1] = (*it).x + (*it).img_x/2;
	(*it).atari_y[0] = (*it).y - (*it).img_y/2;
	(*it).atari_y[1] = (*it).y + (*it).img_y/2;
	return;
}

void SBom_Load(){
	try{
		char fi[128];
		SetTransColor(0,0,0);
		wsprintf(fi , "data/img/shot/bomb/1.png");
		if( (gra_bomb = LoadGraph(fi)) == -1)	throw(fi);
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SBom_Reset(){
	Bomb.life = 0;
	Bomb.img = gra_bomb;
	GetGraphSize(Bomb.img,&Bomb.img_x,&Bomb.img_y);
	return;
}

void SBom_Draw(){
	if(Bomb.life==1){
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		SBom_Move();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Bomb.flash);
		if(loop_count==0)	DrawRotaGraphF(Bomb.x+shake_x, Bomb.y+shake_y, Bomb.large, Bomb.angle, Bomb.img, TRUE, FALSE);
		Bomb.count++;
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if(Boss.exist>=1&&Boss.b_muteki==true){
		int flash = 240;
		if(Boss.spell_num!=104){
			if(Bomb.count>140)	flash = 240-6*(Bomb.count-140);
		}
		else{
			if(Player.nodamage<70)	flash = 6*(Player.nodamage-30);
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD,flash);
		DrawCircle(Boss.x,Boss.y,60,GetColor(255,240,240),TRUE);
	}
	    
	return;
}

void SBom_Make(float x,float y){
	Bomb.x = x;
	Bomb.y = y;
	Bomb.count = 0;
	Bomb.angle = 0;
	Bomb.flash = 255;
	Bomb.life = 1;
	for(int i=0;i<8;i++){
		Bomb.i_hanyou[i] = 0;
		Bomb.d_hanyou[i] = 0;
	}
	if(SAVE.Chara==0){
		Bomb.atack = 30;
	}
	else{
		Bomb.atack = 50;
	}	
	for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
		(*it).pattern = 1;
	}
        Game.maxpoint -= 5000;
	int mp;
	switch(SAVE.Level){
		case 0:	mp = 10000;	break;
		case 1:	mp = 50000;	break;
		case 2:	mp = 100000;	break;
		case 3:	mp = 200000;	break;
		case 4:	mp = 500000;	break;
	}
	if(Game.maxpoint<mp)	Game.maxpoint = mp;
	return;
}

void SBom_Move(){
	int c = Bomb.count;
	if(c<10){
		Bomb.large = 0.2 * c;
	}
	else if(c<120){}
	else if(c<180){
		Bomb.flash -= 4.25;
	}
	else{
		Bomb.life = 0;
	}
	Bomb.y -= 1.0;
	Bomb.angle += 6;
	Boss.damage += Bomb.atack;
	return;
}

void SEn_Load(){
	try{
		char fi[128];
		SetTransColor(0,0,0);
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/dot/fairy/%d.png" , i+1);
			if( LoadDivGraph(fi,16,8,2,32,32,gra_fairy[i]) == -1)	throw(fi);
		}
		wsprintf(fi , "data/img/dot/fairy/4.png");
		if( LoadDivGraph(fi,8,4,2,64,64,gra_big_fairy) == -1)	throw(fi);
		SetTransColor(0,0,0);
		for(int i=0;i<3;i++){
			wsprintf(fi , "data/img/dot/kedama/%d.png" , i+1);
			if( (gra_kedama[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		SetTransColor(0,0,0);
		wsprintf(fi , "data/img/dot/crow/1.png");
		if( LoadDivGraph(fi,8,4,2,32,32,gra_crow) == -1)	throw(fi);
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SEn_Reset(){
	Enemy.clear();
	return;
}

void SEn_Main(){
	for(list<ENEMYDATA>::iterator it=Enemy.begin();it!=Enemy.end();it++){
		if(Game.skip==false){
			SEn_Move(it);
			SEn_Shot(it);
		}
		if((*it).x<-30-(*it).img_x/2 || (*it).x>480+(*it).img_x/2 || (*it).y<-30-(*it).img_y/2 || (*it).y>510+(*it).img_y/2){
			if((*it).b_atari==true&&(*it).img[0]!=gra_circle){
				it = Enemy.erase(it);
				it--;
				continue;
			}
		}
		if((*it).i_hanyou[7]==1){
			it = Enemy.erase(it);
			it--;
			continue;
		}
	}
	
	return;
}

void SEn_Draw(){
	for(list<ENEMYDATA>::iterator it=Enemy.begin();it!=Enemy.end();it++){
		if((*it).img[0]==gra_boss[2][21]){
			SetDrawBright(50,50,200);
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			if(loop_count==0){
				for(int i=0;i<3;i++){
					DrawRotaGraphF((*it).x+shake_x+10*cos(Radian((i+1)*(*it).count+60*i,TRUE)), (*it).y+shake_y+10*sin(Radian((i+1)*(*it).count+60*i,TRUE)), (*it).large, (*it).angle, (*it).img[(*it).img_num], TRUE, FALSE);
				}
			}
			SetDrawBright(255,255,255);
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			if((*it).i_hanyou[6]==1)	SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle, (*it).img[(*it).img_num], TRUE, FALSE);
		}
		if(Game.skip==false)	(*it).count++;
		if((*it).b_atari==true&&(*it).x>17&&(*it).y>13&&(*it).x<404&&(*it).y<461){
			for(list<P_SHOTDATA>::iterator pit=P_Shot.begin();pit!=P_Shot.end();pit++){
				if((*pit).atari_x[0]<(*it).atari_x[1] &&
				   (*pit).atari_x[1]>(*it).atari_x[0] &&
				   (*pit).atari_y[0]<(*it).atari_y[1] &&
				   (*pit).atari_y[1]>(*it).atari_y[0]){
					if((*it).img[0]!=gra_circle){
						(*it).life -= (*pit).atack;
						if((*pit).img!=gra_shot_marisa[1])	SEf_Make((*it).x,(*it).y,7);
						else if((*pit).count<=1)		SEf_Make((*it).x,(*it).y,7);
					}
					else{
						Boss.damage += (*pit).atack/2;
					}
					if((*pit).img!=gra_shot_marisa[1]){
						SSc_AddScore(10);
						pit = P_Shot.erase(pit);
						pit--;
						continue;
					}
					else if((*pit).count==3){
						SSc_AddScore(10);
					}
				}
			}
			if(Player.nodamage==0 && Player.miss==0 &&
			   Player.atari_x[0]<(*it).atari_x[1] &&
			   Player.atari_x[1]>(*it).atari_x[0] &&
			   Player.atari_y[0]<(*it).atari_y[1] &&
			   Player.atari_y[1]>(*it).atari_y[0] &&
			   (*it).img[0]!=gra_circle){
				SPlaySound(2);
				Player.miss = 8;
			}
			if(Bomb.life==1&&Bomb.count>=10){
				float sx = Bomb.x - (*it).x;
				float sy = Bomb.y - (*it).y;
				float sq = sqrt(sx*sx+sy*sy);
				if(sq<70+(*it).img_y/2){
					if((*it).img[0]!=gra_circle)	(*it).life -= Bomb.atack;
				}
			}
		}
		if((*it).life<=0){
			SPlaySound(12);
			SSc_AddScore(1000);
			SEn_Item(it);
			SEf_Make((*it).x,(*it).y,0);
			if((*it).shot_pattern==54){
				SPlaySound(10);
				for(int i=0;i<2;i++){
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0+1.0*i,gra_e_shot[5],10,0,10.0,10);
				}
			}
			it = Enemy.erase(it);
			it--;
			continue;
		}
		//DrawBox((*it).atari_x[0],(*it).atari_y[0],(*it).atari_x[1],(*it).atari_y[1],GetColor(255,255,255),TRUE);
	}
	
	return;
}

void SEn_Make(float x,float y,int img,int life,int m_pattern,int s_pattern,int i_pattern){
	ENEMYDATA P;
	P.x = x;
	P.y = y;
	for(int i=0;i<ATARI_NUM;i++){
		P.atari_x[i] = x;
		P.atari_y[i] = y;
	}
	if(img<3){
		for(int i=0;i<16;i++){
			P.img[i] = gra_fairy[img][i];
		}
	}
	else if(img==3){
		for(int i=0;i<8;i++){
			P.img[i] = gra_big_fairy[i];
		}
	}
	else if(img==4){
		for(int i=0;i<8;i++){
			P.img[i] = gra_crow[i];
		}
	}
	else if(img<8){
		P.img[0] = gra_kedama[img-5];
	}
	else if(img==8){
		P.img[0] = gra_circle;
	}
	P.life = life;
	P.move_pattern = m_pattern;
	P.shot_pattern = s_pattern;
	P.item_pattern = i_pattern;
	P.b_atari = true;
	P.count = 0;
	P.angle = 0;
	P.move_x = 0;
	P.move_y = 0;
	for(int i=0;i<2;i++){
		P.img_count[i] = 0;
	}
	P.flash = 250;
	GetGraphSize(P.img[0],&P.img_x,&P.img_y);
	P.large = 1.0;
	for(int i=0;i<HANYOU_NUM;i++){
		P.i_hanyou[i] = 0;
		P.d_hanyou[i] = 0;
	}
	
	Enemy.push_back(P);
	return;
}

void SEn_Move(list<ENEMYDATA>::iterator &it){
	int p = (*it).move_pattern;
	int c = (*it).count;
	
	if(p==0){//テスト
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 1.0;
		}
		if(c==180){
			if((*it).x<CENTER_X){
				(*it).move_x = cos(Radian(45,TRUE));
				(*it).move_y = sin(Radian(45,TRUE));
			}
			else{
				(*it).move_x = cos(Radian(135,TRUE));
				(*it).move_y = sin(Radian(135,TRUE));
			}
		}
	}
	else if(p==1){//カラス
		if(c==0){
			if((*it).x<CENTER_X)	(*it).move_x = 1;
			else			(*it).move_x = -1;
			(*it).move_y = 0;
			(*it).speed = 3.0;
		}
	}
	else if(p==2){//1-1左
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 7.0 + 0.1*get_rand(20);
		}
		else if(c<15){}
		else if(c<30){
			if(c==15)	(*it).d_hanyou[1] = (*it).speed / 15;
			(*it).speed -= (*it).d_hanyou[1];
		}
		else if(c==30){
			(*it).speed = 0;
			(*it).d_hanyou[0] = 45;
		}
		else{
			(*it).move_x = cos(Radian((*it).d_hanyou[0],TRUE));
			(*it).move_y = sin(Radian((*it).d_hanyou[0],TRUE));
			(*it).d_hanyou[0] -= 2;
			if((*it).d_hanyou[0]<-80)	(*it).d_hanyou[0] = -80;
			(*it).speed += 0.05;
			if((*it).speed>1.5)	(*it).speed = 1.5;
		}
	}
	else if(p==3){//1-1右
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 7.0 + 0.1*get_rand(20);
		}
		else if(c<15){}
		else if(c<30){
			if(c==15)	(*it).d_hanyou[1] = (*it).speed / 15;
			(*it).speed -= (*it).d_hanyou[1];
		}
		else if(c==30){
			(*it).speed = 0;
			(*it).d_hanyou[0] = 135;
		}
		else{
			(*it).move_x = cos(Radian((*it).d_hanyou[0],TRUE));
			(*it).move_y = sin(Radian((*it).d_hanyou[0],TRUE));
			(*it).d_hanyou[0] += 2;
			if((*it).d_hanyou[0]>260)	(*it).d_hanyou[0] = 260;
			(*it).speed += 0.05;
			if((*it).speed>1.5)	(*it).speed = 1.5;
		}
	}
	else if(p==4){//1-2兼1-5
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 5.0;
			if(Game.stage==4&&Game.count>400)	(*it).speed = 7.0;
			(*it).d_hanyou[0] = (*it).speed / 40.0;
		}
		else if(c<=40)	(*it).speed -= (*it).d_hanyou[0];
		else if(c<180){}
		else if(c==180){
			(*it).speed = 1.5; 
			if((*it).life>200)	(*it).life = 200; 
		}
	}
	else if(p==5){//1-3左
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 5.0 + 0.1*get_rand(10);
		}
		else if(c<30){}
		else if(c<60){
			if(c==30)	(*it).d_hanyou[1] = (*it).speed / 30;
			(*it).speed -= (*it).d_hanyou[1];
		}
		else if(c==60){
			(*it).speed = 0;
			(*it).d_hanyou[0] = 45;
		}
		else{
			(*it).move_x = cos(Radian((*it).d_hanyou[0],TRUE));
			(*it).move_y = sin(Radian((*it).d_hanyou[0],TRUE));
			(*it).d_hanyou[0] -= 1;
			if((*it).d_hanyou[0]<-80)	(*it).d_hanyou[0] = -80;
			(*it).speed += 0.05;
			if((*it).speed>1.5)	(*it).speed = 1.5;
		}
	}
	else if(p==6){//1-3右
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 5.0 + 0.1*get_rand(10);
		}
		else if(c<30){}
		else if(c<60){
			if(c==30)	(*it).d_hanyou[1] = (*it).speed / 30;
			(*it).speed -= (*it).d_hanyou[1];
		}
		else if(c==60){
			(*it).speed = 0;
			(*it).d_hanyou[0] = 135;
		}
		else{
			(*it).move_x = cos(Radian((*it).d_hanyou[0],TRUE));
			(*it).move_y = sin(Radian((*it).d_hanyou[0],TRUE));
			(*it).d_hanyou[0] += 1;
			if((*it).d_hanyou[0]>260)	(*it).d_hanyou[0] = 260;
			(*it).speed += 0.05;
			if((*it).speed>1.5)	(*it).speed = 1.5;
		}
	}
	else if(p==7){//1-4
		if(c==0)	(*it).speed = 1.0;
		if(c<40){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			(*it).move_x = sx/sq;
			(*it).move_y = sy/sq;
		}
		if((*it).speed<2.5)	(*it).speed += 0.05;
	}
	else if(p==8){//1-6
		(*it).speed = 2.0;
		if(c==0){
			float sx = CENTER_X - (*it).x;
			float sy = CENTER_Y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			(*it).move_x = sx/sq;
			(*it).move_y = sy/sq;
		}
	}
	else if(p==9||p==10){//2-1
		if(c==0)	(*it).i_hanyou[0] = get_rand(100);
		(*it).speed = 6.0;
		if(p==9){
			if(c<50){
				(*it).move_x = cos(Radian(55,TRUE));
				(*it).move_y = sin(Radian(55,TRUE));
			}
			else if(c<120){
				float angle = atan2((*it).move_y,(*it).move_x);
				(*it).move_x = cos(angle-Radian(4.0,TRUE));
				(*it).move_y = sin(angle-Radian(4.0,TRUE));
			}
		}
		else{
			if(c<50){
				(*it).move_x = cos(Radian(125,TRUE));
				(*it).move_y = sin(Radian(125,TRUE));
			}
			else if(c<120){
				float angle = atan2((*it).move_y,(*it).move_x);
				(*it).move_x = cos(angle+Radian(4.0,TRUE));
				(*it).move_y = sin(angle+Radian(4.0,TRUE));
			}
		}
		(*it).i_hanyou[0] ++;
	}
	else if(p==11){//2-2
		if(c==0)	(*it).speed = 12.5;
		if(c<60){
			(*it).speed -= 0.2;
			(*it).move_x = cos(Radian(270,TRUE));
			(*it).move_y = sin(Radian(270,TRUE));
		}
		if(c<90){
			(*it).life = 100;
		}
		if(c>=120&&c<170){
			if(c==120){
				if((*it).x<CENTER_X)	(*it).i_hanyou[0] = 0;
				else			(*it).i_hanyou[0] = 1;
				(*it).move_y = 1;
			}
			(*it).speed += 0.1;
			float angle = atan2((*it).move_y,(*it).move_x);
			if((*it).i_hanyou[0]==0)	angle -= Radian(1.0,TRUE);
			else				angle += Radian(1.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==12){//2-3
		if(c==0){
			(*it).speed = 5.0;
			(*it).d_hanyou[0] = 80+get_rand(20);
			(*it).move_x = cos(Radian((*it).d_hanyou[0],TRUE));
			(*it).move_y = sin(Radian((*it).d_hanyou[0],TRUE));
		}
		if(c>=40&&c<70)	(*it).speed -= 0.15;
		if(c>=130){
			(*it).move_x = cos(Radian(270+30*sin(Radian(5*(c-130),TRUE)),TRUE));
			(*it).move_y = sin(Radian(270+30*sin(Radian(5*(c-130),TRUE)),TRUE));
			if((*it).speed<5.0)	(*it).speed += 0.1;
		}
	}
	else if(p==13||p==14){//2-4
		if(c==0)	(*it).i_hanyou[0] = get_rand(100);
		(*it).speed = 6.0;
		if(p==13){
			if(c<50){
				(*it).move_x = cos(Radian(0,TRUE));
				(*it).move_y = sin(Radian(0,TRUE));
			}
			else if(c<120){
				float angle = atan2((*it).move_y,(*it).move_x);
				(*it).move_x = cos(angle-Radian(4.0,TRUE));
				(*it).move_y = sin(angle-Radian(4.0,TRUE));
			}
		}
		else{
			if(c<50){
				(*it).move_x = cos(Radian(180,TRUE));
				(*it).move_y = sin(Radian(180,TRUE));
			}
			else if(c<120){
				float angle = atan2((*it).move_y,(*it).move_x);
				(*it).move_x = cos(angle+Radian(4.0,TRUE));
				(*it).move_y = sin(angle+Radian(4.0,TRUE));
			}
		}
		(*it).i_hanyou[0] ++;
	}
	else if(p==15){//2-5
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 7.0;
			(*it).d_hanyou[0] = 0.14;
		}
		else if(c<=50){
			(*it).speed -= (*it).d_hanyou[0];
			(*it).life = 5000;
		}
		else if(c<310){
			(*it).speed = 0;
		}
		else if(c==310){
			(*it).speed = 2.5;
			(*it).move_x = 0;
			(*it).move_y = -1; 
			if((*it).life>200)	(*it).life = 200; 
		}
	}
	else if(p==16){//2-ラスト毛玉
		if(c==0){
			float angle = Radian(80+get_rand(20),TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = 7.0;
		}
	}
	else if(p==17){//3-1
		(*it).speed = 6.5;
		if(c==0){
			float sx = CENTER_X - (*it).x;
			float sy = CENTER_Y - (*it).y;
			float angle = atan2(sy,sx);
			angle += Radian(-20+get_rand(40),TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==18){//3-2
		if(c==0){
			(*it).speed = 0;
			(*it).move_x = 0;
			(*it).move_y = 0;
			SEf_Make((*it).x,(*it).y,5);
			(*it).b_atari = false;
			(*it).flash = 0;
			(*it).life = 1000;
		}
		if(c<15){}
		else if(c==15){
			(*it).life = 400;
			(*it).b_atari = true;
			(*it).flash = 255;
			(*it).d_hanyou[0] = 90;
			if((*it).x<CENTER_X)	(*it).d_hanyou[1] = -2.0;
			else			(*it).d_hanyou[1] = 2.0;
		}
		else if(c<75){}
		else if(c<135){
			(*it).speed += 0.05;
			(*it).d_hanyou[0] += (*it).d_hanyou[1];
			float angle = Radian((*it).d_hanyou[0],TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==19){//3-3(文早回し)
		if(c==0){
			(*it).speed = 0;
			(*it).move_x = 0;
			(*it).move_y = 0;
			SEf_Make((*it).x,(*it).y,5);
			(*it).b_atari = false;
			(*it).flash = 0;
			(*it).life = 1000;
		}
		if(c<15){}
		else if(c==15){
			(*it).life = 120;
			(*it).b_atari = true;
			(*it).flash = 255;
			switch(SAVE.Level){
				case 0:	(*it).d_hanyou[0] = 3.0/60.0;	break;
				case 1:	(*it).d_hanyou[0] = 4.0/60.0;	break;
				case 2:	(*it).d_hanyou[0] = 6.0/60.0;	break;
				case 3:	(*it).d_hanyou[0] = 6.0/60.0;	break;
			}
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			(*it).move_x = sx / sq;
			(*it).move_y = sy / sq;
		}
		else if(c<75){
			(*it).speed += (*it).d_hanyou[0];
		}
	}
	else if(p==20||p==21){//紫登場エフェクト
		if(c==0){
			(*it).d_hanyou[0] = (*it).life;
			(*it).flash = 150;
			(*it).b_atari = false;
			(*it).speed = 0;
		}
		float length;
		if(c<60)	length = 4*(60-c);
		else		length = 50;
		(*it).x = Boss.x + length*cos(Radian((*it).d_hanyou[0],TRUE));
		(*it).y = Boss.y + length*sin(Radian((*it).d_hanyou[0],TRUE));
		if(p==20)	(*it).d_hanyou[0] += 8;
		else if(p==21)	(*it).d_hanyou[0] -= 8;
		if(c==60){
			SEf_Make((*it).x,(*it).y,6,Game.gra_t_effect);
			(*it).i_hanyou[7] = 1;
		}
	}
	else if(p==22){//紫通常２
		if(c==0){
			(*it).d_hanyou[0] = (*it).life;
			(*it).flash = 150;
			(*it).b_atari = false;
			(*it).speed = 0;
		}
		float length;
		if(c<50)	length = 1.5*c;
		else		length = 75;
		(*it).x = Boss.x + length*cos(Radian((*it).d_hanyou[0],TRUE));
		(*it).y = Boss.y + length*sin(Radian((*it).d_hanyou[0],TRUE));
		(*it).d_hanyou[0] += 1;
	}
	else if(p==23){//３面紫通常３
		(*it).speed = 0;
		(*it).flash = 150;
		float d;
		if(Game.stage<=3){
			if(c<50)	d = 2.0*c;
			else		d = 100;
		}
		else{
			if(c<50)	d = 2.5*c;
			else		d = 125;
		}		
		switch((*it).life){
			case 1:	(*it).x = Boss.x + d*sin(1.5*Radian(3*c,TRUE));
				(*it).y = Boss.y + d*sin(Radian(3*c,TRUE));
				break;
			case 2:	(*it).x = Boss.x + d*sin(-1.5*Radian(3*c,TRUE));
				(*it).y = Boss.y + d*sin(Radian(-3*c,TRUE));
				break;
			case 3:	(*it).x = Boss.x + d*sin(1.2*Radian(3*c,TRUE));
				(*it).y = Boss.y + d*sin(Radian(3*c,TRUE));
				break;
			case 4:	(*it).x = Boss.x + d*sin(-1.2*Radian(3*c,TRUE));
				(*it).y = Boss.y + d*sin(Radian(-3*c,TRUE));
				break;
		}
	}
	else if(p==24){//戯符「神々のアジャラ空間」
		(*it).speed = 0;
		(*it).flash = 150;
	}
	else if(p==25){//６面紫通常２
		if(c==0){
			(*it).d_hanyou[0] = (*it).life;
			(*it).flash = 150;
			(*it).b_atari = false;
			(*it).speed = 0;
		}
		float length;
		if(c<50)	length = 2.0*c;
		else		length = 100;
		(*it).x = Boss.x + length*cos(Radian((*it).d_hanyou[0],TRUE));
		(*it).y = Boss.y + length*sin(Radian((*it).d_hanyou[0],TRUE));
		(*it).d_hanyou[0] += 1;
	}
	else if(p==26){//結界「二重光陰結界」
		if(c==0){
			(*it).flash = 0;
			(*it).b_atari = false;
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float an = atan2(sy,sx) + Radian(-20+get_rand(40),TRUE);	
			(*it).move_x = cos(an);
			(*it).move_y = sin(an);
			(*it).speed = 5.0;
		}
		if((*it).y<500 && c%5==0){
			SPlaySound(8);
			if(c%10==0){
				float angle = -30+get_rand(60);
				SLas_Make((*it).x,(*it).y,angle,10.0,gra_laser[0],60,7,0);
			}
			else{
				float angle = 150+get_rand(60);
				SLas_Make((*it).x,(*it).y,angle,10.0,gra_laser[1],60,7,0);
			}
		}
		if((*it).y>=500)	(*it).i_hanyou[7] = 1;
	}
	else if(p==27){//戯符「メンフェンティス降臨」
		(*it).b_atari = false;
		(*it).img[0] = gra_boss[2][21];
		(*it).img_num = 0;
		(*it).flash = 200;
		int cp = c % 210;
		if(cp<80){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float angle = 0;
			if(!(Player.x==(*it).x&&Player.y==(*it).y)) angle = atan2(sy,sx);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
		if(cp<50)	(*it).speed = 0.05*cp;
		if(cp>=160)	(*it).speed = 0.05*(210-cp);
	}
	else if(p>=28 && p<=33){//禁忌「真弾幕結界 -久遠素懐-」
		(*it).b_atari = false;
		(*it).img_num = 0;
		(*it).flash = 150;
		(*it).speed = 0;
		if(p>=28 && p<=29){
			if(c<120)	(*it).d_hanyou[0] = 1.75*c;
			else		(*it).d_hanyou[0] = 210.0;
			if(p==28)	(*it).d_hanyou[1] = 1.0*c;
			else if(p==29)	(*it).d_hanyou[1] = 1.0*c+180.0;
		}
		if(p>=30 && p<=31){
			if(c<120)	(*it).d_hanyou[0] = 1.6*c;
			else		(*it).d_hanyou[0] = 192.0;
			if(p==30)	(*it).d_hanyou[1] = -1.0*c;
			else if(p==31)	(*it).d_hanyou[1] = -1.0*c+180.0;
		}
		if(p>=32 && p<=33){
			if(c<120)	(*it).d_hanyou[0] = 1.75*c;
			else		(*it).d_hanyou[0] = 210.0;
			if(p==32)	(*it).d_hanyou[1] = 1.5*c;
			else if(p==33)	(*it).d_hanyou[1] = 1.5*c+180.0;
		}
		if(c==780){
			(*it).i_hanyou[7] = 1;
			for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();++it){
				(*it).i_hanyou[2] = 1;
			}
		}
		(*it).x = Boss.x+(*it).d_hanyou[0]*cos(Radian((*it).d_hanyou[1],TRUE));
		(*it).y = Boss.y+(*it).d_hanyou[0]*sin(Radian((*it).d_hanyou[1],TRUE));
	}
	else if(p>=34 && p<=37){//「終焉と幻想の境界」
		(*it).b_atari = false;
		(*it).img_num = 0;
		(*it).flash = 0;
		(*it).speed = 3.0;
		if(p==34){
			(*it).move_x = cos(Radian(-20,TRUE));
			(*it).move_y = sin(Radian(-20,TRUE));
		}
		else if(p==35){
			(*it).move_x = cos(Radian(200,TRUE));
			(*it).move_y = sin(Radian(200,TRUE));
		}
		else if(p==36){
			(*it).move_x = cos(Radian(50,TRUE));
			(*it).move_y = sin(Radian(50,TRUE));
		}
		else if(p==37){
			(*it).move_x = cos(Radian(130,TRUE));
			(*it).move_y = sin(Radian(130,TRUE));
		}
	}
	else if(p==38){//Ex-2
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 9.0;
			if(Game.stage==4&&Game.count>400)	(*it).speed = 7.0;
			(*it).d_hanyou[0] = (*it).speed / 40.0;
		}
		else if(c<=40)	(*it).speed -= (*it).d_hanyou[0];
		else if(c<180){}
		else if(c==180){
			(*it).speed = 1.5; 
			if((*it).life>200)	(*it).life = 200; 
		}
	}
	else if(p==39){//Ex-3
		if(c==0){
			if((*it).x<CENTER_X)	(*it).move_x = 1;
			else			(*it).move_x = -1;
			(*it).move_y = 0;
			(*it).speed = 2.0;
		}
	}
	else if(p==40){//Ex-6
		if(c%90==0){
			if((*it).x<CENTER_X)	(*it).move_x = 6.6;
			else			(*it).move_x = -6.6;
			(*it).move_y = 2.4;
			(*it).speed = 1.0;
		}
		else if(c%90<60){
			if((*it).move_x>0)	(*it).move_x -= 0.11;
			else			(*it).move_x += 0.11;
			(*it).move_y -= 0.04;
		}
		else{
			(*it).move_x = 0;
			(*it).move_y = 0;
		}
	}
	else if(p==41){//Ex-8
		if(c==0){
			(*it).move_x = 0;
			(*it).move_y = 1;
			(*it).speed = 10.0;
			if(Game.stage==4&&Game.count>400)	(*it).speed = 7.0;
			(*it).d_hanyou[0] = (*it).speed / 40.0;
		}
		else if(c<=40)	(*it).speed -= (*it).d_hanyou[0];
		else if(c<180){}
		else if(c==420){
			(*it).speed = -1.5; 
		}
	}
	else if(p>=42 && p<=50){//幻影「十王裁判」
		if(c==0){
			(*it).d_hanyou[0] = 40.0*(p-42);//位置角度
			(*it).d_hanyou[1] = 0.0;//x半径
			(*it).d_hanyou[2] = 0.0;//y半径
			(*it).b_atari = false;
			(*it).img_num = 0;
			(*it).flash = 150;
			(*it).speed = 0.0;
		}
		if(c<100){
			(*it).d_hanyou[1] += 1.6;
			(*it).d_hanyou[2] += 2.0;
		}
		(*it).x = CENTER_X+(*it).d_hanyou[1]*cos(Radian((*it).d_hanyou[0],TRUE));
		(*it).y = CENTER_Y+(*it).d_hanyou[2]*sin(Radian((*it).d_hanyou[0],TRUE));
		(*it).d_hanyou[0] += 1.0;
	}
	else if(p>=51 && p<=54){//夢終「エンドオブジャッジメント」
		(*it).b_atari = false;
		(*it).img_num = 0;
		(*it).flash = 0;
		(*it).speed = 3.0;
		if(p==54){
			(*it).move_x = cos(Radian(-20,TRUE));
			(*it).move_y = sin(Radian(-20,TRUE));
		}
		else if(p==53){
			(*it).move_x = cos(Radian(200,TRUE));
			(*it).move_y = sin(Radian(200,TRUE));
		}
		else if(p==52){
			(*it).move_x = cos(Radian(40,TRUE));
			(*it).move_y = sin(Radian(40,TRUE));
		}
		else if(p==51){
			(*it).move_x = cos(Radian(140,TRUE));
			(*it).move_y = sin(Radian(140,TRUE));
		}
	}
	if((*it).img[0]==gra_fairy[0][0] || (*it).img[0]==gra_fairy[1][0] || (*it).img[0]==gra_fairy[2][0]){
		if((*it).move_x<=-0.2){
			if((*it).img_count[0]<5){
				(*it).img_num = 8;
			}
			else{
				(*it).img_num = 9 + ((*it).img_count[0]/5)%3;
			}
			(*it).img_count[0]++;
		}
		else{
			(*it).img_count[0] = 0;
		}
		if(0.2<=(*it).move_x){
			if((*it).img_count[1]<5){
				(*it).img_num = 12;
			}
			else{
				(*it).img_num = 13 + ((*it).img_count[1]/5)%3;
			}
			(*it).img_count[1]++;
		}
		else{
			(*it).img_count[1] = 0;
		}
		if(-0.2<(*it).move_x&&(*it).move_x<0.2){
			(*it).img_num = ((*it).count/5)%3;
		}
	}
	else if((*it).img[0]==gra_big_fairy[0]){
		if((*it).move_x<=-0.2){
			if((*it).img_count[0]<5){
				(*it).img_num = 6;
			}
			else{
				(*it).img_num = 7;
			}
			(*it).img_count[0]++;
		}
		else{
			(*it).img_count[0] = 0;
		}
		if(0.2<=(*it).move_x){
			if((*it).img_count[1]<5){
				(*it).img_num = 4;
			}
			else{
				(*it).img_num = 5;
			}
			(*it).img_count[1]++;
		}
		else{
			(*it).img_count[1] = 0;
		}
		if(-0.2<(*it).move_x&&(*it).move_x<0.2){
			(*it).img_num = ((*it).count/5)%3;
		}
	}
	else if((*it).img[0]==gra_crow[0]){
		if((*it).move_x<=0){
			(*it).img_num = ((*it).count/5)%4;
			if((*it).img_num>=2)	(*it).img_num += 2;
		}
		else{
			(*it).img_num = 2+((*it).count/5)%4;
			if((*it).img_num>=4)	(*it).img_num += 2;
		}
	}
	else if((*it).img[0]==gra_kedama[0]||(*it).img[0]==gra_kedama[1]||(*it).img[0]==gra_kedama[2]){
		(*it).angle += Radian(12,TRUE);
		(*it).img_num = 0;
	}
	else if((*it).img[0]==gra_circle){
		(*it).angle += Radian(12,TRUE);
		(*it).img_num = 0;
		if(p!=24)	(*it).b_atari = false;
	}
	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).atari_x[0] = (*it).x - (*it).img_x/6;
	(*it).atari_x[1] = (*it).x + (*it).img_x/6;
	(*it).atari_y[0] = (*it).y - (*it).img_y/6;
	(*it).atari_y[1] = (*it).y + (*it).img_y/6;
	return;
}

void SEn_Shot(list<ENEMYDATA>::iterator &it){
	if(debug_nobullet==1)	return;
	int p = (*it).shot_pattern;
	int c = (*it).count;
	
	if(p==0){//テスト
		if(c==0)	(*it).i_hanyou[0] = get_rand(29);
		if((c+(*it).i_hanyou[0])%30==15){
			SPlaySound(10);
			SEs_NWay((*it).x,(*it).y,0.0,1,2.5,gra_e_shot[0],0,0,5.0,10);
		}
	}
	else if(p==1){//テスト
		if(c>30&&c%2==0&&c<90){
			SPlaySound(9);
			SEs_NWay((*it).x,(*it).y,0.0,1,1.5+0.1*get_rand(15),gra_e_shot[5],0,-20+get_rand(40),5.0,10);
		}
	}
	else if(p==2){//テスト
		if(c==0)	(*it).i_hanyou[0] = get_rand(119);
		if((c+(*it).i_hanyou[0])%120==10){
			SPlaySound(11);
			SEs_Make((*it).x,(*it).y,90.0,2.5,gra_e_shot[28],10,5.0,10);
		}
	}
	else if(p==3){//1-1兼1-3
		switch(SAVE.Level){
			case 1:
				if((*it).move_pattern!=5&&(*it).move_pattern!=6){
					if(c>40&&c%131==61&&(*it).y<CENTER_Y+50){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[5],10,0);
					}
				}
				break;
			case 2:
				if(c>30&&c%97==51&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,3.0,gra_e_shot[5],10,0);
				}
				break;
			case 3:
				if(c>20&&c%67==41&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,3.5,gra_e_shot[5],10,0);
				}
				break;
		}
	}
	else if(p==4){//1-2
		switch(SAVE.Level){
			case 0:
				if(c>40&&c%4==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<2;i++){
						SEs_Make((*it).x,(*it).y,30*((c-40)/4)+180*i,2.0,gra_e_shot[4],2,7.0);
					}
				}
				break;
			case 1:
				if(c>40&&c%4==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<4;i++){
						SEs_Make((*it).x,(*it).y,15*((c-40)/4)+90*i,2.5,gra_e_shot[4],2,7.0);
					}
				}
				break;
			case 2:
				if(c>40&&c%2==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<5;i++){
						SEs_Make((*it).x,(*it).y,10*((c-40)/2)+72*i,3.0,gra_e_shot[4],2,7.0);
					}
				}
				break;
			case 3:
				if(c>40&&c%2==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<6;i++){
						SEs_Make((*it).x,(*it).y,14*((c-40)/2)+60*i,4.5,gra_e_shot[4],2,7.0,0);
					}
				}
				break;
		}
	}
	else if(p==5){//1-5
		switch(SAVE.Level){
			case 0:
				if(c>=40&&c<120){
					if(c%30==0){
						SPlaySound(10);
						int ra = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make((*it).x,(*it).y,ra+36*i,2.5,gra_e_shot[14],0,6.0,0,1);
						}
					}
				}
				break;
			case 1:
				if(c>=40&&c<120){
					if(c%30==0){
						SPlaySound(10);
						int ra = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make((*it).x,(*it).y,ra+36*i,2.5,gra_e_shot[14],0,6.0,0,1);
						}
					}
				}
				break;
			case 2:
				if(c>=40&&c<120){
					if(c%20==0){
						SPlaySound(10);
						int ra = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make((*it).x,(*it).y,ra+36*i,3.5,gra_e_shot[14],0,6.0,0,1);
						}
					}
					if(c%50==2){
						int ra = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make((*it).x,(*it).y,ra+12*i,3.0,gra_e_shot[6],10,10.0,5);
						}
					}
				}
				break;
			case 3:
				if(c>=40&&c<120){
					if(c%10==0){
						SPlaySound(10);
						int ra = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make((*it).x,(*it).y,ra+36*i,5.5,gra_e_shot[14],0,6.0,0,1);
						}
					}
					if(c%20==2){
						int ra = get_rand(7);
						for(int i=0;i<45;i++){
							SEs_Make((*it).x,(*it).y,ra+8*i,4.5,gra_e_shot[6],10,10.0,5);
						}
					}
				}
				break;
		}
	}
	else if(p==6||p==7){//1-6 加速弾ばら撒き
		switch(SAVE.Level){
			case 0:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==6){
						int angle = c*7;
						for(int i=0;i<1;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,4.0,gra_e_shot[14],30,0.0,0,2);
						}
					}
					else{
						int angle = c*7;
						for(int i=0;i<1;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,4.0,gra_e_shot[15],30,0.0,0,2);
						}
					}
				}
				break;
			case 1:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==6){
						int angle = c*5;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,4.0,gra_e_shot[14],30,0.0,0,2);
						}
					}
					else{
						int angle = c*5;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,4.0,gra_e_shot[15],30,0.0,0,2);
						}
					}
				}
				break;
			case 2:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==6){
						int angle = c*5;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x,(*it).y,angle+90*i,4.0,gra_e_shot[14],30,0.0,0,2);
						}
					}
					else{
						int angle = c*5;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x,(*it).y,angle+90*i,4.0,gra_e_shot[15],30,0.0,0,2);
						}
					}
				}
				break;
			case 3:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==6){
						int angle = c*5;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x,(*it).y,angle+72*i,4.0,gra_e_shot[14],30,0.0,0,2);
						}
					}
					else{
						int angle = c*5;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x,(*it).y,angle+72*i,4.0,gra_e_shot[15],30,0.0,0,2);
						}
					}
				}
				break;
		}
	}	
	else if(p==8){//1-7
		switch(SAVE.Level){
			case 0:
				if(c>30&&c%107==51&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,20.0,1,2.0,gra_e_shot[5],10,0);
				}
				break;
			case 1:
				if(c>30&&c%107==61&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,50.0,1,2.0,gra_e_shot[5],10,0);
				}
				break;
			case 2:
				if(c>30&&c%107==51&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						SEs_NWay((*it).x,(*it).y,25.0,1,4.0-0.5*i,gra_e_shot[5],10,0);
					}
				}
				break;
			case 3:
				if(c>20&&c%77==41&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						SEs_NWay((*it).x,(*it).y,20.0,3,5.0-0.5*i,gra_e_shot[5],10,0);
					}
				}
				break;
		}
	}	
	else if(p==9){//2-1
		c = c + (*it).i_hanyou[0];
		switch(SAVE.Level){
			case 0:
				break;
			case 1:
				if(c==150&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						SEs_NWay((*it).x,(*it).y,0.0,1,1.5-0.2*i,gra_e_shot[5],10,1.0*i);
						SEs_NWay((*it).x,(*it).y,0.0,1,1.5-0.2*i,gra_e_shot[5],10,-1.5*i);
					}
				}
				break;
			case 2:
				if(c%100==0&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					for(int i=0;i<5;i++){
						SEs_NWay((*it).x,(*it).y,0.0,1,3.0-0.2*i,gra_e_shot[5],10,1.0*i);
						SEs_NWay((*it).x,(*it).y,0.0,1,3.0-0.2*i,gra_e_shot[5],10,-1.5*i);
					}
				}
				break;
			case 3:
				if(c%100==0&&(*it).y<CENTER_Y+50){
					SPlaySound(10);
					for(int i=0;i<5;i++){
						SEs_NWay((*it).x,(*it).y,120.0,3,5.0-0.2*i,gra_e_shot[5],10,1.0*i);
						SEs_NWay((*it).x,(*it).y,120.0,3,5.0-0.2*i,gra_e_shot[5],10,-1.5*i);
					}
				}
				break;
		}
	}	
	else if(p==10){//2-2
		switch(SAVE.Level){
			case 0:
				if(c>50){
					if(c<80){
						if(c%10==0){
							SPlaySound(10);
							for(int i=0;i<4;i++){
								SEs_Make((*it).x,(*it).y,90+90*i,3.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
					else{
						if(c%15==0){
							SPlaySound(10);
							for(int i=0;i<1;i++){
								SEs_Make((*it).x,(*it).y,90,2.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
			case 1:
				if(c>50){
					if(c<80){
						if(c%10==0){
							SPlaySound(10);
							for(int i=0;i<4;i++){
								SEs_Make((*it).x,(*it).y,90+90*i,3.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
					else{
						if(c%15==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make((*it).x,(*it).y,90*i,2.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
			case 2:
				if(c>50){
					if(c<80){
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<4;i++){
								SEs_Make((*it).x,(*it).y,90+90*i,4.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
					else{
						if(c%20==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make((*it).x,(*it).y,90*i+10*(c-80)/10,3.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
			case 3:
				if(c>50){
					if(c<80){
						if(c%1==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								SEs_Make((*it).x,(*it).y,90+60*i,7.0,gra_e_shot[0],10);
							}	
						}
					}
					else{
						if(c%10==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make((*it).x,(*it).y,90*i+10*(c-80)/10,3.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
		}
	}
	else if(p==11){//2-5
		switch(SAVE.Level){
			case 0:
				if(c>=60&&(*it).speed==0){
					if(c%20==0){
						SPlaySound(10);
						float angle = 25*c/20;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+90*i,TRUE)),(*it).y+70*sin(Radian(angle+90*i,TRUE)),angle+90*i+170,1.5,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 1:
				if(c>=60&&(*it).speed==0){
					if(c%10==0){
						SPlaySound(10);
						float angle = -25*c/10;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,2.0,gra_e_shot[9],10,0,0.0,0,i%2);
						}	
					}
					if(c%20==0){
						float angle = 20*c/20;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+90*i,TRUE)),(*it).y+70*sin(Radian(angle+90*i,TRUE)),angle+90*i+170,1.5,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 2:
				if(c>=60&&(*it).speed==0){
					if(c%7==0){
						SPlaySound(10);
						float angle = -25*c/7;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,2.0,gra_e_shot[9],10,0,0.0,0,i%2);
						}	
					}
					if(c%10==0){
						float angle = 20*c/10;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+72*i,TRUE)),(*it).y+70*sin(Radian(angle+72*i,TRUE)),angle+72*i+170,1.5,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 3:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = -13*c/3;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,2.5,gra_e_shot[9],10,0,0.0,0,i%3);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+60*i,TRUE)),(*it).y+70*sin(Radian(angle+60*i,TRUE)),angle+60*i+170,1.5,gra_e_shot[8],10);
						}	
					}
				}
				break;
		}
	}
	else if(p==12){//2-6
		switch(SAVE.Level){
			case 0:
				if(c>=60&&(*it).speed==0){
					if(c%20==0){
						SPlaySound(10);
						float angle = 25*c/20;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+90*i,TRUE)),(*it).y+100*sin(Radian(angle+90*i,TRUE)),angle+90*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 1:
				if(c>=60&&(*it).speed==0){
					if(c%10==0){
						SPlaySound(10);
						float angle = -25*c/10;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,2.0,gra_e_shot[9],10,0,0.0,0,i%2);
						}	
					}
					if(c%20==0){
						float angle = 20*c/20;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+90*i,TRUE)),(*it).y+100*sin(Radian(angle+90*i,TRUE)),angle+90*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 2:
				if(c>=60&&(*it).speed==0){
					if(c%7==0){
						SPlaySound(10);
						float angle = -25*c/7;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,2.0,gra_e_shot[9],10,0,0.0,0,i%2);
						}	
					}
					if(c%10==0){
						float angle = 20*c/10;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+72*i,TRUE)),(*it).y+100*sin(Radian(angle+72*i,TRUE)),angle+72*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 3:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = -10*c/3;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,2.5,gra_e_shot[9],10,0,0.0,0,i%3);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+60*i,TRUE)),(*it).y+100*sin(Radian(angle+60*i,TRUE)),angle+60*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
		}
	}
	else if(p==13){//2-6
		switch(SAVE.Level){
			case 0:
				if(c>=60&&(*it).speed==0){
					if(c%20==0){
						SPlaySound(10);
						float angle = 25*c/20;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+140*cos(Radian(angle+60*i,TRUE)),(*it).y+140*sin(Radian(angle+60*i,TRUE)),angle+60*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 1:
				if(c>=60&&(*it).speed==0){
					if(c%10==0){
						SPlaySound(10);
						float angle = 25*c/10;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+180*i,TRUE)),(*it).y+100*sin(Radian(angle+180*i,TRUE)),angle+180*i+160,2.0,gra_e_shot[9],10);
						}	
					}
					if(c%20==0){
						float angle = 20*c/20;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+140*cos(Radian(angle+60*i,TRUE)),(*it).y+140*sin(Radian(angle+60*i,TRUE)),angle+60*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 2:
				if(c>=60&&(*it).speed==0){
					if(c%7==0){
						SPlaySound(10);
						float angle = 25*c/7;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+120*i,TRUE)),(*it).y+100*sin(Radian(angle+120*i,TRUE)),angle+120*i+160,2.0,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 20*c/10;
						for(int i=0;i<8;i++){
							SEs_Make((*it).x+140*cos(Radian(angle+45*i,TRUE)),(*it).y+140*sin(Radian(angle+45*i,TRUE)),angle+45*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 3:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = 10*c/3;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+90*i,TRUE)),(*it).y+100*sin(Radian(angle+90*i,TRUE)),angle+90*i+160,2.0,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<10;i++){
							SEs_Make((*it).x+140*cos(Radian(angle+36*i,TRUE)),(*it).y+140*sin(Radian(angle+36*i,TRUE)),angle+36*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
		}
	}
	else if(p==14){//2-7カラス
		switch(SAVE.Level){
			case 0:
				break;
			case 1:
				if(c==0)	(*it).i_hanyou[0] = get_rand(180);
				if(((*it).i_hanyou[0]+c)%180==90){
					SPlaySound(11);
					float angle = 240+get_rand(60);
					SEs_Make((*it).x,(*it).y,angle,2.0,gra_e_shot[6],10,0.0,0,6);
				}
				break;
			case 2:
				if(c==0)	(*it).i_hanyou[0] = get_rand(100);
				if(((*it).i_hanyou[0]+c)%100==50){
					SPlaySound(11);
					float angle = 240+get_rand(60);
					SEs_Make((*it).x,(*it).y,angle,2.0,gra_e_shot[6],10,0.0,0,6);
				}
				break;
			case 3:
				if(c==0)	(*it).i_hanyou[0] = get_rand(30);
				if(((*it).i_hanyou[0]+c)%30==15){
					SPlaySound(11);
					float angle = 240+get_rand(60);
					SEs_Make((*it).x,(*it).y,angle,2.0,gra_e_shot[6],10,0.0,0,6);
				}
				break;
		}
	}
	else if(p==15){//2-6毛玉
		switch(SAVE.Level){
			case 0:
				break;
			case 1:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				if(((*it).i_hanyou[0]+c)%60==30){
					SPlaySound(11);
					float angle = 240+get_rand(60);
					SEs_Make((*it).x,(*it).y,angle,2.0,gra_e_shot[6],10,0.0,0,6);
				}
				break;
			case 2:
				if(c==0)	(*it).i_hanyou[0] = get_rand(50);
				if(((*it).i_hanyou[0]+c)%50==25){
					SPlaySound(11);
					float angle = 240+get_rand(60);
					SEs_Make((*it).x,(*it).y,angle,2.0,gra_e_shot[6],10,0.0,0,6);
				}
				break;
			case 3:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				if(((*it).i_hanyou[0]+c)%60<30){
					float angle = Radian(atan2((*it).move_y,(*it).move_x),FALSE)-180-60;
					SPlaySound(10);
					for(int i=0;i<3;i++){
						SEs_Make((*it).x,(*it).y,angle+60*i,0.5,gra_e_shot[5],20,0.0,0,14,i%3);
					}
				}
				break;
		}
	}
	else if(p==16){//3-1
		switch(SAVE.Level){
			case 0:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				if(((*it).i_hanyou[0]+c)%120==30&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<6;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(10)+1.0,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
			case 1:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				if(((*it).i_hanyou[0]+c)%60==30&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<6;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(10)+1.0,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
			case 2:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				if(((*it).i_hanyou[0]+c)%60==30&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<8;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(20)+1.0,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
			case 3:
				if(c==0)	(*it).i_hanyou[0] = get_rand(20);
				if(((*it).i_hanyou[0]+c)%50==30&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<15;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(20)+1.5,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
		}
	}
	else if(p==17){//3-2
		switch(SAVE.Level){
			case 0:
				if(c==20){
					SPlaySound(10);
					for(int i=0;i<1;i++){
						SEs_NWay((*it).x,(*it).y,18.0,10,1.5-0.5*i,gra_e_shot[5],10,180.0,0.0,0,0,0);
						SEs_NWay((*it).x,(*it).y,18.0,20,2.0-0.5*i,gra_e_shot[14],10,9.0,0.0,0,0,0);
					}
				}
				break;		
			case 1:
				if(c==20){
					SPlaySound(10);
					for(int i=0;i<2;i++){
						SEs_NWay((*it).x,(*it).y,18.0,10,2.0-0.5*i,gra_e_shot[5],10,180.0,0.0,0,0,0);
						SEs_NWay((*it).x,(*it).y,18.0,20,3.0-0.5*i,gra_e_shot[14],10,9.0,0.0,0,0,0);
					}
				}
				break;		
			case 2:
				if(c==20){
					SPlaySound(10);
					for(int i=0;i<2;i++){
						SEs_NWay((*it).x,(*it).y,14.4,14,2.0-0.5*i,gra_e_shot[5],10,180.0,0.0,0,0,0);
						SEs_NWay((*it).x,(*it).y,14.4,25,3.0-0.5*i,gra_e_shot[14],10,0.0,0.0,0,0,0);
					}
				}
				break;		
			case 3:
				if(c==20){
					SPlaySound(10);
					for(int i=0;i<4;i++){
						SEs_NWay((*it).x,(*it).y,12.0,20,3.0-0.5*i,gra_e_shot[5],10,180.0,0.0,0,0,0);
						SEs_NWay((*it).x,(*it).y,12.0,30,4.0-0.5*i,gra_e_shot[14],10,6.0,0.0,0,0,0);
					}
				}
				break;		
		}
	}	
	else if(p==18){//3-3（文早回し分）
		switch(SAVE.Level){
			int count;
			case 2:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				count = (*it).i_hanyou[0]+c;
				if(count==150){
					SPlaySound(10);
					for(int i=0;i<1;i++){
						SEs_NWay((*it).x,(*it).y,0.0,1,3.0-0.5*i,gra_e_shot[5],10,0,0.0,0,0,0);
					}
				}
				break;		
			case 3:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				count = (*it).i_hanyou[0]+c;
				if(count==100){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						SEs_NWay((*it).x,(*it).y,0.0,1,4.0-0.5*i,gra_e_shot[5],10,0,0.0,0,0,0);
					}
				}
				break;		
		}
	}	
	else if(p==19){//３面紫通常２
		if(c==50){
			int angle = (*it).d_hanyou[0];
			if(angle%360<180)		(*it).d_hanyou[1] = -1.2;
			else				(*it).d_hanyou[1] = 1.2;
			(*it).d_hanyou[2] = (*it).d_hanyou[0];
		}
		if(c>=50){
			switch(SAVE.Level){
				case 0:
					if(c%8==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+120*i,1.2,gra_e_shot[5],10,0.0,0,0,i%3);
						}
					}
					(*it).d_hanyou[2] += (*it).d_hanyou[1]*2;
					break;
				case 1:
					if(c%8==0){
						SPlaySound(10);
						for(int i=0;i<4;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+90*i,1.5,gra_e_shot[5],10,0.0,0,0,i%4);
						}
					}
					(*it).d_hanyou[2] += (*it).d_hanyou[1]*2;
					break;
				case 2:
					if(c%6==0){
						SPlaySound(10);
						for(int i=0;i<5;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+72*i,2.0,gra_e_shot[5],10,0.0,0,0,i%5);
						}
					}
					(*it).d_hanyou[2] += (*it).d_hanyou[1]*1.5;
					break;
				case 3:
					if(c%6==0){
						SPlaySound(10);
						for(int i=0;i<6;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+60*i,2.5,gra_e_shot[5],10,0.0,0,0,i%6);
						}
					}
					(*it).d_hanyou[2] += (*it).d_hanyou[1];
					break;
			}
		}
	}
	else if(p==20){//結界「ムーブド・アンムーブド」
		if(c==0){
			(*it).i_hanyou[0] = (*it).life;
			(*it).life = 255;
			(*it).flash = 150;
			(*it).b_atari = false;
		}
		if(c==(*it).i_hanyou[0]){
			SPlaySound(11);
		}
		if(c>=(*it).i_hanyou[0]){
			switch(SAVE.Level){
				case 0:
					if(c%15==0){
						SPlaySound(10);
						SEs_Make((*it).x,(*it).y,2*c,0.5,gra_e_shot[9],10);
					}
					break;
				case 1:
					if(c%10==0){
						SPlaySound(10);
						SEs_Make((*it).x,(*it).y,2*c,0.5,gra_e_shot[9],10);
					}
					break;
				case 2:
					if(c%10==0){
						SPlaySound(10);
						SEs_Make((*it).x,(*it).y,2*c,0.5,gra_e_shot[9],10);
					}
					break;
				case 3:
					if(c%5==0){
						SPlaySound(10);
						SEs_Make((*it).x,(*it).y,2*c,1.0,gra_e_shot[9],10);
					}
					break;
			}
		}
		if(c==300){
			SEf_Make((*it).x,(*it).y,1);
			(*it).i_hanyou[7] = 1;
		}
	}
	else if(p==21){//３面紫通常３
		if(c>=50){
			if(c==50){
				(*it).i_hanyou[0] = get_rand(30);
			}
			switch(SAVE.Level){
				case 0:
					if((*it).i_hanyou[0]%6==0){
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x+10*cos(Boss.count);
						Player.y = Boss.y+10*sin(Boss.count);
						SPlaySound(10);
						if((*it).life<=2){
							for(int i=0;i<1;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-1.0*i,gra_e_shot[39],30,0.0,0.0,0,2,i%2);
							}
						}
						else{
							for(int i=0;i<1;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-1.0*i,gra_e_shot[41],30,0.0,0.0,0,2,i%2);
							}
						}
						Player.x = x;
						Player.y = y;
					}
					break;
				case 1:
					if((*it).i_hanyou[0]%5==0){
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x+10*cos(Boss.count);
						Player.y = Boss.y+10*sin(Boss.count);
						SPlaySound(10);
						if((*it).life<=2){
							for(int i=0;i<1;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-1.0*i,gra_e_shot[39],30,0.0,0.0,0,2,i%2);
							}
						}
						else{
							for(int i=0;i<1;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-1.0*i,gra_e_shot[41],30,0.0,0.0,0,2,i%2);
							}
						}
						Player.x = x;
						Player.y = y;
					}
					break;
				case 2:
					if((*it).i_hanyou[0]%5==0){
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x+10*cos(Boss.count);
						Player.y = Boss.y+10*sin(Boss.count);
						SPlaySound(10);
						if((*it).life<=2){
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.5-1.0*i,gra_e_shot[39],30,0.0,0.0,0,2,i%2);
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.5-1.0*i,gra_e_shot[41],30,0.0,0.0,0,2,i%2);
							}
						}
						Player.x = x;
						Player.y = y;
					}
					break;
				case 3:
					if((*it).i_hanyou[0]%3==0){
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x+10*cos(Boss.count);
						Player.y = Boss.y+10*sin(Boss.count);
						SPlaySound(10);
						if((*it).life<=2){
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,3.0-1.0*i,gra_e_shot[39],30,0.0,0.0,0,2,i%2);
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,3.0-1.0*i,gra_e_shot[41],30,0.0,0.0,0,2,i%2);
							}
						}
						Player.x = x;
						Player.y = y;
					}
					break;
			}
		}
		(*it).i_hanyou[0]++;
	}
	else if(p==22){//戯符「神々のアジャラ空間」
		switch(SAVE.Level){
			case 0:
				if(c%90==0){
					SPlaySound(10);
					SEs_Make((*it).x,(*it).y,90,1.0,gra_e_shot[39],10);
				}
				break;
			case 1:
				if(c%70==0){
					SPlaySound(10);
					SEs_Make((*it).x,(*it).y,90,1.2,gra_e_shot[39],10);
				}
				break;
			case 2:
				if(c%70==0){
					SPlaySound(10);
					SEs_Make((*it).x,(*it).y,90,1.2,gra_e_shot[39],10);
				}
				break;
			case 3:
				if(c%40==0){
					SPlaySound(10);
					SEs_Make((*it).x,(*it).y,90,1.5,gra_e_shot[39],10);
				}
				break;
		}	
	}
	else if(p==23){//4-1
		switch(SAVE.Level){
			case 1:
				if(c>20&&(*it).y<CENTER_Y+50){
					int cp = c;
					if(cp==31||cp==41||cp==51||cp==61){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[5],10,0,6.0,10);
					}
				}
				break;
			case 2:
				if(c>20&&(*it).y<CENTER_Y+50){
					int cp = c%97;
					if(cp==31||cp==39||cp==47||cp==55){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,3.0,gra_e_shot[5],10,0,10.0,10);
					}
				}
				break;
			case 3:
				if(c>20&&(*it).y<CENTER_Y+50){
					int cp = c%77;
					if(cp==31||cp==37||cp==43||cp==49){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,4.0,gra_e_shot[5],10,0,10.0,10);
					}
				}
				break;
		}

	}
	else if(p==24){//4-2
		switch(SAVE.Level){
			case 1:
				if(c>40&&c%4==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<6;i++){
						SEs_Make((*it).x,(*it).y,12*((c-40)/4)+60*i,3.0,gra_e_shot[4],10);
					}
				}
				if(c>40&&c%50==0&&c<210){
					for(int i=0;i<10;i++){
						SEs_NWay((*it).x,(*it).y,5.0,1,4.0-0.2*i,gra_e_shot[6],10,0);
					}
				}
				break;
			case 2:
				if(c>40&&c%3==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<6;i++){
						SEs_Make((*it).x,(*it).y,12*((c-40)/3)+60*i,3.5,gra_e_shot[4],10);
					}
				}
				if(c>40&&c%40==0&&c<210){
					for(int i=0;i<10;i++){
						SEs_NWay((*it).x,(*it).y,5.0,1,5.0-0.2*i,gra_e_shot[6],10,0);
					}
				}
				break;
			case 3:
				if(c>40&&c%3==0&&c<210){
					SPlaySound(10);
					for(int i=0;i<6;i++){
						SEs_Make((*it).x,(*it).y,12*((c-40)/3)+60*i,4.0,gra_e_shot[4],10);
					}
				}
				if(c>40&&c%30==0&&c<210){
					for(int i=0;i<7;i++){
						SEs_NWay((*it).x,(*it).y,5.0,1+i,7.0-0.5*i,gra_e_shot[6],10,0);
						SEs_NWay((*it).x,(*it).y,5.0,1+i,7.0-0.5*i,gra_e_shot[6],10,-60);
						SEs_NWay((*it).x,(*it).y,5.0,1+i,7.0-0.5*i,gra_e_shot[6],10,60);
					}
				}
				break;
		}
	}
	else if(p==25){//4-5
		switch(SAVE.Level){
			case 1:
				if(c>=40&&c<100){
					if(c%1==0){
						SPlaySound(11);
						for(int i=0;i<2;i++){
							float angle = Radian(180*i+12*c,TRUE);
							float d = 1.5*(c-40);
							SEs_NWay((*it).x+d*cos(angle),(*it).y+d*sin(angle),120.0,1,2.5,gra_e_shot[14],10,0,10.0,10);
						}
					}
				}
				break;
			case 2:
				if(c>=40&&c<100){
					if(c%1==0){
						SPlaySound(11);
						for(int i=0;i<2;i++){
							float angle = Radian(180*i+12*c,TRUE);
							float d = 1.5*(c-40);
							SEs_NWay((*it).x+d*cos(angle),(*it).y+d*sin(angle),120.0,3,3.5,gra_e_shot[14],10,0,10.0,10);
						}
					}
					if(c%50==2){
						int ra = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make((*it).x,(*it).y,ra+12*i,3.0,gra_e_shot[28],10,10.0,5);
						}
					}
				}
				break;
			case 3:
				if(c>=40&&c<100){
					if(c%1==0){
						SPlaySound(11);
						for(int i=0;i<2;i++){
							float angle = Radian(180*i+12*c,TRUE);
							float d = 1.5*(c-40);
							SEs_NWay((*it).x+d*cos(angle),(*it).y+d*sin(angle),72.0,5,5.5,gra_e_shot[14],10,0,10.0,10);
						}
					}
					if(c%20==2){
						int ra = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make((*it).x,(*it).y,ra+12*i,4.5,gra_e_shot[28],10,10.0,5);
						}
					}
				}
				break;
		}
	}
	else if(p==26||p==27){//4-6 加速弾ばら撒き
		switch(SAVE.Level){
			case 1:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==6){
						int angle = c*5;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,5.0,gra_e_shot[14],30,0.0,0,2);
						}
					}
					else{
						int angle = c*5;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,5.0,gra_e_shot[15],30,0.0,0,2);
						}
					}
				}
				break;
			case 2:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==6){
						int angle = c*5;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x,(*it).y,angle+72*i,5.0,gra_e_shot[14],30,0.0,0,2);
						}
					}
					else{
						int angle = c*5;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x,(*it).y,angle+72*i,5.0,gra_e_shot[15],30,0.0,0,2);
						}
					}
				}
				break;
			case 3:
				if(c%2==0&&(*it).y>15&&c<120){
					SPlaySound(10);
					if(p==26){
						int angle = c*5;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x,(*it).y,angle+60*i,5.0,gra_e_shot[14],60,0.0,0,2);
						}
					}
					else{
						int angle = c*5;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x,(*it).y,angle+60*i,5.0,gra_e_shot[15],60,0.0,0,2);
						}
					}
				}
				break;
		}
	}	
	else if(p==28){//4-7
		switch(SAVE.Level){
			case 1:
				if(Game.count<3130){
					if(c==51&&(*it).y<CENTER_Y+50){
						SPlaySound(10);
						for(int i=0;i<5;i++){
							SEs_NWay((*it).x,(*it).y,30.0,3,3.5-0.3*i,gra_e_shot[5],10,0);
						}
					}
				}
				else{
					if(c>=30&&c%50==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,32.0,5,3.0-0.3*i,gra_e_shot[5],10,0.0,8.0,15);
						}
					}
				}
				break;
			case 2:
				if(Game.count<3130){
					if(c==51&&(*it).y<CENTER_Y+50){
						SPlaySound(10);
						for(int i=0;i<5;i++){
							SEs_NWay((*it).x,(*it).y,30.0,3,4.0-0.3*i,gra_e_shot[5],10,0);
						}
					}
				}
				else{
					if(c>=30&&c%50==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,32.0,5,4.0-0.5*i,gra_e_shot[5],10,0.0,10.0,15);
						}
					}
				}
				break;
			case 3:
				if(Game.count<3130){
					if(c==31&&(*it).y<CENTER_Y+50){
						SPlaySound(10);
						for(int i=0;i<10;i++){
							SEs_NWay((*it).x,(*it).y,20.0,3,6.0-0.3*i,gra_e_shot[5],10,0);
						}
					}
				}
				else{
					if(c>=30&&c%30==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,16.0,10,5.0-1.0*i,gra_e_shot[5],10,8.0,10.0,15);
						}
					}
				}
				break;
		}
	}	
	else if(p==29){//5-1
		if(c==0)	(*it).i_hanyou[1] = get_rand(15);
		c = c + (*it).i_hanyou[1];
		switch(SAVE.Level){
			case 1:
				if(c%150==15){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,7.0,3,3.0,gra_e_shot[15],10,0,10.0,10);
				}
				break;
			case 2:
				if(c%150==15){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,7.0,5,3.5,gra_e_shot[15],10,0,10.0,10);
				}
				break;
			case 3:
				if(c%100==15){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,7.0,5,4.5,gra_e_shot[15],10,0,10.0,10);
				}
				break;
		}
	}	
	else if(p==30){//5-2
		switch(SAVE.Level){
			case 1:
				if(c>50){
					if(c<80){
						if(c%3==0){
							SPlaySound(10);
							for(int i=0;i<4;i++){
								SEs_Make((*it).x,(*it).y,90+90*i,3.0+((float)c-50.0)/5.0,gra_e_shot[4],10);
							}	
						}
					}
					else{
						if(c%20==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make((*it).x,(*it).y,45*i+10*(c-80)/20,1.5,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
			case 2:
				if(c>50){
					if(c<80){
						if(c%2==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								SEs_Make((*it).x,(*it).y,90+60*i,3.0+((float)c-50.0)/5.0,gra_e_shot[4],10);
							}	
						}
					}
					else{
						if(c%10==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make((*it).x,(*it).y,45*i+10*(c-80)/10,2.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
			case 3:
				if(c>50){
					if(c<80){
						if(c%1==0){
							SPlaySound(10);
							for(int i=0;i<10;i++){
								SEs_Make((*it).x,(*it).y,90+36*i,3.0+((float)c-50.0)/5.0,gra_e_shot[4],10);
							}	
						}
					}
					else{
						if(c%7==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make((*it).x,(*it).y,45*i+10*(c-80)/7,3.0,gra_e_shot[0],10,5.0,5);
							}	
						}
					}
				}
				break;
		}
	}
	else if(p==31){//5-3
		if(c==0)	(*it).i_hanyou[6] = get_rand(20);
		c = c+(*it).i_hanyou[6];
		int cp;
		switch(SAVE.Level){
			case 1:
				cp = c%40;
				if((*it).y<CENTER_Y){
					if(cp==10){
							SPlaySound(10);
						int rand = get_rand(44);
						for(int i=0;i<8;i++){
							for(int a=0;a<2;a++){
								SEs_Make((*it).x,(*it).y,45*i+rand+22.5*a,2.0-1.0*a,gra_e_shot[14],10,10.0,5);
							}
						}	
					}
				}
				break;
			case 2:
				cp = c%30;
				if((*it).y<CENTER_Y){
					if(cp==10){
							SPlaySound(10);
						int rand = get_rand(44);
						for(int i=0;i<8;i++){
							for(int a=0;a<2;a++){
								SEs_Make((*it).x,(*it).y,45*i+rand+22.5*a,2.5-1.0*a,gra_e_shot[14],10,10.0,5);
							}
						}	
					}
				}
				break;
			case 3:
				cp = c%50;
				if((*it).y<CENTER_Y){
					if(cp==35){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,10.0,3,4.5-0.5*i,gra_e_shot[15],10,0,10.0,5);
						}
					}
					if(cp==10){
							SPlaySound(10);
						int rand = get_rand(44);
						for(int i=0;i<8;i++){
							for(int a=0;a<2;a++){
								SEs_Make((*it).x,(*it).y,45*i+rand+22.5*a,3.0-1.0*a,gra_e_shot[14],10,10.0,5);
							}
						}	
					}
				}
				break;
		}
	}
	else if(p==32){//5-5
		switch(SAVE.Level){
			case 1:
				if(c>=60&&(*it).speed==0){
					if(c%10==0){
						SPlaySound(10);
						float angle = -13*c/5;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,-2.5,gra_e_shot[9],10,5.0,90);
						}	
					}
					else if(c%10==3){
						SPlaySound(10);
						float angle = -13*c/5;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,2.5,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+90*i,TRUE)),(*it).y+70*sin(Radian(angle+90*i,TRUE)),angle+90*i+1.5*c,1.5,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 2:
				if(c>=60&&(*it).speed==0){
					if(c%10==0){
						SPlaySound(10);
						float angle = -13*c/5;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,-2.5,gra_e_shot[9],10,5.0,90);
						}	
					}
					else if(c%10==3){
						SPlaySound(10);
						float angle = -13*c/5;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,2.5,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+60*i,TRUE)),(*it).y+70*sin(Radian(angle+60*i,TRUE)),angle+60*i+1.5*c,1.5,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 3:
				if(c>=60&&(*it).speed==0){
					if(c%6==0){
						SPlaySound(10);
						float angle = -13*c/6;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,-3.0,gra_e_shot[9],10,5.0,90);
						}	
					}
					else if(c%6==3){
						SPlaySound(10);
						float angle = -13*c/6;
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,angle+120*i,3.0,gra_e_shot[9],10);
						}	
					}
					if(c%6==0){
						float angle = 10*c/6;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+70*cos(Radian(angle+60*i,TRUE)),(*it).y+70*sin(Radian(angle+60*i,TRUE)),angle+60*i+1.5*c,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
		}
	}
	else if(p==33){//5-6
		switch(SAVE.Level){
			case 1:
				if(c>=60&&(*it).speed==0){
					if(c%10==0){
						SPlaySound(10);
						float angle = -25*c/10;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,2.0,gra_e_shot[9],10,0,0.0,0,i%2);
							SEs_Make((*it).x,(*it).y,angle+180*i+90,1.5,gra_e_shot[9],10);
						}	
					}
					if(c%20==0){
						float angle = 20*c/20;
						for(int i=0;i<4;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+90*i,TRUE)),(*it).y+100*sin(Radian(angle+90*i,TRUE)),angle+90*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 2:
				if(c>=60&&(*it).speed==0){
					if(c%7==0){
						SPlaySound(10);
						float angle = -25*c/7;
						for(int i=0;i<2;i++){
							SEs_Make((*it).x,(*it).y,angle+180*i,2.0,gra_e_shot[9],10,0,0.0,0,i%2);
							SEs_Make((*it).x,(*it).y,angle+180*i+90,1.5,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 20*c/10;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+72*i,TRUE)),(*it).y+100*sin(Radian(angle+72*i,TRUE)),angle+72*i+170,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
			case 3:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = -10*c/3;
						for(int i=0;i<5;i++){
							SEs_Make((*it).x,(*it).y,angle+72*i,2.0,gra_e_shot[9],10);
							SEs_Make((*it).x,(*it).y,angle+72*i+36,1.5,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<12;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+30*i,TRUE)),(*it).y+100*sin(Radian(angle+30*i,TRUE)),angle+30*i+150,2.0,gra_e_shot[8],10);
						}	
					}
				}
				break;
		}
	}
	else if(p==34){//5-6
		switch(SAVE.Level){
			case 1:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = 7*c/3;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+60*i,TRUE)),(*it).y+100*sin(Radian(angle+60*i,TRUE)),angle+60*i+160,1.5,gra_e_shot[9],10);
						}	
					}
					if(c%30==0){
						float angle = 10*c/30;
						for(int i=0;i<10;i++){
							for(int a=0;a<2;a++){
								SEs_Make((*it).x+140*cos(Radian(angle+36*i,TRUE)),(*it).y+140*sin(Radian(angle+36*i,TRUE)),angle+36*i+180*a,1.0,gra_e_shot[14],10);
							}	
						}	
					}
				}
				break;
			case 2:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = 7*c/3;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+60*i,TRUE)),(*it).y+100*sin(Radian(angle+60*i,TRUE)),angle+60*i+160,1.5,gra_e_shot[9],10);
						}	
					}
					if(c%30==0){
						float angle = 10*c/30;
						for(int i=0;i<10;i++){
							for(int a=0;a<3;a++){
								SEs_Make((*it).x+140*cos(Radian(angle+36*i,TRUE)),(*it).y+140*sin(Radian(angle+36*i,TRUE)),angle+36*i+120*a,1.0,gra_e_shot[14],10);
							}	
						}	
					}
				}
				break;
			case 3:
				if(c>=60&&(*it).speed==0){
					if(c%3==0){
						SPlaySound(10);
						float angle = 7*c/3;
						for(int i=0;i<6;i++){
							SEs_Make((*it).x+100*cos(Radian(angle+60*i,TRUE)),(*it).y+100*sin(Radian(angle+60*i,TRUE)),angle+60*i+160,1.5,gra_e_shot[9],10);
						}	
					}
					if(c%10==0){
						float angle = 10*c/10;
						for(int i=0;i<10;i++){
							for(int a=0;a<4;a++){
								SEs_Make((*it).x+140*cos(Radian(angle+36*i,TRUE)),(*it).y+140*sin(Radian(angle+36*i,TRUE)),angle+36*i+90*a,1.0,gra_e_shot[14],10);
							}	
						}	
					}
				}
				break;
		}
	}
	else if(p==35){//5-6
		switch(SAVE.Level){
			case 1:
				if((*it).y<CENTER_Y+50){
					if(c%10==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,30.0,1,2.0,gra_e_shot[5],10,0,10.0,10);
					}
				}
				break;
			case 2:
				if((*it).y<CENTER_Y+50){
					if(c%10==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,30.0,1,3.5,gra_e_shot[5],10,0,10.0,10);
					}
				}
				break;
			case 3:
				if((*it).y<CENTER_Y+50){
					if(c%10==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,30.0,3,4.5,gra_e_shot[5],10,0,10.0,10);
					}
				}
				break;
		}
	}
	else if(p==36){//6-1
		switch(SAVE.Level){
			case 1:
				if(c==0)	(*it).i_hanyou[0] = get_rand(5);
				if(((*it).i_hanyou[0]+c)%20==0&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(10)+1.0,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
			case 2:
				if(c==0)	(*it).i_hanyou[0] = get_rand(5);
				if(((*it).i_hanyou[0]+c)%10==0&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(20)+1.0,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
			case 3:
				if(c==0)	(*it).i_hanyou[0] = get_rand(5);
				if(((*it).i_hanyou[0]+c)%5==0&&(*it).y<300){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						float angle = get_rand(359);
						SEs_Make((*it).x,(*it).y,angle,0.1*get_rand(20)+1.5,gra_e_shot[15],10,0.0,0,0,i%15);
					}
				}
				break;
		}
	}
	else if(p==37){//6-2
		switch(SAVE.Level){
			case 1:
				if(c>=20 && c<80){
					c-=20;
					if(c%6==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,3.5,gra_e_shot[27],10,-20+get_rand(20));
						for(int i=0;i<2;i++){
							SEs_NWay((*it).x,(*it).y,0.0,1,3.5+0.1*get_rand(15),gra_e_shot[5],10,-5+get_rand(10));
						}
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,0.0,1,4.0+0.1*get_rand(15),gra_e_shot[0],10,-5+get_rand(10));
						}
					}
				}
				break;		
			case 2:
				if(c>=20 && c<80){
					c-=20;
					if(c%6==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,3.5,gra_e_shot[27],10,-20+get_rand(30));
						for(int i=0;i<2;i++){
							SEs_NWay((*it).x,(*it).y,0.0,1,3.5+0.1*get_rand(15),gra_e_shot[5],10,-10+get_rand(20));
						}
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,0.0,1,4.0+0.1*get_rand(15),gra_e_shot[0],10,-10+get_rand(20));
						}
					}
				}
				break;		
			case 3:
				if(c>=20){
					c-=20;
					if(c%6==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,3.5,gra_e_shot[27],10,-20+get_rand(40));
						for(int i=0;i<2;i++){
							SEs_NWay((*it).x,(*it).y,0.0,1,3.5+0.1*get_rand(15),gra_e_shot[5],10,-20+get_rand(30));
						}
						for(int i=0;i<3;i++){
							SEs_NWay((*it).x,(*it).y,0.0,1,4.0+0.1*get_rand(15),gra_e_shot[0],10,-20+get_rand(30));
						}
					}
				}
				break;		
		}
	}	
	else if(p==38){//6-3（文早回し分）
		switch(SAVE.Level){
			int count;
			case 1:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				count = (*it).i_hanyou[0]+c;
				if(count==150){
					SPlaySound(10);
					for(int i=0;i<1;i++){
						SEs_NWay((*it).x,(*it).y,0.0,1,3.0-0.5*i,gra_e_shot[5],10,0,0.0,0,0,0);
					}
				}
				break;
			case 2:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				count = (*it).i_hanyou[0]+c;
				if(count%200==100){
					SPlaySound(10);
					for(int i=0;i<1;i++){
						SEs_NWay((*it).x,(*it).y,10.0,3,4.0-0.5*i,gra_e_shot[5],10,0,0.0,0,0,0);
					}
				}
				break;		
			case 3:
				if(c==0)	(*it).i_hanyou[0] = get_rand(60);
				count = (*it).i_hanyou[0]+c;
				if(count%100==60){
					SPlaySound(10);
					for(int i=0;i<3;i++){
						SEs_NWay((*it).x,(*it).y,10.0,3,4.0-0.5*i,gra_e_shot[5],10,0,0.0,0,0,0);
					}
				}
				break;		
		}
	}	
	else if(p==39){//6面紫通常２
		if(c==50){
			int angle = (*it).d_hanyou[0];
			if(angle%360<180)		(*it).d_hanyou[1] = -1.0;
			else				(*it).d_hanyou[1] = 1.0;
			(*it).d_hanyou[2] = (*it).d_hanyou[0];
		}
		if(c>=50){
			switch(SAVE.Level){
				case 1:
					if(c%8==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+120*i,2.0,gra_e_shot[5],10,0.0,0,0,i%4);
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+120*i,1.5,gra_e_shot[5],10,0.0,0,0,i%4);
						}
						(*it).d_hanyou[2] += (*it).d_hanyou[1]*8.0;
					}
					break;
				case 2:
					if(c%5==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+120*i,2.0,gra_e_shot[5],10,0.0,0,0,i%5);
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+120*i,1.5,gra_e_shot[5],10,0.0,0,0,i%5);
						}
						(*it).d_hanyou[2] += (*it).d_hanyou[1]*8.0;
					}
					break;
				case 3:
					if(c%5==0){
						SPlaySound(10);
						for(int i=0;i<4;i++){
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+90*i,2.5,gra_e_shot[5],10,0.0,0,0,i%6);
							SEs_Make((*it).x,(*it).y,(*it).d_hanyou[2]+90*i,2.0,gra_e_shot[5],10,0.0,0,0,i%6);
						}
						(*it).d_hanyou[2] += (*it).d_hanyou[1]*8.0;
					}
					break;
			}
		}
	}
	else if(p==40){//6面紫通常３
		if(c>=50){
			if(c==50){
				(*it).i_hanyou[0] = get_rand(30);
			}
			switch(SAVE.Level){
				case 1:
					if((*it).i_hanyou[0]%3==0){
						SPlaySound(10);
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x;
						Player.y = Boss.y;
						SPlaySound(10);
						float plus_angle = 10.0 + 0.3*abs(120-Boss.count%240);
						if((*it).life<=2){
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-0.5*i,gra_e_shot[39],120,plus_angle,0.0,180);
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-1.0*i,gra_e_shot[41],120,plus_angle,0.0,180);
							}
						}						
						Player.x = x;
						Player.y = y;
					}
				case 2:
					if((*it).i_hanyou[0]%2==0){
						SPlaySound(10);
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x;
						Player.y = Boss.y;
						SPlaySound(10);
						float plus_angle = 10.0 + 0.3*abs(120-Boss.count%240);
						if((*it).life<=2){
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-0.5*i,gra_e_shot[39],120,plus_angle,0.0,180);
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,2.0-1.0*i,gra_e_shot[41],120,plus_angle,0.0,180);
							}
						}						
						Player.x = x;
						Player.y = y;
					}
					break;
				case 3:
					if((*it).i_hanyou[0]%2==0){
						SPlaySound(10);
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.x;
						Player.y = Boss.y;
						SPlaySound(10);
						float plus_angle = 10.0 + 0.3*abs(120-Boss.count%240);
						if((*it).life<=2){
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,3.0-0.5*i,gra_e_shot[39],120,plus_angle,0.0,180);
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay((*it).x,(*it).y,0.0,1,3.0-1.0*i,gra_e_shot[41],120,plus_angle,0.0,180);
							}
						}						
						Player.x = x;
						Player.y = y;
					}
					break;
			}
		}
		(*it).i_hanyou[0]++;
	}
	else if(p==41 || p==42){//戯符「メンフェンティス降臨」
		if(p==41){
			switch(SAVE.Level){
				case 1:
					if(c%90==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[39],10);
					}
					break;
				case 2:
					if(c%50==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[39],10);
					}
					break;
				case 3:
					if(c%20==0){
						SPlaySound(10);
						SEs_NWay((*it).x,(*it).y,0.0,1,3.0,gra_e_shot[39],10);
					}
					break;
			}	
		}
		if(p==42){
			if(c%6==0){
				SPlaySound(10);
				for(int i=0;i<1;i++){
					float d = get_rand(40);
					float an = Radian(get_rand(359),TRUE);
					SEs_Make((*it).x+d*cos(an),(*it).y+d*sin(an),get_rand(359),0.3,gra_e_shot[(*it).life+21],20,0.0,0,37);
				}
			}
		}
	}
	else if(p>=43 && p<=50){//禁忌「真弾幕結界 -久遠素懐-」
		if(c>=120 && c<780){
			//f_speed : 進む時間
			//f_count : 動き始めるまでの時間
			int img;
			float x = Player.x;
			float y = Player.y;
			Player.x = Boss.x;
			Player.y = Boss.y;
			if(p==43){
				img = 18;
				if(c%40<20 && c%5==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,(float)(c-120)/30.0,c/10,c/60,40);
				}
			}
			if(p==44){
				img = 19;
				if((c+7)%40<20 && c%5==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,-(float)(c-120)/30.0,c/10,c/60,40);
				}
			}
			if(p==45){
				img = 18;
				if(c%60<42 && c%3==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,(float)(c-120)/40.0,c/8,c/60,40);
				}
			}
			if(p==46){
				img = 19;
				if((c+25)%60<42 && c%3==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,-(float)(c-120)/40.0,c/8,c/60,40);
				}
			}
			if(p==47){
				img = 18;
				if(c%30<18 && c%6==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,(float)(c-120)/40.0,c/10,c/60,40);
				}
			}
			if(p==48){
				img = 19;
				if((c+4)%30<18 && c%6==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,-(float)(c-120)/40.0,c/10,c/60,40);
				}
			}
			if(p==49){
				img = 18;
				if(c%2==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,(float)(c-120)/20.0,(c-60)/10,c/60,41);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,(float)(c-120)/20.0,(c-60)/10,c/60,42);
				}
			}
			if(p==50){
				img = 19;
				if(c%2==0){
					SPlaySound(10);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,-(float)(c-120)/20.0,(c-60)/10,c/60,41);
					SEs_NWay((*it).x,(*it).y,0.0,1,2.0,gra_e_shot[img],0,-(float)(c-120)/20.0,(c-60)/10,c/60,42);
				}
			}
			if(c%3==0 && SAVE.Level>1){
				for(int i=0;i<2;i++){
					SEs_Make((*it).x,(*it).y,(*it).d_hanyou[1]-5.0+10.0*i,0.5,gra_e_shot[img],0);
				}
			}
			Player.x = x;
			Player.y = y;
		}
	}
	else if(p==51){//「終焉と幻想の境界」
		if((*it).x>0&&(*it).x<450&&(*it).y>0&&(*it).y<300&&c>10){
			SPlaySound(10);
			for(int i=0;i<2;i++){
				float d = get_rand(c);
				if((*it).y<CENTER_Y)	d = get_rand(2.0*c);
				float angle = Radian(get_rand(359),TRUE);
				SEs_Make((*it).x+d*cos(angle),(*it).y+d*sin(angle),get_rand(359),2.0,gra_e_shot[23+2*get_rand(1)],30,0.0,0,48);
			}
		}
	}
	else if(p==52){//Ex-1
		if(c>0&&c%20==0&&(*it).y<CENTER_Y+50){
			SPlaySound(10);
			SEs_NWay((*it).x,(*it).y,40.0,1,6.0,gra_e_shot[5],10,0,10.0,10);
		}
	}
	else if(p==53){//Ex-2
		if(c>=40&&c<180){
			if(c%1==0){
				for(int i=0;i<3;i++){
					SEs_Make((*it).x,(*it).y,4.0*c+120*i,8.0,gra_e_shot[14],0,4.0+2.0*sin(Radian(18.0*c,TRUE)),0,49+i);
				}
			}
			if(c%5==0){
				SPlaySound(10);
				SEs_NWay((*it).x,(*it).y,20.0,18,4.5,gra_e_shot[6],10,30.0*sin(Radian(3.0*c,TRUE)),10.0,10);
			}
		}
	}
	else if(p==54){//Ex-3
		//打ち返しあり
		if(c==1){
			(*it).i_hanyou[0] = get_rand(60);
		}
		if((*it).i_hanyou[0]%60==30){
			SEs_Make((*it).x,(*it).y,90.0,3.0,gra_e_shot[16],10);
		}
		(*it).i_hanyou[0]++;
	}
	else if(p==55){//Ex-4(早回し)
		if(c==40){
			(*it).d_hanyou[0] = get_rand(360);
		}
		if(c<40){}
		else if(c<70){
			if((c-40)%3==0){
				SPlaySound(10);
				for(int i=0;i<10;i++){
					float angle = 6.0*(*it).i_hanyou[0]+36.0*i;
					float speed = 1.5+((float)c-40.0)*0.08;
					SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[14],5);
					//SEs_Make((*it).x,(*it).y,angle,speed/2.0,gra_e_shot[14],5);
				}
				(*it).i_hanyou[0]++;
			}
		}
		else if(c<100){
			if((c-70)%3==0){
				SPlaySound(10);
				for(int i=0;i<10;i++){
					float angle = -6.0*(*it).i_hanyou[0]+36.0*i;
					float speed = 1.5+((float)c-70.0)*0.08;
					SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[14],5);
					//SEs_Make((*it).x,(*it).y,angle,speed/2.0,gra_e_shot[14],5);
				}
				(*it).i_hanyou[0]++;
			}
		}
		else if(c<130){
			if((c-100)%3==0){
				SPlaySound(10);
				for(int i=0;i<10;i++){
					float angle = 6.0*(*it).i_hanyou[0]+36.0*i;
					float speed = 1.5+((float)c-100.0)*0.08;
					SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[14],5);
					//SEs_Make((*it).x,(*it).y,angle,speed/2.0,gra_e_shot[14],5);
				}
				(*it).i_hanyou[0]++;
			}
		}
		else if(c<160){
			if((c-130)%3==0){
				SPlaySound(10);
				for(int i=0;i<10;i++){
					float angle = -6.0*(*it).i_hanyou[0]+36.0*i;
					float speed = 1.5+((float)c-130.0)*0.08;
					SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[14],5);
					//SEs_Make((*it).x,(*it).y,angle,speed/2.0,gra_e_shot[14],5);
				}
				(*it).i_hanyou[0]++;
			}
		}
	}
	else if(p==56){//Ex-5(早回し)
		if(c==40){
			(*it).d_hanyou[0] = get_rand(360);
		}
		if(c==50){
			SPlaySound(10);
			for(int i=0;i<120;i++){
				float angle = 6.0*i;
				float speed = 2.0+fabs( 1.5*sin(Radian((*it).i_hanyou[0]+7.5*i,TRUE)) );
				SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[52],5);
			}
			SEs_NWay((*it).x,(*it).y,12.0,30,1.0,gra_e_shot[6],5,6.0);
		}
		if(c==90){
			SPlaySound(10);
			for(int i=0;i<120;i++){
				float angle = 6.0*i;
				float speed = 2.0+fabs( 1.5*sin(Radian(5.0*(*it).i_hanyou[0]+13.5*i,TRUE)) );
				SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[52],5);
			}
			SEs_NWay((*it).x,(*it).y,12.0,30,1.0,gra_e_shot[6],5,6.0);
		}
		if(c==130){
			SPlaySound(10);
			for(int i=0;i<120;i++){
				float angle = 6.0*i;
				float speed = 2.0+fabs( 1.5*sin(Radian((*it).i_hanyou[0]+7.5*i,TRUE)) );
				SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[52],5);
				SEs_Make((*it).x,(*it).y,angle+180,speed/2.0,gra_e_shot[52],5);
			}
			SEs_NWay((*it).x,(*it).y,12.0,30,1.0,gra_e_shot[6],5,6.0);
		}
		if(c==170){
			SPlaySound(10);
			for(int i=0;i<120;i++){
				float angle = 6.0*i;
				float speed = 2.0+fabs( 1.5*sin(Radian(5.0*(*it).i_hanyou[0]+13.5*i,TRUE)) );
				SEs_Make((*it).x,(*it).y,angle,speed,gra_e_shot[52],5);
				SEs_Make((*it).x,(*it).y,angle+90,speed/2.0,gra_e_shot[52],5);
			}
			SEs_NWay((*it).x,(*it).y,12.0,30,1.0,gra_e_shot[6],5,6.0);
		}
	}
	else if(p==57){//Ex-6.1
		if(c==1){
			(*it).i_hanyou[0] = get_rand(29);
		}
		if((*it).i_hanyou[0]%30==1){//時計回り1way
			SPlaySound(10);
			SEs_Make((*it).x,(*it).y,0.5*(*it).i_hanyou[0],3.0,gra_e_shot[52],10);
		}
		(*it).i_hanyou[0]++;
	}
	else if(p==58){//Ex-6.2
		if(c==1){
			(*it).i_hanyou[0] = get_rand(29);
		}
		if((*it).i_hanyou[0]%30==1){//反時計回り1way
			SPlaySound(10);
			SEs_Make((*it).x,(*it).y,-0.5*(*it).i_hanyou[0],3.0,gra_e_shot[52],10);
		}
		(*it).i_hanyou[0]++;
	}
	else if(p==59){//Ex-7
		if(c==1){
			(*it).i_hanyou[0] = get_rand(29);
		}
		if((*it).i_hanyou[0]%30==1){//反時計回り1way
			SPlaySound(10);
			SEs_Make((*it).x,(*it).y,-0.5*(*it).i_hanyou[0],3.0,gra_e_shot[52],10);
		}
		(*it).i_hanyou[0]++;
	}
	else if(p==60){//Ex-8
		if(c>30){
			c-=30;
			if(c<=30){
				(*it).d_hanyou[2] = 0;//角度の変位（カウント）
				(*it).d_hanyou[3] = 22.5;//角度プラス分
			}
			else{
				(*it).d_hanyou[3] += 10*sin(Radian((*it).d_hanyou[2],TRUE));
				(*it).d_hanyou[2]++; 
			}
			if(c>0&&c%2==0){
				SPlaySound(10);
				for(int i=0;i<8;i++){
					float angle = 45*i+(*it).d_hanyou[3];
					SEs_Make((*it).x+15*cos(Radian(angle,TRUE)),(*it).y+15*sin(Radian(angle,TRUE)),angle,3.0,gra_e_shot[15],20);
				}
			}
			c+=30;
		}
	}
	else if(p==61 || p==62){//幻影「十王裁判」
		if(c>160){
			c-=160;
			if(c%5==0){
				SPlaySound(10);
				for(int i=0;i<5;i++){
					float angle = (*it).d_hanyou[0]-90.0+45.0*i;
					SEs_Make((*it).x,(*it).y,angle,4.0,gra_e_shot[26],0);
				}
			}
			if(p==61){
				if(c>0&&c%320==0){
					float angle = Radian(atan2(CENTER_Y-(*it).y,CENTER_X-(*it).x),FALSE);
					SLas_Make((*it).x,(*it).y,angle,10.0,gra_laser[0],60,0,0);			
				}
			}
			else{
				if(c>0&&c%320==160){
					float angle = Radian(atan2(Player.y-(*it).y,Player.x-(*it).x),FALSE);
					SLas_Make((*it).x,(*it).y,angle,10.0,gra_laser[1],60,0,0);			
				}
			}
			c+=160;
		}
	}
	else if(p>=63 && p<=66){//夢終「エンドオブジャッジメント」
		if((*it).x>0&&(*it).x<450&&(*it).y>0&&(*it).y<300+50&&c>10){
			SPlaySound(10);
			for(int i=0;i<2;i++){
				float d = get_rand(c);
				if((*it).y<CENTER_Y)	d = get_rand(2.0*c);
				float angle = Radian(get_rand(359),TRUE);
				SEs_Make((*it).x+d*cos(angle),(*it).y+d*sin(angle),get_rand(359),2.0,gra_e_shot[24],30,0.0,0,56+(p-63));
			}
		}
	}
	return;
}

void SEn_Item(list<ENEMYDATA>::iterator &it){
	int p = (*it).item_pattern;
	int bai = 1;
	if(Game.stage>3)	bai = 2;
	
	if(p==0){//赤１
		SIt_Make((*it).x,(*it).y,270,gra_item[0]);
	}
	else if(p==1){//青１
		SIt_Make((*it).x,(*it).y,270,gra_item[1]);
	}
	else if(p==2){//緑１
		SIt_Make((*it).x,(*it).y,270,gra_item[3]);
	}
	else if(p==3){//1-2向日葵妖精
		for(int i=0;i<2*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[0]);
		}
		for(int i=0;i<2*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[1]);
		}
		for(int i=0;i<2*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[3]);
		}
	}
	else if(p==4){//3-2向日葵妖精（早回し分）
		for(int i=0;i<1*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[1]);
		}
		for(int i=0;i<4*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[3]);
		}
	}
	else if(p==5){//3-2向日葵妖精（通常分）
		for(int i=0;i<3*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[1]);
		}
		for(int i=0;i<2*bai;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[3]);
		}
	}
	else if(p==6){//赤２
		for(int i=0;i<2;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[0]);
		}
	}
	else if(p==7){//青２
		for(int i=0;i<2;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[1]);
		}
	}
	else if(p==8){//緑２
		for(int i=0;i<2;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[3]);
		}
	}
	else if(p==9){//Ex向日葵妖精
		for(int i=0;i<10;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[0]);
		}
		for(int i=0;i<10;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[1]);
		}
		for(int i=0;i<10;i++){
			SIt_Make((*it).x-(*it).img_x/2+0.01*get_rand(100)*(*it).img_x,(*it).y-(*it).img_y/2+0.01*get_rand(100)*(*it).img_y,270,gra_item[3]);
		}
	}
	else if(p==10){//Ex向日葵妖精２
		for(int i=0;i<20;i++){ 
			float angle = Radian(get_rand(359),TRUE);
			float d = 50+get_rand(50);
			SIt_Make((*it).x+d*cos(angle),(*it).y+d*sin(angle),270,gra_item[0]);
		}
		for(int i=0;i<20;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = 50+get_rand(50);
			SIt_Make((*it).x+d*cos(angle),(*it).y+d*sin(angle),270,gra_item[1]);
		}
		for(int i=0;i<20;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = 50+get_rand(50);
			SIt_Make((*it).x+d*cos(angle),(*it).y+d*sin(angle),270,gra_item[3]);
		}
		SIt_Make((*it).x,(*it).y,270,gra_item[5]);
	}
	
	return;
}

void SEs_Load(){
	/*===========================================
		小弾 　　　0:赤 1:青 2:黄 3:緑
		中弾 　　　4:赤 5:青 6:黄 7:緑 53:水
		中弾その２ 8:赤 9:青 10:黄 11:緑 12:紫 13:灰
		米弾 　　　14:赤 15:青 16:黄 17:緑 52:水
		鱗弾 　　　18:赤 19:青 20:黄 21:緑
		蝶弾 　　　22:赤 23:青 24:黄 25:緑
	　　　（蝶弾薄部分)0:赤 1:青 2:黄 3:緑
		大弾 　　　26:赤 27:青 28:黄 29:緑 30:灰
		特大弾　　 31:赤 32:青 33:黄 34:緑
		刀弾　　　 35:赤 36:青 37:紫
		札弾　　　 38:赤 39:青 40:黄 41:緑 42:紫
		ジェリー弾 43:赤 44:青 45:黄 46:緑
		クナイ弾 　47:赤 48:青 49:黄 50:緑 51:紫
		氷弾　　　 54:赤 55:青 56:黄 57:緑
	　　　（特大弾薄部)4:赤 5:青 6:黄 7:緑
	===========================================*/
	try{
		char fi[128];
		for(int i=0;i<GRA_E_SHOT_NUM;i++){
			SetTransColor(0,0,0);
			switch(i){
				case 0: wsprintf(fi , "data/img/shot/small/1_a.png");
					break;	
				case 1: wsprintf(fi , "data/img/shot/small/2_a.png");
					break;
				case 2: wsprintf(fi , "data/img/shot/small/3_a.png");
					break;
				case 3: wsprintf(fi , "data/img/shot/small/4_a.png");
					break;
				case 4: wsprintf(fi , "data/img/shot/medium/1_a.png");
					break;
				case 5: wsprintf(fi , "data/img/shot/medium/2_a.png");
					break;
				case 6: wsprintf(fi , "data/img/shot/medium/3_a.png");
					break;
				case 7: wsprintf(fi , "data/img/shot/medium/4_a.png");
					break;
				case 8: wsprintf(fi , "data/img/shot/medium2/1_a.png");
					break;
				case 9: wsprintf(fi , "data/img/shot/medium2/2_a.png");
					break;
				case 10: wsprintf(fi , "data/img/shot/medium2/3_a.png");
					break;
				case 11: wsprintf(fi , "data/img/shot/medium2/4_a.png");
					break;
				case 12: wsprintf(fi , "data/img/shot/medium2/5_a.png");
					break;
				case 13: wsprintf(fi , "data/img/shot/medium2/6_a.png");
					break;
				case 14: wsprintf(fi , "data/img/shot/rice/1_a.png");
					break;
				case 15: wsprintf(fi , "data/img/shot/rice/2_a.png");
					break;
				case 16: wsprintf(fi , "data/img/shot/rice/3_a.png");
					break;
				case 17: wsprintf(fi , "data/img/shot/rice/4_a.png");
					break;
				case 18: wsprintf(fi , "data/img/shot/uroko/1_a.png");
					break;
				case 19: wsprintf(fi , "data/img/shot/uroko/2_a.png");
					break;
				case 20: wsprintf(fi , "data/img/shot/uroko/3_a.png");
					break;
				case 21: wsprintf(fi , "data/img/shot/uroko/4_a.png");
					break;
				case 22: wsprintf(fi , "data/img/shot/butterfly/1_2a.png");
					break;
				case 23: wsprintf(fi , "data/img/shot/butterfly/2_2a.png");	break;
				case 24: wsprintf(fi , "data/img/shot/butterfly/3_2a.png");	break;
				case 25: wsprintf(fi , "data/img/shot/butterfly/4_2a.png");	break;
				case 26: wsprintf(fi , "data/img/shot/big/1_a.png");
					break;
				case 27: wsprintf(fi , "data/img/shot/big/2_a.png");
					break;
				case 28: wsprintf(fi , "data/img/shot/big/3_a.png");
					break;
				case 29: wsprintf(fi , "data/img/shot/big/4_a.png");
					break;
				case 30: wsprintf(fi , "data/img/shot/big/5_a.png");
					break;
				case 31: wsprintf(fi , "data/img/shot/vbig/1_2a.png");
					break;
				case 32: wsprintf(fi , "data/img/shot/vbig/2_2a.png");	break;
				case 33: wsprintf(fi , "data/img/shot/vbig/3_2a.png");	break;
				case 34: wsprintf(fi , "data/img/shot/vbig/4_2a.png");	break;
				case 35: wsprintf(fi , "data/img/shot/katana/1_a.png");
					break;
				case 36: wsprintf(fi , "data/img/shot/katana/2_a.png");
					break;
				case 37: wsprintf(fi , "data/img/shot/katana/3_a.png");
					break;
				case 38: wsprintf(fi , "data/img/shot/huda/1_a.png");
					break;
				case 39: wsprintf(fi , "data/img/shot/huda/2_a.png");	break;
				case 40: wsprintf(fi , "data/img/shot/huda/3_a.png");	break;
				case 41: wsprintf(fi , "data/img/shot/huda/4_a.png");	break;
				case 42: wsprintf(fi , "data/img/shot/huda/5_a.png");	break;
				case 43: wsprintf(fi , "data/img/shot/jerry/1_a.png");
					break;
				case 44: wsprintf(fi , "data/img/shot/jerry/2_a.png");
					break;
				case 45: wsprintf(fi , "data/img/shot/jerry/3_a.png");
					break;
				case 46: wsprintf(fi , "data/img/shot/jerry/4_a.png");
					break;
				case 47: wsprintf(fi , "data/img/shot/kunai/1_a.png");
					break;
				case 48: wsprintf(fi , "data/img/shot/kunai/2_a.png");
					break;
				case 49: wsprintf(fi , "data/img/shot/kunai/3_a.png");
					break;
				case 50: wsprintf(fi , "data/img/shot/kunai/4_a.png");
					break;
				case 51: wsprintf(fi , "data/img/shot/kunai/5_a.png");
					break;
				case 52: wsprintf(fi , "data/img/shot/rice/5_a.png");
					break;
				case 53: wsprintf(fi , "data/img/shot/medium/5_a.png");
					break;
				case 54: wsprintf(fi , "data/img/shot/ice/1_a.png");
					break;
				case 55: wsprintf(fi , "data/img/shot/ice/2_a.png");
					break;
				case 56: wsprintf(fi , "data/img/shot/ice/3_a.png");
					break;
				case 57: wsprintf(fi , "data/img/shot/ice/4_a.png");
					break;
			}
			if( (gra_e_shot[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
		for(int i=0;i<8;i++){
			SetTransColor(0,0,0);
			switch(i){
				case 0: wsprintf(fi , "data/img/shot/butterfly/1_a.png");
					break;
				case 1: wsprintf(fi , "data/img/shot/butterfly/2_a.png");	break;
				case 2: wsprintf(fi , "data/img/shot/butterfly/3_a.png");	break;
				case 3: wsprintf(fi , "data/img/shot/butterfly/4_a.png");	break;
				case 4: wsprintf(fi , "data/img/shot/vbig/1_a.png");
					break;
				case 5: wsprintf(fi , "data/img/shot/vbig/2_a.png");	break;
				case 6: wsprintf(fi , "data/img/shot/vbig/3_a.png");	break;
				case 7: wsprintf(fi , "data/img/shot/vbig/4_a.png");	break;
			}
			if( (gra_e_shot2[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SEs_Reset(){
	E_Shot.clear();
	return;
}

void SEs_Main(){
	for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
		int img2 = (*it).img;
		if(Game.skip==false){
			if((*it).late==0)	SEs_Move(it);
			else			(*it).late--;
		}
		if(((*it).pattern==10||(*it).pattern==11)&&!((*it).y>480+(*it).img_y/2)){}	
		else if((*it).x<0-(*it).img_x/2 || (*it).x>450+(*it).img_x/2 || (*it).y<0-(*it).img_y/2 || (*it).y>480+(*it).img_y/2){
			if((*it).dele_flag!=2&&(*it).count>=1){
				it = E_Shot.erase(it);
				it--;
				continue;
			}
		}
		if((*it).i_hanyou[7]==1){
			if((*it).pattern!=23&&(*it).pattern!=25)	SEf_Make((*it).x,(*it).y,2,(*it).img);
			it = E_Shot.erase(it);
			it--;
			continue;
		}
		/*
		if(debug_AI==1){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			float d = 20;
			if(sq<=d)	(*it).debug_AI = true;
			else		(*it).debug_AI = false;
		}
		*/
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	return;
}

void SEs_Draw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
		int img2 = (*it).img;
		if((*it).late>0){
			if((*it).effect==0){
				int flash = (*it).flash/(*it).max_late;
				float large = 2.00 / (*it).max_late;
				int time = (*it).max_late - (*it).late;
				if(img2==gra_e_shot[14]||img2==gra_e_shot[18]||img2==gra_e_shot[22]||img2==gra_e_shot[38]||img2==gra_e_shot[47]||img2==gra_e_shot[35]||img2==gra_e_shot[54])	img2 = gra_e_shot[4];
				if(img2==gra_e_shot[15]||img2==gra_e_shot[19]||img2==gra_e_shot[23]||img2==gra_e_shot[39]||img2==gra_e_shot[48]||img2==gra_e_shot[36]||img2==gra_e_shot[55])	img2 = gra_e_shot[5];
				if(img2==gra_e_shot[16]||img2==gra_e_shot[20]||img2==gra_e_shot[24]||img2==gra_e_shot[40]||img2==gra_e_shot[49]||img2==gra_e_shot[56])	img2 = gra_e_shot[6];
				if(img2==gra_e_shot[17]||img2==gra_e_shot[21]||img2==gra_e_shot[25]||img2==gra_e_shot[41]||img2==gra_e_shot[50]||img2==gra_e_shot[57])	img2 = gra_e_shot[7];
				if(img2==gra_e_shot[42]||img2==gra_e_shot[51]||img2==gra_e_shot[37])	img2 = gra_e_shot[12];
				if(img2==gra_e_shot[52])	img2 = gra_e_shot[53];
				if(img2==gra_e_shot[31])	img2 = gra_e_shot2[4];
				if(img2==gra_e_shot[32])	img2 = gra_e_shot2[5];
				if(img2==gra_e_shot[33])	img2 = gra_e_shot2[6];
				if(img2==gra_e_shot[34])	img2 = gra_e_shot2[7];
				if(img2==gra_e_shot[43])	img2 = gra_e_shot[26];
				if(img2==gra_e_shot[44])	img2 = gra_e_shot[27];
				if(img2==gra_e_shot[45])	img2 = gra_e_shot[28];
				if(img2==gra_e_shot[46])	img2 = gra_e_shot[29];
				SetDrawBlendMode(DX_BLENDMODE_ADD,time*flash);
				if(img2==gra_e_shot[31]||img2==gra_e_shot[32]||img2==gra_e_shot[33]||img2==gra_e_shot[34])	SetDrawBlendMode(DX_BLENDMODE_ALPHA,time*flash);
				if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, 3.00-time*large, (*it).angle, img2, TRUE, FALSE);
			}
		}
		else{
			if((*it).img==gra_e_shot[31]||(*it).img==gra_e_shot[32]||(*it).img==gra_e_shot[33]||(*it).img==gra_e_shot[34]||(*it).img==gra_e_shot[22]||(*it).img==gra_e_shot[23]||(*it).img==gra_e_shot[24]||(*it).img==gra_e_shot[25]||(*it).img==gra_e_shot[35]||(*it).img==gra_e_shot[36]||(*it).img==gra_e_shot[37]){
				SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash-50);
				int img;
				if((*it).img==gra_e_shot[31])	img = gra_e_shot2[4];
				if((*it).img==gra_e_shot[32])	img = gra_e_shot2[5];
				if((*it).img==gra_e_shot[33])	img = gra_e_shot2[6];
				if((*it).img==gra_e_shot[34])	img = gra_e_shot2[7];
				if((*it).img==gra_e_shot[22]){
					img = gra_e_shot2[0];
					img2 = gra_e_shot[4];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-150);
				}
				if((*it).img==gra_e_shot[23]){
					img = gra_e_shot2[1];
					img2 = gra_e_shot[5];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-150);
				}
				if((*it).img==gra_e_shot[24]){
					img = gra_e_shot2[2];
					img2 = gra_e_shot[6];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-150);
				}
				if((*it).img==gra_e_shot[25]){
					img = gra_e_shot2[3];
					img2 = gra_e_shot[7];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-150);
				}
				if((*it).img==gra_e_shot[35]){
					img = gra_e_shot[8];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-100);
				}
				if((*it).img==gra_e_shot[36]){
					img = gra_e_shot[9];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-100);
				}
				if((*it).img==gra_e_shot[37]){
					img = gra_e_shot[12];
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash-100);
				}
				if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle, img, TRUE, FALSE);
			}
			if(!(GameScene==1&&Boss.img[0]==gra_boss[2][0])&&((*it).img==gra_e_shot[26]||(*it).img==gra_e_shot[27]||(*it).img==gra_e_shot[28]||(*it).img==gra_e_shot[29]||(*it).img==gra_e_shot[30])){
				SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			}
			else if((*it).img==gra_e_shot[31]||(*it).img==gra_e_shot[32]||(*it).img==gra_e_shot[33]||(*it).img==gra_e_shot[34]){
				SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			}
			else{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			}
			if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle, img2, TRUE, FALSE);
			if(Game.skip==false)	(*it).count++;
			//DrawBox((*it).atari_x[0],(*it).atari_y[0],(*it).atari_x[1],(*it).atari_y[1],0,TRUE);
			if((*it).count>1 && (*it).b_atari==true &&
			   Player.atari_x[0]<(*it).atari_x[1] &&
			   Player.atari_x[1]>(*it).atari_x[0] &&
			   Player.atari_y[0]<(*it).atari_y[1] &&
			   Player.atari_y[1]>(*it).atari_y[0]){
				if(Player.nodamage==0 && Player.miss==0){
					SPlaySound(2);
					Player.miss = 8;
				}
				SEf_Make((*it).x,(*it).y,2,(*it).img);
				it = E_Shot.erase(it);
				it--;
				continue;
			}
			float plus=0;
			if(SAVE.Chara==1)	plus = 5;
			if(Player.x-Player.img_x/2-plus<(*it).atari_x[1] &&
			   Player.x+Player.img_x/2+plus>(*it).atari_x[0] &&
			   Player.y-Player.img_y/2-plus<(*it).atari_y[1] &&
			   Player.y+Player.img_y/2+plus>(*it).atari_y[0] &&
			   (*it).b_atari==true){
				if((*it).graze==true && Player.miss==0){
					SPlaySound(3);
					int loop = 1;
					if(Bomb.life==1)	loop = 3;
					for(int i=0;i<loop;i++){
						SEf_Make(Player.x,Player.y,9,gra_graze_effect);
						if(Game.graze<65534){
							Game.graze ++;
							Game.stage_graze[Game.stage]++;
							SSc_AddScore(1000);
						}
						Game.maxpoint += 10;
					}
					(*it).graze = false;
				}
			}
			if((*it).dele_flag==0&& Bomb.life==1&&Bomb.count>=10&&(*it).count>1&&Game.skip==false){
				float sx = Bomb.x - (*it).x;
				float sy = Bomb.y - (*it).y;
				float sq = sqrt(sx*sx+sy*sy);
				if(sq<70+(*it).img_y/2){
					SIt_Make((*it).x,(*it).y,270,gra_item[4],1);
					SEf_Make((*it).x,(*it).y,2,(*it).img);
					it = E_Shot.erase(it);
					it--;
					continue;
				}
			}
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	
	return;
}

void SEs_Make(float x,float y,float angle,float speed,int img,int late,float f_speed,int f_count,int pattern,int effect){
	int limit = 1;
	if(SAVE.Level==3)	limit = 2;
	for(int a=0;a<limit;a++){
		if(E_Shot.size()==5012)	return;
		E_SHOTDATA P;
		P.x = x;
		P.y = y;
		for(int i=0;i<ATARI_NUM;i++){
			P.atari_x[i] = x;
			P.atari_y[i] = y;
		}
		P.move_x = cos(Radian(angle,TRUE));
		P.move_y = sin(Radian(angle,TRUE));
		P.speed = speed+speed*(float)(a-1)*0.2;
		P.img = img;
		P.late = late;
		P.max_late = late;
		P.pattern = pattern;
		P.f_speed = f_speed+f_speed*(float)(a-1)*0.2;
		P.f_count = f_count;
		P.effect = effect;
		P.count = 0;
		P.dele_flag = 0;
		P.graze = true;
		P.b_atari = true;
		P.debug_AI = false;
		P.flash = 255;
		P.angle = atan2(P.move_y,P.move_x)+1.57;
		GetGraphSize(P.img,&P.img_x,&P.img_y);
		P.large = 1.0;
		for(int i=0;i<8;i++){
			P.i_hanyou[i] = 0;
			P.d_hanyou[i] = 0;
		}
		
		E_Shot.push_back(P);
	}
	return;
}

void SEs_NWay(float x,float y,float angle,int number,float speed,int img,int late,float n_way_plus,float f_speed,int f_count,int pattern,int effect){
	float base_angle;
	float sx = Player.x - x;
	float sy = Player.y - y;
	float sq = sqrt(sx*sx+sy*sy);
	E_SHOTDATA P;
	P.move_x = sx / sq;
	P.move_y = sy / sq;
	base_angle = Radian(atan2(P.move_y,P.move_x),FALSE);
	for(int i=0;i<number;i++){
		if(i!=0)	effect = 1;
		if(n_way_plus==0&&number%2==1&&i==0){
			SEs_Make(x,y,base_angle,speed,img,late,f_speed,f_count,pattern,effect);
		}
		else if(number%2==0){//偶数弾（自機外し）
			float last_angle;
			if(i%2==0)	last_angle = base_angle - angle/2 - angle*(i/2) + n_way_plus;
			else		last_angle = base_angle + angle/2 + angle*(i/2) + n_way_plus;
			SEs_Make(x,y,last_angle,speed,img,late,f_speed,f_count,pattern,effect);
		}
		else{//奇数弾（自機狙い）
			float last_angle;
			if(i%2==0)	last_angle = base_angle - angle*(i/2) + n_way_plus;
			else		last_angle = base_angle + angle*((i+1)/2) + n_way_plus;
			SEs_Make(x,y,last_angle,speed,img,late,f_speed,f_count,pattern,effect);
		}
	}
	return;
}

void SEs_Move(list<E_SHOTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	int g = (*it).img;
	
	if((*it).f_count>0&&c==1){
		(*it).d_hanyou[0] = ((*it).f_speed-(*it).speed) / ((*it).f_count-1);
	}
	if(p==-1){//演出用
		(*it).i_hanyou[7] = 1;
	}
	else if(p==1){//1-5
		if(c==1){
			(*it).d_hanyou[0] = (*it).f_speed / 30;
			(*it).d_hanyou[1] = (*it).speed;
			(*it).speed = (*it).f_speed;
		}
		if(c<30)	(*it).speed -= (*it).d_hanyou[0];
		else if(c<60)	(*it).speed = 0;
		else if(c==60){
			SPlaySound(11);
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			(*it).move_x = sx/sq;
			(*it).move_y = sy/sq;
			(*it).speed = (*it).d_hanyou[1];
		}
	}
	else if(p==2){//1-6
		if(c==1){
			(*it).d_hanyou[0] = (*it).speed / 60.0;
			(*it).speed = (*it).f_speed;
		}
		if(c<60)	(*it).speed += (*it).d_hanyou[0];
	}
	else if(p==3){//No.001 ギャザーグラビテーション
		float sx = (*it).x - Boss.x;
		float sy = (*it).y - (Boss.y-60);
		float sq = sqrt(sx*sx+sy*sy);
		if(sq<20){
			(*it).i_hanyou[7] = 1;	
		}
		(*it).dele_flag = 2;
	}
	else if(p==4){//スイカその２
		switch(SAVE.Level){
			case 0:	(*it).speed += 0.03;
                                if(c%30==0&&(*it).y<300){
					SPlaySound(11);
					int effect = 1;
					float angle = Radian(atan2((*it).move_y,(*it).move_x),FALSE);
					effect = 0;
					SEs_Make((*it).x,(*it).y,angle+144,1.5,gra_e_shot[5],10,0.0,0,0,effect);
				}
				break;
			case 1:	(*it).speed += 0.03;
                                if(c%20==0&&(*it).y<300){
					SPlaySound(11);
					int effect = 1;
					float angle = Radian(atan2((*it).move_y,(*it).move_x),FALSE);
					SEs_Make((*it).x,(*it).y,angle+108,1.5,gra_e_shot[4],10,0.0,0,0,effect);
					effect = 0;
					SEs_Make((*it).x,(*it).y,angle+144,1.5,gra_e_shot[5],10,0.0,0,0,effect);
				}
				break;
			case 2:	(*it).speed += 0.03;
                                if(c%20==0&&(*it).y<300){
					SPlaySound(11);
					for(int i=0;i<5;i++){
						int effect = 1;
						float angle = Radian(atan2((*it).move_y,(*it).move_x),FALSE);
						if(i==0)	effect = 0;
						SEs_Make((*it).x,(*it).y,angle+72*i,2.0,gra_e_shot[5],10,0.0,0,0,effect);
					}
				}
				break;
			case 3:	(*it).speed += 0.03;
                                if(c%15==0&&(*it).y<300){
					SPlaySound(11);
					float x = Player.x;
					float y = Player.y;
					Player.x = Boss.d_hanyou[0];
					Player.y = Boss.d_hanyou[1];
					SEs_NWay((*it).x,(*it).y,35.0,5,2.5,gra_e_shot[5],30);
					Player.x = x;
					Player.y = y;
				}
				break;
		}	
	}
	else if(p==5){//疾風迅雷「風神乱れ撃ち」
		if((*it).i_hanyou[0]==0&&((*it).x<20||(*it).x>400)){
			if((*it).x<20)	(*it).x = 20;
			else		(*it).x = 400;
			SEf_Make((*it).x,(*it).y,4,gra_e_shot[7]);
			SPlaySound(11);
			(*it).img = gra_e_shot[21];
			(*it).i_hanyou[0] = 1;
			(*it).move_x *= -1;
		}
	}
	else if(p==6){//2-7カラス
		float max;
		switch(SAVE.Level){
			case 0:	max = 1.0;	break;
			case 1:	max = 1.5;	break;
			case 2:	max = 2.0;	break;
			case 3:	max = 3.0;	break;
		}
		if((*it).move_y<max)	(*it).move_y += 0.05;
	}
	else if(p==7){//レーヴァテイン
		float max = 1.8;
		if((*it).speed<max)	(*it).speed += 0.02;
	}
	else if(p==8){//月のいはかさの呪い
		if((*it).y>400&&(*it).i_hanyou[0]==0)	(*it).i_hanyou[0] = 1;
		if((*it).i_hanyou[0]==1){
			(*it).speed -= 0.05;
			if((*it).speed<=0){
				(*it).img = gra_e_shot[35];
				float sx = Player.x - (*it).x;
				float sy = Player.y - (*it).y;
				float sq = sqrt(sx*sx+sy*sy);
				(*it).move_x = sx/sq;
				(*it).move_y = sy/sq;
				(*it).speed = 0.5;
				(*it).i_hanyou[0] = 2;
			}
		}
	}
	else if(p==9){//蛙は口ゆえ蛇に呑まるる
		if(c<100){}
		else if(c==100){
			SPlaySound(11);
			SEf_Make((*it).x,(*it).y,2,(*it).img);
			(*it).speed = 4.5;
		}
		else if(c<125){
			(*it).speed -= 0.18;
		}
		else if(c<130){
			(*it).speed = 0;
		}
		else{
			(*it).i_hanyou[7] = 1;
		}
	}
	else if(p==10 || p==11){//ストレートとカーブの夢郷
		if(c==1){
			(*it).d_hanyou[0] = (*it).speed / 60.0;
		}
		if(c<60){
			(*it).speed -= (*it).d_hanyou[0];
		}
		if(c==90){
			(*it).speed = 5.0;
			float angle = atan2((*it).move_y,(*it).move_x);
			if(p==10)	angle += Radian((*it).f_speed,TRUE);
			else		angle -= Radian((*it).f_speed,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}                                       
	}
	else if(p==12 || p==13){//ストレートとカーブの夢郷
		if(c==1){
			(*it).d_hanyou[0] = ((*it).speed-2.0) / 90.0;
		}
		if(c<90){
			(*it).speed -= (*it).d_hanyou[0];
			float angle = atan2((*it).move_y,(*it).move_x);
			if(c>=20){
				if(p==12)	angle += Radian(2.0,TRUE);
				else		angle -= Radian(2.0,TRUE);
			}
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==14 || p==15){//風符「竜巻旋風ハリケーン」
		int c_limit = 100;
		if(SAVE.Level==3)	c_limit = 120;
		if(c==1){
			(*it).d_hanyou[0] = ((*it).f_speed-(*it).speed) / c_limit;
			if(Game.stage==2)	(*it).d_hanyou[1] = 3.5+0.1*get_rand(10);
			else			(*it).d_hanyou[1] = 3.5+0.1*get_rand(40);
			(*it).d_hanyou[2] = 3.5;
			(*it).speed = (*it).f_speed;
		}
		if(c>=0&&c<c_limit){
			float angle = atan2((*it).move_y,(*it).move_x);
			if(c>=60&&c<72){
				if(p==14)	angle += Radian((*it).d_hanyou[1],TRUE);
				else		angle -= Radian((*it).d_hanyou[1],TRUE);
			}
			else{
				if(p==14)	angle += Radian((*it).d_hanyou[2],TRUE);
				else		angle -= Radian((*it).d_hanyou[2],TRUE);
			}
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed -= (*it).d_hanyou[0];
		}
		if(c<90){
			(*it).dele_flag = 2;
		}
		else{
			(*it).dele_flag = 0;		
		}
	}
	else if(p==16){//文通常２
		if(c==1){
			(*it).d_hanyou[0] = ((*it).speed) / 50.0;
		}
		if(c<51){
			(*it).speed -= (*it).d_hanyou[0];
		}
		else if(c==51){
			SPlaySound(11);
			float rand;
			if(Game.stage==2){
				switch(SAVE.Level){
					case 0:	rand = -1.0+0.1*get_rand(20);	break;
					case 1:	rand = -1.0+0.1*get_rand(20);	break;
					case 2:	rand = -2.0+0.1*get_rand(40);	break;
					case 3:	rand = -3.0+0.1*get_rand(60);	break;
				}
			}
			else{
				switch(SAVE.Level){
					case 0:	rand = -1.0+0.1*get_rand(20);	break;
					case 1:	rand = -1.0+0.1*get_rand(20);	break;
					case 2:	rand = -2.0+0.1*get_rand(40);	break;
					case 3:	rand = -5.0+0.1*get_rand(100);	break;
				}
			}
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float angle;
			if(sx==0){
				if(sy>0)	angle = Radian(90+rand,TRUE);
				else		angle = Radian(270+rand,TRUE);
			}
			else{
				angle = atan2(sy,sx) + Radian(rand,TRUE);
			}
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = (*it).f_speed;
		}
	}
	else if(p==17||p==18){//写符「業火フラッシュオーバー」
		if(c==30){
			SPlaySound(11);
			(*it).move_x = cos(Radian((*it).f_speed,TRUE));
			(*it).move_y = sin(Radian((*it).f_speed,TRUE));
			SEf_Make((*it).x,(*it).y,2,(*it).img);
		}
		if(c>=30&&c<70){
			float angle = atan2((*it).move_y,(*it).move_x);
			if(p==17)	angle += Radian(5.0,TRUE);
			else		angle -= Radian(5.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed -= 0.05;
		}
	}
	else if(p==19){//3-2向日葵妖精
		float max = -(*it).f_speed;
		if((*it).speed>max){
			(*it).speed -= 0.05;
		}
		if((*it).y<0)	(*it).dele_flag = 1;
		else		(*it).dele_flag = 0;
	}
	else if(p==20 || p==21){//鬼符「八神峰の関門」
		if(p==20){
			if(c==1){
				(*it).d_hanyou[0] = (*it).speed;
				(*it).speed = 0;
			}
			(*it).speed = Boss.d_hanyou[1];
			if((*it).speed>0.5&&(*it).y<350){
				//弾の出現率はf_speed(小数第２位まで有効）
				int rand = get_rand(9999);
				if(rand<(*it).f_speed*100){
					SPlaySound(11);
					Boss.d_hanyou[2] += 3.0;
					SEs_Make((*it).x,(*it).y,Boss.d_hanyou[2],(*it).d_hanyou[0],gra_e_shot[4],30,0.0,0,21);				
				}
			}
		}
		if(p==21){
			if(c==1){
				(*it).d_hanyou[0] = (*it).speed / 40.0;
			}
			if(c<=40){
				(*it).speed = (*it).d_hanyou[0] * c;
			}
		}
	}
	else if(p==22){//天符「天狗隠しの怪」
		(*it).dele_flag = 1;
		if(c==1){
			(*it).d_hanyou[0] = (*it).speed/30.0;
		}
		if(c<=30)	(*it).speed -= (*it).d_hanyou[0];
		else		(*it).speed = 0;
		if(c==40){
			float angle = Radian(atan2(CENTER_Y-(*it).y,CENTER_X-(*it).x),FALSE);
			SLas_Make((*it).x,(*it).y,angle,10.0,gra_laser[0],30,0,0);
		}
		if(c==160){
			SEf_Make((*it).x,(*it).y,2,(*it).img);
			(*it).i_hanyou[7] = 1;
		}	
	}
	else if(p==23 || p==24 || p==25 || p==26){//結界「カーストファンタズム」
		if(p==23 || p==25){
			(*it).dele_flag = 1;
			if(c==1){
				(*it).d_hanyou[0] = (*it).speed/30.0;
			}
			if(c==40){
				SEf_Make((*it).x,(*it).y,2,(*it).img);
				(*it).b_atari = false;
				(*it).img = -1;
			}
			if(c<=30)	(*it).speed -= (*it).d_hanyou[0];
			else		(*it).speed = 0;
			if(p==23){
				switch(SAVE.Level){
					case 0:
						if(c==60 || c==70){
							SPlaySound(10);
							if(c==60){
								float sx = Player.x - (*it).x;
								float sy = Player.y - (*it).y;
								(*it).d_hanyou[1] = Radian(atan2(sy,sx),FALSE);
								(*it).i_hanyou[0] = 0;
							}
							float d = (c-40)*2;
							for(int i=0;i<4;i++){
								float angle = Radian((*it).d_hanyou[1]+45*(*it).i_hanyou[0]+90*i,TRUE);
								float x = (*it).x + d*cos(angle);
								float y = (*it).y + d*sin(angle);
								for(int a=0;a<8;a++){
									SEs_Make(x,y,(*it).d_hanyou[1]+45*a,0.5,gra_e_shot[20+(*it).i_hanyou[0]%2],10,1.0,0,24,a%8);						
								}
							}
							(*it).i_hanyou[0]++; 	
						}
						break;
					case 1:
						if(c==60 || c==70){
							SPlaySound(10);
							if(c==60){
								float sx = Player.x - (*it).x;
								float sy = Player.y - (*it).y;
								(*it).d_hanyou[1] = Radian(atan2(sy,sx),FALSE);
								(*it).i_hanyou[0] = 0;
							}
							float d = (c-40)*2;
							for(int i=0;i<4;i++){
								float angle = Radian((*it).d_hanyou[1]+45*(*it).i_hanyou[0]+90*i,TRUE);
								float x = (*it).x + d*cos(angle);
								float y = (*it).y + d*sin(angle);
								for(int a=0;a<8;a++){
									SEs_Make(x,y,(*it).d_hanyou[1]+45*a,0.5,gra_e_shot[20+(*it).i_hanyou[0]%2],10,1.5,0,24,a%8);						
								}
							}
							if(c==70){
								for(int i=0;i<4;i++){
									float angle = Radian((*it).d_hanyou[1]+90*i,TRUE);
									float de = d*sqrt(2);
									float x = (*it).x + de*cos(angle);
									float y = (*it).y + de*sin(angle);
									for(int a=0;a<8;a++){
										SEs_Make(x,y,(*it).d_hanyou[1]+45*a,1.0,gra_e_shot[20+(*it).i_hanyou[0]%2],10,1.5,0,24,a%8);						
									}
								}
							}
							(*it).i_hanyou[0]++; 	
						}
						break;
					case 2:
						if(c==60 || c==70){
							SPlaySound(10);
							if(c==60){
								float sx = Player.x - (*it).x;
								float sy = Player.y - (*it).y;
								(*it).d_hanyou[1] = Radian(atan2(sy,sx),FALSE);
								(*it).i_hanyou[0] = 0;
							}
							float d = (c-40)*2;
							for(int i=0;i<4;i++){
								float angle = Radian((*it).d_hanyou[1]+45*(*it).i_hanyou[0]+90*i,TRUE);
								float x = (*it).x + d*cos(angle);
								float y = (*it).y + d*sin(angle);
								for(int a=0;a<8;a++){
									SEs_Make(x,y,(*it).d_hanyou[1]+45*a,1.0,gra_e_shot[20+(*it).i_hanyou[0]%2],10,2.5,0,24,a%8);						
								}
							}
							if(c==70){
								for(int i=0;i<4;i++){
									float angle = Radian((*it).d_hanyou[1]+90*i,TRUE);
									float de = d*sqrt(2);
									float x = (*it).x + de*cos(angle);
									float y = (*it).y + de*sin(angle);
									for(int a=0;a<8;a++){
										SEs_Make(x,y,(*it).d_hanyou[1]+45*a,1.0,gra_e_shot[20+(*it).i_hanyou[0]%2],10,2.5,0,24,a%8);						
									}
								}
							}
							(*it).i_hanyou[0]++; 	
						}
						break;
					case 3:
						if(c==60 || c==70){
							SPlaySound(10);
							if(c==60){
								float sx = Player.x - (*it).x;
								float sy = Player.y - (*it).y;
								(*it).d_hanyou[1] = Radian(atan2(sy,sx),FALSE);
								(*it).i_hanyou[0] = 0;
							}
							float d = (c-40)*2;
							for(int i=0;i<4;i++){
								float angle = Radian((*it).d_hanyou[1]+45*(*it).i_hanyou[0]+90*i,TRUE);
								float x = (*it).x + d*cos(angle);
								float y = (*it).y + d*sin(angle);
								for(int a=0;a<8;a++){
									SEs_Make(x,y,(*it).d_hanyou[1]+45*a,1.0,gra_e_shot[20+(*it).i_hanyou[0]%2],10,2.5,0,24,a%8);						
								}
							}
							if(c==70){
								for(int i=0;i<4;i++){
									float angle = Radian((*it).d_hanyou[1]+90*i,TRUE);
									float de = d*sqrt(2);
									float x = (*it).x + de*cos(angle);
									float y = (*it).y + de*sin(angle);
									for(int a=0;a<8;a++){
										SEs_Make(x,y,(*it).d_hanyou[1]+45*a,1.0,gra_e_shot[20+(*it).i_hanyou[0]%2],10,2.5,0,24,a%8);						
									}
								}
							}
							(*it).i_hanyou[0]++; 	
						}
						break;
				}
			}
			if(p==25){
				if(c>=60){
					switch(SAVE.Level){
						case 0:
							if(c%35==0){
								SPlaySound(10);
								(*it).i_hanyou[0] = c-5+get_rand(10);
								for(int i=0;i<3;i++){
									SEs_Make((*it).x,(*it).y,(*it).i_hanyou[0]+120*i,1.5,gra_e_shot[52],10,2.0,0,26,i%3);						
								}
							}
							break;
						case 1:
							if(c%35==0){
								SPlaySound(10);
								(*it).i_hanyou[0] = c-5+get_rand(10);
								for(int i=0;i<4;i++){
									SEs_Make((*it).x,(*it).y,(*it).i_hanyou[0]+90*i,1.5,gra_e_shot[52],10,2.0,0,26,i%4);						
								}
							}
							break;
						case 2:
							if(c%30==0){
								SPlaySound(10);
								(*it).i_hanyou[0] = c-5+get_rand(10);
								for(int i=0;i<4;i++){
									SEs_Make((*it).x,(*it).y,(*it).i_hanyou[0]+90*i,2.0,gra_e_shot[52],10,2.5,0,26,i%4);						
								}
							}
							break;
						case 3:
							if(c%16==0){
								SPlaySound(10);
								(*it).i_hanyou[0] = c-5+get_rand(10);
								for(int i=0;i<4;i++){
									SEs_Make((*it).x,(*it).y,(*it).i_hanyou[0]+90*i,2.0,gra_e_shot[52],10,2.5,0,26,i%4);						
								}
							}
							break;
					}
				}
			}
			if(c==180){
				(*it).i_hanyou[7] = 1;
			}	
		}
		else if(p==24){
			if(c==1){
				(*it).d_hanyou[0] = ((*it).f_speed-(*it).speed) / 30.0;
			}
			if(c<=30){
				(*it).speed += (*it).d_hanyou[0];
			}
		}
		else if(p==26){
			if(c==1){
				(*it).d_hanyou[0] = (0-(*it).speed) / 30.0;
			}
			if(c<=30){
				(*it).speed += (*it).d_hanyou[0];
			}
			if(c==30){
				SPlaySound(11);
				(*it).speed = (*it).f_speed;
				float sx = Player.x - (*it).x;
				float sy = Player.y - (*it).y;
				float angle = atan2(sy,sx);
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
		}
	}
	else if(p==27){//戯符「神々のアジャラ空間」
		if(c==60){
			SEf_Make((*it).x,(*it).y,2,(*it).img);
			(*it).i_hanyou[7] = 1;		
		}
	}
	else if(p==28){//３面紫通常４
		if(c==1){
			(*it).d_hanyou[0] = ((*it).speed-(*it).f_speed)/60.0;
			(*it).speed = (*it).f_speed;
		}
		if(c>=1&&c<61){
			(*it).speed += (*it).d_hanyou[0];
		}
	}
	else if(p==29){//魅了「幻想誘死蝶」
		if(c==1){
			(*it).d_hanyou[0] = (0-(*it).f_speed)/80.0;
			(*it).d_hanyou[1] = (*it).speed / 180.0;
			(*it).i_hanyou[0] = (*it).f_count;
			(*it).f_count = 0;
			(*it).speed = (*it).f_speed;
		}
		if(c>=1&&c<81){
			(*it).speed += (*it).d_hanyou[0];
		}
		if(c==81)	(*it).speed = 0;
		if(c>=81&&c<261){
			if(c==81)	SPlaySound(19);
			(*it).speed += (*it).d_hanyou[1];
			if(c<200){
				float angle = atan2((*it).move_y,(*it).move_x);
				if((*it).i_hanyou[0]==0){
					angle -= Radian(1.5,TRUE);
				}
				else{
					angle += Radian(1.5,TRUE);
				}
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
		}
	}
	else if(p==30 || p==31){//スイカその２
		float angle = atan2((*it).move_y,(*it).move_x);
		if(c<80){
			if(p==30)	angle += Radian(2.0,TRUE);
			else if(p==31)	angle -= Radian(2.0,TRUE);
         	}
	        (*it).move_x = cos(angle);
		(*it).move_y = sin(angle);
		int cp = 4;
		if(c<50)	cp = 8;
		if(c%cp==0){
			SPlaySound(11);
			SEs_Make((*it).x,(*it).y,angle+2*c,0.0,gra_e_shot[5],30,2.0,0,32);
			/*
			float x = Player.x;
			float y = Player.y;
			Player.x = CENTER_X;
			Player.y = CENTER_Y;
			SEs_NWay((*it).x,(*it).y,0.0,1,0.0,gra_e_shot[5],30,0.0,2.0,0,32);
			Player.x = x;
			Player.y = y;
			*/
		}
		(*it).speed += 0.05;
		Boss.i_hanyou[0] ++;	
	}
	else if(p==32){//スイカその２
		if(c==1&&Boss.i_hanyou[1]>0){
			(*it).count = 0;
		}
		if(c==2){
			(*it).d_hanyou[0] = (*it).f_speed / 60.0;
		}
		if(c>=2&&c<62){
			(*it).speed += (*it).d_hanyou[0];
		}	
	}
	else if(p==33){//反射弾
		if((*it).i_hanyou[0]==0&&((*it).x<20||(*it).x>400||(*it).y<15)){
			(*it).i_hanyou[0] = 1;
			if((*it).x<20){
				(*it).x = 20;
				(*it).move_x *= -1;
			}
			if((*it).x>400){
				(*it).x = 400;
				(*it).move_x *= -1;
			}
			if((*it).y<15){
				(*it).y = 15;
				(*it).move_y *= -1;
				(*it).i_hanyou[0] = 0;
			}
		}
	}
	else if(p==34||p==35){//「夢想風神」
		if(c<50){
			float angle = atan2((*it).move_y,(*it).move_x);
			if(p==34)	angle += Radian(3.6,TRUE);
			else		angle -= Radian(3.6,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==36){//鬼符「芙蓉鬼山岳波」
		if(c%10==0&&c>0){
			float angle = Radian(atan2((*it).move_y,(*it).move_x),FALSE);
			SPlaySound(11);
			for(int i=0;i<6;i++){
				int plus = c/10;
				float speed;
				switch(SAVE.Level){
					case 1:	speed = 1.5;	break;
					case 2:	speed = 2.0;	break;
					case 3:	speed = 3.0;	break;
				}
				SEs_Make((*it).x,(*it).y,angle+60*i,speed,gra_e_shot[23],10,0.0,300);			
			}
		}
	}
	else if(p==37){//戯符「メンフェンティス降臨」
		if(c==180){
			SEf_Make((*it).x,(*it).y,2,(*it).img);
			(*it).i_hanyou[7] = 1;		
		}
	}
	else if(p==38 || p==39){//魅惑「妖艶黒死蝶」
		if(c==1){
			(*it).d_hanyou[0] = (*it).f_speed / 180.0;
			(*it).d_hanyou[1] = (*it).speed / 240.0;
			(*it).i_hanyou[0] = (*it).f_count;
			(*it).f_count = 0;
			(*it).speed = (*it).f_speed;
		}
		if(c>=1&&c<181){
			(*it).speed -= (*it).d_hanyou[0];
		}
		if(c==181)	(*it).speed = 0;
		if(c==181+60*(p-38))	SPlaySound(11);
		if(c>=181+60*(p-38)){
			if(c<181+60*(p-38)+240){
				(*it).speed += (*it).d_hanyou[1];
			}
			if(c<181+60*(p-38)+(*it).i_hanyou[0]){
				float angle = atan2((*it).move_y,(*it).move_x);
				if(p==38){
					angle -= Radian(1.0,TRUE);
				}
				else{
					angle += Radian(1.0,TRUE);
				}
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
		}
	}
	else if(p>=40 && p<=42){//禁忌「真弾幕結界 -久遠素懐-」
		if(c==0){
			(*it).i_hanyou[0] = (*it).f_speed;//動きが止まるまでの時間
			(*it).i_hanyou[1] = (*it).f_count;//動き始めるまでの時間
			(*it).d_hanyou[0] = (*it).speed;//最終スピード
			(*it).d_hanyou[1] = (*it).speed / 60.0;//加速度
			(*it).f_count = 0;
			(*it).speed = 2.0;
			if(p==41)	(*it).speed = 4.5;
			if(p==42)	(*it).speed = 3.0;
		}
		if(c<1+(*it).i_hanyou[0]){}
		else{
			if(c==1+(*it).i_hanyou[0]){
				SPlaySound(11);
				(*it).speed = 0;
			}
			if((*it).i_hanyou[2]>0){
				if((*it).i_hanyou[2]>=1+(*it).i_hanyou[1] && (*it).i_hanyou[2]<1+(*it).i_hanyou[1]+60){
					(*it).speed += (*it).d_hanyou[1];
				}
				(*it).i_hanyou[2]++;
			}
		}
	}
	else if(p>=43 && p<=45){//「終焉と幻想の境界」
		if(c==1){
			(*it).i_hanyou[0] = (*it).f_count;
			(*it).f_count = 0;
			(*it).d_hanyou[0] = ((*it).speed-(*it).f_speed)/60.0;
		}
		if(c<(*it).i_hanyou[0]){
			(*it).speed = (*it).f_speed;
		}
		else if(c<(*it).i_hanyou[0]+60){
			if(c==(*it).i_hanyou[0])	SPlaySound(11);
			(*it).speed += (*it).d_hanyou[0];
		}
		if(c>=(*it).i_hanyou[0]-40 && c<(*it).i_hanyou[0]+40){
			float angle = atan2((*it).move_y,(*it).move_x);
			if(p==44)	angle += Radian(0.5,TRUE);
			if(p==45)	angle -= Radian(0.5,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==46 || p==47){//「終焉と幻想の境界」
		if(c==1){
			float angle = atan2((*it).move_y,(*it).move_x);
			float angle2 = atan2(Player.y-(*it).y,Player.x-(*it).x);
			if(p==46)	(*it).d_hanyou[0] = (angle2-angle)/90.0;
			else		(*it).d_hanyou[0] = (2*PI-(angle2-angle))/90.0;
			(*it).i_hanyou[0] = (*it).f_count;
			(*it).f_count = 0;
			(*it).d_hanyou[1] = (*it).speed/(*it).i_hanyou[0];
			(*it).d_hanyou[2] = (*it).f_speed/20.0;
			(*it).speed = (*it).f_speed;
		}
		if(c<21){
			(*it).speed -= (*it).d_hanyou[2];
		}
		else{
			c -= 20;
			if(c<91){
				float angle = atan2((*it).move_y,(*it).move_x);
				if(p==46)	angle += (*it).d_hanyou[0];
				else		angle -= (*it).d_hanyou[0];
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
			if(c<(*it).i_hanyou[0]){
				(*it).speed += (*it).d_hanyou[1];
			}
		}
	}
	else if(p==48){//「終焉と幻想の境界」
		if(c==1){
			(*it).d_hanyou[0] = (*it).speed/90.0;
			(*it).speed = 0.01;
			(*it).dele_flag = 1;
		}
		if(Boss.countdown<=100 && Boss.countdown>10){
			(*it).speed += (*it).d_hanyou[0];
		}
	}
	else if(p==49 || p==50 || p==51){//Ex-2
		if(c==1){
			(*it).d_hanyou[0] = (*it).f_speed / 30;
			(*it).d_hanyou[1] = (*it).speed;
			(*it).speed = (*it).f_speed;
		}
		if(c<30)	(*it).speed -= (*it).d_hanyou[0];
		else if(c<60)	(*it).speed = 0;
		else if(c==60){
			SPlaySound(11);
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float angle = atan2(sy,sx);
			if(p==50)	angle += Radian(30,TRUE);
			if(p==51)	angle -= Radian(30,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = (*it).d_hanyou[1];
		}
	}
	else if(p==52 || p==53){//Ex中ボス通常２
		if(c%5==0&&c>0){
			for(int i=0;i<5;i++){
				SPlaySound(10);
				SEs_NWay((*it).x,(*it).y,0.0,1,3.0+0.5*i,gra_e_shot[18],15,0.0);
			}
		}
		if(p==53){
			float angle = atan2((*it).move_y,(*it).move_x);
			angle += Radian(1.5,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);		
		}
	}
	else if(p==54){//神判「トゥルダクの盟神探湯」
		if(c==1){
			(*it).d_hanyou[0] = (*it).f_speed;//加速度
		}
		if(c<120)	(*it).speed -= (*it).d_hanyou[0];
	}
	else if(p==55){//幻影「十王裁判」
		(*it).speed -= 0.1;
		if((*it).speed<0){
			if((*it).speed<-2.0)	(*it).speed = -2.0;
			if((*it).i_hanyou[0]==0){
				(*it).move_x *= -1;
			        (*it).i_hanyou[0] = 1;
			}
		}
	}
	else if(p>=56 && p<=59){//夢終「エンドオブジャッジメント」
		if(c==1){
			float x = (*it).x - Boss.x;
			float y = (*it).y - Boss.y;
			float d = sqrt(x*x+y*y);
			(*it).d_hanyou[0] = d;
			(*it).d_hanyou[1] = atan2(y,x);
			(*it).speed = 0;
			(*it).dele_flag = 1;
		}
		if(Boss.i_hanyou[0]>=p-55){
			(*it).dele_flag = 0;
			if((*it).i_hanyou[0]<90)	(*it).speed += 0.025;
			(*it).i_hanyou[0]++;
		}
		else{
			(*it).x = Boss.x + (*it).d_hanyou[0]*cos((*it).d_hanyou[1]); 
			(*it).y = Boss.y + (*it).d_hanyou[0]*sin((*it).d_hanyou[1]); 
		}
	}
	else if(p>=60 && p<=61){//夢終「エンドオブジャッジメント」
		if(c<90){
			float angle = atan2((*it).move_y,(*it).move_x);
			if(p==60)	angle += Radian(1.5,TRUE);
			else		angle -= Radian(1.5,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	if((*it).count<(*it).f_count){
		(*it).f_speed -= (*it).d_hanyou[0];
		(*it).x += (*it).move_x * (*it).f_speed;
		(*it).y += (*it).move_y * (*it).f_speed;
	}
	else{
		(*it).x += (*it).move_x * (*it).speed;
		(*it).y += (*it).move_y * (*it).speed;
	}
	if(g==gra_e_shot[31]||g==gra_e_shot[32]||g==gra_e_shot[33]||g==gra_e_shot[34]){
		(*it).angle += Radian(20.0,TRUE);
	}
	else{
		(*it).angle = atan2((*it).move_y,(*it).move_x)+1.57;
	}
	if(g==gra_e_shot[0]||g==gra_e_shot[1]||g==gra_e_shot[2]||g==gra_e_shot[3]){
		//小弾
		(*it).atari_x[0] = (*it).x - 1;
		(*it).atari_x[1] = (*it).x + 1;
		(*it).atari_y[0] = (*it).y - 1;
		(*it).atari_y[1] = (*it).y + 1;
	}
	else if(g==gra_e_shot[4]||g==gra_e_shot[5]||g==gra_e_shot[6]||g==gra_e_shot[7]||g==gra_e_shot[53]){
		//中弾
		(*it).atari_x[0] = (*it).x - 2;
		(*it).atari_x[1] = (*it).x + 2;
		(*it).atari_y[0] = (*it).y - 2;
		(*it).atari_y[1] = (*it).y + 2;
	}
	else if(g==gra_e_shot[8]||g==gra_e_shot[9]||g==gra_e_shot[10]||g==gra_e_shot[11]||g==gra_e_shot[12]||g==gra_e_shot[13]){
		//中弾その２
		(*it).atari_x[0] = (*it).x - 2;
		(*it).atari_x[1] = (*it).x + 2;
		(*it).atari_y[0] = (*it).y - 2;
		(*it).atari_y[1] = (*it).y + 2;
	}
	else if(g==gra_e_shot[26]||g==gra_e_shot[27]||g==gra_e_shot[28]||g==gra_e_shot[29]||g==gra_e_shot[30]){
		//大弾
		(*it).atari_x[0] = (*it).x - 4;
		(*it).atari_x[1] = (*it).x + 5;
		(*it).atari_y[0] = (*it).y - 4;
		(*it).atari_y[1] = (*it).y + 5;
	}
	else if(g==gra_e_shot[14]||g==gra_e_shot[15]||g==gra_e_shot[16]||g==gra_e_shot[17]||g==gra_e_shot[52]){
		//米弾
		(*it).atari_x[0] = (*it).x - 1;
		(*it).atari_x[1] = (*it).x + 1;
		(*it).atari_y[0] = (*it).y - 1;
		(*it).atari_y[1] = (*it).y + 1;
	}
	else if(g==gra_e_shot[31]||g==gra_e_shot[32]||g==gra_e_shot[33]||g==gra_e_shot[34]){
		//特大弾
		(*it).atari_x[0] = (*it).x - 10;
		(*it).atari_x[1] = (*it).x + 10;
		(*it).atari_y[0] = (*it).y - 10;
		(*it).atari_y[1] = (*it).y + 10;
	}
	else if(g==gra_e_shot[18]||g==gra_e_shot[19]||g==gra_e_shot[20]||g==gra_e_shot[21]){
		//鱗弾
		(*it).atari_x[0] = (*it).x - 2;
		(*it).atari_x[1] = (*it).x + 2;
		(*it).atari_y[0] = (*it).y - 2;
		(*it).atari_y[1] = (*it).y + 2;
	}
	else if(g==gra_e_shot[35]||g==gra_e_shot[36]||g==gra_e_shot[37]){
		//刀弾
		(*it).atari_x[0] = (*it).x - 3;
		(*it).atari_x[1] = (*it).x + 3;
		(*it).atari_y[0] = (*it).y - 3;
		(*it).atari_y[1] = (*it).y + 3;
	}
	else if(g==gra_e_shot[38]||g==gra_e_shot[39]||g==gra_e_shot[40]||g==gra_e_shot[41]||g==gra_e_shot[42]){
		//札弾
		(*it).atari_x[0] = (*it).x - 3;
		(*it).atari_x[1] = (*it).x + 3;
		(*it).atari_y[0] = (*it).y - 3;
		(*it).atari_y[1] = (*it).y + 3;
	}
	else if(g==gra_e_shot[43]||g==gra_e_shot[44]||g==gra_e_shot[45]||g==gra_e_shot[46]){
		//ジェリー弾
		(*it).atari_x[0] = (*it).x - 3;
		(*it).atari_x[1] = (*it).x + 3;
		(*it).atari_y[0] = (*it).y - 3;
		(*it).atari_y[1] = (*it).y + 3;
	}
	else if(g==gra_e_shot[47]||g==gra_e_shot[48]||g==gra_e_shot[49]||g==gra_e_shot[50]||g==gra_e_shot[51]){
		//クナイ弾
		(*it).atari_x[0] = (*it).x - 1;
		(*it).atari_x[1] = (*it).x + 1;
		(*it).atari_y[0] = (*it).y - 1;
		(*it).atari_y[1] = (*it).y + 1;
	}
	else if(g==gra_e_shot[54]||g==gra_e_shot[55]||g==gra_e_shot[56]||g==gra_e_shot[57]){
		//氷弾
		(*it).atari_x[0] = (*it).x - 2;
		(*it).atari_x[1] = (*it).x + 2;
		(*it).atari_y[0] = (*it).y - 2;
		(*it).atari_y[1] = (*it).y + 2;
	}
	else if(g==gra_e_shot[22]||g==gra_e_shot[23]||g==gra_e_shot[24]||g==gra_e_shot[25]){
		//蝶弾
		(*it).atari_x[0] = (*it).x - 2;
		(*it).atari_x[1] = (*it).x + 2;
		(*it).atari_y[0] = (*it).y - 2;
		(*it).atari_y[1] = (*it).y + 2;
	}
	return;
}

void SLas_Load(){
	try{
		char fi[128];
		for(int i=0;i<GRA_LASER_NUM;i++){
			wsprintf(fi , "data/img/shot/laser/%d.png",i+1);
			SetTransColor(0,0,0);
			if( (gra_laser[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SLas_Reset(){
	Laser.clear();
	return;
}

void SLas_Main(){
	for(list<LASERDATA>::iterator it=Laser.begin();it!=Laser.end();it++){
		if((*it).x<0-(*it).img_x/2 || (*it).x>450+(*it).img_x/2 || (*it).y<0-(*it).img_y/2 || (*it).y>480+(*it).img_y/2){
			it = Laser.erase(it);
			it--;
			continue;
		}
		SLas_Move(it);
	}

	return;
}

void SLas_Draw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for(list<LASERDATA>::iterator it=Laser.begin();it!=Laser.end();it++){
		float line_x,line_y;
		bool dele = false;
		line_x = (*it).x + 640*cos(Radian((*it).angle,TRUE));
		line_y = (*it).y + 640*sin(Radian((*it).angle,TRUE));
		if((*it).count<60)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
		if((*it).i_hanyou[6]==0)	DrawLine((*it).x+shake_x, (*it).y+shake_y, line_x+shake_x, line_y+shake_y, GetColor(255,255,255)); 
		if((*it).late>0){
			(*it).late --;
			if((*it).pattern==7){
				SEf_Make((*it).x,(*it).y,4,(*it).img);
			}

		}
		else{
			(*it).atari = true;
			bool graze = false;
			if((*it).count%3==0)	graze = true;
			if((*it).count==0&&((*it).pattern==0||(*it).pattern==6||(*it).pattern==7))	SPlaySound(21);
			if((*it).effect==0){
				SEf_Make((*it).x,(*it).y,4,(*it).img);
			}
			SLas_ShotMake(it);
			int revanum = 0;
			int imgnum = (*it).Shot.size();
			for(list<LASER_SHOTDATA>::iterator sit=(*it).Shot.begin();sit!=(*it).Shot.end();sit++,imgnum--){
				(*sit).x = (*it).x + (*it).speed * (*sit).count * cos(Radian((*it).angle,TRUE));
				(*sit).y = (*it).y + (*it).speed * (*sit).count * sin(Radian((*it).angle,TRUE));
				switch((*it).pattern){
					case 0:	
						if((*it).count<60){
						     	(*sit).flash = 255;
						}
						else if((*it).count<90){
						     	(*sit).flash = 255-8.5*((*it).count-60);
						}
						else	dele = true;
						if((*it).count>=75)	(*it).atari = false;
						break;
					case 1:	
						if((*it).count>=20&&(*it).count<140){
							(*sit).flash = 255;
						     	if((*it).count%6==0&&it==Laser.begin()&&revanum==0){
								SPlaySound(10);
								for(int i=0;i<15;i++){
									SEs_Make((*it).x+40*i*cos(Radian((*it).angle+4.0,TRUE)),(*it).y+40*i*sin(Radian((*it).angle+4.0,TRUE)),(*it).angle+90,0.0,gra_e_shot[14],10,0.0,0,7,0);
									SEs_Make((*it).x+40*i*cos(Radian((*it).angle,TRUE)),(*it).y+40*i*sin(Radian((*it).angle,TRUE)),(*it).angle+90,0.0,gra_e_shot[14],10,0.0,0,7,0);
								}
							}
						}
						else if((*it).count<150){
							(*it).atari = false;
							(*sit).flash = 255-25.5*((*it).count-140);
						}
						if((*it).count==150)	dele = true;
						break;
					case 2:	
						if((*it).count>=60&&(*it).count<140){
							(*sit).flash = 255;
						     	if((*it).count%6==0&&it==Laser.begin()&&revanum==0){
								SPlaySound(10);
								for(int i=0;i<15;i++){
									SEs_Make((*it).x+40*i*cos(Radian((*it).angle,TRUE)),(*it).y+40*i*sin(Radian((*it).angle,TRUE)),(*it).angle-90,0.0,gra_e_shot[14],10,0.0,0,7,0);
								}
							}
						}
						else if((*it).count<150){
							(*it).atari = false;
							(*sit).flash = 255-25.5*((*it).count-140);
						}
						if((*it).count==150)	dele = true;
						break;
					case 3:	
						if((*it).count>=50&&(*it).count<130){
							(*sit).flash = 255;
						     	if((*it).count%5==0&&it==Laser.begin()&&revanum==0){
								SPlaySound(10);
								for(int i=0;i<15;i++){
									SEs_Make((*it).x+40*i*cos(Radian((*it).angle,TRUE)),(*it).y+40*i*sin(Radian((*it).angle,TRUE)),(*it).angle+90,0.0,gra_e_shot[14],10,0.0,0,7,0);
								}
							}
						}
						else if((*it).count<140){
							(*it).atari = false;
							(*sit).flash = 255-25.5*((*it).count-130);
						}
						if((*it).count==140)	dele = true;
						break;
					case 4:	
						if((*it).count>=20&&(*it).count<140){
							(*sit).flash = 255;
						     	if((*it).count%6==0&&it==Laser.begin()&&revanum==0){
								SPlaySound(10);
								for(int i=0;i<15;i++){
									SEs_Make((*it).x+40*i*cos(Radian((*it).angle+4.0,TRUE)),(*it).y+40*i*sin(Radian((*it).angle+4.0,TRUE)),(*it).angle-90,0.0,gra_e_shot[14],10,0.0,0,7,0);
									SEs_Make((*it).x+40*i*cos(Radian((*it).angle,TRUE)),(*it).y+40*i*sin(Radian((*it).angle,TRUE)),(*it).angle-90,0.0,gra_e_shot[14],10,0.0,0,7,0);
								}
							}
						}
						else if((*it).count<150){
							(*it).atari = false;
							(*sit).flash = 255-25.5*((*it).count-140);
						}
						if((*it).count==150)	dele = true;
						break;
					case 5:	
						if((*it).count<30){
						     	(*sit).flash = 255;
						}
						else if((*it).count<60){
						     	(*sit).flash = 255-8.5*((*it).count-30);
						}
						else	dele = true;
						if((*it).count>=45)	(*it).atari = false;
						break;
					case 6:
						(*sit).flash = 255;
						break;	
					case 7:	
						if((*it).count<120){
						     	(*sit).flash = 255;
						}
						else if((*it).count<150){
						     	(*sit).flash = 255-8.5*((*it).count-120);
						}
						else	dele = true;
						if((*it).count>=135)	(*it).atari = false;
						break;
				}
				revanum++;
				if((*sit).x<0-(*it).img_x/2 || (*sit).x>450+(*it).img_x/2 || (*sit).y<0-(*it).img_y/2 || (*sit).y>480+(*it).img_y/2){
					sit = (*it).Shot.erase(sit);
					sit--;
					continue;
				}
				if(Bomb.life==1&&Bomb.count>=10){
					float sx = Bomb.x - (*sit).x;
					float sy = Bomb.y - (*sit).y;
					float sq = sqrt(sx*sx+sy*sy);
					if(sq<70+(*it).img_x/2){
						SIt_Make((*sit).x,(*sit).y,270,gra_item[4],1);
						sit = (*it).Shot.erase(sit);
						sit--;
						continue;
					}
				}
				if(dele==false&&imgnum>2){
					SetDrawBlendMode(DX_BLENDMODE_ADD,(*sit).flash);
					if(loop_count==0)	DrawRotaGraphF((*sit).x+shake_x, (*sit).y+shake_y, 1.0, Radian((*it).angle,TRUE)+1.57, (*it).img, TRUE, FALSE);
				}
				(*sit).count++;		
			}
			while((*it).angle>360)	(*it).angle-=360;
			while((*it).angle<0)	(*it).angle+=360;
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			int flag = 0;
			if(sin(Radian((*it).angle,TRUE))>=0 && Player.y>=(*it).y)	flag ++;
			else if(sin(Radian((*it).angle,TRUE))<0 && Player.y<(*it).y)	flag ++;
			if(cos(Radian((*it).angle,TRUE))>=0 && Player.x>=(*it).x)	flag ++;
			else if(cos(Radian((*it).angle,TRUE))<0 && Player.x<(*it).x)	flag ++;
			if((*it).atari==true&&sq<(*it).speed*(*it).count&&flag==2){
				float d;
				if((*it).angle==90||(*it).angle==270)		d = abs((*it).x - Player.x);
				else if((*it).angle==0||(*it).angle==180)	d = abs((*it).y - Player.y);
				else						d = abs(tan(Radian((*it).angle,TRUE))*(Player.x-(*it).x) - (Player.y-(*it).y)) / sqrt(pow(tan(Radian((*it).angle,TRUE)),2)+1);
				if(d<(*it).img_x/2){
					if(Player.nodamage==0 && Player.miss==0){
						SPlaySound(2);
						Player.miss = 8;
					}
					SEf_Make(Player.x,Player.y,2,(*it).img);	
				}
				if(d<(*it).img_x/2+Player.img_x/2){
					if((*it).graze_count%5==0&&Player.miss==0){
						SPlaySound(3);
						SEf_Make(Player.x,Player.y,9,gra_graze_effect);
						if(Game.graze<65534){
							Game.graze ++;
							Game.stage_graze[Game.stage]++;
							SSc_AddScore(1000);
						}
						Game.maxpoint += 10;
					}
					(*it).graze_count++;	
				}
				else{
					(*it).graze_count = 0;
				}
			}
			if(dele==true){
				it = Laser.erase(it);
				it--;
				continue;
			}
			(*it).count++;
		}
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	
	return;
}

void SLas_Make(float x,float y,float angle,float speed,int img,int late,int pattern,int effect){
	LASERDATA P;
	P.x = x;
	P.y = y;
	P.speed = speed;
	P.img = img;
	P.late = late;
	P.pattern = pattern;
	P.count = 0;
	P.graze_count = 0;
	P.angle = angle;
	P.effect = effect;
	P.atari = false;
	GetGraphSize(P.img,&P.img_x,&P.img_y);
	for(int i=0;i<HANYOU_NUM;i++){
		P.i_hanyou[i] = 0;
		P.d_hanyou[i] = 0;
	}
	
	Laser.push_back(P);
	return;
}

void SLas_ShotMake(list<LASERDATA>::iterator &it){
	LASER_SHOTDATA P;
	P.x = (*it).x;
	P.y = (*it).y;
	P.flash = 255;
	P.pattern = (*it).pattern;
	P.count = 0;
	for(int i=0;i<HANYOU_NUM;i++){
		P.i_hanyou[i] = 0;
		P.d_hanyou[i] = 0;
	}
	(*it).Shot.push_back(P);
	return;
}

void SLas_Move(list<LASERDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	
	if(p==1){//レーヴァテイン
		(*it).i_hanyou[6] = 1;
		if(c>=20){
			(*it).x = Boss.x + 20*cos(Radian((*it).angle,TRUE));
			(*it).y = Boss.y + 20*sin(Radian((*it).angle,TRUE));
		}
		if(c>=20&&c<140){
			(*it).angle += 2.25;
		}
	}
	if(p==2||p==3){//レーヴァテイン２
		(*it).i_hanyou[6] = 1;
		(*it).x = Boss.x;
		(*it).y = Boss.y+20;
	}
	if(p==4){//レーヴァテイン３
		(*it).i_hanyou[6] = 1;
		(*it).x = Boss.x + 20*cos(Radian((*it).angle,TRUE));
		(*it).y = Boss.y + 20*sin(Radian((*it).angle,TRUE));
		if(c>=20&&c<140){
			(*it).angle -= 2.25;
		}
	}
	if(p==6){//戯符「神々のアジャラ空間」
		if(c==120)	SPlaySound(19);
		if(c>=180){
			(*it).angle -= 0.15;
		}
	}
	return;
}

void SBos_Load(){
	try{
		char fi[128];
		SetTransColor(0,0,0);
		for(int i=0;i<4;i++){
			wsprintf(fi , "data/img/dot/boss/%d.png" , i+1);
			if( LoadDivGraph(fi,32,8,4,128,128,gra_boss[i]) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SBos_Reset(){
	Boss.count = 0;
	Boss.countdown = 0;
	Boss.exist = 0;
	Boss.gage_exist = 0;
	for(int i=0;i<ZANZOU_NUM;i++){
		Game.zanzou_x[i] = -100;
		Game.zanzou_y[i] = -100;
	}
	return;
}

void SBos_Main(){
	if(Boss.exist>=1 && Game.skip==false){
		if(Boss.life>0||Boss.life==-10){
			if(Game.spell_mode==0)	SBos_Move();
			else			SSp_Move();
			if(Boss.gage_exist==1){
				if(Game.spell_mode==0)	SBos_Shot();
				else			SSp_Shot();
			}
			if(Game.spell_mode==0&&Boss.shot_pattern==-1)	SBos_Shot();
		}
	}
	
	return;
}

void SBos_Draw(){
	FlagSlow = false;
	if(Talk.count>0)	Boss.gage_exist = 0;
	if(Boss.exist>=1){
		if(Boss.pattern==1)	Boss.b_zanzou = true;
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if(Game.spell_mode==1){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
			SetDrawBright(255-abs(200-5*Boss.count%400),200,200);
			if(loop_count==0)	DrawRotaGraphF(Boss.x+shake_x, Boss.y+shake_y, 4.0+0.5*sin(Radian(3*Boss.count,TRUE)), Radian(Game.count*4,TRUE), gra_circle, TRUE, FALSE);
			SetDrawBright(255,255,255);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawRotaGraphF(Boss.x+shake_x, Boss.y+shake_y, 2.5, Radian(Game.count*6,TRUE), gra_circle, TRUE, FALSE);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		if(Boss.b_zanzou==true){
			Game.zanzou_x[0] = Boss.x;
			Game.zanzou_y[0] = Boss.y;
			SetDrawBright(50,50,255);
			for(int i=20-1;i>0;i--){
				if(i>=ZANZOU_NUM || i<0)	break;
				Game.zanzou_x[i] = Game.zanzou_x[i-1];
				Game.zanzou_y[i] = Game.zanzou_y[i-1];
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(ZANZOU_NUM-i)*Boss.flash/ZANZOU_NUM);
				float sx = abs(Boss.x-Game.zanzou_x[i]);
				float sy = abs(Boss.y-Game.zanzou_y[i]);
				if(sx>0.1||sy>0.1){
					if(loop_count==0)	DrawRotaGraphF(Game.zanzou_x[i]+shake_x, Game.zanzou_y[i]+shake_y, Boss.large, 0, Boss.img[Boss.img_num], TRUE, FALSE);
				}
			}
			SetDrawBright(255,255,255);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Boss.flash);
		if(Game.stage==6&&Boss.i_hanyou[6]==1)	SetDrawBright(0,0,0);
		if(Boss.pattern==4)	SetDrawBright(0,0,0);
		if(loop_count==0)	DrawRotaGraphF(Boss.x+shake_x, Boss.y+8*sin(Radian(4*Boss.img_count,TRUE))+shake_y, Boss.large, 0, Boss.img[Boss.img_num], TRUE, FALSE);
		SetDrawBright(255,255,255);
		if(Game.spell_mode==1){
			int s = Boss.spell_num;
			if(s==124){
				if(Player.nodamage>30){
					Boss.b_muteki = true;
				}
				else{
					Boss.b_muteki = false;
				}
			}
			else if((s>=98&&s<=100)||(s>=52&&s<=55)||(s>=103&&s!=112)){
				if(Bomb.life==1){
					Boss.b_muteki = true;
				}
				else{
					Boss.b_muteki = false;
				}
			}
		}
		else{
			Boss.b_muteki = false;
		}
		//DrawBox(Boss.atari_x[0],Boss.atari_y[0],Boss.atari_x[1],Boss.atari_y[1],GetColor(255,0,0),TRUE);
		if(Game.skip==false)	Boss.count++;
		if(Boss.b_atari==true && Player.nodamage==0 && Player.miss==0 &&
		   Player.atari_x[0]<Boss.atari_x[1] &&
		   Player.atari_x[1]>Boss.atari_x[0] &&
		   Player.atari_y[0]<Boss.atari_y[1] &&
		   Player.atari_y[1]>Boss.atari_y[0]){
			SPlaySound(2);
			Player.miss = 8;
		}
		if(Bomb.life==1&&Bomb.count>=10){
			float sx = Bomb.x - Boss.x;
			float sy = Bomb.y - Boss.y;
			float sq = sqrt(sx*sx+sy*sy);
			if(sq<70+Boss.img_y/4){
				Boss.damage += Bomb.atack;
			}
		}
		if(Boss.life>0){
			if(Boss.b_muteki==true)	Boss.damage = 0;
			Boss.life -= Boss.damage*(100-(float)Boss.defence)*0.01;
			if(Boss.life<=0){
				Boss.count = 0;
				Boss.life = 0;
			}
		}
		Boss.damage = 0;
		if(Boss.gage_exist==1&&(Game.stage==1||Game.stage==4)&&Boss.countdown==0){
			if(Game.count<5610||Boss.zanki>0){
				SBos_DeleteBullet(0);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = 0;
				Boss.gage_exist = 0;
			}
			else{
				Boss.count = 0;
				Boss.life = 0;
				Boss.move_x = 0;
				Boss.move_y = 0;
			}
		}
		if(Boss.gage_exist==1&&(Game.stage==2||Game.stage==5)&&Boss.countdown==0){
			if(Game.count<10610||Boss.zanki>0){
				SBos_DeleteBullet(0);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = 0;
				Boss.gage_exist = 0;
			}
			else{
				Boss.count = 0;
				Boss.life = 0;
				Boss.move_x = 0;
				Boss.move_y = 0;
			}
		}
		if(Boss.gage_exist==1&&(Game.stage==3||Game.stage==6)&&Boss.countdown==0){
			if(Game.count<10000||Boss.zanki>0){
				SBos_DeleteBullet(0);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = 0;
				Boss.gage_exist = 0;
			}
			else{
				Boss.count = 0;
				Boss.life = 0;
				Boss.move_x = 0;
				Boss.move_y = 0;
			}
		}
		if(Boss.gage_exist==1&&Game.stage==7&&Boss.countdown==0){
			if(Boss.i_hanyou[1]==0||Boss.zanki>0){
				SBos_DeleteBullet(0);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = 0;
				Boss.gage_exist = 0;
			}
			else{
				Boss.count = 0;
				Boss.life = 0;
				Boss.move_x = 0;
				Boss.move_y = 0;
			}
		}
		if(Boss.life<=0){
			if(Game.spell_mode==0&&Boss.spell_life>0&&(Game.stage==1||Game.stage==4)){
				SBos_DeleteBullet(1);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = Boss.spell_life;
				Game.spell_mode = 1;
				Game.spell_getflag = 0;
				Game.spell_count = 1;
				Boss.defence = Spell[Boss.spell_num].defence;
				Boss.countdown = Spell[Boss.spell_num].count*60;
				Boss.gage_exist = 1;
			}
			else if(Game.spell_mode==0&&Boss.spell_life>0&&((Game.stage==2||Game.stage==5)&&Boss.life!=-10)){
				SBos_DeleteBullet(1);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = Boss.spell_life;
				Game.spell_mode = 1;
				Game.spell_getflag = 0;
				Game.spell_count = 1;
				Boss.defence = Spell[Boss.spell_num].defence;
				Boss.countdown = Spell[Boss.spell_num].count*60;
				Boss.gage_exist = 1;
			}
			else if(Game.spell_mode==0&&Boss.spell_life>0&&(Game.stage==3||Game.stage==6||Game.stage==7)){
				SBos_DeleteBullet(1);
				Boss.move_x = 0;
				Boss.move_y = 0;
				Boss.count = 0;
				Boss.life = Boss.spell_life;
				Game.spell_mode = 1;
				Game.spell_getflag = 0;
				Game.spell_count = 1;
				Boss.defence = Spell[Boss.spell_num].defence;
				Boss.countdown = Spell[Boss.spell_num].count*60;
				Boss.gage_exist = 1;
			}
			else{
				bool b_getspell = true;
				Boss.life = 0;
				if(Boss.countdown==0)	Boss.countdown = -2;
				Boss.countdown++;
				if((((Game.stage==1||Game.stage==4)&&Game.count>5610) || ((Game.stage==2||Game.stage==5)&&Game.count>6800) || (Game.stage==6&&Game.count>5400&&Boss.i_hanyou[6]==0)) && Boss.zanki<=0){
					b_getspell = false;
					Boss.b_atari = false;
					if(Boss.count==0)	SPlaySound(18);
					if(Boss.count<120){
						Boss.x += 0.2;
						Boss.y -= 0.2;
						for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
							float sx = Boss.x-(*it).x;
							float sy = Boss.y-(*it).y;
							float sq = sqrt(sx*sx+sy*sy);
							if(sq<4*Boss.count){
								SEf_Make((*it).x,(*it).y,2,(*it).img);
								SIt_Make((*it).x,(*it).y,270,gra_item[4],1);
								it = E_Shot.erase(it);
								it--;
								continue;
							}
						}
					}
					else{
						SBos_Item();
						SEf_Make(Boss.x,Boss.y,0);
						SPlaySound(12);
						SPlaySound(18);
						b_getspell = true;
						Boss.b_zanzou = false;
						Game.shake_count = 30;
						Boss.gage_exist = 0;
						Boss.exist = 0;
						Talk.count++;
					}
				}
				else if(((Game.stage==3||Game.stage==6)&&Game.count<6800) && Boss.zanki<=0){//中ボス
					b_getspell = false;
					Boss.b_atari = false;
					if(Boss.count==0)	SPlaySound(18);
					if(Boss.count<60){
						Boss.x += 0.2;
						Boss.y -= 0.2;
						for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
							float sx = Boss.x-(*it).x;
							float sy = Boss.y-(*it).y;
							float sq = sqrt(sx*sx+sy*sy);
							if(sq<8*Boss.count){
								SEf_Make((*it).x,(*it).y,2,(*it).img);
								SIt_Make((*it).x,(*it).y,270,gra_item[4],1);
								it = E_Shot.erase(it);
								it--;
								continue;
							}
						}
					}
					else{
						SBos_Item();
						SEf_Make(Boss.x,Boss.y,0);
						SPlaySound(12);
						SPlaySound(18);
						b_getspell = true;
						Game.shake_count = 30;
						Boss.gage_exist = 0;
						Boss.exist = 0;
						GameScene = 0;
						for(list<LASERDATA>::iterator it=Laser.begin();it!=Laser.end();it++){
							for(list<LASER_SHOTDATA>::iterator sit=(*it).Shot.begin();sit!=(*it).Shot.end();sit++){
								SEf_Make((*sit).x,(*sit).y,2,(*it).img);
								SIt_Make((*sit).x,(*sit).y,270,gra_item[4],1);
								sit = (*it).Shot.erase(sit);
								sit--;
								continue;
							}
							it = Laser.erase(it);
							it--;
							continue;
						}
					}
				}
				else if(((Game.stage==6&&Boss.i_hanyou[6]==1&&Game.count>5400) || (Game.stage==3&&Game.count>5400) || (Game.stage==7&&Game.count>10000)) && Boss.zanki<=0){
					b_getspell = false;
					Boss.b_atari = false;
					FlagSlow = true;
					if(Boss.count<=60){
						if(Boss.count%20==0)	SPlaySound(8);
					}
					else{
						if(Boss.count==61){
							SBos_Item();
							SPlaySound(18);
							SBos_DeleteBullet(1);
							Boss.gage_exist = 0;
							Boss.exist = 2;
							Game.spell_count = 0;						
							Game.shake_count = 30;
						}
						if(Item.size()==0){
							SEf_Make(Boss.x,Boss.y,0);
							SPlaySound(12);
							Boss.exist = 0;
							Talk.count++;
							b_getspell = true;
						}
						for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
							(*it).pattern = 1;
						}
					}
					if(Boss.count%1==0){
						for(int i=0;i<2;i++){
							SEf_Make(Boss.x,Boss.y,8);
						}
					}
				}
				else if(Game.stage==7 && Boss.i_hanyou[6]==1 && Boss.zanki<=0){
					b_getspell = false;
					Boss.b_atari = false;
					FlagSlow = true;
					if(Boss.count<=60){
						if(Boss.count%20==0)	SPlaySound(8);
					}
					else{
						if(Boss.count==61){
							SBos_Item();
							SPlaySound(18);
							SBos_DeleteBullet(1);
							Boss.gage_exist = 0;
							Boss.exist = 2;
							Game.spell_count = 0;						
							Game.shake_count = 30;
						}
						if(Item.size()==0){
							SEf_Make(Boss.x,Boss.y,0);
							SPlaySound(12);
							Boss.exist = 0;
							Talk.count++;
							b_getspell = true;
						}
						for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
							(*it).pattern = 1;
						}
					}
					if(Boss.count%1==0){
						for(int i=0;i<2;i++){
							SEf_Make(Boss.x,Boss.y,8);
						}
					}
				}
				if(b_getspell==true&&Game.spell_mode==1){
					Game.spell_mode = 0;
					Game.spell_count = 0;
					Game.getspell_count = 1;
					if(Game.spell_getflag==0){
						SSc_AddScore(Game.spell_bonus);
						Game.getspell_point = Game.spell_bonus;
						if(PlayerControlFlag==0)	SAVE.Spell[Boss.spell_num].get_times[SAVE.Chara][SAVE.Weapon] ++;
					}
					else{
						Game.getspell_point = 0;
					}
				}
				if(Boss.zanki>0){//この下でボスの攻撃を指定
					SBos_DeleteBullet(1);
					Boss.move_x = 0;
					Boss.move_y = 0;
					Boss.count = 0;
					SPlaySound(12);
					SBos_Item();
					SEf_Make(Boss.x,Boss.y,0);
					if(Game.stage==1&&GameScene==1){
						if(Boss.zanki==2){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,18000,4+SAVE.Level,0,2,2,0,40);
						}
						if(Boss.zanki==1){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,8+SAVE.Level,0,-1,-1,0,255);
							Boss.gage_exist = 0;
						}
					}
					if(Game.stage==2&&GameScene==1){
						if(Boss.zanki==3){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,15000,20+SAVE.Level,1,8,7,1,40);
						}
						if(Boss.zanki==2){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,18000,-1,1,10,9,1,40);
						}
						if(Boss.zanki==1){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,24+SAVE.Level,1,-1,-1,1,255);
							Boss.gage_exist = 0;
						}
					}
					if(Game.stage==3&&GameScene==1){
						if(Boss.zanki==4){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,40+SAVE.Level,2,15,14,2,66);
						}
						if(Boss.zanki==3){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,44+SAVE.Level,2,16,15,2,66);
						}
						if(Boss.zanki==2){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,48+SAVE.Level,2,17,16,2,66);
						}
						if(Boss.zanki==1){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,52+SAVE.Level,2,-1,-1,2,255);
							Boss.gage_exist = 0;
						}
					}
					if(Game.stage==4&&GameScene==1){
						if(Boss.zanki==2){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,58+SAVE.Level,0,2,19,5,40);
						}
						if(Boss.zanki==1){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,61+SAVE.Level,0,-1,-1,5,255);
							Boss.gage_exist = 0;
						}
					}
					if(Game.stage==5&&GameScene==1){
						if(Boss.zanki==3){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,14000,70+SAVE.Level,1,8,21,6,40);
						}
						if(Boss.zanki==2){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,16000,-1,1,10,22,6,50);
						}
						if(Boss.zanki==1){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,73+SAVE.Level,1,-1,-1,1,255);
							Boss.gage_exist = 0;
						}
					}
					if(Game.stage==6&&GameScene==1){
						if(Boss.zanki==5){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,85+SAVE.Level,2,15,26,9,66);
						}
						if(Boss.zanki==4){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,88+SAVE.Level,2,18,27,9,66);
						}
						if(Boss.zanki==3){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,91+SAVE.Level,2,17,28,9,66);
						}
						if(Boss.zanki==2){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,94+SAVE.Level,2,-1,-1,10,255);
							Boss.gage_exist = 0;
						}
						if(Boss.zanki==1){	
							SBos_Make(Boss.x,Boss.y,Boss.zanki,1,97+SAVE.Level,2,-1,-1,-1,255);
							Boss.gage_exist = 0;
						}
					}
					if(Game.stage==7&&GameScene==1){
						if(Game.count<5200){
							if(Boss.zanki==1){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,-1,4,19,30,11,40);
							}
						}
						else{
							if(Boss.zanki==9){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,105,3,5,4,12,30);
							}
							if(Boss.zanki==8){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,106,3,4,32,11,30);
							}
							if(Boss.zanki==7){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,107,3,4,3,11,30);
							}
							if(Boss.zanki==6){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,108,3,4,33,11,30);
							}
							if(Boss.zanki==5){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,109,3,6,5,11,30);
							}
							if(Boss.zanki==4){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,10000,110,3,4,34,11,30);
							}
							if(Boss.zanki==3){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,20000,111,3,7,6,11,30);
							}
							if(Boss.zanki==2){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki,1,112,3,-1,-1,11,255);
								Boss.gage_exist = 0;
							}
							if(Boss.zanki==1){	
								SBos_Make(Boss.x,Boss.y,Boss.zanki-1,1,113,3,-1,-1,-1,255);
								Boss.b_atari = false;
								Boss.gage_exist = 0;
							}
						}
					}
				}
				else if((Game.stage==1||Game.stage==4)&&Game.count>5610&&Boss.zanki<=0){}
				else if(Game.stage==1||Game.stage==4){
					GameScene = 0;
					if(Boss.gage_exist==1){
						SBos_DeleteBullet(1);
						SPlaySound(18);
						SBos_Item();
						SEf_Make(Boss.x,Boss.y,0);
						Boss.move_x = 0;
						Boss.move_y = 0;
						Boss.gage_exist = 0;
						Boss.count = 0;
					}
					else if(Boss.gage_exist==0){
						Boss.life = -10;
						Boss.defence = 100;
						if(Boss.count==50)	SBos_MoveTo(0,0,40);
						if(Boss.count==90)	Boss.exist = 0;
					}
				}
				else if((Game.stage==2||Game.stage==5)&&Game.count>6800){}
				else if(Game.stage==2||Game.stage==5){//中ボス
					GameScene = 0;
					Game.spell_mode = 0;
					if(Boss.gage_exist==1){
						SBos_DeleteBullet(1);
						SPlaySound(18);
						SBos_Item();
						SEf_Make(Boss.x,Boss.y,0);
						Boss.move_x = 0;
						Boss.move_y = 0;
						Boss.gage_exist = 0;
						Boss.count = 0;
						Game.shake_count = 15;
					}
					if(Boss.gage_exist==0){
						Boss.life = -10;
						Boss.move_pattern = -1;
						Boss.defence = 100;
						if(Boss.count==50){
							SBos_MoveTo(-100,0,40);
						}
						if(Boss.count==90)	Boss.exist = 0;
					}
				}
				else if(Game.stage==7&&Boss.i_hanyou[6]==1){}
				else if(Game.stage==7){//中ボス
					GameScene = 0;
					Game.spell_mode = 0;
					if(Boss.gage_exist==1){
						SBos_DeleteBullet(1);
						SPlaySound(18);
						SBos_Item();
						SEf_Make(Boss.x,Boss.y,0);
						Boss.move_x = 0;
						Boss.move_y = 0;
						Boss.gage_exist = 0;
						Boss.count = 0;
						Game.shake_count = 15;
					}
					if(Boss.gage_exist==0){
						Boss.life = -10;
						Boss.move_pattern = -1;
						Boss.defence = 100;
						if(Boss.count==50){
							SBos_MoveTo(-100,0,40);
						}
						if(Boss.count==90)	Boss.exist = 0;
					}
				}
				Boss.zanki--;
			}
		}
		//DrawBox(Boss.atari_x[0],Boss.atari_y[0],Boss.atari_x[1],Boss.atari_y[1],GetColor(255,255,255),TRUE);
	}
	
	return;
}

void SBos_DeleteBullet(int flag){
	for(list<ENEMYDATA>::iterator it=Enemy.begin();it!=Enemy.end();it++){
		(*it).life = 0;
	}
	for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
		SEf_Make((*it).x,(*it).y,2,(*it).img);
		if(flag==1)	SIt_Make((*it).x,(*it).y,270,gra_item[4],1);
		it = E_Shot.erase(it);
		it--;
		continue;
	}
	for(list<LASERDATA>::iterator it=Laser.begin();it!=Laser.end();it++){
		for(list<LASER_SHOTDATA>::iterator sit=(*it).Shot.begin();sit!=(*it).Shot.end();sit++){
			SEf_Make((*sit).x,(*sit).y,2,(*it).img);
			if(flag==1)	SIt_Make((*sit).x,(*sit).y,270,gra_item[4],1);
			sit = (*it).Shot.erase(sit);
			sit--;
			continue;
		}
		it = Laser.erase(it);
		it--;
		continue;
	}
	
	return;
}

void SBos_Make(float x,float y,int zanki,int life,int spell_num,int pattern,int move_pattern,int shot_pattern,int item_pattern,int countdown){
	GameScene = 1;
	Boss.x = x;
	Boss.y = y;
	for(int i=0;i<ATARI_NUM;i++){
		Boss.atari_x[i] = x;
		Boss.atari_y[i] = y;
	}
	Boss.pattern = pattern;
	for(int i=0;i<ZANZOU_NUM;i++){
		Game.zanzou_x[i] = x;
		Game.zanzou_y[i] = y;
	}
	for(int i=0;i<BOSS_IMG_NUM;i++){
		if(pattern<4)	Boss.img[i] = gra_boss[pattern][i];
		else		Boss.img[i] = gra_boss[3][i];
	}
	GetGraphSize(Boss.img[0],&Boss.img_x,&Boss.img_y);
	Boss.angle = 0;
	Boss.speed = 0;
	Boss.large = 1.0;
	Boss.exist = 1;
	Boss.gage_exist = 1;
	Boss.zanki = zanki;
	Boss.life = life;
	Boss.life2 = 0;
	if(spell_num==-1)	Boss.spell_life = 0;
	else			Boss.spell_life = Spell[spell_num].life;
	Boss.max_life = Boss.life;
	Boss.defence = 100;
	Boss.damage = 0;
	Boss.spell_num = spell_num;
	for(int i=0;i<BOSS_MOVE_COUNT_NUM;i++){
		Boss.move_count[i] = 0;
	}
	Boss.count = 0;
	Boss.img_count = 0;
	if(countdown==0){
		Boss.countdown = Spell[spell_num].count*60;
		Game.spell_count = 1;
	}
	else{
		Boss.countdown = countdown*60;
	}
	Boss.flash = 255;
	Boss.move_pattern = move_pattern;
	Boss.shot_pattern = shot_pattern;
	Boss.item_pattern = item_pattern;
	for(int i=0;i<HANYOU_NUM;i++){
		Boss.i_hanyou[i] = 0;
		Boss.d_hanyou[i] = 0;
	}
	Boss.b_atari = true;
	Boss.b_zanzou = false;
	Boss.b_muteki = false;

	return;
}

void SBos_Move(){
	int p = Boss.move_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
	
	if(Boss.gage_exist==1){
		if(p==0){
			if(c==0)	SBos_MoveTo(CENTER_X,150,50);
			else if(c%350==290||c%350==90||c%350==180){
				int move_x = 30+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
			if(c==60)	Boss.defence = 0;
		}
		if(p==1){
			if(c==60)	Boss.defence = 0;		
		}
		if(p==2){
			if(Boss.count<50)	c = 0;
			else			c -= 50;
			int cp = c%120;
			if(c>=90){
				if(cp==10){
					int move_x = 30+get_rand(60);
					int move_y = 120+get_rand(60);
					if(Player.x<Boss.x){
						if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
						else				move_x = Boss.x - move_x;
					}
					else{
						if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
						else				move_x = Boss.x + move_x;
					}
					SBos_MoveTo(move_x,move_y,70);			
				}
			}
			if(Boss.count==50)	Boss.defence = 0;		
		}
		if(p==4){//映姫通常２（フランドール）
			int cp = c%90;
			if(cp==1&&c!=1){
				int move_x = 30+get_rand(60);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,40);			
			}
			if(Boss.count==60)	Boss.defence = 0;		
		}
		if(p==5){//映姫通常１（妹紅）
			int cp = c%250;
			if(cp==249){
				int move_x = 20+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);			
			}
			if(Boss.count==60)	Boss.defence = 0;		
		}
		if(p==6){//映姫通常４（諏訪子）
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
			}
			if(Boss.count==60)	Boss.defence = 0;		
		}
		if(p==7){//映姫通常３（紫）
			if(c<90)	c-=90;
			int cp = c%120;
			if(cp==1&&c!=1){
				int move_x = 20+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,60);			
			}
			if(Boss.count==120)	Boss.defence = 0;		
		}
		if(p==8){//文通常１
			if(c<120)	c-=120;
			int cp = c%100;
			if(cp==1&&c!=1){
				int move_x = 40+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,30);			
			}
			if(Boss.count==90)	Boss.defence = 0;		
		}
		if(p==9){//文通常２
			if(Boss.count==90)	Boss.defence = 0;		
		}
		if(p==10){//文通常３
			if(Boss.count==120)	Boss.defence = 0;
			Boss.b_zanzou = true;		
		}
		if(p==12){//３面スイカ・文通常１
			if(Boss.count==60)	Boss.defence = 0;
		}
		if(p==14){//３面紫通常１
			if(Boss.count==60)	Boss.defence = 0;
			if(c<120)	c-=120;
			int cp = c%100;
			if(cp==1&&c!=1){
				int move_x = 30+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);			
			}
		}
		if(p==15){//３面紫通常２
			if(Boss.count==0)	SBos_MoveTo(CENTER_X,180,30);
			if(Boss.count==60)	Boss.defence = 0;
			if(c<150)	c-=150;
			int cp = c%100;
			if(cp==1&&c!=1){
				int move_x = 30+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);			
			}
		}
		if(p==16){//３面紫通常３
			if(Boss.count==0)	SBos_MoveTo(CENTER_X,180,30);
			if(Boss.count==60)	Boss.defence = 0;
			if(c<150)	c-=150;
			int cp = c%100;
			if(cp==1&&c!=1){
				int move_x = 30+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);			
			}
		}
		if(p==17){//３面紫通常４
			if(Boss.count==0)	SBos_MoveTo(CENTER_X,180,30);
			if(Boss.count==60)	Boss.defence = 0;
		}
		if(p==18){//６面紫通常３
			if(Boss.count==0)	SBos_MoveTo(CENTER_X,180,30);
			if(Boss.count==60)	Boss.defence = 0;
		}
		if(p==19){//Ex中ボス通常１・２
			if(c==0)	SBos_MoveTo(CENTER_X,150,50);
			if(c==60)	Boss.defence = 0;
		}
	}
	if(p==3){//射命丸登場
		if(c==0)	SBos_MoveTo(limit_x[1]-Boss.img_x/2,limit_y[0]+Boss.img_y/2,30);
		if(c<20){
			if(Game.stage==2){
				switch(SAVE.Level){
					case 0:
						SPlaySound(11);
						SEs_NWay(Boss.x,Boss.y,15.0,9,1.0,gra_e_shot[18],20-c,4.5,10.0,5);
						SEs_NWay(Boss.x,Boss.y,15.0,9,2.0,gra_e_shot[19],20-c,0,10.0,5);
						break;
					case 1:
						SPlaySound(11);
						SEs_NWay(Boss.x,Boss.y,15.0,11,1.0,gra_e_shot[18],20-c,4.5,10.0,5);
						SEs_NWay(Boss.x,Boss.y,15.0,11,2.0,gra_e_shot[19],20-c,0,10.0,5);
						break;
					case 2:
						SPlaySound(11);
						SEs_NWay(Boss.x,Boss.y,12.0,15,2.5,gra_e_shot[18],20-c,6.0,10.0,5);
						SEs_NWay(Boss.x,Boss.y,12.0,15,3.5,gra_e_shot[19],20-c,0,10.0,5);
						break;
					case 3:
						SPlaySound(11);
						SEs_NWay(Boss.x,Boss.y,9.0,25,4.5,gra_e_shot[18],20-c,4.5,10.0,5);
						SEs_NWay(Boss.x,Boss.y,9.0,25,5.5,gra_e_shot[19],20-c,0,10.0,5);
						break;
				}
			}
			else{
				switch(SAVE.Level){
					case 1:
						SPlaySound(11);
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y,15.0,11,4.0-1.5*i,gra_e_shot[18],20-c,7.5,10.0,5);
							SEs_NWay(Boss.x,Boss.y,15.0,11,5.0-1.5*i,gra_e_shot[19],20-c,0,10.0,5);
						}
						break;
					case 2:
						SPlaySound(11);
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y,12.0,15,4.5-1.5*i,gra_e_shot[18],20-c,6.0,10.0,5);
							SEs_NWay(Boss.x,Boss.y,12.0,15,5.5-1.5*i,gra_e_shot[19],20-c,0,10.0,5);
						}
						break;
					case 3:
						SPlaySound(11);
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y,9.0,25,5.5-2.0*i,gra_e_shot[18],20-c,4.5,10.0,5);
							SEs_NWay(Boss.x,Boss.y,9.0,25,6.5-2.0*i,gra_e_shot[19],20-c,0,10.0,5);
						}
						break;
				}
			}
		}
		if(c==60){
			Boss.life = 0;
		}
	}
	if(p==11){//スイカ登場
		if(c==0)	SBos_MoveTo(CENTER_X,CENTER_Y,50);
	}
	if(p==13){//文登場
		if(c==0)	SBos_MoveTo(CENTER_X,150,30);
	}
	int num = (Boss.count/5)%5;
	switch(num){
		case 0:	Boss.img_num = 0;	break;
		case 1:	Boss.img_num = 8;	break;
		case 2:	Boss.img_num = 16;	break;
		case 3:	Boss.img_num = 1;	break;
		case 4:	Boss.img_num = 9;	break;
	}
	Boss.img_count ++;
	if(Boss.move_count[0]<Boss.move_count[1]){
		if(Boss.move_x<=-0.1){
			if(Boss.move_count[0]<5||Boss.move_count[1]-Boss.move_count[0]<5){
				Boss.img_num = 2;
			}
			else{
				Boss.img_num = 10;
			}
		}
		else if(0.1<=Boss.move_x){
			if(Boss.move_count[0]<5||Boss.move_count[1]-Boss.move_count[0]<5){
				Boss.img_num = 18;
			}
			else{
				Boss.img_num = 26;
			}
		}
		Boss.img_count = 0;
		Boss.move_count[0]++;
	}
	else if(Boss.move_count[0]==Boss.move_count[1]){
		Boss.move_x = 0;
		Boss.move_y = 0;
	}
	Boss.x += Boss.move_x;
	Boss.y += Boss.move_y;
	Boss.atari_x[0] = Boss.x - Boss.img_x/16;
	Boss.atari_x[1] = Boss.x + Boss.img_x/16;
	Boss.atari_y[0] = Boss.y - Boss.img_y/12;
	Boss.atari_y[1] = Boss.y + Boss.img_y/12;
	return;
}

void SBos_MoveTo(float x,float y,int time){
	float sx = (x-Boss.x)/time;
	float sy = (y-Boss.y)/time;
	Boss.move_x = sx;
	Boss.move_y = sy;
	Boss.move_count[0] = 0;
	Boss.move_count[1] = time;
	
	return;
}

void SBos_Shot0(){
	//中ボススイカその１
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
		Boss.img_count = 0;
		int cp = c%350;
		if((cp>=0&&cp<50) || (cp>=90&&cp<140) || (cp>=180&&cp<230)){}
		else if((cp>=50&&cp<55) || (cp>=140&&cp<145) || (cp>=230&&cp<235)){
			Boss.img_num = 5;
		}
		else if((cp>=55&&cp<60) || (cp>=145&&cp<150) || (cp>=235&&cp<240)){
			Boss.img_num = 13;
		}
		else if((cp>=60&&cp<90) || (cp>=150&&cp<180)){
			int late;
			if(cp<90)	late = 90-cp;
			else		late = 180-cp;
			if(cp==60||cp==150){
				Boss.d_hanyou[0] = Player.x;
				Boss.d_hanyou[1] = Player.y;
			}
			Boss.d_hanyou[2] = Player.x;
			Boss.d_hanyou[3] = Player.y;
			Player.x = Boss.d_hanyou[0];
			Player.y = Boss.d_hanyou[1];
			switch(SAVE.Level){
				case 0:
					if(c%3==0){
						SPlaySound(11);
						SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),0,1,0.5+0.1*get_rand(25),gra_e_shot[9],late,-2+get_rand(4),10.0,5);
					}
					break;
				case 1:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),0,1,1.5+0.1*get_rand(25),gra_e_shot[9],late,-3+get_rand(6),10.0,5);
					break;
				case 2:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),50.0,3,1.5+0.1*get_rand(35),gra_e_shot[9],late,-3+get_rand(6),10.0,5);
					break;
				case 3:
					SPlaySound(11);
					for(int i=0;i<2;i++){
						SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),40.0,3,1.5+0.1*get_rand(45),gra_e_shot[9],late,-5+get_rand(10),10.0,5);
					}
					break;
			}
			Boss.img_num = 21;
			Player.x = Boss.d_hanyou[2];
			Player.y = Boss.d_hanyou[3];
		}
		else if(cp<290){
			if(cp==240){
				Boss.d_hanyou[0] = Player.x;
				Boss.d_hanyou[1] = Player.y;
			}
			Boss.d_hanyou[2] = Player.x;
			Boss.d_hanyou[3] = Player.y;
			Player.x = Boss.d_hanyou[0];
			Player.y = Boss.d_hanyou[1];
			int late = 290-cp;
			switch(SAVE.Level){
				case 0:
					if(c%3==0){
						SPlaySound(11);
						SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),40.0,1,0.5+0.1*get_rand(25),gra_e_shot[8],late,0,10.0,5);
					}
					break;
				case 1:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),35.0,1,1.5+0.1*get_rand(25),gra_e_shot[8],late,0,10.0,5);
					break;
				case 2:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),35.0,3,1.5+0.1*get_rand(35),gra_e_shot[8],late,0,10.0,5);
					break;
				case 3:
					SPlaySound(11);
					for(int i=0;i<2;i++){
						SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),10.0,5,1.5+0.1*get_rand(45),gra_e_shot[8],late,0,10.0,5);
					}
					break;
			}
			Boss.img_num = 21;
			Player.x = Boss.d_hanyou[2];
			Player.y = Boss.d_hanyou[3];
		}
	
	return;	
}

void SBos_Shot1(){
	//スイカその１
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 0:
						if(c%15==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x+90*cos(Radian(120*i+13*c/15,TRUE)),Boss.y-50+90*sin(Radian(120*i+13*c/15,TRUE)),120*i+13*c/15+180,1.5,gra_e_shot[27],10);
								SEs_Make(Boss.x+90*cos(Radian(120*i-17*c/15,TRUE)),Boss.y-50+90*sin(Radian(120*i-17*c/15,TRUE)),120*i-17*c/15+180,2.0,gra_e_shot[26],10);
							}
						}
						break;
					case 1:
						if(c%11==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x+90*cos(Radian(120*i+13*c/11,TRUE)),Boss.y-50+90*sin(Radian(120*i+13*c/11,TRUE)),120*i+13*c/11+180,1.5,gra_e_shot[27],10);
								SEs_Make(Boss.x+90*cos(Radian(120*i-17*c/11,TRUE)),Boss.y-50+90*sin(Radian(120*i-17*c/11,TRUE)),120*i-17*c/11+180,2.0,gra_e_shot[26],10);
							}
						}
						break;
					case 2:
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x+90*cos(Radian(120*i+13*c/5,TRUE)),Boss.y-50+90*sin(Radian(120*i+13*c/5,TRUE)),120*i+13*c/5+180,2.0,gra_e_shot[27],10);
								SEs_Make(Boss.x+90*cos(Radian(120*i-17*c/5,TRUE)),Boss.y-50+90*sin(Radian(120*i-17*c/5,TRUE)),120*i-17*c/5+180,2.5,gra_e_shot[26],10);
							}
							for(int i=0;i<2;i++){
								SEs_Make(Boss.x,Boss.y-50,180*i+13*c/5,1.5,gra_e_shot[6],10);
							}
						}
						break;
					case 3:
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x+90*cos(Radian(120*i+9*c/5,TRUE)),Boss.y-50+90*sin(Radian(120*i+9*c/5,TRUE)),120*i+9*c/5+180,2.5,gra_e_shot[27],10);
								SEs_Make(Boss.x+90*cos(Radian(120*i-13*c/5,TRUE)),Boss.y-50+90*sin(Radian(120*i-13*c/5,TRUE)),120*i-13*c/5+180,3.0,gra_e_shot[26],10);
							}
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x,Boss.y-50,120*i+7*c/5,2.0,gra_e_shot[6],10);
							}
						}
						break;
				}
			}
		}
	return;
}

void SBos_Shot2(){
	//スイカその２
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
		if(Boss.count<50)	c = 0;
		else			c -= 50;
		int cp = c%120;
		if(cp>=109&&cp<114)		Boss.img_num = 5;
		else if(cp>=114&&cp<=119)	Boss.img_num = 13;
		if(c>=90&&cp<10){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
		switch(SAVE.Level){
			case 0:
				if(cp==119){
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y-60,72.0,5,0.2,gra_e_shot[31],10,0.0,0.0,0,4);
				}
				break;
			case 1:
				if(cp==119){
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y-60,72.0,5,0.2,gra_e_shot[31],10,0.0,0.0,0,4);
				}
				break;
			case 2:
				if(cp==119){
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y-60,72.0,5,0.2,gra_e_shot[31],10,0.0,0.0,0,4);
				}
				break;
			case 3:
				if(cp==119){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y-60,60.0,6,0.2,gra_e_shot[31],10,30.0,0.0,0,4);
				}
				break;
		}
	return;
}

void SBos_Shot3(){
	//映姫通常２（フランドール）
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
		if(c>=150){
			int cp = (c-150)%40;
			if(cp==0){
				SPlaySound(10);
				for(int i=0;i<60;i++){
					SEs_Make(Boss.x,Boss.y,6*i,1.5,gra_e_shot[14],5,5.0,5);
					SEs_Make(Boss.x,Boss.y,6*i,2.0,gra_e_shot[14],5,5.0,5);
				}
			}
		}
	return;
}

void SBos_Shot4(){
	//映姫通常１（妹紅）
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
		if(c>=150){
			c -= 150;
			if(c%5==0){
				SPlaySound(10);
				if(c<5*4){
					for(int i=0;i<3;i++){
						for(int a=0;a<1+c/6;a++){
							int img;
							if(a==0||a==4)	img = gra_e_shot[39];
							if(a==1||a==3)	img = gra_e_shot[42];
							if(a==2)	img = gra_e_shot[38];
							int effect = 1;
							if(i==0&&a==0)	effect = 0;
							SEs_Make(Boss.x,Boss.y,1.5*c+20.0+120*i-0.5*a,2.0-0.2*a,img,10,0,0.0,0,effect);
						}
					}
				}
				else{
					for(int i=0;i<3;i++){
						for(int a=0;a<5;a++){
							int img;
							if(a==0||a==4)	img = gra_e_shot[39];
							if(a==1||a==3)	img = gra_e_shot[42];
							if(a==2)	img = gra_e_shot[38];
							int effect = 1;
							if(i==0&&a==0)	effect = 0;
							SEs_Make(Boss.x,Boss.y,1.5*c+20.0+120*i-0.5*a,2.0-0.2*a,img,10,0,0.0,0,effect);
						}
					}
				}
			}
		}

	return;
}

void SBos_Shot5(){
	//映姫通常４（諏訪子）
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
		if(c>=150){
			c -= 150;
			if(c%15==0){
				SPlaySound(10);
				int effect;
				for(int a=0;a<8;a++){
					for(int i=0;i<8;i++){
						effect = 1;
						if(a==0&&i==0)	effect = 0;
						float an = -c+45*i+a;
						SEs_Make(Boss.x,Boss.y,an,2.8-0.03*a,gra_e_shot[54],10,0,0.0,0,effect);
					}
				}
				for(int a=0;a<8;a++){
					for(int i=0;i<8;i++){
						effect = 1;
						if(a==0&&i==0)	effect = 0;
						SEs_Make(Boss.x,Boss.y,c+45*i-a,2.3-0.04*a,gra_e_shot[55],10,0,0.0,0,effect);
					}
				}
			}
		}
	return;
}

void SBos_Shot(){
	if(debug_nobullet==1)	return;
	int p = Boss.shot_pattern;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
	
	if(p==-1){//ボスの攻撃移行用パターン
		if(Boss.count==120){
			Boss.life = 0;
			Boss.count = 0;
			Boss.gage_exist = 1;
		}
	}
	switch(p){
		case 0:	SBos_Shot0();	break;
		case 1:	SBos_Shot1();	break;
		case 2:	SBos_Shot2();	break;
		case 3:	SBos_Shot3();	break;
		case 4:	SBos_Shot4();	break;
		case 5:	SBos_Shot5();	break;
	}
	if(p==6){//映姫通常３（紫）
		if(c>=150){
			c -= 150;
			if(c%15==0){
				SPlaySound(10);
				int effect;
				SEs_NWay(Boss.x,Boss.y,11.25,32,2.5,gra_e_shot[51],10,5.625);
				SEs_NWay(Boss.x,Boss.y,11.25,32,1.5,gra_e_shot[48],10,get_rand(11));
			}
		}
	}
	else if(p==7){//文通常１
		if(c>=90){
			c -= 90;
			if(c==0)	SPlaySound(19);
			if(c>=50){
				switch(SAVE.Level){
					case 0:
						c += 70;
						if(c%20==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/20,2.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/20,1.0,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/20,2.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/20,1.0,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
					case 1:
						c += 10;
						if(c%15==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,3.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,1.0,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,3.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,1.0,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
					case 2:
						c += 70;
						if(c%15==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,3.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,3.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),45*c/15,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
					case 3:
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/5,5.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/5,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/5,5.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/5,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
				}
			}
		}
	}
	else if(p==8){//文通常２
		if(c>=90){
			Boss.b_zanzou = true;
			c -= 90;
			int cp = c%390;
			if(cp==0||cp==50||cp==80){
				SPlaySound(8);
				int move_x = 40+get_rand(30);
				int move_y = 100+get_rand(70);
				if(CENTER_X<Boss.x)	move_x = limit_x[0];
				else			move_x = limit_x[1];
				SBos_MoveTo(move_x,move_y,30);			
			}
			if(cp==150){
				int move_x = CENTER_X;
				int move_y = 100+get_rand(70);
				SBos_MoveTo(move_x,move_y,30);			
			}
			if(cp<110){
				switch(SAVE.Level){
					case 0:
						if(c%2==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,30.0,4,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,6.0-0.1*get_rand(20),0,16);		
						}
						break;		
					case 1:
						if(c%2==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,30.0,4,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,7.0-0.1*get_rand(20),0,16);		
						}
						break;		
					case 2:
						if(c%1==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,30.0,4,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,8.0-0.1*get_rand(30),0,16);		
						}
						break;		
					case 3:
						if(c%1==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,20.0,6,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,8.0-0.1*get_rand(30),0,16);		
						}
						break;		
				}
			}
			if(cp>=200&&cp<320){
				if(cp==200){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
				}
				switch(SAVE.Level){
					case 0:
						if(cp%8==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<6;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260)	SEs_NWay(Boss.x,Boss.y,72.0,5,1.5+i*0.4,gra_e_shot[19],10,i*3.0,0.0,0,0,effect);		
								else		SEs_NWay(Boss.x,Boss.y,72.0,5,3.5-i*0.4,gra_e_shot[20],10,i*3.0,0.0,0,0,effect);		
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
					case 1:
						if(cp%8==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<6;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260)	SEs_NWay(Boss.x,Boss.y,36.0,10,2.0+i*0.4,gra_e_shot[19],10,18+i*3.0,0.0,0,0,effect);		
								else		SEs_NWay(Boss.x,Boss.y,36.0,10,4.0-i*0.4,gra_e_shot[20],10,18+i*3.0,0.0,0,0,effect);		
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
					case 2:
						if(cp%5==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<6;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260)	SEs_NWay(Boss.x,Boss.y,36.0,10,2.5+i*0.4,gra_e_shot[19],10,18+i*3.0,0.0,0,0,effect);		
								else		SEs_NWay(Boss.x,Boss.y,36.0,10,4.5-i*0.4,gra_e_shot[20],10,18+i*3.0,0.0,0,0,effect);		
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
					case 3:
						if(cp%5==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<6;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260)	SEs_NWay(Boss.x,Boss.y,24.0,15,2.5+i*0.4,gra_e_shot[19],10,i*3.0,0.0,0,0,effect);		
								else		SEs_NWay(Boss.x,Boss.y,24.0,15,4.5-i*0.4,gra_e_shot[20],10,i*3.0,0.0,0,0,effect);		
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
				}
			}
		}
	}
	else if(p==9){//文通常３
		if(c>=120){
			int cp = (c-120)%240;
			if(cp==0)	SPlaySound(19);
			if(cp>30&&cp<35)	Boss.img_num = 5;
			else if(cp>=35&&cp<40)	Boss.img_num = 13;
			else if(cp>=140&&cp<145)Boss.img_num = 13;
			else if(cp>=145&&cp<150)Boss.img_num = 5;
			else if(cp>=150||cp<=30){}
			else{
				Boss.img_num = 21;
				Boss.img_count = 0;
			}
			if(cp>=40&&cp<140){
				if(cp==40){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;					
				}
				Boss.d_hanyou[2] = Player.x;
				Boss.d_hanyou[3] = Player.y;
				Player.x = Boss.d_hanyou[0];
				Player.y = Boss.d_hanyou[1];
				switch(SAVE.Level){
					case 0:
						if(cp%6==0){
							SPlaySound(10);
							SEs_NWay(Boss.x-22,Boss.y-13,18.0,20,3.0,gra_e_shot[22],10,9.0*(cp%12/6),0.0,0,0,0);				
						}
						break;
					case 1:
						if(cp%5==0){
							SPlaySound(10);
							SEs_NWay(Boss.x-22,Boss.y-13,18.0,20,3.5,gra_e_shot[22],10,9.0*(cp%10/5),0.0,0,0,0);				
						}
						break;
					case 2:
						if(cp%4==0){
							SPlaySound(10);
							SEs_NWay(Boss.x-22,Boss.y-13,14.4,25,4.0,gra_e_shot[22],10,7.2*(cp%8/4),0.0,0,0,0);				
						}
						break;
					case 3:
						if(cp%3==0){
							SPlaySound(10);
							SEs_NWay(Boss.x-22,Boss.y-13,12.0,30,5.0,gra_e_shot[22],10,6.0*(cp%6/3),0.0,0,0,0);				
						}
						break;
				}
				Player.x = Boss.d_hanyou[2];
				Player.y = Boss.d_hanyou[3];
			}
			if(cp==170){
				int move_x = 30+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,40);
			}
		}
	}	
	else if(p==10){//３面スイカ
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 0:
						if(c%13==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/13,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/13,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/13,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/13,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								SEs_Make(x1,y1,angle1,1.5,gra_e_shot[27],10);
								SEs_Make(x2,y2,angle2,2.0,gra_e_shot[29],10);
							}
						}
						break;
					case 1:
						if(c%9==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/9,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/9,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/9,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/9,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								SEs_Make(x1,y1,angle1,2.0,gra_e_shot[27],10);
								SEs_Make(x2,y2,angle2,2.5,gra_e_shot[29],10);
							}
						}
						break;
					case 2:
						if(c%9==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/9,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/9,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/9,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/9,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								SEs_Make(x1,y1,angle1,2.0,gra_e_shot[27],10);
								SEs_Make(x2,y2,angle2,2.5,gra_e_shot[29],10);
							}
						}
						if(c%50==0){
							int rand = get_rand(19);
							for(int i=0;i<12;i++){
								SEs_Make(Boss.x,Boss.y-50,rand+30*i,3.0,gra_e_shot[4],10,0.0,0,0,i%12);
								SEs_Make(Boss.x,Boss.y-50,rand+30*i+7.5,2.5,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+30*i+15,2.0,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+30*i+22.5,1.5,gra_e_shot[4],10,0.0,0,0,1);
							}
						}
						break;
					case 3:
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/5,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/5,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/5,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/5,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								SEs_Make(x1,y1,angle1,2.5,gra_e_shot[27],10);
								SEs_Make(x2,y2,angle2,3.0,gra_e_shot[29],10);
							}
						}
						if(c%50==0){
							int rand = get_rand(19);
							for(int i=0;i<18;i++){
								SEs_Make(Boss.x,Boss.y-50,rand+20*i,4.0,gra_e_shot[4],10,0.0,0,0,i%18);
								SEs_Make(Boss.x,Boss.y-50,rand+20*i+5,3.5,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+20*i+10,3.0,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+20*i+15,2.5,gra_e_shot[4],10,0.0,0,0,1);
							}
						}
						break;
				}
			}
		}		
	}
	else if(p==11){//(アンリミテッドペナンス）
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 3:
						if(c%8==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<3;i++){
								for(int a=0;a<7;a++){
									SEs_Make(x,y,90+c+120*i+2.0*a,4.0-0.3*a,gra_e_shot[19],10,0.0,0,0,1);
									SEs_Make(x,y,90-c+120*i-2.0*a,4.0-0.3*a,gra_e_shot[18],10,0.0,0,0,a%7);
								}
							}
						}
						break;
				}
			}
		}
	}
	else if(p==12){//３面文
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 0:
						if(c%10==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<1;i++){
								for(int a=0;a<6;a++){
									SEs_Make(x,y,2*c+2.0*a,2.5-0.15*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,2*c+180-2.0*a,2.5-0.15*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
					case 1:
						if(c%10==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<1;i++){
								for(int a=0;a<8;a++){
									SEs_Make(x,y,2*c+2.0*a,2.5-0.15*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,2*c+180-2.0*a,2.5-0.15*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
					case 2:
						if(c%10==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<3;i++){
								for(int a=0;a<4;a++){
									SEs_Make(x,y,+c+120*i+2.0*a,3.0-0.3*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,-c+120*i-2.0*a,3.0-0.3*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
					case 3:
						if(c%8==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<3;i++){
								for(int a=0;a<6;a++){
									SEs_Make(x,y,+1.5*c+120*i+2.0*a,5.0-0.5*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,-1.5*c+120*i-2.0*a,5.0-0.5*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
				}
			}
		}
	}
	else if(p==13){//３面紫通常１
		if(c>=60){
			switch(SAVE.Level){
				case 0:
					if(c%10==0){
						SPlaySound(10);
						if(c%20==0){
							for(int i=0;i<1;i++){
								SEs_NWay(Boss.x-30,Boss.y,24.0,15,2.5-1.0*i,gra_e_shot[48],10,0.0,0.0,0,0,i%2);				
							}
						}
						else{
							for(int i=0;i<1;i++){
								SEs_NWay(Boss.x+30,Boss.y,24.0,15,2.0-1.0*i,gra_e_shot[48],10,0.0,0.0,0,0,i%2);				
							}
						}
					}
					break;
				case 1:
					if(c%10==0){
						SPlaySound(10);
						if(c%20==0){
							for(int i=0;i<1;i++){
								SEs_NWay(Boss.x-30,Boss.y,20.0,18,3.0-1.5*i,gra_e_shot[48],10,10.0,0.0,0,0,i%2);				
							}
						}
						else{
							for(int i=0;i<1;i++){
								SEs_NWay(Boss.x+30,Boss.y,20.0,18,2.0-1.0*i,gra_e_shot[48],10,10.0,0.0,0,0,i%2);				
							}
						}
					}
					break;
				case 2:
					if(c%10==0){
						SPlaySound(10);
						if(c%20==0){
							for(int i=0;i<2;i++){
								SEs_NWay(Boss.x-30,Boss.y,18.0,20,3.5-1.5*i,gra_e_shot[48],10,9.0,0.0,0,0,i%2);				
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay(Boss.x+30,Boss.y,18.0,20,3.0-1.0*i,gra_e_shot[48],10,9.0,0.0,0,0,i%2);				
							}
						}
					}
					break;
				case 3:
					if(c%8==0){
						SPlaySound(10);
						if(c%16==0){
							for(int i=0;i<2;i++){
								SEs_NWay(Boss.x-30,Boss.y,18.0,20,5.0-2.0*i,gra_e_shot[48],10,9.0,0.0,0,0,i%2);				
							}
						}
						else{
							for(int i=0;i<2;i++){
								SEs_NWay(Boss.x+30,Boss.y,18.0,20,3.0-1.0*i,gra_e_shot[48],10,9.0,0.0,0,0,i%2);				
							}
						}
					}
					if(c%30==0){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,12.0,30,6.0-1.0*i,gra_e_shot[4],20,6.0,0.0,0,0,i%2);						
						}
					}
					break;
			}
		}
	}
	else if(p==14){//３面紫通常２
		if(c==120){
			for(int i=0;i<2;i++){
				SEn_Make(Boss.x,Boss.y,8,360+180*i,22,19,2);					
			}
		}
		if(c>=170){
			switch(SAVE.Level){
				case 3:
					if(c%90==0){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.0-1.0*i,gra_e_shot[4],20,9.0,0.0,0,0,i%2);						
						}
					}
					break;
			}
		}
	}
	else if(p==15){//３面紫通常３
		if(c==120){
			for(int i=0;i<4;i++){
				SEn_Make(Boss.x,Boss.y,8,1+i,23,21,2);					
			}
		}
		if(c>=170){
			switch(SAVE.Level){
				case 3:
					if(c%90==0){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.0-1.0*i,gra_e_shot[38],20,9.0,0.0,0,0,i%2);						
						}
					}
					break;
			}
		}
	}
	else if(p==16){//３面紫通常４
		if(c>=170){
			switch(SAVE.Level){
				case 0:
					if(c%10==0){
						SPlaySound(10);
						for(int i=0;i<3;i++){
							SEs_Make(Boss.x,Boss.y,c+120.0*i,1.5,gra_e_shot[22],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-c+120.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					break;
				case 1:
					if(c%10==0){
						SPlaySound(10);
						for(int i=0;i<4;i++){
							SEs_Make(Boss.x,Boss.y,c+90.0*i,2.0,gra_e_shot[22],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-c+90.0*i,2.0,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					break;
				case 2:
					if(c%8==0){
						SPlaySound(10);
						for(int i=0;i<6;i++){
							SEs_Make(Boss.x,Boss.y,c+60.0*i,2.0,gra_e_shot[22],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-c+60.0*i,2.0,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					break;
				case 3:
					if(c%8==0){
						SPlaySound(10);
						for(int i=0;i<8;i++){
							SEs_Make(Boss.x,Boss.y,c+45.0*i,2.0,gra_e_shot[22],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-c+45.0*i,2.0,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					break;
			}
		}
	}
	else if(p==17){//４中ボススイカその１
		Boss.img_count = 0;
		int cp = c%350;
		if((cp>=0&&cp<50) || (cp>=90&&cp<140) || (cp>=180&&cp<230)){}
		else if((cp>=50&&cp<55) || (cp>=140&&cp<145) || (cp>=230&&cp<235)){
			Boss.img_num = 5;
		}
		else if((cp>=55&&cp<60) || (cp>=145&&cp<150) || (cp>=235&&cp<240)){
			Boss.img_num = 13;
		}
		else if((cp>=60&&cp<90) || (cp>=150&&cp<180)){
			int late;
			if(cp<90)	late = 90-cp;
			else		late = 180-cp;
			if(cp==60||cp==150){
				Boss.d_hanyou[0] = Player.x;
				Boss.d_hanyou[1] = Player.y;
			}
			Boss.d_hanyou[2] = Player.x;
			Boss.d_hanyou[3] = Player.y;
			Player.x = Boss.d_hanyou[0];
			Player.y = Boss.d_hanyou[1];
			switch(SAVE.Level){
				case 1:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),0,1,1.5+0.1*get_rand(25),gra_e_shot[9],late,-3+get_rand(6),10.0,5);
					if(cp==70||cp==160){
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y-60,40.0,9,3.0-0.5*i,gra_e_shot[33],20,0.0,10.0,15);
						}
					}
					break;
				case 2:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),50.0,3,1.5+0.1*get_rand(35),gra_e_shot[9],late,-3+get_rand(6),10.0,5);
					if(cp==70||cp==160){
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y-60,40.0,9,3.5-0.5*i,gra_e_shot[33],20,0.0,10.0,15);
						}
					}
					break;
				case 3:
					SPlaySound(11);
					for(int i=0;i<2;i++){
						SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),40.0,3,1.5+0.1*get_rand(45),gra_e_shot[9],late,-5+get_rand(10),10.0,5);
					}
					if(cp==70||cp==160){
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y-60,24.0,15,4.0-1.0*i,gra_e_shot[33],20,0.0,10.0,15);
						}
					}
					break;
			}
			Boss.img_num = 21;
			Player.x = Boss.d_hanyou[2];
			Player.y = Boss.d_hanyou[3];
		}
		else if(cp<290){
			if(cp==240){
				Boss.d_hanyou[0] = Player.x;
				Boss.d_hanyou[1] = Player.y;
			}
			Boss.d_hanyou[2] = Player.x;
			Boss.d_hanyou[3] = Player.y;
			Player.x = Boss.d_hanyou[0];
			Player.y = Boss.d_hanyou[1];
			int late = 290-cp;
			switch(SAVE.Level){
				case 1:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),35.0,1,1.5+0.1*get_rand(25),gra_e_shot[8],late,0,10.0,5);
					if(cp==270){
						for(int i=0;i<5;i++){
							SEs_NWay(Boss.x,Boss.y-60,40.0,9,3.0-0.5*i,gra_e_shot[33],20,0.0,10.0,15);
						}
					}
					break;
				case 2:
					SPlaySound(11);
					SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),35.0,3,1.5+0.1*get_rand(35),gra_e_shot[8],late,0,10.0,5);
					if(cp==270){
						for(int i=0;i<5;i++){
							SEs_NWay(Boss.x,Boss.y-60,40.0,9,3.5-0.5*i,gra_e_shot[33],20,0.0,10.0,15);
						}
					}
					break;
				case 3:
					SPlaySound(11);
					for(int i=0;i<2;i++){
						SEs_NWay(Boss.x+get_rand(32)*cos(Radian(get_rand(360),TRUE)),Boss.y-60+get_rand(32)*sin(Radian(get_rand(360),TRUE)),10.0,5,1.5+0.1*get_rand(45),gra_e_shot[8],late,0,10.0,5);
					}
					if(cp==270){
						for(int i=0;i<5;i++){
							SEs_NWay(Boss.x,Boss.y-60,24.0,15,4.0-0.5*i,gra_e_shot[33],20,0.0,10.0,15);
						}
					}
					break;
			}
			Boss.img_num = 21;
			Player.x = Boss.d_hanyou[2];
			Player.y = Boss.d_hanyou[3];
		}
	}
	else if(p==18){//４面スイカその１
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 1:
						if(c%9==0){
							for(int i=0;i<2;i++){
								SEs_Make(Boss.x,Boss.y-50,180*i+6*c/5,1.5,gra_e_shot[45],20,10.0,15);
							}
						}
						Boss.d_hanyou[0] = Player.x;
						Boss.d_hanyou[1] = Player.y;
						Player.x = Boss.x;
						Player.y = Boss.y-50;
						if(c%18<9&&c%3==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								float d2 = 120*sin(Radian(2*c+90,TRUE))+2;
								float ang2 = -3*c+120*i;
								SEs_NWay(Boss.x+d2*cos(Radian(ang2,TRUE)),Boss.y-50+d2*sin(Radian(ang2,TRUE)),0.0,1,2.0,gra_e_shot[44],10,0);
							}
						}
						else if(c%18>=9&&c%3==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								float d1 = 120*sin(Radian(2*c,TRUE))+2;
								float ang1 = 3*c+120*i;
								SEs_NWay(Boss.x+d1*cos(Radian(ang1,TRUE)),Boss.y-50+d1*sin(Radian(ang1,TRUE)),0.0,1,2.0,gra_e_shot[43],10,0);
							}
						}
						Player.x = Boss.d_hanyou[0];
						Player.y = Boss.d_hanyou[1];
						break;
					case 2:
						if(c%5==0){
							for(int i=0;i<2;i++){
								SEs_Make(Boss.x,Boss.y-50,180*i+6*c/5,2.0,gra_e_shot[45],20,10.0,15);
							}
						}
						Boss.d_hanyou[0] = Player.x;
						Boss.d_hanyou[1] = Player.y;
						Player.x = Boss.x;
						Player.y = Boss.y-50;
						if(c%12<6&&c%2==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								float d2 = 120*sin(Radian(2*c+90,TRUE))+2;
								float ang2 = -3*c+120*i;
								SEs_NWay(Boss.x+d2*cos(Radian(ang2,TRUE)),Boss.y-50+d2*sin(Radian(ang2,TRUE)),0.0,1,2.5,gra_e_shot[44],10,0);
							}
						}
						else if(c%12>=6&&c%2==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								float d1 = 120*sin(Radian(2*c,TRUE))+2;
								float ang1 = 3*c+120*i;
								SEs_NWay(Boss.x+d1*cos(Radian(ang1,TRUE)),Boss.y-50+d1*sin(Radian(ang1,TRUE)),0.0,1,2.5,gra_e_shot[43],10,0);
							}
						}
						Player.x = Boss.d_hanyou[0];
						Player.y = Boss.d_hanyou[1];
						break;
					case 3:
						if(c%5==0){
							for(int i=0;i<6;i++){
								SEs_Make(Boss.x,Boss.y-50,60*i+6*c/5,2.0,gra_e_shot[45],20,10.0,15);
							}
						}
						Boss.d_hanyou[0] = Player.x;
						Boss.d_hanyou[1] = Player.y;
						Player.x = Boss.x;
						Player.y = Boss.y-50;
						if(c%6<3){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								float d2 = 120*sin(Radian(2*c+90,TRUE))+2;
								float ang2 = -3*c+120*i;
								SEs_NWay(Boss.x+d2*cos(Radian(ang2,TRUE)),Boss.y-50+d2*sin(Radian(ang2,TRUE)),0.0,1,3.0,gra_e_shot[44],10,0);
							}
						}
						else if(c%6>=3){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								float d1 = 120*sin(Radian(2*c,TRUE))+2;
								float ang1 = 3*c+120*i;
								SEs_NWay(Boss.x+d1*cos(Radian(ang1,TRUE)),Boss.y-50+d1*sin(Radian(ang1,TRUE)),0.0,1,3.0,gra_e_shot[43],10,0);
							}
						}
						Player.x = Boss.d_hanyou[0];
						Player.y = Boss.d_hanyou[1];
						break;
				}
			}
		}
	}
	else if(p==19){//スイカその２
		if(Boss.count<50)	c = 0;
		else			c -= 50;
		if(c>0&&c<=50&&Boss.i_hanyou[0]==0){
			Boss.count = 101;
		}
		else if(Boss.i_hanyou[0]>0){
			Boss.count = 99;
		}
		Boss.i_hanyou[1] = Boss.i_hanyou[0];
		Boss.i_hanyou[0] = 0;
		int cp = c%10000;
		switch(SAVE.Level){
			case 1:
				if(cp==119){
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y,90.0,4,0.0,gra_e_shot[31],10,0.0,0.0,0,30);
					SEs_NWay(Boss.x,Boss.y,90.0,4,0.0,gra_e_shot[31],10,45.0,0.0,0,31);
				}
				break;
			case 2:
				if(cp==119){
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y,60.0,6,0.0,gra_e_shot[31],10,0.0,0.0,0,30);
					SEs_NWay(Boss.x,Boss.y,60.0,6,0.0,gra_e_shot[31],10,30.0,0.0,0,31);
				}
				break;
			case 3:
				if(cp==119){
					SPlaySound(10);
					SEs_NWay(Boss.x,Boss.y,40.0,9,0.0,gra_e_shot[31],10,0.0,0.0,0,30);
					SEs_NWay(Boss.x,Boss.y,40.0,9,0.0,gra_e_shot[31],10,20.0,0.0,0,31);
				}
				break;
		}
	}
	else if(p==20){//５面文通常２
		if(c>=90){
			Boss.b_zanzou = true;
			c -= 90;
			int cp = c%390;
			if(cp==0||cp==50||cp==80){
				SPlaySound(8);
				int move_x = 40+get_rand(30);
				int move_y = 100+get_rand(70);
				if(CENTER_X<Boss.x)	move_x = limit_x[0];
				else			move_x = limit_x[1];
				SBos_MoveTo(move_x,move_y,30);			
			}
			if(cp==150){
				int move_x = CENTER_X;
				int move_y = 100+get_rand(70);
				SBos_MoveTo(move_x,move_y,30);			
			}
			if(cp<110){
				switch(SAVE.Level){
					case 1:
						if(c%2==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,30.0,4,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,7.0-0.1*get_rand(20),0,16);		
						}
						break;		
					case 2:
						if(c%1==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,30.0,4,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,8.0-0.1*get_rand(30),0,16);		
						}
						break;		
					case 3:
						if(c%1==0){
							SPlaySound(10);
							SEs_NWay(Boss.x,Boss.y,20.0,6,6.0-0.1*get_rand(20),gra_e_shot[18],5,180.0,8.0-0.1*get_rand(30),0,16);		
						}
						break;		
				}
			}
			if(cp>=200&&cp<320){
				if(cp==200){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
				}
				switch(SAVE.Level){
					case 1:
						if(cp%8==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<6;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260)	SEs_NWay(Boss.x,Boss.y,36.0,10,2.5+i*0.4,gra_e_shot[19],10,18+i*3.0,0.0,0,0,effect);		
								else		SEs_NWay(Boss.x,Boss.y,36.0,10,4.5-i*0.4,gra_e_shot[20],10,18+i*3.0,0.0,0,0,effect);		
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
					case 2:
						if(cp%5==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<6;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260)	SEs_NWay(Boss.x,Boss.y,30.0,12,3.0+i*0.4,gra_e_shot[19],10,15+i*3.0,0.0,0,0,effect);		
								else		SEs_NWay(Boss.x,Boss.y,30.0,12,5.0-i*0.4,gra_e_shot[20],10,15+i*3.0,0.0,0,0,effect);		
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
					case 3:
						if(cp%5==0){
							Boss.d_hanyou[2] = Player.x;
							Boss.d_hanyou[3] = Player.y;
							Player.x = Boss.d_hanyou[0];
							Player.y = Boss.d_hanyou[1];
							SPlaySound(10);
							for(int i=0;i<7;i++){
								int effect = 1;
								if(i==0)	effect = 0;
								if(cp<260){
									SEs_NWay(Boss.x,Boss.y,24.0,15,3.0+i*0.5,gra_e_shot[19],10,i*3.0,0.0,0,0,effect);		
								}
								else{
									SEs_NWay(Boss.x,Boss.y,24.0,15,6.5-i*0.5,gra_e_shot[20],10,i*3.0,0.0,0,0,effect);		
								}
							}
							Player.x = Boss.d_hanyou[2];
							Player.y = Boss.d_hanyou[3];
						}		
						break;
				}
			}
		}
	}
	else if(p==21){//５面文通常３
		if(c>=90){
			c -= 90;
			if(c==0)	SPlaySound(19);
			if(c>=50){
				switch(SAVE.Level){
					case 1:
						if(c%10==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,3.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10+180,3.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,1.0,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,3.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10+180,3.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,1.0,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
					case 2:
						if(c%10==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,3.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10+180,3.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,3.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10+180,3.5,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/10,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
					case 3:
						if(c%4==0){
							SPlaySound(10);
							for(int i=0;i<6;i++){
								float angle = Radian(60*i+30,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/4,6.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/4+180,6.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/4,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
							for(int i=0;i<6;i++){
								float angle = Radian(60*i,TRUE);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/4,6.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/4+180,6.0,gra_e_shot[8],10,0,0.0,0,0);
								SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),25*c/4,1.5,gra_e_shot[9],10,0,0.0,0,1);
							}
						}
						break;
				}
			}
		}
	}
	else if(p==22){//５面文通常４
		if(Boss.count==0&&SAVE.Level<3){
			int move_y = 120+get_rand(60);
			SBos_MoveTo(CENTER_X,move_y,20);		
		}
		if(c>=90){
			Boss.b_zanzou = true;
			c -= 90;
			int cp = c%250;
			
			if(cp==100){
				int move_x = 50+get_rand(30);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,20);
			}
			if(cp==240){
				int move_y = 120+get_rand(60);
				SBos_MoveTo(CENTER_X,move_y,20);
			}
			if(cp==0){
				SPlaySound(19);
			}
			if(cp==50){
				SPlaySound(10);
				switch(SAVE.Level){
					case 1:
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.0+0.4*i,gra_e_shot[22],10,9.0,0.0,0,33);		
						}
						break;		
					case 2:
						for(int i=0;i<5;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.0+0.4*i,gra_e_shot[22],10,9.0,0.0,0,33);		
						}
						break;		
					case 3:
						for(int i=0;i<7;i++){
							SEs_NWay(Boss.x,Boss.y,12.0,30,3.0+0.4*i,gra_e_shot[22],10,6.0,0.0,0,33);		
						}
						break;		
				}
			
			}
			if(cp>=120&&cp<=180){
				if(cp==120){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
				}
				Boss.d_hanyou[2] = Player.x;
				Boss.d_hanyou[3] = Player.y;
				Player.x = Boss.d_hanyou[0];
				Player.y = Boss.d_hanyou[1];
				switch(SAVE.Level){
					case 1:
						if(cp%12==0){
							SPlaySound(10);
							int cc = (cp-120)/12;
							for(int i=0;i<5;i++){
								SEs_NWay(Boss.x,Boss.y,180.0-36.0*cc,2,5.0-0.4*i,gra_e_shot[23],10);		
								SEs_NWay(Boss.x,Boss.y,180.0-36.0*cc,2,5.0-0.4*i,gra_e_shot[23],10,180.0);		
							}
						}
						break;		
					case 2:
						if(cp%6==0){
							SPlaySound(10);
							int cc = (cp-120)/6;
							for(int i=0;i<5;i++){
								SEs_NWay(Boss.x,Boss.y,180.0-18.0*cc,2,5.0-0.4*i,gra_e_shot[23],10);		
								SEs_NWay(Boss.x,Boss.y,180.0-18.0*cc,2,5.0-0.4*i,gra_e_shot[23],10,180.0);		
							}
						}
						break;		
					case 3:
						if(cp%6==0){
							SPlaySound(10);
							int cc = (cp-120)/6;
							for(int i=0;i<10;i++){
								SEs_NWay(Boss.x,Boss.y,180.0-18.0*cc,2,5.0-0.4*i,gra_e_shot[23],10);		
								SEs_NWay(Boss.x,Boss.y,180.0-18.0*cc,2,5.0-0.4*i,gra_e_shot[23],10,180.0);		
							}
						}
						break;		
				}
				Player.x = Boss.d_hanyou[2];
				Player.y = Boss.d_hanyou[3];
			}
			if(cp>180&&cp<=240){
				switch(SAVE.Level){
					case 1:
						if(cp%6==0){
							SPlaySound(10);
							for(int i=0;i<10;i++){
								SEs_Make(Boss.x,Boss.y,36*i+18,5.0,gra_e_shot[22],10);
							}
						}
						break;		
					case 2:
						if(cp%6==0){
							SPlaySound(10);
							for(int i=0;i<18;i++){
								SEs_Make(Boss.x,Boss.y,20*i+10,5.0,gra_e_shot[22],10);
							}
						}
						break;		
					case 3:
						if(cp%3==0){
							SPlaySound(10);
							for(int i=0;i<18;i++){
								SEs_Make(Boss.x,Boss.y,20*i+10,7.0,gra_e_shot[22],10);
							}
						}
						break;		
				}
			}
		}
	}
	else if(p==23){//６面スイカ
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 1:
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/5,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/5,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/5,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/5,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								for(int i=0;i<2;i++){
									SEs_Make(x1,y1,angle1+180*i,1.5,gra_e_shot[5],10);
									SEs_Make(x2,y2,angle2+180*i,2.0,gra_e_shot[53],10);
								}
							}
						}
						break;
					case 2:
						if(c%9==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/9,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/9,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/9,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/9,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								for(int i=0;i<2;i++){
									SEs_Make(x1,y1,angle1+180*i,1.5,gra_e_shot[5],10);
									SEs_Make(x2,y2,angle2+180*i,2.0,gra_e_shot[53],10);
								}
							}
						}
						if(c%50==0){
							int rand = get_rand(19);
							for(int i=0;i<12;i++){
								SEs_Make(Boss.x,Boss.y-50,rand+30*i,3.0,gra_e_shot[4],10,0.0,0,0,i%100);
								SEs_Make(Boss.x,Boss.y-50,rand+30*i+5,2.5,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+30*i+10,2.0,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+30*i+15,1.5,gra_e_shot[4],10,0.0,0,0,1);
							}
						}
						break;
					case 3:
						if(c%5==0){
							SPlaySound(10);
							for(int i=0;i<2;i++){
								float x1 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+13*c/5,TRUE));
								float x2 = Boss.x+110*sin(Radian(1.0*c,TRUE))*cos(Radian(180*i+90-13*c/5,TRUE));
								float y1 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+13*c/5,TRUE));
								float y2 = Boss.y-50+110*sin(Radian(1.0*c,TRUE))*sin(Radian(180*i+90-13*c/5,TRUE));
								float angle1;
								if(Boss.x==x1){
									if(Boss.y-50>y1)	angle1 = 270;
									else			angle1 = 90;
								}
								else{
									angle1 = Radian(atan2((Boss.y-50)-y1,Boss.x-x1),FALSE);
								}
								float angle2;
								if(Boss.x==x2){
									if(Boss.y-50>y2)	angle2 = 270;
									else			angle2 = 90;
								}
								else{
									angle2 = Radian(atan2((Boss.y-50)-y2,Boss.x-x2),FALSE);
								}
								for(int i=0;i<2;i++){
									SEs_Make(x1,y1,angle1+180*i,1.5,gra_e_shot[5],10);
									SEs_Make(x2,y2,angle2+180*i,2.0,gra_e_shot[53],10);
								}
							}
						}
						if(c%50==0){
							int rand = get_rand(19);
							for(int i=0;i<18;i++){
								SEs_Make(Boss.x,Boss.y-50,rand+20*i,3.0,gra_e_shot[4],10,0.0,0,0,i%18);
								SEs_Make(Boss.x,Boss.y-50,rand+20*i+5,2.5,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+20*i+10,2.0,gra_e_shot[4],10,0.0,0,0,1);
								SEs_Make(Boss.x,Boss.y-50,rand+20*i+15,1.5,gra_e_shot[4],10,0.0,0,0,1);
							}
						}
						break;
				}
			}
		}		
	}
	else if(p==24){//６面文
		if(c>=50){
			if(c>=50&&c<55)		Boss.img_num = 5;
			else if(c>=55&&c<60)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=60){
				switch(SAVE.Level){
					case 1:
						if(c%10==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<3;i++){
								for(int a=0;a<5;a++){
									SEs_Make(x,y,+2.0*c+120*i+2.0*a,3.0-0.4*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,-2.0*c+120*i-2.0*a,3.0-0.4*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
					case 2:
						if(c%10==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<3;i++){
								for(int a=0;a<5;a++){
									SEs_Make(x,y,+2.0*c+120*i+2.0*a,3.5-0.4*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,-2.0*c+120*i-2.0*a,3.5-0.4*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
					case 3:
						if(c%8==0){
							SPlaySound(10);
							float x = Boss.x - 22;
							float y = Boss.y - 13;
							for(int i=0;i<3;i++){
								for(int a=0;a<8;a++){
									SEs_Make(x,y,+2.0*c+120*i+2.0*a,5.0-0.4*a,gra_e_shot[19],10,0.0,0,0,0);
									SEs_Make(x,y,-2.0*c+120*i-2.0*a,5.0-0.4*a,gra_e_shot[18],10,0.0,0,0,0);
								}
							}
						}
						break;
				}
			}
		}
	}
	else if(p==25){//６面紫通常１
		if(c>=60){
			switch(SAVE.Level){
				case 1:
					if(c%20==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,20.0,18,3.0-1.0*i,gra_e_shot[48],10,9.0);				
						}
						for(int i=0;i<1;i++){
							SEs_NWay(Boss.x,Boss.y,24.0,15,1.5-0.5*i,gra_e_shot[50],10,get_rand(23));				
						}
					}
					break;
				case 2:
					if(c%20==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.0-1.0*i,gra_e_shot[48],10,9.0);				
						}
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,24.0,15,1.5-0.5*i,gra_e_shot[50],10,get_rand(23));				
						}
					}
					break;
				case 3:
					if(c%16==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.0-1.0*i,gra_e_shot[48],10,9.0);				
						}
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,1.5-0.5*i,gra_e_shot[50],10,get_rand(17));				
						}
					}
					break;
			}
		}
	}
	else if(p==26){//６面紫通常２
		if(c==120){
			for(int i=0;i<2;i++){
				SEn_Make(Boss.x,Boss.y,8,360+180*i,25,39,2);					
			}
		}
		if(c>=170){
			switch(SAVE.Level){
				case 3:
					if(c%60==0){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,18.0,20,3.5-1.0*i,gra_e_shot[4],20,9.0,0.0,0,0,i%2);						
						}
					}
					break;
			}
		}
	}
	else if(p==27){//６面紫通常３
		if(c==120){
			for(int i=0;i<2;i++){
				SEn_Make(Boss.x,Boss.y,8,1+i,23,40,2);					
			}
		}
		if(c==240){
			for(int i=0;i<2;i++){
				SEn_Make(Boss.x,Boss.y,8,3+i,23,40,2);					
			}
		}
	}
	else if(p==28){//６面紫通常４
		if(c>=170){
			switch(SAVE.Level){
				case 1:
					if(c%8==0){
						SPlaySound(10);
						for(int i=0;i<6;i++){
							SEs_Make(Boss.x,Boss.y,7.5*c/8+60.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-7.5*c/8+60.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					if(c>=120){
						if(c==120)	SPlaySound(11);
						if((c-120)%120==0)	SEs_NWay(Boss.x,Boss.y,0.0,1,5.0,gra_e_shot[31],30,0.0,0.0,120);
					}
					break;
				case 2:
					if(c%5==0){
						SPlaySound(10);
						for(int i=0;i<6;i++){
							SEs_Make(Boss.x,Boss.y,7.5*c/5+60.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-7.5*c/5+60.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					if(c>=120){
						if(c==120)	SPlaySound(11);
						if((c-120)%120==0)	SEs_NWay(Boss.x,Boss.y,0.0,1,5.0,gra_e_shot[31],30,0.0,0.0,120);
					}
					break;
				case 3:
					if(c%5==0){
						SPlaySound(10);
						for(int i=0;i<8;i++){
							SEs_Make(Boss.x,Boss.y,7.5*c/5+45.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
							SEs_Make(Boss.x,Boss.y,-7.5*c/5+45.0*i,1.5,gra_e_shot[23],20,0.0,0,0,0);
						}
					}
					if(c>=120){
						if(c==120)	SPlaySound(11);
						if((c-120)%90==0)	SEs_NWay(Boss.x,Boss.y,0.0,1,5.0,gra_e_shot[31],30,0.0,0.0,120);
					}
					break;
			}
		}
	}
	else if(p==29){//Ex中ボス通常１
		if(c>=60){
			c -= 60;
			int cp = c%340;
			if(cp<60&&cp%3==1){
				if(cp==1){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
				}
				float x = Player.x;
				float y = Player.y;
				Player.x = Boss.d_hanyou[0];
				Player.y = Boss.d_hanyou[1];
				SPlaySound(10);
				int num = cp/3+1;
				for(int i=0;i<4;i++){
					SEs_NWay(Boss.x,Boss.y,10.0,num,6.0,gra_e_shot[18],5,90.0*i);
				}
				Player.x = x;
				Player.y = y;
			}
			else if(cp==60){
				int move_x = 40+get_rand(50);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
			else if(cp<110){}
			else if(cp<170&&(cp-110)%3==0){
				if(cp==110){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
				}
				float x = Player.x;
				float y = Player.y;
				Player.x = Boss.d_hanyou[0];
				Player.y = Boss.d_hanyou[1];
				SPlaySound(10);
				float speed = 2.0+0.15*(cp-110);
				for(int i=0;i<10;i++){
					float angle = 5.0*(170-cp)+15.0*cos(Radian(i*10,TRUE))-3.0;
					SEs_NWay(Boss.x,Boss.y,angle,2,speed/3.0+0.5*i,gra_e_shot[19],5,0.0);
				}
				SEs_NWay(Boss.x,Boss.y,0.0,1,speed,gra_e_shot[19],5,0.0);
				Player.x = x;
				Player.y = y;
			}
			else if(cp==170){
				int move_x = 40+get_rand(50);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
			else if(cp<230){}
			else if(cp<290&&(cp-230)%3==0){
				if(cp==230){
					Boss.d_hanyou[0] = Player.x;
					Boss.d_hanyou[1] = Player.y;
				}
				float x = Player.x;
				float y = Player.y;
				Player.x = Boss.d_hanyou[0];
				Player.y = Boss.d_hanyou[1];
				SPlaySound(10);
				float speed = 2.0+0.15*(cp-230);
				for(int i=0;i<10;i++){
					float angle = 5.0*(290-cp)+15.0*cos(Radian(i*10,TRUE))-3.0;
					SEs_NWay(Boss.x,Boss.y,angle,2,speed/3.0+0.5*i,gra_e_shot[19],5,0.0);
				}
				SEs_NWay(Boss.x,Boss.y,0.0,1,speed,gra_e_shot[19],5,0.0);
				Player.x = x;
				Player.y = y;
			}
			else if(cp==290){
				SBos_MoveTo(CENTER_X,150,50);
			}
			c += 60;
		}
	}
	else if(p==30){//Ex中ボス通常２
		if(c>=160){
			c -= 160;
			int cp = c%740;
			if(cp==1){
				SPlaySound(10);
				SEs_Make(Boss.x,Boss.y,-30.0,7.0,gra_e_shot[32],20,0.0,180,52,0);
				SEs_Make(Boss.x,Boss.y,-150.0,7.0,gra_e_shot[32],20,0.0,180,52,1);
				for(int i=0;i<0;i++){
					SEs_NWay(Boss.x,Boss.y,18.0,20,1.0+0.5*i,gra_e_shot[27],0,9.0);
				}
			}
			else if(cp==180){
				SPlaySound(10);
				SEs_NWay(Boss.x,Boss.y,0.0,1,7.0,gra_e_shot[32],20,0.0,0.0,180,52);
				for(int i=0;i<0;i++){
					SEs_NWay(Boss.x,Boss.y,18.0,20,1.0+0.5*i,gra_e_shot[27],0,9.0);
				}
			}
			else if(cp==360){
				SPlaySound(10);
				SEs_NWay(Boss.x,Boss.y,180.0,2,7.0,gra_e_shot[32],20,0.0,0.0,180,53);
				for(int i=0;i<0;i++){
					SEs_NWay(Boss.x,Boss.y,18.0,20,1.0+0.5*i,gra_e_shot[27],0,9.0);
				}
			}
			else if(cp==560){
				SPlaySound(10);
				for(int i=0;i<4;i++){
					SEs_Make(Boss.x,Boss.y,45.0+90.0*i,7.0,gra_e_shot[32],20,0.0,180,52,0);
				}
				for(int i=0;i<0;i++){
					SEs_NWay(Boss.x,Boss.y,18.0,20,1.0+0.5*i,gra_e_shot[27],0,9.0);
				}
			}

			if(cp==500){
				SBos_MoveTo(CENTER_X,Boss.y+30,50);
			}
			c += 160;
		}
	}
	else if(p==31){//Exエーキ通常１
		if(c>=60){
			if(c%5==0){
				SPlaySound(10);
				float d;
				if(c<160)	d = c-60;
				else		d = 100;
				float angle = Radian(2.7*c+120*(c%15/5),TRUE);
				int rand = get_rand(35);
				for(int i=0;i<10;i++){
					SEs_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),rand+36.0*i,2.0,gra_e_shot[15],10,0.0,0,0,i);
				}
			}
		}
	}
	else if(p==32){//Exエーキ通常２
		if(c>=160){
			if(c%4==0){
				SPlaySound(10);
				float d;
				if(c<140)	d = c-60;
				else		d = 80;
				float angle = Radian(2.7*c+90*(c%16/4),TRUE);
				int rand = get_rand(71);
				for(int i=0;i<5;i++){
					SEs_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),rand+72.0*i,1.5+0.1*get_rand(15),gra_e_shot[39],10,0.0,0,0,i);
				}
			}
		}
	}
	else if(p==33){//Exエーキ通常３
		if(c>=160){
			if(c%4==0){
				SPlaySound(10);
				float d;
				if(c<140)	d = c-60;
				else		d = 80;
				float angle = Radian(2.7*c+90*(c%16/4),TRUE);
				int rand = get_rand(71);
				SEs_NWay(Boss.x+d*cos(angle),Boss.y+d*sin(angle),90.0,4,2.0,gra_e_shot[27],10,get_rand(89));
			}
		}
	}
	else if(p==34){//Exエーキ通常４
		if(c>=160){
			c-=160;
			if(c%150==0&&Boss.i_hanyou[0]>8){
				Boss.i_hanyou[0] -= 4;
			}
			if(c==0)			Boss.i_hanyou[0] = 20;
			if(c%Boss.i_hanyou[0]==0){
				SPlaySound(11);
				float x = CENTER_X - 180 + get_rand(360);
				float y = CENTER_Y - 60 + get_rand(80);
				SEs_NWay(x,y,40.0,9,6.0,gra_e_shot[31+get_rand(1)],10,get_rand(1)*20.0,0.0,90);
			}
		}
	}
	return;
}

void SBos_Item(){
	int p = Boss.item_pattern;
	
	if(p==0){//スイカ　赤4　青4　緑5
		for(int i=0;i<4;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<4;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
	}
	if(p==1){//文　赤6　青5　緑5
		for(int i=0;i<6;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
	}
	if(p==2){//紫　赤7　青6　緑5
		for(int i=0;i<7;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<6;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
	}
	if(p==3){//３面スイカ　赤7　赤大1　青6　緑5
		for(int i=0;i<7;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<6;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
		SIt_Make(Boss.x,Boss.y,270,gra_item[2]);
	}
	if(p==4){//３面文　赤7　青6　緑5　1up1
		for(int i=0;i<7;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<6;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
		SIt_Make(Boss.x,Boss.y,270,gra_item[5]);
	}
	if(p==5){//４面スイカ　赤8　青6　緑10
		for(int i=0;i<8;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<6;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
	}
	if(p==6){//５面文　赤10　青8　緑10
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<8;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
	}
	if(p==7){//６面スイカ　赤10　赤大1　青10　緑10
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
		SIt_Make(Boss.x,Boss.y,270,gra_item[2]);
	}
	if(p==8){//６面文　赤10　1up1　青12　緑10
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<12;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
		SIt_Make(Boss.x,Boss.y,270,gra_item[5]);
	}
	if(p==9){//６面紫　赤12　青14　緑10
		for(int i=0;i<12;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<14;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<10;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
	}
	if(p==10){//ラスト　赤60　青20　緑20
		for(int i=0;i<60;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = get_rand(100);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[0]);
		}
		for(int i=0;i<20;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = get_rand(100);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[1]);
		}
		for(int i=0;i<20;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = get_rand(100);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[3]);
		}
	}
	if(p==11){//Ex映姫　赤18　青18　緑18
		for(int i=0;i<18;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = get_rand(100);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[0]);
		}
		for(int i=0;i<18;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = get_rand(100);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[1]);
		}
		for(int i=0;i<18;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = get_rand(100);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[3]);
		}
	}
	if(p==12){//Ex映姫(1up)　赤18　青18　緑18　1up1
		for(int i=0;i<18;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = 50+get_rand(50);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[0]);
		}
		for(int i=0;i<18;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = 50+get_rand(50);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[1]);
		}
		for(int i=0;i<18;i++){
			float angle = Radian(get_rand(359),TRUE);
			float d = 50+get_rand(50);
			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[3]);
		}
		SIt_Make(Boss.x,Boss.y,270,gra_item[5]);
	}
	if(p==13){//文1up　赤6　青5　緑5 1up1
		for(int i=0;i<6;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
		}
		for(int i=0;i<5;i++){
			SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[3]);
		}
		SIt_Make(Boss.x,Boss.y,270,gra_item[5]);
	}
	
	return;
}

void SSp_Load(){
	for(int i=0;i<SPELL_NUM;i++){
		int count;
		int life;
		int level;
		int defence;
		switch(i){
			case 0:	wsprintf(Spell[i].name , "力業「戸隠山投げ -Easy-」");
				level = 0;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 1:	wsprintf(Spell[i].name , "力業「戸隠山投げ」");
				level = 1;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 2:	wsprintf(Spell[i].name , "薈萃「自重の密」");
				level = 2;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 3:	wsprintf(Spell[i].name , "薈萃「ギャザーグラビテーション」");
				level = 3;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 4:	wsprintf(Spell[i].name , "魑魅「デモンズパンデモニウム -Easy-」");
				level = 0;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 5:	wsprintf(Spell[i].name , "魑魅「デモンズパンデモニウム」");
				level = 1;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 6:	wsprintf(Spell[i].name , "魍魎「百万鬼夜行」");
				level = 2;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 7:	wsprintf(Spell[i].name , "萃夢「百万鬼夜行」");
				level = 3;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 8:	wsprintf(Spell[i].name , "「ミッシングパワー -Easy-」");
				level = 0;
				count = 57;
				defence = 60;
				life = 10000;	break;
			case 9:	wsprintf(Spell[i].name , "「ミッシングパワー」");
				level = 1;
				count = 57;
				defence = 60;
				life = 10000;	break;
			case 10:wsprintf(Spell[i].name , "「ミッシングパープルパワー」");
				level = 2;
				count = 57;
				defence = 60;
				life = 10000;	break;
			case 11:wsprintf(Spell[i].name , "「失われし太古の力」");
				level = 3;
				count = 57;
				defence = 60;
				life = 10000;	break;
			case 12:wsprintf(Spell[i].name , "迅雷「疾風の箭 -Easy-」");
				level = 0;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 13:wsprintf(Spell[i].name , "迅雷「疾風の箭」");
				level = 1;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 14:wsprintf(Spell[i].name , "疾風迅雷「陣風乱れ吹き」");
				level = 2;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 15:wsprintf(Spell[i].name , "疾風迅雷「風神乱れ撃ち」");
				level = 3;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 16:wsprintf(Spell[i].name , "風符「風神木の葉隠れ -Easy-」");
				level = 0;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 17:wsprintf(Spell[i].name , "風符「風神木の葉隠れ」");
				level = 1;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 18:wsprintf(Spell[i].name , "風符「キラーリーフ」");
				level = 2;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 19:wsprintf(Spell[i].name , "風符「竜巻旋風ハリケーン」");
				level = 3;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 20:wsprintf(Spell[i].name , "写符「射命丸フラッシュ -Easy-」");
				level = 0;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 21:wsprintf(Spell[i].name , "写符「射命丸フラッシュ」");
				level = 1;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 22:wsprintf(Spell[i].name , "写符「心傷フラッシュバック」");
				level = 2;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 23:wsprintf(Spell[i].name , "大惨事「業火フラッシュオーバー」");
				level = 3;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 24:wsprintf(Spell[i].name , "塞符「山神渡御 -Easy-」");
				level = 0;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 25:wsprintf(Spell[i].name , "塞符「山神渡御」");
				level = 1;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 26:wsprintf(Spell[i].name , "塞符「天孫降臨」");
				level = 2;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 27:wsprintf(Spell[i].name , "塞符「天上天下の照國」");
				level = 3;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 28:wsprintf(Spell[i].name , "鬼符「スローフジヤマ -Easy-」");
				level = 0;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 29:wsprintf(Spell[i].name , "鬼符「スローフジヤマ」");
				level = 1;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 30:wsprintf(Spell[i].name , "鬼符「芙蓉霊峰大噴火」");
				level = 2;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 31:wsprintf(Spell[i].name , "鬼符「八神峰の関門」");
				level = 3;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 32:wsprintf(Spell[i].name , "天符「仙境異聞 -Easy-」");
				level = 0;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 33:wsprintf(Spell[i].name , "天符「仙境異聞」");
				level = 1;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 34:wsprintf(Spell[i].name , "天符「篤胤伝説」");
				level = 2;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 35:wsprintf(Spell[i].name , "天符「天狗隠しの怪」");
				level = 3;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 36:wsprintf(Spell[i].name , "結界「夢と現の呪 -Easy-」");
				level = 0;
				count = 59;
				defence = 40;
				life = 8000;	break;
			case 37:wsprintf(Spell[i].name , "結界「夢と現の呪」");
				level = 1;
				count = 59;
				defence = 40;
				life = 8000;	break;
			case 38:wsprintf(Spell[i].name , "結界「呪われし世界」");
				level = 2;
				count = 59;
				defence = 50;
				life = 8000;	break;
			case 39:wsprintf(Spell[i].name , "結界「カーストファンタズム」");
				level = 3;
				count = 59;
				defence = 60;
				life = 8000;	break;
			case 40:wsprintf(Spell[i].name , "結界「動と静の均衡 -Easy-」");
				level = 0;
				count = 59;
				defence = 50;
				life = 8000;	break;
			case 41:wsprintf(Spell[i].name , "結界「動と静の均衡」");
				level = 1;
				count = 59;
				defence = 50;
				life = 8000;	break;
			case 42:wsprintf(Spell[i].name , "結界「知る者語らず、知らぬ者語る」");
				level = 2;
				count = 59;
				defence = 50;
				life = 8000;	break;
			case 43:wsprintf(Spell[i].name , "結界「ムーブド・アンムーブド」");
				level = 3;
				count = 59;
				defence = 50;
				life = 8000;	break;
			case 44:wsprintf(Spell[i].name , "戯符「暇を持て余した神々の遊び -Easy-」");
				level = 0;
				count = 89;
				defence = 60;
				life = 15000;	break;
			case 45:wsprintf(Spell[i].name , "戯符「暇を持て余した神々の遊び」");
				level = 1;
				count = 89;
				defence = 60;
				life = 15000;	break;
			case 46:wsprintf(Spell[i].name , "戯符「隙間妖怪エンジン」");
				level = 2;
				count = 89;
				defence = 60;
				life = 15000;	break;
			case 47:wsprintf(Spell[i].name , "戯符「神々のアジャラ空間」");
				level = 3;
				count = 89;
				defence = 60;
				life = 15000;	break;
			case 48:wsprintf(Spell[i].name , "魍魎「二重黒死蝶 -Easy-」");
				level = 0;
				count = 59;
				defence = 60;
				life = 10000;	break;
			case 49:wsprintf(Spell[i].name , "魍魎「二重黒死蝶」");
				level = 1;
				count = 59;
				defence = 60;
				life = 10000;	break;
			case 50:wsprintf(Spell[i].name , "魅了「幻想黒死蝶」");
				level = 2;
				count = 59;
				defence = 60;
				life = 10000;	break;
			case 51:wsprintf(Spell[i].name , "魅了「幻想誘死蝶」");
				level = 3;
				count = 59;
				defence = 60;
				life = 10000;	break;
			case 52:wsprintf(Spell[i].name , "境符「生と死の境界 -輪廻-」");
				level = 0;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 53:wsprintf(Spell[i].name , "境符「生と死の境界 -亡我-」");
				level = 1;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 54:wsprintf(Spell[i].name , "境符「生と死の境界 -忘却-」");
				level = 2;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 55:wsprintf(Spell[i].name , "境符「生と死の境界 -六道-」");
				level = 3;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 56:wsprintf(Spell[i].name , "薈萃「大江山投げ」");
				level = 1;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 57:wsprintf(Spell[i].name , "薈萃「ニュートンの万有斥力」");
				level = 2;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 58:wsprintf(Spell[i].name , "薈萃「人工特異点」");
				level = 3;
				count = 40;
				defence = 60;
				life = 10000;	break;
			case 59:wsprintf(Spell[i].name , "魑魅「百万鬼夜行」");
				level = 1;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 60:wsprintf(Spell[i].name , "萃夢「ライブリーパンデモニウム」");
				level = 2;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 61:wsprintf(Spell[i].name , "萃夢「ミッシングデモン」");
				level = 3;
				count = 51;
				defence = 60;
				life = 10000;	break;
			case 62:wsprintf(Spell[i].name , "「ミッシングパープルパワー」");
				level = 1;
				count = 67;
				defence = 60;
				life = 10000;	break;
			case 63:wsprintf(Spell[i].name , "「失われし太古の力」");
				level = 2;
				count = 67;
				defence = 60;
				life = 10000;	break;
			case 64:wsprintf(Spell[i].name , "「ミッシングファイナルパワー」");
				level = 3;
				count = 67;
				defence = 60;
				life = 10000;	break;
			case 65:wsprintf(Spell[i].name , "疾風迅雷「木の葉塵旋風」");
				level = 1;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 66:wsprintf(Spell[i].name , "疾風迅雷「ダウンバースト」");
				level = 2;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 67:wsprintf(Spell[i].name , "疾風迅雷「ソニックブーム」");
				level = 3;
				count = 21;
				defence = 50;
				life = 8500;	break;
			case 68:wsprintf(Spell[i].name , "風符「キラーリーフ」");
				level = 1;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 69:wsprintf(Spell[i].name , "風符「竜巻旋風ハリケーン」");
				level = 2;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 70:wsprintf(Spell[i].name , "風符「サイクロンウェーブ」");
				level = 3;
				count = 51;
				defence = 50;
				life = 10000;	break;
			case 71:wsprintf(Spell[i].name , "「幻想風靡」");
				level = 1;
				count = 15;
				defence = 100;
				life = 5000;	break;
			case 72:wsprintf(Spell[i].name , "「無双風神」");
				level = 2;
				count = 15;
				defence = 100;
				life = 5000;	break;
			case 73:wsprintf(Spell[i].name , "「夢想風神」");
				level = 3;
				count = 15;
				defence = 100;
				life = 5000;	break;
			case 74:wsprintf(Spell[i].name , "天狗秘儀「ヘリオグラフィ」");
				level = 1;
				count = 81;
				defence = 50;
				life = 15000;	break;
			case 75:wsprintf(Spell[i].name , "天狗秘儀「シュート・ザ・クリミナル」");
				level = 2;
				count = 81;
				defence = 50;
				life = 15000;	break;
			case 76:wsprintf(Spell[i].name , "天狗秘儀「マクロフォーカス」");
				level = 3;
				count = 81;
				defence = 50;
				life = 15000;	break;
			case 77:wsprintf(Spell[i].name , "鬼符「芙蓉霊峰大噴火」");
				level = 1;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 78:wsprintf(Spell[i].name , "鬼符「八神峰の関門」");
				level = 2;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 79:wsprintf(Spell[i].name , "鬼符「芙蓉鬼山岳波」");
				level = 3;
				count = 16;
				defence = 50;
				life = 5000;	break;
			case 80:wsprintf(Spell[i].name , "天符「篤胤伝説」");
				level = 1;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 81:wsprintf(Spell[i].name , "天符「天狗隠しの怪」");
				level = 2;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 82:wsprintf(Spell[i].name , "天符「文政の天狗少女」");
				level = 3;
				count = 26;
				defence = 50;
				life = 8000;	break;
			case 83:wsprintf(Spell[i].name , "結界「呪われし世界」");
				level = 1;
				count = 59;
				defence = 60;
				life = 8000;	break;
			case 84:wsprintf(Spell[i].name , "結界「カーストファンタズム」");
				level = 2;
				count = 59;
				defence = 60;
				life = 8000;	break;
			case 85:wsprintf(Spell[i].name , "結界「カーストスペクター」");
				level = 3;
				count = 59;
				defence = 60;
				life = 8000;	break;
			case 86:wsprintf(Spell[i].name , "結界「光と闇の網目」");
				level = 1;
				count = 79;
				defence = 50;
				life = 9000;	break;
			case 87:wsprintf(Spell[i].name , "結界「岡目八目の閃光」");
				level = 2;
				count = 79;
				defence = 50;
				life = 9000;	break;
			case 88:wsprintf(Spell[i].name , "結界「二重光陰結界」");
				level = 3;
				count = 79;
				defence = 50;
				life = 9000;	break;
			case 89:wsprintf(Spell[i].name , "戯符「隙間妖怪エンジン」");
				level = 1;
				count = 99;
				defence = 60;
				life = 12000;	break;
			case 90:wsprintf(Spell[i].name , "戯符「神々のアジャラ空間」");
				level = 2;
				count = 99;
				defence = 60;
				life = 12000;	break;
			case 91:wsprintf(Spell[i].name , "戯符「メンフェンティス降臨」");
				level = 3;
				count = 99;
				defence = 60;
				life = 12000;	break;
			case 92:wsprintf(Spell[i].name , "魅了「幻想黒死蝶」");
				level = 1;
				count = 79;
				defence = 60;
				life = 13000;	break;
			case 93:wsprintf(Spell[i].name , "魅了「幻想誘死蝶」");
				level = 2;
				count = 79;
				defence = 60;
				life = 13000;	break;
			case 94:wsprintf(Spell[i].name , "魅惑「妖艶黒死蝶」");
				level = 3;
				count = 79;
				defence = 60;
				life = 13000;	break;
			case 95:wsprintf(Spell[i].name , "禁忌「弾幕結界」");
				level = 1;
				count = 64;
				defence = 100;
				life = 10000;	break;
			case 96:wsprintf(Spell[i].name , "禁忌「深弾幕結界 -夢幻包影-」");
				level = 2;
				count = 64;
				defence = 100;
				life = 10000;	break;
			case 97:wsprintf(Spell[i].name , "禁忌「真弾幕結界 -久遠素懐-」");
				level = 3;
				count = 64;
				defence = 100;
				life = 10000;	break;
			case 98:wsprintf(Spell[i].name , "境符「八雲式大結界」");
				level = 1;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 99:wsprintf(Spell[i].name , "境符「博麗大結界」");
				level = 2;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 100:wsprintf(Spell[i].name , "境符「幻想大結界」");
				level = 3;
				count = 150;
				defence = 60;
				life = 25000;	break;
			case 101:wsprintf(Spell[i].name , "「夢と現の境界」");
				level = 1;
				count = 84;
				defence = 100;
				life = 5040;	break;
			case 102:wsprintf(Spell[i].name , "「世界変革の時」");
				level = 2;
				count = 84;
				defence = 100;
				life = 5040;	break;
			case 103:wsprintf(Spell[i].name , "「終焉と幻想の境界」");
				level = 3;
				count = 84;
				defence = 100;
				life = 5040;	break;
			case 104:wsprintf(Spell[i].name , "審判「ギルティ・オワ・ノットギルティ」"); 
				level = 4;
				count = 58;
				defence = 60;
				life = 10000;	break;
			case 105:wsprintf(Spell[i].name , "夢幻「月のいはかさの呪い」"); 
				level = 4;
				count = 58;
				defence = 60;
				life = 10000;	break;
			case 106:wsprintf(Spell[i].name , "幻影「十王裁判」"); 
				level = 4;
				count = 60;
				defence = 60;
				life = 10000;	break;
			case 107:wsprintf(Spell[i].name , "夢幻「レーヴァテイン」");
				level = 4;
				count = 54;
				defence = 50;
				life = 10000;	break;
			case 108:wsprintf(Spell[i].name , "濡衣「フォルス・アキュゼイション」"); 
				level = 4;
				count = 58;
				defence = 60;
				life = 10000;	break;
			case 109:wsprintf(Spell[i].name , "夢幻「蛙は口ゆえ蛇に呑まるる」");
				level = 4;
				count = 61;
				defence = 70;
				life = 10000;	break;
			case 110:wsprintf(Spell[i].name , "鬼人「小野篁の呪い」"); 
				level = 4;
				count = 60;
				defence = 70;
				life = 10000;	break;
			case 111:wsprintf(Spell[i].name , "夢幻「ストレートとカーブの夢郷」");
				level = 4;
				count = 71;
				defence = 70;
				life = 14000;	break;
			case 112:wsprintf(Spell[i].name , "神判「トゥルダクの盟神探湯」"); 
				level = 4;
				count = 95;
				defence = 100;
				life = 10000;	break;
			case 113:wsprintf(Spell[i].name , "夢終「エンドオブジャッジメント」"); 
				level = 4;
				count = 120;
				defence = 60;
				life = 30000;	break;
			case 124:wsprintf(Spell[i].name , "境符「アンリミテッドペナンス」");
				level = 3;
				count = 255;
				defence = 0;
				life = 100000;	break;
		}
		Spell[i].count = count;
		Spell[i].life = life;
		Spell[i].Level = level;
		Spell[i].defence = defence;
	}
	return;
}

void SSp_Move(){
	int p = Boss.spell_num;
	int c = Boss.count;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
	
	if(Boss.gage_exist==1){
		if(p<=3){
			if(c==0)	SBos_MoveTo(CENTER_X,150,50);
			if(Boss.count<70)	c = 0;
			else			c -= 70;
			int cp = c%200;
			if(cp==170){
				int move_x = 50+get_rand(30);
				int move_y = 140+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
		}
		else if(p<=7){
			if(c==0)	SBos_MoveTo(CENTER_X,150,50);
			if(c%240==0&&c!=0){
				int move_x = 50+get_rand(30);
				int move_y = 120+get_rand(50);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
		}
		else if(p<=11){
			if(c==0)	SBos_MoveTo(CENTER_X,80,50);
			if(Boss.count<70)	c = 0;
			else			c -= 70;
			if(c>=30&&c<35)		Boss.img_num = 5;
			else if(c>=35&&c<40)	Boss.img_num = 13;
			else if(c>=40&&c<100){
				if(c==40)	SPlaySound(19);
				Boss.img_num = 21;
				Boss.img_count = 0;
				Boss.large += 0.017;
			}
			if(c>=100){
				if(Boss.i_hanyou[0]==0){
					Boss.i_hanyou[0] = 1;
					Boss.d_hanyou[5] += 0.1;
					SPlaySound(19);
					if(Boss.x<CENTER_X){
						Boss.d_hanyou[0] = 1;
						Boss.d_hanyou[1] = 0.02;
						Boss.d_hanyou[2] = 0;
					}
					else{
						Boss.d_hanyou[0] = -1;
						Boss.d_hanyou[1] = 0.02;
						Boss.d_hanyou[2] = 0;
					}
					/*
						float sx = Player.x - Boss.x;
						float sy = Player.y - Boss.y;
						float sq = sqrt(sx*sx+sy*sy);
						Boss.d_hanyou[0] = sx/sq;
						Boss.d_hanyou[1] = sy/sq;
						Boss.d_hanyou[2] = 0;
					*/
				}
				else{
					Boss.move_count[0] = 10;
					Boss.move_count[1] = 20;
					Boss.move_x = Boss.d_hanyou[0]*Boss.d_hanyou[2];
					Boss.move_y = Boss.d_hanyou[1]*Boss.d_hanyou[2];
					if(SAVE.Level<2){
						if(Boss.d_hanyou[2]<1.5)	Boss.d_hanyou[2] += 0.1;
					}
					else if(SAVE.Level==2){
						if(Boss.d_hanyou[2]<2.5)	Boss.d_hanyou[2] += 0.1;
					}
					else{
						if(Boss.d_hanyou[2]<2.5+Boss.d_hanyou[5])	Boss.d_hanyou[2] += 0.1;
					}
					if(Boss.x<16 || Boss.x>404 || Boss.y<11 || Boss.y>464){
						SPlaySound(13);
						Game.shake_count = 15;
						Boss.i_hanyou[0] = 2;
						if(Boss.x<16)	Boss.x = 16;
						if(Boss.x>404)	Boss.x = 404;
						if(Boss.y<11)	Boss.y = 11;
						if(Boss.y>464)	Boss.y = 464;
						Boss.move_x = 0;
						Boss.move_y = 0;
					}
				}
			}
		}
		else if(p<=15){
			if(c==0)	SBos_MoveTo(CENTER_X,150,30);
			if(c==40)	Boss.b_zanzou = false;
		}
		else if(p<=19){
			if(c==0){
				SBos_MoveTo(CENTER_X+22,170,30);
				Boss.defence = 95;
			}
			if(c==40)	Boss.b_zanzou = false;
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=23){
			if(c==0){
				SBos_MoveTo(CENTER_X,170,30);
				Boss.defence = 95;
			}
			if(c==40)	Boss.b_zanzou = false;
			if(c==120)	Boss.defence = Spell[p].defence;
			if(c>90&&(c-90)%240==180){
				int move_x = 50+get_rand(30);
				int move_y = 100+get_rand(50);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);		
			}
		}
		else if(p<=27){
			if(c==0){
				SBos_MoveTo(CENTER_X+22,170,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=31){
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=35){
			if(c==0){
				SBos_MoveTo(CENTER_X+22,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=39){
			if(c==0){
				SBos_MoveTo(CENTER_X,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=43){
			if(c==0){
				SBos_MoveTo(CENTER_X,120,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=47){
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=51){
			if(c==0){
				SBos_MoveTo(CENTER_X,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=55){
			Boss.i_hanyou[6] = 1;
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
			if(c>300&&(c-300)%300==180){
				int move_x = 30+get_rand(30);
				int move_y = 100+get_rand(50);
				bool flag = true;
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0]+50){
						move_x = Boss.x;
						move_y = Boss.y;
						flag = false;
					}
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1]-50){
						move_x = Boss.x;
						move_y = Boss.y;
						flag = false;
					}
					else				move_x = Boss.x + move_x;
				}
				if(flag==true)	SBos_MoveTo(move_x,move_y,50);		
			}
		}
		else if(p<=58){
			if(c==0){
				SBos_MoveTo(CENTER_X,150,50);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
			if(Boss.count<70)	c = 0;
			else			c -= 70;
			int cp = c%200;
			if(cp==170){
				int move_x = 50+get_rand(30);
				int move_y = 140+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
		}
		else if(p<=61){
			if(c==0){
				SBos_MoveTo(CENTER_X,150,50);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
			if(c%240==0&&c!=0){
				int move_x = 50+get_rand(30);
				int move_y = 120+get_rand(50);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);
			}
		}
		else if(p<=64){
			if(c==0){
				SBos_MoveTo(CENTER_X,80,50);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
			if(Boss.count<70)	c = 0;
			else			c -= 70;
			if(c>=30&&c<35)		Boss.img_num = 5;
			else if(c>=35&&c<40)	Boss.img_num = 13;
			else if(c>=40&&c<100){
				if(c==40)	SPlaySound(19);
				Boss.img_num = 21;
				Boss.img_count = 0;
				Boss.large += 0.017;
			}
			if(c>=100){
				if(Boss.i_hanyou[0]==0){
					Boss.i_hanyou[0] = 1;
					Boss.d_hanyou[5] += 0.1;
					SPlaySound(19);
					float sx = Player.x - Boss.x;
					float sy = Player.y - Boss.y;
					float sq = sqrt(sx*sx+sy*sy);
					Boss.d_hanyou[0] = sx/sq;
					Boss.d_hanyou[1] = sy/sq;
					Boss.d_hanyou[2] = 0;
				}
				else{
					Boss.move_count[0] = 10;
					Boss.move_count[1] = 20;
					Boss.move_x = Boss.d_hanyou[0]*Boss.d_hanyou[2];
					Boss.move_y = Boss.d_hanyou[1]*Boss.d_hanyou[2];
					if(SAVE.Level<2){
						if(Boss.d_hanyou[2]<2.0+Boss.d_hanyou[5])	Boss.d_hanyou[2] += 0.1;
					}
					else if(SAVE.Level==2){
						if(Boss.d_hanyou[2]<2.5+Boss.d_hanyou[5])	Boss.d_hanyou[2] += 0.1;
					}
					else{
						if(Boss.d_hanyou[2]<3.5+Boss.d_hanyou[5])	Boss.d_hanyou[2] += 0.1;
					}
					if(Boss.x<16 || Boss.x>404 || Boss.y<11 || Boss.y>464){
						SPlaySound(13);
						Game.shake_count = 15;
						Boss.i_hanyou[0] = 2;
						if(Boss.x<16)	Boss.x = 16;
						if(Boss.x>404)	Boss.x = 404;
						if(Boss.y<11)	Boss.y = 11;
						if(Boss.y>464)	Boss.y = 464;
						Boss.move_x = 0;
						Boss.move_y = 0;
					}
				}
			}
		}
		else if(p<=67){
			if(c==0)	SBos_MoveTo(CENTER_X,150,30);
			if(c==40)	Boss.b_zanzou = false;
		}
		else if(p<=70){
			if(c==0){
				SBos_MoveTo(CENTER_X+22,170,30);
				Boss.defence = 95;
			}
			if(c==40)	Boss.b_zanzou = false;
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=73){
			if(c==0){
				SBos_MoveTo(-150,50+get_rand(50),40);
			}
		}
		else if(p<=76){
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=79){
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=82){
			if(c==0){
				SBos_MoveTo(CENTER_X+22,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=85){
			if(c==0){
				SBos_MoveTo(CENTER_X,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=88){
			if(c==0){
				SBos_MoveTo(CENTER_X,50,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=91){
			if(c==0){
				SBos_MoveTo(CENTER_X,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=94){
			if(c==0){
				SBos_MoveTo(CENTER_X,180,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p<=97){
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 100;
			}
			if(c==120){
				Boss.flash = 100;
				Boss.b_atari = false;
			}
			else if(c>=120){
				Boss.img_count = 0;
			}
		}
		else if(p<=100){
			if(c==0){
				SBos_MoveTo(CENTER_X,180,30);
				Boss.defence = 95;
			}
			if(c==420)	Boss.defence = Spell[p].defence;
		}
		else if(p<=103){
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 100;
			}
			Boss.life--;
		}
		else if(p==104){
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p==105){//月のいはかさの呪い
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p==106){//幻影「十王裁判」
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
			int cp = c%100;
			if(cp==1&&c!=1){
				int move_x = 30+get_rand(60);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,40);			
			}
		}
		else if(p==107){//レーヴァテイン
			if(c==0){
				SBos_MoveTo(CENTER_X,100,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p==108){//濡衣「フォルス・アキュゼイション」
			if(c==0){
				SBos_MoveTo(CENTER_X,150,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
			int cp = c%90;
			if(cp==1&&c!=1){
				int move_x = 30+get_rand(60);
				int move_y = 120+get_rand(60);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,40);			
			}
		}
		else if(p==109){//蛙は口ゆえ蛇に呑まるる
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p==110){//鬼人「小野篁の呪い」
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p==111){//ストレートとカーブの夢郷
			if(c==0){
				SBos_MoveTo(CENTER_X,50,30);
				Boss.defence = 95;
			}
			if(c==120)	Boss.defence = Spell[p].defence;
		}
		else if(p==112){//神判「トゥルダクの盟神探湯」
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 100;
			}
		}
		else if(p==113){//夢終「エンドオブジャッジメント」
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y,30);
				Boss.defence = 99;
			}
			if(c==60)	Boss.b_atari = true;
		}
		else if(p==124){//境符「アンリミテッドペナンス」
			if(c==0){
				SBos_MoveTo(CENTER_X,CENTER_Y-100,30);
				Boss.defence = 95;
			}
			if(c==30)	Boss.defence = Spell[p].defence;
			if(Boss.move_count[0]==Boss.move_count[1]){
				Boss.d_hanyou[7] += 2.5;
				float speed = 0.5;
				float angle = Radian(Boss.d_hanyou[7],TRUE);
				Boss.x += speed*cos(angle);
				Boss.y += speed*sin(angle);
			}
		}
	}
	int num = (Boss.count/5)%5;
	switch(num){
		case 0:	Boss.img_num = 0;	break;
		case 1:	Boss.img_num = 8;	break;
		case 2:	Boss.img_num = 16;	break;
		case 3:	Boss.img_num = 1;	break;
		case 4:	Boss.img_num = 9;	break;
	}
	Boss.img_count ++;
	if(Boss.move_count[0]<Boss.move_count[1]){
		if(Boss.move_x<=-0.1){
			if(Boss.move_count[0]<5||Boss.move_count[1]-Boss.move_count[0]<5){
				Boss.img_num = 2;
			}
			else{
				Boss.img_num = 10;
			}
		}
		else if(0.1<=Boss.move_x){
			if(Boss.move_count[0]<5||Boss.move_count[1]-Boss.move_count[0]<5){
				Boss.img_num = 18;
			}
			else{
				Boss.img_num = 26;
			}
		}
		Boss.img_count = 0;
		Boss.move_count[0]++;
	}
	else if(Boss.move_count[0]==Boss.move_count[1]){
		Boss.move_x = 0;
		Boss.move_y = 0;
	}
	if(p>=8&&p<=11){
		if(c>=30&&c<35)		Boss.img_num = 5;
		else if(c>=35&&c<40)	Boss.img_num = 13;
		else if(c>=40&&c<100){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
	}
	Boss.x += Boss.move_x;
	Boss.y += Boss.move_y;
	Boss.atari_x[0] = Boss.x - Boss.img_x/16*Boss.large;
	Boss.atari_x[1] = Boss.x + Boss.img_x/16*Boss.large;
	Boss.atari_y[0] = Boss.y - Boss.img_y/12*Boss.large;
	Boss.atari_y[1] = Boss.y + Boss.img_y/12*Boss.large;
	return;
}

void SSp_Shot(){
	if(debug_nobullet==1)	return;
	int p = Boss.spell_num;
	int c = Boss.count;
	if(Boss.count<70)	c = 0;
	else			c -= 70;
	int limit_x[2],limit_y[2];
	limit_x[0] = 70;
	limit_x[1] = 355;
	limit_y[0] = 15;
	limit_y[1] = 460;
	
	/*===========================================
		小弾 　　　0:赤 1:青 2:黄 3:緑
		中弾 　　　4:赤 5:青 6:黄 7:緑 53:水
		中弾その２ 8:赤 9:青 10:黄 11:緑 12:紫 13:灰
		米弾 　　　14:赤 15:青 16:黄 17:緑 52:水
		鱗弾 　　　18:赤 19:青 20:黄 21:緑
		蝶弾 　　　22:赤 23:青 24:黄 25:緑
	　　　（蝶弾薄部分)0:赤 1:青 2:黄 3:緑
		大弾 　　　26:赤 27:青 28:黄 29:緑 30:灰
		特大弾　　 31:赤 32:青 33:黄 34:緑
		刀弾　　　 35:赤 36:青 37:紫
		札弾　　　 38:赤 39:青 40:黄 41:緑 42:紫
		ジェリー弾 43:赤 44:青 45:黄 46:緑
		クナイ弾 　47:赤 48:青 49:黄 50:緑 51:紫
		氷弾　　　 54:赤 55:青 56:黄 57:緑
	　　　（特大弾薄部)4:赤 5:青 6:黄 7:緑
	===========================================*/
	if(p<=3){//力業「戸隠山投げ」
		int cp = c%200;
		if(cp>=0&&cp<20){}
		else if(cp>=20&&cp<25){
			Boss.img_num = 5;
		}
		else if(cp>=25&&cp<30){
			Boss.img_num = 13;
		}
		else if(cp>=30&&cp<110){
			int rand;
			if(cp==30)	SPlaySound(19);
			if(cp%2==0){
				SPlaySound(11);
				for(int i=0;i<3;i++){
					rand = get_rand(359);
					SEs_Make(Boss.x+cp*cos(Radian(rand,TRUE)),Boss.y-60+cp*sin(Radian(rand,TRUE)),rand+180,4.5,gra_e_shot[5],10,5.0,0,3);
				}
				for(int i=0;i<4;i++){
					rand = get_rand(359);
					SEs_Make(Boss.x+cp*cos(Radian(rand,TRUE)),Boss.y-60+cp*sin(Radian(rand,TRUE)),rand+180,4.5,gra_e_shot[28],10,5.0,0,3);
					for(int i=0;i<4;i++){
						rand = get_rand(359);
						SEs_Make(Boss.x+cp*cos(Radian(rand,TRUE)),Boss.y-60+cp*sin(Radian(rand,TRUE)),rand+180,4.5,gra_e_shot[1],10,5.0,0,3);
					}
				}
				if(cp%6==0){
					for(int i=0;i<1;i++){
						rand = get_rand(359);
						SEs_Make(Boss.x+cp*cos(Radian(rand,TRUE)),Boss.y-60+cp*sin(Radian(rand,TRUE)),rand+180,4.5,gra_e_shot[34],10,5.0,0,3);
					}
				}
			}
		}
		else if(cp==130||cp==145||cp==160){
			if(cp==130){
				Boss.d_hanyou[0] = Player.x;
				Boss.d_hanyou[1] = Player.y;
			}
			Boss.d_hanyou[2] = Player.x;
			Boss.d_hanyou[3] = Player.y;
			Player.x = Boss.d_hanyou[0];
			Player.y = Boss.d_hanyou[1];
			SPlaySound(10);
			switch(SAVE.Level){
				case 0:
					for(int i=0;i<2;i++){
						SEs_NWay(Boss.x,Boss.y-60,60.0,5,2.1-0.5*i,gra_e_shot[34],5,180.0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,22.5,15,2.5-0.5*i,gra_e_shot[28],5,180.0,10.0,5);
					}
					for(int i=0;i<1;i++){
						SEs_NWay(Boss.x,Boss.y-60,23.0,2,3.0-0.5*i,gra_e_shot[5],5,0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,20.0,3,3.0-0.3*i,gra_e_shot[1],5,0,10.0,5);
					}
					break;
				case 1:
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,60.0,5,4.1-0.5*i,gra_e_shot[34],5,180.0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,22.5,15,4.5-0.5*i,gra_e_shot[28],5,180.0,10.0,5);
					}
					for(int i=0;i<2;i++){
						SEs_NWay(Boss.x,Boss.y-60,18.0,4,3.5-0.6*i,gra_e_shot[5],5,0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,15.0,5,3.5-0.4*i,gra_e_shot[1],5,0,10.0,5);
					}
					break;
				case 2:
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,36.0,9,3.6-0.6*i,gra_e_shot[34],5,180.0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,15.0,23,4.0-0.6*i,gra_e_shot[28],5,180.0,10.0,5);
					}
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,12.0,4,5.0-0.6*i,gra_e_shot[5],5,0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,12.0,5,5.0-0.4*i,gra_e_shot[1],5,0,10.0,5);
					}
					break;
				case 3:
					for(int i=0;i<5;i++){
						SEs_NWay(Boss.x,Boss.y-60,36.0,9,4.6-0.8*i,gra_e_shot[34],5,180.0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,10.0,35,5.0-0.8*i,gra_e_shot[28],5,180.0,10.0,5);
					}
					for(int i=0;i<5;i++){
						SEs_NWay(Boss.x,Boss.y-60,12.0,4,6.0-0.8*i,gra_e_shot[5],5,0,10.0,5);
						SEs_NWay(Boss.x,Boss.y-60,12.0,5,6.0-0.6*i,gra_e_shot[1],5,0,10.0,5);
					}
					break;
			}
			Player.x = Boss.d_hanyou[2];
			Player.y = Boss.d_hanyou[3];
		}
		if(cp>=30&&cp<150){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
	}
	else if(p<=7){//魑魅「デモンズパンデモニウム」
		switch(SAVE.Level){
			case 0:
				if(c%30==1){
					int img = gra_e_shot[14];
					if(c%60==31)	img = gra_e_shot[15];
					SPlaySound(10);
					for(int i=0;i<18;i++){
						SEs_Make(Boss.x,Boss.y,20.0*i,2.0,img,10);
					}
				}
				if(c%40==1){
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/40,1.5,gra_e_shot[26],10);
					}
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/40+180,1.5,gra_e_shot[27],10);
					}
				}
				break;
			case 1:
				if(c%20==1){
					int img = gra_e_shot[14];
					if(c%40==21)	img = gra_e_shot[15];
					SPlaySound(10);
					for(int i=0;i<20;i++){
						SEs_Make(Boss.x,Boss.y,18.0*i+9.0,2.0,img,10);
					}
				}
				if(c%40==1){
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/40,1.5,gra_e_shot[26],10);
					}
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/40+180,1.5,gra_e_shot[27],10);
					}
				}
				if(c%120==1){
					int rand = get_rand(35);
					for(int i=0;i<10;i++){
						SEs_Make(Boss.x,Boss.y,rand+36.0*i,1.0,gra_e_shot[28],10);
					}
				}
				break;
			case 2:
				if(c%15==1){
					int img = gra_e_shot[14];
					if(c%30==16)	img = gra_e_shot[15];
					SPlaySound(10);
					for(int i=0;i<25;i++){
						SEs_Make(Boss.x,Boss.y,14.4*i-3.6,2.0,img,10);
					}
				}
				if(c%25==1){
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/25,1.5,gra_e_shot[26],10);
					}
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/25+180,1.5,gra_e_shot[27],10);
					}
				}
				if(c%80==1){
					int rand = get_rand(17);
					for(int i=0;i<20;i++){
						SEs_Make(Boss.x,Boss.y,rand+18.0*i,1.0,gra_e_shot[28],10);
					}
				}
				break;
			case 3:
				if(c%10==1){
					int img = gra_e_shot[14];
					if(c%20==11)	img = gra_e_shot[15];
					SPlaySound(10);
					for(int i=0;i<30;i++){
						SEs_Make(Boss.x,Boss.y,12.0*i,2.0,img,10);
					}
				}
				if(c%20==1){
					for(int a=0;a<2;a++){
						for(int i=0;i<3;i++){
							SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/20+180*a,1.5,gra_e_shot[26],10);
						}
					}
					for(int a=0;a<2;a++){
						for(int i=0;i<3;i++){
							SEs_Make(Boss.x+5*cos(Radian(120*i,TRUE)),Boss.y+5*sin(Radian(120*i,TRUE)),31*c/20+90+180*a,1.5,gra_e_shot[27],10);
						}
					}
				}
				if(c%60==1){
					int rand = get_rand(14);
					for(int i=0;i<25;i++){
						SEs_Make(Boss.x,Boss.y,rand+14.4*i,1.0,gra_e_shot[28],10);
					}
				}
				break;
		}		
	}
	else if(p<=11){//「ミッシングパワー」
		if(c>=100){
			switch(SAVE.Level){
				case 0:
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand = get_rand(71);
						for(int i=0;i<5;i++){
							SEs_Make(Boss.x,Boss.y,rand+72.0*i,0.5,gra_e_shot[32],0);
						}
						rand = get_rand(17);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.7,gra_e_shot[27],0);
						}
						rand = get_rand(17);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(5),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(5),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,1.0+0.1*get_rand(5),gra_e_shot[1],0);
						}
					}
					break;
				case 1:
					if(c%90==0){
						int rand = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make(Boss.x,Boss.y,rand+36.0*i,0.5,gra_e_shot[10],10);
						}
					}
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make(Boss.x,Boss.y,rand+36.0*i,0.5+0.1*get_rand(5),gra_e_shot[32],0);
						}
						rand = get_rand(17);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(5),gra_e_shot[27],0);
						}
						rand = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(5),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(5),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,1.0+0.1*get_rand(5),gra_e_shot[1],0);
						}
					}
					break;
				case 2:
					if(c%90==0){
						int rand = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make(Boss.x,Boss.y,rand+36.0*i,1.0,gra_e_shot[10],10);
						}
					}
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand = get_rand(17);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(10),gra_e_shot[32],0);
						}
						rand = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(10),gra_e_shot[27],0);
						}
						rand = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(10),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(10),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,1.0+0.1*get_rand(10),gra_e_shot[1],0);
						}
					}
					break;
				case 3:
					if(c%60==0){
						int rand = get_rand(35);
						for(int i=0;i<10;i++){
							SEs_Make(Boss.x,Boss.y,rand+36.0*i,1.0,gra_e_shot[10],10);
						}
					}
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand = get_rand(17);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(15),gra_e_shot[32],0);
						}
						rand = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(15),gra_e_shot[27],0);
						}
						rand = get_rand(15);
						for(int i=0;i<60;i++){
							SEs_Make(Boss.x,Boss.y,rand+6.0*i,0.5+0.1*get_rand(20),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+6.0*i,0.5+0.1*get_rand(20),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+6.0*i,1.0+0.1*get_rand(20),gra_e_shot[1],0);
						}
					}
					break;
			}
		}
	}
	else if(p<=15){//疾風迅雷「風神乱れ撃ち」
		if(c>=1)	Boss.img_count = 0;
		if(c>=1&&c<6)	Boss.img_num = 5;
		else if(c<12)	Boss.img_num = 13;
		else if(c<18)	Boss.img_num = 21;
		else{	
			Boss.img_num = 21;
			int cp;
			switch(SAVE.Level){
				case 0:
					cp = (c-18)%25;
					if(cp==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i,2.5,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i-1,2.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i+1,2.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i-2,2.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i+2,2.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i-3,1.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i+3,1.9,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
				case 1:
					cp = (c-18)%20;
					if(cp==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i,3.5,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i-1,3.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i+1,3.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i-2,3.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i+2,3.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i-3,2.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.0*c+180*i+3,2.9,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
				case 2:
					cp = (c-18)%10;
					if(cp==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i,4.0,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i-1,3.8,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i+1,3.8,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i-2,3.6,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i+2,3.6,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i-3,3.4,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,2.4*c+180*i+3,3.4,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
				case 3:
					cp = (c-18)%7;
					if(cp==0){
						SPlaySound(10);
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i,4.5,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i-1,4.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i+1,4.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i-2,4.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i+2,4.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i-3,3.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,3.5*c+180*i+3,3.9,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
			}
		}
	}
	else if(p<=19){//風符「竜巻旋風ハリケーン」
		int cp;
		switch(SAVE.Level){
			case 0:
				cp = c%280;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=120&&cp<125)Boss.img_num = 13;
				else if(cp>=125&&cp<130)Boss.img_num = 5;
				else if(cp>=130){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%280==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(59);
				}
				if(cp>=20&&cp<100&&cp%6==0){
					SPlaySound(11);
					for(int i=0;i<6;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+60*i,1.5-0.01*(cp-20),gra_e_shot[17],10,4.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+60*i+30,1.5-0.01*(cp-20),gra_e_shot[52],10,4.5,0,15,effect);
					}
				}
				break;
			case 1:
				cp = c%240;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=120&&cp<125)Boss.img_num = 13;
				else if(cp>=125&&cp<130)Boss.img_num = 5;
				else if(cp>=130){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%240==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(59);
				}
				if(cp>=20&&cp<100&&cp%6==0){
					SPlaySound(11);
					for(int i=0;i<6;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+60*i,2.0-0.01*(cp-20),gra_e_shot[17],10,4.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+60*i+30,2.0-0.01*(cp-20),gra_e_shot[52],10,4.5,0,15,effect);
					}
				}
				break;
			case 2:
				cp = c%240;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=160&&cp<165)Boss.img_num = 13;
				else if(cp>=165&&cp<170)Boss.img_num = 5;
				else if(cp>=170){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%240==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(44);
				}
				if(cp>=20&&cp<140&&cp%5==0){
					SPlaySound(11);
					for(int i=0;i<8;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+45*i,2.5-0.01*(cp-20),gra_e_shot[17],10,4.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+45*i+22.5,2.5-0.01*(cp-20),gra_e_shot[52],10,4.5,0,15,effect);
					}
				}
				break;
			case 3:
				cp = c%180;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=120&&cp<125)Boss.img_num = 13;
				else if(cp>=125&&cp<130)Boss.img_num = 5;
				else if(cp>=130){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%180==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(29);
				}
				if(cp>=20&&cp<100&&cp%2==0){
					SPlaySound(11);
					for(int i=0;i<12;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+30*i,4.0-0.018*(cp-20),gra_e_shot[17],10,4.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+30*i+15,4.0-0.018*(cp-20),gra_e_shot[52],10,4.5,0,15,effect);
					}
				}
				break;
		}
	}
	else if(p<=23){//写符「業火フラッシュオーバー」
		if(c>20){
			c-=20;
			switch(SAVE.Level){
				case 0:
					if(c%12==1){
						SPlaySound(10);
						int pattern = 17;
						int graph = gra_e_shot[8];
						float an = 45*(c%96/12);
						if(c%192>=97){
							pattern = 18;
							graph = gra_e_shot[9];
							an = 360-45*(c%96/12);
						}
						for(int i=0;i<4;i++){
							float angle = Radian(90*i,TRUE);
							float angle2 = Radian(90*i+45,TRUE);
							SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),an,3.0,graph,10,Radian(angle,FALSE),0,pattern,0);
							SEs_Make(Boss.x+20*cos(angle2),Boss.y+20*sin(angle2),an,3.0,graph,10,Radian(angle2,FALSE),0,pattern,0);
						}
					}
					break;
				case 1:
					if(c%10==1){
						SPlaySound(10);
						int pattern = 17;
						int graph = gra_e_shot[8];
						float an = 45*(c%80/10);
						if(c%160>=81){
							pattern = 18;
							graph = gra_e_shot[9];
							an = 360-45*(c%80/10);
						}
						for(int i=0;i<4;i++){
							float angle = Radian(90*i,TRUE);
							float angle2 = Radian(90*i+45,TRUE);
							SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),an,3.5,graph,10,Radian(angle,FALSE),0,pattern,0);
							SEs_Make(Boss.x+20*cos(angle2),Boss.y+20*sin(angle2),an,3.5,graph,10,Radian(angle2,FALSE),0,pattern,0);
						}
					}
					break;
				case 2:
					if(c%6==1){
						SPlaySound(10);
						int pattern = 17;
						int graph = gra_e_shot[8];
						float an = 45*(c%48/6);
						if(c%96>=49){
							pattern = 18;
							graph = gra_e_shot[9];
							an = 360-45*(c%48/6);
						}
						for(int i=0;i<4;i++){
							float angle = Radian(90*i,TRUE);
							float angle2 = Radian(90*i+45,TRUE);
							SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),an,3.5,graph,10,Radian(angle,FALSE),0,pattern,0);
							SEs_Make(Boss.x+20*cos(angle2),Boss.y+20*sin(angle2),an,3.5,graph,10,Radian(angle2,FALSE),0,pattern,0);
						}
					}
					break;
				case 3:
					if(c%5==1){
						SPlaySound(10);
						int pattern = 17;
						int graph = gra_e_shot[8];
						float an = 36*(c%50/5);
						if(c%100>=51){
							pattern = 18;
							graph = gra_e_shot[4];
							an = 360-36*(c%50/5);
						}
						for(int i=0;i<4;i++){
							float angle = Radian(90*i,TRUE);
							float angle2 = Radian(90*i+45,TRUE);
							SEs_Make(Boss.x+20*cos(angle),Boss.y+20*sin(angle),an,3.5,graph,10,Radian(angle,FALSE),0,pattern,0);
							SEs_Make(Boss.x+20*cos(angle2),Boss.y+20*sin(angle2),an,3.5,graph,10,Radian(angle2,FALSE),0,pattern,0);
						}
					}
					break;
			}
		}		
	}
	else if(p<=27){//塞符「天上天下の照國」
		if(Boss.count==30)	SPlaySound(19);
		if(c+10>0&&c+10<5)		Boss.img_num = 5;
		else if(c+10>=5&&c+10<10)	Boss.img_num = 13;
		else if(c!=0){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
		switch(SAVE.Level){
			int cp;
			case 0:
				if(c%25==1){
					SPlaySound(10);
					for(int i=0;i<12;i++){
						SEs_Make(Boss.x-22,Boss.y-13,c/25+30*i,2.0,gra_e_shot[15],10,0.0,0,0,i%12);
						SEs_Make(Boss.x-22,Boss.y-13,-15-c/25+30*i,2.0,gra_e_shot[15],10,0.0,0,0,1);
					}
				}
				cp = 120;
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)		cp = 90;
				if(c%cp==1){
					int rand = get_rand(11);
					for(int i=0;i<30;i++){
						SEs_Make(Boss.x-22,Boss.y-13,rand+12.0*i,1.0,gra_e_shot[3],10,0.0,0,0,i%45);
					}
				}
				break;
			case 1:
				if(c%18==1){
					SPlaySound(10);
					for(int i=0;i<16;i++){
						SEs_Make(Boss.x-22,Boss.y-13,c/18+22.5*i,2.5,gra_e_shot[15],10,0.0,0,0,i%16);
						SEs_Make(Boss.x-22,Boss.y-13,-11.25-c/18+22.5*i,2.5,gra_e_shot[15],10,0.0,0,0,1);
					}
				}
				cp = 90;
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)		cp = 60;
				if(c%cp==1){
					int rand = get_rand(8);
					for(int i=0;i<40;i++){
						SEs_Make(Boss.x-22,Boss.y-13,rand+9.0*i,1.0,gra_e_shot[3],10,0.0,0,0,i%50);
					}
				}
				break;
			case 2:
				if(c%15==1){
					SPlaySound(10);
					for(int i=0;i<16;i++){
						SEs_Make(Boss.x-22,Boss.y-13,c/15+22.5*i,2.5,gra_e_shot[15],10,0.0,0,0,i%16);
						SEs_Make(Boss.x-22,Boss.y-13,-11.25-c/15+22.5*i,2.5,gra_e_shot[15],10,0.0,0,0,1);
					}
				}
				cp = 80;
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)		cp = 50;
				if(c%cp==1){
					int rand = get_rand(7);
					for(int i=0;i<50;i++){
						SEs_Make(Boss.x-22,Boss.y-13,rand+7.2*i,1.0,gra_e_shot[3],10,0.0,0,0,i%72);
					}
				}
				break;
			case 3:
				if(c%12==1){
					SPlaySound(10);
					for(int i=0;i<16;i++){
						SEs_Make(Boss.x-22,Boss.y-13,c/12+22.5*i,4.5,gra_e_shot[20],10,0.0,0,0,i%16);
						SEs_Make(Boss.x-22,Boss.y-13,-11.25-c/12+22.5*i,4.5,gra_e_shot[20],10,0.0,0,0,1);
					}
				}
				cp = 60;
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)		cp = 30;
				if(c%cp==1){
					int rand = get_rand(7);
					for(int i=0;i<50;i++){
						SEs_Make(Boss.x-22,Boss.y-13,rand+7.2*i,1.5,gra_e_shot[16],10,0.0,0,0,i%72);
					}
				}
				break;
		}
	}
	else if(p<=31){//鬼符「八神峰の関門」
		if(c>=30){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
		if(c>=0&&c<20){}
		else if(c>=20&&c<25){
			Boss.img_num = 5;
		}
		else if(c>=25&&c<30){
			Boss.img_num = 13;
		}
		else if(c>=30){
			c-=30;
			switch(SAVE.Level){
				int cp;
				case 0:
					cp = c%200;
					if(cp<=30){
						if(cp==0){
							float sx = Player.x - Boss.x;
							float sy = Player.y - (Boss.y-60);
							if(sx==0){
								if(sy>0)	Boss.d_hanyou[0] = 270;
								else		Boss.d_hanyou[0] = 90;
							}
							else{
								Boss.d_hanyou[0] = Radian(atan2(sy,sx),FALSE);
							}
							Boss.d_hanyou[1] = 0.0;
						}
						SPlaySound(10);
						float length = 3*cp;
						float plus = 9*cp;
						for(int i=0;i<20;i++){
							float angle = Radian(18*i+plus,TRUE);
							SEs_Make(Boss.x+length*cos(angle),Boss.y-60+length*sin(angle),Boss.d_hanyou[0],1.5,gra_e_shot[5],20,0.1,0,20);
						}
					}
					else if(cp<50){}
					else if(cp<110){
						Boss.d_hanyou[1] += 0.1;
					}
					break;
				case 1:
					cp = c%180;
					if(cp<=30){
						if(cp==0){
							float sx = Player.x - Boss.x;
							float sy = Player.y - (Boss.y-60);
							if(sx==0){
								if(sy>0)	Boss.d_hanyou[0] = 270;
								else		Boss.d_hanyou[0] = 90;
							}
							else{
								Boss.d_hanyou[0] = Radian(atan2(sy,sx),FALSE);
							}
							Boss.d_hanyou[1] = 0.0;
						}
						SPlaySound(10);
						float length = 3*cp;
						float plus = 9*cp;
						for(int i=0;i<20;i++){
							float angle = Radian(18*i+plus,TRUE);
							SEs_Make(Boss.x+length*cos(angle),Boss.y-60+length*sin(angle),Boss.d_hanyou[0],1.5,gra_e_shot[5],20,0.3,0,20);
						}
					}
					else if(cp<50){}
					else if(cp<110){
						Boss.d_hanyou[1] += 0.1;
					}
					break;
				case 2:
					cp = c%170;
					if(cp<=30){
						if(cp==0){
							float sx = Player.x - Boss.x;
							float sy = Player.y - (Boss.y-60);
							if(sx==0){
								if(sy>0)	Boss.d_hanyou[0] = 270;
								else		Boss.d_hanyou[0] = 90;
							}
							else{
								Boss.d_hanyou[0] = Radian(atan2(sy,sx),FALSE);
							}
							Boss.d_hanyou[1] = 0.0;
						}
						SPlaySound(10);
						float length = 3*cp;
						float plus = 9*cp;
						for(int i=0;i<20;i++){
							float angle = Radian(18*i+plus,TRUE);
							SEs_Make(Boss.x+length*cos(angle),Boss.y-60+length*sin(angle),Boss.d_hanyou[0],2.0,gra_e_shot[4],20,0.3,0,20);
						}
					}
					else if(cp<50){}
					else if(cp<110){
						Boss.d_hanyou[1] += 0.1;
					}
					break;
				case 3:
					cp = c%170;
					if(cp<=30){
						if(cp==0){
							float sx = Player.x - Boss.x;
							float sy = Player.y - (Boss.y-60);
							if(sx==0){
								if(sy>0)	Boss.d_hanyou[0] = 270;
								else		Boss.d_hanyou[0] = 90;
							}
							else{
								Boss.d_hanyou[0] = Radian(atan2(sy,sx),FALSE);
							}
							Boss.d_hanyou[1] = 0.0;
						}
						SPlaySound(10);
						float length = 3*cp;
						float plus = 9*cp;
						for(int i=0;i<20;i++){
							float angle = Radian(18*i+plus,TRUE);
							SEs_Make(Boss.x+length*cos(angle),Boss.y-60+length*sin(angle),Boss.d_hanyou[0],3.0,gra_e_shot[5],20,0.4,0,20);
						}
					}
					else if(cp<50){}
					else if(cp<110){
						Boss.d_hanyou[1] += 0.1;
					}
					break;
			}
		}
	}
	else if(p<=35){//天符「天狗隠しの怪」
		if(c>=10){
			if(c>=10&&c<15)		Boss.img_num = 5;
			else if(c>=15&&c<20)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=20){
				int cp;
				switch(SAVE.Level){
					case 0:
						cp = c%150;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<6;i++){
								SEs_Make(Boss.x-22,Boss.y-13,145+50.0*i-50+get_rand(100),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%6);
							}
						}
						if(c>140&&c%5==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x-22,Boss.y-13,get_rand(360),1.0+0.1*get_rand(10),gra_e_shot[6],10,0.0,0,0,i%3);
							}
						}
						break;
					case 1:
						cp = c%120;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<6;i++){
								SEs_Make(Boss.x-22,Boss.y-13,145+50.0*i-50+get_rand(100),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%6);
							}
						}
						if(c>140&&c%4==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x-22,Boss.y-13,get_rand(360),1.0+0.1*get_rand(10),gra_e_shot[6],10,0.0,0,0,i%3);
							}
						}
						break;
					case 2:
						cp = c%120;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<6;i++){
								SEs_Make(Boss.x-22,Boss.y-13,145+50.0*i-50+get_rand(100),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%6);
							}
						}
						if(c>140&&c%2==0){
							SPlaySound(10);
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x-22,Boss.y-13,get_rand(360),1.0+0.1*get_rand(10),gra_e_shot[6],10,0.0,0,0,i%3);
							}
						}
						break;
					case 3:
						cp = c%120;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<8;i++){
								SEs_Make(Boss.x-22,Boss.y-13,138.75+37.5*i-30+get_rand(60),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%8);
							}
						}
						if(c>140&&c%2==0){
							SPlaySound(10);
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x-22,Boss.y-13,get_rand(360),1.0+0.1*get_rand(10),gra_e_shot[6],10,0.0,0,0,i%5);
							}
						}
						break;
				}
			}
		}
	}
	else if(p<=39){//結界「カーストファンタズム」
		if(c>=30){
			c -= 30;
			if(c==0){
				Boss.i_hanyou[0] = 150;
			}
			int cp = c%Boss.i_hanyou[0];
			if(cp<60){
				if(cp>=0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else			Boss.img_num = 21;
			}
			if(cp==10){
				switch(SAVE.Level){
					case 0:
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,-50.0,0.0,0,23,0);
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,50.0,0.0,0,25,0);
						if(Boss.life<Boss.spell_life/3 || Boss.countdown<60*15){
							if(Boss.i_hanyou[0] == 150){
								Boss.i_hanyou[0] = 130;
								Boss.count = 130;
							}
						}
						break;
					case 1:
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,-50.0,0.0,0,23,0);
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,50.0,0.0,0,25,0);
						if(Boss.life<Boss.spell_life/3 || Boss.countdown<60*15){
							if(Boss.i_hanyou[0] == 150){
								Boss.i_hanyou[0] = 130;
								Boss.count = 130;
							}
						}
						break;
					case 2:
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,-50.0,0.0,0,23,0);
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,50.0,0.0,0,25,0);
						if(Boss.life<Boss.spell_life/3 || Boss.countdown<60*15){
							if(Boss.i_hanyou[0] == 150){
								Boss.i_hanyou[0] = 130;
								Boss.count = 130;
							}
						}
						break;
					case 3:
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,-50.0,0.0,0,23,0);
						SEs_NWay(Boss.x,Boss.y,0.0,1,8.0,gra_e_shot[32],10,50.0,0.0,0,25,0);
						if(Boss.life<Boss.spell_life/3 || Boss.countdown<60*15){
							if(Boss.i_hanyou[0] == 150){
								Boss.i_hanyou[0] = 100;
								Boss.count = 130;
							}
						}
						break;
				}
			}
			if(cp==90){
				int move_x = 140+get_rand(30);
				int move_y = 100+get_rand(50);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,25);			
			}
		}
	}
	else if(p<=43){//結界「ムーブド・アンムーブド」
		if(c>=50){
			c -= 50;
			int cp;
			switch(SAVE.Level){
				case 0:
					cp = c%210;
					if(cp==0 || cp==90){
						SPlaySound(8);
						float sx = Player.x - Boss.x;
						float sy = Player.y - Boss.y;
						float sq = sqrt(sx*sx+sy*sy);
						float speed = 3.0;
						int time = sq / speed;
						SEs_NWay(Boss.x,Boss.y,45.0,3,speed,gra_e_shot[32],10,0.0,0.0,0,0);
						SEs_NWay(Boss.x,Boss.y,20.0,9,4.0,gra_e_shot[27],10,180.0);
						SEn_Make(Player.x,Player.y,8,time,-1,20,-1);					
					}
					break;
				case 1:
					cp = c%210;
					if(cp==0 || cp==90){
						SPlaySound(8);
						float sx = Player.x - Boss.x;
						float sy = Player.y - Boss.y;
						float sq = sqrt(sx*sx+sy*sy);
						float speed = 4.0;
						int time = sq / speed;
						SEs_NWay(Boss.x,Boss.y,45.0,3,speed,gra_e_shot[32],10,0.0,0.0,0,0);
						SEs_NWay(Boss.x,Boss.y,20.0,9,4.0,gra_e_shot[27],10,180.0);
						SEn_Make(Player.x,Player.y,8,time,-1,20,-1);					
					}
					break;
				case 2:
					cp = c%210;
					if(cp==0 || cp==60 || cp==90){
						SPlaySound(8);
						float sx = Player.x - Boss.x;
						float sy = Player.y - Boss.y;
						float sq = sqrt(sx*sx+sy*sy);
						float speed = 5.0;
						int time = sq / speed;
						SEs_NWay(Boss.x,Boss.y,45.0,3,speed,gra_e_shot[32],10,0.0,0.0,0,0);
						SEs_NWay(Boss.x,Boss.y,20.0,9,4.0,gra_e_shot[27],10,180.0);
						SEn_Make(Player.x,Player.y,8,time,-1,20,-1);					
					}
					break;
				case 3:
					cp = c%210;
					if(cp==0 || cp==60 || cp==90){
						SPlaySound(8);
						float sx = Player.x - Boss.x;
						float sy = Player.y - Boss.y;
						float sq = sqrt(sx*sx+sy*sy);
						float speed = 5.0;
						int time = sq / speed;
						SEs_NWay(Boss.x,Boss.y,45.0,3,speed,gra_e_shot[32],10,0.0,0.0,0,0);
						SEs_NWay(Boss.x,Boss.y,20.0,9,4.0,gra_e_shot[27],10,180.0);
						SEn_Make(Player.x,Player.y,8,time,-1,20,-1);					
					}
					break;
			}
		}
	}
	else if(p<=47){//戯符「神々のアジャラ空間」
		if(c>=50){
			c-=50;
			if(c>=10&&c<15)		Boss.img_num = 5;
			else if(c>=15&&c<20)	Boss.img_num = 13;
			else if(c>=20)		Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=20){
				switch(SAVE.Level){
					case 0:
						if(c==20){
							SPlaySound(19);
							for(int i=0;i<10;i++){
								SLas_Make(Boss.x,Boss.y,0-20*i,10.0,gra_laser[0],60,6,0);
							}
							for(int i=0;i<11;i++){
								SLas_Make(Boss.x,Boss.y,10-20*i,10.0,gra_laser[1],60,6,0);
							}
						}
						if(c==130){
							for(int i=0;i<15;i++){
								//SEn_Make(20+100*i,20,8,255,24,22,2);					
							}
						}
						if(c>=130){
							if(c%50==0){
								for(int i=0;i<8;i++){
									SEs_Make(Boss.x,Boss.y,22.5+45.0*i,1.0,gra_e_shot[42],20);
								}
							}
							if(c%100==0){
								for(int i=0;i<8;i++){
									SEs_Make(Boss.x,Boss.y,45.0*i,1.0,gra_e_shot[27],20);
								}
							}
						}
						break;
					case 1:
						if(c==20){
							SPlaySound(19);
							for(int i=0;i<12;i++){
								SLas_Make(Boss.x,Boss.y,20-20*i,10.0,gra_laser[0],60,6,0);
							}
							for(int i=0;i<13;i++){
								SLas_Make(Boss.x,Boss.y,30-20*i,10.0,gra_laser[1],60,6,0);
							}
						}
						if(c==130){
							for(int i=0;i<15;i++){
								//SEn_Make(20+70*i,20,8,255,24,22,2);					
							}
						}
						if(c>=130){
							if(c%70==0){
								for(int i=0;i<10;i++){
									SEs_Make(Boss.x,Boss.y,18+36.0*i,1.0,gra_e_shot[42],20);
								}
							}
							if(c%100==0){
								for(int i=0;i<10;i++){
									SEs_Make(Boss.x,Boss.y,36.0*i,1.0,gra_e_shot[27],20);
								}
							}
						}
						break;
					case 2:
						if(c==20){
							SPlaySound(19);
							for(int i=0;i<12;i++){
								SLas_Make(Boss.x,Boss.y,20-20*i,10.0,gra_laser[0],60,6,0);
							}
							for(int i=0;i<13;i++){
								SLas_Make(Boss.x,Boss.y,30-20*i,10.0,gra_laser[1],60,6,0);
							}
						}
						if(c==130){
							for(int i=0;i<15;i++){
								//SEn_Make(20+70*i,20,8,255,24,22,2);					
							}
						}
						if(c>=130){
							if(c%50==0){
								for(int i=0;i<12;i++){
									SEs_Make(Boss.x,Boss.y,15+30.0*i,1.0,gra_e_shot[42],20);
								}
							}
							if(c%100==0){
								for(int i=0;i<12;i++){
									SEs_Make(Boss.x,Boss.y,30.0*i,1.0,gra_e_shot[27],20);
								}
							}
						}
						break;
					case 3:
						if(c==20){
							SPlaySound(19);
							for(int i=0;i<12;i++){
								SLas_Make(Boss.x,Boss.y,20-20*i,10.0,gra_laser[0],60,6,0);
							}
							for(int i=0;i<13;i++){
								SLas_Make(Boss.x,Boss.y,30-20*i,10.0,gra_laser[1],60,6,0);
							}
						}
						if(c==130){
							for(int i=0;i<15;i++){
								//SEn_Make(20+70*i,20,8,255,24,22,2);					
							}
						}
						if(c>=130){
							if(c%40==0){
								for(int i=0;i<12;i++){
									SEs_Make(Boss.x,Boss.y,15+30.0*i,1.2,gra_e_shot[42],20);
								}
							}
							if(c%70==0){
								for(int i=0;i<12;i++){
									SEs_Make(Boss.x,Boss.y,30.0*i,1.0,gra_e_shot[27],20);
								}
							}
						}
						break;
				}
			}
		}	
	}
	else if(p<=51){//魅了「幻想誘死蝶」
		if(c>=50){
			c-=50;
			if(c>=10&&c<15)		Boss.img_num = 5;
			else if(c>=15&&c<20)	Boss.img_num = 13;
			else if(c>=20)		Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=20){
				switch(SAVE.Level){
					int cp;
					case 0:
						cp = c%240;
						if(cp==20){
							for(int i=0;i<8;i++){
								SEs_NWay(Boss.x,Boss.y,60.0,6,1.0,gra_e_shot[22],20,get_rand(59),1.0*i+get_rand(5)*0.1,0,29,i%8);
								SEs_NWay(Boss.x,Boss.y,60.0,6,1.0,gra_e_shot[23],20,get_rand(59),1.0*i+get_rand(5)*0.1,1,29,i%8);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
					case 1:
						cp = c%220;
						if(cp==20){
							for(int i=0;i<8;i++){
								SEs_NWay(Boss.x,Boss.y,60.0,6,1.5,gra_e_shot[22],20,get_rand(59),1.0*i+get_rand(5)*0.1,0,29,i%8);
								SEs_NWay(Boss.x,Boss.y,60.0,6,1.5,gra_e_shot[23],20,get_rand(59),1.0*i+get_rand(5)*0.1,1,29,i%8);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
					case 2:
						cp = c%210;
						if(cp==20){
							for(int i=0;i<8;i++){
								SEs_NWay(Boss.x,Boss.y,60.0,6,2.0,gra_e_shot[22],20,get_rand(59),1.0*i+get_rand(5)*0.1,0,29,i%8);
								SEs_NWay(Boss.x,Boss.y,60.0,6,2.0,gra_e_shot[23],20,get_rand(59),1.0*i+get_rand(5)*0.1,1,29,i%8);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
					case 3:
						cp = c%180;
						if(cp==20){
							for(int i=0;i<15;i++){
								SEs_NWay(Boss.x,Boss.y,60.0,6,3.0,gra_e_shot[22],20,get_rand(59),0.5*i+get_rand(5)*0.1,0,29);
								SEs_NWay(Boss.x,Boss.y,60.0,6,3.0,gra_e_shot[23],20,get_rand(59),0.5*i+get_rand(5)*0.1,1,29);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
				}
			}
		}	
	}
	else if(p<=55){//境符「生と死の境界 -六道-」
		static int count[6] = {0,};
		if(c<50){
			for(int i=0;i<6;i++){
				count[i] = 0;
			}
		}
		if(c>=50){
			c -= 50;
			switch(SAVE.Level){
				case 0:
					if(c%15==0){
						SPlaySound(10);
						int cp = c/15;
						for(int i=0;i<5;i++){
							SEs_Make(Boss.x,Boss.y,20*cp+21*i,2.0,gra_e_shot[52],10);
						}
					}
					if(Boss.life<=Boss.spell_life*6/7 || Boss.countdown<=30*60){
						if(count[0]==0)	SPlaySound(8);
						if(count[0]%15==0){
							SPlaySound(10);
							int cp = count[0]/15-10;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,-30*cp+15*i,1.8,gra_e_shot[22],10);
							}
						}
						count[0]++;
					}
					if(Boss.life<=Boss.spell_life*5/7 || Boss.countdown<=30*60){
						if(count[1]==0)	SPlaySound(8);
						if(count[1]%20==0){
							SPlaySound(10);
							int cp = count[1]/20-45;
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x,Boss.y,90*cp+46*i-23,2.0,gra_e_shot[31],10);
							}
						}
						count[1]++;
					}
					if(Boss.life<=Boss.spell_life*4/7 || Boss.countdown<=30*60){
						if(count[2]==0)	SPlaySound(8);
						if(count[2]%15==0){
							SPlaySound(10);    
							int cp = count[2]/15;
							for(int i=0;i<10;i++){
								for(int a=0;a<1;a++){
									SEs_Make(Boss.x,Boss.y,20*cp+40*i,2.0-1.0*a,gra_e_shot[19],10);
								}
							}
						}
						count[2]++;
					}
					if(Boss.life<=Boss.spell_life*3/7 || Boss.countdown<=30*60){
						if(count[3]==0)	SPlaySound(8);
						if(count[3]%10==0){
							SPlaySound(10);
							int cp = count[3]/10;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,-15*cp+45*i,3.0,gra_e_shot[28],10);
							}
						}
						count[3]++;
					}
					if(Boss.life<=Boss.spell_life*2/7 || Boss.countdown<=30*60){
						if(count[4]==0)	SPlaySound(8);
						if(count[4]%8==0){
							SPlaySound(10);
							int cp = count[4]/8;
							for(int i=0;i<5;i++){
								for(int a=0;a<2;a++){ 
									SEs_Make(Boss.x,Boss.y,15*cp+45*i,3.0-0.5*a,gra_e_shot[27],10);
								}
							}
						}
						count[4]++;
					}
					break;
				case 1:
					if(c%10==0){
						SPlaySound(10);
						int cp = c/10;
						for(int i=0;i<5;i++){
							SEs_Make(Boss.x,Boss.y,20*cp+21*i,2.0,gra_e_shot[52],10);
						}
					}
					if(Boss.life<=Boss.spell_life*6/7 || Boss.countdown<=30*60){
						if(count[0]==0)	SPlaySound(8);
						if(count[0]%10==0){
							SPlaySound(10);
							int cp = count[0]/10-10;
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x,Boss.y,-30*cp+15*i,1.8,gra_e_shot[22],10);
							}
						}
						count[0]++;
					}
					if(Boss.life<=Boss.spell_life*5/7 || Boss.countdown<=30*60){
						if(count[1]==0)	SPlaySound(8);
						if(count[1]%15==0){
							SPlaySound(10);
							int cp = count[1]/15-45;
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x,Boss.y,90*cp+46*i-23,2.0,gra_e_shot[31],10);
							}
						}
						count[1]++;
					}
					if(Boss.life<=Boss.spell_life*4/7 || Boss.countdown<=30*60){
						if(count[2]==0)	SPlaySound(8);
						if(count[2]%10==0){
							SPlaySound(10);    
							int cp = count[2]/10;
							for(int i=0;i<10;i++){
								for(int a=0;a<2;a++){
									SEs_Make(Boss.x,Boss.y,20*cp+40*i,2.0-1.0*a,gra_e_shot[19],10);
								}
							}
						}
						count[2]++;
					}
					if(Boss.life<=Boss.spell_life*3/7 || Boss.countdown<=30*60){
						if(count[3]==0)	SPlaySound(8);
						if(count[3]%5==0){
							SPlaySound(10);
							int cp = count[3]/5;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,-15*cp+45*i,3.0,gra_e_shot[28],10);
							}
						}
						count[3]++;
					}
					if(Boss.life<=Boss.spell_life*2/7 || Boss.countdown<=30*60){
						if(count[4]==0)	SPlaySound(8);
						if(count[4]%5==0){
							SPlaySound(10);
							int cp = count[4]/5;
							for(int i=0;i<5;i++){
								for(int a=0;a<2;a++){ 
									SEs_Make(Boss.x,Boss.y,15*cp+45*i,3.0-0.5*a,gra_e_shot[27],10);
								}
							}
						}
						count[4]++;
					}
					break;
				case 2:
					if(c%10==0){
						SPlaySound(10);
						int cp = c/10;
						for(int i=0;i<5;i++){
							SEs_Make(Boss.x,Boss.y,20*cp+21*i,2.0,gra_e_shot[52],10);
						}
					}
					if(Boss.life<=Boss.spell_life*6/7 || Boss.countdown<=30*60){
						if(count[0]==0)	SPlaySound(8);
						if(count[0]%10==0){
							SPlaySound(10);
							int cp = count[0]/10-10;
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x,Boss.y,-30*cp+15*i,1.8,gra_e_shot[22],10);
							}
						}
						count[0]++;
					}
					if(Boss.life<=Boss.spell_life*5/7 || Boss.countdown<=30*60){
						if(count[1]==0)	SPlaySound(8);
						if(count[1]%15==0){
							SPlaySound(10);
							int cp = count[1]/15-45;
							for(int i=0;i<3;i++){
								SEs_Make(Boss.x,Boss.y,90*cp+46*i-23,2.0,gra_e_shot[31],10);
							}
						}
						count[1]++;
					}
					if(Boss.life<=Boss.spell_life*4/7 || Boss.countdown<=30*60){
						if(count[2]==0)	SPlaySound(8);
						if(count[2]%10==0){
							SPlaySound(10);    
							int cp = count[2]/10;
							for(int i=0;i<10;i++){
								for(int a=0;a<2;a++){
									SEs_Make(Boss.x,Boss.y,12*cp+24*i,2.0-1.0*a,gra_e_shot[19],10);
								}
							}
						}
						count[2]++;
					}
					if(Boss.life<=Boss.spell_life*3/7 || Boss.countdown<=30*60){
						if(count[3]==0)	SPlaySound(8);
						if(count[3]%5==0){
							SPlaySound(10);
							int cp = count[3]/5;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,-15*cp+45*i,3.0,gra_e_shot[28],10);
							}
						}
						count[3]++;
					}
					if(Boss.life<=Boss.spell_life*2/7 || Boss.countdown<=30*60){
						if(count[4]==0)	SPlaySound(8);
						if(count[4]%5==0){
							SPlaySound(10);
							int cp = count[4]/5;
							for(int i=0;i<5;i++){
								for(int a=0;a<2;a++){ 
									SEs_Make(Boss.x,Boss.y,15*cp+45*i,3.0-0.5*a,gra_e_shot[27],10);
								}
							}
						}
						count[4]++;
					}
					break;
				case 3:
					if(c%10==0){
						SPlaySound(10);
						int cp = c/10;
						for(int i=0;i<7;i++){
							SEs_Make(Boss.x,Boss.y,15*cp+16*i-10,2.0,gra_e_shot[52],10);
						}
					}
					if(Boss.life<=Boss.spell_life*7/8 || Boss.countdown<=30*60){
						if(count[0]==0)	SPlaySound(8);
						if(count[0]%10==0){
							SPlaySound(10);
							int cp = count[0]/10-10;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,-20*cp+10*i,1.8,gra_e_shot[22],10);
							}
						}
						count[0]++;
					}
					if(Boss.life<=Boss.spell_life*6/8 || Boss.countdown<=30*60){
						if(count[1]==0)	SPlaySound(8);
						if(count[1]%15==0){
							SPlaySound(10);
							int cp = count[1]/15-45;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,60*cp+31*i-15,2.0,gra_e_shot[31],10);
							}
						}
						count[1]++;
					}
					if(Boss.life<=Boss.spell_life*5/8 || Boss.countdown<=30*60){
						if(count[2]==0)	SPlaySound(8);
						if(count[2]%10==0){
							SPlaySound(10);    
							int cp = count[2]/10;
							for(int i=0;i<10;i++){
								for(int a=0;a<2;a++){
									SEs_Make(Boss.x,Boss.y,8*cp+16*i,2.5-1.0*a,gra_e_shot[19],10);
								}
							}
						}
						count[2]++;
					}
					if(Boss.life<=Boss.spell_life*4/8 || Boss.countdown<=30*60){
						if(count[3]==0)	SPlaySound(8);
						if(count[3]%5==0){
							SPlaySound(10);
							int cp = count[3]/5;
							for(int i=0;i<5;i++){
								SEs_Make(Boss.x,Boss.y,-12*cp+36*i,3.5,gra_e_shot[28],10);
							}
						}
						count[3]++;
					}
					if(Boss.life<=Boss.spell_life*3/8 || Boss.countdown<=30*60){
						if(count[4]==0)	SPlaySound(8);
						if(count[4]%5==0){
							SPlaySound(10);
							int cp = count[4]/5;
							for(int i=0;i<5;i++){
								for(int a=0;a<2;a++){ 
									SEs_Make(Boss.x,Boss.y,15*cp+45*i,3.5-0.5*a,gra_e_shot[27],10);
								}
							}
						}
						count[4]++;
					}
					if(Boss.life<=Boss.spell_life*2/8 || Boss.countdown<=30*60){
						if(count[5]==0)	SPlaySound(8);
						if(count[5]%5==0){
							SPlaySound(10);
							int cp = count[5]/5;
							SEs_NWay(Boss.x,Boss.y,9.0,8,4.0,gra_e_shot[25],10,27*cp);
						}
						count[5]++;
					}
					break;
			}
		}
	}
	else if(p<=58){//薈萃「人工特異点」
		int cp = c%200;
		if(cp>=0&&cp<20){}
		else if(cp>=20&&cp<25){
			Boss.img_num = 5;
		}
		else if(cp>=25&&cp<30){
			Boss.img_num = 13;
		}
		else if(cp>=30&&cp<110){
			int rand;
			if(cp==30)	SPlaySound(19);
			if(cp%1==0){
				SPlaySound(11);
				for(int i=0;i<3;i++){
					rand = get_rand(359);
					SEs_Make(Boss.x+cp*2.0*cos(Radian(rand,TRUE)),Boss.y-60+cp*2.0*sin(Radian(rand,TRUE)),rand+180,5.5,gra_e_shot[5],10,5.0,0,3);
				}
				for(int i=0;i<4;i++){
					rand = get_rand(359);
					SEs_Make(Boss.x+cp*2.0*cos(Radian(rand,TRUE)),Boss.y-60+cp*2.0*sin(Radian(rand,TRUE)),rand+180,5.5,gra_e_shot[28],10,5.0,0,3);
					rand = get_rand(359);
					SEs_Make(Boss.x+cp*2.0*cos(Radian(rand,TRUE)),Boss.y-60+cp*2.0*sin(Radian(rand,TRUE)),rand+180,5.5,gra_e_shot[26],10,5.0,0,3);
				}
				if(cp%4==0){
					for(int i=0;i<1;i++){
						rand = get_rand(359);
						SEs_Make(Boss.x+cp*2.0*cos(Radian(rand,TRUE)),Boss.y-60+cp*2.0*sin(Radian(rand,TRUE)),rand+180,5.5,gra_e_shot[34],10,5.0,0,3);
					}
				}
			}
		}
		else if(cp==130||cp==145||cp==160){
			if(cp==130){
				Boss.d_hanyou[0] = Player.x;
				Boss.d_hanyou[1] = Player.y;
			}
			Boss.d_hanyou[2] = Player.x;
			Boss.d_hanyou[3] = Player.y;
			Player.x = Boss.d_hanyou[0];
			Player.y = Boss.d_hanyou[1];
			SPlaySound(10);
			switch(SAVE.Level){
				case 1:
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,45.0,7,3.6-0.8*i,gra_e_shot[34],5,180.0,10.0,10);
						SEs_NWay(Boss.x,Boss.y-60,22.5,15,4.0-0.8*i,gra_e_shot[28],5,180.0,10.0,10);
					}
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,2.0,8,3.5-0.6*i,gra_e_shot[26],5,0,10.0,10);
						SEs_NWay(Boss.x,Boss.y-60,5.0,6,3.5-0.8*i,gra_e_shot[5],5,0,10.0,10);
					}
					break;
				case 2:
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,36.0,9,3.6-0.8*i,gra_e_shot[34],5,180.0,10.0,10);
						SEs_NWay(Boss.x,Boss.y-60,15.0,23,4.0-0.8*i,gra_e_shot[28],5,180.0,10.0,10);
					}
					for(int i=0;i<3;i++){
						SEs_NWay(Boss.x,Boss.y-60,2.0,8,5.0-0.6*i,gra_e_shot[26],5,0,10.0,10);
						SEs_NWay(Boss.x,Boss.y-60,5.0,6,5.0-0.8*i,gra_e_shot[5],5,0,10.0,10);
					}
					break;
				case 3:
					for(int i=0;i<5;i++){
						SEs_NWay(Boss.x,Boss.y-60,36.0,9,4.6-0.8*i,gra_e_shot[34],5,180.0,10.0,10);
						SEs_NWay(Boss.x,Boss.y-60,10.0,35,5.0-0.8*i,gra_e_shot[28],5,180.0,10.0,10);
					}
					for(int i=0;i<5;i++){
						SEs_NWay(Boss.x,Boss.y-60,2.0,10,6.0-0.6*i,gra_e_shot[26],5,0,10.0,10);
						SEs_NWay(Boss.x,Boss.y-60,5.0,8,6.0-0.8*i,gra_e_shot[5],5,0,10.0,10);
					}
					break;
			}
			Player.x = Boss.d_hanyou[2];
			Player.y = Boss.d_hanyou[3];
		}
		if(cp>=30&&cp<150){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
	}
	else if(p<=61){//萃夢「ミッシングデモン」
		switch(SAVE.Level){
			case 1:
				if(c%17==1){
					int img = gra_e_shot[14];
					if(c%34==18)	img = gra_e_shot[4];
					SPlaySound(10);
					for(int i=0;i<20;i++){
						SEs_Make(Boss.x,Boss.y,18.0*i+9.0,2.5,img,10);
					}
				}
				if(c%30==1){
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+10*cos(Radian(120*i,TRUE)),Boss.y+10*sin(Radian(120*i,TRUE)),31*c/30,1.5,gra_e_shot[26],10);
					}
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+10*cos(Radian(120*i,TRUE)),Boss.y+10*sin(Radian(120*i,TRUE)),31*c/30+180,1.5,gra_e_shot[27],10);
					}
				}
				if(c%100==1){
					int rand = get_rand(17);
					for(int i=0;i<20;i++){
						SEs_Make(Boss.x,Boss.y,rand+18.0*i,1.0,gra_e_shot[28],10);
					}
				}
				break;
			case 2:
				if(c%15==1){
					int img = gra_e_shot[14];
					if(c%30==16)	img = gra_e_shot[4];
					SPlaySound(10);
					for(int i=0;i<25;i++){
						SEs_Make(Boss.x,Boss.y,14.4*i-3.6,2.5,img,10);
					}
				}
				if(c%25==1){
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+10*cos(Radian(120*i,TRUE)),Boss.y+10*sin(Radian(120*i,TRUE)),31*c/25,1.5,gra_e_shot[26],10);
					}
					for(int i=0;i<3;i++){
						SEs_Make(Boss.x+10*cos(Radian(120*i,TRUE)),Boss.y+10*sin(Radian(120*i,TRUE)),31*c/25+180,1.5,gra_e_shot[27],10);
					}
				}
				if(c%80==1){
					int rand = get_rand(14);
					for(int i=0;i<25;i++){
						SEs_Make(Boss.x,Boss.y,rand+14.4*i,1.0,gra_e_shot[28],10);
					}
				}
				break;
			case 3:
				if(c%10==1){
					int img = gra_e_shot[14];
					if(c%20==11)	img = gra_e_shot[4];
					SPlaySound(10);
					for(int i=0;i<30;i++){
						SEs_Make(Boss.x,Boss.y,12.0*i,2.5,img,10);
					}
				}
				if(c%20==1){
					for(int a=0;a<2;a++){
						for(int i=0;i<3;i++){
							SEs_Make(Boss.x+10*cos(Radian(120*i,TRUE)),Boss.y+10*sin(Radian(120*i,TRUE)),31*c/20+180*a,1.5,gra_e_shot[26],10);
						}
					}
					for(int a=0;a<2;a++){
						for(int i=0;i<3;i++){
							SEs_Make(Boss.x+10*cos(Radian(120*i,TRUE)),Boss.y+10*sin(Radian(120*i,TRUE)),31*c/20+90+180*a,1.5,gra_e_shot[27],10);
						}
					}
				}
				if(c%60==1){
					int rand = get_rand(11);
					for(int i=0;i<30;i++){
						SEs_Make(Boss.x,Boss.y,rand+12.0*i,1.0,gra_e_shot[28],10);
					}
				}
				break;
		}		
	}
	else if(p<=64){//「ミッシングファイナルパワー」
		if(c>=100){
			switch(SAVE.Level){
				case 1:
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand = get_rand(35);
						rand = get_rand(17);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(5),gra_e_shot[27],0);
						}
						rand = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(5),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(5),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,1.0+0.1*get_rand(5),gra_e_shot[1],0);
						}
					}
					break;
				case 2:
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand = get_rand(17);
						rand = get_rand(11);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(10),gra_e_shot[27],0);
						}
						rand = get_rand(11);
						for(int i=0;i<30;i++){
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(10),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,0.5+0.1*get_rand(10),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+12.0*i,1.0+0.1*get_rand(10),gra_e_shot[1],0);
						}
					}
					break;
				case 3:
					if(Boss.i_hanyou[0]==2){
						Boss.i_hanyou[0] = 0;
						int rand;
						rand = get_rand(11);
						for(int i=0;i<20;i++){
							SEs_Make(Boss.x,Boss.y,rand+18.0*i,0.5+0.1*get_rand(15),gra_e_shot[27],0);
						}
						rand = get_rand(15);
						for(int i=0;i<40;i++){
							SEs_Make(Boss.x,Boss.y,rand+9.0*i,0.5+0.1*get_rand(20),gra_e_shot[9],0);
							SEs_Make(Boss.x,Boss.y,rand+9.0*i,0.5+0.1*get_rand(20),gra_e_shot[5],0);
							SEs_Make(Boss.x,Boss.y,rand+9.0*i,1.0+0.1*get_rand(20),gra_e_shot[1],0);
						}
					}
					break;
			}
		}
	}
	else if(p<=67){//疾風迅雷「ソニックブーム」
		if(c>=1)	Boss.img_count = 0;
		if(c>=1&&c<6)	Boss.img_num = 5;
		else if(c<12)	Boss.img_num = 13;
		else if(c<18)	Boss.img_num = 21;
		else{	
			Boss.img_num = 21;
			int cp;
			switch(SAVE.Level){
				case 1:
					cp = (c-18)%20;
					if(cp==0){
						SPlaySound(10);
						float angle = 3.5*c/20*7;
						while(angle>70){
							angle -= 140;
						}
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i,3.5,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-1,3.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+1,3.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-2,3.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+2,3.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-3,2.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+3,2.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-4,2.7,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+4,2.7,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-5,2.5,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+5,2.5,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
				case 2:
					cp = (c-18)%10;
					if(cp==0){
						SPlaySound(10);
						float angle = 3.5*c/10*7;
						while(angle>70){
							angle -= 140;
						}
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i,4.0,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-1,3.8,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+1,3.8,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-2,3.6,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+2,3.6,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-3,3.4,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+3,3.4,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-4,3.2,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+4,3.2,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-5,3.0,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+5,3.0,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
				case 3:
					cp = (c-18)%7;
					if(cp==0){
						SPlaySound(10);
						float angle = 3.5*c;
						while(angle>70){
							angle -= 140;
						}
						for(int i=0;i<2;i++){
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i,4.5,gra_e_shot[19],10,0.0,0,5,i);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-1,4.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+1,4.3,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-2,4.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+2,4.1,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-3,3.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+3,3.9,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-4,3.7,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+4,3.7,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i-5,3.5,gra_e_shot[19],10,0.0,0,5,1);
							SEs_Make(Boss.x-22,Boss.y-13,angle+180*i+5,3.5,gra_e_shot[19],10,0.0,0,5,1);
						}
					}
					break;
			}
		}
	}
	else if(p<=70){//風符「サイクロンウェーブ」
		int cp;
		switch(SAVE.Level){
			case 1:
				cp = c%240;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=120&&cp<125)Boss.img_num = 13;
				else if(cp>=125&&cp<130)Boss.img_num = 5;
				else if(cp>=130){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%240==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(44);
				}
				if(cp>=20&&cp<100&&cp%5==0){
					SPlaySound(11);
					for(int i=0;i<10;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+36*i,2.0-0.01*(cp-20),gra_e_shot[17],10,6.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+36*i+18,2.0-0.01*(cp-20),gra_e_shot[52],10,6.5,0,15,effect);
					}
				}
				break;
			case 2:
				cp = c%240;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=120&&cp<125)Boss.img_num = 13;
				else if(cp>=125&&cp<130)Boss.img_num = 5;
				else if(cp>=130){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%240==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(44);
				}
				if(cp>=20&&cp<100&&cp%5==0){
					SPlaySound(11);
					for(int i=0;i<12;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+30*i,2.5-0.01*(cp-20),gra_e_shot[17],10,6.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+30*i+15,2.5-0.01*(cp-20),gra_e_shot[52],10,6.5,0,15,effect);
					}
				}
				break;
			case 3:
				cp = c%180;
				if(cp>0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else if(cp>=120&&cp<125)Boss.img_num = 13;
				else if(cp>=125&&cp<130)Boss.img_num = 5;
				else if(cp>=130){}
				else if(cp!=0){
					Boss.img_num = 21;
					Boss.img_count = 0;
				}
				if(Boss.count%180==30){
					SPlaySound(19); 
					Boss.i_hanyou[0] = get_rand(29);
				}
				if(cp>=20&&cp<100&&cp%3==0){
					SPlaySound(11);
					for(int i=0;i<12;i++){
						int effect = 1;
						if(i==0)	effect = 0;
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+30*i,4.0-0.030*(cp-20),gra_e_shot[17],10,6.5,0,14,effect);
						SEs_Make(Boss.x-22,Boss.y-13,Boss.i_hanyou[0]+30*i+15,4.0-0.030*(cp-20),gra_e_shot[52],10,6.5,0,15,effect);
					}
				}
				break;
		}
	}
	else if(p<=73){//「夢想風神」
		int cp;
		if(c==90||c==150){
			SPlaySound(8); 
			if(Boss.x<CENTER_X){
				SBos_MoveTo(550,50+get_rand(120),30);
			}
			else{
				SBos_MoveTo(-150,50+get_rand(120),30);
			}
		}
		if(c==210||c==250){
			SPlaySound(8); 
			if(Boss.x<CENTER_X){
				SBos_MoveTo(550,50+get_rand(120),20);
			}
			else{
				SBos_MoveTo(-150,50+get_rand(120),20);
			}
		}
		switch(SAVE.Level){
			case 1:
				if(c>=270&&c%12==0){
					SPlaySound(8); 
					if(Boss.x<CENTER_X){
						SBos_MoveTo(550,50+get_rand(120),8);
					}
					else{
						SBos_MoveTo(-150,50+get_rand(120),8);
					}
				}
				if(c<90){}
				else if(Boss.x>20&&Boss.x<400 && c<270){
					if(c%2==0){
						SPlaySound(11);
						for(int i=0;i<3;i++){
							float d = get_rand(60);
							float angle = Radian(get_rand(359),TRUE);
							float x = Boss.x + d*cos(angle);
							float y = Boss.y + d*sin(angle);
							if(Boss.move_x>0){
								SEs_Make(x,y,-70-get_rand(20),1.5,gra_e_shot[17],20,1.0,80,35);
							}
							else{
								SEs_Make(x,y,-110+get_rand(20),1.5,gra_e_shot[17],20,1.0,80,34);
							}
						}
					}
				}
				else if(Boss.x>20&&Boss.x<400){
					if(c%1==0){
						SPlaySound(11);
						for(int i=0;i<2;i++){
							float d = get_rand(60);
							float angle = Radian(get_rand(359),TRUE);
							float x = Boss.x + d*cos(angle);
							float y = Boss.y + d*sin(angle);
							if(Boss.move_x>0){
								SEs_Make(x,y,-70-get_rand(20),2.0,gra_e_shot[17],20,1.0,80,35);
							}
							else{
								SEs_Make(x,y,-110+get_rand(20),2.0,gra_e_shot[17],20,1.0,80,34);
							}
						}
					}
				}
				break;
			case 2:
				if(c>=270&&c%12==0){
					SPlaySound(8); 
					if(Boss.x<CENTER_X){
						SBos_MoveTo(550,50+get_rand(120),8);
					}
					else{
						SBos_MoveTo(-150,50+get_rand(120),8);
					}
				}
				if(c<90){}
				else if(Boss.x>20&&Boss.x<400 && c<270){
					if(c%2==0){
						SPlaySound(11);
						for(int i=0;i<4;i++){
							float d = get_rand(60);
							float angle = Radian(get_rand(359),TRUE);
							float x = Boss.x + d*cos(angle);
							float y = Boss.y + d*sin(angle);
							if(Boss.move_x>0){
								SEs_Make(x,y,-70-get_rand(20),2.0,gra_e_shot[17],20,1.0,80,35);
							}
							else{
								SEs_Make(x,y,-110+get_rand(20),2.0,gra_e_shot[17],20,1.0,80,34);
							}
						}
					}
				}
				else if(Boss.x>20&&Boss.x<400){
					if(c%1==0){
						SPlaySound(11);
						for(int i=0;i<3;i++){
							float d = get_rand(60);
							float angle = Radian(get_rand(359),TRUE);
							float x = Boss.x + d*cos(angle);
							float y = Boss.y + d*sin(angle);
							if(Boss.move_x>0){
								SEs_Make(x,y,-70-get_rand(20),2.5,gra_e_shot[17],20,1.0,80,35);
							}
							else{
								SEs_Make(x,y,-110+get_rand(20),2.5,gra_e_shot[17],20,1.0,80,34);
							}
						}
					}
				}
				break;
			case 3:
				if(c>=270&&c%8==0){
					SPlaySound(8); 
					if(Boss.x<CENTER_X){
						SBos_MoveTo(550,50+get_rand(120),8);
					}
					else{
						SBos_MoveTo(-150,50+get_rand(120),8);
					}
				}
				if(c<90){}
				else if(Boss.x>20&&Boss.x<400 && c<270){
					if(c%2==0){
						SPlaySound(11);
						for(int i=0;i<8;i++){
							float d = get_rand(60);
							float angle = Radian(get_rand(359),TRUE);
							float x = Boss.x + d*cos(angle);
							float y = Boss.y + d*sin(angle);
							if(Boss.move_x>0){
								SEs_Make(x,y,-70-get_rand(20),3.0,gra_e_shot[17],20,1.0,80,35);
							}
							else{
								SEs_Make(x,y,-110+get_rand(20),3.0,gra_e_shot[17],20,1.0,80,34);
							}
						}
					}
				}
				else if(Boss.x>20&&Boss.x<400){
					if(c%1==0){
						SPlaySound(11);
						for(int i=0;i<3;i++){
							float d = get_rand(60);
							float angle = Radian(get_rand(359),TRUE);
							float x = Boss.x + d*cos(angle);
							float y = Boss.y + d*sin(angle);
							if(Boss.move_x>0){
								SEs_Make(x,y,-70-get_rand(20),3.5,gra_e_shot[17],20,1.0,80,35);
							}
							else{
								SEs_Make(x,y,-110+get_rand(20),3.5,gra_e_shot[17],20,1.0,80,34);
							}
						}
					}
				}
				break;
		}
	}
	else if(p<=76){//天狗秘儀「マクロフォーカス」
		int cp,dev;
		switch(SAVE.Level){
			case 1:
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)	dev = 80;
				else	dev = 140;
				cp = c%dev;
				if(cp==20){
					SPlaySound(19);
					float x = 125+get_rand(170);
					float y = 90+get_rand(140);
					for(int i=0;i<4;i++){
						SLas_Make(x-105,y-70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x+105,y-70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x-105,y+70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x+105,y+70,90*i,10.0,gra_laser[1],60);
					}
					float px = Player.x;
					float py = Player.y;
					Player.x = x;
					Player.y = y;
					x -= 100;
					y -= 65;
					if(c%(dev*2)<dev){
						for(int i=0;i<11;i++){
							for(int a=0;a<6;a++){
								SEs_NWay(x+20*i,y+26*a,60.0,1,1.0,gra_e_shot[5],60,0.0,0.0,60);
							}
						}
					}
					else{
						int rand = get_rand(359);
						for(int i=0;i<11;i++){
							for(int a=0;a<6;a++){
								float angle = rand+30*i+30*a;
								for(int b=0;b<3;b++){
									SEs_Make(x+20*i,y+26*a,angle+120*b,1.0,gra_e_shot[53],60,0.0,60,0,b);
								}
							}
						}
					}
					Player.x = px;
					Player.y = py;					
				}
				break;
			case 2:
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)	dev = 70;
				else	dev = 120;
				cp = c%dev;
				if(cp==20){
					SPlaySound(19);
					float x = 125+get_rand(170);
					float y = 90+get_rand(140);
					for(int i=0;i<4;i++){
						SLas_Make(x-105,y-70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x+105,y-70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x-105,y+70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x+105,y+70,90*i,10.0,gra_laser[1],60);
					}
					float px = Player.x;
					float py = Player.y;
					Player.x = x;
					Player.y = y;
					x -= 100;
					y -= 65;
					if(c%(dev*2)<dev){
						for(int i=0;i<11;i++){
							for(int a=0;a<6;a++){
								SEs_NWay(x+20*i,y+26*a,60.0,1,1.0,gra_e_shot[5],60,0.0,0.0,60);
							}
						}
					}
					else{
						int rand = get_rand(359);
						for(int i=0;i<11;i++){
							for(int a=0;a<6;a++){
								float angle = rand+20*i+20*a;
								for(int b=0;b<3;b++){
									SEs_Make(x+20*i,y+26*a,angle+120*b,1.0,gra_e_shot[53],60,0.0,60,0,b);
								}
							}
						}
					}
					Player.x = px;
					Player.y = py;					
				}
				break;
			case 3:
				if(Boss.life<Spell[p].life/4||Boss.countdown<60*12)	dev = 50;
				else	dev = 90;
				cp = c%dev;
				if(cp==20){
					SPlaySound(19);
					float x = 125+get_rand(170);
					float y = 90+get_rand(140);
					for(int i=0;i<4;i++){
						SLas_Make(x-105,y-70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x+105,y-70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x-105,y+70,90*i,10.0,gra_laser[1],60);
						SLas_Make(x+105,y+70,90*i,10.0,gra_laser[1],60);
					}
					float px = Player.x;
					float py = Player.y;
					Player.x = x;
					Player.y = y;
					x -= 100;
					y -= 65;
					if(c%(dev*2)<dev){
						for(int i=0;i<11;i++){
							for(int a=0;a<6;a++){
								SEs_NWay(x+20*i,y+26*a,60.0,3,1.5,gra_e_shot[5],60,0.0,0.0,60);
							}
						}
					}
					else{
						int rand = get_rand(359);
						for(int i=0;i<11;i++){
							for(int a=0;a<6;a++){
								float angle = rand+10*i+10*a;
								for(int b=0;b<3;b++){
									SEs_Make(x+20*i,y+26*a,angle+120*b,1.5,gra_e_shot[53],60,0.0,60,0,b);
								}
							}
						}
					}
					Player.x = px;
					Player.y = py;					
				}
				break;
		}
	}
	else if(p<=79){//鬼符「芙蓉鬼山岳波」
		if(c>=30){
			Boss.img_num = 21;
			Boss.img_count = 0;
		}
		if(c>=0&&c<20){}
		else if(c>=20&&c<25){
			Boss.img_num = 5;
		}
		else if(c>=25&&c<30){
			Boss.img_num = 13;
		}
		else if(c>=30){
			c-=30;
			switch(SAVE.Level){
				int cp;
				case 1:
					cp = c%230;
					if(cp==0){
						SPlaySound(9);
						SEs_NWay(Boss.x,Boss.y-60,40.0,4,8.0,gra_e_shot[34],10,0.0,0.0,180,36);
					}
					break;
				case 2:
					cp = c%230;
					if(cp==0){
						SPlaySound(9);
						SEs_NWay(Boss.x,Boss.y-60,40.0,5,8.0,gra_e_shot[34],10,0.0,0.0,180,36);
					}
					break;
				case 3:
					cp = c%170;
					if(cp==0){
						SPlaySound(9);
						SEs_NWay(Boss.x,Boss.y-60,30.0,5,8.0,gra_e_shot[34],10,0.0,0.0,180,36);
					}
					break;
			}
		}
	}
	else if(p<=82){//天符「文政の天狗少女」
		if(c>=10){
			if(c>=10&&c<15)		Boss.img_num = 5;
			else if(c>=15&&c<20)	Boss.img_num = 13;
			else			Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=20){
				int cp;
				switch(SAVE.Level){
					case 1:
						cp = c%120;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<6;i++){
								SEs_Make(Boss.x-22,Boss.y-13,145+50.0*i-50+get_rand(100),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%6);
							}
						}
						if(c>140&&c%4==0){
							SPlaySound(10);
							for(int i=0;i<9;i++){
								SEs_Make(Boss.x-22,Boss.y-13,get_rand(360),1.0+0.1*get_rand(10),gra_e_shot[2],10,0.0,0,0,i%3);
							}
						}
						break;
					case 2:
						cp = c%120;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<6;i++){
								SEs_Make(Boss.x-22,Boss.y-13,145+50.0*i-50+get_rand(100),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%6);
							}
						}
						if(c>140&&c%2==0){
							SPlaySound(10);
							for(int i=0;i<9;i++){
								SEs_Make(Boss.x-22,Boss.y-13,get_rand(360),1.0+0.1*get_rand(10),gra_e_shot[2],10,0.0,0,0,i%3);
							}
						}
						break;
					case 3:
						cp = c%120;
						if(cp==20){
							SPlaySound(11);
							for(int i=0;i<8;i++){
								SEs_Make(Boss.x-22,Boss.y-13,138.75+37.5*i-30+get_rand(60),10.0+0.1*get_rand(40),gra_e_shot[31],10,0.0,0,22,i%8);
							}
						}
						if(c>140&&c%2==0){
							SPlaySound(10);
							for(int i=0;i<12;i++){
								SEs_Make(Boss.x-22,Boss.y-13,0.1*get_rand(3600),1.0+0.1*get_rand(10),gra_e_shot[2],10,0.0,0,0,i%12);
							}
						}
						break;
				}
			}
		}
	}
	else if(p<=85){//結界「カーストスペクター」
		if(c>=30){
			c -= 30;
			if(c==0){
				Boss.i_hanyou[0] = 150;
			}
			int cp = c%Boss.i_hanyou[0];
			if(cp<60){
				if(cp>=0&&cp<5)		Boss.img_num = 5;
				else if(cp>=5&&cp<10)	Boss.img_num = 13;
				else			Boss.img_num = 21;
			}
			if(cp==10){
				SEs_NWay(Boss.x,Boss.y,40.0,2,8.0,gra_e_shot[32],10,0.0,0.0,0,23,0);
				SEs_NWay(Boss.x,Boss.y,120.0,2,8.0,gra_e_shot[32],10,0.0,0.0,0,25,0);
				if(SAVE.Level<3){
					if(Boss.life<Boss.spell_life/3 || Boss.countdown<60*15){
						if(Boss.i_hanyou[0] == 150){
							Boss.i_hanyou[0] = 130;
							Boss.count = 130;
						}
					}
				}
				else{
					if(Boss.life<Boss.spell_life/3 || Boss.countdown<60*15){
						if(Boss.i_hanyou[0] == 150){
							Boss.i_hanyou[0] = 100;
							Boss.count = 130;
						}
					}
				}
			}
			if(cp==90){
				int move_x = 140+get_rand(30);
				int move_y = 100+get_rand(50);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,25);			
			}
		}
	}
	else if(p<=88){//結界「二重光陰結界」
		if(c>=30){
			c -= 30;
			int cp;
			switch(SAVE.Level){
				case 1:
					cp = c % 230;
					if(cp==1)	SPlaySound(19);
					if(cp==20){
						SEn_Make(Boss.x,Boss.y,8,9999,26,-1,-1);					
					}
					if(cp>=40&&cp<60){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.0+0.1*get_rand(15),gra_e_shot[5],20,get_rand(50),0.0,0,0,i);
						}
					}
					if(cp>=70&&cp<90){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.0+0.1*get_rand(15),gra_e_shot[4],20,-get_rand(50),0.0,0,0,i);
						}
					}
					if(cp==110)	Boss.i_hanyou[0] = 1;
					break;
				case 2:
					cp = c % 210;
					if(cp==1)	SPlaySound(19);
					if(cp==20){
						SEn_Make(Boss.x,Boss.y,8,9999,26,-1,-1);					
					}
					if(cp>=40&&cp<60){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.0+0.1*get_rand(15),gra_e_shot[5],20,get_rand(50),0.0,0,0,i);
						}
						for(int i=0;i<1;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.5+0.1*get_rand(5),gra_e_shot[27],20,get_rand(50),0.0,0,0,i);
						}
					}
					if(cp>=70&&cp<90){
						for(int i=0;i<2;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.0+0.1*get_rand(15),gra_e_shot[4],20,-get_rand(50),0.0,0,0,i);
						}
						for(int i=0;i<1;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.5+0.1*get_rand(5),gra_e_shot[26],20,-get_rand(50),0.0,0,0,i);
						}
					}
					if(cp==110)	Boss.i_hanyou[0] = 1;
					break;
				case 3:
					cp = c % 200;
					if(cp==1)	SPlaySound(19);
					if(cp==20){
						SEn_Make(Boss.x,Boss.y,8,9999,26,-1,-1);					
					}
					if(cp>=40&&cp<60){
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.0+0.1*get_rand(25),gra_e_shot[5],20,get_rand(50),0.0,0,0,i);
						}
						for(int i=0;i<1;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.5+0.1*get_rand(10),gra_e_shot[27],20,get_rand(50),0.0,0,0,i);
						}
					}
					if(cp>=70&&cp<90){
						for(int i=0;i<3;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.0+0.1*get_rand(25),gra_e_shot[4],20,-get_rand(50),0.0,0,0,i);
						}
						for(int i=0;i<1;i++){
							SEs_NWay(Boss.x,Boss.y,0.0,1,1.5+0.1*get_rand(10),gra_e_shot[26],20,-get_rand(50),0.0,0,0,i);
						}
					}
					if(cp==110)	Boss.i_hanyou[0] = 1;
					break;
			}
			if(Boss.i_hanyou[0] == 1){
				int move_x = 60+get_rand(30);
				int move_y = 50+get_rand(40);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,50);			
			}
			Boss.i_hanyou[0] = 0;
		}
	}
	else if(p<=91){//戯符「メンフェンティス降臨」
		if(c>=50){
			c-=50;
			if(c>=10&&c<15)		Boss.img_num = 5;
			else if(c>=15&&c<20)	Boss.img_num = 13;
			else if(c>=20)		Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=20){
				switch(SAVE.Level){
					case 1:
						if(c==100){
							for(int i=0;i<15;i++){
								SEn_Make(20+70*i,20,8,255,24,41,2);					
							}
						}
						if(c<500*1){
							if(c%500==20)	SPlaySound(19);
							if(c%500==70){
								SEn_Make(Boss.x,Boss.y,8,2-((c-70)/500)%2,27,42,2);
							}
						}
						if(c>=100 && c%120==0){
							SEs_NWay(Boss.x,Boss.y,60.0,6,2.0,gra_e_shot[27],30,30.0,0.0,180);
						}
						break;
					case 2:
						if(c==100){
							for(int i=0;i<15;i++){
								SEn_Make(20+70*i,20,8,255,24,41,2);					
							}
						}
						if(c<500*2){
							if(c%500==20)	SPlaySound(19);
							if(c%500==70){
								SEn_Make(Boss.x,Boss.y,8,2-((c-70)/500)%2,27,42,2);
							}
						}
						if(c>=100 && c%60==0){
							SEs_NWay(Boss.x,Boss.y,60.0,6,2.0,gra_e_shot[27],30,30.0,0.0,180);
						}
						break;
					case 3:
						if(c==100){
							for(int i=0;i<15;i++){
								SEn_Make(20+70*i,20,8,255,24,41,2);					
							}
						}
						if(c<500*3){
							if(c%500==20)	SPlaySound(19);
							if(c%500==70){
								SEn_Make(Boss.x,Boss.y,8,2-((c-70)/500)%2,27,42,2);
							}
						}
						if(c>=100 && c%60==0){
							SEs_NWay(Boss.x,Boss.y,36.0,10,2.0,gra_e_shot[27],30,18.0,0.0,180);
						}
						break;
				}
			}
		}	
	}
	else if(p<=94){//魅惑「妖艶黒死蝶」
		if(c>=50){
			c-=50;
			if(c>=10&&c<15)		Boss.img_num = 5;
			else if(c>=15&&c<20)	Boss.img_num = 13;
			else if(c>=20)		Boss.img_num = 21;
			Boss.img_count = 0;
			if(c>=20){
				switch(SAVE.Level){
					int cp;
					case 1:
						cp = c%250;
						if(cp==20){
							for(int i=0;i<10;i++){
								SEs_NWay(Boss.x,Boss.y,72.0,5,1.0,gra_e_shot[22],20,get_rand(71),0.35*i+get_rand(25)*0.01,150,38);
								SEs_NWay(Boss.x,Boss.y,72.0,5,1.0,gra_e_shot[23],20,get_rand(71),0.35*i+get_rand(25)*0.01,150,39);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
					case 2:
						cp = c%250;
						if(cp==20){
							for(int i=0;i<12;i++){
								SEs_NWay(Boss.x,Boss.y,72.0,5,1.5,gra_e_shot[22],20,get_rand(71),0.29*i+get_rand(25)*0.01,150,38);
								SEs_NWay(Boss.x,Boss.y,72.0,5,1.5,gra_e_shot[23],20,get_rand(71),0.29*i+get_rand(25)*0.01,150,39);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
					case 3:
						cp = c%160;
						if(cp==20){
							for(int i=0;i<12;i++){
								SEs_NWay(Boss.x,Boss.y,72.0,5,2.0,gra_e_shot[22],20,get_rand(71),0.29*i+get_rand(25)*0.01,150,38);
								SEs_NWay(Boss.x,Boss.y,72.0,5,2.0,gra_e_shot[23],20,get_rand(71),0.29*i+get_rand(25)*0.01,150,39);
							}
						}
						if(cp==40)	SPlaySound(10);
						break;
				}
			}
		}	
	}
	else if(p<=97){//禁忌「真弾幕結界 -久遠素懐-」
		if(c>=40){
			c-=40;
			if(c>=0&&c<5)		Boss.img_num = 5;
			else if(c>=5&&c<10)	Boss.img_num = 13;
			else if(c>=10)		Boss.img_num = 21;
			Boss.img_count = 0;
			if(c==10){
				SEn_Make(Boss.x,Boss.y,8,9999,28,43,-1);
				SEn_Make(Boss.x,Boss.y,8,9999,29,44,-1);
			}
			if(c==940){
				SEn_Make(Boss.x,Boss.y,8,9999,28,45,-1);
				SEn_Make(Boss.x,Boss.y,8,9999,29,46,-1);
			}
			if(c==1840){
				SEn_Make(Boss.x,Boss.y,8,9999,28,47,-1);
				SEn_Make(Boss.x,Boss.y,8,9999,29,48,-1);
				SEn_Make(Boss.x,Boss.y,8,9999,30,47,-1);
				SEn_Make(Boss.x,Boss.y,8,9999,31,48,-1);
			}
			if(c==2770){
				SEn_Make(Boss.x,Boss.y,8,9999,32,49,-1);
				SEn_Make(Boss.x,Boss.y,8,9999,33,50,-1);
			}
		}	
	}
	else if(p<=100){//境符「幻想大結界」
		if(c>=50){
			c-=50;
			if(c>=20){
				switch(SAVE.Level){
					int cp;
					case 1:
						if(c%12==0){
							SPlaySound(10);
							int loop = 1;
							if(Boss.life<Boss.spell_life*1/3 || Boss.countdown<=20*60)	loop = 3;
							else if(Boss.life<Boss.spell_life*2/3)	loop = 2;
							for(int i=0;i<loop;i++){
								SEs_Make(get_rand(440),CENTER_Y,90.0-2.0+get_rand(4),1.0,gra_e_shot[17],10);
								SEs_Make(get_rand(440),CENTER_Y,-90.0-2.0+get_rand(4),1.0,gra_e_shot[17],10);
							}
						}
						if(c%15==0){
							SPlaySound(10);
							int loop = 4;
							if(Boss.life<Boss.spell_life*1/3 || Boss.countdown<=20*60)	loop = 6;
							else if(Boss.life<Boss.spell_life*2/3)	loop = 5;
							float x = Player.x;
							float y = Player.y;
							Player.x = Boss.x;
							Player.y = Boss.y;
							int num = loop;
							loop = 4;
							for(int i=0;i<4;i++){
								float angle = Radian(360/loop*i,TRUE);
								if(num==4)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,1,1.5,gra_e_shot[23],10,c);
								if(num==5)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,3,1.5,gra_e_shot[23],10,c);
								if(num==6)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,5,1.5,gra_e_shot[23],10,c);
							}
							loop = num;
							if(c>=21){
								if(Boss.i_hanyou[1]!=loop)	SPlaySound(8);
							}
							Boss.i_hanyou[1] = loop;
							Player.x = x;
							Player.y = y;
						}
						break;
					case 2:
						if(c%8==0){
							SPlaySound(10);
							int loop = 1;
							if(Boss.life<Boss.spell_life*1/3 || Boss.countdown<=20*60)	loop = 3;
							else if(Boss.life<Boss.spell_life*2/3)	loop = 2;
							for(int i=0;i<loop;i++){
								SEs_Make(get_rand(440),CENTER_Y,90.0-2.0+get_rand(4),1.0,gra_e_shot[17],10);
								SEs_Make(get_rand(440),CENTER_Y,-90.0-2.0+get_rand(4),1.0,gra_e_shot[17],10);
							}
						}
						if(c%15==0){
							SPlaySound(10);
							int loop = 4;
							if(Boss.life<Boss.spell_life*1/3 || Boss.countdown<=20*60)	loop = 6;
							else if(Boss.life<Boss.spell_life*2/3)	loop = 5;
							float x = Player.x;
							float y = Player.y;
							Player.x = Boss.x;
							Player.y = Boss.y;
							int num = loop;
							loop = 4;
							for(int i=0;i<4;i++){
								float angle = Radian(360/loop*i,TRUE);
								if(num==4)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,1,1.5,gra_e_shot[23],10,c/2);
								if(num==5)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,3,1.5,gra_e_shot[23],10,c/2);
								if(num==6)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,5,1.5,gra_e_shot[23],10,c/2);
							}
							loop = num;
							if(c>=21){
								if(Boss.i_hanyou[1]!=loop)	SPlaySound(8);
							}
							Boss.i_hanyou[1] = loop;
							Player.x = x;
							Player.y = y;
						}
						break;
					case 3:
						if(c%5==0){
							SPlaySound(10);
							int loop = 1;
							if(Boss.life<Boss.spell_life*1/3 || Boss.countdown<=20*60)	loop = 3;
							else if(Boss.life<Boss.spell_life*2/3)	loop = 2;
							for(int i=0;i<loop;i++){
								SEs_Make(get_rand(440),CENTER_Y,90.0-2.0+get_rand(4),1.0,gra_e_shot[17],10);
								SEs_Make(get_rand(440),CENTER_Y,-90.0-2.0+get_rand(4),1.0,gra_e_shot[17],10);
							}
						}
						if(c%15==0){
							SPlaySound(10);
							int loop = 4;
							if(Boss.life<Boss.spell_life*1/3 || Boss.countdown<=20*60)	loop = 6;
							else if(Boss.life<Boss.spell_life*2/3)	loop = 5;
							float x = Player.x;
							float y = Player.y;
							Player.x = Boss.x;
							Player.y = Boss.y;
							for(int i=0;i<loop;i++){
								float angle = Radian(360/loop*i,TRUE);
								if(loop==4)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,1,1.5,gra_e_shot[23],10,c/2);
								if(loop==5)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,3,1.5,gra_e_shot[23],10,c/2);
								if(loop==6)	SEs_NWay(Boss.x+80*cos(angle),Boss.y+80*sin(angle),72.0,5,1.5,gra_e_shot[23],10,c/2);
							}
							if(c>=21){
								if(Boss.i_hanyou[1]!=loop)	SPlaySound(8);
							}
							Boss.i_hanyou[1] = loop;
							Player.x = x;
							Player.y = y;
						}
						break;
				}
			}
		}	
	}
	else if(p<=103){//「終焉と幻想の境界」
		if(c>=50){
			c-=50;
			if(c>=20){
				int num;
				if(Boss.count<780){
					num = 0;
					int pp;
					if(SAVE.Level==1)	pp = 12;
					else if(SAVE.Level==2)	pp = 6;
					else			pp = 4;
					if(c%pp==0){
						SPlaySound(10);
						for(int i=0;i<4;i++){
							for(int a=0;a<4;a++){
								SEs_Make(Boss.x,Boss.y,pow(-1,i)*11.0*c/pp+90*a+22.5*i,1.0+0.2*i,gra_e_shot[23],10,0.0,60,0,i%4+a%4);
							}
						}
					}
				}
				else if(Boss.count<810){
					num = 1;
				}
				else if(Boss.count<2130){
					num = 1;
					int cp = (Boss.count-810)%360;
					if(cp<60&&cp%10==0){
						SPlaySound(10);
						if(cp==0){
							Boss.d_hanyou[0] = get_rand(359);
							if(SAVE.Level==1 || SAVE.Level==2){
								if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 25;
								if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 30;
								if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 32;
								if(Boss.i_hanyou[1]==3)	Boss.i_hanyou[2] = 36;
							}
							else{
								if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 30;
								if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 32;
								if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 36;
								if(Boss.i_hanyou[1]==3)	Boss.i_hanyou[2] = 45;
							}
							Boss.i_hanyou[1] ++;
						}
						for(int i=0;i<Boss.i_hanyou[2];i++){
							for(int a=0;a<2;a++){
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+360.0/(float)Boss.i_hanyou[2]*0.5*(cp%20/10)+Boss.d_hanyou[0],2.0+3.0*a,gra_e_shot[23],10,1.8,100,43,i%100+a%6);
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+360.0/(float)Boss.i_hanyou[2]*0.5*(cp%20/10)+Boss.d_hanyou[0],2.0+3.0*a,gra_e_shot[25],10,1.5,100,43,1);
							}
						}
					}
					else if(cp==150 || cp==210){
						if(SAVE.Level==2){
							if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 30;
							if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 32;
							if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 36;
							if(Boss.i_hanyou[1]==3)	Boss.i_hanyou[2] = 45;
						}
						SPlaySound(10);
						int rand = get_rand(359);
						for(int i=0;i<Boss.i_hanyou[2];i++){
							for(int a=0;a<3;a++){
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.8,100,44,i%100+a%6);
								if(SAVE.Level==3)	SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.5,100,44,1);
							}
						}
					}
					else if(cp==180 || cp==240){
						SPlaySound(10);
						int rand = get_rand(359);
						for(int i=0;i<Boss.i_hanyou[2];i++){
							for(int a=0;a<3;a++){
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.8,100,45,i%100+a%6);
								if(SAVE.Level==3)	SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.5,100,45,1);
							}
						}
					}
					else if(cp>240 && cp%5==0){
						float angle = Radian(get_rand(359),TRUE);
						float d = get_rand(100);
						if(cp%20==5)		SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[0],1);
						else if(cp%20==10)	SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[1],1);
						else			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[3],1);
					}
				}
				else if(Boss.count<2820){
					if(Boss.count==2130){
						Boss.i_hanyou[1] = 0;
					}
					num = 2;
					int cp = (Boss.count-2130)%240;
					if(cp<60&&cp%10==0){
						SPlaySound(10);
						if(cp==0){
							Boss.d_hanyou[0] = get_rand(359);
							if(SAVE.Level==1 || SAVE.Level==2){
								if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 30;
								if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 32;
								if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 36;
							}
							else{
								if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 32;
								if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 36;
								if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 45;
							}
							Boss.i_hanyou[1] ++;
						}
						for(int i=0;i<Boss.i_hanyou[2];i++){
							for(int a=0;a<2;a++){
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+360.0/(float)Boss.i_hanyou[2]*0.5*(cp%20/10)+Boss.d_hanyou[0],2.0+3.0*a,gra_e_shot[23],10,1.8,100,43,i%100+a%6);
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+360.0/(float)Boss.i_hanyou[2]*0.5*(cp%20/10)+Boss.d_hanyou[0],2.0+3.0*a,gra_e_shot[25],10,1.5,100,43,1);
							}
						}
					}
					else if(cp>=150&&cp<=180){
						SPlaySound(11);
						int rand = get_rand(359);
						for(int i=0;i<Boss.i_hanyou[2]/10;i++){
							SEs_Make(get_rand(450),CENTER_Y-150+get_rand(200),-110+get_rand(40),2.0+0.1*get_rand(15),gra_e_shot[22],10,3.0,120,46+get_rand(1),i%20);
						}
					}
					else if(cp>180 && cp%5==0){
						float angle = Radian(get_rand(359),TRUE);
						float d = get_rand(100);
						if(cp%20==5)		SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[0],1);
						else if(cp%20==10)	SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[1],1);
						else			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[3],1);
					}
				}
				else if(Boss.count<3480){
					if(Boss.count==2820){
						Boss.i_hanyou[1] = 0;
					}
					num = 3;
					int cp = (Boss.count-2820)%240;
					if(cp==0){
						Boss.d_hanyou[0] = get_rand(359);
						if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 32;
						if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 36;
						if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 45;
						if(SAVE.Level==1){
							if(Boss.i_hanyou[1]==0)	Boss.i_hanyou[2] = 30;
							if(Boss.i_hanyou[1]==1)	Boss.i_hanyou[2] = 32;
							if(Boss.i_hanyou[1]==2)	Boss.i_hanyou[2] = 36;
						}
						Boss.i_hanyou[1] ++;
					}
					if(cp>=20&&cp<=50){
						SPlaySound(11);
						int rand = get_rand(359);
						for(int i=0;i<Boss.i_hanyou[2]/10;i++){
							SEs_Make(get_rand(450),CENTER_Y-150+get_rand(200),-110+get_rand(40),2.0+0.1*get_rand(15),gra_e_shot[23],10,3.0,120,46+get_rand(1),i%20);
						}
					}
					else if(cp==100 || cp==160){
						SPlaySound(10);
						int rand = get_rand(359);
						for(int i=0;i<Boss.i_hanyou[2];i++){
							for(int a=0;a<3;a++){
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.8,100,44,i%100+a%6);
								if(SAVE.Level==3)	SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.5,100,44,1);
							}
						}
					}
					else if(cp==130 || cp==190){
						SPlaySound(10);
						int rand = get_rand(359);
						for(int i=0;i<Boss.i_hanyou[2];i++){
							for(int a=0;a<3;a++){
								SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.8,100,45,i%100+a%6);
								if(SAVE.Level==3)	SEs_Make(Boss.x,Boss.y,360.0/(float)Boss.i_hanyou[2]*i+rand,2.0+1.5*a,gra_e_shot[22],10,1.5,100,45,1);
							}
						}
					}
					else if(cp>190 && cp%5==0){
						float angle = Radian(get_rand(359),TRUE);
						float d = get_rand(100);
						if(cp%20==5)		SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[0],1);
						else if(cp%20==10)	SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[1],1);
					else			SIt_Make(Boss.x+d*cos(angle),Boss.y+d*sin(angle),270,gra_item[3],1);
					}
				}
				if(Boss.count<3480){}
				else if(Boss.count<3510){
					num = 4;
				}
				else{
					num = 4;
					if(Boss.count==3510){
						Boss.d_hanyou[0] = 0;
						for(int i=0;i<4;i++){
							SEn_Make(Boss.x,Boss.y,8,9999,34+i,51,-1);
						}
					}
				if(Boss.count>=3630 && Boss.countdown>90){
						int pp;
						if(SAVE.Level==1)	pp = 8;
						else if(SAVE.Level==2)	pp = 6;
						else			pp = 5;
						if(c%5==0){
							SPlaySound(10);
							float x1 = Boss.x + 120*cos(Radian(-20,TRUE));
							float y1 = Boss.y + 120*sin(Radian(-20,TRUE));
							float x2 = Boss.x + 120*cos(Radian(200,TRUE));
							float y2 = Boss.y + 120*sin(Radian(200,TRUE));
							float x3 = Boss.x + 120*cos(Radian(50,TRUE));
							float y3 = Boss.y + 120*sin(Radian(50,TRUE));
							float x4 = Boss.x + 120*cos(Radian(130,TRUE));
							float y4 = Boss.y + 120*sin(Radian(130,TRUE));
							if(SAVE.Level==1){
								for(int i=0;i<4;i++){
									SEs_Make(x1,y1,Boss.d_hanyou[0],2.5-0.3*i,gra_e_shot[22],10,0.0,0,0,i%100);
									SEs_Make(x2,y2,180.0-Boss.d_hanyou[0],2.5-0.3*i,gra_e_shot[22],10,0.0,0,0,i%100);
								}
							}
							else if(SAVE.Level==2){
								for(int i=0;i<4;i++){
									SEs_Make(x1,y1,Boss.d_hanyou[0],2.5-0.3*i,gra_e_shot[22],10,0.0,0,0,i%100);
									SEs_Make(x2,y2,180.0-Boss.d_hanyou[0],2.5-0.3*i,gra_e_shot[22],10,0.0,0,0,i%100);
								}
								for(int i=0;i<3;i++){
									SEs_Make(x3,y3,-90-Boss.d_hanyou[0],2.0-0.3*i,gra_e_shot[22],10,0.0,0,0,i%100);
									SEs_Make(x4,y4,-90.0+Boss.d_hanyou[0],2.0-0.3*i,gra_e_shot[22],10,0.0,0,0,i%100);
								}
							}
							else{
								for(int i=0;i<4;i++){
									SEs_Make(x1,y1,Boss.d_hanyou[0],3.0-0.5*i,gra_e_shot[22],10,0.0,0,0,i%100);
									SEs_Make(x2,y2,180.0-Boss.d_hanyou[0],3.0-0.5*i,gra_e_shot[22],10,0.0,0,0,i%100);
								}
								for(int i=0;i<3;i++){
									SEs_Make(x3,y3,-90-Boss.d_hanyou[0],2.5-0.5*i,gra_e_shot[22],10,0.0,0,0,i%100);
									SEs_Make(x4,y4,-90.0+Boss.d_hanyou[0],2.5-0.5*i,gra_e_shot[22],10,0.0,0,0,i%100);
								}
							}
							Boss.d_hanyou[0] += 11;
						}
					}
				}
				if(Boss.i_hanyou[0]!=num){
					SPlaySound(8);
					SBos_DeleteBullet(1);
					if(num==1){
						SBos_MoveTo(CENTER_X,130,30);
					}
					if(num==4){
						SBos_MoveTo(CENTER_X,CENTER_Y-50,30);
					}
				}
				Boss.i_hanyou[0] = num;
			}
		}
	}
	else if(p==104){//審判「ギルティ・オワ・ノットギルティ」
		if(c==1){
			Boss.i_hanyou[0] = 3;
			Boss.d_hanyou[0] = 0;
			Boss.d_hanyou[1] = 25.0;
		}
		if(c>=30){
			c-=30;
			if(c%25==0){
				SPlaySound(10);
				for(int i=0;i<Boss.i_hanyou[0];i++){
					float angle;
					if(Boss.i_hanyou[0]%2==0){
						angle = Boss.d_hanyou[0]-Boss.d_hanyou[1]/2.0;
						if(i%2==0)	angle -= Boss.d_hanyou[1]*(i/2);
						else		angle += Boss.d_hanyou[1]*((i+1)/2);
					}
					else{
						angle = Boss.d_hanyou[0];
						if(i%2==0)	angle -= Boss.d_hanyou[1]*(i/2);
						else		angle += Boss.d_hanyou[1]*((i+1)/2);
					}
					SEs_Make(Boss.x,Boss.y,angle,2.5,gra_e_shot[31],10,0.0,0,0,i%Boss.i_hanyou[0]);
					SEs_Make(Boss.x,Boss.y,angle+180,2.5,gra_e_shot[31],10,0.0,0,0,1);
					SEs_Make(Boss.x,Boss.y,-angle,2.5,gra_e_shot[32],10,0.0,0,0,i%Boss.i_hanyou[0]);
					SEs_Make(Boss.x,Boss.y,-angle+180,2.5,gra_e_shot[32],10,0.0,0,0,1);
				}
				Boss.d_hanyou[0] += 10.0;
			}
			if(c>=120){
				c-=120;
				if(c%240==0){
					SPlaySound(19);
					float angle = Radian(atan2(Player.y-Boss.y,Player.x-Boss.x),FALSE);
					SLas_Make(Boss.x,Boss.y,angle,10.0,gra_laser[1],60,0,0);
					Boss.d_hanyou[2] = Player.x;
					Boss.d_hanyou[3] = Player.y;
					//Boss.i_hanyou[0]++;
				}
				else if(c%240>=60&&c%240<100){
					if(c%240==60)	Boss.i_hanyou[1] = 10;
					if(c%2==0){
						SPlaySound(10);
						float x = Player.x;
						float y = Player.y;
						Player.x = Boss.d_hanyou[2];
						Player.y = Boss.d_hanyou[3];
						SEs_NWay(Boss.x,Boss.y,3.0,Boss.i_hanyou[1],6.0-(c%240-60)*0.05,gra_e_shot[27],10,0.0);	
						Player.x = x;
						Player.y = y;
						//Boss.i_hanyou[1]--;
					}
				}
			}
		}
	}
	else if(p==105){//夢幻「月のいはかさの呪い」
		if(c%10==1){
			SPlaySound(10);
			for(int i=0;i<8;i++){
				SEs_Make(Boss.x,Boss.y,-0.4*c+45*i,2.0,gra_e_shot[17],10,0.0,0,0,i%8);
			}
		}
		if(c%15==1){
			for(int i=0;i<4;i++){
				SEs_Make(Boss.x,Boss.y,0.5*c+90*i+45.0,2.5,gra_e_shot[36],10,0.0,0,8,i%4);
			}
		}
	}
	else if(p==106){//幻影「十王裁判」
		if(c==1){
			SPlaySound(19);
			for(int i=0;i<9;i++){
				SEn_Make(Boss.x,Boss.y,8,9999,42+i,61+i%2,-1);
			}
		}
		if(c>140){
			c-=140;
			if(c%12==0){
				SPlaySound(10);
				for(int i=0;i<3;i++){
					float angle = -175 + 50*i + abs(50-c%100)*1.0;
					SEs_Make(Boss.x,Boss.y,angle,5.0,gra_e_shot[27],5,0.0,0,55,i%3);
				}
			}
			if(c%140==0){
				SEs_NWay(Boss.x,Boss.y,30.0,5,1.5,gra_e_shot[31],10,0.0);	
			}
			c+=140;
		}
	}
	else if(p==107){//夢幻「レーヴァテイン」
		int cp = c%800;
		float angle;
		if(cp==1){
			angle = 190;
			SPlaySound(21);
			for(int i=0;i<6;i++){
				SLas_Make(Boss.x+20*cos(Radian(angle,TRUE)),Boss.y+20*sin(Radian(angle,TRUE)),angle,10.0,gra_laser[0],3*i,1,i%6);
			}
		}
		if(cp==181){
			SBos_MoveTo(limit_x[0]-50,limit_y[0]+50,30);
		}
		if(cp==260){
			angle = 90;
			SPlaySound(21);
			SLas_Make(Boss.x,Boss.y,angle,10.0,gra_laser[0],0,2,0);
		}
		if(cp==320){
			SBos_MoveTo(limit_x[1]+60,limit_y[0]+100,70);
		}
		if(cp>=350&&cp<390){
			Boss.move_x -= 0.1;
			Boss.move_y -= 0.1*Boss.move_y/Boss.move_x;
		}
		if(cp==400){
			SBos_MoveTo(limit_x[1]+20,limit_y[0]+40,20);
		}
		if(cp==420){
			angle = 90;
			SPlaySound(21);
			SLas_Make(Boss.x,Boss.y,angle,10.0,gra_laser[0],0,3,0);
		}
		if(cp==470){
			SBos_MoveTo(limit_x[0]-10,limit_y[0]+40,80);
		}
		if(cp==560){
			SBos_MoveTo(CENTER_X,100,140);
			angle = -10;
			SPlaySound(21);
			for(int i=0;i<6;i++){
				SLas_Make(Boss.x+20*cos(Radian(angle,TRUE)),Boss.y+20*sin(Radian(angle,TRUE)),angle,10.0,gra_laser[0],3*i,4,i%6);
			}
		}
	}
	else if(p==108){//濡衣「フォルス・アキュゼイション」
		if(c==1){
			SPlaySound(11);
			float x = Player.x;
			float y = Player.y;
			Player.x = CENTER_X;
			Player.y = CENTER_Y;
			SEs_NWay(Boss.x,Boss.y,3.0,115,3.0,gra_e_shot[26],10,180.0,0.0,180);	
			Player.x = x;
			Player.y = y;
			Boss.i_hanyou[0] = 1;
		}
		if(c>=100 && (c-100)%100==0){
			SPlaySound(11);
			if((c-100)%200==0&&Boss.i_hanyou[0]<7)	Boss.i_hanyou[0]++;
			float x = Player.x;
			float y = Player.y;
			Player.x = CENTER_X-100+get_rand(200);
			Player.y = CENTER_Y+100+get_rand(100);
			for(int i=0;i<Boss.i_hanyou[0];i++){
				float bx = CENTER_X-150+get_rand(300);
				float by = CENTER_Y-100+get_rand(100);
				SEs_NWay(bx,by,3.0,115,3.0,gra_e_shot[26+get_rand(1)],10,180.0,0.0,180);	
			}
			Player.x = x;
			Player.y = y;
		}
	}
	else if(p==109){//夢幻「蛙は口ゆえ蛇に呑まるる」
		int cp = c % 630;
		if(c!=0&&cp%4==0){
			SPlaySound(10);
			float x,y,length,angle;
			if(cp<300){
				length = ((float)cp/300.0)*310.0;
				angle = Radian((float)cp/90.0*360.0 ,TRUE);
				x = Boss.x + length * cos(angle);
				y = Boss.y + length * sin(angle);
				for(int i=0;i<3;i++){
					float an = Radian(get_rand(359),TRUE);
					float sx = x + get_rand(40)*cos(an);
					float sy = y + get_rand(40)*sin(an);
					float an2 = get_rand(359);
					for(int a=0;a<3;a++){
						SEs_Make(sx,sy,an2+60*a,0.0,gra_e_shot[17],10,0.0,0,9,a%3);
					}
				}
			}
			else{
				length = ((float)(cp-300)/330.0)*300.0;
				angle = Radian(-(float)(cp-300)/90.0*360.0 ,TRUE);
				x = Boss.x + length * cos(angle);
				y = Boss.y + length * sin(angle);
				for(int i=0;i<3;i++){
					float an = Radian(get_rand(359),TRUE);
					float sx = x + get_rand(30)*cos(an);
					float sy = y + get_rand(30)*sin(an);
					float an2 = get_rand(359);
					for(int a=0;a<3;a++){
						SEs_Make(sx,sy,an2+60*a,0.0,gra_e_shot[52],10,0.0,0,9,a%3);
					}
				}
			}
		}
	}
	else if(p==110){//鬼人「小野篁の呪い」
		c -= 1;
		int cp;
		if(c>=0)	cp = c%340;
		if(c==-1){
			Boss.i_hanyou[0] = 0;
		}
		else if(cp<170){
			if(cp==0)	SPlaySound(19);
			if(cp<4*12){
				if(cp%4==0){
					float angle = -90.0 + 30.0*cp/4 + 15.0;
					SLas_Make(Boss.x+10*cos(Radian(angle,TRUE)),Boss.y+10*sin(Radian(angle,TRUE)),angle,10.0,gra_laser[0],120,0);
				}
			}
			else if(cp<100){
				if(cp%2==0){
					SPlaySound(10);
					float angle = Radian( 30*(Boss.i_hanyou[0]%2) , TRUE);
					float x = Player.x;
					float y = Player.y;
					Player.x = Boss.x + 60*cos(angle);
					Player.y = Boss.y + 60*sin(angle);
					for(int i=0;i<6;i++){
						SEs_NWay(Boss.x,Boss.y,3.0,10,6.0,gra_e_shot[26],10,60.0*i,0.0,120,0,i);	
					}
					Player.x = x;
					Player.y = y;
				}
			}
			else if(cp==140){
				SPlaySound(10);
				int num = 8 + Boss.i_hanyou[0];
				float angle = 360.0 / (float)num;
				int plus = get_rand(angle);
				for(int i=0;i<3;i++){
					SEs_NWay(Boss.x,Boss.y,angle,num,3.0-0.5*i,gra_e_shot[32],20,plus,0.0,60);
				}
			}
		}
		else{
			cp -= 170;
			if(cp==0)	SPlaySound(19);
			if(cp<4*12){
				if(cp%4==0){
					float angle = -90.0 - 30.0*cp/4;
					SLas_Make(Boss.x+10*cos(Radian(angle,TRUE)),Boss.y+10*sin(Radian(angle,TRUE)),angle,10.0,gra_laser[1],120,0);
				}
			}
			else if(cp<100){
				if(cp%2==0){
					SPlaySound(10);
					float angle = Radian( -15 + 30*(Boss.i_hanyou[0]%2) , TRUE);
					float x = Player.x;
					float y = Player.y;
					Player.x = Boss.x + 60*cos(angle);
					Player.y = Boss.y + 60*sin(angle);
					for(int i=0;i<6;i++){
						SEs_NWay(Boss.x,Boss.y,3.0,10,6.0,gra_e_shot[27],10,60.0*i,0.0,120,0,i);	
					}
					Player.x = x;
					Player.y = y;
				}
			}
			else if(cp==140){
				SPlaySound(10);
				int num = 8 + Boss.i_hanyou[0];
				float angle = 360.0 / (float)num;
				int plus = get_rand(angle);
				for(int i=0;i<3;i++){
					SEs_NWay(Boss.x,Boss.y,angle,num,3.0-0.5*i,gra_e_shot[32],20,plus,0.0,60);
				}
				Boss.i_hanyou[0]++;
			}
		}
	}
	else if(p==111){//夢幻「ストレートとカーブの夢郷」
		if(c==0){
			Boss.defence = 100;
			Boss.i_hanyou[0] = 120;
		}
		if(c==60){
			Boss.defence = Spell[p].defence;
		}
		if(c>0){
			int cp1 = 5;
			if(c%cp1==1){
				SPlaySound(10);
				for(int i=0;i<6;i++){
					SEs_Make(Boss.x,Boss.y,-25+10*i,6.0,gra_e_shot[48],10,150.0-35*i,0,10,i%6);
					SEs_Make(Boss.x,Boss.y,205-10*i,6.0,gra_e_shot[48],10,150.0-35*i,0,11,i%6);
				}
			}
			if(c%Boss.i_hanyou[0]==0){
				for(int i=0;i<6;i++){
					SEs_Make(Boss.x,Boss.y,-70+25*i,4.5,gra_e_shot[31],30,0.0,0,12,i%6);
					SEs_Make(Boss.x,Boss.y,110+25*i,4.5,gra_e_shot[31],30,0.0,0,13,1);
				}
				SLas_Make(Boss.x,Boss.y,20*(Boss.i_hanyou[1]%4),12.0,gra_laser[1],10,5,0);
				SLas_Make(Boss.x,Boss.y,180-20*(Boss.i_hanyou[1]%4),12.0,gra_laser[1],10,5,1);
				Boss.i_hanyou[1] ++;
				if(Boss.life<Spell[p].life/6||Boss.countdown<60*12)		Boss.i_hanyou[0] = 30;
				else if(Boss.life<Spell[p].life*2/3)	Boss.i_hanyou[0] = 60;
				int move_x = 50+get_rand(20);
				int move_y = 50+get_rand(50);
				if(Player.x<Boss.x){
					if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
					else				move_x = Boss.x - move_x;
				}
				else{
					if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
					else				move_x = Boss.x + move_x;
				}
				SBos_MoveTo(move_x,move_y,90);
			}
		}
	}
	else if(p==112){//神判「トゥルダクの盟神探湯」
		if(c>=30){
			c -= 30;
			if(c<1000){
				if(c==0){
					Boss.d_hanyou[0] = 0;//迫ってくる青弾の変位値
					Boss.flash = 0;
					Boss.b_atari = false;
				}
				if(c<650)	Boss.d_hanyou[0] += 0.4;
				if(c%1==0){
					float x = Boss.d_hanyou[0]+get_rand(40);
					float speed = x / 30.0;
					float accel = x / 1800.0;
					for(int i=0;i<8;i++){
						SEs_Make(CENTER_X*2,get_rand(480),180.0,speed,gra_e_shot[27],10,accel,0,54);
					}	
				}
				if(c%3==0){
					SPlaySound(10);
					SEs_Make(0,get_rand(CENTER_Y*2),0.0,1.0,gra_e_shot[53],10);
				}
			}
			else if(c==1000){
				SBos_DeleteBullet(0);
				Boss.d_hanyou[0] = 0;
			}
			else if(c<2000){
				c-=1000;
				if(c<650)	Boss.d_hanyou[0] += 0.4;
				if(c%1==0){
					float x = Boss.d_hanyou[0]+get_rand(40);
					float speed = x / 30.0;
					float accel = x / 1800.0;
					for(int i=0;i<8;i++){
						SEs_Make(0,get_rand(480),0.0,speed,gra_e_shot[27],10,accel,0,54);
					}	
				}
				if(c%3==0){
					SPlaySound(10);
					SEs_Make(CENTER_X*2,get_rand(CENTER_Y*2),180.0,1.0,gra_e_shot[53],10);
				}
			}
			else if(c==2000){
				SBos_DeleteBullet(0);
				Boss.d_hanyou[0] = 0;
			}
			else if(c<3000){
				c-=2000;
				if(c<650)	Boss.d_hanyou[0] += 0.5;
				if(c%1==0){
					float x = Boss.d_hanyou[0]+get_rand(40);
					float speed = x / 30.0;
					float accel = x / 1800.0;
					for(int i=0;i<8;i++){
						SEs_Make(get_rand(CENTER_X*2),CENTER_Y*2,270.0,speed,gra_e_shot[27],10,accel,0,54);
					}	
				}
				if(c%3==0){
					SPlaySound(10);
					SEs_Make(get_rand(CENTER_X*2),0,90.0,1.0,gra_e_shot[53],10);
				}
			}
			else if(c==3000){
				SBos_DeleteBullet(0);
				Boss.d_hanyou[0] = 0;
			}
			else if(c<4000){
				c-=3000;
				if(c<650)	Boss.d_hanyou[0] += 0.5;
				if(c%1==0){
					float x = Boss.d_hanyou[0]+get_rand(40);
					float speed = x / 30.0;
					float accel = x / 1800.0;
					for(int i=0;i<8;i++){
						SEs_Make(get_rand(CENTER_X*2),0,90.0,speed,gra_e_shot[27],10,accel,0,54);
					}	
				}
				if(c%3==0){
					SPlaySound(10);
					SEs_Make(get_rand(CENTER_X*2),CENTER_Y*2,270.0,1.0,gra_e_shot[53],10);
				}
			}
			else if(c==4000){
				SBos_DeleteBullet(0);
				Boss.d_hanyou[0] = 0;
			}
			else{
				c-=4000;
				if(c<1000)	Boss.d_hanyou[0] += 0.15;
				if(c%1==0){
					float x = Boss.d_hanyou[0]+get_rand(40);
					float speed = x / 30.0;
					float accel = x / 1800.0;
					for(int i=0;i<3;i++){
						SEs_Make(get_rand(CENTER_X*2),0,90.0,speed,gra_e_shot[27],10,accel,0,54);
						SEs_Make(get_rand(CENTER_X*2),CENTER_Y*2,270.0,speed,gra_e_shot[27],10,accel,0,54);
					}	
					x *= 0.89;
					speed = x / 30.0;
					accel = x / 1800.0;
					for(int i=0;i<3;i++){
						SEs_Make(CENTER_X*2,get_rand(480),180.0,speed,gra_e_shot[27],10,accel,0,54);
						SEs_Make(0,get_rand(480),0.0,speed,gra_e_shot[27],10,accel,0,54);
					}	
				}
				if(c%16==0){
					SPlaySound(10);
					SEs_Make(get_rand(CENTER_X*2),0,90.0,1.0,gra_e_shot[53],10);
				}
				else if(c%16==4){
					SPlaySound(10);
					SEs_Make(0,get_rand(CENTER_Y*2),0.0,1.0,gra_e_shot[53],10);
				}
				else if(c%16==8){
					SPlaySound(10);
					SEs_Make(get_rand(CENTER_X*2),CENTER_Y*2,270.0,1.0,gra_e_shot[53],10);				
				}
				else if(c%16==12){
					SPlaySound(10);
					SEs_Make(CENTER_X*2,get_rand(CENTER_Y*2),180.0,1.0,gra_e_shot[53],10);
				}
			}
		}
	}
	else if(p==113){//夢終「エンドオブジャッジメント」
		if(c>=70){
			Boss.i_hanyou[6] = 1;
			c -= 70;
			float x[4],y[4];
			x[0] = Boss.x + 100*cos(Radian(-20,TRUE));
			y[0] = Boss.y + 100*sin(Radian(-20,TRUE));
			x[1] = Boss.x + 100*cos(Radian(200,TRUE));
			y[1] = Boss.y + 100*sin(Radian(200,TRUE));
			x[2] = Boss.x + 150*cos(Radian(30,TRUE));
			y[2] = Boss.y + 150*sin(Radian(30,TRUE));
			x[3] = Boss.x + 150*cos(Radian(150,TRUE));
			y[3] = Boss.y + 150*sin(Radian(150,TRUE));
			if(c==0){
				Boss.d_hanyou[0] = 0;
				for(int i=0;i<4;i++){
					SEn_Make(Boss.x,Boss.y,8,9999,51+i,63+i,-1);
				}
			}
			else if(c==150){
				SPlaySound(19);
				for(int i=0;i<4;i++){
					SLas_Make(x[i],y[i],90.0,6.0,gra_laser[0],90);			
				}
			}
			else if(c>=230&&c<300){
				SShake(0,5);
				if(c==230){
					SBos_MoveTo(CENTER_X,CENTER_Y-100,70);				
				}
				if(c%1==0){
					SPlaySound(10);
					for(int i=0;i<4;i++){
						SEs_Make(x[i],y[i],90.0,8.0,gra_e_shot[26],10);
						SEs_Make(x[i]-8.0,y[i],90.0,8.0,gra_e_shot[26],10);
						SEs_Make(x[i]+8.0,y[i],90.0,8.0,gra_e_shot[26],10);
						SEs_Make(x[i]-16.0,y[i],90.0,8.0,gra_e_shot[26],10);
						SEs_Make(x[i]+16.0,y[i],90.0,8.0,gra_e_shot[26],10);
					}
				}					
			}
			if(c>=240&&c<360){
				if(c%3==0){
					SPlaySound(10);
					float angle[2];
					angle[0] = 120.0 - 0.5*(c-240);
					angle[1] = 0.25*(c-240);
					for(int i=0;i<4;i++){
						int a = 0;
						if(i>=2)	a = 1;
						SEs_Make(x[i],y[i],90.0-angle[a],6.0,gra_e_shot[19],0);
						SEs_Make(x[i],y[i],90.0+angle[a],6.0,gra_e_shot[19],0);
					}
				}
			}
			else if(c>=360){
				Boss.defence = Spell[p].defence;
				if(c%3==0){
					SPlaySound(10);
					float angle[4];
					angle[0] = 67.5 - 0.25*fabs(60 - (c-330)%120);
					angle[1] = 52.5 + 0.25*fabs(60 - (c-330)%120);
					angle[2] = 22.5 + 0.25*fabs(60 - (c-330)%120);
					angle[3] = 37.5 - 0.25*fabs(60 - (c-330)%120);
					for(int i=0;i<4-Boss.i_hanyou[0];i++){
						float base = 90.0+angle[i];
						float plus = 60.0;
						if(i>=2)	plus = 30.0;
						for(int a=0;a<3;a++){
							SEs_Make(x[i],y[i],base-plus*a,6.0,gra_e_shot[19],0);
						}
					}
				}
				if(c%120==60){
					SEs_NWay(Boss.x,Boss.y,50.0,3,2.0,gra_e_shot[31],20,0.0);
				}
				if(Boss.life<Spell[p].life*4/5 || Boss.countdown<=30*60)	Boss.i_hanyou[0] = 1;
				if(Boss.life<Spell[p].life*3/5 || Boss.countdown<=30*60)	Boss.i_hanyou[0] = 2;
				if(Boss.life<Spell[p].life*2/5 || Boss.countdown<=30*60)	Boss.i_hanyou[0] = 3;
				if(Boss.life<Spell[p].life*1/5 || Boss.countdown<=30*60)	Boss.i_hanyou[0] = 4;
				if(Boss.life<Spell[p].life*1/5 || Boss.countdown<=30*60){
					if(c%3==0){
						SPlaySound(10);
						SEs_Make(CENTER_X-200+get_rand(400),CENTER_Y-50-get_rand(150),90.0,1.5+0.1*get_rand(10),gra_e_shot[27],10);
					}
					if(Boss.i_hanyou[2]%180==0){
						int rand = get_rand(14);
						SEs_NWay(Boss.x,Boss.y,15.0,24,1.8,gra_e_shot[52],20,rand,0.0,0,60,0);
						SEs_NWay(Boss.x,Boss.y,15.0,24,1.8,gra_e_shot[52],20,rand,0.0,0,61,1);
						SEs_NWay(Boss.x,Boss.y,15.0,24,1.5,gra_e_shot[52],20,rand,0.0,0,60,1);
						SEs_NWay(Boss.x,Boss.y,15.0,24,1.5,gra_e_shot[52],20,rand,0.0,0,61,1);
					}
					Boss.i_hanyou[2]++;
				}
				else if(Boss.life<Spell[p].life*3/5 || Boss.countdown<=30*60){
					if(Boss.i_hanyou[2]%180==0){
						int rand = get_rand(14);
						SEs_NWay(Boss.x,Boss.y,18.0,20,1.8,gra_e_shot[52],20,rand,0.0,0,60,0);
						SEs_NWay(Boss.x,Boss.y,18.0,20,1.8,gra_e_shot[52],20,rand,0.0,0,61,1);
						SEs_NWay(Boss.x,Boss.y,18.0,20,1.5,gra_e_shot[52],20,rand,0.0,0,60,1);
						SEs_NWay(Boss.x,Boss.y,18.0,20,1.5,gra_e_shot[52],20,rand,0.0,0,61,1);
						for(int i=0;i<4-Boss.i_hanyou[0];i++){
							int rand = get_rand(17);
							SEs_NWay(x[i],y[i],18.0,20,1.8,gra_e_shot[52],20,rand,0.0,0,60,0);
							SEs_NWay(x[i],y[i],18.0,20,1.8,gra_e_shot[52],20,rand,0.0,0,61,1);
							SEs_NWay(x[i],y[i],18.0,20,1.5,gra_e_shot[52],20,rand,0.0,0,60,1);
							SEs_NWay(x[i],y[i],18.0,20,1.5,gra_e_shot[52],20,rand,0.0,0,61,1);
						}
						
					}
					Boss.i_hanyou[2]++;
				}
			}
			if(Boss.i_hanyou[0]!=Boss.i_hanyou[1]){
				Boss.i_hanyou[1] = Boss.i_hanyou[0];
				SPlaySound(8);
			}
		}
	}
	/*
	else if(p==124){//境符「アンリミテッドペナンス」
		//if(E_Shot.size()>400)	frame = 50;
		//else			frame = 60;
		if(c==0){
			Boss.i_hanyou[0] = 0;
			Boss.i_hanyou[1] = 0;
		}
		if(c>0){
			c = Boss.i_hanyou[0];
			int pat = Boss.i_hanyou[1];
			if(Boss.life>Boss.spell_life*12/16){
				if(pat==0){
					if(c==0)	SBos_MoveTo(CENTER_X,CENTER_Y-100,30);
					if(c==30)	SPlaySound(19);
					if(c<90)	c = 0;
					c-=90;
					if(c<=30){
						Boss.d_hanyou[0] = 0;//角度の変位（カウント）
						Boss.d_hanyou[1] = 22.5;//角度プラス分
					}
					else{
						Boss.d_hanyou[1] += 10*sin(Radian(Boss.d_hanyou[0],TRUE));
						Boss.d_hanyou[0]++; 
					}
					if(c>0&&c%1==0){
						SPlaySound(10);
						for(int i=0;i<8;i++){
							float angle = 45*i+Boss.d_hanyou[1];
							SEs_Make(Boss.x+15*cos(Radian(angle,TRUE)),Boss.y+15*sin(Radian(angle,TRUE)),angle,6.0,gra_e_shot[15],20);
						}
					}
					if(c==500)	Boss.i_hanyou[1] = 1;
				}
				else if(pat==1){
					if(c==30)	SPlaySound(19);
					if(c<90)	c = 0;
					c-=90;
					if(c%10==1){
						SPlaySound(10);
						SEs_NWay(Boss.x,Boss.y,9.0,7,7.0,gra_e_shot[5],20,0);
					}
					if(c%9==1){
						SPlaySound(10);
						for(int i=0;i<18;i++){
							float angle = 5+10*i;
							SEs_Make(Boss.x+15*cos(Radian(angle,TRUE)),Boss.y+15*sin(Radian(angle,TRUE)),angle,5.0,gra_e_shot[4],20);
						}
						//SEs_NWay(Boss.x,Boss.y,9.0,14,4.0,gra_e_shot[4],20,0);
					}
					if(c==300)	Boss.i_hanyou[1] = 2;		
				}
				else if(pat==2){
					if(c==30)	SPlaySound(19);
					if(c<90)	c = 0;
					c-=90;
					if(c%5==1){
						SPlaySound(10);
						float angle = Radian(get_rand(359),TRUE);
						float d = 70 + get_rand(100);
						for(int i=0;i<3;i++){
							SEs_NWay(CENTER_X+d*cos(angle),100+d/2*sin(angle),72.0,5,6.0-1.0*i,gra_e_shot[15],20,0,10.0,0);
						}
					}
					if(c%20==1){
						SPlaySound(10);
						for(int i=0;i<12;i++){
							float angle = 30.0*i+15.0;
							for(int a=0;a<3;a++){
								SEs_Make(Boss.x+15*cos(Radian(angle,TRUE)),Boss.y+15*sin(Radian(angle,TRUE)),angle,6.0-1.5*a,gra_e_shot[4],30);
							}
							SEs_Make(Boss.x,Boss.y,0,0.0,gra_e_shot[26],30,0.0,0,-1);
						}
						//SEs_NWay(Boss.x,Boss.y,9.0,14,4.0,gra_e_shot[4],20,0);
					}
					if(c%30==1&&c!=1){
						int move_x = 50+get_rand(30);
						int move_y = 120+get_rand(60);
						if(Player.x<Boss.x){
							if(Boss.x-move_x<limit_x[0])	move_x = Boss.x + move_x;
							else				move_x = Boss.x - move_x;
						}
						else{
							if(Boss.x+move_x>limit_x[1])	move_x = Boss.x - move_x;
							else				move_x = Boss.x + move_x;
						}
						SBos_MoveTo(move_x,move_y,30);
					}
					if(c==300)	Boss.i_hanyou[1] = 0;		
				}
			}
			else{
				//発狂モード
				if(pat!=10){
					SPlaySound(12); 
					Boss.i_hanyou[1] = 10;
					Boss.i_hanyou[0] = 0;
					Boss.i_hanyou[2] = 0;
					for(list<E_SHOTDATA>::iterator it=E_Shot.begin();it!=E_Shot.end();it++){
						SEf_Make((*it).x,(*it).y,2,(*it).img);
						SIt_Make((*it).x,(*it).y,270,gra_item[3],1);
						it = E_Shot.erase(it);
						it--;
						continue;
					}
					for(int i=0;i<60;i++){
						SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[0]);
					}
					for(int i=0;i<10;i++){
						SIt_Make(Boss.x-Boss.img_x/4+get_rand(Boss.img_x/2),Boss.y-Boss.img_y/4+get_rand(Boss.img_y/2),270,gra_item[1]);
					}
				}
				c = Boss.i_hanyou[0];
				if(c==150)	SBos_MoveTo(CENTER_X,CENTER_Y,30);
				if(c==180)	SPlaySound(19);
				if(c>210){
					if(c%14==1){
						SPlaySound(10);
						if(Boss.life<Boss.spell_life*3/16){
							if(Boss.i_hanyou[2]==0){
								SPlaySound(19);
							}
							SEs_NWay(Boss.x,Boss.y,10.0,16,1.8,gra_e_shot[18],20,180.0+8*Boss.i_hanyou[2]);
							SEs_NWay(Boss.x,Boss.y,6.0,60,1.0,gra_e_shot[19],20,get_rand(5));
							Boss.i_hanyou[2]++;
						}
                                        	else{
							SEs_NWay(Boss.x,Boss.y,10.0,16,1.8,gra_e_shot[18],20,180.0);
							SEs_NWay(Boss.x,Boss.y,6.0,60,1.0,gra_e_shot[19],20,get_rand(5));
						}
					}
				}
			}
			Boss.i_hanyou[0]++;
			if(pat!=Boss.i_hanyou[1]){
				Boss.i_hanyou[0] = 0;
			}
		}
	}
	*/
	return;
}

void SSp_Draw(){
	if(Game.spell_count>0){
		int x,y;
		if(Game.spell_count==1){
			SPlaySound(17);
			Game.spell_bonus = 1000000*Game.stage + 500000*SAVE.Level + 70*Game.stage*(SAVE.Level+1)*Game.graze;
			Game.spell_bonus_rate = Game.spell_bonus/10 / Boss.countdown;
			Game.spell_bonus_rate *= 10;
			Game.spell_bonus_ratecount = 0;
			if(PlayerControlFlag==0)	SAVE.Spell[Boss.spell_num].challenge_times[SAVE.Chara][SAVE.Weapon] ++;
		}
		if(Game.spell_count<20){
			int size = GetDrawFormatStringWidthToHandle(SpellFont,Spell[Boss.spell_num].name);
			x = 400-size;
			y = 400;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
			//DrawBox(x,y,x+size,y+15,GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*Game.spell_count);
			DrawFormatStringToHandle(x,y,GetColor(255,255,255),SpellFont,Spell[Boss.spell_num].name);
		}
		else if(Game.spell_count<70){
			int size = GetDrawFormatStringWidthToHandle(SpellFont,Spell[Boss.spell_num].name);
			x = 400-size;
			y = 400;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
			//DrawBox(x,y,x+size,y+15,GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawFormatStringToHandle(x,y,GetColor(255,255,255),SpellFont,Spell[Boss.spell_num].name);
		}
		else if(Game.spell_count<100){
			int size = GetDrawFormatStringWidthToHandle(SpellFont,Spell[Boss.spell_num].name);
			x = 400-size;
			y = 400-12*(Game.spell_count-70);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
			//DrawBox(x,y,x+size,y+15,GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawFormatStringToHandle(x,y,GetColor(255,255,255),SpellFont,Spell[Boss.spell_num].name);
		}
		else{
			int size = GetDrawFormatStringWidthToHandle(SpellFont,Spell[Boss.spell_num].name);
			x = 400-size;
			y = 40;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
			//DrawBox(x,y,x+size,y+15,GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(Player.y<y+80&&Player.x>380-size)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
			for(int i=0;i<11;i++){
				DrawBox(400-size+10*i,55,400,58,GetColor(255,25.5*i,25.5*i),TRUE);
			}
			DrawFormatStringToHandle(x,y,GetColor(255,255,255),SpellFont,Spell[Boss.spell_num].name);
			size = GetDrawFormatStringWidthToHandle(SpellBonusFont,"Bonus    failed History 999/999");
			if(Game.spell_getflag==0)	DrawFormatStringToHandle(400-size,60,GetColor(255,255,255),SpellBonusFont,"Bonus %08d History %02d/%02d",Game.spell_bonus,SAVE.Spell[Boss.spell_num].get_times[SAVE.Chara][SAVE.Weapon],SAVE.Spell[Boss.spell_num].challenge_times[SAVE.Chara][SAVE.Weapon]);
			else				DrawFormatStringToHandle(400-size,60,GetColor(255,255,255),SpellBonusFont,"Bonus    failed History %02d/%02d",SAVE.Spell[Boss.spell_num].get_times[SAVE.Chara][SAVE.Weapon],SAVE.Spell[Boss.spell_num].challenge_times[SAVE.Chara][SAVE.Weapon]);
		}
		
		if((Boss.spell_num>=71&&Boss.spell_num<=73) || (Boss.spell_num>=95&&Boss.spell_num<=97) || (Boss.spell_num>=101&&Boss.spell_num<=103) || (Boss.spell_num==112)){
			Game.spell_bonus = 1000000*Game.stage + 500000*SAVE.Level + 70*Game.stage*(SAVE.Level+1)*Game.graze;
			if(Boss.countdown==2){
				Boss.life = 0;
				Boss.count = 0;
				Boss.countdown = 3;
			}
		}
		else{
			Game.spell_bonus = 1000000*Game.stage + 500000*SAVE.Level + 70*Game.stage*(SAVE.Level+1)*Game.graze - Game.spell_bonus_rate*Game.spell_bonus_ratecount;
		}
		if(Game.spell_count>250){
			Game.spell_bonus_ratecount++;
		}
		if(Game.spell_getflag!=0)	Game.spell_bonus = 0;
		Game.spell_count ++;
		if(Game.spell_bonus>99999990)	Game.spell_bonus = 99999990;
	}
	return;
}

void SIt_Load(){
	try{
		char fi[128];
		for(int i=0;i<GRA_ITEM_NUM;i++){
			wsprintf(fi , "data/img/item/%d.png" , i+1);
			SetTransColor(0,0,0);
			if( (gra_item[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SIt_Reset(){
	Item.clear();
	return;
}

void SIt_Main(){
	for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
		SIt_Move(it);
		if(Player.y<130&&Player.miss==0){
			(*it).pattern = 1; 
		}
		if((*it).x<0-(*it).img_x/2 || (*it).x>450+(*it).img_x/2 || (*it).y>480+(*it).img_y/2){
			it = Item.erase(it);
			it--;
			continue;
		}
		if(Game.power==80&&((*it).img==gra_item[0]||(*it).img==gra_item[2])){
			if((*it).pattern==1)	(*it).pattern = 3;
			SIt_Make((*it).x,(*it).y,270,gra_item[4],(*it).pattern);
			it = Item.erase(it);
			it--;
			continue;
		}
	}
	
	return;
}

void SIt_Draw(){
	for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle, (*it).img, TRUE, FALSE);
		(*it).count++;
		if(Player.atari_x[0]<(*it).atari_x[1] &&
		   Player.atari_x[1]>(*it).atari_x[0] &&
		   Player.atari_y[0]<(*it).atari_y[1] &&
		   Player.atari_y[1]>(*it).atari_y[0]){
			if(Player.miss==0){
				SPlaySound(1);
				if((*it).img==gra_item[0]){
					if(Game.power<80) Game.power ++; 
				}
				else if((*it).img==gra_item[1]){
					Game.point ++;
					Game.stage_point[Game.stage]++;
					int point = Game.maxpoint/10;
					float bai = 140 / Player.y;
					if(bai>=1.00){
						bai=1;
					}
					point = point*bai;
					point *= 10;
					if(Game.power==80)	point *= 2;
					SSc_AddScore(point);
					int color = GetColor(255,255,255);
					if(bai==1)	color = GetColor(255,255,100);
					if(bai==1&&Game.power==80)	color = GetColor(255,0,0);
					SEf_Make((*it).x,(*it).y,3,point,color);
					if(Game.point==Game.nextpoint){
						SPlaySound(20);
						if(Player.life<9){
							Player.life ++;
						}
						Game.extend_count = 1;
					}
				}
				else if((*it).img==gra_item[2]){
					Game.power += 20;
					if(Game.power>80) Game.power = 80; 
				}
				else if((*it).img==gra_item[3]){
					int point;
					switch(SAVE.Level){
						case 0:	point = 500;	break;
						case 1:	point = 500;	break;
						case 2:	point = 500;	break;
						case 3:	point = 500;	break;
						case 4:	point = 750;	break;
					}
					if(Game.stage>3)	point *= 2;
					Game.maxpoint += point;
					int color = GetColor(50,255,50);
					SEf_Make((*it).x,(*it).y,3,point,color);
				}
				else if((*it).img==gra_item[4]&&(*it).i_hanyou[7]==1){
					Game.maxpoint += 10;
				}
				else if((*it).img==gra_item[4]){
					Game.maxpoint += 100;
					int color = GetColor(200,255,200);
					SEf_Make((*it).x,(*it).y,3,100,color);
				}
				else if((*it).img==gra_item[5]){
					SPlaySound(20);
					if(Player.life<9){
						Player.life ++;
					}
					Game.extend_count = 1;
				}
				if(Game.maxpoint>9999990)	Game.maxpoint = 9999990;
				it = Item.erase(it);
				it--;
				continue;
			}
		}
		if((*it).pattern!=1&&(*it).pattern!=3&&Player.b_slow==true&&Player.miss==0){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			if(sq<70){
				(*it).pattern = 3;
				(*it).count = 100;
			}
		}
		else if((*it).pattern!=1&&(*it).pattern!=3&&Player.b_slow==false&&Player.miss==0){
			float sx = Player.x - (*it).x;
			float sy = Player.y - (*it).y;
			float sq = sqrt(sx*sx+sy*sy);
			if(sq<40){
				(*it).pattern = 3;
				(*it).count = 100;
			}
		}
	}
	
	return;
}

void SIt_Make(float x,float y,float angle,int img,int num){
	if(Item.size()==5012)	return;
	ITEMDATA P;
	P.x = x;
	P.y = y;
	for(int i=0;i<ATARI_NUM;i++){
		P.atari_x[i] = x;
		P.atari_y[i] = y;
	}
	P.move_x = cos(Radian(angle,TRUE));
	P.move_y = sin(Radian(angle,TRUE));
	P.img = img;
	P.pattern = num;
	P.flash = 255;
	P.count = 0;
	GetGraphSize(P.img,&P.img_x,&P.img_y);
	for(int i=0;i<8;i++){
		P.i_hanyou[i] = 0;
		P.d_hanyou[i] = 0;
	}
	P.i_hanyou[7] = num;//numが1かつimgが緑（小）なら敵弾からの変化
			    //numが2ならプレイヤー死亡時のアイテム
			    //3なら自動回収中の赤アイテム
	if(num==3){
		P.i_hanyou[7] = 0;
		P.pattern = 1;
	}
	
	Item.push_back(P);
	return;
}

void SIt_Move(list<ITEMDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	int g = (*it).img;
	
	if(c<20){
		(*it).large = 0.5 + 0.025 * c;
		(*it).angle = 54 * c;
	}
	else{
		(*it).large = 1.0;
		(*it).angle = 0;
	}
	if(p==0){
		if(c==0||c==1){
			(*it).speed = 2.0;
			(*it).d_hanyou[0] = (*it).speed / 60.0;
		}
		(*it).speed -= (*it).d_hanyou[0];
		if((*it).speed<0&&(*it).i_hanyou[0]==0){
			(*it).move_x = 0;
			(*it).move_y = -1;
			(*it).i_hanyou[0] = 1;
		}
		if((*it).speed<-1.5)	(*it).speed = -1.5;
	}
	else if(p==1){
		if(SAVE.Chara==0)	(*it).speed = 6.0;
		else			(*it).speed = 7.0;
		float sx = Player.x - (*it).x;
		float sy = Player.y - (*it).y;
		float sq = sqrt(sx*sx+sy*sy);
		(*it).move_x = sx/sq;
		(*it).move_y = sy/sq;
	}
	else if(p==2){
		if(c==1){
			(*it).speed = 6.0;
			(*it).d_hanyou[0] = (*it).speed / 60.0;
		}
		(*it).speed -= (*it).d_hanyou[0];
		if((*it).speed<0&&(*it).i_hanyou[0]==0){
			(*it).move_x = 0;
			(*it).move_y = -1;
			(*it).i_hanyou[0] = 1;
		}
		if((*it).speed<-1.5)	(*it).speed = -1.5;
	}
	else if(p==3){
		if(c==100)	(*it).speed = 1.5;
		if((*it).speed<5.0)	(*it).speed += 0.1;
		float sx = Player.x - (*it).x;
		float sy = Player.y - (*it).y;
		float sq = sqrt(sx*sx+sy*sy);
		(*it).move_x = sx/sq;
		(*it).move_y = sy/sq;
	}
	
	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).atari_x[0] = (*it).x - (*it).img_x;
	(*it).atari_x[1] = (*it).x + (*it).img_x;
	(*it).atari_y[0] = (*it).y - (*it).img_y;
	(*it).atari_y[1] = (*it).y + (*it).img_y;

	return;
}

void SEf_Load(){
	try{
		char fi[128];
		wsprintf(fi , "data/img/circle/1.png");
		SetTransColor(0,0,0);
		if( (gra_circle = LoadGraph(fi)) == -1)	throw(fi);
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	return;
}

void SEf_Reset(){
	Effect.clear();
	return;
}

void SEf_Draw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for(list<EFFECTDATA>::iterator it=Effect.begin();it!=Effect.end();it++){
		SEf_Move(it);
		if((*it).i_hanyou[7]==1){
			it = Effect.erase(it);
			it--;
			continue;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		if((*it).i_hanyou[6]==1)	SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if((*it).pattern==3){
			SetDrawBright(255,255,255);
			int color = (*it).i_hanyou[3];
			if((*it).i_hanyou[3]==GetColor(255,0,0)){
				if((*it).count%4<2)	color = GetColor(255,255,100);
				else			color = GetColor(255,50,50);
			}
			DrawFormatString((*it).x+shake_x, (*it).y+shake_y, color,"%d",(*it).i_hanyou[2]);
		}
		else{
			if(loop_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle, (*it).img, TRUE, FALSE);
		}
		(*it).count++;
	}
	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawBright(255,255,255);
	
	return;
}

void SEf_Make(float x,float y,int pattern,int img,int color){
	/*===========================================
		小弾 　　　0:赤 1:青 2:黄 3:緑
		中弾 　　　4:赤 5:青 6:黄 7:緑 53:水
		中弾その２ 8:赤 9:青 10:黄 11:緑 12:紫 13:灰
		米弾 　　　14:赤 15:青 16:黄 17:緑 52:水
		鱗弾 　　　18:赤 19:青 20:黄 21:緑
		蝶弾 　　　22:赤 23:青 24:黄 25:緑
	　　　（蝶弾薄部分)0:赤 1:青 2:黄 3:緑
		大弾 　　　26:赤 27:青 28:黄 29:緑 30:灰
		特大弾　　 31:赤 32:青 33:黄 34:緑
		刀弾　　　 35:赤 36:青 37:紫
		札弾　　　 38:赤 39:青 40:黄 41:緑 42:紫
		ジェリー弾 43:赤 44:青 45:黄 46:緑
		クナイ弾 　47:赤 48:青 49:黄 50:緑 51:紫
		氷弾　　　 54:赤 55:青 56:黄 57:緑
	　　　（特大弾薄部)4:赤 5:青 6:黄 7:緑
	===========================================*/
	EFFECTDATA P;
	P.x = x;
	P.y = y;
	P.move_x = 0;
	P.move_y = 0;
	P.speed = 0;
	P.img = img;
	if(img==gra_e_shot[14]||img==gra_e_shot[18]||img==gra_e_shot[22]||img==gra_e_shot[38]||img==gra_e_shot[47]||img==gra_e_shot[35]||img==gra_e_shot[54])	P.img = gra_e_shot[4];
	if(img==gra_e_shot[15]||img==gra_e_shot[19]||img==gra_e_shot[23]||img==gra_e_shot[39]||img==gra_e_shot[48]||img==gra_e_shot[36]||img==gra_e_shot[55])	P.img = gra_e_shot[5];
	if(img==gra_e_shot[16]||img==gra_e_shot[20]||img==gra_e_shot[24]||img==gra_e_shot[40]||img==gra_e_shot[49]||img==gra_e_shot[56])	P.img = gra_e_shot[6];
	if(img==gra_e_shot[17]||img==gra_e_shot[21]||img==gra_e_shot[25]||img==gra_e_shot[41]||img==gra_e_shot[50]||img==gra_e_shot[57])	P.img = gra_e_shot[7];
	if(img==gra_e_shot[42]||img==gra_e_shot[51]||img==gra_e_shot[37])	P.img = gra_e_shot[12];
	if(img==gra_e_shot[52])	P.img = gra_e_shot[53];
	if(img==gra_e_shot[31])	P.img = gra_e_shot2[4];
	if(img==gra_e_shot[32])	P.img = gra_e_shot2[5];
	if(img==gra_e_shot[33])	P.img = gra_e_shot2[6];
	if(img==gra_e_shot[34])	P.img = gra_e_shot2[7];
	if(img==gra_e_shot[43])	P.img = gra_e_shot[26];
	if(img==gra_e_shot[44])	P.img = gra_e_shot[27];
	if(img==gra_e_shot[45])	P.img = gra_e_shot[28];
	if(img==gra_e_shot[46])	P.img = gra_e_shot[29];
	if(img==gra_laser[0])	P.img = gra_e_shot[26];
	if(img==gra_laser[1])	P.img = gra_e_shot[27];
	P.pattern = pattern;
	P.flash = 255;
	P.count = 0;
	for(int i=0;i<HANYOU_NUM;i++){
		P.i_hanyou[i] = 0;
		P.d_hanyou[i] = 0;
	}
	if(pattern==3){
		P.i_hanyou[2] = img;//点数のこと
		P.i_hanyou[3] = color;
	}
	
	Effect.push_back(P);
	return;
}

void SEf_Move(list<EFFECTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	
	if(p==0){//敵やられモーション
		if(c==0){
			for(int i=0;i<3;i++){
				(*it).i_hanyou[i] = 150 + get_rand(105);
			}
			(*it).img = gra_circle;
		}
		(*it).angle = 12 * c;
		(*it).flash = 255 - 12.75*c;
		(*it).large = 0.075*c;
		SetDrawBright((*it).i_hanyou[0],(*it).i_hanyou[1],(*it).i_hanyou[2]);
		if(c==20)	(*it).i_hanyou[7] = 1;
	}
	else if(p==1){//自機やられモーション
		if(c==0){
			for(int i=0;i<3;i++){
				(*it).i_hanyou[i] = 150 + get_rand(105);
			}
			(*it).img = gra_circle;
		}
		(*it).angle = 12 * c;
		(*it).flash = 255 - 5.1*c;
		(*it).large = 0.04*c;
		SetDrawBright((*it).i_hanyou[0],(*it).i_hanyou[1],(*it).i_hanyou[2]);
		if(c==50)	(*it).i_hanyou[7] = 1;
	}
	else if(p==2){//敵弾消滅モーション
		(*it).flash = 255 - 12.75*c;
		(*it).large = 0.075*c;
		(*it).i_hanyou[6] = 1;
		if(c==20)	(*it).i_hanyou[7] = 1;
	}
	else if(p==3){//点アイテム点数モーション
		(*it).flash = 200;
		(*it).y -= 0.2;
		if(c==60)	(*it).i_hanyou[7] = 1;
	}
	else if(p==4){//レーザーモーション
		(*it).flash = 25.5*c;
		(*it).large = 1.5-0.15*c;
		(*it).i_hanyou[6] = 1;
		if(c==10)	(*it).i_hanyou[7] = 1;
	}
	else if(p==5){//敵登場モーション
		if(c==0){
			(*it).img = gra_circle;
		}
		(*it).angle = 36 * c;
		(*it).flash = 12.75*c;
		(*it).large = 3.0-0.1*c;
		SetDrawBright(255,255,255);
		if(c==20)	(*it).i_hanyou[7] = 1;
	}
	else if(p==6){//紫登場モーション
		if(c<30){
			(*it).flash = 255;
		}
		else if(c<60){
			(*it).flash = 8.5 * (60-c);
		}
		(*it).large = 4.0;
		(*it).i_hanyou[6] = 1;
		SetDrawBright(255,255,255);
		if(c==60)	(*it).i_hanyou[7] = 1;
	}
	else if(p==7){//敵被弾モーション
		if(c==0){
			(*it).i_hanyou[0] = 100+get_rand(100);
			(*it).large = 0.5+0.1*get_rand(7);
			(*it).d_hanyou[0] = Radian(get_rand(359),TRUE);
			(*it).d_hanyou[1] = 2.0 + 0.1*get_rand(60);
			(*it).img = gra_bullet_effect;
			(*it).angle = get_rand(359);
		}
		(*it).i_hanyou[6] = 1;
		(*it).x += (*it).d_hanyou[1]*cos((*it).d_hanyou[0]);
		(*it).y += (*it).d_hanyou[1]*sin((*it).d_hanyou[0]);
		(*it).flash = (*it).i_hanyou[0]/15 * (15-c);
		if(c==15)	(*it).i_hanyou[7] = 1;
	}
	else if(p==8){//紫撃破モーション
		if(c==0){
			(*it).i_hanyou[0] = 150+get_rand(100);
			(*it).large = 1.0+0.1*get_rand(10);
			(*it).d_hanyou[0] = Radian(get_rand(359),TRUE);
			(*it).d_hanyou[1] = 2.0 + 0.1*get_rand(60);
			(*it).img = Game.gra_t_effect;
			(*it).angle = get_rand(359);
		}
		(*it).i_hanyou[6] = 1;
		(*it).x += (*it).d_hanyou[1]*cos((*it).d_hanyou[0]);
		(*it).y += (*it).d_hanyou[1]*sin((*it).d_hanyou[0]);
		(*it).flash = (*it).i_hanyou[0]/15 * (15-c);
		if(c==30)	(*it).i_hanyou[7] = 1;
	}
	else if(p==9){//グレイズモーション
		if(c==0){
			(*it).flash = 200;
			(*it).large = 1.0;
			float angle = Radian(get_rand(359),TRUE);
			(*it).d_hanyou[0] = 2.0 + 0.1*get_rand(30);
			(*it).d_hanyou[1] = cos(angle);
			(*it).d_hanyou[2] = sin(angle);
		}
		else if(c<21){
			(*it).flash -= 10;
			(*it).large -= 0.05;
			(*it).x += (*it).d_hanyou[0] * (*it).d_hanyou[1];
			(*it).y += (*it).d_hanyou[0] * (*it).d_hanyou[2];
		}
		else	(*it).i_hanyou[7] = 1;
	}
	return;
}

void STa_Reset(){
	Talk.count = 0;
	Talk.scene = 0;
	Talk.carsol = 0;
	Talk.b_control = true;
	return;
}

void STa_Draw(){
	if(Talk.count==1)	Boss.gage_exist = 0;
	static int carsol;
	int Box_size;
	int end_scene = 200;
	char message[3][64];
	int count = Talk.count - 50;
	for(int i=0;i<3;i++){
		for(int a=0;a<64;a++){
			message[i][a] = ' ';
		}
	}
	int color;
	int red = GetColor(255,100,100);
	int blue = GetColor(100,100,255);
	int gray = GetColor(150,150,150);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,200);
	if(Talk.count<50){
		SBos_DeleteBullet(1);
		Talk.carsol = 0;
		for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();it++){
			(*it).pattern = 1;
		}
		Player.b_control = false;
		Box_size = Talk.count;
		DrawBox(35,370,385,370+1.4*Box_size,GetColor(0,0,0),TRUE);
	}
	else{
		DrawBox(35,370,385,440,GetColor(0,0,0),TRUE);
		if(GameScene==0){//ボス戦突入前会話
			switch(Game.stage){
				case 1: 
					if(SAVE.Chara==0){
						end_scene = 11;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「ふむ。かなり上まで昇ってきたようね。");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「でも、私の知っている空に答えは無い。");
									break;
							case 2:
								color = red;
								wsprintf(message[1] , "「こんな夜中に何を…");
								if(count<90){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==40){
									SBos_Make(-10,-10,2,25000,SAVE.Level,0,1,1,0,30);
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,50);
									GameScene = 0;
								}
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「悪い子は食べちまうぞ～！");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「あら、そういえば途中で見たわね。");
								break;
							case 5:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「何だか様子がおかしいと思ったんでねぇ。");
								wsprintf(message[2] , "　追ってみたわけよ。");
								break;
							case 6:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「…");
								break;
							case 7:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「案の定、何か良からぬことを企んでるね？");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「上に昇ってみたかっただけよ");
								break;
							case 9:
								if(count==1){
									SMu_PlayBgm(2);
									music_count = 0;
									SAVE.BgmFlag[2]++;
								}
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「いいや、私の天性の勘がそれを否定するね。");
								break;
							case 10:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「そしてこうも言っている。『霊夢を止めろ！』");
								break;
						}
					}
					else{
						end_scene = 11;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「高度５００ｍ。流石に肌寒くなってきたなぁ");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「しっかり着込んできて正解だったぜ");
									break;
							case 2:
								color = red;
								wsprintf(message[1] , "「こんな夜中に何を…");
								if(count<90){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==40){
									SBos_Make(-10,-10,2,25000,SAVE.Level,0,1,1,0,30);
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,50);
									GameScene = 0;
								}
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「悪い子は食べちまうぞ～！");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「鬼が人を喰うのは当然のことだ");
								break;
							case 5:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「むぅ。アンタはいつも通りね。");
								break;
							case 6:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「ああ、私は普通だぜ？");
								break;
							case 7:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「いやいや安心するよ。やっぱり幻想郷には");
								wsprintf(message[2] , "  酒と弾幕が似合うねぇ。");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「…それは私に関係ないと思うのだが");
								break;
							case 9:
								if(count==1){
									SMu_PlayBgm(2);
									music_count = 0;
									SAVE.BgmFlag[2]++;
								}
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「いやいや、さっきも言っただろう？");
								break;
							case 10:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「幻想郷には弾幕が似合う！");
								break;
						}
					}
					break;
				case 2:
					if(SAVE.Chara==0){
						end_scene = 14;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「空の上まで昇ってみたのは良いものの…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「まだまだ出口は見当たらないわねぇ");
								break;
							case 2:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「あの吸血鬼の言ってたことは本当かしら？");
								if(count<90){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==40){
									SBos_Make(-100,-10,3,12000,16+SAVE.Level,1,9,8,1,50);
									Boss.b_zanzou = true;
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,30);
									GameScene = 0;
								}
								if(count==90)	Boss.b_zanzou = false;
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「ええ、本当よ");
								break;
							case 4:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「この上にはきっと、面白い事件が待っているわ");
								break;
							case 5:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「分かったわ。じゃ、そういうことで");
								break;
							case 6:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「ちょっと待ちなさいよ");
								break;
							case 7:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「何を行き急ぐことがある？");
								wsprintf(message[2] , "　話し相手になってくれても良いんじゃない？");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「時は金なり、人間はそんなに");
								wsprintf(message[2] , "　長く生きられないのよ");
								break;
							case 9:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「何だか今日は愛想が悪いわねぇ");
								break;
							case 10:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「いつも通りだと思うけどね");
								break;
							case 11:
								if(count==1){
									SMu_PlayBgm(2);
									music_count = 0;
									SAVE.BgmFlag[2]++;
								}
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「それもそうか。");
								wsprintf(message[2] , "　…けど、ブンヤの目は誤魔化せないよ");
								break;
							case 12:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「貴方と楽しむのも、これで最後になりそうね");
								break;
							case 13:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「フン、瞬きする間すら与えないわよ");
								break;
						}
					}
					else{
						end_scene = 14;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「はて");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「勢い余って空の上まで来てしまった");
								break;
							case 2:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「雲上は空気が薄いと聞いた覚えがあるが、");
								wsprintf(message[2] , "　アレは嘘だったのか？");
								if(count<120){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==70){
									SBos_Make(-100,-10,3,12000,16+SAVE.Level,1,9,8,1,50);
									Boss.b_zanzou = true;
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,30);
									GameScene = 0;
								}
								if(count==120)	Boss.b_zanzou = false;
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「それは貴方の肺活量が逞しいからよ");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「ややっ、今宵も現れたか鴉天狗！");
								break;
							case 5:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「貴方もなにか企んでいるのね？");
								break;
							case 6:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「…やめておきなさい。いつ『アレ』の");
								wsprintf(message[2] , "　目に留まるか分からないんだから…");
								break;
							case 7:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「それに、この先は輪廻の輪を外れた私達に");
								wsprintf(message[2] , "　無縁の場所よ。");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「おいおい");
								wsprintf(message[2] , "　私はまだ人間やめちゃいないぜ");
								break;
							case 9:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「この逞しい探究心が証拠だ");
								break;
							case 10:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「そう。人間も愚かになったものね");
								break;
							case 11:
								if(count==1){
									SMu_PlayBgm(2);
									music_count = 0;
									SAVE.BgmFlag[2]++;
								}
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「適材適所、然るべき場所がある");
								wsprintf(message[2] , "　何故素直に従おうとしない？");
								break;
							case 12:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「待つものは自然の制裁のみよ");
								break;
							case 13:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「外道よ、知りたいか？");
								wsprintf(message[2] , "　その答えはこうだ。『逞しい探究心』");
								break;
						}
					
					}
					break;
				case 3:
					if(Game.count<2000){
						if(count<90){
							Talk.b_control = false;
						}
						else{
							Talk.scene++;
							Talk.count = 50;
						}
						Boss.b_atari = false;
						end_scene = 3;
						switch(Talk.scene){
							case 0:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「やっと追いついたよ。");
								break;
							case 1:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「…ここから先には行かせない！");
								break;
							case 2:
								color = blue;
								if(SAVE.Chara==0){
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「しつこい奴は嫌いよ");
								}
								else{
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「なんでそんなに執念深いんだ？");
								}
								Boss.move_pattern = 12;
								break;
						}
					}
					else if(Game.count<5000){
						if(count<120){
							Talk.b_control = false;
						}
						else{
							Talk.scene++;
							Talk.count = 50;
						}
						Boss.b_atari = false;
						Boss.b_zanzou = true;
						end_scene = 3;
						switch(Talk.scene){
							case 0:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「何だか分からないけど、");
								wsprintf(message[2] , "　貴方を止めなくちゃならない気がするわ");
								break;
							case 1:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「さあ、これ以上は諦めなさい");
								break;
							case 2:
								color = blue;
								if(SAVE.Chara==0){
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「ああーっ、もうしつこいな！");
								}
								else{
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「宇宙空間で羽は無意味だぜ、");
									wsprintf(message[2] , "　諦めな");
								}
								Boss.move_pattern = 12;
								break;
						}
					}
					else{
						Talk.b_control = true;
						if(SAVE.Chara==0){
							end_scene = 21;
							switch(Talk.scene){
								case 0:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「不気味な所ね。此処は一体…");
									break;
								case 1:
									color = gray;
									wsprintf(message[1] , "「貴方は招かれざる客");
									break;
								case 2:
									color = gray;
									wsprintf(message[1] , "「空を飛び、うっかり迷い込んだ小鳥か");
									wsprintf(message[2] , "　不思議な噂を聞き、好奇心を駆られたハンターか");
									break;
								case 3:
									color = gray;
									wsprintf(message[1] , "「或いは…");
									if(count<160){
										Talk.b_control = false;
									}
									else{
										Talk.scene++;
									}
									if(count==1){
										Boss.x = CENTER_X;
										Boss.y = 150;
										SPlaySound(17);	
										for(int i=0;i<6;i++){
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i,20,-1,-1);
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i+30,21,-1,-1);
										}
									}
									if(count==70){
										SBos_Make(CENTER_X,150,4,20000,36+SAVE.Level,2,14,13,2,50);
										Boss.gage_exist = 0;
										Boss.b_atari = false;
										SBos_MoveTo(CENTER_X,170,50);
										GameScene = 0;
									}
									break;
								case 4:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「此処が幻想郷の最果てだと知り、");
									wsprintf(message[2] , "　秩序の破壊を目論む愚か者か");
									break;
								case 5:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「１番が近いかな");
									break;
								case 6:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「籠の中から逃げ出そうとする小鳥よ");
									break;
								case 7:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「『飼い主』に作られた面白味のない世界から");
									wsprintf(message[2] , "　脱走しようとする小鳥。");
									break;
								case 8:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「…やっぱりアンタが最後の砦なのね");
									break;
								case 9:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「…ああ、霊夢。");
									wsprintf(message[2] , "　貴方はなんて愚かな人間なのかしら");
									break;
								case 10:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「全てを知っても幸せにはなれないのに");
									wsprintf(message[2] , "　不変の中に居れば誰も傷つかないのに");
									break;
								case 11:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「どうして私の世界を壊そうとする？");
									break;
								case 12:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「貴方は『私の世界を守る為に作った』のよ？");
									break;
								case 13:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「なんか色々恐ろしいことを");
									wsprintf(message[2] , "　口走ってくれたけど…");
									break;
								case 14:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「…到達してしまったのね、");
									wsprintf(message[2] , "　不可侵の領域に");
									break;
								case 15:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「…そう。此処は所謂『隙間の世界』");
									break;
								case 16:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「夢と現の狭間を漂う、不安定な世界");
									break;
								case 17:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「貴方は来るところまで来てしまった");
									break;
								case 18:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「そしてアンタは私を消す");
									if(count==1){
										SMu_PlayBgm(5);
										music_count = 0;
										SAVE.BgmFlag[5]++;
									}
									break;
								case 19:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「結界の守人が自ら結界を解く？");
									break;
								case 20:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「その荒唐無稽な姿、");
									wsprintf(message[2] , "　貴方らしくて良いわね、霊夢");
									break;
							}
						}
						else{
							end_scene = 18;
							switch(Talk.scene){
								case 0:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「何だか今までと雰囲気が違うな…");
									break;
								case 1:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「やっと出口に到達したのか？");
									break;
								case 2:
									color = gray;
									wsprintf(message[1] , "「貴方は招かれざる客");
									break;
								case 3:
									color = gray;
									wsprintf(message[1] , "「空を飛び、うっかり迷い込んだ小鳥か");
									wsprintf(message[2] , "　不思議な噂を聞き、好奇心を駆られたハンターか");
									break;
								case 4:
									color = gray;
									wsprintf(message[1] , "「或いは…");
									if(count<160){
										Talk.b_control = false;
									}
									else{
										Talk.scene++;
									}
									if(count==1){
										Boss.x = CENTER_X;
										Boss.y = 150;
										SPlaySound(17);	
										for(int i=0;i<6;i++){
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i,20,-1,-1);
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i+30,21,-1,-1);
										}
									}
									if(count==70){
										SBos_Make(CENTER_X,150,4,20000,36+SAVE.Level,2,14,13,2,50);
										Boss.gage_exist = 0;
										Boss.b_atari = false;
										SBos_MoveTo(CENTER_X,170,50);
										GameScene = 0;
									}
									break;
								case 5:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「此処が幻想郷の最果てだと知り、");
									wsprintf(message[2] , "　秩序の破壊を目論む愚か者か");
									break;
								case 6:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「そろそろ出る頃だと思ってたぜ");
									break;
								case 7:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「私がしていることは、");
									wsprintf(message[2] , "　幻想郷の存在をも脅かすからな");
									break;
								case 8:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「あら、『普通の魔法使い』が");
									wsprintf(message[2] , "　よくそんなことを知っているわね。");
									break;
								case 9:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「いや、今は『秩序の破壊を目論む愚か者』。");
									wsprintf(message[2] , "　だから私が直々に制裁を与えに来た");
									break;
								case 10:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「幻想が幻想でなくなるということは、");
									wsprintf(message[2] , "　現実と幻想の境界が曖昧になるということ");
									break;
								case 11:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「だからお前と霊夢は、結界を作って");
									wsprintf(message[2] , "　幻想郷を保護してきたんだ");
									break;
								case 12:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「ええ、その通り");
									wsprintf(message[2] , "　少なくとも私は、今でも幻想郷を守っている");
									break;
								case 13:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「…？");
									break;
								case 14:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「貴方は『普通の魔法使い』にしては");
									wsprintf(message[2] , "　情報を持ちすぎている");
									if(count==1){
										SMu_PlayBgm(5);
										music_count = 0;
										SAVE.BgmFlag[5]++;
									}
									break;
								case 15:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「この夢と現の狭間で");
									wsprintf(message[2] , "　輪廻の境界を彷徨ってもらいましょう");
									break;
								case 16:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「悪いな紫、お前の言うことは全て正しい");
									wsprintf(message[2] , "　それは認めよう");
									break;
								case 17:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「だが、これは私とあいつの勝負");
									wsprintf(message[2] , "　人も妖も、間に入ることは出来ない！");
									break;
							}
						}
					}
					break;
				case 4: 
					if(SAVE.Chara==0){
						end_scene = 12;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「過去に戻って考え直せって言うけど…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「どう考えても私の知ってる過去じゃないわね");
								wsprintf(message[2] , "　こんなに道中激しかったっけ？");
									break;
							case 2:
								color = red;
								wsprintf(message[1] , "「こんな夜中に何を…");
								if(count<90){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==40){
									SBos_Make(-10,-10,2,27000,55+SAVE.Level,0,1,18,5,30);
									//SBos_Make(-10,-10,2,1,104,2,1,-1,5,30);
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,50);
									GameScene = 0;
								}
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「悪い子は食べちまうぞ～！");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「なんというデジャヴ");
								break;
							case 5:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「…？");
								wsprintf(message[2] , "　やっぱり様子がおかしいね。");
								break;
							case 6:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「まるで今から起こることが");
								wsprintf(message[2] , "　分かっているような顔だ");
								break;
							case 7:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「どんな顔してるのよ");
								break;
							case 8:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「ッフフ、そんな顔だよ");
								wsprintf(message[2] , "　何か良からぬことを企んでるね？");
								break;
							case 9:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「上に昇ってみたかっただけよ");
								break;
							case 10:
								if(count==1){
									SMu_PlayBgm(6);
									music_count = 0;
									SAVE.BgmFlag[6]++;
								}
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「いいや、私の天性の勘がそれを否定するね。");
								break;
							case 11:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「そしてこうも言っているのね？");
								wsprintf(message[2] , "　『私を止めろ！』");
								break;
						}
					}
					else{
						end_scene = 11;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「過去に戻って考え直せ、と");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「だが私の決心は変わらんね");
									break;
							case 2:
								color = red;
								wsprintf(message[1] , "「こんな夜中に何を…");
								if(count<90){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==40){
									SBos_Make(-10,-10,2,27000,55+SAVE.Level,0,1,18,5,30);
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,50);
									GameScene = 0;
								}
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「悪い子は食べちまうぞ～！");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「鬼が人を喰うのは当然のことだ");
								break;
							case 5:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「むぅ。アンタはいつも通りね。");
								break;
							case 6:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「あー、いつも通りじゃないがな");
								break;
							case 7:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「あれ、おかしいな。");
								wsprintf(message[2] , "  アンタなら『普通だぜ』とか言いそうなのに");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「うん、ちょっと色々あってな");
								wsprintf(message[2] , "　この会話が面倒だと思っている");
								break;
							case 9:
								if(count==1){
									SMu_PlayBgm(6);
									music_count = 0;
									SAVE.BgmFlag[6]++;
								}
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「悲しいねぇ。私は嫌われているのかい？");
								break;
							case 10:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「いやいや、お前が何を言うのか分かるもので");
								break;
						}
					}
					break;
				case 5:
					if(SAVE.Chara==0){
						end_scene = 12;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「なかなか厳しい道中ね");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「でも雑魚は雑魚、");
								wsprintf(message[2] , "　大したこと無い奴らばかりだったわ");
								break;
							case 2:
								color = red;
								wsprintf(message[1] , "「相変わらず私の好奇心をかき立てるわね");
								if(count<90){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==40){
									SBos_Make(-100,-10,3,15000,67+SAVE.Level,1,9,20,6,50);
									//SBos_Make(Boss.x,Boss.y,Boss.zanki,1,104,2,-1,-1,2,255);
									Boss.b_zanzou = true;
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,30);
									GameScene = 0;
								}
								if(count==90)	Boss.b_zanzou = false;
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「独り言が大きすぎるのではなくて？");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「うーん、また厄介な奴に目をつけられたわね");
								break;
							case 5:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「運命を変えることは出来ないのかしら？");
								break;
							case 6:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「ん、何だか貴方らしくないことを言ってるわね");
								break;
							case 7:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「そして、貴方らしくないことを");
								wsprintf(message[2] , "　考えているのではなくて？");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「・・・！");
								break;
							case 9:
								if(count==1){
									SMu_PlayBgm(7);
									music_count = 0;
									SAVE.BgmFlag[7]++;
								}
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「幻想郷からは逃げられないよ、誰一人として");
								break;
							case 10:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「貴方の見たことの無い、");
								wsprintf(message[2] , "　究極の奥義でこらしめてやるわ！");
								break;
							case 11:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「フン、天狗ごときが");
								wsprintf(message[2] , "　息つく暇も与えないわよ");
								break;
						}
					}
					else{
						end_scene = 11;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「ううっ、やっぱ雑魚が強くなってるなぁ…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「過去のはずなのに過去でないのはどういうことだ");
								break;
							case 2:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「紫は過去へ戻したとか言ってたけど、");
								wsprintf(message[2] , "　アレは嘘だったのか？");
								if(count<120){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==70){
									SBos_Make(-100,-10,3,15000,67+SAVE.Level,1,9,20,6,50);
									//SBos_Make(Boss.x,Boss.y,Boss.zanki,1,104,2,-1,-1,2,255);
									Boss.b_zanzou = true;
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,30);
									GameScene = 0;
								}
								if(count==120)	Boss.b_zanzou = false;
								break;
							case 3:
								Talk.b_control = true;
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「すごい独り言ね。１里先からでも聞こえたわよ");
								break;
							case 4:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「ややっ、今宵も現れたか鴉天狗！");
								break;
							case 5:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「…不思議なテンションだわ。");
								wsprintf(message[2] , "　夜に魅了されたのかしら");
								break;
							case 6:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「アイツが心配しているほど");
								wsprintf(message[2] , "　事態は深刻じゃないみたいね");
								break;
							case 7:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「む、お前紫と手を組んだのか？");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「そうか。何も知らぬ振りは出来ないようだな");
								break;
							case 9:
								if(count==1){
									SMu_PlayBgm(7);
									music_count = 0;
									SAVE.BgmFlag[7]++;
								}
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「私をスルーしようとしたのかしら？");
								break;
							case 10:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「少しは相手しなさいよ…");
								wsprintf(message[2] , "　最期になるかもしれない弾幕を！");
								break;
						}
					
					}
					break;
				case 6:
					if(Game.count<2000){
						if(count<90){
							Talk.b_control = false;
						}
						else{
							Talk.scene++;
							Talk.count = 50;
						}
						Boss.b_atari = false;
						end_scene = 3;
						switch(Talk.scene){
							case 0:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「やっと追いついたよ。");
								break;
							case 1:
								color = red;
								wsprintf(message[0] , "萃香:");
								wsprintf(message[1] , "「…ここから先には行かせない！");
								break;
							case 2:
								color = blue;
								if(SAVE.Chara==0){
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「ホントしつこい奴ね！");
								}
								else{
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「ああ、そんなこともあったな");
								}
								Boss.move_pattern = 12;
								break;
						}
					}
					else if(Game.count<5000){
						if(count<120){
							Talk.b_control = false;
						}
						else{
							Talk.scene++;
							Talk.count = 50;
						}
						Boss.b_atari = false;
						Boss.b_zanzou = true;
						end_scene = 3;
						switch(Talk.scene){
							case 0:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「何だか分からないけど、");
								wsprintf(message[2] , "　貴方を止めなくちゃならない気がするわ");
								break;
							case 1:
								color = red;
								wsprintf(message[0] , "文:");
								wsprintf(message[1] , "「さあ、これ以上は諦めなさい");
								break;
							case 2:
								color = blue;
								if(SAVE.Chara==0){
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「分からないなら邪魔するな！");
								}
								else{
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「もうその台詞は聞き飽きたぜ？");
								}
								Boss.move_pattern = 12;
								break;
						}
					}
					else{
						Talk.b_control = true;
						if(SAVE.Chara==0){
							end_scene = 16;
							switch(Talk.scene){
								case 0:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「さあ、来たわよ、紫！");
									break;
								case 1:
									color = gray;
									wsprintf(message[1] , "「過去に戻って考えてきたのね");
									break;
								case 2:
									color = gray;
									wsprintf(message[1] , "「そして再び、");
									wsprintf(message[2] , "　この『夢と現の狭間』にいるということは");
									if(count<160){
										Talk.b_control = false;
									}
									else{
										Talk.scene++;
									}
									if(count==1){
										Boss.x = CENTER_X;
										Boss.y = 150;
										SPlaySound(17);	
										for(int i=0;i<6;i++){
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i,20,-1,-1);
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i+30,21,-1,-1);
										}
									}
									if(count==70){
										SBos_Make(CENTER_X,150,5,20000,82+SAVE.Level,2,14,25,9,50);
										Boss.gage_exist = 0;
										Boss.b_atari = false;
										SBos_MoveTo(CENTER_X,170,50);
										GameScene = 0;
									}
									break;
								case 3:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「貴方の考えは、以前と変わっていないのね？");
									break;
								case 4:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「あの問いに、素直に答えていれば良かったわ");
									break;
								case 5:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「面倒くさいルートを通ってしまったわね。");
									wsprintf(message[2] , "　でも、これでやっと最後の壁。");
									break;
								case 6:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「夢の世界への入口は、目の前にある！");
									break;
								case 7:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「…夢の世界？");
									break;
								case 8:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「愚かな人間よ、幻想に生きる旅人よ、聞きなさい");
									break;
								case 9:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「夢の世界とは、幻想郷のこと。");
									wsprintf(message[2] , "　貴方が夢見ているのは夢ではなく現");
									break;
								case 10:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「まだ、その真実に辿り着けないの…？");
									break;
								case 11:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「アンタの言葉遊びに付き合っている暇はないわ！");
									if(count==1){
										SMu_PlayBgm(8);
										music_count = 0;
										SAVE.BgmFlag[8]++;
									}
									break;
								case 12:
									color = blue;
									wsprintf(message[0] , "霊夢:");
									wsprintf(message[1] , "「さあ、終わらせるわよ、この夢の世界を！");
									break;
								case 13:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「…結局、貴方は自己矛盾を");
									wsprintf(message[2] , "　抱えた存在に過ぎない");
									break;
								case 14:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「創造主である『私』から、");
									wsprintf(message[2] , "　誰も逃れることは出来ない！");
									break;
								case 15:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「優雅に、妖艶に、その二色の羽を散らすが良い！");
									break;
							}
						}
						else{
							end_scene = 21;
							switch(Talk.scene){
								case 0:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「さあ、来たぜ、紫！");
									break;
								case 1:
									color = gray;
									wsprintf(message[1] , "「過去に戻って考えてきたのね");
									break;
								case 2:
									color = gray;
									wsprintf(message[1] , "「そして再び、");
									wsprintf(message[2] , "　この『夢と現の狭間』にいるということは");
									if(count<160){
										Talk.b_control = false;
									}
									else{
										Talk.scene++;
									}
									if(count==1){
										Boss.x = CENTER_X;
										Boss.y = 150;
										SPlaySound(17);	
										for(int i=0;i<6;i++){
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i,20,-1,-1);
											SEn_Make(CENTER_X,CENTER_Y,8,360+60*i+30,21,-1,-1);
										}
									}
									if(count==70){
										SBos_Make(CENTER_X,150,5,20000,82+SAVE.Level,2,14,25,9,50);
										Boss.gage_exist = 0;
										Boss.b_atari = false;
										SBos_MoveTo(CENTER_X,170,50);
										GameScene = 0;
									}
									break;
								case 3:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「貴方の考えは、以前と変わっていないのね？");
									break;
								case 4:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「ああ。私は行くぜ");
									break;
								case 5:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「もう一度過去を遡って気付いた。");
									break;
								case 6:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「幻想郷の生活は、");
									wsprintf(message[2] , "　結局同じような『弾幕ごっこ』しかない");
									break;
								case 7:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「そりゃそうだ。");
									wsprintf(message[2] , "　此処は言わば、閉鎖空間だから。");
									break;
								case 8:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「目新しいものも無い、");
									wsprintf(message[2] , "　いつも不変の世界。");
									break;
								case 9:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「だから私は、異変を求めて");
									wsprintf(message[2] , "　外の世界に行く");
									break;
								case 10:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「たとえ幻想郷が消滅することになっても？");
									break;
								case 11:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「幻想郷は消えない。");
									wsprintf(message[2] , "　外界との境界が曖昧になるだけだ");
									break;
								case 12:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「紫、お前は怖いんだろう？自分の知らない");
									wsprintf(message[2] , "　モノが、自分の世界に入ってくるのが");
									break;
								case 13:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「そして自分の世界が、");
									wsprintf(message[2] , "　外の世界の色に染まることが");
									break;
								case 14:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「…");
									break;
								case 15:
									color = blue;
									wsprintf(message[0] , "魔理沙:");
									wsprintf(message[1] , "「二回目の弾幕は、お前の恐怖を映し出していたぜ");
									break;
								case 16:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「貴方は思った以上に目が良いのね");
									if(count==1){
										SMu_PlayBgm(8);
										music_count = 0;
										SAVE.BgmFlag[8]++;
									}
									break;
								case 17:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「しかし、貴方は私の生み出した者。");
									wsprintf(message[2] , "　その世界から抜け出すことは死を意味する");
									break;
								case 18:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「…結局、貴方は自己矛盾を");
									wsprintf(message[2] , "　抱えた存在に過ぎない");
									break;
								case 19:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「創造主である『私』から、");
									wsprintf(message[2] , "　誰も逃れることは出来ない！");
									break;
								case 20:
									color = red;
									wsprintf(message[0] , "紫:");
									wsprintf(message[1] , "「優雅に、妖艶に、その漆黒の翼を散らすが良い！");
									break;
							}
						}
					}
					break;
				case 7:
					if(SAVE.Chara==0){
						Talk.b_control = true;
						end_scene = 25;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「『弾幕ごっこ、しませんか』ねぇ…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「性質の悪いイタズラかと思ったけど");
								wsprintf(message[2] , "　道中の様子から、そうではなさそうね…");
								break;
							case 2:
								color = gray;
								wsprintf(message[1] , "「そう、戯言ではありません");
								break;
							case 3:
								color = gray;
								wsprintf(message[1] , "「全ての人は輪廻の輪の上に在る");
								break;
							case 4:
								color = gray;
								wsprintf(message[1] , "「人はその輪から逃れることが出来ない");
								break;
							case 5:
								color = gray;
								wsprintf(message[1] , "「だが、束縛から解き放たれた人が、此処に居る");
								break;
							case 6:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「…そうか。遂に現れたのね");
								break;
							case 7:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「幻想郷からの刺客が！");
								if(count<160){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==1){
									Boss.x = CENTER_X;
									Boss.y = 150;
									SPlaySound(17);	
									for(int i=0;i<6;i++){
										SEn_Make(CENTER_X,CENTER_Y,8,360+60*i,20,-1,-1);
										SEn_Make(CENTER_X,CENTER_Y,8,360+60*i+30,21,-1,-1);
									}
								}
								if(count==70){
									SBos_Make(CENTER_X,150,9,20000,104,3,4,31,11,30);
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,50);
									GameScene = 0;
								}
								break;
							case 8:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「刺客とは人聞きの悪い。");
								wsprintf(message[2] , "　私はただ、貴方を往生させに来ただけです");
								break;
							case 9:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「遠まわしに殺そうとしてるってことね");
								break;
							case 10:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「いいえ、殺すのではありません。");
								break;
							case 11:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方達を元居た場所、在るべき場所へと");
								wsprintf(message[2] , "　連れ戻しに来たのです");
								break;
							case 12:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「貴方『達』…？");
								break;
							case 13:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「ご存知なかったのですか？");
								break;
							case 14:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「３年前、貴方の他にもう一人、");
								wsprintf(message[2] , "　外の世界…現の世界へと往生した者がいます");
								break;
							case 15:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「白黒の魔法使いは、好奇心に駆られ");
								wsprintf(message[2] , "　幻想を捨てた");
								break;
							case 16:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「そして貴方も、幻の依存性に不満を覚え");
								wsprintf(message[2] , "　幻想郷を出て行った…");
								break;
							case 17:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「笑わせないで。");
								break;
							case 18:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「私の人生は私のものよ。");
								wsprintf(message[2] , "　どう生きたって私の勝手でしょ？");
								break;
							case 19:
								if(count==1){
									SMu_PlayBgm(13);
									music_count = 0;
									SAVE.BgmFlag[13]++;
								}
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「…生物には、生きる為の最低条件がある");
								break;
							case 20:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「私達幻想人は、幻想がその条件の一つなのです");
								break;
							case 21:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「それが幻想でなくなったとき");
								wsprintf(message[2] , "　幻想郷はどうなるか…");
								break;
							case 22:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方には、私達の世界の存続のために");
								wsprintf(message[2] , "　『死んで』もらいます");
								break;
							case 23:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「望むところよ！");
								wsprintf(message[2] , "　久しぶりの弾幕ごっこだしね！");
								break;
							case 24:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方の記憶を蘇らせる弾幕…");
								wsprintf(message[2] , "　幻想の心、復活せん！");
								break;
						}
					}
					else{
						Talk.b_control = true;
						end_scene = 30;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「『弾幕ごっこ、しませんか』…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「弾幕ごっこ…懐かしい響きだな");
								break;
							case 2:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「３年前、私は幻想郷から");
								wsprintf(message[2] , "　現の世界へとやって来た。");
								break;
							case 3:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「幻なんて何も無い、物神化の世界へと");
								break;
							case 4:
								color = gray;
								wsprintf(message[1] , "「そう、貴方は幻を捨てた");
								break;
							case 5:
								color = gray;
								wsprintf(message[1] , "「そして空虚な現の世界へやって来た");
								break;
							case 6:
								color = gray;
								wsprintf(message[1] , "「私たちをも捨てて…");
								break;
							case 7:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「…その声には聞き覚えがあるな");
								break;
							case 8:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「彼岸花なんてとっくに散ったぜ？");
								if(count<160){
									Talk.b_control = false;
								}
								else{
									Talk.scene++;
								}
								if(count==1){
									Boss.x = CENTER_X;
									Boss.y = 150;
									SPlaySound(17);	
									for(int i=0;i<6;i++){
										SEn_Make(CENTER_X,CENTER_Y,8,360+60*i,20,-1,-1);
										SEn_Make(CENTER_X,CENTER_Y,8,360+60*i+30,21,-1,-1);
									}
								}
								if(count==70){
									SBos_Make(CENTER_X,150,9,20000,104,3,4,31,11,30);
									Boss.gage_exist = 0;
									Boss.b_atari = false;
									SBos_MoveTo(CENTER_X,170,50);
									GameScene = 0;
								}
								break;
							case 9:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「そうですか。");
								wsprintf(message[2] , "　でも、私は季節性の者ではありません。");
								break;
							case 10:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「東京上空で弾幕は危ないぜ？");
								break;
							case 11:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「６０年経ったからと言って");
								wsprintf(message[2] , "　それは悪い冗談だと思うな");
								break;
							case 12:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「久しぶりの再会なのに、随分冷たいですね。");
								break;
							case 13:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「…いや、貴方の場合はいつも通りでしょうか");
								break;
							case 14:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「ああ。私は普通だ。");
								break;
							case 15:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「では、こちらは話が早いですね。");
								wsprintf(message[2] , "　今すぐ死になさい");
								break;
							case 16:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「…悪い冗談にしか聴こえないが、");
								wsprintf(message[2] , "　要するに幻想郷へ戻れってことか？");
								break;
							case 17:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「…そして、何となく察していたが");
								wsprintf(message[2] , "　私の他にも幻想郷を抜けた奴がいるな？");
								break;
							case 18:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「流石は霧雨魔理沙。勘が鋭いですね。");
								break;
							case 19:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「３年前、貴方の他にもう一人、");
								wsprintf(message[2] , "　外の世界…現の世界へと往生した者がいます");
								break;
							case 20:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「紅白の蝶は、幻の依存性に不満を覚え");
								wsprintf(message[2] , "　幻想郷を出て行った");
								break;
							case 21:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「そして貴方も、好奇心に駆られ");
								wsprintf(message[2] , "　幻想を捨てた…");
								break;
							case 22:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「人は好奇心無しでは生きられない");
								break;
							case 23:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「興味の向くものが無い人など");
								wsprintf(message[2] , "　死んでいるのも同然だ");
								break;
							case 24:
								if(count==1){
									SMu_PlayBgm(13);
									music_count = 0;
									SAVE.BgmFlag[13]++;
								}
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方は元々幻想人だった");
								break;
							case 25:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方達のせいで、現と幻の境界は曖昧になった");
								break;
							case 26:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「強すぎる好奇心は、時に他人を殺すことになる");
								break;
							case 27:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方には、私達の世界の存続のために");
								wsprintf(message[2] , "　『死んで』もらいます");
								break;
							case 28:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「望むところだ！");
								wsprintf(message[2] , "　幻想郷最後の弾幕、見せてみろ！");
								break;
							case 29:
								color = red;
								wsprintf(message[0] , "映姫:");
								wsprintf(message[1] , "「貴方を幻へと誘う弾幕…");
								wsprintf(message[2] , "　幻想の心、復活せん！");
								break;
						}
					}
					break;
			}
		}
		if(GameScene==1){//ボス戦後会話
			switch(Game.stage){
				case 1: 
					if(SAVE.Chara==0){
						end_scene = 2;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「まったく。幻想郷には勘の良い奴が多すぎるわ。");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「さあ、早いこと上へ行きましょう");
								break;
						}
					}
					else{
						end_scene = 2;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「なかなか火力のある弾幕だった。");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「私ほどじゃないけどな");
								break;
						}
					}
					break;
				case 2:
					if(SAVE.Chara==0){
						end_scene = 2;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「空にあるのはマスコミ天狗のみか…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「答えはまだまだ先にあるのね");
								wsprintf(message[2] , "　もっと上に…");
								break;
						}
					}
					else{
						end_scene = 2;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「鬼も天狗も、私と会う前に");
								wsprintf(message[2] , "　霊夢と会ったみたいだったな");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「あいつには負けてられないぜ");
								wsprintf(message[2] , "　もっと上に行こう");
								break;
						}
					}
					break;
				case 3:
					end_scene = 4;
					Talk.b_control = false;
					if(Talk.count>170){
						switch(Talk.scene){
							case 0:
								if(Talk.count>200)	Talk.b_control = true;
								if(Player.life>=2&&Game.con_times==0&&SAVE.Level>0){
									color = gray;
									wsprintf(message[1] , "　このまま幻想郷を脱出する");
									wsprintf(message[2] , "　心残りがある");									
								}
								else{
									end_scene = 0;
								}
								if(c_pad[PAD_DOWN]==1 || c_key[KEY_INPUT_DOWN]==1){
									Talk.carsol = 2;
								}
								if(c_pad[PAD_UP]==1 || c_key[KEY_INPUT_UP]==1){
									Talk.carsol = 1;
								}
								if(Talk.count==171)	Talk.carsol = 1;
								break;
							case 1:
								Talk.b_control = false;
								if(Talk.carsol==1){
									end_scene = 1;
								}
								else{
									if(count==300){
										Talk.scene++;
										Talk.count = 170;
									}
									color = gray;
									wsprintf(message[1] , "「…まだ、こっちの世界に未練があるのね");
								}
								break;
							case 2:
								Talk.b_control = false;
								if(count==300){
									Talk.scene++;
									Talk.count = 170;
								}
								color = gray;
								wsprintf(message[1] , "「貴方の選択が本当に正しかったのか");
								wsprintf(message[2] , "　幻想郷を捨てても本当に良いのか");
								break;
							case 3:
								Talk.b_control = false;
								if(count==350){
									Talk.scene++;
									Talk.count = 170;
								}
								color = gray;
								wsprintf(message[1] , "「もう一度、過去に戻って");
								wsprintf(message[2] , "　考え直す時間を与えましょう");
								break;
							default:	
								SetDrawBlendMode(DX_BLENDMODE_ADD,200);
								DrawCircle(CENTER_X,CENTER_Y,400,GetColor(255,255,255),TRUE);
								break;
						}
					}
					break;
				case 4: 
					if(SAVE.Chara==0){
						end_scene = 3;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「萃香の攻撃も激しかったわね");
								wsprintf(message[2] , "　一体どういうことなのかしら");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「…そうか、アイツは私を試しているのか");
								break;
							case 2:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「私が結界を破る力を持つのかどうか…");
								break;
						}
					}
					else{
						end_scene = 3;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「過去に戻って考え直せ…");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「そうか。要するに『諦めろ』ってことだったのか");
								break;
							case 2:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「上等じゃないか。多少相手が強くなった方が");
								wsprintf(message[2] , "　やりがいがあるし");
								break;
						}
					}
					break;
				case 5:
					if(SAVE.Chara==0){
						end_scene = 2;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「邪魔者は全て消えたわ");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "霊夢:");
								wsprintf(message[1] , "「あとはアイツを倒すだけね…");
								break;
						}
					}
					else{
						end_scene = 2;
						switch(Talk.scene){
							case 0:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「ふー、おっかない。");
								wsprintf(message[2] , "　やっぱり天狗は敵に回すと怖いな");
								break;
							case 1:
								color = blue;
								wsprintf(message[0] , "魔理沙:");
								wsprintf(message[1] , "「さあ、あとはアイツを倒すだけ…");
								break;
						}
					}
					break;
				case 6:
					if(Boss.i_hanyou[6]==0){
						end_scene = 31;
						if(Talk.scene==0 && Talk.count==120){
							SMu_StopBgm();
							SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01);
						}
						color = gray;
						Talk.b_control = false;
						int co = 10;
						if(Talk.scene==11)	co = 60;
						if(Talk.scene==15)	co = 60;
						if(Talk.count==co+170){
							Talk.scene++;
							Talk.count = 170;
						}
						wsprintf(message[1] , "われを尊しとおもいて、賢に傲り士を慢るなかれ");
						for(int i=0;i<32-Talk.scene;i++){
							if(62-2*i>=0){
								message[1][62-2*i] = ' ';
								message[1][63-2*i] = ' ';
							}
						}
					}
					else{
						Talk.b_control = false;
						if(count==350){
							Talk.scene++;
							Talk.count = 170;
						}
						end_scene = 1;
						Talk.carsol = 1;
					}
					break;
				case 7:
					Talk.b_control = false;
					if(count==350){
						Talk.scene++;
						Talk.count = 170;
					}
					end_scene = 1;
					Talk.carsol = 1;
			}
		}
		for(int i=0;i<3;i++){
			int color2 = GetColor(255,255,255);	
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(GameScene==1&&Game.stage==3&&Talk.scene==0){
				if(Talk.carsol!=i){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
					color2 = GetColor(100,100,100);
				}
			}
			DrawStringToHandle(40,375+20*i,message[i],color2,MessageFont,color);
		}
		if(Talk.b_control==true){
			if(count>600||(Game.Shot==1)||Game.Skip%3==1){
				SPlaySound(22);				
				Talk.scene++;
				Talk.count = 50;
				Talk.carsol = Talk.carsol%2;
			}
		}
	}
	
	Talk.count++;
	if(Game.stage==6 && Boss.i_hanyou[6]==0 && GameScene==1){
		if(Talk.count<120){
			SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01*(float)(120-Talk.count)/120.0);
		}		
	}
	if(Talk.scene==end_scene&&GameScene==0){
		Talk.count = 0;
		Talk.scene = 0;
		Boss.count = 0;
		Boss.gage_exist = 1;
		Boss.b_atari = true;
		Player.b_control = true;
		GameScene = 1;
	}
	else if(Talk.scene==end_scene&&GameScene==1){
		if(Game.stage==6 && Boss.i_hanyou[6]==0){
			SMu_PlayBgm(9);
			music_count = 0;
			SAVE.BgmFlag[9]++;
			SBos_Make(Boss.x,Boss.y,0,0,SAVE.Level+100,2,-1,-1,-1,255);
			Boss.i_hanyou[6] = 1;
			Talk.count = 0;
			Talk.scene = 0;
			Boss.count = 0;
			Boss.gage_exist = 1;
			Boss.b_atari = false;
			Player.b_control = true;
			GameScene = 1;
		}
		else{
			Talk.carsol = Talk.carsol%2;//0:通常　1:オールクリア
			Talk.count = 0;
			Talk.scene = 0;
			Player.b_control = true;
			ResultCount = 1;
		}
	}
	return;
}

void SEnd_Load(){
	try{
		char fi[128];
		for(int i=0;i<GRA_ENDING_NUM;i++){
			SetTransColor(0,0,0);
			wsprintf(fi , "data/img/back/end.png");
			if( (Ending.img[i] = LoadGraph(fi)) == -1)	throw(fi);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SEnd_Load\n構造体指定番号のいずれかが異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}	
	return;
}

void SEnd_Reset(){
	//クリア時に呼ぶ
	SMu_StopBgm();
	if(Game.stage==7){
		SMe_ChangeScene(STAFFROLE);
		SMu_ChangeVolumeBgm(0);
		return;	
	}
	Ending.count = 0;
	Ending.end_scene = 100;
	Ending.fadein = 255;
	Ending.scene = 0;
	SMu_PlayBgm(10);
	SAVE.BgmFlag[10]++;
	
	return;
}

void SEnd_Draw(){
	Ending.end_scene = 100;
	int scene = Ending.scene;
	if(Ending.scene==0){
		if(Ending.count<60){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(60-Ending.count));
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
		}
		else{
			Ending.scene ++;
		}
	}
	else{
		if(SAVE.Chara==0){
			SEnd_Reimu();
		}
		else{
			SEnd_Marisa();
		}
	}
	if(scene!=Ending.scene){
		Ending.count = 0;
	}
	if(Ending.scene == Ending.end_scene){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*Ending.count);
		DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
		if(Ending.count<60){
			SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01*(60-Ending.count)/60);
		}
		else{
			SMe_ChangeScene(STAFFROLE);
			SMu_ChangeVolumeBgm(0);
		}
	}
	Ending.count++;
	
	return;
}

void SEnd_Reimu(){
	int s = Ending.scene;
	int c = Ending.count;
	int st_size = 20;
	bool b_control = true;//1.5秒後決定で進む、１０秒で自動進む
	char message[128];
	int base_y = 100;
	if(Game.con_times>0){
		Ending.end_scene = 13;
		for(int i=1;i<s+1;i++){
			st_size = 20;
			base_y = 100;
			c = Ending.count;
			s = Ending.scene;
			for(int a=0;a<128;a++){
				message[a] = ' ';
			}
			int white = GetColor(255,255,255);
			int red = GetColor(255,200,200);
			int blue = GetColor(200,200,255);
			int black = GetColor(0,0,0);
			int color = white;
			int color2 = black;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i==s){
				if(c<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Ending.count);
			}
			if(s<=5){
				if(i>=1)	wsprintf(message,"結界の守人と結界主の、無意味な戦いは終わった");
				if(i>=2)	wsprintf(message,"守人が、主を裏切って結界を破ろうとした");
				if(i>=3)	wsprintf(message,"だが、現実はそう甘くなかった");
				if(i>=4)	wsprintf(message,"結界は強固で、全く解けそうになかったのだ");
				if(i>=5)	wsprintf(message,"まるで現を知ることを恐れるように");
				if(i<=2)	DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				else		DrawStringToHandle(50,base_y+st_size*(i+1),message,color,EndingFont,color2);
			}
			else if(s<=13){
				base_y = 150;
				color = blue;
				i -= 5;
				if(i>=1)	wsprintf(message,"紫:…貴方にその結界は解けないわ");
				if(i>=2)	wsprintf(message,"　 才能に驕ってばかりで怠惰な貴方には");
				if(i>=3)	wsprintf(message,"　 幻想と現実の境界を変えることなど出来ない");
				if(i>=4)	wsprintf(message,"　 努力を積み重ねなさい");
				if(i>=5)	wsprintf(message,"　 生と死の境界を彷徨うほどに");
				if(i>=6)	wsprintf(message,"");
				if(i<=3)	DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				else		DrawStringToHandle(50,base_y+st_size*(i+1),message,color,EndingFont,color2);
				i += 5;
				if(s>10&&i>10){
					color = white;
					base_y = 350;
					st_size = 40;
					i -= 10;
					if(i>=1)	wsprintf(message,"幻想郷の主を越えることは不可能なのか？");
					if(i>=2){
						wsprintf(message,"Bad End　ノーコンティニューで紫を倒そう");
						color = GetColor(255,100,100);
					}
					if(i>=3){
						wsprintf(message,"");
					}
					if(i==2){
						int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
						DrawStringToHandle(320-size/2,base_y+st_size*i,message,color,EndingFont,color2);
					}
					else{
						DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
					}
					i += 10;
				}
			}
		}
	}
	else if(Game.stage==3){
		Ending.end_scene = 18;
		if(s==9){
			if(Ending.count==60)	Ending.scene++;			
			b_control = false;
		}
		else if(s==10){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ending.count);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(Ending.count==120)	Ending.scene++;			
			b_control = false;
		}
		else if(s==11){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			b_control = false;
			if(Ending.count==120)	Ending.scene++;			
		}
		else if(s==12){
			if(Ending.count<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(120-Ending.count));
			else                    SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(c<120)	b_control = false;
		}
		else if(s>=16){
			if(s==16&&Ending.count<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ending.count);
			else				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawRotaGraphF(320,240,1.0,0,Ending.img[0],TRUE,FALSE);
			if(c<120)	b_control = false;
		}
		for(int i=1;i<s+1;i++){
			st_size = 20;
			base_y = 100;
			c = Ending.count;
			s = Ending.scene;
			for(int a=0;a<128;a++){
				message[a] = ' ';
			}
			int white = GetColor(255,255,255);
			int red = GetColor(255,200,200);
			int blue = GetColor(200,200,255);
			int black = GetColor(0,0,0);
			int color = white;
			int color2 = black;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i==s){
				if(c<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Ending.count);
			}
			if(s<=2){
				if(i>=1)	wsprintf(message,"結界の守人と結界主の、不毛な戦いは終わった");
				if(i>=2)	wsprintf(message,"守人が、主を裏切って結界を破る");
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
			}
			else if(s<=10){
				color = blue;
				i -= 2;
				if(i>=1){
					base_y = 100;
					wsprintf(message,"紫:…本当に行ってしまうのね？");
					color = blue;
				}
				if(i>=2){
					base_y = 110;
					wsprintf(message,"霊夢:ええ。これで私を止める理由も無くなったでしょ？");
					color = red;
				}
				if(i>=3){
					base_y = 110;
					wsprintf(message,"　　 …幻想郷での生活、なかなか楽しかったわよ");
					color = red;
				}
				if(i>=4){
					base_y = 120;
					wsprintf(message,"紫:もう二度と戻って来れないわよ？");
					color = blue;
				}
				if(i>=5){
					base_y = 130;
					wsprintf(message,"霊夢:行きはよいよい 帰りはこわい、ね");
					color = red;
				}
				if(i>=6){
					base_y = 130;
					wsprintf(message,"　　 でも私は行くわ");
					color = red;
				}
				if(i>=7){
					base_y = 140;
					wsprintf(message,"紫:…お別れね。さようなら、霊夢");
					color = blue;
				}
				if(i>=8){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i += 2;
			}
			else if(s<=11){
				i-=10;
				if(i>=1){
					wsprintf(message,"…そう、これが真実なのね");
					color = black;
					color2 = white;
				}
				if(c<180)	b_control = false;
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=10;
			}
			else if(s<=15){
				base_y = 150;
				i-=11;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"外の世界なんて、初めから存在しなかった");
				}
				if(i>=2){
					st_size = 25;
					wsprintf(message,"天空高く高く昇った少女がどうなるか");
				}
				if(i>=3){
					st_size = 25;
					wsprintf(message,"異世界の扉を、霊夢は開けてしまった");
				}
				if(i>=4){
					st_size = 30;
					wsprintf(message,"…だから言ったじゃない。");
					color = blue;
				}
				if(i>=5){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=11;
			}
			else if(s<=18){
				base_y = 300;
				i-=15;
				if(i>=1){
					st_size = 60;
					wsprintf(message,"もう二度と　ここには戻って来れないと");
					color = blue;
				}
				if(i>=2){
					st_size = 60;
					wsprintf(message,"Normal End　難易度Normal以上・残機２以上で紫を倒そう");
					color = GetColor(255,100,100);
				}
				if(i>=3){
					wsprintf(message,"");
				}
				if(i==2){
					int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
					DrawStringToHandle(320-size/2,base_y+st_size*i,message,color,EndingFont,color2);				
				}
				else{
					DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				}
				i+=15;
			}
		}
	}
	else{
		Ending.end_scene = 24;
		if(s==9){
			if(Ending.count==60)	Ending.scene++;			
			b_control = false;
		}
		else if(s==10){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ending.count);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(Ending.count==120)	Ending.scene++;			
			b_control = false;
		}
		else if(s==11){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			b_control = false;
			if(Ending.count==120)	Ending.scene++;			
		}
		else if(s==12){
			if(Ending.count<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(120-Ending.count));
			else                    SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(c<120)	b_control = false;
		}
		for(int i=1;i<s+1;i++){
			st_size = 20;
			base_y = 100;
			c = Ending.count;
			s = Ending.scene;
			for(int a=0;a<128;a++){
				message[a] = ' ';
			}
			int white = GetColor(255,255,255);
			int red = GetColor(255,200,200);
			int blue = GetColor(200,200,255);
			int black = GetColor(0,0,0);
			int color = white;
			int color2 = black;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i==s){
				if(c<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Ending.count);
			}
			if(s<=2){
				if(i>=1)	wsprintf(message,"結界の守人と結界主の幻闘は終わった");
				if(i>=2)	wsprintf(message,"守人が、主を裏切って結界を破る");
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
			}
			else if(s<=10){
				color = blue;
				i -= 2;
				if(i>=1){
					base_y = 100;
					wsprintf(message,"紫:うっ…まさか巫女が私を越えるなんてね…");
					color = blue;
				}
				if(i>=2){
					base_y = 110;
					wsprintf(message,"霊夢:・・・");
					color = red;
				}
				if(i>=3){
					base_y = 120;
					wsprintf(message,"紫:今の私に、貴方を止める権利は無いわ");
					color = blue;
				}
				if(i>=4){
					base_y = 120;
					wsprintf(message,"　 さあ、行きなさい。外の世界へ");
					color = blue;
				}
				if(i>=5){
					base_y = 130;
					wsprintf(message,"霊夢:ええ。これで貴方達とはお別れね");
					color = red;
				}
				if(i>=6){
					base_y = 130;
					wsprintf(message,"　　 …後は任せたわよ、紫");
					color = red;
				}
				if(i>=7){
					base_y = 140;
					wsprintf(message,"紫:…さようなら");
					color = blue;
				}
				if(i>=8){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i += 2;
			}
			else if(s<=11){
				i-=10;
				if(i>=1){
					wsprintf(message,"…うっ、眩しい…");
					color = black;
					color2 = white;
				}
				if(c<180)	b_control = false;
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=10;
			}
			else if(s<=14){
				base_y = 150;
				i-=11;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"霊夢の目の前には、博麗神社があった");
				}
				if(i>=2){
					st_size = 25;
					wsprintf(message,"ただ、違う点を挙げるとすれば");
				}
				if(i>=3){
					st_size = 25;
					wsprintf(message,"その神社は完全に廃れていた");
				}
				if(i>=4){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=11;
			}
			else if(s<=18){
				base_y = 150;
				i-=14;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"これが外の世界…");
					color = red;
				}
				if(i>=2){
					st_size = 30;
					wsprintf(message,"外の世界は、汚かった");
					color = white;
				}
				if(i>=3){
					st_size = 30;
					wsprintf(message,"信仰を忘れ、科学を追求した結果だろうか");
				}
				if(i>=4){
					st_size = 30;
					wsprintf(message,"空気は澱み、動物の声は聴こえなかった");
				}
				if(i>=5){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=14;
			}
			else if(s<=24){
				base_y = 150;
				i-=18;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"だが、霊夢は後悔していない");
				}
				if(i>=2){
					st_size = 25;
					wsprintf(message,"これが、自分の求めていた世界なのだ");
				}
				if(i>=3){
					st_size = 25;
					wsprintf(message,"夢ではなく、現の世界");
				}
				if(i>=4){
					st_size = 30;
					wsprintf(message,"そこに幻想の声は無かった");
				}
				if(i>=5){
					wsprintf(message,"Good End　オールクリア！");
					base_y = 250;
					color = GetColor(255,100,100);
				}
				if(i>=6){
					wsprintf(message,"");
				}
				if(i>=5){
					int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
					DrawStringToHandle(320-size/2,base_y+st_size*i,message,color,EndingFont,color2);				
				}
				else{
					DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				}
				i+=18;
			}
		}	
	}

	if((Ending.count>30&&Ending.scene!=Ending.end_scene&&(c_pad[SAVE.Key_Shot]==1||c_key[KEY_INPUT_Z]==1)) || Ending.count==600){
		SPlaySound(22);
		Ending.scene++;
	}
	
	return;
}

void SEnd_Marisa(){
	int s = Ending.scene;
	int c = Ending.count;
	int st_size = 20;
	bool b_control = true;//1.5秒後決定で進む、１０秒で自動進む
	char message[128];
	int base_y = 100;
	if(Game.con_times>0){
		Ending.end_scene = 13;
		for(int i=1;i<s+1;i++){
			st_size = 20;
			base_y = 100;
			c = Ending.count;
			s = Ending.scene;
			for(int a=0;a<128;a++){
				message[a] = ' ';
			}
			int white = GetColor(255,255,255);
			int red = GetColor(255,200,200);
			int blue = GetColor(200,200,255);
			int black = GetColor(0,0,0);
			int color = white;
			int color2 = black;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i==s){
				if(c<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Ending.count);
			}
			if(s<=5){
				if(i>=1)	wsprintf(message,"魔法使いと妖怪の、無意味な戦いは終わった");
				if(i>=2)	wsprintf(message,"魔法使いは、妖怪の強力な結界を破ろうとした");
				if(i>=3)	wsprintf(message,"だが、現実はそう甘くなかった");
				if(i>=4)	wsprintf(message,"結界は強固で、全く解けそうになかったのだ");
				if(i>=5)	wsprintf(message,"まるで現を知ることを恐れるように");
				if(i<=2)	DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				else		DrawStringToHandle(50,base_y+st_size*(i+1),message,color,EndingFont,color2);
			}
			else if(s<=13){
				base_y = 150;
				color = blue;
				i -= 5;
				if(i>=1)	wsprintf(message,"紫:…貴方にその結界は解けないわ");
				if(i>=2)	wsprintf(message,"　 目前の幸福に囚われ未来が見えない貴方には");
				if(i>=3)	wsprintf(message,"　 幻想と現実の境界を変えることなど出来ない");
				if(i>=4)	wsprintf(message,"　 努力を積み重ねなさい");
				if(i>=5)	wsprintf(message,"　 生と死の境界を彷徨うほどに");
				if(i>=6)	wsprintf(message,"");
				if(i<=3)	DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				else		DrawStringToHandle(50,base_y+st_size*(i+1),message,color,EndingFont,color2);
				i += 5;
				if(s>10&&i>10){
					color = white;
					base_y = 350;
					st_size = 40;
					i -= 10;
					if(i>=1)	wsprintf(message,"幻想郷の主を越えることは不可能なのか？");
					if(i>=2){
						wsprintf(message,"Bad End　ノーコンティニューで紫を倒そう");
						color = GetColor(255,100,100);
					}
					if(i>=3){
						wsprintf(message,"");
					}
					if(i==2){
						int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
						DrawStringToHandle(320-size/2,base_y+st_size*i,message,color,EndingFont,color2);
					}
					else{
						DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
					}
					i += 10;
				}
			}
		}
	}
	else if(Game.stage==3){
		Ending.end_scene = 18;
		if(s==9){
			if(Ending.count==60)	Ending.scene++;			
			b_control = false;
		}
		else if(s==10){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ending.count);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(Ending.count==120)	Ending.scene++;			
			b_control = false;
		}
		else if(s==11){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			b_control = false;
			if(Ending.count==120)	Ending.scene++;			
		}
		else if(s==12){
			if(Ending.count<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(120-Ending.count));
			else                    SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(c<120)	b_control = false;
		}
		else if(s>=16){
			if(s==16&&Ending.count<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ending.count);
			else				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawRotaGraphF(320,240,1.0,0,Ending.img[0],TRUE,FALSE);
			if(c<120)	b_control = false;
		}
		for(int i=1;i<s+1;i++){
			st_size = 20;
			base_y = 100;
			c = Ending.count;
			s = Ending.scene;
			for(int a=0;a<128;a++){
				message[a] = ' ';
			}
			int white = GetColor(255,255,255);
			int red = GetColor(255,200,200);
			int blue = GetColor(200,200,255);
			int black = GetColor(0,0,0);
			int color = white;
			int color2 = black;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i==s){
				if(c<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Ending.count);
			}
			if(s<=2){
				if(i>=1)	wsprintf(message,"魔法使いと妖怪の、不毛な戦いは終わった");
				if(i>=2)	wsprintf(message,"魔法使いが、妖怪の結界を破る");
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
			}
			else if(s<=10){
				color = blue;
				i -= 2;
				if(i>=1){
					base_y = 100;
					wsprintf(message,"紫:…本当に行ってしまうのね？");
					color = blue;
				}
				if(i>=2){
					base_y = 110;
					wsprintf(message,"魔理沙:ああ。最後にお前とやれて良かったぜ");
					color = red;
				}
				if(i>=3){
					base_y = 110;
					wsprintf(message,"　　　 …これからも幻想郷を守ってくれよな");
					color = red;
				}
				if(i>=4){
					base_y = 120;
					wsprintf(message,"紫:もう二度と戻って来れないわよ？");
					color = blue;
				}
				if(i>=5){
					base_y = 130;
					wsprintf(message,"魔理沙:大丈夫、ある程度の覚悟は出来ている");
					color = red;
				}
				if(i>=6){
					base_y = 130;
					wsprintf(message,"　　　 たとえこちら側に戻って来れなくても…");
					color = red;
				}
				if(i>=7){
					base_y = 140;
					wsprintf(message,"紫:…お別れね。さようなら、魔理沙");
					color = blue;
				}
				if(i>=8){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i += 2;
			}
			else if(s<=11){
				i-=10;
				if(i>=1){
					wsprintf(message,"…ハハ、そういうことか…");
					color = black;
					color2 = white;
				}
				if(c<180)	b_control = false;
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=10;
			}
			else if(s<=15){
				base_y = 150;
				i-=11;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"外の世界なんて、初めから存在しなかった");
				}
				if(i>=2){
					st_size = 25;
					wsprintf(message,"天空高く高く昇った少女がどうなるか");
				}
				if(i>=3){
					st_size = 25;
					wsprintf(message,"異世界の扉を、魔理沙は開けてしまった");
				}
				if(i>=4){
					st_size = 30;
					wsprintf(message,"…だから言ったじゃない。");
					color = blue;
				}
				if(i>=5){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=11;
			}
			else if(s<=18){
				base_y = 300;
				i-=15;
				if(i>=1){
					st_size = 60;
					wsprintf(message,"もう二度と　ここには戻って来れないと");
					color = blue;
				}
				if(i>=2){
					st_size = 60;
					wsprintf(message,"Normal End　難易度Normal以上・残機２以上で紫を倒そう");
					color = GetColor(255,100,100);
				}
				if(i>=3){
					wsprintf(message,"");
				}
				if(i==2){
					int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
					DrawStringToHandle(320-size/2,base_y+st_size*i,message,color,EndingFont,color2);				
				}
				else{
					DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				}
				i+=15;
			}
		}
	}
	else{
		Ending.end_scene = 24;
		if(s==9){
			if(Ending.count==60)	Ending.scene++;			
			b_control = false;
		}
		else if(s==10){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*Ending.count);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(Ending.count==120)	Ending.scene++;			
			b_control = false;
		}
		else if(s==11){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			b_control = false;
			if(Ending.count==120)	Ending.scene++;			
		}
		else if(s==12){
			if(Ending.count<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(120-Ending.count));
			else                    SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			if(c<120)	b_control = false;
		}
		for(int i=1;i<s+1;i++){
			st_size = 20;
			base_y = 100;
			c = Ending.count;
			s = Ending.scene;
			for(int a=0;a<128;a++){
				message[a] = ' ';
			}
			int white = GetColor(255,255,255);
			int red = GetColor(255,200,200);
			int blue = GetColor(200,200,255);
			int black = GetColor(0,0,0);
			int color = white;
			int color2 = black;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(i==s){
				if(c<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*Ending.count);
			}
			if(s<=2){
				if(i>=1)	wsprintf(message,"魔法使いと結界主の幻闘は終わった");
				if(i>=2)	wsprintf(message,"魔法使いが、主を裏切って結界を破る");
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
			}
			else if(s<=10){
				color = blue;
				i -= 2;
				if(i>=1){
					base_y = 100;
					wsprintf(message,"紫:うっ…まさか魔理沙が私を越えるなんてね…");
					color = blue;
				}
				if(i>=2){
					base_y = 110;
					wsprintf(message,"魔理沙:・・・");
					color = red;
				}
				if(i>=3){
					base_y = 120;
					wsprintf(message,"紫:今の私に、貴方を止める権利は無いわ");
					color = blue;
				}
				if(i>=4){
					base_y = 120;
					wsprintf(message,"　 さあ、行きなさい。外の世界へ");
					color = blue;
				}
				if(i>=5){
					base_y = 130;
					wsprintf(message,"魔理沙:ああ。これでお前たちとはお別れだな");
					color = red;
				}
				if(i>=6){
					base_y = 130;
					wsprintf(message,"　　　 …新しい世界へ行ってくるぜ");
					color = red;
				}
				if(i>=7){
					base_y = 140;
					wsprintf(message,"紫:…さようなら");
					color = blue;
				}
				if(i>=8){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i += 2;
			}
			else if(s<=11){
				i-=10;
				if(i>=1){
					wsprintf(message,"…これは…？");
					color = black;
					color2 = white;
				}
				if(c<180)	b_control = false;
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=10;
			}
			else if(s<=14){
				base_y = 150;
				i-=11;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"魔理沙の目の前には、博麗神社があった");
				}
				if(i>=2){
					st_size = 25;
					wsprintf(message,"ただ、違う点を挙げるとすれば");
				}
				if(i>=3){
					st_size = 25;
					wsprintf(message,"その神社は完全に廃れていた");
				}
				if(i>=4){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=11;
			}
			else if(s<=18){
				base_y = 150;
				i-=14;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"これが外の世界…");
					color = red;
				}
				if(i>=2){
					st_size = 30;
					wsprintf(message,"外の世界は、汚かった");
					color = white;
				}
				if(i>=3){
					st_size = 30;
					wsprintf(message,"信仰を忘れ、科学を追求した結果だろうか");
				}
				if(i>=4){
					st_size = 30;
					wsprintf(message,"空気は澱み、動物の声は聴こえなかった");
				}
				if(i>=5){
					wsprintf(message,"");
				}
				DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				i+=14;
			}
			else if(s<=24){
				base_y = 150;
				i-=18;
				if(i>=1){
					st_size = 25;
					wsprintf(message,"だが、魔理沙は後悔していない");
				}
				if(i>=2){
					st_size = 25;
					wsprintf(message,"これが、自分の求めていた世界なのだ");
				}
				if(i>=3){
					st_size = 25;
					wsprintf(message,"不変ではなく、異変のある世界");
				}
				if(i>=4){
					st_size = 30;
					wsprintf(message,"ずっと遠くで、幻想の消える音がした");
				}
				if(i>=5){
					wsprintf(message,"Good End　オールクリア！");
					base_y = 250;
					color = GetColor(255,100,100);
				}
				if(i>=6){
					wsprintf(message,"");
				}
				if(i>=5){
					int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
					DrawStringToHandle(320-size/2,base_y+st_size*i,message,color,EndingFont,color2);				
				}
				else{
					DrawStringToHandle(50,base_y+st_size*i,message,color,EndingFont,color2);
				}
				i+=18;
			}
		}	
	}

	if((Ending.count>30&&Ending.scene!=Ending.end_scene&&(c_pad[SAVE.Key_Shot]==1||c_key[KEY_INPUT_Z]==1)) || Ending.count==600){
		SPlaySound(22);
		Ending.scene++;
	}
	
	return;
}

void SEnd_Main(){
	SEnd_Draw();
	return;
}

void SSR_Main(){
	SSR_Draw();
	return;
}

void SSR_Draw(){
	static int count;
	static int count2;
	static int count3;
	if(Game.game_count==0){
		SMu_PlayBgm(11);
		SAVE.BgmFlag[11]++;
		count = 0;
		count2 = 0;
		count3 = 0;
	}     
	SMe_Effect();
	int flash = 200;
	if(count<100)	flash = count*2;
	SetDrawBright(20+0.1*abs((Game.game_count+1000)%2000-1000), 20+0.1*abs((Game.game_count+2000)%2000-1000), 20+0.1*abs(Game.game_count%2000-1000));
 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
	DrawGraph(0,0,Game.gra_title_back,TRUE);
	SetDrawBright(255,255,255);
 	SetDrawBlendMode(DX_BLENDMODE_ADD,flash);
	for(int i=0;i<50;i++){
		DrawRotaGraphF(T_Effect[i].x, T_Effect[i].y, T_Effect[i].large, 0, Game.gra_t_effect, TRUE, FALSE);
	}
	for(int i=0;i<73;i++){
		char message[128];
		int color = GetColor(255,255,255);
		switch(i){
			case 0:	wsprintf(message,"東方大往生 ～ the Eastern Indolent Life.");	break;
			case 1:	wsprintf(message,"ver1.50a 2009年11月30日");	break;
			case 3:	wsprintf(message,"Staff");	break;
			case 7:	wsprintf(message,"Graphic");	color = GetColor(255,150,150);	break;
			case 9:	wsprintf(message,"KMAP");	break;
			case 10:wsprintf(message,"Hamukorosama");	break;
			case 11:wsprintf(message,"Tyarinko-Kadura");	break;
			case 12:wsprintf(message,"pixiv user");	break;
			case 13:wsprintf(message,"okabi");	break;
			case 17:wsprintf(message,"BGM/Sound");	color = GetColor(255,150,150);	break;
			case 19:wsprintf(message,"ZUN");	break;
			case 20:wsprintf(message,"okabi");	break;
			case 24:wsprintf(message,"Program");	color = GetColor(255,150,150);	break;
			case 26:wsprintf(message,"okabi");	break;
			case 30:wsprintf(message,"BulletDesign");	color = GetColor(255,150,150);	break;
			case 32:wsprintf(message,"okabi");	break;
			case 33:wsprintf(message,"Dampei");	break;
			case 37:wsprintf(message,"SpecialThanks");	color = GetColor(255,150,150);	break;
			case 39:wsprintf(message,"Dampei");	break;
			case 40:wsprintf(message,"Yu");	break;
			case 41:wsprintf(message,"Tyarinko-Kadura");	break;
			case 42:wsprintf(message,"Tomo");	break;
			case 43:wsprintf(message,"Marky");	break;
			case 44:wsprintf(message,"Isshi");	break;
			case 45:wsprintf(message,"Kyon");	break;
			case 46:wsprintf(message,"S.Uemura");	break;
			case 47:wsprintf(message,"F.Yoshida");	break;
			case 48:wsprintf(message,"T.Kushida");	break;
			case 49:wsprintf(message,"S.Yamane");	break;
			case 50:wsprintf(message,"H.Yamanouchi");	break;
			case 51:wsprintf(message,"T.Yamanaka");	break;
			case 52:wsprintf(message,"Y.Shimamoto");	break;
			case 53:wsprintf(message,"S.Hotta");	break;
			case 54:wsprintf(message,"S.Morisada");	break;
			case 55:wsprintf(message,"Y.Yoshida");	break;
			case 56:wsprintf(message,"Y.Muraoka");	break;
			case 58:wsprintf(message,"and...");	break;
			case 60:wsprintf(message,"you");	break;
			case 72:wsprintf(message,"Thank you for playing!!");	color = GetColor(150,250,150);	break;
			default:wsprintf(message,"");	break;	
		}
		int size = GetDrawFormatStringWidthToHandle(SRFont, message);
		float y = 600 + 25*i - count/4;
		if(y>-50&&y<500){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawStringToHandle(320-size/2,y,message,color,SRFont);
		}
	}
	if(600+25*72-count/4>230){
		count++;
		if(c_key[KEY_INPUT_LCONTROL]>0||c_key[KEY_INPUT_RCONTROL]>0)	count += 9;
	}
	else if(count3==0){
		count2++;
		if(count2>60){
			count2 -= 60;
			int flash2 = 255;
			if(count2<50)	flash2 = count2*5.1;
		 	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash2);
			char message[128] = {'\0',};
			int color = GetColor(255,255,255);
			if(Game.con_times==0&&Game.stage>=6){
				if(SAVE.Level==1)	wsprintf(message,"ノーマルクリアおめでとう！次はハードに挑戦だ！");
				if(SAVE.Level==2)	wsprintf(message,"ハードをクリアした貴方は、シューターと自称できます");
				if(SAVE.Level==3)	wsprintf(message,"ルナティックをクリアした貴方は、素晴らしい努力家です");
				if(SAVE.Level==4)	wsprintf(message,"ここまでプレイしてくれて、ありがとう！");
			}
			int size = GetDrawFormatStringWidthToHandle(EndingFont, message);
			DrawStringToHandle(320-size/2,350,message,color,EndingFont);
			count2 += 60;
		}
		if(count2>180){
			if(c_key[KEY_INPUT_Z]>0||c_pad[SAVE.Key_Shot]>0||count2>480){
				count3++;
			}
		}
	}
	else{
		int flash = 255;
		if(count3<150)	flash = 1.7*count3;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
		DrawBox(0,0,640,480,0,TRUE);
		if(count3<280){
			SMu_ChangeVolumeBgm(255*SAVE.BGM*0.01*(280-count3)/280);
		}
		else{
			SSc_SaveScore();
		}	
		count3++;
	}
	return;
}

#endif
