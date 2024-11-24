
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


#define	V 21
#define	H 65
#define N 100

typedef struct{
	int x,y;
	int ModX,ModY;
	char imagen;
}snk;

typedef struct{
	int x,y;
}frt;

snk snake[N];
frt fruta;

void Inicio(int *tam, char campo[V][H]);
void Intro_campo(char campo[V][H]);
void Intro_datos(char campo[V][H], int tam);
void Draw(char campo[V][H]);
void loop(char campo[V][H],int tam);
void input(char campo[V][H],int *tam, int *muerto);
void Kpdate(char campo[V][H], int tam);
void Intro_datos2(char campo[V][H], int tam);
void gotoxy(int x, int y);

int main(){

	int tam;
	char campo[V][H];

	Inicio(&tam,campo);
	loop(campo,tam);

	system("pause");
	return 0;
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }



void Inicio(int *tam, char campo[V][H]){
	int i;
	snake[0].x = 32;
	snake[0].y = 10;

	*tam = 4;

	srand(time(NULL));
	fruta.x = rand() % (H - 1);
	fruta.y = rand() % (V - 1);

	while(fruta.x == 0){
		fruta.x = rand() % (H - 1);
	}

	while(fruta.y == 0){
		fruta.y = rand() % (V - 1);
	}

	for (i = 0; i < *tam; i++){
		snake[i].ModX = 1;
		snake[i].ModY = 0;
	}

	Intro_campo(campo);
	Intro_datos(campo,*tam);
}

void Intro_campo(char campo[V][H]){
	int i,j;
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			if(i==0 || i==V-1){
				campo [i][j] = '-';
			}
			else if (j == 0 || j== H-1){
				campo [i][j] = '|';
			}
			else{
				campo[i][j] = ' ';
			}
		}
	}
}

void Intro_datos(char campo[V][H], int tam){
	int i;

	for (i=1;i<tam;i++){
		snake[i].x = snake[i-1].x - 1;
		snake[i].y = snake[i-1].y;
		snake[i].imagen = 'X';
	}

	snake[0].imagen='O';

	for(i=0;i<tam;i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}

	campo[fruta.y][fruta.x] = 'ó';
}

void Draw(char campo[V][H]){
	int i,j;
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			printf("%c",campo[i][j]);
		}
		printf("\n");
	}
}

void loop(char campo[V][H],int tam){
	int muerto;
	muerto = 0;

	do{
		gotoxy(0,0);
		Draw(campo);
		input(campo,&tam,&muerto);
		Kpdate(campo,tam);
	}while(muerto == 0);
}

void input(char campo[V][H],int *tam, int *muerto){
	int i;
	char key;

	if(snake[0].x == 0 || snake[0].x == H-1 || snake[0].y == 0 || snake[0].y == V-1){
		*muerto = 1;
	}

	for (i = 1; i < *tam && *muerto==0;i++){
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y){
			*muerto = 1;
		}
	}

	if(snake[0].x==fruta.x && snake[0].y==fruta.y){

		*tam += 1;
		snake[*tam - 1].imagen = 'X';

		fruta.x = rand() % (H - 1);
		fruta.y = rand() % (V - 1);
		while(fruta.x == 0){
			fruta.x = rand() % (H - 1);
		}
		while(fruta.y == 0){
			fruta.y = rand() % (V - 1);
		}
	}
	if(*muerto == 0){
		if (kbhit()==1){
			key = getch();

			if(key=='s' && snake[0].ModY !=-1){
				snake[0].ModX = 0;
				snake[0].ModY = 1;
			}


			if(key=='w' && snake[0].ModY !=1){
				snake[0].ModX = 0;
				snake[0].ModY = -1;
			}


			if(key=='a' && snake[0].ModX !=1){
				snake[0].ModX = -1;
				snake[0].ModY = 0;
			}


			if(key=='d' && snake[0].ModX !=-1){
				snake[0].ModX = 1;
				snake[0].ModY = 0;
			}
		}
	}
}

void Kpdate(char campo[V][H], int tam){
	Intro_campo(campo);
	Intro_datos2(campo,tam);
}

void Intro_datos2(char campo[V][H], int tam){
	int i;
	
	for (i = tam-1;i>0;i--){
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].x += snake[0].ModX;
	snake[0].y += snake[0].ModY;

	for(i = 0;i < tam; i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}

	campo[fruta.y][fruta.x] = '%';

}