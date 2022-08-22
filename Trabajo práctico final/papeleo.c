#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "utiles.h"


#define MENSAJE_NIVEL_GANADO "\
\n \
                                                                                                                                \n \
      7MM---Mq.                              db                                               db                    7MM      OO \n \
       MM   `MM.                                                                                                     MM      88 \n \
       MM   ,M9 `7Mb,od8 ,pW-Wq.`7M'   `MF'`7MM  `7MMpMMMb.pMMMb.  ,pW°Wq.       7MMpMMMb.   7MM  7M     MF .gP.Ya   MM      || \n \
       MMmmdM9    MM'  '6W'   `Wb `VA ,V'    MM    MM    MM    MM 6W'   `Wb       MM    MM    MM   VA   ,V ,M'   Yb  MM      || \n \
       MM         MM    8M     M8   XMX      MM    MM    MM    MM 8M     M8       MM    MM    MM    VA ,V  8M-----°  MM      || \n \
       MM         MM    YA.   ,A9 ,V' VA.    MM    MM    MM    MM YA.   ,A9       MM    MM    MM     VVV   YM.    ,  MM         \n \
     .JMML.     .JMML.   `Ybmd9'.AM.   .MA..JMML..JMML  JMML  JMML.`Ybmd9'      .JMML  JMML..JMML.    W     `Mbmmd'.JMML.    OO \n \
\n \
\n \
\n \
\n"



#define MAX_OBSTACULOS 100
#define MAX_HERRAMIENTAS 100
#define MAX_PAPELEOS 10
#define MAX_NIVELES 3


#define LADRILLO_EMOJI "\U0001f9f1"
#define FUEGO_EMOJI "\U0001f525"
#define MEDIAS_EMOJI "\U0001f9e6"
#define BOTELLA_DE_GRITOS_EMOJI "\U0001f9f4"
#define AHUYENTA_RANDALL_EMOJI "\U0001f6b7"
#define MARTILLO_EMOJI "\U0001f528"
#define EXTINTOR_EMOJI "\U0001f9ef"
#define MOVIMIENTOS_EMOJI "\U0001f45f"
#define MIKE_EMOJI "\U0001f47e"


const char OBSEQUIO_JASMIN = 'J';
const char OBSEQUIO_OLAF = 'O';
const char OBSEQUIO_STITCH = 'S';
const char OBSEQUIO_RAYO = 'R';


const int DIMENSIONES_NIVEL_1 = 22;
const int DIMENSIONES_NIVEL_2 = 17;
const int DIMENSIONES_NIVEL_3 = 12;

const char FUEGO = 'F';
const char MEDIAS = 'M';
const char BOTELLA_DE_GRITOS = 'G';
const char AHUYENTA_RANDALL = 'I';
const char MIKE = 'W';
const char PARED = '#';

const int MARTILLOS_NIVEL_1 = 4;
const int EXTINTORES_NIVEL_1 = 4;
const int MARTILLOS_NIVEL_2 = 5;
const int EXTINTORES_NIVEL_2 = 2;
const int MARTILLOS_NIVEL_3 = 6;
const int EXTINTORES_NIVEL_3 = 2;
const int MARTILLOS_EXTRA_JASMIN = 1;

const int TOPE_FUEGOS_NIVEL_1 = 10;
const int TOPE_FUEGOS_NIVEL_1_OLAF = 8;
const int TOPE_MEDIAS_NIVEL_1 = 5;
const int TOPE_FUEGOS_NIVEL_2 = 5;
const int TOPE_FUEGOS_NIVEL_2_OLAF = 4;
const int TOPE_MEDIAS_NIVEL_2 = 4;
const int TOPE_FUEGOS_NIVEL_3 = 3;
const int TOPE_MEDIAS_NIVEL_3 = 3;

const int TOPE_BOTELLAS_NIVEL_1 = 4;
const int TOPE_INTERRUPTORES_NIVEL_1 = 1;
const int TOPE_BOTELLAS_NIVEL_2 = 3;
const int TOPE_INTERRUPTORES_NIVEL_2 = 1;
const int TOPE_BOTELLAS_NIVEL_3 = 2;
const int TOPE_INTERRUPTORES_NIVEL_3 = 0;

const int MOVIMIENTOS_INICIALES_NIVEL_1 = 40;
const int MOVIMIENTOS_INICIALES_NIVEL_2 = 30;
const int MOVIMIENTOS_INICIALES_NIVEL_3 = 20;
const int MOVIMIENTOS_EXTRA_RAYO = 10;

const int TOPE_PAPELEOS_NIVEL_1 = 2;
const int TOPE_PAPELEOS_NIVEL_2 = 3;
const int TOPE_PAPELEOS_NIVEL_3 = 4;
const int TOPE_PAPELEOS_NIVEL_3_STITCH = 3;

const int TOPE_PAREDES_RANDOM_NIVEL_1 = 40;
const int TOPE_PAREDES_RANDOM_NIVEL_2 = 30;
const int TOPE_PAREDES_RANDOM_NIVEL_3 = 20;

const int MAXIMO_NIVEL = 3;
const int INDEX_NIVEL_MAXIMO = 2; //3 es el nivel máximo, para leerse en el vector de niveles es 3 -1 = 2

const int PENALIZACION_FUEGOS = 0;
const int PENALIZACION_MEDIAS = 10;
const int BONUS_BOTELLA = 7;

const int NUMERO_DE_RANDALL_NIVEL_1 = 7;
const int NUMERO_DE_RANDALL_NIVEL_2 = 5;
const int NUMERO_DE_RANDALL_NIVEL_3 = 3;

static const int CONDICION_JUGANDO = 0;
static const int CONDICION_GANADO = 1;
static const int CONDICION_PERDIDO = -1;


// Comandos de monivimiento, direccion y herramientas

const char MOVIMIENTO_LATERAL_DERECHA = 'D';
const char MOVIMIENTO_LATERAL_IZQUIERDA = 'A';
const char MOVIMIENTO_ROTACIONAL_HORARIO = 'E';
const char MOVIMIENTO_ROTACIONAL_ANTIHORARIO = 'Q';
const char UTILIZAR_MARTILLO = 'Z';
const char UTILIZAR_EXTINTOR = 'C';

const char SELECCIONAR_DIRECCION_ARRIBA = 'W';
const char SELECCIONAR_DIRECCION_ABAJO = 'S';
const char SELECCIONAR_DIRECCION_IZQUIERDA = 'A';
const char SELECCIONAR_DIRECCION_DERECHA = 'D';

//


typedef struct papeleo{
    coordenada_t posicion;
    int id_papeleo;
    bool recolectado;
} papeleo_t;

typedef struct objeto{
    coordenada_t posicion;
    char tipo;
} objeto_t;

typedef struct nivel{
    coordenada_t paredes[MAX_PAREDES];
    int tope_paredes;
    objeto_t obstaculos[MAX_OBSTACULOS];
    int tope_obstaculos;
    objeto_t herramientas[MAX_HERRAMIENTAS];
    int tope_herramientas;
    papeleo_t papeleos[MAX_PAPELEOS];
    int tope_papeleos;
    coordenada_t pos_inicial_jugador;
}nivel_t;

typedef struct jugador{
    coordenada_t posicion;
    int movimientos;
    int martillos;
    int extintores;
    bool ahuyenta_randall;
    int movimientos_realizados;
}jugador_t;

typedef struct juego{
    int nivel_actual;
    nivel_t niveles[MAX_NIVELES];
    jugador_t jugador;
    char personaje_tp1;
}juego_t;


//Precondiciones: numero_nivel debe corresponder a un nivel dentro del juego.
//Postcondiciones: Devuelve un entero que va desde 0 hasta el máximo de casillas dentro de las dimensiones de la matriz del nivel.
int numero_random(int numero_nivel){
    int max = 0;
    switch (numero_nivel){
    case (1):
        max = DIMENSIONES_NIVEL_1;
        break;
    case (2):
        max = DIMENSIONES_NIVEL_2;
        break;
    case (3):
        max = DIMENSIONES_NIVEL_3;
        break;
    default:
        printf("todo mal");
    }
    int num = rand() % max; // La amplitud del rango es max y el valor mínimo es 0.
    return num;
}


//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con una pared.
bool verificar_posicion_paredes(coordenada_t posicion_nueva, coordenada_t paredes[MAX_PAREDES], int tope_paredes){
  bool es_posicion_valida = true;
  int i = 0;

  while(es_posicion_valida && i < tope_paredes){
    if((posicion_nueva.fil == paredes[i].fil) && (posicion_nueva.col == paredes[i].col)){
      es_posicion_valida = false;
    }
    i++;
  }
  return es_posicion_valida;
}

//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con el jugador.
bool verificar_posicion_jugador(coordenada_t posicion_nueva, coordenada_t posicion_jugador){
  bool es_posicion_valida = true;

  if ((posicion_nueva.fil == posicion_jugador.fil) && (posicion_nueva.col == posicion_jugador.col)){
    es_posicion_valida = false;
  }
  return es_posicion_valida;
}


//----------------------------------------------------OBSTACULOS--------------------------------------------------------------------//



//Precondiciones: numero_nivel debe corresponder a un nivel dentro del juego.
//Postcondiciones: Devuelve el tope de fuegos y medias correspondiente a un nivel del juego.
void obtener_topes_obstaculos(int* tope_fuegos, int* tope_medias, int numero_nivel, char amigo_pide_favor){
  if (numero_nivel == 1 && amigo_pide_favor == OBSEQUIO_OLAF){
    (*tope_fuegos) = TOPE_FUEGOS_NIVEL_1_OLAF;
    (*tope_medias) = TOPE_MEDIAS_NIVEL_1;
  }
  else if (numero_nivel == 2 && amigo_pide_favor == OBSEQUIO_OLAF){
    (*tope_fuegos) = TOPE_FUEGOS_NIVEL_2_OLAF;
    (*tope_medias) = TOPE_MEDIAS_NIVEL_2;
  }
  else{
    switch (numero_nivel){
      case (1):
        (*tope_fuegos) = TOPE_FUEGOS_NIVEL_1;
        (*tope_medias) = TOPE_MEDIAS_NIVEL_1;
        break;
      case (2):
        (*tope_fuegos) = TOPE_FUEGOS_NIVEL_2;
        (*tope_medias) = TOPE_MEDIAS_NIVEL_2;
        break;
      case (3):
        (*tope_fuegos) = TOPE_FUEGOS_NIVEL_3;
        (*tope_medias) = TOPE_MEDIAS_NIVEL_3;
        break;
      default:
        printf("todo mal");
    }
  }
}


//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con un fuego.
bool verificar_posicion_obstaculos_fuegos(coordenada_t posicion_nueva, coordenada_t paredes[MAX_PAREDES], int tope_paredes){
    bool paso_la_prueba = false;

    int i = 0;
    int nueva_fil = posicion_nueva.fil;
    int nueva_col = posicion_nueva.col;

    while(!(paso_la_prueba) && i < tope_paredes){
      if((paredes[i].fil == nueva_fil) && (paredes[i].col == nueva_col -1)){
        paso_la_prueba = true;
      }
      else if((paredes[i].fil == nueva_fil -1) && (paredes[i].col == nueva_col)){
        paso_la_prueba = true;
      }
      else if((paredes[i].fil == nueva_fil) && (paredes[i].col == nueva_col +1)){
        paso_la_prueba = true;
      }
      else if((paredes[i].fil == nueva_fil +1) && (paredes[i].col == nueva_col)){
        paso_la_prueba = true;
      }
      i++;
    }
    return paso_la_prueba;
}


//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con un obstáculo.
bool verificar_posicion_obstaculos(coordenada_t posicion_nueva, coordenada_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos){
    bool paso_la_prueba = true;
    int i = 0;

    while(paso_la_prueba && i < tope_obstaculos){
        if((posicion_nueva.fil == obstaculos[i].fil) && (posicion_nueva.col == obstaculos[i].col)){
            paso_la_prueba = false;
        }
      i++;
    }
    return paso_la_prueba;
}


//Precondiciones: -
//Postcondiciones: Agrega a un array auxiliar la posición de un obstáculo que no se superpone con ningún otro elemento en la matriz.
void crear_posicion_obstaculos_corregido(coordenada_t* posicion_nueva, coordenada_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, bool se_generan_fuegos,
  coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion_jugador ,int numero_nivel){

  bool coordenada_valida = false;
    if (se_generan_fuegos){
      while(!coordenada_valida){
        bool no_fallo = true;
        (*posicion_nueva).fil = numero_random(numero_nivel);
        (*posicion_nueva).col = numero_random(numero_nivel);
        if (!(verificar_posicion_paredes((*posicion_nueva), paredes, tope_paredes))){
          no_fallo = false;
        }
        else if(no_fallo && !(verificar_posicion_obstaculos((*posicion_nueva), obstaculos, (*tope_obstaculos)))){
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_obstaculos_fuegos((*posicion_nueva), paredes, tope_paredes))){
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_jugador((*posicion_nueva), posicion_jugador))){
          no_fallo = false;
        }
        else{
          coordenada_valida = true;
        }
      }
    }

    else{
      while(!coordenada_valida){
        bool no_fallo = true;
        (*posicion_nueva).fil = numero_random(numero_nivel);
        (*posicion_nueva).col = numero_random(numero_nivel);
        if (!(verificar_posicion_paredes((*posicion_nueva), paredes, tope_paredes))){
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_obstaculos((*posicion_nueva), obstaculos, (*tope_obstaculos)))) {
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_jugador((*posicion_nueva), posicion_jugador))){
          no_fallo = false;
        }
        else {
          coordenada_valida = true;
        }
      }
    }
  (*tope_obstaculos) += 1;
  obstaculos[(*tope_obstaculos)] = (*posicion_nueva);
}


//Precondiciones: -
//Postcondiciones: Agrega al array de obstáculos del nivel obstáculos que no se superponen con ningún otro elemento en el nivel.
void obtener_obstaculos(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){
    coordenada_t posicion_nueva;
    coordenada_t posiciones_usadas_obstaculos[MAX_OBSTACULOS];
    int tope_posiciones_usadas_obstaculos = 0;
    int tope_fuegos = 0;
    int tope_medias = 0;
    obtener_topes_obstaculos(&tope_fuegos, &tope_medias, numero_nivel, amigo_pide_favor);
    for(int i = 0; i < tope_fuegos; i++){
        crear_posicion_obstaculos_corregido(&posicion_nueva, posiciones_usadas_obstaculos, &tope_posiciones_usadas_obstaculos,
          true, (*nivel).paredes, (*nivel).tope_paredes, (*nivel).pos_inicial_jugador, numero_nivel);

        (*nivel).obstaculos[i].tipo = FUEGO;
        (*nivel).obstaculos[i].posicion = posicion_nueva;
    }

     for(int j = 0; j < tope_medias; j++){
       crear_posicion_obstaculos_corregido(&posicion_nueva, posiciones_usadas_obstaculos, &tope_posiciones_usadas_obstaculos,
         false, (*nivel).paredes, (*nivel).tope_paredes, (*nivel).pos_inicial_jugador, numero_nivel);

       (*nivel).obstaculos[j + tope_fuegos].tipo = MEDIAS;
       (*nivel).obstaculos[j + tope_fuegos].posicion = posicion_nueva;
    }
    (*nivel).tope_obstaculos = tope_posiciones_usadas_obstaculos;

}


//------------------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------HERRAMIENTAS--------------------------------------------------------------------//


//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con un obstáculo (Adaptado al tipo de dato objeto_t).
bool verificar_posicion_obstaculos_aux(coordenada_t posicion_nueva, objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos){
    bool paso_la_prueba = true;
    int i = 0;

    while(paso_la_prueba && i < tope_obstaculos){
        if((posicion_nueva.fil == obstaculos[i].posicion.fil) && (posicion_nueva.col == obstaculos[i].posicion.col)){
            paso_la_prueba = false;
        }
        i++;
    }
    return paso_la_prueba;
}


//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con una herramienta.
bool verificar_posicion_herramientas(coordenada_t posicion_nueva, coordenada_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas){
    bool paso_la_prueba = true;
    int i = 0;

    while(paso_la_prueba && i < tope_herramientas){
        if((posicion_nueva.fil == herramientas[i].fil) && (posicion_nueva.col == herramientas[i].col)){
            paso_la_prueba = false;
        }
        i++;
    }
    return paso_la_prueba;
}


//Precondiciones: -
//Postcondiciones: Agrega a un array auxiliar la posición de una herramienta que no se superpone con ningún otro elemento en la matriz.
void crear_posicion_herramientas_mapa(coordenada_t* posicion_nueva, coordenada_t herramientas[MAX_HERRAMIENTAS], int* tope_herramientas,
    objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion_jugador, int numero_nivel){

      bool coordenada_valida = false;
      while(!coordenada_valida){
        bool no_fallo = true;
        (*posicion_nueva).fil = numero_random(numero_nivel);
        (*posicion_nueva).col = numero_random(numero_nivel);
        if (!(verificar_posicion_paredes((*posicion_nueva), paredes, tope_paredes))){
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_obstaculos_aux((*posicion_nueva), obstaculos, tope_obstaculos))){
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_herramientas((*posicion_nueva), herramientas, (*tope_herramientas)))){
          no_fallo = false;
        }
        else if (no_fallo && !(verificar_posicion_jugador((*posicion_nueva), posicion_jugador))){
          no_fallo = false;
        }
        else {
          coordenada_valida = true;
        }
    }
  (*tope_herramientas) += 1;
  herramientas[(*tope_herramientas)] = (*posicion_nueva);
}


//Precondiciones: numero_nivel debe corresponder a un numero de nivel posible dentro del juego.
//Postcondiciones: Cambia por referencia los valores de los martillos y extintores de la mochila del jugador, según el nivel en el que se encuentre.
void obtener_herramientas_mochila(int* extintores, int* martillos, int numero_nivel, char amigo_pide_favor){
  if (amigo_pide_favor == OBSEQUIO_JASMIN){
    switch (numero_nivel) {
      case (1):
        (*martillos) = MARTILLOS_NIVEL_1 + MARTILLOS_EXTRA_JASMIN;
        (*extintores) = EXTINTORES_NIVEL_1;
        break;
      case (2):
        (*martillos) = MARTILLOS_NIVEL_2 + MARTILLOS_EXTRA_JASMIN;
        (*extintores) = EXTINTORES_NIVEL_2;
        break;
      case (3):
        (*martillos) = MARTILLOS_NIVEL_3 + MARTILLOS_EXTRA_JASMIN;;
        (*extintores) = EXTINTORES_NIVEL_3;
        break;
      default:
        printf("todo mal");
    }
  }
  else{
    switch (numero_nivel) {
      case (1):
        (*martillos) = MARTILLOS_NIVEL_1;
        (*extintores) = EXTINTORES_NIVEL_1;
        break;
      case (2):
        (*martillos) = MARTILLOS_NIVEL_2;
        (*extintores) = EXTINTORES_NIVEL_2;
        break;
      case (3):
        (*martillos) = MARTILLOS_NIVEL_3;
        (*extintores) = EXTINTORES_NIVEL_3;
        break;
      default:
        printf("todo mal");
    }
  }
}


//Precondiciones: numero_nivel debe corresponder a un nivel dentro del juego.
//Postcondiciones: Devuelve el tope de botellas e interruptores correspondiente a un nivel del juego.
void obtener_topes_herramientas_mapa(int* tope_botellas, int* tope_interruptores, int numero_nivel){
  switch (numero_nivel){
    case (1):
      (*tope_botellas) = TOPE_BOTELLAS_NIVEL_1;
      (*tope_interruptores) = TOPE_INTERRUPTORES_NIVEL_1;
      break;
    case (2):
      (*tope_botellas) = TOPE_BOTELLAS_NIVEL_2;
      (*tope_interruptores) = TOPE_INTERRUPTORES_NIVEL_2;
      break;
    case (3):
      (*tope_botellas) = TOPE_BOTELLAS_NIVEL_3;
      (*tope_interruptores) = TOPE_INTERRUPTORES_NIVEL_3;
      break;
    default:
      printf("todo mal");
  }
}


//Precondiciones: -
//Postcondiciones: Agrega al array de obstáculos del nivel obstáculos que no se superponen con ningún otro elemento en el nivel.
void obtener_herramientas_mapa(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){
    coordenada_t posicion_nueva;
    coordenada_t posiciones_usadas_herramientas[MAX_HERRAMIENTAS];
    int tope_herramientas = 0;
    int tope_botellas = 0;
    int tope_interruptores = 0;
    obtener_topes_herramientas_mapa(&tope_botellas, &tope_interruptores, numero_nivel);
    for(int i = 0; i < tope_botellas; i++){
        crear_posicion_herramientas_mapa(&posicion_nueva, posiciones_usadas_herramientas, &tope_herramientas, (*nivel).obstaculos, (*nivel).tope_obstaculos,
        (*nivel).paredes, (*nivel).tope_paredes, (*nivel).pos_inicial_jugador, numero_nivel);

        (*nivel).herramientas[i].tipo = BOTELLA_DE_GRITOS;
        (*nivel).herramientas[i].posicion = posicion_nueva;
    }

     for(int j = 0; j < tope_interruptores; j++){
       crear_posicion_herramientas_mapa(&posicion_nueva, posiciones_usadas_herramientas, &tope_herramientas, (*nivel).obstaculos, (*nivel).tope_obstaculos,
       (*nivel).paredes, (*nivel).tope_paredes, (*nivel).pos_inicial_jugador, numero_nivel);

       (*nivel).herramientas[j + tope_botellas].tipo = AHUYENTA_RANDALL;
       (*nivel).herramientas[j + tope_botellas].posicion = posicion_nueva;
    }
    (*nivel).tope_herramientas = tope_herramientas;
}


//------------------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------PAPELEOS--------------------------------------------------------------------//

//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con un papeleo.
bool verificar_posicion_papeleos(coordenada_t posicion_nueva, coordenada_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    bool paso_la_prueba = true;
    int i = 0;

    while(paso_la_prueba && i < tope_papeleos){
        if((posicion_nueva.fil == papeleos[i].fil) && (posicion_nueva.col == papeleos[i].col)){
            paso_la_prueba = false;
        }
        i++;
    }
    return paso_la_prueba;
}

//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con una herramienta.
bool verificar_posicion_herramientas_aux(coordenada_t posicion_nueva, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas){
    bool paso_la_prueba = true;
    int i = 0;

    while(paso_la_prueba && i < tope_herramientas){
        if((posicion_nueva.fil == herramientas[i].posicion.fil) && (posicion_nueva.col == herramientas[i].posicion.col)){
            paso_la_prueba = false;
        }
        i++;
    }
    return paso_la_prueba;
}


//Precondiciones: -
//Postcondiciones: Agrega a un array auxiliar papeleos que no se superponen con ningún otro elemento en el nivel.
void crear_posicion_papeleos(coordenada_t* posicion_nueva, coordenada_t papeleos[MAX_PAPELEOS], int* tope_papeleos, objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas,
    objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion_jugador ,int numero_nivel){

  bool coordenada_valida = false;
  while(!coordenada_valida){
    bool no_fallo = true;
    (*posicion_nueva).fil = numero_random(numero_nivel);
    (*posicion_nueva).col = numero_random(numero_nivel);
    if (!(verificar_posicion_paredes((*posicion_nueva), paredes, tope_paredes))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_obstaculos_aux((*posicion_nueva), obstaculos, tope_obstaculos))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_herramientas_aux((*posicion_nueva), herramientas, tope_herramientas))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_papeleos((*posicion_nueva), papeleos, (*tope_papeleos)))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_jugador((*posicion_nueva), posicion_jugador))){
      no_fallo = false;
    }
    else{
      coordenada_valida = true;
    }
  }
  papeleos[(*tope_papeleos)] = (*posicion_nueva);
  (*tope_papeleos) += 1;
}


//Precondiciones: numero_nivel debe corresponder a un nivel dentro del juego.
//Postcondiciones: Define los topes para los arrays de papeleos en base al nivel actual.
void obtener_topes_papeleos(int* tope_papeleos, int numero_nivel, char amigo_pide_favor){
  if (numero_nivel == 3 && amigo_pide_favor == OBSEQUIO_STITCH){
    (*tope_papeleos) = TOPE_PAPELEOS_NIVEL_3_STITCH;
  }
  else{
    switch (numero_nivel){
      case (1):
        (*tope_papeleos) = TOPE_PAPELEOS_NIVEL_1;
        break;
      case (2):
        (*tope_papeleos) = TOPE_PAPELEOS_NIVEL_2;
        break;
      case (3):
        (*tope_papeleos) = TOPE_PAPELEOS_NIVEL_3;
        break;
      default:
        printf("todo mal");
    }
  }
}


//Precondiciones: -
//Postcondiciones: Agrega al array de papeleos del nivel papeleos que no se superponen con ningún otro elemento en el nivel
//                 (Además de definirlos como no recogidos y asignarles un número).
void obtener_papeleos(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){
    coordenada_t posicion_nueva;
    coordenada_t posiciones_usadas_papeleos[MAX_PAPELEOS];
    int tope_posiciones_usadas_papeleos = 0;
    int tope_papeleos = 0;
    obtener_topes_papeleos(&tope_papeleos, numero_nivel, amigo_pide_favor);
    for(int i = 0; i < tope_papeleos; i++){
        crear_posicion_papeleos(&posicion_nueva, posiciones_usadas_papeleos, &tope_posiciones_usadas_papeleos, (*nivel).herramientas, (*nivel).tope_herramientas,
        (*nivel).obstaculos, (*nivel).tope_obstaculos, (*nivel).paredes, (*nivel).tope_paredes, (*nivel).pos_inicial_jugador, numero_nivel);

        (*nivel).papeleos[i].posicion = posicion_nueva;
        (*nivel).papeleos[i].id_papeleo = i+1;
        (*nivel).papeleos[i].recolectado = false;
    }
    (*nivel).tope_papeleos = tope_posiciones_usadas_papeleos;
}

//Precondiciones: -
//Postcondiciones: Devuelve un bool que indica si la coordenada analizada se superpone con un papeleo.
bool verificar_posicion_papeleos_aux(coordenada_t posicion_nueva, papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    bool paso_la_prueba = true;
    int i = 0;

    while(paso_la_prueba && i < tope_papeleos){
        if((posicion_nueva.fil == papeleos[i].posicion.fil) && (posicion_nueva.col == papeleos[i].posicion.col)
        && !(papeleos[i].recolectado)){
            paso_la_prueba = false;
        }
        i++;
    }
    return paso_la_prueba;
}


//------------------------------------------------------------------------------------------------------------------------//


//Precondiciones: -
//Postcondiciones: Agrega a la matriz auxiliar (que muestra la información del nivel) la información dentro de los arrays de info de nivel.
void construir_e_imprimir_matriz(juego_t juego, int dimension, int numero_nivel){
  char matrix[dimension][dimension];
  for (int i = 0; i < dimension; i++){
    for (int j = 0; j < dimension; j++){
        matrix[i][j] = ' ';
    }
  }
  int fil_aux = 0;
  int col_aux = 0;
  for (int i = 0; i < juego.niveles[numero_nivel].tope_paredes; i++){
    fil_aux = juego.niveles[numero_nivel].paredes[i].fil;
    col_aux = juego.niveles[numero_nivel].paredes[i].col;
    matrix[fil_aux][col_aux] = PARED;
  }

  for (int i = 0; i < juego.niveles[numero_nivel].tope_obstaculos; i++){
    fil_aux = juego.niveles[numero_nivel].obstaculos[i].posicion.fil;
    col_aux = juego.niveles[numero_nivel].obstaculos[i].posicion.col;
    matrix[fil_aux][col_aux] = juego.niveles[numero_nivel].obstaculos[i].tipo;
  }

  for (int i = 0; i < juego.niveles[numero_nivel].tope_herramientas; i++){
    fil_aux = juego.niveles[numero_nivel].herramientas[i].posicion.fil;
    col_aux = juego.niveles[numero_nivel].herramientas[i].posicion.col;
    matrix[fil_aux][col_aux] = juego.niveles[numero_nivel].herramientas[i].tipo;
  }

  for (int i = 0; i < juego.niveles[numero_nivel].tope_papeleos; i++){
    if (!(juego.niveles[numero_nivel].papeleos[i].recolectado)){
      int id = i+1;
      fil_aux = juego.niveles[numero_nivel].papeleos[i].posicion.fil;
      col_aux = juego.niveles[numero_nivel].papeleos[i].posicion.col;
      switch (id) {
        case (1):
        matrix[fil_aux][col_aux] = '1';
        break;
        case (2):
        matrix[fil_aux][col_aux] = '2';
        break;
        case (3):
        matrix[fil_aux][col_aux] = '3';
        break;
        case (4):
        matrix[fil_aux][col_aux] = '4';
        break;
        default:
        printf("todo mal");
      }
    }
  }

  fil_aux = juego.jugador.posicion.fil;
  col_aux = juego.jugador.posicion.col;
  matrix[fil_aux][col_aux] = MIKE;

  for (int i = 0; i < dimension; i++){
    for (int j = 0; j < dimension; j++){
      if (matrix[i][j] == PARED){
        printf("%s", LADRILLO_EMOJI);
      }
      else if (matrix[i][j] == FUEGO){
        printf("%s", FUEGO_EMOJI);
      }
      else if (matrix[i][j] == MEDIAS){
        printf("%s", MEDIAS_EMOJI);
      }
      else if (matrix[i][j] == BOTELLA_DE_GRITOS){
        printf("%s", BOTELLA_DE_GRITOS_EMOJI);
      }
      else if (matrix[i][j] == MIKE){
        printf("%s", MIKE_EMOJI);
      }
      else if (matrix[i][j] == AHUYENTA_RANDALL){
        printf("%s", AHUYENTA_RANDALL_EMOJI);
      }
      else{
        printf(" %c", matrix[i][j]);
      }
    }
    printf("\n");
  }
}


//Precondiciones: -
//Postcondiciones: Genera la matriz auxiliar (muestra la información del nivel).
void imprimir_terreno(juego_t juego){
  int dimension = 0;
  int numero_nivel = 0;
  switch (juego.nivel_actual) {
    case (1):
      numero_nivel = 0;
      dimension = DIMENSIONES_NIVEL_1;
      break;
    case (2):
    numero_nivel = 1;
      dimension = DIMENSIONES_NIVEL_2;
      break;
    case (3):
      numero_nivel = 2;
      dimension = DIMENSIONES_NIVEL_3;
      break;
    default:
      printf("todo mal");
  }
  printf("%s ", MOVIMIENTOS_EMOJI);
  printf("%i MOVIMIENTOS DISPONIBLES\n", juego.jugador.movimientos);
  printf("-----------------------------\n");
  printf("%s ", MARTILLO_EMOJI);
  printf("%i MARTILLOS DISPONIBLES\n", juego.jugador.martillos);
  printf("-----------------------------\n");
  printf("%s ", EXTINTOR_EMOJI);
  printf("%i EXTINTORES DISPONIBLES\n", juego.jugador.extintores);
  printf("-----------------------------\n");
  printf("%s ", AHUYENTA_RANDALL_EMOJI);
  printf("EL AHUYENTA RANDALL SE ENCUENTRA ");
  if (juego.jugador.ahuyenta_randall){
    printf("ACTIVADO\n");
    printf("\n");
  }
  else{
    printf("DESACTIVADO\n");
    printf("\n");
  }
  construir_e_imprimir_matriz(juego, dimension, numero_nivel);
}


//Precondiciones: numero_nivel debe corresponder a un nivel posible dentro del juego.
//Postcondiciones: Modifica por referencia los movimientos del usuario en base al nivel en el que esté y su personaje.
void definir_movimientos_iniciales(int* movimientos, char amigo_pide_favor){
  if (amigo_pide_favor == OBSEQUIO_RAYO){
    (*movimientos) = MOVIMIENTOS_INICIALES_NIVEL_1 + MOVIMIENTOS_EXTRA_RAYO;
  }
  else{
    (*movimientos) = MOVIMIENTOS_INICIALES_NIVEL_1;
  }
}


//Precondiciones: numero_nivel debe corresponder a un nivel posible dentro del juego.
//Postcondiciones: Arma los arrays que almacenan la información de los niveles.
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){
  obtener_paredes(numero_nivel, (*nivel).paredes, &((*nivel).tope_paredes), &((*nivel).pos_inicial_jugador));
  obtener_obstaculos(nivel, numero_nivel, amigo_pide_favor);
  obtener_herramientas_mapa(nivel, numero_nivel, amigo_pide_favor);
  obtener_papeleos(nivel, numero_nivel, amigo_pide_favor);
}


//Precondiciones: -
//Postcondiciones: Inicia los niveles del juego almacenando la información de estos en los arrays correpondientes.
void inicializar_juego(juego_t* juego, char amigo_pide_favor){
  int contador_de_creacion = 0;

  (*juego).personaje_tp1 = amigo_pide_favor;
  (*juego).nivel_actual = 1;

  obtener_herramientas_mochila(&((*juego).jugador.extintores), &((*juego).jugador.martillos), (*juego).nivel_actual, amigo_pide_favor);
  definir_movimientos_iniciales(&((*juego).jugador.movimientos), amigo_pide_favor);

  inicializar_nivel(&((*juego).niveles[contador_de_creacion]), (*juego).nivel_actual, amigo_pide_favor);
  (*juego).jugador.posicion = (*juego).niveles[contador_de_creacion].pos_inicial_jugador; //Pone al jugador en la posicion inicial del 1er nivel
  //
  contador_de_creacion += 1;
  inicializar_nivel(&((*juego).niveles[contador_de_creacion]), 2, amigo_pide_favor);
  //
  contador_de_creacion += 1;
  inicializar_nivel(&((*juego).niveles[contador_de_creacion]), MAXIMO_NIVEL, amigo_pide_favor);
  //
}


//------------------------------------------------FUNCIONES TP3-----------------------------------------------------------------//

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Devuelve false si el jugador choca con una pared al moverse hacia la izquierda y true si es un movimiento válido
bool se_puede_mover_izquierda(jugador_t jugador, nivel_t nivel){
  bool movimiento_posible = true;
  int i = 0;

  int fila_actual = jugador.posicion.fil;
  int columna_actual = jugador.posicion.col;

  while (movimiento_posible && i < nivel.tope_paredes){
    if (nivel.paredes[i].fil == fila_actual && nivel.paredes[i].col == columna_actual -1){
      movimiento_posible = false;
      printf("Te chocaste con una pared! Proba otra dirección!\n");
      //detener_el_tiempo((float)1.2);
    }
    i++;
  }
  return movimiento_posible;
}

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Devuelve false si el jugador se choca con una pared al moverse hacia la derecha y true si es un movimiento válido
bool se_puede_mover_derecha(jugador_t jugador, nivel_t nivel){
  bool movimiento_posible = true;
  int i = 0;

  int fila_actual = jugador.posicion.fil;
  int columna_actual = jugador.posicion.col;

  while (movimiento_posible && i < nivel.tope_paredes){
    if (nivel.paredes[i].fil == fila_actual && nivel.paredes[i].col == columna_actual +1){
      movimiento_posible = false;
      printf("Te chocaste con una pared! Proba otra dirección!\n");
      //detener_el_tiempo((float)1.2);
    }
    i++;
  }
  return movimiento_posible;
}

//Precondiciones: -
//Postcondiciones: Devuelve las dimensiones de la matriz que delimita al nivel actual.
int dimension_nivel(int nivel_actual){
  int dimension = 0;

  switch (nivel_actual) {
    case (1):
      dimension = DIMENSIONES_NIVEL_1;
      break;
    case (2):
      dimension = DIMENSIONES_NIVEL_2;
      break;
    case (3):
      dimension = DIMENSIONES_NIVEL_3;
      break;
    default:
      printf("todo mal");
  }

  return dimension;
}


//----------------------------------------------------------------------------//

//Precondiciones: -
//Postcondiciones: Rota una coordenada de manera antihoraria.
void rotar_coordenada_antihorariamente(coordenada_t* coordenada_original, int dimension){
  coordenada_t coordenada_rot_antihorario;

  coordenada_rot_antihorario.fil = abs((*coordenada_original).col - dimension +1); //dimension +1 es la dimension de la matriz según como se calcula en la realidad
  coordenada_rot_antihorario.col = (*coordenada_original).fil;
  (*coordenada_original) = coordenada_rot_antihorario;
}

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Recibe las posiciones de todo sobre la matriz y las rota de manera antihoraria.
void movimiento_rotacional_antihorario(jugador_t* jugador, nivel_t* nivel, int nivel_actual){
  int dimension = dimension_nivel(nivel_actual);

  coordenada_t coordenada_aux;

  for (int i = 0; i < (*nivel).tope_paredes; i++){
    coordenada_aux = (*nivel).paredes[i];
    rotar_coordenada_antihorariamente(&coordenada_aux, dimension);
    (*nivel).paredes[i] = coordenada_aux;
  }

  for (int i = 0; i < (*nivel).tope_obstaculos; i++){
    coordenada_aux = (*nivel).obstaculos[i].posicion;
    rotar_coordenada_antihorariamente(&coordenada_aux, dimension);
    (*nivel).obstaculos[i].posicion = coordenada_aux;
  }

  for (int i = 0; i < (*nivel).tope_herramientas; i++){
    coordenada_aux = (*nivel).herramientas[i].posicion;
    rotar_coordenada_antihorariamente(&coordenada_aux, dimension);
    (*nivel).herramientas[i].posicion = coordenada_aux;
  }

  for (int i = 0; i < (*nivel).tope_papeleos; i++){
    coordenada_aux = (*nivel).papeleos[i].posicion;
    rotar_coordenada_antihorariamente(&coordenada_aux, dimension);
    (*nivel).papeleos[i].posicion = coordenada_aux;
  }
  coordenada_aux = (*jugador).posicion;
  rotar_coordenada_antihorariamente(&coordenada_aux, dimension);
  (*jugador).posicion = coordenada_aux;
}


//----------------------------------------------------------------------------//

//Precondiciones: -
//Postcondiciones: Rota una coordenada de manera horaria.
void rotar_coordenada_horariamente(coordenada_t* coordenada_original, int dimension){
  coordenada_t coordenada_rot_horario;

  coordenada_rot_horario.fil = (*coordenada_original).col;
  coordenada_rot_horario.col = abs((*coordenada_original).fil - dimension +1); //coordenada_original +1 es la dimension de la coordenada según como se calcula en la realidad
  (*coordenada_original) = coordenada_rot_horario;
}

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Recibe las posiciones de todo sobre la matriz y las rota de manera horaria.
void movimiento_rotacional_horario(jugador_t* jugador, nivel_t* nivel, int nivel_actual){
  int dimension = dimension_nivel(nivel_actual);

  coordenada_t coordenada_aux;

  for (int i = 0; i < (*nivel).tope_paredes; i++){
    coordenada_aux = (*nivel).paredes[i];
    rotar_coordenada_horariamente(&coordenada_aux, dimension);
    (*nivel).paredes[i] = coordenada_aux;
  }

  for (int i = 0; i < (*nivel).tope_obstaculos; i++){
    coordenada_aux = (*nivel).obstaculos[i].posicion;
    rotar_coordenada_horariamente(&coordenada_aux, dimension);
    (*nivel).obstaculos[i].posicion = coordenada_aux;
  }

  for (int i = 0; i < (*nivel).tope_herramientas; i++){
    coordenada_aux = (*nivel).herramientas[i].posicion;
    rotar_coordenada_horariamente(&coordenada_aux, dimension);
    (*nivel).herramientas[i].posicion = coordenada_aux;
  }

  for (int i = 0; i < (*nivel).tope_papeleos; i++){
    coordenada_aux = (*nivel).papeleos[i].posicion;
    rotar_coordenada_horariamente(&coordenada_aux, dimension);
    (*nivel).papeleos[i].posicion = coordenada_aux;
  }
  coordenada_aux = (*jugador).posicion;
  rotar_coordenada_horariamente(&coordenada_aux, dimension);
  (*jugador).posicion = coordenada_aux;
}


//----------------------------------------------------------------------------//

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Lee la posición del jugador y analiza si se encuentra sobre algún obstaculo para luego aplicar su efecto en el juego.
//                 Luego devuelve un booleano que indica si se aplico o no un efecto.
bool jugador_sobre_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos,
  jugador_t* jugador, bool* se_piso_fuego){

  coordenada_t posicion_jugador = (*jugador).posicion;

  bool se_aplico_efectos_obstaculos = false;
  int i = 0;

  while (!(se_aplico_efectos_obstaculos) && i < tope_obstaculos){
    if (obstaculos[i].posicion.fil == posicion_jugador.fil && obstaculos[i].posicion.col == posicion_jugador.col){

      if(obstaculos[i].tipo == FUEGO){
        (*jugador).movimientos = PENALIZACION_FUEGOS;
        (*se_piso_fuego) = true;
        se_aplico_efectos_obstaculos = true;
      }

      else if (obstaculos[i].tipo == MEDIAS){
        (*jugador).movimientos -= PENALIZACION_MEDIAS;
        se_aplico_efectos_obstaculos = true;
      }
    }
    i++;
  }
  return se_aplico_efectos_obstaculos;
}

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Lee la posición del jugador y analiza si se encuentra sobre alguna herramienta para luego aplicar su efecto en el juego.
//                 Luego devuelve un booleano que indica si se aplico o no un efecto.
bool jugador_sobre_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas,
  jugador_t* jugador, bool* jugador_activo_ahuyenta_randall){

  coordenada_t posicion_jugador = (*jugador).posicion;

  bool se_aplico_efectos_herramientas = false;
  int i = 0;

  while (!(se_aplico_efectos_herramientas) && i < tope_herramientas){
    if (herramientas[i].posicion.fil == posicion_jugador.fil && herramientas[i].posicion.col == posicion_jugador.col){

      if(herramientas[i].tipo == BOTELLA_DE_GRITOS){
        (*jugador).movimientos += BONUS_BOTELLA;
        se_aplico_efectos_herramientas = true;
      }

      else if (herramientas[i].tipo == AHUYENTA_RANDALL){
        (*jugador_activo_ahuyenta_randall) = true;
        se_aplico_efectos_herramientas = true;
      }
    }
    i++;
  }
  return se_aplico_efectos_herramientas;
}

//Precondiciones: El campo posicion del jugador debe tener cargada una posición válida.
//Postcondiciones: Lee la posición del jugador y llama a las funciones que aplican efectos sobre el juego de encontrarse sobre algún elemento.
void analizar_posicion_actual(nivel_t* nivel, jugador_t* jugador, int nivel_actual, bool* se_piso_fuego){
  int proximo_papeleo = 0;

  while ((*nivel).papeleos[proximo_papeleo].recolectado){
      proximo_papeleo++;
  }

  coordenada_t posicion_jugador = (*jugador).posicion;
  bool efecto_aplicado = false;
  bool jugador_activo_ahuyenta_randall = false;

  while (!(efecto_aplicado)){
    if ((*nivel).papeleos[proximo_papeleo].posicion.fil == posicion_jugador.fil
    && (*nivel).papeleos[proximo_papeleo].posicion.col == posicion_jugador.col){

      printf("RECOGISTE EL PAPELEO NUMERO %i!\n", proximo_papeleo+1);
      //detener_el_tiempo((float)2.5);
      (*nivel).papeleos[proximo_papeleo].recolectado = true;
      efecto_aplicado = true;
    }

    else if (jugador_sobre_obstaculos((*nivel).obstaculos, (*nivel).tope_obstaculos,
    jugador, se_piso_fuego)){
      if (*(se_piso_fuego)){
        printf("Caíste sobre un fuego! Te quedaste sin movimientos :(\n");
        //detener_el_tiempo((float)2.5);
        efecto_aplicado = true;
      }
      else{
        printf("Caíste sobre una media! Perdiste 10 movimientos :(\n");
        //detener_el_tiempo((float)1.5);
        efecto_aplicado = true;
      }
    }
    else if (jugador_sobre_herramientas((*nivel).herramientas, (*nivel).tope_herramientas,
    jugador, &jugador_activo_ahuyenta_randall)){

      if (jugador_activo_ahuyenta_randall){
        printf("Pisaste el dispositivo para ahuyentar a Randall!\n");
        (*jugador).ahuyenta_randall = !((*jugador).ahuyenta_randall);
        if ((*jugador).ahuyenta_randall){
          printf("Lo activaste! Ahora Randall no va a molestar\n");
        }
        else{
          printf("Lo activaste! Ahora Randall puede aparecer!\n");
        }
      //detener_el_tiempo((float)1.5);
        efecto_aplicado = true;
      }
      else{
        printf("Recogiste una botella de gritos! Sumas 7 movimientos\n");
        //detener_el_tiempo((float)1.5);
        efecto_aplicado = true;
      }
    }
    else{
      efecto_aplicado = true;
    }
  }
}

//Precondiciones: La posicion del jugador debe ser una posición válida.
//Postcondiciones: Devuelve un booleano que indica si el jugador ya se encuentra por encima de una pared para detener su caída.
bool tiene_piso_debajo(coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion_jugador){
  bool toco_piso = false;
  int i = 0;

  while (!(toco_piso) && i < tope_paredes){
    if (posicion_jugador.fil == paredes[i].fil -1
      && posicion_jugador.col == paredes[i].col){
        toco_piso = true;
      }
      i++;
  }
  return toco_piso;
}

//Precondiciones: El campo poisición del jugador debe tener cargada una posicion válida.
//Postcondiciones: Verifica si el jugador se encuentra cayendo y de estarlo lo deja caer hasta que llegue a una pared que haga de piso
//                 o se aplique un efecto que lo haga detenerse.
void verificar_gravedad(juego_t* juego, int index_nivel_actual, bool* se_piso_fuego){
  imprimir_terreno((*juego));
  bool jugador_en_caida = true;

  int tope_papeleos = (*juego).niveles[index_nivel_actual].tope_papeleos;

  while (jugador_en_caida){
    if (tiene_piso_debajo((*juego).niveles[index_nivel_actual].paredes, (*juego).niveles[index_nivel_actual].tope_paredes, (*juego).jugador.posicion)){
      jugador_en_caida = false;
    }
    else if ((*juego).niveles[index_nivel_actual].papeleos[tope_papeleos -1].recolectado){
        jugador_en_caida = false;
    }
    else if (jugador_en_caida && !(*se_piso_fuego) && (*juego).jugador.movimientos >= 0){
      (*juego).jugador.posicion.fil++;
      //system("clear");
      imprimir_terreno((*juego));
      //detener_el_tiempo((float)0.20);
      analizar_posicion_actual(&((*juego).niveles[index_nivel_actual]), &((*juego).jugador),(*juego).nivel_actual, se_piso_fuego);
    }
    else{
      jugador_en_caida = false;
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------//
//Precondiciones: -
//Postcondiciones: Devuelve true si todavía no se cumple la condición bajo la cual se deja de generar paredes, false de lo contrario.
bool se_debe_generar_pared(jugador_t jugador, int nivel_actual){
  bool fuera_de_tope = false;
  if ((nivel_actual == 1 && jugador.movimientos_realizados <= TOPE_PAREDES_RANDOM_NIVEL_1)
    || (nivel_actual == 2 && jugador.movimientos_realizados <= TOPE_PAREDES_RANDOM_NIVEL_2)
    || (nivel_actual == 3 && jugador.movimientos_realizados <= TOPE_PAREDES_RANDOM_NIVEL_3)){
      fuera_de_tope = true;
    }
    return fuera_de_tope;
  }

//Precondiciones: -
//Postcondiciones: Genera una pared aleatoria en una posición libre si los movimientos realizados no exceden el límite del nivel.
void generar_pared_aleatoria(nivel_t* nivel, jugador_t jugador, int nivel_actual){
  bool pared_posible = false;
  bool no_fallo = true;

  coordenada_t pared_aleatoria;

  if (se_debe_generar_pared(jugador, nivel_actual)){
    while (!(pared_posible)){
      no_fallo = true;
      pared_aleatoria.fil = numero_random(nivel_actual);
      pared_aleatoria.col = numero_random(nivel_actual);

      if (!(verificar_posicion_paredes(pared_aleatoria, (*nivel).paredes, (*nivel).tope_paredes))){
        no_fallo = false;
      }
      else if (no_fallo && !(verificar_posicion_obstaculos_aux(pared_aleatoria, (*nivel).obstaculos, (*nivel).tope_obstaculos))){
        no_fallo = false;
      }
      else if (no_fallo && !(verificar_posicion_herramientas_aux(pared_aleatoria, (*nivel).herramientas, (*nivel).tope_herramientas))){
        no_fallo = false;
      }
      else if (no_fallo && !(verificar_posicion_papeleos_aux(pared_aleatoria, (*nivel).papeleos, (*nivel).tope_papeleos))){
        no_fallo = false;
      }
      else if (no_fallo && !(verificar_posicion_jugador(pared_aleatoria, jugador.posicion))){
        no_fallo = false;
      }
      else{
        pared_posible = true;
      }
    }
    (*nivel).paredes[(*nivel).tope_paredes] = pared_aleatoria;
    (*nivel).tope_paredes++;
  }
  else{
    printf("TOPE DE MOVIMIENTOS!\n");
  }
}

//Precondiciones: -
//Postcondiciones: Genera un index aleatorio correspondiente a un papeleo no recogido.
int index_papeleo_random(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    int primer_papeleo_no_recogido = 0;
    int index_papeleo_elegido = 0;

    while (papeleos[primer_papeleo_no_recogido].recolectado){
      primer_papeleo_no_recogido++;
    }
    if (primer_papeleo_no_recogido == (tope_papeleos -1)){
      index_papeleo_elegido = primer_papeleo_no_recogido;
    }
    else{
      index_papeleo_elegido = rand() % (tope_papeleos) + (primer_papeleo_no_recogido); // La amplitud del rango es la del ultimo papeleo disponible
                                        //y el valor mínimo es el primer papeleo que no se recogio.
    }
    return index_papeleo_elegido;;
}

//Precondiciones: -
//Postcondiciones: Devuelve el número de movimientos realizados que activa a Randall según el nivel.
int definir_numero_de_randall(int nivel_actual){
  int numero_de_randall = 0;
  switch (nivel_actual) {
    case (1):
      numero_de_randall = NUMERO_DE_RANDALL_NIVEL_1;
      break;
    case (2):
      numero_de_randall = NUMERO_DE_RANDALL_NIVEL_2;
      break;
    case (3):
      numero_de_randall = NUMERO_DE_RANDALL_NIVEL_3;
      break;
    default:
      printf("todo mal Randall");
      break;
  }
  return numero_de_randall;
}

//Precondiciones: -
//Postcondiciones: Genera una coordenada aleatoria para un papeleo
//                 verificando superposición con el resto de elementos en la matriz.
void coordenada_papeleo_movido(nivel_t* nivel, coordenada_t* coordenada_nueva,
  coordenada_t posicion_jugador, int nivel_actual){

  bool coordenada_valida = false;
  bool no_fallo = true;

  while(!coordenada_valida){
    (*coordenada_nueva).fil = numero_random(nivel_actual);
    (*coordenada_nueva).col = numero_random(nivel_actual);
    if (!(verificar_posicion_paredes((*coordenada_nueva), (*nivel).paredes, (*nivel).tope_paredes))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_obstaculos_aux((*coordenada_nueva), (*nivel).obstaculos, (*nivel).tope_obstaculos))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_herramientas_aux((*coordenada_nueva), (*nivel).herramientas, (*nivel).tope_herramientas))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_papeleos_aux((*coordenada_nueva), (*nivel).papeleos, (*nivel).tope_papeleos))){
      no_fallo = false;
    }
    else if (no_fallo && !(verificar_posicion_jugador((*coordenada_nueva), posicion_jugador))){
      no_fallo = false;
    }
    else{
      coordenada_valida = true;
    }
  }
}

//Precondiciones: El campo posición del jugador debe corresponder a una posicion válida.
//Postcondiciones: Verifica si el jugador cumplió las condiciones para que Randall mueva un papaeleo.
void verificar_ahuyenta_randall(nivel_t* nivel, jugador_t jugador, int nivel_actual){
  int numero_de_randall = definir_numero_de_randall(nivel_actual);

  if (!(jugador.ahuyenta_randall) && (jugador.movimientos_realizados % numero_de_randall) == 0){
    coordenada_t coordenada_nueva;
    coordenada_papeleo_movido(nivel, &(coordenada_nueva), jugador.posicion, nivel_actual);
    printf("Randall hizo de las suyas y movió un papeleo!\n");
    int index_papeleo = index_papeleo_random((*nivel).papeleos, (*nivel).tope_papeleos);
    (*nivel).papeleos[index_papeleo].posicion = coordenada_nueva;
  }
}

//-----------------------------------------------------------------------------------------------------------------//

//Precondiciones: -
//Postcondiciones: Elimina físicamente a la pared seleccionada del vector de paredes.
void eliminacion_fisica_paredes(coordenada_t paredes[MAX_PAREDES], int* tope_paredes, int index_pared_seleccinada){
  coordenada_t pared_auxiliar = paredes[(*tope_paredes) -1];

  paredes[(*tope_paredes) -1] = paredes[index_pared_seleccinada]; //Envío la pared que deseo eliminar al final del vector.
  paredes[index_pared_seleccinada] = pared_auxiliar; //Para no perder la pared del final del vector, la intercambio con la que deseo eliminar.
  (*tope_paredes)--; //Elimino la lectura de esa pared sacandole 1 al tope.
}

//Precondiciones: Corrimiento lateral y vertical deben corresponder a la distancia en las 4 direcciones
//                a la que se encuentra la pared del jugador.
//Postcondiciones: Rompe la pared en la dirección selecionada y resta los martillos usados.
void eliminar_pared_en_direccion(coordenada_t paredes[MAX_PAREDES], coordenada_t posicion_jugador, int* tope_paredes,
  int* cantidad_martillos, bool* comando_efectuado, int corrimiento_lateral, int corrimiento_vertical){

  bool se_rompio_pared = false;
  int i = 0;

  while(!(se_rompio_pared) && i < (*tope_paredes)){

    if (paredes[i].fil == posicion_jugador.fil + corrimiento_vertical
    && paredes[i].col == posicion_jugador.col + corrimiento_lateral){

      eliminacion_fisica_paredes(paredes, tope_paredes, i);
      (*cantidad_martillos)--;
      (*comando_efectuado) = true;
      se_rompio_pared = true;
    }
    i++;
  }
  if (!(se_rompio_pared)){
    printf("Error al intentar romper una pared en la direccion que señalada!\n");
    //detener_el_tiempo((float)1.2);
  }
}

//Precondiciones: posicion_jugador debe corresponder a una posición válida.
//Postcondiciones: Recibe la dirección en la que el jugador quiere romper la pared
//                 y llama a las funciones encargadas de eliminarla del vector paredes.
void romper_pared(nivel_t* nivel, coordenada_t posicion_jugador, int* cantidad_martillos, int nivel_actual, bool* comando_efectuado){
  int dimension = dimension_nivel(nivel_actual);

  printf("Seleccione la dirección en la que quiere romper una pared!\n");
  char direccion_usuario;
  bool direccion_correcta = false;

  while(!(direccion_correcta)){
    scanf(" %c", &direccion_usuario);

    if (direccion_usuario == SELECCIONAR_DIRECCION_ARRIBA){
      if (posicion_jugador.fil -1 == 0){
        printf("Error! Esa pared no puede romperse!\n");
        direccion_correcta = true;
        //detener_el_tiempo((float)1.2);
      }
      else{
        eliminar_pared_en_direccion((*nivel).paredes, posicion_jugador, &((*nivel).tope_paredes), cantidad_martillos, comando_efectuado, 0, -1);
        direccion_correcta = true;
      }
    }
    else if (direccion_usuario == SELECCIONAR_DIRECCION_ABAJO){
      if (posicion_jugador.fil +1 == dimension -1){
        printf("Error! Esa pared no puede romperse!\n");
        direccion_correcta = true;
        //detener_el_tiempo((float)1.2);
      }
      else{
        eliminar_pared_en_direccion((*nivel).paredes, posicion_jugador, &((*nivel).tope_paredes), cantidad_martillos, comando_efectuado, 0, +1);
        direccion_correcta = true;
      }
    }
    else if (direccion_usuario == SELECCIONAR_DIRECCION_IZQUIERDA){
      if (posicion_jugador.col -1 == 0){
        printf("Error! Esa pared no puede romperse!\n");
        direccion_correcta = true;
        //detener_el_tiempo((float)1.2);
      }
      else{
        eliminar_pared_en_direccion((*nivel).paredes, posicion_jugador, &((*nivel).tope_paredes), cantidad_martillos, comando_efectuado, -1, 0);
        direccion_correcta = true;
      }
    }
    else if (direccion_usuario == SELECCIONAR_DIRECCION_DERECHA){
      if (posicion_jugador.col +1 == dimension -1){
        printf("Error! Esa pared no puede romperse!\n");
        direccion_correcta = true;
        //detener_el_tiempo((float)1.2);
      }
      else{
        eliminar_pared_en_direccion((*nivel).paredes, posicion_jugador, &((*nivel).tope_paredes), cantidad_martillos, comando_efectuado, +1, 0);
        direccion_correcta = true;
      }
    }
    else{
      printf("Ingrese una direccion válida!\n");
      //detener_el_tiempo((float)1.2);
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------//

//Precondiciones: -
//Postcondiciones: Elimina físicamente al fuego seleccionado del vector de paredes.
void eliminacion_fisica_fuegos(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, int index_fuego_seleccionado){
  objeto_t obstaculo_auxiliar = obstaculos[(*tope_obstaculos) -1];

  obstaculos[(*tope_obstaculos) -1] = obstaculos[index_fuego_seleccionado]; //Envío el fuego que deseo eliminar al final del vector.
  obstaculos[index_fuego_seleccionado] = obstaculo_auxiliar; //Para no perder el fuego del final del vector, lo intercambio con el que deseo eliminar.
  (*tope_obstaculos)--; //Elimino la lectura de ese fuego sacandole 1 al tope.
}

//Precondiciones: Corrimiento lateral y vertical deben corresponder a la distancia en las 4 direcciones
//                a la que se encuentra el fuego del jugador.
//Postcondiciones: Extingue un fuego en la dirección selecionada y resta los extintores usados.
void eliminar_fuego_en_direccion(objeto_t obstaculos[MAX_OBSTACULOS], coordenada_t posicion_jugador, int* tope_obstaculos,
  int* cantidad_extintores, bool* comando_efectuado, int corrimiento_lateral, int corrimiento_vertical){

  bool se_extinguio_fuego = false;
  int i = 0;

  while(!(se_extinguio_fuego) && i < (*tope_obstaculos)){

    if (obstaculos[i].posicion.fil == posicion_jugador.fil + corrimiento_vertical
    && obstaculos[i].posicion.col == posicion_jugador.col + corrimiento_lateral){

      eliminacion_fisica_fuegos(obstaculos, tope_obstaculos, i);
      (*cantidad_extintores)--;
      (*comando_efectuado) = true;
      se_extinguio_fuego = true;
    }
    i++;
  }
  if (!(se_extinguio_fuego)){
    printf("Error al intentar extinguir un fuego en la direccion señalada!\n");
    //detener_el_tiempo((float)1.2);
  }
}

//Precondiciones: posicion_jugador debe corresponder a una posición válida.
//Postcondiciones: Recibe la dirección en la que el jugador quiere extinguir un fuego
//                 y llama a las funciones encargadas de eliminarlo del vector obstáculos.
void extinguir_fuegos(nivel_t* nivel, coordenada_t posicion_jugador, int* cantidad_extintores, int nivel_actual, bool* comando_efectuado){
  printf("Seleccione la dirección en la que quiere extinguir un fuego!\n");
  char direccion_usuario;
  bool direccion_correcta = false;

  while (!(direccion_correcta)) {
    scanf(" %c", &direccion_usuario);

    if (direccion_usuario == SELECCIONAR_DIRECCION_ARRIBA){
      eliminar_fuego_en_direccion((*nivel).obstaculos, posicion_jugador, &((*nivel).tope_obstaculos), cantidad_extintores, comando_efectuado, 0, -1);
      direccion_correcta = true;
    }
    else if (direccion_usuario == SELECCIONAR_DIRECCION_ABAJO){
      eliminar_fuego_en_direccion((*nivel).obstaculos, posicion_jugador, &((*nivel).tope_obstaculos), cantidad_extintores, comando_efectuado, 0, +1);
      direccion_correcta = true;
    }
    else if (direccion_usuario == SELECCIONAR_DIRECCION_IZQUIERDA){
      eliminar_fuego_en_direccion((*nivel).obstaculos, posicion_jugador, &((*nivel).tope_obstaculos), cantidad_extintores, comando_efectuado, -1, 0);
      direccion_correcta = true;
    }
    else if (direccion_usuario == SELECCIONAR_DIRECCION_DERECHA){
      eliminar_fuego_en_direccion((*nivel).obstaculos, posicion_jugador, &((*nivel).tope_obstaculos), cantidad_extintores, comando_efectuado, +1, 0);
      direccion_correcta = true;
    }
    else{
      printf("Ingrese una direccion válida!\n");
    }
  }
}


//-----------------------------------------------------------------------------------------------------------------//

//Precondiciones: -
//Postcondiciones: Llama a las funciones que ejecutan los movimientos espaciales sobre el nivel y
//                 contabiliza el movimiento del usuario
void ejecutar_movimiento(juego_t* juego, int index_nivel_actual, char comando){
  if (comando == MOVIMIENTO_LATERAL_IZQUIERDA){
      (*juego).jugador.posicion.col--;
      (*juego).jugador.movimientos--;
      (*juego).jugador.movimientos_realizados++;
  }
  else if (comando == MOVIMIENTO_LATERAL_DERECHA){
    (*juego).jugador.posicion.col++;
    (*juego).jugador.movimientos--;
    (*juego).jugador.movimientos_realizados++;
  }
  else if (comando == MOVIMIENTO_ROTACIONAL_HORARIO){
    movimiento_rotacional_horario(&((*juego).jugador), &((*juego).niveles[index_nivel_actual]), (*juego).nivel_actual);
    (*juego).jugador.movimientos--;
    (*juego).jugador.movimientos_realizados++;
  }
  else if (comando == MOVIMIENTO_ROTACIONAL_ANTIHORARIO){
    movimiento_rotacional_antihorario(&((*juego).jugador), &((*juego).niveles[index_nivel_actual]), (*juego).nivel_actual);
    (*juego).jugador.movimientos--;
    (*juego).jugador.movimientos_realizados++;
  }
}

//Precondiciones: comando debe corresponder a uno de los comandos posibles que puede ingresar el usuario.
//Postcondiciones: Interpreta el comando ingresado por el usuario y realiza las acciones correspondientes a este.
void ejecutar_comando(juego_t* juego, char comando, int index_nivel_actual,
  bool* se_uso_herramienta, bool* se_roto_mapa, bool* se_piso_fuego, bool* comando_efectuado){

  if (comando == MOVIMIENTO_LATERAL_IZQUIERDA && se_puede_mover_izquierda((*juego).jugador, (*juego).niveles[index_nivel_actual])){
      ejecutar_movimiento(juego, index_nivel_actual, comando);
      (*comando_efectuado) = true;
  }
  else if (comando == MOVIMIENTO_LATERAL_DERECHA && se_puede_mover_derecha((*juego).jugador, (*juego).niveles[index_nivel_actual])){
    ejecutar_movimiento(juego, index_nivel_actual, comando);
    (*comando_efectuado) = true;
  }
  else if (comando == MOVIMIENTO_ROTACIONAL_HORARIO){
    ejecutar_movimiento(juego, index_nivel_actual, comando);
    (*se_roto_mapa) = true;
    (*comando_efectuado) = true;
  }
  else if (comando == MOVIMIENTO_ROTACIONAL_ANTIHORARIO){
    ejecutar_movimiento(juego, index_nivel_actual, comando);
    (*se_roto_mapa) = true;
    (*comando_efectuado) = true;
  }
  else if (comando == UTILIZAR_MARTILLO && (*juego).jugador.martillos != 0){
    printf("Eligio usar un martillo!\n");
    romper_pared(&((*juego).niveles[index_nivel_actual]), (*juego).jugador.posicion, &((*juego).jugador.martillos), (*juego).nivel_actual, comando_efectuado);
    (*se_uso_herramienta) = true;
  }
  else if (comando == UTILIZAR_MARTILLO && (*juego).jugador.martillos == 0){
    printf("Error! No dispones de más martillos!\n");
    //detener_el_tiempo((float)1);
  }
  else if (comando == UTILIZAR_EXTINTOR && (*juego).jugador.extintores != 0){
    printf("Eligio usar un extintor!\n");
    extinguir_fuegos(&((*juego).niveles[index_nivel_actual]), (*juego).jugador.posicion, &((*juego).jugador.extintores), (*juego).nivel_actual, comando_efectuado);
    (*se_uso_herramienta) = true;
  }
  else if (comando == UTILIZAR_EXTINTOR && (*juego).jugador.extintores == 0){
    printf("Error! No dispones de más extintores!\n");
    //detener_el_tiempo((float)1);
  }
}

//Precondiciones: -
//Postcondiciones: Permite que el usuario ingrese un comando y se cicla hasta que este
//                 corresponda a una acción posible.
void pedir_comandos(juego_t* juego, bool* se_uso_herramienta, bool* se_roto_mapa, bool* se_piso_fuego, bool* comando_efectuado){
  char comando_usuario;
  bool orden_correcta = false;
  int index_nivel_actual = (*juego).nivel_actual -1;

  while (!(orden_correcta)){
    scanf(" %c", &comando_usuario);
    if (comando_usuario == MOVIMIENTO_LATERAL_IZQUIERDA){
      orden_correcta = true;
    }
    else if (comando_usuario == MOVIMIENTO_LATERAL_DERECHA){
      orden_correcta = true;
    }
    else if (comando_usuario == MOVIMIENTO_ROTACIONAL_HORARIO){
      orden_correcta = true;
    }
    else if (comando_usuario == MOVIMIENTO_ROTACIONAL_ANTIHORARIO){
      orden_correcta = true;
    }
    else if (comando_usuario == UTILIZAR_MARTILLO){
        orden_correcta = true;
    }
    else if (comando_usuario == UTILIZAR_EXTINTOR){
        orden_correcta = true;
    }
    if (!(orden_correcta)){
      printf("Intente con otro comando!\n");
    }
  }
  ejecutar_comando(juego, comando_usuario, index_nivel_actual, se_uso_herramienta, se_roto_mapa, se_piso_fuego, comando_efectuado);
}


//-----------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------//


//Precondiciones: -
//Postcondiciones: Devuelve CONDICION_GANADO (1) si el jugador ya recolectó todos los papeleos
//                o CONDICION_JUGANDO (0) si todavía restan papeleos por recoger.
int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
  int condicion_nivel = CONDICION_JUGANDO;
  int contador_de_recolectados = 0;

  for (int i = 0; i < tope_papeleos; i++){
    if (papeleos[i].recolectado){
      contador_de_recolectados++;
    }
  }

  if (contador_de_recolectados == tope_papeleos){
    condicion_nivel = CONDICION_GANADO;
  }
  return condicion_nivel;
}


//Precondiciones: -
//Postcondiciones: La función devuelve el estado actual del juego analizando si se cumplen
//                 las condiciones para perder, ganar o seguir en juego.
//Devolverá:
//--> CONDICION_JUGANDO (0) si el estado es jugando. ---> Estado predeterminado si no se cumple que el jugador perdió o ganó
//--> CONDICION_GANADO (1) si el jugador llego a recoger todos los papeleos (así sea su último movimiento)
//--> CONDICION_PERDIDO (-1) si no tiene movimientos restantes y no recogió todo.
int estado_juego(juego_t juego){
  int condicion_juego = CONDICION_JUGANDO;

  if (juego.jugador.movimientos >= 0
    && estado_nivel(juego.niveles[INDEX_NIVEL_MAXIMO].papeleos, juego.niveles[INDEX_NIVEL_MAXIMO].tope_papeleos) == CONDICION_GANADO){

      condicion_juego = CONDICION_GANADO;
  }
  else if (juego.jugador.movimientos <= 0 &&
    estado_nivel(juego.niveles[INDEX_NIVEL_MAXIMO].papeleos, juego.niveles[INDEX_NIVEL_MAXIMO].tope_papeleos) != CONDICION_GANADO){

      condicion_juego = CONDICION_PERDIDO;
  }
  return condicion_juego;
}


//Precondiciones: numero_nivel debe corresponder a un nivel posible dentro del juego.
//Postcondiciones: Modifica por referencia los movimientos del usuario en base al nivel en el que esté y su personaje.
int movimientos_nivel(int numero_nivel){
  int movimientos_nivel = 0;

  switch (numero_nivel) {
    case (2):
      movimientos_nivel = MOVIMIENTOS_INICIALES_NIVEL_2;
      break;
    case (3):
      movimientos_nivel = MOVIMIENTOS_INICIALES_NIVEL_3;
      break;
    default:
      printf("todo mal");
  }
return movimientos_nivel;
}

//Precondiciones -
//Postcondiciones: Realiza todas las acciones sobre el juego al pasar de nivel.
void pasar_de_nivel(juego_t* juego){
  (*juego).nivel_actual++;
  (*juego).jugador.movimientos += movimientos_nivel((*juego).nivel_actual);
  (*juego).jugador.movimientos_realizados = 0;
  obtener_herramientas_mochila(&((*juego).jugador.extintores), &((*juego).jugador.martillos), (*juego).nivel_actual, (*juego).personaje_tp1);
  (*juego).jugador.posicion = (*juego).niveles[(*juego).nivel_actual -1].pos_inicial_jugador;
  (*juego).jugador.ahuyenta_randall = false;
}

//Precondiciones -
//Postcondiciones: Realiza todas las acciones correspondientes a un turno dentro del juego.
void realizar_jugada(juego_t* juego){
  bool comando_efectuado = false;
  bool se_uso_herramienta = false;
  bool se_roto_mapa = false;
  bool se_piso_fuego = false;

  pedir_comandos(juego, &(se_uso_herramienta), &(se_roto_mapa), &(se_piso_fuego), &(comando_efectuado));

  if (comando_efectuado){
    if (!(se_uso_herramienta) && !(se_roto_mapa)){
      analizar_posicion_actual(&((*juego).niveles[(*juego).nivel_actual -1]), &((*juego).jugador),(*juego).nivel_actual, &(se_piso_fuego));
    }
    verificar_gravedad(juego, ((*juego).nivel_actual -1), &(se_piso_fuego));
    if (!(se_uso_herramienta)){
      verificar_ahuyenta_randall(&((*juego).niveles[(*juego).nivel_actual -1]), (*juego).jugador, (*juego).nivel_actual);
      generar_pared_aleatoria(&((*juego).niveles[(*juego).nivel_actual -1]), (*juego).jugador, (*juego).nivel_actual);
    }
  }
  if(estado_nivel((*juego).niveles[(*juego).nivel_actual -1].papeleos, (*juego).niveles[(*juego).nivel_actual -1].tope_papeleos) == CONDICION_GANADO
  && (*juego).nivel_actual < MAXIMO_NIVEL){
    pasar_de_nivel(juego);
    //system("clear");
    printf("%s\n", MENSAJE_NIVEL_GANADO);
    printf("Comienza el nivel %i\n", (*juego).nivel_actual);
    //detener_el_tiempo((float)3);
  }
}
