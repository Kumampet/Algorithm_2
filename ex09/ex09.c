#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *p;
int **m;

void init(int n)
{ //\u5404\u7a2e\u521d\u671f\u5316
  int i;
  p = (int *)malloc(sizeof(int) * (n + 1)); //\u5165\u529b\u6642\u306e\u884c\u5217\u306e\u6b21\u6570
  m = malloc(sizeof(int *) * (n + 1));      //\u5404\u30b9\u30c6\u30c3\u30d7\u3067\u306e\u884c\u5217\u7a4d
  for (i = 0; i <= n; i++)
  {
    m[i] = malloc(sizeof(int) * (n + 1));
  }
}

int min(int a, int q)
{ //\u8a08\u7b97\u3057\u305f\u884c\u5217\u7a4d\u306e\u3046\u3061\u6700\u5c0f\u306e\u7d44\u307f\u5408\u308f\u305b\u3092\u8fd4\u3059
  if (a > q)
  {
    return q;
  }
}

void matrixChainOrder(int n)
{
  int i, l, j, k, q;

  for (i = 1; i <= n; i++)
  { //\u6700\u4e0b\u7aef\u306f\uff10\u3067\u521d\u671f\u5316
    m[i][i] = 0;
  }
  for (l = 2; l <= n; l++)
  {
    for (i = 1; i <= n - l + 1; i++)
    {
      j = i + l - 1;
      m[i][j] = INT_MAX;
      for (k = i; k <= j - 1; k++)
      {
        q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        m[i][j] = min(m[i][j], q);
      }
    }
  }
}

int main()
{
  int n, garbage;
  int i;

  printf("Number of Arrays\n");
  scanf("%d", &n);
  init(n);
  printf("Input Matrix (ex: A[n][m])\n");
  scanf("%d %d", &p[0], &p[1]);
  for (i = 2; i <= n; i++)
  {
    scanf("%d %d", &garbage, &p[i]);
  }
  matrixChainOrder(n);
  printf("Matrix-Chain-Order is: %d\n", m[1][n]);
  return 0;
}