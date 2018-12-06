#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(int x, int y) //RETURNS 0 IF (x, y) IS INVALID, 1 IF VALID
{
  if(x > 399 || x < 0 || y > 399 || y < 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int main(int argc, char const *argv[]) {
  int i, j, x[50], y[50], changes = 50, offset = 1, point, infinite[50], counter[50];
  int grid[400][400][2];
  //grid[x][y][0] TRACKS CLOSEST COORDINATE, -1 IS UNSET, -2 IS TIED DISTANCE
  //grid[x][y][1] TRACKS SET STATUS, 0 IS UNSET, 1 IF SET, 2 IF FRESH, 3 IF CEMENT
  char c, buff[20];
  FILE * fp = fopen("input1.txt", "r");

  if(!fp)
  {
    printf("Error: File not opened\n");
    return 0;
  }

  for(i = 0; i < 50; i++) //INITIALISE x[] AND y[] AND infinite[]
  {
    x[i] = 0;
    y[i] = 0;
    infinite[i] = 0;
    counter[i] = 0;
  }

  for(j = 0; j < 400; j++)  //INITIALISE grid[][]
  {
    for(i = 0; i < 400; i++)
    {
      grid[i][j][0] = -1;
      grid[i][j][1] = 0;
    }
  }

  for(i = 0; i < 50; i++) //SET COORDINATES
  {
    for(j = 0; j < 20; j++)
    {
      buff[j] = '\0';
    }
    c = '\0';
    j = 0;
    while(c != '\n' && c != EOF) //READ LINE INTO buff[]
    {
      c = fgetc(fp);
      buff[j] = c;
      j++;
    }
    //printf("%d\tbuff[] = %s\n",i, buff);
    j = 0;
    while(buff[j] != ',') //FIND x[i]
    {
      //printf("%d:\tx Found %c\n", i, buff[j]);
      if(buff[j] != ',')
      {
        x[i] *= 10;
        x[i] += (int) buff[j] - 48;
      }
      j++;
    }
    j += 1;
    while(buff[j] != '\n' && buff[j] != EOF) //FIND y[i]
    {
      j++;
      //printf("%d:\ty Found %c\n", i, buff[j]);
      if(buff[j] != '\n' && buff[j] != EOF)
      {
        y[i] *= 10;
        y[i] += (int) buff[j] - 48;
      }
    }
  }

  for(i = 0; i < 50; i++) //SET OWN COORDINATES ON grid[][][] TO SELF
  {
    grid[x[i]][y[i]][0] = i;
    grid[x[i]][y[i]][1] = 2;
  }
  printf("offset %d complete %d changes made\n", 0, changes);

  while(changes > 0) //PROPAGATE
  {
    changes = 0;
    for(j = 0; j < 400; j++)
    {
      for(i = 0; i < 400; i++)
      {
        if(grid[i][j][1] == 2) //IF FRESH, PROPAGATE
        {
          if(isValid(i, j + 1) == 1) //ABOVE
          {
            if(grid[i][j + 1][1] == 1 && grid[i][j + 1][0] != grid[i][j][0]) //IF ALREADY SET THIS ITERATION, TIE
            {
              grid[i][j + 1][0] = -2;
            }
            if(grid[i][j + 1][1] == 0) //IF UNSET, SET
            {
              grid[i][j + 1][0] = grid[i][j][0]; //SET TO ORIGIN POINT VALUE
              grid[i][j + 1][1] = 1; //MARK AS SET
              changes++;
            }
          }
          if(isValid(i, j - 1) == 1) //BELOW
          {
            if(grid[i][j - 1][1] == 1 && grid[i][j - 1][0] != grid[i][j][0]) //IF ALREADY SET THIS ITERATION, TIE
            {
              grid[i][j - 1][0] = -2;
            }
            if(grid[i][j - 1][1] == 0) //IF UNSET, SET
            {
              grid[i][j - 1][0] = grid[i][j][0]; //SET TO ORIGIN POINT VALUE
              grid[i][j - 1][1] = 1; //MARK AS SET
              changes++;
            }
          }
          if(isValid(i + 1, j) == 1) //RIGHT
          {
            if(grid[i + 1][j][1] == 1 && grid[i + 1][j][0] != grid[i][j][0]) //IF ALREADY SET THIS ITERATION, TIE
            {
              grid[i + 1][j][0] = -2;
            }
            if(grid[i + 1][j][1] == 0) //IF UNSET, SET
            {
              grid[i + 1][j][0] = grid[i][j][0]; //SET TO ORIGIN POINT VALUE
              grid[i + 1][j][1] = 1; //MARK AS SET
              changes++;
            }
          }
          if(isValid(i - 1, j) == 1) //LEFT
          {
            if(grid[i - 1][j][1] == 1 && grid[i - 1][j][0] != grid[i][j][0]) //IF ALREADY SET THIS ITERATION, TIE
            {
              grid[i - 1][j][0] = -2;
            }
            if(grid[i - 1][j][1] == 0) //IF UNSET, SET
            {
              grid[i - 1][j][0] = grid[i][j][0]; //SET TO ORIGIN POINT VALUE
              grid[i - 1][j][1] = 1; //MARK AS SET
              changes++;
            }
          }
        }
      }
    }
    for(j = 0; j < 400; j++)
    {
      for(i = 0; i < 400; i++)
      {
        if(grid[i][j][1] == 1 || grid[i][j][1] == 2)
        {
          grid[i][j][1]++; //SET TO FRESH; FRESH TO CEMENT
        }
      }
    }
    printf("PROPAGATE iteration complete %d changes made\n", changes);
  }

  j = 0; //BOTTOM ROW INFINITE CHECK
  for(i = 0; i < 400; i++)
  {
    printf("BOTTOM checking (%d, %d)\n", i, j);
    if(grid[i][j][0] != -2)
    {
      infinite[grid[i][j][0]] = 1;
    }
  }
  i = 399; //RIGHT COLUMN INFINITE CHECK
  for(j = 0; j < 400; j++)
  {
    printf("RIGHT checking (%d, %d)\n", i, j);
    if(grid[i][j][0] != -2)
    {
      infinite[grid[i][j][0]] = 1;
    }
  }
  j = 399; //TOP ROW INFINITE CHECK
  for(i = 399; i > 0; i--)
  {
    printf("TOP checking (%d, %d)\n", i, j);
    if(grid[i][j][0] != -2)
    {
      infinite[grid[i][j][0]] = 1;
    }
  }
  i = 0; //LEFT ROW INFINITE CHECK
  for(j = 399; j > 0; j--)
  {
    printf("LEFT checking (%d, %d)\n", i, j);
    if(grid[i][j][0] != -2)
    {
      infinite[grid[i][j][0]] = 1;
    }
  }

  for(j = 0; j < 400; j++) //OUTPUT
  {
    for(i = 0; i < 400; i++)
    {
      if(grid[i][j][0] != -2)
      {
        counter[grid[i][j][0]]++;
      }
      //printf("%d\t", grid[i][j][0]);
    }
    //printf("\n");
  }

  j = 0;
  for(i = 1; i < 50; i++)
  {
    if(infinite[i] == 0)
    {
      printf("%d:\t%d\n", i, counter[i]);
      if(counter[i] > counter[j])
      {
        j = i;
      }
    }
    else
    {
      printf("%d:\tinfinite\n", i);
    }
  }
  printf("Largest Finite Co-Ordinate: %d, Size: %d (%d, %d)\n", j, counter[j], x[j], y[j]);

  return 0;
}
