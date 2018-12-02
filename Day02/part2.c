#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  char alphaCount[250][26], buffer;
  int letterCount, lineCount, incorrectCount, compareLineCount;
  FILE * fp = fopen("input1.txt", "r");

  for(lineCount = 0; lineCount < 250; lineCount++) //LOOPS THROUGH LINES
  {
    for(letterCount = 0; letterCount < 26; letterCount++) //LOOPS THROUGH LETTERS
    {
      alphaCount[lineCount][letterCount] = fgetc(fp);
      //printf("%c", alphaCount[lineCount][letterCount]);
    }
    //printf("\n");
    buffer = fgetc(fp);
  }

  for(lineCount = 0; lineCount < 250; lineCount++)
  {
    for(compareLineCount = lineCount; compareLineCount < 250; compareLineCount++)
    {
      incorrectCount = 0;
      for(letterCount = 0; letterCount < 26; letterCount++)
      {
        if(alphaCount[lineCount][letterCount] != alphaCount[compareLineCount][letterCount])
        {
          incorrectCount++;
          if(incorrectCount > 1)
          {
            break;
          }
        }
      }
      if(incorrectCount == 1)
      {
        for(letterCount = 0; letterCount < 26; letterCount++)
        {
          printf("%c", alphaCount[lineCount][letterCount]);
        }
        printf("\n");
        for(letterCount = 0; letterCount < 26; letterCount++)
        {
          printf("%c", alphaCount[compareLineCount][letterCount]);
        }
        printf("\n");
      }
    }
  }

  fclose(fp);
  return 0;
}
