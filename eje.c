//Andres Artavia-2017075875
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
//gcc –o eje eje.c

void millaskm(double array[]){
	int size = (int) sizeof(array);
	for (int i = 0; i < 10; i++){
		printf("millas: ");
		printf("%lf",array[i]);
		printf(", km: ");
		double a = array[i] * 1.60934;
		printf("%lf",a);
		printf("\n");
	}
}

void centtofar(){
	double Cin;
	printf("Digite C: ");
	scanf("%lf",&Cin);
	printf("F: ");
	printf("%lf",(Cin * 9/5) + 32);
	printf("\n");
}

int digitos(int n, int res){
	if(n <= 0){
		return res;
	} else {
		return digitos(n/10,res+1);
	}
}

int digitosPar(int n, int res){
	if(n <= 0){
		return res;
	} else {
		if ((n % 10)%2 == 0){
			return digitosPar((n / 10),res+1);
		} else{
			return digitosPar((n / 10),res);
		}
	}
}

int strcmpE(char *s, char *p){

	while((*s != '\0' || *p != '\0')){
		s++;
	  p++;
		if (*s == '\0' && *p == '\0'){
			return 0;
		}
		if (*s == '\0'){
			return -1;
		}
		if (*p == '\0'){
			return 1;
		}

	}
}

char* strcatE(char *dest, const char *src){
   char *rdest = dest;
    while (*dest){
      dest++;
	}
    while (*dest++ = *src++);
    return rdest;
}

int countWordAux(char *fileName, const char *word){
    char str[BUFFER_SIZE];
    char *pos;
    int index, count;
	FILE *file;
	file = fopen(fileName, "r");
    count = 0;
    while ((fgets(str, BUFFER_SIZE, file)) != NULL){
        index = 0;
        while ((pos = strstr(str + index, word)) != NULL){
            index = (pos - str) + 1;
            count++;
        }
    }
	printf("%d",count);
    return count;
}

void countWord(char *fileName){
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL) return;
	char c;
	char word[15];
	int i = 0;
	while((c = fgetc(fp)) != EOF){
		if(c == ' ' || c == '\n'){
			if(i > 3){
				printf("\n");
				word[i] = '\0';
				printf(word);

				i = 0;
				printf(" : ");
				countWordAux(fileName,word);
			}
				i = 0;
		}
		else{
			word[i] = c;
			i++;
		}
	}
	fclose(fp);
}

struct Node{
	int apariciones;
	char word[15];
	struct Node *next;
};

void main(){
	//printf("millas a km, en rango [1 - 10]. ");
	//printf("\n");
	double array[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
	//millaskm(array);
	//printf("C to F");
	//printf("\n");
	//centtofar();
	//printf("Digitos de 15400: ");
	//printf("%d",digitos(15400,0));
	//printf("\n");
	//printf("Digitos pares de 246124: ");
	//printf("%d",digitosPar(246124,0));
	//printf("\n");
	//printf("%d", strcmpE("as","ass"));
//printf("\n");
//char a[10]={"abc"}, b[10]={"def"};
	//printf(strcatE(a,b));
	//printf("\n");
	///char file[10] = {"texto.txt"};
	char file[10] = {"eje.txt"};
	printf("Aparicion de las palabras en un texto");
	printf("\n");
	countWord(file);
	printf("\n");
}
