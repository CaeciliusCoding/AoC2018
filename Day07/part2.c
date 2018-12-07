#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int i, j = 0, status[26][2], instructions[101][2], time = 0, worker[5], flag = 1;
  char c = '\0', buff[50];
  FILE * fp = fopen("input1.txt", "r");

  for(i = 0; i < 26; i++)
  {
    status[i][0] = 0; //0 IF NOT READY, 1 IF READY, 2 IF BUSY, 3 IF DONE
    status[i][1] = 61 + i; //TIME REMAINING
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

  while(flag > 0)
  {
    //printf("second %d:\n", time);
    for(i = 0; i < 26; i++) //SET ALL UNFINISHED TASKS
    {
      if(status[i][0] == 0)
      {
        status[i][0] = 1;
      }
    }
    for(i = 0; i < 101; i++) //UPDATE status[] TO 0 IF DEPENDENT
    {
      if(instructions[i][0] != -1)
      {
        //printf("\tinstruction\t%d\t(%c -> %c)\n", i, ((char) instructions[i][0] + 65), ((char) instructions[i][1] + 65));
        status[instructions[i][1]][0] = 0;
      }
      else
      {
        //printf("\tinstruction %d complete\n", i);
      }
    }
    /*printf("\tstatus register:\n");
    for(i = 0; i < 26; i++)
    {
      printf("\t\t%c: %d (%ds remaining)\n", ((char) i + 65), status[i][0], status[i][1]);
    }*/
    flag = 0; //EACH WORKER FINDS A TASK IF POSSIBLE
    for(i = 0; i < 5; i++)
    {
      for(j = 0; j < 26; j++) //FIND FIRST INSTRUCTION READY
      {
        if(status[j][0] == 1)
        {
          status[j][0] = 2;
          status[j][1]--;
          worker[i] = j;
          flag = i;
          //printf("\tworker%d worked on %c (%ds remaining)\n", i, ((char) worker[i] + 65), status[j][1]);
          break;
        }
      }
      if(flag != i) //IF IDLE SET worker[i] TO -1
      {
        worker[i] = -1;
        flag = i;
        //printf("\tworker%d is idle\n", i);
      }
    }
    for(i = 0; i < 26; i++) //REMOVE ANY COMPLETE TASKS & INSTRUCTIONS
    {
      if(status[i][0] == 2 && status[i][1] > 0)
      {
        status[i][0] = 1; //MARK AS READY
      }
      if(status[i][0] == 2 && status[i][1] == 0)
      {
        status[i][0] = 3; //MARK AS DONE
        printf("\t\ttask %c complete\n", ((char) i + 65));
        for(j = 0; j < 101; j++) //REMOVE INSTRUCTIONS
        {
          if(instructions[j][0] == i)
          {
            instructions[j][0] = -1;
            instructions[j][1] = -1;
          }
        }
      }
    }
    flag = 26;
    for(i = 0; i < 26; i++) //UPDATE FLAG
    {
      if(status[i][0] == 3)
      {
        flag--;
      }
    }
    //printf("%d tasks remaining\n\n", flag);
    time++;
  }
  printf("Total time taken: %ds", time);

  return 0;
}
