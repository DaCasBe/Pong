#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define V 21
#define H 75

void borde(char campo[V][H]);
void jugador(char campo[V][H],int inicioJugador,int finalJugador);
void IA(char campo[V][H],int inicioIA,int finalIA);
void pelota(char campo[V][H],int pelX,int pelY);
void leerCampo(char campo[V][H]);
void inicio(char campo[V][H],int pelX,int pelY,int inicioJugador,int finalJugador,int inicioIA,int finalIA);
void bucledeljuego(char campo[V][H],int pelX,int pelY,int inicioJugador,int finalJugador,int inicioIA,int finalIA,int modX,int modY,int modIA);
void dibujarCampo(char campo[V][H]);
void direcciones(char campo[V][H],int *pelX,int *pelY,int *inicioJugador,int *finalJugador,int *inicioIA,int *finalIA,int *modX,int *modY,int *modIA,int *gol);
void actualizar(char campo[V][H],int pelX,int pelY,int inicioJugador,int finalJugador,int inicioIA,int finalIA);

int main(){
	int pelX=37;
	int pelY=10;
	int inicioJugador=8;
	int finalJugador=12;
	int inicioIA=2;
	int finalIA=18;
	char campo[V][H];
	int modX=-1;
	int modY=-1;
	int modIA=-1;
	
	inicio(campo,pelX,pelY,inicioJugador,finalJugador,inicioIA,finalIA);
	bucledeljuego(campo,pelX,pelY,inicioJugador,finalJugador,inicioIA,finalIA,modX,modY,modIA);
	
	system("pause");
	return 0;
}

void inicio(char campo[V][H],int pelX,int pelY,int inicioJugador,int finalJugador,int inicioIA,int finalIA){
	borde(campo);
	jugador(campo,inicioJugador,finalJugador);
	IA(campo,inicioIA,finalIA);
	pelota(campo,pelX,pelY);
}

void borde(char campo[V][H]){
	int i;
	int j;
	
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			if(i==0 || i==V-1){
				campo[i][j]='-';
			}
			else if(j==0 || j==H-1){
				campo[i][j]='|';
			}
			else{
				campo[i][j]=' ';
			}
		}
	}
}

void jugador(char campo[V][H],int inicioJugador,int finalJugador){
	int i;
	int j;
	
	for(i=inicioJugador;i<=finalJugador;i++){
		for(j=2;j<=3;j++){
			campo[i][j]='X';
		}
	}
}

void IA(char campo[V][H],int inicioIA,int finalIA){
	int i;
	int j;
	
	for(i=inicioIA;i<=finalIA;i++){
		for(j=H-4;j<=H-3;j++){
			campo[i][j]='X';
		}
	}
}

void pelota(char campo[V][H],int pelX,int pelY){
	campo[pelY][pelX]='O';
}

void leerCampo(char campo[V][H]){
	int i;
	int j;
	
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			printf("%c",campo[i][j]);
		}
		printf("\n");
	}
}

void bucledeljuego(char campo[V][H],int pelX,int pelY,int inicioJugador,int finalJugador,int inicioIA,int finalIA,int modX,int modY,int modIA){
	int gol=0;
	
	do{
		dibujarCampo(campo);
		direcciones(campo,&pelX,&pelY,&inicioJugador,&finalJugador,&inicioIA,&finalIA,&modX,&modY,&modIA,&gol);
		actualizar(campo,pelX,pelY,inicioJugador,finalJugador,inicioIA,finalIA);
		Sleep(0.0001);
	}while(gol==0);
}

void dibujarCampo(char campo[V][H]){
	system("cls");
	leerCampo(campo);
}

void direcciones(char campo[V][H],int *pelX,int *pelY,int *inicioJugador,int *finalJugador,int *inicioIA,int *finalIA,int *modX,int *modY,int *modIA,int *gol){
	int i;
	char tecla;
	
	if(*pelY==1 || *pelY==V-2){
		*modY *= -1;
	}
	if(*pelX==1 || *pelX==H-2){
		*gol=1;
	}
	if(*pelX==4){
		for(i=(*inicioJugador);i<=(*finalJugador);i++){
			if(i==(*pelY)){
				*modX *= -1;
			}
		}
	}
	if(*pelX==H-5){
		for(i=(*inicioIA);i<=(*finalIA);i++){
			if(i==(*pelY)){
				*modX *= -1;
			}
		}
	}
	if(*inicioIA==1 || *finalIA==V-1){
		*modIA *= -1;
	}
	if(*gol==0){
		*pelX += (*modX);
		*pelY += (*modY);
		*inicioIA += (*modIA);
		*finalIA += (*modIA);
		if(kbhit()==1){
			tecla=getch();
			if(tecla=='f'){
				if(*inicioJugador!=1){
					*inicioJugador -= 1;
					*finalJugador -= 1;
				}
			}
			if(tecla=='j'){
				if(*finalJugador!=V-2){
					*inicioJugador += 1;
					*finalJugador += 1;
				}
			}
		}
	}
}

void actualizar(char campo[V][H],int pelX,int pelY,int inicioJugador,int finalJugador,int inicioIA,int finalIA){
	borde(campo);
	jugador(campo,inicioJugador,finalJugador);
	IA(campo,inicioIA,finalIA);
	pelota(campo,pelX,pelY);
}
