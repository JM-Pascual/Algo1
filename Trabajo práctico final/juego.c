#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "obsequio.h"
#include "papeleo.h"
#include "utiles.h"
#include "controlador.h"


#define MENSAJE_BIENVENIDA "\
                                                                                  ⠀⠀⠀⠀⠀⠀⣤⡀⠀⠀⢀⣠⠖⠚⠉⠉⠙⠒⢦⡀⠀⠀⠀⣠⡄⠀⠀⠀⠀⠀ \n \
                                                                                  ⠀⠀⠀⠀⠀⣸⠁⠳⣄⣰⠋⣠⠖⠉⠉⠈⠉⠓⢤⡙⢦⣀⡼⠁⢳⠀⠀⠀⠀⠀ \n \
                                                                                  ⠀⠀⠀⠀⢀⡇⢀⣤⡾⢡⢞⣤⡒⠭⠭⠭⠭⠕⣦⣙⣆⠻⣦⡀⠘⡇⠀⠀⠀⠀ \n \
                                                                                  ⠀⠀⠀⠀⠘⣧⠞⡝⢠⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠉⠻⣦⠹⡝⢦⡇⠀⠀⠀⠀ \n \
                                                                                  ⠀⠀⠀⢀⡼⠁⡘⢠⠋⠀⠀⠀⡠⠔⠒⠒⠒⠤⡀⠀⠀⠈⢇⠱⠈⠳⡄⠀⠀⠀ \n \
                                                                                  ⠀⠀⢀⡞⠀⠀⠁⡎⠀⠀⠀⡞⠀⣴⣿⣿⣷⡀⠙⡄⠀⠀⠘⡄⠁⠀⠹⣆⠀⠀ \n \
                                                                                  ⠀⢀⡞⠀⠀⠀⠀⡇⠀⠀⠘⡇⠀⢿⣿⣿⡿⠃⠀⡇⠀⠀⢀⡇⠀⠀⠀⠹⡄⠀ \n \
                                                                                  ⠀⡾⠁⠀⠀⠀⠀⣿⡀⠀⠀⠙⠦⣀⣀⣀⣀⡠⠞⠀⠀⠀⡼⡆⠀⠀⠀⠀⢹⡀ \n \
                                                                                  ⢰⠇⠀⠀⠀⠀⠀⠐⡿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢜⠝⠀⠀⠀⠀⠀⠀⣇ \n \
                                                                                  ⣼⠀⠀⠀⢀⣀⠀⠀⠈⠪⢕⡲⢤⣤⣀⣀⣠⡤⠴⣚⠕⠁⠀⠀⣀⣀⠀⠀⠀⢸ \n \
                                                                                  ⡏⠀⠀⠉⠈⡷⢄⡀⠀⠀⠀⠈⠁⠒⠒⠒⠒⠊⠉⠀⠀⠀⠀⣀⢔⡇⠈⠀⠀⢸ \n \
                                                                                  ⣷⠀⠀⠀⠀⠘⡌⢮⡑⠲⡤⠤⢤⠀⠤⠤⠤⠤⠤⠤⡔⠒⡩⢋⡞⠀⠀⠀⠀⢸ \n \
                                                                                  ⢸⡀⠀⠀⠀⠀⠈⢦⡜⣖⢍⠢⠼⠣⠠⠦⠔⠣⠤⡊⣑⠟⡤⠋⠀⠀⠀⠀⠀⡾ \n \
                                                                                  ⠈⣧⠀⠀⠀⠀⠀⠀⠉⠛⠤⣕⣎⣰⢊⡑⣔⣙⣖⡥⠞⠋⠀⠀⠀⠀⠀⠀⣰⠃ \n \
                                                                                  ⠀⠈⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠋⠀ \n \
                                                                                  ⠀⠀⠈⠻⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀ \n \
                                                                                  ⠀⠀⠀⠀⠈⠛⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⠞⠁⠀⠀⠀⠀ \n \
                                                                                  ⠀⠀⠀⠀⠀⠀⠀⠈⠙⠓⠶⠤⣤⣄⣀⣀⣀⣤⡤⠴⠖⠛⠁⠀⠀⠀⠀⠀⠀⠀ \n \
                                                                                  \n \
                                                                                  \n \
BBBBBBBBBBBBBBBBB   IIIIIIIIIIEEEEEEEEEEEEEEEEEEEEEENNNNNNNN        NNNNNNNNVVVVVVVV           VVVVVVVVEEEEEEEEEEEEEEEEEEEEEENNNNNNNN        NNNNNNNNIIIIIIIIIIDDDDDDDDDDDDD             OOOOOOOOO      \n \
B::::::::::::::::B  I::::::::IE::::::::::::::::::::EN:::::::N       N::::::NV::::::V           V::::::VE::::::::::::::::::::EN:::::::N       N::::::NI::::::::ID::::::::::::DDD        OO:::::::::OO    \n \
B::::::BBBBBB:::::B I::::::::IE::::::::::::::::::::EN::::::::N      N::::::NV::::::V           V::::::VE::::::::::::::::::::EN::::::::N      N::::::NI::::::::ID:::::::::::::::DD    OO:::::::::::::OO   \n \
BB:::::B     B:::::BII::::::IIEE::::::EEEEEEEEE::::EN:::::::::N     N::::::NV::::::V           V::::::VEE::::::EEEEEEEEE::::EN:::::::::N     N::::::NII::::::IIDDD:::::DDDDD:::::D  O:::::::OOO:::::::O  \n \
B::::B     B:::::B  I::::I    E:::::E         EEEEEEN::::::::N    N::::::N V:::::V           V:::::V   E:::::E       EEEEEEN::::::::::N    N::::::N  I::::I    D:::::D    D:::::D O::::::O   O::::::::O  \n \
B::::B     B:::::B  I::::I    E:::::E             N:::::::::::N   N::::::N  V:::::V         V:::::V    E:::::E             N:::::::::::N   N::::::N  I::::I    D:::::D     D:::::DO:::::O     O:::::::O  \n \
B::::BBBBBB:::::B   I::::I    E::::::EEEEEEEEEE   N:::::::N::::N  N::::::N   V:::::V       V:::::V     E::::::EEEEEEEEEE   N:::::::N::::N  N::::::N  I::::I    D:::::D     D:::::DO:::::O     O:::::::O  \n \
B:::::::::::::BB    I::::I    E:::::::::::::::E   N::::::N N::::N N::::::N    V:::::V     V:::::V      E:::::::::::::::E   N::::::N N::::N N::::::N  I::::I    D:::::D     D:::::DO:::::O     O:::::::O  \n \
B::::BBBBBB:::::B   I::::I    E:::::::::::::::E   N::::::N  N::::N:::::::N     V:::::V   V:::::V       E:::::::::::::::E   N::::::N  N::::N:::::::N  I::::I    D:::::D     D:::::DO:::::O     O:::::::O  \n \
B::::B     B:::::B  I::::I    E::::::EEEEEEEEEE   N::::::N   N:::::::::::N      V:::::V V:::::V        E::::::EEEEEEEEEE   N::::::N   N:::::::::::N  I::::I    D:::::D     D:::::DO:::::O     O:::::::O  \n \
B::::B     B:::::B  I::::I    E:::::E             N::::::N    N::::::::::N       V:::::V:::::V         E:::::E             N::::::N    N::::::::::N  I::::I    D:::::D     D:::::DO:::::O     O:::::::O  \n \
B::::B     B:::::B  I::::I    E:::::E         EEEEEEN::::N     N:::::::::N        V:::::::::V          E:::::E       EEEEEEN::::::N     N:::::::::N  I::::I    D:::::D    D:::::D O::::::O   O::::::::O  \n \
BB:::::BBBBBB::::::BII::::::IIEE::::::EEEEEEEE:::::EN::::::N      N::::::::N         V:::::::V         EE::::::EEEEEEEE:::::EN::::::N      N::::::::NII::::::IIDDD:::::DDDDD:::::D  O:::::::OOO:::::::O  \n \
B:::::::::::::::::B I::::::::IE::::::::::::::::::::EN::::::N       N:::::::N          V:::::V          E::::::::::::::::::::EN::::::N       N:::::::NI::::::::ID:::::::::::::::DD    OO:::::::::::::OO  \n \
B::::::::::::::::B  I::::::::IE::::::::::::::::::::EN::::::N        N::::::N           V:::V           E::::::::::::::::::::EN::::::N        N::::::NI::::::::ID::::::::::::DDD        OO:::::::::OO    \n \
BBBBBBBBBBBBBBBBB   IIIIIIIIIIEEEEEEEEEEEEEEEEEEEEEENNNNNNNN         NNNNNNN            VVV            EEEEEEEEEEEEEEEEEEEEEENNNNNNNN         NNNNNNNIIIIIIIIIIDDDDDDDDDDDDD             OOOOOOOOO      \n \
\n \
\n \
\n"



#define MENSAJE_GANASTE_JUEGO "\n \
                                                                                            \n \
     .g8OOObgd       db        MN.   `7MF'     db       .MSSSbgd PTTMMTTYMMMM  |EEYMMMM\n \
   .dP'     `M      ;MM:       MMN.    M      ;MM:     ,MI            MM        M      `7  \n \
   dM'       `     ,V^MM.      M YMb   M     ,V^MM.    `MMb.          MM        MM   d    \n \
   MM             ,M  `MM      M  `MN. M    ,M  `MM      `YMMNq.      MM        MMmmMM    \n \
   MM.    `7MMF'  AbmmmqMA     M   `MM.M    AbmmmqMA   .     `MM      MM        MM   Y  , \n \
   `Mb.     MM   A'     VML    M     YMM   A'     VML  Mb     dM      MM        MM     ,M \n \
     `GbmmmdPY .AMA.   .AMMA..JML.    YM .AMA.   .AMMA.PSYbmmdS     .JMML.    .JMMmmmmMMM \n \
\n \
             5 | 5 |  ---------------------------\n \
             | |_| |  |                         |\n \
             5   O O|_    ¡¡¡Felicitaciones!!!  |\n \
            5          3  Gracias por jugar :)  |\n \
           5      3     3                       |\n \
          5   _    3     3 ----------------------\n \
         5    |3____3     3      ||\n \
        5     | | | |_____5      ||\n \
       5       3| | | |5 |     __||\n \
      5  5  3   -------  |_____| ||\n \
     5   |   |           |       --|\n \
     |   |   |           |_____  --|\n \
     |  |_|_|_|          |     3--- \n \
    53                  | \n \
   5 53        |        5 \n \
  5 5  |       |       | \n \
 ___5 5|       |       | \n \
|____5 |______5 3______| \n \
\n \
\n"


#define MENSAJE_PERDISTE_JUEGO "\n \
8 888888888o   8 8888888888   8 888888888o.   8 888888888o.       8 8888    d888888o. 8888888 8888888888 8 8888888888  \n \
8 8888    `88. 8 8888         8 8888    `88.  8 8888    `^888.    8 8888  .`8888:' `88.     8 8888       8 8888         \n \
8 8888     `88 8 8888         8 8888     `88  8 8888        `88.  8 8888  8.`8888.   Y8     8 8888       8 8888         \n \
8 8888     ,88 8 8888         8 8888     ,88  8 8888         `88  8 8888  `8.`8888.         8 8888       8 8888         \n \
8 8888.   ,88' 8 888888888888 8 8888.   ,88'  8 8888          88  8 8888   `8.`8888.        8 8888       8 888888888888 \n \
8 888888888P'  8 8888         8 888888888P'   8 8888          88  8 8888    `8.`8888.       8 8888       8 8888         \n \
8 8888         8 8888         8 8888`8b       8 8888         ,88  8 8888     `8.`8888.      8 8888       8 8888         \n \
8 8888         8 8888         8 8888 `8b.     8 8888        ,88'  8 8888 8b   `8.`8888.     8 8888       8 8888         \n \
8 8888         8 8888         8 8888   `8b.   8 8888    ,o88P'    8 8888 `8b.  ;8.`8888     8 8888       8 8888         \n \
8 8888         8 888888888888 8 8888     `88. 8 888888888P'       8 8888  `Y8888P ,88P'     8 8888       8 888888888888 \n \
\n \
    _ \n \
   | | \n \
   | |___( )   //////   \n \
   |_|   |||  | o o|   \n \
         |||  ( c  )                  ____ \n \
          ||| | -/                  ||    8_ \n \
           |||||||                  ||     | \n \
           ||||||                ...||__/|-- \n \
           ||||||             __|________|__ \n \
             |||             |______________| \n \
             |||             || ||      || || \n \
             |||             || ||      || || \n \
   --------------------------||-||------||-||---------- \n \
             |__>            || ||      || ||  \n \
\n \
    Mejor suerte la próxima! :( \n \
\n"


#define CONTROLES "\n \
       ,o888888o.        ,o888888o.     b.             8 8888888 8888888888 8 888888888o.      ,o888888o.     8 8888         8 8888888888     d888888o.   \n \
      8888     `88.   . 8888     `88.   888o.          8       8 8888       8 8888    `88.  . 8888     `88.   8 8888         8 8888         .`8888:8 `88. \n \
   ,8 8888       `8. ,8 8888       `8b  Y88888o.       8       8 8888       8 8888     `88 ,8 8888       `8b  8 8888         8 8888         8.`8888.   Y8 \n \
   88 8888           88 8888        `8b .`Y888888o.    8       8 8888       8 8888     ,88 88 8888        `8b 8 8888         8 8888         `8.`8888.     \n \
   88 8888           88 8888         88 8o. `Y888888o. 8       8 8888       8 8888.   ,888 88 8888         88 8 8888         8 888888888888  `8.`8888.    \n \
   88 8888           88 8888         88 8`Y8o. `Y88888o8       8 8888       8 888888888P8  88 8888         88 8 8888         8 8888           `8.`8888.   \n \
   88 8888           88 8888        ,8P 8   `Y8o. `Y8888       8 8888       8 8888`8b      88 8888        ,8P 8 8888         8 8888            `8.`8888.  \n \
   `8 8888       .88 `8 8888       ,8P  8      `Y8o. `Y8       8 8888       8 8888 `8b.    `8 8888       ,8P  8 8888         8 8888        8b   `8.`8888. \n \
      8888     ,888   ` 8888     ,888   8         `Y8o.`       8 8888       8 8888   `8b.   ` 8888     ,888   8 8888         8 8888        `8b.  ;8.`8888 \n \
       `8888888P8        `8888888P8     8            `Yo       8 8888       8 8888     `88.    `8888888P8     8 888888888888 8 888888888888 `Y8888P ,88P \n \
\n \
\n \
\n \
                                   .-----------------------------------------------------------------------------.\n \
                                   ||Es| |F1 |F2 |F3 |F4 |F5 | |F6 |F7 |F8 |F9 |F10|                             |\n \
                                   ||__| |___|___|___|___|___| |___|___|___|___|___|                             |\n \
                                   | _____________________________________________    _________    ___________   |\n \
                                   ||~  |! | |§ |$ |  |& |/ |( |) |= |? |` || |<-|   |Del|Help |  |{ |} |/ |*||  |\n \
                                   ||`__|1_|2_|3_|4_|5_|6_|7_|8_|9_|0_|ß_|´_||_|__|  |____|____|  |[ |]_|__|__|  |\n \
                                   ||<-  |Q |W |E |R |T |Z |U |I |O |P |Ü |* |   ||               |7 |8 |9 |- |  |\n \
                                   ||->__|__|__|__|__|__|__|__|__|__|__|__|+_|_  ||               |__|__|__|__|  |\n \
                                   ||Ctr|oC|A |S |D |F |G |H |J |K |L |Ö |Ä |^ |<'|               |4 |5 |6 |+ |  |\n \
                                   ||___|_L|__|__|__|__|__|__|__|__|__|__|__|#_|__|       __      |__|__|__|__|  |\n \
                                   ||^    |> |Y |X |C |V |B |N |M |; |: |_ |^     |      |A |     |1 |2 |3 |E |  |\n \
                                   ||_____|<_|__|__|__|__|__|__|__|,_|._|-_|______|    __||_|__   |__|__|__|n |  |\n \
                                   |   |Alt|A  |                       |A  |Alt|      |<-|| |->|  |0    |. |t |  |\n \
                                   |   |___|___|_______________________|___|___|      |__|V_|__|  |_____|__|e_|  |\n \
                                   |                                                                             |\n \
                                   `-----------------------------------------------------------------------------'\n \
\n \
    El juego consiste en llevar a Mike desde un nivel a otro, recogiendo los papeleos dispersos por el mapa (EN ORNDEN!) para lograr que Roz nos deje en paz finalmente.\n \
    Estos se encuentran representados por números, los cuales indican a su vez el orden en el que deben recogerse.\n \
\n \
    Dispondrás de varias acciones posibles para acercarte a los papeleos:\n \
    - A ---> Movimiento lateral hacia la izquierda (Cuesta 1 movimiento)\n \
    - D ---> Movimiento lateral hacia la derecha (Cuesta 1 movimiento)\n \
    - E ---> Rotación horaria del mapa (Cuesta 1 movimiento)\n \
    - Q ---> Rotación antihoraria del mapa (Cuesta 1 movimiento)\n \
    - Z ---> Utilizar martillo (Cuesta 1 martillo)\n \
    - C ---> Utilizar extintor (Cuesta 1 extintor)\n \
\n \
    Los martillos permiten romper una pared aledaña en alguna de las 4 direcciones. Las únicas paredes que no podes romper son las que delimitan el nivel en el que estás\n \
    (No está bueno hacer vandalismo, por mucho que odiemos a Roz).\n \
    Por otro lado los extintores permiten extinguir un fuego, también en alguna de las 4 direcciones (Ahora vas a entender que utilidad tiene esto).\n \
    Y, antes de que me olvide, CUIDADO CON ROTAR! TE PODES CAER :O\n \
\n \
    A medida que vayas moviendote, te podes topar con alguno de estos obstáculos o herramientas:\n \
    - FUEGOS ---> Al pisar uno perdes AUTOMÁTICAMENTE el juego, ya que te dejan sin movimientos!\n \
    - MEDIAS ---> Pisarlas te va a traer un problema en la empresa! Por lo que terminas perdiendo 10 MOVIMIENTOS.\n \
    - BOTELLAS DE GRITOS ---> Pisar alguna de estas botellas te va a agregar 7 MOVIMIENTOS! Aprovechalas, son muy útiles.\n \
    - INTERRUPTOR AHUYENTA A RANDALL ---> Randall no se podía quedar afuera, y decide molestarte moviendo de lugar papeleos cuando el decida, pisar este interruptor evita que aparezca.\n \
\n \
    En base al personaje que obtuviste en el cuestionario, tendrás alguno de estos 4 bonus durante el juego!\n \
    - Jasmín: Obsequia 1 MARTILLO extra en cada nivel, gracias al genio de la lámpara.\n \
    - Rayo Mcqueen: Obsequia 10 MOVIMIENTOS extras al comenzar el primer nivel, gracias a su extrema velocidad.\n \
    - Stitch: Obsequia una de sus pistolitas con una única munición, la cual quema 1 PAPELEO del último nivel.\n \
    - Olaf: Con su naturaleza helada, extingue 2 FUEGOS del primer nivel, y 1 FUEGO del segundo nivel.\n \
\n \
    (CONSEJO): No siempre ahuyentar a Randall es buena idea, a veces los papeleos aparecen en posiciones muy difíciles de alcanzar, por lo que podes hacer uso de las picardías de tu némesis.\n \
    (CONSEJO): Los movimientos que te sobren de un nivel se agregan al otro, aprovecha esto!\n \
    (CONSEJO): Antes de planear una jugada rotando el mapa, revisa que tengas los movimientos disponibles para llevarla a cabo.\n \
\n \
    Una vez termines de recolectar los papeleos dispersos en los 3 niveles, Mike por fin será libre de ordenar su papeleo. \n \
    A partir de ahora los comandos que ingreses no necesitan que toques la tecla enter para funcionar. Mucha suerte! :)\n \
\n"


const int CONDICION_JUGANDO = 0;
const int CONDICION_GANADO = 1;
const int CONDICION_PERDIDO = -1;



int main() {
  printf("%s", MENSAJE_BIENVENIDA);
  srand ((unsigned)time(NULL)); // Genera la semilla aleatoria.
  char obsequio = obtener_obsequio();
  juego_t juego;
  inicializar_controlador();
  juego.personaje_tp1 = obsequio;
  printf("Cargando juego!\n");
  //detener_el_tiempo((float)2.5);
  printf("%s\n", CONTROLES);
  inicializar_juego(&juego, obsequio);

  while (estado_juego(juego) == CONDICION_JUGANDO){
    imprimir_terreno(juego);
    realizar_jugada(&juego);
    imprimir_terreno(juego);
    //system("clear");
  }

  if (estado_juego(juego) == CONDICION_GANADO){
    printf("%s", MENSAJE_GANASTE_JUEGO);
  }
  else{
    printf("%s", MENSAJE_PERDISTE_JUEGO);
  }
  terminar_controlador();
  return 0;
}
