#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  size_t size = (sizeof(char) * 50000);
  char * buff;
  char c;
  int i, j, removeCounter, alphaCounter;
  FILE * fp;

  for(alphaCounter = 0; alphaCounter < 26; alphaCounter++)
  {
    c = ' ';
    fp = fopen("input1.txt", "r");
    buff = (char *) malloc(size);
    removeCounter = 1;
    i = 0;

    if(!fp)
    {
      printf("Error: File not opened\n");
      return 0;
    }

    while(c != EOF)
    {
      c = fgetc(fp);
      //printf("Found %c\n", c);
      if((((int) c) != (alphaCounter + 65) && (((int) c) != (alphaCounter + 97))))
      {
        buff[i] = c;
      }
      else
      {
        buff[i] = ' ';
        //printf("Excluded %c, Inserted %c instead (alphaCounter = %d)\n", c, buff[i], alphaCounter);
      }
      //printf("Inserted %c\n", buff[i]);
      i++;
    }
    buff[i] = '\0';

    //printf("alphaCounter = %d, removeCounter = %d\n", alphaCounter, removeCounter);
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
      //printf("pass done, alphaCounter = %d, removed = %d\n", alphaCounter, removeCounter);
    }

    j = 0;
    for(i = 0; i < 50000; i++)
    {
      if(buff[i] != ' ')
      {
        //printf("%c", buff[i]);
        j++;
      }
    }
    printf("For %c remaining string = %d\n", ((char) (alphaCounter + 65)), j);
    free(buff);
  }
  return 0;
}
