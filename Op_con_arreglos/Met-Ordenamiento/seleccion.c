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


void seleccion(int vector[MAX_VECTOR], int tope_vector){
  int aux;
  int posicion_minimo;

  for (int  i = 0; i < tope_vector -1; i++){
    posicion_minimo = i;
    for (int j = i +1; j < tope_vector; j++){

      if (vector[posicion_minimo] > vector[j]){
        posicion_minimo = j;
      }
    } //Después de terminar un ciclo de este for, en la variable minimo me queda la posicion del valor más chico.

    aux = vector[posicion_minimo];
    vector[posicion_minimo] = vector[i];
    vector[i] = aux; //Siempre en i voy a tener el lugar donde debe ir el valor más chico.
  }
}


int main(){

  int vector[MAX_VECTOR] = {0, 5, 3, 4, 8, 1, 7, 2, 6, 9, 10};
  imprimir_vector(vector, 11);

  seleccion(vector, 11);
  imprimir_vector(vector, 11);

  return 0;
}
