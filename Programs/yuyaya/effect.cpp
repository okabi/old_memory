#include "effect.h"
#include "enemy.h"
#include "system.h"

list<EFFECTDATA> Effect;
list<EFFECTDATA> Effect2;//自機の下
list<EFFECTDATA> Effect3;//敵弾の上
list<ITEMDATA> Item;

void EfReset();
void EfDraw();
void EfMove(list<EFFECTDATA>::iterator &it);
void EfMake(float x,float y,int img,int pattern,int spe_count,float angle);
void EfDraw2();
void EfMove2(list<EFFECTDATA>::iterator &it);
void EfMake2(float x,float y,int num,int pattern,float angle,bool bBlend);
void EfDraw3();
void EfMove3(list<EFFECTDATA>::iterator &it);
void EfMake3(float x,float y,int pattern,float angle);
void IDraw();
void IMove(list<ITEMDATA>::iterator &it);
void IMake(float x,float y,int img,int late);

void EfReset(){
	Effect.clear();
	Effect2.clear();
	Effect3.clear();
	Item.clear();

	return;
}

void EfDraw(){
	for(list<EFFECTDATA>::iterator it=Effect.begin(); it!=Effect.end(); ++it){
		EfMove(it);
		if((*it).bDelete==true){
			it = Effect.erase(it);
			it--;
			continue;			
		}
		if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		if((*it).pattern==8 || (*it).pattern==9){//敵弾出現、消滅
			if(GetSkip()){
				if((*it).img==FRED)		DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEShot[ESHOT(MEDIUM,RED)], TRUE, FALSE);	
				else if((*it).img==FBLUE)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEShot[ESHOT(MEDIUM,BLUE)], TRUE, FALSE);	
				else if((*it).img<8*18){
					int type = (*it).img/8;
					if(type==SMALL)		type = SMALL;
					else if(type==BIG || type==OVAL || type==STAR)	type = BIG;
					else			type = MEDIUM;
					DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEShot[ESHOT(type,(*it).img%8)], TRUE, FALSE);
				}
				else{
					DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEShot[(*it).img], TRUE, FALSE);
				}
			}
		}
		else{
			if(GetSkip()){
				if((*it).img>=0)	DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEffect[(*it).img], TRUE, FALSE);
				else			DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEffect2[-(*it).img-1], TRUE, FALSE);
			}
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void EfMove(list<EFFECTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	bool bAngle = true;

	if(p>=0 && p<4){//敵に着弾したときのチュドーン(0:通常弾 1:通常レーザー 2:ハイパー弾 3:ハイパーレーザー)
		if(c==0){
			(*it).speed = 3.0 + 0.01*get_rand(500);
			//(*it).speed = 8.0 + 0.01*get_rand(800);
			(*it).angle = Radian(0.1*get_rand(3600),TRUE);
			(*it).move_x = cos((*it).angle);
			(*it).move_y = sin((*it).angle);
			(*it).large = 0.1 + 0.01*get_rand(50);
			(*it).flash = 150;
			(*it).f_hanyou[0] = (*it).large / 10.0;
			if(p==0){
				(*it).red = 255;
				(*it).green = 100;
				(*it).blue = 100;
			}
			else if(p==1){
				(*it).red = 255;
				(*it).green = 200;
				(*it).blue = 100;
			}
			else if(p==2 || p==3){
				if(Player[0].chara==0){
					(*it).red = 255;
					(*it).green = 100;
					(*it).blue = 255;
				}
				else if(Player[0].chara==1){
					(*it).red = 150;
					(*it).green = 150;
					(*it).blue = 255;
				}
				else if(Player[0].chara==2){
					(*it).red = 100;
					(*it).green = 100;
					(*it).blue = 255;
				}
				else if(Player[0].chara==3){
					(*it).red = 255;
					(*it).green = 100;
					(*it).blue = 100;
				}
				else if(Player[0].chara==4){
					(*it).red = 255;
					(*it).green = 255;
					(*it).blue = 100;
				}
				else if(Player[0].chara==5){
					(*it).red = 100;
					(*it).green = 255;
					(*it).blue = 100;
				}
			}
		}
		if(c<10)	(*it).large -= (*it).f_hanyou[0];
		else		(*it).bDelete = true;
	}
	else if(p==4){//敵が爆発┗(^o^)┛
		bAngle = false;
		if(c==15)	(*it).img = 4;
		if(c<20)	(*it).large = 0.1+0.05*c;
		else		(*it).bDelete = true;
		(*it).angle += Radian(45.0,TRUE);
		(*it).flash = 12.75*(20-c);
	}
	else if(p==5){//自機が爆発させていただいてます┗(^o^)┛
		bAngle = false;
		if(c==20)	(*it).img = 6;
		if(c<30)	(*it).large = 0.1+0.1*c;
		else		(*it).bDelete = true;
		(*it).angle += Radian(45.0,TRUE);
		(*it).flash = 8.5*(30-c);
	}
	else if(p==6 || p==7){//ボム消えるときのえふぇ☆
		bAngle = false;
		if(p==6){
			if(c==0)	(*it).large = 3.0;
			(*it).red = 100;
			(*it).green = 100;
			(*it).blue = 255;
			(*it).flash = 22.75*(20-c);
		}
		else if(p==7){
			if(c==0)	(*it).large = 1.0;
			(*it).red = 255;
			(*it).green = 50;
			(*it).blue = 50;
			(*it).flash = 2.0*(20-c);
		}
		if(c<20)	(*it).large += 0.1;
		else		(*it).bDelete = true;
		(*it).angle += Radian(45.0,TRUE);
	}
	else if(p==8){//敵弾登場
		bAngle = false;
		if(c==0){
			(*it).large = 3.0;
			(*it).flash = 0;
			(*it).f_hanyou[0] = 2.0 / (*it).spe_count;
			(*it).f_hanyou[1] = 200.0 / (*it).spe_count;
		}
		(*it).large -= (*it).f_hanyou[0];
		(*it).flash += (*it).f_hanyou[1];
		if(c==(*it).spe_count)	(*it).bDelete = true;
		(*it).angle += Radian(45.0,TRUE);
	}
	else if(p==9){//敵弾消滅☆
		bAngle = false;
		(*it).spe_count = 20;
		if((*it).img<8*18){
			if(c==0){
				(*it).large = 1.0;
				(*it).flash = 150;
				(*it).f_hanyou[0] = 2.0 / (*it).spe_count;
				(*it).f_hanyou[1] = 150.0 / (*it).spe_count;
			}
			(*it).large += (*it).f_hanyou[0];
			(*it).flash -= (*it).f_hanyou[1];
		}
		else{
			if(c==0){
				(*it).large = 1.0;
				(*it).flash = 150;
				(*it).f_hanyou[0] = 1.0 / (*it).spe_count;
				(*it).f_hanyou[1] = 150.0 / (*it).spe_count;
			}
			(*it).large -= (*it).f_hanyou[0];
			(*it).flash -= (*it).f_hanyou[1];
		}
		if(c==(*it).spe_count)	(*it).bDelete = true;
		(*it).angle += Radian(45.0,TRUE);
	}
	else if(p==10){//ハイパー溜まったよー
		bAngle = false;
		if(c==0)	(*it).f_hanyou[0] = Radian((*it).spe_count,TRUE);
		(*it).f_hanyou[0] += Radian(12.0,TRUE);
		(*it).speed = 4.0;
		(*it).flash = 150;
		(*it).large = 0.1*(20-c);
		(*it).move_x = cos((*it).f_hanyou[0]);
		(*it).move_y = sin((*it).f_hanyou[0]);
		if(c==20)	(*it).bDelete = true;
		(*it).angle += Radian(45.0,TRUE);
	}
	else if(p==11){//敵さんチャージ
		bAngle = false;
		if(c==0){
			float d = (*it).spe_count;
			float an = get_rand(360);
			(*it).x += d*cos(Radian(an,TRUE));
			(*it).y += d*sin(Radian(an,TRUE));
			(*it).move_x = cos(Radian(an+180,TRUE));
			(*it).move_y = sin(Radian(an+180,TRUE));
			(*it).speed = d / 40.0;
			(*it).angle = Radian(get_rand(360),TRUE);
		}
		if(c==40)	(*it).bDelete = true;
		(*it).flash = 6.375*c;
		(*it).large = 0.15*(40-c);
		(*it).angle += Radian(10.0,TRUE);
	}
	else if(p==12){//バス核爆発
		bAngle = false;
		(*it).large = 0.20*c;
		if(c<120)	(*it).flash = 150;
		else if(c<180)	(*it).flash = 150-2.5*(c-120);
		else		(*it).bDelete = true;
		(*it).angle += Radian(10.0,TRUE);
	}
 	else if(p==13){//ニュークリアきもも
		if(c==0){
			(*it).angle = Atan2((*it).move_y, (*it).move_x);
			(*it).speed = 1.5;
			(*it).bBlend = true;
			(*it).flash = 255;
		}
		if(c<40)	(*it).large = 0.025*c;
		else		(*it).large = 1.0;
		if(c>500)	(*it).bDelete = true;
	}
 	else if(p==14){//コア・オブ・ザ・セカンドサン
		list<BOSSDATA>::iterator bit = Boss.begin();
		(*it).x = (*bit).x;
		(*it).y = (*bit).y;
		if(c==0){
			(*it).move_y = 1.0;
			(*it).bBlend = true;
			(*it).flash = 255;
		}
		if(c<40)	(*it).large = 0.025*c;
		else		(*it).large = 1.0;
	}
	else if(p==15){//グレイズ
		if(c==0){
			(*it).speed = 3.0 + 0.01*get_rand(500);
			//(*it).speed = 8.0 + 0.01*get_rand(800);
			(*it).angle = Radian(0.1*get_rand(3600),TRUE);
			(*it).move_x = cos((*it).angle);
			(*it).move_y = sin((*it).angle);
			(*it).large = 0.4 + 0.01*get_rand(30);
			(*it).flash = 150;
			(*it).f_hanyou[0] = (*it).large / 20.0;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 255;
		}
		if(c<20)	(*it).large -= (*it).f_hanyou[0];
		else		(*it).bDelete = true;
	}
	else if(p==16 || p==17){//ハイパー終了しますよー
		bAngle = false;
		if(c==0){
			(*it).f_hanyou[0] = Atan2((*it).move_y,(*it).move_x);
			(*it).f_hanyou[1] = Player[0].x;
			(*it).f_hanyou[2] = Player[0].y;
		}
		if(p==16)	(*it).f_hanyou[0] += Radian(3.0,TRUE);
		else if(p==17)	(*it).f_hanyou[0] -= Radian(3.0,TRUE);
		(*it).move_x = cos((*it).f_hanyou[0]);
		(*it).move_y = sin((*it).f_hanyou[0]);
		if(Player[0].chara==0){
			(*it).red = 255;
			(*it).green = 100;
			(*it).blue = 255;
		}
		else if(Player[0].chara==1){
			(*it).red = 150;
			(*it).green = 150;
			(*it).blue = 255;
		}
		else if(Player[0].chara==2){
			(*it).red = 100;
			(*it).green = 100;
			(*it).blue = 255;
		}
		else if(Player[0].chara==3){
			(*it).red = 255;
			(*it).green = 100;
			(*it).blue = 100;
		}
		else if(Player[0].chara==4){
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 100;
		}
		else if(Player[0].chara==5){
			(*it).red = 100;
			(*it).green = 255;
			(*it).blue = 100;
		}
		(*it).flash = 7.0*c;
		(*it).large = 0.08*(30-c);
		(*it).x = (*it).f_hanyou[1] + 6.0*(30-c)*(*it).move_x;
		(*it).y = (*it).f_hanyou[2] + 6.0*(30-c)*(*it).move_y;
		(*it).angle += Radian(3.0,TRUE);
		if(c==30)	(*it).bDelete = true;
	}
	else if(p==18){//ハイパー終了したよー
		bAngle = false;
		(*it).flash = 255-5.1*c;
		(*it).large = 0.1*c;
		//(*it).x = Player[0].x;
		//(*it).y = Player[0].y;
		(*it).angle += Radian(12.0,TRUE);
		if(c==50)	(*it).bDelete = true;
	}

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;
	
	if(bAngle==true)	(*it).angle = Atan2((*it).move_y,(*it).move_x);
	
	return;
}

void EfMake(float x,float y,int img,int pattern,int spe_count,float angle){
//カンスト5000
	if(Effect.size()==5000){
	
	}
	else{
		EFFECTDATA P;
		P.x = x;
		P.y = y;
		P.large = 1.0;
		P.angle = 0.0;
		P.speed = 0.0;
		P.move_x = 0.0;
		P.move_y = 0.0;
		if(fabs(angle)>0.01){
			P.move_x = cos(angle);
			P.move_y = sin(angle);
		}
		P.flash = 255;
		P.red = 255;
		P.green = 255;
		P.blue = 255;
		P.img = img;
		P.count = 0;
		P.num = 0;
		P.spe_count = spe_count;
		P.pattern = pattern;
		P.bBlend = true;
		P.bDelete = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}

		Effect.push_back(P);
	}
	
	return;
}

void EfDraw2(){
	for(list<EFFECTDATA>::iterator it=Effect2.begin(); it!=Effect2.end(); ++it){
		EfMove2(it);
		if((*it).bDelete==true){
			it = Effect2.erase(it);
			it--;
			continue;			
		}
		if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		if((*it).pattern==0){
			//draw_hit((*it).x, (*it).y, (*it).i_hanyou[0], 1);
			draw_hit((*it).x, (*it).y, (*it).i_hanyou[0], 3);
		}
		else if((*it).pattern==1){
			if((*it).num==1000000)		draw_hit((*it).x, (*it).y, (*it).num, 3);
			else				draw_hit((*it).x, (*it).y, (*it).num, 2);
		}
		else if((*it).pattern==2 || (*it).pattern==3 || (*it).pattern==4){
			DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, 1.0, (*it).angle-M_PI/2.0, (*it).img, TRUE, FALSE);
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void EfMove2(list<EFFECTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	
	if(p==0){//アイテム取得時ヒット数表示
		if(c<50){
			//(*it).red = 200;
			//(*it).green = 255;
			//(*it).blue = 200;
			//(*it).speed = 3.0;
			(*it).speed = 1.0;
			//float angle = Radian(45,TRUE);
			float angle = Radian(-90,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			if(c>=30)	(*it).flash = 7.0*(50-c);
			else		(*it).flash = 140;
			if(c==0)	(*it).i_hanyou[1] = (*it).num/30 + 1;
			(*it).i_hanyou[0] += (*it).i_hanyou[1];
			if((*it).i_hanyou[0]>(*it).num)	(*it).i_hanyou[0] = (*it).num;
		}
		else	(*it).bDelete = true;
	}
	else if(p==1){//ハイパーアイテム取得時ぽいんと表示
		if(c<50){
			(*it).speed = 3.0;
			float angle = Radian(45,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			if(c>=30)	(*it).flash = 5.0*(50-c);
			else		(*it).flash = 100;
		}
		else	(*it).bDelete = true;
	}
	else if(p==2 || p==3){//もしもシリーズってレベルじゃねーぞ！
		int gx,gy;
		GetGraphSize((*it).img,&gx,&gy);
		gx /= 2;
		gy /= 2;
		if(c<=1){
			if(p==2)	(*it).speed = 8.0;
			else if(p==3)	(*it).speed = 12.0;
			float angle = Radian((*it).f_hanyou[0],TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
		(*it).angle += Radian(9.0,TRUE);
		if((*it).x+gx<10 || (*it).y+gy<10 || (*it).x-gx>430 || (*it).y-gy>470){
			(*it).bDelete = true;
		}
		if(p==3){
			if((*it).x-gx<10 || (*it).y-gy<10 || (*it).x+gx>430 || (*it).y+gy>470){
				if((*it).i_hanyou[0]==15){}
				else{
					if((*it).x-gx<10 || (*it).x+gx>430)	(*it).move_x *= -1;
					if((*it).y-gy<10 || (*it).y+gy>470)	(*it).move_y *= -1;
					(*it).i_hanyou[0]++;
				}
			}
		}	
	}
	else if(p==4){//ラストワード敵エフェクト
		if(c==0){
			(*it).speed = 1.0 + 0.01*get_rand(300);
			(*it).angle = Radian(-150.0 + 0.1*get_rand(1200),TRUE);
			(*it).move_x = cos((*it).angle);
			(*it).move_y = sin((*it).angle);
			(*it).large = 0.5 + 0.01*get_rand(30);
			(*it).flash = 100;
			(*it).f_hanyou[0] = (*it).large / 30.0;
			if(p==4){
				(*it).red = 255;
				(*it).green = 50 + get_rand(150);
				(*it).blue = 255;
			}
		}
		if(c<30)	(*it).large -= (*it).f_hanyou[0];
		else		(*it).bDelete = true;
	}

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;

	return;
}

void EfMake2(float x,float y,int num,int pattern,float angle,bool bBlend){
//カンスト5000
	if(Effect2.size()==5000){
	}
	else{
		EFFECTDATA P;
		P.x = x;
		P.y = y;
		P.large = 1.0;
		P.angle = angle;
		P.speed = 0.0;
		P.move_x = 0.0;
		P.move_y = 0.0;
		P.flash = 255;
		P.red = 255;
		P.green = 255;
		P.blue = 255;
		if(pattern==2 || pattern==3 || pattern==4)	P.img = num;
		else		P.img = 0;
		P.count = 0;
		P.num = num;
		P.spe_count = 0;
		P.pattern = pattern;
		P.bBlend = bBlend;
		P.bDelete = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}
		if(pattern==2 || pattern==3)	P.f_hanyou[0] = angle;

		Effect2.push_back(P);
	}
	
	return;
}

void EfDraw3(){
	for(list<EFFECTDATA>::iterator it=Effect3.begin(); it!=Effect3.end(); ++it){
		EfMove3(it);
		if((*it).bDelete==true){
			it = Effect3.erase(it);
			it--;
			continue;			
		}
		if((*it).bBlend==false)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		if((*it).pattern==0){
			DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gEffect[(*it).img], TRUE, FALSE);
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void EfMove3(list<EFFECTDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	
	if(p==0){//気符「英語雲散霧消」の霧
		if(c==0){
 			float angle = Radian(get_rand(360),TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).angle = Radian(get_rand(360),TRUE);
			(*it).speed = 0.5;
		}
		if(c<50)	(*it).flash = 5.1*c;
		else if(c<180)	(*it).flash = 255;
		else if(c<230)	(*it).flash = (230-c)*5.1;
		else		(*it).bDelete = true;
	}

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;

	return;
}

void EfMake3(float x,float y,int pattern,float angle){
//カンスト5000
	if(Effect3.size()==5000){
	}
	else{
		EFFECTDATA P;
		P.x = x;
		P.y = y;
		P.large = 1.0;
		P.angle = 0.0;
		P.speed = 0.0;
		P.move_x = 0.0;
		P.move_y = 0.0;
		P.flash = 255;
		P.red = 255;
		P.green = 255;
		P.blue = 255;
		if(pattern==0)		P.img = 10;
		P.count = 0;
		P.num = 0;
		P.spe_count = 0;
		P.pattern = pattern;
		P.bBlend = true;
		P.bDelete = false;
		for(int i=0;i<8;i++){
			P.f_hanyou[i] = 0;
			P.i_hanyou[i] = 0;
		}

		Effect3.push_back(P);
	}
	
	return;
}

void IDraw(){
	SetDrawBright(255,255,255);
	for(list<ITEMDATA>::iterator it=Item.begin(); it!=Item.end(); ++it){
		if((*it).count>=0){
			IMove(it);
			int gx,gy;
			GetGraphSize(gItem[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			gx *= (*it).large;
			gy *= (*it).large;
			if((*it).x+gx<10 || (*it).x-gx>430 || (*it).y+gy<10 || (*it).y-gy>470){
				if((*it).bDelete==true || (*it).count>=120 || (((*it).img==0||(*it).img==1||(*it).img==2)&&(*it).count==0)){
					if(!((*it).img==3&&(*it).y+gy<10)){
						it = Item.erase(it);
						it--;
						continue;			
					}
				}
			}
			else{
				if((*it).img!=0)	(*it).bDelete = true;
			}
			if(GetSkip()){
				if((*it).img==0 || (*it).img==1 || (*it).img==2){
					int flash = 200;
					SetDrawBlendMode(DX_BLENDMODE_ADD,flash);
					DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large*1.3, (*it).angle-M_PI/2.0, gItem[(*it).img], TRUE, FALSE);
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
				DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, (*it).large, (*it).angle-M_PI/2.0, gItem[(*it).img], TRUE, FALSE);
			}
		}
		else{
			(*it).bKira = true;
			int flash = 100.0+2.5*(*it).count;
			if(flash<0)	flash = 0;
			SetDrawBlendMode(DX_BLENDMODE_ADD,flash);
			if(GetSkip()){
				DrawRotaGraphF((*it).x+shake_x, (*it).y+shake_y, 1.0-0.15*(*it).count, Radian(24.0*(*it).count,TRUE)-M_PI/2.0, gEShot[ESHOT(MEDIUM,YELLOW)], TRUE, FALSE);
			}
		}
		(*it).count++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void IMove(list<ITEMDATA>::iterator &it){
	int p = (*it).pattern;
	int c = (*it).count;
	
	if((*it).img==0 || (*it).img==1 || (*it).img==2){
		if((*it).img<=1 && c<20)	(*it).large = 0.05 * c;
		else if((*it).img==2 && c<20)	(*it).large = 0.06 * c;
		else if((*it).img<=1)	(*it).large = 1.0;
		else	(*it).large = 1.2;
		if(c<60)	(*it).angle += Radian(24.0,TRUE);
		else		(*it).angle = Atan2(1,0);
	}
	else if((*it).img==3){
		if(c<5)	(*it).large = 0.3 * c;
		else	(*it).large = 1.5;
		(*it).angle = Atan2(1,0);
	}
	else if((*it).img==4 || (*it).img==5){
		if(c<5)	(*it).large = 0.4 * c;
		else	(*it).large = 2.0;
		(*it).angle = Atan2(1,0);
	}
	
	if(p==0){
		if(c<40)	(*it).speed = 4.0 - 0.2*c;
		else		(*it).speed = -4.0;
		(*it).move_x = 0;
		(*it).move_y = -1;
	}
	else if(p==1){
		if(c<40){
			(*it).speed = 4.0 - 0.2*c;
			(*it).move_x = 0;
			(*it).move_y = -1;
		}
		else{
			float angle = Atan2(Player[0].y-(*it).y, Player[0].x-(*it).x);
			(*it).speed = 7.0;
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
		}
	}
	else if(p==2){
		if(c<40)	(*it).speed = 4.0 - 0.2*c;
		else		(*it).speed = -4.0;
		(*it).move_x = 0;
		(*it).move_y = -1;
	}
	else if(p==3){
		//ボム・1upアイテムふよふよ
		if(c==0){
			float angle = Radian(225,TRUE);
			(*it).move_x = cos(angle);
			(*it).move_y = sin(angle);
			(*it).speed = 2.0;
		}
		if((*it).bound_num<10){
			int gx,gy;
			GetGraphSize(gItem[(*it).img],&gx,&gy);
			gx /= 2;
			gy /= 2;
			gx *= 2;
			gy *= 2;
			if((*it).x-gx<0 || (*it).x+gx>440){
				(*it).move_x *= -1;
				(*it).bound_num++;
			}
			if((*it).y-gy<0 || (*it).y+gy>480){
				(*it).move_y *= -1;
				(*it).bound_num++;
			}
		}	
	}

	(*it).x += (*it).speed * (*it).move_x;
	(*it).y += (*it).speed * (*it).move_y;

	int gx,gy;
	GetGraphSize(gItem[(*it).img],&gx,&gy);
	gx *= (*it).large;
	gy *= (*it).large;
	(*it).atari = sqrt((float)(gx/2*gx/2+gy/2*gy/2));
	
	return;
}

void IMake(float x,float y,int img, int late){
//カンスト5000
	if(Item.size()==5000 || (Player[0].level==IMPOSSIBLE&&(img==4||img==5))){
	
	}
	else{
		ITEMDATA P;
		P.x = x;
		P.y = y;
		P.large = 1.0;
		P.angle = 0.0;
		P.speed = 0.0;
		P.move_x = 0.0;
		P.move_y = -1.0;
		int gx,gy;
		GetGraphSize(gItem[img],&gx,&gy);
		P.atari = sqrt((float)(gx/2*gx/2+gy/2*gy/2));
		P.flash = 255;
		P.img = img;
		P.count = -late;
		P.bound_num = 0;
		if(img==0 || img==1 || img==2){
			P.soten = 0;
			P.pattern = 1;
			//int add = Player[0].soten/pow(10,2-img);
			//if(Player[0].hit>0)	EfMake2(x, y, add/10*10, 0);
			//if(Player[0].hit>0)	EfMake2(x, y, Player[0].hit, 0);
		}
		else if(img==3){
			P.soten = 0;
			P.pattern = 2;
		}
		else if(img==4 || img==5){
			P.soten = 0;
			P.pattern = 3;
		}
		P.bKira = false;
		P.bDelete = false;

		Item.push_back(P);
	}
	
	return;
}