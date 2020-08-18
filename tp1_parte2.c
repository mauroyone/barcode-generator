#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tp1.h"

#define ANCHO 380
#define ALTO 190

#define ENCABEZADO "P1"
#define COMENTARIO '#'
#define COMENTARIO_P1 "La imagen es de"
#define COMENTARIO_P2 "de ancho por"
#define COMENTARIO_P3 "de alto"

status_t convertir_bw_a_01(char cadena_codificada[MAX_CADENA])
{
    size_t i=0;
    
    if (strlen(cadena_codificada)!=95)
    {
		fputs(MSJ_ERROR_CANTIDAD_DIGITOS,stderr);
		return ERROR_CANTIDAD_DIGITOS;
	}
    for(i=0;i<95;i++)
    {
        if(cadena_codificada[i]==BLANCO)
        {
            cadena_codificada[i]=CARACTER_0;
        }
        else
        { 
			if(cadena_codificada[i]==NEGRO)
			{
				cadena_codificada[i]=CARACTER_1;
			}
			else 
			{
			fputs(MSJ_ERROR_CARGA_DATOS,stderr);
			return ERROR_CARGA_DATOS;
			} 
		}       
	}
    cadena_codificada[i]='\0';
    return OK;
}

void imprimir_encabezado_pbm (int ancho, int alto)
{
    puts(ENCABEZADO);
    putchar('\n');
    printf("%i %i \n",ancho,alto);
    printf("%c %s %i %s %i %s \n",COMENTARIO,COMENTARIO_P1,ancho,COMENTARIO_P2,alto,COMENTARIO_P3);
}
void asignar_dimensiones (char const aux_ancho[], char const aux_alto[], uint *ancho, uint *alto)
{
	char *temp;
	
	*ancho=strtol(aux_ancho,&temp,10);
	if(*temp)
	{
		*ancho=ANCHO;
	}
	*alto=strtol(aux_alto,&temp,10);
	if (*temp)
	{
		*alto=ALTO;
	}
}
void imprimir_barras(char valor,int cantidad)
{
    size_t i;
    for(i=0;i<cantidad;i++)
    {
        putchar(valor);
    }
    putchar('\t');
}

int main(void)
{
        size_t i,j;
        uint ancho, alto, cantidad;
        char cadena_b_w[MAX_CADENA], cadena_bordes[MAX_CADENA];
        char aux_ancho[MAX_CADENA], aux_alto[MAX_CADENA];
        for(i=0;i<95;i++){
			if(i==0||i==2||i==46||i==48||i==92||i==94)
				cadena_bordes[i]=NEGRO;
			else
				cadena_bordes[i]=BLANCO;
		}
		cadena_bordes[i]='\0';
        fgets(cadena_b_w,MAX_CADENA,stdin);
        fgets(aux_ancho,MAX_CADENA,stdin);
		fgets(aux_alto,MAX_CADENA,stdin);
        /*Por ahora solo toma cadena WB, cuando definamos como vamos a pasarla vemos de adaptarlo*/

        if(cadena_b_w[strlen(cadena_b_w)-1]=='\n')
            cadena_b_w[strlen(cadena_b_w)-1]='\0';
        if(convertir_bw_a_01(cadena_b_w)!=OK)
        {
			fputs(MSJ_ERROR_SALIDA,stderr);
			return EXIT_FAILURE;
		}
        if(convertir_bw_a_01(cadena_bordes)!=OK)
        {
			fputs(MSJ_ERROR_SALIDA,stderr);
			return EXIT_FAILURE;
		}
		asignar_dimensiones(aux_ancho,aux_alto, &ancho,&alto);
        imprimir_encabezado_pbm(ancho-ancho%95,alto);

        cantidad=ancho/95;
        for(i=0;i<alto*0.8;i++)
        {
			for(j=0;j<strlen(cadena_b_w);j++)
			{
				imprimir_barras(cadena_b_w[j],cantidad);
			}
		}
		for(i=0;i<alto;i++)
		{
			for(j=0;j<strlen(cadena_bordes);j++)
			{	
				imprimir_barras(cadena_bordes[j], cantidad);
			}
		}
        return 0;
}
