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
} tComisaria;

void CargarDatos(tComisaria *comisarias);
void GuardarDatos(tComisaria *comisarias);

void ImportarDatos(tComisaria *comisarias);
void AltaComisaria(tComisaria *comisarias);
void BuscarComisaria(tComisaria *comisarias);

int main() {

	tComisaria comisarias[500];

	char opc = 'a';

	CargarDatos(comisarias);

	for (int i = 0; i < 500; i++)
	{
		comisarias[i].id = 0;
	}

	while (opc != 'z') {
		system("cls");
		printf("=============MENU=============\n");
		printf("a: Importar Datos\n");
		printf("b: Alta Comisaria\n");
		printf("c: Buscar Comisaria\n");
		printf("d: Exportar Comisaria por Partido\n");
		printf("e: Estadisticas De Comisarias Por Partido\n");
		printf("z: Guardar y salir\n");

		scanf("%c", &opc);

		switch (opc) {
		case 'a':
			ImportarDatos(comisarias);
			break;
		case 'b':
			AltaComisaria(comisarias);
			break;
		case 'c':
			BuscarComisaria(comisarias);
			break;
		case 'd':
			break;
		case 'e':
			break;
		case 'z':
			GuardarDatos(comisarias);
			break;
		default:
			break;
		}
	}

	/*
	printf("\n%d\n", comisarias[5].id);
	printf("%s\n", comisarias[5].nombre);
	printf("%s\n", comisarias[5].representante);
	*/

	system("pause");
	return 0;
}

void CargarDatos(tComisaria *comisarias) {
	FILE *comisBin;
	comisBin = fopen("comisarias.bin", "rb");
	fread(comisarias, sizeof(tComisaria), 1, comisBin);
	fclose(comisBin);
}

void GuardarDatos(tComisaria *comisarias) {
	FILE *comisBin;
	comisBin = fopen("comisarias.bin", "wb");
	fwrite(comisarias, sizeof(tComisaria), 1, comisBin);
	fseek(comisBin, 0, SEEK_SET);
	fclose(comisBin);
}


void ImportarDatos(tComisaria *comisarias) {
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

void AltaComisaria(tComisaria *comisarias) {
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

void BuscarComisaria(tComisaria *comisarias) {
	char textoBuscar[100];
	int opc = 1, contador = 0;
	char opcionBuscar;
	printf("\nBuscar por: \n");
	printf("1-Nombre\n");
	printf("2-Representante\n\n");

	scanf("%d", &opc);

	printf("Ingrese texto a buscar en mayusculas: ");

	scanf("%s", textoBuscar);
	
	if (opc == 1) {

		for (int i = 0; i < 500; i++) {
			if (strstr(comisarias->nombre, textoBuscar) != NULL) {
				contador++;
				printf("\n%d\n", comisarias->id);
				printf("%s\n", comisarias->nombre);
				printf("%s\n", comisarias->representante);
				if (contador == 20) {
					contador = 0;
					printf("\nc-�Continuar?");
					printf("\nv-Visualizar");
					printf("\ne-Editar");

					scanf("%c", &opcionBuscar);
						switch (opcionBuscar){
						case 'v': {
							system("pause");
						}
						case 'e': {
							system("pause");
						}
						default:
							break;
						}
					}
				}
			comisarias++;
			}
			
		}
	else {
		for (int i = 0; i < 500; i++)
		{
			if (strstr(comisarias->representante, textoBuscar) != NULL) {
				printf("\n%d\n", comisarias->id);
				printf("%s\n", comisarias->nombre);
				printf("%s\n", comisarias->representante);
			}
			comisarias++;
		}
	}
	
	

	system("pause");
}

void EditarRegistro(tComisaria comisarias[]) {
		int opc = 0, id = 0;
		char nombre[34], direccion[63], partido[22], representante[45];

		printf("Ingrese el ID de la comisaria a editar");
		scanf("%d", &id);

		printf("Desea cambiar:\n");
		printf("1: Nombre\n");
		printf("2:Direccion\n");
		printf("3:Partido\n");
		printf("4:Representante\n");
		printf(" 5: Salir\n");
		scanf("%d", &opc);

		switch (opc) {
		case 1:
			printf("Escriba el nuevo nombre para la comisaria (maximo 34 caracteres)");
			scanf("%s", &nombre);
			strcpy(nombre, comisarias[id].nombre);
			break;

		case 2:
			printf("Escriba el nuevo direccion para la comisaria (maximo 34 caracteres)");
			scanf("%s", &direccion);
			strcpy(direccion, comisarias[id].direccion);
			break;

		case 3:
			printf("Escriba el nuevo partido para la comisaria (maximo 34 caracteres)");
			scanf("%s", &partido);
			strcpy(partido, comisarias[id].partido);
			break;

		case 4:
			printf("Escriba el nuevo representante para la comisaria (maximo 34 caracteres)");
			scanf("%s", &representante);
			strcpy(representante, comisarias[id].representante);
			break;

		default:
			break;
		}


	}