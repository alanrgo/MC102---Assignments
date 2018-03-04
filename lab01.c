/***********************************************************************
*  EXERCICIO DE PROGRAMACAO - LAB01 
*  PAD: ALAN RICARDO GOMES 	RA: 145103
*
*  CHECKLIST: 
*  --- Somente variaveis simples
*  --- Sem ifs aninhados
*  --- Codigo sem continue ou break
*  --- Unico cabecalho eh stdio.h
*  --- Descricao de entrada e saida
*
*  ENTRADA: 
*  --- 8 Numeros referentes aos buracos dos simbolos
*  --- 8 Numeros referentes ao numero de componentes do simbolo
*
*  SAIDA:
*  --- Palavra de 8 (ou menos) letras maisculas formando uma palavra
*
*  Compilar with gcc lab01.c -o lab01 -Wall -Werror -ansi -pedantic -lm 
*
************************************************************************/	

#include <stdio.h>

int main () {
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;
	int x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0, x6 = 0, x7 = 0, x8 = 0;
	int odd_flag = 0;
	int prod = 1;

	scanf("%d %d %d %d %d %d %d %d\n", &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);
	scanf("%d %d %d %d %d %d %d %d\n", &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8);

	/*CONDICAO 1 */
	if ( c4 != 2 && c4 != 9 ){
		x1 += 3;
		x2 += 3;
		x3 += 3;
		x4 += 3;
		x5 += 3;
		x6 += 3;
		x7 += 3;
		x8 += 3;
	}

	/*CONDICAO 2 */
	if ( c1 >= 11 && c1 <= 42 ){
		x8 += 7;
		x7 += 8;
	}

	/*CONDICAO 3 */
	if ( c1 % 2 == 0 || c2 % 2 == 0 || c3 % 2 == 0 || c4 % 2 == 0 || c5 % 2 == 0 || c6 % 2 == 0 || c7 % 2 == 0 || c8 % 2 == 0 )
		odd_flag = 1;
	if (!odd_flag)
		x1 += 2*c5;

	/*CONDICAO 4 */
	if ( (c3 < 20 || c6 < 20) && !(c3 < 20 && c6 < 20)){
		x4 += 6;
		x5 += 6;
	}

	/*CONDICAO 5 */
	if ( c8 != 3 && c8 >= c7 )
		x3 += c2;

	/*CONDICAO 6 */
	prod = c1*c2*c3*c4*c5*c6*c7*c8;
	if( (prod % 5 == 0 && prod % 10 != 0) || prod == 30 )
		x6 += 1;

	/*CONDICAO 7 */
	if ( c2 == c8 || c3 == c7 ){
		x6 += 1;
	}

	/*CONVERSAO FINAL */ 
	x1 += 64;
	x2 += 64;
	x3 += 64;
	x4 += 64;
	x5 += 64;
	x6 += 64;
	x7 += 64;
	x8 += 64;

	if ( x1  > 64 && x1 < 91)
		printf("%c", x1);
	if ( x1 == 91 )
		printf (" ");

	if ( x2  > 64 && x2 < 91)
		printf("%c", x2);
	if ( x2 == 91 )
		printf (" ");

	if ( x3  > 64 && x3 < 91)
		printf("%c", x3);
	if ( x3 == 91 )
		printf (" ");

	if ( x4  > 64 && x4 < 91)
		printf("%c", x4);
	if ( x4 == 91 )
		printf (" ");

	if ( x5  > 64 && x5 < 91)
		printf("%c", x5);
	if ( x5 == 91 )
		printf (" ");

	if ( x6  > 64 && x6 < 91)
		printf("%c", x6);
	if ( x6 == 91 )
		printf (" ");

	if ( x7  > 64 && x7 < 91)
		printf("%c", x7);
	if ( x7 == 91 )
		printf (" ");

	if ( x8  > 64 && x8  < 91)
		printf("%c", x8);
	if ( x8 == 91 )
		printf (" ");
	printf("\n");

	return 0;
}