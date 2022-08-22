#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50

const int NO_ENCONTRADO = -1;


int busqueda_binaria_rec(int vector[MAX_VECTOR], int elemento, int inicio, int final){
  int centro = (inicio + final)/2;

  if (vector[centro] == elemento){
    return centro;
  }

  else if (vector[centro] < elemento && inicio <= final){
    return busqueda_binaria_rec(vector, elemento, centro +1, final);
  }

  else if (vector[centro] > elemento && inicio <= final){
    return busqueda_binaria_rec(vector, elemento, inicio, centro -1);
  }

  else{
    return NO_ENCONTRADO;
  }
}


int busqueda_binaria(int vector[MAX_VECTOR], int tope_vector, int elemento){

  return busqueda_binaria_rec(vector, elemento, 0, tope_vector -1);
}


int main(){

  int vector[MAX_VECTOR] = {1, 2, 4, 5, 6, 9, 11, 16, 20, 25, 36, 40};
  int tope_vector = 12;

  int posicion_valor_buscado = busqueda_binaria(vector, tope_vector, 1);
  printf("%i es la posición del valor buscado!\n", posicion_valor_buscado);

  return 0;
}
