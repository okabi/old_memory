#include "spell.h"
#include "map.h"
#include "player.h"
#include "bomb.h"


list<SPELLDATA> Spell;

void SpLoad();
void SpMake(float x,float y,int type,int player);
void SpDraw();
void SpMove(list<SPELLDATA>::iterator &it);

void SpLoad(){
	Spell.clear();

	return;
}

void SpMake(float x,float y,int type,int player){
	SPELLDATA P;
	P.x = x;
	P.y = y;
	P.angle = 0;
	P.large = 1.0;
	switch(type){
		case 0: //マスタースパーク
			P.img = gSpell[0];
			break;
	}
	P.type = type;
	P.count = 0;
	P.player = player;
	P.flash = 255;
	P.bDelete = false;
	for(int i=0;i<8;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	
	Spell.push_back(P);

	return;
}

void SpDraw(){
	for(list<SPELLDATA>::iterator it=Spell.begin(); it!=Spell.end(); ++it){
		SpMove(it);
		if((*it).bDelete==true){
			it = Spell.erase(it);
			it--;
			continue;						
		}
		if((*it).type==0){
			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
			if(repeat==9)	DrawModiGraph((*it).f_hanyou[0],(*it).f_hanyou[1],(*it).f_hanyou[2],(*it).f_hanyou[3],(*it).f_hanyou[4],(*it).f_hanyou[5],(*it).f_hanyou[6],(*it).f_hanyou[7],(*it).img,TRUE);
		}
	}
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()==0){
			int count = Player[i].get_spell_count();
			if(count<30){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,count*8.5);
				DrawSt(160*i,100,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].spell_name);
			}
			else if(count<90){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawSt(160*i,100,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].spell_name);
			}
			else if(count<100){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawSt(160*i,100-3*(count-90),GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].spell_name);
			}
			else if(count<240){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				DrawSt(160*i,70,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].spell_name);
			}
			else if(count<360){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-2.125*(count-240));
				DrawSt(160*i,70,GetColor(200,200,255),GetColor(0,0,0),font_default,Player[i].spell_name);
			}
		}
	}

	return;
}

void SpMove(list<SPELLDATA>::iterator &it){
	if(bTimeStop==true&&(*it).type!=1)	return;
	int c = (*it).count;
	if((*it).type==0){
		if(c==0){
			(*it).i_hanyou[0] = Player[(*it).player].get_direction();
			play_sound(13);
			Player[(*it).player].bMove = false;
		}

		float haba = X_NUM_TO_ZAHYO(4) - X_NUM_TO_ZAHYO(0);
		float length = 600;
		if(c<60){
			haba = 2.0;
			length = 10*c;
		}
		else if(c<90){
			haba = (X_NUM_TO_ZAHYO(4) - X_NUM_TO_ZAHYO(0))/30.0*(c-60)+1;
		}
		else if(c<180){}
		else if(c<240){
			haba = (X_NUM_TO_ZAHYO(4) - X_NUM_TO_ZAHYO(0))/60.0*(240-c)+1;
		}
		else{
			(*it).bDelete = true;
                	Player[(*it).player].bMove = true;
		}
		if((*it).i_hanyou[0]==0){
			(*it).f_hanyou[0] = (*it).x - haba/2.0;
			(*it).f_hanyou[1] = (*it).y - length;
			(*it).f_hanyou[2] = (*it).x + haba/2.0;
			(*it).f_hanyou[3] = (*it).y - length;
			(*it).f_hanyou[4] = (*it).x + haba/2.0;
			(*it).f_hanyou[5] = (*it).y;
			(*it).f_hanyou[6] = (*it).x - haba/2.0;
			(*it).f_hanyou[7] = (*it).y;
		}
		else if((*it).i_hanyou[0]==1){
			(*it).f_hanyou[0] = (*it).x + length;
			(*it).f_hanyou[1] = (*it).y - haba/2.0;
			(*it).f_hanyou[2] = (*it).x + length;
			(*it).f_hanyou[3] = (*it).y + haba/2.0;
			(*it).f_hanyou[4] = (*it).x;
			(*it).f_hanyou[5] = (*it).y + haba/2.0;
			(*it).f_hanyou[6] = (*it).x;
			(*it).f_hanyou[7] = (*it).y - haba/2.0;
		}
		else if((*it).i_hanyou[0]==2){
			(*it).f_hanyou[0] = (*it).x + haba/2.0;
			(*it).f_hanyou[1] = (*it).y + length;
			(*it).f_hanyou[2] = (*it).x - haba/2.0;
			(*it).f_hanyou[3] = (*it).y + length;
			(*it).f_hanyou[4] = (*it).x - haba/2.0;
			(*it).f_hanyou[5] = (*it).y;
			(*it).f_hanyou[6] = (*it).x + haba/2.0;
			(*it).f_hanyou[7] = (*it).y;
		}
		else if((*it).i_hanyou[0]==3){
			(*it).f_hanyou[0] = (*it).x - length;
			(*it).f_hanyou[1] = (*it).y + haba/2.0;
			(*it).f_hanyou[2] = (*it).x - length;
			(*it).f_hanyou[3] = (*it).y - haba/2.0;
			(*it).f_hanyou[4] = (*it).x;
			(*it).f_hanyou[5] = (*it).y - haba/2.0;
			(*it).f_hanyou[6] = (*it).x;
			(*it).f_hanyou[7] = (*it).y + haba/2.0;
		}
		if(c>=90&&c<210){
			haba = X_NUM_TO_ZAHYO(3) - X_NUM_TO_ZAHYO(0);
			for(int i=0;i<PLAYER_NUM;i++){
				if(i!=(*it).player&&Player[i].get_condition()==0){
					float x,y;
					Player[i].get_xy(&x,&y);
					bool out = false;
					if((*it).i_hanyou[0]==0){
						if(y<(*it).y&&(*it).x-haba/2.0<x&&x<(*it).x+haba/2.0)	out = true;
					}
					else if((*it).i_hanyou[0]==1){
						if(x>(*it).x&&(*it).y-haba/2.0<y&&y<(*it).y+haba/2.0)	out = true;
					}
					else if((*it).i_hanyou[0]==2){
						if(y>(*it).y&&(*it).x-haba/2.0<x&&x<(*it).x+haba/2.0)	out = true;
					}
					else if((*it).i_hanyou[0]==3){
						if(x<(*it).x&&(*it).y-haba/2.0<y&&y<(*it).y+haba/2.0)	out = true;
					}
					if(out==true){
						Player[i].change_condition(1);
					}
				}
			}
		}
	}
	else if((*it).type==1){
		if(c>=60&&c<240)	bTimeStop = true;
		if(c==60){
			if(Player[(*it).player].get_condition()==0){
				float x,y;
				Player[(*it).player].get_xy(&x,&y);
				int pattern = 0;
				if(Player[(*it).player].bSpbomb==true)	pattern = 1;
				for(int i=0;i<4;i++){
					Player[(*it).player].bomb_num--;
					BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), (*it).player, Player[(*it).player].get_power(), pattern, i+6);
				}
			}
		}
		if(c==240){
			bTimeStop = false;
			(*it).bDelete = true;
		}
		if(c!=0&&c%60==0)	play_sound(8);
	}
	else if((*it).type==2){
		if(c==0)	play_sound(14);
		if(c<50)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,3*c);
		else if(c>=290&&c<340)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,3*(340-c));
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,GetColor(255,100,100),TRUE);
               	if(c>=50&&c<230){
			if(c%6==0){
				int rand_x,rand_y;
				bool flag = false;
				for(int i=0;i<10;i++){
					rand_x = get_rand(LARGE_X-1);
					rand_y = get_rand(LARGE_Y-1);
					if(Map.field[rand_x][rand_y]==0){
						flag = true;
						break;
					}
				}
				if(flag==true){
					if(Para.time_count<3600)	BMake(rand_x, rand_y, (*it).player, 3, 0, 10);
					else				BMake(rand_x, rand_y, (*it).player, 1, 0, 10);
				}
			}
		}
		if(c==339)	(*it).bDelete = true;
	}
	else if((*it).type==3){
		if(c==0)	play_sound(14);
		if(c<50)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,3*c);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,GetColor(255,100,100),TRUE);
		if(c==60){
			for(list<BOMBDATA>::iterator it=Bomb.begin();it!=Bomb.end();++it){
				if(Para.time_count>3600)	(*it).power = 99;
				else				(*it).power = 9;
				(*it).pattern = 1;
				(*it).bExplosion = true;
			}
			(*it).bDelete = true;
			DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
		}
	}
	(*it).count++;

	return;
}
