#include <stdio.h>
#include <stdbool.h>


//Constantes

const char P1_OLAF = 'T';  //Las constantes que comienzan con "P1" o "P2" corresponden a las opciones disponibles para las preguntas 1 y 2 (respectivamente).
const char P1_STICH = 'N';
const char P1_RAYO = 'C';
const char P1_JASMIN = 'A';
const char P2_OLAF = 'B';
const char P2_STICH = 'P';
const char P2_RAYO = 'K';
const char P2_JASMIN = 'G';
const int MAX_HORA = 23;
const int MAX_MIN = 59;
const int PUNTAJE_MIN_OLAF_STITCH = 13; //Las constantes que comienzan con "PUNTAJE" son los valores que separan los dos posibles escenarios en base al puntaje del user.
const int PUNTAJE_MAX_OLAF_STITCH = 41;
const int PUNTAJE_MIN_MCQ_JASMIN = 42;
const int PUNTAJE_MAX_MCQ_JASMIN = 68;
const int HORA_EXAMEN = 15;
const int MINUTO_EXAMEN = 30;
const int MIN_NOTA = 1;
const int MAX_NOTA = 10;
static const char OBSEQUIO_JASMIN = 'J';
static const char OBSEQUIO_OLAF = 'O';
static const char OBSEQUIO_STITCH = 'S';
static const char OBSEQUIO_RAYO = 'R';

//Precondiciones: -
//Postcondiciones: Muestra la respuesta del usuario dentro de un void para mantener la buena práctica.
void respuesta_en_pantalla(char respuesta){
  printf("%c es la opción elegida.\n", respuesta);
}


//Precondiciones: -
//Postcondiciones: Muestra la respuesta del usuario dentro de un void para mantener la buena práctica.
void horario_en_pantalla(int hora, int minutos){
  printf("La hora de llegada a la facultad es %i:%i.\n",hora, minutos);
}


//Precondiciones: -
//Postcondiciones: Muestra la respuesta del usuario dentro de un void para mantener la buena práctica.
void nota_en_pantalla(int nota){
  printf("La nota obtenida en el exámen es de %i.\n", nota);
}


//Precondiciones: -
//Postcondiciones: Interacción con el usuario dentro de una función void para buena práctica, cambia por referencia la respuesta del usuario en la pregunta 1.
void input_pregunta1(char* respuesta1){
  scanf(" %c", respuesta1);
}


//Precondiciones: -
//Postcondiciones: Cambia por referencia el valor de "input_correcto1" a true si se cumple que la variable respuesta1 corresponda a una opción posible del cuestionario.
void control_pregunta1(bool* input_correcto1,char respuesta1){
  if (respuesta1 == P1_OLAF || respuesta1 == P1_STICH || respuesta1 == P1_RAYO || respuesta1 == P1_JASMIN){
    (*input_correcto1) = true;
  }
}


//Precondiciones: -
//Postcondiciones: Pregunta al usuario hasta que ingresa una de las opciones posibles del cuestionario (pregunta 1, constantes "P1"), luego almacena en una variable la respuesta.
char inicializar_pregunta1(){
  printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes.\n¿Qué otro transporte elegís?\n");
  printf("Ingrese una opción dentro de las siguientes disponibles:\n");
  printf("Ingrese 'T' si decide ir en trineo.\nIngrese 'N' si decide ir en nave espacial.\n");
  printf("Ingrese 'C' si decide ir en camión.\nIngrese 'A' si decide ir en alfombra voladora.\n");
  char respuesta1;
  bool input_correcto1 = false;
  input_pregunta1(&respuesta1);
  control_pregunta1(&input_correcto1, respuesta1);
  while (!input_correcto1){
    printf("Error! Favor de ingresar una de las opciones disponibles (Recuerde que la opción debe estar typeada en Mayúscula).\n");
    input_pregunta1(&respuesta1);
    control_pregunta1(&input_correcto1, respuesta1);
  }
  return respuesta1;
}


//Precondiciones: -
//Postcondiciones: Interacción con el usuario dentro de una función void para buena práctica, cambia por referencia la respuesta del usuario en la pregunta 2.
void input_pregunta2(char* respuesta2){
  scanf(" %c", respuesta2);
}


//Precondiciones: -
//Postcondiciones: Cambia por referencia el valor de "input_correcto2" a true si se cumple que la variable respuesta2 corresponda a una opción del cuestionario.
void control_pregunta2(bool* input_correcto2,char respuesta2){
  if (respuesta2 == P2_OLAF || respuesta2 == P2_STICH || respuesta2 == P2_RAYO || respuesta2 == P2_JASMIN){
    (*input_correcto2) = true;
  }
}


//Precondiciones: -
//Postcondiciones: Pregunta al usuario hasta que ingresa una de las opciones posibles del cuestionario (pregunta 2, constantes "P2"), luego almacena en una variable la respuesta.
char inicializar_pregunta2(){
  printf("En medio del camino te encontras con una manifestación.\n");
  printf("¿Que medio utilizas para deshacerte de la manifestación?\n");
  printf("Ingrese una opción dentro de las siguientes disponibles:\n");
  printf("Ingrese 'B' si decide tirar bolas de nieve.\nIngrese 'P' si decide utilizar la pistola de Stich.\n");
  printf("Ingrese 'K' si decide subirse al Rayo McQueen.\nIngrese 'G' si decide pedirle un deseo al genio.\n");
  char respuesta2;
  bool input_correcto2 = false;
  input_pregunta2(&respuesta2);
  control_pregunta2(&input_correcto2, respuesta2);
  while (!input_correcto2){
    printf("Error! Favor de ingresar una de las opciones disponibles (Recuerde que la opción debe estar typeada en Mayúscula).\n");
    input_pregunta2(&respuesta2);
    control_pregunta2(&input_correcto2, respuesta2);
  }
  return respuesta2;
}


//Precondiciones: -
//Postcondiciones: Cambia por referencia el valor de "horario_correcto" a true si se cumple que el horario ingresado es válido.
void checkeo_horario(bool* horario_correcto,int llegada_hora_aux, int llegada_minuto_aux){
  if (llegada_hora_aux <= MAX_HORA && llegada_hora_aux >= 0 && llegada_minuto_aux <= MAX_MIN){
    (*horario_correcto) = true;
  }
}


//Precondiciones: -
//Postcondiciones: Cambia por referencia los valores de "hora_llegada" y "minuto_llegada" por la hora ingresada en el formato 00:00 a 23:59 (control realizado en checkeo_horario).
void cambio_de_horario(int* hora_llegada, int* minuto_llegada){
  printf("Para continuar el test, debe ingresar al horario en el cual arribó a la universidad.\n");
  printf("¡Recuerde que debe ingresar el horario en el formato digital de 00:00 a 23:59! (y separando de la forma ---> hora.minutos)\n");
  float llegada_raw;
  bool horario_correcto = false;
  scanf(" %f", &llegada_raw);
  int llegada_hora_aux = (int)llegada_raw;
  int llegada_minuto_aux = (int)(llegada_raw*100) - (llegada_hora_aux*100);
  checkeo_horario(&horario_correcto, llegada_hora_aux, llegada_minuto_aux);
  while (!horario_correcto){
    printf("Error! Debe ingresar un horario válido.\n");
    scanf(" %f", &llegada_raw);
    llegada_hora_aux = (int)llegada_raw;
    llegada_minuto_aux = (int)(llegada_raw*100) - (llegada_hora_aux*100);
    checkeo_horario(&horario_correcto, llegada_hora_aux, llegada_minuto_aux);
  }
  (*hora_llegada) = llegada_hora_aux;
  (*minuto_llegada) = llegada_minuto_aux;
}


//Precondiciones: -
//Postcondiciones: Devuelve un valor correspondiente a la nota de un exámen luego de verificar que pudiera corresponder a una posible (que esté entre 1 y 10).
int input_nota_examen(){
  printf("Finalmente, ingrese la nota que obtuvo en el final:\n");
  int nota;
  scanf(" %i", &nota);
  while (nota < MIN_NOTA || nota > MAX_NOTA){
    printf("Error! Según el sistema de notas de la facultad, su nota solo puede ir de 1 a 10.\n");
    printf("Intente nuevamente.\n");
    scanf(" %i", &nota);
  }
  return nota;
}


//Precondiciones: "respuesta_pregunta1" debe corresponder a una de las opciones disponibles a la primera pregunta del cuestionario (Control realizado en la función control_pregunta1).
//Postcondiciones: Devuelve un valor que corresponde al puntaje del usuario luego de analizar la respuesta de la pregunta 1.
int analisis_puntos1(char respuesta_pregunta1){
  int puntos1;
  if (respuesta_pregunta1 == P1_OLAF || respuesta_pregunta1 == P1_STICH){
    puntos1 = 10;
  }
  if (respuesta_pregunta1 == P1_RAYO || respuesta_pregunta1 == P1_JASMIN){
    puntos1 = 20;
  }
  return puntos1;
}


//Precondiciones: "respuesta_pregunta2" debe corresponder a una de las opciones disponibles a la segunda pregunta del cuestionario (Control realizado en la función control_pregunta2).
//Postcondiciones: Devuelve un valor que corresponde al puntaje del usuario luego de analizar la respuesta de la pregunta 2.
int analisis_puntos2(char respuesta_pregunta2){
  int puntos2;
  if (respuesta_pregunta2 == P2_OLAF){
    puntos2 = 3;
  }
  if (respuesta_pregunta2 == P2_STICH){
    puntos2 = 6;
  }
  if (respuesta_pregunta2 == P2_RAYO){
    puntos2 = 9;
  }
  if (respuesta_pregunta2 == P2_JASMIN){
    puntos2 = 12;
  }
  return puntos2;
}


//Precondiciones: "respuesta_nota" debe corresponder a una nota posible de obtener al rendir un exámen, es decir que este entre 1 y 10 (control realizado en input_nota_examen).
//Postcondiciones: Devuelve un valor que corresponde al multiplicador de puntaje del usuario luego de analizar su nota en el examen con el criterio del test.
int determinar_multiplicador(int respuesta_nota){
  int multiplicador;
  if (respuesta_nota >= 1 && respuesta_nota <= 3){
    multiplicador = 1;
  }
  if (respuesta_nota >= 4 && respuesta_nota <= 6){
    multiplicador = 2;
  }
  if (respuesta_nota >= 7 && respuesta_nota <= 8){
    multiplicador = 3;
  }
  if (respuesta_nota >= 9 && respuesta_nota <= 10){
    multiplicador = 4;
  }
  return multiplicador;
}


//Precondiciones: "puntos1", "puntos2" y "multiplicador" deben corresponder a números definidos en base a las respuestas del usuario a lo largo del cuestionario y su criterio.
//Precondiciones: "hora_llegada" y "minuto_llegada" deben corresponder a la hora ingresada por el usuario dentro del esquema de 00:00 a 23:59 (control realizado en checkeo_horario).
//Postcondiciones: Determina el personaje asignado al usuario en base al puntaje final que obtuvo luego de aplicado el algoritmo de determinación de puntaje final.
void resultado_personaje(int puntos1,int puntos2,int multiplicador,int hora_llegada,int minuto_llegada,char* obsequio){
  int puntaje_final = puntos1 + (puntos2 * multiplicador);
  printf("%i es el puntaje obtenido, %i el multiplicador\n", puntaje_final, multiplicador);
  if (puntaje_final <= PUNTAJE_MAX_OLAF_STITCH){
    if (hora_llegada < HORA_EXAMEN){
      printf("Llegaste antes al exámen gracias a la nave de Stitch!\n");
      printf("-Stitch-\n");
      (*obsequio) = OBSEQUIO_STITCH;
    }
    if (hora_llegada > HORA_EXAMEN){
      printf("Llegaste tarde al exámen porque el trineo de Olaf es muy lento!\n");
      printf("-Olaf-\n");
      (*obsequio) = OBSEQUIO_OLAF;
    }
    if (hora_llegada == 15 && minuto_llegada > MINUTO_EXAMEN){
      printf("Llegaste tarde al exámen porque el trineo de Olaf es muy lento! -Olaf-\n");
      printf("-Olaf-\n");
      (*obsequio) = OBSEQUIO_OLAF;
    }
    if (hora_llegada == 15 && minuto_llegada < MINUTO_EXAMEN){
      printf("Llegaste antes al exámen gracias a la nave de Stitch!\n");
      printf("-Stitch-\n");
      (*obsequio) = OBSEQUIO_STITCH;
    }
    if (hora_llegada == 15 && minuto_llegada == MINUTO_EXAMEN){
      printf("Llegaste puntual al exámen gracias a la nave de Stitch!\n");
      printf("-Stitch-\n");
      (*obsequio) = OBSEQUIO_STITCH;
    }
  }
  if (puntaje_final >= PUNTAJE_MIN_MCQ_JASMIN && puntaje_final<= PUNTAJE_MAX_MCQ_JASMIN){
    if (hora_llegada < HORA_EXAMEN){
      printf("Llegaste antes al exámen gracias a la alfombra voladora de Jasmín!\n");
      printf("-Jasmín-\n");
      (*obsequio) = OBSEQUIO_JASMIN;
    }
    if (hora_llegada > HORA_EXAMEN){
      printf("Llegaste tarde al exámen porque el camón del Rayo se quedo en el tráfico!\n");
      printf("-Rayo McQueen-\n");
      (*obsequio) = OBSEQUIO_RAYO;
    }
    if (hora_llegada == 15 && minuto_llegada > MINUTO_EXAMEN){
      printf("Llegaste tarde al exámen porque el camón del Rayo se quedo en el tráfico!\n");
      printf("-Rayo McQueen-\n");
      (*obsequio) = OBSEQUIO_RAYO;
    }
    if (hora_llegada == 15 && minuto_llegada < MINUTO_EXAMEN){
      printf("Llegaste antes al exámen gracias a la alfombra voladora de Jasmín!\n");
      printf("-Jasmín-\n");
      (*obsequio) = OBSEQUIO_JASMIN;
    }
    if (hora_llegada == 15 && minuto_llegada == MINUTO_EXAMEN){
      printf("Llegaste puntual al exámen gracias a la alfombra voladora de Jasmín!\n");
      printf("-Jasmín-\n");
      (*obsequio) = OBSEQUIO_JASMIN;
    }
  }
}


char obtener_obsequio() {
  char obsequio;
  printf("Bienvenido al test de personalidad de AyP1!\n");
  printf("En el siguiente test, luego de contestar una serie de preguntas en contexto fiubense, se le asignara un personaje dentro de un listado.\n");
  printf("Comencemos!\n");
  char respuesta_pregunta1 = inicializar_pregunta1();
  respuesta_en_pantalla(respuesta_pregunta1);
  char respuesta_pregunta2 = inicializar_pregunta2();
  respuesta_en_pantalla(respuesta_pregunta2);
  int hora_llegada;
  int minuto_llegada;
  cambio_de_horario(&hora_llegada, &minuto_llegada);
  horario_en_pantalla(hora_llegada, minuto_llegada);
  int respuesta_nota = input_nota_examen();
  nota_en_pantalla(respuesta_nota);
  int puntos_pregunta_1 = analisis_puntos1(respuesta_pregunta1);
  int puntos_pregunta_2 = analisis_puntos2(respuesta_pregunta2);
  int multiplicador = determinar_multiplicador(respuesta_nota);
  printf("A continuación el programa determinará su personaje.\n");
  resultado_personaje(puntos_pregunta_1, puntos_pregunta_2, multiplicador, hora_llegada, minuto_llegada, &obsequio);
  return obsequio;
}
