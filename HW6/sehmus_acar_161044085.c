#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ROW 512
#define COL 512

int place(int M[][COL], int row, int col, bool visited[][COL]) {

  return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL) && (M[row][col] > 0) && (M[row][col] <= 128) && !visited[row][col];
}

void recursion(int M[][COL], int row, int col, bool visited[][COL]) {
  int k;
  // yönler yukarı , sol , assagı , sag şeklinde sıra ile
  int rowNbr[] = {-1,0,1,0};
  int colNbr[] = {0,-1,0,1};

  visited[row][col] = true;
  k = 0;
  while (k < 4) {
    if (place(M, row + rowNbr[k], col + colNbr[k], visited))
      recursion(M, row + rowNbr[k], col + colNbr[k], visited);
    k++;
  }
}

int print_coo(int M[][COL], FILE * fp_2) {
  int x[262144];
  int y[262144];
  bool visited[ROW][COL];
  memset(visited, 0, sizeof(visited));

  int num_isl = 0;
  for (int i = 0; i < ROW; ++i)
    for (int j = 0; j < COL; ++j)
      if (M[i][j] && !visited[i][j]) {
        recursion(M, i, j, visited);
        x[num_isl] = j;
        y[num_isl] = i;
        ++num_isl;
      }
  fprintf(fp_2, "%d\n", num_isl);
  for (int i = 0; i < num_isl; i++) {
    fprintf(fp_2, "x_coordinate%d %d y_coordinate%d %d\n", i, y[i], i, x[i]);
  }

  return num_isl;
}
void atama(FILE * fp, int Map[][COL]) {
  int i = 0;
  int j = 0;
  char * pch;
  char line[524288];
  fgets(line, 524288, fp);
  pch = strtok(line, " ");
  while (i < ROW && pch != NULL) {
    j = 0;
    while (j < COL && pch != NULL) {
      sscanf(pch, "%d", & Map[i][j]);
      pch = strtok(NULL, " ");
      j++;
    }
    i++;
  }
}

int main() {
  FILE * fp;
  FILE * fp_2;
  int Map[ROW][COL];
  fp = fopen("input.txt", "r");
  fp_2 = fopen("output.txt", "w");
  atama(fp, Map);
  print_coo(Map, fp_2);
  return 0;
}