#include <stdio.h>
#include <stdlib.h>
#define PLAYERS 405
#define MAX_MARBLE 70953

struct marble {
  struct marble *next; //CLOCKWISE
  struct marble *prev; //COUNTERCLOCKWISE
  int value;
};

void printMarbles(struct marble *current, int turn)
{
  struct marble *m = current->next;
  if(turn == -1)
  {
    printf("[-]\t(%d)", current->value);
  }
  else
  {
    printf("[%d]\t(%d)", turn, current->value);
  }
  while(m != current)
  {
    printf(" %d", m->value);
    m = m->next;
  }
  printf("\n");
}

int scoreMarble(struct marble **current)
{
  struct marble *m = *current, *clock, *anti;
  int i;
  for(i = 0; i < 7; i++)
  {
    m = m->prev;
  }
  clock = m->next;
  anti = m->prev;
  clock->prev = anti;
  anti->next = clock;
  i = m->value;
  *current = clock;
  free(m);
  return i;
}

struct marble * insertMarble(struct marble *current, int score)
{
  struct marble *clock, *anti, *insert;
  anti = current->next;
  clock = anti->next;

  insert = (struct marble *) malloc(sizeof(struct marble));
  insert->next = clock;
  insert->prev = anti;
  insert->value = score;

  anti->next = insert;
  clock->prev = insert;
  return insert;
}

int main(int argc, char const *argv[]) {
  struct marble *current, *m;
  int score[PLAYERS], i, turn = 0, count = 1;

  for(i = 0; i < PLAYERS; i++) //INITIALISE score[]
  {
    score[i] = 0;
  }

  m = (struct marble *) malloc(sizeof(struct marble));
  m->next = m; //SETUP ROOT MARBLE
  m->prev = m;
  m->value = 0;
  current = m;

  //printMarbles(current, -1);
  while(count <= MAX_MARBLE)
  {
    if(count % 23 == 0)
    {
      score[turn] += count;
      /*i = scoreMarble(&current);
      printf("SCORE\telf %d scoring marble %d + marble %d\n", turn, count, i);
      score[turn] += i;
      printMarbles(current, turn);*/
      score[turn] += scoreMarble(&current);
    }
    else
    {
      current = insertMarble(current, count);
      //printMarbles(current, turn);
    }
    if(++turn == PLAYERS)
    {
      turn = 0;
    }
    count++;
  }

  i = 0;
  for(turn = 0; turn < PLAYERS; turn++)
  {
    if(score[turn] > i)
    {
      i = score[turn];
    }
  }

  printf("Highest score = %d\n", i);
  return 0;
}
