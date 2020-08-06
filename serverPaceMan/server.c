#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include "macros.h"

struct sockaddr_in address;
struct struct_tablero tablero;
struct struct_jugador jugador;

int servidor, cliente;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024];
char *ok = "ok";
char *nombresDefault = "BPIC";
char *nombresEAT_ABLE = "bpic";
bool flagEntradaAdmin = false;
bool flagFin = false;
char comandoAdmin[1024];
int posPill[2] = {0,0};
int posiblePills[2][10] = {{1,1,1,1,8,8,18,18,24,24},{1,9,11,19,1,19,1,19,1,19}};
int positionNumber[10] = {0,1,2,3,4,5,6,7,8,9};

struct struct_jugador{
  int posX;
  int posY;
  int puntaje;
  int vidas;
  bool super;
};

struct fantasma{
  char nombre;
  char anterior;
  int posX;
  int posY;
  int aleatorio;
};

struct fruta{
  int score;
  int posX;
  int posY;
  int puntos;
  bool wasDot;
};

struct pill{
  int posX;
  int posY;
  bool wasDot;
};

struct struct_tablero{
  int numeroFantasmas;
  int numeroPills;
  struct fantasma fantasmasActivos[4];
  struct pill pills[10];
  struct fruta bonus;
  int velocidad;
  char area[ALTO][LARGO];
  int dots;
};

int inArray(int numero, int array[]){
    for(int i = 0 ; i < MAX_PILLS; i++) {
      printf("%d\n", array[i]);
        if(array[i] == numero) {
            return i;
        }
    }
    return -1;
}

int fillTablero(){
  jugador.vidas = 3;
  jugador.puntaje = 0;
  jugador.posX = DEFAULT_X;
  jugador.posY = DEFAULT_Y;
  jugador.super = false;
  tablero.numeroFantasmas = 0;
  tablero.numeroPills = 0;
  tablero.dots = NUMERO_DOTS;
  int c;
  FILE *file;
  file = fopen("area", "r");
  if (file) {
    while ((c = getc(file)) != EOF)
        for (int i = 0; i < ALTO; i++){
          for (int j = 0; j < LARGO+1; j++){
            tablero.area[i][j] = c;
            c = getc(file);
          }
        }
    fclose(file);
  } else {
    printf("%s\n", "error opening txt");
    return -1;
  }
  return 0;
}

void wait(int seconds){
  int total = time(0) + seconds;
  while(time(0) < total);
}

void* hiloConsolaAdmin(void *args){
  do{
    printf("Enter a command: ");
    fgets(comandoAdmin,1024,stdin);
    flagEntradaAdmin = true;
    if (strcmp(comandoAdmin,"pill\n") == 0){
      if (tablero.numeroPills < MAX_PILLS) {
            char posIn[5];
            printf("Enter position number: ");
            fgets(posIn,5,stdin);
            int posInAux = atoi(posIn);
            if (inArray(posInAux,positionNumber) != -1) {
              positionNumber[posInAux] = -1;
              posPill[0] = posiblePills[0][posInAux];
              posPill[1] = posiblePills[1][posInAux];
            } else {
              printf("%s\n", "invalid pos, try again");
            }
          } else {
            printf("%s\n", "no more power ups");
          }
    }
    if (strcmp(comandoAdmin,"fruta\n") == 0) {
      char scoreIn[5];
      printf("Enter position score: ");
      fgets(scoreIn,5,stdin);
      tablero.bonus.score = atoi(scoreIn);
      tablero.bonus.posX = DEFAULT_FRUTA_X;
      tablero.bonus.posY = DEFAULT_FRUTA_Y;
    }
    wait(2);
  } while(!flagFin);
}

void* superPacMan(void *args){
  for (int i = 0; i <= tablero.numeroFantasmas; i++){
    tablero.area[tablero.fantasmasActivos[i].posX][tablero.fantasmasActivos[i].posY] = nombresEAT_ABLE[i];
    printf("%d\n", i);
  }
  wait(5);
  jugador.super = false;
  for (int i = 0; i <= tablero.numeroFantasmas; i++){
    tablero.area[tablero.fantasmasActivos[i].posX][tablero.fantasmasActivos[i].posY] = nombresDefault[i];
  }
}

void moverFantasma(int i){
  int posX = tablero.fantasmasActivos[i].posX;
  int posY = tablero.fantasmasActivos[i].posY;
  tablero.area[posX][posY] = tablero.fantasmasActivos[i].anterior;
  if ((posX == DEFAULT_SPAWN_X-3 && posY == DEFAULT_SPAWN_Y)){
    posX = posX-1;
  } else {
    if ((posX == DEFAULT_SPAWN_X-2 && posY == DEFAULT_SPAWN_Y)){
      posX = posX-1;
    } else {
      if ((posX == DEFAULT_SPAWN_X-1 && posY == DEFAULT_SPAWN_Y)){
        posX = posX-1;
      } else {
        if ((posX == DEFAULT_SPAWN_X && posY == DEFAULT_SPAWN_Y)){
          posX = posX-1;

        } else {
          if (tablero.fantasmasActivos[i].aleatorio == 0){
            tablero.fantasmasActivos[i].aleatorio = 0;//cambiar para entre frames
            int n = rand() % 3;
            int incrementoX = 0;
            int incrementoY = 0;
            if (n == 0){
              incrementoX = -1;
            } else {
              if (n == 1){
                incrementoY = 1;
              } else {
                if (n == 2){
                  incrementoX = 1;
                } else {
                  incrementoY = -1;
                }
              }
            }
            if ((tablero.area[posX + incrementoX][posY + incrementoY] != PARED) && (tablero.area[posX + incrementoX][posY + incrementoY] != SPAWN)){
              posX = posX + incrementoX;
              posY = posY + incrementoY;

            } else {
              incrementoX = 0;
              incrementoY = 0;
              for (int j = 0; j < 4; j++){
                if (j == 0){
                  incrementoX = -1;
                } else {
                  if (j == 1){
                    incrementoY = 1;
                  } else {
                    if (j == 2){
                      incrementoX = 1;
                    } else {
                      incrementoY = -1;
                    }
                  }
                }
                if ((tablero.area[posX + incrementoX][posY + incrementoY] != PARED) && (tablero.area[posX + incrementoX][posY + incrementoY] != SPAWN)){
                  posX = posX + incrementoX;
                  posY = posY + incrementoY;

                }
              }
            }
          } else {
            tablero.fantasmasActivos[i].aleatorio = tablero.fantasmasActivos[i].aleatorio + 1;
          }
        }
      }
    }
  }
  tablero.fantasmasActivos[i].posX = posX;
  tablero.fantasmasActivos[i].posY= posY;
  tablero.fantasmasActivos[i].anterior = tablero.area[posX][posY];
  tablero.area[posX][posY] = tablero.fantasmasActivos[i].nombre;
  //toogle betwen random move and good move, maybe using vectors?

}

void checkCommand(){
  if (flagEntradaAdmin){
    if (strcmp(comandoAdmin,"fantasma\n") == 0) {
      if (tablero.numeroFantasmas < MAX_GHOSTS) {
        tablero.fantasmasActivos[tablero.numeroFantasmas].posX = DEFAULT_SPAWN_X;
        tablero.fantasmasActivos[tablero.numeroFantasmas].posY = DEFAULT_SPAWN_Y;
        tablero.fantasmasActivos[tablero.numeroFantasmas].nombre = nombresDefault[tablero.numeroFantasmas];
        tablero.fantasmasActivos[tablero.numeroFantasmas].anterior = SPAWN;
        tablero.fantasmasActivos[tablero.numeroFantasmas].aleatorio = 0;
        tablero.area[DEFAULT_SPAWN_X][DEFAULT_SPAWN_Y] = nombresDefault[tablero.numeroFantasmas];
        tablero.numeroFantasmas = tablero.numeroFantasmas + 1;
        flagEntradaAdmin = false;
        strcpy(comandoAdmin,"");
        return;
      } else {
        printf("%s\n", "deje de pedirla");
      }
    }
    if (strcmp(comandoAdmin,"pill\n") == 0) {
        tablero.pills[tablero.numeroPills].posX = posPill[0];
        tablero.pills[tablero.numeroPills].posY = posPill[1];
        if (tablero.area[posPill[0]][posPill[1]] == PUNTO) {
          tablero.pills[tablero.numeroPills].wasDot = true;
        } else {
          tablero.pills[tablero.numeroPills].wasDot = false;
        }
        tablero.area[posPill[0]][posPill[1]] = PILL;
        tablero.numeroPills = tablero.numeroPills + 1;
        flagEntradaAdmin = false;
        strcpy(comandoAdmin,"");
   }
   if (strcmp(comandoAdmin,"speed\n") == 0) {
     tablero.velocidad = tablero.velocidad + 1;
     printf("%s\n", "gottsagofast");

   }
   if (strcmp(comandoAdmin,"fruta\n") == 0) {
     if (tablero.area[DEFAULT_FRUTA_X][DEFAULT_FRUTA_Y] == PUNTO) {
       tablero.bonus.wasDot = true;
     } else {
       tablero.bonus.wasDot = false;
     }
     tablero.area[DEFAULT_FRUTA_X][DEFAULT_FRUTA_Y] = FRUTA;
     flagEntradaAdmin = false;
     strcpy(comandoAdmin,"");
   }
  }
}

void checkMove(int posX, int posY){
  checkCommand();
  bool flagDead = false;
  for (int i = 0; i < tablero.numeroFantasmas; i++){
    moverFantasma(i);
  }
  if (tablero.area[posX][posY] != PARED && tablero.area[posX][posY] != SPAWN){
    if (tablero.area[posX][posY] == PUNTO){
      jugador.puntaje = jugador.puntaje + PTO_DOT;
      tablero.dots =  tablero.dots - 1;
    }
    if (tablero.area[posX][posY] == PILL) {
      for (int i = 0; i <= tablero.numeroPills; i++) {
        if (tablero.pills[i].wasDot && (tablero.pills[i].posX == posX && tablero.pills[i].posY == posY)){
          tablero.dots =  tablero.dots - 1;
        }
      }
      jugador.super = true;
      pthread_t contador;
      int hilo = pthread_create(&contador,NULL, &superPacMan,NULL);

    }
    if (tablero.bonus.posX == posX && tablero.bonus.posY == posY) {
      jugador.puntaje = jugador.puntaje + tablero.bonus.score;
      if (tablero.bonus.wasDot) {
        tablero.dots =  tablero.dots - 1;
      }
      tablero.bonus.posX = -1;
      tablero.bonus.posY = -1;
    }
    for (int i = 0; i < tablero.numeroFantasmas; i++){
      if (tablero.fantasmasActivos[i].posX == posX && tablero.fantasmasActivos[i].posY == posY){
        if (jugador.super) {
          printf("%s\n","Score");
          //mandar a pos default
        } else {
          printf("%s\n","DED");
          flagDead = true;
        }
      }
    }
    if (flagDead){
      posX = DEFAULT_X;
      posY = DEFAULT_Y;
      jugador.vidas = jugador.vidas - 1;
      if (jugador.vidas <= 0) {
        flagEntradaAdmin = true;
        strcpy(comandoAdmin,"DED");
        return;
      }
    }
    tablero.area[jugador.posX][jugador.posY] = VACIO;
    tablero.area[posX][posY] = PACMAN;
    jugador.posX = posX;
    jugador.posY = posY;
    if (tablero.dots == 0){
      printf("%s\n", "gano");
    }
  }
}

void armarRespuesta(char *respuesta) {
  bzero(buffer,1024);
  strcpy(respuesta,tablero.area[0]);
  char aux[16];///no sirve el cat?
  sprintf(aux, "%d", jugador.vidas);
  strcat(respuesta,aux);
  printf("%s\n", aux);
  sprintf(aux, "%d", jugador.puntaje);
  strcat(respuesta,aux);
}

void procesarEntrada(char *respuesta){
  int incrementoX = 0;
  int incrementoY = 0;
  if (strcmp(respuesta,END_COMMAND) == 0) {
    printf("%s\n", "FIN");
    return;
  }
  if (strcmp(respuesta,RIGHT_COMMAND) == 0) {
    incrementoY = 1;
  }
  if (strcmp(respuesta,LEFT_COMMAND) == 0) {
    incrementoY = -1;
  }
  if (strcmp(respuesta,DOWN_COMMAND) == 0) {
    incrementoX = 1;
  }
  if (strcmp(respuesta,UP_COMMAND) == 0) {
    incrementoX = -1;
  }
  checkMove(jugador.posX+incrementoX,jugador.posY+incrementoY);
  armarRespuesta(respuesta);
}

void startServer(){

  if ((servidor = socket(AF_INET, SOCK_STREAM, 0)) == 0){
      perror("socket failed");
      exit(EXIT_FAILURE);
  }
  if (setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
      perror("setsockopt");
      exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(servidor, (struct sockaddr *)&address, sizeof(address))<0){
      perror("bind failed");
      exit(EXIT_FAILURE);
  }
  if (listen(servidor, 3) < 0){
      perror("listen");
      exit(EXIT_FAILURE);
  }
  printf("%s\n", "stand-by");
  if ((cliente = accept(servidor, (struct sockaddr *)&address,(socklen_t*)&addrlen)) < 0 ){
      perror("accept");
      exit(EXIT_FAILURE);
  }
  pthread_t idConsola;
  int hilo = pthread_create(&idConsola,NULL, &hiloConsolaAdmin,NULL);
  printf("%s\n", "admin iniciado");
  //Detecta cliente y manda ok
  write(cliente , ok , strlen(ok));
  shutdown(cliente,2);

  bzero(buffer,1024);
  while(strcmp(buffer,"OUT") != 0){

    if (listen(servidor, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((cliente = accept(servidor, (struct sockaddr *)&address,(socklen_t*)&addrlen)) < 0 ){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    bzero(buffer,1024);
    int len = recv(cliente, buffer, sizeof(buffer), 0);

    if (len > 0) {
      procesarEntrada(buffer);
      write(cliente, buffer, 1024);
      shutdown(cliente,2);
    }
  }
  flagFin = true;
  pthread_join(idConsola,NULL);
}


int main(int argc, char const *argv[]){
    if (-1 != fillTablero()){
      startServer();
    } else{
      printf("%s\n", "FATAL: Archivo con tablero no encontrado, server no iniciado");
    }

    return 0;
}
