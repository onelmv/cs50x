# Questions

## What's `stdint.h`?

C standar library to be able to work with very specific int .

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Use integers Unsigned with  8, 16, 32 or 64 bytes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE` : 8 bytes.
`DWORD`: 32 bytes.
`LONG`: 32 bytes.
`WORD` : 16 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x424d , 0100 0010 0100 1101 , BM

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the bitmap file (in bytes ) , and biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

the bitmap is a top-down DIB and its origin is the upper-left corner, and it cann't be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Because a correct memory address was not obtained, and avoid segmentation fault.

## Why is the third argument to `fread` always `1` in our code?

Becacuse the quantity of unit to read in the file is 1 ,BITMAPFILEHEADER or BITMAPINFOHEADER .

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Seek the padding position.

## What is `SEEK_CUR`?

It's the curent position where the file it's reading.

## Whodunit?

"It was professor plum with the candlestick in the library"
