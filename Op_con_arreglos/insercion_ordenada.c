#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50



//Precondiciones: El vector debe estar preordenado antes de llamar a la funcion
//                y se debe buscar un ordenamiento de menor a mayor (caso contrario se invierten los signos).
//                El tope debe ser >= 0.
//                Se debe enviar un valor posible como elemento (si es un vector de num naturales, que sea > 0).
//Postcondiciones: Devuelve el vector original con el elemento adicional siguiendo el orden establecido

void insercion_ordenada(int vector[MAX_VECTOR], int* tope_vector, int elemento){
  int valor_aux;

  for (int i = 0; i < (*tope_vector); i++){

    if (elemento < vector[i]){
      valor_aux = vector[i];
      vector[i] = elemento;
      elemento = valor_aux;
    }

  }

  vector[(*tope_vector)] = elemento;
  (*tope_vector)++;

}


int main(){

  int vector[MAX_VECTOR] = {1, 2, 4, 5, 6};
  int tope_vector = 5;

  for (int i = 0; i < tope_vector; i++){
    printf("%i ", vector[i]);
  }
  printf("\n");

  insercion_ordenada(vector, &tope_vector, 3);

  for (int i = 0; i < tope_vector; i++){
    printf("%i ", vector[i]);
  }
}
