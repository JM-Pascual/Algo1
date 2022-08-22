#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50


void imprimir_vector(int vector[MAX_VECTOR], int tope_vector){

  printf("\n(");

  for (int i = 0; i < tope_vector; i++){

      printf(" %i", vector[i]);
  }

  printf(" )\n");
}


void quicksort (int vector[MAX_VECTOR], int inicio ,int tope) {
  int i;
  int j;
  int pivot;
  int temp;
  int ultimo = tope -1;

  if (inicio < ultimo) {
   pivot = inicio ; // Elige el pivote
   i = inicio;
   j = ultimo;

  while (i < j) {
    while ((vector[i] <= vector[pivot] ) && (i < ultimo ) )
   i++;
    while (vector[j] > vector[pivot])
     j--;
        if (i < j) {
            temp = vector[i];
            vector[i] = vector[j];
            vector[j] = temp ;
        }
  }

  temp = vector[pivot];
  vector[pivot] = vector[j];
  vector[j] = temp ;
  quicksort(vector, inicio, j -1) ;
  quicksort(vector, j +1, ultimo ) ;

  }
}


int main(){

  int vector[MAX_VECTOR] = {0, 5, 3, 4, 8, 1, 7, 2, 6, 9, 10};
  imprimir_vector(vector, 11);

  quicksort(vector, 0, 11);
  imprimir_vector(vector, 11);

  return 0;
}
