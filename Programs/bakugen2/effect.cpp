#include "effect.h"
#include "player.h"
#include "map.h"
#include "item.h"

list<EFFECTDATA> Effect;
list<EFFECTDATA> BackEffect;

static float mx[4],my[4];

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
	if(img>=0)	P.img = gEffect[img];
	else		P.img = gItem[0];
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
				float ang = Atan2(say,sax);
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
  	if(p==47){//ギガフレア・アトミックボム
		if(c==0){
			(*it).speed = 0;
			(*it).large = 0.0;
			(*it).bBlend = false;
			(*it).flash = 255;
		}
		(*it).large += 0.8;
		(*it).flash--;
		if((*it).flash==0)	(*it).bDelete = true;
	}
  	if(p==48){//レイディアントシルバーガン
		if(c==0){
			(*it).speed = 0;
			(*it).large = 1.3;
			(*it).bBlend = true;
			(*it).i_hanyou[0] = -1;
		}
		if((*it).i_hanyou[0]==6){
			if(c%10<5){
				(*it).red = 150;
				(*it).green = 150;
				(*it).blue = 0;
			}
			else{
				(*it).red = 255;
				(*it).green = 255;
				(*it).blue = 100;
        		}
	        }
		else{
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 255;
		}
		if(bTreasure==true){
			(*it).flash = 0;
			if(TreasureCount==0){
				play_sound(18);
				(*it).flash = 0;
				int num = 3+get_rand(3);
				for(int a=0;a<num;a++){
					int rand_x,rand_y;
					bool flag = false;
					for(int i=0;i<50;i++){
						rand_x = get_rand(LARGE_X-1);
						rand_y = get_rand(LARGE_Y-1);
						if(Map.field[rand_x][rand_y]==0){
							flag = true;
							break;
						}
					}
					if(flag==true){
						IMake(rand_x, rand_y, (*it).i_hanyou[0], true);
						Map.field[rand_x][rand_y] = 3;
					}
				} 
			}
			TreasureCount++;
			if(TreasureCount<70){
				if(TreasureCount<50){
					(*it).bBlend = false;
					(*it).flash = 5.1*(50-TreasureCount);
					(*it).large += 1.2;
				}
				else{
					(*it).flash = 0;
				}
			}
			else{
				(*it).flash = 5.1*(TreasureCount-70);
				(*it).large = 1.3;
				(*it).bBlend = true;
			}
			if(TreasureCount==120){
				TreasureCount = 0;
				bTreasure = false;
			}
		}
		else{
			(*it).flash = 255;
			if(c%60==0){
				int be = (*it).i_hanyou[0];
				while(1){
					int rand = get_rand(255)+1;
					if(rand<10)		(*it).i_hanyou[0] = 0;
					else if(rand<20)	(*it).i_hanyou[0] = 1;
					else if(rand<30)	(*it).i_hanyou[0] = 2;
					else if(rand<40)	(*it).i_hanyou[0] = 3;
					else if(rand<50)	(*it).i_hanyou[0] = 4;
					else if(rand<76)	(*it).i_hanyou[0] = 5;
					else if(rand<102)	(*it).i_hanyou[0] = 6;
					else if(rand<112)	(*it).i_hanyou[0] = 7;
					else if(rand<128)	(*it).i_hanyou[0] = 8;
					else if(rand<192)	(*it).i_hanyou[0] = 9;
					else if(rand<224)	(*it).i_hanyou[0] = 10;
					else if(rand<256)	(*it).i_hanyou[0] = 11;
					if(be!=(*it).i_hanyou[0])	break;
				}
				(*it).img = gItem[(*it).i_hanyou[0]];
			}
		}
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
	if(img>=0)	P.img = gEffect[img];
	else if(img==-1)P.img = gMap[MapData[Map.type].img_block[0]][MapData[Map.type].img_block[1]];
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
	SetUseMaskScreenFlag(TRUE);
	FillMaskScreen(0);
	int mcount=0;
	for(int i=0;i<4;i++){
		mx[i] = -1;
		my[i] = -1;
	}
	for(int b=0;b<PLAYER_NUM;b++){
		if(Player[b].get_condition()==0&&Player[b].get_chara()==REISEN){
			int sx,sy;
			float x,y;
			GetMaskSize(&sx, &sy, gEffect[7]);
			Player[b].get_xy(&x,&y);
			mx[mcount] = x;
			my[mcount] = y;
			mcount++;
			DrawMask(x-sx/2, y-sy/2, gEffect[7], DX_MASKTRANS_BLACK);
		}
	}
	SetUseMaskScreenFlag(FALSE);

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
		if(repeat==9){
			if((*it).pattern!=43)	DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,(*it).img,TRUE,FALSE);
			else			DrawExtendGraph((*it).x+shake_x, (*it).y+shake_y, (*it).x+X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0)+shake_x, (*it).y+Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0)+shake_y, (*it).img, TRUE);
		}
		SetDrawBright(255,255,255);
		SetUseMaskScreenFlag(FALSE);
	}

	SetUseMaskScreenFlag(FALSE);

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
				float ang = Atan2(say,sax);
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
	if(p==42){//反魂蝶
		if(c==0){
			(*it).speed = 0;
			(*it).large = 1.0;
		}
		if(c<30){
			(*it).large += 0.05;
			(*it).flash -= 8.5;
		}
		else	(*it).bDelete = true;
	}
	if(p==43){//幻影の壁（イリュージョンウォール）
		if(c==0){
			(*it).speed = 0;
			(*it).large = 1.0;
			(*it).flash = 0;
		}
		if(c<51){
			(*it).flash += 5;
		}
		else if(c<550){
			(*it).flash = 255;
		}
		else if(c<601){
			(*it).flash -= 5;
		}	
		else	(*it).bDelete = true;

		int sx,sy;
		GetMaskSize(&sx, &sy, gEffect[7]);
		SetUseMaskScreenFlag(FALSE);
		for(int b=0;b<4;b++){
			if(mx[b]!=-1){
				float ssx = mx[b] - (*it).x;
				float ssy = my[b] - (*it).y;
				float d = sqrt(ssx*ssx+ssy*ssy);
				if(d<sqrt((sx/2)*(sx/2)+(sy/2)*(sy/2))+20){
					SetUseMaskScreenFlag(TRUE);
					break;
				}
			}
			else	break;
		}
	}

	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).count++;
	
        return;
}
