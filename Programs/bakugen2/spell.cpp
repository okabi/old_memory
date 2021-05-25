#include "spell.h"
#include "map.h"
#include "player.h"
#include "bomb.h"
#include "stg.h"
#include "item.h"
#include "menu.h"
#include "net.h"


list<SPELLDATA> Spell;

void SpLoad();
void SpMake(float x,float y,int type,int player,int level, bool special);
void SpDraw();
void SpMove(list<SPELLDATA>::iterator &it);
int SpAtari(list<SPELLDATA>::iterator &it,bool bDeath);

void SpLoad(){
	Spell.clear();

	return;
}

void SpMake(float x,float y,int type,int player,int level,bool special){
	SPELLDATA P;
	P.x = x;
	P.y = y;
	P.angle = 0;
	P.spark_angle = 0;
	P.large = 1.0;
	P.haba = 0;
	switch(type){
		case 0: //マスタースパーク
			P.img = gSpell[0];
			break;
		case 7: //アサシンスパーク
			P.img = gSpell[0];
			break;
		case 8: //ファイナルスパーク
			P.img = gSpell[0];
			break;
		case 16: //妖童餓鬼の断食
			P.img = gSpell[1];
			break;
		case 17: //二百由旬の一閃
			P.img = gSpell[1];
			break;
		case 18: //業風神閃斬
			P.img = gSpell[1];
			break;
		case 29: //のびーるアーム
			P.img = gSpell[1];
			break;
	}
	P.type = type;
	P.level = level;
	P.count = 0;
	P.player = player;
	P.flash = 255;
	P.bDelete = false;
	for(int i=0;i<8;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	wsprintf(Player[player].special,"\0");
	if(special==true){
		switch(type){
			case 0:
				wsprintf(Player[player].special, "「マスタースパーク」");
				break;
			case 1:
				wsprintf(Player[player].special, "「ジャック・ザ・リッパー」");
				break;
			case 2:
				wsprintf(Player[player].special, "「全世界ナイトメア」");
				break;
			case 3:
				wsprintf(Player[player].special, "「そして誰もいなくなるか？」");
				break;
			case 4:
				wsprintf(Player[player].special, "「夢想封印」");
				break;
			case 5:
				wsprintf(Player[player].special, "「夢想封印・散」");
				break;
			case 6:
				wsprintf(Player[player].special, "「夢想封印・滅」");
				break;
			case 7:
				wsprintf(Player[player].special, "「アサシンスパーク」");
				break;
			case 9:
				wsprintf(Player[player].special, "「ファイナルスパーク」");
				break;
			case 10:
				wsprintf(Player[player].special, "「ジャック・ザ・ルドビレ」");
				break;
			case 11:
				wsprintf(Player[player].special, "「殺人ドール」");
				break;
			case 12:
				wsprintf(Player[player].special, "「ミッドナイトディザスター」");
				break;
			case 13:
				wsprintf(Player[player].special, "「レミリアストーカー」");
				break;
			case 14:
				wsprintf(Player[player].special, "「そして誰も彼も死ぬがよい」");
				break;
			case 15:
				wsprintf(Player[player].special, "「４９５年の波紋」");
				break;
			case 16:
				wsprintf(Player[player].special, "「妖童餓鬼の断食」");
				break;
			case 17:
				wsprintf(Player[player].special, "「二百由旬の一閃」");
				break;
			case 18:
				wsprintf(Player[player].special, "「業風神閃斬」");
				break;
			case 19:
				wsprintf(Player[player].special, "「亡我郷」");
				break;
			case 20:
				wsprintf(Player[player].special, "「完全なる墨染の桜」");
				break;
			case 21:
				wsprintf(Player[player].special, "「反魂蝶」");
				break;
			case 22:
				wsprintf(Player[player].special, "「動と静の均衡」");
				break;
			case 23:
				wsprintf(Player[player].special, "「夢と現の境界」");
				break;
			case 24:
				wsprintf(Player[player].special, "「メビウスの表裏」");
				break;
			case 25:
				wsprintf(Player[player].special, "「幻想催眠（インビシブルウォール）」");
				break;
			case 26:
				wsprintf(Player[player].special, "「幻影の壁（イリュージョンウォール）」");
				break;
			case 27:
				wsprintf(Player[player].special, "「月兎爆誕（ルナファントム）」");
				break;
			case 28:
				wsprintf(Player[player].special, "「オプティカルカモフラージュ」");
				break;
			case 29:
				wsprintf(Player[player].special, "「のびーるアーム」");
				break;
			case 30:
				wsprintf(Player[player].special, "「スピン・ザ・ボンバー」");
				break;
			case 31:
				wsprintf(Player[player].special, "「天の恵み」");
				break;
			case 32:
				wsprintf(Player[player].special, "「サモンタケミナカタ」");
				break;
			case 33:
				wsprintf(Player[player].special, "「ミラクルフルーツ」");
				break;
			case 34:
				wsprintf(Player[player].special, "「重水素融合」");
				break;
			case 35:
				wsprintf(Player[player].special, "「ギガフレア」");
				break;
			case 36:
				wsprintf(Player[player].special, "「アトミックボム」");
				break;
		}
	}
	
	Spell.push_back(P);

	return;
}

void SpDraw(){
	for(list<SPELLDATA>::iterator it=Spell.begin(); it!=Spell.end(); ++it){
		SpMove(it);
		if((*it).bDelete==true){
			it = Spell.erase(it);
			it--;
			continue;						
		}
		if((*it).type==0||(*it).type==7||(*it).type==8||(*it).type==9){
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			if(repeat==9)	DrawModiGraph((*it).f_hanyou[0]+shake_x,(*it).f_hanyou[1]+shake_y,(*it).f_hanyou[2]+shake_x,(*it).f_hanyou[3]+shake_y,(*it).f_hanyou[4]+shake_x,(*it).f_hanyou[5]+shake_y,(*it).f_hanyou[6]+shake_x,(*it).f_hanyou[7]+shake_y,(*it).img,TRUE);
		}
		else if((*it).type==16||(*it).type==17||(*it).type==18){
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			if(repeat==9){
				for(int i=0;i<3;i++){
					if((*it).i_hanyou[0]==0)	DrawModiGraph((*it).f_hanyou[0]-(*it).f_hanyou[2]+shake_x,(*it).f_hanyou[1]+shake_y,(*it).f_hanyou[0]+(*it).f_hanyou[2]+shake_x,(*it).f_hanyou[1]+shake_y,(*it).x+(*it).f_hanyou[2]+shake_x,(*it).y+shake_y,(*it).x-(*it).f_hanyou[2]+shake_x,(*it).y+shake_y,(*it).img,TRUE);
					if((*it).i_hanyou[0]==1)	DrawModiGraph((*it).f_hanyou[0]+shake_x,(*it).f_hanyou[1]-(*it).f_hanyou[2]+shake_y,(*it).f_hanyou[0]+shake_x,(*it).f_hanyou[1]+(*it).f_hanyou[2]+shake_y,(*it).x+shake_x,(*it).y+(*it).f_hanyou[2]+shake_y,(*it).x+shake_x,(*it).y-(*it).f_hanyou[2]+shake_y,(*it).img,TRUE);
					if((*it).i_hanyou[0]==2)	DrawModiGraph((*it).f_hanyou[0]+(*it).f_hanyou[2]+shake_x,(*it).f_hanyou[1]+shake_y,(*it).f_hanyou[0]-(*it).f_hanyou[2]+shake_x,(*it).f_hanyou[1]+shake_y,(*it).x-(*it).f_hanyou[2]+shake_x,(*it).y+shake_y,(*it).x+(*it).f_hanyou[2]+shake_x,(*it).y+shake_y,(*it).img,TRUE);
					if((*it).i_hanyou[0]==3)	DrawModiGraph((*it).f_hanyou[0]+shake_x,(*it).f_hanyou[1]+(*it).f_hanyou[2]+shake_y,(*it).f_hanyou[0]+shake_x,(*it).f_hanyou[1]-(*it).f_hanyou[2]+shake_y,(*it).x+shake_x,(*it).y-(*it).f_hanyou[2]+shake_y,(*it).x+shake_x,(*it).y+(*it).f_hanyou[2]+shake_y,(*it).img,TRUE);
				}
			}
		}
		else if((*it).type==29){
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			SetDrawBright(0,255,255);
			if(repeat==9){
				float haba = 10.0;
				DrawExtendGraph((*it).x-(*it).f_hanyou[0]+shake_x, (*it).y-haba+shake_y, (*it).x+(*it).f_hanyou[1]+shake_x, (*it).y+haba+shake_y, (*it).img, TRUE);
				DrawExtendGraph((*it).x-haba+shake_x, (*it).y-(*it).f_hanyou[2]+shake_y, (*it).x+haba+shake_x, (*it).y+(*it).f_hanyou[3]+shake_y, (*it).img, TRUE);
			}
		}
		else if((*it).type==35||(*it).type==36){
			if(repeat==9){
				if((*it).type==36){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).i_hanyou[0]);
					DrawOval((*it).x, (*it).f_hanyou[0], (X_NUM_TO_ZAHYO(10)-X_NUM_TO_ZAHYO(0))/2.0-3.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-10.0, GetColor(0,0,0),TRUE);
				}
				SetDrawBright(255,100,100);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,gSpell[2],TRUE,FALSE);
				SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
				DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,gSpell[2],TRUE,FALSE);
				DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,gSpell[3],TRUE,FALSE);
			}
		}
		SetDrawBright(255,255,255);
	}
	SetDrawBright(255,255,255);
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()==0){
			int count = Player[i].get_spell_count();
			char draw[128];
			if(Player[i].special[0]=='\0')	wsprintf(draw,"%s",Player[i].spell_name[Player[i].draw_level]);
			else				wsprintf(draw,"%s",Player[i].special);
			if(count<30){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,count*8.5);
				if(Player[i].draw_level>=0)	DrawSt(160*i,100,GetColor(200,200,255),GetColor(0,0,0),font_default,draw);
				else	DrawSt(160*i,100,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].special);
			}
			else if(count<90){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(Player[i].draw_level>=0)	DrawSt(160*i,100,GetColor(200,200,255),GetColor(0,0,0),font_default,draw);
				else	DrawSt(160*i,100,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].special);
			}
			else if(count<100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(Player[i].draw_level>=0)	DrawSt(160*i,100-3*(count-90),GetColor(200,200,255),GetColor(0,0,0),font_default,draw);
				else	DrawSt(160*i,100-3*(count-90),GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].special);
			}
			else if(count<240){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				if(Player[i].draw_level>=0)	DrawSt(160*i,70,GetColor(200,200,255),GetColor(0,0,0),font_default,draw);
				else	DrawSt(160*i,70,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].special);
			}
			else if(count<360){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-2.125*(count-240));
				if(Player[i].draw_level>=0)	DrawSt(160*i,70,GetColor(200,200,255),GetColor(0,0,0),font_default,draw);
				else	DrawSt(160*i,70,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].special);
			}
		}
	}

	return;
}

void SpMove(list<SPELLDATA>::iterator &it){
	if(bTimeStop==true&&(*it).type!=1&&(*it).type!=10&&(*it).type!=11)	return;
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
	int c = (*it).count;
	if((*it).type==0||(*it).type==7||(*it).type==8||(*it).type==9){//0:マスタースパーク 7:アサシンスパーク 8.9:ファイナルスパーク 
		if(c==0){
			(*it).i_hanyou[0] = Player[(*it).player].get_direction();
			play_sound(13);
		}
		Player[(*it).player].bMove = false;

		(*it).haba = X_NUM_TO_ZAHYO(4) - X_NUM_TO_ZAHYO(0);
		if((*it).type==7)	(*it).haba = X_NUM_TO_ZAHYO(5) - X_NUM_TO_ZAHYO(0);
		float length = 600;
		if((*it).type==7){
			if(c<60){
				(*it).haba = (X_NUM_TO_ZAHYO(5) - X_NUM_TO_ZAHYO(0))/60.0*c+1;
				length = 1*c;
			}
			else if(c<90){
			}
			else if(c<180){}
			else if(c<240){
				(*it).haba = (X_NUM_TO_ZAHYO(5) - X_NUM_TO_ZAHYO(0))/60.0*(240-c)+1;
			}
			else{
				(*it).bDelete = true;
       	         		Player[(*it).player].bMove = true;
			}
			if(c>=60){
				length = 60+10*(c-60);
			}
		}
		else{
			if(c<60){
				(*it).haba = 2.0;
				length = 10*c;
			}
			else if(c<90){
				(*it).haba = (X_NUM_TO_ZAHYO(4) - X_NUM_TO_ZAHYO(0))/30.0*(c-60)+1;
			}
			else if(c<180){}
			else if(c<240){
				(*it).haba = (X_NUM_TO_ZAHYO(4) - X_NUM_TO_ZAHYO(0))/60.0*(240-c)+1;
			}
			else{
				(*it).bDelete = true;
       	         		Player[(*it).player].bMove = true;
			}
		}
		if((*it).type<8){
			if((*it).i_hanyou[0]==0){
				(*it).f_hanyou[0] = (*it).x - (*it).haba/2.0;
				(*it).f_hanyou[1] = (*it).y - length;
				(*it).f_hanyou[2] = (*it).x + (*it).haba/2.0;
				(*it).f_hanyou[3] = (*it).y - length;
				(*it).f_hanyou[4] = (*it).x + (*it).haba/2.0;
				(*it).f_hanyou[5] = (*it).y;
				(*it).f_hanyou[6] = (*it).x - (*it).haba/2.0;
				(*it).f_hanyou[7] = (*it).y;
			}
			else if((*it).i_hanyou[0]==1){
				(*it).f_hanyou[0] = (*it).x + length;
				(*it).f_hanyou[1] = (*it).y - (*it).haba/2.0;
				(*it).f_hanyou[2] = (*it).x + length;
				(*it).f_hanyou[3] = (*it).y + (*it).haba/2.0;
				(*it).f_hanyou[4] = (*it).x;
				(*it).f_hanyou[5] = (*it).y + (*it).haba/2.0;
				(*it).f_hanyou[6] = (*it).x;
				(*it).f_hanyou[7] = (*it).y - (*it).haba/2.0;
			}
			else if((*it).i_hanyou[0]==2){
				(*it).f_hanyou[0] = (*it).x + (*it).haba/2.0;
				(*it).f_hanyou[1] = (*it).y + length;
				(*it).f_hanyou[2] = (*it).x - (*it).haba/2.0;
				(*it).f_hanyou[3] = (*it).y + length;
				(*it).f_hanyou[4] = (*it).x - (*it).haba/2.0;
				(*it).f_hanyou[5] = (*it).y;
				(*it).f_hanyou[6] = (*it).x + (*it).haba/2.0;
				(*it).f_hanyou[7] = (*it).y;
			}
			else if((*it).i_hanyou[0]==3){
				(*it).f_hanyou[0] = (*it).x - length;
				(*it).f_hanyou[1] = (*it).y + (*it).haba/2.0;
				(*it).f_hanyou[2] = (*it).x - length;
				(*it).f_hanyou[3] = (*it).y - (*it).haba/2.0;
				(*it).f_hanyou[4] = (*it).x;
				(*it).f_hanyou[5] = (*it).y - (*it).haba/2.0;
				(*it).f_hanyou[6] = (*it).x;
				(*it).f_hanyou[7] = (*it).y + (*it).haba/2.0;
			}
		}
		else{
			float angle;
			if((*it).i_hanyou[0]==0){
				if((*it).type==8)	angle = Radian(-70,TRUE);
				else			angle = Radian(250,TRUE);
			}
			else if((*it).i_hanyou[0]==1){
				if((*it).type==8)	angle = Radian(-20,TRUE);
				else			angle = Radian(20,TRUE);
			}
			else if((*it).i_hanyou[0]==2){
				if((*it).type==8)	angle = Radian(110,TRUE);
				else			angle = Radian(70,TRUE);
			}
			else if((*it).i_hanyou[0]==3){
				if((*it).type==8)	angle = Radian(160,TRUE);
				else			angle = Radian(200,TRUE);
			}
			(*it).f_hanyou[0] = (*it).x + length*cos(angle) - (*it).haba/2.0*sin(angle);
			(*it).f_hanyou[1] = (*it).y + length*sin(angle) + (*it).haba/2.0*cos(angle);
			(*it).f_hanyou[2] = (*it).x + length*cos(angle) + (*it).haba/2.0*sin(angle);
			(*it).f_hanyou[3] = (*it).y + length*sin(angle) - (*it).haba/2.0*cos(angle);
			(*it).f_hanyou[4] = (*it).x + (*it).haba/2.0*sin(angle);
			(*it).f_hanyou[5] = (*it).y - (*it).haba/2.0*cos(angle);
			(*it).f_hanyou[6] = (*it).x - (*it).haba/2.0*sin(angle);
 			(*it).f_hanyou[7] = (*it).y + (*it).haba/2.0*cos(angle);
		}
		SpAtari(it);
	}
	else if((*it).type==1||(*it).type==10||(*it).type==11){//1:ジャック・ザ・リッパー 10:ジャック・ザ・ルドビレ 11:殺人ドール
		if(c>=60&&c<240){
			bTimeStop = true;
			Player[(*it).player].bTime = true;
			if((*it).type==11)			TimeStopType = 2;
			else if((*it).type==10&&TimeStopType<2)	TimeStopType = 1;
			else if((*it).type==1&&TimeStopType<1)	TimeStopType = 0;
		}
		if(c==60){			
			if(Player[(*it).player].get_condition()==0&&TimeStopType==0){
				float x,y;
				Player[(*it).player].get_xy(&x,&y);
				int pattern = 0;
				if(Player[(*it).player].bSpbomb==true)	pattern = 1;
				for(int i=0;i<4;i++){
					Player[(*it).player].bomb_num--;
					BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), (*it).player, Player[(*it).player].get_power(), pattern, i+6);
				}
			}
		}
		if(c==240){
			Player[(*it).player].bTime = false;
			bTimeStop = false;
			(*it).bDelete = true;
		}
		if(c!=0&&c%60==0)	play_sound(8);
	}
	else if((*it).type==2||(*it).type==12||(*it).type==13){//2:全世界ナイトメア 12:ミッドナイトディザスター 13:レミリアストーカー
		if(c==0)	play_sound(14);
		if(c<50)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,3*c);
		else if(c>=290&&c<340)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,3*(340-c));
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,GetColor(255,100,100),TRUE);
               	if(c>=50&&c<230){
			if(c%6==0){
				if((*it).type==2||(*it).type==12){
					int rand_x,rand_y;
					bool flag = false;
					for(int i=0;i<10;i++){
						rand_x = get_rand(LARGE_X-1);
						rand_y = get_rand(LARGE_Y-1);
						if(Map.field[rand_x][rand_y]==0){
							flag = true;
							break;
						}
					}
					if(flag==true){
						if((*it).type==2){
							if(Para.time_count<3600)	BMake(rand_x, rand_y, (*it).player, 3, 0, 10);
							else				BMake(rand_x, rand_y, (*it).player, 1, 0, 10);
						}
						else if((*it).type==12){
							if(Para.time_count<3600)	BMake(rand_x, rand_y, (*it).player, 3, 0, 21);
							else				BMake(rand_x, rand_y, (*it).player, 1, 0, 21);
						}
					}
				}
				else if((*it).type==13){
					int rand_x,rand_y,rand,alive=0;
					for(int i=0;i<4;i++){
						if(Player[i].get_condition()==0)	alive ++;
					}
					bool flag = false;
					if(alive>=2){
						while(1){
							rand = get_rand(3);
							if(rand!=(*it).player&&Player[rand].get_condition()==0){
								float x,y;
								Player[rand].get_xy(&x,&y);
								rand_x = X_ZAHYO_TO_NUM(x);
								rand_y = Y_ZAHYO_TO_NUM(y);
								flag = true;
							}
							if(flag==true)	break;
						}
					}
					else{
						for(int i=0;i<10;i++){
							rand_x = get_rand(LARGE_X-1);
							rand_y = get_rand(LARGE_Y-1);
							if(Map.field[rand_x][rand_y]==0){
								flag = true;
								break;
							}
						}
					}
					if(flag==true){
						if(Para.time_count<3600)	BMake(rand_x, rand_y, (*it).player, 3, 0, 10);
						else				BMake(rand_x, rand_y, (*it).player, 1, 0, 10);
					}
				}
			}
		}
		if(c==339)	(*it).bDelete = true;
	}
	else if((*it).type==3||(*it).type==14||(*it).type==15){//3:そして誰もいなくなるか？ 14:そして誰も彼も死ぬがよい 15:４９５年の波紋
		if(c==0)	play_sound(14);
		if(c<50)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,3*c);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,GetColor(255,100,100),TRUE);
		if(c==60){
			for(list<BOMBDATA>::iterator bit=Bomb.begin();bit!=Bomb.end();++bit){
				if(Para.time_count>3600&&(*it).type==14)	(*bit).power = 99;
				else				(*bit).power = 9;
				if(Para.time_count>3600){
					if((*it).type==14)	(*bit).pattern = 1;
					else if((*it).type==15)	(*bit).pattern = -1;
				}
				else{
					(*bit).pattern = 1;
				}
				(*bit).bExplosion = true;
			}
			(*it).bDelete = true;
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
		}
	}
	else if((*it).type==4||(*it).type==5||(*it).type==6){//4:夢想封印 5:夢想封印・散 6:夢想封印・滅
		for(int i=0;i<4;i++){
			Player[(*it).player].bomb_num--;
			if((*it).type==4)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, i+2);
			if((*it).type==5)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, i+13);
			if((*it).type==6)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, i+17);
		}
		(*it).bDelete = true;
	}
	else if((*it).type==16||(*it).type==17||(*it).type==18){//16:妖童餓鬼の断食 17:二百由旬の一閃 18:業風神閃斬 
		if(Player[(*it).player].get_condition()!=0){
			(*it).bDelete = true;
			return;
		}
		if(c==0){
			(*it).i_hanyou[0] = Player[(*it).player].get_direction();
			(*it).x = X_ZAHYO_TO_NUM((*it).x);
			(*it).x = X_NUM_TO_ZAHYO((*it).x)+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
			(*it).y = Y_ZAHYO_TO_NUM((*it).y);
			(*it).y = Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0;
			play_sound(14);
			Player[(*it).player].bMove = false;
		}

		if(c<60){}
		else if(c==60){
			(*it).f_hanyou[2] = 5;//幅
			play_sound(18);
			if((*it).i_hanyou[0]==0){
				for(int i=Y_ZAHYO_TO_NUM((*it).y);i>=0;i--){
					if(Map.field[X_ZAHYO_TO_NUM((*it).x)][i]!=0&&Map.field[X_ZAHYO_TO_NUM((*it).x)][i]!=3){
						(*it).f_hanyou[0] = (*it).x;
						(*it).f_hanyou[1] = Y_NUM_TO_ZAHYO(i+1);
						Player[(*it).player].set_xy((*it).x,Y_NUM_TO_ZAHYO(i+1)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0);
						break;
					}
					else{
						if((*it).type==17){
							Player[(*it).player].bomb_num--;
							BMake(X_ZAHYO_TO_NUM((*it).x), i, (*it).player, Player[(*it).player].get_power(), 0, 0, 180, false);
						}
						else if((*it).type==18){
							Player[(*it).player].bomb_num-=2;
							BMake(X_ZAHYO_TO_NUM((*it).x), i, (*it).player, Player[(*it).player].get_power(), 0, 8, 180, false);
							BMake(X_ZAHYO_TO_NUM((*it).x), i, (*it).player, Player[(*it).player].get_power(), 0, 9, 180, false);
						}
					}
				}
			}
			else if((*it).i_hanyou[0]==1){
				for(int i=X_ZAHYO_TO_NUM((*it).x);i<LARGE_X;i++){
					if(Map.field[i][Y_ZAHYO_TO_NUM((*it).y)]!=0&&Map.field[i][Y_ZAHYO_TO_NUM((*it).y)]!=3){
						(*it).f_hanyou[0] = X_NUM_TO_ZAHYO(i-1);
						(*it).f_hanyou[1] = (*it).y;
						Player[(*it).player].set_xy(X_NUM_TO_ZAHYO(i-1)+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0,(*it).y);
						break;
					}
					else{
						if((*it).type==17){
							Player[(*it).player].bomb_num--;
							BMake(i, Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 0, 180, false);
						}
						else if((*it).type==18){
							Player[(*it).player].bomb_num-=2;
							BMake(i, Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 6, 180, false);
							BMake(i, Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 7, 180, false);
						}
					}
				}
			}
			else if((*it).i_hanyou[0]==2){
				for(int i=Y_ZAHYO_TO_NUM((*it).y);i<LARGE_Y;i++){
					if(Map.field[X_ZAHYO_TO_NUM((*it).x)][i]!=0&&Map.field[X_ZAHYO_TO_NUM((*it).x)][i]!=3){
						(*it).f_hanyou[0] = (*it).x;
						(*it).f_hanyou[1] = Y_NUM_TO_ZAHYO(i-1);
						Player[(*it).player].set_xy((*it).x,Y_NUM_TO_ZAHYO(i-1)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0);
						break;
					}
					else{
						if((*it).type==17){
							Player[(*it).player].bomb_num--;
							BMake(X_ZAHYO_TO_NUM((*it).x), i, (*it).player, Player[(*it).player].get_power(), 0, 0, 180, false);
						}
						else if((*it).type==18){
							Player[(*it).player].bomb_num-=2;
							BMake(X_ZAHYO_TO_NUM((*it).x), i, (*it).player, Player[(*it).player].get_power(), 0, 8, 180, false);
							BMake(X_ZAHYO_TO_NUM((*it).x), i, (*it).player, Player[(*it).player].get_power(), 0, 9, 180, false);
						}
					}
				}
			}
			else if((*it).i_hanyou[0]==3){
				for(int i=X_ZAHYO_TO_NUM((*it).x);i>=0;i--){
					if(Map.field[i][Y_ZAHYO_TO_NUM((*it).y)]!=0&&Map.field[i][Y_ZAHYO_TO_NUM((*it).y)]!=3){
						(*it).f_hanyou[0] = X_NUM_TO_ZAHYO(i+1);
						(*it).f_hanyou[1] = (*it).y;
						Player[(*it).player].set_xy(X_NUM_TO_ZAHYO(i+1)+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0,(*it).y);
						break;
					}
					else{
						if((*it).type==17){
							Player[(*it).player].bomb_num--;
							BMake(i, Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 0, 180, false);
						}
						else if((*it).type==18){
							Player[(*it).player].bomb_num-=2;
							BMake(i, Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 6, 180, false);
							BMake(i, Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 7, 180, false);
						}
					}
				}
			}
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
			Player[(*it).player].set_muteki_count(240);			
			Player[(*it).player].bMove = true;			
		}
		else	Player[(*it).player].bMove = true;
		if(c<90){}
		else if(c<95){
			(*it).f_hanyou[2]--;		
		}
		else{
			(*it).bDelete = true;
		}
		SpAtari(it);
	}
	else if((*it).type==19||(*it).type==20||(*it).type==21){//19:亡我郷 20:完全なる墨染の桜 21:反魂蝶
		if((*it).type<21){
			if((*it).type==19)	Player[(*it).player].bBouga = true;
			if((*it).type==20)	Player[(*it).player].bSumizome = true;
			(*it).bDelete = true;
		}
		else{
			if(Para.time_count>=3600){
				(*it).bDelete = true;
				return;
			}
			if(c!=0){
				if(HangonLife<=0)	(*it).bDelete = true;
			}
			if(c==0){
				BEfMake(Enemy.x,Enemy.y,3,42);
				Enemy.bExist = false;
				Player[(*it).player].bMove = false;
				Player[(*it).player].bKickbomb = false;
				Player[(*it).player].dokuro = 0;
				float x,y;
				Player[(*it).player].get_xy(&x,&y);
				(*it).f_hanyou[0] = x;
				(*it).f_hanyou[1] = y;
				float dx = (X_NUM_TO_ZAHYO(LARGE_X-1)+X_NUM_TO_ZAHYO(0)+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0)/2.0 - x;
				float dy = (Y_NUM_TO_ZAHYO(LARGE_Y-1)+Y_NUM_TO_ZAHYO(0)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0)/2.0 - y;
				float d = sqrt(dx*dx+dy*dy);
				float angle = Atan2(dy, dx);
				Player[(*it).player].d_hanyou[0] = cos(angle);
				Player[(*it).player].d_hanyou[1] = sin(angle);
				Player[(*it).player].d_hanyou[2] = d / 1770.0;
				HangonLife = 0;
				for(int i=0;i<4;i++){
					if(i!=(*it).player&&Player[i].get_condition()==0){
						HangonLife += Player[i].get_bomb()*45;
					}
				}
				if(HangonLife<45*5)	HangonLife = 45*5;
				(*it).i_hanyou[0] = HangonLife;
				(*it).i_hanyou[1] = -1;
			}
			else if(c<=60){
				Player[(*it).player].d_hanyou[3] = Player[(*it).player].d_hanyou[2]*(60.0-(float)c);
				float x,y;
				Player[(*it).player].get_xy(&x,&y);
				Player[(*it).player].large += 0.01;
				x += Player[(*it).player].d_hanyou[0] * Player[(*it).player].d_hanyou[3];
				y += Player[(*it).player].d_hanyou[1] * Player[(*it).player].d_hanyou[3];
				Player[(*it).player].set_xy(x,y);	
				(*it).f_hanyou[0] = x;
				(*it).f_hanyou[1] = y;
			}
			else if(c==61){
				Player[(*it).player].bMove = true;
			}
			else{
				c += 60;
				if(c%180==0){
					int level = (3600-Para.time_count)/400.0+1;//1~10
					int bomb,spell;
					Player[(*it).player].get_key(&bomb,&spell);
					int before = (*it).i_hanyou[1];
					if(bomb==0&&spell==0)	(*it).i_hanyou[1] = 0;
					if(bomb>=1&&spell==0)	(*it).i_hanyou[1] = 1;
					if(bomb==0&&spell>=1)	(*it).i_hanyou[1] = 2;
					if(bomb>=1&&spell>=1)	(*it).i_hanyou[1] = 3;
					if((*it).i_hanyou[1]==before)	(*it).i_hanyou[1] = ((*it).i_hanyou[1]+1)%4;
					(*it).i_hanyou[2] = level;
					(*it).f_hanyou[4] = 0.1*get_rand(3600);
				}
				float x,y;
				Player[(*it).player].get_xy(&x,&y);
				if((*it).i_hanyou[1]==0){
					if(c%180==0||c%180==15||c%180==30||c%180==45||c%180==60){
						play_sound(10);
						int num = 10+1*(*it).i_hanyou[2];
						float per = 360.0 / (float)num;
						for(int i=0;i<num;i++){
							if(c%180%30==0){
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per, 1.5, gShot[2][3],2,0,20);
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per, 1.5, gShot[2][3],2,6,20);
							}
							else{
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per, 1.5, gShot[2][5],2,0,20);
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per, 1.5, gShot[2][5],2,6,20);
							}
						}
					}
					if(c%180==80||c%180==95||c%180==110||c%180==125||c%180==140){
						play_sound(20);
					}
				}
				else if((*it).i_hanyou[1]==1){
					if(c%180==0||c%180==30||c%180==60||c%180==90){
						play_sound(10);
						int num = 5+1*(*it).i_hanyou[2];
						float per = 360.0 / (float)num;
						for(int i=0;i<num;i++){
							if(c%180%60==0){
								for(int j=0;j<3;j++)	ShMake(x, y, (*it).f_hanyou[4]+(float)i*per, 1.2, gShot[2][0],2,7+j,0);
							}
							else{
								for(int j=0;j<3;j++)	ShMake(x, y, (*it).f_hanyou[4]+(float)i*per, 1.2, gShot[2][0],2,10+j,0);
							}
						}
					}
					if(c%180==60||c%180==90||c%180==120||c%180==150){
						play_sound(20);
					}
				}
				else if((*it).i_hanyou[1]==2){
					if(c%180==0){
						play_sound(10);
						int num = 10+1*(*it).i_hanyou[2];
						float per = 360.0 / (float)num;
						for(int i=0;i<num;i++){
							for(int j=0;j<8;j++){
								int pa = 13+j%4;
								for(int a=0;a<4;a++){
									int n = (j%4+a)%4;
									if(n!=(*it).player&&Player[n].get_condition()==0){
										pa = 13+n;
										break;
									}
								}
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per+12*j, 1.5+3.5*(float)j/8.0, gShot[2][3],2,pa,10);
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per+12*j+(float)per/2.0, 1.5+3.5*(float)j/8.0, gShot[2][5],2,pa,10);
							}
						}
					}
					if(c%180==100){
						play_sound(20);
					}
				}
				else if((*it).i_hanyou[1]==3){
					if(c%180==0){
						play_sound(10);
						int num = 10+1*(*it).i_hanyou[2];
						float per = 360.0 / (float)num;
						for(int i=0;i<num;i++){
							for(int j=0;j<8;j++){
								int pa = 17+j%4;
								for(int a=0;a<4;a++){
									int n = (j%4+a)%4;
									if(n!=(*it).player&&Player[n].get_condition()==0){
										pa = 17+2*n+(j/4)%2;
										break;
									}
								}
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per+12*j, 1.5+3.5*(float)j/8.0, gShot[2][3],2,pa,10);
								ShMake(x, y, (*it).f_hanyou[4]+(float)i*per+12*j+(float)per/2.0, 1.5+3.5*(float)j/8.0, gShot[2][5],2,pa,10);
							}
						}
					}
					if(c%180==100){
						play_sound(20);
					}
				}
			}
		}
	}
	else if((*it).type==22||(*it).type==23||(*it).type==24){//22:動と静の均衡 23:夢と現の境界 24:メビウスの表裏
		if(c==0)	play_sound(19);
		if((*it).type!=22){
			if(c<50)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2*c);
			else if(c>=390)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2*(440-c));
			else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
		}
		else{
			if(c<50)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2*c);
			else if(c>=550)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2*(600-c));
			else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
		}
		DrawBox(0,0,640,480,GetColor(150,0,150),TRUE);
		if((*it).type==22||(*it).type==23){
			if((*it).type==22){
				if(c<60){}
				else if(c>=60&&c<550){
					bYukari = true;
				}
				else{
					bYukari = false;
				}
				if(c==600)	(*it).bDelete = true;
			}
			else{
				if(c<60){}
				else if(c>=60&&c<390){
					Hanten = (*it).player;
				}
				else{
					bYukari = false;
					Hanten = -1;
				}
				if(c==440)	(*it).bDelete = true;
			}
		}
		else{
			if(c<60){}
			else{
				play_sound(18);
				int livenum = 0;
				for(int i=0;i<4;i++){
					if(Player[i].get_condition()==0)	livenum++;
				}
				if(livenum==4){
					int rand = get_rand(3);
					while(1){
						if((*it).player==rand){
							rand = (rand+1)%4;
						}
						else	break;
					}
					float x,y,rx,ry;
					Player[(*it).player].get_xy(&x,&y);
					Player[rand].get_xy(&rx,&ry);
					Player[(*it).player].set_xy(rx,ry);
					Player[rand].set_xy(x,y);
					int rand2,rand3;
					for(int i=0;i<4;i++){
						rand2 = i;
						if(rand2!=(*it).player&&rand2!=rand){
							break;
						}
					}
					for(int i=0;i<4;i++){
						rand3 = i;
						if(rand3!=(*it).player&&rand3!=rand&&rand3!=rand2){
							break;
						}
					}
					float rx2,ry2,rx3,ry3;
					Player[rand2].get_xy(&rx2,&ry2);
					Player[rand3].get_xy(&rx3,&ry3);
					Player[rand2].set_xy(rx3,ry3);
					Player[rand3].set_xy(rx2,ry2);
				}
				else if(livenum==3){
					int rand = get_rand(3);
					int rand2 = get_rand(3);
					int rand3 = get_rand(3);
					while(1){
						if(Player[rand].get_condition()!=0){
							rand = (rand+1)%4;
						}
						else	break;
					}
					while(1){
						if(rand2==rand||Player[rand2].get_condition()!=0){
							rand2 = (rand2+1)%4;
						}
						else	break;
					}
					while(1){
						if(rand3==rand||rand3==rand2||Player[rand3].get_condition()!=0){
							rand3 = (rand3+1)%4;
						}
						else	break;
					}
					float x,y,rx,ry;
					Player[rand].get_xy(&x,&y);
					Player[rand2].get_xy(&rx,&ry);
					Player[rand].set_xy(rx,ry);
					Player[rand2].set_xy(x,y);
					float rx2,ry2;
					Player[rand].get_xy(&x,&y);
					Player[rand3].get_xy(&rx2,&ry2);
					Player[rand].set_xy(rx2,ry2);
					Player[rand3].set_xy(x,y);
				}
				else if(livenum==2){
					int rand = get_rand(3);
					int rand2 = get_rand(3);
					while(1){
						if(Player[rand].get_condition()!=0){
							rand = (rand+1)%4;
						}
						else	break;
					}
					while(1){
						if(rand2==rand||Player[rand2].get_condition()!=0){
							rand2 = (rand2+1)%4;
						}
						else	break;
					}
					float x,y,rx,ry;
					Player[rand].get_xy(&x,&y);
					Player[rand2].get_xy(&rx,&ry);
					Player[rand].set_xy(rx,ry);
					Player[rand2].set_xy(x,y);
				}
				
				DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);			
				(*it).bDelete = true;
			}
		}
	}
	else if((*it).type==25||(*it).type==26||(*it).type==27){//25:幻想催眠（インビシブルウォール） 26:幻影の壁（イリュージョンウォール） 27:月兎爆誕（ルナファントム）
		if(c==0)	play_sound(18);
		if((*it).type==25){
			if(c<50){
				MapFlash = 5.1*(50-c);
			}
			else if(c<550){
				MapFlash = 0;
			}
			else if(c<600){
				MapFlash = 5.1*(c-550);
			}
			else{
				MapFlash = -1;
				(*it).bDelete = true;
			}
		}
		else if((*it).type==26){
			if(c==0){
				for(int i=0;i<30;i++){
					int x,y;
					x = get_rand(LARGE_X-1);
					y = get_rand(LARGE_Y-1);
					for(int j=0;j<10;j++){
						if(Map.field[x][y]==0)	break;
						else{
							x = get_rand(LARGE_X-1);
							y = get_rand(LARGE_Y-1);
						}
					}
					if(Map.field[x][y]==0)	BEfMake(X_NUM_TO_ZAHYO(x), Y_NUM_TO_ZAHYO(y), -1, 43);
				}
				(*it).bDelete = true;
			}
		}
		else if((*it).type==27){
			if(c==0){
				for(int i=0,num=0;i<ILLUSION_NUM&&num<2;i++){
					if(Illusion[i].player_num==-1){
						float x,y;
						Player[(*it).player].get_xy(&x,&y);
						int ix = X_ZAHYO_TO_NUM(x);
						int iy = Y_ZAHYO_TO_NUM(y);
						for(int a=0;a<10;a++){
							ix = get_rand(LARGE_X-1);
							iy = get_rand(LARGE_Y-1);
							if(Map.field[ix][iy]==0||Map.field[ix][iy]==3)	break;
						}
						if(Map.field[ix][iy]!=0&&Map.field[ix][iy]!=3){
							ix = X_ZAHYO_TO_NUM(x);
							iy = Y_ZAHYO_TO_NUM(y);
						}
						Illusion[i].make((X_NUM_TO_ZAHYO(ix)+X_NUM_TO_ZAHYO(ix+1))/2.0, (Y_NUM_TO_ZAHYO(iy)+Y_NUM_TO_ZAHYO(iy+1))/2.0, Player[(*it).player].chara, Player[(*it).player].color, false, (*it).player);	
						num++;
					}
				}
			}
			if(c<50){
				Player[(*it).player].illusion_flash = 5.1*c;
			}
			else if(c<550){
				Player[(*it).player].illusion_flash = 255;
			}
			else if(c<600){
				Player[(*it).player].illusion_flash = 5.1*(600-c);
			}
			else{
				Player[(*it).player].illusion_flash = 0;
				for(int i=0,num=0;i<ILLUSION_NUM&&num<9;i++){
					if(Illusion[i].player_num==(*it).player){
						Illusion[i].player_num = -1;
						num++;
					}
				}
				(*it).bDelete = true;
			}
		}
	}
	else if((*it).type==28||(*it).type==29||(*it).type==30){//28:オプティカルカモフラージュ 29:のびーるアーム 30:スピン・ザ・ボンバー
		if((*it).type==28){
			if(c==0){
				Player[(*it).player].bCamo = true;
			}
			if(c<50){
				Player[(*it).player].flash = 5.1*(50-c);
			}
			else if(c<550){
				Player[(*it).player].flash = 0;
			}
			else if(c<600){
				Player[(*it).player].flash = 5.1*(c-550);
			}
			else{
				Player[(*it).player].flash = 255;
				(*it).bDelete = true;
				Player[(*it).player].bCamo = false;
			}
			if(Player[(*it).player].bCamo==false){
				Player[(*it).player].flash = 255;
				(*it).bDelete = true;
			}
		}
		else if((*it).type==29){
			(*it).haba = 10;
			if(c==0){
				(*it).i_hanyou[0] = Player[(*it).player].get_direction();
				(*it).x = X_NUM_TO_ZAHYO(X_ZAHYO_TO_NUM((*it).x))+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
				(*it).y = Y_NUM_TO_ZAHYO(Y_ZAHYO_TO_NUM((*it).y))+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0;
				play_sound(13);
			}
			Player[(*it).player].bMove = false;
       	
			if(c<180){
				float speed = 5.0;
				float x[2],y[2];
				x[0] = (*it).x-(*it).f_hanyou[0]-speed;
				x[1] = (*it).x+(*it).f_hanyou[1]+speed;
				y[0] = (*it).y-(*it).f_hanyou[2]-speed;
				y[1] = (*it).y+(*it).f_hanyou[3]+speed;
				if(Map.field[X_ZAHYO_TO_NUM(x[0])][Y_ZAHYO_TO_NUM((*it).y)]!=1&&Map.field[X_ZAHYO_TO_NUM(x[0])][Y_ZAHYO_TO_NUM((*it).y)]!=2){
					(*it).f_hanyou[0] += speed;
				}
				if(Map.field[X_ZAHYO_TO_NUM(x[1])][Y_ZAHYO_TO_NUM((*it).y)]!=1&&Map.field[X_ZAHYO_TO_NUM(x[1])][Y_ZAHYO_TO_NUM((*it).y)]!=2){
					(*it).f_hanyou[1] += speed;
				}
				if(Map.field[X_ZAHYO_TO_NUM((*it).x)][Y_ZAHYO_TO_NUM(y[0])]!=1&&Map.field[X_ZAHYO_TO_NUM((*it).x)][Y_ZAHYO_TO_NUM(y[0])]!=2){
					(*it).f_hanyou[2] += speed;
				}
				if(Map.field[X_ZAHYO_TO_NUM((*it).x)][Y_ZAHYO_TO_NUM(y[1])]!=1&&Map.field[X_ZAHYO_TO_NUM((*it).x)][Y_ZAHYO_TO_NUM(y[1])]!=2){
					(*it).f_hanyou[3] += speed;
				}
				for(int i=0;i<4;i++){
					(*it).f_hanyou[4+i] = (*it).f_hanyou[i] / 30.0;
				}
				for(list<BOMBDATA>::iterator bit=Bomb.begin(); bit!=Bomb.end(); ++bit){
					//if((*bit).direction>-1)	continue;
					if((*bit).x!=X_ZAHYO_TO_NUM((*bit).fx) || (*bit).y!=Y_ZAHYO_TO_NUM((*bit).fy))	continue;
					x[0] = (*it).x-(*it).f_hanyou[0];
					x[1] = (*it).x+(*it).f_hanyou[1];
					y[0] = (*it).y-(*it).f_hanyou[2];
					y[1] = (*it).y+(*it).f_hanyou[3];
					int di = (*bit).direction;
					if(x[0]<(*bit).fx&&(*bit).fx<(*it).x&&(*it).y-(*it).haba<(*bit).fy&&(*bit).fy<(*it).y+(*it).haba){
						(*bit).direction = 2;
					}
					if((*it).x<(*bit).fx&&(*bit).fx<x[1]&&(*it).y-(*it).haba<(*bit).fy&&(*bit).fy<(*it).y+(*it).haba){
						(*bit).direction = 3;
					}
					if(y[0]<(*bit).fy&&(*bit).fy<(*it).y&&(*it).x-(*it).haba<(*bit).fx&&(*bit).fx<(*it).x+(*it).haba){
						(*bit).direction = 0;
					}
					if((*it).y<(*bit).fy&&(*bit).fy<y[1]&&(*it).x-(*it).haba<(*bit).fx&&(*bit).fx<(*it).x+(*it).haba){
						(*bit).direction = 1;
					}
				}
			}
			else if(c<210){
				for(int i=0;i<4;i++){
					(*it).f_hanyou[i] -= (*it).f_hanyou[i+4];
				}
			}
			else{
				(*it).bDelete = true;
       		         	Player[(*it).player].bMove = true;
			}
			SpAtari(it);
		}
		else if((*it).type==30){
			BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 26);
			BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 27);
			BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 33);
			BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 0, 34);
			(*it).bDelete = true;
		}
	}
	else if((*it).type==31||(*it).type==32||(*it).type==33){//31:天の恵み 32:サモンタケミナカタ 33:ミラクルフルーツ
		if((*it).type==31){
			if(c==0){
				play_sound(14);
				int rand_x,rand_y,rand_x2,rand_y2;
				int ppx = X_ZAHYO_TO_NUM((*it).x);
				int ppy = Y_ZAHYO_TO_NUM((*it).y);
				bool flag = false;
				for(int i=0;i<50;i++){
					rand_x = X_ZAHYO_TO_NUM((*it).x)+get_rand(4)-2;
					rand_y = Y_ZAHYO_TO_NUM((*it).y)+get_rand(4)-2;
					if(rand_x>0&&rand_x<LARGE_X&&rand_y>0&&rand_y<LARGE_Y&&Map.field[rand_x][rand_y]==0&&(rand_x!=ppx||rand_y!=ppy)){
						flag = true;
						break;
					}
				}
				bool flag2 = false;
				for(int i=0;i<50;i++){
					rand_x2 = X_ZAHYO_TO_NUM((*it).x)+get_rand(4)-2;
					rand_y2 = Y_ZAHYO_TO_NUM((*it).y)+get_rand(4)-2;
					if(rand_x2!=rand_x&&rand_y2!=rand_y&&rand_x2>0&&rand_x2<LARGE_X&&rand_y2>0&&rand_y2<LARGE_Y&&Map.field[rand_x2][rand_y2]==0&&(rand_x!=ppx||rand_y!=ppy)){
						flag2 = true;
						break;
					}
				}
				if(flag==true){
					(*it).i_hanyou[1] = rand_x;
					(*it).i_hanyou[2] = rand_y;
				}
				if(flag2==true){
					(*it).i_hanyou[3] = rand_x2;
					(*it).i_hanyou[4] = rand_y2;
				}
			}
			if(c<30){
				float x = (X_NUM_TO_ZAHYO((*it).i_hanyou[1])+X_NUM_TO_ZAHYO((*it).i_hanyou[1]+1))/2.0; 
				float y = (Y_NUM_TO_ZAHYO((*it).i_hanyou[2])+Y_NUM_TO_ZAHYO((*it).i_hanyou[2]+1))/2.0; 
				if((*it).i_hanyou[1]>0&&(*it).i_hanyou[2]>0)	BEfMake(x,y,0,41);
				x = (X_NUM_TO_ZAHYO((*it).i_hanyou[3])+X_NUM_TO_ZAHYO((*it).i_hanyou[3]+1))/2.0; 
				y = (Y_NUM_TO_ZAHYO((*it).i_hanyou[4])+Y_NUM_TO_ZAHYO((*it).i_hanyou[4]+1))/2.0; 
				if((*it).i_hanyou[3]>0&&(*it).i_hanyou[4]>0)	BEfMake(x,y,0,41);
			}
			else{
				if((*it).i_hanyou[1]>0&&(*it).i_hanyou[2]>0){
					IMake((*it).i_hanyou[1], (*it).i_hanyou[2], get_rand(ITEM_GRAPH_NUM-1), true);
					Map.field[(*it).i_hanyou[1]][(*it).i_hanyou[2]] = 3;
				}
				if((*it).i_hanyou[3]>0&&(*it).i_hanyou[4]>0){
					IMake((*it).i_hanyou[3], (*it).i_hanyou[4], get_rand(ITEM_GRAPH_NUM-1), true);
					Map.field[(*it).i_hanyou[3]][(*it).i_hanyou[4]] = 3;
				}
				(*it).bDelete = true;
			}
		}	
		else if((*it).type==32){
			if(c==0){
				play_sound(14);
			}
			if(c>=60&&c<=115&&c%5==0){
				Player[(*it).player].bomb_num--;
				int x,y;
				if(c<=70){
					x = 7+2*(c-60)/5;
					y = 4;
				}
				else if(c<=90){
					x = 11;
					y = 4+(c-70)/5;
				}
				else if(c<=100){
					x = 11-2*(c-90)/5;
					y = 8;
				}
				else if(c<=115){
					x = 7;
					y = 8-(c-100)/5;
				}
				if(Map.field[x][y]==0||Map.field[x][y]==3){
					play_sound(3);
					BMake(x, y, (*it).player, Player[(*it).player].get_power(), 2, 28);
				}
			}
			else if(c==115){
				(*it).bDelete = true;
			}
		}	
		else if((*it).type==33){
			int d = Player[(*it).player].get_direction();
			if(d==0)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, 29);
			if(d==1)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, 32);
			if(d==2)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, 30);
			if(d==3)	BMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).y), (*it).player, Player[(*it).player].get_power(), 2, 31);
			(*it).bDelete = true;
		}
	}
	else if((*it).type==34||(*it).type==35||(*it).type==36){//34:重水素融合 35:ギガフレア 36:アトミックボム
		if((*it).type==34){
			play_sound(14);
			Player[(*it).player].add_speed(0.5);
			Player[(*it).player].level_plus();
			(*it).bDelete = true;
		}
		else if((*it).type==35){
			if(c==0){
				play_sound(14);
				play_sound(9);
				(*it).flash = 100;
				Player[(*it).player].bMove = false;
				int d = Player[(*it).player].get_direction();
				if(d==0){
					(*it).f_hanyou[0] = 0;
					(*it).f_hanyou[1] = -1;
				}
				else if(d==1){
					(*it).f_hanyou[0] = 1;
					(*it).f_hanyou[1] = 0;
				}
				else if(d==2){
					(*it).f_hanyou[0] = 0;
					(*it).f_hanyou[1] = 1;
				}
				else if(d==3){
					(*it).f_hanyou[0] = -1;
					(*it).f_hanyou[1] = 0;
				}
				if(d==1||d==3){
					for(int i=0;i<20;i++){
						EfMake(640.0-256.0*0.8/2.0-256.0*0.8*i,(Y_NUM_TO_ZAHYO(Y_ZAHYO_TO_NUM((*it).y))+Y_NUM_TO_ZAHYO(Y_ZAHYO_TO_NUM((*it).y)+1))/2.0,1,42);
                        		}
				}
				else if(d==0||d==2){
					for(int i=0;i<20;i++){
						EfMake((X_NUM_TO_ZAHYO(X_ZAHYO_TO_NUM((*it).x))+X_NUM_TO_ZAHYO(X_ZAHYO_TO_NUM((*it).x)+1))/2.0,256.0*0.8/2.0+256.0*0.8*i,1,45);
                        		}
				}
				Player[(*it).player].set_muteki_count(240);
			}
			if(c<180){
				(*it).large = (1.2 / 180.0)*c;
				SShake(0,10.0*(float)c/180.0);
				(*it).f_hanyou[2] += 0.005;
			}
			else if(c==180){
				play_sound(21);
				(*it).large = 1.2;
				float x,y;
				Player[(*it).player].get_xy(&x,&y);
				EfMake(x,y,5,47);
				(*it).f_hanyou[2] = 20.0;
				shake_x = 0;
				shake_y = 0;
			}
			else if(c<240){}
			else{
				Player[(*it).player].spell_level = 1;
				if(Player[(*it).player].gage_per>1) Player[(*it).player].gage_per--;
				(*it).bDelete = true;
			}
			if(c==240)	Player[(*it).player].bMove = true;
			(*it).x += (*it).f_hanyou[0]*(*it).f_hanyou[2];		
			(*it).y += (*it).f_hanyou[1]*(*it).f_hanyou[2];
			(*it).angle += Radian(6,TRUE);		
			SpAtari(it);
		}
		else if((*it).type==36){
			if(c==0){
				play_sound(14);
				play_sound(9);
				(*it).flash = 100;
				(*it).x = 4+get_rand(LARGE_X-9);
				(*it).y = 4+get_rand(LARGE_Y-9);
				(*it).f_hanyou[0] = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
				for(int i=0;i<20;i++){
					EfMake(640.0-256.0*0.8/2.0-256.0*0.8*i,(Y_NUM_TO_ZAHYO((*it).y-5)+Y_NUM_TO_ZAHYO((*it).y-4))/2.0,1,42);
					EfMake((X_NUM_TO_ZAHYO((*it).x+5)+X_NUM_TO_ZAHYO((*it).x+6))/2.0,480.0-256.0*0.8/2.0-256.0*0.8*i,1,43);
					EfMake(256.0*0.8/2.0+256.0*0.8*i,(Y_NUM_TO_ZAHYO((*it).y+5)+Y_NUM_TO_ZAHYO((*it).y+6))/2.0,1,44);
					EfMake((X_NUM_TO_ZAHYO((*it).x-5)+X_NUM_TO_ZAHYO((*it).x-4))/2.0,256.0*0.8/2.0+256.0*0.8*i,1,45);
				}
				(*it).x = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
				(*it).y = (*it).f_hanyou[0]-960.0-128.0-64*0.5;
			}
			if(c<240){
				SShake(0,10.0*(float)c/240.0);
				(*it).i_hanyou[0] = 255.0*(float)c/240.0;
			}
			if(c<180){
				(*it).large = 1.7;
				(*it).y += 5.0;
			}
			else if(c<240){
				(*it).i_hanyou[0] = 255;
				(*it).y += 0.5;
				(*it).flash += 2;
			}
			else if(c==240){
				play_sound(21);
				EfMake((*it).x,(*it).f_hanyou[0],5,47);
				shake_x = 0;
				shake_y = 0;
				if(Para.time_count<3600){
					EMake(X_ZAHYO_TO_NUM((*it).x), Y_ZAHYO_TO_NUM((*it).f_hanyou[0]), (*it).player, 12, 1, (*it).player);
				}
				else{
					for(int i=0;i<11;i++){
						int num = X_ZAHYO_TO_NUM((*it).x)-5+i;
						if(0<num&&num<LARGE_X&&Map.field[num][Y_ZAHYO_TO_NUM((*it).f_hanyou[0])]!=1)	EMake(num,Y_ZAHYO_TO_NUM((*it).f_hanyou[0]),(*it).player,5,-1,(*it).player);//タテだけ
					}
					for(int i=0;i<11;i++){
						int num = Y_ZAHYO_TO_NUM((*it).f_hanyou[0])-5+i;
						if(0<num&&num<LARGE_Y&&Map.field[X_ZAHYO_TO_NUM((*it).x)][num]!=1)	EMake(X_ZAHYO_TO_NUM((*it).x),num,(*it).player,5,-2,(*it).player);//ヨコだけ
					}
				}
				Player[(*it).player].spell_level = 1;
				if(Player[(*it).player].gage_per>1) Player[(*it).player].gage_per--;
				(*it).bDelete = true;
			}
		}
	}
	(*it).count++;

	return;
}

int SpAtari(list<SPELLDATA>::iterator &it, bool bDeath){
//戻り値はビット状態によって判断
	int value = 0;
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
	int c = (*it).count;

	if((*it).type==0||(*it).type==7||(*it).type==8||(*it).type==9){//0:マスタースパーク 7:アサシンスパーク 8.9:ファイナルスパーク 
		if((c>=90&&c<210)||(*it).type==7){
			float haba = (*it).haba - 1.2*(X_NUM_TO_ZAHYO(1) - X_NUM_TO_ZAHYO(0));
			for(int i=0;i<PLAYER_NUM;i++){
				if(i!=(*it).player&&Player[i].get_condition()==0){
					float x,y;
					Player[i].get_xy(&x,&y);
					bool out = false;
					if((*it).type<8){
						if((*it).i_hanyou[0]==0){
							if((*it).f_hanyou[1]<y&&y<(*it).y&&(*it).x-haba/2.0<x&&x<(*it).x+haba/2.0)	out = true;
						}
						else if((*it).i_hanyou[0]==1){
							if((*it).x<x&&x<(*it).f_hanyou[2]&&(*it).y-haba/2.0<y&&y<(*it).y+haba/2.0)	out = true;
						}
						else if((*it).i_hanyou[0]==2){
							if((*it).y<y&&y<(*it).f_hanyou[1]&&(*it).x-haba/2.0<x&&x<(*it).x+haba/2.0)	out = true;
						}
						else if((*it).i_hanyou[0]==3){
							if((*it).f_hanyou[0]<x&&x<(*it).x&&(*it).y-haba/2.0<y&&y<(*it).y+haba/2.0)	out = true;
						}
					}
					else{
						float angle;
						if((*it).i_hanyou[0]==0){
							if((*it).type==8)	angle = Radian(-70,TRUE);
							else			angle = Radian(250,TRUE);
						}
						else if((*it).i_hanyou[0]==1){
							if((*it).type==8)	angle = Radian(-20,TRUE);
							else			angle = Radian(20,TRUE);
						}
						else if((*it).i_hanyou[0]==2){
							if((*it).type==8)	angle = Radian(110,TRUE);
							else			angle = Radian(70,TRUE);
						}
						else if((*it).i_hanyou[0]==3){
							if((*it).type==8)	angle = Radian(160,TRUE);
							else			angle = Radian(200,TRUE);
						}
						float d = fabs(tan(angle)*x-y+(*it).y-tan(angle)*(*it).x) / sqrt(tan(angle)*tan(angle)+1);
						if(d<haba/2.0){
							if((*it).f_hanyou[0]<(*it).x&&x<(*it).x-30*cos(angle))	out = true;
							if((*it).f_hanyou[0]>(*it).x&&x>(*it).x+30*cos(angle))	out = true;
						}
					}
					if(out==true&&bDeath==true){
						Player[(*it).player].level_plus();
						Player[i].change_condition(1,4);
						if(usernum>=2){
							if(Player[i].get_condition()==1&&Player[(*it).player].bMan==true&&SAVE.User[(*it).player]!=-1&&!(bOnline==true&&(*it).player!=NetWork.NFD[0].player_num)){
								if((*it).player==i)	Profile[SAVE.User[(*it).player]].killme_num++;
								else			Profile[SAVE.User[(*it).player]].kill_num++;
							}
						}
					}
					else if(out==true&&bDeath==false){
						if(i==0)	value += 1;
						if(i==1)	value += 2;
						if(i==2)	value += 4;
						if(i==3)	value += 8;
					}
				}
			}
		}
	}
	else if((*it).type==16||(*it).type==17||(*it).type==18){//16:妖童餓鬼の断食 17:二百由旬の一閃 18:業風神閃斬 
		if(c>=60&&c<95){
			for(int i=0;i<PLAYER_NUM;i++){
				if(i!=(*it).player&&Player[i].get_condition()==0){
					float x,y;
					Player[i].get_xy(&x,&y);
					bool out = false;
					if((*it).i_hanyou[0]==0){
						if((*it).f_hanyou[1]<y&&y<(*it).y&&(*it).x-(*it).f_hanyou[2]*3<x&&x<(*it).x+(*it).f_hanyou[2]*3)	out = true;
					}
					else if((*it).i_hanyou[0]==1){
						if((*it).x<x&&x<(*it).f_hanyou[0]&&(*it).y-(*it).f_hanyou[2]*3<y&&y<(*it).y+(*it).f_hanyou[2]*3)	out = true;
					}
					else if((*it).i_hanyou[0]==2){
						if((*it).y<y&&y<(*it).f_hanyou[1]&&(*it).x-(*it).f_hanyou[2]*3<x&&x<(*it).x+(*it).f_hanyou[2]*3)	out = true;
					}
					else if((*it).i_hanyou[0]==3){
						if((*it).f_hanyou[0]<x&&x<(*it).x&&(*it).y-(*it).f_hanyou[2]*3<y&&y<(*it).y+(*it).f_hanyou[2]*3)	out = true;
					}
					if(out==true&&bDeath==true){
						Player[(*it).player].level_plus();
						Player[i].change_condition(1,3);
						if(usernum>=2){
							if(Player[i].get_condition()==1&&Player[(*it).player].bMan==true&&SAVE.User[(*it).player]!=-1&&!(bOnline==true&&(*it).player!=NetWork.NFD[0].player_num)){
								if((*it).player==i)	Profile[SAVE.User[(*it).player]].killme_num++;
								else			Profile[SAVE.User[(*it).player]].kill_num++;
							}
						}
					}
					else if(out==true&&bDeath==false){
						if(i==0)	value += 1;
						if(i==1)	value += 2;
						if(i==2)	value += 4;
						if(i==3)	value += 8;
					}
				}
			}
		}
	}
	else if((*it).type==29){//29:のびーるアーム
		if(c>=20&&c<210){
			float haba = 10;
			for(int i=0;i<PLAYER_NUM;i++){
				if(i!=(*it).player&&Player[i].get_condition()==0){
					float px,py,x[2],y[2];
					Player[i].get_xy(&px,&py);
					x[0] = (*it).x-(*it).f_hanyou[0];
					x[1] = (*it).x+(*it).f_hanyou[1];
					y[0] = (*it).y-(*it).f_hanyou[2];
					y[1] = (*it).y+(*it).f_hanyou[3];
					if(x[0]<px&&px<x[1]&&(*it).y-haba<py&&py<(*it).y+haba || y[0]<py&&py<y[1]&&(*it).x-haba<px&&px<(*it).x+haba){
						if(bDeath==true){
							Player[(*it).player].level_plus();
							Player[i].change_condition(1,3);
							if(usernum>=2){
								if(Player[i].get_condition()==1&&Player[(*it).player].bMan==true&&SAVE.User[(*it).player]!=-1&&!(bOnline==true&&(*it).player!=NetWork.NFD[0].player_num)){
									if((*it).player==i)	Profile[SAVE.User[(*it).player]].killme_num++;
									else			Profile[SAVE.User[(*it).player]].kill_num++;
								}
							}
						}
						else if(bDeath==false){
							if(i==0)	value += 1;
							if(i==1)	value += 2;
							if(i==2)	value += 4;
							if(i==3)	value += 8;
						}
					}
				}
			}
		}
	}
	else if((*it).type==35){//35:ギガフレア
		for(int i=0;i<PLAYER_NUM;i++){
			if(i!=(*it).player&&Player[i].get_condition()==0){
				float px,py;
				Player[i].get_xy(&px,&py);
				float sx = px - (*it).x;
				float sy = py - (*it).y;
				float d = sqrt(sx*sx+sy*sy);
				if(d<(*it).large*128.0){
					if(bDeath==true){
						Player[(*it).player].level_plus();
						Player[i].change_condition(1,99);
						if(usernum>=2){
							if(Player[i].get_condition()==1&&Player[(*it).player].bMan==true&&SAVE.User[(*it).player]!=-1&&!(bOnline==true&&(*it).player!=NetWork.NFD[0].player_num)){
								if((*it).player==i)	Profile[SAVE.User[(*it).player]].killme_num++;
								else			Profile[SAVE.User[(*it).player]].kill_num++;
							}
						}
					}
					else if(bDeath==false){
						if(i==0)	value += 1;
						if(i==1)	value += 2;
						if(i==2)	value += 4;
						if(i==3)	value += 8;
					}
				}
			}
		}
	}


	return value;
}
