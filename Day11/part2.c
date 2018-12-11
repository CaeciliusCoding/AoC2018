#include <stdio.h>
#include <stdlib.h>
#define SERIAL 1788

int main(int argc, char const *argv[]) {
  int grid[300][300], i, j, power, highPower = -46, x, highX = -1, y, highY = -1, size, highSize = 0;

  for(j = 0; j < 300; j++) //POPULATE GRID
  {
    for(i = 0; i < 300; i++)
    {
      grid[i][j] = (i + 11) * j; //SET TO rackID * y
      grid[i][j] += SERIAL; //INCREASE BY serial
      grid[i][j] *= (i + 11); //MULTIPLY BY rackID
      if(grid[i][j] < 100)
      {
        grid[i][j] = 0;
      }
      else
      {
        grid[i][j] -= grid[i][j] % 100; //DELETE units AND tens
        grid[i][j] /= 100; //DIVIDE BY 100
        grid[i][j] = grid[i][j] % 10; //LEAVE ONLY ORIGINAL hundreds COLUMN
      }
      grid[i][j] -= 5; //REDUCE BY 5
    }
  }


  for(size = 1; size <= 300; size++) //FIND HIGHEST POWER SQUARE
  {
    printf("doing size %d\n", size);
    for(j = 0; j < (301 - size); j++)
    {
      for(i = 0; i < (301 - size); i++)
      {
        power = 0;
        for(y = 0; y < size; y++)
        {
          for(x = 0; x < size; x++)
          {
            power += grid[i + x][j + y];
          }
        }
        //printf("(%d, %d) \t@%d\ttotal power = %d\n", (i + 1), (j + 1), size, power);
        if(power > highPower)
        {
          highPower = power;
          highX = i;
          highY = j;
          highSize = size;
        }
      }
    }
  }

  printf("(%d, %d) at size %d\n", (highX + 1), highY, highSize);

  /*printf("\t235\t236\t237\t238\t239\t240\n");
  for(j = 33; j < 42; j++)
  {
    printf("%d\t", j + 1);
    for(i = 234; i < 240; i++)
    {
      printf("%d\t", grid[i][j]);
    }
    printf("\n");
  }*/

  return 0;
}
