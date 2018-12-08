#include <stdio.h>
#include <stdlib.h>

int array[18367], nodeVal[3000], count = 0;

int expand(int start, int id)
{
  int children, metadata, length = 2, i = 0;
  children = array[start];
  metadata = array[start + 1];
  int childID[children];
  printf("SETUP \tNode%d: %d children, %d metadata\n", id, children, metadata);
  while (i < children)
  {
    count++;
    childID[i] = count;
    printf("EXPAND \tNode%d: child %d (Node%d), current length = %d\n", id, (i + 1), childID[i], length);
    length += expand((start + length), count);
    i++;
  }
  i = 0;
  if(children == 0)
  {
    while(i < metadata)
    {
      nodeVal[id] += array[length + start];
      length++;
      i++;
    }
    printf("DATA \tNode%d: no children, metadata sum = %d\n", id, nodeVal[id]);
  }
  else
  {
    while(i < metadata)
    {
      if(!array[length + start] == 0 && array[length + start] <= children)
      {
        nodeVal[id] += nodeVal[childID[(array[length + start] - 1)]];
        printf("DATA \tNode%d: child %d (Node%d), adding %d, value = %d\n", id, array[length + start], childID[(array[length + start] - 1)], nodeVal[childID[(array[length + start] - 1)]], nodeVal[id]);
      }
      i++;
      length++;
    }
  }
  return length;
}

int main(int argc, char const *argv[]) {
  int  i = 0, j = 0;
  char c = '\0';
  FILE * fp = fopen("input1.txt", "r");

  for(i = 0; i < 1986; i++)
  {

  }

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
      //printf("%d;", array[j]);
      j++;
    }
    else //INCREASE i
    {
      i *= 10;
      i += (int) c - 48;
    }
  }
  printf("Array populated, Length: %d\n", j);

  i = expand(0, 0);
  //printf("i = %d, number of nodes = %d\n", i, count);
  printf("Value of Root Node = %d\n", nodeVal[0]);

  fclose(fp);
  return 0;
}
