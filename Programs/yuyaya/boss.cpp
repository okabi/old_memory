#include "effect.h"
#include "boss.h"
#include "system.h"
#include "enemy.h"
#include "talk.h"

int BGcount;//BossGage
int BGcount2;
int BGcount3;
int BossCount;//ボス戦カウントダウン
int SpBackCount;
int SpNum;//現在発動中
int NmBonus;
int SpBonus;
int SpBonusRate;
int GetSpBonus;
int GetSpBonusCount;
bool bSun;//コア・オブ・ザ・セカンドサン

list<BOSSDATA> Boss;
SPELLDATA Spell[SPELL_NUM];

void SpLoad();
void SpBackDraw();
void SpDraw();
void BReset();
void BDraw();
void BMove(list<BOSSDATA>::iterator &it);
void BTalkMove(list<BOSSDATA>::iterator &it);
void BToMove(list<BOSSDATA>::iterator &it,float tox,float toy,int time);
void BMake(float x,float y,int img,int ship,ATACKDATA Patack[ATACK_NUMA][ATACK_NUMB]);
void BDrawGage();

void SpLoad(){
	for(int i=0;i<SPELL_NUM;i++){
		for(int j=0;j<BACK_JIMG_NUM;j++)	Spell[i].back_Jimg[j] = -1;
		for(int j=0;j<BACK_PIMG_NUM;j++)	Spell[i].back_Pimg[j] = -1;
		for(int j=0;j<CATIN_IMG_NUM;j++)	Spell[i].catin_img[j] = -1;
		for(int j=0;j<NAME_NUM;j++)		Spell[i].name[j] = '\0';
		Spell[i].back_type = 0;
		Spell[i].catin_type = 0;
		if(i==0){
			Spell[i].level = EASY;
			Spell[i].bonus = 20000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 6;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "畏符「秋の空とゴジラの心」");
		}
		else if(i==1){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 6;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "畏符「秋の空とゴジラの心」");
		}
		else if(i==2){
			Spell[i].level = HARD;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 6;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "怪符「ハロースミッチワールド」");
		}
		else if(i==3){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 6;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "怪符「リトルスミッチ」");
		}
		else if(i==4){
			Spell[i].level = EASY;
			Spell[i].bonus = 20000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "顔符「ＫＢＣ」");
		}
		else if(i==5){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "顔符「デスフェイススマイルズ」");
		}
		else if(i==6){
			Spell[i].level = HARD;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "顔符「爆幻Ⅱで死の宣告ドクロ取った時の顔」");
		}
		else if(i==7){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "顔符「ポリケイゴジレン・トランス」");
		}
		else if(i==8){
			Spell[i].level = EASY;
			Spell[i].bonus = 20000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 14;
			Spell[i].catin_img[1] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 1;
			sprintf(Spell[i].name, "核符「ゴジラvsモスラ ～ 村岡は逃げる」");
		}
		else if(i==9){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 14;
			Spell[i].catin_img[1] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 1;
			sprintf(Spell[i].name, "核符「ゴジラvsモスラ ～ 村岡は逃げる」");
		}
		else if(i==10){
			Spell[i].level = HARD;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 14;
			Spell[i].catin_img[1] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 1;
			sprintf(Spell[i].name, "核符「ニュークリア・フェイス」");
		}
		else if(i==11){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 1;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 14;
			Spell[i].catin_img[1] = 7;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 1;
			sprintf(Spell[i].name, "核符「第三次世界大戦」");
		}
		else if(i==12){
			Spell[i].level = EASY;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 2;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 16;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "弾符「マイクポップコーンは神」");
		}
		else if(i==13){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 2;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 16;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "弾符「マイクポップコーンは至上のスナック」");
		}
		else if(i==14){
			Spell[i].level = HARD;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 2;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 16;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "弾符「バター醤油味っていうのがイカス」");
		}
		else if(i==15){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 2;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 16;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "弾符「魔逝苦ポップコーン」");
		}
		else if(i==16){
			Spell[i].level = EASY;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "野菜符「キャロットビーム」");
		}
		else if(i==17){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "野菜符「キャロットビーム」");
		}
		else if(i==18){
			Spell[i].level = HARD;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "野菜符「千切人参」");
		}
		else if(i==19){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "野菜符「人参雨霰」");
		}
		else if(i==20){
			Spell[i].level = EASY;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 15;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "蒸発「英語雲散霧消」");
		}
		else if(i==21){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 15;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "蒸発「数学雲散霧消」");
		}
		else if(i==22){
			Spell[i].level = HARD;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 15;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "霧符「国語完全消去」");
		}
		else if(i==23){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 15;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "開放「勉強完全粉砕わーいわーい」");
		}
		else if(i==24){
			Spell[i].level = EASY;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "嫁符「早苗は俺の嫁」");
		}
		else if(i==25){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "嫁符「早苗は俺の嫁」");
		}
		else if(i==26){
			Spell[i].level = HARD;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "嫁符「クレイジーマタージ」");
		}
		else if(i==27){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 25;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "嫁符「サモンコチヤサナエ」");
		}
		else if(i==28){
			Spell[i].level = EASY;
			Spell[i].bonus = 40000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 23;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「ポリケイゴジレン・シス」");
		}
		else if(i==29){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 23;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「４９５年の煮込み」");
		}
		else if(i==30){
			Spell[i].level = HARD;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 23;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「完全なる墨染のパスタ -美味-」");
		}
		else if(i==31){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 23;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「サブタレイニアンキャベツ」");
		}
		else if(i==32){
			Spell[i].level = EASY;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "光符「ステマニシューティングスター」");
		}
		else if(i==33){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "光符「ステマニシューティングスター」");
		}
		else if(i==34){
			Spell[i].level = HARD;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "光符「開眼音符流星群」");
		}
		else if(i==35){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 120000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "光符「ギャラクティックナイト」");
		}
		else if(i==36){
			Spell[i].level = EASY;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "妖星「心無い譜面」");
		}
		else if(i==37){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "妖星「ゆや様は本当に頭の良い御方」");
		}
		else if(i==38){
			Spell[i].level = HARD;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "妖星「ミッシングワールド」");
		}
		else if(i==39){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 120000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "妖星「ダンシングマッド」");
		}
		else if(i==40){
			Spell[i].level = EASY;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].catin_img[1] = 31;
			Spell[i].catin_img[2] = 32;
			Spell[i].catin_img[3] = 32;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 2;
			sprintf(Spell[i].name, "顔芸「ニュークリア・キモモ」");
		}
		else if(i==41){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].catin_img[1] = 31;
			Spell[i].catin_img[2] = 32;
			Spell[i].catin_img[3] = 32;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 2;
			sprintf(Spell[i].name, "顔芸「ニュークリア・キモモ」");
		}
		else if(i==42){
			Spell[i].level = HARD;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].catin_img[1] = 31;
			Spell[i].catin_img[2] = 32;
			Spell[i].catin_img[3] = 32;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 2;
			sprintf(Spell[i].name, "顔芸「デンシャマル・エクスカーション」");
		}
		else if(i==43){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 120000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].catin_img[1] = 31;
			Spell[i].catin_img[2] = 32;
			Spell[i].catin_img[3] = 32;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 2;
			sprintf(Spell[i].name, "顔芸「核湯山制御不能」");
		}
		else if(i==44){
			Spell[i].level = EASY;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「走らさせていただいてます」");
		}
		else if(i==45){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「走らさせていただいてます」");
		}
		else if(i==46){
			Spell[i].level = HARD;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「トレインドトレイン」");
		}
		else if(i==47){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 120000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「ベイカー街の暴走機関車」");
		}
		else if(i==48){
			Spell[i].level = EASY;
			Spell[i].bonus = 60000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "爆幻「ランドマインランド」");
		}
		else if(i==49){
			Spell[i].level = NORMAL;
			Spell[i].bonus = 80000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "爆幻「ランドマインランド」");
		}
		else if(i==50){
			Spell[i].level = HARD;
			Spell[i].bonus = 100000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].catin_img[1] = 31;
			Spell[i].catin_img[2] = 32;
			Spell[i].catin_img[3] = 32;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 2;
			sprintf(Spell[i].name, "爆幻「コア・オブ・ザ・セカンドサン」");
		}
		else if(i==51){		
			Spell[i].level = LUNATIC;
			Spell[i].bonus = 120000000;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "爆幻「ザ・ギョフラー」");
		}
		else if(i==52){		
			Spell[i].level = LASTWORD;
			Spell[i].bonus = 999999990;
			Spell[i].back_Jimg[0] = 2;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 14;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「妖蛾乱舞」");
		}
		else if(i==53){		
			Spell[i].level = LASTWORD;
			Spell[i].bonus = 999999990;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「ハレ晴レメシウマ」");
		}
		else if(i==54){		
			Spell[i].level = LASTWORD;
			Spell[i].bonus = 999999990;
			Spell[i].back_Jimg[0] = 3;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 23;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「ヤンデレスカイハイ」");
		}
		else if(i==55){		
			Spell[i].level = LASTWORD;
			Spell[i].bonus = 999999990;
			Spell[i].back_Jimg[0] = 5;
			Spell[i].back_Pimg[0] = 2;
			Spell[i].catin_img[0] = 29;
			Spell[i].back_type = 0;
			Spell[i].catin_type = 0;
			sprintf(Spell[i].name, "「アプローチングレーザー」");
		}
	}

	return;
}

void SpBackDraw(){
	list<BOSSDATA>::iterator it = Boss.begin();
	if(Boss.size()==0)	return;
	if((*it).bSpell==false){
		if(SpBackCount<=60 && (*it).death_count==0 && (*it).life>0){
			NmBonus = 9999;
		}
	}
	if((*it).bSpell==true){
		if(SpBackCount==0 && (*it).death_count==0 && (*it).life>0){
			PlaySound(24);
			if(replay_play==false){
				if(SAVE.SpChallenge[Player[0].chara][SpNum]<999){
					if(Player[0].level!=BABY && Player[0].level!=IMPOSSIBLE)	SAVE.SpChallenge[Player[0].chara][SpNum]++;
				}
			}
			int level = Player[0].level;
			if(level==BABY)		level = EASY;
			if(level==IMPOSSIBLE)	level = LUNATIC;
			int total = Player[0].total_hit;
			if(total > 1000000000/((Player[0].stage+level) * 5000))	total = 1000000000/((Player[0].stage+level) * 5000);
			SpBonus = Player[0].total_hit * (Player[0].stage+level) * 5000;
			if(SpBonus<Spell[SpNum].bonus)	SpBonus = Spell[SpNum].bonus;
			if(SpBonus>999999990)	SpBonus = 999999990;
			if(BossCount>0)	SpBonusRate = ((SpBonus/10) / (BossCount-180))*10;
			else		SpBonusRate = 0;
		}
		int flash1=150;
		int flash2=150;
		if(Player[0].stage==3)	flash2 = 100;
		if(SpBackCount<50){
			flash1 = 3.0*SpBackCount;
			flash2 = 3.0*SpBackCount;
			if(Player[0].stage==3)	flash2 = 2.0*SpBackCount;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash1);
		for(int i=0;i<BACK_JIMG_NUM;i++){
			if(Spell[SpNum].back_Jimg[i]!=-1){
				if(GetSkip())	DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y+shake_y, 1.0, 0, gBack[Spell[SpNum].back_Jimg[i]], FALSE, FALSE);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD,flash2);
		for(int i=0;i<BACK_PIMG_NUM;i++){
			if(Spell[SpNum].back_Pimg[i]!=-1){
				if(Spell[SpNum].back_type==0){
					if(GetSkip())	DrawRotaGraphF(CENTER_X+shake_x, CENTER_Y+shake_y, 1.2, Radian(Scount,TRUE), gBack2[Spell[SpNum].back_Pimg[i]], TRUE, FALSE);
				}
			}
		}
		for(int i=0;i<CATIN_IMG_NUM;i++){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(Spell[SpNum].catin_img[i]!=-1){
				int gx,gy;
				GetGraphSize(gCatin[Spell[SpNum].catin_img[i]], &gx, &gy);
				float x,y;
				float x2,y2;
				if(Spell[SpNum].catin_type==0){
					if(SpBackCount<30){
						x = CENTER_X + 30 + (float)gx*sin(Radian(90.0-3*SpBackCount,TRUE));
						y = CENTER_Y - 30 - (float)gy*sin(Radian(90.0-3*SpBackCount,TRUE));
					}
					else if(SpBackCount<90){
						x = CENTER_X + 30 - (SpBackCount-30);
						y = CENTER_Y - 30 + (SpBackCount-30);
					}
					else if(SpBackCount<120){
						x = CENTER_X - 30 - (float)gx*(SpBackCount-90)/30.0;
						y = CENTER_Y + 30 + (float)gy*(SpBackCount-90)/30.0;
					}
					if(SpBackCount<120){
						if(GetSkip())	DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Spell[SpNum].catin_img[i]], TRUE, FALSE);
					}
				}
				else if(Spell[SpNum].catin_type==1){
					if(SpBackCount<30){
						x = CENTER_X - 30 + (float)gx*sin(Radian(90.0-3*SpBackCount,TRUE));
						y = CENTER_Y - 30 - (float)gy*sin(Radian(90.0-3*SpBackCount,TRUE));
						x2 = CENTER_X + 30 - (float)gx*sin(Radian(90.0-3*SpBackCount,TRUE));
						y2 = CENTER_Y - 30 - (float)gy*sin(Radian(90.0-3*SpBackCount,TRUE));
					}
					else if(SpBackCount<90){
						x = CENTER_X - 30 - (SpBackCount-30);
						y = CENTER_Y - 30 + (SpBackCount-30);
						x2 = CENTER_X + 30 + (SpBackCount-30);
						y2 = CENTER_Y - 30 + (SpBackCount-30);
					}
					else if(SpBackCount<120){
						x = CENTER_X - 90 - (float)gx*(SpBackCount-90)/30.0;
						y = CENTER_Y + 30 + (float)gy*(SpBackCount-90)/30.0;
						x2 = CENTER_X + 90 + (float)gx*(SpBackCount-90)/30.0;
						y2 = CENTER_Y + 30 + (float)gy*(SpBackCount-90)/30.0;
					}
					if(SpBackCount<120){
						if(GetSkip()){
							if(i==0)	DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Spell[SpNum].catin_img[i]], TRUE, FALSE);
							else if(i==1)	DrawRotaGraphF(x2+shake_x, y2+shake_y, 1.0, 0, gCatin[Spell[SpNum].catin_img[i]], TRUE, FALSE);
						}
					}
				}
				else if(Spell[SpNum].catin_type==2){//ゆやや
					if(SpBackCount==0 && (*it).death_count==0 && (*it).life>0)	PlaySound(32);
					if(i==0){
						SetDrawBlendMode(DX_BLENDMODE_ADD,255);
						float large = 1.0;
						if(SpBackCount<30){
							x = CENTER_X;
							y = CENTER_Y + 30 + (float)gy*sin(Radian(90.0-3*SpBackCount,TRUE));
						}
						else if(SpBackCount<90){
							x = CENTER_X;
							y = CENTER_Y + 30 - (SpBackCount-30);
						}
						else if(SpBackCount<150){
							SetDrawBlendMode(DX_BLENDMODE_ADD,255-4.25*(SpBackCount-90));
							large = 1.0 + (SpBackCount-90)/60.0;
							x = CENTER_X;
							y = CENTER_Y + 30 - (SpBackCount-30);
						}
						if(SpBackCount<150){
							if(GetSkip()){
								DrawRotaGraphF(x+shake_x, y+shake_y, large, 0, gCatin[Spell[SpNum].catin_img[i]], TRUE, FALSE);
							}
						}
					}
					else{
						int gx,gy;
						GetGraphSize(gCatin[Spell[SpNum].catin_img[i]], &gx, &gy);
						if(SpBackCount<30)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*SpBackCount);
						else if(SpBackCount<90)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
						else if(SpBackCount<150)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-4.25*(SpBackCount-90));
						for(int j=0;j<4;j++){
							if(i==1){//放射能まーく
								x = 1.0*SpBackCount;
								x -= gx;
								x += 2*j*gx;
								y = CENTER_Y;
							}
							else if(i==2){//こーしょん
								x = -1.0*SpBackCount;
								x -= gx;
								x += j*gx;
								y = CENTER_Y-64-gy/2;
							}
							else if(i==3){//こーしょん
								x = -1.0*SpBackCount;
								x -= gx;
								x += j*gx;
								y = CENTER_Y+64+gy/2;
							}
							if(SpBackCount<150){
								if(GetSkip()){
									DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Spell[SpNum].catin_img[i]], TRUE, FALSE);
								}
							}
						}
					}					
				}
			}
		}
	}
	SpBackCount++;

	return;
}

void SpDraw(){
//スペルカード名とかゲットポイントとか
	float plus = 0.5*pow(BGcount2-20,2);
	list<BOSSDATA>::iterator it = Boss.begin();
	if((*it).bSpell==true){
		int flash;
		if(SpBackCount<30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*SpBackCount);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		int size = GetDrawStringWidthToHandle(Spell[SpNum].name , NAME_NUM, spell_font);
		float x = 420-size;
		float y = 35 - plus;
		if(SpBackCount<60)		y = 350;
		else if(SpBackCount<110)	y = 350-315*sin(Radian(1.8*(SpBackCount-60),TRUE));
		int gx,gy;
		GetGraphSize(gEffect[7], &gx, &gy);
		if(GetSkip())	DrawGraphF(420-gx, y+22-gy, gEffect[7], TRUE);
		DrawSt(x, y, GetColor(255,255,255), 0, spell_font, Spell[SpNum].name);
		if(SpBackCount>=110){
			if(GetSkip())	DrawGraphF(140, y+22, gSystem[12], TRUE);
			if(SpBackCount>=240)	SpBonus -= SpBonusRate;
			if(GetSkip()){
				if(SpBonus>0)	draw_score(185, y+22, (unsigned int)SpBonus, 9, false);
				else		DrawGraphF(238, y+22, gScore[12], TRUE);
				DrawGraphF(295, y+22, gSystem[13], TRUE);
				if(Player[0].level!=BABY && Player[0].level!=IMPOSSIBLE)	draw_score(345, y+22, (unsigned int)SAVE.SpGet[Player[0].chara][SpNum], 3, false);
				else								draw_score(345, y+22, (unsigned int)0, 3, false);
				DrawGraphF(381, y+22, gScore[11], TRUE);
				if(Player[0].level!=BABY && Player[0].level!=IMPOSSIBLE)	draw_score(392, y+22, (unsigned int)SAVE.SpChallenge[Player[0].chara][SpNum], 0, false);
				else								draw_score(392, y+22, (unsigned int)0, 0, false);
			}
		}
	}
	if(GetSpBonusCount>0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
		int keta = draw_spell(0, 0, GetSpBonus);
		if(GetSpBonusCount<30)			SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*GetSpBonusCount);
		else if(GetSpBonusCount<150)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		else if(GetSpBonusCount<180)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(180-GetSpBonusCount));
		float y = 70;
		if(GetSpBonusCount<30)	y += (30-GetSpBonusCount);
		if(GetSkip())	DrawRotaGraphF(CENTER_X, y, 1.0, 0, gSystem[10], TRUE, FALSE);
		draw_spell(CENTER_X-18*((float)keta/2.0), y+22, GetSpBonus);
		
		GetSpBonusCount++;
		if(GetSpBonusCount==180)	GetSpBonusCount = 0;
	}
	return;
}

void SMove0(list<BOSSDATA>::iterator &it){
//秋符「秋の空とゴジラの心」 怪符「ハロースミッチワールド」
//y=sqrt(sqrt(x)) +- sqrt(6-pow(x,2))	(-sqrt(6) <= x <= sqrt(6))
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, 150, 30);
	}
	if(c<90){}
	else{
		if(level==EASY){
			c = (c-90)%260;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 200);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%8==0){
					PlaySound(22);
					int num = 40;
					float ang = -(c-40)/8*72+(*it).f_hanyou[0];
					if(((*it).count-90)%460<230)	ang = (c-40)/8*72+(*it).f_hanyou[0];
					for(int i=0;i<num;i++){
						float sq = sqrt(6);
						float rate = 2.0*sq/(float)num;
						float x = sq-i*rate;
						float y1 = sqrt(fabs(x)) + sqrt(pow(sq,2)-pow(x,2));
						float y2 = sqrt(fabs(x)) - sqrt(pow(sq,2)-pow(x,2));
						float r1 = 15.0*sqrt(x*x+y1*y1);
						float r2 = 15.0*sqrt(x*x+y2*y2);
						float theta1 = atan2(y1,x);
						float theta2 = atan2(y2,x);
						float xx1 = r1*cos(theta1+Radian(ang+90,TRUE));
						float yy1 = r1*sin(theta1+Radian(ang+90,TRUE));
						float xx2 = r2*cos(theta2+Radian(ang+90,TRUE));
						float yy2 = r2*sin(theta2+Radian(ang+90,TRUE));
						if(((*it).count-90)%460<230){
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 2.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 2.0, FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 2.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 2.0, FRED, true, 0, 15);
						}
						else{
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 2.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 2.0, FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 2.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 2.0, FRED, true, 0, 15);
						}
					}
					ESMake((*it).x, (*it).y, ang, 2.0, ESHOT(SMALL,RED), true, 3, 15);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%15==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 3, 5.0, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==NORMAL){
			c = (c-90)%230;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 200);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%5==0){
					PlaySound(22);
					int num = 40;
					float ang = -(c-40)/5*45+(*it).f_hanyou[0];
					if(((*it).count-90)%460<230)	ang = (c-40)/5*45+(*it).f_hanyou[0];
					for(int i=0;i<num;i++){
						float sq = sqrt(6);
						float rate = 2.0*sq/(float)num;
						float x = sq-i*rate;
						float y1 = sqrt(fabs(x)) + sqrt(pow(sq,2)-pow(x,2));
						float y2 = sqrt(fabs(x)) - sqrt(pow(sq,2)-pow(x,2));
						float r1 = 15.0*sqrt(x*x+y1*y1);
						float r2 = 15.0*sqrt(x*x+y2*y2);
						float theta1 = atan2(y1,x);
						float theta2 = atan2(y2,x);
						float xx1 = r1*cos(theta1+Radian(ang+90,TRUE));
						float yy1 = r1*sin(theta1+Radian(ang+90,TRUE));
						float xx2 = r2*cos(theta2+Radian(ang+90,TRUE));
						float yy2 = r2*sin(theta2+Radian(ang+90,TRUE));
						if(((*it).count-90)%460<230){
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0, FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0, FRED, true, 0, 15);
						}
						else{
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0, FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0, FRED, true, 0, 15);
						}
					}
					ESMake((*it).x, (*it).y, ang, 3.0, ESHOT(SMALL,RED), true, 3, 15);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%10==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 5, 6.0, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==HARD){
			c = (c-90)%230;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 200);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%5==0){
					PlaySound(22);
					int num = 40;
					float ang = -(c-40)/5*45+(*it).f_hanyou[0];
					if(((*it).count-90)%460<230)	ang = (c-40)/5*45+(*it).f_hanyou[0];
					for(int i=0;i<num;i++){
						float sq = sqrt(6);
						float rate = 2.0*sq/(float)num;
						float x = sq-i*rate;
						float y1 = sqrt(fabs(x)) + sqrt(pow(sq,2)-pow(x,2));
						float y2 = sqrt(fabs(x)) - sqrt(pow(sq,2)-pow(x,2));
						float r1 = 15.0*sqrt(x*x+y1*y1);
						float r2 = 15.0*sqrt(x*x+y2*y2);
						float theta1 = atan2(y1,x);
						float theta2 = atan2(y2,x);
						float xx1 = r1*cos(theta1+Radian(ang+90,TRUE));
						float yy1 = r1*sin(theta1+Radian(ang+90,TRUE));
						float xx2 = r2*cos(theta2+Radian(ang+90,TRUE));
						float yy2 = r2*sin(theta2+Radian(ang+90,TRUE));
						if(((*it).count-90)%460<230){
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 4.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 4.0, FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 4.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 4.0, FRED, true, 0, 15);
						}
						else{
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 4.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 4.0, FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 4.0, FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 4.0, FRED, true, 0, 15);
						}
					}
					ESMake((*it).x, (*it).y, ang, 4.0, ESHOT(SMALL,RED), true, 3, 15);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 6.5, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==LUNATIC){
			c = (c-90)%230;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 200);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%4==0){
					PlaySound(22);
					int num = 40;
					float ang = -(c-40)/4*36+(*it).f_hanyou[0];
					if(((*it).count-90)%460<230)	ang = (c-40)/4*36+(*it).f_hanyou[0];
					for(int i=0;i<num;i++){
						float sq = sqrt(6);
						float rate = 2.0*sq/(float)num;
						float x = sq-i*rate;
						float y1 = sqrt(fabs(x)) + sqrt(pow(sq,2)-pow(x,2));
						float y2 = sqrt(fabs(x)) - sqrt(pow(sq,2)-pow(x,2));
						float r1 = 15.0*sqrt(x*x+y1*y1);
						float r2 = 15.0*sqrt(x*x+y2*y2);
						float theta1 = atan2(y1,x);
						float theta2 = atan2(y2,x);
						float xx1 = r1*cos(theta1+Radian(ang+90,TRUE));
						float yy1 = r1*sin(theta1+Radian(ang+90,TRUE));
						float xx2 = r2*cos(theta2+Radian(ang+90,TRUE));
						float yy2 = r2*sin(theta2+Radian(ang+90,TRUE));
						if(((*it).count-90)%460<230){
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
						}
						else{
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 3.0+3.0*(c/4%2), FRED, true, 0, 15);
						}
					}
					ESMake((*it).x, (*it).y, ang, 3.0+3.0*(c/4%2), ESHOT(SMALL,RED), true, 3, 15);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==IMPOSSIBLE){
			c = (c-90)%230;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 200);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%2==0){
					PlaySound(22);
					int num = 40;
					float ang = -(c-40)/2*36+(*it).f_hanyou[0];
					if(((*it).count-90)%460<230)	ang = (c-40)/2*36+(*it).f_hanyou[0];
					for(int i=0;i<num;i++){
						float sq = sqrt(6);
						float rate = 2.0*sq/(float)num;
						float x = sq-i*rate;
						float y1 = sqrt(fabs(x)) + sqrt(pow(sq,2)-pow(x,2));
						float y2 = sqrt(fabs(x)) - sqrt(pow(sq,2)-pow(x,2));
						float r1 = 15.0*sqrt(x*x+y1*y1);
						float r2 = 15.0*sqrt(x*x+y2*y2);
						float theta1 = atan2(y1,x);
						float theta2 = atan2(y2,x);
						float xx1 = r1*cos(theta1+Radian(ang+90,TRUE));
						float yy1 = r1*sin(theta1+Radian(ang+90,TRUE));
						float xx2 = r2*cos(theta2+Radian(ang+90,TRUE));
						float yy2 = r2*sin(theta2+Radian(ang+90,TRUE));
						if(((*it).count-90)%460<230){
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
						}
						else{
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
							ESMake((*it).x+xx1, (*it).y+yy1, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
							ESMake((*it).x+xx2, (*it).y+yy2, ang, 5.0+4.0*(c/2%2), FRED, true, 0, 15);
						}
					}
					ESMake((*it).x, (*it).y, ang, 5.0+4.0*(c/2%2), ESHOT(SMALL,RED), true, 3, 15);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 12.0, FRED, true, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove1(list<BOSSDATA>::iterator &it){
//うんざんみたいな（本体）
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, 150, 30);
	}
	if(c==50){
		PlaySound(20);
		EfMake((*it).x, (*it).y, 4, 5);
		for(int i=0;i<30;i++)	EfMake((*it).x, (*it).y, -2, 11, 200);
	}
	if(c==90){
		BToMove(it, CENTER_X, -256, 60);
	}
	if(c<150){}
	else{
		if(c==150){
			int gx,gy;
			GetGraphSize(gBoss[2], &gx, &gy);
			ATACKDATA at[ATACK_NUMA][ATACK_NUMB];
			for(int i=0;i<ATACK_NUMA;i++){
				for(int j=0;j<ATACK_NUMB;j++){
					at[i][j].life = 1000;		
					at[i][j].defence = 100;
					at[i][j].pattern = 0;
					at[i][j].red = 255;
					at[i][j].green = 255;
					at[i][j].blue = 255;
					at[i][j].count = 0;
					at[i][j].bSpell = false;
				}
			}
			at[0][0].pattern = 4;
			BMake(430+gx/2, CENTER_Y, 2, 0, at);
			at[0][0].pattern = 5;
			BMake(10-gx/2, CENTER_Y, 2, 0, at);
		}
	}

	return;
}

void SMove2(list<BOSSDATA>::iterator &it){
//核符「ゴジラvsモスラ　～ 村岡は逃げる」（ゴジラ）
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<180){}
	else{
		(*it).x += 2.0*sin(Radian(3*c,TRUE));
		(*it).y += 1.0*sin(Radian(5*c,TRUE));
	}
	if(c==0){
		ATACKDATA at[ATACK_NUMA][ATACK_NUMB];
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				at[i][j].life = 1000;		
				at[i][j].defence = 100;
				at[i][j].pattern = 0;
				at[i][j].red = 255;
				at[i][j].green = 255;
				at[i][j].blue = 255;
				at[i][j].count = 0;
				at[i][j].bSpell = false;
			}
		}
		at[0][0].pattern = 7;
		BMake(600, 200, 0, 0, at);
	}
	
	if(c<90){}
	else{
		c -= 90;
		if(c>=60 && c<=90){
			(*it).y = 150 - 60.0*pow(c-60,2)/900.0;
		}
		if(c>=180){
			if(c==180)	PlaySound(18);
			if(level==EASY){
				if(c%10==0){
					ESMake(10+get_rand(420), 10+get_rand(140), 90, 0.5+0.1*get_rand(10), FRED, true, 0, 15);
					ESMake(10+get_rand(420), 10+get_rand(140), -90, 0.5+0.1*get_rand(10), FRED, true, 0, 15);
				}
				if(c%5==0){
					ESMake(10+get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(10), FRED, true, 0, 15);
					ESMake(10+get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(10), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(10), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(10), FRED, true, 0, 15);
				}
			}	
			else if(level==NORMAL){
				if(c%8==0){
					ESMake(10+get_rand(420), 10+get_rand(140), 90, 0.5+0.1*get_rand(15), FRED, true, 0, 15);
					ESMake(10+get_rand(420), 10+get_rand(140), -90, 0.5+0.1*get_rand(15), FRED, true, 0, 15);
				}
				if(c%5==0){
					ESMake(10+get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(15), FRED, true, 0, 15);
					ESMake(10+get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(15), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(15), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(15), FRED, true, 0, 15);
				}
			}	
			else if(level==HARD){
				if(c%3==0){
					ESMake(10+get_rand(420), 10+get_rand(140), 90, 0.5+0.1*get_rand(20), FRED, true, 0, 15);
					ESMake(10+get_rand(420), 10+get_rand(140), -90, 0.5+0.1*get_rand(20), FRED, true, 0, 15);
				}
				if(c%3==0){
					ESMake(10+get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(20), FRED, true, 0, 15);
					ESMake(10+get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(20), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(20), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(20), FRED, true, 0, 15);
				}
				/*
				if(Player[0].hyper_count>0){
					if((*it).count%8==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 6.5, FRED, true, 0, 0);
					}
				}
				*/
			}	
			else if(level==LUNATIC){
				if(c%1==0){
					ESMake(10+get_rand(420), 10+get_rand(140), 90, 0.5+0.1*get_rand(25), FRED, true, 0, 15);
					ESMake(10+get_rand(420), 10+get_rand(140), -90, 0.5+0.1*get_rand(25), FRED, true, 0, 15);
				}
				if(c%1==0){
					ESMake(10+get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(25), FRED, true, 0, 15);
					ESMake(10+get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(25), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), 90, 0.5+0.1*get_rand(25), FRED, true, 0, 15);
					ESMake(430-get_rand(120), 10+get_rand(140), -90, 0.5+0.1*get_rand(25), FRED, true, 0, 15);
				}
				/*
				if(Player[0].hyper_count>0){
					if((*it).count%5==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, FRED, true, 0, 0);
					}
				}
				*/
			}	
			else if(level==IMPOSSIBLE){
				if(c%1==0){
					ESMake(10+get_rand(420), 10+get_rand(140), 90, 0.5+0.1*get_rand(45), FRED, true, 0, 15);
					ESMake(10+get_rand(420), 10+get_rand(140), -90, 0.5+0.1*get_rand(45), FRED, true, 0, 15);
				}
				if(c%1==0){
					ESMake(10+get_rand(160), 10+get_rand(140), 90, 0.5+0.1*get_rand(45), FRED, true, 0, 15);
					ESMake(10+get_rand(160), 10+get_rand(140), -90, 0.5+0.1*get_rand(45), FRED, true, 0, 15);
					ESMake(430-get_rand(160), 10+get_rand(140), 90, 0.5+0.1*get_rand(45), FRED, true, 0, 15);
					ESMake(430-get_rand(160), 10+get_rand(140), -90, 0.5+0.1*get_rand(45), FRED, true, 0, 15);
				}
				/*
				if(Player[0].hyper_count>0){
					if((*it).count%1==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 12.0, FRED, true, 0, 0);
					}
				}
				*/
			}	
		}
	}

	return;
}

void SMove3(list<BOSSDATA>::iterator &it){
//弾符「マイクポップコーンは神」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<50){}
	else{
		c -= 50;
		if(level==EASY){
			const int per = 300;
			int time = c/per;
			c = c%per;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c==40){
				(*it).f_hanyou[0] = get_rand(180);
				float rand = 0.1*get_rand(300);
				for(int i=0;i<10;i++){
					float angle = Radian(36*i+rand,TRUE);
					int pat;
					if(time%2==0)	pat = 6;
					else		pat = 7;
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, pat, pat+2);
				}
			}
			if(c==per-70){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
		}	
		else if(level==NORMAL){
			const int per = 300;
			int time = c/per;
			c = c%per;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c==40){
				(*it).f_hanyou[0] = get_rand(180);
				float rand = 0.1*get_rand(300);
				for(int i=0;i<12;i++){
					float angle = Radian(30*i+rand,TRUE);
					int pat;
					if(time%2==0)	pat = 6;
					else		pat = 7;
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, pat, pat+2);
				}
			}
			if(c==per-70){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
		}	
		else if(level==HARD){
			const int per = 300;
			int time = c/per;
			c = c%per;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c==40){
				(*it).f_hanyou[0] = get_rand(120);
				float rand = 0.1*get_rand(300);
				for(int i=0;i<12;i++){
					float angle = Radian(30*i+rand,TRUE);
					int pat;
					if(time%2==0)	pat = 6;
					else		pat = 7;
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, pat, pat+2);
				}
			}
			if(c==per-70){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(KUNAI,RED), false, 0, 0);
				}
			}
			*/
		}	
		else if(level==LUNATIC){
			const int per = 300;
			int time = c/per;
			c = c%per;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c==40){
				(*it).f_hanyou[0] = get_rand(120);
				float rand = 0.1*get_rand(300);
				for(int i=0;i<8;i++){
					float angle = Radian(45*i+rand,TRUE);
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, 6, 8);
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, 7, 9);
				}
			}
			if(c==per-70){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(KUNAI,RED), false, 0, 0);
				}
			}
			*/
		}	
		else if(level==IMPOSSIBLE){
			const int per = 300;
			int time = c/per;
			c = c%per;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c==40){
				(*it).f_hanyou[0] = get_rand(72);
				float rand = 0.1*get_rand(300);
				for(int i=0;i<10;i++){
					float angle = Radian(36*i+rand,TRUE);
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, 6, 8);
					EMake((*it).x+1*cos(angle), (*it).y+1*sin(angle), 256, 13, 7, 9);
				}
			}
			if(c==per-70){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(KUNAI,RED), false, 0, 0);
				}
			}
			*/
		}	
	}

	return;
}

void SMove4(list<BOSSDATA>::iterator &it){
//野菜符「キャロットビーム」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c==0){
		BToMove(it, CENTER_X, 150, 30);
	}
	if(c<90){}
	else{
		if(level==EASY){
			c = (c-90)%400;
			if(c%6==0){
				PlaySound(22);
				for(int i=0;i<2;i++){
					float angle = Radian(3.0*c+180.0*i, TRUE);
					float lx = 350.0;
					float ly = 50.0;
					float x = (*it).x + lx*cos(angle);
					float y = (*it).y - 34 + ly*sin(angle);
					ESMake(x, y, 90.0+180.0*i, 1.0, ESHOT(SSTAR,BLUE), false, 0, 15);
				}
			}
			if(c<60){}
			else if(c==60){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			else if(c<150){}
			else if(c==150){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
			}
			else if(c<190){}
			else if(c==190){
				PlaySound(10);
				float angle = Radian(Atan2(Player[0].y-((*it).y-34), Player[0].x-(*it).x),FALSE) + 180.0;
				for(int i=0;i<3;i++){
					ELMake((*it).x, (*it).y-34, 120.0, angle, 8.0, ESHOT(RICE,ORANGE), 8+i, 0);
				}
			}
			else if(c<250){}
			else if(c<400){
				c -= 250;
				if(c%60==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(450);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 45.0, 8, 2.0, ESHOT(STAR,RED), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		else if(level==NORMAL){
			c = (c-90)%400;
			if(c%3==0){
				PlaySound(22);
				for(int i=0;i<2;i++){
					float angle = Radian(3.0*c+180.0*i, TRUE);
					float lx = 350.0;
					float ly = 50.0;
					float x = (*it).x + lx*cos(angle);
					float y = (*it).y - 34 + ly*sin(angle);
					ESMake(x, y, 90.0+180.0*i, 1.5, ESHOT(SSTAR,BLUE), false, 0, 15);
				}
			}
			if(c<60){}
			else if(c==60){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			else if(c<150){}
			else if(c==150){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
			}
			else if(c<190){}
			else if(c==190){
				PlaySound(10);
				float angle = Radian(Atan2(Player[0].y-((*it).y-34), Player[0].x-(*it).x),FALSE) + 180.0;
				for(int i=0;i<5;i++){
					ELMake((*it).x, (*it).y-34, 120.0, angle, 12.0, ESHOT(RICE,ORANGE), 8+i, 0);
				}
			}
			else if(c<250){}
			else if(c<400){
				c -= 250;
				if(c%30==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(300);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 30.0, 12, 4.0, ESHOT(STAR,RED), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		else if(level==HARD){
			c = (c-90)%400;
			if(c%2==0){
				PlaySound(22);
				for(int i=0;i<2;i++){
					float angle = Radian(3.0*c+180.0*i, TRUE);
					float lx = 250.0;
					float ly = 50.0;
					float x = (*it).x + lx*cos(angle);
					float y = (*it).y - 34 + ly*sin(angle);
					ESMake(x, y, 5.0*c+180.0*i, 1.5, ESHOT(RICE,ORANGE), false, 0, 15);
				}
			}
			if(c<60){}
			else if(c==60){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			else if(c<150){}
			else if(c==150){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
			}
			else if(c<190){}
			else if(c==190){
				PlaySound(10);
				float angle = Radian(Atan2(Player[0].y-((*it).y-34), Player[0].x-(*it).x),FALSE) + 180.0;
				for(int i=0;i<5;i++){
					ELMake((*it).x, (*it).y-34, 120.0, angle, 12.0, ESHOT(RICE,BLUE), 8+i, 0);
				}
			}
			else if(c<250){}
			else if(c<400){
				c -= 250;
				if(c%20==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(240);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 24.0, 15, 4.0, ESHOT(STAR,ORANGE), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		else if(level==LUNATIC){
			c = (c-90)%400;
			if(c%1==0){
				PlaySound(22);
				for(int i=0;i<2;i++){
					float angle = Radian(3.0*c+180.0*i, TRUE);
					float lx = 250.0;
					float ly = 50.0;
					float x = (*it).x + lx*cos(angle);
					float y = (*it).y - 34 + ly*sin(angle);
					ESMake(x, y, 11.0*c+180.0*i, 2.0, ESHOT(RICE,ORANGE), false, 0, 15);
				}
			}
			if(c<60){}
			else if(c==60){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			else if(c<150){}
			else if(c==150){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
			}
			else if(c<190){}
			else if(c==190){
				PlaySound(10);
				float angle = Radian(Atan2(Player[0].y-((*it).y-34), Player[0].x-(*it).x),FALSE) + 180.0;
				for(int i=0;i<5;i++){
					ELMake((*it).x, (*it).y-34, 120.0, angle, 12.0, ESHOT(RICE,BLUE), 8+i, 0);
				}
			}
			else if(c<250){}
			else if(c<400){
				c -= 250;
				if(c%10==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(240);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 24.0, 15, 5.0, ESHOT(STAR,ORANGE), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		else if(level==IMPOSSIBLE){
			c = (c-90)%400;
			if(c%1==0){
				PlaySound(22);
				for(int i=0;i<4;i++){
					float angle = Radian(3.0*c+90.0*i, TRUE);
					float lx = 250.0;
					float ly = 50.0;
					float x = (*it).x + lx*cos(angle);
					float y = (*it).y - 34 + ly*sin(angle);
					ESMake(x, y, 11.0*c+90.0*i, 2.5, ESHOT(RICE,ORANGE), false, 0, 15);
				}
			}
			if(c<60){}
			else if(c==60){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			else if(c<150){}
			else if(c==150){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
			}
			else if(c<190){}
			else if(c==190){
				PlaySound(10);
				float angle = Radian(Atan2(Player[0].y-((*it).y-34), Player[0].x-(*it).x),FALSE) + 180.0;
				for(int i=0;i<5;i++){
					ELMake((*it).x, (*it).y-34, 120.0, angle, 12.0, ESHOT(RICE,BLUE), 8+i, 0);
				}
			}
			else if(c<250){}
			else if(c<400){
				c -= 250;
				if(c%10==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(180);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 18.0, 20, 6.0, ESHOT(STAR,ORANGE), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		
		if(Player[0].hyper_count>0){
			/*
			if(level==EASY){
				if((*it).count%15==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 3, 5.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==NORMAL){
				if((*it).count%10==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 5, 6.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove5(list<BOSSDATA>::iterator &it){
//気符「英語雲散霧消」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, 150, 30);
	}
	if(c<90){}
	else{
		if(level==EASY){
			c = (c-90)%240;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y-34, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);			
			}
			if(c==40){
				for(int i=0;i<7;i++){
					float angle = Radian(60+10*i,TRUE);
					float x = (*it).x + cos(angle);
					float y = (*it).y - 34 + sin(angle);
					EMake(x, y, 256, -1, 11, 12);
					EMake(x, y, 256, -1, 12, 12);
				}
			}
			if(c==150){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
		}
		else if(level==NORMAL){
			c = (c-90)%240;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y-34, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);			
			}
			if(c==40){
				for(int i=0;i<7;i++){
					float angle = Radian(60+10*i,TRUE);
					float x = (*it).x + cos(angle);
					float y = (*it).y - 34 + sin(angle);
					EMake(x, y, 256, -1, 11, 12);
					EMake(x, y, 256, -1, 12, 12);
				}
			}
			if(c==150){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			if((*it).count>=200){
				if(c%90==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(120);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 12.0, 30, 1.0, ESHOT(MEDIUM2,BLUE), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		else if(level>=HARD){
			c = (c-90)%480;
			if(c==0 || c==240){
				PlaySound(20);
				EfMake((*it).x, (*it).y-34, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);			
			}
			if(c==40){
				for(int i=0;i<7;i++){
					float angle = Radian(60+10*i,TRUE);
					float x = (*it).x + cos(angle);
					float y = (*it).y - 34 + sin(angle);
					EMake(x, y, 256, -1, 11, 12);
					EMake(x, y, 256, -1, 12, 12);
				}
			}
			else if(c==280){
				for(int i=0;i<12;i++){
					float angle = Radian(30*i,TRUE);
					float x = (*it).x + cos(angle);
					float y = (*it).y - 34 + sin(angle);
					EMake(x, y, 256, -1, 13, 12);
				}
			}
			if(c==150 || c==390){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 80+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 90);
			}
			if((*it).count>=200){
				if(c%90==0){
					PlaySound(22);
					ang_plus = 0.1*get_rand(120);
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 12.0, 30, 1.0, ESHOT(MEDIUM2,BLUE), false, 0, 0);
					ang_plus = 0;
				}
			}
		}
		
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove6(list<BOSSDATA>::iterator &it){
//嫁符「早苗は俺の嫁」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, CENTER_Y-50, 60);
	}
	if(c<90){}
	else{
		if(level==EASY || level==NORMAL || level==HARD){
			c = c-90;
			if(c==0){
				//ELMake(10, Player[0].y, 24.0, 0, 10.0, ESHOT(RICE,RED), 13, 60);
				//ELMake(430, Player[0].y, 24.0, 180, 10.0, ESHOT(RICE,RED), 13, 60);
			}
			c = c%630;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y-34, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);			
			}
			if(c==40){
				float l = 80.0;
				float angle = Radian(-162,TRUE);
				float angle2 = Radian(-162+36,TRUE);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y - 34 + l*sin(angle);
				float x2 = (*it).x + l*cos(angle2);
				float y2 = (*it).y - 34 + l*sin(angle2);
				EMake(x, y, 256, -1, 14, 13);
				EMake(x2, y2, 256, -1, 15, 14);
			}
			if(c==250)	(*it).i_hanyou[0] = 1;
			else if(c==340)	(*it).i_hanyou[0] = 2;
			else		(*it).i_hanyou[0] = 0;
			if(c==400){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-80+get_rand(30);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		else if(level==LUNATIC || level==IMPOSSIBLE){
			c = c-90;
			if(c==0){
				//ELMake(10, Player[0].y, 24.0, 0, 10.0, ESHOT(RICE,RED), 13, 60);
				//ELMake(430, Player[0].y, 24.0, 180, 10.0, ESHOT(RICE,RED), 13, 60);
			}
			c = c%520;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y-34, 4, 5);
				for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);			
			}
			if(c==40){
				float l = 100.0;
				if(level==IMPOSSIBLE)	l = 80.0;
				float angle = Radian(-45.0*3,TRUE);
				float angle2 = Radian(-45.0*3+120.0,TRUE);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y - 34 + l*sin(angle);
				float x2 = (*it).x + l*cos(angle2);
				float y2 = (*it).y - 34 + l*sin(angle2);
				EMake(x, y, 256, -1, 16, 15);
				EMake(x2, y2, 256, -1, 17, 16);
			}
			if(c>=244 && c<=246)		(*it).i_hanyou[0] = 1;
			else if(c>=328 && c<=330)	(*it).i_hanyou[0] = 2;
			else				(*it).i_hanyou[0] = 0;
			if(c==400){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-80+get_rand(30);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove7(list<BOSSDATA>::iterator &it){
//「４９５年の煮込み」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, CENTER_Y, 60);
	}
	if(c<90){}
	else{
		(*it).bMuteki = false;
		if(level==EASY){
			c = c-90;
			if(c==0){
				for(int i=0;i<20;i++)	ELMake(0, 0, 12.0, 18.0*i, 8.0, ESHOT(RICE,ORANGE), 14, 60);
			}
			if(c>=60){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				bool flag = false;
				(*it).f_hanyou[0] = 0.5 + 1.5*(100.0-per)*0.01;
				if(BossCount<15*60){
					if((*it).i_hanyou[0]!=4){
						(*it).i_hanyou[0] = 4;
						PlaySound(18);
					}
					if(c%50==0)	flag = true;
					(*it).f_hanyou[0] = 2.0;
				}
				else if(per<25.0){
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
					if(c%80==0)	flag = true;
				}
				else if(per<50.0){
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
					if(c%110==0)	flag = true;
				}
				else if(per<75.0){
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
					if(c%140==0)	flag = true;
				}
				else{
					if(c%170==0)	flag = true;
				}
				if(flag==true){
					PlaySound(22);
					float x = (*it).x + 150-get_rand(300);
					float y = (*it).y-34 - get_rand(100);
					ang_plus = 0.1*get_rand(100);
					ESNWay(x, y, Player[0].x, Player[0].y, 10.0, 36, 1.5, ESHOT(RICE,RED), false, 26, 15);
					ang_plus = 0;
				}
			}
			if(c!=0 && c%240==0){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-80+get_rand(30);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		else if(level==NORMAL){
			c = c-90;
			if(c==0){
				for(int i=0;i<30;i++)	ELMake(0, 0, 12.0, 12.0*i, 8.0, ESHOT(RICE,ORANGE), 14, 60);
			}
			if(c>=60){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				bool flag = false;
				(*it).f_hanyou[0] = 1.0 + 2.0*(100.0-per)*0.01;
				if(BossCount<15*60){
					if((*it).i_hanyou[0]!=4){
						(*it).i_hanyou[0] = 4;
						PlaySound(18);
					}
					if(c%30==0)	flag = true;
					(*it).f_hanyou[0] = 3.0;
				}
				else if(per<25.0){
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
					if(c%60==0)	flag = true;
				}
				else if(per<50.0){
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
					if(c%90==0)	flag = true;
				}
				else if(per<75.0){
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
					if(c%120==0)	flag = true;
				}
				else{
					if(c%150==0)	flag = true;
				}
				if(flag==true){
					PlaySound(22);
					float x = (*it).x + 150-get_rand(300);
					float y = (*it).y-34 - get_rand(100);
					ang_plus = 0.1*get_rand(60);
					ESNWay(x, y, Player[0].x, Player[0].y, 6.0, 60, 1.5, ESHOT(RICE,RED), false, 26, 15);
					ang_plus = 0;
				}
			}
			if(c!=0 && c%240==0){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-80+get_rand(30);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		else if(level==HARD){
			c = c-90;
			if(c==0){
				for(int i=0;i<30;i++)	ELMake(0, 0, 12.0, 12.0*i, 8.0, ESHOT(RICE,GRAY), 14, 60);
			}
			if(c>=60){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				bool flag = false;
				(*it).f_hanyou[0] = 1.0 + 2.0*(100.0-per)*0.01;
				if(BossCount<15*60){
					if((*it).i_hanyou[0]!=4){
						(*it).i_hanyou[0] = 4;
						PlaySound(18);
					}
					if(c%30==0)	flag = true;
					(*it).f_hanyou[0] = 3.0;
				}
				else if(per<25.0){
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
					if(c%60==0)	flag = true;
				}
				else if(per<50.0){
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
					if(c%90==0)	flag = true;
				}
				else if(per<75.0){
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
					if(c%120==0)	flag = true;
				}
				else{
					if(c%150==0)	flag = true;
				}
				if(flag==true){
					PlaySound(22);
					float x = (*it).x + 150-get_rand(300);
					float y = (*it).y-34 - get_rand(100);
					ang_plus = 0.1*get_rand(40);
					ESNWay(x, y, Player[0].x, Player[0].y, 4.0, 90, 1.5, ESHOT(RICE,GRAY), false, 26, 15);
					ang_plus = 0;
				}
			}
			if(c!=0 && c%240==0){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-80+get_rand(30);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		else if(level==LUNATIC || level==IMPOSSIBLE){
			c = c-90;
			if(c==0){
				for(int i=0;i<30;i++)	ELMake(0, 0, 12.0, 12.0*i, 8.0, ESHOT(RICE,RED), 14, 60);
			}
			if(c>=60){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				bool flag = false;
				(*it).f_hanyou[0] = 2.0 + 2.0*(100.0-per)*0.01;
				if(BossCount<15*60){
					if((*it).i_hanyou[0]!=4){
						(*it).i_hanyou[0] = 4;
						PlaySound(18);
					}
					if(c%3==0)	flag = true;
					(*it).f_hanyou[0] = 4.0;
				}
				else if(per<25.0){
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
					if(c%5==0)	flag = true;
				}
				else if(per<50.0){
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
					if(c%10==0)	flag = true;
				}
				else if(per<75.0){
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
					if(c%20==0)	flag = true;
				}
				else{
					if(c%30==0)	flag = true;
				}
				if(flag==true){
					PlaySound(22);
					if(level==LUNATIC){
						if((*it).i_hanyou[1]%2==0){
							ang_plus = 4.0*(*it).i_hanyou[2];
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 60.0, 6, 1.5, ESHOT(BIG,GREEN), false, 27, 15, 0.0, 0, true);
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 60.0, 6, 1.5, ESHOT(BIG,GREEN), false, 28, 15, 0.0, 0, false);
						}
						else{
							ang_plus = 4.0*(*it).i_hanyou[2];
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 30.0, 12, 1.5, ESHOT(MEDIUM,GREEN), false, 27, 15, 0.0, 0, true);
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 30.0, 12, 1.5, ESHOT(MEDIUM,GREEN), false, 28, 15, 0.0, 0, false);
						}
					}
					else if(level==IMPOSSIBLE){
						if((*it).i_hanyou[1]%2==0){
							ang_plus = -4.0*(*it).i_hanyou[2];
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 24.0, 15, 1.5, ESHOT(BIG,GREEN), false, 27, 15, 0.0, 0, true);
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 24.0, 15, 1.5, ESHOT(BIG,GREEN), false, 28, 15, 0.0, 0, false);
						}
						else{
							ang_plus = -4.0*(*it).i_hanyou[2];
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 14.4, 25, 1.5, ESHOT(MEDIUM,GREEN), false, 27, 15, 0.0, 0, true);
							ESNWay((*it).x, (*it).y-34, (*it).x+1, (*it).y-34, 14.4, 25, 1.5, ESHOT(MEDIUM,GREEN), false, 28, 15, 0.0, 0, false);
						}
					}
					ang_plus = 0;
					(*it).i_hanyou[1]++;
					(*it).i_hanyou[2]++;
				}
			}
			if(c!=0 && c%240==0){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-80+get_rand(30);
				float plus = 30+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<140)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>300)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove8(list<BOSSDATA>::iterator &it){
//光符「ステマニシューティングスター」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, CENTER_Y, 60);
	}
	if(c<90){}
	else{
		if(level==EASY || level==NORMAL || level==HARD){
			c = c-90;
			c = c%480;
			if(c>=0 && c<60){
				if(c%10==0){
					float angle = -140 + 20*c/10;
					ESL2Make((*it).x-32, (*it).y-45, 6.0, angle, 5.0, BLUE, 1);
				}
			}
			if(c>=240 && c<300){
				c -= 240;
				if(c%10==0){
					float angle = -40 - 20*c/10;
					ESL2Make((*it).x-32, (*it).y-45, 6.0, angle, 5.0, BLUE, 2);
				}
				c += 240;
			}
			if(c==120 || c==360){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-40+get_rand(40);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<CENTER_X-50)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>CENTER_X+50)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		else if(level==LUNATIC){
			c = c-90;
			c = c%480;
			if(c>=0 && c<60){
				if(c%5==0){
					float angle = -190 + 20*c/5;
					ESL2Make((*it).x-32, (*it).y-45, 6.0, angle, 5.0, BLUE, 1);
				}
			}
			if(c>=240 && c<300){
				c -= 240;
				if(c%5==0){
					float angle = 10 - 20*c/5;
					ESL2Make((*it).x-32, (*it).y-45, 6.0, angle, 5.0, BLUE, 2);
				}
				c += 240;
			}
			if(c==120 || c==360){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-40+get_rand(40);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<CENTER_X-50)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>CENTER_X+50)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		else if(level==IMPOSSIBLE){
			c = c-90;
			c = c%480;
			if(c>=0 && c<60){
				if(c%4==0){
					float angle = -210 + 20*c/4;
					ESL2Make((*it).x-32, (*it).y-45, 6.0, angle, 5.0, BLUE, 1);
				}
			}
			if(c>=240 && c<300){
				c -= 240;
				if(c%4==0){
					float angle = 90 - 20*c/4;
					ESL2Make((*it).x-32, (*it).y-45, 6.0, angle, 5.0, BLUE, 2);
				}
				c += 240;
			}
			if(c==120 || c==360){
				float x = (*it).x;
				float y = (*it).y;
				y = CENTER_Y-40+get_rand(40);
				float plus = 10+get_rand(20);
				if(Player[0].x<(*it).x){
					if(x-plus<CENTER_X-50)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>CENTER_X+50)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 120);
			}
		}
		
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove9(list<BOSSDATA>::iterator &it){
//妖星「ゆや様は本当に頭の良い御方」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c==0){
		BToMove(it, CENTER_X, CENTER_Y, 60);
	}
	if(c<90){}
	else{
		c = c-90;
		if(c==0){
			for(int i=0;i<16;i++)	ELMake(CENTER_X, CENTER_Y, 12.0, 90.0*i, 8.0, ESHOT(RICE,PURPLE), 16+i, 180);
			BToMove(it, CENTER_X, 150, 60);
		}
		if(level==EASY){
			int dev = 20;
			if(c%dev==0){
				//PlaySound(22);
				for(int i=0;i<7;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x-32, (*it).y-45, 35.0*(c/dev)+30.0*i, 1.5, ESHOT(KNIFE,RED), false, 0, 5, 0.0, 0, flag);				
					ESMake((*it).x-32, (*it).y-45, 180.0+45.0*(c/dev)+32.0*i, 1.0, ESHOT(KNIFE,BLUE), false, 0, 5, 0.0, 0, false);				
				}
			}
		}
		else if(level==NORMAL){
			int dev = 12;
			if(c%dev==0){
				//PlaySound(22);
				for(int i=0;i<7;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x-32, (*it).y-45, 25.0*(c/dev)+20.0*i, 1.5, ESHOT(KNIFE,RED), false, 0, 5, 0.0, 0, flag);				
					ESMake((*it).x-32, (*it).y-45, 180.0+35.0*(c/dev)+22.0*i, 1.0, ESHOT(KNIFE,BLUE), false, 0, 5, 0.0, 0, false);				
				}
			}
		}
		else if(level==HARD){
			int dev = 10;
			if(c%dev==0){
				//PlaySound(22);
				for(int i=0;i<7;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x-32, (*it).y-45, 25.0*(c/dev)+20.0*i, 2.0, ESHOT(KNIFE,RED), false, 0, 5, 0.0, 0, flag);				
					ESMake((*it).x-32, (*it).y-45, 180.0+35.0*(c/dev)+22.0*i, 1.5, ESHOT(KNIFE,BLUE), false, 0, 5, 0.0, 0, false);				
				}
			}
		}
		else if(level==LUNATIC){
			int dev = 6;
			if(c%dev==0){
				//PlaySound(22);
				for(int i=0;i<7;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x-32, (*it).y-45, 20.0*(c/dev)+15.0*i, 2.5, ESHOT(KNIFE,RED), false, 0, 5, 0.0, 0, flag);				
					ESMake((*it).x-32, (*it).y-45, 180.0+30.0*(c/dev)+17.0*i, 2.0, ESHOT(KNIFE,BLUE), false, 0, 5, 0.0, 0, false);				
				}
			}
		}
		else if(level==IMPOSSIBLE){
			int dev = 4;
			if(c%dev==0){
				//PlaySound(22);
				for(int i=0;i<7;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x-32, (*it).y-45, 20.0*(c/dev)+15.0*i, 3.0, ESHOT(KNIFE,RED), false, 0, 5, 0.0, 0, flag);				
					ESMake((*it).x-32, (*it).y-45, 180.0+30.0*(c/dev)+17.0*i, 2.5, ESHOT(KNIFE,BLUE), false, 0, 5, 0.0, 0, false);				
				}
			}
		}

		if(c>60 && c%30==0){
			float x = (*it).x;
			float y = (*it).y;
			float plus2 = -15+get_rand(30);
			float plus = 5+get_rand(15);
			if(Player[0].x<(*it).x){
				if(x-plus<CENTER_X-150)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>CENTER_X+150)	x -= plus;
				else		x += plus;
			}
			if(y+plus<100 || y+plus>180 )		y -= plus;
			else		y += plus;
			BToMove(it, x, y, 30);
		}

		
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove10(list<BOSSDATA>::iterator &it){
//顔芸「ニュークリア・キモモ」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, 140, 60);
	}
	if(c<60){}
	else{
		int c2 = c-60;
		c = c2 % 360;
		int img = FRED;//ESHOT(BIG,RED);
		int img2 = ESHOT(MEDIUM,BLUE);
		if((c2/360)%2==1)	img = FBLUE;
		if(((c2/360)%2==1 && c>=180) || ((c2/360)%2==0 && c<60)){
			img2 = ESHOT(MEDIUM,RED);
		}
		if(c<30){
			if(c==0)	PlaySound(20);
			float d = 5 + 10.0*c;
			for(int i=0;i<5;i++)	EfMake((*it).x, (*it).y, -2, 11, d);
		}
		if(c==60 || ((level==HARD || level==LUNATIC || level==IMPOSSIBLE)&&c==180) || (level==IMPOSSIBLE&&c==300)){
			bES = false;
			PlaySound(33);
			float base_angle = 360.0 + Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
			float size = 12.0;//画像直径20
			for(int i=0;i<5;i++){
				int num = 264 / size;
				for(int j=num-1;j<num;j++){
					int num2 = 1;
					if(j>0)	num2 = 2*M_PI*j / 2.0; 
					float angle = 360.0 / (float)num2;
					for(int a=0;a<num2;a++){
						ESMake((*it).x, (*it).y, base_angle+72*i, angle*a, img, true, 39+a%2, 0, size/2.0*j, 0);				
					}
				}
				EfMake((*it).x, (*it).y, 11, 13, 0, Radian(base_angle+72*i,TRUE));
			}
			if(c==60)	EfMake((*it).x, (*it).y, 12, 12);
			bES = true;
		}
		if(level==EASY){
			if(c2>=180 && !(c>=60 && c<180)){
				if(c2%4==0){
					PlaySound(22);
					for(int i=0;i<3;i++){
						for(int j=0;j<1;j++){
							float angle;
							if(img2==ESHOT(MEDIUM,BLUE))	angle = 2.0*c2 + 120.0*i + 0.1*get_rand(15);
							else				angle = -2.0*c2 + 120.0*i + 0.1*get_rand(15);
							ESMake((*it).x, (*it).y, angle, 1.0-0.01*get_rand(20), img2, false, 0, 10);				
						}
					}
				}
			}
		}
		else if(level==NORMAL || level==HARD){
			if(c2>=180 && !(c>=60 && c<180)){
				if(c2%3==0){
					PlaySound(22);
					for(int i=0;i<3;i++){
						for(int j=0;j<1;j++){
							float angle;
							if(img2==ESHOT(MEDIUM,BLUE))	angle = 2.0*c2 + 120.0*i + 0.1*get_rand(15);
							else				angle = -2.0*c2 + 120.0*i + 0.1*get_rand(15);
							ESMake((*it).x, (*it).y, angle, 1.2-0.01*get_rand(20), img2, false, 0, 10);				
						}
					}
				}
			}
		}
		else if(level==LUNATIC || level==IMPOSSIBLE){
			if(c2>=180 && !(c>=60 && c<180)){
				if(c2%2==0){
					PlaySound(22);
					for(int i=0;i<3;i++){
						for(int j=0;j<1;j++){
							float angle;
							if(img2==ESHOT(MEDIUM,BLUE))	angle = 2.0*c2 + 120.0*i + 0.1*get_rand(15);
							else				angle = -2.0*c2 + 120.0*i + 0.1*get_rand(15);
							ESMake((*it).x, (*it).y, angle, 1.5-0.01*get_rand(50), img2, false, 0, 10);				
						}
					}
				}
			}
		}
		if(level==LUNATIC || level==IMPOSSIBLE){
			if(c==120){
				for(int i=0;i<30;i++){
					float angle = 90.0+12.0*i;
					float x = (*it).x + 30.0*cos(Radian(angle,TRUE));
					float y = (*it).y + 15.0*sin(Radian(angle,TRUE));
					ELMake(x, y, 12.0, angle, 8.0, ESHOT(RICE,PURPLE), 32, 60);
				}
			}
		}
		
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void SMove11(list<BOSSDATA>::iterator &it){
//「走らさせていただいてます」
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<30){}
	else if(c<60){
		if(c==30)	PlaySound(20);
		float d = 5 + 10.0*(c-30);
		for(int i=0;i<5;i++)	EfMake((*it).x, (*it).y, -2, 11, d);	
	}
	else if(c<150){
		if(c==90){
			BToMove(it, CENTER_X, -256, 60);
		}
	}
	else{
	 	c -= 150;
		(*it).bMuteki = false;
		if(level==EASY || level==NORMAL){
			c = c%640;
			if(c<80){
				int num = 20;
				if(c%num==0){
					PlaySound(25);
					EMake(-86, 58+96*(c/num), 250, 18, 37, 34);
				}
			}
			else if(c<320){}
			else if(c<400){
				c -= 320;
				int num = 20;
				if(c%20==0){
					PlaySound(25);
					EMake(526, 58+96*(c/num), 250, 18, 38, 35);
				}
			}
			else if(c<640){}
			
			if(c<140){}
			else if(c==140){
				(*it).x = -118;
				(*it).y = CENTER_Y-200;
			}
			else if(c<320){
				(*it).x += 6.0;
				(*it).y += 3.3;
			}
			else if(c<460){}
			else if(c==460){
				(*it).x = 558;
				(*it).y = CENTER_Y+200;
			}
			else if(c<640){
				(*it).x -= 6.0;
				(*it).y -= 3.3;
			}			
		}
		else if(level==HARD){
			c = c%680;
			if(c<100){
				int num = 20;
				if(c%num==0){
					PlaySound(25);
					EMake(-86, 58+96*(c/num), 250, 18, 37, 34);
				}
			}
			else if(c<340){}
			else if(c<440){
				c -= 340;
				int num = 20;
				if(c%20==0){
					PlaySound(25);
					EMake(526, 58+96*(c/num), 250, 18, 38, 35);
				}
			}
			else if(c<680){}
			
			if(c<160){}
			else if(c==160){
				(*it).x = -118;
				(*it).y = CENTER_Y-200;
			}
			else if(c<340){
				(*it).x += 6.0;
				(*it).y += 3.3;
			}
			else if(c<500){}
			else if(c==500){
				(*it).x = 558;
				(*it).y = CENTER_Y+200;
			}
			else if(c<680){
				(*it).x -= 6.0;
				(*it).y -= 3.3;
			}			
		}
		else if(level==LUNATIC || level==IMPOSSIBLE){
			c = c%640;
			if(c<80){
				int num = 20;
				if(c%num==0){
					PlaySound(25);
					EMake(-86, 58+96*(c/num), 250, 18, 37, 34);
					EMake(CENTER_X-96-48+96*(c/num), -182, 250, 18, 39, 36);
				}
			}
			else if(c<320){}
			else if(c<400){
				c -= 320;
				int num = 20;
				if(c%20==0){
					PlaySound(25);
					EMake(526, 58+96*(c/num), 250, 18, 38, 35);
					EMake(CENTER_X-96-48+96*(c/num), 662, 250, 18, 40, 37);
				}
			}
			else if(c<640){}
			
			if(c<140){}
			else if(c==140){
				(*it).x = -118;
				(*it).y = CENTER_Y-200;
			}
			else if(c<320){
				(*it).x += 6.0;
				(*it).y += 3.3;
			}
			else if(c<460){}
			else if(c==460){
				(*it).x = 558;
				(*it).y = CENTER_Y+200;
			}
			else if(c<640){
				(*it).x -= 6.0;
				(*it).y -= 3.3;
			}			
		}

		if((*it).x>10 && (*it).x<430 && (*it).y>10 && (*it).y<470){
			if(level==EASY){
				if(c%15==0){
					PlaySound(21);
					for(int i=0;i<20;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, 18.0*i, 1.2, FBLUE, true, 0, 10, 0.0, 0, flag);				
					}
				}
			}
			else if(level==NORMAL){
				if(c%10==0){
					PlaySound(21);
					for(int i=0;i<20;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, 18.0*i, 1.2, FBLUE, true, 0, 10, 0.0, 0, flag);				
					}
				}
			}
			else if(level==HARD || level==LUNATIC || level==IMPOSSIBLE){
				if(c%6==0){
					PlaySound(21);
					for(int i=0;i<20;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, 18.0*i, 1.2, FBLUE, true, 0, 10, 0.0, 0, flag);				
					}
				}
			}
			if(Player[0].hyper_count>0){
				/*
				if(level==HARD){
					if((*it).count%8==0){
						ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
						ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
					}
				}
				else if(level==LUNATIC){
					if((*it).count%5==0){
						ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
						ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
					}
				}
				else if(level==IMPOSSIBLE){
					if((*it).count%1==0){
						ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
						ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
					}
				}
				*/
			}
		}
	}

	return;
}

void SMove12(list<BOSSDATA>::iterator &it){
//爆幻「ランドマインランド」(E/N)
//爆幻「コア・オブ・ザ・セカンドサン」(H)
//爆幻「ザ・ギョフラー」(L/I)
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(level==EASY || level==NORMAL || level==LUNATIC || level==IMPOSSIBLE){
		if(c<90){}
		else{
		 	c -= 90;
			(*it).bMuteki = false;
			if(level==EASY){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				int tm;
				if(BossCount<20*60){
					tm = 10;
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
				}
				else if(per<33.3){
					tm = 15;
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
				}
				else if(per<66.6){
					tm = 20;
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
				}
				else			tm = 30;
				if(c%tm==0){
					PlaySound(25);
					for(int i=0;i<1;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x-32, (*it).y-45, -90+pow(-1,i)*1.5*c, 1.5, ESHOT(BIG,PURPLE), false, 41, 10, 0.0, 0, flag);				
					}
				}
				int time = 5;
				if(c%time==0){
					PlaySound(22);
					for(int i=0;i<3;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x-32, (*it).y-45, 4.0*c/time+120*i, 1.0+0.3*((int)(c/time)%3), ESHOT(OVAL,RED), false, 0, 10, 0.0, 0, flag);				
					}
				}
			}
			else if(level==NORMAL){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				int tm;
				if(BossCount<20*60){
					tm = 10;
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
				}
				else if(per<33.3){
					tm = 15;
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
				}
				else if(per<66.6){
					tm = 20;
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
				}
				else			tm = 30;
				if(c%tm==0){
					PlaySound(25);
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x-32, (*it).y-45, -90+pow(-1,i)*1.5*c, 2.5, ESHOT(BIG,PURPLE), false, 41, 10, 0.0, 0, flag);				
					}
				}
				int time = 5;
				if(c%time==0){
					PlaySound(22);
					for(int i=0;i<3;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x-32, (*it).y-45, 4.0*c/time+120*i, 1.0+0.4*((int)(c/time)%3), ESHOT(OVAL,RED), false, 0, 10, 0.0, 0, flag);				
					}
				}
			}
			else if(level==LUNATIC || level==IMPOSSIBLE){
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				int tm;
				if(BossCount<20*60){
					tm = 6;
					if((*it).i_hanyou[0]!=3){
						(*it).i_hanyou[0] = 3;
						PlaySound(18);
					}
				}
				else if(per<33.3){
					tm = 10;
					if((*it).i_hanyou[0]!=2){
						(*it).i_hanyou[0] = 2;
						PlaySound(18);
					}
				}
				else if(per<66.6){
					tm = 15;
					if((*it).i_hanyou[0]!=1){
						(*it).i_hanyou[0] = 1;
						PlaySound(18);
					}
				}
				else			tm = 30;
				if(c%tm==0){
					PlaySound(22);
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x-32, (*it).y-45, -90+pow(-1,i)*2.5*c, 3.0, ESHOT(BIG,PURPLE), false, 41, 10, 0.0, 0, flag);				
					}
				}
				int time = 60;
				if(level==IMPOSSIBLE)	time = 40;
				if(BossCount<20*60 || per<33.3){
					time = 30;
					if(level==IMPOSSIBLE)	time = 20;
				}
				if(c%time==0){
					PlaySound(25);
					ESMake((*it).x-32, (*it).y-45, 0, 0.0, ESHOT(BIG,GREEN), false, 43, 10);				
				}
			}
		}
	}
	else if(level==HARD){
		bRG = false;
		if(c<30){
			float d = 5 + 10.0*c;
			for(int i=0;i<5;i++)	EfMake((*it).x, (*it).y, -2, 11, d);		
		}
		if(c<60){}
		else{
		 	c -= 60;
			(*it).bMuteki = false;
			if(c==0){
				bSun = true;
				PlaySound(33);
				EfMake((*it).x, (*it).y, 11, 14, 0, Radian(90,TRUE));
			}
			if(c%60==0){
				float size = 12.0;//画像直径20
				int num = 264 / size;
				for(int j=num-1;j<num;j++){
					int num2 = 1;
					if(j>0)	num2 = 2*M_PI*j / 2.0; 
					float angle = 360.0 / (float)num2;
					for(int a=0;a<num2;a++){
						ESMake((*it).x, (*it).y, 0, angle*a, FBLUE, true, 44+a%2, 0, size/2.0*j, 0);				
					}
				}
			}
			
			/*
			float sx = Player[0].x-(*it).x;
			float sy = Player[0].y-(*it).y;
			float d = sqrt(sx*sx+sy*sy);
			(*it).x += 0.2*sx/d;
			(*it).y += 0.2*sy/d;
			*/
			
			float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
			int tm;
			if(BossCount<20*60){
				tm = 10;
				if((*it).i_hanyou[0]!=3){
					(*it).i_hanyou[0] = 3;
					PlaySound(18);
				}
			}
			else if(per<33.3){
				tm = 15;
				if((*it).i_hanyou[0]!=2){
					(*it).i_hanyou[0] = 2;
					PlaySound(18);
				}
			}
			else if(per<66.6){
				tm = 20;
				if((*it).i_hanyou[0]!=1){
					(*it).i_hanyou[0] = 1;
					PlaySound(18);
				}
			}
			else			tm = 25;
			if(c%tm==0){
				PlaySound(22);
				for(int i=0;i<10;i++){
					float an = Radian(15.0*(*it).i_hanyou[1]+36.0*i,TRUE);
					ESMake(CENTER_X+340*cos(an), CENTER_Y+340*sin(an), Radian(an,FALSE), 0.0, FRED, true, 46, 0);				
				}
				(*it).i_hanyou[1] ++;
			}
		}
	}

	if(Player[0].hyper_count>0){
		/*
		if(level==HARD){
			if((*it).count%8==0){
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
			}
		}
		else if(level==LUNATIC){
			if((*it).count%5==0){
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
			}
		}
		else if(level==IMPOSSIBLE){
			if((*it).count%1==0){
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
			}
		}
		*/
	}

	return;
}

void SMove13(list<BOSSDATA>::iterator &it){
//「妖蛾乱舞」:体力6000
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<180){}
	else{
		(*it).angle = Radian((*it).f_hanyou[1],TRUE);
		(*it).x = CENTER_X - (*it).f_hanyou[2] * cos(Radian((*it).f_hanyou[1],TRUE));
		(*it).y = CENTER_Y - (*it).f_hanyou[0] * sin(Radian((*it).f_hanyou[1],TRUE));
		(*it).x += 25.0*sin(Radian(3*c,TRUE));
		(*it).y += 10.0*sin(Radian(5*c,TRUE));
	}
	float mangle[4],md[4],mx[4],my[4];//前方左翼・右翼、後方左翼・右翼
	mangle[0] = Atan2(20.5,-93);
	md[0] = sqrt(20.5*20.5 + 93*93);
	mangle[1] = Atan2(26.5,90);
	md[1] = sqrt(26.5*26.5 + 90*90);
	mangle[2] = Atan2(-23.5,-10);
	md[2] = sqrt(23.5*23.5 + 10*10);
	mangle[3] = Atan2(-30.5,52);
	md[3] = sqrt(30.5*30.5 + 52*52);
	if(c<=180)	(*it).f_hanyou[1] = 90;
	for(int i=0;i<4;i++){
		mx[i] = (*it).x + md[i]*cos(mangle[i] + Radian((*it).f_hanyou[1]-90,TRUE));
		my[i] = (*it).y + md[i]*sin(mangle[i] + Radian((*it).f_hanyou[1]-90,TRUE));
	}

	if(c<90){}
	else{
		c -= 90;
		if(c==0){
			ELMake(mx[2], my[2], 30.0, 90.0, 12.0, ESHOT(BIG,RED), 6, 60);
			ELMake(mx[3], my[3], 30.0, 90.0, 12.0, ESHOT(BIG,RED), 7, 60);
		}
		if(c<30){
			if(c==0)	PlaySound(20);
			for(int j=0;j<4;j++){
				for(int i=0;i<1;i++)	EfMake(mx[j], my[j], -2, 11, 300);
			}
		}
		if(c>=60&&c<=90){
			(*it).y = CENTER_Y - 180.0*pow(c-60,2)/900.0;
		}
		if(c<=90){
			float dx = CENTER_X - (*it).x;
			float dy = CENTER_Y - (*it).y;
			(*it).f_hanyou[0] = sqrt(dx*dx+dy*dy);
			(*it).f_hanyou[2] = 160;
			(*it).f_hanyou[1] = 90;
		}

		float plus_angle,pa2;
		if(c<120){
			plus_angle = 0;
			pa2 = 90.0 - 0.25*c;
		}
		else{
			plus_angle = 0.0*sin(Radian((*it).count-120,TRUE));
			pa2 = 60.0;
		}
		float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
		if(c%3==0){
			PlaySound(22);
			for(int i=0;i<5;i++){
				if(/*c<120&&*/i==2)	continue;
				int patt = 0;
				if(per<15)	patt = 48;
				ESMake(mx[0], my[0], (*it).f_hanyou[1]-2*pa2+pa2*i+plus_angle, 9.0, ESHOT(UROKO,RED), false, patt, 0);
				ESMake(mx[1], my[1], (*it).f_hanyou[1]-2*pa2+pa2*i-plus_angle, 9.0, ESHOT(UROKO,RED), false, patt, 0);
			}
		}
		if(c==0){
			for(int j=0;j<4;j++){
				bool flag = false;
				if(j==0)	flag = true;
				for(int i=0;i<4;i++){
					ESNWay(mx[i], my[i], Player[0].x, Player[0].y, 15.0, 24, 4.0-0.8*j, ESHOT(BFLY,GREEN), false, 0, 60, 0, 0, flag);
					ang_plus = 7.5;
					ESNWay(mx[i], my[i], Player[0].x, Player[0].y, 15.0, 24, 3.6-0.8*j, ESHOT(BFLY,YELLOW), false, 0, 60, 0, 0, false);
					ang_plus = 0;
				}
			}
		}
		
		if(c>=180){
			c -= 180;
			if(c==0)	PlaySound(18);
			(*it).f_hanyou[1] += 0.3;
			
			if(per<15){
				if((*it).i_hanyou[0]==1){
					PlaySound(18);
					(*it).i_hanyou[0]++;
				}
				if(c%50<20 && c%1==0){
					for(int i=0;i<2;i++){
						ESNWay(mx[i], my[i], Player[0].x, Player[0].y, 20.0, 6, 5.0, ESHOT(BFLY,BLUE), false, 47, 5);
					}
				}
			}
			else if(per<50){
				if((*it).i_hanyou[0]==0){
					PlaySound(18);
					(*it).i_hanyou[0]++;
				}
				if(c%50<25 && c%3==0){
					for(int i=0;i<2;i++){
						ESNWay(mx[i], my[i], Player[0].x, Player[0].y, 20.0, 6, 5.0, ESHOT(BFLY,BLUE), false, 47, 5);
					}
				}
			}
			else{
				if(c%50<20 && c%5==0){
					for(int i=0;i<2;i++){
						ESNWay(mx[i], my[i], Player[0].x, Player[0].y, 20.0, 6, 5.0, ESHOT(BFLY,BLUE), false, 47, 5);
					}
				}
			}
        	}
	}

	return;
}

void SMove14(list<BOSSDATA>::iterator &it){
//「ヤンデレスカイハイ」:体力10000
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<60){
		(*it).i_hanyou[0] = 2;
	}
	else{
		c -= 60;
		c = c%780;
		if(c==0){
			(*it).i_hanyou[0]++;
		}
		else if(c<30){
			for(int i=0;i<1;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
		}
		else if(c<60){}
		else if(c<=90){
			PlaySound(21);
			for(int i=0;i<1+1*((*it).i_hanyou[0]+1);i++){
				ESMake((*it).x, (*it).y-34, 0.1*get_rand(3600), 3.0, ESHOT(KNIFE,BLUE), false, 49, 10, 2.0+0.01*get_rand(500));				
				ESMake((*it).x, (*it).y-34, 0.1*get_rand(3600), 3.0, ESHOT(KNIFE,BLUE), false, 50, 10, 2.0+0.01*get_rand(500));				
			}
		}
		else if(c<300){}
		else if(c==300){
			float x = (*it).x;
			float y = (*it).y;
			y = 160+get_rand(80);
			float plus = 10+get_rand(60);
			if(Player[0].x<(*it).x){
				if(x-plus<140)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>300)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		else if(c<360){}
		else if(c<390){
			for(int i=0;i<1;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 300);
		}
		else if(c<510){
			c -= 390;
			PlaySound(21);
			for(int i=0;i<1+(*it).i_hanyou[0];i++){
				float per = 360.0 / (*it).i_hanyou[0];
				float anglex = Radian(12.0*c+per*i,TRUE);
				float angley = Radian(9.0*c+per*i,TRUE);
				float angle = 10.0*c+per*i;
				float l = 1.5*c;
				float x,y;
				x = (*it).x + l*cos(anglex);
				y = (*it).y - 34 + l*sin(angley);
				ESMake(x, y, angle, 3.0, ESHOT(KATANA,GREEN), false, 49+c%2, 20, 4.0);
			}
		}
		else if(c<720){}
		else if(c==720){
			float x = (*it).x;
			float y = (*it).y;
			y = 160+get_rand(80);
			float plus = 10+get_rand(60);
			if(Player[0].x<(*it).x){
				if(x-plus<140)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>300)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		else if(c<780){}
	}

	return;
}

void SMove15(list<BOSSDATA>::iterator &it){
//あらま～ラストスペル
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<60){
		if(c==0){
			BToMove(it, CENTER_X, 150, 40);
			(*it).i_hanyou[0] = 0;
			(*it).i_hanyou[1] = 90;
			(*it).f_hanyou[0] = 0.5;
		}
	}
	else{
		c -= 60;
		float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
		if(level==NORMAL){
			if(per<35.0 || BossCount<20*60){
				if((*it).i_hanyou[0]!=2){
					PlaySound(18);
					(*it).i_hanyou[0] = 2;
				}
				if(c%2==0)	(*it).i_hanyou[1] ++;
			}
			else if(per<80.0){
				if((*it).i_hanyou[0]!=1){
					PlaySound(18);
					(*it).i_hanyou[0] = 1;
				}
				if(c%2==0)	(*it).i_hanyou[1] ++;
			}
			else{}
			int cp = 14;
			if(c%cp==0){
				(*it).f_hanyou[0] = 1.0*sin(Radian((*it).i_hanyou[1],TRUE));
				PlaySound(22);
				for(int i=0;i<12;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x, (*it).y, 30.0*i+2.0*c/cp, 4.0, ESHOT(BFLY, PURPLE), false, 52, 10, 1.0, 120, flag);				
				}
				if((*it).i_hanyou[0]==2){
					for(int i=0;i<12;i++){
						bool flag = false;
						ESMake((*it).x, (*it).y, 30.0*i+15.0+2.0*c/cp, 4.0, ESHOT(BFLY, PURPLE), false, 52, 10, 1.0, 120, flag);				
					}			
				}
			}
		}
	}

	return;
}

void BReset(){
	BGcount = 0;
	BGcount2 = 0;
	BGcount3 = 0;
	BossCount = 0;
	SpBackCount = 0;
	SpNum = 0;
	NmBonus = 0;
	SpBonus = 0;
	SpBonusRate = 0;
	GetSpBonus = 0;
	GetSpBonusCount = 0;
	bSun = false;
	Boss.clear();

	return;
}

void BDraw(){
	int loop_num = 1;
	list<BOSSDATA>::iterator eit = Boss.begin();
	//if(bTalk==false && (*eit).life>0 && Player[0].hyper_count>0 && (Player[0].level==LUNATIC || Player[0].level==IMPOSSIBLE) && NowPart==BOSS && !((*eit).bSpell==false && ((*eit).pattern==18 || (*eit).pattern==21)))	loop_num = 2;
	for(int k=0;k<loop_num;k++){
		list<BOSSDATA>::iterator bit = Boss.begin();
		for(list<BOSSDATA>::iterator it=Boss.begin(); it!=Boss.end(); ++it){
			if((*eit).life>0 || k==0){
				if((*eit).bSpell==false && ((*eit).pattern==18 || (*eit).pattern==21)){
					if(Player[0].muteki_count>0)	(*eit).muteki_count = 30;
					if((*eit).muteki_count>0)	(*eit).muteki_count--;
				}
				int hcount = Player[0].hyper_count;
				if(Player[0].level==BABY)	Player[0].hyper_count = 1;
				Prank = Player[0].hyper_rank;
				//if(Player[0].stress_gage>=MAJIGIRE)	Prank += 3;
				if(Player[0].hyper_count>0)	Prank = 20;
				if(Prank>20)	Prank = 20;
				//bRG = true;
				//bES = true;
				if(bTalk==false)	BMove(it);
				else			BTalkMove(it);
				//bRG = false;
				//bES = false;
				if(Player[0].level==BABY)	Player[0].hyper_count = hcount;
			}
			if(k==0 && bTalk==false){
				//if(Player[0].stage==4){
					float d = 0.1*get_rand(200);
					float angle = Radian(0.1*get_rand(3600),TRUE);		
					for(int i=0;i<3;i++)	EfMake2((*it).x+d*cos(angle), (*it).y+d*sin(angle), gEffect[2], 4);
				//}			
			}
			if((*it).bDeath==true){
				EfMake((*it).x, (*it).y, 5, 5);
				//イージーの上昇値
				unsigned int add;
				if((*it).img==0)	add = 20000000;	//モスラ 2000万
				else if((*it).img==1)	add = 30000000;	//ゴジラ 3000万
				else if((*it).img==2)	add = 0;	//横顔ゴジラ 0万
				else if(Player[0].stage==2 && (*it).img==3)	add = 30000000;	//2面アホ 3000万
				else if(Player[0].stage==3 && (*it).img==3)	add = 40000000;	//3面アホ 4000万
				else if((*it).img==4)	add = 40000000;	//蒸発 4000万
				else if((*it).img==5)	add = 50000000;	//ゆやさま 5000万
				//4面アホ どちらも6000万
				//5面中ボスたち 1億
				//あらま～ 10億
				//真ボス 100億
				if(Player[0].level==NORMAL)		add *= 2.0; 
				else if(Player[0].level==HARD)		add *= 3.0; 
				else if(Player[0].level==LUNATIC)	add *= 4.0; 
				else if(Player[0].level==IMPOSSIBLE)	add *= 5.0; 
				add_score(add);
				it = Boss.erase(it);
				it--;
				continue;			
			}
			int gx,gy;
			GetGraphSize(gEnemy[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){}
			else	(*it).bDelete = true;
			
			bool flow = true;
			if((*it).img==0 || (*it).img==2 || ((*it).bSpell==true&&(*it).pattern>=8&&(*it).pattern<=11))	flow = false;
       	
			if((*it).bSpell==true){
				SetDrawBlendMode(DX_BLENDMODE_ADD,150);
				float large = 1.0;
				if((*it).count<20)	large = 0.05*(*it).count;
				float plus = 5.0*sin(Radian(6*(*it).img_count,TRUE));
				if(k==loop_num-1 && GetSkip()){
					if(flow==true)	DrawRotaGraphF((*it).x+shake_x, (*it).y+plus+shake_y, large, Radian(12*(*it).count,TRUE), gEffect[8], TRUE, FALSE);
					else		DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, large, Radian(12*(*it).count,TRUE), gEffect[8], TRUE, FALSE);
				}
			}
			
			if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			SetDrawBright(255,255,255);
			float per = 100.0 * (float)(*bit).life / (float)(*bit).max_life;
			if((*it).death_count>0){
				SetDrawBright(255,50,50);
			}
			else{
				if((*it).bDamage==true){
					(*it).bDamage = false;
					//SetDrawBright(100,100,255);
					if((*bit).life<600)	PlaySound(6);
					else			PlaySound(7);
				}
				if(per<10.0){
					if((*bit).count%4<2)	SetDrawBright(255,50,50);
				}
				else if(per<20.0){
					if((*bit).count%6<2)	SetDrawBright(255,50,50);
				}
				else if(per<30.0){
					if((*bit).count%10<2)	SetDrawBright(255,50,50);
				}
				else if(per<40.0){
					if((*bit).count%20<2)	SetDrawBright(255,50,50);
				}
				else if(per<50.0){
					if((*bit).count%30<2)	SetDrawBright(255,50,50);
				}
			}
			if(flow==false){
				if(k==loop_num-1 && GetSkip()){
					if((*it).pattern==5)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gBoss[(*it).img], TRUE, TRUE);
					else			DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gBoss[(*it).img], TRUE, FALSE);
				}
			}
			else{
				float plus = 5.0*sin(Radian(6*(*it).img_count,TRUE));
				if(k==loop_num-1 && GetSkip()){
					DrawRotaGraphF((*it).x+shake_x, (*it).y+plus+shake_y, (*it).large, (*it).angle-M_PI/2.0, gBoss[(*it).img], TRUE, FALSE);
				}
			}
			if(k==loop_num-1 && GetSkip()){
				if((*eit).muteki_count>0){
					float plus = 0;
					if(flow==true)	plus = 5.0*sin(Radian(6*(*it).img_count,TRUE));
					SetDrawBlendMode(DX_BLENDMODE_ADD,4*(*eit).muteki_count);
					DrawCircle((*it).x+shake_x, (*it).y+plus+shake_y, 80.0, GetColor(255,255,255), TRUE);
				}
			}
			if(bTalk==false)	(*it).count++;
			if(k==0)	(*it).img_count++;
		}
		SetDrawBright(255,255,255);
	}
	
	return;
}

void BMove0(list<BOSSDATA>::iterator &it){
//モスラ第一攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, 150, 30);
	}
	if(c<30)	(*it).angle = Radian(90+1.5*(30-c),TRUE);
	else		(*it).angle = Radian(90,TRUE);
	if(c<30){}
	else{
		(*it).x += 2.0*sin(Radian(3*c,TRUE));
		(*it).y += 1.0*sin(Radian(5*c,TRUE));
	}
	if(c<70){}
	else{
		if(level==EASY){
			int loo = Loo(10,5);
			c = (c-70)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==NORMAL){
			int loo = Loo(6,3);
			c = (c-70)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==HARD){
			int loo = Loo(5,2);
			c = (c-70)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c%10==0){
				for(int i=0;i<2;i++){
					float angle = (*it).count+get_rand(10);
					ESMake((*it).x-10, (*it).y-23.5, angle, 2.0, ESHOT(SMALL,BLUE), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, angle+180, 2.0, ESHOT(SMALL,BLUE), false, 0, 0);
				}
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==LUNATIC){
			int loo = Loo(3,1);
			c = (c-70)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c%5==0){
				for(int i=0;i<3;i++){
					float angle = 2*(*it).count+get_rand(10);
					ESMake((*it).x-10, (*it).y-23.5, angle, 3.0, ESHOT(SMALL,BLUE), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, angle+180, 3.0, ESHOT(SMALL,BLUE), false, 0, 0);
				}
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==IMPOSSIBLE){
			c = (c-70)%420;
			if(c%1==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 15.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 15.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c%2==0){
				for(int i=0;i<5;i++){
					float angle = 6*(*it).count+get_rand(12);
					ESMake((*it).x-10, (*it).y-23.5, angle, 5.0, ESHOT(SMALL,BLUE), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, angle+180, 5.0, ESHOT(SMALL,BLUE), false, 0, 0);
				}
			}
			if(c<60){
				if(c%1==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)c*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%1==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-90)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%1==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-180)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c%1==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-300)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-300)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-300)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
	}

	return;
}

void BMove1(list<BOSSDATA>::iterator &it){
//モスラ第二攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X, 150, 10);
	}
	if(c<10){}
	else{
		(*it).x += 2.0*sin(Radian(3*c,TRUE));
		(*it).y += 1.0*sin(Radian(7*c,TRUE));
	}
	if(c<50){}
	else{
		if(level==EASY){
			int loo = Loo(10,5);
			if(c==50){
				for(int i=0;i<5;i++){
					ELMake((*it).x-10, (*it).y-23.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 0, 60);
					ELMake((*it).x+52, (*it).y-30.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 1, 60);
				}
			}
			c = (c-50)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c==300){
					float angle1 = 90.0;
					float angle2 = 90.0;
					ELMake((*it).x-93, (*it).y+20.5, 15.0, angle1, 5.0, ESHOT(RICE,PURPLE), 2, 30);
					ELMake((*it).x+90, (*it).y+26.5, 15.0, angle2, 5.0, ESHOT(RICE,PURPLE), 3, 30);
				}
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 60.0, 3, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 1, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==NORMAL){
			int loo = Loo(6,3);
			if(c==50){
				for(int i=0;i<5;i++){
					ELMake((*it).x-10, (*it).y-23.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 0, 60);
					ELMake((*it).x+52, (*it).y-30.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 1, 60);
				}
			}
			c = (c-50)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c==300){
					float angle1 = 90.0;
					float angle2 = 90.0;
					ELMake((*it).x-93, (*it).y+20.5, 15.0, angle1, 8.0, ESHOT(RICE,PURPLE), 2, 30);
					ELMake((*it).x+90, (*it).y+26.5, 15.0, angle2, 8.0, ESHOT(RICE,PURPLE), 3, 30);
				}
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 40.0, 5, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 4.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==HARD){
			int loo = Loo(5,2);
			if(c==50){
				for(int i=0;i<5;i++){
					ELMake((*it).x-10, (*it).y-23.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 0, 60);
					ELMake((*it).x+52, (*it).y-30.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 1, 60);
				}
			}
			c = (c-50)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c%10==0){
				for(int i=0;i<2;i++){
					float angle = (*it).count+get_rand(10);
					ESMake((*it).x-10, (*it).y-23.5, angle, 2.0, ESHOT(SMALL,BLUE), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, angle+180, 2.0, ESHOT(SMALL,BLUE), false, 0, 0);
				}
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c==300){
					float angle1 = 30.0;
					float angle2 = 30.0;
					for(int i=0;i<3;i++){
						ELMake((*it).x-93, (*it).y+20.5, 15.0, angle1+60.0*i, 8.0, ESHOT(RICE,PURPLE), 2, 30);
						ELMake((*it).x+90, (*it).y+26.5, 15.0, angle2+60.0*i, 8.0, ESHOT(RICE,PURPLE), 3, 30);
					}
				}
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 30.0, 5, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 5.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==LUNATIC){
			int loo = Loo(3,1);
			if(c==50){
				for(int i=0;i<5;i++){
					ELMake((*it).x-10, (*it).y-23.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 0, 60);
					ELMake((*it).x+52, (*it).y-30.5, 15.0, 210+30.0*i, 12.0, ESHOT(RICE,PURPLE), 1, 60);
				}
			}
			c = (c-50)%420;
			if(c%3==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 7.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c%5==0){
				for(int i=0;i<3;i++){
					float angle = 2*(*it).count+get_rand(10);
					ESMake((*it).x-10, (*it).y-23.5, angle, 3.0, ESHOT(SMALL,BLUE), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, angle+180, 3.0, ESHOT(SMALL,BLUE), false, 0, 0);
				}
			}
			if(c<60){
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%loo==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%loo==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c==300){
					float angle1 = 30.0;
					float angle2 = 30.0;
					for(int i=0;i<5;i++){
						ELMake((*it).x-93, (*it).y+20.5, 15.0, angle1+30.0*i, 12.0, ESHOT(RICE,PURPLE), 2, 30);
						ELMake((*it).x+90, (*it).y+26.5, 15.0, angle2+30.0*i, 12.0, ESHOT(RICE,PURPLE), 3, 30);
					}
				}
				if(c%loo==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 20.0, 5, 7.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 3, 7.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
		else if(level==IMPOSSIBLE){
			if(c==50){
				for(int i=0;i<5;i++){
					ELMake((*it).x-10, (*it).y-23.5, 15.0, 210+30.0*i, 18.0, ESHOT(RICE,PURPLE), 0, 60);
					ELMake((*it).x+52, (*it).y-30.5, 15.0, 210+30.0*i, 18.0, ESHOT(RICE,PURPLE), 1, 60);
				}
			}
			c = (c-50)%420;
			if(c%1==0){
				float plus_angle = 40.0*sin(Radian(3*(*it).count,TRUE));
				for(int i=0;i<5;i++){
					ESMake((*it).x-10, (*it).y-23.5, 210+30.0*i+plus_angle, 15.0, ESHOT(MEDIUM,RED), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, 210+30.0*i+plus_angle, 15.0, ESHOT(MEDIUM,RED), false, 0, 0);
				}
			}
			if(c==0 || c==90 || c==180 || c==300){
				(*it).f_hanyou[3] = Player[0].x;
				(*it).f_hanyou[4] = Player[0].y;
			}
			if(c%2==0){
				for(int i=0;i<5;i++){
					float angle = 6*(*it).count+get_rand(12);
					ESMake((*it).x-10, (*it).y-23.5, angle, 5.0, ESHOT(SMALL,BLUE), false, 0, 0);
					ESMake((*it).x+52, (*it).y-30.5, angle+180, 5.0, ESHOT(SMALL,BLUE), false, 0, 0);
				}
			}
			if(c<60){
				if(c%1==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)c*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<90){}
			else if(c<150){
				if(c%1==0){
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-90)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<180){}
			else if(c<240){
				if(c%1==0){
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-180)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<300){}
			else if(c<360){
				if(c==300){
					float angle1 = 30.0;
					float angle2 = 30.0;
					for(int i=0;i<12;i++){
						ELMake((*it).x-93, (*it).y+20.5, 15.0, angle1+30.0*i, 18.0, ESHOT(RICE,PURPLE), 2, 30);
						ELMake((*it).x+90, (*it).y+26.5, 15.0, angle2+30.0*i, 18.0, ESHOT(RICE,PURPLE), 3, 30);
					}
				}
				if(c%1==0){
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-300)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+5, (*it).y+32.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-300)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x-93, (*it).y+20.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 72.0-((float)(c-300)*0.8), 5, 12.0, ESHOT(MEDIUM,RED), false, 0, 5);
					ESNWay((*it).x+90, (*it).y+26.5, (*it).f_hanyou[3], (*it).f_hanyou[4], 3.0, 5, 12.0, ESHOT(MEDIUM,BLUE), false, 0, 5);
				}
			}
			else if(c<420){}
		}
	}

	return;
}

void BMove2(list<BOSSDATA>::iterator &it){
//ゴジラ第一攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		if(level==EASY){
			c = (c-20)%260;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%8==0){
					PlaySound(22);
					if(((*it).count-20)%520<230)	ESMake((*it).x, (*it).y, (c-40)/8*72+(*it).f_hanyou[0], 2.5, ESHOT(VERYBIG,BBLUE), true, 1, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/8*72+(*it).f_hanyou[0], 2.5, ESHOT(VERYBIG,BBLUE), true, 1, 30);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
		}
		else if(level==NORMAL){
			c = (c-20)%230;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%5==0){
					PlaySound(22);
					if(((*it).count-20)%460<230)	ESMake((*it).x, (*it).y, (c-40)/5*45+(*it).f_hanyou[0], 3.0, ESHOT(VERYBIG,BBLUE), true, 1, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/5*45+(*it).f_hanyou[0], 3.0, ESHOT(VERYBIG,BBLUE), true, 1, 30);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
		}
		else if(level==HARD){
			c = (c-20)%200;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%2==0){
					PlaySound(22);
					if(((*it).count-20)%400<200)	ESMake((*it).x, (*it).y, (c-40)/2*18+(*it).f_hanyou[0], 3.0+2.0*(c/2%2), ESHOT(VERYBIG,BBLUE), true, 1, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/2*18+(*it).f_hanyou[0], 3.0+2.0*(c/2%2), ESHOT(VERYBIG,BBLUE), true, 1, 30);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 6.5, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==LUNATIC){
			c = (c-20)%200;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%1==0){
					PlaySound(22);
					if(((*it).count-20)%400<200)	ESMake((*it).x, (*it).y, (c-40)/1*9+(*it).f_hanyou[0], 3.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 1, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/1*9+(*it).f_hanyou[0], 3.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 1, 30);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==IMPOSSIBLE){
			c = (c-20)%200;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%1==0){
					PlaySound(22);
					ESMake((*it).x, (*it).y, (c-40)/1*9+(*it).f_hanyou[0], 4.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 1, 30);
					ESMake((*it).x, (*it).y, -(c-40)/1*9+(*it).f_hanyou[0], 4.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 1, 30);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 12.0, FRED, true, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove3(list<BOSSDATA>::iterator &it){
//ゴジラ第二攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		if(level==EASY){
			c = (c-20)%260;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%8==0){
					PlaySound(22);
					if(((*it).count-20)%520<230)	ESMake((*it).x, (*it).y, (c-40)/8*72+(*it).f_hanyou[0], 2.5, ESHOT(VERYBIG,BBLUE), true, 4, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/8*72+(*it).f_hanyou[0], 2.5, ESHOT(VERYBIG,BBLUE), true, 4, 30);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
		}
		else if(level==NORMAL){
			c = (c-20)%230;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%5==0){
					PlaySound(22);
					if(((*it).count-20)%460<230)	ESMake((*it).x, (*it).y, (c-40)/5*45+(*it).f_hanyou[0], 3.0, ESHOT(VERYBIG,BBLUE), true, 4, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/5*45+(*it).f_hanyou[0], 3.0, ESHOT(VERYBIG,BBLUE), true, 4, 30);
				}
			}
			else if(c<170){}
			else if(c==170){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
		}
		else if(level==HARD){
			c = (c-20)%200;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%2==0){
					PlaySound(22);
					if(((*it).count-20)%400<200)	ESMake((*it).x, (*it).y, (c-40)/2*18+(*it).f_hanyou[0], 3.0+2.0*(c/2%2), ESHOT(VERYBIG,BBLUE), true, 4, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/2*18+(*it).f_hanyou[0], 3.0+2.0*(c/2%2), ESHOT(VERYBIG,BBLUE), true, 4, 30);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 6.5, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==LUNATIC){
			c = (c-20)%200;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%1==0){
					PlaySound(22);
					if(((*it).count-20)%400<200)	ESMake((*it).x, (*it).y, (c-40)/1*9+(*it).f_hanyou[0], 3.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 4, 30);
					else				ESMake((*it).x, (*it).y, -(c-40)/1*9+(*it).f_hanyou[0], 3.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 4, 30);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, FRED, true, 0, 0);
				}
			}
			*/
		}
		else if(level==IMPOSSIBLE){
			c = (c-20)%200;
			if(c==0){
				PlaySound(20);
				EfMake((*it).x, (*it).y, 4, 5);
				for(int i=0;i<8;i++)	EfMake((*it).x, (*it).y, -2, 11, 100);
			}
			if(c<40){}
			else if(c<80){
				if(c==40){
					(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).f_hanyou[0] += 180;
				}
				if(c%1==0){
					PlaySound(22);
					ESMake((*it).x, (*it).y, (c-40)/1*9+(*it).f_hanyou[0], 4.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 4, 30);
					ESMake((*it).x, (*it).y, -(c-40)/1*9+(*it).f_hanyou[0], 4.0+1.0*(c%4), ESHOT(VERYBIG,BBLUE), true, 4, 30);
				}
			}
			else if(c<140){}
			else if(c==140){
				float x = (*it).x;
				float y = (*it).y;
				y = 110+get_rand(80);
				float plus = 30+get_rand(70);
				if(Player[0].x<(*it).x){
					if(x-plus<90)	x += plus;
					else		x -= plus;
				}
				else{
					if(x+plus>350)	x -= plus;
					else		x += plus;
				}
				BToMove(it, x, y, 60);
			}
			/*
			if(Player[0].hyper_count>0){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 12.0, FRED, true, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove4(list<BOSSDATA>::iterator &it){
//うんざん（横）
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<60){
		if(c==0){
			PlaySound(27);
			int gx,gy;
			GetGraphSize(gBoss[(*it).img], &gx, &gy);
			if(p==4)	BToMove(it, 430-gx/2, CENTER_Y, 60);
			else if(p==5)	BToMove(it, 10+gx/2, CENTER_Y, 60);
		}
	}
	else{
		if(level==EASY){
			c = (c-60)%280;
			if((*it).count%20==0){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-11.5, (*it).y-53, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(10), FRED, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+11.5, (*it).y-53, -45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(10), FRED, true, 5, 30);
				}
			}
			if(c==120){
				PlaySound(20);
				if(p==4){
					EfMake((*it).x-10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x-10.5, (*it).y-156, -2, 11, 200);
				}
				else if(p==5){
					EfMake((*it).x+10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x+10.5, (*it).y-156, -2, 11, 200);
				}
			}
			else if(c==160){
				if(p==4){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x-10.5)),FALSE);
					ELMake((*it).x-10.5, (*it).y-156, 12.0, angle, 8.0, ESHOT(RICE,PURPLE), 2, 50);
				}
				else if(p==5){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x+10.5)),FALSE);
					ELMake((*it).x+10.5, (*it).y-156, 12.0, angle, 8.0, ESHOT(RICE,PURPLE), 2, 50);
				}
			}
		}
		else if(level==NORMAL){
			c = (c-60)%250;
			if((*it).count%12==0){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-11.5, (*it).y-53, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(10), FRED, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+11.5, (*it).y-53, -45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(10), FRED, true, 5, 30);
				}
			}
			if(c==120){
				PlaySound(20);
				if(p==4){
					EfMake((*it).x-10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x-10.5, (*it).y-156, -2, 11, 200);
				}
				else if(p==5){
					EfMake((*it).x+10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x+10.5, (*it).y-156, -2, 11, 200);
				}
			}
			else if(c==160){
				if(p==4){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x-10.5)),FALSE);
					ELMake((*it).x-10.5, (*it).y-156, 30.0, angle, 15.0, ESHOT(RICE,PURPLE), 2, 50);
				}
				else if(p==5){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x+10.5)),FALSE);
					ELMake((*it).x+10.5, (*it).y-156, 30.0, angle, 15.0, ESHOT(RICE,PURPLE), 2, 50);
				}
			}
		}
		else if(level==HARD){
			c = (c-60)%220;
			if((*it).count%10==0){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-11.5, (*it).y-53, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(15), FRED, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+11.5, (*it).y-53, -45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(15), FRED, true, 5, 30);
				}
			}
			if((*it).count%10==5){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-41.5, (*it).y-92, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(15), FBLUE, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+41.5, (*it).y-92, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(15), FBLUE, true, 5, 30);
				}
			}
			if(c==120){
				PlaySound(20);
				if(p==4){
					EfMake((*it).x-10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x-10.5, (*it).y-156, -2, 11, 200);
				}
				else if(p==5){
					EfMake((*it).x+10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x+10.5, (*it).y-156, -2, 11, 200);
				}
			}
			else if(c==160){
				if(p==4){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x-10.5)),FALSE);
					ELMake((*it).x-10.5, (*it).y-156, 30.0, angle, 15.0, ESHOT(RICE,PURPLE), 2, 50);
				}
				else if(p==5){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x+10.5)),FALSE);
					ELMake((*it).x+10.5, (*it).y-156, 30.0, angle, 15.0, ESHOT(RICE,PURPLE), 2, 50);
				}
			}

			/*
			if(Player[0].hyper_count>0){
				if((*it).count%10==0){
					if(p==4){
						ESNWay((*it).x-11.5, (*it).y-53, Player[0].x, Player[0].y, 10.0, 5, 6.0, FRED, true, 0, 0);
					}
					else if(p==5){
						ESNWay((*it).x+11.5, (*it).y-53, Player[0].x, Player[0].y, 10.0, 5, 6.0, FRED, true, 0, 0);
					}
				}
			}
			*/
		}
		else if(level==LUNATIC){
			int gx,gy;
			GetGraphSize(gBoss[2], &gx, &gy);
			float haba = gy/4.0;
			float plus = pow(-1,p%2)*haba*sin(Radian(2.0*(*it).i_hanyou[0],TRUE));
			(*it).y = CENTER_Y + plus;
			c = (c-60)%220;
			if((*it).count%6==0){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-11.5, (*it).y-53, 45.0+0.1*get_rand(1800), 1.5+0.1*get_rand(20), FRED, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+11.5, (*it).y-53, -45.0+0.1*get_rand(1800), 1.5+0.1*get_rand(20), FRED, true, 5, 30);
				}
			}
			if((*it).count%6==3){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-41.5, (*it).y-92, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(20), FBLUE, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+41.5, (*it).y-92, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(20), FBLUE, true, 5, 30);
				}
			}
			if(c==120){
				PlaySound(20);
				if(p==4){
					EfMake((*it).x-10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x-10.5, (*it).y-156, -2, 11, 200);
				}
				else if(p==5){
					EfMake((*it).x+10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x+10.5, (*it).y-156, -2, 11, 200);
				}
			}
			else if(c==160){
				Lto_x = Player[0].x;
				Lto_y = Player[0].y;
				Lspe_count = (*it).i_hanyou[0]-1;
				if(p==4){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x-10.5)),FALSE);
					ELMake((*it).x-10.5, (*it).y-156, 30.0, angle, 18.0, ESHOT(RICE,PURPLE), 4, 50);
				}
				else if(p==5){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x+10.5)),FALSE);
					ELMake((*it).x+10.5, (*it).y-156, 30.0, angle, 18.0, ESHOT(RICE,PURPLE), 5, 50);
				}
			}
			
			(*it).i_hanyou[0]++;

			/*
			if(Player[0].hyper_count>0){
				if((*it).count%8==0){
					if(p==4){
						ESNWay((*it).x-11.5, (*it).y-53, Player[0].x, Player[0].y, 10.0, 7, 6.5, FRED, true, 0, 0);
					}
					else if(p==5){
						ESNWay((*it).x+11.5, (*it).y-53, Player[0].x, Player[0].y, 10.0, 7, 6.5, FRED, true, 0, 0);
					}
				}
			}
			*/
		}
		else if(level==IMPOSSIBLE){
			int gx,gy;
			GetGraphSize(gBoss[2], &gx, &gy);
			float haba = gy/4.0;
			float plus = pow(-1,p%2)*haba*sin(Radian(2.0*(*it).i_hanyou[0],TRUE));
			(*it).y = CENTER_Y + plus;
			c = (c-60)%220;
			if((*it).count%2==0){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-11.5, (*it).y-53, 45.0+0.1*get_rand(1800), 1.5+0.1*get_rand(50), FRED, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+11.5, (*it).y-53, -45.0+0.1*get_rand(1800), 1.5+0.1*get_rand(50), FRED, true, 5, 30);
				}
			}
			if((*it).count%2==1){
				PlaySound(22);
				if(p==4){
					ESMake((*it).x-41.5, (*it).y-92, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(50), FBLUE, true, 5, 30);
				}
				else if(p==5){
					ESMake((*it).x+41.5, (*it).y-92, 45.0+0.1*get_rand(1800), 1.0+0.1*get_rand(50), FBLUE, true, 5, 30);
				}
			}
			if(c==120){
				PlaySound(20);
				if(p==4){
					EfMake((*it).x-10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x-10.5, (*it).y-156, -2, 11, 200);
				}
				else if(p==5){
					EfMake((*it).x+10.5, (*it).y-156, 4, 5);
					for(int i=0;i<8;i++)	EfMake((*it).x+10.5, (*it).y-156, -2, 11, 200);
				}
			}
			else if(c==160){
				Lto_x = Player[0].x;
				Lto_y = Player[0].y;
				Lspe_count = (*it).i_hanyou[0]-1;
				if(p==4){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x-10.5)),FALSE);
					ELMake((*it).x-10.5, (*it).y-156, 100.0, angle, 18.0, ESHOT(RICE,PURPLE), 4, 50);
				}
				else if(p==5){
					float angle = Radian(atan2(Player[0].y-((*it).y-156), Player[0].x-((*it).x+10.5)),FALSE);
					ELMake((*it).x+10.5, (*it).y-156, 100.0, angle, 18.0, ESHOT(RICE,PURPLE), 5, 50);
				}
			}
			
			(*it).i_hanyou[0]++;

			/*
			if(Player[0].hyper_count>0){
				if((*it).count%5==0){
					if(p==4){
						ESNWay((*it).x-11.5, (*it).y-53, Player[0].x, Player[0].y, 10.0, 7, 7.0, FRED, true, 0, 0);
					}
					else if(p==5){
						ESNWay((*it).x+11.5, (*it).y-53, Player[0].x, Player[0].y, 10.0, 7, 7.0, FRED, true, 0, 0);
					}
				}
			}
			*/
		}
	}

	return;
}

void BMove6(list<BOSSDATA>::iterator &it){
//ゴジラ最終スペル準備
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		(*it).bMuteki = true;
		BToMove(it, CENTER_X+60, 150, 60);
	}
	if(c==120){
		(*it).life = 0;
	}

	return;
}

void BMove7(list<BOSSDATA>::iterator &it){
//核符「ゴジラvsモスラ　～ 村岡は逃げる」（モスラ）
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		BToMove(it, CENTER_X+40, 200, 30);
	}
	if(c<30)	(*it).angle = Radian(90+1.5*(30-c),TRUE);
	else		(*it).angle = Radian(90,TRUE);
	if(c<180){}
	else{
		(*it).x += 2.0*sin(Radian(3*c,TRUE));
		(*it).y += 1.0*sin(Radian(5*c,TRUE));
	}

	if(c<90){}
	else{
		c -= 90;
		if(c==0){
			ELMake((*it).x-93, (*it).y+20.5, 30.0, 90.0, 12.0, ESHOT(BIG,RED), 6, 60);
			ELMake((*it).x+90, (*it).y+26.5, 30.0, 90.0, 12.0, ESHOT(BIG,RED), 7, 60);
		}
		if(c>=60&&c<=90){
			(*it).y = 200 - 60.0*pow(c-60,2)/900.0;
		}
		float plus_angle,pa2;
		if(c<120){
			plus_angle = 0;
			pa2 = 90.0 - 0.25*c;
		}
		else{
			plus_angle = 0.0*sin(Radian((*it).count-120,TRUE));
			pa2 = 60.0;
		}
		if(c%3==0){
			PlaySound(22);
			for(int i=0;i<5;i++){
				if(c<120&&i==2)	continue;
				ESMake((*it).x-93, (*it).y+20.5, 90-2*pa2+pa2*i+plus_angle, 9.0, ESHOT(UROKO,RED), false, 0, 0);
				ESMake((*it).x+90, (*it).y+26.5, 90-2*pa2+pa2*i-plus_angle, 9.0, ESHOT(UROKO,RED), false, 0, 0);
			}
		}
	}

	return;
}

void BMove8(list<BOSSDATA>::iterator &it){
//２面どあほ第一スペル準備
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		(*it).bMuteki = true;
		BToMove(it, CENTER_X, 150, 60);
	}
	if(c==90){
		SESDelete(3);	
		(*it).bMuteki = false;
		(*it).life = 0;
	}

	return;
}

void BMove9(list<BOSSDATA>::iterator &it){
//蒸発第一攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = (c-20)%280;
		if(c==0){
			PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
			for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 100);
		}
		if(c<40){}
		else if(c<160){
			c -= 40;
			if(level==EASY){
				if(c%2==0){
					PlaySound(21);
					float anglex = Radian(12.0*c,TRUE);
					float angley = Radian(9.0*c,TRUE);
					float angle = 10.0*c;
					float l = 1.5*c;
					float x[2],y[2];
					x[0] = (*it).x + l*cos(anglex);
					y[0] = (*it).y - 34 + l*sin(angley);
					x[1] = (*it).x - l*cos(anglex);
					y[1] = (*it).y - 34 - l*sin(angley);
					for(int i=0;i<2;i++){
						ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(RICE,RED+5*i), false, 0, 20, 4.0, 40);
					}
				}
			}
			else if(level==NORMAL){
				if(c%1==0){
					PlaySound(21);
					float anglex = Radian(12.0*c,TRUE);
					float angley = Radian(9.0*c,TRUE);
					float angle = 10.0*c;
					float l = 1.5*c;
					float x[2],y[2];
					x[0] = (*it).x + l*cos(anglex);
					y[0] = (*it).y - 34 + l*sin(angley);
					x[1] = (*it).x - l*cos(anglex);
					y[1] = (*it).y - 34 - l*sin(angley);
					for(int i=0;i<2;i++){
						ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(RICE,RED+5*i), false, 0, 20, 5.0, 40);
					}
				}
			}
			else if(level==HARD){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<3;i++){
						float anglex = Radian(12.0*c+120*i,TRUE);
						float angley = Radian(9.0*c+120*i,TRUE);
						float angle = 10.0*c+120*i;
						float l = 1.5*c;
						float x,y;
						x = (*it).x + l*cos(anglex);
						y = (*it).y - 34 + l*sin(angley);
						int img = RED;
						if(i%2==0)	img= BLUE;
						ESMake(x, y, angle, 1.0, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
					}
				}
			}
			else if(level==LUNATIC){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<3;i++){
						for(int j=0;j<2;j++){
							float anglex = Radian(12.0*c+120*i+60*j,TRUE);
							float angley = Radian(9.0*c+120*i+60*j,TRUE);
							float angle = 10.0*c+120*i+60*j;
							float l = 1.5*c;
							float x,y;
							x = (*it).x + l*cos(anglex);
							y = (*it).y - 34 + l*sin(angley);
							int img = RED;
							if(i%2==0)	img= BLUE;
							float speed = 1.0;
							if(j==1)	speed = 1.5;
							ESMake(x, y, angle, speed, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
						}
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<5;i++){
						for(int j=0;j<3;j++){
							float anglex = Radian(12.0*c+72*i+36*j,TRUE);
							float angley = Radian(9.0*c+72*i+36*j,TRUE);
							float angle = 10.0*c+72*i+36*j;
							float l = 1.5*c;
							float x,y;
							x = (*it).x + l*cos(anglex);
							y = (*it).y - 34 + l*sin(angley);
							int img = RED;
							if(i%2==1)	img= BLUE;
							float speed = 1.0;
							if(j==1)	speed = 1.5;
							if(j==2)	speed = 2.0;
							ESMake(x, y, angle, speed, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
						}
					}
				}
			}
		}
		else if(c==160){
			float x = (*it).x;
			float y = (*it).y;
			y = 140+get_rand(80);
			float plus = 60+get_rand(60);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 90);
		}
		else if(c<280){}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove10(list<BOSSDATA>::iterator &it){
//蒸発第二攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = (c-20)%280;
		if(c==0){
			PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
			for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 100);
		}
		if(c<40){}
		else if(c<160){
			c -= 40;
			if(level==EASY){
				if(c%2==0){
					PlaySound(21);
					float anglex = Radian(12.0*c,TRUE);
					float angley = Radian(9.0*c,TRUE);
					float angle = 10.0*c;
					float l = 1.5*c;
					float x[2],y[2];
					x[0] = (*it).x + l*cos(anglex);
					y[0] = (*it).y - 34 + l*sin(angley);
					x[1] = (*it).x - l*cos(anglex);
					y[1] = (*it).y - 34 - l*sin(angley);
					for(int i=0;i<2;i++){
						ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(RICE,RED+5*i), false, 0, 20, 4.0, 40);
					}
					if(c%20==0){
						for(int i=0;i<2;i++){
							ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(VERYBIG,BRED+6*i), true, 0, 20, 4.0, 40);
						}
					}
				}
			}
			else if(level==NORMAL){
				if(c%1==0){
					PlaySound(21);
					float anglex = Radian(12.0*c,TRUE);
					float angley = Radian(9.0*c,TRUE);
					float angle = 10.0*c;
					float l = 1.5*c;
					float x[2],y[2];
					x[0] = (*it).x + l*cos(anglex);
					y[0] = (*it).y - 34 + l*sin(angley);
					x[1] = (*it).x - l*cos(anglex);
					y[1] = (*it).y - 34 - l*sin(angley);
					for(int i=0;i<2;i++){
						ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(RICE,RED+5*i), false, 0, 20, 5.0, 40);
					}
					if(c%10==0){
						for(int i=0;i<2;i++){
							ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(VERYBIG,BRED+6*i), true, 0, 20, 4.0, 40);
						}
					}
				}
			}
			else if(level==HARD){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<3;i++){
						float anglex = Radian(12.0*c+120*i,TRUE);
						float angley = Radian(9.0*c+120*i,TRUE);
						float angle = 10.0*c+120*i;
						float l = 1.5*c;
						float x,y;
						x = (*it).x + l*cos(anglex);
						y = (*it).y - 34 + l*sin(angley);
						int img = RED;
						if(i%2==0)	img= BLUE;
						int img2 = BRED;
						if(i%2==0)	img2= BBLUE;
						ESMake(x, y, angle, 1.0, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
						if(c%8==0){
							ESMake(x, y, angle, 1.0, ESHOT(VERYBIG,img2), true, 0, 20, 4.0, 40);
						}
					}
				}
			}
			else if(level==LUNATIC){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<3;i++){
						for(int j=0;j<2;j++){
							float anglex = Radian(12.0*c+120*i+60*j,TRUE);
							float angley = Radian(9.0*c+120*i+60*j,TRUE);
							float angle = 10.0*c+120*i+60*j;
							float l = 1.5*c;
							float x,y;
							x = (*it).x + l*cos(anglex);
							y = (*it).y - 34 + l*sin(angley);
							int img = RED;
							if(i%2==0)	img= BLUE;
							int img2 = BRED;
							if(i%2==0)	img2= BBLUE;
							float speed = 1.0;
							if(j==1)	speed = 1.5;
							ESMake(x, y, angle, speed, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
							if(c%8==0){
								ESMake(x, y, angle, speed, ESHOT(VERYBIG,img2), true, 0, 20, 4.0, 40);
							}
						}
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<5;i++){
						for(int j=0;j<3;j++){
							float anglex = Radian(12.0*c+72*i+36*j,TRUE);
							float angley = Radian(9.0*c+72*i+36*j,TRUE);
							float angle = 10.0*c+72*i+36*j;
							float l = 1.5*c;
							float x,y;
							x = (*it).x + l*cos(anglex);
							y = (*it).y - 34 + l*sin(angley);
							int img = RED;
							if(i%2==1)	img= BLUE;
							int img2 = BRED;
							if(i%2==1)	img2= BBLUE;
							float speed = 1.0;
							if(j==1)	speed = 1.5;
							if(j==2)	speed = 2.0;
							ESMake(x, y, angle, speed, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
							if(c%6==0){
								ESMake(x, y, angle, speed, ESHOT(VERYBIG,img2), true, 0, 20, 4.0, 40);
							}
						}
					}
				}
			}
		}
		else if(c==160){
			float x = (*it).x;
			float y = (*it).y;
			y = 140+get_rand(80);
			float plus = 60+get_rand(60);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 90);
		}
		else if(c<280){}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove11(list<BOSSDATA>::iterator &it){
//蒸発第三攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = (c-20)%220;
		if(c==0){
			PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
			for(int i=0;i<16;i++)	EfMake((*it).x, (*it).y-34, -2, 11, 100);
		}
		if(c<40){}
		else if(c<160){
			c -= 40;
			if(level==EASY){
				if(c%2==0){
					PlaySound(21);
					float anglex = Radian(12.0*c,TRUE);
					float angley = Radian(9.0*c,TRUE);
					float angle = 3.0*c;
					float angle2 = -4.0*c;
					float l = 1.5*c;
					float x[2],y[2];
					x[0] = (*it).x + l*cos(anglex);
					y[0] = (*it).y - 34 + l*sin(angley);
					x[1] = (*it).x - l*cos(anglex);
					y[1] = (*it).y - 34 - l*sin(angley);
					for(int i=0;i<2;i++){
						ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(RICE,RED+5*i), false, 0, 20, 4.0, 40);
						ESMake(x[i], y[i], angle2*pow(-1,i), 1.0, ESHOT(RICE,PURPLE), false, 0, 20, 4.0, 40);
					}
				}
			}
			else if(level==NORMAL){
				if(c%1==0){
					PlaySound(21);
					float anglex = Radian(12.0*c,TRUE);
					float angley = Radian(9.0*c,TRUE);
					float angle = 3.0*c;
					float angle2 = -4.0*c;
					float l = 1.5*c;
					float x[2],y[2];
					x[0] = (*it).x + l*cos(anglex);
					y[0] = (*it).y - 34 + l*sin(angley);
					x[1] = (*it).x - l*cos(anglex);
					y[1] = (*it).y - 34 - l*sin(angley);
					for(int i=0;i<2;i++){
						ESMake(x[i], y[i], angle*pow(-1,i), 1.0, ESHOT(RICE,RED+5*i), false, 0, 20, 5.0, 40);
						ESMake(x[i], y[i], angle2*pow(-1,i), 1.0, ESHOT(RICE,PURPLE), false, 0, 20, 5.0, 40);
					}
				}
			}
			else if(level==HARD){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<3;i++){
						float anglex = Radian(12.0*c+120*i,TRUE);
						float angley = Radian(9.0*c+120*i,TRUE);
						float angle = 3.0*c+120*i;
						float angle2 = -4.0*c+120*i;
						float l = 1.5*c;
						float x,y;
						x = (*it).x + l*cos(anglex);
						y = (*it).y - 34 + l*sin(angley);
						int img = RED;
						if(i%2==0)	img= BLUE;
						ESMake(x, y, angle, 1.0, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
						ESMake(x, y, angle2, 1.0, ESHOT(RICE,PURPLE), false, 0, 20, 5.0, 40);
					}
				}
			}
			else if(level==LUNATIC){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<3;i++){
						for(int j=0;j<2;j++){
							float anglex = Radian(12.0*c+120*i+60*j,TRUE);
							float angley = Radian(9.0*c+120*i+60*j,TRUE);
							float angle = 3.0*c+120*i+60*j;
							float angle2 = -4.0*c+120*i+60*j;
							float l = 1.5*c;
							float x,y;
							x = (*it).x + l*cos(anglex);
							y = (*it).y - 34 + l*sin(angley);
							int img = RED;
							if(i%2==0)	img= BLUE;
							float speed = 1.0;
							if(j==1)	speed = 1.5;
							ESMake(x, y, angle, speed, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
							ESMake(x, y, angle2, 1.0, ESHOT(RICE,PURPLE), false, 0, 20, 5.0, 40);
						}
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%1==0){
					PlaySound(21);
					for(int i=0;i<5;i++){
						for(int j=0;j<3;j++){
							float anglex = Radian(12.0*c+72*i+36*j,TRUE);
							float angley = Radian(9.0*c+72*i+36*j,TRUE);
							float angle = 3.0*c+72*i+36*j;
							float angle2 = -4.0*c+72*i+36*j;
							float l = 1.5*c;
							float x,y;
							x = (*it).x + l*cos(anglex);
							y = (*it).y - 34 + l*sin(angley);
							int img = RED;
							if(i%2==1)	img= BLUE;
							float speed = 1.0;
							if(j==1)	speed = 1.5;
							if(j==2)	speed = 2.0;
							ESMake(x, y, angle, speed, ESHOT(RICE,img), false, 0, 20, 5.0, 40);
							ESMake(x, y, angle2, 1.0, ESHOT(RICE,PURPLE), false, 0, 20, 5.0, 40);
						}
					}
				}
			}
		}
		else if(c==160){
			float x = (*it).x;
			float y = (*it).y;
			y = 140+get_rand(80);
			float plus = 60+get_rand(60);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		else if(c<280){}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 6.5, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y-34, Player[0].x, Player[0].y, 10.0, 7, 12.0, ESHOT(RICE,RED), false, 0, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove12(list<BOSSDATA>::iterator &it){
//蒸発最終スペル準備
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		(*it).bMuteki = true;
		BToMove(it, CENTER_X, CENTER_Y, 60);
	}
	if(c==120){
		(*it).life = 0;
	}

	return;
}

void BMove13(list<BOSSDATA>::iterator &it){
//アホ３面中ボス
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = c-20;
		if(c==0){
			if(level==EASY){
				for(int i=0;i<2;i++){
					float angle = Radian(180*i,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 28, 24);
				}
			}
			else if(level==NORMAL){
				for(int i=0;i<3;i++){
					float angle = Radian(120*i,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 28, 24);
				}
			}
			else if(level==HARD){
				for(int i=0;i<2;i++){
					float angle = Radian(180*i+90,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 27, 24);
					angle = Radian(180*i,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 28, 24);
				}
			}
			else if(level==LUNATIC || level==IMPOSSIBLE){
				for(int i=0;i<2;i++){
					float angle = Radian(180*i+30,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 27, 24);
					angle = Radian(180*i+60,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 28, 24);
					angle = Radian(180*i,TRUE);
					EMake((*it).x+cos(angle), (*it).y+sin(angle), 256, 13, 29, 24);
				}
			}
		}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(KUNAI,RED), false, 30, 0);
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(KUNAI,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(KUNAI,RED), false, 30, 0);
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(KUNAI,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(KUNAI,RED), false, 30, 0);
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(KUNAI,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove14(list<BOSSDATA>::iterator &it){
//ゆやや第一攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = c-20;
		int c2 = c;
		c = c%300;
		if(level==EASY){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<6;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+60.0*j, 1.0, ESHOT(UROKO,RED), false, 33, 30, 2.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+60.0*j, 1.0, ESHOT(UROKO,BLUE), false, 34, 30, 2.0, 0, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==NORMAL){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<10;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+36.0*j, 1.0, ESHOT(UROKO,RED), false, 33, 30, 2.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+36.0*j, 1.0, ESHOT(UROKO,BLUE), false, 34, 30, 2.0, 0, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==HARD){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<8;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.8, ESHOT(UROKO,RED), false, 33, 30, 2.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.8, ESHOT(UROKO,BLUE), false, 34, 30, 2.0, 0, flag);
						}
						for(int j=0;j<8;j++){
							bool flag = false;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.5, ESHOT(UROKO,ORANGE), false, 34, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.5, ESHOT(UROKO,WATER), false, 33, 30, 3.0, 0, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==LUNATIC){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(30,TRUE);
					for(int i=0;i<6;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<8;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.8, ESHOT(UROKO,RED), false, 33, 30, 2.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.8, ESHOT(UROKO,BLUE), false, 34, 30, 2.0, 0, flag);
						}
						for(int j=0;j<8;j++){
							bool flag = false;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.5, ESHOT(UROKO,ORANGE), false, 34, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.5, ESHOT(UROKO,WATER), false, 33, 30, 3.0, 0, flag);
						}
						angle += Radian(60,TRUE);
					}
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(30,TRUE);
					for(int i=0;i<6;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<8;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.8, ESHOT(UROKO,RED), false, 33, 30, 2.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.8, ESHOT(UROKO,BLUE), false, 34, 30, 2.0, 0, flag);
						}
						for(int j=0;j<8;j++){
							bool flag = false;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.5, ESHOT(UROKO,ORANGE), false, 34, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 0.5, ESHOT(UROKO,WATER), false, 33, 30, 3.0, 0, flag);
						}
						for(int j=0;j<8;j++){
							bool flag = false;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 1.1, ESHOT(UROKO,RED), false, 33, 30, 4.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+45.0*j, 1.1, ESHOT(UROKO,BLUE), false, 34, 30, 3.0, 0, flag);
						}
						angle += Radian(60,TRUE);
					}
				}
			}
		}
		if(c==120){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove15(list<BOSSDATA>::iterator &it){
//ゆやや第二攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = c-20;
		int c2 = c;
		c = c%300;
		if(level==EASY){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<3;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+120.0*j, 1.0, ESHOT(UROKO,RED), false, 35, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+120.0*j, 1.0, ESHOT(UROKO,BLUE), false, 36, 30, 3.0, 0, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==NORMAL){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<4;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,RED), false, 35, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,BLUE), false, 36, 30, 3.0, 0, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==HARD){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<4;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 0.8, ESHOT(UROKO,RED), false, 35, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 0.8, ESHOT(UROKO,BLUE), false, 36, 30, 3.0, 0, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==LUNATIC){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(30,TRUE);
					for(int i=0;i<6;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<4;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 0.8, ESHOT(UROKO,RED), false, 35, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 0.8, ESHOT(UROKO,BLUE), false, 36, 30, 3.0, 0, flag);
						}
						angle += Radian(60,TRUE);
					}
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=150){
				if(c%6==0){
					PlaySound(18);
					float d = 20.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(30,TRUE);
					for(int i=0;i<6;i++){
						float x = (*it).x - 32 + d*cos(angle);
						float y = (*it).y - 45 + d*sin(angle);
						for(int j=0;j<4;j++){
							bool flag = false;
							if(j==0)	flag = true;
							if(c2/300%2==0)	ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 0.8, ESHOT(UROKO,RED), false, 35, 30, 3.0, 0, flag);
							else		ESMake(x, y, (*it).f_hanyou[2]+90.0*j, 0.8, ESHOT(UROKO,BLUE), false, 36, 30, 3.0, 0, flag);
						}
						angle += Radian(60,TRUE);
					}
				}
			}
		}
		if(c==120){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove16(list<BOSSDATA>::iterator &it){
//ゆやや第三攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c<20){}
	else{
		c = c-20;
		int c2 = c;
		c = c%300;
		if(level==EASY){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=180){
				if(c%2==0){
					PlaySound(18);
					float d = 12.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					float r;
					r = 30.0;
					float plus_ang;
					if(c2/300%2==0)	plus_ang = Radian(12.0*c,TRUE);
					else		plus_ang = Radian(-12.0*c,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle) + r*cos(angle+plus_ang);
						float y = (*it).y - 45 + d*sin(angle) + r*sin(angle+plus_ang);
						int gx,gy;
						GetGraphSize(gEShot[ESHOT(UROKO,PURPLE)],&gx,&gy);
						gx /= 2;
						gy /= 2;
						if(x+gx<10 || y+gy<10 || x-gx>430 || y-gy>470){
							angle += Radian(90,TRUE);
							continue;
						}
						for(int j=0;j<1;j++){
							bool flag = false;
							if(j==0)	flag = true;
							ESMake(x, y, Radian(angle+plus_ang,FALSE), 1.0, ESHOT(UROKO,PURPLE), false, 0, 30, 0.0, 60, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==NORMAL){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=180){
				if(c%1==0){
					PlaySound(18);
					float d = 12.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					float r;
					r = 30.0;
					float plus_ang;
					if(c2/300%2==0)	plus_ang = Radian(12.0*c,TRUE);
					else		plus_ang = Radian(-12.0*c,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle) + r*cos(angle+plus_ang);
						float y = (*it).y - 45 + d*sin(angle) + r*sin(angle+plus_ang);
						int gx,gy;
						GetGraphSize(gEShot[ESHOT(UROKO,PURPLE)],&gx,&gy);
						gx /= 2;
						gy /= 2;
						if(x+gx<10 || y+gy<10 || x-gx>430 || y-gy>470){
							angle += Radian(90,TRUE);
							continue;
						}
						for(int j=0;j<1;j++){
							bool flag = false;
							if(j==0)	flag = true;
							ESMake(x, y, Radian(angle+plus_ang,FALSE), 1.0, ESHOT(UROKO,PURPLE), false, 0, 30, 0.0, 60, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==HARD){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=180){
				if(c%1==0){
					PlaySound(18);
					float d = 12.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(45,TRUE);
					float r;
					r = 30.0;
					float plus_ang;
					if(c2/300%2==0)	plus_ang = Radian(12.0*c,TRUE);
					else		plus_ang = Radian(-12.0*c,TRUE);
					for(int i=0;i<4;i++){
						float x = (*it).x - 32 + d*cos(angle) + r*cos(angle+plus_ang);
						float y = (*it).y - 45 + d*sin(angle) + r*sin(angle+plus_ang);
						int gx,gy;
						GetGraphSize(gEShot[ESHOT(UROKO,PURPLE)],&gx,&gy);
						gx /= 2;
						gy /= 2;
						if(x+gx<10 || y+gy<10 || x-gx>430 || y-gy>470){
							angle += Radian(90,TRUE);
							continue;
						}
						for(int j=0;j<3;j++){
							bool flag = false;
							if(j==0)	flag = true;
							ESMake(x, y, Radian(angle+plus_ang,FALSE)+120.0*j, 1.0, ESHOT(UROKO,PURPLE), false, 0, 30, 0.0, 60, flag);
						}
						angle += Radian(90,TRUE);
					}
				}
			}
		}
		else if(level==LUNATIC || level==IMPOSSIBLE){
			if(c==0){
				PlaySound(22);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = get_rand(360);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 5.0, ESHOT(VERYBIG,BBLUE), false, 0, 10);				
			}
			if(c>60 && c<=180){
				if(c%1==0){
					PlaySound(18);
					float d = 12.0*(c-60)/3.0;
					float angle = Atan2((*it).f_hanyou[1]-((*it).y-45), (*it).f_hanyou[0]-((*it).x-32));
					angle -= Radian(30,TRUE);
					float r;
					r = 30.0;
					float plus_ang;
					if(c2/300%2==0)	plus_ang = Radian(12.0*c,TRUE);
					else		plus_ang = Radian(-12.0*c,TRUE);
					for(int i=0;i<6;i++){
						float x = (*it).x - 32 + d*cos(angle) + r*cos(angle+plus_ang);
						float y = (*it).y - 45 + d*sin(angle) + r*sin(angle+plus_ang);
						int gx,gy;
						GetGraphSize(gEShot[ESHOT(UROKO,PURPLE)],&gx,&gy);
						gx /= 2;
						gy /= 2;
						if(x+gx<10 || y+gy<10 || x-gx>430 || y-gy>470){
							angle += Radian(60,TRUE);
							continue;
						}
						for(int j=0;j<3;j++){
							bool flag = false;
							if(j==0)	flag = true;
							ESMake(x, y, Radian(angle+plus_ang,FALSE)+120.0*j, 1.0, ESHOT(UROKO,PURPLE), false, 0, 30, 0.0, 60, flag);
							if(level==IMPOSSIBLE){
								ESMake(x, y, Radian(angle+plus_ang,FALSE)+120.0*j, 2.0, ESHOT(UROKO,PURPLE), false, 0, 30, 0.0, 60, false);
							}
						}
						angle += Radian(60,TRUE);
					}
				}
			}
		}
		if(c==180){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}

	return;
}

void BMove17(list<BOSSDATA>::iterator &it){
//ゆやや第四攻撃
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	bES = false;
	
	if(c<0){}
	else{
		c = c-0;
		if((*it).i_hanyou[0]==0)	(*it).i_hanyou[1]++;
		else				(*it).i_hanyou[1] = 0;
		(*it).i_hanyou[0] = 0;
		if(level==EASY || level==NORMAL){
			if((*it).i_hanyou[1]==90){
				PlaySound(22);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 6.0, ESHOT(VERYBIG,BBLUE), false, 37, 10, 0.0, 60);				
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 90.0, 4, 6.0, ESHOT(VERYBIG,BBLUE), false, 38, 10, 0.0, 60, false);				
			}
			(*it).f_hanyou[0] += 2.0;
		}
		else if(level==HARD || level==LUNATIC || level==IMPOSSIBLE){
			if((*it).i_hanyou[1]==90){
				PlaySound(22);
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 6.0, ESHOT(VERYBIG,BBLUE), false, 37, 10, 0.0, 60);				
				ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 60.0, 6, 6.0, ESHOT(VERYBIG,BBLUE), false, 38, 10, 0.0, 60, false);				
			}
			(*it).f_hanyou[0] += 2.0;
		}
		if(c%120==0){
			float x = (*it).x;
			float y = (*it).y;
			y = 170+get_rand(50);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
		if(Player[0].hyper_count>0){
			/*
			if(level==HARD){
				if((*it).count%8==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 3.5, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==LUNATIC){
				if((*it).count%5==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 5.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			else if(level==IMPOSSIBLE){
				if((*it).count%1==0){
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,RED), false, 30, 0);
					ESNWay((*it).x-32, (*it).y-45, Player[0].x, Player[0].y, 10.0, 7, 7.0, ESHOT(ICE,BLUE), false, 31, 0);
				}
			}
			*/
		}
	}
	bES = true;

	return;
}

void BMove18(list<BOSSDATA>::iterator &it){
//神コンデンサー第一形態
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(c<180){
		float to_x = CENTER_X;
		float to_y = 150;
		if(c==0){
			float sx = (*it).x - to_x;
			float sy = (*it).y - to_y;
			(*it).f_hanyou[0] = Atan2(sy,sx);
			(*it).f_hanyou[1] = ((*it).f_hanyou[0] - (-M_PI/2.0)) / 180.0;
			(*it).f_hanyou[2] = sqrt(sx*sx+sy*sy);
			(*it).f_hanyou[3] = (*it).f_hanyou[2] / 180.0;
		}
		(*it).f_hanyou[2] -= (*it).f_hanyou[3];
		(*it).f_hanyou[0] -= (*it).f_hanyou[1];
		(*it).x = to_x + (*it).f_hanyou[2]*cos((*it).f_hanyou[0]);
		(*it).y = to_y + (*it).f_hanyou[2]*sin((*it).f_hanyou[0]);
	}
	else{
		c = (c-180)%4390;
		if(c<800){
			(*it).x += 1.5*cos(Radian(2.0*c,TRUE));
			(*it).y += 1.5*cos(Radian(3.0*c,TRUE));
			if(level==NORMAL){
				int num;
				if(c<330)	num = 2;
				else if(c<450)	num = 4;
				//else if(c<588)	num = 8;
				else if(c<650)	num = 8;
				else if(c<710)	num = 16;
				else		num = 32;
				if(c%5==0 || c%8==0){
					for(int i=0;i<num;i++){
						float angle = 3.0*(c/4) + (360.0/(float)num)*i;
						bool flag = false;
						if(i==0)	flag = true;
						if(c%5==0){
							int img = ESHOT(MEDIUM,BLUE);
							if(c%10==0)	img = ESHOT(SMALL,BLUE);
							ESMake((*it).x, (*it).y, angle, 6.0, img, false, 0, 10, 0.0, 0, flag);
						}
						if(c%8==0)	ESMake((*it).x, (*it).y, -angle, 6.0, ESHOT(MEDIUM,RED), false, 0, 10, 0.0, 0, flag);
					}
				}
			}
			else if(level==HARD){
				int num;
				if(c<330)	num = 2;
				else if(c<450)	num = 4;
				else if(c<588)	num = 8;
				else if(c<650)	num = 16;
				else if(c<710)	num = 32;
				else		num = 64;
				if(c%5==0 || c%8==0){
					for(int i=0;i<num;i++){
						float angle = 3.0*(c/4) + (360.0/(float)num)*i;
						bool flag = false;
						if(i==0)	flag = true;
						if(c%5==0){
							int img = ESHOT(MEDIUM,BLUE);
							if(c%10==0)	img = ESHOT(SMALL,BLUE);
							ESMake((*it).x, (*it).y, angle, 6.0, img, false, 0, 10, 0.0, 0, flag);
						}
						if(c%8==0)	ESMake((*it).x, (*it).y, -angle, 6.0, ESHOT(MEDIUM,RED), false, 0, 10, 0.0, 0, flag);
					}
				}
			}
			else if(level==LUNATIC){
				int num;
				if(c<330)	num = 2;
				else if(c<450)	num = 4;
				else if(c<588)	num = 8;
				else if(c<650)	num = 16;
				else if(c<710)	num = 32;
				else		num = 64;
				if(c%5==0 || c%8==0){
					for(int i=0;i<num;i++){
						float angle = 3.0*(c/4) + (360.0/(float)num)*i;
						bool flag = false;
						if(i==0)	flag = true;
						if(c%5==0){
							int img = ESHOT(MEDIUM,BLUE);
							if(c%10==0)	img = ESHOT(SMALL,BLUE);
							ESMake((*it).x, (*it).y, angle, 6.0, img, false, 0, 10, 0.0, 0, flag);
							ESMake((*it).x, (*it).y, angle, 5.0, img, false, 0, 10, 0.0, 0, false);
						}
						if(c%8==0){
							ESMake((*it).x, (*it).y, -angle, 6.0, ESHOT(MEDIUM,RED), false, 0, 10, 0.0, 0, flag);
							ESMake((*it).x, (*it).y, -angle, 5.0, ESHOT(MEDIUM,RED), false, 0, 10, 0.0, 0, false);
						}
					}
				}
			}
			else if(level==IMPOSSIBLE){
				int num;
				if(c<330)	num = 2;
				else if(c<450)	num = 4;
				else if(c<588)	num = 8;
				else if(c<650)	num = 16;
				else if(c<710)	num = 32;
				else		num = 64;
				if(c%5==0 || c%8==0){
					for(int i=0;i<num;i++){
						float angle = 3.0*(c/4) + (360.0/(float)num)*i;
						bool flag = false;
						if(i==0)	flag = true;
						if(c%5==0){
							int img = ESHOT(MEDIUM,BLUE);
							if(c%10==0)	img = ESHOT(SMALL,BLUE);
							ESMake((*it).x, (*it).y, angle, 6.0, img, false, 0, 10, 0.0, 0, flag);
							for(int j=0;j<3;j++)	ESMake((*it).x, (*it).y, angle, 5.5-0.5*j, img, false, 0, 10, 0.0, 0, false);
						}
						if(c%8==0){
							ESMake((*it).x, (*it).y, -angle, 6.0, ESHOT(MEDIUM,RED), false, 0, 10, 0.0, 0, flag);
							for(int j=0;j<3;j++)	ESMake((*it).x, (*it).y, -angle, 5.5-0.5*j, ESHOT(MEDIUM,RED), false, 0, 10, 0.0, 0, false);
						}
					}
				}
			}
		}
		else if(c<1850){
			if(c==800){
				BToMove(it, CENTER_X, CENTER_Y, 60);
				(*it).i_hanyou[0] = 0;
			}
			else if(c<859){}
			else if(c==859){
				for(int i=0;i<15;i++){
					ELMake((*it).x, (*it).y, 15.0, 24.0*i, 12.0, ESHOT(RICE,PURPLE), 33, 60);
				}
			}
			else{
				int num;
				if(level==NORMAL){
					if(c==860)	(*it).f_hanyou[0] = 90.0;
					if(c<1100){
						num = 4;
						(*it).f_hanyou[0] += 0.5;
						(*it).i_hanyou[0] = 0;
					}
					else if(c<1340){
						num = 6;
						(*it).f_hanyou[0] -= 0.75;
						(*it).i_hanyou[0] = 1;
					}
					else if(c<1580){
						num = 8;
						(*it).f_hanyou[0] += 1.0;
						(*it).i_hanyou[0] = 0;
					}
					else if(c<1700){
						num = 10;
						(*it).f_hanyou[0] -= 1.25;
						(*it).i_hanyou[0] = 1;
					}
					else if(c<1820){
						num = 10;
						(*it).f_hanyou[0] -= 1.25;
						(*it).i_hanyou[0] = 1;
					}
					else{
						(*it).i_hanyou[0] = 2;
					}
				}
				else if(level==HARD){
					if(c==860)	(*it).f_hanyou[0] = 90.0;
					if(c<1100){
						num = 4;
						(*it).f_hanyou[0] += 0.5;
						(*it).i_hanyou[0] = 0;
					}
					else if(c<1340){
						num = 6;
						(*it).f_hanyou[0] -= 0.8;
						(*it).i_hanyou[0] = 1;
					}
					else if(c<1580){
						num = 8;
						(*it).f_hanyou[0] += 1.1;
						(*it).i_hanyou[0] = 0;
					}
					else if(c<1700){
						num = 10;
						(*it).f_hanyou[0] -= 1.4;
						(*it).i_hanyou[0] = 1;
					}
					else if(c<1820){
						num = 10;
						(*it).f_hanyou[0] -= 1.7;
						(*it).i_hanyou[0] = 1;
					}
					else{
						(*it).i_hanyou[0] = 2;
					}
				}
				else if(level==LUNATIC || level==IMPOSSIBLE){
					if(c==860)	(*it).f_hanyou[0] = 90.0;
					if(c<1100){
						num = 4;
						(*it).f_hanyou[0] += 0.5;
						(*it).i_hanyou[0] = 0;
					}
					else if(c<1340){
						num = 6;
						(*it).f_hanyou[0] -= 0.75;
						(*it).i_hanyou[0] = 1;
					}
					else if(c<1580){
						num = 12;
						(*it).f_hanyou[0] += 1.25;
						(*it).i_hanyou[0] = 0;
					}
					else if(c<1700){
						num = 20;
						(*it).f_hanyou[0] -= 1.5;
						(*it).i_hanyou[0] = 1;
					}
					else if(c<1820){
						num = 20;
						(*it).f_hanyou[0] -= 2.0;
						(*it).i_hanyou[0] = 1;
					}
					else{
						(*it).i_hanyou[0] = 2;
					}
				}
				if((*it).i_hanyou[0]<=1){
					if(c%5==0){
						for(int j=0;j<5;j++){
							if(level==IMPOSSIBLE){
								if(j==0)	ang_plus = 0;
								else if(j==1)	ang_plus = 2.0;
								else if(j==2)	ang_plus = -2.0;
								else if(j==3)	ang_plus = 4.0;
								else if(j==4)	ang_plus = -4.0;
							}
							else{
								if(j==0)	ang_plus = 0;
								else if(j==1)	ang_plus = 1.0;
								else if(j==2)	ang_plus = -1.0;
								else if(j==3)	ang_plus = 2.0;
								else if(j==4)	ang_plus = -2.0;
							}
							ESNWay((*it).x, (*it).y, (*it).x+cos(Radian((*it).f_hanyou[0],TRUE)), (*it).y+sin(Radian((*it).f_hanyou[0],TRUE)), 360.0/(float)num, num, 9.0, ESHOT(ZAYAKU,BLUE), false, 0, 0, 0.0, 0, false);
							ang_plus = 0;
						}
					}
				}
			}
		}
		else if(c<3380){
			if(c==1850){
				BToMove(it, CENTER_X, 100, 30);
				(*it).i_hanyou[0] = 0;
			}
			else if(c<1879){}
			else if(c==1879){
				for(int i=0;i<5;i++){
					ELMake(0.0, -10.0-100.0*i, 15.0, 0.0, 12.0, ESHOT(RICE,PURPLE), 34, 60);
					ELMake(440.0, -60.0-100.0*i, 15.0, 180.0, 12.0, ESHOT(RICE,PURPLE), 35, 60);
				}
			}
			else if(c<2360){
				c -= 1880;
				if(level==HARD || level==LUNATIC || level==IMPOSSIBLE){
					if(c==180){
						for(int i=0;i<5;i++){
							ELMake(450.0+100.0*i, 0.0, 15.0, 90.0, 12.0, ESHOT(RICE,PURPLE), 37, 60);
							ELMake(-10.0-100.0*i, 480.0, 15.0, -90.0, 12.0, ESHOT(RICE,PURPLE), 36, 60);
						}
					}
				}
				if(level==NORMAL){
					if(c%60==0){
						(*it).i_hanyou[1] = 12;
						(*it).f_hanyou[0] = Player[0].x;
						(*it).f_hanyou[1] = Player[0].y;
					}
					if(c%5==0){
						for(int i=0;i<5;i++){
							ang_plus = 72.0*i;
							ESNWay((*it).x, (*it).y, (*it).f_hanyou[0], (*it).f_hanyou[1], 2.0, (*it).i_hanyou[1], 2.0+(float)(c%60)*0.1, ESHOT(ZAYAKU,BLUE), false, 0, 5);
							ang_plus = 0;
						}
						(*it).i_hanyou[1]--;
					}
				}
				else if(level==HARD || level==LUNATIC || level==IMPOSSIBLE){
					if(c%60==0){
						(*it).i_hanyou[1] = 15;
						(*it).f_hanyou[0] = Player[0].x;
						(*it).f_hanyou[1] = Player[0].y;
					}
					if(c%4==0){
						for(int i=0;i<5;i++){
							ang_plus = 72.0*i;
							ESNWay((*it).x, (*it).y, (*it).f_hanyou[0], (*it).f_hanyou[1], 1.0, (*it).i_hanyou[1], 3.0+(float)(c%60)*0.1, ESHOT(ZAYAKU,BLUE), false, 0, 5);
							ang_plus = 0;
						}
						(*it).i_hanyou[1]--;
					}
				}
				c += 1880;
			}
			else if(c==2360){
				BToMove(it, CENTER_X, CENTER_Y, 60);
				(*it).i_hanyou[1] = 15;
			}
			else if(c<2420){}
			else if(c<3320){
				c -= 2420;
				if(c%60==0)	(*it).i_hanyou[1] += 3;
				bool flag = false;
				if(c%60<(*it).i_hanyou[1])	flag = true; 
				if(flag==true){
					PlaySound(22);
					if(level==LUNATIC || level==IMPOSSIBLE){
						for(int i=0;i<3;i++){
							ESMake((*it).x, (*it).y, 2.0*c+120.0*i, 0.0, ESHOT(BIG,BLUE), true, 51, 5, 8.0, 30, true);					
							if(level==IMPOSSIBLE)	ESMake((*it).x, (*it).y, 60.0+2.0*c+120.0*i, 0.0, ESHOT(BIG,RED), true, 51, 5, 5.0, 30, true);
						}
					}
					else{
						ESMake((*it).x, (*it).y, 2.0*c, 0.0, ESHOT(BIG,BLUE), false, 51, 5, 8.0, 30, true);					
					}
				}
				c += 2420;
			}
			else	(*it).i_hanyou[0] = 1;
		}
		else if(c<4300){
			if(c==3380){
				BToMove(it, CENTER_X, 130, 60);
				(*it).f_hanyou[0] = 0;
			}
			else if(c<3440){}
			else{
				(*it).x += 1.5*cos(Radian(2.0*c,TRUE));
				(*it).y += 1.5*cos(Radian(3.0*c,TRUE));
				if((*it).x<Player[0].x)	(*it).x += 1.0;
				else			(*it).x -= 1.0;
				if(level==NORMAL){
					if(c%4==0){
						float r = 120.0*sin(Radian((*it).f_hanyou[0],TRUE));
						for(int i=0;i<3;i++){
							for(int j=0;j<5;j++){
								ESMake((*it).x+r*cos(Radian(2.0*c+120*i,TRUE)), (*it).y+r*cos(Radian(2.0*c+120*i,TRUE)), 4.0*c+120*i+72*j, 3.0, ESHOT(MEDIUM,PURPLE), false, 0, 5);					
							}
						}
					}
				}
				else if(level==HARD){
					if(c%3==0){
						float r = 120.0*sin(Radian((*it).f_hanyou[0],TRUE));
						for(int i=0;i<3;i++){
							for(int j=0;j<5;j++){
								ESMake((*it).x+r*cos(Radian(2.0*c+120*i,TRUE)), (*it).y+r*cos(Radian(2.0*c+120*i,TRUE)), 4.0*c+120*i+72*j, 3.0, ESHOT(MEDIUM,PURPLE), false, 0, 5);					
							}
						}
					}
				}
				else if(level==LUNATIC || level==IMPOSSIBLE){
					if(c%3==0){
						float r = 120.0*sin(Radian((*it).f_hanyou[0],TRUE));
						for(int i=0;i<3;i++){
							for(int j=0;j<9;j++){
								ESMake((*it).x+r*cos(Radian(2.0*c+120*i,TRUE)), (*it).y+r*cos(Radian(2.0*c+120*i,TRUE)), 4.0*c+120*i+40*j, 3.0, ESHOT(MEDIUM,PURPLE), false, 0, 5);					
							}
						}
					}
				}
				(*it).f_hanyou[0] += 1.0;
			}
		}
		else if(c==4300){
			BToMove(it, CENTER_X, 150, 90);
		}
		else{}
	}

	return;
}

void BMove19(list<BOSSDATA>::iterator &it){
//「妖蛾乱舞」(準備)
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		(*it).bMuteki = true;
		(*it).f_hanyou[0] = 288;
		(*it).f_hanyou[1] = 108;
		(*it).f_hanyou[2] = 90;
	}
	if(c==90){
		SESDelete(3);	
		(*it).bMuteki = false;
		(*it).life = 0;
	}

	if(c<90){
		(*it).f_hanyou[0] -= 3.2;
		(*it).f_hanyou[1] -= 2.5;
		(*it).x = CENTER_X + (*it).f_hanyou[0]*cos(Radian((*it).f_hanyou[1],TRUE));
		(*it).y = CENTER_Y + (*it).f_hanyou[0]*sin(Radian((*it).f_hanyou[1],TRUE));
	}

	return;
}

void BMove20(list<BOSSDATA>::iterator &it){
//「ヤンデレスカイハイ」(準備)
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		(*it).bMuteki = true;
		BToMove(it, CENTER_X, CENTER_Y, 90);
		(*it).mrate_x = 0;
		(*it).mrate_y = 0;
		(*it).f_hanyou[0] = 315;
		(*it).f_hanyou[1] = 90;
	}
	if(c==90){
		SESDelete(3);	
		(*it).bMuteki = false;
		(*it).life = 0;
	}

	if(c<90){
		(*it).f_hanyou[0] -= 3.5;
		(*it).f_hanyou[1] -= 8.0;
		(*it).x = CENTER_X + (*it).f_hanyou[0]*cos(Radian((*it).f_hanyou[1],TRUE));
		(*it).y = CENTER_Y - 40 + (*it).f_hanyou[0]*sin(Radian((*it).f_hanyou[1],TRUE));
	}
	(*it).to_x = (*it).x;
	(*it).to_y = (*it).y;

	return;
}

void BMove21(list<BOSSDATA>::iterator &it){
//神コンデンサー第二形態
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0){
		(*it).bMuteki = true;
		(*it).f_hanyou[0] = 288;
		(*it).f_hanyou[1] = 108;
		(*it).f_hanyou[2] = 90;
	}
	if(c==90){
		SESDelete(3);	
		(*it).bMuteki = false;
		(*it).life = 0;
	}

	if(c<90){
		(*it).f_hanyou[0] -= 3.2;
		(*it).f_hanyou[1] -= 2.5;
		(*it).x = CENTER_X + (*it).f_hanyou[0]*cos(Radian((*it).f_hanyou[1],TRUE));
		(*it).y = CENTER_Y + (*it).f_hanyou[0]*sin(Radian((*it).f_hanyou[1],TRUE));
	}

	return;
}

void BMove22(list<BOSSDATA>::iterator &it){
//おかび第一通常
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0)	(*it).i_hanyou[0] = 10;
	else if(c<20){}
	else{
		c = (c-20)%250;
		if(c==0){
			//PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
		}
		else if(c<20){
			for(int i=0;i<1;i++)	EfMake((*it).x, (*it).y, -2, 11, 100+5*c);
		}
		if(c<40){}
		else if(c<70){
			c-=40;
			if(c==0){
				(*it).f_hanyou[0] = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			}
			if(c%2==0){
				PlaySound(22);
				for(int i=0;i<(*it).i_hanyou[0];i++){
					float angle;
					float base = 360.0 / (float)(*it).i_hanyou[0];
					int img;
					if((*it).i_hanyou[0]%2==0){
						angle = base/2.0 + base*i;
						img = FBLUE;
					}
					else{
						angle = base*i;
						img = FRED;
					}
					angle = (*it).f_hanyou[0]+Radian(angle,TRUE);
					float r = 20.0 + c*15;
					float x = (*it).x + r*cos(angle);
					float y = (*it).y + r*sin(angle);
					float sx = x - Player[0].x;
					float sy = y - Player[0].y;
					if(sx*sx+sy*sy >= 50*50)	ESMake(x, y, Radian(angle,FALSE), 0.0, img, true, 53+(*it).i_hanyou[0]%2, 10, 0.0, 30-c+50);
				}
			}
			c+=40;
		}
		else if(c==70)	(*it).i_hanyou[0]++;
		else if(c<190){}
		else if(c==190){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
	}

	return;
}

void BMove23(list<BOSSDATA>::iterator &it){
//おかび第二通常
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0)	(*it).i_hanyou[0] = 10;
	else if(c<20){}
	else{
		c = (c-20)%250;
		if(c==0){
			//PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
		}
		else if(c<20){
			for(int i=0;i<1;i++)	EfMake((*it).x, (*it).y, -2, 11, 100+5*c);
		}
		if(c<40){}
		else if(c<70){
			c-=40;
			if(c==0){
				(*it).f_hanyou[0] = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			}
			if(c%2==0){
				PlaySound(22);
				for(int i=0;i<(*it).i_hanyou[0];i++){
					float angle;
					float base = 360.0 / (float)(*it).i_hanyou[0];
					int img;
					if((*it).i_hanyou[0]%2==0){
						angle = base/2.0 + base*i + 5.0*c;
						img = FBLUE;
					}
					else{
						angle = base*i - 5.0*c;
						img = FRED;
					}
					angle = (*it).f_hanyou[0]+Radian(angle,TRUE);
					float r = 20.0 + c*15;
					float x = (*it).x + r*cos(angle);
					float y = (*it).y + r*sin(angle);
					float sx = x - Player[0].x;
					float sy = y - Player[0].y;
					if(sx*sx+sy*sy >= 50*50)	ESMake(x, y, Radian(angle,FALSE), 0.0, img, true, 55+(*it).i_hanyou[0]%2, 10, 0.0, 30-c+50);
				}
			}
			c+=40;
		}
		else if(c==70)	(*it).i_hanyou[0]++;
		else if(c<190){}
		else if(c==190){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
	}

	return;
}

void BMove24(list<BOSSDATA>::iterator &it){
//おかび第三通常
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0)	(*it).i_hanyou[0] = 8;
	else if(c<20){}
	else{
		c = (c-20)%265;
		if(c==0){
			//PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
		}
		else if(c<20){
			for(int i=0;i<1;i++)	EfMake((*it).x, (*it).y, -2, 11, 100+5*c);
		}
		if(c<55){}
		else if(c<85){
			c-=55;
			if(c==0){
				(*it).f_hanyou[0] = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			}
			if(c%2==0){
				PlaySound(22);
				for(int i=0;i<(*it).i_hanyou[0]+1;i++){
					float angle;
					float base = 360.0 / (float)((*it).i_hanyou[0]+1);
					int img;
					angle = base*i - 5.0*c;
					img = FRED;
					angle = (*it).f_hanyou[0]+Radian(angle,TRUE);
					float r = 20.0 + c*15;
					float x = (*it).x + r*cos(angle);
					float y = (*it).y + r*sin(angle);
					float sx = x - Player[0].x;
					float sy = y - Player[0].y;
					if(sx*sx+sy*sy >= 50*50)	ESMake(x, y, Radian(angle,FALSE), 0.0, img, true, 56, 10, 0.0, 30-c+50);
				}
			}
			c+=55;
		}
		else if(c==85) (*it).i_hanyou[0]+=2;
		if(c<40){}
		else if(c<70){
			c-=40;
			if(c==0){
				(*it).f_hanyou[0] = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			}
			if(c%2==0){
				PlaySound(22);
				for(int i=0;i<(*it).i_hanyou[0];i++){
					float angle;
					float base = 360.0 / (float)(*it).i_hanyou[0];
					int img;
					angle = base/2.0 + base*i + 5.0*c;
					img = FBLUE;
					angle = (*it).f_hanyou[0]+Radian(angle,TRUE);
					float r = 20.0 + c*15;
					float x = (*it).x + r*cos(angle);
					float y = (*it).y + r*sin(angle);
					float sx = x - Player[0].x;
					float sy = y - Player[0].y;
					if(sx*sx+sy*sy >= 50*50)	ESMake(x, y, Radian(angle,FALSE), 0.0, img, true, 55, 10, 0.0, 30-c+50);
				}
			}
			c+=40;
		}
		else if(c<205){}
		else if(c==205){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
	}

	return;
}

void BMove25(list<BOSSDATA>::iterator &it){
//おかび第四通常
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	bRG = false;
	
	if(c==0)	(*it).i_hanyou[0] = 10;
	else if(c<20){}
	else{
		c = (c-20)%250;
		if(c==0){
			//PlaySound(20);
			EfMake((*it).x, (*it).y, 4, 5);
		}
		else if(c<20){
			for(int i=0;i<1;i++)	EfMake((*it).x, (*it).y, -2, 11, 100+5*c);
		}
		if(c<40){}
		else if(c<100){
			c-=40;
			if(c==0){
				(*it).f_hanyou[0] = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			}
			if(c%2==0){
				PlaySound(22);
				for(int i=0;i<(*it).i_hanyou[0];i++){
					float angle;
					float base = 360.0 / (float)(*it).i_hanyou[0];
					int img;
					if((*it).i_hanyou[0]%2==0){
						angle = base/2.0 + base*i + 5.0*c;
						img = FBLUE;
					}
					else{
						angle = base*i - 5.0*c;
						img = FRED;
					}
					angle = (*it).f_hanyou[0]+Radian(angle,TRUE);
					float r = 20.0 + c*7.5;
					float x = (*it).x + r*cos(angle);
					float y = (*it).y + r*sin(angle);
					float sx = x - Player[0].x;
					float sy = y - Player[0].y;
					if(sx*sx+sy*sy >= 50*50)	ESMake(x, y, Radian(angle,FALSE), 0.0, img, true, 57+(*it).i_hanyou[0]%2, 10, 0.0, 60-c+50);
				}
			}
			c+=40;
		}
		else if(c==100)	(*it).i_hanyou[0]++;
		else if(c<190){}
		else if(c==190){
			float x = (*it).x;
			float y = (*it).y;
			y = 110+get_rand(80);
			float plus = 30+get_rand(70);
			if(Player[0].x<(*it).x){
				if(x-plus<90)	x += plus;
				else		x -= plus;
			}
			else{
				if(x+plus>350)	x -= plus;
				else		x += plus;
			}
			BToMove(it, x, y, 60);
		}
	}

	return;
}

void BMove(list<BOSSDATA>::iterator &it){
	if((*it).life<=0){
		(*it).life = 0;
		if((*it).death_count==0)	SESDelete(2,(*it).x,(*it).y);
		else				SESDelete(0);
		if((*it).death_count==0){
			int ggx,ggy;
			GetGraphSize(gBoss[(*it).img], &ggx, &ggy);
			for(int i=0;i<20;i++)	IMake((*it).x-ggx/2+get_rand(ggx), (*it).y-ggy/2+get_rand(ggy), 3);			
			if((*it).img==3 && Player[0].stage==2)	IMake((*it).x, (*it).y, 4);
			if((*it).img==3 && Player[0].stage==3)	IMake((*it).x, (*it).y, 5);
		}
		if((*it).death_count<120){
			int gx,gy;
			GetGraphSize(gBoss[(*it).img],&gx,&gy);
			EfMake((*it).x-gx/2+get_rand(gx), (*it).y-gy/2+get_rand(gy), 3, 4);
			if((*it).death_count%5==0){
				PlaySound(18);
			}
			(*it).x += 1;
			(*it).y += 1;
		}
		else if((*it).death_count==120){
			PlaySound(19);
			(*it).bDeath= true;
			if(NowPart==BOSS){
				if((*it).img==1)	TMake(1);
				else if((*it).img==4)	TMake(3);
				else if((*it).img==5)	TMake(5);
			}
		}
		
		(*it).death_count++;
		return;
	}

	int p = (*it).pattern;
	int c = (*it).count;
	
	if((*it).bSpell==false){
		if(p==0)	BMove0(it);//モスラ第一攻撃
		else if(p==1)	BMove1(it);//モスラ第二攻撃
		else if(p==2)	BMove2(it);//ゴジラ第一攻撃
		else if(p==3)	BMove3(it);//ゴジラ第二攻撃
		else if(p==4 || p==5)	BMove4(it);//うんざん（横）
		else if(p==6)	BMove6(it);//ゴジラ最終スペル準備
		else if(p==7)	BMove7(it);//核符「ゴジラvsモスラ　～ 村岡は逃げる」（モスラ）
		else if(p==8)	BMove8(it);//２面どあほ第一スペル準備
		else if(p==9)	BMove9(it);//蒸発第一攻撃
		else if(p==10)	BMove10(it);//蒸発第二攻撃
		else if(p==11)	BMove11(it);//蒸発第三攻撃
		else if(p==12)	BMove12(it);//蒸発最終スペル準備
		else if(p==13)	BMove13(it);//3面中ボスアホ
		else if(p==14)	BMove14(it);//ゆやや第一攻撃
		else if(p==15)	BMove15(it);//ゆやや第二攻撃
		else if(p==16)	BMove16(it);//ゆやや第三攻撃
		else if(p==17)	BMove17(it);//ゆやや第四攻撃
		else if(p==18)	BMove18(it);//神コンデンサー第一形態
		else if(p==19)	BMove19(it);//「妖蛾乱舞」準備
		else if(p==20)	BMove20(it);//「ヤンデレスカイハイ」準備
		else if(p==21)	BMove21(it);//神コンデンサー第二形態
		else if(p==22)	BMove22(it);//おかび第一攻撃
		else if(p==23)	BMove23(it);//おかび第二攻撃
		else if(p==24)	BMove24(it);//おかび第三攻撃
		else if(p==25)	BMove25(it);//おかび第四攻撃
	}
	else{
		if(p>=0 && p<=3)	SMove0(it);//秋符「秋の空とゴジラの心」
		else if(p>=4 && p<=7)	SMove1(it);//うんざんみたいな
		else if(p>=8 && p<=11)	SMove2(it);//核符「ゴジラvsモスラ　～ 村岡は逃げる」
		else if(p>=12 && p<=15)	SMove3(it);//弾符「マイクポップコーンは神」
		else if(p>=16 && p<=19)	SMove4(it);//野菜符「キャロットビーム」
		else if(p>=20 && p<=23)	SMove5(it);//気符「数学雲散霧消」
		else if(p>=24 && p<=27)	SMove6(it);//嫁符「早苗は俺の嫁」
		else if(p>=28 && p<=31)	SMove7(it);//「４９５年の煮込み」
		else if(p>=32 && p<=35)	SMove8(it);//光符「ステマニシューティングスター」
		else if(p>=36 && p<=39)	SMove9(it);//妖星「ゆや様は本当に頭の良い御方」
		else if(p>=40 && p<=43)	SMove10(it);//顔芸「ニュークリア・キモモ」
		else if(p>=44 && p<=47)	SMove11(it);//「走らさせていただいてます」
		else if(p>=48 && p<=51)	SMove12(it);//爆幻「ランドマインランド」
		else if(p==52)		SMove13(it);//「妖蛾乱舞」
		else if(p==54)		SMove15(it);//「ヤンデレスカイハイ」
	}
	
	if((*it).move_count>0){
		(*it).move_count--;
		(*it).x = (*it).to_x + (*it).mrate_x*pow((*it).move_count,2);
		(*it).y = (*it).to_y + (*it).mrate_y*pow((*it).move_count,2);
		if((*it).img==4)	(*it).angle += (*it).f_hanyou[7];
	}
	else{
		if((*it).bSpell==true && (p==52)){}
		else	(*it).angle = Atan2(1.0,0);
	}

	return;
}

void BTalkMove(list<BOSSDATA>::iterator &it){
	int p = (*it).img;
	int c = (*it).img_count;
	
	if(p==1){
		if(c==0)	BToMove(it, CENTER_X, 150, 120);
		else if(c==120)	NowNum++;
	}
	else if(p==4){
		if(c==0)	BToMove(it, CENTER_X, (*it).y, 120);
		else if(c==120)	NowNum++;
	}
	else if(p==5){
		if(c==0)	BToMove(it, CENTER_X, 150, 120);
		else if(c==120)	NowNum++;
	}
	
	if((*it).move_count>0){
		(*it).move_count--;
		(*it).x = (*it).to_x + (*it).mrate_x*pow((*it).move_count,2);
		(*it).y = (*it).to_y + (*it).mrate_y*pow((*it).move_count,2);
		if(p==4)	(*it).angle += (*it).f_hanyou[7];
	}
	else	(*it).angle = Atan2(1.0,0);

	return;
}

void BToMove(list<BOSSDATA>::iterator &it,float tox,float toy,int time){
	if((*it).x!=tox)	(*it).mrate_x = ((*it).x-tox) / (float)pow(time,2);
	else			(*it).mrate_x = 0;
	if((*it).y!=toy)	(*it).mrate_y = ((*it).y-toy) / (float)pow(time,2);
	else			(*it).mrate_y = 0;
	(*it).to_x = tox;
	(*it).to_y = toy;
	
	(*it).move_count = time;
	(*it).f_hanyou[7] = Radian(1800.0,TRUE)/(float)time;

	return;
}

void BMake(float x,float y,int img,int ship,ATACKDATA Patack[ATACK_NUMA][ATACK_NUMB]){
//カンスト8
	if(Boss.size()==8){
	
	}
	else{
		int level = Player[0].level;
		if(level==BABY)	level = EASY;
		else if(level==IMPOSSIBLE)	level = LUNATIC;
		else if(level==EXTRA)		level = LUNATIC+1;
		BOSSDATA P;
		P.x = x;
		P.y = y;
		P.to_x = x;
		P.to_y = y;
		P.large = 1.0;
		P.angle = Radian(90,TRUE);
		P.mrate_x = 0;
		P.mrate_y = 0;
		if(img==0){
			P.atari_num = 3;
			P.atari[0].x = 0;
			P.atari[0].y = 0;
			P.atari[0].large = 23;
			P.atari[1].x = 65;
			P.atari[1].y = 0;
			P.atari[1].large = 28;
			P.atari[2].x = -65;
			P.atari[2].y = 0;
			P.atari[2].large = 20;
			P.soten = 640;
		}
		else if(img==1){
			P.atari_num = 1;
			P.atari[0].x = 0;
			P.atari[0].y = 0;
			P.atari[0].large = 15;
			P.soten = 640;
		}
		else if(img==2){
			P.atari_num = 1;
			P.atari[0].x = 29;
			P.atari[0].y = -100;
			P.atari[0].large = 110;
			P.soten = 640;
		}
		else if(img==3){
			P.atari_num = 1;
			P.atari[0].x = 0;
			P.atari[0].y = 0;
			P.atari[0].large = 15;
			if(Player[0].stage==2)		P.soten = 640;
			else if(Player[0].stage==3)	P.soten = 1280;
		}
		else if(img==4){
			P.atari_num = 2;
			P.atari[0].x = 0;
			P.atari[0].y = 0;
			P.atari[0].large = 8;
			P.atari[1].x = 0;
			P.atari[1].y = -32;
			P.atari[1].large = 14;
			P.soten = 1280;
		}
		else if(img==5){
			P.atari_num = 1;
			P.atari[0].x = 8;
			P.atari[0].y = 10;
			P.atari[0].large = 20;
			P.soten = 5120;
		}
		P.soten *= (level+1)*0.5;
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				P.atack[i][j] = Patack[i][j];
			}
		}
		P.flash = 255;
		P.ship = ship;
		P.now_numA = 0;
		P.now_numB = 0;
		P.life = Patack[0][0].life;
		P.max_life = Patack[0][0].life;
		P.defence = Patack[0][0].defence;
		P.pattern = Patack[0][0].pattern;
		P.img = img;
		P.count = 0;
		P.img_count = 0;
		P.muteki_count = 0;
		P.death_count = 0;
		P.move_count = 0;
		P.bSpell = Patack[0][0].bSpell;
		P.bDamage = false;
		P.bDeath = false;
		P.bBlend = false;
		P.bAtari = true;
		P.bMuteki = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}

		Boss.push_back(P);
		if(Boss.size()==1){
			BossCount = Patack[0][0].count*60;
			BGcount = 0;
			BGcount2 = 0;
			BGcount3 = 0;
			SpBackCount = 0;
		}
	}
	
	return;
}

void BDrawGage(){
	list<BOSSDATA>::iterator it = Boss.begin();
	if(Boss.size()>0 && (*it).death_count==0){
		float plus = 0.5*pow(BGcount2-20,2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawArea(30, 10-plus, 30+7.0*BGcount3, 25-plus);
		list<BOSSDATA>::iterator it=Boss.begin();
		int all_life = 0;
		for(int i=0;i<ATACK_NUMB;i++){
			all_life += (*it).atack[(*it).now_numA][i].life*(float)(*it).atack[(*it).now_numA][i].defence/100.0;
		}
		int draw_life = 0;
		double rate = 350.0 / (double)all_life;
		for(int i=ATACK_NUMB-1;i>=(*it).now_numB;i--){
			int minus = (*it).atack[(*it).now_numA][i].life*(double)(*it).atack[(*it).now_numA][i].defence/100.0*rate;
			if(draw_life+minus>350)	minus = 350 - draw_life;
			SetDrawBright((*it).atack[(*it).now_numA][i].red, (*it).atack[(*it).now_numA][i].green, (*it).atack[(*it).now_numA][i].blue);
			if(GetSkip()){
				if(i!=(*it).now_numB)	DrawExtendGraph(30+draw_life, 10-plus, 30+draw_life+minus, 25-plus, gGage, TRUE);
				else			DrawExtendGraph(30+draw_life, 10-plus, 30+draw_life+(*it).life*(double)(*it).defence/100.0*rate, 25-plus, gGage, TRUE);
			}
			draw_life += minus;
		}
		SetDrawArea(0, 0, 640, 480);
		SetDrawBright(255,255,255);
		DrawBox(30, 10-plus, 380, 25-plus, GetColor(255,255,255), FALSE);

		if(BGcount<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*BGcount);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(GetSkip())	DrawGraph(30, 25-plus, gBossName[(*it).img], TRUE);

                SetDrawBright(255,10,10);
		for(int i=0;i<(*it).ship;i++){
			if(BGcount<20+15*i)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			else if(BGcount<20+15*i+30)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(BGcount-(20+15*i)));
			else				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(GetSkip())	DrawGraph(40+12*i, 38-plus, gSystem[5], TRUE);
		}
		
		if(bTalk==false)	BossCount--;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
		int num = draw_hit(0, 0, BossCount/60, 2);
		if(BGcount<120)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*BGcount);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
                SetDrawBright(255,255,255);
		if(BossCount/60>99)		draw_hit(430-18*2, 10, 99, 2);
		else if(BossCount/60>10)	draw_hit(430-18*num, 10, BossCount/60, 2);
		else				draw_hit(430-18*num, 10, BossCount/60, 3);
		if(BossCount%60==0){
			if(BossCount>0){
				if(BossCount/60<=6)		PlaySound(17);
				else if(BossCount/60<=11)	PlaySound(16);
			}
			if(BossCount==0)	(*it).life = 0;
		}

		if(Player[0].y<100){
			if(BGcount2>0)	BGcount2--;
		}
		else if(BGcount2<20)	BGcount2++;

		BGcount++;
		BGcount3++;
	}
	else{
		if(BGcount2<20)	BGcount2++;
	}
	SetDrawBright(255,255,255);

	return;
}

