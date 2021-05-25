#include "effect.h"
#include "player.h"

list<EFFECTDATA> Effect;
list<EFFECTDATA> BackEffect;

void EfLoad();
void EfMake(float x,float y,int img,int pattern);
void EfDraw();
void EfMove(list<EFFECTDATA>::iterator &it);
void BEfMake(float x,float y,int img,int pattern);
void BEfDraw();
void BEfMove(list<EFFECTDATA>::iterator &it);


void EfLoad(){
	Effect.clear();
	BackEffect.clear();

	return;
}

void EfMake(float x,float y,int img,int pattern){
	EFFECTDATA P;
	P.bDelete = false;
	P.bBlend = true;
	P.x = x;
	P.y = y;
	P.large = 1.0;
	P.angle = 0;
	P.move_x = 0;
	P.move_y = 0;
	P.speed = 0;
	P.img = gEffect[img];
	P.count = 0;
	P.pattern = pattern;
	P.flash = 255;
	P.red = 255;
	P.green = 255;
	P.blue = 255;
	for(int i=0;i<8;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	Effect.push_back(P);

	return;
}

void EfDraw(){
	for(list<EFFECTDATA>::iterator it=Effect.begin();it!=Effect.end();++it){
		EfMove(it);
		if((*it).bDelete==true){
			it = Effect.erase(it);
			it--;
			continue;			
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if((*it).bBlend==true)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		if(repeat==9)	DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,(*it).img,TRUE,FALSE);
		SetDrawBright(255,255,255);
	}

	return;
}

void EfMove(list<EFFECTDATA>::iterator &it){
	if(bTimeStop==true)	return;
	int c = (*it).count;
	int p = (*it).pattern;
	if(p==0){//ゲージアイテム取得
		if(c==0){
			(*it).speed = 0;
			(*it).f_hanyou[0] = 0.1;
			(*it).large = 0.5;
			(*it).move_x = cos(Radian(-45-get_rand(90),TRUE));
			(*it).move_y = -1;
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 0;
			(*it).blue = 0;
		}
		if(c<30){
			(*it).speed += (*it).f_hanyou[0];
			(*it).flash -= 8.5;
		}
		else	(*it).bDelete = true;
	}
	for(int i=0;i<4;i++){//みそプレイヤー位置
		if(p>=1+10*i&&p<=10+10*i){
			if(c==0){
				Player[i].get_xy(&(*it).f_hanyou[0],&(*it).f_hanyou[1]);//目標地点
				(*it).f_hanyou[2] = (*it).x;
				(*it).f_hanyou[3] = (*it).y;
				(*it).large = 0.4;
			}
			if(c<80){
				switch((p-1)%10){
					case 0:	(*it).f_hanyou[4] = 0.9*(80-c)/3;		break;
					case 1:	(*it).f_hanyou[4] = -0.9*(80-c)/3;	break;
					case 2:	(*it).f_hanyou[4] = 1.8*(80-c)/3;		break;
					case 3:	(*it).f_hanyou[4] = -1.8*(80-c)/3;	break;
					case 4:	(*it).f_hanyou[4] = 2.7*(80-c)/3;		break;
					case 5:	(*it).f_hanyou[4] = -2.7*(80-c)/3;	break;
					case 6:	(*it).f_hanyou[4] = 3.6*(80-c)/3;		break;
					case 7:	(*it).f_hanyou[4] = -3.6*(80-c)/3;	break;
					case 8:	(*it).f_hanyou[4] = 4.5*(80-c)/3;		break;
					case 9:	(*it).f_hanyou[4] = -4.5*(80-c)/3;	break;
				}
				(*it).f_hanyou[4] = Radian((*it).f_hanyou[4],TRUE);
				float sax = (*it).f_hanyou[0] - (*it).f_hanyou[2];
				float say = (*it).f_hanyou[1] - (*it).f_hanyou[3];
				float ang = atan2(say,sax);
				float saq = sqrt(sax*sax+say*say) / 80.0;
				float r = saq * c;
				(*it).x = (*it).f_hanyou[2] + r*cos(ang+(*it).f_hanyou[4]);
				(*it).y = (*it).f_hanyou[3] + r*sin(ang+(*it).f_hanyou[4]);
			}
			else	(*it).bDelete = true;
		}
	}
	if(p==41){//みそボム投下可能
		if(c==0){
			(*it).speed = 0;
			(*it).f_hanyou[0] = 0.1;
			(*it).large = 0.5;
			(*it).move_x = cos(Radian(-45-get_rand(90),TRUE));
			(*it).move_y = -1;
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 0;
		}
		if(c<30){
			(*it).speed += (*it).f_hanyou[0];
			(*it).flash -= 8.5;
		}
		else	(*it).bDelete = true;
	}
	if(p>=42&&p<=45){//ランドマインランド
		if(c==0){
			(*it).speed = 3.0;
			(*it).large = 0.88;
			if(p==42){
				(*it).move_x = 1;
			}
			if(p==43){
				(*it).move_y = 1;
				(*it).angle = M_PI/2.0;
			}
			if(p==44){
				(*it).move_x = -1;
			}
			if(p==45){
				(*it).move_y = -1;
				(*it).angle = M_PI/2.0;
			}
			(*it).bBlend = true;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 255;
		}
		if(c<60){}
		else if(c<120){
			(*it).flash = 4.25*(120-c);
		}
		else	(*it).bDelete = true;
	}
	if(p==46){//コアオブザセカンドサン
		if(c==0){
			(*it).speed = 0;
			(*it).large = 2.0;
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 255;
		}
		if(bSecondSun==true){
			if((*it).large<50.0)	(*it).large += 0.5;
			else			(*it).large = 50.0;
		}
		else{
			if((*it).large>2.0)	(*it).large -= 0.5;
			else			(*it).large = 2.0;
		}
		(*it).flash = 55+abs(150-(2*c)%300);
	}


	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).count++;
	
        return;
}

void BEfMake(float x,float y,int img,int pattern){
	EFFECTDATA P;
	P.bDelete = false;
	P.bBlend = true;
	P.x = x;
	P.y = y;
	P.large = 1.0;
	P.angle = 0;
	P.move_x = 0;
	P.move_y = 0;
	P.speed = 0;
	P.img = gEffect[img];
	P.count = 0;
	P.pattern = pattern;
	P.flash = 255;
	P.red = 255;
	P.green = 255;
	P.blue = 255;
	for(int i=0;i<8;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	BackEffect.push_back(P);

	return;
}

void BEfDraw(){
	for(list<EFFECTDATA>::iterator it=BackEffect.begin();it!=BackEffect.end();++it){
		BEfMove(it);
		if((*it).bDelete==true){
			it = BackEffect.erase(it);
			it--;
			continue;			
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if((*it).bBlend==true)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		if(repeat==9)	DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,(*it).img,TRUE,FALSE);
		SetDrawBright(255,255,255);
	}

	return;
}

void BEfMove(list<EFFECTDATA>::iterator &it){
	if(bTimeStop==true)	return;
	int c = (*it).count;
	int p = (*it).pattern;
	if(p==0){//ゲージアイテム取得
		if(c==0){
			(*it).speed = 0;
			(*it).f_hanyou[0] = 0.1;
			(*it).large = 0.5;
			(*it).x += 5-get_rand(10);
			(*it).move_x = cos(Radian(-45-get_rand(90),TRUE));
			(*it).move_y = -1;
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 0;
			(*it).blue = 0;
		}
		if(c<30){
			(*it).speed += (*it).f_hanyou[0];
			(*it).flash -= 8.5;
		}
		else	(*it).bDelete = true;
	}
	for(int i=0;i<4;i++){//みそプレイヤー位置
		if(p>=1+10*i&&p<=10+10*i){
			if(c==0){
				Player[i].get_xy(&(*it).f_hanyou[0],&(*it).f_hanyou[1]);//目標地点
				(*it).f_hanyou[2] = (*it).x;
				(*it).f_hanyou[3] = (*it).y;
				(*it).large = 0.4;
			}
			if(c<80){
				switch((p-1)%10){
					case 0:	(*it).f_hanyou[4] = 0.9*(80-c)/3;		break;
					case 1:	(*it).f_hanyou[4] = -0.9*(80-c)/3;	break;
					case 2:	(*it).f_hanyou[4] = 1.8*(80-c)/3;		break;
					case 3:	(*it).f_hanyou[4] = -1.8*(80-c)/3;	break;
					case 4:	(*it).f_hanyou[4] = 2.7*(80-c)/3;		break;
					case 5:	(*it).f_hanyou[4] = -2.7*(80-c)/3;	break;
					case 6:	(*it).f_hanyou[4] = 3.6*(80-c)/3;		break;
					case 7:	(*it).f_hanyou[4] = -3.6*(80-c)/3;	break;
					case 8:	(*it).f_hanyou[4] = 4.5*(80-c)/3;		break;
					case 9:	(*it).f_hanyou[4] = -4.5*(80-c)/3;	break;
				}
				(*it).f_hanyou[4] = Radian((*it).f_hanyou[4],TRUE);
				float sax = (*it).f_hanyou[0] - (*it).f_hanyou[2];
				float say = (*it).f_hanyou[1] - (*it).f_hanyou[3];
				float ang = atan2(say,sax);
				float saq = sqrt(sax*sax+say*say) / 80.0;
				float r = saq * c;
				(*it).x = (*it).f_hanyou[2] + r*cos(ang+(*it).f_hanyou[4]);
				(*it).y = (*it).f_hanyou[3] + r*sin(ang+(*it).f_hanyou[4]);
			}
			else	(*it).bDelete = true;
		}
	}
	if(p==41){//みそボム投下可能
		if(c==0){
			(*it).speed = 0;
			(*it).f_hanyou[0] = 0.1;
			(*it).large = 0.5;
			(*it).x += 5-get_rand(10);
			(*it).move_x = cos(Radian(-45-get_rand(90),TRUE));
			(*it).move_y = -1;
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 0;
		}
		if(c<30){
			(*it).speed += (*it).f_hanyou[0];
			(*it).flash -= 8.5;
		}
		else	(*it).bDelete = true;
	}


	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).count++;
	
        return;
}
