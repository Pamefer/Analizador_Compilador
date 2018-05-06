#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//VARIABLES
char arrayseparadores1[] = {' ', '{', '(', ')', '}', ';', ':', '\n', '\t'};
char arrayseparadores12[] = {'=', '+', '-', '%', '*'}; //PARA IDENTIFICADORES
char arrayseparadores2[] = {'=', '+', '-', '%', '*'}; //PARA NUMEROS
char arrayseparadores3[] = {'<', '>'};

typedef char cadenaCaracteres [50]; //Definimos el tipo cadenaCaracteres
cadenaCaracteres arraypalareservadas[] = {"\nJARVIS", "JARVIS", "\nimp", "\nclase", "clase", "modo", "abierto", "ent", "cad", "imp", "bucle", "si", "no", "hacer", "mientras", "est", "car", "num"}; //Creamos un vector de cadenas

//FUNCIONES
char* buscarSeparador(char buscar, char array[]);
char* borrarCaracter(char* name);
char* buscarTDS(char* cadena1, cadenaCaracteres arreglo[]);
char* escribirarchivo(char* cadena1, char* cadena2);
char* escribirarchivocahr(char* cadena1, char* cadena2);

int main() {
    FILE* miarchivo = NULL;
    char* nombre_archivo = "C://Users//Pamela//Desktop//compilador.txt";
    char caracter;
    char cadena[100] = "";
    int estado = 0;
    int decimal = 0;
    char caracter_anterior;
    int pendiente = 0;
    //abrir archivo
    miarchivo = fopen(nombre_archivo, "r"); //r->leer; w->escribir;a->agregar al final;

    if (miarchivo == NULL) {//para saber si existe o no el archivo
        printf("\nError de apertura del archivo. \n\n");
    } else {
        //LEER CARACTER POR CARACTER
        while (feof(miarchivo) == 0) {
            //Extraer caracter de archivo
            if (pendiente == 0) {
                caracter = fgetc(miarchivo);
                printf("Extraido de archivo= %c \n", caracter);
                //Concatenar caracter con cadena
                strncat(cadena, &caracter, 1);
                // printf("Cadena actual= ");
                puts(cadena);
            }

            /*SWITCH */
            switch (estado) {
                case 0:
                    /*Saber si es un caracter*/
                    if (isalpha(caracter)) {
                        estado = 3;
                    }/*Saber si es un digito */
                    else if (isdigit(caracter)) {
                        estado = 1;
                    } else if (isspace(caracter)) {/* isspace comprende: 
                                                                            ' ' space (SPC)
                                                                            '\t' horizontal tab
                                                                            '\n' newline
                                                                            '\v' vertical tab
                                                                            '\f' feed
                                                                            '\r' carriage
                                                                              */
                        caracter_anterior = caracter;
                        estado = 4;
                        pendiente = 1;
                    } else if (buscarSeparador(caracter, arrayseparadores1) == 1) {
                        caracter_anterior = caracter;
                        estado = 4;
                        pendiente = 1;
                    } else if (buscarSeparador(caracter, arrayseparadores2) == 1) {
                        estado = 5;
                        pendiente = 1;
                        caracter_anterior = caracter;
                    } else if (buscarSeparador(caracter, arrayseparadores3) == 1) {
                        caracter_anterior = caracter;
                        pendiente = 1;
                        estado = 6;
                    } else if (caracter == '/') {
                        estado = 7;
                    }
                    break;
                case 1:
                    if (isdigit(caracter)) {
                        estado = 1;
                    }//FUNCION DE BUSCAR SEPARADOR
                    else if (buscarSeparador(caracter, arrayseparadores2) == 1 || buscarSeparador(caracter, arrayseparadores1) == 1) {
                        printf("SEPARADOR %c \n", caracter);

                        //BORRO SEPARADOR DE LA CADENA
                        borrarCaracter(cadena);
                        printf("NUMERO: %s\n", cadena);
                        if (decimal == 0) {
                            escribirarchivo(cadena, "NUMERO ENTERO");
                            decimal = 0;
                        } else {
                            escribirarchivo(cadena, "NUMERO DECIMAL");
                            decimal = 0;
                        }
                        if (buscarSeparador(caracter, arrayseparadores2) == 1) {
                            escribirarchivocahr(caracter, "OPERADOR (GRUPO 2)");
                        } else if (buscarSeparador(caracter, arrayseparadores3) == 1) {
                            escribirarchivocahr(caracter, "COMPARADOR (GRUPO 3)");
                        } else if (buscarSeparador(caracter, arrayseparadores1) == 1) {
                            escribirarchivocahr(caracter, "SEPARADOR (GRUPO 1)");
                        }
                        //resetear cadena!!
                        cadena[0] = 0;
                        estado = 0;
                    } else if (caracter == '.') {
                        decimal = 1;
                        estado = 1;
                    } else {
                        printf("ERROR");
                    }
                    break;
                case 3:
                    if (isalpha(caracter) || isdigit(caracter)) {
                        estado = 3;
                    }//FUNCION DE BUSCAR SEPARADOR
                    else if ((buscarSeparador(caracter, arrayseparadores1) == 1) || (buscarSeparador(caracter, arrayseparadores12) == 1) || (buscarSeparador(caracter, arrayseparadores3) == 1)) {
                        //printf("SEPARADOR");                        
                        //BORRO SEPARADOR DE LA CADENA
                        borrarCaracter(cadena);
                        if (buscarTDS(cadena, arraypalareservadas)) {
                            printf("PALABRA RESERVADA: %s\n", cadena);
                            //escribo archivo
                            escribirarchivo(cadena, "PALABRA RESERVADA");
                            //resetear cadena!!
                            cadena[0] = 0;
                        } else {
                            printf("IDENTIFICADOR: %s\n", cadena);
                            //escribo archivo
                            escribirarchivo(cadena, "IDENTIFICADOR");
                            //resetear cadena!!
                            cadena[0] = 0;
                        }
                        if (buscarSeparador(caracter, arrayseparadores2) == 1) {
                            escribirarchivocahr(caracter, "OPERADOR (GRUPO 2)");
                        } else if (buscarSeparador(caracter, arrayseparadores3) == 1) {
                            escribirarchivocahr(caracter, "COMPARADOR (GRUPO 3)");
                        } else if (buscarSeparador(caracter, arrayseparadores1) == 1) {
                            escribirarchivocahr(caracter, "SEPARADOR (GRUPO 1)");
                        }
                        estado = 0;
                    } else {
                        printf("ERROR");
                    }
                    break;
                case 4:
                    printf("SEPARADOR: %s\n", cadena);
                    escribirarchivocahr(caracter_anterior, "SEPARADOR GRUPO1");
                    //resetear cadena!!
                    cadena[0] = 0;
                    pendiente = 0;
                    estado = 0;
                    break;
                case 5:
                    printf("OPERADOR: %s\n", cadena);
                    escribirarchivocahr(caracter_anterior, "OPERADOR (GRUPO2)");
                    //resetear cadena!!
                    cadena[0] = 0;
                    pendiente = 0;
                    estado = 0;
                    break;
                case 6:
                    printf("COMPARADOR: %s\n", cadena);
                    escribirarchivocahr(caracter_anterior, "COMPARADOR GRUPO3");
                    //resetear cadena!!
                    cadena[0] = 0;
                    pendiente = 0;
                    estado = 0;
                    break;
                case 7:
                    if (caracter == '*') {
                        estado = 7;
                    } else if (isalpha(caracter) || isdigit(caracter)) {
                        estado = 7;
                    } else if (caracter == '/') {
                        printf("COMENTARIO: %s\n", cadena);
                        //escribo archivo
                        escribirarchivo(cadena, "COMENTARIO");
                        //resetear cadena!!
                        cadena[0] = 0;
                        estado = 0;
                    }
                    break;
                default:
                    printf("Caso por defecto???\n");
                    break;
            }
        }
    }

    fclose(miarchivo);
    return (EXIT_SUCCESS);
}

char* buscarSeparador(char buscar, char array[]) {
    int i = 0;
    int encontrado = 0; //1->encontrado
    for (i = 0; i<sizeof (array); i++) {
        if (buscar == array[i]) {
            encontrado = 1;
        }
    }
    return encontrado;
}

/*BORRA ULTIMO CARACTER*/
char* borrarCaracter(char* name) {
    int i = 0;
    while (name[i] != '\0') {
        i++;
    }
    name[i - 1] = '\0';
    return name;
}

char* buscarTDS(char* cadena1, cadenaCaracteres arregl[]) {
    int ret = 0;
    int i = 0;
    for (i = 0; i < 18; i++) {//EL 18 es cantidad en arraypalareservadas MODIFICAR   SEGUN CANTIDAD EN ese arreglo
        if ((strncmp(cadena1, arregl[i], strlen(cadena1)) == 0)&&(strncmp(cadena1, arregl[i], strlen(arregl[i])) == 0)) {
            ret = 1; //UNO SI LO ENCONTRO
        }
        //printf("%i \n", ret);
    }
    return (int) ret;
}

char* escribirarchivo(char* cadena1, char* cadena2) {
    FILE* archivo_resultado = NULL;
    char* nombre_archivo = "C://Users//Pamela//Desktop//resultado.txt";

    //abrir archivo
    archivo_resultado = fopen(nombre_archivo, "a+"); //r->leer; w->escribir;a->agregar al final;
    fprintf(archivo_resultado, "\n%s ----> %s", cadena1, cadena2);
    fputs("\r", archivo_resultado);
    fclose(archivo_resultado);
}

char* escribirarchivocahr(char* cadena1, char* cadena2) {
    FILE* archivo_resultado = NULL;
    char* nombre_archivo = "C://Users//Pamela//Desktop//resultado.txt";
    //abrir archivo
    archivo_resultado = fopen(nombre_archivo, "a+"); //r->leer; w->escribir;a->agregar al final;
    fprintf(archivo_resultado, "\n%c ----> %s", cadena1, cadena2);
    fputs("\r", archivo_resultado);
    fclose(archivo_resultado);
}