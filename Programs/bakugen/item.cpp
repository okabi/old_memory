#include "item.h"
#include "map.h"
#include "player.h"


list<ITEMDATA> Item;

void ILoad();
void IMake(int x,int y,int type);
void IDraw();
void IMove(list<ITEMDATA>::iterator &it);

void ILoad(){
	Item.clear();

	return;
}

void IMake(int x,int y,int type, bool exist){
	ITEMDATA P;
	P.x = x;
	P.y = y;
	P.angle = 0;
	P.img = gItem[type];
	P.type = type;
	P.count = 0;
	P.bExist = exist;
	
	Item.push_back(P);

	return;
}

void IDraw(){
	for(list<ITEMDATA>::iterator it=Item.begin(); it!=Item.end(); ++it){
		if((*it).bExist==true){
			if(Map.field[(*it).x][(*it).y]!=3){
				it = Item.erase(it);
				it--;
				continue;						
			}
			IMove(it);
			bool dflag = false;
			for(int i=0;i<PLAYER_NUM;i++){
				float x,y;
				Player[i].get_xy(&x,&y);
				if(X_ZAHYO_TO_NUM(x)==(*it).x&&Y_ZAHYO_TO_NUM(y)==(*it).y){
					if((*it).type==0){
						Player[i].power_plus();
					}
					else if((*it).type==1){
						Player[i].bomb_max_plus();
					}
					else if((*it).type==2){
						Player[i].gage_count_plus(300);
					}
					else if((*it).type==3){
						Player[i].power_plus(9);
					}
					else if((*it).type==4){
						Player[i].power_plus(-1);
					}
					else if((*it).type==5){
						Player[i].bKickbomb = true;
					}
					else if((*it).type==6){
						Player[i].bSpbomb = true;
					}
					Map.field[(*it).x][(*it).y] = 0;
					dflag = true;
					break;
				}
			}
			if(dflag==true){
				play_sound(6);
				it = Item.erase(it);
				it--;
				continue;						
			}
			SetDrawMode(DX_DRAWMODE_BILINEAR);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if((*it).type==6){
				if((*it).count%10<5)	SetDrawBright(150,150,0);
				else			SetDrawBright(255,255,100);
                        }
			float x = (X_NUM_TO_ZAHYO((*it).x)+X_NUM_TO_ZAHYO((*it).x+1))/2.0;
			float y = (Y_NUM_TO_ZAHYO((*it).y)+Y_NUM_TO_ZAHYO((*it).y+1))/2.0;
			if(repeat==9)	DrawRotaGraphF(x+shake_x,y+shake_y,1.5,(*it).angle,(*it).img,TRUE);
			SetDrawBright(255,255,255);
		}
	}

	return;
}

void IMove(list<ITEMDATA>::iterator &it){
	if(bTimeStop==true)	return;
	if((*it).count>100&&(*it).count%200<15){
		(*it).angle = Radian(24*((*it).count%200),TRUE);
	}
	else{
		(*it).angle = 0;
	}
	(*it).count++;
	
	return;
}
