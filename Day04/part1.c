#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int guard[4000], i, j = 0, currentHour, currentMinute, sleep[60], oldMinute, id;
  char buff[255], c = 'a';
  FILE * fp = fopen("input2.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 0;
  }

  for(i = 0; i < 60; i++)
  {
    sleep[i] = 0;
  }

  for(i = 0; i < 4000; i++)
  {
    guard[i] = 0; //guard[i] is minutes asleep
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
      guard[id] += (currentMinute - oldMinute);
      if(id == 2441) //MAGIC NUMBER GUARD ID FROM RUN 1
      {
        for(i = oldMinute; i < currentMinute; i++)
        {
          sleep[i]++;
        }
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

  j = 0;
  for(i = 1; i < 4000; i++)
  {
    if(guard[i] > guard[j])
    {
      j = i;
    }
  }
  printf("Guard #%d slept most (%d)\n", j, guard[j]);
  id = j;

  j = 0;
  for(i = 1; i < 60; i++)
  {
    if(sleep[i] > sleep[j])
    {
      j = i;
    }
  }
  printf("Most slept minute: %d (%d times)\n", j, sleep[j]);
  printf("Checksum: %d\n", (id * j));

  fclose(fp);

  return 0;
}
