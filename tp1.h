#ifndef TP1_H
#define TP1_H

#define LONGITUD_CODIGO 13
#define MAX_CADENA 100
#define INICIO 0
#define MEDIO 6
#define FIN 12
#define REPRESENTACION_G 'G'
#define REPRESENTACION_L 'L'
#define REPRESENTACION_R 'R'
#define SEPARADOR '|'
#define BLANCO 'W'
#define NEGRO 'B'
#define CARACTER_0 '0'
#define CARACTER_1 '1'

#define MASCARA 0x01

#define MSJ_INGRESAR_CODIGO "Ingrese el codigo numerico"

#define MSJ_ERROR_SALIDA "El programa se cerrara."
#define MSJ_ERROR_CANTIDAD_DIGITOS "Error: La cantidad de digitos ingersada es incorrecta"
#define MSJ_ERROR_CARGA_DATOS "Error: Alguno de los valores ingresados es incorrecto"
#define MSJ_ERROR_REDUNDANCIA "Error: El valor de la cifra de redundancia es incorrecto"
#define MSJ_VALORES_DEFECTO "Se tomaran los valores por defecto"

#define ANCHO 380
#define ALTO 190

#define ENCABEZADO "P1"
#define COMENTARIO '#'
#define COMENTARIO_P1 "La imagen es de"
#define COMENTARIO_P2 "de ancho por"
#define COMENTARIO_P3 "de alto"

typedef unsigned int uint;

typedef enum
{
    OK,
    ERROR_CANTIDAD_DIGITOS,
    ERROR_CARGA_DATOS,
    ERROR_VALOR_REDUNDANCIA
} status_t;

typedef enum
{
    CERO,
    UNO,
    DOS,
	TRES,
	CUATRO,
	CINCO,
	SEIS,
	SIETE,
	OCHO,
	NUEVE
} digitos_t;

typedef enum
{
    PRIMER_DIGITO_CERO,
    PRIMER_DIGITO_UNO,
	PRIMER_DIGITO_DOS,
	PRIMER_DIGITO_TRES,
	PRIMER_DIGITO_CUATRO,
	PRIMER_DIGITO_CINCO,
	PRIMER_DIGITO_SEIS,
	PRIMER_DIGITO_SIETE,
	PRIMER_DIGITO_OCHO,
	PRIMER_DIGITO_NUEVE
} primer_digito_t;

const uint BoW (digitos_t digito);
const uint representacion_doce_digitos (primer_digito_t primer_digito);
void pedir_codigo_numerico(char codigo[MAX_CADENA]);
void pedir_dimensiones(char aux_ancho[], char aux_alto[]);
status_t validar_codigo(char const cadena[]);
void definir_codificacion(char c[MAX_CADENA], uint n);
void generar_cadena_B_W(char const codigo[MAX_CADENA], char const codificacion[MAX_CADENA], char cadena_b_w[MAX_CADENA]);
status_t validar_dimensiones(char const aux_ancho[], char const aux_alto[]);

#endif
