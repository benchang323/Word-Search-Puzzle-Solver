// search_functions.c
// Benjamin Chang
// bchang26
#include <stdio.h>
#include <string.h>
#include "search_functions.h"

/* 
 * Given a filename and a MAX_SIZExMAX_SIZE grid to fill, this function 
 * populates the grid and returns n, the actual grid dimension. 
 * If filename_to_read_from can't be opened, this function returns -1.
 * If the file contains an invalid grid, this function returns -2.
 */
int populate_grid(char grid[][MAX_SIZE], char t_grid[][MAX_SIZE], char filename_to_read_from[]) {
  //If file_name_to_read_from can't be opened, return -1
  FILE *file = fopen(filename_to_read_from, "r");
  if (ferror(file)){
    return -1;
  }

  //Store content from file into a temporary 1D array, where \n is replaced with *
  char temp[(MAX_SIZE) * (MAX_SIZE)];
  for (int i = 0; i < (MAX_SIZE) * (MAX_SIZE); i++){
    temp[i] = fgetc(file);
    if (temp[i] == '\n'){
      temp[i] = '*';
    }
    // Remove all non-ASCII characters
    if ((int)temp[i] < 32 || (int)temp[i] > 126){
      temp[i] = 0;
    }
  }

  //Get location of all * in the array
  int star_locations[strlen(temp)];
  int star_count = 0;
  for (int i = 0; i < (int)strlen(temp); i++){
    if (temp[i] == '*'){
      star_locations[star_count] = i;
      star_count++;
    }
  }

  /* In any of the following cases, your program should output "Invalid grid." and exit with return value -2:
  1. if two of the grid rows have differing numbers of letters
  2. if the number of rows doesn't match the number of columns
  3. if the number of rows (and columns) is 0 or greater than 10 */

  //1. if two of the grid rows have differing numbers of letters
  //Check if the interval between the locations are the same, if not, return -2
  int interval = star_locations[1] - star_locations[0];
  for (int i = 1; i < star_count; i++){
    if (star_locations[i] - star_locations[i - 1] != interval){
      return -2;
    } 
  }

  //2. if the number of rows doesn't match the number of columns
  //Check if interval-1 is equal to the number of astericks
  if (interval - 1 != star_count){
    return -2;
  }

  //3. if the number of rows (and columns) is 0 or greater than 10
  //Check if number of astericks is more than 10 or less than and equal to 0
  if (star_count > 10 || star_count <= 0){
    return -2;
  }

  //Condense the 1D array into a 2D array, where * separates the rows
  int n = 0;
  int count = 0;
  for (int i = 0; i < (int)strlen(temp); i++){
    if (temp[i] == '*'){
      n++;
      count = 0;
    }
    else {
      grid[n][count] = temp[i];
      count++;
    }
  }

  //Transpose the grid to create t_grid
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      t_grid[j][i] = grid[i][j];
    }
  }
  return star_count;
}

/* 
 * The function returns the number of times the given word string was found in the grid facing down.
 * The function sends corresponding output to specified file pointer, which points to an open stream. 
 * Output lines appear in order of the first characcter's appearance in a left-to-right scan of each row beginning with row 0
 *
 * Parameters:
 *    grid: a MAX_SIZExMAX_SIZE grid of characters
 *    n: the actual size of grid
 *    word: a word to search for
 *    *write_to: an open stream file pointer
 * 
 * Returns:
 *  1 if the word was not found, 0 otherwise
 */
int find_down (char t_grid[][MAX_SIZE], int n, char word[], FILE *write_to){
  //Search for word in temp_grid from up to down using find_right function
  int status = find_right(t_grid, n, word, write_to, 1);
  
  //Return status         
  if (status == 1){
    return 1;
  }
  return 0;
}

/* 
 * The function returns the number of times the given word string was found in the grid facing up.
 * The function sends corresponding output to specified file pointer, which points to an open stream. 
 * Output lines appear in order of the first characcter's appearance in a left-to-right scan of each row beginning with row 0
 *
 * Parameters:
 *    grid: a MAX_SIZExMAX_SIZE grid of characters
 *    n: the actual size of grid
 *    word: a word to search for
 *    *write_to: an open stream file pointer
 * 
 * Returns:
 *   1 if the word was not found, 0 otherwise
 */
int find_up (char t_grid[][MAX_SIZE], int n, char word[], FILE *write_to){ 
  //Search for word in temp_grid from down to up using find_left function
  int status = find_left(t_grid, n, word, write_to, 1); //something is wrong with this

  //Return status
  if (status == 1){
    return 1;
  }
  return 0;
}

/* 
 * The function returns the number of times the given word string was found in the grid facing right.
 * The function sends corresponding output to specified file pointer, which points to an open stream. 
 * Output lines appear in order of the first characcter's appearance in a left-to-right scan of each row beginning with row 0
 *
 * Parameters:
 *    grid: a MAX_SIZExMAX_SIZE grid of characters
 *    n: the actual size of grid
 *    word: a word to search for
 *    *write_to: an open stream file pointer
 *    dir: output is reversed if dir is 1
 * 
 * Returns: 
 *   1 if the word was not found, 0 otherwise
 */
int find_right(char grid[][MAX_SIZE], int n, char word[], FILE *write_to, int dir){
  //Status indicates if the word was found
  int status = 1;
  //Search for word in grid from left to right
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      //If the first letter of word is found, check if the rest of the word is found
      if (grid[i][j] == word[0]){ 
        int k = 0;
        while (grid[i][j+k] == word[k] && k+j < n){
          k++;
        }
        //If the rest of the word is found, print results to write_to, an open stream
        if (k == (int)strlen(word)){
          if (dir == 1){
            fprintf(write_to, "%s %d %d D\n", word, j, i);
          }
          else {
            fprintf(write_to, "%s %d %d R\n", word, i, j);
          }
          status = 0;
        }
      }
    }
  }

  //Return status
  if (status == 1){
    return 1;
  }
  return 0;
} 

/* 
 * The function returns the number of times the given word string was found in the grid facing left.
 * The function sends corresponding output to specified file pointer, which points to an open stream. 
 * Output lines appear in order of the first characcter's appearance in a left-to-right scan of each row beginning with row 0
 *
 * Parameters:
 *    grid: a MAX_SIZExMAX_SIZE grid of characters
 *    n: the actual size of grid
 *    word: a word to search for
 *    *write_to: an open stream file pointer
 *    dir: output is reversed if dir is 1
 * 
 * Returns:
 *  1 if the word was not found, 0 otherwise
 */
int find_left (char grid[][MAX_SIZE], int n, char word[], FILE *write_to, int dir){
  //Status indicates if the word was found
  int status = 1;
  //Search for word in grid from left to right
  for (int i = 0; i < n; i++){
    for (int j = n-1; j >= 0; j--){
      //If the first letter of word is found, check if the rest of the word is found
      if (grid[i][j] == word[0]){ 
        int k = 0;
        while (grid[i][j-k] == word[k] && j-k >= 0){
          k++;
        }
        //If the rest of the word is found, print results to write_to, an open stream
        if (k == (int)strlen(word)){
          if (dir == 1){
            fprintf(write_to, "%s %d %d U\n", word, j, i);
          }
          else {
            fprintf(write_to, "%s %d %d L\n", word, i, j);
          }
          status = 0;
        }
      }
    }
  }

  //Return status
  if (status == 1){
    return 1;
  }
  return 0;
}

/* 
 * The function returns the number of times the given word string was found in the grid. This function is similar to the other 4 find_functions above, 
 * but reports ALL appearances of the given word, in the required R,L,D,U order.
 * The function sends corresponding output to specified file pointer, which points to an open stream. 
 * Output lines appear in order of the first characcter's appearance in a left-to-right scan of each row beginning with row 0
 *
 * Parameters:
 *    grid: a MAX_SIZExMAX_SIZE grid of characters
 *    n: the actual size of grid
 *    word: a word to search for
 *    *write_to: an open stream file pointer
 * 
 * Returns:
 *   1 if the word was not found, 0 otherwise
 */
int find_all (char grid[][MAX_SIZE], char t_grid[][MAX_SIZE], int n, char word[], FILE *write_to) {
  //Initialize status
  int status = 0;

  //Right
  status += find_right(grid, n, word, write_to, 0);
  //Left
  status += find_left(grid, n, word, write_to, 0);
  //Down
  status += find_down(t_grid, n, word, write_to);
  //Up
  status += find_up(t_grid, n, word, write_to);

  //Return status
  if (status == 4){
    return 1;
  }
  return 0;
} 

/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match. The definition of this function is provided 
 * for you.
 */
int file_eq(char lhs_name[], char rhs_name[]) {
  FILE* lhs = fopen(lhs_name, "r");
  FILE* rhs = fopen(rhs_name, "r");

  // don't compare if we can't open the files
  if (lhs == NULL || rhs == NULL) return 0;

  int match = 1;
  // read until both of the files are done or there is a mismatch
  while (!feof(lhs) || !feof(rhs)) {
	if (feof(lhs) ||                      // lhs done first
		feof(rhs) ||                  // rhs done first
		(fgetc(lhs) != fgetc(rhs))) { // chars don't match
	  match = 0;
	  break;
	  }
  }
  fclose(lhs);
  fclose(rhs);
  return match;
}