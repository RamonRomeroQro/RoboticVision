//----------------------------------------------------------------------------//
// Template for reading portable gray map files (*.pgm)                       //
//                                                                            //
//                                                RickWare                    //
//                                                August 22, 2011             //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//         Prototype declarations                                             //
//----------------------------------------------------------------------------//

void heading (void);      /* Displays program heading */
void openfiles (void);    /* Opens input and output files in binary */
void userdefined (void);  /* Here, the user will implement his routine */
void readhdr (void);      /* Read header from input image file */
void addhdr (void);       /* Add header to output image file */
void closefiles (void);   /* Close all files used in program */

//----------------------------------------------------------------------------//
//         Include declarations                                               //
//----------------------------------------------------------------------------//

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>

//----------------------------------------------------------------------------//
//         Variable declarations                                              //
//----------------------------------------------------------------------------//

int    MRows, NCols;                 /* Number of Rows and columns in image */
FILE   *infptr, *outfptr, *outfptrh; /* Input and output file pointers */
char   infile[40];                   /* Name of input file */
char   outfile[40];                  /* Name of output file */
int    MaxGray;                      /* Nivel maximo de gris */
//----------------------------------------------------------------------------//
//         Main program                                                       //
//----------------------------------------------------------------------------//

main ()
{
     // Display heading
     heading ();
     // Open Input and Output Image Files
     openfiles ();
     // Read header from image file
     readhdr();
     // Add header to output file
     addhdr();
     // Execute userdefined procedure
     userdefined ();
     // Close all image files
     closefiles ();
     
     printf("\n Bye! Bye!\n");
     system("PAUSE");
     return(1);
} // end main ();

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void heading ()
{
     printf("Programa que lee imagenes en formato *.pgm\n");
     printf("El programa obtiene el negativo de la imagen de entrada\n");
     printf("Autor: Jorge Quintero\n");
     printf("Fecha: Agosto 23, 2011\n");
} // end heading ()

//----------------------------------------------------------------------------//
//         Openfiles                                                          //
//----------------------------------------------------------------------------//

void openfiles ()
{
     //Este procedimiento abre y crea archivos de imagenes en formato *.pgm
     
     //Abrir el archivo de entrada
     printf("\n Da el nombre completo de la imagen de entrada (ej: lena.pgm) ");
     scanf("%s",&infile);
     //Checar si el archivo de entrada existe y abrirlo
     if ((infptr = fopen(infile,"rb")) == NULL )
     {
       printf("El archivo con nombre %s no existe!, Adios!\n", infile);
       system("PAUSE");
       exit(1);
     }
      //Crear el archivo de salida
     printf("\n Da el nombre completo de la imagen de salida (ej: lenaout.pgm) ");
     scanf("%s",&outfile);
     //Crear el archivo de salida y verificar si fue creado exitosamente
             if ((outfptr = fopen(outfile,"wb")) == NULL )
             {
               printf("El archivo con nombre %s no pudo ser creado!, Adios!\n", outfile);
               system("PAUSE");
               exit(1);
             }
     
    
}  //end openfiles ()

//----------------------------------------------------------------------------//
//         Read Header                                                        //
//----------------------------------------------------------------------------//

void readhdr ()
{
     int i=0;
     char c;
     char buffer[128];
     
     //Leer la informacion de la imagen
     //Metodo 1 de lectura de archivos binarios, un caracter a la vez
     //Leer el "P5" de la imagen de entrada
     do
     {
     c = fgetc (infptr); /* Lee un caracter y avanza el puntero */
     buffer[i++] = c;
     } while (c != '\n');
     
     //Validar si el archivo de entrada esta en formato P5
     if (buffer[1] = '5')
     printf ("El archivo de entrada parece estar en formato P5, OK!\n\n");
     else
     {
         printf ("El archivo de entrada NO esta en formato P5, Adios!\n\n");
         system("PAUSE");
         exit(1);
     }
     
     //Leer el resto del encabezado
     //Metodo 2 de lectura de archivos, leyendo valores completos
     fscanf(infptr,"%d %d\n%d\n",&MRows,&NCols,&MaxGray);
     //Desplegar en pantalla el header
     //printf("%s",buffer);
     printf("%d x %d\n",MRows,NCols);
     printf("%d\n\n",MaxGray);
     
         
         
     
}  // end readhdr ()

//----------------------------------------------------------------------------//
//         Add Header                                                         //
//----------------------------------------------------------------------------//

void addhdr ()
{
     fprintf(outfptr,"P5\n%d %d\n%d\n",MRows,NCols,MaxGray);
} //addhdr ()

//----------------------------------------------------------------------------//
//         User defined section                                               //
//----------------------------------------------------------------------------//

void userdefined ()
{
     unsigned char pixel;
     //Obtener el negativo de la imagen de entrada
     pixel = fgetc(infptr); /* Leyendo primer pixel de la imagen de entrada */
     do
     {
           fputc ((255 - pixel), outfptr); /* Generar el negativo de cada píxel */
           pixel = fgetc(infptr);
     } while (not feof(infptr));
     
}  // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void closefiles ()
{
     //Cerrar el archivo de entrada y de salida
     fclose(infptr);
     fclose(outfptr);
}  // end closefiles ()
