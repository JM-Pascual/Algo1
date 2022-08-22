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


void burbujeo(int vector[MAX_VECTOR], int tope_vector, bool es_menor_a_mayor){
  int aux;

  for (int i = 0; i < tope_vector -1; i++){

    for (int j = 0; j < tope_vector -i -1; j++){

      if (vector[j] > vector[j +1] && es_menor_a_mayor){

        aux = vector[j];
        vector[j] = vector[j +1];
        vector[j +1] = aux;

      }

    }
  }
}

int main(){

  int vector[MAX_VECTOR] = {0, 5, 3, 4, 8, 1, 7, 2, 6, 9, 10};
  imprimir_vector(vector, 11);

  burbujeo(vector, 11, true);
  imprimir_vector(vector, 11);

  return 0;
}
