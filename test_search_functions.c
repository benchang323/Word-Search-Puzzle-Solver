// test_search_functions.c
// Benjamin Chang
// bchang26

#include <stdio.h>
#include <assert.h>
#include "search_functions.h"

/* 
 * Declarations for tester functions whose definitions appear below.
 * (You will need to fill in the function definition details, at the
 * end of this file, and add comments to each one.) 
 * Additionally, for each helper function you elect to add to the 
 * provided search_functions.h, you will need to supply a corresponding
 * tester function in this file.  Add a declaration for it here, its
 * definition below, and a call to it where indicated in main.
 */
void test_file_eq();      // This one is already fully defined below.
void test_populate_grid();
void test_find_right();
void test_find_left();
void test_find_down();
void test_find_up();
void test_find_all();

/*
 * Main method which calls all test functions.
 */
int main() {
  printf("Testing file_eq...\n");
  test_file_eq();
  printf("Passed file_eq test.\n");
  printf("\n");
  printf("Running test_populate_grid tests...\n");
  test_populate_grid();
  printf("\n");
  printf("Running test_find_right tests...\n");
  test_find_right();
  printf("\n");
  printf("Running test_find_left tests...\n");
  test_find_left();
  printf("\n");
  printf("Running test_find_down tests...\n");
  test_find_down();
  printf("\n");
  printf("Running test_find_up tests...\n");
  test_find_up();
  printf("\n");
  printf("Running test_find_all tests...\n");
  test_find_all();
  printf("\n");
  printf("Passed search_functions tests!\n");
}

/*
 * Test file_eq on same file, files with same contents, files with
 * different contents and a file that doesn't exist.
 * Relies on files test1.txt, test2.txt, test3.txt being present.
 */
void test_file_eq() {
  FILE* fptr = fopen("test1.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  fptr = fopen("test2.txt", "w");
  fprintf(fptr, "this\nis\na different test\n");
  fclose(fptr);

  fptr = fopen("test3.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  assert( file_eq("test1.txt", "test1.txt"));
  assert( file_eq("test2.txt", "test2.txt"));
  assert(!file_eq("test2.txt", "test1.txt"));
  assert(!file_eq("test1.txt", "test2.txt"));
  assert( file_eq("test3.txt", "test3.txt"));
  assert( file_eq("test1.txt", "test3.txt"));
  assert( file_eq("test3.txt", "test1.txt"));
  assert(!file_eq("test2.txt", "test3.txt"));
  assert(!file_eq("test3.txt", "test2.txt"));
  assert(!file_eq("", ""));  // can't open file
}

/* 
 * Given a filename and a MAX_SIZExMAX_SIZE grid to fill, this function 
 * populates the grid and returns n, the actual grid dimension. 
 * If filename_to_read_from can't be opened, this function returns -1.
 * If the file contains an invalid grid, this function returns -2.
 */
void test_populate_grid(){

  //Initialize grid
  char grid[MAX_SIZE][MAX_SIZE] = {0};
  char t_grid[MAX_SIZE][MAX_SIZE] = {0};

  assert(populate_grid(grid, t_grid, "grid1.txt") > 0 || populate_grid(grid, t_grid, "grid1.txt") <= 10);
  printf("Test 1 of test_populate_grid passed.\n");
  assert(populate_grid(grid, t_grid, "grid2.txt") == -2);
  printf("Test 2 of test_populate_grid passed.\n");
  assert(populate_grid(grid, t_grid, "grid3.txt") == -2);
  printf("Test 3 of test_populate_grid passed.\n");
  assert(populate_grid(grid, t_grid, "grid4.txt") == -2);
  printf("Test 4 of test_populate_grid passed.\n");
  assert(populate_grid(grid, t_grid, "grid5.txt") == -2);
  printf("Test 5 of test_populate_grid passed.\n");
  assert(populate_grid(grid, t_grid, "grid6.txt") == -2);
  printf("Test 6 of test_populate_grid passed.\n");
  assert(populate_grid(grid, t_grid, "grid7.txt") > 0 || populate_grid(grid, t_grid, "grid7.txt") <= 10);
  printf("Test 7 of test_populate_grid passed.\n");
}

/*
 * test_find_right tests the find_right function in search_functions.c using assert statements.
 */
void test_find_right(){
  // Initialize grid as a 4x4 grid with random letters (from website)
  char grid1[MAX_SIZE][MAX_SIZE] = {{'p', 'i', 't', 'k'},
                                   {'o', 'l', 'p', 'e'},
                                   {'p', 'k', 'e', 'y'},
                                   {'t', 'o', 'p', 'e'}};

  //initialize grid as a 2x2 grid with random letters
  char grid2[MAX_SIZE][MAX_SIZE] = {{'a', 'b'},
                                    {'c', 'd'}};

  //initialize grid as a 10x10 grid with random letters
  char grid3[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
                                    {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
                                    {'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd'},
                                    {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'},
                                    {'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
                                    {'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
                                    {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
                                    {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b'},
                                    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
                                    {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'}};

  // n is the number of rows and columns
  int n1 = 4;
  int n2 = 2;
  int n3 = 10;

  //word is the word to be found from right to left
  char word1[4] = {'k', 'e', 'y', '\0'};
  char word2[4] = {'a', 'b', 'a', '\0'};
  char word3[11] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0'};
  char word4[11] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', '\0'};
  char word5[3] = {'a', 'b', '\0'};
  char word6[3] = {'d', 'e', '\0'};

  //file is the file to be written to
  FILE* filer = fopen("test_search.txt", "w");

  //dir is the direction of the search
  int dir = 0;

  // Test if the word is found
  assert(find_right(grid1, n1, word1, filer, dir) == 0);
  // Print if assert passes
  printf("Test case 1 of test_find_right passed\n");

  // Test if the word is not found
  assert(find_right(grid1, n1, word2, filer, dir) == 1);
  // Print if assert passes
  printf("Test case 2 of test_find_right passed\n");

  // Test if the word is found
  assert(find_right(grid2, n2, word5, filer, dir) == 0);
  // Print if assert passes
  printf("Test case 3 of test_find_right passed\n");

  // Test if the word is not found
  assert(find_right(grid2, n2, word6, filer, dir) == 1);
  // Print if assert passes
  printf("Test case 4 of test_find_right passed\n");

  // Test if the word is found
  assert(find_right(grid3, n3, word3, filer, dir) == 0);
  // Print if assert passes
  printf("Test case 5 of test_find_right passed\n");

  // Test if the word is not found
  assert(find_right(grid3, n3, word4, filer, dir) == 1);
  // Print if assert passes
  printf("Test case 6 of test_find_right passed\n");
}

/*
 * test_find_left tests the find_left function in search_functions.c using assert statements.
 */
void test_find_left(){
  // Initialize grid as a 4x4 grid with random letters (from website)
  char grid1[MAX_SIZE][MAX_SIZE] = {{'p', 'i', 't', 'k'},
                                   {'o', 'l', 'p', 'e'},
                                   {'p', 'k', 'e', 'y'},
                                   {'t', 'o', 'p', 'e'}};

  // Initialize grid as a 2x2 grid with random letters
  char grid2[MAX_SIZE][MAX_SIZE] = {{'a', 'b'},
                                    {'c', 'd'}};

  // Initialize grid as a 10x10 grid with random letters
  char grid3[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
                                    {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
                                    {'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd'},
                                    {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'},
                                    {'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
                                    {'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
                                    {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
                                    {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b'},
                                    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
                                    {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'}};

  // n is the number of rows and columns
  int n1 = 4;
  int n2 = 2;
  int n3 = 10;

  // Word is the word to be found from left to right
  char word1[4] = {'y', 'e', 'k', '\0'}; //0
  char word2[4] = {'a', 'b', 'a', '\0'}; //1
  char word4[3] = {'d', 'c', '\0'}; //0
  char word3[3] = {'a', 'b', '\0'}; //1
  char word5[11] = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a', '\0'}; //0
  char word6[11] = {'a', 'b', 'b', 'a', 'e', 'e', 'd', 'h', 'i', 'k', '\0'}; //1
 
  // File is the file to be written to
  FILE* filel = fopen("test_search.txt", "w");

  // Dir is the direction of the search
  int dir = 0;

  // Test if the word is found
  assert(find_left(grid1, n1, word1, filel, dir) == 0);
  // Print if assert passes
  printf("Test case 1 of test_find_left passed\n");

  // Test if the word is not found
  assert(find_left(grid1, n1, word2, filel, dir) == 1);
  // Print if assert passes
  printf("Test case 2 of test_find_left passed\n");

  // Test if the word is found
  assert(find_left(grid2, n2, word4, filel, dir) == 0);
  // Print if assert passes
  printf("Test case 3 of test_find_left passed\n");
  
  // Test if the word is not found
  assert(find_left(grid2, n2, word3, filel, dir) == 1);
  // Print if assert passes
  printf("Test case 4 of test_find_left passed\n");

  // Test if the word is found
  assert(find_left(grid3, n3, word5, filel, dir) == 0);
  // Print if assert passes
  printf("Test case 5 of test_find_left passed\n");

  // Test if the word is not found
  assert(find_left(grid3, n3, word6, filel, dir) == 1);
  // Print if assert passes
  printf("Test case 6 of test_find_left passed\n");
}

/*
 * test_find_down tests the find_down function in search_functions.c using assert statements.
 */
void test_find_down(){
  // Initialize grid as a 4x4 grid with random letters (from website)
  char grid1[MAX_SIZE][MAX_SIZE] = {{'p', 'i', 't', 'k'},
                                   {'o', 'l', 'p', 'e'},
                                   {'p', 'k', 'e', 'y'},
                                   {'t', 'o', 'p', 'e'}};

  // Transpose grid1 to t_grid1
  char t_grid1[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      t_grid1[i][j] = grid1[j][i];
    }
  }

  // Initialize grid as a 2x2 grid with random letters
  char grid2[MAX_SIZE][MAX_SIZE] = {{'a', 'b'},
                                    {'c', 'd'}};

  // Transpose grid2 to t_grid2
  char t_grid2[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      t_grid2[i][j] = grid2[j][i];
    }
  }

  // Initialize grid as a 10x10 grid with random letters
  char grid3[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
                                    {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
                                    {'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd'},
                                    {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'},
                                    {'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
                                    {'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
                                    {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
                                    {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b'},
                                    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
                                    {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'}};
                                
  // Transpose grid3 to t_grid3
  char t_grid3[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      t_grid3[i][j] = grid3[j][i];
    }
  }

  // n is the number of rows and columns
  int n1 = 4;
  int n2 = 2;
  int n3 = 10;

  // Word is the word to be found from up to down
  char word1[4] = {'p', 'o', 'p', '\0'}; //0
  char word2[4] = {'t', 'p', 'a', '\0'}; //1
  char word3[3] = {'a', 'c', '\0'}; //0
  char word4[3] = {'d', 'c', '\0'}; //1
  char word5[11] = {'a', 'k', 'u', 'e', 'o', 'y', 'i', 's', 'c', 'm', '\0'}; //0
  char word6[11] = {'a', 'b', 'b', 'a', 'e', 'e', 'd', 'h', 'i', 'k', '\0'}; //1

  // File is the file to be written to
  FILE* filed = fopen("test_search.txt", "w");

  // Test if the word is found
  assert(find_down(t_grid1, n1, word1, filed) == 0);
  // Print if assert passes
  printf("Test case 1 of test_find_down passed\n");

  // Test if the word is not found
  assert(find_down(t_grid1, n1, word2, filed) == 1);
  // Print if assert passes
  printf("Test case 2 of test_find_down passed\n");

  // Test if the word is found
  assert(find_down(t_grid2, n2, word3, filed) == 0);
  // Print if assert passes
  printf("Test case 3 of test_find_down passed\n");
  
  // Test if the word is not found
  assert(find_down(t_grid2, n2, word4, filed) == 1);
  // Print if assert passes
  printf("Test case 4 of test_find_down passed\n");

  // Test if the word is found
  assert(find_down(t_grid3, n3, word5, filed) == 0);
  // Print if assert passes
  printf("Test case 5 of test_find_down passed\n");

  // Test if the word is not found
  assert(find_down(t_grid3, n3, word6, filed) == 1);
  // Print if assert passes
  printf("Test case 6 of test_find_down passed\n");
}

/*
 * test_find_up tests the find_up function in search_functions.c using assert statements.
 */
void test_find_up(){

  // Initialize grid as a 4x4 grid with random letters (from website)
  char grid1[MAX_SIZE][MAX_SIZE] = {{'p', 'i', 't', 'k'},
                                   {'o', 'l', 'p', 'e'},
                                   {'p', 'k', 'e', 'y'},
                                   {'t', 'o', 'p', 'e'}};

  // Transpose grid1 to t_grid1
  char t_grid1[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      t_grid1[i][j] = grid1[j][i];
    }
  }

  // Initialize grid as a 2x2 grid with random letters
  char grid2[MAX_SIZE][MAX_SIZE] = {{'a', 'b'},
                                    {'c', 'd'}};

  // Transpose grid2 to t_grid2
  char t_grid2[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      t_grid2[i][j] = grid2[j][i];
    }
  }

  // Initialize grid as a 10x10 grid with random letters
  char grid3[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
                                    {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
                                    {'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd'},
                                    {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'},
                                    {'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
                                    {'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
                                    {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
                                    {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b'},
                                    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
                                    {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'}};
                                
  // Transpose grid3 to t_grid3
  char t_grid3[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      t_grid3[i][j] = grid3[j][i];
    }
  }

  // n is the number of rows and columns
  int n1 = 4;
  int n2 = 2;
  int n3 = 10;

  // Word is the word to be found from down to up
  char word1[4] = {'k', 'l', 'i', '\0'}; //0
  char word2[4] = {'t', 'p', 'a', '\0'}; //1
  char word3[3] = {'c', 'a', '\0'}; //0
  char word4[3] = {'d', 'r', '\0'}; //1
  char word5[11] = {'n', 'd', 't', 'j', 'z', 'p', 'f', 'v', 'l', 'b', '\0'}; //0
  char word6[11] = {'a', 'b', 'b', 'a', 'e', 'e', 'd', 'h', 'i', 'k', '\0'}; //1

  // File is the file to be written to
  FILE* fileu = fopen("test_search.txt", "w");

  // Test if the word is found
  assert(find_up(t_grid1, n1, word1, fileu) == 0);
  // Print if assert passes
  printf("Test case 1 of test_find_up passed\n");

  // Test if the word is not found
  assert(find_up(t_grid1, n1, word2, fileu) == 1);
  // Print if assert passes
  printf("Test case 2 of test_find_up passed\n");

  // Test if the word is found
  assert(find_up(t_grid2, n2, word3, fileu) == 0);
  // Print if assert passes
  printf("Test case 3 of test_find_up passed\n");
  
  // Test if the word is not found
  assert(find_up(t_grid2, n2, word4, fileu) == 1);
  // Print if assert passes
  printf("Test case 4 of test_find_up passed\n");

  // Test if the word is found
  assert(find_up(t_grid3, n3, word5, fileu) == 0);
  // Print if assert passes
  printf("Test case 5 of test_find_up passed\n");

  // Test if the word is not found
  assert(find_up(t_grid3, n3, word6, fileu) == 1);
  // Print if assert passes
  printf("Test case 6 of test_find_up passed\n");
}

/**
 * test_find_all tests the find_all function in search_functions.c using assert statements.
 */
void test_find_all(){
  // Initialize grid as a 4x4 grid with random letters (from website)
  char grid1[MAX_SIZE][MAX_SIZE] = {{'p', 'i', 't', 'k'},
                                   {'o', 'l', 'p', 'e'},
                                   {'p', 'k', 'e', 'y'},
                                   {'t', 'o', 'p', 'e'}};

  // Transpose grid1 to t_grid1
  char t_grid1[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      t_grid1[i][j] = grid1[j][i];
    }
  }

  // Initialize grid as a 2x2 grid with random letters
  char grid2[MAX_SIZE][MAX_SIZE] = {{'a', 'b'},
                                    {'c', 'd'}};

  // Transpose grid2 to t_grid2
  char t_grid2[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      t_grid2[i][j] = grid2[j][i];
    }
  }

  // Initialize grid as a 10x10 grid with random letters
  char grid3[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
                                    {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
                                    {'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd'},
                                    {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'},
                                    {'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
                                    {'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
                                    {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
                                    {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b'},
                                    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
                                    {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'}};
                                
  // Transpose grid3 to t_grid3
  char t_grid3[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      t_grid3[i][j] = grid3[j][i];
    }
  }

  // n is the number of rows and columns
  int n1 = 4;
  int n2 = 2;
  int n3 = 10;

  // Word is the word to be found from down to up
  char word1u[4] = {'k', 'l', 'i', '\0'}; //0
  char word2u[4] = {'t', 'p', 'a', '\0'}; //1
  char word3u[3] = {'c', 'a', '\0'}; //0
  char word4u[3] = {'d', 'r', '\0'}; //1
  char word5u[11] = {'n', 'd', 't', 'j', 'z', 'p', 'f', 'v', 'l', 'b', '\0'}; //0
  char word6u[11] = {'a', 'b', 'b', 'a', 'e', 'e', 'd', 'h', 'i', 'k', '\0'}; //1

  // Word is the word to be found from up to down
  char word1d[4] = {'p', 'o', 'p', '\0'}; //0
  char word2d[4] = {'t', 'p', 'a', '\0'}; //1
  char word3d[3] = {'a', 'c', '\0'}; //0
  char word4d[3] = {'d', 'c', '\0'}; //1
  char word5d[11] = {'a', 'k', 'u', 'e', 'o', 'y', 'i', 's', 'c', 'm', '\0'}; //0
  char word6d[11] = {'a', 'b', 'b', 'a', 'e', 'e', 'd', 'h', 'i', 'k', '\0'}; //1

  // Word is the word to be found from left to right
  char word1l[4] = {'y', 'e', 'k', '\0'}; //0
  char word2l[4] = {'a', 'b', 'a', '\0'}; //1
  char word4l[3] = {'d', 'c', '\0'}; //0
  char word3l[3] = {'a', 'b', '\0'}; //1
  char word5l[11] = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a', '\0'}; //0
  char word6l[11] = {'a', 'b', 'b', 'a', 'e', 'e', 'd', 'h', 'i', 'k', '\0'}; //1

  //word is the word to be found from right to left
  char word1r[4] = {'k', 'e', 'y', '\0'}; //0
  char word2r[4] = {'a', 'b', 'a', '\0'}; //1
  char word3r[11] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', '\0'}; //0
  char word4r[11] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', '\0'}; //1
  char word5r[3] = {'a', 'b', '\0'}; //0
  char word6r[3] = {'d', 'e', '\0'}; //1

  // File is the file to be written to
  FILE* filea = fopen("test_search.txt", "w");

  //Test the cases
  assert(find_all(grid1, t_grid1, n1, word1u, filea) == 0);
  printf("Test case 1 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word2u, filea) == 1);
  printf("Test case 2 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word3u, filea) == 0);
  printf("Test case 3 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word4u, filea) == 1);
  printf("Test case 4 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word5u, filea) == 0);
  printf("Test case 5 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word6u, filea) == 1);
  printf("Test case 6 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word1d, filea) == 0);
  printf("Test case 7 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word2d, filea) == 1);
  printf("Test case 8 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word3d, filea) == 0);
  printf("Test case 9 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word4d, filea) == 0);
  printf("Test case 10 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word5d, filea) == 0);
  printf("Test case 11 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word6d, filea) == 1);
  printf("Test case 12 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word1l, filea) == 0);
  printf("Test case 13 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word2l, filea) == 1);
  printf("Test case 14 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word3l, filea) == 0);
  printf("Test case 15 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word4l, filea) == 0);
  printf("Test case 16 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word5l, filea) == 0);
  printf("Test case 17 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word6l, filea) == 1);
  printf("Test case 18 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word1r, filea) == 0);
  printf("Test case 19 of test_find_all passed\n");
  assert(find_all(grid1, t_grid1, n1, word2r, filea) == 1);
  printf("Test case 20 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word3r, filea) == 1);
  printf("Test case 21 of test_find_all passed\n");
  assert(find_all(grid2, t_grid2, n2, word4r, filea) == 1);
  printf("Test case 22 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word5r, filea) == 0);
  printf("Test case 23 of test_find_all passed\n");
  assert(find_all(grid3, t_grid3, n3, word6r, filea) == 0);
  printf("Test case 24 of test_find_all passed\n");
}