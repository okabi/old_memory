#include "player.h"
#include "map.h"
#include "bomb.h"
#include "item.h"
#include "stg.h"
#include "spell.h"
#include "menu.h"
#include "net.h"

CLASS_PLAYER Player[PLAYER_NUM];
CLASS_PLAYER Illusion[ILLUSION_NUM];


void PLoad();
void PMain();

void PLoad(){
	for(int i=0;i<PLAYER_NUM;i++){
		Player[i].player_num = i;
		Player[i].bIllusion = false;
	}
	for(int i=0;i<ILLUSION_NUM;i++){
		Illusion[i].player_num = -1;
		Illusion[i].level = 3;
		Illusion[i].bIllusion = true;
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
	for(int i=0;i<ILLUSION_NUM;i++){
		if(Illusion[i].player_num>=0){
			Illusion[i].draw();
			if(Para.start_count==0)	Illusion[i].control();
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
	if(bTimeStop==true&&chara!=SAKUYA&&bTime==false)	return;
	if(bTimeStop==false){
		bRudo = false;
	}
	if(bIllusion==true&&player_num>=0){
		flash = Player[player_num].illusion_flash;
	}
	int check_num = -1;
	/*
	bomb=0;
	spell=0;
	up=0;
	down=0;
	left=0;
	right=0;
	*/
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
	if(replay_play==true&&bIllusion==false){
		replay_control();
	}
	else if(bMan==true){
		if(bOnline==true){
			if(NetWork.NGD.input[player_num]&1)	bomb ++;
			else			bomb = 0;
			if(NetWork.NGD.input[player_num]&2)	spell ++;
			else			spell = 0;
			if(NetWork.NGD.input[player_num]&8)	up ++;
			else			up = 0;
			if(NetWork.NGD.input[player_num]&16)	down ++;
			else			down = 0;
			if(NetWork.NGD.input[player_num]&32)	left ++;
			else			left = 0;
			if(NetWork.NGD.input[player_num]&64)	right ++;
			else			right = 0;
		}
		else{
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
	}
	else{
		if(AI_count%1==0){ 
			if(Para.time_count<3600)	AI_Last(&bomb,&spell,&up,&down,&left,&right);
			else				AI(&bomb,&spell,&up,&down,&left,&right);
		}
		else{
			bomb = 0;
			spell = 0;
		}
		AI_count++;
		/*
		ai_x = x;
		ai_y = y;
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
	float sp = speed;
	int mx = bomb_max;
	int po = power;
	if(bIllusion==true){
		sp = 7.5;
		mx = 15;
		po = 4;
	}
	int le = spell_level;
	bool flag_hanten = false;
	bool flag_item = false;
	if(Hanten>=0&&player_num!=Hanten)	flag_hanten = true;
	if(dokuro_count>0){
		if(dokuro&1)	sp = 7.5;
		if(dokuro&2)	sp = 1.0;
		if(dokuro&4)	bomb_max = 0;
		if(dokuro&8)	bomb = 1;
		if(dokuro&16)	power = 1;
		if(dokuro&32){
			if(gage_count==0) gage_count = 1;
		}
		if(dokuro&64)	gage = 0;
		if(dokuro&128)	spell_level = 3;
		if(dokuro&256){
			flag_hanten = true;
		}
		if(dokuro&512){
			flag_item = true;
		}
		if(dokuro&1024){
			if(dokuro_death_count==0){
				dokuro_death_count = 540;
			}
			if(dokuro_death_count%60==0){
				if(dokuro_death_count<=180)	play_sound(8);
				else				play_sound(7);
			}
			dokuro_death_count--;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawRotaGraphF(x,y,1.4,0,gNumber[dokuro_death_count/60+1],TRUE,FALSE);
			if(dokuro_death_count==0){
				if(Para.time_count<3600)	EMake(X_ZAHYO_TO_NUM(x),Y_ZAHYO_TO_NUM(y),player_num,50,1,-1);
				else{
					for(int i=0;i<9;i++){
						int num = X_ZAHYO_TO_NUM(x)-4+i;
						if(0<num&&num<LARGE_X&&Map.field[num][Y_ZAHYO_TO_NUM(y)]!=1)	EMake(num,Y_ZAHYO_TO_NUM(y),player_num,4,-1,player_num);//タテだけ
					}
					for(int i=0;i<9;i++){
						int num = Y_ZAHYO_TO_NUM(y)-4+i;
						if(0<num&&num<LARGE_Y&&Map.field[X_ZAHYO_TO_NUM(x)][num]!=1)	EMake(X_ZAHYO_TO_NUM(x),num,player_num,4,-2,player_num);//ヨコだけ
					}
				}
				change_condition(1,-1);
			}
		}
		else	dokuro_death_count = 0;
	}
	else	dokuro_death_count = 0;
	if(flag_hanten==true){
		int uu = up;
		up = down;
		down = uu;
		int ll = left;
		left = right;
		right = ll;
	}	
	if(left>0){
		if(up>0){
			x -= sp / sq;
			y -= sp / sq;
		}
		else if(down>0){
			x -= sp / sq;
			y += sp / sq;
		}
		else{
			x -= sp;
		}
	}
	else if(right>0){
		if(up>0){
			x += sp / sq;
			y -= sp / sq;
		}
		else if(down>0){
			x += sp / sq;
			y += sp / sq;
		}
		else{
			x += sp;
		}
	}
	else if(up>0)	y -= sp;
	else if(down>0)	y += sp;
	else		img_count --;
	img_count++;

	atari_map(bomb,spell,up,down,left,right);
	atari_x[0] = x - 6;	
	atari_x[1] = x + 6;	
	atari_y[0] = y - 0;	
	atari_y[1] = y + 16;
	if(flag_item==true){
		int nx = X_ZAHYO_TO_NUM(x);
		int ny = Y_ZAHYO_TO_NUM(y);
		int nbx = X_ZAHYO_TO_NUM(bx);
		int nby = Y_ZAHYO_TO_NUM(by);
		if(nx!=nbx||ny!=nby){
			for(int i=0;i<50;i++){
				int rand = get_rand(4);
				if(rand==0){
					if(bomb_max>1){
						IMake(nbx, nby, 1, true);
						Map.field[nbx][nby] = 3;
						bomb_max--;
						mx--;
						break;
					}
				}
				else if(rand==1){
					if(power>1){
						IMake(nbx, nby, 0, true);
						Map.field[nbx][nby] = 3;
						power--;
						po--;
						break;
					}
				}
				else if(rand==2){
					if(bKickbomb==true){
						IMake(nbx, nby, 5, true);
						Map.field[nbx][nby] = 3;
						bKickbomb = false;
						break;
					}
				}
				else if(rand==3){
					if(bSpbomb==true){
						IMake(nbx, nby, 6, true);
						Map.field[nbx][nby] = 3;
						bSpbomb = false;
						break;
					}
				}
			}
		}
	}
	for(int i=0;i<4;i++){
		if(bIllusion==true)	break;
		if(i!=player_num&&Player[i].get_condition()==0){
			float px,py;
			Player[i].get_xy(&px,&py);
			float sx = fabs(x - px); 
			float sy = fabs(y - py);
			float dx = 20 * large;
			float dy = 28 * large;
			if(sx<dx && sy<dy){
				if(bAtariPlayer[i]==false && Player[i].bAtariPlayer[player_num]==false){
					bAtariPlayer[i] = true;
					Player[i].bAtariPlayer[player_num] = true;
					if(dokuro!=0 || Player[i].dokuro!=0){
						play_sound(19);
						int dd = Player[i].dokuro;
						Player[i].dokuro = dokuro;
						dokuro = dd;
						int cc = Player[i].dokuro_count;
						Player[i].dokuro_count = dokuro_count;
						dokuro_count = cc;
					}
				}
				else{
					bAtariPlayer[i] = true;
					Player[i].bAtariPlayer[player_num] = true;
				}
			}
			else{
				bAtariPlayer[i] = false;
				Player[i].bAtariPlayer[player_num] = false;
			}
		}
	}
	bx = x;
	by = y;
	
	const int img_per = 5;
	if(up>0)	img_num = 0 + abs(2-(img_count/img_per+1)%4);
	else if(down>0)	img_num = 6 + abs(2-(img_count/img_per+1)%4);
	else if(left>0)	img_num = 9 + abs(2-(img_count/img_per+1)%4);
	else if(right>0)img_num = 3 + abs(2-(img_count/img_per+1)%4);
	
	gage_plus(gage_per);

	if(bomb==1&&bomb_num<bomb_max&&(bTimeStop==false||TimeStopType==2)){
		if(Map.field[X_ZAHYO_TO_NUM(x)][Y_ZAHYO_TO_NUM(y)]==0){
			play_sound(3);
			if(bSpbomb==true){
				if(bIllusion==false)	BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, 1, 1);
				else			BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, 1, 22+player_num);
			}
			else{
				if(bIllusion==false)	BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power);		
				else			BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, 0, 22+player_num);
			}
		}
	}
	else if(bomb==1&&bTimeStop==true&&TimeStopType==1&&bRudo==false){
		if(Map.field[X_ZAHYO_TO_NUM(x)][Y_ZAHYO_TO_NUM(y)]==0){
			play_sound(3);
			bRudo = true;
			int pattern = 0;
			if(bSpbomb==true)	pattern = 1;
			for(int i=0;i<4;i++){
				bomb_num--;
				if(bIllusion==false)	BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, pattern, i+6);
				else			BMake(X_ZAHYO_TO_NUM(x), Y_ZAHYO_TO_NUM(y), player_num, power, pattern, 22+player_num);
			}
		}
	}
	if(bIllusion==false&&spell==1&&gage==gage_max){
		bool sflag = true;
		if(chara==REIMU){
			SpMake(x,y,3+spell_level,player_num,spell_level);
		}
		else if(chara==MARISA){
			if(spell_level==1)	SpMake(x,y,0,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,7,player_num,spell_level);
			if(spell_level==3){
				SpMake(x,y,0,player_num,spell_level);
				SpMake(x,y,8,player_num,spell_level);
				SpMake(x,y,9,player_num,spell_level);
			}
		}
		else if(chara==SAKUYA){
			if(spell_level==1)	SpMake(x,y,1,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,10,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,11,player_num,spell_level);
		}
		else if(chara==REMILIA){
			if(spell_level==1)	SpMake(x,y,2,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,12,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,13,player_num,spell_level);
		}
		else if(chara==FRANDRE){
			if(spell_level==1)	SpMake(x,y,3,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,14,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,15,player_num,spell_level);
		}
		else if(chara==YOUMU){
			if(spell_level==1)	SpMake(x,y,16,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,17,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,18,player_num,spell_level);
		}
		else if(chara==YUYUKO){
			if(spell_level==1){
				if(bBouga==false)	SpMake(x,y,19,player_num,spell_level);
				else			sflag = false;
			}
			if(spell_level==2){
				if(bSumizome==false)	SpMake(x,y,20,player_num,spell_level);
				else			sflag = false;
			}
			if(spell_level==3){
				if(Para.time_count<3600&&HangonType==-1){
					SpMake(x,y,21,player_num,spell_level);
					HangonType = player_num;
				}
				else			sflag = false;
			}
		}
		else if(chara==YUKARI){
			if(spell_level==1)	SpMake(x,y,22,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,23,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,24,player_num,spell_level);
		}
		else if(chara==REISEN){
			if(spell_level==1)	SpMake(x,y,25,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,26,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,27,player_num,spell_level);
		}
		else if(chara==NITORI){
			if(spell_level==1)	SpMake(x,y,30,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,28,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,29,player_num,spell_level);
		}
		else if(chara==SANAE){
			if(spell_level==1)	SpMake(x,y,31,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,32,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,33,player_num,spell_level);
		}
		else if(chara==UTUHO){
			if(spell_level==1)	SpMake(x,y,34,player_num,spell_level);
			if(spell_level==2)	SpMake(x,y,35,player_num,spell_level);
			if(spell_level==3)	SpMake(x,y,36,player_num,spell_level);
		}
		if(sflag==true){
			play_sound(11);
			gage = 0;
			spell_count = 1;
			draw_level = spell_level-1;
		}
	}
	
	if(spell_count>0){
		spell_count++;
		if(spell_count==360)	spell_count = 0;
	}
	if(gage_count>0){
		gage_plus(12);
		gage_count--;
		if(bTimeStop==false)	BEfMake(x,y+10,0,0);
	}
	if(muteki_count>0){
		muteki_count--;
	}
	if(dokuro_count>0){
		dokuro_count++;
	}
	if(hit>0){
		if(usernum>=2){
			if(bMan==true&&SAVE.User[player_num]!=-1&&!(bOnline==true&&player_num!=NetWork.NFD[0].player_num)){
				if(hit>Profile[SAVE.User[player_num]].max_renbaku)	Profile[SAVE.User[player_num]].max_renbaku = hit;
			}
		}
		gage_plus(30);
		if(hit_count==10){
			hit--;
			hit_count = 0;
		}
		hit_count++;
	}
	bomb_max = mx;
	power = po;
	spell_level = le;

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

void CLASS_PLAYER::hangon_control(){
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
		/*
		if(Para.time_count<3600)	AI_Last(&bomb,&spell,&up,&down,&left,&right);
		else				AI(&bomb,&spell,&up,&down,&left,&right);
		ai_x = x;
		ai_y = y;
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
	float sp = 0.4;
	if(left>0){
		if(up>0){
			x -= sp / sq;
			y -= sp / sq;
		}
		else if(down>0){
			x -= sp / sq;
			y += sp / sq;
		}
		else{
			x -= sp;
		}
	}
	else if(right>0){
		if(up>0){
			x += sp / sq;
			y -= sp / sq;
		}
		else if(down>0){
			x += sp / sq;
			y += sp / sq;
		}
		else{
			x += sp;
		}
	}
	else if(up>0)	y -= sp;
	else if(down>0)	y += sp;
	else		img_count --;
	img_count++;

	atari_map(bomb,spell,up,down,left,right);
	atari_x[0] = x - 6;	
	atari_x[1] = x + 6;	
	atari_y[0] = y - 0;	
	atari_y[1] = y + 16;
	bx = x;
	by = y;
	
	img_num = 7;

	if(spell_count>0){
		spell_count++;
		if(spell_count==360)	spell_count = 0;
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
	if(muteki_count>0){
		if(muteki_count%6<3)	SetDrawBright(255,255,255);
		else			SetDrawBright(30,30,255);
	}
	if(dokuro_count>0){
		if(dokuro_count%12<6)	SetDrawBright(255,255,255);
		else			SetDrawBright(0,0,0);
	}
	if(repeat==9){
		if(bIllusion==false&&flash<255){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,50);
			DrawOval(x, y+(Y_NUM_TO_ZAHYO(1)-Y_NUM_TO_ZAHYO(0))/2.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-5.0, (X_NUM_TO_ZAHYO(1)-X_NUM_TO_ZAHYO(0))/2.0-12.0, GetColor(0,0,0),TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
		DrawRotaGraphF(x+shake_x,y+shake_y,large,0,img[img_num],TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
	SetDrawBright(255,255,255);
	if(HangonType==player_num&&bIllusion==false){
		for(list<SPELLDATA>::iterator it=Spell.begin(); it!=Spell.end(); ++it){
			if((*it).type==21){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
				if(repeat==9){
					float x,y;
					Player[(*it).player].get_xy(&x,&y);
					DrawBox(x-100, y+30, x+100, y+40, GetColor(50,0,0),TRUE);
					int p = 200.0*((float)HangonLife/(float)(*it).i_hanyou[0]);
					int blue = 2.55*(p-100);
					if(blue<0)	blue = 0;
					int color = GetColor(255-p,100,blue);
					DrawBox(x-100, y+30, x-100+p, y+40, color,TRUE);
				}
			}
		}
        }
	
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
					if(bBouga==true&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]==2||Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]==2)){
						break;
					}
					if(bSumizome==true&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]==-2||Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]==-2)){
						break;
					}
					y = by;
				}
				break;
			case 1:	if((Y_ZAHYO_TO_NUM(by2)!=Y_ZAHYO_TO_NUM(y2))&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=0 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=3 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=3)&&down>0){
					if(bBouga==true&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]==2 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]==2)){
						break;
					}
					if(bSumizome==true&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]==-2 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]==-2)){
						break;
					}
					y = by;
				}
				break;
			case 2:	if((X_ZAHYO_TO_NUM(bx1)!=X_ZAHYO_TO_NUM(x1))&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]!=0 || Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]!=3 || Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]!=3)&&left>0){
					if(bBouga==true&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]==2 || Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]==2)){
						break;
					}
					if(bSumizome==true&&(Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y1)]==-2 || Map.field[X_ZAHYO_TO_NUM(x1)][Y_ZAHYO_TO_NUM(y2)]==-2)){
						break;
					}
					x = bx;
				}
				break;
			case 3:	if((X_ZAHYO_TO_NUM(bx2)!=X_ZAHYO_TO_NUM(x2))&&(Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]!=0 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=0)&&(Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]!=3 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]!=3)&&right>0){
					if(bBouga==true&&(Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]==2 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]==2)){
						break;
					}
					if(bSumizome==true&&(Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y1)]==-2 || Map.field[X_ZAHYO_TO_NUM(x2)][Y_ZAHYO_TO_NUM(y2)]==-2)){
						break;
					}
					x = bx;
				}
				break;
		}
	}
	if(Map.field[X_ZAHYO_TO_NUM(x)][Y_ZAHYO_TO_NUM(y)]==1){
		x = bx;
		y = by;
	}
	
	return;
}

void CLASS_PLAYER::set_xy(float sx,float sy){
	if(condition!=0)	return;
	x = sx;
	y = sy;	
	bx = sx;
	by = sy;

	return;
}

void CLASS_PLAYER::get_xy(float *sx,float *sy){
	*sx = x;
	*sy = y;	

	return;
}

void CLASS_PLAYER::get_key(int *sbomb,int *sspell){
	*sbomb = bomb;
	*sspell = spell;	

	return;
}

int CLASS_PLAYER::get_condition(){
	return condition;
}
void CLASS_PLAYER::change_condition(int change,int sflag){
	if(change==-1){
		condition = -1;
		return;
	}
	if(HangonType==player_num){
		if(bMove==true){
			HangonLife -= sflag;
		}
		if(HangonLife>0)	return;
	}
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
	if(condition!=change&&muteki_count==0&&sflag!=-1){
		if(change==1&&bCamo==true&&sflag!=-1){
			bCamo = false;
			muteki_count = 120;
			play_sound(20);
			return;
		}
		else if(change==1&&Para.time_count<=3600){
			play_sound(5);
			change = 4;
			if(usernum>=2&&bMan==true&&SAVE.User[player_num]!=-1&&!(bOnline==true&&player_num!=NetWork.NFD[0].player_num)){
				if(bFirstDeath==true){
					int start_time = (90+SAVE.MatchTime*30)*60;
					int time = (start_time - Para.time_count)/60;
					int sum = Profile[SAVE.User[player_num]].death_average*Profile[SAVE.User[player_num]].first_death_num+time;
					Profile[SAVE.User[player_num]].first_death_num++;
					Profile[SAVE.User[player_num]].death_average = sum / Profile[SAVE.User[player_num]].first_death_num; 
				}
				Profile[SAVE.User[player_num]].death_num++;
			}
			bFirstDeath = false;
		}
		else if(change==1){
			play_sound(5);
			if(usernum>=2&&bMan==true&&SAVE.User[player_num]!=-1&&!(bOnline==true&&player_num!=NetWork.NFD[0].player_num)){
				if(bFirstDeath==true){
					int start_time = (90+SAVE.MatchTime*30)*60;
					int time = (start_time - Para.time_count)/60;
					int sum = Profile[SAVE.User[player_num]].death_average*Profile[SAVE.User[player_num]].first_death_num+time;
					Profile[SAVE.User[player_num]].first_death_num++;
					Profile[SAVE.User[player_num]].death_average = sum / Profile[SAVE.User[player_num]].first_death_num; 
				}
				Profile[SAVE.User[player_num]].death_num++;
			}
			bFirstDeath = false;
		}
		else if(change==3){
			play_sound(15);
			reborn_count = 0;
		}
		else if(change==0){
			muteki_count = 120;
		}
		condition = change;
	}
	return;
}

int CLASS_PLAYER::get_bomb(){
	return bomb_max;
}

int CLASS_PLAYER::get_hit(){
	return hit;
}

int CLASS_PLAYER::get_spell_count(){
	return spell_count;
}

void CLASS_PLAYER::set_spell_count(int add){
	spell_count += add;
	return;
}

int CLASS_PLAYER::get_muteki_count(){
	return muteki_count;
}

void CLASS_PLAYER::set_muteki_count(int add){
	muteki_count = add;
	return;
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

float CLASS_PLAYER::get_speed(){
	return speed;
}

void CLASS_PLAYER::add_speed(float add){
	speed += add;
	return;
}

void CLASS_PLAYER::power_plus(int plus){
	if(power+plus<9&&power+plus>0)	power += plus;
	else if(power+plus<=0)		power = 1;
	else				power = 9;
	return;
}

void CLASS_PLAYER::bomb_max_plus(int plus){
	if(bomb_max+plus<9&&bomb_max+plus>0)	bomb_max += plus;
	else if(bomb_max+plus<=0)		bomb_max = 1;
	else				bomb_max = 9;
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

void CLASS_PLAYER::hit_reset(){
	hit = 0;
	hit_count = 0;
	return;
}

void CLASS_PLAYER::level_plus(int plus){
	if(condition!=0)	return;
	if(spell_level+plus<3)	spell_level += plus;
	else		spell_level = 3;
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
		if(dokuro!=0){
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
		spell_level = 1;
		bKickbomb = false;
		bSpbomb = false;
		bBouga = false;
		bSumizome = false;
		dokuro = 0;
		dokuro_count = 0; 
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
		reborn[0] = x;
		reborn[1] = y;
		bMove = false;
		flash = 0;
		x = reborn[2];
		y = reborn[3];
		bx = reborn[2];
		by = reborn[3];
	}
	if(reborn_count<40){
		for(int i=0;i<10;i++){
			EfMake(reborn[0],reborn[1],0,1+i+player_num*10);
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

void CLASS_PLAYER::make(float sx,float sy,int schara,int scolor,bool man,int pnum){
//初期化処理
	if(pnum>=0)	player_num = pnum;
	x = sx;
	y = sy;
	bx = x;
	by = y;
	ai_x = x;
	ai_y = y;
	chara = schara;
	switch(chara){
		case REIMU:
			speed = 3.0;
			gage_per = 3;
			wsprintf(spell_name[0] , "「夢想封印」");
			wsprintf(spell_name[1] , "「夢想封印・散」");
			wsprintf(spell_name[2] , "「夢想封印・滅」");
			break;
		case MARISA:
			speed = 4.5;
			gage_per = 3;
			wsprintf(spell_name[0] , "「マスタースパーク」");
			wsprintf(spell_name[1] , "「アサシンスパーク」");
			wsprintf(spell_name[2] , "「ファイナルスパーク」");
			break;
		case SAKUYA:
			speed = 4.0;
			gage_per = 0;
			wsprintf(spell_name[0] , "「ジャック・ザ・リッパー」");
			wsprintf(spell_name[1] , "「ジャック・ザ・ルドビレ」");
			wsprintf(spell_name[2] , "「殺人ドール」");
			break;
		case REMILIA:
			speed = 3.0;
			gage_per = 2;
			wsprintf(spell_name[0] , "「全世界ナイトメア」");
			wsprintf(spell_name[1] , "「ミッドナイトディザスター」");
			wsprintf(spell_name[2] , "「レミリアストーカー」");
			break;
		case FRANDRE:
			speed = 3.5;
			gage_per = 3;
			wsprintf(spell_name[0] , "「そして誰もいなくなるか？」");
			wsprintf(spell_name[1] , "「そして誰も彼も死ぬがよい」");
			wsprintf(spell_name[2] , "「４９５年の波紋」");
			break;
		case YOUMU:
			speed = 4.5;
			gage_per = 1;
			wsprintf(spell_name[0] , "「妖童餓鬼の断食」");
			wsprintf(spell_name[1] , "「二百由旬の一閃」");
			wsprintf(spell_name[2] , "「業風神閃斬」");
			break;
		case YUYUKO:
			speed = 3.5;
			gage_per = 1;
			wsprintf(spell_name[0] , "「亡我郷」");
			wsprintf(spell_name[1] , "「完全なる墨染の桜」");
			wsprintf(spell_name[2] , "「反魂蝶」");
			break;
		case YUKARI:
			speed = 3.5;
			gage_per = 1;
			wsprintf(spell_name[0] , "「動と静の均衡」");
			wsprintf(spell_name[1] , "「夢と現の境界」");
			wsprintf(spell_name[2] , "「メビウスの表裏」");
			break;
		case REISEN:
			speed = 4.5;
			gage_per = 2;
			wsprintf(spell_name[0] , "「幻想催眠（インビシブルウォール）」");
			wsprintf(spell_name[1] , "「幻影の壁（イリュージョンウォール）」");
			wsprintf(spell_name[2] , "「月兎爆誕（ルナファントム）」");
			break;
		case NITORI:
			speed = 4.0;
			gage_per = 2;
			wsprintf(spell_name[0] , "「スピン・ザ・ボンバー」");
			wsprintf(spell_name[1] , "「オプティカルカモフラージュ」");
			wsprintf(spell_name[2] , "「のびーるアーム」");
			break;
		case SANAE:
			speed = 3.0;
			gage_per = 5;
			wsprintf(spell_name[0] , "「天の恵み」");
			wsprintf(spell_name[1] , "「サモンタケミナカタ」");
			wsprintf(spell_name[2] , "「ミラクルフルーツ」");
			break;
		case UTUHO:
			speed = 2.5;
			gage_per = 4;
			wsprintf(spell_name[0] , "「重水素融合」");
			wsprintf(spell_name[1] , "「ギガフレア」");
			wsprintf(spell_name[2] , "「アトミックボム」");
			break;
	}
	for(int i=0;i<4;i++){
		bAtariPlayer[i] = false;
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
	dokuro_count = 0;
	dokuro_death_count = 0;
	AI_count = 0;
	illusion_flash = 0;
	flash = 255;
	img_count = 0;
	img_num = 7;
	control_num = SAVE.Key_Type[player_num];//どのパッドで操作するか
	color = scolor;
	for(int i=0;i<PLAYER_CHIP_NUM;i++){
		img[i] = gPlayer[chara][color][i];
	}
	for(int i=0;i<2;i++){
		atari_x[i] = sx;
		atari_y[i] = sy;
	}
	for(int i=0;i<8;i++){
		d_hanyou[i] = 0;
		i_hanyou[i] = 0;
	}
	for(int i=0;i<4;i++)	reborn[i] = 0;
	bSpbomb = false;
	bKickbomb = false;
	bMan = man;
	bMove = true;
	bTime = false;
	bCamo = false;
	bRudo = false;
	bBouga = false;
	bSumizome = false;
	bomb = 0;
	spell = 0;
	up = 0;
	down = 0;
	left = 0;
	right = 0;
	spell_level = 1;
	draw_level = 0;
	dokuro = 0;
	if(bIllusion==true){
		bomb_max = Player[player_num].get_bomb();
		power = Player[player_num].get_power();
		flash = 0;
	}
	for(int i=0;i<LARGE_X;i++){
		for(int j=0;j<LARGE_Y;j++){
			AI_value[i][j] = 0;
			AI_bomb[i][j] = 0;
			AI_map[i][j] = 0;
		}
	}

	return;
}

struct RECORDDATA{
	int x;
	int y;
	vector<int> PastX;
	vector<int> PastY;
	int direction;
};

/*void CLASS_PLAYER::AI(int *bomb,int *spell,int *up,int *down,int *left,int *right){
	//MAP情報は取得済み
	//BombとExp情報も取得済み
	

	int x1 = X_ZAHYO_TO_NUM(x-7);
	int x2 = X_ZAHYO_TO_NUM(x+7);
	int y1 = Y_ZAHYO_TO_NUM(y-4);
	int y2 = Y_ZAHYO_TO_NUM(y+18);
	if(to_direction==-1){
		if(gage==gage_max&&Search(X_ZAHYO_TO_NUM(x),Y_ZAHYO_TO_NUM(y))>=0){
			*bomb = 0;
			*spell = 1;
		}
		else{
			if((bBomb==true&&i_hanyou[3]==0)||(bIllusion==true&&Map.field[X_ZAHYO_TO_NUM(x)][Y_ZAHYO_TO_NUM(y)]==3))		*bomb = 1;
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
		if(ai_x!=x||ai_y!=y){
			*spell = 0;
			*bomb = 1;
		}
	}
	
	for(int i=0;i<LARGE_X;i++){
		for(int j=0;j<LARGE_Y;j++){
			AI_value[i][j] = 0;
			AI_bomb[i][j] = 0;
			AI_map[i][j] = 0;
		}
	}
	return;

}
*/

void CLASS_PLAYER::AI_Record(vector<ZAHYODATA> &Record,int c_num){
	int search_num = 5;
	if(bomb_num==0&&ai_x==x&&ai_y==y&&bMove==true)	search_num = 10;	
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
				else if(i!=0&&bKickbomb==true&&*check==-2){
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
				else if(i!=0&&bKickbomb==true&&*check==-2){
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
				else if(i!=0&&bKickbomb==true&&*check==-2){
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
				else if(i!=0&&bKickbomb==true&&*check==-2){
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	char message[64];
	int search_num = 5;
	if(bomb_num==0&&ai_x==x&&ai_y==y&&bMove==true)	search_num = 10;	
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
		if(gage==gage_max&&Search(X_ZAHYO_TO_NUM(x),Y_ZAHYO_TO_NUM(y))>=0){
			*bomb = 0;
			*spell = 1;
			if(chara==MARISA){
				*spell = 0;
				bool fl = false;
				for(int i=0;i<PLAYER_NUM;i++){
					if(player_num!=i&&Player[i].get_condition()==0){
						float px,py;
						Player[i].get_xy(&px,&py);
						if(get_direction()==0){
							if(py<y)	*spell = 1;
						}
						if(get_direction()==1){
							if(px>x)	*spell = 1;
						}
						if(get_direction()==2){
							if(py>y)	*spell = 1;
						}
						if(get_direction()==3){
							if(px<x)	*spell = 1;
						}
					}	
				}
				if(*spell==0)	*bomb = 1;
			}
		}
		else{
			if((bBomb==true&&i_hanyou[3]==0)||(bIllusion==true&&Map.field[X_ZAHYO_TO_NUM(x)][Y_ZAHYO_TO_NUM(y)]==3))		*bomb = 1;
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
		if(ai_x!=x||ai_y!=y){
			*spell = 0;
			*bomb = 1;
		}
	}
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
	vector<int> vvari;//0:敵 1:弾 2:爆弾(まだ大丈夫） 3:爆風 4:爆弾（ヤバイ）
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
		if((*it).pattern==10||flag==true||(*it).count>=100)	vvari.push_back(4);
		else							vvari.push_back(2);
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
				else if(vvari.at(a)==4){
					if(priority[i]>-75)	priority[i] = -75;
					flag = false;				
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
	if(1/*X_ZAHYO_TO_NUM(ai_x)==X_ZAHYO_TO_NUM(x) && Y_ZAHYO_TO_NUM(ai_y)==Y_ZAHYO_TO_NUM(y)*/){
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
						priority[a+1] += 10;
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
		if(ai_x!=x||ai_y!=y){
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
	if(i_hanyou[0]>=0&&Player[i_hanyou[0]].get_condition()==0){
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
				if((*it).pattern==10&&chara==REMILIA&&value>-1)	value = -1;
				else	value = -20;
			}
			else if((X_ZAHYO_TO_NUM(x)!=(*it).x||Y_ZAHYO_TO_NUM(y)!=(*it).y)&&bKickbomb==true&&(*it).count<100/*&&sx==(*it).x&&sy==(*it).y*/){
				value = -1;
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
			if((*it).pattern==10&&chara==REMILIA&&value>-1)	value = -1;
			else	value = -30;
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
