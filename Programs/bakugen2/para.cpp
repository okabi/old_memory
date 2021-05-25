#include "para.h"
#include "net.h"
#include "menu.h"

CLASS_PARA Para;

void ParaMain();

void ParaMain(){
	Para.draw();

	return;
}


void CLASS_PARA::draw(){
	char message[64];
        for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()>=0){
			if(Player[i].get_condition()==0){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			}
			else{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				SetDrawBright(50,50,50);
			}
			if(bOnline==true){
				if(Player[i].bMan==false)	wsprintf(message , "COM%d",i+1);
				else				wsprintf(message , "%s",NetWork.NFD[netsettingB_carsol[i]].name);
			}
			else{
				if(Player[i].bMan==false)	wsprintf(message , "COM%d",i+1);
				else if(SAVE.User[i]==-1)	wsprintf(message , "ÉQÉXÉg%d",i+1);
				else				wsprintf(message , "%s",Profile[SAVE.User[i]].name);
			}
			DrawSt(160*i+50,0,GetColor(255,255,255),GetColor(0,0,255),font_default,message);
			if(repeat==9)	DrawGraphF(160*i,0,gFace[Player[i].chara],FALSE);
			wsprintf(message , "Lv%d",Player[i].spell_level);
			DrawSt(160*i+60,15,GetColor(255,255,255),GetColor(0,0,255),font_default,message);
			wsprintf(message , "B:%d P:%d",Player[i].bomb_max, Player[i].power);
			DrawSt(160*i+60,30,GetColor(255,255,255),GetColor(0,0,255),font_default,message);
			wsprintf(message , "hit:%d",Player[i].hit);
			DrawSt(160*i+60,45,GetColor(255,255,255),GetColor(0,255,0),font_default,message);
			if(repeat==9)	DrawBox(160*i+102,19,160*i+152,25,GetColor(150,0,0),TRUE);
			int x = 50.0*((float)Player[i].gage/(float)Player[i].gage_max);
			if(repeat==9){
				if(x==50)	DrawBox(160*i+102,19,160*i+152,25,GetColor(255,255-abs(180-5*count%360),255),TRUE);
				else		DrawBox(160*i+102,19,160*i+102+x,25,GetColor(255,255,75),TRUE);
			}
			SetDrawBright(255,255,255);
		}
		//Player[i].draw();
	}
	int time[2];
	time[0] = time_count/3600;
	time[1] = (time_count-time[0]*3600)/60;
	wsprintf(message , "TIME %d:%02d",time[0],time[1]);
	int size = GetDrawStringWidthToHandle(message,sizeof(message),font_time);
	int color = GetColor(255,255,255);
	if(time_count<=300){
		color = GetColor(255,100,100);	
		if(time_count%60==0)	play_sound(8);
	}
	else if(time_count<=600){
		color = GetColor(255,200,200);	
		if(time_count%60==0)	play_sound(7);
	}
	DrawSt(320-size/2,70,color,0,font_time,message);
	if(start_count==0){
		if(bTimeStop==false)	time_count--;
	}
	count++;
	
	return;
}
