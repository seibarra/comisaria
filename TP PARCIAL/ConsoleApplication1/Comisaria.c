#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int id;
	char nombre[34];
	char direccion[63];
	char partido[22];
	char representante[45];
} comisaria;

void AltaComisaria(comisaria *comisarias);
void ImportarDatos(comisaria *comisarias);

int main() {

	comisaria comisarias[500];

	char opc = 'a';

	for (int i = 0; i < 500; i++)
	{
		comisarias[i].id = 0;
	}

	while (opc != 'z') {
		system("cls");
		printf("=============MENU=============\n");
		printf("A: Importar Datos\n");
		printf("B: Alta Comisaria\n");
		printf("C: Buscar Comisaria\n");
		printf("D: Exportar Comisaria por Partido\n");
		printf("E: Estadisticas De Comisarias Por Partido\n");
		printf("Z: Salir\n");

		scanf("%c", &opc);

		switch (opc) {
		case 'a':
			ImportarDatos(comisarias);
			break;
		case 'b':
			AltaComisaria(comisarias);
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
	}

	/*
	printf("\n%d\n", comisarias[5].id);
	printf("%s\n", comisarias[5].nombre);
	printf("%s\n", comisarias[5].direccion);
	printf("%s\n", comisarias[5].partido);
	printf("%s\n", comisarias[5].representante);
	*/

	system("pause");
	return 0;
}


void ImportarDatos(comisaria *comisarias) {
	int i = 0;
	char strLinea[178];


	FILE *comisFile;
	comisFile = fopen("comisaria.txt", "r");
	if (comisFile == NULL) {
		printf("No se pudo abrir archivo\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	fgets(strLinea, 168, comisFile);

	while (!feof(comisFile) && i < 500) {

		sscanf(strLinea, "%d", &comisarias->id);
		strncpy(comisarias->nombre, strLinea + 8, 33);
		comisarias->nombre[33] = '\0';
		strncpy(comisarias->direccion, strLinea + 41, 62);
		comisarias->direccion[62] = '\0';
		strncpy(comisarias->partido, strLinea + 103, 21);
		comisarias->partido[21] = '\0';
		strncpy(comisarias->representante, strLinea + 124, 168);
		comisarias->representante[44] = '\0';
		i++;
		comisarias++;
		fgets(strLinea, 500, comisFile);
	}

	fclose(comisFile);
	printf("\nLos datos han sido importados.\n");
	system("pause");
}

void AltaComisaria(comisaria *comisarias) {
	int aux = 0;
	for (int i = 0; i < 500; i++)
	{
		if (comisarias[i].id != 0) {
			aux = i + 1;
		}
	}
	comisarias[aux].id = aux;
	printf("\nNombre de la comisaria a agregar: ");
	scanf("%s", &comisarias[aux].nombre);
	printf("\nDireccion de la comisaria: ");
	scanf("%s", &comisarias[aux].direccion);
	printf("\nPartido al que corresponde: ");
	scanf("%s", &comisarias[aux].partido);
	printf("\nRepresentante de la comisaria: ");
	scanf("%s", &comisarias[aux].representante);

	printf("\n\n%d\n", comisarias[aux].id);
	printf("%s\n", comisarias[aux].nombre);
	printf("%s\n", comisarias[aux].direccion);
	printf("%s\n", comisarias[aux].partido);
	printf("%s\n", comisarias[aux].representante);
	system("pause");
}