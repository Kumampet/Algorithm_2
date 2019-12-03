#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
/*
タイムスタンプ d[v]: v を最初に発見した発見時刻を記録します。
タイムスタンプ f[v]: v の隣接リストを調べ終えた完了時刻を記録します。
*/
typedef struct{
  int id;//要素の中身
  int k;//子供の数
  int *v;//kで動的に確保した子供のID
  int color;//巡回判定の色
  int dscv;//最初に発見したステップ数が入る
  int fin;//巡回終了したステップ数が入る
}Graph;

Graph *G;
int n;
int **Adj;
int t;


void getDef(){
  int i,j;

  Adj = malloc(sizeof(int*) * (n+1));
  for(i=1;i<=n;i++){
    Adj[i] = malloc(sizeof(int) * (n+1));
    for(j=1;j<=n;j++){
      Adj[i][j] = 0;
    }
  }
}

void printer(){
  int i, j;

  for(i=1; i<=n; i++){
    printf("G[ID]: %d Discover Time: %d Finished Time: %d\n",G[i].id, G[i].dscv, G[i].fin);
  }
}

void visit(int id){
  int i;

  //バーテックスの探索を判定する
  G[id].color = GRAY;//探索準備
  G[id].dscv = ++t;
  for(i=1; i<=G[id].k; i++){
    if(G[G[id].v[i]].color == WHITE){//未探索判定
      visit(G[id].v[i]);
    }
  }
  G[id].color = BLACK;//探索済み
  G[id].fin = ++t;
}

void dfs(){
  int i,j;
//深さ優先探索の本質
  for(i=1; i<=n; i++){//初期設定でいったん全てのバーテックスを白にする
    G[i].color = WHITE;
  }
  t = 0;//探索ステップを０に初期化
  for(i=1; i<=n; i++){
    if(G[i].color == WHITE){
      visit(G[i].id);
    }
  }
}

int main() {
  int i, j;
  int id;

  //-----各種入力処理------
  printf("要素の個数を入力(Input element count)");
  scanf("%d",&n);
  G = malloc(sizeof(Graph) * (n+1));
  getDef();
  for (i = 1; i <= n; i++) {
    printf("要素のIDを入力してください。Please input element ID\n");
    scanf("%d",&id);
    G[id].id = id;//ID番目にIDを直接入れることで順番を守る
    printf("[%d]の要素の子供の数を指定してください。Please decide [%d]'s childlen count.\n",G[id].id, G[id].id);
    scanf("%d",&G[id].k);
    if(G[id].k != 0){
      G[id].v = (int*)malloc(sizeof(int) * (G[id].k+1));
      for(j = 1; j <= G[id].k; j++){
	printf("[%d]の子供のIDを入力してください。Please input [&d]'s childlen ID.\n",G[id].id, G[id].id);
	printf("%d / %d\n",j, G[id].k);
        scanf("%d",&G[id].v[j]);
      }
    }
  }
  dfs();
  printer();

  free(G);
  free(Adj);
  return 0;
}
