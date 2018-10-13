//~/pset4/resize.c
//pset4 cs50
//onelmv
//10.12.2018
//Resize a BMP file n times.

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "%i is not valid. Enter a number between 1 and 100.\n", n);
        return 1;
    }

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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER bfUpdate = bf; //new file header
    BITMAPINFOHEADER biUpdate = bi; //new info header

    biUpdate.biWidth = bi.biWidth * n;  //update width
    biUpdate.biHeight = bi.biHeight * n;//update Height

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int updatePadding = (4 - (biUpdate.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // update padding

    //update sizeImage (RGBTriples)
    biUpdate.biSizeImage = ((sizeof(RGBTRIPLE) * biUpdate.biWidth) + updatePadding) * abs(biUpdate.biHeight);
    //update size (MBP Header + RGBTriples)
    bfUpdate.bfSize = biUpdate.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write resized BITMAPFILEHEADER
    fwrite(&bfUpdate, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write resized BITMAPINFOHEADER
    fwrite(&biUpdate, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int line = 0 ; line < n ; line++) // line * n
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple * n, to resized file
                for (int k = 0; k < n ; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add updated padding to resized file
            for (int l = 0; l < updatePadding; l++)
            {
                fputc(0x00, outptr);
            }

            if (line < n - 1) //vertical resize
            {
                fseek(inptr, -(sizeof(RGBTRIPLE) * bi.biWidth), SEEK_CUR);  // return to the beginning of the current line
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }
    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    // success
    return 0;
}
