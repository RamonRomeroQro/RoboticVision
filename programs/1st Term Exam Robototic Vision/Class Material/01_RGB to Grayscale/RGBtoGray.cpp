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
void     closefiles();
void     display(void);
//------------------------------------------------------------------------------
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
//------------------------------------------------------------------------------
int      MRows, NCols;                     //indices for rows and cols
FILE     *infptr, *outfptr;                //input/output file pointers
char     infile[40];
char     static  outfile[40];              //names of input/output image files

//------------------------------------------------------------------------------
//-----------------------------MAIN---------------------------------------------
//------------------------------------------------------------------------------
main()
{
    //--------------( Display Heading with information )----------------------
    heading();
    //---------------(Open Input & Output Image Files)------------------------
    openfiles();
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
//----------------------------CLOSEFILES----------------------------------------
//------------------------------------------------------------------------------
void closefiles()
{ //------------------------(Close Files)---------------------------------------
  fclose(infptr);
  fclose(outfptr);
  return;
} //end closefiles()
//------------------------------------------------------------------------------
