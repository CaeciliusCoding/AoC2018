#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  static int grid[1000][1000];
  int xStart, yStart, xWidth, yWidth, x, y, overCount = 0, i = 0;
  char buff[26];
  char c;
  FILE * fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
  }

  for(y = 0; y < 1000; y++) //INITIALISES grid[][]
  {
    for(x = 0; x < 1000; x++)
    {
      grid[x][y] = 0;
      //printf("(%d,%d)\n", x, y);
    }
  }
  //printf("Initialised grid[][]\n");

  for(i = 0; i < 25; i++)
  {
    buff[i] = ' ';
  }
  buff[25] = '\0';

  i = 0;
  while (1) {
    c = fgetc(fp);
    //printf("%s\n", buff);
    if(c == '\n' || c == EOF) //IF END OF LINE
    {
      //printf("%s\n", buff);
      //printf("End of Line\n");
      x = 0;
      y = 0;
      xStart = 0;
      yStart = 0;
      xWidth = 0;
      yWidth = 0;
      while(buff[y] != '@')
      {
        y++;
      }
      x = y + 2; //SETS x TO START OF xStart
      y = x;
      while(buff[y] != ',')
      {
        y++;
      }
      //printf("xStart: ");
      for(i = x; i < y; i++) //SETS xStart
      {
        xStart *= 10;
        xStart += ((int) buff[i] - 48);
        //printf("%c", buff[i]);
      }
      //printf("\n");
      x = y + 1; //SETS x TO START of yStart
      y = x;
      while(buff[y] != ':')
      {
        y++;
      }
      //printf("yStart: ");
      for(i = x; i < y; i++) //SETS yStart
      {
        yStart *= 10;
        yStart += ((int) buff[i] - 48);
        //printf("%c", buff[i]);
      }
      //printf("\n");
      x = y + 2; //SETS x TO START OF xWidth
      y = x;
      while(buff[y] != 'x')
      {
        y++;
      }
      //printf("xWidth: ");
      for(i = x; i < y; i++) //SETS xWidth
      {
        xWidth *= 10;
        xWidth += ((int) buff[i] - 48);
        //printf("%c", buff[i]);
      }
      //printf("\n");
      x = y + 1;
      y = x;
      while(buff[y] != ' ')
      {
        y++;
      }
      //printf("yWidth: ");
      for(i = x; i < y; i++) //SETS yWidth
      {
        yWidth *= 10;
        yWidth += ((int) buff[i] - 48);
        //printf("%c", buff[i]);
      }
      //printf("\n");
      //printf("Start: (%d,%d) : %dx%d\n", xStart, yStart, xWidth, yWidth);


      for(i = 0; i < 25; i++)
      {
        buff[i] = ' ';
      }
      i = 0;
      for(y = yStart; y < (yStart + yWidth); y++)
      {
        for(x = xStart; x < (xStart + xWidth); x++)
        {
          grid[x][y]++;
          if(grid[x][y] == 2)
          {
            overCount++;
          }
        }
      }
      //printf("Start: (%d,%d) : %dx%d\n", xStart, yStart, xWidth, yWidth, overCount, (xWidth * yWidth));
    }
    else
    {
      buff[i] = c;
      i++;
    }
    if(c == EOF)
    {
      break;
    }

  }

  printf("Overlapped squares: %d\n", overCount);
  return 0;
}
