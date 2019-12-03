#include <stdio.h>
#include <stdlib.h>

#define N 8
#define SIZE 8
#define FREE 0
#define NOT_FREE -1

typedef struct{
  char queen;
  int attack;
  int dpos;
  int dneg;
}Board;

Board B[SIZE][SIZE];
//int queen_sum;

//---------------------------------------------
//-------チェス盤の初期化-------
void init(){
  int i,j;

  for(j=0; j<SIZE; j++){//y方向
    for(i=0; i<SIZE; i++){//x方向
      B[i][j].queen = '.';
      B[i][j].attack = FREE;
      B[i][j].dpos = i+j;
      B[i][j].dneg = i-j+N-1;
    }
  }
}

//------チェス盤の表示-------
void printBoard(){
  int i,j;

  for(j=0; j<SIZE; j++){
    for(i=0; i<SIZE; i++){
      printf("%s",B[i][j].queen);
      if(j!=SIZE)printf(" ");
    }
    printf("\n");
  }
}

//-------初期クイーンの管理--------
void putDefQueen(int x,int y){
  int i,j;

  B[x][y].queen = 'Q';//指定位置に配置

  for(j=0; j<SIZE; j++){//y方向
    for(i=0; i<SIZE; i++){//x方向
      //配置位置基準の攻撃範囲にフラグを立てる作業
      if(i==x){
        B[i][j].attack = NOT_FREE;
      }
      if(j==y){
        B[i][j].attack = NOT_FREE;
      }
      if(B[i][j].dpos == B[x][y].dpos){
        B[i][j].attack = NOT_FREE;
      }
      if(B[i][j].dneg == B[x][y].dneg){
        B[i][j].attack = NOT_FREE;
      }
    }
  }
}

void putQueen(int j){
  int i;

  if(j==N){
    printBoard();
    return;
  }

  for(i=0; i<SIZE; i++){
    if(
      (B[i][j].attack == NOT_FREE)||
      (B[i][j].dpos == NOT_FREE)||
      (B[i][j].dneg == NOT_FREE)
    ){
      //printf("countinue!\n");
      continue;
    }
    //printf("%d,%d\n",i,j );
    B[i][j].queen = 'Q';
    //queen_sum++;
    B[i][j].attack = NOT_FREE;
    B[i][j].dpos = NOT_FREE;
    B[i][j].dneg = NOT_FREE;
    putQueen(j+1);
    B[i][j].queen = '.';
    //queen_sum--;
    B[i][j].attack = FREE;
    B[i][j].dpos = FREE;
    B[i][j].dneg = FREE;
  }
}

int main() {
  int k;
  int r, c;
  int i,j;
  int a,b;

  init();
  scanf("%d",&k);//初期クイーンの数
  //queen_sum = k;//クイーンの総数を初期化
  for(i=0; i<k; i++){//クイーンの初期数分読み込む
    scanf("%d%d",&r, &c);
    putDefQueen(r,c);//初期クイーンの配置
  }
  //-----行を頭から見て残りのqueenの配置-------
  for(i=0; i<SIZE; i++){
    putQueen(i);
  }
  //printBoard();
  return 0;
}
