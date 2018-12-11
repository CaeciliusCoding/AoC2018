#include <stdio.h>
#include <stdlib.h>
#define SERIAL 1788

int main(int argc, char const *argv[]) {
  int grid[301][301], i, j, power, highPower = -46, highX = 0, highY = 0;

  for(j = 1; j < 301; j++) //POPULATE GRID
  {
    for(i = 1; i < 301; i++)
    {
      grid[i][j] = (i + 10) * j; //SET TO rackID * y
      grid[i][j] += SERIAL; //INCREASE BY serial
      grid[i][j] *= (i + 10); //MULTIPLY BY rackID
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

  for(j = 1; j < 289; j++)
  {
    for(i = 1; i < 289; i++)
    {
      power = grid[i][j] + grid[i + 1][j] + grid[i + 2][j];
      power += grid[i][j + 1] + grid[i + 1][j + 1] + grid[i + 2][j + 1];
      power += grid[i][j + 2] + grid[i + 1][j + 2] + grid[i + 2][j + 2];
      if(power > highPower)
      {
        highPower = power;
        highX = i;
        highY = j;
      }
    }
  }

  printf("(%d, %d)\n", highX, highY);

  return 0;
}
