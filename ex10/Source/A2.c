//チェス盤が無限に沸く現象に名前を付けよう

#include <stdio.h>
#include <stdlib.h>

#define N 8
#define FREE 0
#define NOT_FREE -1
#define NODATA -10

//row->行
//col->列
int row[N];
int col[N];
int dpos[N*2];
int dneg[N*2];
int *mark;
int k;

void init(){
  int i,j;

  mark = (int*)malloc(sizeof(int) * k);
  for(i=0; i<N; i++){
    row[i]=NODATA;
    col[i]=NODATA;
  }
}

void printBoard(){
  int i,j;

  for(i=0; i<N; i++){
    if(row[i]>-1){
      for(j=0; j<N; j++){
        if(j==row[i]){
          printf("%c",'Q');
        }else printf("%c",'.');
        if(j!=N) printf(" ");
      }
    }else{
      for(j=0; j<N; j++){
        printf("%c",'.');
        if(j!=N) printf(" ");
      }
    }
    printf("\n");
  }
}

void putQueen(int i){
  int j;

  if(i==N){
    printBoard();
    printf("-------------------------\n");
    return;
  }

  for(j=0; j<k; j++){
    if(mark[j]==i){
      putQueen(i+1);
    }
  }
  for(j=0; j<N; j++){
    if(
      (col[j]==NOT_FREE)||
      (dpos[i+j]==NOT_FREE)||
      (dneg[i-j+N-1]==NOT_FREE)
    ){
      continue;
    }
    row[i] = j;
    col[j] = NOT_FREE;
    dpos[i+j] = NOT_FREE;
    dneg[i-j+N-1] = NOT_FREE;
    //printf("row[%d]:j=%d,col[%d]:%d,dpos[%d]:%d,dneg[%d]:%d\n",i,j,j,col[j],i+j,dpos[i+j],i-j+N-1,dneg[i-j+N-1]);
    putQueen(i+1);
    col[j] = FREE;
    dpos[i+j] = FREE;
    dneg[i-j+N-1] = FREE;
  }
}

int main() {
  int c,r;
  int i;

  scanf("%d",&k);
  init();
  for(i=0; i<k; i++){
    scanf("%d%d",&c,&r);
    mark[i] = r;
    row[r]=c;
    col[c] = NOT_FREE;
    dpos[r+c] = NOT_FREE;
    dneg[r-c+N-1] = NOT_FREE;
  }
  putQueen(0);
  //printBoard();

  //free(r);
  return 0;
}
