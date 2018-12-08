#include <stdio.h>
#include <stdlib.h>

int array[18367], total = 0, count = 0;

int expand(int start, int id)
{
  int children, metadata, length = 2, i = 0;
  children = array[start];
  metadata = array[start + 1];
  printf("SETUP Node%d: %d children, %d metadata\n", id, children, metadata);
  while (i < children)
  {
    printf("EXPAND Node%d: child %d, current length = %d\n", id, (i + 1), length);
    length += expand((start + length), ++count);
    i++;
  }
  i = 0;
  while(i < metadata)
  {
    printf("DATA Node%d: metadata %d, adding %d, total = %d\n", id, i, array[length + start], (total + array[length + start]));
    total += array[length + start];
    length++;
    i++;
  }
  return length;
}

int main(int argc, char const *argv[]) {
  int  i = 0, j = 0;
  char c = '\0';
  FILE * fp = fopen("input1.txt", "r");

  for(i = 0; i < 18367; i++) //INITALISE array[]
  {
    array[i] = 0;
  }
  i = 0;

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 1;
  }

  while(c != EOF) //POPULATE array[] WITH INPUT
  {
    c = fgetc(fp);
    if(c == '\n' || c == ' ' || c == EOF) //ADD i TO array[]
    {
      array[j] = i;
      i = 0;
      printf("%d;", array[j]);
      j++;
    }
    else //INCREASE i
    {
      i *= 10;
      i += (int) c - 48;
    }
  }
  printf("\nArray populated, Length: %d\n", j);

  i = expand(0, 0);
  printf("i = %d\n", i);
  printf("Total of Metadata = %d\n", total);

  fclose(fp);
  return 0;
}
