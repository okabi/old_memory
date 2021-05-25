#include "stg.h"
#include "map.h"
#include "player.h"
#include "net.h"
#include "menu.h"

ENEMYDATA Enemy;
list<SHOTDATA> Shot;

void StMain();
void StLoad();
void EnMake();
void EnDraw();
void EnMove();
void EnShot0();
void EnShot1();
void EnShot2();
void EnShot3();
void EnShot4();
void EnShot5();
void EnShot6();
void ShMake(float x,float y,float angle,float speed,int img,int type,int pattern,int late);
void ShDraw();
void ShMove(list<SHOTDATA>::iterator &it);

void StMain(){
	EnDraw();
	ShDraw();
	

	return;
}

void StLoad(){
	Enemy.bExist = false;
	Shot.clear();

	return;
}

void EnMake(){
	Enemy.bExist = true;
	Enemy.x = CENTER_X;
	Enemy.y = -100;
	Enemy.atari = 20;
	Enemy.large = 1.0;
	Enemy.img = gEnemy;
	Enemy.count = 0;
	Enemy.level = 0;
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()==0)	Enemy.level++;
	}
	for(int i=0;i<4;i++){
		Enemy.f_hanyou[i] = 0;
		Enemy.i_hanyou[i] = 0;
	}
	Enemy.type = get_rand(2);
	Enemy.flash = 255;
	Enemy.bShotend = false;

	return;
}

void EnDraw(){
	if(Enemy.bExist==true){
		EnMove();
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		//SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,Enemy.flash);
		if(repeat==9)	DrawRotaGraphF(Enemy.x+shake_x,Enemy.y+shake_y,Enemy.large,0,Enemy.img,TRUE,FALSE);
	}

	return;
}

void EnMove(){
	if(bTimeStop==true)	return;
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
	int c = Enemy.count;
	if(c==0){
		float x = (CENTER_Y+10) - Enemy.y;
		Enemy.f_hanyou[0] = (-5.0*5.0) / (2.0*x);
		Enemy.f_hanyou[1] = 5.0;
	}
	if(c<180){
		Enemy.y += Enemy.f_hanyou[1];
		Enemy.f_hanyou[1] += Enemy.f_hanyou[0];
	}
	else if(c<240){}
	else{
		if(Enemy.bShotend==true&&Enemy.i_hanyou[0]==120){
			if(Para.time_count<700){
				Enemy.type = ENEMY_PATTERN_MAX;
			}
			else{
				int a = Enemy.type;
				if(Para.time_count>2000){
					for(;a==Enemy.type;){
						Enemy.type = get_rand(2);
					}
				}
				else{
					for(;a==Enemy.type;){
						Enemy.type = 3+get_rand(2);
					}
				}
			}
			Enemy.bShotend = false;
			Enemy.i_hanyou[0] = 0;
			Enemy.i_hanyou[1] = 0;
		}
		else if(Enemy.bShotend==true){
			Enemy.i_hanyou[0]++;
		}
		else{
			if(Enemy.type==0)	EnShot0();
			if(Enemy.type==1)	EnShot1();
			if(Enemy.type==2)	EnShot2();
			if(Enemy.type==3)	EnShot3();
			if(Enemy.type==4)	EnShot4();
			if(Enemy.type==5)	EnShot5();
			if(Enemy.type==6)	EnShot6();
			Enemy.i_hanyou[1]++;	
		}
	}
	Enemy.count++;
	if(Enemy.count>=180&&bTimeStop==false){
		for(int i=0;i<PLAYER_NUM;i++){
			if(Player[i].get_condition()==0){
				float px,py;
				Player[i].get_xy(&px,&py);
				float sx = px - Enemy.x;
				float sy = py - Enemy.y;
				if(sqrt(sx*sx+sy*sy)<Enemy.atari){
					if(usernum>=2){
						if(Player[i].bMan==true&&SAVE.User[i]!=-1){
							if(!(bOnline==true&&i!=NetWork.NFD[0].player_num))	Profile[SAVE.User[i]].danmaku_num++;
						}
					}
					Player[i].change_condition(1);
				}
			}
		}
	}

	return;
}

void EnShot0(){
//ƒŒƒxƒ‹‚P
	int c = Enemy.i_hanyou[1];
	
	if(c==0)	Enemy.f_hanyou[2] = 0;
	if(c%30==0){
		Enemy.f_hanyou[2] -= 30.0;
		Enemy.f_hanyou[3] = 0;
	}
	if(c%10==0){
		play_sound(10);
		for(int a=0;a<2;a++){
			int rand = get_rand(180);
			ShMake(Enemy.x,Enemy.y,180*a+rand,2.0,gShot[0][0],0,0,15);
		}
		Enemy.f_hanyou[3] += 0.3;
	}
	if(c==179)	Enemy.bShotend = true;
	
	return;
}

void EnShot1(){
//ƒŒƒxƒ‹‚P
	int c = Enemy.i_hanyou[1];
	
	if(c==0)	Enemy.f_hanyou[2] = 0;
	if(c<10&&c%10==0){
		play_sound(10);
		int rand = get_rand(360);
		for(int i=0;i<6;i++){
			for(int a=0;a<4;a++){
				ShMake(Enemy.x,Enemy.y,60*i+rand+15*a,2.0+0.2*a,gShot[1][6],1,1,10);
				ShMake(Enemy.x,Enemy.y,60*i+rand+15*a,2.0+0.2*a,gShot[1][6],1,2,10);
			}
		}
	}
	if(c==179)	Enemy.bShotend = true;
	
	return;
}

void EnShot2(){
//ƒŒƒxƒ‹‚P
	int c = Enemy.i_hanyou[1];
	
	if(c==0){
		Enemy.f_hanyou[2] = get_rand(360);
	}
	Enemy.f_hanyou[2] += 1.0;
	if(c<120&&c%1==0){
		play_sound(10);
		if(c%2==0)	ShMake(Enemy.x,Enemy.y,Enemy.f_hanyou[2],2.0,gShot[0][4],0,3,10);
		else		ShMake(Enemy.x,Enemy.y,Enemy.f_hanyou[2],2.0,gShot[0][4],0,4,10);
		Enemy.f_hanyou[2] += 10.0;
	}
	if(c==179)	Enemy.bShotend = true;
	
	return;
	
	return;
}

void EnShot3(){
//ƒŒƒxƒ‹‚Q
	int c = Enemy.i_hanyou[1];
	
	if(c%6==0){
		play_sound(10);
		for(int i=0;i<2;i++){
			ShMake(Enemy.x,Enemy.y,45.0+Enemy.i_hanyou[2]*17,1.0,gShot[0][0],0,0,15);
			ShMake(Enemy.x,Enemy.y,135.0-Enemy.i_hanyou[2]*17,1.0,gShot[0][5],0,0,15);
		}
		Enemy.i_hanyou[2]++;
	}
	if(c%10==0){
		play_sound(10);
		for(int i=0;i<2;i++){
			ShMake(Enemy.x,Enemy.y,45.0+Enemy.i_hanyou[3]*21,1.5,gShot[0][0],0,0,15);
			ShMake(Enemy.x,Enemy.y,135.0-Enemy.i_hanyou[3]*21,1.5,gShot[0][5],0,0,15);
		}
		Enemy.i_hanyou[3]++;
	}
	if(c==180)	Enemy.bShotend = true;
	
	return;
}

void EnShot4(){
//ƒŒƒxƒ‹‚Q
	int c = Enemy.i_hanyou[1];
	
	if(c==0)	Enemy.f_hanyou[2] = 0;
	if(c%30==0){
		Enemy.f_hanyou[2] += 30.0;
		Enemy.f_hanyou[3] = 0;
	}
	if(c%3==0){
		play_sound(10);
		for(int a=0;a<2;a++){
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]-8.0+c/3,1.5+Enemy.f_hanyou[3],gShot[1][2],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]-4.0+c/3,1.5+Enemy.f_hanyou[3],gShot[1][1],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]+c/3,1.5+Enemy.f_hanyou[3],gShot[1][0],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]+4.0+c/3,1.5+Enemy.f_hanyou[3],gShot[1][1],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]+8.0+c/3,1.5+Enemy.f_hanyou[3],gShot[1][2],1,0,15);
		}
		Enemy.f_hanyou[3] += 0.3;
	}
	if(c==179)	Enemy.bShotend = true;
	
	return;
}

void EnShot5(){
//ƒŒƒxƒ‹‚Q
	int c = Enemy.i_hanyou[1];
	
	if(c==0)	Enemy.f_hanyou[2] = 0;
	if(c%30==0){
		Enemy.f_hanyou[2] -= 30.0;
		Enemy.f_hanyou[3] = 0;
	}
	if(c%3==0){
		play_sound(10);
		for(int a=0;a<2;a++){
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]-8.0-c/3,1.5+Enemy.f_hanyou[3],gShot[1][2],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]-4.0-c/3,1.5+Enemy.f_hanyou[3],gShot[1][1],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]-c/3,1.5+Enemy.f_hanyou[3],gShot[1][0],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]+4.0-c/3,1.5+Enemy.f_hanyou[3],gShot[1][1],1,0,15);
			ShMake(Enemy.x,Enemy.y,180*a+Enemy.f_hanyou[2]+8.0-c/3,1.5+Enemy.f_hanyou[3],gShot[1][2],1,0,15);
		}
		Enemy.f_hanyou[3] += 0.3;
	}
	if(c==179)	Enemy.bShotend = true;
	
	return;
}

void EnShot6(){
//ƒŒƒxƒ‹‚R
	int c = Enemy.i_hanyou[1];
	
	if(c%1==0){
		play_sound(10);
		int num = 7-Para.time_count/100;
		for(int i=0;i<num;i++){
			int rand = get_rand(360);
			ShMake(Enemy.x,Enemy.y,rand,0.5+0.1*get_rand(10),gShot[1][get_rand(7)],0,5,15);
		}
	}
	
	return;
}

void ShMake(float x,float y,float angle,float speed,int img,int type,int pattern,int late){
	SHOTDATA P;
	P.x = x;
	P.y = y;
	P.move_x = cos(Radian(angle,TRUE));
	P.move_y = sin(Radian(angle,TRUE));
	P.angle = angle;
	P.speed = speed;
	P.type = type;
	P.img = img;
	P.count = 0;
	P.flash = 255;
	P.late = late;
	P.max_late = late;
	P.pattern = pattern;
	for(int i=0;i<4;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	if(type==0){
		P.atari = 3.0;
	}
	else if(type==1){
		P.atari = 2.0;
	}
	else if(type==2){
		P.atari = 5.0;
	}
	
	Shot.push_back(P);

	return;
}

void ShDraw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	for(list<SHOTDATA>::iterator it=Shot.begin();it!=Shot.end();++it){
		if((*it).late>0){
			if(bTimeStop==true)	continue;
			float large = 1.0 + 1.5 * ((float)(*it).late/(float)(*it).max_late);
			(*it).late--;
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			if(repeat==9){
				int i;
				for(int j=0;j<SHOT_GRAPH_NUMA;j++){
					bool flag = false;
					for(i=0;i<SHOT_GRAPH_NUMB;i++){
						if((*it).img==gShot[j][i]){
							flag = true;
							break;
						}
					}
					if(flag==true)	break;
				}
				DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,large,Radian((*it).angle,TRUE),gShot[0][i],TRUE,FALSE);
			}
		}
		else{
			ShMove(it);
			int x = X_ZAHYO_TO_NUM((*it).x);
			int y = Y_ZAHYO_TO_NUM((*it).y);
			if(x==0||x==LARGE_X-1||y==0||y==LARGE_Y-1){
				it = Shot.erase(it);
				it--;
				continue;			
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			if(repeat==9)	DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,1.0,Radian((*it).angle,TRUE)+1.57,(*it).img,TRUE,FALSE);
		}
	}

	return;
}

void ShMove(list<SHOTDATA>::iterator &it){
	if(bTimeStop==true)	return;
	int p = (*it).pattern;
	
	if(p==1 || p==2){
		if((*it).count==0){
			(*it).f_hanyou[0] = 1.0 / 60.0;
		}
		float angle = Atan2((*it).move_y,(*it).move_x);
		if((*it).count<120){
			if(p==1){
				angle += Radian(2.8,TRUE);
			}
			else if(p==2){
				angle -= Radian(2.6,TRUE);
			}
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
		if((*it).count<60)	(*it).speed -= (*it).f_hanyou[0];
	}
	else if(p==3||p==4){
		if((*it).count<20){}
		if((*it).count==20){
			if(p==3)	(*it).f_hanyou[0] = ((*it).speed-(1.5)) / 60.0;
			else		(*it).f_hanyou[0] = ((*it).speed-(-1.5)) / 60.0;
		}
		else if((*it).count<80){
			(*it).speed -= (*it).f_hanyou[0];
		}
		if(p==4){
			if((*it).count<50){
				float angle = Atan2((*it).move_y,(*it).move_x);
				angle += Radian(3.0,TRUE);
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
		}
	}
	else if(p==5){
		if((*it).count==0){
			(*it).f_hanyou[0] = (*it).speed;
		}
		(*it).speed = (*it).f_hanyou[0] + 0.01*(700.0-(float)Para.time_count);
	}
	else if(p==6){
		if((*it).count>=60&&(*it).count<120){
			(*it).speed += 0.05;
		}
	}
	else if(p>=7&&p<=9){
		if((*it).count>=60&&(*it).count<120){
			(*it).speed += 0.03*(p-7);
		}
		if((*it).count>=60&&(*it).count<90){
			float angle = Atan2((*it).move_y,(*it).move_x);
			angle += Radian(1.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);	
		}
	}
	else if(p>=10&&p<=12){
		if((*it).count>=60&&(*it).count<120){
			(*it).speed += 0.03*(p-10);
		}
		if((*it).count>=60&&(*it).count<90){
			float angle = Atan2((*it).move_y,(*it).move_x);
			angle -= Radian(1.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);	
		}
	}
 	else if(p>=13&&p<=16){
		if((*it).count==0){
			(*it).f_hanyou[0] = (*it).speed/60.0;
			(*it).f_hanyou[1] = 5.5 - (*it).speed;
		}
		if((*it).count<60){
			(*it).speed -= (*it).f_hanyou[0];
		}
		if((*it).count==90){
			float x,y;
			Player[p-13].get_xy(&x,&y);
			float angle = Atan2(y-(*it).y,x-(*it).x);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).img = gShot[2][6];	
		}
		if((*it).count>=90&&(*it).count<120){
			(*it).speed += (*it).f_hanyou[1]/30.0;		
		}
	}
 	else if(p>=17&&p<=24){
		if((*it).count==0){
			(*it).f_hanyou[0] = (*it).speed/60.0;
			(*it).f_hanyou[1] = 2.5;
		}
		if((*it).count<60){
			(*it).speed -= (*it).f_hanyou[0];
		}
		if((*it).count==90){
			float x,y;
			Player[(p-17)/2].get_xy(&x,&y);
			float angle = Atan2(y-(*it).y,x-(*it).x);
			if((p-17)%2==0)	angle += Radian(15.0,TRUE);
			else		angle -= Radian(15.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).img = gShot[2][6];	
		}
		if((*it).count>=90&&(*it).count<120){
			(*it).speed += (*it).f_hanyou[1]/30.0;		
		}
	}

	(*it).x += (*it).move_x*(*it).speed;
	(*it).y += (*it).move_y*(*it).speed;
	(*it).angle = Radian(Atan2((*it).move_y,(*it).move_x),FALSE);
	(*it).count++;
	
	return;
}
