#include "pshot.h"
#include "effect.h"
#include "system.h"

list<PSHOTDATA> PShot;
list<PLASERDATA> PLaser;
list<BOMBDATA> Bomb;

void PSReset();
void PSDraw();
void PSMove(list<PSHOTDATA>::iterator &it);
void PSMake(float x,float y,float speed, float angle,int img,int pattern,int atack);
void PLDraw();
void PLMove(list<PLASERDATA>::iterator &it);
void PLMake(int img,int atack);
void PBDraw();
void PBMove(list<BOMBDATA>::iterator &it);
void PBMake(float x,float y,float angle,int img,int atack,bool au);

void PSReset(){
	PShot.clear();
	PLaser.clear();
	Bomb.clear();

	return;
}

void PSDraw(){
	for(list<PSHOTDATA>::iterator it=PShot.begin(); it!=PShot.end(); ++it){
		PSMove(it);
		int gx,gy;
		GetGraphSize(gPShot[Player[0].chara][(*it).img],&gx,&gy);
		gx /= 2;
		gy /= 2;
		if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){
			if((*it).bDelete==true || (*it).count>=60){
				it = PShot.erase(it);
				it--;
				continue;			
			}
		}
		else{
			(*it).bDelete = true;
		}
		if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if(Player[0].chara>=3 && Player[0].stress_gage>=MAJIGIRE)	SetDrawBright(255,150,150);
		if(GetSkip()){
			if(Player[0].hyper_count==0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle+M_PI/2.0, gPShot[Player[0].chara][(*it).img], TRUE, FALSE);
			else{
				int img_num = 0;
				if(Player[0].chara>0)	img_num = 12 + Player[0].chara;
				DrawExtendGraphF((*it).x-gx*2+shake_x, (*it).y-gy*2+shake_y, (*it).x+gx*2+shake_x, (*it).y+gy*2+shake_y, gEffect[img_num], TRUE);
				DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle+M_PI/2.0, gPShot[Player[0].chara][(*it).img+3], TRUE, FALSE);
			}
		}
		(*it).count++;
		SetDrawBright(255,255,255);
	}
	
	return;
}

void PSMove(list<PSHOTDATA>::iterator &it){
	list<BOSSDATA>::iterator bit = Boss.begin();
	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;
	
	(*it).angle = Atan2((*it).move_y,(*it).move_x);

	if(Player[0].hyper_count>0 && (Boss.size()==0 || (*bit).bSpell==false))	(*it).bBlend = true;
	else				(*it).bBlend = false;
	
	return;
}

void PSMake(float x,float y,float speed, float angle,int img,int pattern,int atack){
//カンスト2000
	if(PShot.size()==2000){
	
	}
	else{
		PSHOTDATA P;
		P.x = x;
		P.y = y;
		P.speed = speed;
		P.large = 1.0;
		P.angle = Radian(angle,TRUE);
		P.move_x = cos(P.angle);
		P.move_y = sin(P.angle);
		int gx,gy;
		GetGraphSize(gPShot[Player[0].chara][img],&gx,&gy);
		P.atari = sqrt((float)(gx*gx+gy*gy))/2.0;
		if(Player[0].chara%3==0 && (img==0||img==3))		P.life = 3;
		else if(Player[0].chara%3==0 && (img==1||img==4))	P.life = 1;
		else if(Player[0].chara%3==2 && (img==0||img==3))	P.life = 2;
		else if(Player[0].chara%3==2 && (img==1||img==4))	P.life = 0;
		else						P.life = 0;
		if(Player[0].level==IMPOSSIBLE)	P.life += 6;
		else				P.life += 3;
		if(Player[0].chara>=3){
			P.life *= 2;
			if(Player[0].stress_gage>=MAJIGIRE)	P.life *= 1.5;
		}
		P.flash = 150;
		if(Player[0].chara==3 && (img==0 || img==3))	P.flash = 200;
		P.atack = atack;
		if(Player[0].chara>=3 && Player[0].stress_gage>=MAJIGIRE){
			if(Player[0].chara==3)		P.atack *= 1.5;
			else if(Player[0].chara==4)	P.atack *= 2.0;
			else if(Player[0].chara==5)	P.atack *= 1.2;
		}
		P.img = img;
		P.count = 0;
		P.pattern = pattern;
		P.bBlend = false;
		P.bDelete = false;

		PShot.push_back(P);
	}
	
	return;
}

void PLDraw(){
	for(list<PLASERDATA>::iterator it=PLaser.begin(); it!=PLaser.end(); ++it){
		PLMove(it);
		if((*it).bBlend==false)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		if((*it).bDelete==true){
			(*it).delete_count--;
		}
		else{
			if((*it).delete_count<10)	(*it).delete_count++;
		}
		if((*it).delete_count==0){
			it = PLaser.erase(it);
			it--;
			continue;			
		}
		if(Player[0].chara>=3 && Player[0].stress_gage>=MAJIGIRE)	SetDrawBright(255,100,100);
		if(GetSkip()){
			if(Player[0].hyper_count==0)	DrawExtendGraphF((*it).x[1]-(*it).large+shake_x, (*it).y[1]+shake_y, (*it).x[0]+(*it).large+shake_x, (*it).y[0]+shake_y, gPShot[Player[0].chara][(*it).img], TRUE);
			else				DrawExtendGraphF((*it).x[1]-(*it).large+shake_x, (*it).y[1]+shake_y, (*it).x[0]+(*it).large+shake_x, (*it).y[0]+shake_y, gPShot[Player[0].chara][(*it).img+3], TRUE);
			SetDrawBright(255,255,255);
			for(int i=0;i<6;i++){
				float place = (*it).y[0]-(80*i+(12*(*it).count)%80);
				if(place>(*it).y[1]){
					if((*it).y[0]-place<100)	SetDrawBlendMode(DX_BLENDMODE_ADD,1.50*((*it).y[0]-place));
					else				SetDrawBlendMode(DX_BLENDMODE_ADD,150);
					DrawExtendGraphF((*it).x[0]-(*it).large-10+shake_x, place-4+shake_y, (*it).x[0]+(*it).large+10+shake_x, place+4+shake_y, gEffect[18], TRUE);
				}
			}
		}
		(*it).bDelete = true;
		(*it).count++;
		SetDrawBright(255,255,255);
	}
		
	return;
}

void PLMove(list<PLASERDATA>::iterator &it){
	(*it).length += 25.0;
	if((*it).length>460)	(*it).length = 460;
	if(Player[0].death_count==0){
		(*it).x[0] = Player[0].x;
		(*it).y[0] = Player[0].y;
		(*it).x[1] = Player[0].x;
		(*it).y[1] = Player[0].y-(*it).length;
	}

	if(Player[0].hyper_count==0)	(*it).large = 40.0 * (*it).delete_count / 10.0;
	else				(*it).large = 60.0 * (*it).delete_count / 10.0;

	return;
}

void PLMake(int img,int atack){
//カンスト1
	if(PLaser.size()!=0){
		for(list<PLASERDATA>::iterator it=PLaser.begin(); it!=PLaser.end(); ++it){
			(*it).img = img;
			(*it).bDelete = false;
		}
	}
	else{
		PLASERDATA P;
		P.x[0] = Player[0].x;
		P.y[0] = Player[0].y;
		P.x[1] = Player[0].x;
		P.y[1] = Player[0].y;
		P.length = 0.0;
		P.large = 0.0;
		P.flash = 150;
		P.atack = atack;
		if(Player[0].chara>=3 && Player[0].stress_gage>=MAJIGIRE){
			if(Player[0].chara==3)		P.atack *= 1.3;
			else if(Player[0].chara==4)	P.atack *= 1.5;
			else if(Player[0].chara==5)	P.atack *= 1.1;
		}
		P.img = img;
		P.count = 0;
		P.delete_count = 0;
		P.bBlend = true;
		P.bDelete = false;

		PLaser.push_back(P);
	}
	
	return;
}

void PBDraw(){
	if(Bomb.size()>0){
		SESDelete(5);
	}
	for(list<BOMBDATA>::iterator it=Bomb.begin(); it!=Bomb.end(); ++it){
		PBMove(it);
		if((*it).bDelete==true){
			if((*it).img==7){
				for(int i=0;i<BOMB_NUM;i++){
					if(i%1==0)	EfMake((*it).zx[i], (*it).zy[i], 2, (*it).img);
				}
			}
			else{
				EfMake((*it).x, (*it).y, 2, (*it).img);
			}
			it = Bomb.erase(it);
			it--;
			continue;			
		}
		for(int i=BOMB_NUM-1;i>0;i--){
			if((*it).zx[i]!=(*it).x || (*it).zy[i]!=(*it).y){
				SetDrawBright(255,150,150);
				float flash = (float)(*it).flash*(float)(BOMB_NUM-i)/(float)BOMB_NUM;
				float large = (*it).large*(float)(BOMB_NUM-i)/(float)BOMB_NUM;
				SetDrawBlendMode(DX_BLENDMODE_ADD,flash);
				if(GetSkip())	DrawRotaGraphF((*it).zx[i]+shake_x, (*it).zy[i]+shake_y, large, (*it).angle+M_PI/2.0, gPShot[Player[0].chara][(*it).img], TRUE, FALSE);
			}
		}
		SetDrawBright(255,255,255);
		SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if(GetSkip())	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle+M_PI/2.0, gPShot[Player[0].chara][(*it).img], TRUE, FALSE);
		(*it).count++;
	}
	
	return;
}

void PBMove(list<BOMBDATA>::iterator &it){
	if((*it).img==7){
		if((*it).count==0){
			if((*it).bAuto==false)	(*it).speed = 8.0;
			else			(*it).speed = 6.0;
		}
		float angle = Atan2((*it).move_y,(*it).move_x);
		if((*it).bAuto==false)	angle += Radian(4.0,TRUE);
		else			angle += Radian(6.0,TRUE);
		(*it).move_x = cos(angle);
		(*it).move_y = sin(angle);
	}
	if((*it).bAuto==true && (*it).count==60)	(*it).bDelete = true;
	if((*it).bAuto==false && (*it).count==180)	(*it).bDelete = true;

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;
	(*it).angle += Radian(6.0,TRUE);
	if((*it).count<10)	(*it).large = 0.1*(*it).count;
	else			(*it).large = 1.0;

	(*it).zx[0] = (*it).x;
	(*it).zy[0] = (*it).y;
	for(int i=BOMB_NUM-1;i>0;i--){
		(*it).zx[i] = (*it).zx[i-1];
		(*it).zy[i] = (*it).zy[i-1];
	}
	
	return;
}

void PBMake(float x,float y,float angle,int img,int atack,bool au){
	Player[0].hyper_count = 0;
	Player[0].spcard = 0;
	BOMBDATA P;
	P.x = x;
	P.y = y;
	for(int i=0;i<BOMB_NUM;i++){
		P.zx[i] = x;
		P.zy[i] = y;
	}
	P.large = 1.0;
	P.angle = Radian(angle,TRUE);
	P.speed = 0.0;
	P.move_x = cos(P.angle);
	P.move_y = sin(P.angle);
	int gx,gy;
	GetGraphSize(gPShot[Player[0].chara][img],&gx,&gy);
	P.atari = gx/2+40;
	P.flash = 255;
	P.atack = atack;
	P.img = img;
	P.count = 0;
	P.bDelete = false;
	P.bAuto = au;

	Bomb.push_back(P);
	
	return;
}