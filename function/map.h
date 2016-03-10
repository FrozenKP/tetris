#include"cstdio"
#include"cstdlib"
#include"piece.h"

using namespace std;

void map_ori(struct map* in);
void map_paste(struct map *map,struct piece *in,int mode);
void map_mop(struct map *map,struct piece *in);
int map_check(struct map map,struct piece in,char kb);
int rotate_check(struct map map,struct piece in,char kb);

struct map{
	char map[40][20];
	int row=40,col=20;
};

void map_ori(struct map* in){
	int a,b;
	for(a=in->row;a>0;a--){
		for(b=in->col;b>0;b--){
			in->map[a-1][b-1]='.';
		}
	}
}

void map_paste(struct map *map,struct piece *in,int mode){
	int a;
	switch(mode){
		case 0:
			for(a=0;a<4;a++)map->map[in->row[a]][in->col[a]]='x';
			break;
		case 1:
			for(a=0;a<4;a++)map->map[in->row[a]][in->col[a]]=in->color;
			break;
	}
}

void map_mop(struct map *map,struct piece *in){
	int a;
	for(a=0;a<4;a++)map->map[in->row[a]][in->col[a]]='.';
}

int map_check(struct map map,struct piece in,char kb){
	int a;
	map_mop(&map,&in);
	for(a=0;a<4;a++){
		if(kb==EOF||kb=='s'||kb=='S'){
			if(in.row[a]+1>=20)return 0;
			if(map.map[in.row[a]+1][in.col[a]]!='.')return 0;
		}else if(kb=='a'||kb=='A'){
			if(in.col[a]-1<0)return 0;
			if(map.map[in.row[a]][in.col[a]-1]!='.')return 0;
		}else if(kb=='d'||kb=='D'){
			if(in.col[a]+1>=10)return 0;
			if(map.map[in.row[a]][in.col[a]+1]!='.')return 0;
		}
	}
	/*free(&in);
	free(&map);*/
	return 1;
}

int rotate_check(struct map map,struct piece in,char kb){
	int a;
	map_mop(&map,&in);
	rotate(&in,kb);
	for(a=0;a<4;a++){
		if(in.row[a]<0||in.row[a]>=20)return 0;
		else if(in.col[a]<0||in.col[a]>=10)return 0;
		else if(map.map[in.row[a]][in.col[a]]!='.')return 0;
	}
	/*free(&in);
	free(&map);*/
	return 1;
}



