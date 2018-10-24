#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
	char nombre[33];
	char direccion[60];
	char partido[50];
	char representante[100];
} comisaria;


int main() {

	comisaria comisarias[500];

	int opc;

	printf("=============MENU=============");
	printf("A: Importar Datos");
	printf("B: Alta Comisaria");
	printf("C: Buscar Comisaria");
	printf("D: Exportar Comisaria por Partido");
	printf("E: Estadisticas De Comisarias Por Partido");
	printf("Z: Salir");

	scanf("%d", &opc);

	switch (opc) {
	case 'a':
		break;
	case 'b':
		break;
	case 'c':
		break;
	case 'd':
		break;
	case 'e':
		break;
	case 'z':
		break;
	default:
		break;
	}

	FILE *comisFile;
	comisFile = fopen("comisaria.txt","r");
	if (comisFile == NULL) {
		printf("No se pudo abrir archivo");
		exit(EXIT_FAILURE);
	}

}