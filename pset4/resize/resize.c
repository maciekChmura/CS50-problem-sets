/**
 * Resize image
 */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize [resize factor] [infile] [outfile]\n");
        return 1;
    }
    // resize factor variable
    int n = atoi(argv[1]);

    //check resize factor range
    if ( n < 1 || n > 100) {
        fprintf(stderr, "Resize factor must be between 1 and 100\n");
        return 1;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, newf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    newf = bf;
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, newi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    newi = bi;
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // calculate sizes
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("%i\n", padding);
    newi.biWidth = bi.biWidth * n;
    newi.biHeight = bi.biHeight * n;

    // determine padding for scanlines

    int paddingAfter = (4 - (newi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("%i\n", paddingAfter);

    newi.biSizeImage = ((sizeof(RGBTRIPLE) * newi.biWidth) + paddingAfter ) * abs(newi.biHeight);

    newf.bfSize = newi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    //bf.bfSize *= n;
    fwrite(&newf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&newi, sizeof(BITMAPINFOHEADER), 1, outptr);
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //for n - 1 times to resize vertically
        for ( int m = 0; m < n; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // write RGB triple to outfile
                for ( int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over padding, if any in original bmp
            //fseek(inptr, padding, SEEK_CUR);
            // add new padding to new bmp
            for (int k = 0; k < paddingAfter; k++) {
                fputc(0x00, outptr);
            }
            fseek(inptr, (long int)(bi.biWidth * sizeof(RGBTRIPLE))*(-1), SEEK_CUR);
        }
        fseek(inptr, (long int)(bi.biWidth * sizeof(RGBTRIPLE)) + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    // success
    return 0;
}