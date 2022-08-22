#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50

void eliminacion_fisica(int vector[MAX_VECTOR], int* tope_vector, int elemento_a_eliminar){
  bool se_realizaron_cambios = false;
  int elemento_aux;


  for (int i = 0; i < (*tope_vector); i++){

    if (vector[i] == elemento_a_eliminar){
      elemento_aux = vector[i +1];
      vector[i +1] = elemento_a_eliminar;
      vector[i] = elemento_aux;
      se_realizaron_cambios = true;
    }
  }

  if (se_realizaron_cambios){
      (*tope_vector)--;
  }
}


int main(){

  int vector[MAX_VECTOR] = {1, 2, 4, 5, 6};
  int tope_vector = 5;

  for (int i = 0; i < tope_vector; i++){
    printf("%i ", vector[i]);
  }
  printf("\n");

  eliminacion_fisica(vector, &tope_vector, 4);
  
  for (int i = 0; i < tope_vector; i++){
    printf("%i ", vector[i]);
  }
}
