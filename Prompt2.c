/*
 ============================================================================
 Name        : Prompt2.c
 Author      : Rahul M. Juliato
 Version     : 0.2 (Added Sorting)
 Copyright   : RMJ 2021 - GPL3
 Description : Implements a Linked List in C and perform operations
               On the prompt use the commands:
	       put X
	       remove Y
	       get Y
	       first
	       last
	       list
	       clear
	       exit
	       Where X is an integer content and Y is an integer position

	       On Linux/UNIX like systems compile and execute with:
	       $ gcc Promp2.c -o teste2 && ./teste2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Creates the type Array (Dinamic List) and list "a" */
typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

Array a;


/* Functions Prototypes */
void init();
void put();
void get();
void first();
void last();
void rem();
void list();
void clear();
void print_auxiliares();
int get_args();
void sort();


/* Aux Functions */
void print_entry(char *entry) {
	printf("You entered: %s\n", entry);	
}

int get_args(char complete[], int from, int len){
  int c = 0;
  char* sub = malloc(len+1);
  
  while (c < len){
    sub[c] = complete[from+c-1];
    c++;
  }
  sub[c] = '\0';
  return atoi(sub); 
}


/* Array work functions */
void init(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used  = 0;
  a->size = initialSize;
}


void put(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void rem(int position) {
  int i;
  Array temp;
  init(&temp,10);
  for (i = 0; i < a.used; i++) {
    if (i != (position - 1)){
      put(&temp, a.array[i]);
    }
  }
  a = temp;
  printf("%d\n", position);
  list();
}

void get(int position) {
  position -= 1;
  if (position <= a.used) {
    printf("%d\n", a.array[position]);
  }
}

void first(){
   printf("%d\n", a.array[0]);
}

void last(){
  printf("%d\n", a.array[a.used - 1]);
}

void list() {
  int i;
  if (a.used > 0) {
    for (i = 0; i < a.used; i++ ) {
      printf("%d ", a.array[i]);
    }
    printf("\n");
  }
}

void clear(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void sort() {
  int sorting[100], i, j, n, swap;
  
  n = a.used;

  /* Populate array to sort */
  for (i = 0; i < n; i++) {
    sorting[i] = a.array[i];
  }

  /* Sort */
  for (i = 0; i < n; i++) {
    for (j = 0; j < (n - i - 1); j++) {
      if (sorting[j] > sorting[j+1])  {
	  swap = sorting[j];
	  sorting[j] = sorting[j+1];
	  sorting[j+1] = swap;
	}
    }
  }

  /* Populate results back to list */

  clear(&a);
  for (i = 0; i < n; i++) {
    put(&a, sorting[i]);
  }

  list();
}



/* Main */

int main(int argc, char *argv[]) {
	char input[201];
	char sub[201];
	init(&a, 5); 
	
	while(1) {
		printf("prompt> ");
		if (fgets(input, 200, stdin) == NULL) {
		  printf("An error ocurred.\n");
		  break;
		}

		if (strncmp(input, "exit\n", 5) == 0) {
		  printf("Leaving. Good bye.\n");
		  break;
		}

		if (strncmp(input, "put", 3) == 0) {
		  put(&a, get_args(input, 4, strlen(input)));
		  printf("%d\n", get_args(input, 4, strlen(input)));
		}

		if (strncmp(input, "get", 3) == 0) {
		  get(get_args(input, 4, strlen(input)));
		}

		if (strncmp(input, "remove", 6) == 0) {
		  rem(get_args(input, 7, strlen(input)));
		}

		if (strncmp(input, "list", 4) == 0) {
		  list();
		}

		if (strncmp(input, "clear", 5) == 0) {
		  clear(&a);
		}

		if (strncmp(input, "first", 5) == 0) {
		  first();
		}

		if (strncmp(input, "last", 4) == 0) {
		  last();
		}

      		if (strncmp(input, "sort", 4) == 0) {
		  sort();
		}
		
	}

	return EXIT_SUCCESS;
}

