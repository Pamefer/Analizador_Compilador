package analizador;
//se importa las librerias necesarias

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.*;

/**
 *
 * @author Galo
 */
public class Analizador {

    public static void main(String[] args) {
        
        File archivo = null;
        FileReader fr = null;
        BufferedReader br = null;

        try {

            archivo = new File("/Users/Galo/Documents/Analizador/src/analizador/archivo.txt");
            //en archivo.txt se encuentra el patrón  

            fr = new FileReader(archivo);
            br = new BufferedReader(fr);

            // Lectura del fichero
            String linea;
            while ((linea = br.readLine()) != null) {

                //la linea leida la guardamos en una variable
                String lenguaje = linea;
                Scanner tex = new Scanner(System.in);

                boolean bucle = true;

                System.out.println("Ingrese la expresión: ");
                while (bucle == true) {

                    String texto = tex.next(); // ingresamos lo que queremos analizar

                    //estas librerias nos aydan a buscar conicidencias con el lenguaje
                    Pattern pattern = Pattern.compile(lenguaje); //Conicdencia entre el lenguaje del archivo
                    Matcher matcher = pattern.matcher(texto);        //y la palabra ingresada
                    String[ ] a = new String[19];
                    
                    while (matcher.find()) {
                        for (int y=1;y<=18;y++){
                            a[y]="dato"+y;
                            a[y] = matcher.group(y);
                        }
                      
                        if (a[1] != null || a[2] != null || a[3] != null || a[4] != null || a[5] != null || a[6] != null || a[7] != null || a[8] != null || a[9] != null) {
                            System.out.print("  Palabra reservada\n");
                        }
                        if (a[10] != null) {
                            System.out.print(" Cadena\n");
                        }
                        if (a[11] != null || a[14] != null) {
                            System.out.print(" Número\n");
                        }
                        if (a[12] != null) {
                            System.out.print(" Inicio de Cadena\n");
                        }
                        if (a[13] != null) {
                            System.out.print(" Incio de Números\n");
                        }
                        if (a[15] != null) {
                            System.out.print(" Operador aritmético\n");
                        }
                        if (a[16] != null) {
                            System.out.print(" Parentesis\n");
                        }
                        if (a[17] != null) {
                            System.out.print("Llave\n");
                        }
                        if (a[18] != null) {
                            System.out.print("Fin de Línea\n");
                        }

                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {

        }

    }
}
