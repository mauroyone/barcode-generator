#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "barcode_generator.h"

static const uint str_digits[]=
{
    /*Taking W=0 & B=1 the R code is:*/
    0x72,	/*BBB WWBW*/
	0x66,	/*BBW WBBW*/
	0x6C,	/*BBW BBWW*/
	0x42,	/*BWW WWBW*/
	0x5C,	/*BWB BBWW*/
	0x4E,	/*BWW BBBW*/
	0x50,	/*BWB WWWW*/
	0x44,	/*BWW WBWW*/
	0x48,	/*BWW BWWW*/
	0x74	/*BBB WBWW*/
};

const uint BoW (digits_t digit)
{
	switch(digit)
	{
		case ZERO: return str_digits[ZERO];
		case ONE: return str_digits[ONE];
		case TWO: return str_digits[TWO];
		case THREE: return str_digits[THREE];
		case FOUR: return str_digits[FOUR];
		case FIVE: return str_digits[FIVE];
		case SIX: return str_digits[SIX];
		case SEVEN: return str_digits[SEVEN];
		case EIGHT: return str_digits[EIGHT];
		case NINE: return str_digits[NINE];
	}
	return str_digits[digit];
}

static const uint str_first_digit[]=
{
    /*Tomando L=0 G=1*/
    0x00,  /*LLLLLL*/
	0x0B,  /*LLGLGG*/
	0x0D,  /*LLGGLG*/
	0x0E,  /*LLGGGL*/
	0x13,  /*LGLLGG*/
	0x19,  /*LGGLLG*/
	0x1C,  /*LGGGLL*/
	0x15,  /*LGLGLG*/
	0x16,  /*LGLGGL*/
	0x1A   /*LGGLGL*/
};

const uint twelve_digit_representation (first_digit_t first_digit)
{
	switch(first_digit)
	{
		case first_digit_ZERO: return str_first_digit[first_digit_ZERO];
		case first_digit_ONE: return str_first_digit[first_digit_ONE];
		case first_digit_TWO: return str_first_digit[first_digit_TWO];
		case first_digit_THREE: return str_first_digit[first_digit_THREE];
		case first_digit_FOUR: return str_first_digit[first_digit_FOUR];
		case first_digit_FIVE: return str_first_digit[first_digit_FIVE];
		case first_digit_SIX: return str_first_digit[first_digit_SIX];
		case first_digit_SEVEN: return str_first_digit[first_digit_SEVEN];
		case first_digit_EIGHT: return str_first_digit[first_digit_EIGHT];
		case first_digit_NINE: return str_first_digit[first_digit_NINE];
	}
	return str_first_digit[first_digit];
}
int main (void)
{
	char barcode_numer[MAX_STRING], encode[MAX_STRING];
	char encoded_string_b_w[MAX_STRING];
	char aux_width[MAX_STRING], aux_height[MAX_STRING];
	first_digit_t first_digit;
	uint representation_type;

    ask_for_numeric_code(barcode_numer);
    ask_for_dimensions(aux_width, aux_height);
	
	if (code_validation(barcode_numer) != OK)
    {
		fputc('\n',stderr);
		fputs(MSJ_ERROR_EXIT,stderr);
		return EXIT_FAILURE;
	}
	
	first_digit = barcode_numer[0]-48;
	representation_type = twelve_digit_representation(first_digit);
    define_codification(encode,representation_type);
    generate_string_B_W(barcode_numer,encode,encoded_string_b_w);
    
	if (validate_dimensions(aux_width, aux_height) != OK)
	{
		fputs(MSJ_ERROR_INPUT_DATA, stderr);
		fputs(MSJ_DEFAULT_VALUES, stderr);
	}
    else
    {
		puts(aux_width);
		puts(aux_height);
	}
	return EXIT_SUCCESS;
}

void ask_for_numeric_code(char code[MAX_STRING])
{
    /* The function asks for the barcode from STDIN, then it format as needed
	   removing the '\n' from fgets() and replacing it for a '\0' */

    fgets(code, MAX_STRING, stdin);
	if(code[strlen(code)-1]=='\n')
		code[strlen(code)-1]='\0';
}

void ask_for_dimensions(char aux_width[], char aux_height[])
{
	fgets(aux_width, MAX_STRING, stdin);
	if (aux_width[strlen(aux_width)-1] == '\n')
		aux_width[strlen(aux_width)-1] = '\0';

	fgets(aux_height, MAX_STRING, stdin);
    if (aux_height[strlen(aux_height)-1]=='\n')
        aux_height[strlen(aux_height)-1]='\0';
}

status_t code_validation(char const string[])
{
	/* The function validates the given code */

	int redundancy_digit, aux=0;
	size_t i;

	if (strlen(string)!= CODE_LENGHT)
    {
        fputs(MSJ_ERROR_DIGIT_NUMBER, stderr);

        return ERROR_NUMBER_OF_DIGITS;
    }

	for(i=0; i < strlen(string); i++)
	{
		if (!isdigit(string[i]))
		{
			fputs(MSJ_ERROR_INPUT_DATA, stderr);
			return ERROR_INPUT_DATA;
        }
	}

	for (i=0; i < strlen(string)-1; i++)
    {
		if (i%2)
			aux += 3*(string[i]-48);
		else aux += (string[i]-48);
	}

	redundancy_digit = 10 - aux%10;
	if(redundancy_digit == 10)
		redundancy_digit = 0;
	if (redundancy_digit != string[i]-48)
    {
		fputs(MSJ_ERROR_REDUNDANCY, stderr);
		return ERROR_REDUNDANCY_VALUE;
	}
	return OK;
}

void define_codification(char c[MAX_STRING], uint n)
{
    /* The function defines, for each element, if the representation
	   is L, G or R. Then it saves an array of the style: 
	   "LGLGLG|RRRRRR/0" */

    size_t i;

    for(i=START; i < MIDDLE; i++)
	{
		if (n&(MASK<<((MIDDLE-1)-i)))
            c[i]=REPRESENTATION_G;
		else c[i]=REPRESENTATION_L;
	}

	c[i] = SEP;

	for(i=MIDDLE+1; i < END+1; i++)
		c[i] = REPRESENTATION_R;

	c[i] = '\0';
}

void generate_string_B_W(char const code[MAX_STRING], char const codification[MAX_STRING], char string_b_w[MAX_STRING])
{
    /* Generates the string B-W from the code and codification type 
	   Then prints it to STDOUT*/

    digits_t digit;
    size_t i, j, aux;
    uint bow;
    
    string_b_w[0] = BLACK;
	string_b_w[1] = WHITE;
	string_b_w[2] = BLACK;
	string_b_w[3] = '\0';
    for(i=0; i < END+1; i++)
    {
		digit = code[i+1]-48;
		bow = BoW(digit);
		aux = strlen(string_b_w);
		switch (codification[i])
		{
			case REPRESENTATION_L:
            {
                for (j=aux; j < aux+7; j++)
                {
                    if (~bow&((MASK)<<(MIDDLE*(i+1)-j+i+3)))
                        string_b_w[j] = BLACK;
                    else string_b_w[j] = WHITE;
                }
                string_b_w[j] = '\0';
            }
            break;
			case REPRESENTATION_G:
            {
                for (j=aux; j < aux+7; j++)
                {
                    if (bow&((MASK)<<(j-(MIDDLE+1)*i-3)))
                        string_b_w[j] = BLACK;
                    else string_b_w[j] = WHITE;
                }
                string_b_w[j] = '\0';
            }
			break;
			case SEP:
			{
				string_b_w[45] = WHITE;
				string_b_w[46] = BLACK;
				string_b_w[47] = WHITE;
				string_b_w[48] = BLACK;
				string_b_w[49] = WHITE;
				string_b_w[50] = '\0';
			}
			break;
			case REPRESENTATION_R:
            {
                for (j=aux; j < aux+7; j++)
                {
                    if (bow&((MASK)<<(MIDDLE*(i+1)-j+i)))
                        string_b_w[j] = BLACK;
                    else string_b_w[j] = WHITE;
                }
            }
            string_b_w[j] = '\0';
			break;
		}
	}
	string_b_w[j] = BLACK;
	string_b_w[j+1] = WHITE;
	string_b_w[j+2] = BLACK;
	string_b_w[j+3] = '\0';
	puts(string_b_w);
}

status_t validate_dimensions(char const aux_width[], char const aux_height[])
{
	size_t i;
	
	for(i=0; i < strlen(aux_width); i++)
		if(!isdigit(aux_width[i]))
			return ERROR_INPUT_DATA;
	for(i=0; i < strlen(aux_height); i++)
		if(!isdigit(aux_height[i]))
			return ERROR_INPUT_DATA;
	return OK;
}

