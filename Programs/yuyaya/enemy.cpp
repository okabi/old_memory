#include "enemy.h"
#include "boss.h"
#include "pshot.h"
#include "effect.h"
#include "system.h"

list<ENEMYDATA> Enemy;
list<ESHOTDATA> EShot;
list<ELASERDATA> ELaser;
list<ESLASERDATA> ESLaser;
float Lto_x;
float Lto_y;
int Lspe_count;
float ang_plus;
int Prank;

void EReset();
void EDraw();
void EMove(list<ENEMYDATA>::iterator &it);
void EShotS(list<ENEMYDATA>::iterator &it);
void EMake(float x,float y,int life,int img,int move_pattern,int shot_pattern);
void ESDraw();
void ESMove(list<ESHOTDATA>::iterator &it);
void ESMake(float x,float y,float angle,float speed,int img,bool blend,int pattern,int late,float f_speed,int f_count,bool eff,float hanyou);
void ESNWay(float x,float y,float tox,float toy,float angle,int num,float speed,int img,bool blend,int pattern,int late,float f_speed,int f_count,bool eff);
void ELDraw();
void ELMove(list<ELASERDATA>::iterator &it);
void ELMake(float x,float y,float size,float angle,float speed,int img,int pattern,int late);
void ESLDraw();
void ESL1Move(list<ESLASERDATA>::iterator &it);
void ESL2Move(list<ESLASERDATA>::iterator &it);
void ESL1Make(float x, float y, float size, float length, float angle, float speed, int img, int pattern);
void ESL2Make(float x, float y, float size, float angle, float speed,int img, int pattern);

void EReset(){
	Enemy.clear();
	EShot.clear();
	ELaser.clear();
	ESLaser.clear();
	Lto_x = 0;
	Lto_y = 0;
	Lspe_count = 0;
	ang_plus = 0;
	Prank = 0;

	return;
}

void EDraw(){
	int loop_num = 1;
	/*
	list<BOSSDATA>::iterator bit = Boss.begin();
	if((*bit).life>0 && Player[0].hyper_count>0 && (Player[0].level==HARD || Player[0].level==LUNATIC || Player[0].level==IMPOSSIBLE) && NowPart==BOSS)	loop_num = 2;
	*/
	for(int k=0;k<loop_num;k++){
		for(list<ENEMYDATA>::iterator it=Enemy.begin(); it!=Enemy.end(); ++it){
			EMove(it);
			int hcount = Player[0].hyper_count;
			if(Player[0].level==BABY)	Player[0].hyper_count = 30;
			Prank = Player[0].hyper_rank;
			//if(Player[0].stress_gage>=MAJIGIRE)	Prank += 3;
			if(Player[0].hyper_count>0 && Prank<10)	Prank = 10;
			bES = true;
			bRG = true;
			EShotS(it);
			bES = false;
			bRG = false;
			if(Player[0].level==BABY)	Player[0].hyper_count = hcount;
			int gx,gy;
			GetGraphSize(gEnemy[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			if(fabs((*it).move_x)>0.9){
				float sw = gx;
				gx = gy;
				gy = sw;
			}
			if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){
				if((*it).bDelete==true || (*it).count>=1200){
					it = Enemy.erase(it);
					it--;
					continue;			
				}
			}
			else{
				(*it).bDelete = true;
			}
			if((*it).bDe==true){
				EfMake((*it).x, (*it).y, 3, 4);
				it = Enemy.erase(it);
				it--;
				continue;			
			}
			(*it).count++;
		}
	}
	if(GetSkip()){
		for(int q=0;q<2;q++){
			for(list<ENEMYDATA>::iterator it=Enemy.begin(); it!=Enemy.end(); ++it){
				if((q==0&&(*it).bAtari==true) || (q==1&&(*it).bAtari==false))	continue; 
				if((*it).bBlend==false)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
				else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
				SetDrawBright(255,255,255);
				float per = 100.0 * (float)(*it).life / (float)(*it).max_life;
				if((*it).bDamage==true){
					(*it).bDamage = false;
					//SetDrawBright(100,100,255);
					if(per<20.0)	PlaySound(6);
					else		PlaySound(7);
				}
				if(per<10.0){
					if((*it).count%4<2)	SetDrawBright(255,50,50);
				}
				else if(per<20.0){
					if((*it).count%6<2)	SetDrawBright(255,50,50);
				}
				else if(per<30.0){
					if((*it).count%10<2)	SetDrawBright(255,50,50);
				}
				else if(per<40.0){
					if((*it).count%20<2)	SetDrawBright(255,50,50);
				}
				else if(per<50.0){
					if((*it).count%30<2)	SetDrawBright(255,50,50);
				}
        	
				if(0/*(*bit).bSpell==true*/){
					SetDrawBlendMode(DX_BLENDMODE_ADD,150);
					float large = 0.4;
					if((*it).count<20)	large = 0.02*(*it).count;
					DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, large, Radian(12*(*it).count,TRUE), gEffect[8], TRUE, FALSE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
				}
				if((*it).img!=-1){
					DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEnemy[(*it).img], TRUE, FALSE);
					if((*it).img==8 || (*it).img==1 || (*it).img==10){
						DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).f_hanyou[0]-M_PI/2.0, gEnemy[9], TRUE, FALSE);
					}
					else if((*it).img==18 && ((*it).move_pattern==25 || (*it).move_pattern==26)){
						float x[3],y[3],angle[3],px=Player[0].x,py=Player[0].y;
						x[0] = (*it).x;
						y[0] = (*it).y-46;
						x[1] = (*it).x-26;
						y[1] = (*it).y-18;
						x[2] = (*it).x+26;
						y[2] = (*it).y-18;
						for(int i=0;i<3;i++){
							angle[i] = Atan2(py-y[i],px-x[i]);
							if(i>0)	angle[i] = Radian((*it).f_hanyou[i-1],TRUE);
							DrawRotaGraphF(x[i]+shake_x, y[i]+shake_y, (*it).large, angle[i]-M_PI/2.0, gEnemy[9], TRUE, FALSE);
						}
					}
					else if((*it).img==23){
						float large = 1.2 + 0.4*sin(Radian(6.0*(*it).count,TRUE));
						DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, large, Radian(10.0*(*it).count,TRUE)-M_PI/2.0, gEnemy[24], TRUE, FALSE);
					}
				}			
			}
		}
	}
	SetDrawBright(255,255,255);
	
	return;
}

void EMove(list<ENEMYDATA>::iterator &it){
	int p = (*it).move_pattern;
	int c = (*it).count;
	bool bAngle = true;

	list<BOSSDATA>::iterator bit = Boss.begin();
	
	if(p==0){//雑魚空中
		if(c==0){
			(*it).speed = 4.0+0.01*get_rand(200);
			(*it).angle = Radian(80.0+0.01*get_rand(2000),TRUE);
			(*it).move_x = cos((*it).angle);
			(*it).move_y = sin((*it).angle);
			(*it).f_hanyou[0] = 0.05;
		}
		(*it).speed -= (*it).f_hanyou[0];
	}
	else if(p==1){//ゆっくり下降空中
		if(c==0){
			(*it).speed = 1.0;
			(*it).move_y = 1;
		}
	}
	else if(p==2){//戦車
		if(c==0){
			(*it).speed = 1.0;
			(*it).move_x = cos(Atan2(265,-400));
			(*it).move_y = sin(Atan2(265,-400));
		}
		(*it).y += BackY-(*it).back_y;
		(*it).back_y = BackY;
	}
	else if(p==3){//スピリット
		if(c==0){
			(*it).speed = 5.0;
			(*it).move_y = 1;
			(*it).f_hanyou[7] = (*it).speed / 60.0;
		}
		if(c<60)	(*it).speed -= (*it).f_hanyou[7];
		else if(c<300)	(*it).speed = 0.4;
		else		(*it).speed = 1;
	}
	else if(p==4){//マイク（専用）
		if(c==0){
			(*it).speed = 2.0;
			(*it).move_y = 1;
			(*it).bNoDamage = true;
		}
		if(c==60)	(*it).bNoDamage = false;
		(*it).move_x = sin(Radian(3*c,TRUE));
	}
	else if(p==5){//コーン
		if(c==0){
			(*it).speed = 3.0+0.1*get_rand(40);
			(*it).f_hanyou[0] = get_rand(90)+225;
			(*it).angle = Radian(get_rand(360),TRUE);
			(*it).move_x = cos(Radian((*it).f_hanyou[0],TRUE));
			(*it).move_y = sin(Radian((*it).f_hanyou[0],TRUE));
		}
		if(c==20)	(*it).bNoDamage = false;
		if((*it).move_y<1)	(*it).move_y += 0.02;
		else			(*it).move_y = 1.0;
	}
	else if(p==6 || p==7){//マイク（弾符「マイクポップコーンは神」）
		if(c==0){
			(*it).flash = 150;
			(*it).speed = 0;
			(*it).f_hanyou[0] = Atan2((*it).y-(*bit).y, (*it).x-(*bit).x);
			(*it).f_hanyou[1] = (*bit).f_hanyou[0];
			(*it).bBlend = true;
			(*it).bNoDamage = true;
			(*it).bAtari = false;
		}
		(*it).speed += 0.03;
		(*it).move_x = cos((*it).f_hanyou[0]);
		(*it).move_y = sin((*it).f_hanyou[0]);
		if(p==6)	(*it).f_hanyou[0] += Radian(1.0, TRUE);
		else if(p==7)	(*it).f_hanyou[0] -= Radian(1.0, TRUE);
	}
	else if(p==8){//フラフィ・ソロー
		if(c==0){
			(*it).speed = 6.0;
			(*it).move_x = cos(Radian(90,TRUE));
			(*it).move_y = sin(Radian(90,TRUE));
			(*it).i_hanyou[1] = 0;
		}
		if((*it).y>20 && (*it).i_hanyou[1]<60){
			float angle = Atan2((*it).move_y, (*it).move_x);
			float sqang = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			float ang1 = angle-sqang;
			if(ang1<0)	ang1 += 2*M_PI;
			float ang2 = sqang-angle;
			if(ang2<0)	ang2 += 2*M_PI;
			if(ang1<ang2)	angle -= Radian(1.0,TRUE);
			else		angle += Radian(1.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).i_hanyou[1]++;
		}
	}
	else if(p==9 || p==10){//銀次
		if(c==0){
			(*it).speed = 5.0+0.1*get_rand(50);
			if(p==9){
				(*it).move_x = cos(Radian(0,TRUE));
				(*it).move_y = sin(Radian(0,TRUE));
			}
			else{
				(*it).move_x = cos(Radian(180,TRUE));
				(*it).move_y = sin(Radian(180,TRUE));
			}
			(*it).f_hanyou[0] = ((*it).speed-(1+0.1*get_rand(15))) / 60.0;
		}
		if(c<40){}
		else if(c<100){
			float angle = Atan2((*it).move_y,(*it).move_x);
			if(p==9){
				angle -= Radian(4.6,TRUE);
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
			else{
				angle += Radian(4.6,TRUE);
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
			(*it).speed -= (*it).f_hanyou[0];
		}
	}
	else if(p>=11 && p<=13){//気符「英語雲散霧消」の見えない敵
		if(p==11 || p==12){
			if(c==0){
				(*it).f_hanyou[0] = Atan2((*it).y-((*bit).y-34), (*it).x-(*bit).x);
				(*it).move_x = cos((*it).f_hanyou[0]);
				(*it).move_y = sin((*it).f_hanyou[0]);
				if(Player[0].level==EASY)	(*it).speed = 3.0;
				else	(*it).speed = 4.0;
			}
			(*it).f_hanyou[0] = Atan2((*it).move_y,(*it).move_x);
			if(c<90){
				if(p==11)	(*it).f_hanyou[0] += Radian(2.0,TRUE);
				else if(p==12)	(*it).f_hanyou[0] -= Radian(2.0,TRUE);
				(*it).move_x = cos((*it).f_hanyou[0]);
				(*it).move_y = sin((*it).f_hanyou[0]);
			}
		}
		else if(p==13){
			if(c==0){
				(*it).f_hanyou[0] = Atan2((*it).y-((*bit).y-34), (*it).x-(*bit).x);
				(*it).move_x = cos((*it).f_hanyou[0]);
				(*it).move_y = sin((*it).f_hanyou[0]);
				if(Player[0].level==EASY)	(*it).speed = 3.0;
				else	(*it).speed = 4.0;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = Player[0].x;
			}
			if(c<60){
				float angle = Atan2((*it).move_y, (*it).move_x);
				float sqang = Atan2((*it).f_hanyou[1]-(*it).y, (*it).f_hanyou[2]-(*it).x);
				float ang1 = angle-sqang;
				if(ang1<0)	ang1 += 2*M_PI;
				float ang2 = sqang-angle;
				if(ang2<0)	ang2 += 2*M_PI;
				if(ang1<ang2)	angle -= Radian(4.0,TRUE);
				else		angle += Radian(4.0,TRUE);
				(*it).move_x = cos(angle);
				(*it).move_y = sin(angle);
			}
		}
	}
	else if(p>=14 && p<=17){//「早苗は俺の嫁」
		if(p==14 || p==15){
			if(c%30==0){
				int num = c/30;
				float to_x,to_y,sq,angle;
				float l = 80.0;
				if(p==14){
					if(num==0)	angle = Radian(-18,TRUE);
					else if(num==1)	angle = Radian(126,TRUE);
					else if(num==2)	angle = Radian(-90,TRUE);
					else if(num==3)	angle = Radian(54,TRUE);
					else if(num==4)	angle = Radian(-162,TRUE);
					else if(num==5)	(*it).x = -100;
				}
				else{
					if(num==0)	angle = Radian(-18+36,TRUE);
					else if(num==1)	angle = Radian(126+36,TRUE);
					else if(num==2)	angle = Radian(-90+36,TRUE);
					else if(num==3)	angle = Radian(54+36,TRUE);
					else if(num==4)	angle = Radian(-162+36,TRUE);
					else if(num==5)	(*it).x = -100;
				}			
				to_x = (*bit).x + l*cos(angle);
				to_y = (*bit).y - 34 + l*sin(angle);
				float sx = to_x-(*it).x;
				float sy = to_y-(*it).y;
				sq = sqrt(sx*sx+sy*sy);
				(*it).speed = sq / 30.0;
				float an = Atan2(to_y-(*it).y, to_x-(*it).x);
				(*it).move_x = cos(an);
				(*it).move_y = sin(an);
			}
		}
		else if(p==16 || p==17){
			if(c%18==0){
				int num = c/18;
				float to_x,to_y,sq,angle;
				float l = 100.0;
				if(Player[0].level==IMPOSSIBLE)	l = 80.0;
				if(p==16)	angle = Radian(45.0*(3*num),TRUE);
				else if(p==17)	angle = Radian(45.0*(3*num)+120.0,TRUE);
				if(num==8)	(*it).x = -100;
				to_x = (*bit).x + l*cos(angle);
				to_y = (*bit).y - 34 + l*sin(angle);
				float sx = to_x-(*it).x;
				float sy = to_y-(*it).y;
				sq = sqrt(sx*sx+sy*sy);
				(*it).speed = sq / 18.0;
				float an = Atan2(to_y-(*it).y, to_x-(*it).x);
				(*it).move_x = cos(an);
				(*it).move_y = sin(an);
			}
		}
	}
	else if(p==18){//ヴォイド
		if(c==0){
			(*it).speed = 8.0;
			(*it).f_hanyou[7] = (*it).speed / 60.0;
			(*it).move_y = 1;
		}
		if(c<60)	(*it).speed -= (*it).f_hanyou[7];
		else if(c<420)	(*it).speed = 0;
		else		(*it).speed -= 0.1;
	}
	else if(p==19 || p==20){//3面小型戦車（from上下）
		if(c==0){
			(*it).speed = 1.0;
			(*it).move_x = 0;
			if(p==19)	(*it).move_y = 1;
			else		(*it).move_y = -1-(BackX-(*it).back_x);
		}
		(*it).y += BackX-(*it).back_x;
		(*it).back_x = BackX;
	}
	else if(p==21 || p==22){//3面中型戦車（from左右）
		if(c==0){
			(*it).speed = 3.0;
			(*it).move_y = 0;
			if(p==21)	(*it).move_x = 1;
			else		(*it).move_x = -1;
			(*it).back_x = BackX;
		}
		if((*it).speed>0)	(*it).speed -= 0.02;
		else{
			(*it).speed = 0;
			(*it).move_x = 0;
			(*it).move_y = 1;
		}
		(*it).y += BackX-(*it).back_x;
		(*it).back_x = BackX;
	} 
	else if(p==23 || p==24){//3面マイク（from左右）
		if(c==0){
			(*it).speed = 1.5;
			if(p==23)	(*it).move_x = 1;
			else		(*it).move_x = -1;
			(*it).bNoDamage = true;
		}
		if(c==60)	(*it).bNoDamage = false;
		(*it).move_y = 1.0*sin(Radian(1*c,TRUE));
	} 
	else if(p==25 || p==26){//3面トレインドトレイン（from上下）
		if(c==0){
			(*it).speed = 1.2;
			(*it).move_x = 0;
			if(p==25)	(*it).move_y = 1;
			else		(*it).move_y = -1-(BackX-(*it).back_x);
			(*it).f_hanyou[0] = 0;
			(*it).f_hanyou[1] = 180;
		}
		(*it).y += BackX-(*it).back_x;
		(*it).back_x = BackX;
		(*it).f_hanyou[0] += 2.0;
		(*it).f_hanyou[1] -= 2.0;
	} 
	else if(p>=27 && p<=29){//3面アホが出すマイク
		float bx = CENTER_X;
		float by = CENTER_Y;
		float d;
		float plus;
		int ic = c%480;
		if(ic<30)	plus = ic*0.1;
		else if(ic<60)	plus = (60-ic)*0.1;
		else if(ic<90)	plus = 0;
		else if(ic<150)	plus = -(ic-90)*0.05;
		else if(ic<210)	plus = -(210-ic)*0.05;
		else if(ic<240)	plus = 0;
		else if(ic<300)	plus = (ic-240)*0.05;
		else if(ic<420)	plus = 3.0;
		else if(ic<480)	plus = (480-ic)*0.05;
		if(p==27){
			d = 70;
		}
		else if(p==28){
			d = 140;
			plus *= -1;
		}
		else if(p==29){
			d = 210;
		}
		if(c==0){
			(*it).f_hanyou[0] = Atan2((*bit).y-(*it).y, (*bit).x-(*it).x);
			(*it).speed = 0;
			(*it).flash = 150;
			(*it).bNoDamage = true;
			(*it).bAtari = false;
		}
		if(c<30){
			float a = d / 30.0;
			d = a*c;
		}
		(*it).f_hanyou[0] += Radian(plus,TRUE);
		(*it).x = bx + d*cos((*it).f_hanyou[0]);
		(*it).y = by + d*sin((*it).f_hanyou[0]);
		if(Boss.size()==0)	(*it).bDe = true;
	}
	else if(p==30 || p==31){//毛玉（from左、右）
		if(c==0){
			float angle;
			if(p==30)	angle = Radian(0,TRUE);
			else		angle = Radian(180,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = 6.0 + 0.1*get_rand(30);
			(*it).i_hanyou[0] = get_rand(1);
		}
		if(c>=40 && c<100){
			float angle = Atan2((*it).move_y,(*it).move_x);
			if((*it).i_hanyou[0]==0)	angle += Radian(12.0,TRUE);
			else				angle -= Radian(12.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==32 || p==33){//色毛玉（from左上、右上）
		if(c==0){
			float angle;
			if(p==32)	angle = Radian(45,TRUE);
			else		angle = Radian(135,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = 8.0;
		}
		if(c>=40 && c<100){
			float angle = Atan2((*it).move_y,(*it).move_x);
			if(p==32)	angle -= Radian(4.5,TRUE);
			else		angle += Radian(4.5,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==34 || p==35){//色毛玉（from左下、右下）
		if(c==0){
			float angle;
			if(p==34)	angle = Radian(-45,TRUE);
			else		angle = Radian(-135,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = 8.0;
		}
		if(c>=40 && c<100){
			float angle = Atan2((*it).move_y,(*it).move_x);
			if(p==34)	angle += Radian(4.5,TRUE);
			else		angle -= Radian(4.5,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==36){//陰陽玉
		if(c==0){
			float angle = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = 5.0+0.1*get_rand(40);
			(*it).f_hanyou[0] = (*it).speed / 40.0;
		}
		if(c==120){
			float angle = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
		if(c<40)	(*it).speed -= (*it).f_hanyou[0];
		else if(c<120)	(*it).speed = 0;
		else if(c<180)	(*it).speed += 6.0 / 60.0;
		(*it).x += 0.5 * cos(Radian(6*c,TRUE));
		(*it).y += 0.5 * sin(Radian(6*c+90,TRUE));
	}
	else if(p>=37 && p<=40){//走らさせていただいてます☆
		//37:左から 38:右から 39:上から 40:下から
		if(c==0){
			if(p==37)	(*it).move_x = 1;
			else if(p==38)	(*it).move_x = -1;
			else if(p==39)	(*it).move_y = 1;
			else if(p==40)	(*it).move_y = -1;
			(*it).speed = 0.0;
		}
		if((*it).speed<5.0)	(*it).speed += 0.1;

		(*it).angle = Atan2((*it).move_y,(*it).move_x);
		bAngle = false;
	}

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;
	
	if(bAngle==true){
		if((*it).img==14)	(*it).angle += Radian(4.0,TRUE);
		else if((*it).img>=19 && (*it).img<=22)	(*it).angle += Radian(6.0,TRUE);
		else if((*it).img==13 || (*it).img==10 || (*it).img==18)	(*it).angle = Atan2(1.0,0);
		else			(*it).angle = Atan2((*it).move_y,(*it).move_x);
	}
	
	return;
}

void EShotS(list<ENEMYDATA>::iterator &it){
//ESMake(float x,float y,float angle,float speed,int img,bool blend,int pattern,int late,float f_speed,int f_count,bool eff)
//ESNWay(float x,float y,float tox,float toy,float angle,int num,float speed,int img,bool blend,int pattern,int late,float f_speed,int f_count)
//ELMake(float x,float y,float size,float angle,float speed,int img,int pattern,int late)
	int p = (*it).shot_pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;

	list<BOSSDATA>::iterator bit = Boss.begin();


	if(p==-1){//ちゅーとりあるフラフィ(Fraphy)
		int img = ESHOT(RICE,RED);
		if(Player[0].hyper_count==0){}
		else{
			if(c%40==0){
				ESNWay((*it).x, (*it).y+16, Player[0].x, Player[0].y, 30.0, 1, 3.0, img, false, 0, 5);
			}
		}
	}
	else if(p==-2){//ちゅーとりあるフラフィ(Fraphy)
		if(c==40){
			float angle = Radian(atan2(Player[0].y-((*it).y+16), Player[0].x-(*it).x),FALSE);
			ELMake((*it).x, (*it).y+16, 15.0, angle, 5.0, ESHOT(RICE,PURPLE), 2, 60);	
		}
	}
	else if(p==-3){//ちゅーとりあるフラフィ(Fraphy)
		if(c==40){
			float angle = Radian(atan2(Player[0].y-((*it).y+16), Player[0].x-(*it).x),FALSE);
			for(int i=0;i<6;i++){
				ESL1Make((*it).x, (*it).y+16, 6.0, 250.0, angle+60*i, 3.0, RED);
			}
		}
	}
	else if(p==-4){//ちゅーとりあるフラフィ(Fraphy)
		if(c==40){
			float angle = Radian(atan2(Player[0].y-((*it).y+16), Player[0].x-(*it).x),FALSE);
			for(int i=0;i<6;i++){
				ESL2Make((*it).x, (*it).y+16, 4.0, angle+60*i, 2.0, BLUE, 0);
			}
		}
	}
	else if(p==0){//フラフィ(Fraphy)
		int img = ESHOT(RICE,RED);
		if(c==0)	(*it).i_hanyou[1] = 1+get_rand(99);
		if(level==EASY){
			if(Player[0].hyper_count==0){}
			else{
				if(c%40==0){
					ESNWay((*it).x, (*it).y+16, Player[0].x, Player[0].y, 30.0, 1, 2.0, img, false, 0, 5);
				}
			}
		}
		else if(level==NORMAL){
			int loo = Loo(100, 20);
			if(c%loo==loo/2){
				if((*it).i_hanyou[1]<=Per(5,100))	ESNWay((*it).x, (*it).y+16, Player[0].x, Player[0].y, 30.0, 1, 2.5, img, false, 0, 5);
			}
		}
		else if(level==HARD){
			int loo = Loo(75,15);
			if(c==0)	(*it).i_hanyou[0] = get_rand(loo);
			if(c%loo==loo/2){
				if((*it).i_hanyou[1]<=Per(20,100))	ESNWay((*it).x, (*it).y+16, Player[0].x, Player[0].y, 30.0, 1, 3.0, img, false, 0, 5);
			}
		}
		else if(level==LUNATIC){
			int loo = Loo(50,10);
			if(c%loo==loo/2){
				if((*it).i_hanyou[1]<=Per(40,100))	ESNWay((*it).x, (*it).y+16, Player[0].x, Player[0].y, 30.0, 3, 3.5, img, false, 0, 5);
			}
		}
		else if(level==IMPOSSIBLE){
			int loo = Loo(50,10);
			if(c%loo==loo/2){
				if((*it).i_hanyou[1]<=Per(50,100))	ESNWay((*it).x, (*it).y+16, Player[0].x, Player[0].y, 2.0, 4, 10.0, img, false, 0, 5);
			}
		}
	}
	else if(p==1){//ハードフラフィ(Hard Fraphy)
		if(level==EASY){
			int loo = Loo(500,400);
			float angle = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
			if((*it).y<CENTER_Y && c>=60 && ((c-60)%loo<40 && (c-60)%10==0)){
				ESMake((*it).x-10, (*it).y+24, angle, 2.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x-18, (*it).y+24, angle, 2.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+10, (*it).y+24, angle, 2.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+18, (*it).y+24, angle, 2.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
			}
		}
		else if(level==NORMAL){
			int loo = Loo(180,80);
			float angle = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
			if((*it).y<CENTER_Y && c>=60 && ((c-60)%loo<20 && (c-60)%5==0)){
				ESMake((*it).x-10, (*it).y+24, angle, 3.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x-18, (*it).y+24, angle, 3.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+10, (*it).y+24, angle, 3.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+18, (*it).y+24, angle, 3.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
			}
		}
		else if(level==HARD){
			int loo = Loo(150,80);
			float angle = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
			if((*it).y<CENTER_Y && c>=60 && ((c-60)%loo<20 && (c-60)%5==0)){
				ESMake((*it).x-10, (*it).y+24, angle, 4.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x-18, (*it).y+24, angle, 4.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+10, (*it).y+24, angle, 4.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+18, (*it).y+24, angle, 4.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
			}
		}
		else if(level==LUNATIC){
			int loo = Loo(60,10);
			float angle = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
			if((*it).y<CENTER_Y && (c%loo<35 && c%3==0)){
				ESMake((*it).x-10, (*it).y+24, angle, 5.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x-18, (*it).y+24, angle, 5.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+10, (*it).y+24, angle, 5.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+18, (*it).y+24, angle, 5.0, ESHOT(NEEDLE,BLUE), false, 0, 5);
			}
			if((*it).y<CENTER_Y && c%loo==loo/2){
				for(int i=0;i<5;i++)	ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 15.0, 5, 6.0-0.4*i, ESHOT(MEDIUM,RED), false, 0, 5);
			}
		}
		else if(level==IMPOSSIBLE){
			int loo = Loo(50,50);
			float angle = Radian(Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
			if((*it).y<CENTER_Y && (c%loo<20 && c%2==0)){
				ESMake((*it).x-10, (*it).y+24, angle, 7.5, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x-18, (*it).y+24, angle, 7.5, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+10, (*it).y+24, angle, 7.5, ESHOT(NEEDLE,BLUE), false, 0, 5);
				ESMake((*it).x+18, (*it).y+24, angle, 7.5, ESHOT(NEEDLE,BLUE), false, 0, 5);
			}
			if((*it).y<CENTER_Y && c%150==20){
				for(int i=0;i<40;i++)	ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 15.0, 9, 10.5-0.2*i, ESHOT(MEDIUM,RED), false, 0, 5);
			}
		}
	}
	else if(p==2){//ハイパーマスター(Hyper Master)
		if(level==EASY){
			int loo = Loo(500,300);
			if(c==0){
				(*it).i_hanyou[0] = get_rand(loo);
				(*it).i_hanyou[1] = get_rand(loo);
				(*it).i_hanyou[2] = get_rand(loo);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = Player[0].x;
				(*it).f_hanyou[3] = Player[0].y;
				(*it).f_hanyou[4] = Player[0].x;
				(*it).f_hanyou[5] = Player[0].y;
			}
			if((*it).y<CENTER_Y){
				if((c+(*it).i_hanyou[0])%loo==0){
					(*it).f_hanyou[0] = Player[0].x;
					(*it).f_hanyou[1] = Player[0].y;
				}
				if((c+(*it).i_hanyou[1])%loo==0){
					(*it).f_hanyou[2] = Player[0].x;
					(*it).f_hanyou[3] = Player[0].y;
				}
				if((c+(*it).i_hanyou[2])%loo==0){
					(*it).f_hanyou[4] = Player[0].x;
					(*it).f_hanyou[5] = Player[0].y;
				}
				if((c+(*it).i_hanyou[0])%loo<40 && (c+(*it).i_hanyou[0])%10==0)	ESNWay((*it).x, (*it).y+64, (*it).f_hanyou[0], (*it).f_hanyou[1], 30.0, 1, 2.5, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[1])%loo<40 && (c+(*it).i_hanyou[1])%10==0)	ESNWay((*it).x-52, (*it).y-44, (*it).f_hanyou[2], (*it).f_hanyou[3], 30.0, 1, 2.5, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[2])%loo<40 && (c+(*it).i_hanyou[2])%10==0)	ESNWay((*it).x+52, (*it).y-44, (*it).f_hanyou[4], (*it).f_hanyou[5], 30.0, 1, 2.5, ESHOT(RICE,BLUE), false, 0, 5);
			}
		}
		else if(level==NORMAL){
			int loo = Loo(120,60);
			if(c==0){
				(*it).i_hanyou[0] = get_rand(loo);
				(*it).i_hanyou[1] = get_rand(loo);
				(*it).i_hanyou[2] = get_rand(loo);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = Player[0].x;
				(*it).f_hanyou[3] = Player[0].y;
				(*it).f_hanyou[4] = Player[0].x;
				(*it).f_hanyou[5] = Player[0].y;
			}
			if((*it).y<CENTER_Y){
				if((c+(*it).i_hanyou[0])%loo==0){
					(*it).f_hanyou[0] = Player[0].x;
					(*it).f_hanyou[1] = Player[0].y;
				}
				if((c+(*it).i_hanyou[1])%loo==0){
					(*it).f_hanyou[2] = Player[0].x;
					(*it).f_hanyou[3] = Player[0].y;
				}
				if((c+(*it).i_hanyou[2])%loo==0){
					(*it).f_hanyou[4] = Player[0].x;
					(*it).f_hanyou[5] = Player[0].y;
				}
				if((c+(*it).i_hanyou[0])%loo<20 && (c+(*it).i_hanyou[0])%8==0)	ESNWay((*it).x, (*it).y+64, (*it).f_hanyou[0], (*it).f_hanyou[1], 30.0, 5, 3.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[1])%loo<20 && (c+(*it).i_hanyou[1])%8==0)	ESNWay((*it).x-52, (*it).y-44, (*it).f_hanyou[2], (*it).f_hanyou[3], 30.0, 5, 3.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[2])%loo<20 && (c+(*it).i_hanyou[2])%8==0)	ESNWay((*it).x+52, (*it).y-44, (*it).f_hanyou[4], (*it).f_hanyou[5], 30.0, 5, 3.0, ESHOT(RICE,BLUE), false, 0, 5);
			}
		}
		else if(level==HARD){
			int loo = Loo(100,50);
			if(c==0){
				(*it).i_hanyou[0] = get_rand(loo);
				(*it).i_hanyou[1] = get_rand(loo);
				(*it).i_hanyou[2] = get_rand(loo);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = Player[0].x;
				(*it).f_hanyou[3] = Player[0].y;
				(*it).f_hanyou[4] = Player[0].x;
				(*it).f_hanyou[5] = Player[0].y;
			}
			if((*it).y<CENTER_Y){
				if((c+(*it).i_hanyou[0])%loo==0){
					(*it).f_hanyou[0] = Player[0].x;
					(*it).f_hanyou[1] = Player[0].y;
				}
				if((c+(*it).i_hanyou[1])%loo==0){
					(*it).f_hanyou[2] = Player[0].x;
					(*it).f_hanyou[3] = Player[0].y;
				}
				if((c+(*it).i_hanyou[2])%loo==0){
					(*it).f_hanyou[4] = Player[0].x;
					(*it).f_hanyou[5] = Player[0].y;
				}
				if((c+(*it).i_hanyou[0])%loo<20 && (c+(*it).i_hanyou[0])%5==0)	ESNWay((*it).x, (*it).y+64, (*it).f_hanyou[0], (*it).f_hanyou[1], 25.0, 7, 4.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[1])%loo<20 && (c+(*it).i_hanyou[1])%5==0)	ESNWay((*it).x-52, (*it).y-44, (*it).f_hanyou[2], (*it).f_hanyou[3], 25.0, 7, 4.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[2])%loo<20 && (c+(*it).i_hanyou[2])%5==0)	ESNWay((*it).x+52, (*it).y-44, (*it).f_hanyou[4], (*it).f_hanyou[5], 25.0, 7, 4.0, ESHOT(RICE,BLUE), false, 0, 5);
			}
		}
		else if(level==LUNATIC){
			int loo = Loo(60,40);
			if(c==0){
				(*it).i_hanyou[0] = get_rand(loo);
				(*it).i_hanyou[1] = get_rand(loo);
				(*it).i_hanyou[2] = get_rand(loo);
				(*it).i_hanyou[3] = get_rand(loo);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = Player[0].x;
				(*it).f_hanyou[3] = Player[0].y;
				(*it).f_hanyou[4] = Player[0].x;
				(*it).f_hanyou[5] = Player[0].y;
				(*it).f_hanyou[6] = Player[0].x;
				(*it).f_hanyou[7] = Player[0].y;
			}
			if((*it).y<CENTER_Y){
				if((c+(*it).i_hanyou[0])%loo==0){
					(*it).f_hanyou[0] = Player[0].x;
					(*it).f_hanyou[1] = Player[0].y;
				}
				if((c+(*it).i_hanyou[1])%loo==0){
					(*it).f_hanyou[2] = Player[0].x;
					(*it).f_hanyou[3] = Player[0].y;
				}
				if((c+(*it).i_hanyou[2])%loo==0){
					(*it).f_hanyou[4] = Player[0].x;
					(*it).f_hanyou[5] = Player[0].y;
				}
				if((c+(*it).i_hanyou[3])%loo==0){
					(*it).f_hanyou[6] = Player[0].x;
					(*it).f_hanyou[7] = Player[0].y;
				}
				if((c+(*it).i_hanyou[0])%loo<30 && (c+(*it).i_hanyou[0])%4==0)	ESNWay((*it).x, (*it).y+64, (*it).f_hanyou[0], (*it).f_hanyou[1], 20.0, 7, 5.5, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[1])%loo<30 && (c+(*it).i_hanyou[1])%4==0)	ESNWay((*it).x-52, (*it).y-44, (*it).f_hanyou[2], (*it).f_hanyou[3], 20.0, 7, 5.5, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[2])%loo<30 && (c+(*it).i_hanyou[2])%4==0)	ESNWay((*it).x+52, (*it).y-44, (*it).f_hanyou[4], (*it).f_hanyou[5], 20.0, 7, 5.5, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[3])%loo<30 && (c+(*it).i_hanyou[2])%4==0)	ESNWay((*it).x, (*it).y, (*it).f_hanyou[6], (*it).f_hanyou[7], 20.0, 7, 5.5, ESHOT(RICE,BLUE), false, 0, 5);
			}
		}
		else if(level==IMPOSSIBLE){
			int loo = Loo(40,40);
			if(c==0){
				(*it).i_hanyou[0] = get_rand(loo);
				(*it).i_hanyou[1] = get_rand(loo);
				(*it).i_hanyou[2] = get_rand(loo);
				(*it).i_hanyou[3] = get_rand(loo);
				(*it).f_hanyou[0] = Player[0].x;
				(*it).f_hanyou[1] = Player[0].y;
				(*it).f_hanyou[2] = Player[0].x;
				(*it).f_hanyou[3] = Player[0].y;
				(*it).f_hanyou[4] = Player[0].x;
				(*it).f_hanyou[5] = Player[0].y;
				(*it).f_hanyou[6] = Player[0].x;
				(*it).f_hanyou[7] = Player[0].y;
			}
			if((*it).y<CENTER_Y){
				if((c+(*it).i_hanyou[0])%loo==0){
					(*it).f_hanyou[0] = Player[0].x;
					(*it).f_hanyou[1] = Player[0].y;
				}
				if((c+(*it).i_hanyou[1])%loo==0){
					(*it).f_hanyou[2] = Player[0].x;
					(*it).f_hanyou[3] = Player[0].y;
				}
				if((c+(*it).i_hanyou[2])%loo==0){
					(*it).f_hanyou[4] = Player[0].x;
					(*it).f_hanyou[5] = Player[0].y;
				}
				if((c+(*it).i_hanyou[3])%loo==0){
					(*it).f_hanyou[6] = Player[0].x;
					(*it).f_hanyou[7] = Player[0].y;
				}
				if((c+(*it).i_hanyou[0])%loo<30 && (c+(*it).i_hanyou[0])%2==0)	ESNWay((*it).x, (*it).y+64, (*it).f_hanyou[0], (*it).f_hanyou[1], 20.0, 11, 11.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[1])%loo<30 && (c+(*it).i_hanyou[1])%2==0)	ESNWay((*it).x-52, (*it).y-44, (*it).f_hanyou[2], (*it).f_hanyou[3], 20.0, 11, 11.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[2])%loo<30 && (c+(*it).i_hanyou[2])%2==0)	ESNWay((*it).x+52, (*it).y-44, (*it).f_hanyou[4], (*it).f_hanyou[5], 20.0, 11, 11.0, ESHOT(RICE,BLUE), false, 0, 5);
				if((c+(*it).i_hanyou[3])%loo<30 && (c+(*it).i_hanyou[2])%2==0)	ESNWay((*it).x, (*it).y, (*it).f_hanyou[6], (*it).f_hanyou[7], 20.0, 11, 11.0, ESHOT(RICE,BLUE), false, 0, 5);
			}
		}
	}
	else if(p==3){//肉弾戦車(Nikudan Sensha)
		if(c==0){
			(*it).i_hanyou[0] = get_rand(120);
		}
		if((*it).y>0 && (*it).x<440){
			list<BOSSDATA>::iterator bit = Boss.begin();
			if(Boss.size()==0||(*bit).death_count>0){
				if(level==EASY){
					if(Player[0].hyper_count==0){}
					else{
						if((c+(*it).i_hanyou[0])%40==0){
							ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 3.0, ESHOT(MEDIUM,RED), false, 0, 5);
						}
					}
				}
				else if(level==NORMAL){
					int loo = Loo(180,40);	
					if(c%loo<20 && c%5==0 && (*it).y<CENTER_Y){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 4.0, ESHOT(MEDIUM,RED), false, 0, 5);
					}
				}
				else if(level==HARD){
					int loo = Loo(120,35);	
					if(c%loo<20 && c%5==0 && (*it).y<CENTER_Y){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 5.0, ESHOT(MEDIUM,RED), false, 0, 5);
					}
				}
				else if(level==LUNATIC){
					int loo = Loo(120,30);	
					if(c%loo<30 && c%5==0 && (*it).y<CENTER_Y){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 20.0, 1, 6.0, ESHOT(MEDIUM,RED), false, 0, 5);
					}
				}
				else if(level==IMPOSSIBLE){
					int loo = Loo(60,20);	
					if(c%loo<30 && c%5==0 && (*it).y<CENTER_Y){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 20.0, 3, 10.0, ESHOT(MEDIUM,RED), false, 0, 5);
					}
				}
			}
		}
	}
	else if(p==4){//小弾戦車(Small Bullet Sensha)
		if(c==0){
			(*it).i_hanyou[0] = get_rand(120);
		}
		if((*it).y>0 && (*it).y<CENTER_Y && (*it).x<440){
			list<BOSSDATA>::iterator bit = Boss.begin();
			if(Boss.size()==0||(*bit).death_count>0){
				if(level==EASY){
					if(Player[0].hyper_count==0){}
					else{
						if((c+(*it).i_hanyou[0])%60==0){
							ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 1.0, ESHOT(SMALL,RED), false, 0, 5);
						}
					}
				}
				else if(level==NORMAL){
					if(Player[0].hyper_count==0){}
					else{
						if((c+(*it).i_hanyou[0])%30==0){
							ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 2.0, ESHOT(SMALL,RED), false, 0, 5);
						}
					}
				}
				else if(level==HARD){
					if(Player[0].hyper_count==0){}
					else{
						if((c+(*it).i_hanyou[0])%25==0){
							ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 3.0, ESHOT(SMALL,RED), false, 0, 5);
						}
					}
				}
				else if(level==LUNATIC){
					if(Player[0].hyper_count==0){}
					else{
						if((c+(*it).i_hanyou[0])%20==0){
							ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 4.0, ESHOT(SMALL,BLUE), false, 0, 5);
						}
					}
				}
				else if(level==IMPOSSIBLE){
					if(Player[0].hyper_count==0){}
					else{
						if((c+(*it).i_hanyou[0])%20==0){
							ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 3, 5.0, ESHOT(SMALL,BLUE), false, 0, 5);
						}
					}
				}
			}
		}
	}
	else if(p==5){//スピリット(Spirit)
		if((*it).y<CENTER_Y){
			if(level==EASY){
				if(c>=60 && c<120){
					c = c-60;
					if(c==0 || c==120){
						(*it).f_hanyou[0] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x-18));
						(*it).f_hanyou[1] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x+18));
						(*it).i_hanyou[0] = 1;
					}
					if(Player[0].hyper_count==0){
						if(c%10==0){
							if(c<120){
								ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 30.0, (*it).i_hanyou[0], 3.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							else{
								ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 30.0, (*it).i_hanyou[0], 3.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							(*it).i_hanyou[0]++;
						}
					}
					else{
						if(c%8==0){
							ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 15.0, (*it).i_hanyou[0], 3.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 15.0, (*it).i_hanyou[0], 3.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							(*it).i_hanyou[0]++;
						}
					}
				}
			}
			else if(level==NORMAL){
				if(c>=60 && c<240){
					c = c-60;
					if(c==0 || c==120){
						(*it).f_hanyou[0] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x-18));
						(*it).f_hanyou[1] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x+18));
						(*it).i_hanyou[0] = 1;
					}
					if(Player[0].hyper_count==0){
						if(c%10==0){
							if(c<120){
								ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 24.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							else{
								ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 24.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							(*it).i_hanyou[0]++;
						}
					}
					else{
						if(c%8==0){
							ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 12.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 12.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							(*it).i_hanyou[0]++;
						}
					}
				}
			}
			else if(level==HARD){
				if(c>=60 && c<240){
					c = c-60;
					if(c==0 || c==120){
						(*it).f_hanyou[0] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x-18));
						(*it).f_hanyou[1] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x+18));
						(*it).i_hanyou[0] = 1;
					}
					if(Player[0].hyper_count==0){
						if(c%8==0){
							if(c<120){
								ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 20.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							else{
								ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 20.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							(*it).i_hanyou[0]++;
						}
					}
					else{
						if(c%6==0){
							ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 10.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 10.0, (*it).i_hanyou[0], 4.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							(*it).i_hanyou[0]++;
						}
					}
				}
			}
			else if(level==LUNATIC){
				if(c>=60 && c<240){
					c = c-60;
					if(c==0 || c==120){
						(*it).f_hanyou[0] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x-18));
						(*it).f_hanyou[1] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x+18));
						(*it).i_hanyou[0] = 1;
					}
					if(Player[0].hyper_count==0){
						if(c%7==0){
							if(c<120){
								ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 20.0, (*it).i_hanyou[0], 5.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							else{
								ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 20.0, (*it).i_hanyou[0], 5.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							(*it).i_hanyou[0]++;
						}
					}
					else{
						if(c%6==0){
							ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 10.0, (*it).i_hanyou[0], 5.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 10.0, (*it).i_hanyou[0], 5.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							(*it).i_hanyou[0]++;
						}
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c>=60 && c<240){
					c = c-60;
					if(c==0 || c==120){
						(*it).f_hanyou[0] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x-18));
						(*it).f_hanyou[1] = Atan2(Player[0].y-((*it).y+18), Player[0].x-((*it).x+18));
						(*it).i_hanyou[0] = 1;
					}
					if(Player[0].hyper_count==0){
						if(c%6==0){
							if(c<120){
								ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 6.0, (*it).i_hanyou[0], 6.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							else{
								ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 6.0, (*it).i_hanyou[0], 6.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							}
							(*it).i_hanyou[0]++;
						}
					}
					else{
						if(c%3==0){
							ESNWay((*it).x-18, (*it).y+18, (*it).x-18+cos((*it).f_hanyou[0]), (*it).y+18+sin((*it).f_hanyou[0]), 3.0, (*it).i_hanyou[0], 6.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							ESNWay((*it).x+18, (*it).y+18, (*it).x+18+cos((*it).f_hanyou[1]), (*it).y+18+sin((*it).f_hanyou[1]), 3.0, (*it).i_hanyou[0], 6.0, ESHOT(UROKO,PURPLE), false, 0, 5);
							(*it).i_hanyou[0]++;
						}
					}
				}
			}
		}
	}
	else if(p==6){//マイク(Mike)
		if((*it).y<CENTER_Y){
			if(level==EASY){}
			else if(level==NORMAL){
				int loo = Loo(120,60);	
				if(c>0 && c%loo==0){
					ang_plus = 15.0;
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 12, 2.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
					ang_plus = 0.0;
				}
			}
			else if(level==HARD){
				int loo = Loo(120,30);	
				ang_plus = 9.0;
				if(c>0 && c%loo==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 18.0, 20, 3.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
				ang_plus = 0.0;
			}
			else if(level==LUNATIC){
				int loo = Loo(90,30);	
				if(c>0 && c%loo==0){
					ang_plus = 6.0;
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 5.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
					ang_plus = 0.0;
				}
			}
			else if(level==IMPOSSIBLE){
				int loo = Loo(60,10);	
				if(c>0 && c%loo==0){
					for(int i=0;i<6;i++){
						ang_plus = 2.0*i;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 6.0-0.8*i, ESHOT(MEDIUM2,GREEN), false, 0, 10);
					}
					ang_plus = 0.0;
				}
			}
		}
	}
	else if(p==7){//コーン(Corn)
		bRG = false;
		if(level==EASY){
			if(Player[0].hyper_count>0){
				if(c==15){
					for(int i=0;i<3;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 0.0, 1, 4.1-0.5*i, ESHOT(ICE,BLUE), false, 0, 10);
				}
			}
		}
		else if(level==NORMAL){
			if(Player[0].hyper_count>0){
				if(c==15){
					for(int i=0;i<4;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 0.0, 1, 5.0-0.5*i, ESHOT(ICE,BLUE), false, 0, 10);
				}
			}
		
		}
		else if(level==HARD){
			if(Player[0].hyper_count>0){
				if(c==15){
					for(int i=0;i<5;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 0.0, 1, 5.4-0.5*i, ESHOT(ICE,BLUE), false, 0, 10);
				}
			}
		}
		else if(level==LUNATIC){
			if(c==15){
				for(int i=0;i<6;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 0.0, 1, 5.8-0.5*i, ESHOT(ICE,BLUE), false, 0, 10);
			}
		}
		else if(level==IMPOSSIBLE){
			if(c==15){
				for(int i=0;i<12;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 72.0, 5, 8.3-0.5*i, ESHOT(ICE,BLUE), false, 0, 10);
			}
		}
	}
	else if(p==8 || p==9){//マイク(弾符「マイクポップコーンは神」)
		bES = false;
		bRG = false;
		float sx = Player[0].x - (*it).x;
		float sy = Player[0].y - (*it).y;
		float sq = sqrt(sx*sx+sy*sy);
		int img;
		if(p==8)	img = ESHOT(ICE,GREEN);
		else if(p==9)	img = ESHOT(ICE,WATER);
		if(level==EASY){
			if(sq>60){
				int per = 20;
				if(Player[0].hyper_count>0)	per = 10;
				if(c%per==0){
					PlaySound(23);
					float angle = Radian((*it).f_hanyou[0],FALSE);
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[1]+angle+180*i, 1.0, img, false, 0, 30, 0.0, 120, flag);
					}
				}
			}
		}
		else if(level==NORMAL){
			if(sq>60){
				int per = 10;
				if(Player[0].hyper_count>0)	per = 5;
				if(c%per==0){
					PlaySound(23);
					float angle = Radian((*it).f_hanyou[0],FALSE);
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[1]+angle+180*i, 1.0, img, false, 0, 30, 0.0, 120, flag);
					}
				}
			}
		}
		else if(level==HARD){
			if(sq>60){
				int per = 10;
				if(Player[0].hyper_count>0)	per = 5;
				if(c%per==0){
					PlaySound(23);
					float angle = Radian((*it).f_hanyou[0],FALSE);
					float rand = 0.1*get_rand(1200);
					for(int i=0;i<3;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[1]+angle+120*i, 1.0, img, false, 0, 30, 0.0, 120, flag);
					}
				}
			}
		}
		else if(level==LUNATIC){
			if(sq>60){
				int per = 8;
				if(Player[0].hyper_count>0)	per = 4;
				if(c%per==0){
					PlaySound(23);
					float angle = Radian((*it).f_hanyou[0],FALSE);
					for(int i=0;i<3;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[1]+angle+120*i, 1.0, img, false, 0, 30, 0.0, 120, flag);
					}
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(sq>60){
				int per = 8;
				if(Player[0].hyper_count>0)	per = 4;
				if(c%per==0){
					PlaySound(23);
					float angle = Radian((*it).f_hanyou[0],FALSE);
					for(int i=0;i<5;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[1]+angle+72*i, 1.0, img, false, 0, 30, 0.0, 120, flag);
					}
				}
			}
		}
	}
	else if(p==10){//フラフィ・ソロー(Fraphy Sorrow)
		if(level==EASY){}
		else if(level==NORMAL){
			int loo = Loo(50, 10);
			if(c%loo==loo/2&&(*it).y<CENTER_Y+100){
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 0.0, 1, 1.5, ESHOT(MEDIUM,BLUE), false, 0, 10);
			}
		}
		else if(level==HARD){
			int loo = Loo(40, 10);
			if(c%loo==loo/2&&(*it).y<CENTER_Y+100){
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 0.0, 1, 2.0, ESHOT(MEDIUM,BLUE), false, 0, 10);
			}
		}
		else if(level==LUNATIC){
			int loo = Loo(40, 5);
			if(c%loo==loo/2&&(*it).y<CENTER_Y+100){
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 45.0, 3, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 10);
			}
		}
		else if(level==IMPOSSIBLE){
			int loo = Loo(30, 5);
			if(c%loo==loo/2&&(*it).y<CENTER_Y+100){
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 2.0, 3, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 10);
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 90.0, 2, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 10);
			}
		}
	}
	else if(p==11){//銀次(Ginji)
		if(level==EASY){
			if(c>=90){
				if(c<150 && c%2==0){
					ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 60.0, 2, 2.0+0.06*(c-90), ESHOT(MEDIUM,PURPLE), true, 0, 10);
				}
			}
		}
		else if(level==NORMAL){
			if(c>=90){
				if(c<150 && c%2==0){
					ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 40.0, 2, 2.0+0.1*(c-90), ESHOT(MEDIUM,PURPLE), true, 0, 10);
				}
			}
		}
		else if(level==HARD){
			if(c>=90){
				if(c<150 && c%2==0){
					ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 40.0, 3, 2.0+0.12*(c-90), ESHOT(MEDIUM,PURPLE), true, 0, 10);
				}
			}
		}
		else if(level==LUNATIC){
			if(c>=90){
				if(c<150 && c%2==0){
					ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 5.0, 6, 2.0+0.12*(c-90), ESHOT(MEDIUM,PURPLE), true, 0, 10);
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(c>=90){
				if(c<180 && c%2==0){
					ESNWay((*it).x, (*it).y+24, Player[0].x, Player[0].y, 8.0, 8, 2.0+0.1*(c-90), ESHOT(MEDIUM,PURPLE), true, 0, 10);
				}
			}
		}
	}
	else if(p==12){//気符「英語雲散霧消」の見えない敵
		bES = false;
		bRG = false;
		if(level==EASY){
			if(c%15==0){
				PlaySound(23);
				EfMake3((*it).x,(*it).y,0);
			}
			if(c%45==0){
				float angle = Radian(get_rand(360),TRUE);
				float l = get_rand(30);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y + l*sin(angle);
				ESMake(x, y, get_rand(360), 0.5+0.1*get_rand(5), ESHOT(MEDIUM,BLUE), false, 0, 60, 0.0, 60, false);
			}
		}
		else if(level==NORMAL){
			if(c%10==0){
				PlaySound(23);
				EfMake3((*it).x,(*it).y,0);
			}
			if(c%40==0){
				float angle = Radian(get_rand(360),TRUE);
				float l = get_rand(30);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y + l*sin(angle);
				ESMake(x, y, get_rand(360), 0.5+0.1*get_rand(5), ESHOT(MEDIUM,BLUE), false, 0, 60, 0.0, 60, false);
			}
		}
		else if(level==HARD){
			if(c%10==0){
				PlaySound(23);
				EfMake3((*it).x,(*it).y,0);
			}
			if(c%30==0){
				float angle = Radian(get_rand(360),TRUE);
				float l = get_rand(30);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y + l*sin(angle);
				ESMake(x, y, get_rand(360), 0.5+0.1*get_rand(5), ESHOT(MEDIUM,BLUE), false, 0, 60, 0.0, 60, false);
			}
		}
		else if(level==LUNATIC){
			if(c%10==0){
				PlaySound(23);
				EfMake3((*it).x,(*it).y,0);
			}
			if(c%20==0){
				float angle = Radian(get_rand(360),TRUE);
				float l = get_rand(30);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y + l*sin(angle);
				ESMake(x, y, get_rand(360), 0.5+0.1*get_rand(10), ESHOT(MEDIUM,BLUE), false, 0, 60, 0.0, 120, false);
			}
		}
		else if(level==IMPOSSIBLE){
			if(c%10==0){
				PlaySound(23);
				EfMake3((*it).x,(*it).y,0);
			}
			if(c%4==0){
				float angle = Radian(get_rand(360),TRUE);
				float l = get_rand(30);
				float x = (*it).x + l*cos(angle);
				float y = (*it).y + l*sin(angle);
				ESMake(x, y, get_rand(360), 0.5+0.1*get_rand(10), ESHOT(MEDIUM,BLUE), false, 0, 60, 0.0, 120, false);
			}
		}
	}
	else if(p>=13 && p<=16){//「早苗は俺の嫁」
		bES = false;
		bRG = false;
		if(p==13 || p==14){
			if((*it).x>0){
				int per;
				if(level==EASY)		per = 4;
				else if(level==NORMAL)	per = 3;
				else if(level==HARD)	per = 2;
				if(c%per==0){
					if(p==13)	(*it).f_hanyou[0] = 60.0+4.8*c;
					else if(p==14)	(*it).f_hanyou[0] = 60.0+4.8*c+36.0;
					PlaySound(22);
					float angle = Atan2((*it).move_y,(*it).move_x);
					for(int i=0;i<5;i++){
						int img,pat;
						if(p==13){
							img = ESHOT(RICE,BLUE);
							pat = 6+i;
						}
						else if(p==14){
							img = ESHOT(SMALL,GREEN);
							pat = 11+i;
						}
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, angle, 0.0, img, false, pat, 25, 0.0, 0, flag, (*it).f_hanyou[0]);
					}
				}
			}
		}
		else if(p==15 || p==16){
			if((*it).x>0){
				int per;
				if(level==LUNATIC)		per = 1;
				else if(level==IMPOSSIBLE)	per = 1;
				if(c%per==0){
					if(p==15)	(*it).f_hanyou[0] = 7.5*c;
					else if(p==16)	(*it).f_hanyou[0] = 7.5*c+120.0;
					PlaySound(22);
					float angle = Atan2((*it).move_y,(*it).move_x);
					for(int i=0;i<5;i++){
						int img,pat;
						if(p==15){
							img = ESHOT(RICE,BLUE);
							pat = 16+i;
						}
						else if(p==16){
							img = ESHOT(SMALL,RED);
							pat = 21+i;
						}
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, angle, 0.0, img, false, pat, 25, 0.0, 0, flag, (*it).f_hanyou[0]);
						if(level==IMPOSSIBLE){
							list<BOSSDATA>::iterator bit = Boss.begin();
							float sx = (*it).x-(*bit).x;
							float sy = (*it).y-(*bit).y;
							float l = sqrt(sx*sx+sy*sy);
							float an = Atan2(sy,sx);
							float x = (*bit).x + 1.5*l*cos(an);
							float y = (*bit).y + 1.5*l*sin(an);
							if(p==15)	img = ESHOT(RICE,WATER);
							else if(p==16)	img = ESHOT(SMALL,GREEN);
							ESMake(x, y, angle, 0.0, img, false, pat, 25, 0.0, 0, flag, (*it).f_hanyou[0]);
						}
					}
				}
			}
		}
	}
	else if(p==17){//ヴォイド(Void)
		if(level==EASY){
			int loo = Loo(20,10);
			if(c==60){
				(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[1] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[2] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[3] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[4] = 120.0;
			}
			if(c>60){
				c-=60;
				if(c%loo==0){
					//PlaySound(22);
					for(int j=0;j<4;j++){
						for(int i=0;i<3;i++){
							float x,y;
							if(j==0){
								x = (*it).x-40;
								y = (*it).y-30;
							}
							else if(j==1){
								x = (*it).x+40;
								y = (*it).y-30;
							}
							else if(j==2){
								x = (*it).x-40;
								y = (*it).y+50;
							}
							else if(j==3){
								x = (*it).x+40;
								y = (*it).y+50;
							}
							float angle = (*it).f_hanyou[j];
							bool flag = false;
							if(i==0)	flag = true;
							else if(i==1)	angle -= (*it).f_hanyou[4];
							else if(i==2)	angle += (*it).f_hanyou[4];
							ESMake(x, y, angle, 2.0, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
					}
					(*it).f_hanyou[4] -= 8.0;
				}
			}
		}
		else if(level==NORMAL){
			int loo = Loo(15,10);
			if(c==60){
				(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[1] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[2] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[3] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[4] = 120.0;
			}
			if(c>60){
				c-=60;
				if(c%loo==0){
					//PlaySound(22);
					for(int j=0;j<4;j++){
						for(int i=0;i<3;i++){
							float x,y;
							if(j==0){
								x = (*it).x-40;
								y = (*it).y-30;
							}
							else if(j==1){
								x = (*it).x+40;
								y = (*it).y-30;
							}
							else if(j==2){
								x = (*it).x-40;
								y = (*it).y+50;
							}
							else if(j==3){
								x = (*it).x+40;
								y = (*it).y+50;
							}
							float angle = (*it).f_hanyou[j];
							bool flag = false;
							if(i==0)	flag = true;
							else if(i==1)	angle -= (*it).f_hanyou[4];
							else if(i==2)	angle += (*it).f_hanyou[4];
							ESMake(x, y, angle, 2.5, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
					}
					(*it).f_hanyou[4] -= 8.0;
				}
			}
		}
		else if(level==HARD){
			int loo = Loo(10,5);
			if(c==60){
				(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[1] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[2] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[3] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[4] = 120.0;
			}
			if(c>60){
				c-=60;
				if(c%loo==0){
					//PlaySound(22);
					for(int j=0;j<4;j++){
						for(int i=0;i<3;i++){
							float x,y;
							if(j==0){
								x = (*it).x-40;
								y = (*it).y-30;
							}
							else if(j==1){
								x = (*it).x+40;
								y = (*it).y-30;
							}
							else if(j==2){
								x = (*it).x-40;
								y = (*it).y+50;
							}
							else if(j==3){
								x = (*it).x+40;
								y = (*it).y+50;
							}
							float angle = (*it).f_hanyou[j];
							bool flag = false;
							if(i==0)	flag = true;
							else if(i==1)	angle -= (*it).f_hanyou[4];
							else if(i==2)	angle += (*it).f_hanyou[4];
							ESMake(x, y, angle, 3.0, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
					}
					(*it).f_hanyou[4] -= 5.0;
				}
			}
		}
		else if(level==LUNATIC){
			int loo = Loo(8,5);
			if(c==60){
				(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[1] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[2] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[3] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[4] = 120.0;
			}
			if(c>60){
				c-=60;
				if(c%loo==0){
					//PlaySound(22);
					for(int j=0;j<4;j++){
						for(int i=0;i<5;i++){
							float x,y;
							if(j==0){
								x = (*it).x-40;
								y = (*it).y-30;
							}
							else if(j==1){
								x = (*it).x+40;
								y = (*it).y-30;
							}
							else if(j==2){
								x = (*it).x-40;
								y = (*it).y+50;
							}
							else if(j==3){
								x = (*it).x+40;
								y = (*it).y+50;
							}
							float angle = (*it).f_hanyou[j];
							bool flag = false;
							if(i==0)	flag = true;
							else if(i==1)	angle -= (*it).f_hanyou[4];
							else if(i==2)	angle += (*it).f_hanyou[4];
							else if(i==3)	angle -= 2*(*it).f_hanyou[4];
							else if(i==4)	angle += 2*(*it).f_hanyou[4];
							ESMake(x, y, angle, 3.5, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
					}
					(*it).f_hanyou[4] -= 5.0;
				}
			}
		}
		else if(level==IMPOSSIBLE){
			int loo = Loo(5,2);
			if(c==60){
				(*it).f_hanyou[0] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[1] = Radian(Atan2(Player[0].y-((*it).y-30), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[2] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x-40)),FALSE);
				(*it).f_hanyou[3] = Radian(Atan2(Player[0].y-((*it).y+50), Player[0].x-((*it).x+40)),FALSE);
				(*it).f_hanyou[4] = 120.0;
			}
			if(c>60){
				c-=60;
				if(c%loo==0){
					//PlaySound(22);
					for(int j=0;j<4;j++){
						for(int i=0;i<5;i++){
							float x,y;
							if(j==0){
								x = (*it).x-40;
								y = (*it).y-30;
							}
							else if(j==1){
								x = (*it).x+40;
								y = (*it).y-30;
							}
							else if(j==2){
								x = (*it).x-40;
								y = (*it).y+50;
							}
							else if(j==3){
								x = (*it).x+40;
								y = (*it).y+50;
							}
							float angle = (*it).f_hanyou[j];
							bool flag = false;
							if(i==0)	flag = true;
							else if(i==1)	angle -= (*it).f_hanyou[4];
							else if(i==2)	angle += (*it).f_hanyou[4];
							else if(i==3)	angle -= 2*(*it).f_hanyou[4];
							else if(i==4)	angle += 2*(*it).f_hanyou[4];
							ESMake(x, y, angle, 4.0, ESHOT(MEDIUM,PURPLE), false, 0, 10, 0.0, 0, flag);				
						}
					}
					(*it).f_hanyou[4] -= 5.0;
				}
			}
		}
	}
	else if(p==18){//銀次(Ginji)
		if(level==EASY){
			int loo = Loo(15,10);
			if(c>=90){
				if(c<210 && c%loo==0){
					//PlaySound(22);
					for(int i=0;i<1;i++){
						float d = get_rand(30);
						float angle = Radian(get_rand(360),TRUE);
						float x = (*it).x + d*cos(angle);
						float y = (*it).y + 24 + d*sin(angle);
						ang_plus = -2.0+0.1*get_rand(40);
						ESNWay(x, y, Player[0].x, Player[0].y, 0.0, 1, 2.0, ESHOT(MEDIUM,BLUE), false, 0, 5, 0.0, 0);
						ang_plus = 0;
					}
				}
			}
		}
		else if(level==NORMAL){
			int loo = Loo(15,10);
			if(c>=90){
				if(c<210 && c%loo==0){
					//PlaySound(22);
					for(int i=0;i<3;i++){
						float d = get_rand(30);
						float angle = Radian(get_rand(360),TRUE);
						float x = (*it).x + d*cos(angle);
						float y = (*it).y + 24 + d*sin(angle);
						ang_plus = -4.0+0.1*get_rand(80);
						ESNWay(x, y, Player[0].x, Player[0].y, 0.0, 1, 2.0, ESHOT(MEDIUM,BLUE), false, 0, 5, 0.0, 0);
						ang_plus = 0;
					}
				}
			}
		}
		else if(level==HARD){
			int loo = Loo(10,5);
			if(c>=90){
				if(c<210 && c%loo==0){
					//PlaySound(22);
					for(int i=0;i<3;i++){
						float d = get_rand(30);
						float angle = Radian(get_rand(360),TRUE);
						float x = (*it).x + d*cos(angle);
						float y = (*it).y + 24 + d*sin(angle);
						ang_plus = -5.0+0.1*get_rand(100);
						ESNWay(x, y, Player[0].x, Player[0].y, 0.0, 1, 2.0, ESHOT(MEDIUM,BLUE), false, 0, 5, 0.0, 0);
						ang_plus = 0;
					}
				}
			}
		}
		else if(level==LUNATIC){
			int loo = Loo(8,5);
			if(c>=90){
				if(c<210 && c%loo==0){
					//PlaySound(22);
					for(int i=0;i<3;i++){
						float d = get_rand(30);
						float angle = Radian(get_rand(360),TRUE);
						float x = (*it).x + d*cos(angle);
						float y = (*it).y + 24 + d*sin(angle);
						ang_plus = -5.0+0.1*get_rand(100);
						ESNWay(x, y, Player[0].x, Player[0].y, 70.0, 3, 2.0, ESHOT(MEDIUM,BLUE), false, 0, 5, 0.0, 0);
						ang_plus = 0;
					}
				}
			}
		}
		else if(level==IMPOSSIBLE){
			int loo = Loo(5,2);
			if(c>=90){
				if(c<210 && c%loo==0){
					//PlaySound(22);
					for(int i=0;i<3;i++){
						float d = get_rand(30);
						float angle = Radian(get_rand(360),TRUE);
						float x = (*it).x + d*cos(angle);
						float y = (*it).y + 24 + d*sin(angle);
						ang_plus = -5.0+0.1*get_rand(100);
						ESNWay(x, y, Player[0].x, Player[0].y, 50.0, 5, 3.0, ESHOT(MEDIUM,BLUE), false, 0, 5, 0.0, 0);
						ang_plus = 0;
					}
				}
			}
		}
	}
	else if(p==19){//レーザーテスト用
		if(c==40){// && c<50){
			float d = 50.0;
			float angle = Radian(36.0*(c-40),TRUE);
			float x = CENTER_X + d*cos(angle);
			float y = CENTER_Y + d/2.0*sin(angle);
			ESL2Make(x, y, 6.0, Radian(angle,FALSE), 2.0, BLUE, 1);
			ESL1Make(x, y, 6.0, 250.0, Radian(angle,FALSE)+180.0, 3.0, RED);
		}
	}
	else if(p==20){//3面小弾戦車(Small Bullet Sensha)
		if(c==0){
			(*it).i_hanyou[0] = get_rand(120);
		}
		float sx = Player[0].x-(*it).x;
		float sy = Player[0].y-(*it).y;
		float d = sqrt(sx*sx+sy*sy);
		if((*it).bDelete==true && d>120 && (*it).y<CENTER_Y){
			if(level==EASY){
				if(Player[0].hyper_count==0){}
				else{
					if((c+(*it).i_hanyou[0])%120==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 3.0, ESHOT(SMALL,RED), false, 0, 5);
					}
				}
			}
			else if(level==NORMAL){
				if(Player[0].hyper_count==0){}
				else{
					if((c+(*it).i_hanyou[0])%60==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 5.0, ESHOT(SMALL,RED), false, 0, 5);
					}
				}
			}
			else if(level==HARD){
				if(Player[0].hyper_count==0){}
				else{
					if((c+(*it).i_hanyou[0])%50==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 6.0, ESHOT(SMALL,RED), false, 0, 5);
					}
				}
			}
			else if(level==LUNATIC){
				if(Player[0].hyper_count==0){}
				else{
					if((c+(*it).i_hanyou[0])%40==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 1, 8.0, ESHOT(SMALL,BLUE), false, 0, 5);
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(Player[0].hyper_count==0){}
				else{
					if((c+(*it).i_hanyou[0])%40==0){
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 30.0, 3, 12.0, ESHOT(SMALL,BLUE), false, 0, 5);
					}
				}
			}
		}
	}
	else if(p==21){//3面中型戦車(Medium Bullet Sensha)
		c -= (*it).i_hanyou[0];
		int freq = 1;
		if(Player[0].hyper_count>0)	freq = 2;
		float sx = Player[0].x-(*it).x;
		float sy = Player[0].y-(*it).y;
		float d = sqrt(sx*sx+sy*sy);
		if(c>60 && (*it).bDelete==true && d>120){
			c-=60;
			if(level==EASY){
				if(c%(40/freq)==0 && c<60){
					for(int i=0;i<5;i++){
						bool eff = false;
						if(i==0)	eff = true;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 4.0, 2, 4.0-0.5*i, ESHOT(MEDIUM,PURPLE), false, 0, 5, 0.0, 0, eff);
					}
				}
			}
			else if(level==NORMAL){
				if(c%(20/freq)==0 && c<60){
					for(int i=0;i<5;i++){
						bool eff = false;
						if(i==0)	eff = true;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 4.0, 3, 5.0-0.6*i, ESHOT(MEDIUM,PURPLE), false, 0, 5, 0.0, 0, eff);
					}
				}
			}
			else if(level==HARD){
				if(c%(20/freq)==0 && c<60){
					for(int i=0;i<5;i++){
						bool eff = false;
						if(i==0)	eff = true;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 4.0, 5, 6.0-0.8*i, ESHOT(MEDIUM,PURPLE), false, 0, 5, 0.0, 0, eff);
					}
				}
			}
			else if(level==LUNATIC){
				if(c%(20/freq)==0 && c<60){
					for(int i=0;i<10;i++){
						bool eff = false;
						if(i==0)	eff = true;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 4.0, 7, 7.0-0.5*i, ESHOT(MEDIUM,PURPLE), false, 0, 5, 0.0, 0, eff);
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%(18/freq)==0 && c<60){
					for(int i=0;i<10;i++){
						bool eff = false;
						if(i==0)	eff = true;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 4.0, 9, 7.0-0.5*i, ESHOT(MEDIUM,PURPLE), false, 0, 5, 0.0, 0, eff);
					}
				}
			}
		}
	}
	else if(p==22){//3面電車(Trained Train)
		float x[3],y[3],angle[3],px=Player[0].x,py=Player[0].y;
		x[0] = (*it).x;
		y[0] = (*it).y-46;
		x[1] = (*it).x-26;
		y[1] = (*it).y-18;
		x[2] = (*it).x+26;
		y[2] = (*it).y-18;
		int freq = 1;
		if(Player[0].hyper_count>0)	freq = 2;
		if((*it).bDelete==true && c>60){
			c-=120;
			if(level==EASY){
				if(c%(20/freq)==0){
					for(int i=1;i<3;i++){
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 1.5, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, true);				
					}
				}
				if(c%(180/freq)==0 && (*it).y<CENTER_Y){
					for(int i=0;i<3;i++){
						ESNWay(x[0], y[0], Player[0].x, Player[0].y, 45.0, 3, 3.0-0.5*i, ESHOT(OVAL,RED), false, 0, 5, 0.0, 0, true);
					}
				}
			}
			else if(level==NORMAL){
				if(c%(10/freq)==0){
					for(int i=1;i<3;i++){
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 2.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, true);				
					}
				}
				if(c%(120/freq)==0 && (*it).y<CENTER_Y){
					for(int i=0;i<3;i++){
						ESNWay(x[0], y[0], Player[0].x, Player[0].y, 25.0, 5, 4.0-0.5*i, ESHOT(OVAL,RED), false, 0, 5, 0.0, 0, true);
					}
				}
			}
			else if(level==HARD){
				if(c%(10/freq)==0){
					for(int i=1;i<3;i++){
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 3.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, true);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 2.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
					}
				}
				if(c%(120/freq)==0 && (*it).y<CENTER_Y){
					for(int i=0;i<5;i++){
						ESNWay(x[0], y[0], Player[0].x, Player[0].y, 25.0, 5, 5.0-0.5*i, ESHOT(OVAL,RED), false, 0, 5, 0.0, 0, true);
					}
				}
			}
			else if(level==LUNATIC){
				if(c%(10/freq)==0){
					for(int i=1;i<3;i++){
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 3.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, true);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 2.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 1.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
					}
				}
				if(c%(90/freq)==0 && (*it).y<CENTER_Y){
					for(int i=0;i<5;i++){
						ESNWay(x[0], y[0], Player[0].x, Player[0].y, 25.0, 6, 5.0-0.5*i, ESHOT(OVAL,RED), false, 0, 5, 0.0, 0, true);
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%(10/freq)==0){
					for(int i=1;i<3;i++){
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 5.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 4.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 3.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, true);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 2.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
						ESMake(x[i], y[i], (*it).f_hanyou[i-1], 1.0, ESHOT(ZAYAKU,BLUE), false, 0, 10, 0.0, 0, false);				
					}
				}
				if(c%(90/freq)==0 && (*it).y<CENTER_Y){
					for(int i=0;i<5;i++){
						ESNWay(x[0], y[0], Player[0].x, Player[0].y, 15.0, 10, 7.0-0.5*i, ESHOT(OVAL,RED), false, 0, 5, 0.0, 0, true);
					}
				}
			}
		}
	}
	else if(p==23){//3面マイク(Mike)
		if(level==EASY){}
		else if(level==NORMAL){
			ang_plus = 30.0;
			if(Player[0].hyper_count==0){
				if(c%100==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 60.0, 6, 2.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%50==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 60.0, 6, 2.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
			}
			ang_plus = 0.0;
		}
		else if(level==HARD){
			ang_plus = 18.0;
			if(Player[0].hyper_count==0){
				if(c%100==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 36.0, 10, 3.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%30==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 36.0, 10, 3.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
			}
			ang_plus = 0.0;
		}
		else if(level==LUNATIC){
			if(Player[0].hyper_count==0){
				if(c%80==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 24.0, 15, 5.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%30==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 24.0, 15, 5.0, ESHOT(MEDIUM2,GREEN), false, 0, 10);
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(Player[0].hyper_count==0){
				if(c>0 && c%60==0){
					for(int i=0;i<6;i++){
						ang_plus = 2.0*i;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 24.0, 15, 6.0-0.8*i, ESHOT(MEDIUM2,GREEN), false, 0, 10);
					}
					ang_plus = 0.0;
				}
			}
			else{
				if(c>0 && c%10==0){
					for(int i=0;i<6;i++){
						ang_plus = 2.0*i;
						ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 24.0, 15, 6.0-0.8*i, ESHOT(MEDIUM2,GREEN), false, 0, 10);
					}
					ang_plus = 0.0;
				}
			}
		}
	}
	else if(p==24){//3面アホが出すマイク
		bES = false;
		bRG = false;
		c = c%480;
		if(c==60 || c==210){
			PlaySound(22);
			if(level==EASY){
				for(int i=0;i<5;i++){
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 25.0, i+1, 0.0, ESHOT(UROKO,RED), false, 29, 10, 7.0-0.5*i, 50, true);
				}	
			}
			else if(level==NORMAL){
				for(int i=0;i<10;i++){
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 25.0, i+1, 0.0, ESHOT(UROKO,RED), false, 29, 10, 7.0-0.5*i, 50, true);
				}	
			}
			else if(level==HARD){
				for(int i=0;i<10;i++){
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 25.0, i+1, 0.0, ESHOT(UROKO,RED), false, 29, 10, 7.0-0.5*i, 50, true);
				}	
			}
			else if(level==LUNATIC){
				for(int i=0;i<10;i++){
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 25.0, i+1, 0.0, ESHOT(UROKO,RED), false, 29, 10, 7.0-0.5*i, 50, true);
				}	
			}
			else if(level==IMPOSSIBLE){
				for(int i=0;i<10;i++){
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 25.0, i+1, 0.0, ESHOT(UROKO,RED), false, 29, 10, 7.0-0.5*i, 50, true);
				}	
			}
		}
		if(c==330){
			int i=0;
			for(list<ENEMYDATA>::iterator eit=Enemy.begin(); eit!=Enemy.end(); ++eit,i++){
				if(it==eit)	break;
			}
			ELMake((*it).x, (*it).y, 15.0, i, 12.0, ESHOT(RICE,PURPLE), 15, 60);				
		}
		if(c>=360 && c<440 && (*it).y<CENTER_Y+200){
			if(level==EASY){
				if(c%6==0){
					PlaySound(22);
					float ang = (*it).f_hanyou[0];
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 10.0, 3, 1.0+0.1*get_rand(10), ESHOT(RICE,BLUE), false, 0, 10, 4.0, 60, true);
				}
			}
			else if(level==NORMAL){
				if(c%3==0){
					PlaySound(22);
					float ang = (*it).f_hanyou[0];
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 10.0, 3, 1.0+0.1*get_rand(10), ESHOT(RICE,BLUE), false, 0, 10, 4.0, 60, true);
				}
			}
			else if(level==HARD){
				if(c%3==0){
					PlaySound(22);
					float ang = (*it).f_hanyou[0];
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 10.0, 3, 1.5+0.1*get_rand(10), ESHOT(RICE,BLUE), false, 0, 10, 4.0, 60, true);
				}
			}
			else if(level==LUNATIC){
				if(c%3==0){
					PlaySound(22);
					float ang = (*it).f_hanyou[0];
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 10.0, 3, 1.5+0.1*get_rand(10), ESHOT(RICE,BLUE), false, 0, 10, 4.0, 60, true);
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%3==0){
					PlaySound(22);
					float ang = (*it).f_hanyou[0];
					ESNWay((*it).x, (*it).y, CENTER_X, CENTER_Y, 10.0, 5, 1.5+0.1*get_rand(10), ESHOT(RICE,BLUE), false, 0, 10, 4.0, 60, true);
				}
			}
		}
	}
	else if((p>=25 && p<=27) || p==31 || p==32){//3面毛玉
		if(level==EASY){}
		else if(level==NORMAL){
			ang_plus = 9.0;
			if(Player[0].hyper_count==0){
				if(c==100){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 18.0, 20, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%120==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 18.0, 20, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
				}
			}
			ang_plus = 0.0;
		}
		else if(level==HARD){
			ang_plus = 6.0;
			if(Player[0].hyper_count==0){
				if(c==100){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%120==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
				}
			}
			ang_plus = 0.0;
		}
		else if(level==LUNATIC){
			ang_plus = 6.0;
			if(Player[0].hyper_count==0){
				if(c==100){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
					for(int i=0;i<3;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 6.0-1.0*i, ESHOT(UROKO,GREEN), false, 0, 10, 0.0, 0, false);
				}
			}
			else{
				if(c>0 && c%100==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
					for(int i=0;i<3;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 12.0, 30, 6.0-1.0*i, ESHOT(UROKO,GREEN), false, 0, 10, 0.0, 0, false);
				}
			}
			ang_plus = 0.0;
		}
		else if(level==IMPOSSIBLE){
			ang_plus = 4.5;
			if(Player[0].hyper_count==0){
				if(c==100){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 9.0, 40, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
					for(int i=0;i<3;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 9.0, 40, 6.0-1.0*i, ESHOT(UROKO,GREEN), false, 0, 10, 0.0, 0, false);
				}
			}
			else{
				if(c>0 && c%50==0){
					ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 9.0, 40, 7.0, ESHOT(UROKO,GREEN), false, 0, 10);
					for(int i=0;i<3;i++)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 9.0, 40, 6.0-1.0*i, ESHOT(UROKO,GREEN), false, 0, 10, 0.0, 0, false);
				}
			}
			ang_plus = 0.0;
		}
	}
	else if(p==28){//3面色毛玉（赤）
		
	}
	else if(p==29){//3面色毛玉（青）
		
	}
	else if(p==30){//3面色毛玉（緑）
		if(level==EASY){
			/*
			if(c==0){
				(*it).i_hanyou[0] = get_rand(720);
			}
			if(Player[0].hyper_count==0){
				if(c==(*it).i_hanyou[0]){
					ESNWay((*it).x, (*it).y, (*it).x+1, (*it).y, 180.0, 2, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%120==0){
					ESNWay((*it).x, (*it).y, (*it).x+1, (*it).y, 180.0, 2, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
			*/
		}
		else if(level==NORMAL){
			if(c==0){
				(*it).i_hanyou[0] = get_rand(420);
			}
			if(Player[0].hyper_count==0){
				if(c==(*it).i_hanyou[0]){
					ESNWay((*it).x, (*it).y, (*it).x+1, (*it).y, 180.0, 2, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%100==0){
					ESNWay((*it).x, (*it).y, (*it).x+1, (*it).y, 180.0, 2, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
		}
		else if(level==HARD){
			if(c==0){
				(*it).i_hanyou[0] = get_rand(420);
			}
			if(Player[0].hyper_count==0){
				if(c==(*it).i_hanyou[0]){
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 90.0, 4, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%90==0){
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 90.0, 4, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
		}
		else if(level==LUNATIC){
			if(c==0){
				(*it).i_hanyou[0] = get_rand(360);
			}
			if(Player[0].hyper_count==0){
				if(c==(*it).i_hanyou[0]){
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 60.0, 6, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
			else{
				if(c>0 && c%60==0){
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 60.0, 6, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(c==0){
				(*it).i_hanyou[0] = get_rand(360);
			}
			if(Player[0].hyper_count==0){
				if(c==(*it).i_hanyou[0]){
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 45.0, 8, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 45.0, 8, 3.5, ESHOT(KUNAI,BLUE), false, 0, 10, 0.0, 0, false);
				}
			}
			else{
				if(c>0 && c%60==0){
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 45.0, 8, 1.5, ESHOT(KUNAI,BLUE), false, 0, 10);
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+1, 45.0, 8, 3.5, ESHOT(KUNAI,BLUE), false, 0, 10, 0.0, 0, false);
				}
			}
		}		
	}
	else if(p==33){//3面陰陽玉
		if(level==EASY){
			if(c>=40){
				c-=40;
				if(c==0){
					(*it).f_hanyou[1] = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).i_hanyou[0] = 4;
				}
				if((*it).i_hanyou[0]>0 && c%15==0){
					ESL1Make((*it).x, (*it).y, 6.0, 250.0, (*it).f_hanyou[1]+90*(*it).i_hanyou[0], 4.0, RED);
					(*it).i_hanyou[0]--;
				}
			}
		}
		else if(level==NORMAL){
			if(c>=40){
				c-=40;
				if(c==0){
					(*it).f_hanyou[1] = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).i_hanyou[0] = 6;
				}
				if((*it).i_hanyou[0]>0 && c%10==0){
					ESL1Make((*it).x, (*it).y, 6.0, 250.0, (*it).f_hanyou[1]+60*(*it).i_hanyou[0], 4.0, RED);
					(*it).i_hanyou[0]--;
				}
			}
		}
		else if(level==HARD){
			if(c>=40){
				c-=40;
				if(c==0){
					(*it).f_hanyou[1] = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).i_hanyou[0] = 10;
				}
				if((*it).i_hanyou[0]>0 && c%6==0){
					ESL1Make((*it).x, (*it).y, 6.0, 250.0, (*it).f_hanyou[1]+36*(*it).i_hanyou[0], 5.0, RED);
					(*it).i_hanyou[0]--;
				}
			}
		}
		else if(level==LUNATIC){
			if(c>=40){
				c-=40;
				if(c==0){
					(*it).f_hanyou[1] = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).i_hanyou[0] = 20;
				}
				if((*it).i_hanyou[0]>0 && c%3==0){
					ESL1Make((*it).x, (*it).y, 6.0, 250.0, (*it).f_hanyou[1]+18*(*it).i_hanyou[0], 6.0, RED);
					(*it).i_hanyou[0]--;
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(c>=40){
				c-=40;
				if(c==0){
					(*it).f_hanyou[1] = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
					(*it).i_hanyou[0] = 20;
				}
				if((*it).i_hanyou[0]>0 && c%3==0){
					ESL1Make((*it).x, (*it).y, 6.0, 250.0, (*it).f_hanyou[1]-18*(*it).i_hanyou[0], 6.0, RED);
					(*it).i_hanyou[0]--;
				}
			}
		}
	}
	else if(p>=34 && p<=37){//「走らさせていただいてます」
		bES = false;
		bRG = false;
		if(c==0){
			(*it).f_hanyou[0] = 0;//アングル
		}
		float sx = Player[0].x-(*it).x;
		float sy = Player[0].y-(*it).y;
		float d = sqrt(sx*sx+sy*sy);
		if(d>50.0){
			if(level==EASY){
				if(c%5==0){
					PlaySound(22);
					(*it).f_hanyou[0] += 30.0;
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[0]+180*i, 1.0, FRED, true, 0, 60, 0.0, 30, flag);
					}
				}
			}
			else if(level==NORMAL || level==HARD){
				if(c%3==0){
					PlaySound(22);
					(*it).f_hanyou[0] += 30.0;
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[0]+180*i, 1.0, FRED, true, 0, 60, 0.0, 30, flag);
					}
				}
			}
			else if(level==LUNATIC){
				if(c%3==0){
					PlaySound(22);
					(*it).f_hanyou[0] += 30.0;
					for(int i=0;i<2;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[0]+180*i, 1.0, FRED, true, 0, 60, 0.0, 30, flag);
					}
				}
			}
			else if(level==IMPOSSIBLE){
				if(c%3==0){
					PlaySound(22);
					(*it).f_hanyou[0] += 30.0;
					for(int i=0;i<3;i++){
						bool flag = false;
						if(i==0)	flag = true;
						ESMake((*it).x, (*it).y, (*it).f_hanyou[0]+120*i, 1.0, FRED, true, 0, 60, 0.0, 30, flag);
					}
				}
			}
		}
	}

	if((*it).img==1 || (*it).img==8 || (*it).img==10){
		(*it).f_hanyou[0] = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
	}
	
	return;
}

void EMake(float x,float y,int life,int img,int move_pattern,int shot_pattern){
//カンスト500
	if(Enemy.size()==500){
	
	}
	else{
		int level = Player[0].level;
		if(level==BABY)	level = EASY;
		else if(level==IMPOSSIBLE)	level = LUNATIC;
		else if(level==EXTRA)		level = LUNATIC+1;
		ENEMYDATA P;
		P.x = x;
		P.y = y;
		P.speed = 0.0;
		P.large = 1.0;
		P.angle = 0.0;
		P.move_x = 0.0;
		P.move_y = 0.0;
		int gx,gy;
		GetGraphSize(gEnemy[img],&gx,&gy);
		P.atari = sqrt((float)(gx*gx+gy*gy))/6.0;
		P.flash = 255;
		P.back_x = BackX;
		P.back_y = BackY;
		P.life = life;
		P.max_life = life;
		P.img = img;
		P.count = 0;
		P.move_pattern = move_pattern;
		P.shot_pattern = shot_pattern;
		if(img==0 || img==2 || img==3 || img==4 || img==5 || img==11 || img==12 || img==13 || img==14 || img==15 || img==16 || img==17 || img==19 || img==20 || img==21 || img==22 || img==23)	P.bAtari = true;
		else		P.bAtari = false;
		//ノーマルの素点
		if(img==-1)		P.soten = 0;//画像なし
		else if(img==0)		P.soten = 320;//フラフィ
		else if(img==1)		P.soten = 160;//小弾戦車
		else if(img==3)		P.soten = 81920;//ヴォイド
		else if(img==5)		P.soten = 2560;//ハードフラフィ
		else if(img==6)		P.soten = 20480;//ハイパーマスター
		else if(img==8)		P.soten = 1280;//肉弾戦車
		else if(img==10)	P.soten = 2560;//横からの戦車
		else if(img==11)	P.soten = 40960;//スピリット
		else if(img==13)	P.soten = 320;//マイク
		else if(img==14)	P.soten = 80;//コーン
		else if(img==16)	P.soten = 160;//フラフィ・ソロー
		else if(img==17)	P.soten = 2560;//銀次
		else if(img==18)	P.soten = 163840;//トレインドトレイン
		else if(img==19)	P.soten = 320;//フワフワ毛玉
		else if(img==20)	P.soten = 160;//赤毛玉
		else if(img==21)	P.soten = 160;//青毛玉
		else if(img==22)	P.soten = 160;//緑毛玉
		else if(img==23)	P.soten = 2560;//陰陽玉
		P.soten *= (level+1)*0.5;
		P.bDe = false;
		P.bBlend = false;
		P.bBomb = false;
		P.bDelete = false;
		P.bDamage = false;
		if(img==14 || img==-1)	P.bNoDamage = true;
		else			P.bNoDamage = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}
		if(Player[0].stage==3 && P.bAtari==false)	P.flash = 200;

		Enemy.push_back(P);
	}
	
	return;
}

void ESDraw(){
	for(list<ESHOTDATA>::iterator it=EShot.begin(); it!=EShot.end(); ++it){
		if((*it).count>=0){
			bES = true;
			bRG = true;		
			if((*it).bMove==false)	ESMove(it);
			bES = false;
			bRG = false;		
			int gx,gy;
			if((*it).img<0)	GetGraphSize(gEShot2[-6*((*it).img+1)],&gx,&gy);
			else		GetGraphSize(gEShot[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){
				if(!((*it).pattern==37 || (*it).pattern==38 || (*it).pattern==39 || (*it).pattern==40 || (*it).pattern==46 || (((*it).pattern==49||(*it).pattern==50)&&(*it).i_hanyou[0]==0))){
					if((*it).y+gy>=10 || (*it).bDelete==true){
						if((*it).pattern==48){
							ESMake((*it).x, (*it).y, get_rand(360), 1.0, ESHOT(BFLY,RED), false, 0, 0);
						}
						it = EShot.erase(it);
						it--;
						continue;			
					}
				}
			}
			else{
				(*it).bDelete = true;
			}
			if((((*it).bDelete==true||(*it).count>=180)&&Bomb.size()>0) || (*it).bDe==true){
				EfMake((*it).x, (*it).y, (*it).img, 9);
				it = EShot.erase(it);
				it--;
				continue;		
			}
			if((*it).bBlend==true)	SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
			if(GetSkip()){
				if((*it).img<0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle+M_PI/2.0, gEShot2[-6*((*it).img+1)+(*it).count/2%6], TRUE, FALSE);
				else{
					DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle+M_PI/2.0, gEShot[(*it).img], TRUE, FALSE);
				}
			}
		}
		if((*it).bMove==false)	(*it).count++;
		else			(*it).bMove = false;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void ESMove(list<ESHOTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	list<BOSSDATA>::iterator bit = Boss.begin();
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	
	if(p==1){//ゴジラ第一攻撃
		if((*it).x<10 || (*it).y<10 || (*it).x>430){
			PlaySound(23);
			(*it).bDe = true;
			if(level==EASY){
				for(int i=0;i<10;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(10), FBLUE, true, 2); 
				}
			}
			else if(level==NORMAL){
				for(int i=0;i<10;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(20), FBLUE, true, 2); 
				}
			}
			else if(level==HARD){
				for(int i=0;i<5;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(25), FBLUE, true, 2); 
				}
			}
			else if(level==LUNATIC){
				for(int i=0;i<6;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(40), FBLUE, true, 2); 
				}
			}
			else if(level==IMPOSSIBLE){
				for(int i=0;i<6;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 2.0+0.1*get_rand(50), FBLUE, true, 2); 
				}
			}
		}
	}
	else if(p==2){//ゴジラ第一攻撃
		float angle = Atan2((*it).move_y, (*it).move_x);
		if(angle<-M_PI/2 || angle>M_PI/2){
			angle -= Radian(3.0,TRUE);
			if(angle>=-M_PI/2 && angle<=M_PI/2)	angle = M_PI/2;
		}
		else if(angle>=-M_PI/2 && angle<=M_PI/2){
			angle += Radian(3.0,TRUE);
			if(angle<-M_PI/2 || angle>M_PI/2)	angle = M_PI/2;
		}
		(*it).move_x = cos(angle);
		(*it).move_y = sin(angle);
	}
	else if(p==3){//秋符「秋の空とゴジラの心」
		if((*it).x<10 || (*it).y<10 || (*it).x>430){
			PlaySound(23);
			(*it).bDe = true;
			if(level==EASY){
				for(int i=0;i<5;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(5), FBLUE, true, 2); 
				}
			}
			else if(level==NORMAL){
				for(int i=0;i<5;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(10), FBLUE, true, 2); 
				}
			}
			else if(level==HARD){
				for(int i=0;i<1;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(20), FBLUE, true, 2); 
				}
				float angle = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE);
				ELMake((*it).x, (*it).y, 12.0, angle, 15.0, ESHOT(RICE,PURPLE), 2, 30);
			}
			else if(level==LUNATIC){
				for(int i=0;i<2;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 1.0+0.1*get_rand(30), FBLUE, true, 2); 
				}
				float angle = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE)-60.0;
				for(int i=0;i<5;i++)	ELMake((*it).x, (*it).y, 12.0, angle+30.0*i, 18.0, ESHOT(RICE,PURPLE), 2, 30);
			}
			else if(level==IMPOSSIBLE){
				for(int i=0;i<2;i++){
					float angle = Radian(get_rand(360),TRUE);
					float d = get_rand(24);
					//ESMake((*it).x+d*cos(angle), (*it).y+d*sin(angle), get_rand(360), 2.0+0.1*get_rand(40), FBLUE, true, 2); 
				}
				float angle = Radian(atan2(Player[0].y-(*it).y, Player[0].x-(*it).x),FALSE)-60.0;
				for(int i=0;i<5;i++)	ELMake((*it).x, (*it).y, 50.0, angle+30.0*i, 18.0, ESHOT(RICE,PURPLE), 2, 30);
			}
		}
	}
	else if(p==4){//ゴジラ第二攻撃
		if((*it).y<CENTER_Y+50 && (*it).count>0){
			if(level==EASY){
				int loo = Loo(40,20);
				if((*it).count%loo==0){
					PlaySound(23);
					ESMake((*it).x, (*it).y, 90, 1.0, FBLUE, true, 0, 15, 0, 0, true); 
					ESMake((*it).x, (*it).y, 90, 2.0, FBLUE, true, 0, 15, 0, 0, false); 
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y-10.0, 30.0, 5, 3.0, FBLUE, true, 0, 15, 0, 0, false);
				}
			}
			else if(level==NORMAL){
				int loo = Loo(40,20);
				if((*it).count%loo==0){
					PlaySound(23);
					ESMake((*it).x, (*it).y, 90, 1.0, FBLUE, true, 0, 15, 0, 0, true); 
					ESMake((*it).x, (*it).y, 90, 2.0, FBLUE, true, 0, 15, 0, 0, false); 
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y-10.0, 30.0, 5, 3.0, FBLUE, true, 0, 15, 0, 0, false);
				}
			}
			else if(level==HARD){
				int loo = Loo(30,10);
				if((*it).count%loo==0){
					PlaySound(23);
					ESMake((*it).x, (*it).y, 90, 3.0, FBLUE, true, 0, 15, 0, 0, true); 
					ESMake((*it).x, (*it).y, 90, 2.0, FBLUE, true, 0, 15, 0, 0, false); 
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y-10.0, 30.0, 5, 3.0, FBLUE, true, 0, 15, 0, 0, false);
				}
			}
			else if(level==LUNATIC){
				int loo = Loo(30,10);
				if((*it).count%loo==0){
					PlaySound(23);
					ESMake((*it).x, (*it).y, 90, 3.0, FBLUE, true, 0, 15, 0, 0, true); 
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y-10.0, 30.0, 5, 3.0, FBLUE, true, 0, 15, 0, 0, false);
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+10.0, 30.0, 1, 2.0, FBLUE, true, 0, 15, 0, 0, false);
				}
			}
			else if(level==IMPOSSIBLE){
				int loo = Loo(30,10);
				if((*it).count%loo==0){
					PlaySound(23);
					ESMake((*it).x, (*it).y, 90, 3.0, FBLUE, true, 0, 15, 0, 0, true); 
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y-10.0, 30.0, 5, 5.0, FBLUE, true, 0, 15, 0, 0, false);
					ESNWay((*it).x, (*it).y, (*it).x, (*it).y+10.0, 30.0, 1, 4.0, FBLUE, true, 0, 15, 0, 0, false);
				}
			}
		}
	}      	
	else if(p==5){//うんざん
		float angle = Atan2((*it).move_y, (*it).move_x);
		if(angle<-M_PI/2 || angle>M_PI/2){
			angle -= Radian(0.4,TRUE);
			if(angle>=-M_PI/2 && angle<=M_PI/2)	angle = M_PI/2;
		}
		else if(angle>=-M_PI/2 && angle<=M_PI/2){
			angle += Radian(0.4,TRUE);
			if(angle<-M_PI/2 || angle>M_PI/2)	angle = M_PI/2;
		}
		(*it).move_x = cos(angle);
		(*it).move_y = sin(angle);
	}
	else if(p>=6 && p<=25){//早苗は俺の嫁
		float angle;
		int pat = p;
		if((p>=6 && p<=10) || (p>=16 && p<=20)){ 
			if(pat>=6 && pat<=10)		pat -= 6;
			else if(pat>=16 && pat<=20)	pat -= 16;
			if((*it).img/8==SMALL)		pat = (pat+1)%5;
			if(pat==0)	angle = Radian(-18,TRUE);
			else if(pat==1)	angle = Radian(54,TRUE);
			else if(pat==2)	angle = Radian(126,TRUE);
			else if(pat==3)	angle = Radian(-162,TRUE);
			else if(pat==4)	angle = Radian(-90,TRUE);
		}
		else if((pat>=11 && pat<=15) || (pat>=21 && pat<=25)){
			if(pat>=11 && pat<=15)		pat -= 11;
			else if(pat>=21 && pat<=25)	pat -= 21;
			if((*it).img/8==SMALL)		pat = (pat+1)%5;
			if(pat==0)	angle = Radian(-18+36,TRUE);
			else if(pat==1)	angle = Radian(54+36,TRUE);
			else if(pat==2)	angle = Radian(126+36,TRUE);
			else if(pat==3)	angle = Radian(-162+36,TRUE);
			else if(pat==4)	angle = Radian(-90+36,TRUE);
		}
		if((*it).i_hanyou[0]<2){
			if((*bit).i_hanyou[0]==1 && (*it).i_hanyou[0]==0){
				PlaySound(23);
				if(p>=6 && p<=15){
					(*it).f_hanyou[2] = 5.0;
					if((*it).img/8==SMALL)	(*it).f_hanyou[2] = 2.0;
				}
				else if(p>=16 && p<=25){
					(*it).f_hanyou[2] = 5.3;
					if((*it).img/8==SMALL)	(*it).f_hanyou[2] = 2.3;
				}
				(*it).f_hanyou[1] = (*it).f_hanyou[2] / 90.0;
				(*it).i_hanyou[0] = 1;
			}
			else if((*bit).i_hanyou[0]==2 && (*it).i_hanyou[0]==1){
				PlaySound(23);
				float angle2 = Radian((*it).f_hanyou[0],TRUE);
				(*it).move_x = cos(angle2);
				(*it).move_y = sin(angle2);
				(*it).speed = 0.0;
				(*it).f_hanyou[1] = 0.5 / 120.0;
				(*it).i_hanyou[0] = 2;
			}
		}
		if((*it).i_hanyou[0]==1){
			(*it).f_hanyou[2] -= (*it).f_hanyou[1];
			(*it).x += (*it).f_hanyou[2]*cos(angle);
			(*it).y += (*it).f_hanyou[2]*sin(angle);
		}
		else if((*it).i_hanyou[0]==2){
			if((*it).i_hanyou[1]<120){
				(*it).speed += (*it).f_hanyou[1];
			}
			(*it).i_hanyou[1]++;
		}
	}
	else if(p==26){//「４９５年の煮込み」
		(*it).speed = (*bit).f_hanyou[0];
		if((*it).i_hanyou[0]==0){
			int gx,gy;
			if((*it).img<0)	GetGraphSize(gEShot2[-6*((*it).img+1)],&gx,&gy);
			else		GetGraphSize(gEShot[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			(*it).x += (*it).speed * (*it).move_x;
			(*it).y += (*it).speed * (*it).move_y;
			if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430){
				if((*it).x+gx<10){
					(*it).x = 10-gx; 
					(*it).move_x *= -1;
				}
				if((*it).x-gx>430){
					(*it).x = 430+gx; 
					(*it).move_x *= -1;
				}
				if((*it).y+gy<10){
					(*it).y = 10-gy; 
					(*it).move_y *= -1;
				}
				(*it).i_hanyou[0]++;        	
			}
			else{
				(*it).x -= (*it).speed * (*it).move_x;
				(*it).y -= (*it).speed * (*it).move_y;
			}
		}
	}
	else if(p==27 || p==28){//「サブタレイニアンキャベツ」
		(*it).speed = (*bit).f_hanyou[0];
		if(c<120){
			float angle = Atan2((*it).move_y,(*it).move_x);
			if(p==27)	angle += Radian(5.0,TRUE);
			else		angle -= Radian(5.0,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==29){//3面アホ
		if(c==50){
			PlaySound(23);
			if(level!=IMPOSSIBLE)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 72.0, 5, 2.0, ESHOT(UROKO,PURPLE), false, 0, 1, 0.0, 60, true);
			else			ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 18.0, 20, 2.0, ESHOT(UROKO,PURPLE), false, 0, 1, 0.0, 60, true);
			(*it).img = ESHOT(UROKO,PURPLE);
			float ang = Atan2((*it).move_y,(*it).move_x);
			ang += Radian(90,TRUE);
			(*it).move_x = cos(ang);
			(*it).move_y = sin(ang);
			(*it).bDe = true;
		}
	}
	else if(p==30 || p==31){//3面・4面ボス発狂弾
		float ang = Atan2((*it).move_y,(*it).move_x);
		if(p==30)	ang += Radian( 5.0*cos(Radian(12*c,TRUE)) , TRUE);
		else		ang -= Radian( 5.0*cos(Radian(12*c,TRUE)) , TRUE);
		(*it).move_x = cos(ang);
		(*it).move_y = sin(ang);
	}
	else if(p==32){//3面毛玉
		if(c==0){
			(*it).f_hanyou[0] = (*it).speed / 60.0;
		}
		if(c<60)	(*it).speed -= (*it).f_hanyou[0];
		if(c==60){
			PlaySound(23);
			if(level==EASY)		ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 120.0, 3, 3.0, ESHOT(RICE,PURPLE), false);
			else if(level==NORMAL)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 120.0, 3, 3.0, ESHOT(RICE,PURPLE), false);
			else if(level==HARD)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 72.0, 5, 4.0, ESHOT(RICE,PURPLE), false);
			else if(level==LUNATIC || level==IMPOSSIBLE){
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 72.0, 5, 4.0, ESHOT(RICE,PURPLE), false);
				ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 72.0, 5, 6.0, ESHOT(RICE,PURPLE), false);
			}
			(*it).bDe = true;
		}
	}
	else if(p==33 || p==34){//ゆやや通常攻撃
		bES = false;
		bRG = false;		
		if(c>60){
			int gx,gy;
			if((*it).img<0)	GetGraphSize(gEShot2[-6*((*it).img+1)],&gx,&gy);
			else		GetGraphSize(gEShot[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){
				(*it).bDe = true;
			}
		}
		if(c==0){
			(*it).f_hanyou[0] = (*it).f_speed / 120.0;
			(*it).f_hanyou[1] = (*it).speed / 60.0;
			(*it).speed = (*it).f_speed;
		}
		if(c<120)	(*it).speed -= (*it).f_hanyou[0];
		else if(c<180)	(*it).speed += (*it).f_hanyou[1];
		if(c<120){
			float ang = Atan2((*it).move_y,(*it).move_x);
			if(p==33)	ang += Radian( 4.0 , TRUE);
			else		ang -= Radian( 4.0 , TRUE);
			(*it).move_x = cos(ang);
			(*it).move_y = sin(ang);	
		}
	}
	else if(p==35 || p==36){//ゆやや第二攻撃
		bES = false;
		bRG = false;		
		if(c>60){
			int gx,gy;
			if((*it).img<0)	GetGraphSize(gEShot2[-6*((*it).img+1)],&gx,&gy);
			else		GetGraphSize(gEShot[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){
				(*it).bDe = true;
			}
		}
		if(c==0){
			(*it).f_hanyou[0] = (*it).f_speed / 120.0;
			(*it).f_hanyou[1] = (*it).speed / 60.0;
			(*it).speed = (*it).f_speed;
		}
		if(c<120)	(*it).speed -= (*it).f_hanyou[0];
		else if(c<180)	(*it).speed += (*it).f_hanyou[1];
		if(c<120){
			float ang = Atan2((*it).move_y,(*it).move_x);
			if(p==33)	ang += Radian( 4.0 , TRUE);
			else		ang -= Radian( 4.0 , TRUE);
			(*it).move_x = cos(ang);
			(*it).move_y = sin(ang);	
		}
		if(c==60){
			(*it).bDe = true;
			if(level==EASY){
				PlaySound(23);
				float x = (*it).x;
				float y = (*it).y;
				for(int j=0;j<4;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,GREEN), false, 33, 0, 2.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,WATER), false, 34, 0, 2.0, 0, flag);
				}
			}
			else if(level==NORMAL){
				PlaySound(23);
				float x = (*it).x;
				float y = (*it).y;
				for(int j=0;j<6;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 1.0, ESHOT(UROKO,GREEN), false, 33, 0, 2.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 1.0, ESHOT(UROKO,WATER), false, 34, 0, 2.0, 0, flag);
				}
			}
			else if(level==HARD){
				PlaySound(23);
				float x = (*it).x;
				float y = (*it).y;
				for(int j=0;j<4;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,GREEN), false, 33, 0, 2.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,WATER), false, 34, 0, 2.0, 0, flag);
				}
				for(int j=0;j<4;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 0.5, ESHOT(UROKO,ORANGE), false, 34, 30, 3.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 0.5, ESHOT(UROKO,YELLOW), false, 33, 30, 3.0, 0, flag);
				}
			}
			else if(level==LUNATIC){
				PlaySound(23);
				float x = (*it).x;
				float y = (*it).y;
				for(int j=0;j<4;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,GREEN), false, 33, 0, 2.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 1.0, ESHOT(UROKO,WATER), false, 34, 0, 2.0, 0, flag);
				}
				for(int j=0;j<4;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 0.5, ESHOT(UROKO,ORANGE), false, 34, 30, 3.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+90.0*j, 0.5, ESHOT(UROKO,YELLOW), false, 33, 30, 3.0, 0, flag);
				}
			}
			else if(level==IMPOSSIBLE){
				PlaySound(23);
				float x = (*it).x;
				float y = (*it).y;
				for(int j=0;j<6;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 1.0, ESHOT(UROKO,GREEN), false, 33, 0, 2.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 1.0, ESHOT(UROKO,WATER), false, 34, 0, 2.0, 0, flag);
				}
				for(int j=0;j<6;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 0.5, ESHOT(UROKO,ORANGE), false, 34, 30, 3.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 0.5, ESHOT(UROKO,YELLOW), false, 33, 30, 3.0, 0, flag);
				}
				for(int j=0;j<6;j++){
					bool flag = false;
					if(p==35)	ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 1.1, ESHOT(UROKO,RED), false, 33, 30, 4.0, 0, flag);
					else		ESMake(x, y, (*bit).f_hanyou[2]+60.0*j, 1.1, ESHOT(UROKO,BLUE), false, 34, 30, 3.0, 0, flag);
				}
			}
		}
	}
	else if(p==37 || p==38){//ゆやや第四攻撃
		bES = false;
		float ang = Atan2((*it).move_y,(*it).move_x);
		if(c<150){
			if(p==37)	ang += Radian( 3.0 , TRUE);
			else		ang -= Radian( 3.0 , TRUE);
			(*it).move_x = cos(ang);
			(*it).move_y = sin(ang);	
		}
		else	(*it).bDe = true;
		if(level==EASY){
			if(c%10==0){
				PlaySound(18);
				float an = Radian(ang , FALSE);
				ESMake((*it).x, (*it).y, an+(*bit).f_hanyou[0], 1.0, ESHOT(UROKO,RED), false, 0, 60, 0.0, 60);
			}
		}
		if(level==NORMAL || level==HARD){
			if(c%5==0){
				PlaySound(18);
				float an = Radian(ang , FALSE);
				ESMake((*it).x, (*it).y, an+(*bit).f_hanyou[0], 1.0, ESHOT(UROKO,RED), false, 0, 60, 0.0, 60);
			}
		}
		else if(level==LUNATIC){
			if(c%5==0){
				PlaySound(18);
				float an = Radian(ang , FALSE);
				for(int i=0;i<3;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x, (*it).y, -50+50*i+an+(*bit).f_hanyou[0], 1.0, ESHOT(UROKO,RED), false, 0, 60, 0.0, 60, flag);
				}
			}
		}
		else if(level==IMPOSSIBLE){
			if(c%5==0){
				PlaySound(18);
				float an = Radian(ang , FALSE);
				for(int i=0;i<5;i++){
					bool flag = false;
					if(i==0)	flag = true;
					ESMake((*it).x, (*it).y, -60+30*i+an+(*bit).f_hanyou[0], 1.0, ESHOT(UROKO,RED), false, 0, 60, 0.0, 60, flag);
				}
			}
		}
		(*bit).i_hanyou[0]++; 
	}
	else if(p==39 || p==40){//ニュークリアきもも
		if(c==0){
			(*it).f_hanyou[0] = (*it).f_speed / 40.0;//最大半径/20
			(*it).f_hanyou[1] = 0;//現在半径
			(*it).f_hanyou[2] = (*it).x;//基準x
			(*it).f_hanyou[3] = (*it).y;//基準y
			(*it).f_hanyou[4] = (*it).move_x;//基準移動ベクトルx
			(*it).f_hanyou[5] = (*it).move_y;//基準移動ベクトルy
			(*it).f_hanyou[6] = (*it).speed;//極座標角度
			(*it).f_speed = 0;
			(*it).speed = 0.0;
		}
		if(c<40)	(*it).f_hanyou[1] += (*it).f_hanyou[0];
		(*it).x = (*it).f_hanyou[2] + (*it).f_hanyou[1]*cos(Radian((*it).f_hanyou[6],TRUE));
		(*it).y = (*it).f_hanyou[3] + (*it).f_hanyou[1]*sin(Radian((*it).f_hanyou[6],TRUE));
		(*it).f_hanyou[2] += 1.5 * (*it).f_hanyou[4];
		(*it).f_hanyou[3] += 1.5 * (*it).f_hanyou[5];
		(*it).move_x = cos(Radian((*it).f_hanyou[6],TRUE));
		(*it).move_y = sin(Radian((*it).f_hanyou[6],TRUE));
		if(p==39)	(*it).f_hanyou[6] += 1.0;
		else		(*it).f_hanyou[6] -= 1.0;
		if(c>500)	(*it).bDe = true;		 
	}
	else if(p==41 || p==43){//ランドマインランド
		bES = false;
		bRG = false;		
		int gx,gy;
		if((*it).img<0)	GetGraphSize(gEShot2[-6*((*it).img+1)],&gx,&gy);
		else		GetGraphSize(gEShot[(*it).img],&gx,&gy);
		gx /= 2;
		gy /= 2;
		bool flag = false;
		int img = FBLUE;
		if(p==43)	img = FRED;
		if(p==41){
			if((*it).x-gx<15 || (*it).y-gy<15 || (*it).x+gx>425 || (*it).y+gy>465){
				flag = true;
			}
		}
		else if(p==43){
			if(c==0){
				float sx = Player[0].x - (*it).x;
				float sy = Player[0].y - (*it).y;
				float d = sqrt(sx*sx+sy*sy);
				float ang = Atan2(sy,sx);
				(*it).move_x = cos(ang);
				(*it).move_y = sin(ang);
				(*it).speed = 2.0*d/60.0;
				(*it).f_hanyou[0] = (*it).speed/60.0;
			}
			(*it).speed -= (*it).f_hanyou[0];
			if(c==60){
				flag = true;
			}
		}
		if(flag==true){
			PlaySound(33);
			if(level==EASY){
				for(int i=0;i<4;i++){
					for(int j=0;j<3;j++){
						ESMake((*it).x, (*it).y, 90*i, 0.0, img, true, 42, 0, 1.0+1.5*j, 20);				
					}
				}
			}
			else if(level==NORMAL){
				for(int i=0;i<4;i++){
					for(int j=0;j<6;j++){
						ESMake((*it).x, (*it).y, 90*i, 0.0, img, true, 42, 0, 1.0+1.5*j, 20);				
					}
				}
			}
			else if(level==LUNATIC || level==IMPOSSIBLE){
				for(int i=0;i<4;i++){
					for(int j=0;j<8;j++){
						ESMake((*it).x, (*it).y, 90*i, 0.0, img, true, 42, 0, 1.0+1.5*j, 20);				
					}
				}
			}
			(*it).bDe = true;
		}	
	}
	else if(p==42){//ランドマインランド
		if(c==(*it).f_count)	(*it).bDe = true;
	}
	else if(p==44 || p==45){//コア・オブ・ザ・セカンドサン
		if(c==0){
			(*it).f_hanyou[0] = (*it).f_speed / 40.0;//最大半径/20
			(*it).f_hanyou[1] = 0;//現在半径
			(*it).f_hanyou[4] = (*it).move_x;//基準移動ベクトルx
			(*it).f_hanyou[5] = (*it).move_y;//基準移動ベクトルy
			(*it).f_hanyou[6] = (*it).speed;//極座標角度
			(*it).f_speed = 0;
			(*it).speed = 0.0;
		}
		(*it).f_hanyou[2] = (*bit).x;//基準x
		(*it).f_hanyou[3] = (*bit).y;//基準y
		if(c<40)	(*it).f_hanyou[1] += (*it).f_hanyou[0];
		(*it).x = (*it).f_hanyou[2] + (*it).f_hanyou[1]*cos(Radian((*it).f_hanyou[6],TRUE));
		(*it).y = (*it).f_hanyou[3] + (*it).f_hanyou[1]*sin(Radian((*it).f_hanyou[6],TRUE));
		(*it).move_x = cos(Radian((*it).f_hanyou[6],TRUE));
		(*it).move_y = sin(Radian((*it).f_hanyou[6],TRUE));
		if(p==44)	(*it).f_hanyou[6] += 1.0;
		else		(*it).f_hanyou[6] -= 1.0;
		if(c==60)	(*it).bDe = true;		 
	}
	else if(p==46){//コア・オブ・ザ・セカンドサン
		float sx = (*bit).x - (*it).x;
		float sy = (*bit).y - (*it).y;
		float d = sqrt(sx*sx+sy*sy);
		float sp = 0;
		switch((*bit).i_hanyou[0]){
			case 0:	sp = 0.5;	break;	
			case 1:	sp = 0.7;	break;	
			case 2:	sp = 1.0;	break;	
			case 3:	sp = 1.3;	break;	
		}
		if(d!=0){			
			(*it).x += sp*sx/d;
			(*it).y += sp*sy/d;
		}
		if(d<128)	(*it).bDe = true;
	}
	else if(p==47 || p==48){//妖蛾乱舞
		if(p==47){
			if(c==0)	(*it).f_hanyou[0] = (*it).speed / 60.0;
			if(c<60){
				(*it).speed -= (*it).f_hanyou[0];
			}
			else if(c<70)	(*it).speed = 0;
			else if(c==70){
				PlaySound(23);
				(*it).img = ESHOT(BFLY,PURPLE);
				(*it).speed = 4.0;
				float ang = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
				(*it).move_x = cos(ang);
				(*it).move_y = sin(ang);
			}
		}
	}
	else if(p==49 || p==50){//ヤンデレスカイハイ
		if(c==0){
			(*it).f_hanyou[0] = (*it).f_speed / 90.0;
			(*it).f_hanyou[1] = (*it).speed / 120.0;
			(*it).speed = (*it).f_speed;
		}
		if(c==90){
			float a = Atan2((*it).move_y,(*it).move_x);
			float b = Atan2((*bit).y-(*it).y,(*bit).x-(*it).x);
			float c1 = a-b;
			float c2 = b-a; 
			if(p==49)	(*it).f_hanyou[2] = c1;		
			if(p==50)	(*it).f_hanyou[2] = c2;		
		}
		if(c<90){
			(*it).speed -= (*it).f_hanyou[0];
		}
		else if(c==30)	(*it).speed = 0;
		else if(c<=210)	(*it).speed += (*it).f_hanyou[1];
		if(c<90){}
		else if(c<210){
			c -= 90;
			float ang = Atan2((*bit).y-(*it).y, (*bit).x-(*it).x);
			if(p==49){
				ang += (*it).f_hanyou[2]*(120-c)/120.0;
				(*it).move_x = cos(ang);
				(*it).move_y = sin(ang);
			}
			else if(p==50){
				ang -= (*it).f_hanyou[2]*(120-c)/120.0;
				(*it).move_x = cos(ang);
				(*it).move_y = sin(ang);
			}
		}
		else{
			if((*it).i_hanyou[0]==0){
				float ang = Atan2((*bit).y-(*it).y, (*bit).x-(*it).x);
				(*it).move_x = cos(ang);
				(*it).move_y = sin(ang);		
			}
		}
		if(c>180 && (*it).i_hanyou[0]==0){
			float dx = (*bit).x - (*it).x;
			float dy = (*bit).y - (*it).y;
			float d = sqrt(dx*dx+dy*dy);
			if(d<20){
				PlaySound(23);
				(*it).i_hanyou[0] = 1;
				int img = SMALL;
				if(get_rand(1)==0)	img = MEDIUM;
				ESMake((*it).x, (*it).y, 0.1*get_rand(3600), 2.5, ESHOT(img,RED), false, 0, 0, 3.0+0.01*get_rand(400), 30);				
				(*it).bDe = true;
			}
		}
	}
	else if(p==51){//神コンデンサー第一形態・第三波
		if(c==40){
			float ang = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			(*it).move_x = cos(ang);
			(*it).move_y = sin(ang);
		}
		if(c>=40){
			(*it).speed += 0.15;
		}
	}
	else if(p==52){//あらま～ラストスペル
		if(c==0){
			(*it).f_hanyou[0] += (*bit).f_hanyou[0];
		}
		if(c<180){
			float ang = Atan2((*it).move_y, (*it).move_x);
			ang += Radian((*it).f_hanyou[0],TRUE);
			(*it).move_x = cos(ang);
			(*it).move_y = sin(ang);
		}
	}
	else if(p==53 || p==54){//おかび第一通常
		if((*it).count==(*it).f_count){
			if((*it).y<400){
				PlaySound(23);
				if(p==53)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 90.0, 1, 4.5-(*it).y/100.0, ESHOT(KNIFE,BLUE), false, 0, 10);			
				else if(p==54)	ESNWay((*it).x, (*it).y, Player[0].x, Player[0].y, 90.0, 2, 4.5-(*it).y/100.0, ESHOT(KNIFE,RED), false, 0, 10);			
			}
			(*it).bDe = true;
		}
	}
	else if(p==55 || p==56){//おかび第二/三通常
		if((*it).count==(*it).f_count){
			PlaySound(23);
			float ang = Atan2((*it).move_y, (*it).move_x);
			ang = Radian(ang,FALSE);
			if(p==55)	ESMake((*it).x, (*it).y, ang+180, 2.0, ESHOT(KNIFE,BLUE), false, 0, 10);				
			else if(p==56)	ESMake((*it).x, (*it).y, ang+180, 2.0, ESHOT(KNIFE,RED), false, 0, 10);				
			(*it).bDe = true;
		}
	}
	else if(p==57 || p==58){//おかび第四通常
		if((*it).count==(*it).f_count){
			if(1/*(*it).y<400*/){
				PlaySound(23);
				float ang = Atan2((*it).move_y, (*it).move_x);
				ang = Radian(ang,FALSE);
				if(p==57){
					for(int i=0;i<2;i++){
						bool flag = true;
						if(i>0)	flag = false;
						ESMake((*it).x, (*it).y, ang+40*i+160, 1.5, ESHOT(KNIFE,BLUE), false, 0, 10, 0.0, 0, flag);				
					}
				}
				else if(p==58){
					for(int i=0;i<2;i++){
						bool flag = true;
						if(i>0)	flag = false;
						ESMake((*it).x, (*it).y, ang+40*i+160, 1.5, ESHOT(KNIFE,RED), false, 0, 10, 0.0, 0, flag);				
					}
				}
			}
			(*it).bDe = true;
		}
	}
		
	if((*it).count<(*it).f_count){
		float accel = ((*it).f_speed-(*it).speed)/(float)(*it).f_count;
		accel *= (float)((*it).f_count-(*it).count);
		(*it).x += ((*it).speed+accel) * (*it).move_x;
		(*it).y += ((*it).speed+accel) * (*it).move_y;
	}
	else{
		(*it).x += (*it).speed * (*it).move_x;
		(*it).y += (*it).speed * (*it).move_y;
	}
	
	if((*it).img/8==VERYBIG)	(*it).angle = Radian(12*c,TRUE);
	else if((*it).img/8==SSTAR || (*it).img/8==STAR)	(*it).angle = Radian(6*c,TRUE);
	else	(*it).angle = Atan2((*it).move_y,(*it).move_x);
	
	return;
}

void ESMake(float x,float y,float angle,float speed,int img,bool blend,int pattern,int late,float f_speed,int f_count,bool eff,float hanyou){
//カンスト5000
	int loo = 1;
	if(bRG==true && Player[0].chara>=3){
		if(Player[0].stress_gage>=MAJIGIRE+(MAX_STRESS_GAGE-MAJIGIRE)*1/2)	loo = 3;
		else if(Player[0].stress_gage>=MAJIGIRE+(MAX_STRESS_GAGE-MAJIGIRE)*0/2)	loo = 2;
	}
	for(int k=0;k<loo;k++){
	if(EShot.size()==5000){
	
	}
	else{
		int level = Player[0].level;
		if(level==BABY)	level = EASY;
		if(level==IMPOSSIBLE)	level = LUNATIC;
		if(level==EXTRA)	level = LUNATIC;
		ESHOTDATA P;
		P.x = x;
		P.y = y;
		P.speed = speed;
		if(bES==true)	P.speed *= 1.0+Prank/30.0;
		if(bRG==true){
			if(k==0)	P.speed *= 1.0;
			if(k==1)	P.speed *= 0.8;
			if(k==2)	P.speed *= 1.2;
		}
		P.f_speed = f_speed;
		P.large = 1.0;
		P.angle = Radian(angle,TRUE);
		P.move_x = cos(P.angle);
		P.move_y = sin(P.angle);
		if(img<0)		P.atari = 6.0;
		else if(img/8==SMALL)	P.atari = 2.0;
		else if(img/8==MEDIUM)	P.atari = 4.0;
		else if(img/8==MEDIUM2)	P.atari = 4.0;
		else if(img/8==BIG)	P.atari = 6.0;
		else if(img/8==NEEDLE)	P.atari = 2.0;
		else if(img/8==RICE)	P.atari = 2.0;
		else if(img/8==ICE)	P.atari = 2.0;
		else if(img/8==ZAYAKU)	P.atari = 3.0;
		else if(img/8==OVAL)	P.atari = 5.0;
		else if(img/8==KUNAI)	P.atari = 2.0;
		else if(img/8==UROKO)	P.atari = 3.0;
		else if(img/8==FUDA)	P.atari = 3.0;
		else if(img/8==MONEY)	P.atari = 4.0;
		else if(img/8==BFLY)	P.atari = 4.0;
		else if(img/8==SSTAR)	P.atari = 2.0;
		else if(img/8==STAR)	P.atari = 6.0;
		else if(img/8==KATANA)	P.atari = 4.0;
		else if(img/8==KNIFE)	P.atari = 4.0;
		else if(img/8==VERYBIG)	P.atari = 15.0;
		int gx,gy;
		if(img<0)	GetGraphSize(gEShot2[-6*(img+1)],&gx,&gy);
		else		GetGraphSize(gEShot[img],&gx,&gy);
		gx /= 2;
		gy /= 2;
		P.kasuri = gx + 24;
		P.flash = 255;
		P.soten = 2*(1+LUNATIC-level);
		P.life = 2;
		/*
		if(Player[0].chara<=2){
			//P.life += 2*(Player[0].hyper_rank-1);
			P.life = 2;
		}
		*/
		P.late = late;
		P.img = img;
		P.f_count = f_count;
		P.count = -late;
		P.pattern = pattern;
		P.bBlend = blend;
		if(img/8==VERYBIG || img<0){
			P.bBlend = true;
		}
		P.bDe = false;
		P.bMove = false;
		P.bHyper = false;
		P.bGraze = false;
		P.bDeNow = false;
		P.bDelete = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}
		if(pattern>=6 && pattern<=25)	P.f_hanyou[0] = hanyou;

		if(k==0&&late>0&&eff==true)	EfMake(x, y, img, 8, late);
		EShot.push_back(P);
	}
	}
	
	return;
}

void ESNWay(float x,float y,float tox,float toy,float angle,int num,float speed,int img,bool blend,int pattern,int late,float f_speed,int f_count,bool eff){
	if(late>0&&eff==true)	EfMake(x, y, img, 8, late);
	float base = Radian(Atan2(toy-y,tox-x),FALSE)+ang_plus;
	if(num%2==1){
		ESMake(x, y, base, speed, img, blend, pattern, late, f_speed, f_count, false);
	}
	for(int i=0;i<num/2;i++){
		float toangle[2];
		if(num%2==0){
			toangle[0] = base - angle/2.0 - angle*i;
			toangle[1] = base + angle/2.0 + angle*i;
		}
		else{
			toangle[0] = base - angle*(i+1);
			toangle[1] = base + angle*(i+1);
		}
		for(int a=0;a<2;a++)	ESMake(x, y, toangle[a], speed, img, blend, pattern, late, f_speed, f_count, false);
	}

	return;
}

void ELDraw(){
	for(list<ELASERDATA>::iterator it=ELaser.begin(); it!=ELaser.end(); ++it){
		ELMove(it);
		if((*it).bDelete==true){
			if(fabs((*it).size[0]-(*it).max_size)<=0.01){
				for(int i=0;i<(*it).length[0]/16;i++){
					float x = (*it).x[0][4] + 16*i*cos(Radian((*it).angle,TRUE));
					float y = (*it).y[0][4] + 16*i*sin(Radian((*it).angle,TRUE));
					EfMake(x, y, (*it).img, 9);
				}
			}
			it = ELaser.erase(it);
			it--;
			continue;			
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if((*it).count>=0){
			if(GetSkip())	DrawRotaGraphF((*it).x[0][4]+shake_x, (*it).y[0][4]+shake_y, 1.0*(*it).size[0]/(float)(*it).max_size, (*it).angle-M_PI/2.0, gEShot[ESHOT(BIG,(*it).img%8)], TRUE, FALSE);
		}

		SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		for(int i=1;i>=0;i--){
			if(i==0||((*it).length[0]!=(*it).length[1]&&(*it).bDraw==true)){
				if(GetSkip())	DrawModiGraphF((*it).x[i][0]+shake_x, (*it).y[i][0]+shake_y, (*it).x[i][1]+shake_x, (*it).y[i][1]+shake_y, (*it).x[i][2]+shake_x, (*it).y[i][2]+shake_y, (*it).x[i][3]+shake_x, (*it).y[i][3]+shake_y, gEShot[(*it).img], TRUE);
			}
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void ELMove(list<ELASERDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;

	if(p==0 || p==1){
		//モスラ第二攻撃
		list<BOSSDATA>::iterator bit = Boss.begin();
		for(int i=0;i<2;i++){
			if(p==0){
				(*it).x[i][4] = (*bit).x-10;
				(*it).y[i][4] = (*bit).y-23.5;
			}
			else if(p==1){
				(*it).x[i][4] = (*bit).x+52;
				(*it).y[i][4] = (*bit).y-30.5;
			}
		}
		if(c==-(*it).late){
			(*it).f_hanyou[0] = (*it).angle;
		}
		(*it).angle = (*it).f_hanyou[0] + 20.0*sin(Radian(3*c,TRUE));
	}
	else if(p==2 || p==3){
		//モスラ第二攻撃
		if(c<70){}
		else if(c<120){
			(*it).size[0] = (*it).max_size*(120.0-c)/50.0; 
		}
		else	(*it).bDelete = true;
	}
	else if(p==4 || p==5){
		//うんざんみたいな
		int gx,gy;
		GetGraphSize(gBoss[2], &gx, &gy);
		float haba = gy/4.0;
		float plus = pow(-1,p%2)*haba*sin(Radian(2.0*(*it).spe_count,TRUE));
		for(int i=0;i<2;i++){
			(*it).y[i][4] = CENTER_Y - 156 + plus;
			if(p==4)	(*it).y[i][4] -= 11.5;
			else		(*it).y[i][4] += 11.5;
		}
		(*it).angle = Radian(Atan2((*it).to_y-(*it).y[0][4],(*it).to_x-(*it).x[0][4]), FALSE);
		if(c<70){}
		else if(c<120){
			(*it).size[0] = (*it).max_size*(120.0-c)/50.0; 
		}
		else	(*it).bDelete = true;
		(*it).spe_count++;
	}
	else if(p==6 || p==7){
		//核符「ゴジラvsモスラ　～ 村岡は逃げる」
		list<BOSSDATA>::iterator bit = Boss.begin();
		if(Boss.size()>1)	++bit;
		for(int i=0;i<2;i++){
			if(p==6){
				(*it).x[i][4] = (*bit).x-93;
				(*it).y[i][4] = (*bit).y+20.5;
			}
			else if(p==7){
				(*it).x[i][4] = (*bit).x+90;
				(*it).y[i][4] = (*bit).y+26.5;
			}
		}
		if(c==0){
			PlaySound(27);
		}
		if(c<130){}
		else if(c<180){
			(*it).size[0] = (*it).max_size*(180.0-c)/50.0; 
		}
		else	(*it).bDelete = true;
	}
	else if(p>=8 && p<=12){
		//野菜符「キャロットビーム」
		list<BOSSDATA>::iterator bit = Boss.begin();
		if(c==0){
			float angleA = Atan2(Player[0].y-(*it).y[0][4], Player[0].x-(*it).x[0][4]);
			float angleB = Radian((*it).angle,TRUE);
			if(1/*Player[0].level==NORMAL*/){
				if(p==9)	angleB -= Radian(10.0,TRUE);
				else if(p==10)	angleB += Radian(10.0,TRUE);
				else if(p==11)	angleB -= Radian(20.0,TRUE);
				else if(p==12)	angleB += Radian(20.0,TRUE);
			}
			float a = angleA - angleB;
			if(a<0)	a += 2*M_PI;
			float b = angleB - angleA;
			if(b<0)	b += 2*M_PI;
			if(a<b)		(*it).f_hanyou[0] = a / 40.0; 
			else		(*it).f_hanyou[0] = -b / 40.0; 
		}
		for(int i=0;i<2;i++){
			(*it).x[i][4] = (*bit).x + 40.0*cos(Radian((*it).angle,TRUE));
			(*it).y[i][4] = (*bit).y - 34 + 40.0*sin(Radian((*it).angle,TRUE));
		}
		if(c<40){
			(*it).angle += Radian((*it).f_hanyou[0], FALSE);
		}
		if(c<60){
			(*it).length[0] = -(*it).speed;
		}
		if(c<30){}
		else if(c<60){
			SShake(0,(float)(c-30)*0.14);
		}
		else if(c<150){
			SShake(0,4.2);
		}
		else if(c<210){
			SShake(0,(float)(210-c)*0.07);
		}
		if(c<150){}
		else if(c<210){
			(*it).size[0] = (*it).max_size*(210.0-c)/60.0; 
		}
		else	(*it).bDelete = true;
	}
	else if(p==13){
		//「早苗は俺の嫁」
		for(int i=0;i<2;i++){
			(*it).y[i][4] = Player[0].y;
		}
	}
	else if(p==14){
		//「４９５年の煮込み」
		list<BOSSDATA>::iterator bit = Boss.begin();
		if((*it).f_hanyou[0]<50.0)	(*it).f_hanyou[0] += 1.0;
		(*it).angle += 0.5;
		for(int i=0;i<2;i++){
			(*it).x[i][4] = (*bit).x + (*it).f_hanyou[0]*cos(Radian((*it).angle,TRUE));
			(*it).y[i][4] = (*bit).y-34 + 0.8*(*it).f_hanyou[0]*sin(Radian((*it).angle,TRUE));
		}
	}
	else if(p==15){
		//3面アホ
		list<ENEMYDATA>::iterator eit = Enemy.begin();
		if(c==-(*it).late){
			(*it).i_hanyou[0] = (*it).angle;
		}
		for(int i=0;i<(*it).i_hanyou[0];i++)	++eit;
		(*it).angle = Radian((*eit).f_hanyou[0],FALSE)-180;
		c += (*it).late;

		for(int i=0;i<2;i++){
			(*it).x[i][4] = (*eit).x;
			(*it).y[i][4] = (*eit).y;
		}

		if(c<130){}
		else if(c<180){
			(*it).size[0] = (*it).max_size*(180.0-c)/50.0; 
		}
		else	(*it).bDelete = true;
	}
	else if(p>=16 && p<=31){
		//「ゆや様は本当に頭の良いお方」
		list<BOSSDATA>::iterator bit = Boss.begin();
		if((*it).f_hanyou[0]<90.0)	(*it).f_hanyou[0] += 0.5;
		float ang = Radian((*it).f_hanyou[0],TRUE);
		float rev_ang = Radian(90.0*(int)((p-16)/4)+0.5*c, TRUE);
		if((p-16)/4%2==0)	(*it).angle += 0.2;
		else			(*it).angle -= 0.2;
		for(int i=0;i<2;i++){
			(*it).x[i][4] = CENTER_X + 200.0*sin(ang)*cos(rev_ang);
			(*it).y[i][4] = CENTER_Y + 220.0*sin(ang)*sin(rev_ang);
		}
	}
	else if(p==32){//ニュークリアきもも
		if(c<130){}
		else if(c<180){
			(*it).size[0] = (*it).max_size*(180.0-c)/50.0; 
		}
		else	(*it).bDelete = true;
	}
	else if(p==33){//神コンデンサー第一形態・第二波
		list<BOSSDATA>::iterator bit = Boss.begin();
		if((*bit).i_hanyou[0]==0)	(*it).angle -= 1.5;
		else if((*bit).i_hanyou[0]==1)	(*it).angle += 1.5;
		else	(*it).bDelete = true;
		if((*it).f_hanyou[0]<30.0){
			(*it).f_hanyou[0] += 1.0;
		}
		for(int i=0;i<2;i++){
			(*it).x[i][4] = (*bit).x + (*it).f_hanyou[0]*cos(Radian((*it).angle,TRUE));
			(*it).y[i][4] = (*bit).y + (*it).f_hanyou[0]*sin(Radian((*it).angle,TRUE));
		}
	}
	else if(p>=34 && p<=37){//神コンデンサー第一形態・第三波
		list<BOSSDATA>::iterator bit = Boss.begin();
		if((*bit).i_hanyou[0]==1)	(*it).bDelete = true;
		for(int i=0;i<2;i++){
			if(p==34 || p==35){
				(*it).y[i][4] += 3.0;
				if((*it).y[i][4]>=490.0)	(*it).y[i][4] -= 500.0;
			}
			else if(p==36){
				(*it).x[i][4] += 3.0;
				if((*it).x[i][4]>=470.0)	(*it).x[i][4] -= 500.0;
			}
			else if(p==37){
				(*it).x[i][4] -= 3.0;
				if((*it).x[i][4]<=-30.0)	(*it).x[i][4] += 500.0;
			}
		}
		if(level==IMPOSSIBLE){
			if(c%30==0)	ESMake((*it).x[0][4], (*it).y[0][4], (*it).angle, 1.5, ESHOT(MEDIUM,GREEN), false, 0, 0, 0.0, 0, false);
		}
		else{
			if(c%45==0)	ESMake((*it).x[0][4], (*it).y[0][4], (*it).angle, 1.5, ESHOT(MEDIUM,GREEN), false, 0, 0, 0.0, 0, false);
		}
	}

	if(c>=0)	(*it).length[0] += (*it).speed;
	if((*it).speed<12.0)	(*it).length[1] += 12.0;
	else			(*it).length[1] += (*it).speed;
	for(int i=0;i<2;i++){
		if((*it).length[i]>630)	(*it).length[i] = 630;
	}
	
	for(int i=0;i<2;i++){
		(*it).x[i][5] = (*it).x[i][4] + (*it).length[i]*cos(Radian((*it).angle,TRUE));
		(*it).y[i][5] = (*it).y[i][4] + (*it).length[i]*sin(Radian((*it).angle,TRUE));
		(*it).x[i][0] = (*it).x[i][4] + (*it).size[i]*cos(Radian((*it).angle+90,TRUE));
		(*it).y[i][0] = (*it).y[i][4] + (*it).size[i]*sin(Radian((*it).angle+90,TRUE));
		(*it).x[i][1] = (*it).x[i][4] + (*it).size[i]*cos(Radian((*it).angle-90,TRUE));
		(*it).y[i][1] = (*it).y[i][4] + (*it).size[i]*sin(Radian((*it).angle-90,TRUE));
		(*it).x[i][2] = (*it).x[i][5] + (*it).size[i]*cos(Radian((*it).angle-90,TRUE));
		(*it).y[i][2] = (*it).y[i][5] + (*it).size[i]*sin(Radian((*it).angle-90,TRUE));
		(*it).x[i][3] = (*it).x[i][5] + (*it).size[i]*cos(Radian((*it).angle+90,TRUE));
		(*it).y[i][3] = (*it).y[i][5] + (*it).size[i]*sin(Radian((*it).angle+90,TRUE));
	}
	if(c==0){
		PlaySound(15);
	}
	
	return;
}

void ELMake(float x,float y,float size,float angle,float speed,int img,int pattern,int late){
//カンスト256
	if(ELaser.size()==256){
	
	}
	else{
		PlaySound(25);
		ELASERDATA P;
		for(int i=0;i<2;i++){
			for(int j=0;j<6;j++){
				P.x[i][j] = x;
				P.y[i][j] = y;
			}
			P.length[i] = 0;
		}
		P.max_size = size;
		P.size[0] = size;
		P.size[1] = 2.0;
		P.angle = angle;
		P.speed = speed;
		P.flash = 255;
		P.img = img;
		P.count = -late;
		P.late = late;
		P.pattern = pattern;
		P.bDraw = true;
		P.bDelete = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}
		P.to_x = Lto_x;
		P.to_y = Lto_y;
		P.spe_count = Lspe_count;

		ELaser.push_back(P);
	}
	
	return;
}

void ESLDraw(){
	for(list<ESLASERDATA>::iterator it=ESLaser.begin(); it!=ESLaser.end(); ++it){
		bES = true;
		bRG = true;
		if((*it).type==0)	ESL1Move(it);
		else if((*it).type==1)	ESL2Move(it);
		bES = false;
		bRG = false;
		if((*it).bDelete==true){
			it = ESLaser.erase(it);
			it--;
			continue;			
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		if((*it).bEff==true){
			if(GetSkip())	DrawRotaGraphF((*it).base_x+shake_x, (*it).base_y+shake_y, 1.0, (*it).angle-M_PI/2.0, gEShot[ESHOT(BIG,(*it).img%8)], TRUE, FALSE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		if((*it).type==0){
			if(GetSkip()){
				float x[4],y[4];
				x[0] = (*it).edge_x[1] + (*it).size*cos((*it).angle-Radian(90.0,TRUE));
				y[0] = (*it).edge_y[1] + (*it).size*sin((*it).angle-Radian(90.0,TRUE));
				x[1] = (*it).edge_x[1] + (*it).size*cos((*it).angle+Radian(90.0,TRUE));
				y[1] = (*it).edge_y[1] + (*it).size*sin((*it).angle+Radian(90.0,TRUE));
				x[2] = (*it).edge_x[0] + (*it).size*cos((*it).angle+Radian(90.0,TRUE));
				y[2] = (*it).edge_y[0] + (*it).size*sin((*it).angle+Radian(90.0,TRUE));
				x[3] = (*it).edge_x[0] + (*it).size*cos((*it).angle-Radian(90.0,TRUE));
				y[3] = (*it).edge_y[0] + (*it).size*sin((*it).angle-Radian(90.0,TRUE));
				DrawModiGraphF(x[0]+shake_x, y[0]+shake_y, x[1]+shake_x, y[1]+shake_y, x[2]+shake_x, y[2]+shake_y, x[3]+shake_x, y[3]+shake_y, gEShot[(*it).img], TRUE);
			}
		}
		else if((*it).type==1){
			if(GetSkip()){
				float dx[2],dy[2];
				for(int i=0;i<LASER_ELEMENT_NUM-1&&i<(*it).count;i++){
					float num1 = Radian(90.0/(float)(LASER_ELEMENT_NUM/2.0)*fabs(i-LASER_ELEMENT_NUM/2.0), TRUE);
					float num2 = Radian(90.0/(float)(LASER_ELEMENT_NUM/2.0)*fabs(i+1-LASER_ELEMENT_NUM/2.0), TRUE);
					float size1 = (*it).size * cos(num1);
					float size2 = (*it).size * cos(num2);
					float sy = (*it).y[i] - (*it).y[i+1];
					float sx = (*it).x[i] - (*it).x[i+1];
					float angle = Atan2(sy, sx);
					float x[4],y[4];
					if(i==0){
						x[0] = (*it).x[i] + size1*cos(angle-Radian(90.0,TRUE));
						y[0] = (*it).y[i] + size1*sin(angle-Radian(90.0,TRUE));
						x[1] = (*it).x[i] + size1*cos(angle+Radian(90.0,TRUE));
						y[1] = (*it).y[i] + size1*sin(angle+Radian(90.0,TRUE));
					}
					else{
						for(int j=0;j<2;j++){
							x[j] = dx[(j+1)%2];
							y[j] = dy[(j+1)%2];
						}
					}
					x[2] = (*it).x[i+1] + size2*cos(angle+Radian(90.0,TRUE));
					y[2] = (*it).y[i+1] + size2*sin(angle+Radian(90.0,TRUE));
					x[3] = (*it).x[i+1] + size2*cos(angle-Radian(90.0,TRUE));
					y[3] = (*it).y[i+1] + size2*sin(angle-Radian(90.0,TRUE));
					for(int j=0;j<2;j++){
						dx[j] = x[j+2];
						dy[j] = y[j+2];
					}
					DrawModiGraphF(x[0]+shake_x, y[0]+shake_y, x[1]+shake_x, y[1]+shake_y, x[2]+shake_x, y[2]+shake_y, x[3]+shake_x, y[3]+shake_y, gLaser[(*it).img][i], TRUE);
				}
			}
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void ESL1Move(list<ESLASERDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;

	(*it).length[0] += (*it).speed;
	(*it).edge_x[1] += (*it).speed*cos((*it).angle);
	(*it).edge_y[1] += (*it).speed*sin((*it).angle);
	if((*it).length[0]>(*it).length[1]){
		float over = (*it).length[0] - (*it).length[1];
		(*it).edge_x[0] = (*it).base_x + over*cos((*it).angle);
		(*it).edge_y[0] = (*it).base_y + over*sin((*it).angle);
		(*it).bEff = false;
	}

	int num = 0; 
	for(int i=0;i<2;i++){
		if((*it).edge_x[i]+(*it).size<10-10 || (*it).edge_y[i]+(*it).size<10-10 || (*it).edge_x[i]-(*it).size>430+10 || (*it).edge_y[i]-(*it).size>470+10){
			num++;
		}
	}
	if(num==2)	(*it).bDelete = true;
	
	return;
}

void ESL2Move(list<ESLASERDATA>::iterator &it){
	bool bDe = true;
	list<BOSSDATA>::iterator bit = Boss.begin();
	int level = Player[0].level;
	if(level==BABY)	level = NORMAL;
	int p = (*it).pattern;
	int c = (*it).count;

	if(p==0){//チュートリアル
		if(c<120){
			(*it).angle += Radian(3.0,TRUE);
			(*it).speed += 0.04;
		}
	}
	else if(p==1 || p==2){//電車「鉄道マニアはこの程度出来て当然」
		bES = false;
		if(c<150)	bDe = false;
		if(c<120){
			if(p==1)	(*it).angle += Radian(2.0,TRUE);
			else		(*it).angle -= Radian(2.0,TRUE);
		}
		else{
			if(p==1)	(*it).angle += Radian(0.5,TRUE);
			else		(*it).angle -= Radian(0.5,TRUE);
		}
		
		if(c==0){
			(*it).f_hanyou[0] = ((*it).speed-0.5) / 120.0;
		}
		if(c<120){
			(*it).speed -= (*it).f_hanyou[0];
		}
		else if(c<240){
			(*it).speed += (*it).f_hanyou[0];
		}
		if(c>=120){
			c -= 120;
			if(level==EASY){
				if(c%13==0){
					PlaySound(21);
					if((*it).y[0]<CENTER_Y+50){
						for(int i=0;i<1;i++)	ESMake((*it).x[0], (*it).y[0], Radian((*it).angle,FALSE)+160.0+0.1*get_rand(400), 2.0+0.1*get_rand(20), ESHOT(SSTAR,WATER), true, 0, 0, 0.0, 0, false);
					}
				}
				bRG = false;
				if(c%20==0){
					if(p==1)	ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 90.0, 4, 1.0, ESHOT(UROKO,RED), false, 33, 30, 2.0);				
					else		ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 90.0, 4, 1.0, ESHOT(UROKO,BLUE), false, 34, 30, 2.0);				
				}
			}
			else if(level==NORMAL){
				if(c%7==0){
					PlaySound(21);
					if((*it).y[0]<CENTER_Y+50){
						for(int i=0;i<1;i++)	ESMake((*it).x[0], (*it).y[0], Radian((*it).angle,FALSE)+160.0+0.1*get_rand(400), 3.0+0.1*get_rand(20), ESHOT(SSTAR,WATER), true, 0, 0, 0.0, 0, false);
					}
				}
				bRG = false;
				if(c%20==0){
					if(p==1)	ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 60.0, 6, 1.0, ESHOT(UROKO,RED), false, 33, 30, 2.0);				
					else		ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 60.0, 6, 1.0, ESHOT(UROKO,BLUE), false, 34, 30, 2.0);				
				}
			}
			else if(level==HARD){
				if(c%7==0){
					PlaySound(21);
					if((*it).y[0]<CENTER_Y+50){
						for(int i=0;i<1;i++)	ESMake((*it).x[0], (*it).y[0], Radian((*it).angle,FALSE)+160.0+0.1*get_rand(400), 3.0+0.1*get_rand(20), ESHOT(SSTAR,WATER), true, 0, 0, 0.0, 0, false);
					}
				}
				bRG = false;
				if(c%20==0){
					if(p==1)	ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 24.0, 15, 1.0, ESHOT(UROKO,RED), false, 33, 30, 2.0);				
					else		ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 24.0, 15, 1.0, ESHOT(UROKO,BLUE), false, 34, 30, 2.0);				
				}
			}
			else if(level==LUNATIC || level==IMPOSSIBLE){
				if(c%7==0){
					PlaySound(21);
					if((*it).y[0]<CENTER_Y){
						for(int i=0;i<1;i++)	ESMake((*it).x[0], (*it).y[0], Radian((*it).angle,FALSE)+160.0+0.1*get_rand(400), 2.0+0.1*get_rand(20), ESHOT(SSTAR,WATER), true, 0, 0, 0.0, 0, false);
					}
				}
				bRG = false;
				if(c%30==0){
					if(p==1)	ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 60.0, 6, 1.0, ESHOT(UROKO,RED), false, 33, 30, 2.0);				
					else		ESNWay((*it).x[0], (*it).y[0], Player[0].x, Player[0].y, 60.0, 6, 1.0, ESHOT(UROKO,BLUE), false, 34, 30, 2.0);				
				}
			}
		}
	}

	
	for(int i=LASER_ELEMENT_NUM-1;i>0;i--){
		(*it).x[i] = (*it).x[i-1];
		(*it).y[i] = (*it).y[i-1];
	}

	(*it).x[0] += (*it).speed*cos((*it).angle);
	(*it).y[0] += (*it).speed*sin((*it).angle);

	if(c>LASER_ELEMENT_NUM){
		(*it).bEff = false;
	}

	int num = 0; 
	for(int i=0;i<LASER_ELEMENT_NUM;i++){
		if((*it).x[i]+(*it).size<10-10 || (*it).y[i]+(*it).size<10-10 || (*it).x[i]-(*it).size>430+10 || (*it).y[i]-(*it).size>470+10){
			num++;
		}
	}
	if(bDe==true && num==LASER_ELEMENT_NUM)	(*it).bDelete = true;

	return;
}

void ESL1Make(float x, float y, float size, float length, float angle, float speed, int img, int pattern){
//直線。カンスト256
	if(ESLaser.size()==256){
	
	}
	else{
		PlaySound(31);
		ESLASERDATA P;
		P.base_x = x;
		P.base_y = y;
		for(int i=0;i<2;i++){
			P.edge_x[i] = x;
			P.edge_y[i] = y;
		}
		for(int i=0;i<LASER_ELEMENT_NUM;i++){
			P.x[i] = x;
			P.y[i] = y;
		}
		P.angle = Radian(angle,TRUE);
		P.speed = speed;
		P.move_x = cos(P.angle);
		P.move_y = sin(P.angle);
		P.size = size;
		P.length[0] = 0;
		P.length[1] = length;
		P.type = 0;
		P.flash = 255;
		P.img = img;
		P.count = 0;
		P.pattern = pattern;
		P.bDelete = false;
		P.bEff = true;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}

		ESLaser.push_back(P);
	}
	
	return;
}

void ESL2Make(float x, float y, float size, float angle, float speed,int img, int pattern){
//へにょり。カンスト256
	if(ESLaser.size()==256){
	
	}
	else{
		PlaySound(31);
		ESLASERDATA P;
		P.base_x = x;
		P.base_y = y;
		for(int i=0;i<2;i++){
			P.edge_x[i] = x;
			P.edge_y[i] = y;
		}
		for(int i=0;i<LASER_ELEMENT_NUM;i++){
			P.x[i] = x;
			P.y[i] = y;
		}
		P.angle = Radian(angle,TRUE);
		P.speed = speed;
		P.move_x = cos(P.angle);
		P.move_y = sin(P.angle);
		P.size = size;
		P.length[0] = 0;
		P.length[1] = 0;
		P.type = 1;
		P.flash = 255;
		P.img = img;
		P.count = 0;
		P.pattern = pattern;
		P.bDelete = false;
		P.bEff = true;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}

		ESLaser.push_back(P);
	}
	
	return;
}
