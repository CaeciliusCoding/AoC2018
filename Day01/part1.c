#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse(char * string, int length)
{
  int i;
  long long int total = 0;
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
  int i = 0;
  long long int f = 0;
  char buff[256];
  char c = '1';
  FILE * fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File doesn't exist\n");
    return 0;
  }

  while(c != EOF)
  {
    c = fgetc(fp);
    if(c == EOF)
    {
      break;
    }
    if(c == '\n')
    {
      buff[i] = 0;
      f += parse(buff, i);
      i = 0;
      strcpy(buff, "");
    }
    else
    {
      buff[i] = c;
      i++;
    }
  }
  f += parse(buff, i);

  printf("Frequency = %d\n", f);
  fclose(fp);
  return 0;
}
