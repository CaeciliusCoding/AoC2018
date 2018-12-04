#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char line[1044][255], c;
  int i, j = 0, month[1044], day[1044], hour[1044], minute[1044], counter = 0;
  FILE * fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 0;
  }

  for(j = 0; j < 1044; j++)
  {
    for(i = 0; i < 255; i++)
    {
      line[j][i] = '\0';
    }
  }
  j = 0;

  while(c != EOF)
  {
    i = 0;
    while(c != '\n' && c != EOF) //GET LINE INTO buff[]
    {
      c = fgetc(fp);
      line[j][i] = c;
      i++;
    }
    j++;
    if(c != EOF)
    {
      c = '\0';
    }
  }

  for(j = 0; j < 1044; j++)
  {
    month[j] = (((int) line[j][6] - 48) * 10) + ((int) line[j][7] - 48);
    day[j] = (((int) line[j][9] - 48) * 10) + ((int) line[j][10] - 48);
    hour[j] = (((int) line[j][12] - 48) * 10) + ((int) line[j][13] - 48);
    minute[j] = (((int) line[j][15] - 48) * 10) + ((int) line[j][16] - 48);
    //printf("%d-%d %d:%d\n", month[j], day[j], hour[j], minute[j]);
  }

  for(int x = 0; x < 1044; x++)
  {
    i = 0;
    for(j = 1; j < 1044; j++)
    {
      if(month[j] == month[i])
      {
        //GO UP A LEVEL
        if(day[j] == day[i])
        {
          //GO UP A LEVEL
          if(hour[j] == hour[i])
          {
            if(minute[j] < minute[i])
            {
              i = j;
            }
          }
          else
          {
            if(hour[j] < hour[i])
            {
              i = j;
            }
          }
        }
        else
        {
          if(day[j] < day[i])
          {
            i = j;
          }
        }
      }
      else
      {
        if(month[j] < month[i])
        {
          i = j;
        }
      }
    }
    printf("%s", line[i]);
    month[i] = 13;
    day[i] = 32;
    hour[i] = 24;
    minute[i] = 60;
    counter++;
  }

  //printf("%d lines output\n", counter);
  fclose(fp);

  return 0;
}
