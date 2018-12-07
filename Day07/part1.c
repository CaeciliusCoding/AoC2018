#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int i, j = 0, status[26], instructions[101][2], counter;
  char c = '\0', buff[50];
  FILE * fp = fopen("input1.txt", "r");

  for(i = 0; i < 26; i++)
  {
    status[i] = 1; //0 = NOT READY, 1 = READY, 2 = COMPLETE
  }

  if(!fp)
  {
    printf("Error: File not opened");
    return -1;
  }

  for(j = 0; j < 101; j++)
  {
    for(i = 0; i < 50; i++)
    {
      buff[i] = '\0';
    }
    i = 0;
    while(c != EOF && c != '\n')
    {
      c = fgetc(fp);
      buff[i] = c;
      i++;
    }
    c = '\0';
    instructions[j][0] = ((int) buff[5]) - 65; //instructions[j][0] IS REQUIREMENT
    instructions[j][1] = ((int) buff[36]) - 65; //instructions[j][1] IS DEPENDENT
    //printf("%d -> %d\n", instructions[j][0], instructions[j][1]);
  }

  for(counter = 0; counter < 26; counter++)
  {
    for(i = 0; i < 101; i++) //UPDATE status[] TO 0 IF DEPENDENT
    {
      if(instructions[i][1] != -1)
      {
        status[instructions[i][1]] = 0;
      }
    }
    for(i = 0; i < 26; i++) //FIND FIRST READY INSTRUCTION
    {
      if(status[i] == 1)
      {
        status[i] = 2;
        printf("%c", ((char) i + 65));
        for(j = 0; j < 101; j++)
        {
          if(instructions[j][0] == i)
          {
            status[instructions[j][1]] = 1; //SET ALL DEPENDENT status[] TO 1
            instructions[j][0] = -1;
            instructions[j][1] = -1;
          }
        }
        break;
      }
    }
  }
  printf("\n");

  return 0;
}
