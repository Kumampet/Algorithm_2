#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a < b) ? a : b)

int G[8][8];
int b_num=0;
int v;

void init(){
  int i, j;
  for(i=0; i<v; i++){
    for(j=0; j<v; j++){
      G[i][j]=0;
    }
  }
}

void warshal_floid(int n){
  int i,j,k;
  for(k=0; k<n; k++){
    for(i=0; i<n; i++){
      for(j=0; j<n; j++){
	G[i][j]=min(G[i][j], G[i][k] + G[k][j]);
      }
    }
  }
}

int main(){
  int i,j;
  char from,to;

  init();
  
  printf("Input vaertex number.\n");
  scanf("%d",&v);
  printf("Input branch number.\n");
  scanf("%d",&b_num);

  for(i=0; i<b_num; i++){
    printf("Inupt From(char) and To(char).\n");
    scanf(" %c %c",&from,&to);
    printf("From:%d\n",(int)from);
    G[from-10][to-10]=1;
  }

  warshal_floid(v);

  for(i=0;i<v;i++){
    for(j=0; j<v; j++){
      if(G[i][j]!=0){
	printf("From %d to %d\n",(char)i+'a',(char)j+'a');
      }
    }
  }
  return 0;
}