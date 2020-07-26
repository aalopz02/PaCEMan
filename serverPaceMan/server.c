#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define LARGO 21
#define ALTO 27

int servidor, cliente;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024];
char *respuesta = "ok";
char *respuesta2 = "not ok";
struct struct_tablero tablero;

struct struct_tablero{
  int puntaje;
  int vidas;
  char area[ALTO][LARGO];
};


void fillTablero(){
  tablero.vidas = 3;
  tablero.puntaje = 0;
  int c;
  FILE *file;
  file = fopen("area", "r");
  if (file) {
    while ((c = getc(file)) != EOF)
        for (int i = 0; i < ALTO; i++){
          for (int j = 0; j < LARGO+1; j++){
            tablero.area[i][j] = c;
            putchar(tablero.area[i][j]);
            c = getc(file);
          }
        }
    fclose(file);
  } else {
    printf("%s\n", "error opening txt");
  }

}

void conect(){
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
  address.sin_port = htons( PORT );

  if (bind(servidor, (struct sockaddr *)&address, sizeof(address))<0){
      perror("bind failed");
      exit(EXIT_FAILURE);
  }
  if (listen(servidor, 3) < 0){
      perror("listen");
      exit(EXIT_FAILURE);
  }
  if ((cliente = accept(servidor, (struct sockaddr *)&address,(socklen_t*)&addrlen)) < 0 ){
      perror("accept");
      exit(EXIT_FAILURE);
  }
  bzero(buffer,1024);
  while(strcmp(buffer,"out") != 0){

    bzero(buffer,1024);
    int len = recv(cliente, buffer, sizeof(buffer), 0);

    if (len > 0) {
      printf("%s\n", buffer);
      if (strcmp(buffer,"perro") == 0){
        write(cliente , respuesta , strlen(respuesta));
        printf("Message sent\n");
      } else{
        write(cliente , respuesta2 , strlen(respuesta2));
        printf("Message sent\n");

      }
    }
    shutdown(cliente,2);
    if (listen(servidor, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((cliente = accept(servidor, (struct sockaddr *)&address,(socklen_t*)&addrlen)) < 0 ){
        perror("accept");
        exit(EXIT_FAILURE);
    }

  }
}


int main(int argc, char const *argv[]){

    fillTablero();

    return 0;
}
