#include "system.h"
#include "talk.h"
#include "boss.h"

TALKDATA Talk[CHARA_NUM][TALK_NUM];

bool bTalk;
int TalkNum;
int NowNum;//��b�ԍ�
int TalkCount;
int TalkCount2;
int TalkCount3;

void TLoad();
void TReset();
void TDraw();
void TMove(int chara, int i);
void TMake(int num);


void TLoad0(){
	int chara = 0;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂾂����ȏ��ɖ������񂾂݂����ˁc");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���G�����퓬�@�����ł���A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�f�J�����ɂ͎ア�邪���ł���c");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�S�W���o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A���͉邶��Ȃ��ă��X���ł���");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴖ��[��");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�Ɉ��A����Ƃ��̓T���O���X���O�����̂�");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������낤");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܂�������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����͉������������Ă���Ȃ�������");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ł����H");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����͕������ł���");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ɋQ�����p�l�ǂ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���e���R��ɏW�܂�A���΂���̕����ł�");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����͂���͕����ȏ���");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�ŁA�ǂ�����Ό��z���ɋA���̂�����H");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�́H�Ȃɂ��ꂨ��������");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�E�E�E");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 2;//�a�f�l�J�n
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���O���N���Ȃ�ċ����Ȃ����A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�Ƃ肠��������܂��傤");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�e�������ˁH����ɏ��Ă΋����Ă����̂�");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����G�ɉ񂷂Ƃǂ��Ȃ邩�A�����Ă������");
					}
				}
				else if(i==16){
					Talk[chara][num].flag[i] = 3;//�G����������
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������т���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��[���A��邼�[�I^^");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǂ��H���ꂪ�ޏ��̗͂�");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����̉��b�ł͎���|���Ȃ���");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������т���");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�c�܂�������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "������A���̐�ǂ�����΂����̂�����H");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 11;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�́H����Ȃ��ƒm��܂����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ƌ������A�A���^�N�H");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 11;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܁A����Ⴛ����");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�͂��낻��A��܂���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�������A�j����������^^");
					}
				}
				else if(i==7){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���储��");
					}
				}
				else if(i==8 || i==9){
					if(i==8)	Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					if(i==9)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�͂��B���ꂩ��ǂ��������̂��c");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 22;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̐i�W�������܂܎O����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�Ă��I����āA�H�ɂȂ�����������ǁc");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ȃ̂�����˂��A���̐��E");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�퓬�@�A��̎��̓|�b�v�R�[���H");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���łɃA�z���ۂ��̂���������");
					}
				}
				else if(i==4){
					Talk[chara][num].flag[i] = 1;//�����o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�݂₠����������������������������");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�a���˂���������������������������");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�I�H");
					}
				}
				else if(i==7){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�V���[�e�B���O�����ł�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "����O�����ł��o����l�ȓ�Փx�ɂ���");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�m��񂪂�");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�H�H�H������������(߄D�)�������������H�H�H");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�ŁA�A���^���������̈���Ȃ́H");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A��܂�");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�A��ȁI");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�ŁA�ǂ��������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���̐��E����E�o�ł���̂�����H");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�l�ɂ͕�����܂��~");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̃Q�[��������̖l����Ȃ���");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ʓ|������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�o�Ă���z�Ђ��[����|���Ă�����");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c����H����l���G���Ȃ�ł���");
					}
				}
				else if(i==19){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��[���A���܂ōl�����Z���I�ł��邼�[");
					}
				}
				else if(i==20){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�I�H");
					}
				}
				else if(i==21){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��؂̃p���[�Ō��C���������[�I");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������ӂ����ނӂ�����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���E��D�����背�[�U�[����������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���������������Ă��ꂽ���");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ł��A���F�M���͂��̒��x�̗͂Ȃ̂�");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�i�@�L_�T`�j̰�");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���āA���ꂩ��ǂ����܂��傤��");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����[��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�K���Ɋ撣���");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A���̐�͒e�����������Ԃ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�o���Ȃ����[�U�[���o�Ă��܂��̂�");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���ƒ��ӂ��Ă���������");
					}
				}
				else if(i==8 || i==9){
					if(i==9)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�i�@�L_�T`�j̰�");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 21;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̕ӂ͂������L��������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���������̂˂��c");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�Ȃ񂾂��悭������Ȃ�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����͂��邯��");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//���l�o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̕ӂ���v�X�̐�ł���");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 3;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�R�Ɉ͂܂�Ă��āA�ő���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��͍~��Ȃ��ł�����");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��A����ƃ}�g���Ȋ炵���z��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�������");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ȃ����ŋߕ������ŉ\��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�R�X�v���C���[�ł���");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��������H");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�S�W������������ꂽ�ƕ�����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���A���łɃA�z��");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�d�Ԃ̎ʐ^���B��ɗ������ɁA���Ȃ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�������̂Řb�������Ă݂��̂ł�");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂾁A�A���^���������̈���Ȃ̂�");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴀ���X�Ƙb���Ă����ʂ�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�A���^�����̃T���h�o�b�O�ɂȂ�Ȃ���");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�Ȃ��Ȃ��Ђǂ����Ƃ����Ȃ�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���������ɂ��}�g���Ȃ̂͂��܂���");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�̓j�R�~����Ȃ��ł���");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������낤");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܂��A���낻��q���g��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�~�������ł��傤");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 2;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�S�W�������Ȃ����������Ă���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�������N�͌o���Ă܂�����");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�I�����m���Ă�́H");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��������̂��߂�ǂ����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�l�Ə����w�����S������邩�ǂ��炩��");
					}
				}
				else if(i==19){
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�́H");
					}
				}
				else if(i==20){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���{��ł���");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��I������������I�I�I");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A�������ׂ����Ƃ�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�S�Č������");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������ƒm���Ă鎖��f���Ȃ���");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 1;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������������I�I�I");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c��ɖ��܂��Ă݂�H");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂��A���݂܂���ł���");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǂ���炠�Ȃ��͂��̐��E��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�l�Ԃ���Ȃ��悤��");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�����͂����ɗ��ĊԂ��Ȃ��̂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�悭������Ȃ��̂ł���");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�㋉���̕��X�́A���Ȃ��ɂ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����m���Ă���悤�ł���");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܂�A�A���^�̐�y��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�T���Ηǂ��̂ˁH");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 0;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������ƂɂȂ�܂���");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�Ƃ������A�A���^���ē�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���Ȃ�����");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 4;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�͍�����R�[���X�Ȃ��");
					}
				}
				else if(i==14){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���储��");
					}
				}
				else if(i==15 || i==16){
					if(i==15)	Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					if(i==16)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 5;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�Ȃ�ł���ȂɃ����h�C�z");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�΂�����Ȃ̂�����c");
					}
				}
			}
		}
	}

	return;
}

void TLoad1(){
	int chara = 1;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 12;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ђ������������ς����[");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���傤�̂������͂���ɂ��悤");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�S�W���o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�y���y���i�O�ցO�j");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ւ񂫂�����邢�ł�");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���݂܂���ł���");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c����̂ǂ����ӂ��Ă�񂾂�");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ł͒E���ł��l�т��܂�");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��������邢�����߂�");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ɐU��ꂽ������������");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�L�G�ցG`)");
					}
				}
				else if(i==11){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹���j���W���Ԃ���");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 5;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂����܂���������");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������т���");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��������H�c");
					}
				}
				else if(i==3 || i==4){
					if(i==4)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���p�̔��������G������ĎQ��܂���");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̎O�����Ԃ̓l�g�Q�O����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ƂĂ��[�����������ł���");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�����o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�݂₠����������������������������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�a���˂���������������������������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ł��ˁA�����a����܂���");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�V���[�e�B���O�����ł�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "����O�����ł��o����l�ȓ�Փx�ɂ���");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[�����[���A�N�\�r�j������");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�e�������Ă�������ł�����");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ł��ˁA���������v���Ă��܂���");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂾂��M���Ƃ͕����荇�������ȋC�����܂�");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ȐH�ו��͉��ł����H");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��؂ł�");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ł��ˁA�����ł�");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ꏏ�ɖ�؂��Ԃ��ׂ����ɏo�܂��傤");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 24;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����͖��Âł���");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��[���A�������[�O�O");
					}
				}
				else if(i==16){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹�[�_�C�R���Ԃ���");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������ӂ����ނӂ�����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����������������������������������");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�䎌���Ⴂ�܂�");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 22;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��͂�A���ƋM���͕����荇���Ȃ��悤�ł�");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ł��ˁA���������v���Ă��܂���");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������ق�������̂��}�i�[�ł�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���悤�Ȃ�");
					}
				}
				else if(i==6 || i==7){
					if(i==7)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹�[��x�Ɨ��񂶂�ˁ[��O�O");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 16;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�̐S�̊����ɔ�ׂ��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�g�̂̊����Ȃ�đ債�����Ɩ���");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A�l�g�Q�������Ȃ�");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���̎鐝��C������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�R�₷��");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//���l�o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̕ӂ���v�X�̐�ł���");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ɂ��͏���");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���ꂩ�疈������Ă������H");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�H");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����m��񂯂ǁA�ŋ߂��O���Ȃ���");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�͖�؂��Ԃ��ׂ����ɏo�܂���");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ق�");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���ƁA���c�����T���ɍs���܂�");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�c�ʖڂ��R�C�c�A�������Ƃ����Ȃ���)");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�d�ԂƂ������Ȃ��H");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���͍��A�d�Ԃ̎ʐ^���B���Ă��");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�L�~���ꏏ�ɍs������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�l�l�A�ǂ����낤�H");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ڂ��͂����₳�Ȃ��������ł�");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==15){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���O�����[�n�N�T�C�Ԃ���");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 11;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��I������������I�I�I");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "..");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], ".....");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "...");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "..");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�O���[�v��b�r�炷��");
					}
				}
				else if(i==9 || i==10){
					if(i==10)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 23;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ڂ��͂��Ȃ�����Ƃ������񂷂�");
					}
				}
			}
		}
	}

	return;
}

void TLoad2(){
	int chara = 2;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 12;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[��A���낻��V�т͂�߂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�S�W���T����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂩕�����Ȃ���肪����񂾂��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�A�C�c�ǂ��ɂ���񂾂�H");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�S�W���o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���q�ɏ������_���[");
					}
				}
				else if(i==3){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴖ��[��");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A������");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̂��A4STEP��49�Ԃ�˂񂯂ǁc");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[�A��������ƖZ������");
						else if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�҂��Ƃ��Ă���ւ�");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�������܂ŉ��b�݂����Ȑ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], " �M�����Ă��̂�)");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ƃ���ŁA�������[�ւ񂩂����H");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����H�m���Ȃ�");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�i�@�L_�T`�j̰�");
					}
				}
				else if(i==11){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ȊO�ɗp�͂ˁ[��I�I�I");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 6;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�o���o���I�J�`���J�`���I�I");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "(�L�[�{�[�h���N���b�V�����鉹)");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ŁA49�Ԃ�˂񂯂ǁc");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������I�I�I");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���储��");
					}
				}
				else if(i==4 || i==5){
					if(i==4)	Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					if(i==5)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A�C�c�����������񂾂�E�E�E");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 16;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̕ӂ͍g�t���Y�킾��");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ɂ��Ă��A�S�W���͉�����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�s�����񂾂낤�H");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�����o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�݂₠����������������������������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�a���˂���������������������������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������O���������");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹�����������������낊�肨����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���������������������ӂ��������G���F");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̂��A�S�W�������ɍs�������m��ȁc");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "p������邢��т��Ղɂ񂐂�����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����������ς����������ۂ����ς�");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�����A�b�ɂȂ�Ȃ��ȁE�E�E");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], " �߂�ǂ������E�E�E)");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�܂��A�����Ă��炤�Ȃ�N���ǂ���)");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A4STEP��49�ԕ�����H");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�́H�ӂ��[���Ă��ՁH");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�g�C���b�g�y�[�p�[�ɂ��܂����O�O");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�B");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴀ���A��茩���邩��E�E�E");
					}
				}
				else if(i==15){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹�[�A�s�[�}����������");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������ӂ����ނӂ�����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��������������A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��茩�Ă�����ȁH");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���߂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��؂�ׂ����̓r��������O�O");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�́H");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����A���[�������Ƃ�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�A��܂��O�O");
					}
				}
				else if(i==5){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���储��");
					}
				}
				else if(i==6 || i==7){
					if(i==6)	Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					if(i==7)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�c���Ȃ񂾃A�C�c)");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 21;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�~�ɂȂ��Ă��S�W���ɉ�ĂȂ��Ƃ�");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������܂������Ȃ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "49�ԓ�����Ȃ����E�E�E");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���C�ɂ��̌i�F��������");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//���l�o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�΂���Ȃ���");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǁ[������A����ȏ���");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�S�W�����[�ւ񂩂����H");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�S�W���Ȃ�A��������������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ǂ��Ă�����");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����͑��c�����T���ɂ�����");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��؂�ׂ����ɏo���񂶂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ����������H");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����Ȃ��Ƃ������Ă��C������");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴀ����A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "4STEP��49�ԕ�����H");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǂ�ǂ�A������ƌ��Ă݂悤");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�B");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�E�E�E�B");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�E�E�E�B");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�悵�A�u�d�Ԃłc�v��邩");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ˁ[");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A����σX�e�}�j�ɂ��悤����");
					}
				}
				else if(i==19){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�܂��p�v���C���n�܂��)");
					}
				}
				else if(i==20){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�̂���_�����ɂ���Ă�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "����Ă邩��(���");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 11;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��I������������I�I�I");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�X�e�}�j�A�~�X������");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����A���h���ݒ�ɂȂ��Ă���������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 35;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�S��ǁ[�ł�����)");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴀ���͂����s����");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[�A���ł₩��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����ŃA�[�o�����C�i�[�B���čs���ւ�H");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��������̃A���O����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ō���ŁI");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����A�����������Ƃ�");
					}
				}
				else if(i==8){
					Talk[chara][num].flag[i] = 5;//�v���C���[����������
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���储��");
					}
				}
				else if(i==9 || i==10){
					if(i==9)	Talk[chara][num].flag[i] = 5;//�v���C���[����������
					if(i==10)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 34;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���[��A�ǂ����Ă��̖��͂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�N���������Ă���Ȃ��̂��낤�c");
					}
				}
			}
		}
	}

	return;
}

void TLoad3(){
	int chara = 3;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].flag[i] = 1;//�S�W���o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = -1;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�I�H");
					}
				}
				else if(i==2){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�I�H");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 12;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂾋���");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������ɂ���Ȃɑ傫�ȋ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�������Ƃ�");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������낤");
					}
				}
				else if(i==9){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 12;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�I�H");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 5;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̋U�҂��܂�������������");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���F�͂����̃~���[(�د");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������т���");
					}
				}
				else if(i==3 || i==4){
					if(i==4)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(�د");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 14;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǂ��i�F���ȁ[");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ōr��ł����S���������");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�����o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�݂₠����������������������������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�a���˂���������������������������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A���������");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�׋��Ȃ狳���邯��");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹����������������������������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�׋��Ȃ�ăg�C���ɗ����Ă�����{�P");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 12;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������pk�A�����������������Ղ������݂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����������炔���΂날�������ۂ���");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������ӂӂ��������ӂ�����������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�₳���₢���������Ⴕ�Ⴕ��₳���₳��");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���{��ł���");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���悤�Ȃ�");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A��̂�");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹�[�A���Ⴊ������������");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 4;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������ӂ����ނӂ�����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����y���y���y���y���y���y���y��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�y���y���y���y���y���y���y���y��");
					}
				}
				else if(i==2 || i==3){
					if(i==3)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[���[���[�ā[");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 15;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��~���Ă���");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 6;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̊i�D�ł͎���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "����������������܂ł́i�O�ցO�j");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���鋌�Ղɂ���R���A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂾂���");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//���l�o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A�S�W����");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����Ȋ����i�D�ŉ����Ă񂷂�");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[�A����A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�������[�ւ񂩂����H");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A����");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�S���ɎU��΂��؂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�Ԃ��ׂ����ɏo�邻���ł�");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�C�~�t");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������[�������");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܂����A������ǂ��Ă����܂ŁH");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 8;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 8;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==14){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 8;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����₾���̂Ԃ���");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 9;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���炳�������s����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������낤");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������A�������낻��A�邩��");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 9;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==7 || i==8){
					if(i==8)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 7;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�i�Ȃɂ��̂������j");
					}
				}
			}
		}
	}

	return;
}

void TLoad4(){
	int chara = 4;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 12;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ӂ���A�܂��܂��̓�������");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܁A�d�X�����͊ȒP����");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�S�W���o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���܂��Ăق����́[");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�y���y���i�O�ցO�j");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������邹�[�ȁA���܂�");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��ł�ł�ł�������������");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��ŁA�����_��");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����T���Ă�B");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ǂ����Ō��[�ւ񂩂����H");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����A���ĂȂ�����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�Ȃ񂩗p���ł����邎�H");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�y���y������i�O�ցO�j");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c��");
					}
				}
				else if(i==11){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��[���A��邼�[�O�O");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂������������`�`�`�I�I�H�H");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܁A�d�X������Ă����r�s�f��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "����Ȃ�Ɋ���Ă�(����");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������т���");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c����");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��[���A�����T���ɂ������i�O�ցO�j");
					}
				}
				else if(i==5){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A������Ɓc");
					}
				}
				else if(i==6 || i==7){
					if(i==6)	Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					if(i==7)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���[��A����͔Z���ȃK�`�z���̏L���c");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 14;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���݂����݂���");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�́A�ǂ��ł������B");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���ɕK�v�Ȃ͓̂d�Ԃ��B�d�ԁB");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�����o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�݂₠����������������������������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�a���˂���������������������������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���A��������Ȃ���");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c��H");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�d�ԁ���������������������������������");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������݂��ɂ����ǂ܂��ǂ�������������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���������킨�������Ȃ��͂���̂�߂�����");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�Ƃ�ł��Ȃ����ɗ��Ă��܂����悤��");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���ꂩ�疈����؂��Ă������H");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���O�ǂ񂾂���؍D���Ȃ񂾂�");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����A�����ł�");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��H");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ł���؂̉̂́E�E�E");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���邹�[�A�����؂Ńr���^����");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 9;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������ӂ����ނӂ�����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����ς�a�f�l��؂����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�z���g�͖�؍D���Ȃ񂶂�ˁH");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������[�ȁA�p�v���J��������");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������͑S���̖�؂��Ԃ��ׂ�����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�o�Ă�񂾂�����������������������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�H");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���ƃS�W�����߂�������������������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��������I�ސw�I");
					}
				}
				else if(i==6){
					Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A�΂��΂�");
					}
				}
				else if(i==7 || i==8){
					if(i==7)	Talk[chara][num].flag[i] = 6;//�G�l�~�[����������
					if(i==8)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�S�W����A���O�͉����֍s���c");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 14;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�d�ԃn�@�n�@(*�L�D`)");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ᕟ�ᕟ�`�B");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���̃t�H�[���̔������ɖ�����邺�c");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������A����ȑ��̓���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ʐ^���B��ɂ����̂�������ĂȂ�");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//���l�o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����A���̕ӂ��ᒿ������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�l�Ɠ����̕��ł����E�E�E�I�H");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�I�H");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�I�H");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�Ȃ񂩁A���ɂ��������˂񂯂ǁc");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ł���");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������āc�U�N�O��");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����ʂꂽ�Z����E�E�E�I�H");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܂����E�E�E���O�͉��̒�I�H");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Z����I�I�I�I�I");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 28;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���I�I�I�I");
					}
				}
				else if(i==13){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ł��w���܂��傤��");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��I������������I�I�I");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Z����A���̏�����Ȃ�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�X�y���J�[�h��");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ł��Ă���");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���Ă��A�����ʂꂽ��Ȃ�āA�������H");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���������΁A���ɂ�����ȌZ�Ȃ�āc");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�ł́A�����������ƂŁB");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���悤�Ȃ�");
					}
				}
				else if(i==8 || i==9){
					if(i==9)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 29;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
			}
		}
	}

	return;
}

void TLoad5(){
	int chara = 5;
	for(int num=0;num<TALK_NUM;num++){
		if(num==0){
			Talk[chara][num].talk_num = 16;
			Talk[chara][num].Nimg = 13;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����[���ς�炸�}�W�L�`");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���X���o�Ă���Ƃ��T���");
					}
				}
				else if(i==2){
					Talk[chara][num].flag[i] = 1;//�S�W���o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����܁`�A����܁`");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����܁`�`�`�`");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 6;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������[�[�[");
					}
				}
				else if(i==5){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������낤");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�n�@�B���ꂵ�������ւ�̂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�}�W�c�O���");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂���������������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "(�ײײײײ�");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 8;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܁A�Ƃ肠������������[");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��[����邼�[�O�O");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂����S�t���O�[");
					}
				}
				else if(i==12){
					Talk[chara][num].flag[i] = 2;//�a�f�l�J�n
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ł́A�l�͂����ʂ�d�������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�g���܂��ˁO�O");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������}�C�L������߂��[");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܂��ǂ����B�ǂ����ア���ȁ[(�΂�");
					}
				}
				else if(i==15){
					Talk[chara][num].flag[i] = 3;//�G����������
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 7;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������������������ӂ��������G���F");
					}
				}
			}
		}
		else if(num==1){
			Talk[chara][num].talk_num = 8;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�߰����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 12;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ウ�[�[�B���L�����g����0���Ƃ�(�΂�");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������т��邤��邤�邤��");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�܁A���͂�����ƋA�邯�ǁA");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "���O�����ɂ����Ƃ���");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�́H");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������q���񂪗��邩��A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�K���ɑ��肵�Ƃ��Ă������Ⴂ�ˁ`");
					}
				}
				else if(i==6 || i==7){
					if(i==7)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 9;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�i�@�L_�T`�j̰�");
					}
				}
			}
		}
		else if(num==2){
			Talk[chara][num].talk_num = 18;
			Talk[chara][num].Nimg = 17;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����[��i�ł��ȁ[");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���񂾂������t�������Ă�ƁA");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�΂����Ă݂����Ȃ�");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǂ񂾂��R���L������[�ȁ[(�Í�����");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A�z�͂܂��R�̒��ɂ�����[���ȁ[");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�v�[�N�X�N�X");
					}
				}
				else if(i==4){
					Talk[chara][num].flag[i] = 1;//�����o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�݂₠����������������������������");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�a���˂���������������������������");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�C�G�X�I");
					}
				}
				else if(i==7){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���{�A");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�N�[���j�b�N�I");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���������������������������̂�");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�H�H�H������������(߄D�)�������������H�H�H");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���{��ł���");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�A��܂�");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����[���ƃL�~�}�W�L�`�ł��ˁ[");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�n�C�����ł����ǂȂɂ��O�O");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����߂�ǂ���");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==17){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 24;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����[����J�{�`����������(�΂�");
					}
				}
			}
		}
		else if(num==3){
			Talk[chara][num].talk_num = 10;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����������������ӂ����ނӂ�����");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 22;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܁[�[�[");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�ŁA���̑O�ɒN���ɉ�����H");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A��������������");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������[�[");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂��������I�I�H�E���܂��C�~�t������");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܁[�܁[�A�����{��Ȃ��Ł`");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��������ŃJ���E���ێ悵�Ȃ����i�΂�");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�C���C���}����̂̓J���V�E���ł�");
					}
				}
				else if(i==8 || i==9){
					if(i==9)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 23;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���q�ɏ������_���[�[�[�[");
					}
				}
			}
		}
		else if(num==4){
			Talk[chara][num].talk_num = 20;
			Talk[chara][num].Nimg = 18;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E�E�E�E");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�l�h��������Ł[��");
					}
				}
				else if(i==3){
					Talk[chara][num].flag[i] = 1;//���l�o��A�X�L�b�v�s��
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = -1;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���{��ł���");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "(���ԯ");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���̃h�����߂��`");
					}
				}
				else if(i==6){
					Talk[chara][num].bName[i] = true;
					Talk[chara][num].Pimg[i][0] = 36;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�d���Ȃ�����Ȃ��ł���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��͐��܂�t���Ă̂��̂ł�����");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�߰����");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���[�A�L�[�{�[�h�����ɒu�������ȁ[");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 28;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�L�[�{�[�h�N���b�V�������(�m�m");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ł��[�A�������ɗ��q�������[�H");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A�l�����͕������s���Ă܂���");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����[�A�Ȃ�ł��S�W���Ə�����");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�����ň��������z������Ƃ�");
					}
				}
				else if(i==14){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "������͂����̎G���₯�ǂ�(�΂�");
					}
				}
				else if(i==15){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ق��A���̔p�l�W�c�̒���");
					}
				}
				else if(i==16){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�ǂ�ȓz�������̂ł����H");
					}
				}
				else if(i==17){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���[�ˁ[�A�m���Ă邯�ǂ߂�ǂ�");
					}
				}
				else if(i==18){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�͂��H");
					}
				}
				else if(i==19){
					Talk[chara][num].flag[i] = 7;//�a�f�l�J�n �� �G����������
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܂��͔��낤���H");
					}
				}
			}
		}
		else if(num==5){
			Talk[chara][num].talk_num = 17;
			Talk[chara][num].Nimg = -1;
			for(int i=0;i<Talk[chara][num].talk_num;i++){
				if(i==0){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��I������������I�I�I");
					}
				}
				else if(i==1){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "����͋��v�����₩��ȁ[(�m");
					}
				}
				else if(i==2){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��{�I�ɂւ�����(�m�m");
					}
				}
				else if(i==3){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�������������I�I�I");
					}
				}
				else if(i==4){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 30;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����ꂽ�߰����");
					}
				}
				else if(i==5){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�E�E�E��ŁA");
					}
				}
				else if(i==6){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��ł�ł�ł�����������");
					}
				}
				else if(i==7){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�Ⴄ�I�N�Ȃ�ł����A");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�S�W���Ə����ɏ������̂�");
					}
				}
				else if(i==8){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�����A�A����");
					}
				}
				else if(i==9){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�܁[�A�����ő҂��Ă������");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "�g���̂߂ł����F�����l");
					}
				}
				else if(i==10){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�g���H");
					}
				}
				else if(i==11){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�K���ɘb���i�߂Ƃ���");
						else if(j==1)	sprintf(Talk[chara][num].speak[i][j], "��͂܁[��肭�s����낤��");
					}
				}
				else if(i==12){
					Talk[chara][num].Pimg[i][0] = 38;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c�ǂ��������ƂȂ�ł����H");
					}
				}
				else if(i==13){
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 1;
					Talk[chara][num].Eactive[i][0] = 0;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 0;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "���Ⴀ�t���������ɍ������Ă���(�΂�");
					}
				}
				else if(i==14){
					Talk[chara][num].flag[i] = 5;//�v���C���[����������
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "��A���储��");
					}
				}
				else if(i==15 || i==16){
					if(i==15)	Talk[chara][num].flag[i] = 5;//�v���C���[����������
					if(i==16)	Talk[chara][num].flag[i] = 4;//�X�e�[�W�N���A
					Talk[chara][num].Pimg[i][0] = 37;
					Talk[chara][num].Eimg[i][0] = 29;
					Talk[chara][num].Pactive[i][0] = 0;
					Talk[chara][num].Eactive[i][0] = 1;
					for(int j=0;j<MAX_LINE;j++){
						Talk[chara][num].speak_color[i][j] = 1;
						if(j==0)	sprintf(Talk[chara][num].speak[i][j], "�c���[��A���ς�炸�͂߂Ȃ��l����");
					}
				}
			}
		}
	}

	return;
}

void TLoad(){
	bTalk = false;
	TalkNum = 0;
	NowNum = 0;
	TalkCount = 0;
	TalkCount2 = 0;
	TalkCount3 = 0;
	for(int k=0;k<CHARA_NUM;k++){
		for(int i=0;i<TALK_NUM;i++){
			Talk[k][i].talk_num = 0;
			Talk[k][i].Nimg = -1;
			Talk[k][i].Ncount = 0;
			for(int j=0;j<MAX_TALK;j++){
				Talk[k][i].flag[j] = 0;
				Talk[k][i].bName[j] = false;
				for(int a=0;a<MAX_LINE;a++){
					Talk[k][i].speak_color[j][a] = 0;
					for(int b=0;b<MAX_CHAR;b++){
						Talk[k][i].speak[j][a][b] = '\0';
					}
				}
				for(int a=0;a<MAX_PLAYER;a++){
					Talk[k][i].Pimg[j][a] = -1;
					Talk[k][i].Pimg_count[a] = 0;
					Talk[k][i].Pactive[j][a] = 0;
					Talk[k][i].Pactive_count[a] = 0;
				}
				for(int a=0;a<MAX_ENEMY;a++){
					Talk[k][i].Eimg[j][a] = -1;
					Talk[k][i].Eimg_count[a] = 0;
					Talk[k][i].Eactive[j][a] = 0;
					Talk[k][i].Eactive_count[a] = 0;
				}
			}
		}
	}

	for(int chara=0;chara<CHARA_NUM;chara++){
		if(chara==0)		TLoad0();
		else if(chara==1)	TLoad1();
		else if(chara==2)	TLoad2();
		else if(chara==3)	TLoad3();
		else if(chara==4)	TLoad4();
		else if(chara==5)	TLoad5();
	}

	return;
}

void TReset(){
	bTalk = false;
	TalkNum = 0;
	NowNum = 0;
	TalkCount = 0;
	TalkCount2 = 0;
	TalkCount3 = 0;

	return;
}

void TDraw(){
	if(bTalk==true){
		TMove(Player[0].chara,TalkNum);
		if(NowNum>=Talk[Player[0].chara][TalkNum].talk_num){
			bTalk = false;
			return;
		}

		for(int i=0;i<MAX_PLAYER;i++){
			if(Talk[Player[0].chara][TalkNum].Pimg[NowNum][i]!=-1){
				if(Talk[Player[0].chara][TalkNum].Pimg_count[i]<40)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*Talk[Player[0].chara][TalkNum].Pimg_count[i]);
				else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int bright = 255-4*(40-Talk[Player[0].chara][TalkNum].Pactive_count[i]);
				SetDrawBright(bright, bright, bright);
				int sx,sy;
				GetGraphSize(gCatin[Talk[Player[0].chara][TalkNum].Pimg[NowNum][i]], &sx, &sy);
				float x = 40+sx/2 - 0.03*pow(Talk[Player[0].chara][TalkNum].Pactive_count[i]-40,2);
				if(TalkCount3>0)	x -= TalkCount3*(sx+30)/120;
				float y = 552-sy/2 + 0.2*pow(Talk[Player[0].chara][TalkNum].Pimg_count[i]-40,2);
				if(GetSkip())	DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Talk[Player[0].chara][TalkNum].Pimg[NowNum][i]], TRUE, FALSE);
			}
		}
		for(int i=0;i<MAX_ENEMY;i++){
			if(Talk[Player[0].chara][TalkNum].Eimg[NowNum][i]!=-1){
				if(Talk[Player[0].chara][TalkNum].Eimg_count[i]<40)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*Talk[Player[0].chara][TalkNum].Eimg_count[i]);
				else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int bright = 255-4*(40-Talk[Player[0].chara][TalkNum].Eactive_count[i]);
				SetDrawBright(bright, bright, bright);
				int sx,sy;
				GetGraphSize(gCatin[Talk[Player[0].chara][TalkNum].Eimg[NowNum][i]], &sx, &sy);
				float x = 400-sx/2 + 0.03*pow(Talk[Player[0].chara][TalkNum].Eactive_count[i]-40,2);
				if(TalkCount3>0)	x += TalkCount3*(sx+30)/120;
				float y = 552-sy/2 + 0.2*pow(Talk[Player[0].chara][TalkNum].Eimg_count[i]-40,2);
				if(GetSkip())	DrawRotaGraphF(x+shake_x, y+shake_y, 1.0, 0, gCatin[Talk[Player[0].chara][TalkNum].Eimg[NowNum][i]], TRUE, FALSE);
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawBright(10,10,10);
		if(GetSkip()){
			if(TalkCount<50)	DrawExtendGraph(30, 400, 410, 400+1.2*TalkCount, gGage, TRUE);
			else			DrawExtendGraph(30, 400, 410, 460, gGage, TRUE);
		}
		SetDrawBright(255,255,255);
		if(TalkCount2<10)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,25.5*TalkCount2);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<2;i++){
			int color;
			if(Talk[Player[0].chara][TalkNum].speak_color[NowNum][i]==0)		color = GetColor(255,150,150);
			else if(Talk[Player[0].chara][TalkNum].speak_color[NowNum][i]==1)	color = GetColor(150,150,255);
			DrawSt(40, 410+20*i, GetColor(255,255,255), color, talk_font, Talk[Player[0].chara][TalkNum].speak[NowNum][i]);
		}
		
		if(Talk[Player[0].chara][TalkNum].Ncount>0){
			if(Talk[Player[0].chara][TalkNum].Ncount<40)		SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*Talk[Player[0].chara][TalkNum].Ncount);
			else if(Talk[Player[0].chara][TalkNum].Ncount<160)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			else if(Talk[Player[0].chara][TalkNum].Ncount<200)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,6.375*(200-Talk[Player[0].chara][TalkNum].Ncount));
			else					SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
			int sx,sy;
			GetGraphSize(gCatin[Talk[Player[0].chara][TalkNum].Nimg], &sx, &sy);
			if(GetSkip())	DrawRotaGraphF(400-sx/2+shake_x, 380-sy/2+shake_y, 1.0, 0, gCatin[Talk[Player[0].chara][TalkNum].Nimg], TRUE, FALSE);
			Talk[Player[0].chara][TalkNum].Ncount++;
		}
		
		TalkCount++;
		if(TalkCount>=50)	TalkCount2++;
	}
	SetDrawBright(255,255,255);
	
	return;
}

void TMove(int chara, int i){
	if(TalkCount2>0){
		for(int j=0;j<MAX_PLAYER;j++){
			if(Talk[chara][i].Pimg[NowNum][j]!=-1){
				if(j==0 && Talk[chara][i].flag[NowNum]==5){
					if(Talk[chara][i].Pimg_count[j]>0)	Talk[chara][i].Pimg_count[j]--;//�v���C���[����������
				}
				else if(Talk[chara][i].Pimg_count[j]<40)	Talk[chara][i].Pimg_count[j]++;
				if(Talk[chara][i].Pactive[NowNum][j]==1){
					if(Talk[chara][i].Pactive_count[j]<40)	Talk[chara][i].Pactive_count[j]++;
				}
				else if(Talk[chara][i].Pactive[NowNum][j]==0){
					if(Talk[chara][i].Pactive_count[j]>0)	Talk[chara][i].Pactive_count[j]--;
				}
			}
                }
		for(int j=0;j<MAX_ENEMY;j++){
			if(Talk[chara][i].Eimg[NowNum][j]!=-1){
				if(j==0 && Talk[chara][i].flag[NowNum]==6){
					if(Talk[chara][i].Eimg_count[j]>0)	Talk[chara][i].Eimg_count[j]--;//�G����������
				}
				else if(Talk[chara][i].Eimg_count[j]<40)	Talk[chara][i].Eimg_count[j]++;
				if(Talk[chara][i].Eactive[NowNum][j]==1){
					if(Talk[chara][i].Eactive_count[j]<40)	Talk[chara][i].Eactive_count[j]++;
				}
				else if(Talk[chara][i].Eactive[NowNum][j]==0){
					if(Talk[chara][i].Eactive_count[j]>0)	Talk[chara][i].Eactive_count[j]--;
				}
			}
                }
		
		
		if(Talk[chara][i].flag[NowNum]==3 || Talk[chara][i].flag[NowNum]==7){
			if(TalkCount3==120){
				NowNum++;
				TalkCount2 = -1;
			}
			TalkCount3++;
		}
		if(TalkCount2==1){
			if(Talk[chara][i].bName[NowNum]==true)	Talk[chara][i].Ncount = 1;
			if(i==0){
				if(Talk[chara][i].flag[NowNum]==1){
					BMake(-100, 150, 1, 2, atack); 
				}
				else if(Talk[chara][i].flag[NowNum]==2 || Talk[chara][i].flag[NowNum]==7){
					MuPlayBgm(3);
				}
			}
			else if(i==2){
				if(Talk[chara][i].flag[NowNum]==1){
					BMake(530, 180, 4, 3, atack); 
				}
				else if(Talk[chara][i].flag[NowNum]==2 || Talk[chara][i].flag[NowNum]==7){
					MuPlayBgm(5);
				}
			}
			else if(i==4){
				if(Talk[chara][i].flag[NowNum]==1){
					BMake(-100, CENTER_Y, 5, 4, atack); 
				}
				else if(Talk[chara][i].flag[NowNum]==2 || Talk[chara][i].flag[NowNum]==7){
					MuPlayBgm(7);
				}
			}
		}

		int up,down,left,right,shot,bomb,slow,skip,pause;
		if(replay_play==false)	GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
		else			RMain(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause,false);
		if(Talk[chara][i].flag[NowNum]!=1 && Talk[chara][i].flag[NowNum]!=3 && Talk[chara][i].flag[NowNum]!=7 && Talk[chara][i].flag[NowNum]!=4 && TalkCount2>5){
			if(shot==1 || skip>0 || TalkCount2==360){
				NowNum++;
				TalkCount2 = -1;
			}
		}

		if(Talk[chara][i].flag[NowNum]==4){
			//�X�e�[�W�N���A
			Ccount = 1;
			TalkCount2 = 10;
		}
	}
	
	return;
}

void TMake(int num){
	SESDelete(3);
	bTalk = true;
	TalkNum = num;
	NowNum = 0;
	TalkCount = 0;
	TalkCount2 = 0;
	TalkCount3 = 0;
	for(int i=0;i<MAX_PLAYER;i++){
		Talk[Player[0].chara][num].Pimg_count[i] = 0;
		Talk[Player[0].chara][num].Pactive_count[i] = 0;
	}
	for(int i=0;i<MAX_ENEMY;i++){
		Talk[Player[0].chara][num].Eimg_count[i] = 0;
		Talk[Player[0].chara][num].Eactive_count[i] = 0;
	}
	Talk[Player[0].chara][num].Ncount = 0;
		
	return;
}