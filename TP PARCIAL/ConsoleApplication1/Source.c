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


void QuitarEspacios(char *linea);

void ImportarDatos(tComisaria *comisarias);
void AltaComisaria(tComisaria *comisarias);
void BuscarComisaria(tComisaria *comisarias, tComisaria comisaria[]);
void MostrarYEditarRegistro(tComisaria comisaria[]);
void VisualizarRegistro(tComisaria comisaria[]);
void ExportarPorPartido(tComisaria *comisarias);
void MostrarTablaDePartidos(tComisaria *comisarias);
void CargarDatos(tComisaria *comisarias);
void GuardarDatos(tComisaria *comisarias);

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
		getchar();
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
			ExportarPorPartido(comisarias);
			break;
		case 'e':
			MostrarTablaDePartidos(comisarias);
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
	comisBin = fopen("comisaria.bin", "rb");
	if (comisBin != NULL) {
		for (i = 0; i < 500; i++){
		fread(comisarias, sizeof(tComisaria), 1, comisBin);
		comisarias++;
	    }
	    fclose(comisBin);
	}
	
	
}

void GuardarDatos(tComisaria *comisarias) {
	int i = 0;
	FILE *comisBin;
	comisBin = fopen("comisaria.bin", "wb");
	for (i = 0; i < 500; i++){
		fwrite(comisarias, sizeof(tComisaria), 1, comisBin);
		comisarias++;
	}
	fseek(comisBin, 0, SEEK_SET);
	fclose(comisBin);
}


void ImportarDatos(tComisaria *comisarias) {
	int i = 0, lineaTerminada = 0;
	char strLinea[178];


	FILE *comisFile;
	comisFile = fopen("comisaria.txt", "r");
	if (comisFile == NULL) {
		printf("\n\nNo se pudo abrir archivo\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	fgets(strLinea, 200, comisFile);

	while (!feof(comisFile) && i < 500) {

		sscanf(strLinea, "%d", &comisarias->id);
	
		strncpy(comisarias->nombre, strLinea + 8, 33);
		comisarias->nombre[33] = '\0';
		if(strstr(comisarias->nombre, "\n") != NULL) lineaTerminada = 1;
		QuitarEspacios(comisarias->nombre);
		
		if(lineaTerminada != 1){
		strncpy(comisarias->direccion, strLinea + 41, 62);
		comisarias->direccion[62] = '\0';
		if(strstr(comisarias->direccion, "\n") != NULL) lineaTerminada = 1;
		QuitarEspacios(comisarias->direccion);
		}
		
		if(lineaTerminada != 1){
		strncpy(comisarias->partido, strLinea + 103, 21);
		comisarias->partido[21] = '\0';
		if(strstr(comisarias->partido, "\n") != NULL) lineaTerminada = 1;
		QuitarEspacios(comisarias->partido);
		}
		
		if(lineaTerminada != 1){
		strncpy(comisarias->representante, strLinea + 124, 168);
		comisarias->representante[44] = '\0';
		if(strstr(comisarias->representante, "\n") != NULL) lineaTerminada = 1;
		QuitarEspacios(comisarias->representante);
		}
		
		lineaTerminada = 0;
		i++;
		comisarias++;
		fgets(strLinea, 200, comisFile);
	}
	
	fclose(comisFile);
	printf("\nLos datos han sido importados.\n");
	system("pause");
}

void QuitarEspacios(char *linea){
	int a = 0, b = 0, i = 0;
	int posEspacioEncontrado; 
	
	while (linea[a] != '\0'){
			if(linea[a] != ' '){
				posEspacioEncontrado = -1; 
			}else{
				posEspacioEncontrado = a;
				while(linea[a] == ' '){
					a++;
				}
				if(linea[a] != '\0') 
				posEspacioEncontrado = -1;
				else break;
			}
			a++;
	}
	if (posEspacioEncontrado != -1){
		for (a = b = posEspacioEncontrado; linea[a] != '\0'; a++) 
   			linea[b] = '\0';
	}
	for (a = b = 0; linea[a] != '\0'; a++){
      	if (linea[a] == '\n') linea[a] = '\0';
	}
}

void AltaComisaria(tComisaria *comisarias) {
	int aux = 0;
	int i = 0;
	for (i = 0; i < 500; i++)
	{
		if (comisarias->id != 0) {
			comisarias++;
		}
	}
	comisarias->id = aux;
	printf("\nNombre de la comisaria a agregar: ");
	gets(comisarias->nombre);
	//getchar();
	printf("\nDireccion de la comisaria: ");
	gets(comisarias->direccion);
	//getchar();
	printf("\nPartido al que corresponde: ");
	gets(comisarias->partido);
	//getchar();
	printf("\nRepresentante de la comisaria: ");
	gets(comisarias->representante);

	printf("\n\n%d\n", comisarias->id);
	printf("%s\n", comisarias->nombre);
	printf("%s\n", comisarias->direccion);
	printf("%s\n", comisarias->partido);
	printf("%s\n", comisarias->representante);
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
	id--;
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
		id--;
		printf("\nNombre: %s", comisaria[id].nombre);
		printf("\nDireccion: %s", comisaria[id].direccion);
		printf("\nPartido: %s", comisaria[id].partido);
		printf("\nRepresentante: %s\n\n", comisaria[id].representante);
		
		system("pause");
}

void ExportarPorPartido(tComisaria *comisarias){
	char partidoABuscar[22];
	int i = 0;
	int comisariasEncontradas = 0;
	
	FILE *comisariasDelPartido;
	comisariasDelPartido = fopen("Comisarias por partido.txt", "w");
	
	printf("Ingrese partido a buscar: ");
	getchar();
	gets(partidoABuscar);
	system("cls");
		
	for (i = 0; i < 500; i++) {
		if (strstr(comisarias->partido, partidoABuscar) != NULL) {
			fprintf(comisariasDelPartido, "%d %s\t %s\t %s\t %s\n\n", comisarias->id, comisarias->nombre, comisarias->direccion, comisarias->partido, comisarias->representante);
			printf("%d %s\t %s\t %s\t %s\n\n", comisarias->id, comisarias->nombre, comisarias->direccion, comisarias->partido, comisarias->representante);
			comisariasEncontradas++;		
		}
		comisarias++;
	}
	fclose(comisariasDelPartido);
	if (comisariasEncontradas == 0) printf("\nNo se ha encontrado comisarias de ese partido\n");
	else printf("\n\nEl total de comisarias encontradas con %s es: %d\n", partidoABuscar, comisariasEncontradas);
	system("pause");
	
}

void MostrarTablaDePartidos(tComisaria *comisarias){
	int i = 0, a = 0, b = 0,c = 0;
	int partidoEncontrado = 0; //1-verdadero 0-falso
	char partidos[500][22];
	int cantidadPartidos[500];
	
	for (i = 0; i < 500; i++)
	{
		cantidadPartidos[i] = 0;
		strcpy(partidos[i], "");
	}
	
	FILE *comisFile;
	comisFile = fopen("comisaria.txt", "r");
	if(comisFile == NULL){
		printf("\n\nNo se pudo abrir el archivo");
		system("pause");
		exit(EXIT_FAILURE);
	}
	strcmp(partidos[0], partidos[1]);
	for(a = 0; a < 500; a++){
		for(b = 0; b < 500; b++){
			if(strcmp(comisarias->partido, partidos[b]) == 0){
				partidoEncontrado = 1;
				cantidadPartidos[b]++;
				break;
			}
		}
		if (partidoEncontrado == 0){
			for(c = 0; c < 500; c++){
				if(partidos[c][0] == '\0'){
					strcpy(partidos[c], comisarias->partido);
					cantidadPartidos[c]++;
					break;
				}
			}
		}
		partidoEncontrado = 0;
		comisarias++;
	}
	
	printf("Cantidad\n\nPartido\n");
	
	for(i = 0; i < 500; i++){
		if(partidos[i][0] != '\0'){
			printf("%d\t%s\n", cantidadPartidos[i], partidos[i]);
		}
	}
	system("pause");
}
