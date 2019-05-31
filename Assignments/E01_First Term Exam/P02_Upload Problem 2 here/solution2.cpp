//----------------------------------------------------------------------------//
// Template for reading portable gray map files (*.pgm)                       //
//                                                                            //
//                                                RickWare                    //
//                                                August 23, 2018             //
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
#include <iostream>
#include <algorithm>

using namespace std;
//----------------------------------------------------------------------------//
//         Variable declarations                                              //
//----------------------------------------------------------------------------//

int    MRows, NCols;                 /* Number of Rows and columns in image */
FILE   *infptr, *outfptr, *outfptrh; /* Input and output file pointers */
char   infile[40];                   /* Name of input file */
char   outfile[40];                  /* Name of output file */

//----------------------------------------------------------------------------//
//         Main program                                                       //
//----------------------------------------------------------------------------//

int main ()
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
     int i;
     for (i=0; i<16; i++)
       printf("                                    +                       \n");
       printf("                      Digital Image Processing in C         \n");
       printf("                          Date: August 23, 2018             \n");
       printf("                            Author: RickWare                \n");
     for (i=0; i<3; i++)
       printf("                                    +                       \n");
       return;
} // end heading ()

//----------------------------------------------------------------------------//
//         Openfiles                                                          //
//----------------------------------------------------------------------------//

void openfiles ()
{
     printf("\n Opening Input and Output image files\n");
     printf(" Enter name of *.pgm INPUT image file (example: lena.pgm) ");
     scanf("%s",infile);
     
     //Check if input file exists
     if ((infptr = fopen(infile, "rb")) == NULL)
     {
       printf(" Cannot open input image file: %s\n",infile);
       printf(" Exiting program...\n");
       system("PAUSE");
       exit(1);
       }
     
     printf(" Enter name of *.pgm OUTPUT image file (example: lenaout.pgm) ");
     scanf("%s",outfile);
     
     //Check if output file was created succesfully
     if ((outfptr = fopen(outfile, "wb")) == NULL)
     {
       printf(" Cannot create output image file: %s\n",outfile);
       printf(" Exiting program...\n");
       system("PAUSE");
       exit(1);
       }
       
     // If this point is reached, file are OK
     printf(" File opened and created OK! \n\n");
     
}  //end openfiles ()

//----------------------------------------------------------------------------//
//         Read Image File Header                                             //
//----------------------------------------------------------------------------//

void readhdr ()
{
     int   i=0, MaxRGB;
     char  c, buffer[128];
     
     //Read header of PGM file
     printf("\n\n File <%s> Header: \n",infile);
     
     do
     {
       c = fgetc(infptr);
       buffer[i] = c;
       i++; 
     } while (c != '\n');
     
     //Check if file is P5 (pgm) format
     if (buffer[1] == '5')
       printf("\n Input file is pgm, OK\n");
     else
     {
       printf("\n Input file is NOT pgm, Exiting program...\n");
       system("PAUSE");
       exit(0);
     }
     
     //File is pgm, read rest of header
     fscanf(infptr,"%d %d %d",&NCols, &MRows, &MaxRGB);
     //Make file pointer point to the first byte of the image
     c = fgetc(infptr);
     //Image info
     printf("%d ",NCols);
     printf("%d   <---- Width x Height) \n",MRows);
     printf("%d   <---- Max. Grayscale level) \n\n",MaxRGB);
}  // end readhdr ()

//----------------------------------------------------------------------------//
//         Add Image Header to output file                                    //
//----------------------------------------------------------------------------//

void addhdr ()
{
     fprintf(outfptr, "P5\n%d %d\n%d\n",NCols-2 ,MRows-2,255);
} //addhdr ()

//----------------------------------------------------------------------------//
//         User defined section                                               //        
//         Your preprocessors/algorithms will be defined here                 //
//----------------------------------------------------------------------------//

void userdefined ()
{
  unsigned char p;
  //unsigned char calcp[(MRows-2)*(NCols-2)];

	p=fgetc(infptr);
	int i,j;
	//Allocate a matrix
	unsigned  char **arr = (unsigned char **)malloc(MRows * sizeof(unsigned char *)); 
    for (i=0; i<MRows; i++) {
    	arr[i] = (unsigned char *)malloc(NCols * sizeof(unsigned char)); 
    }
    // Note that arr[i][j] is same as *(*(arr+i)+j) 
    for (i = 0; i <  MRows; i++){
      for (j = 0; j < NCols; j++){
       arr[i][j] = p;  
       p=fgetc(infptr);
      }
    }
    //int e=0;
    unsigned char win[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (i = 1; i <  MRows-1; i++){
      for (j = 1; j < NCols-1; j++){

    
        win[0]=arr[i-1][j-1];
        win[1]=arr[i-1][j];
        win[2]=arr[i-1][j+1];

        win[3]=arr[i][j-1];
        win[4]=arr[i][j];
        win[5]=arr[i][j+1];
        win[6]=arr[i+1][j-1];
        win[7]=arr[i+1][j];
        win[8]=arr[i+1][j+1];


        sort(win, win + 9);
        float median = 0;

        if (9 % 2 != 0) {
          median = win[9 / 2];
        } else {
          median = (win[(9 - 1) / 2] + win[9 / 2]) / 2.0;
        }
               fputc(median, outfptr);  



      }
    }


        
	//write on output pointer rotateLeft
  
    
  
}  // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void closefiles ()
{
     fclose(infptr);
     fclose(outfptr);
}  // end closefiles ()
