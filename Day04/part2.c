#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int guard[4000][60], i, j = 0, currentHour, currentMinute, oldMinute, id;
  char buff[255], c = 'a';
  FILE * fp = fopen("input2.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 0;
  }

  for(i = 0; i < 4000; i++)
  {
    for(j = 0; j < 60; j++)
    {
      guard[i][j] = 0; //guard[id][minute]
    }
  }

  while(c != EOF)
  {
    i = 0;
    while(c != '\n' && c != EOF) //GET LINE INTO buff[]
    {
      c = fgetc(fp);
      //printf("c = %c\n", c);
      buff[i] = c;
      i++;
      //printf("added %c (%c)\n", c, buff[i]);
    }
    buff[i + 1] = '\0';
    //printf("%s", buff);
    oldMinute = currentMinute;
    currentHour = (((int) buff[12] - 48) * 10) + ((int) buff[13] - 48);
    currentMinute = (((int) buff[15] - 48) * 10) + ((int) buff[16] - 48);
    if(buff[19] == 'G')
    {
      id = 0;
      j = 27;
      while(buff[j] != ' ')
      {
        j++;
      }
      for(i = 26; i < j; i++)
      {
        id *= 10;
        id += (int) buff[i] - 48;
      }
      //printf("(%d:%d)\t Guard #%d on duty\n", currentHour, currentMinute, id);
    }
    if(buff[19] == 'f')
    {
      //printf("(%d:%d)\t Guard #%d now asleep\n", currentHour, currentMinute, id);
    }
    if(buff[19] == 'w')
    {
      for(i = oldMinute; i < currentMinute; i++)
      {
        guard[id][i]++;
      }
      //printf("(%d:%d)\t Guard #%d now awake, slept %d (total = %d)\n", currentHour, currentMinute, id, (currentMinute - oldMinute), guard[id]);
    }
    if(c != EOF)
    {
      c = ' ';
    }
    else
    {
      //printf("\n");
      //printf("end of file\n");
    }
    for(i = 0; i < 255; i++)
    {
      buff[i] = '\0';
    }
  }

  id = 0;
  currentMinute = 0;
  for(j = 0; j < 4000; j++)
  {
    for(i = 0; i < 60; i++)
    {
      if(guard[j][i] > guard[id][currentMinute])
      {
        id = j;
        currentMinute = i;
      }
    }
  }
  printf("Guard #%d most frequently asleep at minute %d (%d times)\n", id, currentMinute, (guard[id][currentMinute]));
  printf("Checksum: %d\n", (id * currentMinute));

  fclose(fp);

  return 0;
}
