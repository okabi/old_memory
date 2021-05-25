#include "map.h"
#include "item.h"
#include "para.h"
#include "bomb.h"

GRAND_MAPDATA MapData[MAP_NUM];
MAPDATA Map;

void MLoad();
void MDraw();
void M1Event();
void M2Event();

void MLoad(){
	for(int i=0;i<MAP_NUM;i++){
		switch(i){
			case 0:
				MapData[i].img_ground[0] = 0;
				MapData[i].img_ground[1] = 0;
				MapData[i].img_wall[0] = 0;
				MapData[i].img_wall[1] = 1;
				MapData[i].img_block[0] = 0;
				MapData[i].img_block[1] = 2;
				MapData[i].block_num = 90;
				MapData[i].item_num[0] = 10;
				MapData[i].item_num[1] = 15;
				MapData[i].item_num[2] = 4;
				MapData[i].item_num[3] = 2;
				MapData[i].item_num[4] = 4;
				MapData[i].item_num[5] = 2;
				MapData[i].item_num[6] = 1;
				wsprintf(MapData[i].name , "BORING FOREST");
				break;
			case 1:
				MapData[i].img_ground[0] = 1;
				MapData[i].img_ground[1] = 0;
				MapData[i].img_wall[0] = 1;
				MapData[i].img_wall[1] = 1;
				MapData[i].img_block[0] = 1;
				MapData[i].img_block[1] = 2;
				MapData[i].block_num = 90;
				MapData[i].item_num[0] = 10;
				MapData[i].item_num[1] = 15;
				MapData[i].item_num[2] = 2;
				MapData[i].item_num[3] = 2;
				MapData[i].item_num[4] = 4;
				MapData[i].item_num[5] = 4;
				MapData[i].item_num[6] = 2;
				wsprintf(MapData[i].name , "LANDMINE LAND");
				break;
			case 2:
				MapData[i].img_ground[0] = 2;
				MapData[i].img_ground[1] = 0;
				MapData[i].img_wall[0] = 2;
				MapData[i].img_wall[1] = 1;
				MapData[i].img_block[0] = 2;
				MapData[i].img_block[1] = 2;
				MapData[i].block_num = 90;
				MapData[i].item_num[0] = 20;
				MapData[i].item_num[1] = 15;
				MapData[i].item_num[2] = 3;
				MapData[i].item_num[3] = 8;
				MapData[i].item_num[4] = 0;
				MapData[i].item_num[5] = 2;
				MapData[i].item_num[6] = 2;
				wsprintf(MapData[i].name , "CORE OF THE 2ND SUN");
				break;
		}
	}
	
	for(int i=0;i<LARGE_X;i++){
		for(int a=0;a<LARGE_Y;a++){
			if(i==0||a==0||i==LARGE_X-1||a==LARGE_Y-1||(i%2==0&&a%2==0))	Map.field[i][a] = 1;
			else								Map.field[i][a] = 0;
			if(Map.type==2&&i==9&&a==6)					Map.field[i][a] = 1;		
		}	
	}
	int itemnum[ITEM_GRAPH_NUM] = {0,};
	for(int i=0;i<MapData[Map.type].block_num;i++){
		bool flag = false;
		while(flag==false){
			int x = get_rand(LARGE_X-1);
			int y = get_rand(LARGE_Y-1);
			if((x<=2&&y<=2)||(x<=2&&y>=LARGE_Y-3)||(x>=LARGE_X-3&&y>=LARGE_Y-3)||(x>=LARGE_X-3&&y<=2)){}
			else{
				if(Map.field[x][y]==0){
					Map.field[x][y] = 2;
					for(int a=0;a<ITEM_GRAPH_NUM;a++){
						if(itemnum[a]<MapData[Map.type].item_num[a]){
							IMake(x,y,a);
							itemnum[a]++;
							break;
						}
					}
					break;
				}
			}
		}
	}

	return;
}

void MDraw(){
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
	if(repeat==9)	DrawExtendGraph(-10,-10,650,490,gBack[0],FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	for(int i=0;i<LARGE_X;i++){
		for(int a=0;a<LARGE_Y;a++){
			DrawExtendGraph(X_NUM_TO_ZAHYO(i)+shake_x,Y_NUM_TO_ZAHYO(a)+shake_y,1+X_NUM_TO_ZAHYO(i+1)+shake_x,1+Y_NUM_TO_ZAHYO(a+1)+shake_y,gMap[MapData[Map.type].img_ground[0]][MapData[Map.type].img_ground[1]],TRUE);
			if(repeat==9){
				if(Map.field[i][a]==1)		DrawExtendGraph(X_NUM_TO_ZAHYO(i)+shake_x,Y_NUM_TO_ZAHYO(a)+shake_y,1+X_NUM_TO_ZAHYO(i+1)+shake_x,1+Y_NUM_TO_ZAHYO(a+1)+shake_y,gMap[MapData[Map.type].img_wall[0]][MapData[Map.type].img_wall[1]],TRUE);
				else if(Map.field[i][a]==2)	DrawExtendGraph(X_NUM_TO_ZAHYO(i)+shake_x,Y_NUM_TO_ZAHYO(a)+shake_y,1+X_NUM_TO_ZAHYO(i+1)+shake_x,1+Y_NUM_TO_ZAHYO(a+1)+shake_y,gMap[MapData[Map.type].img_block[0]][MapData[Map.type].img_block[1]],TRUE);
			}
		}	
	}
	if(Map.type==1){
		M1Event();
	}
	else if(Map.type==2){
		M2Event();
	}

	return;
}

void M1Event(){
	static int flag=0;
	static int power = 1;
	static int x[2];
	static int y;
	int start_time = (90+SAVE.MatchTime*30)*60;
	int time = start_time - Para.time_count;
	if(time<10)	flag = 0;
	if(time>=30*60&&Para.time_count>4000){
		int count = time - 30*60;
		if(count%(20*60)==0){
			play_sound(9);
			for(int i=0;i<20;i++){
				EfMake(640.0-256.0*0.8/2.0-256.0*0.8*i,(Y_NUM_TO_ZAHYO(1)+Y_NUM_TO_ZAHYO(2))/2.0,1,42);
				EfMake((X_NUM_TO_ZAHYO(LARGE_X-2)+X_NUM_TO_ZAHYO(LARGE_X-1))/2.0,480.0-256.0*0.8/2.0-256.0*0.8*i,1,43);
				EfMake(256.0*0.8/2.0+256.0*0.8*i,(Y_NUM_TO_ZAHYO(LARGE_Y-2)+Y_NUM_TO_ZAHYO(LARGE_Y-1))/2.0,1,44);
				EfMake((X_NUM_TO_ZAHYO(1)+X_NUM_TO_ZAHYO(2))/2.0,256.0*0.8/2.0+256.0*0.8*i,1,45);
			}
			flag = 1;
			x[0] = 9;
			x[1] = 9;
			y = 1;
			power = 1+get_rand(5);
		}
		else if(count%(20*60)>=120&&flag>=1){
			if((count-120)%10==0){
				if(Map.field[x[0]][y]!=1&&Map.field[x[0]][y]!=2)	BMake(x[0], y, 0, power, 0, 12);
				if(Map.field[x[1]][y]!=1&&Map.field[x[1]][y]!=2)	BMake(x[1], y, 0, power, 0, 12);
				if(flag==1){
					x[0]--;
					x[1]++;
					if(x[0]==1){
						flag = 2;
					}
				}
				else if(flag==2){
					y++;
					if(y==11)	flag = 3;
				}
				else if(flag==3){
					x[0]++;
					x[1]--;
					if(x[0]==10)	flag = 0;
				}
			}
		}
	}

	return;
}

void M2Event(){
	static int flag=0;
	int start_time = (90+SAVE.MatchTime*30)*60;
	int time = start_time - Para.time_count;
	if(Effect.size()==0&&Para.time_count>3600){
		EfMake((X_NUM_TO_ZAHYO(9)+X_NUM_TO_ZAHYO(10))/2.0,(Y_NUM_TO_ZAHYO(6)+Y_NUM_TO_ZAHYO(7))/2.0,2,46);
	}
	if(time>=30*60&&Para.time_count>3600){
		int count = time - 30*60;
		if(count%(25*60)==0){
			play_sound(9);
			play_sound(14);
			for(int i=0;i<20;i++){
				EfMake(640.0-256.0*0.8/2.0-256.0*0.8*i,(Y_NUM_TO_ZAHYO(0)+Y_NUM_TO_ZAHYO(1))/2.0,1,42);
				EfMake(640.0-256.0*0.8/2.0-256.0*0.8*i,(Y_NUM_TO_ZAHYO(LARGE_Y-1)+Y_NUM_TO_ZAHYO(LARGE_Y))/2.0,1,42);
			}
			flag = 1;
		}
		else if(count%(25*60)<120&&flag>=1){
			int c = count%(25*60);
			if(bTimeStop==false)	SShake(0,3.0*(float)c/120.0);
		}
		else if(count%(25*60)>=120&&flag>=1){
			int c = count%(25*60);
			if(bTimeStop==false)	SShake(0,3.0*(float)(13*60-c)/(float)(13*60-120));
			bSecondSun = true;
			if(count%(25*60)==13*60){
				bSecondSun = false;
				flag = 0;
			}
		}
	}
	
	return;
}