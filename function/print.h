#include"cstdio"
#include"cstdlib"
#include<windows.h>  			//gotoyx	setcolor()
#include"map.h"

using namespace std;

void gotoyx(int ypos, int xpos);
void SetColor(int f=7,int b=0);
void change_unicode_print(char in);
void mop(struct piece *in);
void predict(struct piece in,struct map map,struct piece *pred);
void preview(struct piece in,struct piece prev);
void keep(struct piece *prev,struct piece *kee,int check);

void gotoyx(int ypos, int xpos){
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void SetColor(int f,int b){
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

void change_unicode_print(char in){
	switch(in){
		case '#':
			printf("―");
			break;
		case ' ':
			printf("  ");
			break;
	}
}

void print_map(struct piece *in){
	SetColor(in->color,0);
	int a;
	for(a=0;a<4;a++){
		if(in->row[a]<2&&in->col[a]<10)continue;
		gotoyx(in->row[a]*2+1,in->col[a]*4+2);
		printf("――");
		gotoyx(in->row[a]*2+2,in->col[a]*4+2);
		printf("――");
	}
	SetColor(7,0);
}

void mop(struct piece *in){
	SetColor(0,0);
	int a;
	for(a=0;a<4;a++){
		if(in->row[a]<2&&in->col[a]<10)continue;
		gotoyx(in->row[a]*2+1,in->col[a]*4+2);
		printf("――");
		gotoyx(in->row[a]*2+2,in->col[a]*4+2);
		printf("――");
		
	}
	SetColor(7,0);
}

void predict(struct piece in,struct map map,struct piece *pred){
	mop(pred);
	*pred=in;
	while(map_check(map,*pred,EOF))move(pred,EOF);
	int a;
	for(a=0;a<4;a++){
		if(pred->row[a]<2)continue;
		gotoyx(pred->row[a]*2+1,pred->col[a]*4+2);
		printf("ーー");
		gotoyx(pred->row[a]*2+2,pred->col[a]*4+2);
		printf("ーー");
	}
}

void preview(struct piece in,struct piece prev){
	int a;
	for(a=0;a<4;a++){
		in.row[a]+=1;
		in.col[a]+=8;
		prev.row[a]+=1;
		prev.col[a]+=8;
	}
	mop(&in);
	print_map(&prev);
}

void keep(struct piece *prev,struct piece *kee,int check){
	int a;
	for(a=0;a<4;a++){
		kee->row[a]+=6;
		kee->col[a]+=8;
		prev->row[a]+=1;
		prev->col[a]+=8;
	}
	mop(prev);
	if(check==1)mop(kee);
	else{
		pop(kee);
		for(a=0;a<4;a++){
			kee->row[a]+=6;
			kee->col[a]+=8;
		}
	}
	struct piece tmp;
	tmp=*prev;
	*prev=*kee;
	*kee=tmp;
	for(a=0;a<4;a++){
		kee->row[a]+=5;
		prev->row[a]-=5;
	}
	print_map(prev);
	print_map(kee);
	for(a=0;a<4;a++){
		kee->row[a]-=6;
		kee->col[a]-=8;
		prev->row[a]-=1;
		prev->col[a]-=8;
	}
}
