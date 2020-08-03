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

bool flagEntradaAdmin = false;
bool flagFin = false;
char comandoAdmin[1024];

struct struct_jugador{
  int posX;
  int posY;
  int puntaje;
  int vidas;
};

struct struct_tablero{
  int fantasmas;
  char area[ALTO][LARGO];
};


int fillTablero(){
  jugador.vidas = 3;
  jugador.puntaje = 0;
  jugador.posX = DEFAULT_X;
  jugador.posY = DEFAULT_Y;
  tablero.fantasmas =  4;
  int c;
  FILE *file;
  file = fopen("area", "r");
  if (file) {
    while ((c = getc(file)) != EOF)
        for (int i = 0; i < ALTO; i++){
          for (int j = 0; j < LARGO+1; j++){
            tablero.area[i][j] = c;
            //putchar(tablero.area[i][j]);
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
  while(!flagFin){
    printf( "Enter a value :");
    fgets(comandoAdmin,1024,stdin);
    flagEntradaAdmin = true;
    wait(2);
  }
}

void checkMove(int posX, int posY){
  if (tablero.area[posX][posY] != PARED){
    if (tablero.area[posX][posY] == PUNTO){
      jugador.puntaje = jugador.puntaje + 1;

    }
    tablero.area[jugador.posX][jugador.posY] = VACIO;
    tablero.area[posX][posY] = PACMAN;
    jugador.posX = posX;
    jugador.posY = posY;

  } else {
    printf("%s\n", "bloqued");
  }
}

void armarRespuesta(char *respuesta) {
  bzero(buffer,1024);
  strcpy(respuesta,tablero.area[0]);
}

void procesarEntrada(char *respuesta){
  printf("In: ");
  printf("%s\n", buffer);
  if (strcmp(respuesta,"OUT") == 0) {
    printf("%s\n", "FIN");
    return;
  }
  if (strcmp(respuesta,"RIGHT") == 0) {
    printf("%s\n", "RIGHT");
    checkMove(jugador.posX,jugador.posY+1);
  }
  if (strcmp(respuesta,"LEFT") == 0) {
    printf("%s\n", "LEFT");
    checkMove(jugador.posX,jugador.posY-1);
  }
  if (strcmp(respuesta,"DOWN") == 0) {
    printf("%s\n", "DOWN");
    checkMove(jugador.posX+1,jugador.posY);
  }
  if (strcmp(respuesta,"UPS") == 0) {
    printf("%s\n", "UPS");
    checkMove(jugador.posX-1,jugador.posY);
  }
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

      if (flagEntradaAdmin){
        write(cliente , comandoAdmin , strlen(comandoAdmin));
        printf("admin sent\n");
        flagEntradaAdmin = false;
      }
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
