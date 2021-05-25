#include "system.h"
#include "talk.h"
#include "boss.h"

TALKDATA Talk[CHARA_NUM][TALK_NUM];

bool bTalk;
int TalkNum;
int NowNum;//会話番号
int TalkCount;
int TalkCount2;
int TalkCount3;

void TLoad();
void TReset();
void TDraw();
void TMove(int chara, int i);
void TMake(int num);


void TLoad0(){
	int chara = 0;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "なんだか妙な所に迷い込んだみたいね…");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "超雑魚い戦闘機が飛んでたり、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "デカい割には弱い蛾が飛んでたり…");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//ゴジラ登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "アレは蛾じゃなくてモスラですよ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃじゃーん");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "人に挨拶するときはサングラスを外すものよ");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうたろう");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…まぁいいわ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ここは何処だか教えてくれないかしら");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ここですか？");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ここは物理室ですよ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "勝利に飢えた廃人どもが");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "爆弾を蹴りに集まる、名ばかりの部活です");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "それはそれは物騒な所ね");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…で、どうすれば幻想郷に帰れるのかしら？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "は？なにそれおいしいの");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・・・・");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 2;//ＢＧＭ開始
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "お前が誰かなんて興味ないし、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "とりあえず爆りましょう");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…弾幕勝負ね？それに勝てば教えてくれるのね");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "私を敵に回すとどうなるか、教えてあげるわ");
					}
				}
				else if(i==16){
					Talk[chara][num].flag[i] = 3;//絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうびいる");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "よーし、やるぞー！^^");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "どう？これが巫女の力よ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ただの怪獣では私を倒せないわ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうびいる");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "……まぁいいわ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "それより、この先どうすればいいのかしら？");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 11;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "は？そんなこと知りませんよ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "と言うか、アンタ誰？");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 11;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…ま、そりゃそうか");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕はそろそろ帰りますね");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "見たいアニメがあるんで^^");
					}
				}
				else if(i==7){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "え、ちょおま");
					}
				}
				else if(i==8 || i==9){
					if(i==8)	Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					if(i==9)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…はぁ。これからどうしたものか…");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 22;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さて");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "何の進展も無いまま三ヶ月");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "夏が終わって、秋になっちゃったけど…");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "何なのかしらねぇ、この世界");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "戦闘機、蛾の次はポップコーン？");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ついでにアホっぽいのもいたけど");
					}
				}
				else if(i==4){
					Talk[chara][num].flag[i] = 1;//蒸発登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "胃やあああああああああああああああ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "和漢ねええええええええええええええ");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・！？");
					}
				}
				else if(i==7){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕シューティング無理です");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "生後三ヶ月でも出来る様な難易度にしろ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "知らんがな");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "工工工ｴｴｴｴｴｴｪｪｪｪｪｪ(ﾟДﾟ)ｪｪｪｪｪｪｴｴｴｴｴｴ工工工");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…で、アンタも物理部の一員なの？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "帰ります");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…帰るな！");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…で、どうやったら");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "この世界から脱出できるのかしら？");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さっき言ったじゃん");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "僕には分かりませ円");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "このゲーム作ったの僕じゃないし");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "それもそうね");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "もう面倒だから");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "出てくる奴片っ端から倒していこう");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…あれ？これ僕が敵側なんですか");
					}
				}
				else if(i==19){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "わーい、今まで考えた技を披露できるぞー");
					}
				}
				else if(i==20){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・！？");
					}
				}
				else if(i==21){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "野菜のパワーで元気モリモリー！");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああういおふぃｒむふぃおれ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "視界を奪ったりレーザー強制したり");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "小賢しい事をしてくれたわね");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "でも、所詮貴方はその程度の力なのよ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "（　´_ゝ`）ﾌｰﾝ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さて、これからどうしましょうか");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "白根ーよ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "適当に頑張れば");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ただ、この先は弾消しも押し返しも");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "出来ないレーザーが出てきますので");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "割と注意してくださいね");
					}
				}
				else if(i==8 || i==9){
					if(i==9)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "（　´_ゝ`）ﾌｰﾝ");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 21;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うー寒っ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "この辺はだだっ広いだけで");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "何も無いのねぇ…");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…なんだかよく分からない");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "建物はあるけど");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//ゆや様登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "この辺じゃ久々の雪ですね");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "山に囲まれていて、滅多に");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "雪は降らないですから");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ん、やっとマトモな顔した奴が");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "来たわね");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あなたが最近物理部で噂の");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "コスプレイヤーですか");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "･･･うｎ？");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゴジラや蒸発がやられたと聞いて");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "あ、ついでにアホも");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "電車の写真を撮りに来た時に、あなたを");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "見つけたので話しかけてみたのです");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "なんだ、アンタも物理部の一員なのか");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃあ長々と話しても無駄ね");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "アンタも私のサンドバッグになりなさい");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…なかなかひどいこというなぁ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "物理部員にもマトモなのはいますよ");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕はニコ厨じゃないですし");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうたろう");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…まぁ、そろそろヒントも");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "欲しい頃でしょう");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゴジラがあなたを見かけてから");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "もう半年は経ってますしね");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "！何か知ってるの？");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "説明するのもめんどいんで");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "僕と将棋指すか鉄道を語るかどちらかで");
					}
				}
				else if(i==19){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…は？");
					}
				}
				else if(i==20){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "日本語でおｋ");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆ！ゆゆっゆゆゆっゆゆ！！！");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さあ、もう語るべきことは");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "全て語ったわ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さっさと知ってる事を吐きなさい");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆゆゆゆゆゆゆゆゆゆゆゆ！！！");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…雪に埋まってみる？");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はい、すみませんでした");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "どうやらあなたはこの世界の");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "人間じゃないようだ");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕たちはここに来て間もないので");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "よく分からないのですが");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "上級生の方々は、あなたについて");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "何か知っているようでした");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…つまり、アンタの先輩を");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "探せば良いのね？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そういうことになりますね");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…というか、アンタが案内");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "しなさいよ");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕は今からコーラスなんで");
					}
				}
				else if(i==14){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "え、ちょおま");
					}
				}
				else if(i==15 || i==16){
					if(i==15)	Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					if(i==16)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…なんでこんなにメンドイ奴");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ばっかりなのかしら…");
					}
				}
			}
		}
	}

	return;
}

void TLoad1(){
	int chara = 1;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 12;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ひこうきがいっぱいだー");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "きょうのおかずはこれにしよう");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//ゴジラ登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "お、蒸発だ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ペロペロ（＾ω＾）");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "たいへんきもちわるいです");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "すみませんでした");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…それのどこが謝ってるんだよ");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "では脱いでお詫びします");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "きもちわるいからやめろ");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発に振られたおっおっおっ");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(´；ω；`)");
					}
				}
				else if(i==11){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせえニンジンぶつけんぞ");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 5;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はいざまあああああ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうびいる");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "それもう秋田");
					}
				}
				else if(i==3 || i==4){
					if(i==4)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "効用の美しい亜季がやって参りました");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "この三ヶ月間はネトゲ三昧で");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "とても充実した毎日でした");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//蒸発登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "胃やあああああああああああああああ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "和漢ねええええええええええええええ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "奇遇ですね、私も和漢りません");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕シューティング無理です");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "生後三ヶ月でも出来る様な難易度にしろ");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そーだそーだ、クソビニロンめ");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "弾多すぎてきもいんですけど");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "奇遇ですね、私もそう思っていました");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "なんだか貴方とは分かり合えそうな気がします");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "嫌いな食べ物は何ですか？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "野菜です");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "奇遇ですね、私もです");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "一緒に野菜をぶっ潰す旅に出ましょう");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "それは明暗ですね");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "よーし、いくぞー＾＾");
					}
				}
				else if(i==16){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせーダイコンぶつけんぞ");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああういおふぃｒむふぃおれ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああいうういういういういうい");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "台詞が違います");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "やはり、私と貴方は分かり合えないようです");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "奇遇ですね、私もそう思っていました");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "負けたほうが去るのがマナーです");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "さようなら");
					}
				}
				else if(i==6 || i==7){
					if(i==7)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせー二度と来んじゃねーよ＾＾");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 16;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕の心の寒さに比べると");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "身体の寒さなんて大したこと無い");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ああ、ネトゲしたいなぁ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…この朱雀門イラつくわ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "燃やすか");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//ゆや様登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "この辺じゃ久々の雪ですね");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "こんにちは蒸発");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "これから毎日門を焼こうぜ？");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…？");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "何か知らんけど、最近お前来ないな");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕は野菜をぶっ潰す旅に出ました");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ほう");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あと、早苗さんを探しに行きます");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(…駄目だコイツ、早く何とかしないと)");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "電車とか興味ない？");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "俺は今、電車の写真を撮ってるんだ");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "キミも一緒に行こうよ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ネネ、良いだろう？");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ぼくはこちやさなえがすきです");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==15){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "お前うぜーハクサイぶつけんぞ");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 11;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆ！ゆゆっゆゆゆっゆゆ！！！");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ざ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ま");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "..");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], ".....");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "...");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "..");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "グループ会話荒らすな");
					}
				}
				else if(i==9 || i==10){
					if(i==10)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ぼくはさなえさんとけっこんする");
					}
				}
			}
		}
	}

	return;
}

void TLoad2(){
	int chara = 2;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 12;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うーん、そろそろ遊びはやめて");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ゴジラ探すか");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "なんか分からない問題があるんだよな");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "アイツどこにいるんだろ？");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//ゴジラ登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "調子に乗っちゃダメー");
					}
				}
				else if(i==3){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃじゃーん");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "おお、見つけた");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あのさ、4STEPの49番やねんけど…");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あー、今ちょっと忙しいわ");
						else if(j==0)	sprintf(Talk[chara][num].speak[i][j], "待っといてくれへんか");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(さっきまで怪獣みたいな声で");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], " 熱唱してたのに)");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ところで、蒸発見ーへんかった？");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発？知らんなぁ");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "（　´_ゝ`）ﾌｰﾝ");
					}
				}
				else if(i==11){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発以外に用はねーよ！！！");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 6;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "バンバン！カチャカチャ！！");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "(キーボードをクラッシュする音)");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "で、49番やねんけど…");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発ぅぅぅぅぅぅ！！！");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "え、ちょおま");
					}
				}
				else if(i==4 || i==5){
					if(i==4)	Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					if(i==5)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "アイツ何があったんだろ・・・");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 16;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "この辺は紅葉が綺麗だな");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "それにしても、ゴジラは何処へ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "行ったんだろう？");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//蒸発登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "胃やあああああああああああああああ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "和漢ねええええええええええええええ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "俺もお前が分からん");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせええええええうぇろｊりおうる");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "くぁｗせｄｒｆｔｇｙふじこｌｐ；＠：");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あのさ、ゴジラ何処に行ったか知らな…");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "pおｂんるいんびおぷにんｐｄｐｎ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "歩青あえおっぱおおおあおぽおっぱい");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(ああ、話にならないな・・・");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], " めんどくせぇ・・・)");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(まぁ、教えてもらうなら誰も良いか)");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発、4STEPの49番分かる？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "は？ふぉーすてっぷ？");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "トイレットペーパーにしました＾＾");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・。");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃあさ、問題見せるから・・・");
					}
				}
				else if(i==15){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせー、ピーマン投げつけんぞ");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああういおふぃｒむふぃおれ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "俺が勝ったから、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "問題見てくれるよな？");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あ、ごめん");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "野菜を潰す旅の途中だから＾＾");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・は？");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃ、そーいうことで");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "帰ります＾＾");
					}
				}
				else if(i==5){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "え、ちょおま");
					}
				}
				else if(i==6 || i==7){
					if(i==6)	Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					if(i==7)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(…何なんだアイツ)");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 21;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "冬になってもゴジラに会えてないとか");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "しかもまだ解けないし");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "49番難しすぎないか・・・");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…何気にこの景色もいいな");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//ゆや様登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "πじゃないか");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "どーしたん、こんな所で");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あ、ゆやや");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ゴジラ見ーへんかった？");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゴジラなら、ついさっき蒸発を");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "追っていった");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゑ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発は早苗さんを探しにいった");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "野菜を潰す旅に出たんじゃ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "なかったっけ？");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そんなことも言ってた気がする");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃあゆやや、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "4STEPの49番分かる？");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "どれどれ、ちょっと見てみよう");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・。");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・・・・。");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・・・・。");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "よし、「電車でＤ」やるか");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いいねー");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あ、やっぱステマニにしようかな");
					}
				}
				else if(i==19){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(また廃プレイが始まるよ)");
					}
				}
				else if(i==20){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "昔からダンおにやってて");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "慣れてるから(ﾄﾞﾔ");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 11;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆ！ゆゆっゆゆゆっゆゆ！！！");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ステマニ、ミスったか");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いや、矢印揺れる設定になってただけだし");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(心底どーでもいい)");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃあ俺はもう行くわ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "えー、ついでやから");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ここでアーバンライナー撮って行かへん？");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ここからのアングルは");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "最高やで！");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃ、そういうことで");
					}
				}
				else if(i==8){
					Talk[chara][num].flag[i] = 5;//プレイヤーが引っ込む
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "え、ちょおま");
					}
				}
				else if(i==9 || i==10){
					if(i==9)	Talk[chara][num].flag[i] = 5;//プレイヤーが引っ込む
					if(i==10)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…うーん、どうしてこの魅力を");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "誰も理解してくれないのだろう…");
					}
				}
			}
		}
	}

	return;
}

void TLoad3(){
	int chara = 3;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].flag[i] = 1;//ゴジラ登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = -1;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…！？");
					}
				}
				else if(i==2){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…！？");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 12;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "なんだ鏡か");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "物理室にこんなに大きな鏡が");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "あったとは");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうたろう");
					}
				}
				else if(i==9){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 12;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…！？");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 5;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "俺の偽者ざまあああああああ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "所詮はただのミラー(ｷﾘｯ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうびいる");
					}
				}
				else if(i==3 || i==4){
					if(i==4)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(ｷﾘｯ");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 14;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "良い景色だなー");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "爆幻で荒んでいた心が癒される");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//蒸発登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "胃やあああああああああああああああ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "和漢ねええええええええええええええ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あ、蒸発じゃん");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "勉強なら教えるけど");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせええええええええええええええ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "勉強なんてトイレに流してきたわボケ");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 12;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゑ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "言う尾pk、おｊヴぇｔｇｒｊぷいおｐみえ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ｋｊかうｋらｔｒばろあｐｗｒぽしｎ");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そいうふふぃえあｊふぃえおｐｊｆ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "やさいやいしああしゃしゃしゃやさいやさい");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "日本語でおｋ");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さようなら");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "帰るのか");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせー、じゃがいも投げつけんぞ");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 4;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああういおふぃｒむふぃおれ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発ペロペロペロペロペロペロペロ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ペロペロペロペロペロペロペロペロ");
					}
				}
				else if(i==2 || i==3){
					if(i==3)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "たーすーけーてー");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 15;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "雪降ってきた");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "この格好では死ぬ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "だが蒸発を見つけるまでは（＾ω＾）");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…平城旧跡にあるコレ、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "なんだっけ");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//ゆや様登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あ、ゴジラだ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そんな寒い格好で何してんすか");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あー、ゆやや、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "蒸発見ーへんかった？");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "帰った");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゑ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "全国に散らばる野菜を");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ぶっ潰す旅に出るそうです");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "イミフ");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "俺もよー分からん");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…まさか、蒸発を追ってここまで？");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 8;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 8;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==14){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 8;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "もうやだこのぶかつ");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 9;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "おらさ東京さ行くだ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうたろう");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "寒いし、もうそろそろ帰るかな");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そうすれば");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==7 || i==8){
					if(i==8)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "（なにこのくうき）");
					}
				}
			}
		}
	}

	return;
}

void TLoad4(){
	int chara = 4;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 12;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ふぅん、まずまずの道中だな");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ま、妖々夢よりは簡単かな");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//ゴジラ登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "かまってほしいのー");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ペロペロ（＾ω＾）");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "今日もうるせーな、おまえ");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "んでんでんでｗｗｗｗｗｗｗ");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "んで、何視点の");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "蒸発探してる。");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "どっかで見ーへんかった？");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いや、見てないけど");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "なんか用事でもあるｎ？");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ペロペロする（＾ω＾）");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…ゑ");
					}
				}
				else if(i==11){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "よーし、やるぞー＾＾");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はぁぁぁぁぁぁ～～～！！？？");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ま、妖々夢やってたしＳＴＧは");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "それなりに慣れてる(ﾄﾞﾔﾔ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうびいる");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…うｎ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "よーし、蒸発探しにいくお（＾ω＾）");
					}
				}
				else if(i==5){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あっ、ちょっと…");
					}
				}
				else if(i==6 || i==7){
					if(i==6)	Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					if(i==7)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…うーん、これは濃厚なガチホモの臭い…");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 14;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "もみじもみもみ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…は、どうでもいい。");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "俺に必要なのは電車だ。電車。");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//蒸発登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "胃やあああああああああああああああ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "和漢ねええええええええええええええ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "お、蒸発じゃないか");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…ん？");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "電車○きももｗｗｗｗｗｗｗｗｗｗｗｗｗ");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "きももみだにうっどまｍどうぇっうぇｗｗ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "あすだおわおおｃさなえはおれのよめｓｄｆ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…とんでもない所に来てしまったようだ");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "これから毎日野菜を焼こうぜ？");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "お前どんだけ野菜好きなんだよ");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いや、嫌いです");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゑ？");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "でも野菜の歌は・・・");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うるせー、小松菜でビンタすんぞ");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 9;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああういおふぃｒむふぃおれ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "やっぱりＢＧＭ野菜じゃん");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ホントは野菜好きなんじゃね？");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うっせーな、パプリカ投げつけんぞ");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "今おれは全国の野菜をぶっ潰す旅に");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "出てるんだあぁあぁｓだｓｄさああｓ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・？");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あとゴジラきめええええええええから");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "逃げるっ！退陣！");
					}
				}
				else if(i==6){
					Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ、ばいばい");
					}
				}
				else if(i==7 || i==8){
					if(i==7)	Talk[chara][num].flag[i] = 6;//エネミーが引っ込む
					if(i==8)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…ゴジラよ、お前は何処へ行く…");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 14;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "電車ハァハァ(*´Д`)");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "眼福眼福～。");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "あのフォームの美しさに魅かれるぜ…");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "だから、こんな大雪の日に");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "写真を撮りにきたのも後悔してない");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//ゆや様登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "おや、この辺じゃ珍しいな");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "僕と同族の方ですか・・・！？");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・！？");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・！？");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…なんか、俺にそっくりやねんけど…");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ですね");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "もしかして…６年前に");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "生き別れた兄さん・・・！？");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "まさか・・・お前は俺の弟！？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "兄さん！！！！！");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "弟よ！！！！");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "将棋でも指しましょうか");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆ！ゆゆっゆゆゆっゆゆ！！！");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "兄さん、今の将棋やない");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "スペルカードや");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "でっていう");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…ってか、生き別れた弟なんて、いたか？");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…そういえば、俺にもそんな兄なんて…");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・では、そういうことで。");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "さようなら");
					}
				}
				else if(i==8 || i==9){
					if(i==9)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
			}
		}
	}

	return;
}

void TLoad5(){
	int chara = 5;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 16;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いやー相変わらずマジキチ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "モスラ出てくるとか鬱やわ");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//ゴジラ登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あらま～、あらま～");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あらま～～～～");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うっぜーーー");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうたろう");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ハァ。それしか言えへんのか");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "マジ残念やな");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はいあそたああああ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "(ｲﾗｲﾗｲﾗｲﾗｲﾗ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ま、とりあえず爆ろっかー");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "よーしやるぞー＾＾");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はい死亡フラグー");
					}
				}
				else if(i==12){
					Talk[chara][num].flag[i] = 2;//ＢＧＭ開始
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "では、僕はいつも通り妖夢ちゃん");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "使いますね＾＾");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "だからマイキャラやめろよー");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…まぁ良いか。どうせ弱いしなー(笑う");
					}
				}
				else if(i==15){
					Talk[chara][num].flag[i] = 3;//絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "くぁｗせｄｒｆｔｇｙふじこｌｐ；＠：");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ﾌﾟｰｸｽｸｽ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "弱えーー。凶キャラ使って0勝とか(笑う");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそうびいるうるるうるうう");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…ま、俺はちょっと帰るけど、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "お前ここにおっとけよ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "は？");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "もうすぐお客さんが来るから、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "適当に相手しといてくだちゃいね～");
					}
				}
				else if(i==6 || i==7){
					if(i==7)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "（　´_ゝ`）ﾌｰﾝ");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 18;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いやー絶景ですなー");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "こんだけ落ち葉が舞ってると、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "火をつけてみたくなる");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "どんだけ燃え広がるやろーなー(暗黒微笑");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "アホはまだ山の中にいるやろーしなー");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "プークスクス");
					}
				}
				else if(i==4){
					Talk[chara][num].flag[i] = 1;//蒸発登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "胃やあああああああああああああああ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "和漢ねええええええええええええええ");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "イエス！");
					}
				}
				else if(i==7){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "高須、");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "クーリニック！");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "だああもうおうだおしうｄｈのあ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "工工工ｴｴｴｴｴｴｪｪｪｪｪｪ(ﾟДﾟ)ｪｪｪｪｪｪｴｴｴｴｴｴ工工工");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "日本語でおけ");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "帰ります");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそた");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ちょーっとキミマジキチですねー");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ハイそうですけどなにか＾＾");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "もうめんどいわ");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゑ");
					}
				}
				else if(i==17){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うぜーからカボチャ投げつけんぞ(笑う");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あああああういおふぃｒむふぃおれ");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ざ");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "まーーー");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "で、俺の前に誰かに会った？");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ、物理部員数名と");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あそたーー");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はああああ！！？・おまｗイミフあｓｄ");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "まーまー、そう怒らないで～");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "牛乳飲んでカリウム摂取しなさい（笑う");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "イライラ抑えるのはカルシウムです");
					}
				}
				else if(i==8 || i==9){
					if(i==9)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "調子に乗っちゃダメーーーー");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 20;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・・・・");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…僕ドラえもんでーす");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//ゆや様登場、スキップ不可
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "日本語でおｋ");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(ﾄﾞﾔﾔｯ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "そのドヤ顔やめろよ～");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…仕方ないじゃないですか");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "顔は生まれ付いてのものですから");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ﾌﾟｰｸｽｸｽ");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…あー、キーボード何処に置いたかなー");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "キーボードクラッシュすんな(藁藁");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "うｎ");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "でさー、物理室に来客あったー？");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いえ、僕今日は物理室行ってませんし");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "いやー、なんでもゴジラと蒸発に");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "爆幻で圧勝した奴がいるとか");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "あいつらはただの雑魚やけどな(笑う");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ほう、あの廃人集団の中で");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "どんな奴だったのですか？");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "さーねー、知ってるけどめんどい");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "はい？");
					}
				}
				else if(i==19){
					Talk[chara][num].flag[i] = 7;//ＢＧＭ開始 兼 絵が引っ込む
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "まずは爆ろうぜ？");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆ！ゆゆっゆゆゆっゆゆ！！！");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆややは漁夫だけやからなー(藁");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "基本的にへたっぴ(藁藁");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆゆゆゆゆゆゆゆゆゆゆゆ！！！");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゆやや壊れたﾌﾟｰｸｽｸｽ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "・・・んで、");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "んでんでんでｗｗｗｗｗｗ");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "違う！誰なんですか、");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "ゴジラと蒸発に勝ったのは");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ああ、アレね");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "まー、ここで待ってたら会えるわ");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "紅白のめでたい色した人");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "紅白？");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "適当に話し進めといて");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "後はまー上手く行くやろうし");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…どういうことなんですか？");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "じゃあフランちゃんに告白してくる(笑う");
					}
				}
				else if(i==14){
					Talk[chara][num].flag[i] = 5;//プレイヤーが引っ込む
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "ゑ、ちょおま");
					}
				}
				else if(i==15 || i==16){
					if(i==15)	Talk[chara][num].flag[i] = 5;//プレイヤーが引っ込む
					if(i==16)	Talk[chara][num].flag[i] = 4;//ステージクリア
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "…うーん、相変わらず掴めない人だな");
					}
				}
			}
		}
	}

	return;
}

void TLoad(){
	bTalk = false;
	TalkNum = 0;
	NowNum = 0;
	TalkCount = 0;
	TalkCount2 = 0;
	TalkCount3 = 0;
	for(int k=0;k<CHARA_NUM;k++){
		for(int i=0;i<TALK_NUM;i++){
			Talk[k][i].talk_num = 0;
			Talk[k][i].Nimg = -1;
			Talk[k][i].Ncount = 0;
			for(int j=0;j<MAX_TALK;j++){
				Talk[k][i].flag[j] = 0;
				Talk[k][i].bName[j] = false;
				for(int a=0;a<MAX_LINE;a++){
					Talk[k][i].speak_color[j][a] = 0;
					for(int b=0;b<MAX_CHAR;b++){
						Talk[k][i].speak[j][a][b] = '\0';
					}
				}
				for(int a=0;a<MAX_PLAYER;a++){
					Talk[k][i].Pimg[j][a] = -1;
					Talk[k][i].Pimg_count[a] = 0;
					Talk[k][i].Pactive[j][a] = 0;
					Talk[k][i].Pactive_count[a] = 0;
				}
				for(int a=0;a<MAX_ENEMY;a++){
					Talk[k][i].Eimg[j][a] = -1;
					Talk[k][i].Eimg_count[a] = 0;
					Talk[k][i].Eactive[j][a] = 0;
					Talk[k][i].Eactive_count[a] = 0;
				}
			}
		}
	}

	for(int chara=0;chara<CHARA_NUM;chara++){
		if(chara==0)		TLoad0();
		else if(chara==1)	TLoad1();
		else if(chara==2)	TLoad2();
		else if(chara==3)	TLoad3();
		else if(chara==4)	TLoad4();
		else if(chara==5)	TLoad5();
	}

	return;
}

void TReset(){
	bTalk = false;
	TalkNum = 0;
	NowNum = 0;
	TalkCount = 0;
	TalkCount2 = 0;
	TalkCount3 = 0;

	return;
}

void TDraw(){
	if(bTalk==true){
		TMove(Player[0].chara,TalkNum);
		if(NowNum>=Talk[Player[0].chara][TalkNum].talk_num){
			bTalk = false;
			return;
		}

		for(int i=0;i<MAX_PLAYER;i++){
			if(Talk[Player[0].chara][TalkNum].Pimg[NowNum][i]!=-1){
				if(Talk[Player[0].chara][TalkNum].Pimg_count[i]<40)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*Talk[Player[0].chara][TalkNum].Pimg_count[i]);
				else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int bright = 255-4*(40-Talk[Player[0].chara][TalkNum].Pactive_count[i]);
				SetDrawBright(bright, bright, bright);
				int sx,sy;
				GetGraphSize(gCatin[Talk[Player[0].chara][TalkNum].Pimg[NowNum][i]], &sx, &sy);
				float x = 40+sx/2 - 0.03*pow(Talk[Player[0].chara][TalkNum].Pactive_count[i]-40,2);
				if(TalkCount3>0)	x -= TalkCount3*(sx+30)/120;
				float y = 552-sy/2 + 0.2*pow(Talk[Player[0].chara][TalkNum].Pimg_count[i]-40,2);
				if(GetSkip())	DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Talk[Player[0].chara][TalkNum].Pimg[NowNum][i]], TRUE, FALSE);
			}
		}
		for(int i=0;i<MAX_ENEMY;i++){
			if(Talk[Player[0].chara][TalkNum].Eimg[NowNum][i]!=-1){
				if(Talk[Player[0].chara][TalkNum].Eimg_count[i]<40)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*Talk[Player[0].chara][TalkNum].Eimg_count[i]);
				else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int bright = 255-4*(40-Talk[Player[0].chara][TalkNum].Eactive_count[i]);
				SetDrawBright(bright, bright, bright);
				int sx,sy;
				GetGraphSize(gCatin[Talk[Player[0].chara][TalkNum].Eimg[NowNum][i]], &sx, &sy);
				float x = 400-sx/2 + 0.03*pow(Talk[Player[0].chara][TalkNum].Eactive_count[i]-40,2);
				if(TalkCount3>0)	x += TalkCount3*(sx+30)/120;
				float y = 552-sy/2 + 0.2*pow(Talk[Player[0].chara][TalkNum].Eimg_count[i]-40,2);
				if(GetSkip())	DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Talk[Player[0].chara][TalkNum].Eimg[NowNum][i]], TRUE, FALSE);
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawBright(10,10,10);
		if(GetSkip()){
			if(TalkCount<50)	DrawExtendGraph(30, 400, 410, 400+1.2*TalkCount, gGage, TRUE);
			else			DrawExtendGraph(30, 400, 410, 460, gGage, TRUE);
		}
		SetDrawBright(255,255,255);
		if(TalkCount2<10)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,25.5*TalkCount2);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<2;i++){
			int color;
			if(Talk[Player[0].chara][TalkNum].speak_color[NowNum][i]==0)		color = GetColor(255,150,150);
			else if(Talk[Player[0].chara][TalkNum].speak_color[NowNum][i]==1)	color = GetColor(150,150,255);
			DrawSt(40, 410+20*i, GetColor(255,255,255), color, talk_font, Talk[Player[0].chara][TalkNum].speak[NowNum][i]);
		}
		
		if(Talk[Player[0].chara][TalkNum].Ncount>0){
			if(Talk[Player[0].chara][TalkNum].Ncount<40)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*Talk[Player[0].chara][TalkNum].Ncount);
			else if(Talk[Player[0].chara][TalkNum].Ncount<160)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			else if(Talk[Player[0].chara][TalkNum].Ncount<200)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*(200-Talk[Player[0].chara][TalkNum].Ncount));
			else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			int sx,sy;
			GetGraphSize(gCatin[Talk[Player[0].chara][TalkNum].Nimg], &sx, &sy);
			if(GetSkip())	DrawRotaGraphF(400-sx/2+shake_x, 380-sy/2+shake_y, 1.0, 0, gCatin[Talk[Player[0].chara][TalkNum].Nimg], TRUE, FALSE);
			Talk[Player[0].chara][TalkNum].Ncount++;
		}
		
		TalkCount++;
		if(TalkCount>=50)	TalkCount2++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void TMove(int chara, int i){
	if(TalkCount2>0){
		for(int j=0;j<MAX_PLAYER;j++){
			if(Talk[chara][i].Pimg[NowNum][j]!=-1){
				if(j==0 && Talk[chara][i].flag[NowNum]==5){
					if(Talk[chara][i].Pimg_count[j]>0)	Talk[chara][i].Pimg_count[j]--;//プレイヤーが引っ込む
				}
				else if(Talk[chara][i].Pimg_count[j]<40)	Talk[chara][i].Pimg_count[j]++;
				if(Talk[chara][i].Pactive[NowNum][j]==1){
					if(Talk[chara][i].Pactive_count[j]<40)	Talk[chara][i].Pactive_count[j]++;
				}
				else if(Talk[chara][i].Pactive[NowNum][j]==0){
					if(Talk[chara][i].Pactive_count[j]>0)	Talk[chara][i].Pactive_count[j]--;
				}
			}
                }
		for(int j=0;j<MAX_ENEMY;j++){
			if(Talk[chara][i].Eimg[NowNum][j]!=-1){
				if(j==0 && Talk[chara][i].flag[NowNum]==6){
					if(Talk[chara][i].Eimg_count[j]>0)	Talk[chara][i].Eimg_count[j]--;//敵が引っ込む
				}
				else if(Talk[chara][i].Eimg_count[j]<40)	Talk[chara][i].Eimg_count[j]++;
				if(Talk[chara][i].Eactive[NowNum][j]==1){
					if(Talk[chara][i].Eactive_count[j]<40)	Talk[chara][i].Eactive_count[j]++;
				}
				else if(Talk[chara][i].Eactive[NowNum][j]==0){
					if(Talk[chara][i].Eactive_count[j]>0)	Talk[chara][i].Eactive_count[j]--;
				}
			}
                }
		
		
		if(Talk[chara][i].flag[NowNum]==3 || Talk[chara][i].flag[NowNum]==7){
			if(TalkCount3==120){
				NowNum++;
				TalkCount2 = -1;
			}
			TalkCount3++;
		}
		if(TalkCount2==1){
			if(Talk[chara][i].bName[NowNum]==true)	Talk[chara][i].Ncount = 1;
			if(i==0){
				if(Talk[chara][i].flag[NowNum]==1){
					BMake(-100, 150, 1, 2, atack); 
				}
				else if(Talk[chara][i].flag[NowNum]==2 || Talk[chara][i].flag[NowNum]==7){
					MuPlayBgm(3);
				}
			}
			else if(i==2){
				if(Talk[chara][i].flag[NowNum]==1){
					BMake(530, 180, 4, 3, atack); 
				}
				else if(Talk[chara][i].flag[NowNum]==2 || Talk[chara][i].flag[NowNum]==7){
					MuPlayBgm(5);
				}
			}
			else if(i==4){
				if(Talk[chara][i].flag[NowNum]==1){
					BMake(-100, CENTER_Y, 5, 4, atack); 
				}
				else if(Talk[chara][i].flag[NowNum]==2 || Talk[chara][i].flag[NowNum]==7){
					MuPlayBgm(7);
				}
			}
		}

		int up,down,left,right,shot,bomb,slow,skip,pause;
		if(replay_play==false)	GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
		else			RMain(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause,false);
		if(Talk[chara][i].flag[NowNum]!=1 && Talk[chara][i].flag[NowNum]!=3 && Talk[chara][i].flag[NowNum]!=7 && Talk[chara][i].flag[NowNum]!=4 && TalkCount2>5){
			if(shot==1 || skip>0 || TalkCount2==360){
				NowNum++;
				TalkCount2 = -1;
			}
		}

		if(Talk[chara][i].flag[NowNum]==4){
			//ステージクリア
			Ccount = 1;
			TalkCount2 = 10;
		}
	}
	
	return;
}

void TMake(int num){
	SESDelete(3);
	bTalk = true;
	TalkNum = num;
	NowNum = 0;
	TalkCount = 0;
	TalkCount2 = 0;
	TalkCount3 = 0;
	for(int i=0;i<MAX_PLAYER;i++){
		Talk[Player[0].chara][num].Pimg_count[i] = 0;
		Talk[Player[0].chara][num].Pactive_count[i] = 0;
	}
	for(int i=0;i<MAX_ENEMY;i++){
		Talk[Player[0].chara][num].Eimg_count[i] = 0;
		Talk[Player[0].chara][num].Eactive_count[i] = 0;
	}
	Talk[Player[0].chara][num].Ncount = 0;
		
	return;
}