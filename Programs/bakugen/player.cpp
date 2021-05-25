#include "player.h"
#include "map.h"
#include "bomb.h"
#include "item.h"
#include "stg.h"
#include "spell.h"

CLASS_PLAYER Player[PLAYER_NUM];

void PLoad();
void PMain();

void PLoad(){
	for(int i=0;i<PLAYER_NUM;i++){
		Player[i].player_num = i;
	}

	return;
}

void PMain(){
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()==0||Player[i].get_condition()==2){
			Player[i].draw();
		}
		else if(Player[i].get_condition()==1){
			if(bTimeStop==false){
				Player[i].death_function();
			}
		}
		else if(Player[i].get_condition()==3){
			if(bTimeStop==false){
				Player[i].reborn_function();
			}
		}
	}

	return;
}

CLASS_PLAYER::CLASS_PLAYER(){
	condition = -1;
	return;
}

void CLASS_PLAYER::control(){
//gage_plus(10000);
	if(bTimeStop==true&&chara!=SAKUYA)	return;
	int check_num = -1;
	/*
	bomb=0;
	spell=0;
	up=0;
	down=0;
	left=0;
	right=0;
	*/
	if(replay_play==true){
		replay_control();
	}
	else if(bMan==true){
		if(control_num==DX_INPUT_PAD1)		check_num = 0;
		else if(control_num==DX_INPUT_PAD2)	check_num = 1;
		else if(control_num==DX_INPUT_PAD3)	check_num = 2;
		else if(control_num==DX_INPUT_PAD4)	check_num = 3;
		else					check_num = -1;
		//check_num = 0;
		if(check_num>=0){
			if(c_pad[check_num][SAVE.Key_Bomb[player_num]]>0)	bomb ++;
			else	bomb = 0;
			if(c_pad[check_num][SAVE.Key_Spell[player_num]]>0)	spell ++;
			else	spell = 0;
			if(c_pad[check_num][PAD_UP]>0)	up ++;
			else	up = 0;
			if(c_pad[check_num][PAD_DOWN]>0)	down ++;
			else	down = 0;
			if(c_pad[check_num][PAD_LEFT]>0)	left ++;
			else	left = 0;
			if(c_pad[check_num][PAD_RIGHT]>0)	right ++;
			else	right = 0;
		}
		else{
			if(c_key[KEY_INPUT_Z]>0)	bomb ++;
			else	bomb = 0;
			if(c_key[KEY_INPUT_X]>0)	spell ++;
			else	spell = 0;
			if(c_key[KEY_INPUT_UP]>0)	up ++;
			else	up = 0;
			if(c_key[KEY_INPUT_DOWN]>0)	down ++;
			else	down = 0;
			if(c_key[KEY_INPUT_LEFT]>0)	left ++;
			else	left = 0;
			if(c_key[KEY_INPUT_RIGHT]>0)	right ++;
			else	right = 0;
		}
	}
	else{
		if(Para.time_count<3600)	AI_Last(&bomb,&spell,&up,&down,&left,&right);
		else				AI(&bomb,&spell,&up,&down,&left,&right);
		/*
			check_num = 0;
			bomb = c_pad[check_num][SAVE.Key_Bomb[player_num]];
			spell = c_pad[check_num][SAVE.Key_Spell[player_num]];
			up = c_pad[check_num][PAD_UP];
			down = c_pad[check_num][PAD_DOWN];
			left = c_pad[check_num][PAD_LEFT];
			right = c_pad[check_num][PAD_RIGHT];
		*/
	}
	if(bMove==false){
		bomb = 0;
		spell = 0;
		up = 0;
		down = 0;
		left = 0;
		right = 0;
	}

	float sq = sqrt(2);	
	if(left>0){
		if(up>0){
			x -= speed / sq;
			y -= speed / sq;
		}
		else if(down>0){
			x -= speed / sq;
			y += speed / sq;
		}
		else{
			x -= speed;
		}
	}
	else if(right>0){
		if(up>0){
			x += speed / sq;
			y -= speed / sq;
		}
		else if(down>0){
			x += speed / sq;
			y += speed / sq;
		}
		else{
			x += speed;
		}
	}
	else if(up>0)	y -= speed;
	else if(down>0)	y += speed;
	else		img_count --;
	img_count++;

	atari_map(bomb,spell,up,down,left,right);
	atari_x[0] = x - 6;	
	atari_x[1] = x + 6;	
	atari_y[0] = y - 0;	
	atari_y[1] = y + 16;
	bx = x;
	by = y;
	
	const int img_per = 5;
	if(up>0)	img_num = 0 + abs(2-(img_count/img_per+1)%4);
	else if(down>0)	img_num = 6 + abs(2-(img_count/img_per+1)%4);
	else if(left>0)	img_num = 9 + abs(2-(img_count/img_per+1)%4);
	else if(right>0)img_num = 3 + abs(2-(img_count/img_per+1)%4);
	
	gage_plus(gage_per);

	if(bomb==1&&bomb_num<bomb_max&&bTimeStop==false){
		if(Map.field[X_ZAHYO_TO_NUM(x)][Y_ZAHYO_TO_NUM(y)]==0){
			play_sound(3);
			if(bSpbomb==true){
			       BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, 1, 1);
			}
			else{
				BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power);		
			}
		}
	}
	if(spell==1&&gage==gage_max){
		play_sound(11);
		gage = 0;
		spell_count = 1;
		if(chara==REIMU){
			for(int i=0;i<3;i++){
				/*int num = i%4;
				for(int a=0;a<4;a++){
					if(num==player_num)	num = (num+1)%4;
					if(Player[num].get_condition()==0)	break;
				}
				bomb_num--;
				BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, 2, num+2);
				*/
				bomb_num--;
				BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, 2, i+2);
			}
		}
		else if(chara==MARISA){
			SpMake(x,y,0,player_num);
		}
		else if(chara==SAKUYA){
			SpMake(x,y,1,player_num);
		}
		else if(chara==REMILIA){
			SpMake(x,y,2,player_num);
		}
		else if(chara==FRANDRE){
			SpMake(x,y,3,player_num);
		}
	}
	
	if(spell_count>0){
		spell_count++;
		if(spell_count==360)	spell_count = 0;
	}
	if(gage_count>0){
		gage_plus(10);
		gage_count--;
		if(bTimeStop==false)	BEfMake(x,y+10,0,0);
	}
	if(muteki_count>0){
		muteki_count--;
	}
	if(hit>0){
		gage_plus(30);
		if(hit_count==10){
			hit--;
			hit_count = 0;
		}
		hit_count++;
	}

	return;
}

void CLASS_PLAYER::miso_control(){
	if(bTimeStop==true&&chara!=SAKUYA)	return;
	int check_num = -1;
	if(replay_play==true){
		replay_control();
	}
	else if(bMan==true){
		if(control_num==DX_INPUT_PAD1)		check_num = 0;
		else if(control_num==DX_INPUT_PAD2)	check_num = 1;
		else if(control_num==DX_INPUT_PAD3)	check_num = 2;
		else if(control_num==DX_INPUT_PAD4)	check_num = 3;
		else					check_num = -1;
		//check_num = 0;
		if(check_num>=0){
			if(c_pad[check_num][SAVE.Key_Bomb[player_num]]>0)	bomb ++;
			else	bomb = 0;
			if(c_pad[check_num][SAVE.Key_Spell[player_num]]>0)	spell ++;
			else	spell = 0;
			if(c_pad[check_num][PAD_UP]>0)	up ++;
			else	up = 0;
			if(c_pad[check_num][PAD_DOWN]>0)	down ++;
			else	down = 0;
			if(c_pad[check_num][PAD_LEFT]>0)	left ++;
			else	left = 0;
			if(c_pad[check_num][PAD_RIGHT]>0)	right ++;
			else	right = 0;
		}
		else{
			if(c_key[KEY_INPUT_Z]>0)	bomb ++;
			else	bomb = 0;
			if(c_key[KEY_INPUT_X]>0)	spell ++;
			else	spell = 0;
			if(c_key[KEY_INPUT_UP]>0)	up ++;
			else	up = 0;
			if(c_key[KEY_INPUT_DOWN]>0)	down ++;
			else	down = 0;
			if(c_key[KEY_INPUT_LEFT]>0)	left ++;
			else	left = 0;
			if(c_key[KEY_INPUT_RIGHT]>0)	right ++;
			else	right = 0;
		}
	}
	else{
		AI_Miso(&bomb,&spell,&up,&down,&left,&right);
	}
	if(bMove==false){
		bomb = 0;
		spell = 0;
		up = 0;
		down = 0;
		left = 0;
		right = 0;
	}

	bx = x;
	by = y;

	if(left>0&&(Y_ZAHYO_TO_NUM(y+15)==0||Y_ZAHYO_TO_NUM(y-15)==LARGE_Y-1)){
		i_hanyou[2] = 2;
		x -= 3.0;
	}
	else if(right>0&&(Y_ZAHYO_TO_NUM(y+15)==0||Y_ZAHYO_TO_NUM(y-15)==LARGE_Y-1)){
		i_hanyou[2] = 1;
		x += 3.0;
	}
	else if(up>0&&(X_ZAHYO_TO_NUM(x+15)==0||X_ZAHYO_TO_NUM(x-15)==LARGE_X-1)){
		i_hanyou[2] = 0;
		y -= 3.0;
	}
	else if(down>0&&(X_ZAHYO_TO_NUM(x+15)==0||X_ZAHYO_TO_NUM(x-15)==LARGE_X-1)){
		i_hanyou[2] = 3;
		y += 3.0;
	}
	if(Y_ZAHYO_TO_NUM(y+15)==0)		y = Y_NUM_TO_ZAHYO(1)-(15+1);
	if(Y_ZAHYO_TO_NUM(y-15)==LARGE_Y-1)	y = Y_NUM_TO_ZAHYO(LARGE_Y-1)+(15+1);
	if(X_ZAHYO_TO_NUM(x+15)==0)		x = X_NUM_TO_ZAHYO(1)-(15+1);
	if(X_ZAHYO_TO_NUM(x-15)==LARGE_X-1)	x = X_NUM_TO_ZAHYO(LARGE_X-1)+(15+1);
	
	if(Y_ZAHYO_TO_NUM(y-15)==LARGE_Y-1)		img_num = 1;
	else if(Y_ZAHYO_TO_NUM(y+15)==0)		img_num = 7;
	else if(X_ZAHYO_TO_NUM(x-15)==LARGE_X-1)	img_num = 10;
	else if(X_ZAHYO_TO_NUM(x+15)==0)		img_num = 4;
	
	if(bomb_num<bomb_max){
		if(bTimeStop==false){
			if(Para.time_count%1==0)	BEfMake(x,y+10,0,41);
		}
	}
	if(bomb==1&&bomb_num==0){
		int to_x[3],to_y[3];
		bool flag = false;
		for(int i=0;i<3;i++){
			to_x[i] = -1;
			to_y[i] = -1;
		}
		if(img_num==10||img_num==4){
			for(int i=X_ZAHYO_TO_NUM(x),a=0;i>=0&&i<=LARGE_X-1&&a<3;){
				if(img_num==10)	i--;
				else if(img_num==4)	i++;
				int check = Map.field[i][Y_ZAHYO_TO_NUM(y)];
				if(check!=-2&&check!=1&&check!=2){
					flag = true;
					to_x[a] = i;
					to_y[a] = Y_ZAHYO_TO_NUM(y);
					a++;
				}
			}
		}
		else if(img_num==7||img_num==1){
			for(int i=Y_ZAHYO_TO_NUM(y),a=0;i>=0&&i<=LARGE_Y-1&&a<3;){
				if(img_num==1)	i--;
				else if(img_num==7)	i++;
				int check = Map.field[X_ZAHYO_TO_NUM(x)][i];
				if(check!=-2&&check!=1&&check!=2){
					flag = true;
					to_x[a] = X_ZAHYO_TO_NUM(x);
					to_y[a] = i;
					a++;
				}
			}
		}
		if(flag==true){
			int num=0;
			for(int i=0;i<3;i++){
				num = i;
				if(to_x[num]>-1&&to_x[num]<=LARGE_X-1&&to_y[num]>-1&&to_y[num]<=LARGE_Y-1){
					if(num==0&&img_num==10&&right>0)	break;
					if(num==0&&img_num==4&&left>0)	break;
					if(num==0&&img_num==1&&down>0)	break;
					if(num==0&&img_num==7&&up>0)	break;
					if(num==1&&img_num==10&&left==0)	break;
					if(num==1&&img_num==4&&right==0)	break;
					if(num==1&&img_num==1&&up==0)	break;
					if(num==1&&img_num==7&&down==0)	break;
					if(num==2&&img_num==10&&left>0)	break;
					if(num==2&&img_num==4&&right>0)	break;
					if(num==2&&img_num==1&&up>0)	break;
					if(num==2&&img_num==7&&down>0)	break;
				}
				else	break;
			}
			if(to_x[num]>-1&&to_x[num]<=LARGE_X-1&&to_y[num]>-1&&to_y[num]<=LARGE_Y-1){
				play_sound(3);
				BMake(to_x[num], to_y[num], player_num, power, 0, 11);
			}
		}
	}
	if(spell_count>0){
		spell_count++;
		if(spell_count==360)	spell_count = 0;
	}
	bool exist_flag = false;
	for(list<BOMBDATA>::iterator it=Bomb.begin();it!=Bomb.end();++it){
		if((*it).type==player_num&&(*it).pattern!=12){
			exist_flag = true;
			break;
		}
	}
	for(list<EXPDATA>::iterator it=Exp.begin();it!=Exp.end();++it){
		if((*it).type==player_num){
			exist_flag = true;
			break;
		}
	}
	if(exist_flag==false){
		bomb_num = 0;
	}

	return;
}

void CLASS_PLAYER::replay_control(){
	if(bMan==true){
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&1)	bomb += 1;
		else	bomb = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&2)	spell += 1;
		else	spell = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&4)	up += 1;
		else	up = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&8)	down += 1;
		else	down = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&16)	left += 1;
		else	left = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&32)	right += 1;
		else	right = 0;
	}
	else{
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&1)	bomb = 1;
		else	bomb = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&2)	spell = 1;
		else	spell = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&4)	up = 1;
		else	up = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&8)	down = 1;
		else	down = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&16)	left = 1;
		else	left = 0;
		if(Replay[replay_play_num].replay_element[replay_count][player_num]&32)	right = 1;
		else	right = 0;
	}
	return;
}

void CLASS_PLAYER::draw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
	if(muteki_count>0){
		if(muteki_count%6<3)	SetDrawBright(255,255,255);
		else			SetDrawBright(30,30,255);
	}
	if(repeat==9)	DrawRotaGraphF(x+shake_x,y+shake_y,large,0,img[img_num],TRUE);
	SetDrawBright(255,255,255);

	return;
}

void CLASS_PLAYER::gage_plus(int value){
	if(gage<gage_max){
		if(gage+value>=gage_max){
			gage = gage_max;
			play_sound(12);
		}
		else{
			gage += value;
		}
	}

	return;
}

void CLASS_PLAYER::atari_map(int bomb,int spell,int up,int down,int left,int right){
	float x1,x2,y1,y2,bx1,bx2,by1,by2;
	bx1 = bx - 5;
	bx2 = bx + 5;
	by1 = by - 2;
	by2 = by + 16;
	if(bKickbomb==true){
		x1 = x - 5;
		x2 = x + 5;
		y1 = y - 2;
		y2 = y + 16;
		for(list<BOMBDATA>::iterator it=Bomb.begin(); it!=Bomb.end(); ++it){
			if((*it).direction>-1)	continue;
			if((X_ZAHYO_TO_NUM(bx1)!=(*it).x||Y_ZAHYO_TO_NUM(by1)!=(*it).y) &&
			   (X_ZAHYO_TO_NUM(bx2)!=(*it).x||Y_ZAHYO_TO_NUM(by1)!=(*it).y) &&
			   (X_ZAHYO_TO_NUM(bx1)!=(*it).x||Y_ZAHYO_TO_NUM(by2)!=(*it).y) &&
			   (X_ZAHYO_TO_NUM(bx2)!=(*it).x||Y_ZAHYO_TO_NUM(by2)!=(*it).y)){
			if((X_ZAHYO_TO_NUM(x1)==(*it).x&&Y_ZAHYO_TO_NUM(y1)==(*it).y) ||
			   (X_ZAHYO_TO_NUM(x2)==(*it).x&&Y_ZAHYO_TO_NUM(y1)==(*it).y) ||
			   (X_ZAHYO_TO_NUM(x1)==(*it).x&&Y_ZAHYO_TO_NUM(y2)==(*it).y) ||
			   (X_ZAHYO_TO_NUM(x2)==(*it).x&&Y_ZAHYO_TO_NUM(y2)==(*it).y)){
			   	play_sound(3);
				if(up>0)	(*it).direction = 0;   
				else if(down>0)	(*it).direction = 1;   
				else if(left>0)	(*it).direction = 2;   
				else if(right>0)(*it).direction = 3;	   
			}
			}
		}
	
	}
	for(int i=0;i<4;i++){
		x1 = x - 5;
		x2 = x + 5;
		y1 = y - 2;
		y2 = y + 16;
		switch(i){
			case 0:	if((Y_ZAHYO_TO_NUM(by1)!=Y_ZAHYO_TO_NUM(y1))&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]!=0 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]!=3 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]!=3)&&up>0){
					y = by;
				}
				break;
			case 1:	if((Y_ZAHYO_TO_NUM(by2)!=Y_ZAHYO_TO_NUM(y2))&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=0 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=3 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=3)&&down>0){
					y = by;
				}
				break;
			case 2:	if((X_ZAHYO_TO_NUM(bx1)!=X_ZAHYO_TO_NUM(x1))&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]!=0 || Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]!=3 || Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=3)&&left>0){
					x = bx;
				}
				break;
			case 3:	if((X_ZAHYO_TO_NUM(bx2)!=X_ZAHYO_TO_NUM(x2))&&(Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]!=0 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]!=3 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=3)&&right>0){
					x = bx;
				}
				break;
		}
	}
	
	return;
}

void CLASS_PLAYER::get_xy(float *sx,float *sy){
	*sx = x;
	*sy = y;	

	return;
}

int CLASS_PLAYER::get_condition(){
	return condition;
}
void CLASS_PLAYER::change_condition(int change){
	if(condition!=change&&muteki_count==0){
		if(change==1&&Para.time_count<=3600){
			play_sound(5);
			change = 4;
		}
		else if(change==1){
			play_sound(5);
		}
		else if(change==3){
			play_sound(15);
		}
		else if(change==0){
			muteki_count = 120;
		}
		condition = change;
	}
	return;
}

int CLASS_PLAYER::get_hit(){
	return hit;
}

int CLASS_PLAYER::get_spell_count(){
	return spell_count;
}

int CLASS_PLAYER::get_muteki_count(){
	return muteki_count;
}

int CLASS_PLAYER::get_direction(){
//上・右・下・左
	int di = img_num/3;
	return di;
}

int CLASS_PLAYER::get_chara(){
	return chara;
}

int CLASS_PLAYER::get_power(){
	return power;
}

void CLASS_PLAYER::power_plus(int plus){
	if(power+plus<9&&power+plus>0)	power += plus;
	else if(power+plus<=0)		power = 1;
	else				power = 9;
	return;
}

void CLASS_PLAYER::bomb_max_plus(int plus){
	if(bomb_max+plus<9)	bomb_max += plus;
	else			bomb_max = 9;
	return;
}

void CLASS_PLAYER::gage_count_plus(int plus){
	gage_count += plus;
	return;
}

void CLASS_PLAYER::hit_plus(int plus){
	if(condition!=0)	return;
	if(hit+plus<99)	hit += plus;
	else		hit = 99;
	hit_count = 0;
	return;
}

void CLASS_PLAYER::death_function(){
	if(death_count==0){
		d_hanyou[0] = x;
		d_hanyou[1] = y;
		bMove = false;
		flash = 0;
		gage_count = 0;
		hit_count = 0;
		if(player_num==0){
			x = (X_NUM_TO_ZAHYO(0)+X_NUM_TO_ZAHYO(1))/2.0;
			y = (Y_NUM_TO_ZAHYO(0)+Y_NUM_TO_ZAHYO(1))/2.0;
		}
		else if(player_num==1){
			x = (X_NUM_TO_ZAHYO(LARGE_X-1)+X_NUM_TO_ZAHYO(LARGE_X))/2.0;
			y = (Y_NUM_TO_ZAHYO(LARGE_Y-1)+Y_NUM_TO_ZAHYO(LARGE_Y))/2.0;
		}
		else if(player_num==2){
			x = (X_NUM_TO_ZAHYO(0)+X_NUM_TO_ZAHYO(1))/2.0;
			y = (Y_NUM_TO_ZAHYO(LARGE_Y-1)+Y_NUM_TO_ZAHYO(LARGE_Y))/2.0;
		}
		else if(player_num==3){
			x = (X_NUM_TO_ZAHYO(LARGE_X-1)+X_NUM_TO_ZAHYO(LARGE_X))/2.0;
			y = (Y_NUM_TO_ZAHYO(0)+Y_NUM_TO_ZAHYO(1))/2.0;
		}
	}
	if(death_count<40){
		for(int i=0;i<10;i++){
			EfMake(d_hanyou[0],d_hanyou[1],0,1+i+player_num*10);
		}
	}
	if(death_count==50){
		if(bSpbomb==true){
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
				IMake(rand_x, rand_y, 6, true);
				Map.field[rand_x][rand_y] = 3;
			}			
		}
		if(bKickbomb==true){
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
				IMake(rand_x, rand_y, 5, true);
				Map.field[rand_x][rand_y] = 3;
			}			
		}
		for(int a=0;a<power-2;a++){
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
				IMake(rand_x, rand_y, 0, true);
				Map.field[rand_x][rand_y] = 3;
			}			
		}
		for(int a=0;a<bomb_max-1;a++){
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
				IMake(rand_x, rand_y, 1, true);
				Map.field[rand_x][rand_y] = 3;
			}			
		}
		bomb_max = 1;
		power = 2;
		gage = 0;
		hit = 0;
		bKickbomb = false;
		bSpbomb = false;
	}
	if(death_count==120){
		change_condition(2);
		bMove = true;
		flash = 255;
		death_count = -1;
		i_hanyou[0] = -1;
		i_hanyou[1] = 0;
	}
	death_count++;

	return;
}

void CLASS_PLAYER::reborn_function(){
	if(reborn_count==0){
		d_hanyou[0] = x;
		d_hanyou[1] = y;
		bMove = false;
		flash = 0;
		x = d_hanyou[2];
		y = d_hanyou[3];
	}
	if(reborn_count<40){
		for(int i=0;i<10;i++){
			EfMake(d_hanyou[0],d_hanyou[1],0,1+i+player_num*10);
		}
	}
	if(reborn_count==120){
		change_condition(0);
		bMove = true;
		flash = 255;
		reborn_count = -1;
	}
	reborn_count++;

	return;
}

void CLASS_PLAYER::make(float sx,float sy,int schara,bool man){
//初期化処理
	x = sx;
	y = sy;
	bx = x;
	by = y;
	chara = schara;
	switch(chara){
		case REIMU:
			speed = 3.0;
			gage_per = 4;
			wsprintf(spell_name , "「夢想封印」");
			break;
		case MARISA:
			speed = 4.5;
			gage_per = 3;
			wsprintf(spell_name , "「マスタースパーク」");
			break;
		case SAKUYA:
			speed = 4.0;
			gage_per = 3;
			wsprintf(spell_name , "「ジャック・ザ・リッパー」");
			break;
		case REMILIA:
			speed = 3.0;
			gage_per = 2;
			wsprintf(spell_name , "「全世界ナイトメア」");
			break;
		case FRANDRE:
			speed = 3.5;
			gage_per = 2;
			wsprintf(spell_name , "「そして誰もいなくなるか？」");
			break;
	}
	speed = 0.5*(speed+1);
	large = 1.4;
	condition = 0;
	bomb_num = 0;
	bomb_max = 1;
	power = 2;
	hit = 0;
	hit_count = 0;
	gage = 0;
	gage_max = 10000;
	gage_count = 0;
	spell_count = 0;
	death_count = 0;
	reborn_count = 0;
	muteki_count = 0;
	flash = 255;
	img_count = 0;
	img_num = 7;
	control_num = SAVE.Key_Type[player_num];//どのパッドで操作するか
	for(int i=0;i<PLAYER_CHIP_NUM;i++){
		img[i] = gPlayer[chara][i];
	}
	for(int i=0;i<2;i++){
		atari_x[i] = sx;
		atari_y[i] = sy;
	}
	for(int i=0;i<8;i++){
		d_hanyou[i] = 0;
		i_hanyou[i] = 0;
	}
	bSpbomb = false;
	bKickbomb = false;
	bMan = man;
	bMove = true;
	bomb = 0;
	spell = 0;
	up = 0;
	down = 0;
	left = 0;
	right = 0;


	return;
}

void CLASS_PLAYER::AI_Record(vector<ZAHYODATA> &Record,int c_num){
	const int search_num = 5;
	vector<ZAHYODATA> Mem;//探索で歩いた道のり
	for(int count=0;count<c_num;count++){
		if(count==1){
			bool fl = false;
			for(int i=0;i<Record.size();i++){
				if(Record.at(i).priority>=0){
					fl = true;
					break;
				}
			}
			if(fl==true)	continue;
		}
		Record.clear();
		Mem.clear();
		int num[10];//要素数:探査深度 値:上下左右
		for(int i=0;i<search_num;i++){
			num[i] = 0;
		}
		ZAHYODATA Now;
		Now.x = X_ZAHYO_TO_NUM(x);
		Now.y = Y_ZAHYO_TO_NUM(y);
		Now.direction = -1;
		Now.num = -1;
		Now.priority = Search(Now.x,Now.y);
		Record.push_back(Now);
		Mem.push_back(Now);
		for(int i=0;;){
			int nowprio = Now.priority;
			if(i==-1)	break;
			if(num[i]==4){
				num[i] = 0;
				if(i>0){
					num[i-1]++;
					Mem.pop_back();
					Now = Mem.back();
				}
				i -= 1;
				continue;
			}
			int *check = NULL;
			if(num[i]==0){
				check = &Map.field[Now.x][Now.y-1];
				if(*check!=1&&*check!=2&&*check!=-2){
					Now.y --;
					if(i==0)	Now.direction = 0;
				}
				else if(bKickbomb==true&&*check==-2){
					int di = Now.direction;
					int pr = Now.priority;
					int nu = Now.num;
					Now.y --;
					if(i==0)	Now.direction = 0;
					Now.priority = Search(Now.x,Now.y);
					Now.num = i;
					Record.push_back(Now);
					Now.y ++;
					Now.direction = di;
					Now.priority = pr;
					Now.num = nu;
				}
			}
			else if(num[i]==1){
				check = &Map.field[Now.x][Now.y+1];
				if(*check!=1&&*check!=2&&*check!=-2){
					Now.y ++;
					if(i==0)	Now.direction = 1;
				}
				else if(bKickbomb==true&&*check==-2){
					int di = Now.direction;
					int pr = Now.priority;
					int nu = Now.num;
					Now.y ++;
					if(i==0)	Now.direction = 0;
					Now.priority = Search(Now.x,Now.y);
					Now.num = i;
					Record.push_back(Now);
					Now.y --;
					Now.direction = di;
					Now.priority = pr;
					Now.num = nu;
				}
			}
			else if(num[i]==2){
				check = &Map.field[Now.x-1][Now.y];
				if(*check!=1&&*check!=2&&*check!=-2){
					Now.x --;
					if(i==0)	Now.direction = 2;
				}
				else if(bKickbomb==true&&*check==-2){
					int di = Now.direction;
					int pr = Now.priority;
					int nu = Now.num;
					Now.x --;
					if(i==0)	Now.direction = 0;
					Now.priority = Search(Now.x,Now.y);
					Now.num = i;
					Record.push_back(Now);
					Now.x ++;
					Now.direction = di;
					Now.priority = pr;
					Now.num = nu;
				}
			}
			else if(num[i]==3){
				check = &Map.field[Now.x+1][Now.y];
				if(*check!=1&&*check!=2&&*check!=-2){
					Now.x ++;
					if(i==0)	Now.direction = 3;
				}
				else if(bKickbomb==true&&*check==-2){
					int di = Now.direction;
					int pr = Now.priority;
					int nu = Now.num;
					Now.x ++;
					if(i==0)	Now.direction = 0;
					Now.priority = Search(Now.x,Now.y);
					Now.num = i;
					Record.push_back(Now);
					Now.x --;
					Now.direction = di;
					Now.priority = pr;
					Now.num = nu;
				}
			}
			bool flag = false;
			for(int i=0;i<Mem.size();i++){
				if(Now.x==Mem.at(i).x&&Now.y==Mem.at(i).y&&Mem.at(i).num<i){
					flag = true;
					break;
				}
			}
			Now.priority = Search(Now.x,Now.y);
			Now.num = i;
			Mem.push_back(Now);
			bool flag2 = false;
			if(count==1||Record.front().priority<0)	flag2 = true;
			if(check!=&Map.field[Now.x][Now.y]||i==search_num-1||(flag2==false&&Now.priority<0)||(flag2==true&&Now.priority<Record.front().priority)||flag==true){
				Mem.pop_back();
				Now = Mem.back();
				num[i]++;
				continue;
			}
			else{
				Record.push_back(Now);
			}
			i++;
		}
	}
	Mem.clear();

	return;
}

void CLASS_PLAYER::AI(int *bomb,int *spell,int *up,int *down,int *left,int *right){
//0.１０歩以内で歩ける場所をサーチする
//1.自分のボム＆カウントが120以上のボムの爆風＆現存する爆風が届かない場所をサーチ
//2.アイテムがある場所をサーチ
//3.ボムを置くと最も多くのブロックを壊せる場所をサーチ
//4.ボムを設置してない場合、ボムを置いても詰まない場所をサーチ
//5.自分のいる場所の優先度が最も高くて、ボムを置いても詰まない場合、ボムを設置
	char message[64];
	const int search_num = 5;	
	vector<ZAHYODATA> Record;//今まで探索したところの記録
	AI_Record(Record);
	int max_priority = -100;
	bool bBomb = false;
	int max_num = search_num;
	int to_direction = 0;
	int to_x,to_y;
	for(int i=0;i<Record.size();i++){
		Record.at(i).bBomb = true;
		if(Record.at(i).priority<0)	Record.at(i).bBomb = false;			
		if(bomb_num<bomb_max){
			int pattern = 0;
			if(bSpbomb==true)	pattern = 1;
			int ch = Map.field[Record.at(i).x][Record.at(i).y];
			BMake(Record.at(i).x,Record.at(i).y,player_num,power,pattern);
			vector<ZAHYODATA> Rec;
			AI_Record(Rec);
			bool flag = false;
			for(int a=0;a<Rec.size();a++){
				if( Search(Rec.at(a).x,Rec.at(a).y) >= 0){
					Record.at(i).priority += 4;
					flag = true;
					break;
				}
			}
			if(flag==false){
				Record.at(i).priority -= 5;
				Record.at(i).bBomb = false;			
			}
			bomb_num--;
			Map.field[Record.at(i).x][Record.at(i).y] = ch;
			Bomb.pop_back();
		}
		/*
		wsprintf(message , "%d",Record.at(i).num);
		DrawSt(X_NUM_TO_ZAHYO(Record.at(i).x),Y_NUM_TO_ZAHYO(Record.at(i).y),GetColor(255,255,255),0,font_default,message);
		wsprintf(message , "%d",Record.at(i).priority);
		DrawSt(X_NUM_TO_ZAHYO(Record.at(i).x),Y_NUM_TO_ZAHYO(Record.at(i).y)+15,GetColor(255,255,255),0,font_default,message);
		*/
		if(max_priority<Record.at(i).priority || (max_priority==Record.at(i).priority&&Record.at(i).num<max_num)){
			to_direction = Record.at(i).direction;
			max_priority = Record.at(i).priority;
			max_num = Record.at(i).num;
			to_x = Record.at(i).x;
			to_y = Record.at(i).y;
			bBomb = Record.at(i).bBomb;
		}
	}
	Record.clear();

	int x1 = X_ZAHYO_TO_NUM(x-7);
	int x2 = X_ZAHYO_TO_NUM(x+7);
	int y1 = Y_ZAHYO_TO_NUM(y-4);
	int y2 = Y_ZAHYO_TO_NUM(y+18);
	if(to_direction==-1){
		if(gage==gage_max&&Search(X_ZAHYO_TO_NUM(x),Y_ZAHYO_TO_NUM(y))>=0/*&&(chara==REIMU||chara==MARISA||chara==SAKUYA||chara==REMILIA)*/){
			*bomb = 0;
			*spell = 1;
		}
		else{
			if(bBomb==true&&i_hanyou[3]==0)		*bomb = 1;
			else					*bomb = 0;
			*spell = 0;
		}
		*up = 0;
		*down = 0;
		*left = 0;
		*right = 0;
	}
	else if(to_direction==0){
		*bomb = 0;
		*spell = 0;
		*up = 1;
		*down = 0;
		if(x2>X_ZAHYO_TO_NUM(x)){
			*left = 1;
			*up = 0;
		}
		else{
			*left = 0;
		}
		if(x1<X_ZAHYO_TO_NUM(x)){
			*right = 1;
			*up = 0;
		}
		else{
			*right = 0;
		}
	}
	else if(to_direction==1){
		*bomb = 0;
		*spell = 0;
		*up = 0;
		*down = 1;
		if(x2>X_ZAHYO_TO_NUM(x)){
			*left = 1;
			*down = 0;
		}
		else{
			*left = 0;
		}
		if(x1<X_ZAHYO_TO_NUM(x)){
			*right = 1;
			*down = 0;
		}
		else{
			*right = 0;
		}
	}
	else if(to_direction==2){
		*bomb = 0;
		*spell = 0;
		*left = 1;
		*right = 0;
		if(y2>Y_ZAHYO_TO_NUM(y)){
			*up = 1;
			*left = 0;
		}
		else{
			*up = 0;
		}
		if(y1<Y_ZAHYO_TO_NUM(y)){
			*down = 1;
			*left = 0;
		}
		else{
			*down = 0;
		}
	}
	else if(to_direction==3){
		*bomb = 0;
		*spell = 0;
		*left = 0;
		*right = 1;
		if(y2>Y_ZAHYO_TO_NUM(y)){
			*up = 1;
			*right = 0;
		}
		else{
			*up = 0;
		}
		if(y1<Y_ZAHYO_TO_NUM(y)){
			*down = 1;
			*right = 0;
		}
		else{
			*down = 0;
		}
	}

	if(level==0&&bomb_num>0)	*bomb = 0;
	if(level==1&&bomb_num>1)	*bomb = 0;
	if(level==2&&bomb_num>4)	*bomb = 0;
	if(level==0&&*spell==1){
		*spell = 0;
		if(bomb_num==0)	*bomb = 1;
	}
	if(level==1&&*spell==1){
		if(bx!=x||by!=y){
			*spell = 0;
			*bomb = 1;
		}
	}

	/*
	wsprintf(message , " ●");
	DrawSt(X_NUM_TO_ZAHYO(to_x),Y_NUM_TO_ZAHYO(to_y)+5,GetColor(255,255,255),0,font_default,message);
	*/
	return;
}

void CLASS_PLAYER::AI_Last(int *bomb,int *spell,int *up,int *down,int *left,int *right){
//弾幕・リリー・もうすぐ爆発する爆弾の爆風に当たるところの優先度は最低
//それ以外の爆風に当たるところの優先度も低め
//詰んでいる場合、４画に分けた場所に応じて移動
//アイテムが近くにあるなら、取りに行く
//安全なら爆弾を設置する
	float ax[9],ay[9],root=sqrt(2.0);
	int priority[9];
	for(int i=0;i<9;i++){
		ax[i] = x;
		ay[i] = y;
		priority[i] = 0;
	}
	ay[1] -= speed;
	ax[2] += speed/root;
	ay[2] -= speed/root;
	ax[3] += speed;
	ax[4] += speed/root;
	ay[4] += speed/root;
	ay[5] += speed;
	ax[6] -= speed/root;
	ay[6] += speed/root;
	ax[7] -= speed;
	ax[8] -= speed/root;
	ay[8] -= speed/root;
	float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
	vector<float> vx;
	vector<float> vy;
	vector<float> vatari;
	vector<int> vvari;//0:敵 1:弾 2:爆弾 3:爆風
	vx.push_back(Enemy.x);
	vy.push_back(Enemy.y);
	vatari.push_back(Enemy.atari);
	vvari.push_back(0);
	for(list<SHOTDATA>::iterator it=Shot.begin();it!=Shot.end();++it){
		float sx = x - (*it).x;
		float sy = y - (*it).y;
		if(sqrt(sx*sx+sy*sy)<speed*5){
			vx.push_back((*it).x);
			vy.push_back((*it).y);
			vatari.push_back((*it).atari);
			vvari.push_back(1);
		}
	}
	for(list<BOMBDATA>::iterator it=Bomb.begin();it!=Bomb.end();++it){
		vx.push_back((*it).fx);
		vy.push_back((*it).fy);
		bool flag = false;
		for(list<SPELLDATA>::iterator sit=Spell.begin();sit!=Spell.end();++sit){
			if((*sit).type==3)	flag = true;
		}
		if(flag==true)	vatari.push_back(sa*9.0+5);
		else		vatari.push_back(sa*(*it).power+5);
		vvari.push_back(2);
	}
	for(list<EXPDATA>::iterator it=Exp.begin();it!=Exp.end();++it){
		vx.push_back(X_NUM_TO_ZAHYO((*it).x)+sa);
		vy.push_back(Y_NUM_TO_ZAHYO((*it).y)+sa);
		vatari.push_back(sa*(*it).power+5);
		vvari.push_back(3);
	}
	bool minus = true;
	for(int i=0;i<9;i++){
		bool flag = true;
		for(int a=0;a<vx.size();a++){
			float sx = ax[i] - vx.at(a);
			float sy = ay[i] - vy.at(a);
			if(sqrt(sx*sx+sy*sy)<vatari.at(a)){
				if(vvari.at(a)==0||vvari.at(a)==1||vvari.at(a)==3){
					priority[i] = -100;
					flag = false;
					break;
				}
				else if(vvari.at(a)==2){
					flag = false;
					priority[i] = -50;
				}
			}
		}
		if(flag==true){
			minus = false;
		}
	}
	if(1/*minus==true*/){//詰んでるとき
		if((x<=640.0-106.6&&y<=60+70)||(x>=(106.6*3)&&x<=(106.6*3)+106.6&&y<=(60+70*3)&&y>=(60+70*3)-70)){
			priority[4] += 10;
		}
		else if((x>=640.0-106.6&&y<=480-70)||(x>=(106.6*3)&&x<=(106.6*3)+106.6&&y<=(60+70*3)+70&&y>=(60+70*3))){
			priority[6] += 10;
		}
		else if((x>=106.6&&y>=480-70)||(x>=(106.6*3)-106.6&&x<=(106.6*3)&&y<=(60+70*3)+70&&y>=(60+70*3))){
			priority[8] += 10;
		}
		else if((x<=106.6&&y>=60+70)||(x>=(106.6*3)-106.6&&x<=(106.6*3)&&y<=(60+70*3)&&y>=(60+70*3)-70)){
			priority[2] += 10;
		}
		else if(x>=106.6&&x<=640.0-106.6*2&&y<=60+70*2&&y>=60+70){
			priority[3] += 10;
		}
		else if(x>=640.0-106.6*2&&x<=640.0-106.6&&y>=60+70&&y<=480-70*2){
			priority[5] += 10;
		}
		else if(x>=106.6*2&&x<=640.0-106.6&&y<=480-70&&y>=480-70*2){
			priority[7] += 10;
		}
		else if(x>=106.6&&x<=106.6*2&&y<=480-70&&y>=60+70*2){
			priority[1] += 10;
		}
	}
	/*
	for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();++it){
		float sx = x - (*it).x;
		float sy = y - (*it).y;
		if(sqrt(sx*sx+sy*sy)<50){
			if(x<(*it).x){
				priority[2] += 10;
				priority[3] += 10;
				priority[4] += 10;
			}
			else{
				priority[6] += 10;
				priority[7] += 10;
				priority[8] += 10;
			}
			if(y<(*it).y){
				priority[1] += 10;
				priority[2] += 10;
				priority[8] += 10;
			}
			else{
				priority[4] += 10;
				priority[5] += 10;
				priority[6] += 10;
			}
			break;
		}
	}
	*/

	bool bombflag = false;
	if(1/*X_ZAHYO_TO_NUM(bx)==X_ZAHYO_TO_NUM(x) && Y_ZAHYO_TO_NUM(by)==Y_ZAHYO_TO_NUM(y)*/){
		bombflag = true;
		float sa = (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
		int px = X_ZAHYO_TO_NUM(x);
		int py = Y_ZAHYO_TO_NUM(y);
		float fpx = X_NUM_TO_ZAHYO(px) + sa;
		float fpy = Y_NUM_TO_ZAHYO(py) + sa;
		for(list<BOMBDATA>::iterator it=Bomb.begin();it!=Bomb.end();++it){
			float sx = fpx - (*it).fx;
			float sy = fpy - (*it).fy;
			bool flag = false;
			for(list<SPELLDATA>::iterator sit=Spell.begin();sit!=Spell.end();++sit){
				if((*sit).type==3)	flag = true;
			}
			if(flag==true)	bombflag = false;
			if((sqrt(sx*sx+sy*sy)<sa*(*it).power)||(flag==true&&sqrt(sx*sx+sy*sy)<sa*9.0)){
				bombflag = false;
				if((*it).x==px&&(*it).y==py){
					for(int a=0;a<8;a++){
						priority[a+1] += 15;
					}
				}
				if((*it).x<px){
					for(int a=0;a<9;a++){
						if(a!=6&&a!=7&&a!=8)	priority[a] += 15;
					}
					priority[2] += 5;
					priority[3] += 5;
					priority[4] += 5;
				}
				if((*it).y<py){
					for(int a=0;a<9;a++){
						if(a!=1&&a!=2&&a!=8)	priority[a] += 15;
					}
					priority[4] += 5;
					priority[5] += 5;
					priority[6] += 5;
				}
				if((*it).x>px){
					for(int a=0;a<9;a++){
						if(a!=2&&a!=3&&a!=4)	priority[a] += 15;
					}
					priority[6] += 5;
					priority[7] += 5;
					priority[8] += 5;
				}
				if((*it).y>py){
					for(int a=0;a<9;a++){
						if(a!=4&&a!=5&&a!=6)	priority[a] += 15;
					}
					priority[1] += 5;
					priority[2] += 5;
					priority[8] += 5;
				}
			}
		}
		for(list<EXPDATA>::iterator it=Exp.begin();it!=Exp.end();++it){
			float sx = fpx - (X_NUM_TO_ZAHYO((*it).x)+sa);
			float sy = fpy - (Y_NUM_TO_ZAHYO((*it).y)+sa);
			if(sqrt(sx*sx+sy*sy)<sa*(*it).power){
				bombflag = false;
				break;
			}
		}
	}
	if(1){
		bool flag = false;
		for(list<SPELLDATA>::iterator sit=Spell.begin();sit!=Spell.end();++sit){
			if((*sit).type==3)	flag = true;
		}
		if(flag==true||bomb_num==2)	bombflag = false;
	}
	int max_priority = -1000;
	int num = 0;
	for(int i=0;i<9;i++){
		if(max_priority<priority[i]){
			max_priority = priority[i];
			num = i;
		}
	}

	if(num==0){
		*bomb = 0;
		*spell = 0;
		if(max_priority>=0){
			if(gage==gage_max&&chara!=MARISA)	*spell = 1;
			else{
				if(bombflag==true)	*bomb = 1;
			}
		}
		*up = 0;
		*down = 0;
		*left = 0;
		*right = 0;
	}
	else{
		*bomb = 0;
		*spell = 0;
		if(max_priority>=0){
			if(gage==gage_max&&chara!=MARISA)	*spell = 1;
			else{
				if(bombflag==true)	*bomb = 1;
			}
		}
		if(num==8||num==1||num==2)	*up = 1;
		else				*up = 0;
		if(num==4||num==5||num==6)	*down = 1;
		else				*down = 0;
		if(num==6||num==7||num==8)	*left = 1;
		else				*left = 0;
		if(num==2||num==3||num==4)	*right = 1;
		else				*right = 0;
	}

	if(level==0)	*bomb = 0;
	if(level==1&&bomb_num>1)	*bomb = 0;
	if(level==0&&*spell==1){
		*spell = 0;
	}
	if(level==1&&*spell==1){
		if(bx!=x||by!=y){
			*spell = 0;
			*bomb = 1;
		}
	}

	return;
}

void CLASS_PLAYER::AI_Miso(int *bomb,int *spell,int *up,int *down,int *left,int *right){
//0.敵とx座標かy座標を合わせに行く。最初に捕まった人(i_hanyou[0])にサーチを固定する
//1.置ける3箇所に爆風が届いているかサーチ
//2.置ける3箇所にボムをおいた場合、詰むキャラがいるかサーチ
	*bomb = 0;
	*spell = 0;
	*up = 0;
	*down = 0;
	*left =0;
	*right = 0;
	if(i_hanyou[0]>=0){
		float px,py;
		Player[i_hanyou[0]].get_xy(&px,&py);
		if(X_ZAHYO_TO_NUM(px)<X_ZAHYO_TO_NUM(x))	*left = 1;
		else if(X_ZAHYO_TO_NUM(px)>X_ZAHYO_TO_NUM(x))	*right = 1;
		else{
			int to_x[3],to_y[3];
			for(int i=0;i<3;i++){
				to_x[i] = -1;
				to_y[i] = -1;
			}
			if(img_num==10||img_num==4){
				for(int i=X_ZAHYO_TO_NUM(x),a=0;i>=0&&i<=LARGE_X-1&&a<3;){
					if(img_num==10)	i--;
					else if(img_num==4)	i++;
					int check = Map.field[i][Y_ZAHYO_TO_NUM(y)];
					if(check!=-2&&check!=1&&check!=2){
						to_x[a] = i;
						to_y[a] = Y_ZAHYO_TO_NUM(y);
						a++;
					}
				}
			}
			if(img_num==7||img_num==1){
				for(int i=Y_ZAHYO_TO_NUM(y),a=0;i>=0&&i<=LARGE_Y-1&&a<3;){
					if(img_num==1)	i--;
					else if(img_num==7)	i++;
					int check = Map.field[X_ZAHYO_TO_NUM(x)][i];
					if(check!=-2&&check!=1&&check!=2){
						to_x[a] = X_ZAHYO_TO_NUM(x);
						to_y[a] = i;
						a++;
					}
				}
			}
			int num=0;
			for(int i=0;i<3;i++){
				num = i;
				if(to_x[num]>-1&&to_x[num]<=LARGE_X-1&&to_y[num]>-1&&to_y[num]<=LARGE_Y-1){
					bool ok = false;
					for(list<EXPDATA>::iterator it=Exp.begin();it!=Exp.end();++it){
						int ppx = to_x[num];
						int ppy = to_y[num];
						int x0 = (*it).x - (*it).x_length[0];
						int x1 = (*it).x + (*it).x_length[1];
						int y0 = (*it).y - (*it).y_length[0];
						int y1 = (*it).y + (*it).y_length[1];
						if((x0<=ppx&&ppx<=x1&&ppy==(*it).y) || (y0<=ppy&&ppy<=y1&&ppx==(*it).x)){
							ok = true;
							break;
						}
					}
					/*
					for(int a=0;a<PLAYER_NUM;a++){
						if(a!=player_num&&Player[a].get_condition()==0){
							int ch = Map.field[to_x[num]][to_y[num]];
							float px,py;
							Player[a].get_xy(&px,&py);
							BMake(to_x[num],to_y[num],player_num,power,0);
							int value = Player[a].Search(X_ZAHYO_TO_NUM(px),Y_ZAHYO_TO_NUM(py));
							bomb_num--;
							Map.field[to_x[num]][to_y[num]] = ch;
							Bomb.pop_back();
							if(value<0){
								ok = true;
								break;
							}
						}
					}
					*/
					if(ok==true){
						if(num==0){
							if(img_num==10)	*right = 1;
							if(img_num==4)	*left = 1;
							if(img_num==1)	*down = 1;
							if(img_num==7)	*up = 1;
						}
						if(num==2){
							if(img_num==10)	*left = 1;
							if(img_num==4)	*right = 1;
							if(img_num==1)	*up = 1;
							if(img_num==7)	*down = 1;
						}
						*bomb = 1;
						break;
					}
				}
				else	break;
			}			
		}
	}
	else{
		if(fabs(bx-x)<0.01){
			i_hanyou[1] = (i_hanyou[1]+1)%2;
		}
		if(i_hanyou[1]==0)	*left = 1;
		else			*right = 1;
		for(int i=0;i<PLAYER_NUM;i++){
			if(i!=player_num&&Player[i].get_condition()==0){
				float px,py;
				Player[i].get_xy(&px,&py);
				if(X_ZAHYO_TO_NUM(x)==X_ZAHYO_TO_NUM(px)){
					i_hanyou[0] = i;
					break;
				}
			}
		}
	}
	if(level<=1)	*bomb = 1;	
	return;
}

int CLASS_PLAYER::Search(int sx,int sy){
	int value=0;
	for(list<ITEMDATA>::iterator it=Item.begin();it!=Item.end();++it){
        	if((*it).bExist==true){
			if(sx==(*it).x&&sy==(*it).y){
				if((power<9&&((*it).type==0||(*it).type==3)) || (bomb_max<9&&(*it).type==1) || (bSpbomb==false&&(*it).type==6) || (bKickbomb==false&&(*it).type==5) || (*it).type==2){
					value += 5;
					break;
				}
			}
		}
	}
	int dummy[4],pattern=0;
	if(bSpbomb==true)	pattern = 1;	
	value += ELength(sx,sy,power,pattern,&dummy[0],&dummy[1],&dummy[2],&dummy[3],false);
	i_hanyou[3] = 0;
	for(list<BOMBDATA>::iterator it=Bomb.begin();it!=Bomb.end();++it){
		int x_length[2]={0,},y_length[2]={0,};
		int power = (*it).power;
		int pattern = (*it).pattern;
		for(list<SPELLDATA>::iterator sit=Spell.begin();sit!=Spell.end();++sit){
			if((*sit).type==3){
				if(Para.time_count>3600)	power = 99;
				else				power = 9;
				pattern = 1;
				i_hanyou[3] = 1;
				break;
			}
		}
		ELength((*it).x,(*it).y,power,pattern,&x_length[0],&x_length[1],&y_length[0],&y_length[1],false);
		int x0 = (*it).x - x_length[0];
		int x1 = (*it).x + x_length[1];
		int y0 = (*it).y - y_length[0];
		int y1 = (*it).y + y_length[1];
		if((x0<=sx&&sx<=x1&&sy==(*it).y) || (y0<=sy&&sy<=y1&&sx==(*it).x)){
			if(power==99||(*it).pattern==10||(*it).pattern==12){
				value = -20;
			}
			else if((sx!=(*it).x||sy!=(*it).y)&&bKickbomb==true&&(*it).count<100&&sx==(*it).x&&sy==(*it).y){
				value = 0;
			}
			else if((*it).count<100){
				value = -10;
			}
			else{
				value = -20;
			}
			break;
        	}
	}
	for(list<EXPDATA>::iterator it=Exp.begin();it!=Exp.end();++it){
		int x0 = (*it).x - (*it).x_length[0];
		int x1 = (*it).x + (*it).x_length[1];
		int y0 = (*it).y - (*it).y_length[0];
		int y1 = (*it).y + (*it).y_length[1];
		if((*it).count<45&&(x0<=sx&&sx<=x1&&sy==(*it).y) || (y0<=sy&&sy<=y1&&sx==(*it).x)){
			value = -30;
			break;
		}
	}
	for(list<SPELLDATA>::iterator it=Spell.begin();it!=Spell.end();++it){
		if((*it).type==0&&(*it).count<210){
			float haba = X_NUM_TO_ZAHYO(3) - X_NUM_TO_ZAHYO(0);
			float ssx = X_NUM_TO_ZAHYO(sx)+(X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0;
			float ssy = Y_NUM_TO_ZAHYO(sy)+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0;
			bool out = false;
			if((*it).i_hanyou[0]==0){
				if(ssy<(*it).y&&(*it).x-haba/2.0<ssx&&ssx<(*it).x+haba/2.0)	out = true;
			}
			else if((*it).i_hanyou[0]==1){
				if(ssx>(*it).x&&(*it).y-haba/2.0<ssy&&ssy<(*it).y+haba/2.0)	out = true;
			}
			else if((*it).i_hanyou[0]==2){
				if(ssy>(*it).y&&(*it).x-haba/2.0<ssx&&ssx<(*it).x+haba/2.0)	out = true;
			}
			else if((*it).i_hanyou[0]==3){
				if(ssx<(*it).x&&(*it).y-haba/2.0<ssy&&ssy<(*it).y+haba/2.0)	out = true;
			}
			if(out==true){
				value = -30;
				//DrawSt(X_NUM_TO_ZAHYO(sx),Y_NUM_TO_ZAHYO(sy),GetColor(255,255,255),0,font_default," !!");
				break;
			}
		}
	}

	return value;
}

void CLASS_PLAYER::replay_main(){
//ボタン押下状況の保存
	unsigned char REPLAY = 0;
	if(bomb>0)	REPLAY += 1;
	if(spell>0)	REPLAY += 2;
	if(up>0)	REPLAY += 4;
	if(down>0)	REPLAY += 8;
	if(left>0)	REPLAY += 16;
	if(right>0)	REPLAY += 32;
	SReplay.replay_element[replay_count][player_num] = REPLAY;
	
	return;
}
