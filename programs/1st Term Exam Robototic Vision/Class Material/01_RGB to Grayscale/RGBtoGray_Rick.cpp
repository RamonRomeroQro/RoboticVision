//+++++++++++++++++++++++++++++++<M D I P>++++++++++++++++++++++++++++++++++++++
//
//     >>>MASK DIGITAL IMAGE PROCESSING Program<<<
//
//        This program reads an input color image in *.ppm format
//        and converts it into a grayscale image in *.pgm format
//        using the following equation:
//            Gray(x,y) = 1/3 (Red(x,y) + Green(x,y) + Blue(x,y)
//        for every every pixel located at (x,y) in the image
//
//------------------------------------------------------------------------------
//                  Version updated: February 5, 2009
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
void     convert(void);
void     readhdr(void);
void     closefiles();
void     display(void);
//------------------------------------------------------------------------------
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
//------------------------------------------------------------------------------
int      MRows, NCols;                     //indices for rows and cols
FILE     *infptr, *outfptr, *outfptrh;    //input/output file pointers
char     infile[40];
char     static  outfile[40];              //names of input/output image files

//------------------------------------------------------------------------------
//-----------------------------MAIN---------------------------------------------
//------------------------------------------------------------------------------
main()
{
    //--------------( Display Heading with information )------------------------
    heading();
    //---------------(Open Input & Output Image Files)--------------------------
    openfiles();
    //---------------------(Convert to grayscale)-------------------------------
    convert();
    //------------------(Close Any Open Image Files)----------------------------
    closefiles();
    //--------------------------------------------------------------------------
    printf("\n Bye! Bye!\n");
    system("PAUSE");
    return (1);
} //end main()

//------------------------------------------------------------------------------
//----------------------------HEADING-------------------------------------------
//------------------------------------------------------------------------------
void heading()
{ int      i;
  for (i=0;i<16;i++) printf("                                     +\n");
  printf("                       Digital Image Processing Program\n");
  printf("                         Updated: February 5, 2009\n");
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
  
  if ((outfptrh = fopen("histogram.txt","wb")) == NULL)
  { printf(" Can NOT open output histogram file <%s>\n\n",outfile);
    printf(" Exiting program....."); system("PAUSE"); exit(1);
  }
  else printf(" Output file <%s> is opened sucessfully\n\n",outfile); 
  
  readhdr();
  return;
}//end openfiles()

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
}//end readhdr()

//------------------------------------------------------------------------------
//-------------------------conversion and historgram----------------------------
//------------------------------------------------------------------------------
void convert()
{
  unsigned char R,G,B,Gray;
  unsigned int histcount[256];
  char string[10];
  
  //Initialize histogram count to 0
  for (int i=0;i<256;i++)
   histcount[i] = 0;
    
  //Add *.pgm Header
  fprintf(outfptr,"P5\n512 512\n255\n");
  
  //Perform conversions
  R = fgetc(infptr);
  do{    
     G = fgetc(infptr);
     B = fgetc(infptr);
     Gray =(R + G + B) / 3;
     //Increment histogram for grayscale level
     histcount[Gray]++;
     fputc(Gray,outfptr);
     //Read next pixel to check if we have an End of File
     R = fgetc(infptr);
  } while (!feof(infptr));
  
  //Convert the histogram values from integers to string
  for (int i=0;i<256;i++){
    itoa (histcount[i],string,10);
    fputs(string,outfptrh);
    fputs("\n",outfptrh);
  }
}

//------------------------------------------------------------------------------
//----------------------------CLOSEFILES----------------------------------------
//------------------------------------------------------------------------------
void closefiles()
{ //------------------------(Close Files)---------------------------------------
  fclose(infptr);
  fclose(outfptr);
  fclose(outfptrh);
  return;
} //end closefiles()
//------------------------------------------------------------------------------
