#include "bomb.h"
#include "item.h"
#include "map.h"
#include "para.h"
#include "player.h"

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

void BMake(int x,int y,int type,int power,int img,int pattern){
	if(pattern!=12)	Player[type].bomb_num++;
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
		BMove(it);
		if((*it).bExplosion==true){
			if((*it).pattern==10){
				Player[(*it).type].hit_plus(-1);
			}
			if((*it).pattern==12)	EMake((*it).x,(*it).y,0,(*it).power,(*it).pattern,-1);
			else			EMake((*it).x,(*it).y,(*it).type,(*it).power,(*it).pattern,(*it).who);
			it = Bomb.erase(it);
			it--;
			continue;			
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if(repeat==9){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if((*it).pattern==10||(*it).pattern==12||((*it).pattern==11&&(*it).i_hanyou[0]==0))	DrawOval((*it).fx/*X_NUM_TO_ZAHYO((*it).x)+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0*/, Y_NUM_TO_ZAHYO((*it).y)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-3.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-10.0, GetColor(0,0,0),TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			DrawRotaGraphF((*it).fx+shake_x,(*it).fy+shake_y,(*it).large,(*it).angle,(*it).img,TRUE);
		}
	}

	return;
}

void BMove(list<BOMBDATA>::iterator &it){
	if(bTimeStop==true)	return;
	(*it).large = 1.0 + fabs(0.9-0.18*(float)((*it).count/5%10));
	if((*it).count==180 || Map.field[(*it).x][(*it).y]<=-3){
		(*it).bExplosion = true;
		(*it).who = Map.field[(*it).x][(*it).y]+3;
        }
	if((*it).pattern==1 || ((*it).pattern>=2&&(*it).pattern<=5)){
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
	if((*it).pattern>=2&&(*it).pattern<=5){//夢想封印
		if(Player[(*it).pattern-2].get_condition()==0&&(*it).pattern-2!=(*it).type){
			float x,y;
			Player[(*it).pattern-2].get_xy(&x,&y);
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
			(*it).speed = 2.0;
		}
		else{
			(*it).pattern = ((*it).pattern-2+1)%4+2;
			if((*it).pattern-2==(*it).type){
				(*it).pattern = ((*it).pattern-2+1)%4+2;
			}
		}
	}
	else if((*it).pattern>=6&&(*it).pattern<=9){//ジャック・ザ・リッパー
		if((*it).count==0)	(*it).direction = (*it).pattern-6;
	}
	else if((*it).pattern==10){//全世界ナイトメア
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
			if((*it).pattern<2||(*it).pattern>5)	(*it).direction = -1;
			(*it).fx = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
			(*it).fy = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
			//(*it).x = X_ZAHYO_TO_NUM((*it).fx);
			//(*it).y = Y_ZAHYO_TO_NUM((*it).fy);
			//Map.field[(*it).x][(*it).y] = -2;
		}
	}
	(*it).count++;
		
	return;
}

void EMake(int x,int y,int type,int power,int pattern,int who){
	if(pattern!=12)	Player[type].hit_plus();
	if(pattern!=10&&type!=who&&pattern!=12&&who!=-1){
		Player[type].hit_plus(Player[who+3].get_hit());
	}
	change_volume_sound(50.0*(float)SAVE.Sound/100.0+205.0*(float)power/9.0);
	play_sound_pan(4,0/*31.25*X_NUM_TO_ZAHYO(x)-10000*/);
	change_volume_sound(255.0*SAVE.Sound*0.01);
	EXPDATA P;
	Map.field[x][y] = 0;
	ELength(x,y,power,pattern,&P.x_length[0],&P.x_length[1],&P.y_length[0],&P.y_length[1],true);
 	P.type = type;
	P.count = 0;
	P.x = x;
	P.y = y;
	P.power = power;
	P.pattern = pattern;
	P.flash = 255;
	
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
				}
			}
		}
		return 0;
	}
	int x_length[2] = {0,0};
	int y_length[2] = {0,0};
	int dest = 0;
	for(int i=1;i<=power;i++){
		if(Map.field[x-i][y]==1){
			break;
		}
		else if(Map.field[x-i][y]>=2){
			if(Map.field[x-i][y]==2)	dest++;
			if(flag==true)	Map.field[x-i][y] = 0;
			if(pattern!=1){
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
		if(Map.field[x+i][y]==1){
			break;
		}
		else if(Map.field[x+i][y]>=2){
			if(Map.field[x+i][y]==2)	dest++;
			if(flag==true)	Map.field[x+i][y] = 0;
			if(pattern!=1){
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
		if(Map.field[x][y-i]==1){
			break;
		}
		else if(Map.field[x][y-i]>=2){
			if(Map.field[x][y-i]==2)	dest++;
			if(flag==true)	Map.field[x][y-i] = 0;
			if(pattern!=1){
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
		if(Map.field[x][y+i]==1){
			break;
		}
		else if(Map.field[x][y+i]>=2){
			if(Map.field[x][y+i]==2)	dest++;
			if(flag==true)	Map.field[x][y+i] = 0;
			if(pattern!=1){
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
	for(list<EXPDATA>::iterator it=Exp.begin(); it!=Exp.end(); ++it){
		EMove(it);
		if((*it).count==60){
			if((*it).pattern!=12)	Player[(*it).type].bomb_num--;
			it = Exp.erase(it);
			it--;
			continue;			
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if((*it).pattern==1)	SetDrawBlendMode(DX_BLENDMODE_SUB,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if((*it).type==0)	SetDrawBright(255,100,100);
		else if((*it).type==1)	SetDrawBright(100,100,255);
		else if((*it).type==2)	SetDrawBright(100,255,100);
		else if((*it).type==3)	SetDrawBright(255,255,100);
		if((*it).pattern==10)	SetDrawBright(255,50,50);
		if((*it).pattern==12)	SetDrawBright(255,0,255);
		if(Para.time_count<3600){
			float x0 = (float)(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0+X_NUM_TO_ZAHYO((*it).x-(*it).power/2.0);
			float x1 = (float)(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0+X_NUM_TO_ZAHYO((*it).x+(*it).power/2.0);
			float y0 = (float)(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0+Y_NUM_TO_ZAHYO((*it).y-(*it).power/2.0);
			float y1 = (float)(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0+Y_NUM_TO_ZAHYO((*it).y+(*it).power/2.0);
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
	}

	return;
}

void EMove(list<EXPDATA>::iterator &it){
	if(bTimeStop==true)	return;
	(*it).flash = 255.0 * (float)(60-(*it).count)/60.0;
	
	if(Para.time_count<3600){
		if((*it).count>=5&&(*it).count<45){
			for(list<BOMBDATA>::iterator bit=Bomb.begin();bit!=Bomb.end();++bit){
				float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
				float sx = (*bit).fx-X_NUM_TO_ZAHYO((*it).x);
				float sy = (*bit).fy-Y_NUM_TO_ZAHYO((*it).y);
				if(sqrt(sx*sx+sy*sy)<sa*(*it).power){
					(*bit).bExplosion = true;
					(*bit).who = (*it).type;
				}
			}	
			/*
			for(int i=0;i<LARGE_X;i++){
				for(int a=0;a<LARGE_Y;a++){
					float sx = X_NUM_TO_ZAHYO(i);
					float sy = Y_NUM_TO_ZAHYO(a);
					float ssx = sx - X_NUM_TO_ZAHYO((*it).x);
					float ssy = sy - Y_NUM_TO_ZAHYO((*it).y);
					float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
					if(sqrt(ssx*ssx+ssy*ssy)<sa*(*it).power){
						if(Map.field[i][a]==-2)	Map.field[i][a] = -3-(*it).type;
					}
				}
			}
			*/
		}
		if((*it).count<45){
			for(int i=0;i<PLAYER_NUM;i++){
				if((*it).pattern==10&&Player[i].get_chara()==REMILIA)	continue;
				if(Player[i].get_condition()==0){
					float px,py;
					Player[i].get_xy(&px,&py);
					float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
					float sx = px - (X_NUM_TO_ZAHYO((*it).x)+sa);
					float sy = py - (Y_NUM_TO_ZAHYO((*it).y)+sa);
					if(sqrt(sx*sx+sy*sy)<sa*(*it).power){
						Player[i].change_condition(1);
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
				}
			}	
			/*
			for(int i=0;i<=(*it).x_length[0];i++){
				if(Map.field[(*it).x-i][(*it).y]==-2)	Map.field[(*it).x-i][(*it).y] = -3-(*it).type;
			}
			for(int i=1;i<=(*it).x_length[1];i++){
				if(Map.field[(*it).x+i][(*it).y]==-2)	Map.field[(*it).x+i][(*it).y] = -3-(*it).type;
			}
			for(int i=1;i<=(*it).y_length[0];i++){
				if(Map.field[(*it).x][(*it).y-i]==-2)	Map.field[(*it).x][(*it).y-i] = -3-(*it).type;
			}
			for(int i=1;i<=(*it).y_length[1];i++){
				if(Map.field[(*it).x][(*it).y+i]==-2)	Map.field[(*it).x][(*it).y+i] = -3-(*it).type;
			}
			*/
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
				if((*it).pattern==10&&Player[i].get_chara()==REMILIA)	continue;
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
							Player[(*it).type].d_hanyou[2] = px;
							Player[(*it).type].d_hanyou[3] = py;
						}
					}
				}
			}	
		}
	}
	(*it).count++;
	
	return;
}
