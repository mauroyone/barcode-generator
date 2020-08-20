#ifndef BARCODE_GENERATOR_H
#define BARCODE_GENERATOR_H

#define CODE_LENGHT 13
#define MAX_STRING 100
#define START 0
#define MIDDLE 6
#define END 12
#define REPRESENTATION_G 'G'
#define REPRESENTATION_L 'L'
#define REPRESENTATION_R 'R'
#define SEP '|'
#define WHITE 'W'
#define BLACK 'B'
#define CHARACTER_0 '0'
#define CHARACTER_1 '1'

#define MASK 0x01

#define MSJ_ENTER_CODE "Enter the numeric code"

#define MSJ_ERROR_EXIT "The program will exit"
#define MSJ_ERROR_DIGIT_NUMBER "Error: The number of entered digits is incorrect"
#define MSJ_ERROR_INPUT_DATA "Error: At least one value is incorrect"
#define MSJ_ERROR_REDUNDANCY "Error: The redundancy value is incorrect"
#define MSJ_DEFAULT_VALUES "Setting default values"

#define WIDTH 380
#define HEIGHT 190

#define HEADER "P1"
#define COMMENT '#'
#define COMMENT_P1 "The image size is"
#define COMMENT_P2 "width"
#define COMMENT_P3 "height"

typedef unsigned int uint;

typedef enum
{
    OK,
    ERROR_NUMBER_OF_DIGITS,
    ERROR_INPUT_DATA,
    ERROR_REDUNDANCY_VALUE
} status_t;

typedef enum
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
} digits_t;

typedef enum
{
    first_digit_ZERO,
    first_digit_ONE,
	first_digit_TWO,
	first_digit_THREE,
	first_digit_FOUR,
	first_digit_FIVE,
	first_digit_SIX,
	first_digit_SEVEN,
	first_digit_EIGHT,
	first_digit_NINE
} first_digit_t;

const uint BoW (digits_t digit);
const uint twelve_digit_representation (first_digit_t first_digit);
void ask_for_numeric_code(char code[MAX_STRING]);
void ask_for_dimensions(char aux_width[], char aux_height[]);
status_t code_validation(char const string[]);
void define_codification(char c[MAX_STRING], uint n);
void generate_string_B_W(char const code[MAX_STRING], char const codification[MAX_STRING], char string_b_w[MAX_STRING]);
status_t validate_dimensions(char const aux_width[], char const aux_height[]);

#endif
