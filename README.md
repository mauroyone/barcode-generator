# barcode-generator
This project was build in ANSI-C and uses the EAN-13 system.

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

<table>
  <tr>
    <th> Digit </th>
    <th> L Code </th>
    <th> G Code </th>
    <th> R Code </th>
  </tr>
  <tr>
    <th> 0 </th>
    <th> WWWBBWB </th>
    <th> WBWWBBB </th>
    <th> BBBWWBW </th>
  </tr>
  <tr>
    <th> 1 </th>
    <th> WWBBWWB </th>
    <th> WBBWWBB </th>
    <th> BBWWBBW </th>
  </tr>
  <tr>
    <th> 2 </th>
    <th> WWBWWBB </th>
    <th> WWBBWBB </th>
    <th> BBWBBWW </th>
  </tr>
  <tr>
    <th> 3 </th>
    <th> WBBBBWB </th>
    <th> WBWWWWB </th>
    <th> BWWWWBW </th>
  </tr>
  <tr>
    <th> 4 </th>
    <th> WBWWWBB </th>
    <th> WWBBBWB </th>
    <th> BWBBBWW </th>
  </tr>
  <tr>
    <th> 5 </th>
    <th> WBBWWWB </th>
    <th> WBBBWWB </th>
    <th> BWWBBBW </th>
  </tr>
  <tr>
    <th> 6 </th>
    <th> WBWBBBB </th>
    <th> WWWWBWB </th>
    <th> BWBWWWW </th>
  </tr>
  <tr>
    <th> 7 </th>
    <th> WBBBWBB </th>
    <th> WWBWWWB </th>
    <th> BWWWBWW </th>
  </tr>
  <tr>
    <th> 8 </th>
    <th> WBBWBBB </th>
    <th> WWWBWWB </th>
    <th> BWWBWWW </th>
  </tr>
  <tr>
    <th> 9 </th>
    <th> WWWBWBB </th>
    <th> WWBWBBB </th>
    <th> BBBWBWW </th>
  </tr>
</table>

Where B is black and represents a filled bar and W is white and represents an empty bar.
Check that each digit is represented by seven bar.

Note: the R code is the L code complement while G code is R's reverse. This means they are redundant between them.


## Barcode codification
The codification styles depends on the first digit:

<table>
  <tr>
    <th> First digit </th>
    <th> Firts chunk </th>
    <th> Second chunk </th>
  </tr>
  <tr>
    <th> 0 </th>
    <th> LLLLLL </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 1 </th>
    <th> LLGLGG </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 2 </th>
    <th> LLGGLG </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 3 </th>
    <th> LLGGGL </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 4 </th>
    <th> LGLLGG </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 5 </th>
    <th> LGGLLG </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 6 </th>
    <th> LGGGLL </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 7 </th>
    <th> LGLGLG </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 8 </th>
    <th> LGLGGL </th>
    <th> RRRRRR </th>
  </tr>
  <tr>
    <th> 9 </th>
    <th> LGGLGL</th>
    <th> RRRRRR </th>
  </tr>
</table>

The lateral guards always use a BWB codification and the middle one a BWBWB. This means, each barcode has 12*7 + 2*3 + 1*5 = 95 bars.


## PBM Format
A PBM file consists of a "P1" header where its dimensions are specified (hight x width) and the values for each pixel from top left to
bottom right. They are represented by 0s for empty pixels and 1s for filled ones.
The pixels are splitted by one or more blanck spaces.

In addition, comments can be added if the line starts with a '#' symbol.

Example:

`P1`<br>
`# 5x5 image.`<br>
`5 5`<br>
`0 1 1 1 1`<br>
`0 0 0 1 1`<br>
`0 0 1 0 1`<br>
`0 1 0 0 1`<br>
`1 0 0 0 0`<br>


Representation of a 5x5 pixel graph. A black arrow pointing to the top right corner.


## How to compile
The compiler used is gcc:

`gcc -o barcode_generator.exe barcode_generator.c -Wall -ansi -pedantic` <br>
`gcc -o pbm_generator.exe pbm_generator.c -Wall -ansi -pedantic`

## How to use
On Linux: ./ barcode_generator.exe | ./pbm_generator.exe > my_pbm.pbm
On Windows: barcode_generator.exe | pbm_generator.exe > my_pbm.pbm

On both cases, a product code will be asked as well as the dimensions for the image file.
If the dimensions are omitted, the default values are going to be used.
