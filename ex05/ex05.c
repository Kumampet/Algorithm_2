#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 1000
#define TRUE 1
#define FALSE 0

int D[SIZE][SIZE];
int COST[SIZE];
int V[SIZE];
int N;
char USE[SIZE];

int dijkstra(int s, int g){
  int min, target;
  int i,neear;
  COST[s] = 0;

  while(1){
    min = INT_MAX;
    for(i=0; i<N; i++){
      if(!USE[i] && min > COST[i]){
	min = COST[i];
	target = i;
      }
    }

    if(target == g){
      return COST[g];
    }

    for(neear = 0; neear<N; neear++){
      if(COST[neear]>D[target][neear] + COST[target]){
	COST[neear] = D[target][neear] + COST[target];
	V[neear] = target;
      }
    }
    USE[target] = TRUE;
  }
}

int main(){
  int r;
  int a,b,l;
  int s,d;

  int i,j,node;
  for(i=0; i<SIZE; i++){
    COST[i] = INT_MAX;
    USE[i] = FALSE;
    V[i] = -1;
    for(j=0; j<SIZE; j++){
      D[i][j] = INT_MAX;
    }
  }

  printf("バーテックスの数を入力：input vertex number\n");
  scanf("%d",&N);
  printf("ルートの数の入力：Root number\n");
  scanf("%d",&r);

  for(i=0; i<r; i++){
    printf("道の両端のバーテックスとその道の距離を入力\n");
    scanf("%d %d %d",&a,&b,&l);
    D[a][b]=l;
  }
  scanf("%d %d",&s,&d);

  printf("距離：%d\n",dijkstra(s,d));

  node = d;
  printf("%d",node);
  while(1){
    node = V[node];
    printf(" -> %d",node);
    if(node == s){
      break;
    }
  }

  return 0;
}
