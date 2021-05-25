#include "item.h"
#include "map.h"
#include "player.h"
#include "spell.h"


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
	P.dokuro_type = get_rand(10);
	P.count = 0;
	P.bExist = exist;
	
	Item.push_back(P);

	return;
}

void IDraw(){
	for(list<ITEMDATA>::iterator it=Item.begin(); it!=Item.end(); ++it){
		if((*it).bExist==true){
			if(Map.field[(*it).x][(*it).y]!=3){
				if((*it).type==10){
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
						IMake(rand_x, rand_y, 10, true);
						Map.field[rand_x][rand_y] = 3;
					}
				}				
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
					for(bool loo=false;loo==false;){
						loo = true;
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
						else if((*it).type==7){
							Player[i].bomb_max_plus(-1);
						}
						else if((*it).type==8){
							Player[i].level_plus();
						}
						else if((*it).type==9){
							play_sound(11);
							Player[i].set_spell_count(1);
							while(1){
								int rand = get_rand(36);
								if(rand==9 || rand==21){}
								else if(rand==8){
									SpMake(x,y,0,i,-1,true);
									SpMake(x,y,8,i,-1,true);
									SpMake(x,y,9,i,-1,true);
									break;
								}
								else{
									SpMake(x,y,rand,i,-1,true);
									break;
								}
							}							
						}
						else if((*it).type==10){
							if((*it).dokuro_type==0&&(Player[i].dokuro&1)==0)		Player[i].dokuro += 1;
							else if((*it).dokuro_type==1&&(Player[i].dokuro&2)==0)		Player[i].dokuro += 2;
							else if((*it).dokuro_type==2&&(Player[i].dokuro&4)==0)		Player[i].dokuro += 4;
							else if((*it).dokuro_type==3&&(Player[i].dokuro&8)==0)		Player[i].dokuro += 8;
							else if((*it).dokuro_type==4&&(Player[i].dokuro&16)==0)		Player[i].dokuro += 16;
							else if((*it).dokuro_type==5&&(Player[i].dokuro&32)==0)		Player[i].dokuro += 32;
							else if((*it).dokuro_type==6&&(Player[i].dokuro&64)==0)		Player[i].dokuro += 64;
							else if((*it).dokuro_type==7&&(Player[i].dokuro&128)==0)	Player[i].dokuro += 128;
							else if((*it).dokuro_type==8&&(Player[i].dokuro&256)==0)	Player[i].dokuro += 256;
							else if((*it).dokuro_type==9&&(Player[i].dokuro&512)==0)	Player[i].dokuro += 512;
							else if((*it).dokuro_type==10&&(Player[i].dokuro&1024)==0)	Player[i].dokuro += 1024;
							Player[i].dokuro_count = 1;	
						}
						else if((*it).type==11){
							loo = false;
							(*it).type = get_rand(20)/2;
						}
					}
					Map.field[(*it).x][(*it).y] = 0;
					dflag = true;
					break;
				}
			}
			if(dflag==true){
				if((*it).type==10)	play_sound(19);
				else	play_sound(6);
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
