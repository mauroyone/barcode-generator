#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "barcode_generator.h"


status_t convert_bw_to_01(char encoded_string[MAX_STRING])
{
    size_t i = 0;
    
    if (strlen(encoded_string) != 95)
    {
		fputs(MSJ_ERROR_DIGIT_NUMBER,stderr);
		return ERROR_NUMBER_OF_DIGITS;
	}
    for(i=0; i < 95; i++)
    {
        if(encoded_string[i] == WHITE)
        {
            encoded_string[i] = CHARACTER_0;
        }
        else
        { 
			if(encoded_string[i] == BLACK)
			{
				encoded_string[i] = CHARACTER_1;
			}
			else 
			{
			fputs(MSJ_ERROR_INPUT_DATA,stderr);
			return ERROR_INPUT_DATA;
			} 
		}       
	}
    encoded_string[i] = '\0';
    return OK;
}

void print_pbm_header (int width, int height)
{
    puts(HEADER);
    putchar('\n');
    printf("%i %i \n", width, height);
    printf("%c %s %i %s %i %s \n",COMMENT, COMMENT_P1, width, COMMENT_P2, height, COMMENT_P3);
}
void assign_dimensions (char const aux_width[], char const aux_height[], uint *width, uint *height)
{
	char *temp;
	
	*width = strtol(aux_width, &temp, 10);
	if(*temp)
	{
		*width = WIDTH;
	}
	*height = strtol(aux_height, &temp, 10);
	if (*temp)
	{
		*height = HEIGHT;
	}
}
void print_bars(char value, int number)
{
    size_t i;
    for(i=0; i < number; i++)
    {
        putchar(value);
    }
    putchar('\t');
}

int main(void)
{
        size_t i,j;
        uint width, height, number;
        char string_b_w[MAX_STRING], string_borders[MAX_STRING];
        char aux_width[MAX_STRING], aux_height[MAX_STRING];
        for(i=0; i < 95; i++){
			if(i == 0 || i == 2 || i == 46 || i == 48 || i == 92 || i == 94)
				string_borders[i] = BLACK;
			else
				string_borders[i] = WHITE;
		}
		string_borders[i] = '\0';
        fgets(string_b_w, MAX_STRING, stdin);
        fgets(aux_width, MAX_STRING, stdin);
		fgets(aux_height, MAX_STRING, stdin);

        /* At this point it only takes the WB string */
        if(string_b_w[strlen(string_b_w)-1] == '\n')
            string_b_w[strlen(string_b_w)-1] = '\0';
        if(convert_bw_to_01(string_b_w) != OK)
        {
			fputs(MSJ_ERROR_EXIT, stderr);
			return EXIT_FAILURE;
		}
        if(convert_bw_to_01(string_borders) != OK)
        {
			fputs(MSJ_ERROR_EXIT, stderr);
			return EXIT_FAILURE;
		}
		assign_dimensions(aux_width, aux_height, &width, &height);
        print_pbm_header(width-width%95, height);

        number = width/95;
        for(i=0; i < height*0.8; i++)
        {
			for(j=0; j < strlen(string_b_w); j++)
			{
				print_bars(string_b_w[j], number);
			}
		}
		for(i=0; i < height; i++)
		{
			for(j=0; j < strlen(string_borders); j++)
			{	
				print_bars(string_borders[j], number);
			}
		}
        return 0;
}
