#include"cstdio"
#include"cstdlib"
#include"time.h"
#include <algorithm>    // std::next_permutation, std::sort

using namespace std;

struct piece{
	int row[4],col[4];
	int color;
};

void pop(struct piece *out);
void move(struct piece *out,char kb);
void rotate(struct piece *out,char kb);

void pop(struct piece *out){
	switch(rand()%7){
		case 0:								//――――
			out->row[0]=0;
			out->col[0]=3;
			out->row[1]=0;
			out->col[1]=4;
			out->row[2]=0;
			out->col[2]=5;
			out->row[3]=0;
			out->col[3]=6;
			out->color=11;
			break;
		case 1:								//――
			out->row[0]=0;					//――
			out->col[0]=4;
			out->row[1]=0;
			out->col[1]=5;
			out->row[2]=1;
			out->col[2]=4;
			out->row[3]=1;
			out->col[3]=5;
			out->color=14;
			break;
		case 2:								//  ―
			out->row[0]=0;					//―――
			out->col[0]=5;
			out->row[1]=1;
			out->col[1]=4;
			out->row[2]=1;
			out->col[2]=5;
			out->row[3]=1;
			out->col[3]=6;
			out->color=13;
			break;
		case 3:								//――
			out->row[0]=0;					//  ――
			out->col[0]=4;
			out->row[1]=0;
			out->col[1]=5;
			out->row[2]=1;
			out->col[2]=5;
			out->row[3]=1;
			out->col[3]=6;
			out->color=12;
			break;
		case 4:								//  ――
			out->row[0]=0;					//――
			out->col[0]=5;
			out->row[1]=0;
			out->col[1]=6;
			out->row[2]=1;
			out->col[2]=5;
			out->row[3]=1;
			out->col[3]=4;
			out->color=10;
			break;
		case 5:								//―
			out->row[0]=0;					//―――
			out->col[0]=4;
			out->row[1]=1;
			out->col[1]=4;
			out->row[2]=1;
			out->col[2]=5;
			out->row[3]=1;
			out->col[3]=6;
			out->color=9;
			break;
		case 6:								//    ―
			out->row[0]=0;					//―――
			out->col[0]=6;
			out->row[1]=1;
			out->col[1]=4;
			out->row[2]=1;
			out->col[2]=5;
			out->row[3]=1;
			out->col[3]=6;
			out->color=15;
			break;
	}
}

void move(struct piece *out,char kb){
	int a;
	switch(kb){
		case 'a':
			for(a=0;a<4;a++)out->col[a]-=1;
			break;
		case 'A':
			for(a=0;a<4;a++)out->col[a]-=1;
			break;
		case 'd':
			for(a=0;a<4;a++)out->col[a]+=1;
			break;
		case 'D':
			for(a=0;a<4;a++)out->col[a]+=1;
			break;
		case 's':
			for(a=0;a<4;a++)out->row[a]+=1;
			break;
		case 'S':
			for(a=0;a<4;a++)out->row[a]+=1;
			break;
		case EOF:
			for(a=0;a<4;a++)out->row[a]+=1;
			break;
	}
}

void rotate(struct piece *out,char kb){
	int a,tmp_row,tmp_col;
	switch(kb){
		case'j':							//0 1
			for(a=0;a<4;a++){				//-1 0
				if(a==2)continue;
				tmp_row=out->row[a];
				tmp_col=out->col[a];
				out->row[a]=(-1)*(tmp_col-out->col[2])+out->row[2];
				out->col[a]=(tmp_row-out->row[2])+out->col[2];
			}
			break;
		case'J':							//0 1
			for(a=0;a<4;a++){				//-1 0
				if(a==2)continue;
				tmp_row=out->row[a];
				tmp_col=out->col[a];
				out->row[a]=(-1)*(tmp_col-out->col[2])+out->row[2];
				out->col[a]=(tmp_row-out->row[2])+out->col[2];
			}
			break;
		case'k':							//0 -1
			for(a=0;a<4;a++){				//1 0
				if(a==2)continue;
				tmp_row=out->row[a];
				tmp_col=out->col[a];
				out->row[a]=(tmp_col-out->col[2])+out->row[2];
				out->col[a]=(-1)*(tmp_row-out->row[2])+out->col[2];
			}
			break;
		case'K':							//0 -1
			for(a=0;a<4;a++){				//1 0
				if(a==2)continue;
				tmp_row=out->row[a];
				tmp_col=out->col[a];
				out->row[a]=(tmp_col-out->col[2])+out->row[2];
				out->col[a]=(-1)*(tmp_row-out->row[2])+out->col[2];
			}
			break;
	}
}

