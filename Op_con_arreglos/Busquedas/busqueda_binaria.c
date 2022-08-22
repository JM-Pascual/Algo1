#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50

const int NO_ENCONTRADO = -1;

//Precondiciones: Este método solo sirve para vectores ordenados! Aprovecha justamente esta propiedad.
//Postcondiciones: Devuelve la posicion dentro del vector del elemento que busco.

int busqueda_binaria(int vector[MAX_VECTOR], int tope_vector, int valor_buscado){
  bool encontrado = false;

  int inicio = 0;
  int final = tope_vector -1;
  int centro = ((final - inicio) / 2);

  if (vector[inicio] > valor_buscado){
    return NO_ENCONTRADO;
  }

  else if (vector[final] < valor_buscado){
    return NO_ENCONTRADO;
  }

  else{
    while(inicio < final && !(encontrado)){
      printf("%i es el valor del centro\n", centro);

      if (vector[centro] == valor_buscado){
        encontrado = true;
      }

      else if(valor_buscado < vector[centro]){
        final = centro -1;
        centro = ((final + inicio) / 2);
      }

      else{
        inicio = centro +1;
        centro = ((final + inicio) / 2);
      }
    }

    if (!(encontrado)){
      return NO_ENCONTRADO;
    }

    else{
      return centro;
    }
  }
}


int main(){

  int vector[MAX_VECTOR] = {1, 2, 4, 5, 6, 9, 11, 16, 20, 25, 36, 40};
  int tope_vector = 12;

  int posicion_valor_buscado = busqueda_binaria(vector, tope_vector, 9);
  printf("%i es la posición del valor buscado!\n", posicion_valor_buscado);

  return 0;
}
