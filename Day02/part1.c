#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  int alphaCount[26], i, doubleCount = 0, tripleCount = 0, doubleBool = 0, tripleBool = 0;
  char c = '0';
  FILE * fp = fopen("input1.txt", "r");

  for(i = 0; i < 26; i++) //INITIALISES alphaCount
  {
    alphaCount[i] = 0;
  }

  while(c != EOF)
  {
    while(1) //LOOPS THROUGH LINE
    {
      c = fgetc(fp);
      if(c != '\n' && c != EOF)
      {
        i = (int) c;
        i -= 97;
        alphaCount[i]++;
        //printf("\tFound %c; Total: %d\n", c, alphaCount[i]);
      }
      else
      {
        break;
      }
    }

    //printf("Finished line\n");

    for(i = 0; i < 26; i++) //CALCULATES DOUBLES AND TRIPLES
    {
      if(alphaCount[i] == 2)
      {
        if(doubleBool == 0)
        {
          doubleCount++;
        }
        doubleBool = 1;
        //printf("double letter: %c\n", (char)(i + 97) );
      }
      if(alphaCount[i] == 3 && tripleBool == 0)
      {
        if(tripleBool == 0)
        {
          tripleCount++;
        }
        tripleBool = 1;
        //printf("triple letter: %c\n", (char)(i + 97) );
      }
    }

    for(i = 0; i < 26; i++)
    {
      alphaCount[i] = 0;
    }
    doubleBool = 0;
    tripleBool = 0;
  }

  i = doubleCount * tripleCount;
  //printf("Doubles: %d; Triples: %d; ", doubleCount, tripleCount);
  printf("Checksum: %d\n", i);

  fclose(fp);
  return 0;
}
