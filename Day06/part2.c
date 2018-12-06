#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int diff(int a, int b)
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

int main(int argc, char const *argv[]) {
  int i, j, x[50], y[50], point, dist, counter = 0;
  long int grid[400][400];
  char c, buff[20];
  FILE * fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 0;
  }

  for(i = 0; i < 50; i++) //INITIALISE x[] AND y[] AND infinite[]
  {
    x[i] = 0;
    y[i] = 0;
  }

  for(j = 0; j < 400; j++)  //INITIALISE grid[][]
  {
    for(i = 0; i < 400; i++)
    {
      grid[i][j] = 0;
    }
  }

  for(i = 0; i < 50; i++) //SET COORDINATES
  {
    for(j = 0; j < 20; j++)
    {
      buff[j] = '\0';
    }
    c = '\0';
    j = 0;
    while(c != '\n' && c != EOF) //READ LINE INTO buff[]
    {
      c = fgetc(fp);
      buff[j] = c;
      j++;
    }
    //printf("%d\tbuff[] = %s\n",i, buff);
    j = 0;
    while(buff[j] != ',') //FIND x[i]
    {
      //printf("%d:\tx Found %c\n", i, buff[j]);
      if(buff[j] != ',')
      {
        x[i] *= 10;
        x[i] += (int) buff[j] - 48;
      }
      j++;
    }
    j += 1;
    while(buff[j] != '\n' && buff[j] != EOF) //FIND y[i]
    {
      j++;
      //printf("%d:\ty Found %c\n", i, buff[j]);
      if(buff[j] != '\n' && buff[j] != EOF)
      {
        y[i] *= 10;
        y[i] += (int) buff[j] - 48;
      }
    }
  }

  for(j = 0; j < 400; j++) //CALCULATE SUM OF DISTANCES
  {
    for(i = 0; i < 400; i++)
    {
      for(point = 0; point < 50; point++)
      {
        dist = diff(i, x[point]) + diff(j, y[point]);
        grid[i][j] += dist;
      }
      if(grid[i][j] < 10000)
      {
        counter++;
      }
    }
  }

  printf("Total of %d Co-Ordinates with < 10000 total distance\n", counter);

  return 0;
}
