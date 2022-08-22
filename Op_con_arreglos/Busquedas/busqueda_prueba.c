#include <stdio.h>
#include <stdbool.h>

#define MAX_VECTOR 50

const int NO_ENCONTRADO = -1;

typedef struct recuerdo {
      int id_recuerdo;
      int duracion;
      char tipo; //'A': alegre, 'T': triste o 'N': neutro
} recuerdo_t;


void busqueda_binaria_rec(recuerdo_t vector[MAX_VECTOR], int elemento, int inicio, int final){
  int centro = (inicio + final)/2;

  printf("centro: %i\n", centro);

  if (vector[centro].duracion == elemento){
    printf("si\n");
  }

  else if (vector[centro].duracion < elemento && inicio <= final){
    busqueda_binaria_rec(vector, elemento, centro +1, final);
  }

  else if (vector[centro].duracion > elemento && inicio <= final){
    busqueda_binaria_rec(vector, elemento, inicio, centro -1);
  }

  else if (inicio > final){
    printf("no\n");
  }
}


void busqueda_binaria(recuerdo_t vector[MAX_VECTOR], int tope_vector, int elemento){

  busqueda_binaria_rec(vector, elemento, 0, tope_vector -1);
}


int main(){
    recuerdo_t recuerdos[MAX_VECTOR];

    recuerdos[0].duracion = 10;
    recuerdos[1].duracion = 20;
    recuerdos[2].duracion = 90;
    recuerdos[4].duracion = 342;
    recuerdos[3].duracion = 1000;

    busqueda_binaria(recuerdos, 4, 342);
}
