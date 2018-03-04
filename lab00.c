/***********************************************************************
*  EXERCICIO DE PROGRAMACAO - LAB00
*  PAD: ALAN RICARDO GOMES 	RA: 145103
*
*  ENTRADA: 
*  --- 2 Numeros inteiros
*
*  SAIDA:
*  --- String mostrando a operacao de soma desses dois numeros
*
*  Compilar with gcc lab00.c -o lab00 -Wall -Werror -ansi -pedantic -lm 
*
************************************************************************/	

#include <stdio.h>

int main(){
	int num_1 = 0, num_2 = 0;

	scanf("%d %d", &num_1, &num_2);
	printf("%d + %d = %d\n", num_1, num_2, num_1 + num_2);
	return 0;
}