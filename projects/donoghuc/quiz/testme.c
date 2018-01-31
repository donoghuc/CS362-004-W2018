#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// return a psudo random integer in given range (inclusive)
int rand_between(int min, int max){
    return rand() % (max + 1 - min) + min;
}

// return a psudo random character from array defined below
char inputChar()
{
    // possible chars that will increment state plus one that wont...
    char c_set[10] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']', '_'};
    return c_set[rand_between(0,9)];
}

// note that this function must return a pointer to a string. A safe way to do this is to use
// static memory. In this case an array of 6 chars is staticly generated and filled with a random
// scramble of the string "reset"
char *inputString()
{
    // set of characters to pick from 
    char string_set[5] = {'r','e','s','e','t'};
    // staticly allocate this so it can be pointed to 
    static char scrambled_set[6];
    //counters for picking without replacement
    int str_set_len = 4;
    int counter = 0;
    int rand_index;
    // algorithm to choose from string set without replacement
    while (str_set_len >= 0) {
        rand_index = rand_between(0, str_set_len);
        scrambled_set[counter] = string_set[rand_index];
        counter++;
        for (int i = rand_index; i < str_set_len; i++) {
          string_set[i] = string_set[i+1];
        }
        str_set_len--;
    }
    // ensure string is null terminated and return
    scrambled_set[5] = '\0';
    return scrambled_set;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
