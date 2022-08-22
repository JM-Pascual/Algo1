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



void insercion(int vector[MAX_VECTOR], int tope){
    int aux;
    int j;

    for (int i = 1; i < tope; i++) {
        j=i;
        aux = vector[i];
        while (j > 0 && aux < vector[j-1]){
            vector[j] = vector[j-1];
            j--;
        }
        vector[j] = aux;
    }
}


int main(){

  int vector[MAX_VECTOR] = {0, 5, 3, 4, 8, 1, 7, 2, 6, 9, 10};
  imprimir_vector(vector, 11);

  insercion(vector, 11);
  imprimir_vector(vector, 11);

  return 0;
}
