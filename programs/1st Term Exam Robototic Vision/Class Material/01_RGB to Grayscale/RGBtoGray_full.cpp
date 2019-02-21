//                        ITESM-CQ                      
//                     Prog Dig Imag               
// -----------------------------------------------------------------------------
//                     PPM --- PGM                    
//    Alumnos:
//      Edgar Olvera Gonzales 
//      Edmond Daniel Chavez Chavez  
//    Matriculas:
//      A00881964
//      A01200517    
//    Fecha: 07 de Febrero del 2008.                        
//+++++++++++++++++++++++++++++++<M D I P>++++++++++++++++++++++++++++++++++++++
//
//             >>>MASK DIGITAL IMAGE PROCESSING Program<<<
//
//        This program reads an input color image in *.ppm format
//        and converts it into a grayscale image in *.pgm format
//        using the following equation:
//            Gray(x,y) = 1/3 (Red(x,y) + Green(x,y) + Blue(x,y)
//        for every every pixel located at (x,y) in the image
//
//------------------------------------------------------------------------------
//                  Version updated: January 31, 2008
//                               RickWare
//------------------------------------------------------------------------------

//==============================================================================
//------------------------P R O G R A M-----------------------------------------
//==============================================================================
//
//  main();
//     heading();               display program heading
//     openfiles();             opens input & output image files
//     readhdr();               reads input image file header
//     closefiles();            closes input and processed output image files
//------------------------------------------------------------------------------
void     heading(void);
void     openfiles(void);
void     readhdr(void);
void     writehdr(void);
void     readbody(void);
void     closefiles();
void     display(void);
//------------------------------------------------------------------------------
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
//------------------------------------------------------------------------------
int      MRows, NCols,i,temp,cont;         //indices for rows and cols
FILE     *infptr, *outfptr;                //input/output file pointers
char     infile[40];
char     static  outfile[40];              //names of input/output image files
long int comienzo,final;
unsigned int inread[4],suma[1];
fpos_t  principio;


//------------------------------------------------------------------------------
//-----------------------------MAIN---------------------------------------------
//------------------------------------------------------------------------------
main()
{
//--------------(  Display Heading with information )-----------------------
    heading();
//---------------( Open Input & Output Image Files )------------------------
    openfiles();
//---------------(       Write Header to file      )------------------------
    writehdr();
//---------------(        Read Body from file      )------------------------
    readbody();
//------------------(Close Any Open Image Files)----------------------------
    closefiles();
//--------------------------------------------------------------------------
    printf("\n Bye! Bye!\n");
    system("PAUSE");
    return (1);
}
//end main()

//------------------------------------------------------------------------------
//----------------------------HEADING-------------------------------------------
//------------------------------------------------------------------------------
void heading()
{ int      i;
  for (i=0;i<16;i++) printf("                                     +\n");
  printf("                       Digital Image Processing Program\n");
  printf("                         Updated: January 31, 2008\n");
  printf("                                 RickWare\n");
  for (i=0;i<4;i++)  printf("                                     +\n");
}//end heading()

//------------------------------------------------------------------------------
//--------------------------OPENFILES-------------------------------------------
//------------------------------------------------------------------------------
void openfiles(void)
{
  printf("\n                 OPEN an image file\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(" Enter name of *.ppm INPUT image file: ? ");
  scanf("%s",&infile);
  printf(" Enter name of *.pgm OUTPUT image file: ? ");
  scanf("%s",&outfile);
    
  if ((infptr = fopen(infile, "rb")) == NULL)
  { printf(" Can NOT open input image file: <%s>\n",infile);
    printf(" Exiting program..... "); system("PAUSE"); exit(1);
  }
  else  printf(" Input file <%s> opened sucessfully\n\n",infile);
  if ((outfptr = fopen(outfile,"wb")) == NULL)
  { printf(" Can NOT open output image file <%s>\n\n",outfile);
    printf(" Exiting program....."); system("PAUSE"); exit(1);
  }
  else printf(" Output file <%s> is opened sucessfully\n\n",outfile);
  readhdr();
  return;
}
//end openfiles()

//------------------------------------------------------------------------------
//------------------------------READHDR-----------------------------------------
//------------------------------------------------------------------------------
void readhdr()
{
  int     i, k=0, MaxRGB;
  char    c, c1, buffer[128];
//-----------------------[Read PPM File Header]-------------------------------
  printf("\n\n File <%s> Header Bytes:\n",infile);
  printf("------------------------------------------------------------\n");
    i = 0;
    do
    { c = fgetc(infptr);
//quitar linea
// printf("valor de C: %i\n",c);
      buffer[i] = c; i++;
    } while (c != '\n');
    
     c1 = buffer[1];
     
     if (c1 == '6')
     {
       printf("\nFile type is:  <P%c>\n",c1);
     }
     else
     { printf(" Image is in WRONG format!! Quitting.........\n\n");
       system("PAUSE");
       exit(0);
     }
    
  fscanf(infptr,"%d %d %d",&NCols, &MRows, &MaxRGB);
  c = fgetc(infptr);
  printf("%d ",NCols);
  printf("%d     <-----(Width & Height)\n", MRows);
  printf("%d         <-----(Max. RGB Level)\n\n",MaxRGB);

}
//end readhdr()

//------------------------------------------------------------------------------
//------------------------------READBODY-----------------------------------------
//------------------------------------------------------------------------------
void readbody()
{
    if( (comienzo=ftell( infptr )) < 0 )   printf( "ERROR: ftell no ha funcionado\n" );
    else    printf( "Posición en archivo despues del header: %d\n\n", comienzo );
    fseek( infptr, 0L, SEEK_END );
    final = ftell( infptr );

    fseek( infptr, 15, SEEK_SET );
    printf("Comienzo: %d\n",comienzo);
    printf("final: %d\n",final);
    cont=15;
    fgetpos( infptr, &principio );
    printf( "Posicion del fichero: %d\n", principio );
//fseek( infptr, 786430, SEEK_SET );
//fsetpos( infptr, &set );
//printf( "Posicion del fichero: %d\n", principio );
     do
     {
        temp=0;
        for(i=0;i<3;i++)
        {

          inread[i]=fgetc(infptr);
//printf("el valor %d de inread es %i\n",i,inread[i]);
          temp = temp + inread[i];
        }
        temp=temp/3;
//printf("el valor de la suma dividido entre 3 : %d\n",temp);
        cont+=3;
//cont++;
        fputc(temp,outfptr);
//printf("el valor de cont es: %d\n",cont);
     }
     while(cont<final+1);
//while(cont<255);
     fgetpos( infptr, &principio );
     printf( "Posicion del fichero: %d\n", principio );

}
//end readbody()

//------------------------------------------------------------------------------
//------------------------------WRITEHDR----------------------------------------
//------------------------------------------------------------------------------
void writehdr()
{
//rewind(infptr);
//fputc('P',infptr);
//printf( "%c", fputc('P6', outfptr) );
    fputs( "P5\n512\n512\n255\n", outfptr );
//fputc(162,outfptr);

}
//end writehdr()

//------------------------------------------------------------------------------
//----------------------------CLOSEFILES----------------------------------------
//------------------------------------------------------------------------------
void closefiles()
{
//------------------------(Close Files)---------------------------------------
  fclose(infptr);
  fclose(outfptr);
  return;
}
//end closefiles()
//------------------------------------------------------------------------------

