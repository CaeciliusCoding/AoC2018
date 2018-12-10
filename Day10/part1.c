#include <stdio.h>
#include <stdlib.h>
#define INPUT 342
#define MAX_TIME 100000
#define SECOND 10681

int point[INPUT][4];

int parseInput(char *string, int num)
{
  int i, out = 0;
  switch (num) {
  case 0:
    for(i = 11; i < 16; i++)
    {
      out *= 10;
      out += (int) string[i] - 48;
    }
    if(string[10] == '-') //CHECK HORIZONTAL COORDINATE
    {
      out -= (2 * out);
    }
    //printf("\tHC: %d\n", out);
    return out;
    break;
  case 1:
    for(i = 19; i < 24; i++)
    {
      out *= 10;
      out += (int) string[i] - 48;
    }
    if(string[18] == '-') //CHECK VERTICAL COORDINATE
    {
      out -= (2 * out);
    }
    //printf("\tVC: %d\n", out);
    return out;
    break;
  case 2:
    out = (int) string[37] - 48;
    if(string[36] == '-') //CHECK HORIZONTAL VELOCITY
    {
      out -= (2 * out);
    }
    //printf("\tHV: %d\n", out);
    return out;
    break;
  case 3:
    out = (int) string[41] - 48;
    if(string[40] == '-') //CHECK VERTICAL VELOCITY
    {
      out -= (2 * out);
    }
    //printf("\tVV: %d\n", out);
    return out;
    break;
  }
}

int difference(int a, int b)
{
  if(a > b)
  {
    return a - b;
  }
  else
  {
    return b - a;
  }
}

void printGrid(int hMin, int hMax, int vMin, int vMax)
{
  int x, y, flag, i;
  for(y = vMin; y <= vMax; y++)
  {
    for(x = hMin; x <= hMax; x++)
    {
      flag = 0;
      for(i = 0; i < INPUT; i++)
      {
        if(point[i][0] == x && point[i][1] == y)
        {
          flag = 1;
        }
      }
      if(flag == 1)
      {
        printf("*");
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {
  int i, j, hMax, hMin, hDiff = 99999, hSmall = -1, vMax, vMin, vDiff = 99999, vSmall = -1;
  //point[][0] HORIZONTAL COORDINATE
  //point[][1] VERTICAL COORDINATE
  //point[][2] HORIZONTAL VELOCITY
  //point[][3] VERTICAL VELOCITY
  char c, buff[42];
  FILE *fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 1;
  }

  for(i = 0; i < INPUT; i++)
  {
    for(j = 0; j < 4; j++)
    {
      point[i][j] = 0;
    }
  }

  j = 0;
  i = 0;
  while(c != EOF)
  {
    c = fgetc(fp);
    if(c == EOF || c == '\n')
    {
      //printf("POINT %d:\n", j);
      for(i = 0; i < 4; i++)
      {
        point[j][i] = parseInput(buff, i);
      }
      i = 0;
      j++;
    }
    else
    {
      buff[i++] = c;
    }
  }

  /*for(i = 0; i < INPUT; i++)
  {
    printf("%d:\t(%d, %d)  \t<%d,%d>\n", i, point[i][0], point[i][1], point[i][2], point[i][3]);
  }*/

  for(j = 0; j < MAX_TIME; j++) //FIND SECOND OF SMALLEST GRID
  {
    hMax = -99999;
    hMin = 99999;
    vMax = -99999;
    vMin = 99999;
    for(i = 0; i < INPUT; i++)
    {
      if(point[i][0] > hMax)
      {
        hMax = point[i][0];
      }
      if(point[i][0] < hMin)
      {
        hMin = point[i][0];
      }
      if(point[i][1] > vMax)
      {
        vMax = point[i][1];
      }
      if(point[i][1] < vMin)
      {
        vMin = point[i][1];
      }
    }
    if(difference(hMax, hMin) < hDiff)
    {
      hDiff = difference(hMax, hMin);
      hSmall = j;
    }
    if(difference(vMax, vMin) < vDiff)
    {
      vDiff = difference(vMax, vMin);
      vSmall = j;
    }
    if(j == SECOND && SECOND != -1) //PRINT GRID
    {
      printGrid(hMin, hMax, vMin, vMax);
    }
    for(i = 0; i < INPUT; i++)
    {
      point[i][0] += point[i][2];
      point[i][1] += point[i][3];
    }
  }
  printf("After %d iterations:\n", MAX_TIME);
  printf("\tsmallest HORIZONTAL difference [%d] at SECOND %d\n", hDiff, hSmall);
  printf("\tsmallest VERTICAL difference [%d] at SECOND %d\n", vDiff, vSmall);

  fclose(fp);
  return 0;
}
