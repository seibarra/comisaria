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
void BuscarComisaria(tComisaria *comisarias, tComisaria comisaria[]);
void MostrarYEditarRegistro(tComisaria comisaria[]);
void VisualizarRegistro(tComisaria comisaria[]);

int main(void) {
	tComisaria comisarias[500];
	
	int i = 0;
	char opc = 'a';
	
	for (i = 0; i < 500; i++)
	{
		comisarias[i].id = 0;
	}

	CargarDatos(comisarias);
	

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
			BuscarComisaria(comisarias, comisarias);
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

	return 0;
}

void CargarDatos(tComisaria *comisarias) {
	int i = 0;
	FILE *comisBin;
	comisBin = fopen("C:\\Users\\PPC\\Documents\\GitHub\\comisaria\\TP PARCIAL\\comisaria.bin", "rb");
	if (comisBin != NULL) {
		for (i = 0; i < 500; i++){
		fread(comisarias, sizeof(tComisaria), 1, comisBin);
		comisarias++;
	    }
	}
	
	fclose(comisBin);
}

void GuardarDatos(tComisaria *comisarias) {
	int i = 0;
	FILE *comisBin;
	comisBin = fopen("C:\\Users\\PPC\\Documents\\GitHub\\comisaria\\TP PARCIAL\\comisaria.bin", "wb");
	for (i = 0; i < 500; i++){
		fwrite(comisarias, sizeof(tComisaria), 1, comisBin);
		comisarias++;
	}
	fseek(comisBin, 0, SEEK_SET);
	fclose(comisBin);
}


void ImportarDatos(tComisaria *comisarias) {
	int i = 0;
	char strLinea[178];


	FILE *comisFile;
	comisFile = fopen("C:\\Users\\PPC\\Documents\\GitHub\\comisaria\\TP PARCIAL\\comisaria.txt", "r");
	if (comisFile == NULL) {
		printf("\n\nNo se pudo abrir archivo\n");
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
	int i = 0;
	for (i = 0; i < 500; i++)
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

void BuscarComisaria(tComisaria *comisarias, tComisaria comisaria[]) {
	char textoBuscar[100];
	int opc = 1, contador = 0, i = 0;
	printf("\nBuscar por: \n");
	printf("1-Nombre\n");
	printf("2-Representante\n\n");

	scanf("%d", &opc);
	getchar();
	
	
	
	if (opc == 1 || opc == 2) {
		
		printf("Ingrese texto a buscar: ");
		gets(textoBuscar);
		system("cls");
		
		for (i = 0; i < 500; i++) {
			if (strstr(comisarias->nombre, textoBuscar) != NULL && opc == 1) {
				contador++;
				printf("\n%d", comisarias->id);
				printf("\n%s", comisarias->nombre);
				printf("\n%s", comisarias->representante);
				}
			else if (strstr(comisarias->representante, textoBuscar) != NULL  && opc == 2) {
				contador++;
				printf("\n%d\n", comisarias->id);
				printf("%s\n", comisarias->nombre);
				printf("%s\n", comisarias->representante);
			}
	
			if (contador == 20 || i >= 499) {
				if (contador == 20){
					printf("\n1-Continuar");
				}else if (contador > 0){
					printf("\n\n-No hay mas resultados-\n");
				}else if (contador == 0){
					printf("\n\n-No se ha encontrado ningun resultado-\n");
				}
				if (contador > 0){
					printf("\n2-Visualizar datos comisaria");
					printf("\n3-Editar datos comisaria");
				}
				printf("\n4-Volver al menu\n");

				scanf("%d", &opc);
				
				switch (opc){
					case 1:
						break;
					case 2: 
						VisualizarRegistro(comisaria);
						i = 500;
						break;
					case 3: 
						MostrarYEditarRegistro(comisaria);
						i = 500;
						break;
					case 4:
						i = 500;
						break;
					default:
						break;
					}
					contador = 0;
				}
			comisarias++;
		}
			
	}
	else {
		printf("\n\nEl numero introducido no es valido\n");
		system("pause");
	}
}

void MostrarYEditarRegistro(tComisaria comisaria[]) {
	int opc = 0, id = 0;
	char nombre[33], direccion[62], partido[21], representante[44];

	printf("\nIngrese el ID de la comisaria a editar: ");
	scanf("%d", &id);
	
	do{
		system("cls");
	
		printf("ID: %d", id);
		printf("\nNombre: %s", comisaria[id].nombre);
		printf("\nDireccion: %s", comisaria[id].direccion);
		printf("\nPartido: %s", comisaria[id].partido);
		printf("\nRepresentante: %s", comisaria[id].representante);
		
	
		printf("\n\nDesea cambiar:\n");
		printf("1-Nombre\n");
		printf("2-Direccion\n");
		printf("3-Partido\n");
		printf("4-Representante\n");
		printf("5-Salir\n");
		
		scanf("%d", &opc);
		getchar();
		switch (opc) {
		case 1:
			printf("\nEscriba el nuevo nombre para la comisaria (maximo 34 caracteres): ");
			gets(nombre);
			strcpy(comisaria[id].nombre, nombre);
			break;

		case 2:
			printf("\n\nEscriba la nueva direccion para la comisaria (maximo 62 caracteres): ");
			gets(direccion);
			strcpy(comisaria[id].direccion, direccion);
			break;

		case 3:
			printf("Escriba el nuevo partido para la comisaria (maximo 21 caracteres): ");
			gets(partido);
			strcpy(comisaria[id].partido, partido);
			break;

		case 4:
			printf("Escriba el nuevo representante para la comisaria (maximo 44 caracteres): ");
			gets(representante);
			strcpy(comisaria[id].representante, representante);
			break;
		default:
			break;
		}
	}while(opc != 5);

}

void VisualizarRegistro(tComisaria comisaria[]){
	int id = 0;
	printf("\nIngrese el ID de la comisaria a visualizar: ");
	scanf("%d", &id);
	
	system("cls");
	
		printf("ID: %d", id);
		printf("\nNombre: %s", comisaria[id].nombre);
		printf("\nDireccion: %s", comisaria[id].direccion);
		printf("\nPartido: %s", comisaria[id].partido);
		printf("\nRepresentante: %s\n\n", comisaria[id].representante);
		
		system("pause");
}
/*
ExportarPorPartido(tComisaria *comisarias){
	char partidoABuscar[21];
	int comisariasEncontradas = 0;
	printf("Ingrese partido a buscar: ");
		gets(partidoABuscar);
		system("cls");
		
		for (i = 0; i < 500; i++) {
			if (strcmp(comisarias->partido, partidoABuscar) == 0) {
				
		}
}*/


