#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50


int busqueda_lineal_rec(int numero_buscado, int vector[MAX_VECTOR], int tope_vector, int posicion){
  printf("Analizo la posicion %i, el valor dentro es: %i\n", posicion, vector[posicion]);
  if (vector[posicion] == numero_buscado){
    return 1;
  }

  else if (posicion < tope_vector){
    posicion++;
    return 1 + busqueda_lineal_rec(numero_buscado, vector, tope_vector, posicion);
  }

  else{
    return (-1 * (tope_vector +1));
  }
}


int busqueda_lineal(int numero_buscado, int vector[MAX_VECTOR], int tope_vector){
  if (vector[0] == numero_buscado){
    return 0;
  }

  else{
    return 0 + busqueda_lineal_rec(numero_buscado, vector, tope_vector, 1);
  }
}


int main(){
  int vector[MAX_VECTOR] = {1, 4, 5, 6, 7, 21, 14, 9, 3, 22, 2, 34};

  int index_numero_buscado = busqueda_lineal(2, vector, 12);
  if (index_numero_buscado < 0){
    printf("No se ha encontrado el valor indicado dentro del vector.\n");
  }
  else{
    printf("La posicion del numero buscado es: %i\n", index_numero_buscado);
  }

  return 0;
}
