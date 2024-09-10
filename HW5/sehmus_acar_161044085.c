#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * getlinex(char * str);
double foo(char * str);

int main() {
  char str[20];
  printf("Define the Object\n");

  getlinex(str);
  double x = foo(str);

  printf("Total cost of %s is %.1lf\n", str, x);

  return 0;
}

char * getlinex(char * str) {
  fflush(stdin);
  char c;
  scanf("%[^\n]%c", str, & c);
  return str;
}

double foo(char * str) {

  char string[10][100], temp[100];
  char * token;
  double arr[10], sum = 0.0;
  int i = 0, j = 0;

  printf("What is %s\n", str);
  getlinex(temp);

  token = strtok(temp, "* +");

  while (token != NULL) {
    if (i % 2 == 0) {
      sscanf(token, "%lf", & arr[j]);
      i++;
    } else {
      strcpy(string[j], token);
      i++;
      j++;
    }
    token = strtok(NULL, "* +");
  }

  if (i == 1) return arr[0];

  for (int k = 0; k < j; k++) {
    sum += arr[k] * foo(string[k]);
  }

  return sum;

}