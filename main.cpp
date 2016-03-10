#include"cstdio"
#include"cstdlib"
#include"conio.h" 							//kbhit()
#include".\\function\\print.h"				//gotoyx() SetColor() change_unicode_print() print_map() mop() predict() 
											//preview() keep()
											//piece.h pop() move() rotate()
											//map.h map_ori() map_paste() map_mop() map_check() rotate_check()
using namespace std;

void line(struct map *map,struct piece *in,int *score);
int end(struct piece in);

int main(){
	srand(time(NULL));
	SYSTEMTIME sys;
	FILE *model_in;
	model_in=freopen(".\\model\\model.txt","r",stdin);
	
	int row,col;
	int a,b;
	
	fscanf(model_in,"%d %d",&row,&col);
	fgetchar();
	for(a=0;a<row;a++){
		for(b=0;b<col;b++){
			change_unicode_print(fgetchar());
		}
		printf("\n");
		fgetchar();
	}
	
	fclose(model_in);
	
	struct piece in,pred,prev,kee;
	struct map map;
	int piece_exist=1,score=0,kee_check=0;
	char kbtmp='*';
	
	map_ori(&map);
	
	gotoyx(1,2);
	printf("score:%d",score);
	
	pop(&prev);
	
	while(1){
		if(piece_exist){
			in=prev;
			pop(&prev);
			preview(in,prev);
			map_paste(&map,&in,0);
			print_map(&in);
			piece_exist=0;
			pred=in;
			predict(in,map,&pred);
		}
		if(kbhit()){
			kbtmp=getch();
			if(kbtmp=='j'||kbtmp=='J'||kbtmp=='k'||kbtmp=='K'){
				if(rotate_check(map,in,kbtmp)){
					mop(&in);
					map_mop(&map,&in);
					rotate(&in,kbtmp);
					predict(in,map,&pred);
					map_paste(&map,&in,0);
					print_map(&in);
				}
			}else if(kbtmp=='l'||kbtmp=='L'){
				keep(&prev,&kee,kee_check);
				kee_check=1;
			}else if(kbtmp==' '){
				mop(&in);
				map_mop(&map,&in);
				while(map_check(map,in,EOF))move(&in,EOF);
				predict(in,map,&pred);
				map_paste(&map,&in,1);
				print_map(&in);
				piece_exist=1;
				line(&map,&in,&score);
				gotoyx(1,2);
				printf("score:%d",score);
				if(end(in)){
					gotoyx(2,2);
					printf("end\n");
					gotoyx(42,0);
					break;
				}
				continue;
			}else if(map_check(map,in,kbtmp)){
				mop(&in);
				map_mop(&map,&in);
				move(&in,kbtmp);
				predict(in,map,&pred);
				map_paste(&map,&in,0);
				print_map(&in);
			}
			kbtmp='*';	
		}
		GetLocalTime(&sys);
		if(sys.wMilliseconds%500==0){
			if(map_check(map,in,EOF)){
				mop(&in);
				map_mop(&map,&in);
				move(&in,EOF);
				map_paste(&map,&in,0);
				print_map(&in);
			}else{
				map_paste(&map,&in,1);
				piece_exist=1;
				line(&map,&in,&score);
				gotoyx(1,2);
				printf("score:%d",score);
				if(end(in)){
					gotoyx(2,2);
					printf("end\n");
					gotoyx(42,0);
					break;
				}
			}	
		}
	}
	system("PAUSE");
	return 0;
}

void line(struct map *map,struct piece *in,int *score){
	int a,b,c,d;
	for(c=0;c<20;c++){
		for(b=0;b<10;b++){
			if(map->map[c][b]=='.')break;
			if(b==9){
				*(score)+=1;
				/*SetColor(5,0);
				for(a=0;a<10;a++){
					map->map[c][a]='.';
					gotoyx(c*2+1,a*4+2);
					printf("◆◆");
					gotoyx(c*2+2,a*4+2);
					printf("◆◆");
				}
				_sleep(500);*/
				SetColor(0,0);
				for(a=0;a<10;a++){
					map->map[c][a]='.';
					gotoyx(c*2+1,a*4+2);
					printf("■■");
					gotoyx(c*2+2,a*4+2);
					printf("■■");
				}
				for(a=c-1;a>=0;a--){
					for(d=0;d<10;d++){
						if(map->map[a][d]!='.'){
							map->map[a+1][d]=map->map[a][d];
							map->map[a][d]='.';
							SetColor(0,0);
							gotoyx(a*2+1,d*4+2);
							printf("■■");
							gotoyx(a*2+2,d*4+2);
							printf("■■");
							SetColor(map->map[a+1][d],0);
							gotoyx((a+1)*2+1,d*4+2);
							printf("■■");
							gotoyx((a+1)*2+2,d*4+2);
							printf("■■");
						}
					}
				}
				SetColor(7,0);
				c--;
			}
		}
	}
}

int end(struct piece in){
	int a;
	for(a=0;a<4;a++){
		if(in.row[a]<=2)return 1;
	}
	return 0;
}
/*
產生順序 
rotate check
(x)mop all problem
time replace number
end
收藏圖形 
*/
