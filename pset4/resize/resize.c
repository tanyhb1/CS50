#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "Usage: ./copy n infile outfile\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    FILE *input = fopen(infile, "r");
    if(input == NULL)
    {
        fprintf(stderr, "Error: could not open file\n");   
        return 2;
    }
    
    FILE *output = fopen(outfile, "w");
    if(output == NULL)
    {
        fclose(input);
        fprintf(stderr, "Error: could not create file\n");   
        return 3;
    }
    
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, input);
    
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(output);
        fclose(input);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int height = bi.biHeight;
    int width = bi.biWidth;
    
    bi.biWidth = bi.biWidth*n;
    bi.biHeight = bi.biHeight*n;
   
    int paddingO = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingN = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; 
    
    bf.bfSize = 54+(bf.bfSize-54)*n; 
    bi.biSizeImage = bi.biSizeImage*n;

    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, output);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, output);
    RGBTRIPLE *space = malloc(sizeof(RGBTRIPLE) * bi.biWidth);

    //height
    for(int i = 0, biheight = abs(height); i < biheight; i++)
    {
        //multiplying height by factor of n
     
        int counter = 0;
        //width
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, input);
                
            for(int k = 0; k < n; k++)
            {   
                space[counter] = triple;
                counter = counter + 1;
            }
                
        }
        fseek(input, paddingO, SEEK_CUR);
        
        for(int k = 0; k < n; k++)
        {

            fwrite(space, sizeof(RGBTRIPLE), bi.biWidth, output);   

            
            for(int x = 0; x < paddingN; x++)
            {
                fputc(0x00, output);   
            }
        }
            

    }
    
        // close infile
    fclose(input);

    // close outfile
    fclose(output);
    
    free(space);

    // success
    return 0;
}