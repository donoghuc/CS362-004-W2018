#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// return a psudo random integer in given range (inclusive)
int rand_between(int min, int max){
    return rand() % (max + 1 - min) + min;
}
// // c is the devil
// void scramble_string(char *return_this){

//     char string_set[5] = {'r','e','s','e','t'};
//     char scrambled_set[6];
//     int str_set_len = 4;
//     int counter = 0;
//     int rand_index;

//     while (str_set_len >= 0) {
//       rand_index = rand_between(0, str_set_len);
//       scrambled_set[counter] = string_set[rand_index];
//       printf("%c, %d, %d, %d\n",string_set[rand_index],counter,str_set_len,rand_index);
//       counter++;

//       for (int i = rand_index; i < str_set_len; i++) {
//         string_set[i] = string_set[i+1];
//       }
//       str_set_len--;
//     }
//     printf("%s\n", scrambled_set);
//     strncpy(return_this, scrambled_set, 6)
//   // char* myFunction(char * buf, int buf_len){
//   // strncpy(buf, "my string", buf_len);
//   // return buf;
// }


// return a psudo random character from array defined below
char inputChar()
{
    char c_set[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
    return c_set[rand_between(0,8)];
}

// building 
char *inputString()
{
    int x;
    x = rand_between(0,3);

    static char * s_set[] = {"reset", "not_reset", "shut_down", "restart"};
    return s_set[x];

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
