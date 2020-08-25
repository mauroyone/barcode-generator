# barcode-generator
This project was build in C and uses the EAN-13 system.

There are two parts:
  - The first one receives a product number (thirteen digits) from STDIN and returns a 95 secuence of 'B/W'
  representing the barcode via STDOUT.
  - The second one receives the 95 secuence via STDIN and generates the PBM. If no dimensions are provided, default values 
  are going to be used (380x190).
  

## EAN-13
This standard uses (as it name states) thirteen digits to get a unique barcode.
The first twelve ones represent the product, and the last one is a redundancy number.

The redundancy number is calculated as the pondered sum of 1 for the odd digits and 3 for the even.
Then, we calculate the number needed to get to the next multiple of 10. (i.e. the sum is 56, the next multiple of 10 is 60,
hence, the redundancy is 60 - 56 = 4)


## Barcode representation
The representation is a vertical bars sucession, all of the same width.
There are two chunks of bars, cointained in between guards and splitted by a central sep. Each chunk has six digits.

The guards and the central sep use the totallity of the vertical space. While the twelve digits use only the top 80%.
The last twelve digits are presented by seven vertical bars, the first one defines the type of encode to be used.


## Encoded types
There are three posible codifications for each digit:

Dıgit | L Code  | G Code  | R Code
  0   | WWWBBWB | WBWWBBB | BBBWWBW
  1   | WWBBWWB | WBBWWBB | BBWWBBW
  2   | WWBWWBB | WWBBWBB | BBWBBWW
  3   | WBBBBWB | WBWWWWB | BWWWWBW
  4   | WBWWWBB | WWBBBWB | BWBBBWW
  5   | WBBWWWB | WBBBWWB | BWWBBBW
  6   | WBWBBBB | WWWWBWB | BWBWWWW
  7   | WBBBWBB | WWBWWWB | BWWWBWW
  8   | WBBWBBB | WWWBWWB | BWWBWWW
  9   | WWWBWBB | WWBWBBB | BBBWBWW
  
Where B is black and represents a filled bar and W is white and represents an empty bar.
Check that each digit is represented by seven bar.

Note: the R code is the L code complement while G code is R's reverse. This means they are redundant between them.


## Barcode codification
The codification styles depends on the first digit:
First dıgit | First chunk | Second chunk
0           | LLLLLL      | RRRRRR
1           | LLGLGG      | RRRRRR
2           | LLGGLG      | RRRRRR
3           | LLGGGL      | RRRRRR
4           | LGLLGG      | RRRRRR
5           | LGGLLG      | RRRRRR
6           | LGGGLL      | RRRRRR
7           | LGLGLG      | RRRRRR
8           | LGLGGL      | RRRRRR
9           | LGGLGL      | RRRRRR

The lateral guards always use a BWB codification and the middle one a BWBWB. This means, each barcode has 12*7 + 2*3 + 1*5 = 95 bars.


## PBM Format
A PBM file consists of a "P1" header where its dimensions are specified (hight x width) and the values for each pixel from top left to
bottom right. They are represented by 0s for empty pixels and 1s for filled ones.
The pixels are splitted by one or more blanck spaces.

In addition, comments can be added if the line starts with a '#' symbol.

Example:

P1
# Comentario
5 5
# La imagen es de 5 de ancho por 5 de alto.
0 1 1 1 1
0 0 0 1 1
0 0 1 0 1
0 1 0 0 1
1 0 0 0 0

Representation of a 5x5 pixel graph. A black arrow pointing to the top right corner.


gcc -o barcode_generator.exe tp1_parte1 tp1_parte2 -Wall -ansi -pedantic
