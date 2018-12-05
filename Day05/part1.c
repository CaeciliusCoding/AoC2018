#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  size_t size = (sizeof(char) * 50000);
  char * buff = (char *) malloc(size);
  char c;
  int i = 0, j, removeCounter = 1;
  FILE * fp;

  fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 0;
  }

  while(c != EOF)
  {
    c = fgetc(fp);
    //printf("Found %c\n", c);
    buff[i] = c;
    //printf("Inserted %c\n", buff[i]);
    i++;
  }
  buff[i] = '\0';

  while(removeCounter > 0)
  {
    removeCounter = 0;
    for(i = 0; i < 49999; i++)
    {
      if(buff[i] != ' ')
      {
        j = i + 1;
        while(buff[j] == ' ') //buff[j] is next remaining letter
        {
          j++;
        }
        if(((int) buff[i] + 32) == ((int) buff[j]) || ((int) buff[i] - 32) == ((int) buff[j]))
        {
          buff[i] = ' ';
          buff[j] = ' ';
          removeCounter++;
        }
      }
    }
  }

  j = 0;
  for(i = 0; i < 50000; i++)
  {
    if(buff[i] != ' ')
    {
      printf("%c", buff[i]);
      j++;
    }
  }
  printf("\nLength of remaining string = %d\n", j);

  fclose(fp);

  return 0;
}
