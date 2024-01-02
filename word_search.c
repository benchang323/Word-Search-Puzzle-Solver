// word_search.c
// Benjamin Chang
// bchang26
#include <stdio.h>
#include <ctype.h>
#include "search_functions.h"

/*
 * This is the HW3 main function that performs a word search.
 */
int main(int argc, char* argv[]){
  //If the command line argument does not contain file name, return 1
  if (argc != 2){
    printf("Please enter a command line argument.\n");
    return 1;
  }

  //Prompt user for input and store it in word[]
  char word[MAX_SIZE];
  int a = scanf("%s", word);

  //Loop until the user enters ^d, then exit
  while(a != EOF)
  {
    //The program should be case insensitive in its search
    for (int i = 0; word[i] != '\0'; i++){
      word[i] = tolower(word[i]);
    }

    //Initialize grid
    char grid[MAX_SIZE][MAX_SIZE] = {0};
    char t_grid[MAX_SIZE][MAX_SIZE] = {0};

    //Populate grid
    int n = populate_grid(grid, t_grid, argv[1]);
    
    //Check status of populate_grid
    if (n == -1){
      printf("Grid file failed to open.\n");
      return -1;
    }
    else if (n == -2){
      printf("Invalid grid.\n");
      return -2;
    }
    else {
      //Create an open stream file to write to
      FILE *out = fopen("output.txt", "w");
      int status = find_all(grid, t_grid, n, word, out);
      fclose(out);
      if (status == 1) {
        printf("'%s' - not found.\n", word);
      }
      else if (status == 0) {
        //Print out the output.txt file
        FILE *print = fopen("output.txt", "r");
        char c;
        while ((c = fgetc(print)) != EOF){
          printf("%c", c);
        }
        fclose(print);
      }
    }
    a = scanf("%s", word);
  }
  return 0;
}