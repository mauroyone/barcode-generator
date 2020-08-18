#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tp1.h"

static const uint str_digitos[]=
{
    /*Tomando W=0 y B=1 la codifición R es:*/
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

const uint BoW (digitos_t digito)
{
	switch(digito)
	{
		case CERO: return str_digitos[CERO];
		case UNO: return str_digitos[UNO];
		case DOS: return str_digitos[DOS];
		case TRES: return str_digitos[TRES];
		case CUATRO: return str_digitos[CUATRO];
		case CINCO: return str_digitos[CINCO];
		case SEIS: return str_digitos[SEIS];
		case SIETE: return str_digitos[SIETE];
		case OCHO: return str_digitos[OCHO];
		case NUEVE: return str_digitos[NUEVE];
	}
	return str_digitos[digito];
}

static const uint str_primer_digito[]=
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

const uint representacion_doce_digitos (primer_digito_t primer_digito)
{
	switch(primer_digito)
	{
		case PRIMER_DIGITO_CERO: return str_primer_digito[PRIMER_DIGITO_CERO];
		case PRIMER_DIGITO_UNO: return str_primer_digito[PRIMER_DIGITO_UNO];
		case PRIMER_DIGITO_DOS: return str_primer_digito[PRIMER_DIGITO_DOS];
		case PRIMER_DIGITO_TRES: return str_primer_digito[PRIMER_DIGITO_TRES];
		case PRIMER_DIGITO_CUATRO: return str_primer_digito[PRIMER_DIGITO_CUATRO];
		case PRIMER_DIGITO_CINCO: return str_primer_digito[PRIMER_DIGITO_CINCO];
		case PRIMER_DIGITO_SEIS: return str_primer_digito[PRIMER_DIGITO_SEIS];
		case PRIMER_DIGITO_SIETE: return str_primer_digito[PRIMER_DIGITO_SIETE];
		case PRIMER_DIGITO_OCHO: return str_primer_digito[PRIMER_DIGITO_OCHO];
		case PRIMER_DIGITO_NUEVE: return str_primer_digito[PRIMER_DIGITO_NUEVE];
	}
	return str_primer_digito[primer_digito];
}
int main (void)
{
	char numero_codigo_de_barras[MAX_CADENA],como_codificar[MAX_CADENA];
	char cadena_codificada_b_w[MAX_CADENA];
	char aux_ancho[MAX_CADENA], aux_alto[MAX_CADENA];
	primer_digito_t primer_digito;
	uint tipo_de_representacion;

    pedir_codigo_numerico(numero_codigo_de_barras);
    pedir_dimensiones(aux_ancho, aux_alto);
	if (validar_codigo(numero_codigo_de_barras) != OK)
    {
		fputc('\n',stderr);
		fputs(MSJ_ERROR_SALIDA,stderr);
		return EXIT_FAILURE;
	}
	primer_digito=numero_codigo_de_barras[0]-48;
	tipo_de_representacion=representacion_doce_digitos(primer_digito);
    definir_codificacion(como_codificar,tipo_de_representacion);
    generar_cadena_B_W(numero_codigo_de_barras,como_codificar,cadena_codificada_b_w);
    if (validar_dimensiones(aux_ancho, aux_alto) != OK)
	{
		fputs(MSJ_ERROR_CARGA_DATOS,stderr);
		fputs(MSJ_VALORES_DEFECTO,stderr);
	}
    else
    {
		puts(aux_ancho);
		puts(aux_alto);
	}
	return EXIT_SUCCESS;
}

void pedir_codigo_numerico(char codigo[MAX_CADENA])
{
    /* Se encarga de pedir por STDIN el codigo de barras y darle el formato correspondiente
      quitando el '\n' que deja el fgets y reemplazandolo por '\0' */

    fgets(codigo, MAX_CADENA, stdin);
	if(codigo[strlen(codigo)-1]=='\n')
		codigo[strlen(codigo)-1]='\0';
}

void pedir_dimensiones(char aux_ancho[], char aux_alto[])
{
	fgets(aux_ancho,MAX_CADENA,stdin);
	if (aux_ancho[strlen(aux_ancho)-1]=='\n')
		aux_ancho[strlen(aux_ancho)-1]='\0';
	fgets(aux_alto, MAX_CADENA, stdin);
    if (aux_alto[strlen(aux_alto)-1]=='\n')
        aux_alto[strlen(aux_alto)-1]='\0';
}

status_t validar_codigo(char const cadena[])
{
	/* Se encarga de validar el codigo numerico para longitud, valores y redundancia*/

	int digito_redundancia, aux=0;
	size_t i;

	if (strlen(cadena)!= LONGITUD_CODIGO)
    {
        fputs(MSJ_ERROR_CANTIDAD_DIGITOS,stderr);

        return ERROR_CANTIDAD_DIGITOS;
    }

	for(i=0;i<strlen(cadena);i++)
	{
		if (!isdigit(cadena[i]))
		{
			fputs(MSJ_ERROR_CARGA_DATOS,stderr);
			return ERROR_CARGA_DATOS;
        }
	}

	for (i=0;i<(strlen(cadena)-1);i++)
    {
		if (i%2)
			aux+=3*(cadena[i]-48);
		else aux+=(cadena[i]-48);
	}

	digito_redundancia=10-aux%10;
	if(digito_redundancia==10)
		digito_redundancia=0;
	if (digito_redundancia!=cadena[i]-48)
    {
		fputs(MSJ_ERROR_REDUNDANCIA,stderr);
		return ERROR_VALOR_REDUNDANCIA;
	}
	return OK;
}

void definir_codificacion(char c[MAX_CADENA], uint n)
{
    /* Se encarga de definir si la representacion es L, G o R
       para cada elemento del codigo numerico. Se termina guardando
       un arreglo del estilo: "LGLGLG|RRRRRR/0" */

    size_t i;

    for(i=INICIO;i<MEDIO;i++)
	{
		if (n&(MASCARA<<((MEDIO-1)-i)))
            c[i]=REPRESENTACION_G;
		else c[i]=REPRESENTACION_L;
	}

	c[i]=SEPARADOR;

	for(i=MEDIO+1;i<FIN+1;i++)
		c[i]=REPRESENTACION_R;

	c[i]='\0';
}

void generar_cadena_B_W(char const codigo[MAX_CADENA], char const codificacion[MAX_CADENA], char cadena_b_w[MAX_CADENA])
{
    /* Genera la cadena de B-W a partir del codigo y el tipo de codificacion necesaria y la imprime por STDOUT*/

    digitos_t digito;
    size_t i,j,aux;
    uint bow;
    
    cadena_b_w[0]=NEGRO;
	cadena_b_w[1]=BLANCO;
	cadena_b_w[2]=NEGRO;
	cadena_b_w[3]='\0';
    for(i=0;i<FIN+1;i++)
    {
		digito=codigo[i+1]-48;
		bow=BoW(digito);
		aux=strlen(cadena_b_w);
		switch (codificacion[i])
		{
			case REPRESENTACION_L:
            {
                for (j=aux;j<aux+7;j++)
                {
                    if (~bow&((MASCARA)<<(MEDIO*(i+1)-j+i+3)))
                        cadena_b_w[j]=NEGRO;
                    else cadena_b_w[j]=BLANCO;
                }
                cadena_b_w[j]='\0';
            }
            break;
			case REPRESENTACION_G:
            {
                for (j=aux;j<aux+7;j++)
                {
                    if (bow&((MASCARA)<<(j-(MEDIO+1)*i-3)))
                        cadena_b_w[j]=NEGRO;
                    else cadena_b_w[j]=BLANCO;
                }
                cadena_b_w[j]='\0';
            }
			break;
			case SEPARADOR:
			{
				cadena_b_w[45]=BLANCO;
				cadena_b_w[46]=NEGRO;
				cadena_b_w[47]=BLANCO;
				cadena_b_w[48]=NEGRO;
				cadena_b_w[49]=BLANCO;
				cadena_b_w[50]='\0';
			}
			break;
			case REPRESENTACION_R:
            {
                for (j=aux;j<aux+7;j++)
                {
                    if (bow&((MASCARA)<<(MEDIO*(i+1)-j+i)))
                        cadena_b_w[j]=NEGRO;
                    else cadena_b_w[j]=BLANCO;
                }
            }
            cadena_b_w[j]='\0';
			break;
		}
	}
	cadena_b_w[j]=NEGRO;
	cadena_b_w[j+1]=BLANCO;
	cadena_b_w[j+2]=NEGRO;
	cadena_b_w[j+3]='\0';
	puts(cadena_b_w);
}

status_t validar_dimensiones(char const aux_ancho[], char const aux_alto[])
{
	size_t i;
	
	for(i=0; i<strlen(aux_ancho);i++)
		if(!isdigit(aux_ancho[i]))
			return ERROR_CARGA_DATOS;
	for(i=0; i<strlen(aux_alto);i++)
		if(!isdigit(aux_alto[i]))
			return ERROR_CARGA_DATOS;
	return OK;
}

