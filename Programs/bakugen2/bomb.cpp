#include "bomb.h"
#include "item.h"
#include "map.h"
#include "para.h"
#include "player.h"
#include "menu.h"
#include "net.h"

list<BOMBDATA> Bomb;
list<EXPDATA> Exp;

void BLoad();
void BMake(int x,int y,int type,int power,int img);
void BDraw();
void BMove(list<BOMBDATA>::iterator &it);
void EMake(int x,int y,int type,int power,int pattern);
int ELength(int x,int y,int power,int pattern,int *x_lengthA,int *x_lengthB,int *y_lengthA,int *y_lengthB);
void EDraw();
void EMove(list<EXPDATA>::iterator &it);


void BLoad(){
	Bomb.clear();
	Exp.clear();

	return;
}

void BMake(int x,int y,int type,int power,int img,int pattern, int timer, bool renbaku){
	Map.field[x][y] = -2;
	BOMBDATA P;
	P.large = 1.0;
	P.angle = 0;
	P.img = gBomb[img][type];
	P.count = 0;
	P.flash = 255;
	P.fx = (X_NUM_TO_ZAHYO(x)+X_NUM_TO_ZAHYO(x+1))/2.0;
	P.fy = (Y_NUM_TO_ZAHYO(y)+Y_NUM_TO_ZAHYO(y+1))/2.0;
	P.x = x;
	P.y = y;
	P.power = power;
	P.type = type;
	P.pattern = pattern;
	P.direction = -1;
	P.bExplosion = false;
	P.bDelete = false;
	P.bYukari = false;
	P.timer = timer;
	if(bYukari==true&&bAICheck==false){
		P.timer = 20+get_rand(100);
		P.bYukari = true;
	}
	P.bRenbaku = renbaku;
	P.who = type;
	P.speed = 4.0;
	for(int i=0;i<8;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	
	Bomb.push_back(P);

	return;
}

void BDraw(){
	for(list<BOMBDATA>::iterator it=Bomb.begin(); it!=Bomb.end(); ++it){
		if((*it).bExplosion==false||(*it).pattern==11||(*it).pattern==10||(*it).pattern==21||(*it).pattern==12)	BMove(it);
		if((*it).pattern!=10&&(*it).pattern!=21&&(*it).pattern!=12&&((*it).pattern<22||(*it).pattern>25)&&(*it).pattern!=28&&((*it).pattern<28||(*it).pattern>32)){
			if(!((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20)){
				Player[(*it).type].bomb_num++;
			}
		}
		if((*it).bDelete==true){
			it = Bomb.erase(it);
			it--;
			continue;			
		}
		if((*it).bExplosion==true){
			Map.field[(*it).x][(*it).y] = 0;
			if((*it).pattern==10||(*it).pattern==21){
				Player[(*it).type].hit_plus(-1);
			}
			if((*it).pattern==-1){//495年の波紋
				for(int i=0;i<5;i++){
					int num = (*it).x-2+i;
					if(0<num&&num<LARGE_X&&Map.field[num][(*it).y]!=1)	EMake(num,(*it).y,(*it).type,2,-1,(*it).who);//タテだけ
				}
				for(int i=0;i<5;i++){
					int num = (*it).y-2+i;
					if(0<num&&num<LARGE_Y&&Map.field[(*it).x][num]!=1)	EMake((*it).x,num,(*it).type,2,-2,(*it).who);//ヨコだけ
				}
			}
			else if((*it).pattern==12)	EMake((*it).x,(*it).y,0,(*it).power,(*it).pattern,-1,(*it).bRenbaku);
			else				EMake((*it).x,(*it).y,(*it).type,(*it).power,(*it).pattern,(*it).who,(*it).bRenbaku);
			it = Bomb.erase(it);
			it--;
			continue;			
		}
		else{
			//AI用
			int dummy[4];
			ELength((*it).x,(*it).y,(*it).power,(*it).pattern,&dummy[0],&dummy[1],&dummy[2],&dummy[3],false);		
			for(int i=0;i<PLAYER_NUM;i++){
				if(Player[i].get_condition()==0){
					bool flag = true;
					if((((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20))&&(Player[i].get_chara()==REIMU||(*it).type==i))	flag = false;
					else if(((*it).pattern==10||(*it).pattern==21)&&(Player[i].get_chara()==REMILIA||(*it).type==i))	flag = false;
					else if(((*it).pattern==26||(*it).pattern==27||(*it).pattern==33||(*it).pattern==34)&&(Player[i].get_chara()==NITORI||(*it).type==i))	flag = false;
					else if(((*it).pattern==28||((*it).pattern>=29&&(*it).pattern<=32))&&(Player[i].get_chara()==SANAE||(*it).type==i))	flag = false;
					else if((*it).pattern>=22&&(*it).pattern<=25&&(Player[i].get_chara()==REISEN||(*it).type==i))	flag = false;
					if(flag==true){
						
					}
					else{
						//Player[i].
					}
				}
			}
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if(repeat==9){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if((*it).pattern==10||(*it).pattern==12||((*it).pattern==11&&(*it).i_hanyou[0]==0))	DrawOval((*it).fx, Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-3.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-10.0, GetColor(0,0,0),TRUE);
			else if((*it).pattern==21)	DrawOval((*it).fx, (*it).f_hanyou[5], (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-3.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-10.0, GetColor(0,0,0),TRUE);	
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			DrawRotaGraphF((*it).fx+shake_x,(*it).fy+shake_y,(*it).large,(*it).angle,(*it).img,TRUE);
			if((*it).bYukari==true){
				DrawRotaGraphF((*it).fx+shake_x,(*it).fy+shake_y,0.15*(*it).large,0,gEffect[4],TRUE);
			}
		}
	}

	return;
}

void BMove(list<BOMBDATA>::iterator &it){
	if(bTimeStop==true)	return;
	(*it).large = 1.0 + fabs(0.9-0.18*(float)((*it).count/5%10));
	if((*it).count==(*it).timer || (*it).count==180 || Map.field[(*it).x][(*it).y]<=-3){
		(*it).bExplosion = true;
		//(*it).who = Map.field[(*it).x][(*it).y]+3;
        }
	if(((*it).pattern>=28&&(*it).pattern<=32) || (*it).pattern==1 || ((*it).pattern>=2&&(*it).pattern<=5) || ((*it).pattern>=13&&(*it).pattern<=16) || ((*it).pattern>=17&&(*it).pattern<=20)){
		(*it).angle -= Radian(6,TRUE);
	}
	if(bSecondSun==true){//CORE OF THE 2ND SUN  
		float x = (X_NUM_TO_ZAHYO(9)+X_NUM_TO_ZAHYO(10))/2.0;
		float y = (Y_NUM_TO_ZAHYO(6)+Y_NUM_TO_ZAHYO(7))/2.0;
		if(fabs((*it).f_hanyou[0]-(*it).fx)<0.1&&fabs((*it).f_hanyou[1]-(*it).fy)<0.1)	(*it).i_hanyou[0] = ((*it).i_hanyou[0]+1)%2;
		if(X_ZAHYO_TO_NUM(x)==(*it).x&&X_ZAHYO_TO_NUM(x)==X_ZAHYO_TO_NUM((*it).fx-14)&&X_ZAHYO_TO_NUM(x)==X_ZAHYO_TO_NUM((*it).fx+14)){
			if((*it).i_hanyou[0]==0){
				(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
				(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;	
				(*it).i_hanyou[0] = 1;
			}
		}
		if(Y_ZAHYO_TO_NUM(y)==(*it).y&&Y_ZAHYO_TO_NUM(y)==Y_ZAHYO_TO_NUM((*it).fy-14)&&Y_ZAHYO_TO_NUM(y)==Y_ZAHYO_TO_NUM((*it).fy+14)){
			if((*it).i_hanyou[0]==1){
				(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
				(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;	
				(*it).i_hanyou[0] = 0;
			}
		}
		if((*it).i_hanyou[0]==0){
			if(X_ZAHYO_TO_NUM(x)<(*it).x)	(*it).direction = 2;
			if(X_ZAHYO_TO_NUM(x)>(*it).x)	(*it).direction = 3;
		}
		else{
			if(Y_ZAHYO_TO_NUM(y)<(*it).y)	(*it).direction = 0;
			if(Y_ZAHYO_TO_NUM(y)>(*it).y)	(*it).direction = 1;
		}
		(*it).f_hanyou[0] = (*it).fx;
		(*it).f_hanyou[1] = (*it).fy;
		(*it).speed = 1.0;
	}
	if(((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20)){//夢想封印系統
		float x,y;
		if((*it).pattern>=2&&(*it).pattern<=5){
			if((*it).type==(*it).pattern-2){
				(*it).bDelete = true;
			}
			else if(Player[(*it).pattern-2].get_condition()!=0){
				for(int i=0;i<4;i++){
					int num = ((*it).pattern-2+i)%4;
					if(num!=(*it).type&&Player[num].get_condition()==0){
						(*it).pattern = num + 2;
						return;
					}
				}
			}
			Player[(*it).pattern-2].get_xy(&x,&y);
		}
		if((*it).pattern>=13&&(*it).pattern<=16){
			if((*it).type==(*it).pattern-13){
				(*it).bDelete = true;
			}
			else if(Player[(*it).pattern-13].get_condition()!=0){
				for(int i=0;i<4;i++){
					int num = ((*it).pattern-13+i)%4;
					if(num!=(*it).type&&Player[num].get_condition()==0){
						(*it).pattern = num + 13;
						return;
					}
				}
			}
			Player[(*it).pattern-13].get_xy(&x,&y);
		}
		if((*it).pattern>=17&&(*it).pattern<=20){
			if((*it).type==(*it).pattern-17){
				(*it).bDelete = true;
			}
			else if(Player[(*it).pattern-17].get_condition()!=0){
				for(int i=0;i<4;i++){
					int num = ((*it).pattern-17+i)%4;
					if(num!=(*it).type&&Player[num].get_condition()==0){
						(*it).pattern = num + 17;
						return;
					}
				}
			}
			Player[(*it).pattern-17].get_xy(&x,&y);
		}
		if(fabs((*it).f_hanyou[0]-(*it).fx)<0.1&&fabs((*it).f_hanyou[1]-(*it).fy)<0.1)	(*it).i_hanyou[0] = ((*it).i_hanyou[0]+1)%2;
		if(X_ZAHYO_TO_NUM(x)==(*it).x&&X_ZAHYO_TO_NUM(x)==X_ZAHYO_TO_NUM((*it).fx-14)&&X_ZAHYO_TO_NUM(x)==X_ZAHYO_TO_NUM((*it).fx+14)){
			if((*it).i_hanyou[0]==0){
				(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
				(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;	
				(*it).i_hanyou[0] = 1;
			}
		}
		if(Y_ZAHYO_TO_NUM(y)==(*it).y&&Y_ZAHYO_TO_NUM(y)==Y_ZAHYO_TO_NUM((*it).fy-14)&&Y_ZAHYO_TO_NUM(y)==Y_ZAHYO_TO_NUM((*it).fy+14)){
			if((*it).i_hanyou[0]==1){
				(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
				(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;	
				(*it).i_hanyou[0] = 0;
			}
		}
		if((*it).i_hanyou[0]==0){
			if(X_ZAHYO_TO_NUM(x)<(*it).x)	(*it).direction = 2;
			if(X_ZAHYO_TO_NUM(x)>(*it).x)	(*it).direction = 3;
		}
		else{
			if(Y_ZAHYO_TO_NUM(y)<(*it).y)	(*it).direction = 0;
			if(Y_ZAHYO_TO_NUM(y)>(*it).y)	(*it).direction = 1;
		}
		(*it).f_hanyou[0] = (*it).fx;
		(*it).f_hanyou[1] = (*it).fy;
		if((*it).pattern>=2&&(*it).pattern<=5)	(*it).speed = 2.0;
		if((*it).pattern>=13&&(*it).pattern<=16)(*it).speed = 2.5;
		if((*it).pattern>=17&&(*it).pattern<=20)(*it).speed = 3.0;
	}
	else if((*it).pattern>=6&&(*it).pattern<=9){//ジャック・ザ・リッパー
		if((*it).count==0)	(*it).direction = (*it).pattern-6;
	}
	else if((*it).pattern==10||(*it).pattern==21){//全世界ナイトメア系統
		(*it).bExplosion = false;
		(*it).direction = -2;
		Map.field[(*it).x][(*it).y] = 0;
		if((*it).pattern==21&&(*it).count==0){
			(*it).f_hanyou[3] = 0;
			for(int j=0;j<10;j++){
				(*it).i_hanyou[6] = get_rand(3);
				if((*it).i_hanyou[6]==0){
					if(Map.field[(*it).x][(*it).y-1]==0||Map.field[(*it).x][(*it).y-1]==3)	break;
					else	(*it).i_hanyou[6] = -2;
				}
				if((*it).i_hanyou[6]==1){
					if(Map.field[(*it).x+1][(*it).y]==0||Map.field[(*it).x+1][(*it).y]==3)	break;
					else	(*it).i_hanyou[6] = -2;
				}
				if((*it).i_hanyou[6]==2){
					if(Map.field[(*it).x][(*it).y+1]==0||Map.field[(*it).x][(*it).y+1]==3)	break;
					else	(*it).i_hanyou[6] = -2;
				}
				if((*it).i_hanyou[6]==3){
					if(Map.field[(*it).x-1][(*it).y]==0||Map.field[(*it).x-1][(*it).y]==3)	break;
					else	(*it).i_hanyou[6] = -2;
				}
			}
			(*it).f_hanyou[5] = Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0;
			if((*it).i_hanyou[6]==0)	(*it).f_hanyou[3] = -(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0)+1);
			if((*it).i_hanyou[6]==1)	(*it).f_hanyou[3] = X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0)+1;
			if((*it).i_hanyou[6]==2)	(*it).f_hanyou[3] = Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0)+1;
			if((*it).i_hanyou[6]==3)	(*it).f_hanyou[3] = -(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0)+1);
		} 
		if((*it).count<60){
			if((*it).pattern==10)	(*it).fy = Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0-9*(60-(*it).count);
			else{
				if((*it).i_hanyou[6]==0||(*it).i_hanyou[6]==2)	(*it).f_hanyou[5] += (*it).f_hanyou[3]/60.0;
				else	(*it).fx += (*it).f_hanyou[3]/60.0;
				(*it).fy = (*it).f_hanyou[5]-9*(60-(*it).count);
				(*it).x = X_ZAHYO_TO_NUM((*it).fx);
				(*it).y = Y_ZAHYO_TO_NUM((*it).f_hanyou[5]);
			}
		}
		else{
			(*it).bExplosion = true;
		}
	}
	else if((*it).pattern==11){//みそボン
		if((*it).count<10){
			(*it).direction = -2;
			(*it).fy = Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0-9*(10-(*it).count);
			(*it).bExplosion = false;
		}
		else if((*it).count==10){
			(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
			(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
			(*it).direction = -1;		
			Map.field[(*it).x][(*it).y] = -2;
		}
		else{
			(*it).i_hanyou[0] = 1;
		}
	}
	else if((*it).pattern==12){//ランドマインランド
		(*it).flash = 0;
		(*it).bExplosion = false;
		(*it).direction = -2;
		Map.field[(*it).x][(*it).y] = 0; 
		if((*it).count<60){
			(*it).fy = Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0-9*(60-(*it).count);
		}
		else{
			(*it).bExplosion = true;
			//Map.field[(*it).x][(*it).y] = -2; 
		}
	}
	else if((*it).pattern>=22&&(*it).pattern<=25){//月兎爆誕（ルナファントム）
		if((*it).count==0)	(*it).direction = -1;
		(*it).flash = Player[(*it).pattern-22].illusion_flash;
		if((*it).flash==0){
			Map.field[(*it).x][(*it).y] = 0;
			(*it).bDelete = true;
		}
		//(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
		//(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
		//Map.field[(*it).x][(*it).y] = 0;
	}
	else if((*it).pattern==26||(*it).pattern==27||(*it).pattern==33||(*it).pattern==34){//スピン・ザ・ボンバー
		if((*it).count==0){
			if((*it).pattern==26)				(*it).direction = 0;
			else if((*it).pattern==27)			(*it).direction = 2;
			else if((*it).pattern==33)			(*it).direction = 1;
			else if((*it).pattern==34)			(*it).direction = 3;
		}
		(*it).speed = 6.0;
		if((*it).direction==-1){
			if((*it).i_hanyou[0]==0)	(*it).direction = 1;	 	
			if((*it).i_hanyou[0]==1)	(*it).direction = 0;	 	
			if((*it).i_hanyou[0]==2)	(*it).direction = 3;	 	
			if((*it).i_hanyou[0]==3)	(*it).direction = 2;	 	
		}
		(*it).i_hanyou[0] = (*it).direction;
		if((*it).x!=(*it).i_hanyou[1]||(*it).y!=(*it).i_hanyou[2]){
			if((*it).direction==0&&(Map.field[(*it).x+1][(*it).y]==0||Map.field[(*it).x+1][(*it).y]==3))	(*it).direction = 3;
			else if((*it).direction==1&&(Map.field[(*it).x-1][(*it).y]==0||Map.field[(*it).x-1][(*it).y]==3))	(*it).direction = 2;
			else if((*it).direction==2&&(Map.field[(*it).x][(*it).y-1]==0||Map.field[(*it).x][(*it).y-1]==3))	(*it).direction = 0;
			else if((*it).direction==3&&(Map.field[(*it).x][(*it).y+1]==0||Map.field[(*it).x][(*it).y+1]==3))	(*it).direction = 1;
		}
		(*it).i_hanyou[1] = (*it).x;
		(*it).i_hanyou[2] = (*it).y;
	}
	else if((*it).pattern==28){//サモンタケミナカタ
		
	}
	else if((*it).pattern>=29&&(*it).pattern<=32){//ミラクルフルーツ
		if((*it).count==0){
			(*it).direction = (*it).pattern-29;
		}
		if((*it).direction==-1&&(*it).i_hanyou[1]==0){
			if((*it).pattern==29){
				 if(Map.field[(*it).x-1][(*it).y]==0||Map.field[(*it).x-1][(*it).y]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 31, 180-(*it).count);
				 if(Map.field[(*it).x+1][(*it).y]==0||Map.field[(*it).x+1][(*it).y]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 32, 180-(*it).count);
			}
			else if((*it).pattern==30){
				 if(Map.field[(*it).x-1][(*it).y]==0||Map.field[(*it).x-1][(*it).y]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 31, 180-(*it).count);
				 if(Map.field[(*it).x+1][(*it).y]==0||Map.field[(*it).x+1][(*it).y]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 32, 180-(*it).count);
			}
			else if((*it).pattern==31){
				 if(Map.field[(*it).x][(*it).y-1]==0||Map.field[(*it).x][(*it).y-1]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 29, 180-(*it).count);
				 if(Map.field[(*it).x][(*it).y+1]==0||Map.field[(*it).x][(*it).y+1]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 30, 180-(*it).count);
			}
			else if((*it).pattern==32){
				 if(Map.field[(*it).x][(*it).y-1]==0||Map.field[(*it).x][(*it).y-1]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 29, 180-(*it).count);
				 if(Map.field[(*it).x][(*it).y+1]==0||Map.field[(*it).x][(*it).y+1]==3)	BMake((*it).x, (*it).y, (*it).type, (*it).power, 2, 30, 180-(*it).count);
			}
			(*it).i_hanyou[1] = 1;
		}
	}
	//パターン34まで使ってるよん
	
	int *check,cx,cy;
	if((*it).direction!=-1){
		Map.field[(*it).x][(*it).y] = 0;
	}
	if((*it).direction==-1){
		(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
		(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
		(*it).speed = 4.0;	
	}
	else if((*it).direction==0){
		(*it).fy -= (*it).speed;
		(*it).y = Y_ZAHYO_TO_NUM((*it).fy);
		cx = (*it).x;
		cy = Y_ZAHYO_TO_NUM((*it).fy-(float)(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0);
		check = &Map.field[cx][cy];
	}
	else if((*it).direction==1){
		(*it).fy += (*it).speed;
		(*it).y = Y_ZAHYO_TO_NUM((*it).fy);
		cx = (*it).x;
		cy = Y_ZAHYO_TO_NUM((*it).fy+(float)(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0);
		check = &Map.field[cx][cy];
	}
	else if((*it).direction==2){
		(*it).fx -= (*it).speed;
		(*it).x = X_ZAHYO_TO_NUM((*it).fx);
		cx = X_ZAHYO_TO_NUM((*it).fx-(float)(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0);
		cy = (*it).y;
		check = &Map.field[cx][cy];
	}
	else if((*it).direction==3){
		(*it).fx += (*it).speed;
		(*it).x = X_ZAHYO_TO_NUM((*it).fx);
		cx = X_ZAHYO_TO_NUM((*it).fx+(float)(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0);
		cy = (*it).y;
		check = &Map.field[cx][cy];
	}
	if((*it).direction>-1){
		Map.field[(*it).x][(*it).y] = -2;
		bool flag = false;
		for(int i=0;i<PLAYER_NUM;i++){
			if(Player[i].get_condition()==0){
				float x,y;
				Player[i].get_xy(&x,&y);
				if(X_ZAHYO_TO_NUM(x)==cx&&Y_ZAHYO_TO_NUM(y)==cy){
					flag = true;
					break;
				}
			}
		}
		if((check!=&Map.field[(*it).x][(*it).y]&&*check==-2)||*check==1||*check==2||flag==true){
			if((*it).pattern<2||(*it).pattern>5){
				if(bIceStream==true){
					if((*it).direction==0)		(*it).direction = 1;
					else if((*it).direction==1)	(*it).direction = 0;
					else if((*it).direction==2)	(*it).direction = 3;
					else if((*it).direction==3)	(*it).direction = 2;
				}
				else	(*it).direction = -1;
			}
			(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
			(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
		}
	}
	(*it).count++;
		
	return;
}

void EMake(int x,int y,int type,int power,int pattern,int who,bool renbaku){
	if(renbaku==true&&(pattern<22||pattern>25)&&pattern!=11){
		if(pattern!=12)	Player[type].hit_plus();
		if(pattern!=10&&pattern!=21&&type!=who&&pattern!=12&&who!=-1){
			play_sound(17);
			Player[type].hit_plus(Player[who].get_hit());
			//Player[who].hit_reset();
		}
	}
	change_volume_sound(50.0*(float)SAVE.Sound/100.0+205.0*(float)power/9.0);
	play_sound_pan(4,0/*31.25*X_NUM_TO_ZAHYO(x)-10000*/);
	change_volume_sound(255.0*SAVE.Sound*0.01);
	EXPDATA P;
	Map.field[x][y] = 0;
	if(pattern<22||pattern>25)	ELength(x,y,power,pattern,&P.x_length[0],&P.x_length[1],&P.y_length[0],&P.y_length[1],true);
	else{
		ELength(x,y,power,pattern,&P.x_length[0],&P.x_length[1],&P.y_length[0],&P.y_length[1],false);
 		if(P.x_length[0]>0)	P.x_length[0]--;
 		if(P.x_length[1]>0)	P.x_length[1]--;
 		if(P.y_length[0]>0)	P.y_length[0]--;
 		if(P.y_length[1]>0)	P.y_length[1]--;
	}
	P.type = type;
	P.count = 0;
	P.x = x;
	P.y = y;
	P.power = power;
	P.pattern = pattern;
	P.flash = 255;
	P.now_power = 0.0;
	P.per_power = (float)power / 10.0;
	
	Exp.push_back(P);

	return;
}

int ELength(int x,int y,int power,int pattern,int *x_lengthA,int *x_lengthB,int *y_lengthA,int *y_lengthB,bool flag){
//戻り値:破壊できるブロック数
	if(Para.time_count<3600){
		*x_lengthA = 0;
		*x_lengthB = 0;
		*y_lengthA = 0;
		*y_lengthB = 0;
		if(flag==true){
			for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();++it){
				float ix = X_NUM_TO_ZAHYO((*it).x);
				float iy = Y_NUM_TO_ZAHYO((*it).y);
				float sx = ix - X_NUM_TO_ZAHYO(x);
				float sy = iy - Y_NUM_TO_ZAHYO(y);
				float sa = X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0);
				if(sqrt(sx*sx+sy*sy)<sa*power/2.0){
					Map.field[(*it).x][(*it).y] = 0;
					if((*it).type==10){
						int rand_x,rand_y;
						bool bflag = false;
						for(int i=0;i<50;i++){
							rand_x = get_rand(LARGE_X-1);
							rand_y = get_rand(LARGE_Y-1);
							if(Map.field[rand_x][rand_y]==0){
								bflag = true;
								break;
							}
						}
						if(bflag==true){
							IMake(rand_x, rand_y, 10, true);
							Map.field[rand_x][rand_y] = 3;
						}
					}	
				}
			}
		}
		return 0;
	}
	int x_length[2] = {0,0};
	int y_length[2] = {0,0};
	int dest = 0;
	for(int i=1;i<=power;i++){
		if(pattern==-1)	break;
		if(Map.field[x-i][y]==1){
			if(flag==true&&Map.type==5&&x-i==9&&y==6){
				bTreasure = true;
			}
			break;
		}
		else if(Map.field[x-i][y]>=2){
			if(Map.field[x-i][y]==2)	dest++;
			if(flag==true)	Map.field[x-i][y] = 0;
			if(pattern!=1&&pattern!=-1&&pattern!=-2){
				x_length[0]++;
				break;
			}
		}
		else if(Map.field[x-i][y]==-2){
			x_length[0]++;
			break;
		}
		x_length[0]++;
	}
	for(int i=1;i<=power;i++){
		if(pattern==-1)	break;
		if(Map.field[x+i][y]==1){
			if(flag==true&&Map.type==5&&x+i==9&&y==6){
				bTreasure = true;
			}
			break;
		}
		else if(Map.field[x+i][y]>=2){
			if(Map.field[x+i][y]==2)	dest++;
			if(flag==true)	Map.field[x+i][y] = 0;
			if(pattern!=1&&pattern!=-1&&pattern!=-2){
				x_length[1]++;
				break;
			}
		}
		else if(Map.field[x+i][y]==-2){
			x_length[1]++;
			break;
		}
		x_length[1]++;
	}
	for(int i=1;i<=power;i++){
		if(pattern==-2)	break;
		if(Map.field[x][y-i]==1){
			if(flag==true&&Map.type==5&&x==9&&y-i==6){
				bTreasure = true;
			}
			break;
		}
		else if(Map.field[x][y-i]>=2){
			if(Map.field[x][y-i]==2)	dest++;
			if(flag==true)	Map.field[x][y-i] = 0;
			if(pattern!=1&&pattern!=-1&&pattern!=-2){
				y_length[0]++;
				break;
			}
		}
		else if(Map.field[x][y-i]==-2){
			y_length[0]++;
			break;
		}
		y_length[0]++;
	}
	for(int i=1;i<=power;i++){
		if(pattern==-2)	break;
		if(Map.field[x][y+i]==1){
			if(flag==true&&Map.type==5&&x==9&&y+i==6){
				bTreasure = true;
			}
			break;
		}
		else if(Map.field[x][y+i]>=2){
			if(Map.field[x][y+i]==2)	dest++;
			if(flag==true)	Map.field[x][y+i] = 0;
			if(pattern!=1&&pattern!=-1&&pattern!=-2){
				y_length[1]++;
				break;
			}
		}
		else if(Map.field[x][y+i]==-2){
			y_length[1]++;
			break;
		}
		y_length[1]++;
	}
	*x_lengthA = x_length[0];
	*x_lengthB = x_length[1];
	*y_lengthA = y_length[0];
	*y_lengthB = y_length[1];

	return dest;
}

void EDraw(){
	for(int i=0;i<4;i++){
		Player[i].bomb_num = 0;
	}
	for(list<EXPDATA>::iterator it=Exp.begin(); it!=Exp.end(); ++it){
		EMove(it);
		if((*it).count==60){
			//if((*it).pattern!=12&&!((*it).pattern>=22&&(*it).pattern<=25))	Player[(*it).type].bomb_num--;
			it = Exp.erase(it);
			it--;
			continue;			
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if((*it).pattern==1||(*it).pattern==-1||(*it).pattern==-2)	SetDrawBlendMode(DX_BLENDMODE_SUB,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if((*it).type==0)	SetDrawBright(255,100,100);
		else if((*it).type==1)	SetDrawBright(100,100,255);
		else if((*it).type==2)	SetDrawBright(100,255,100);
		else if((*it).type==3)	SetDrawBright(255,255,100);
		if((*it).pattern==10||(*it).pattern==21)	SetDrawBright(255,50,50);
		else if((*it).pattern==12)			SetDrawBright(255,0,255);
		else if((*it).pattern==26||(*it).pattern==27||(*it).pattern==33||(*it).pattern==34)	SetDrawBright(0,255,255);
		else if((*it).pattern>=28&&(*it).pattern<=32)	SetDrawBright(0,255,0);
		else if(((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20))	SetDrawBright(0,120,255);	
		if(Para.time_count<3600){
			float x0 = (float)(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0+X_NUM_TO_ZAHYO((*it).x-(*it).now_power/2.0);
			float x1 = (float)(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0+X_NUM_TO_ZAHYO((*it).x+(*it).now_power/2.0);
			float y0 = (float)(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0+Y_NUM_TO_ZAHYO((*it).y-(*it).now_power/2.0);
			float y1 = (float)(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0+Y_NUM_TO_ZAHYO((*it).y+(*it).now_power/2.0);
			for(int i=0;i<3;i++){
				float rand[4];
				for(int a=0;a<4;a++){
					rand[a] = 0.1 * (float)get_rand(100);
					if(bTimeStop==true)	rand[a] = 0;
				}
				if(repeat==9)	DrawExtendGraphF(x0+rand[0],y0+rand[1],x1-rand[2],y1-rand[3],gExplosion,TRUE);
			}
		}
		else{
			float bx0 = X_NUM_TO_ZAHYO((*it).x);
			float bx1 = X_NUM_TO_ZAHYO((*it).x+1);
			float by0 = Y_NUM_TO_ZAHYO((*it).y);
			float by1 = Y_NUM_TO_ZAHYO((*it).y+1);
			float x0 = X_NUM_TO_ZAHYO((*it).x-(*it).x_length[0]);
			float x1 = X_NUM_TO_ZAHYO((*it).x+(*it).x_length[1]+1);
			float y0 = Y_NUM_TO_ZAHYO((*it).y-(*it).y_length[0]);
			float y1 = Y_NUM_TO_ZAHYO((*it).y+(*it).y_length[1]+1);
			if((*it).x_length[0]>0||(*it).x_length[1]>0){
				for(int i=0;i<3;i++){
					float rand[4];
					for(int a=0;a<4;a++){
						rand[a] = 0.1 * (float)get_rand(100);
						if(bTimeStop==true)	rand[a] = 0;
					}
					if(repeat==9)	DrawExtendGraphF(x0+rand[0],by0+rand[1],x1-rand[2],by1-rand[3],gExplosion,TRUE);
				}
			}
			if((*it).y_length[0]>0||(*it).y_length[1]>0){
				for(int i=0;i<3;i++){
					float rand[4];
					for(int a=0;a<4;a++){
						rand[a] = 0.1 * (float)get_rand(100);
						if(bTimeStop==true)	rand[a] = 0;
					}
					if(repeat==9)	DrawExtendGraphF(bx0+rand[0],y0+rand[1],bx1-rand[2],y1-rand[3],gExplosion,TRUE);
				}
			}
		}
		SetDrawBright(255,255,255);
		if((*it).pattern!=10&&(*it).pattern!=21&&(*it).pattern!=12&&((*it).pattern<22||(*it).pattern>25)&&(*it).pattern!=28&&((*it).pattern<28||(*it).pattern>32)){
			if(!((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20)){
				Player[(*it).type].bomb_num++;
			}
		}
	}

	return;
}

void EMove(list<EXPDATA>::iterator &it){
	if(bTimeStop==true)	return;
	(*it).flash = 255.0 * (float)(60-(*it).count)/60.0;
	if((*it).pattern>=22&&(*it).pattern<=25){
		(*it).flash *= (float)Player[(*it).pattern-22].illusion_flash/255.0;
		if(Player[(*it).pattern-22].illusion_flash<255){
			(*it).count++;
			return;
		}
	}
	
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
	if(Para.time_count<3600){
		if((*it).now_power<(*it).power)	(*it).now_power += (*it).per_power;
		if((*it).count>=5&&(*it).count<45){
			for(list<BOMBDATA>::iterator bit=Bomb.begin();bit!=Bomb.end();++bit){
				float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
				float sx = (*bit).fx-X_NUM_TO_ZAHYO((*it).x);
				float sy = (*bit).fy-Y_NUM_TO_ZAHYO((*it).y);
				if(sqrt(sx*sx+sy*sy)<sa*(*it).now_power){
					(*bit).bExplosion = true;
					(*bit).who = (*it).type;
					if((*it).pattern==11)	(*bit).who = -1;
				}
			}	
		}
		if((*it).count<45){
			for(int i=0;i<PLAYER_NUM;i++){
				if((((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20))&&(Player[i].get_chara()==REIMU||(*it).type==i))	continue;
				if(((*it).pattern==10||(*it).pattern==21)&&(Player[i].get_chara()==REMILIA||(*it).type==i))	continue;
				if(((*it).pattern==26||(*it).pattern==27||(*it).pattern==33||(*it).pattern==34)&&(Player[i].get_chara()==NITORI||(*it).type==i))	continue;
				if(((*it).pattern==28||((*it).pattern>=29&&(*it).pattern<=32))&&(Player[i].get_chara()==SANAE||(*it).type==i))	continue;
				if((*it).pattern>=22&&(*it).pattern<=25&&(Player[i].get_chara()==REISEN||(*it).type==i))	continue;
				if(Player[i].get_condition()==0){
					float px,py;
					Player[i].get_xy(&px,&py);
					float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
					float sx = px - (X_NUM_TO_ZAHYO((*it).x)+sa);
					float sy = py - (Y_NUM_TO_ZAHYO((*it).y)+sa);
					float kake = 1.0;
					if(Player[i].large>1.45)	kake = 1.2;
					if(sqrt(sx*sx+sy*sy)<sa*(*it).now_power*kake){
						Player[i].change_condition(1);
						if((*it).pattern!=12&&Player[i].get_condition()==1){
							Player[(*it).type].level_plus();
							if(usernum>=2){
								if(Player[(*it).type].bMan==true&&SAVE.User[(*it).type]!=-1&&!(bOnline==true&&(*it).type!=NetWork.NFD[0].player_num)){
									if((*it).type==i)	Profile[SAVE.User[(*it).type]].killme_num++;
									else			Profile[SAVE.User[(*it).type]].kill_num++;
								}
							}
						}
					}
				}
			}	
		}
	}
	else{
		if((*it).count>=5&&(*it).count<45){
			for(list<BOMBDATA>::iterator bit=Bomb.begin();bit!=Bomb.end();++bit){
				int x = (*bit).x;
				int y = (*bit).y;
				int x0 = (*it).x - (*it).x_length[0];
				int x1 = (*it).x + (*it).x_length[1];
				int y0 = (*it).y - (*it).y_length[0];
				int y1 = (*it).y + (*it).y_length[1];
				if((x0<=x&&x<=x1&&y==(*it).y) || (y0<=y&&y<=y1&&x==(*it).x)){
					(*bit).bExplosion = true;
					(*bit).who = (*it).type;
					if((*it).pattern==11)	(*bit).who = -1;
				}
			}	
		}
		else if((*it).count==45){
			for(list<ITEMDATA>::iterator iit=Item.begin();iit!=Item.end();++iit){
				int x0 = (*it).x - (*it).x_length[0];
				int x1 = (*it).x + (*it).x_length[1];
				int y0 = (*it).y - (*it).y_length[0];
				int y1 = (*it).y + (*it).y_length[1];
				if((x0<=(*iit).x&&(*iit).x<=x1&&(*iit).y==(*it).y) || (y0<=(*iit).y&&(*iit).y<=y1&&(*iit).x==(*it).x)){
					(*iit).bExist = true;
					Map.field[(*iit).x][(*iit).y] = 3;
				}
			}
		}
		if((*it).count<45){
			for(int i=0;i<PLAYER_NUM;i++){
				if((((*it).pattern>=2&&(*it).pattern<=5)||((*it).pattern>=13&&(*it).pattern<=16)||((*it).pattern>=17&&(*it).pattern<=20))&&(Player[i].get_chara()==REIMU||(*it).type==i))	continue;
				if(((*it).pattern==10||(*it).pattern==21)&&(Player[i].get_chara()==REMILIA||(*it).type==i))	continue;
				if(((*it).pattern==26||(*it).pattern==27||(*it).pattern==33||(*it).pattern==34)&&(Player[i].get_chara()==NITORI||(*it).type==i))	continue;
				if(((*it).pattern==28||((*it).pattern>=29&&(*it).pattern<=32))&&(Player[i].get_chara()==SANAE||(*it).type==i))	continue;
				if((*it).pattern>=22&&(*it).pattern<=25&&(Player[i].get_chara()==REISEN||(*it).type==i))	continue;
				if(Player[i].get_condition()==0){
					float px,py;
					Player[i].get_xy(&px,&py);
					int x = X_ZAHYO_TO_NUM(px);
					int y = Y_ZAHYO_TO_NUM(py);
					int x0 = (*it).x - (*it).x_length[0];
					int x1 = (*it).x + (*it).x_length[1];
					int y0 = (*it).y - (*it).y_length[0];
					int y1 = (*it).y + (*it).y_length[1];
					if((x0<=x&&x<=x1&&y==(*it).y) || (y0<=y&&y<=y1&&x==(*it).x)){
						Player[i].change_condition(1);
						if((*it).pattern==11&&Player[(*it).type].get_condition()==2&&Player[i].get_muteki_count()==0){
							Player[(*it).type].change_condition(3);
							Player[(*it).type].reborn[2] = px;
							Player[(*it).type].reborn[3] = py;
							if(usernum>=2){
								if(Player[(*it).type].bMan==true&&SAVE.User[(*it).type]!=-1&&!(bOnline==true&&(*it).type!=NetWork.NFD[0].player_num)){
									Profile[SAVE.User[(*it).type]].miso_kill_num++;
								}
							}
						}
						else{
							if((*it).pattern!=12&&Player[i].get_condition()==1){
								Player[(*it).type].level_plus();
								if(usernum>=2){
									if(Player[(*it).type].bMan==true&&SAVE.User[(*it).type]!=-1&&!(bOnline==true&&(*it).type!=NetWork.NFD[0].player_num)){
										if((*it).type==i)	Profile[SAVE.User[(*it).type]].killme_num++;
										else			Profile[SAVE.User[(*it).type]].kill_num++;
									}
								}
							}
						}
					}
				}
			}	
		}
	}
	(*it).count++;
	
	return;
}
