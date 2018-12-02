#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse(char * string, int length)
{
  int i;
  long int total = 0;
  //printf("parse recieved %s, length of %d\n", string, length);
  for(i = 1; i < length; i++)
  {
    //printf("\tparse found %c at position %d (total = %d before)\n", string[i], i, total);
    total *= 10;
    total += ((int) string[i] - 48);
    //printf("\t total now = %d\n", total);
  }

  if(string[0] == '+')
  {
    //printf("%s parse= %d\n", string, total);
    return total;
  }
  else
  {
    total = -total;
    //printf("%s parse= %d\n", string, total);
    return total;
  }
}

int main(int argc, char const *argv[])
{
  int i = 0, fCount = 0, fLoop;
  long int f = 0;
  long int fPast[300000];
  char buff[256];
  char c = '1';
  FILE * fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File doesn't exist\n");
    return 0;
  }

  while(1)
  {
    //printf("top of loop\n");
    c = fgetc(fp);
    //printf("found %c\n", c);
    if(c == '\n')
    {
      //printf("\t in \\n if statement\n");
      buff[i] = 0;
      f += parse(buff, i);
      i = 0;
      strcpy(buff, "");
      for(fLoop = 0; fLoop < fCount; fLoop++)
      {
        if(f == fPast[fLoop])
        {
          printf("Repeated frequency = %d\n", f);
          printf("fCount at %d\n", fCount);
          return 0;
        }
      }
      //printf("New Frequency registered = %d\n", f);
      fPast[fCount] = f;
      fCount++;
    }
    else
    {
      if(c == EOF)
      {
        //printf("end of file found\n");
        buff[i] = 0;
        f += parse(buff, i);
        i = 0;
        strcpy(buff, "");
        for(fLoop = 0; fLoop < fCount; fLoop++)
        {
          if(f == fPast[fLoop])
          {
            printf("Repeated frequency = %d\n", f);
            printf("fCount at %d\n", fCount);
            return 0;
          }
        }
        //printf("New Frequency registered = %d\n", f);
        fPast[fCount] = f;
        fCount++;
        fclose(fp);
        fp = fopen("input1.txt", "r");
      }
      else
      {
        buff[i] = c;
        i++;
      }
    }
  }

  fclose(fp);
  return 0;
}
