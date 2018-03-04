/***********************************************************************
*  EXERCICIO DE PROGRAMACAO - LAB02
*  PAD: ALAN RICARDO GOMES 	RA: 145103
*
*  CHECKLIST: 
*  --- Somente variaveis simples
*  --- Codigo sem continue ou break
*  --- Unico cabecalho eh stdio.h
*  --- Descricao de entrada e saida
*
*  ENTRADA: 
*  --- 11 Numeros inteiros referentes ao tempo de viagem de uma estrela a outra
*  
*  SAIDA:
*  --- numero inteiro referente ao tempo gasto de viagem entre Daneb e Altair
*
*	Algoritmo: Calcula-se todos os tempos de todos os caminhos possiveis. 
* 	Escolhe-se o menor tempo. Verifica-se se, ao escolher sempre o menor tempo
*   ao sair de uma estrela, finalizariamos com um tempo multiplo de 6. Caso aconteca,
*	o vortex eh criado e o tempo final eh 0. Caso contrario, mantemos o valor do menor tempo
*   previamente cauculado.
*  
*  Compilar with gcc lab02.c -o lab02 -Wall -Werror -ansi -pedantic -lm 
*
************************************************************************/

#include <stdio.h>

int main(){
	int mul6 = 0;
	int A, B, C, D, E, F, G, H, I, J, K;
	int min_A = 0, min_B = 0, min_C = 0, min_D = 0, min_E = 0, min_F = 0, min_G = 0, min_H = 0, min_I = 0, min_J = 0, min_K = 0;
	int custo = 0, custo_min = 0;
	int vortex, temp_min;

	/* Leitura dos dados */
	scanf("%d %d %d %d %d %d %d %d %d %d %d\n", &A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K);

	/* Caminhos */
	
	/*Primeiro caminho possivel*/
	custo = A + D + F + J;
	custo_min = custo;

	/*Segundo caminho possivel*/
	custo = A + D + F + I + K;
	if( custo_min > custo )
		custo_min = custo;

	/*Terceiro caminho possivel*/
	custo = A + D + G + K;
	if( custo_min > custo )
		custo_min = custo;

	/*Quarto caminho possivel*/
	custo = A + E + J;
	if( custo_min > custo )
		custo_min = custo;

	/*Quinto caminho possivel*/
	custo = A + E + I + K;
	if( custo_min > custo )
		custo_min = custo;

	/*Sexto caminho possivel*/
	custo = B + F + J;
	if( custo_min > custo )
		custo_min = custo;

	/*Setimo caminho possivel*/
	custo = B + F + I + K;
	if( custo_min > custo )
		custo_min = custo;

	/*Oitavo caminho possivel*/
	custo = B + G + K;
	if( custo_min > custo )
		custo_min = custo;

	/*Nono caminho possivel*/
	custo = C + H + K;
	if( custo_min > custo )
		custo_min = custo;

	/*Verifica vortex*/ 

	/* Minimum path(s) from Deneb */
	/* -- getting the min value -- */
	temp_min = A;
	if( temp_min > B )
		temp_min = B;
	if( temp_min > C )
		temp_min = C;

	/* -- flagging the paths */
	if( temp_min == A )
		min_A = 1;
	if( temp_min == B )
		min_B = 1;
	if( temp_min == C )
		min_C = 1;

	/* Minimum path(s) from Rukh */
	/* -- getting the min value -- */
	temp_min = D;
	if( temp_min > E )
		temp_min = E;

	/* -- flagging the paths */
	if( temp_min == D )
		min_D = 1;
	if( temp_min == E )
		min_E = 1;

	/* Minimum path(s) from Sadr */
	/* -- getting the min value -- */
	temp_min = F;
	if( temp_min > G )
		temp_min = G;

	/* -- flagging the paths */
	if( temp_min == F )
		min_F = 1;
	if( temp_min == G )
		min_G = 1;

	/* Minimum path(s) from Vega */
	/* -- getting the min value -- */
	temp_min = J;
	if( temp_min > I )
		temp_min = I;

	/* -- flagging the paths */
	if( temp_min == J )
		min_J = 1;
	if( temp_min == I )
		min_I = 1;

	/* Minimum path(s) from Gienah */
	/* -- getting the min value -- */
	min_H = 1; /* Only one option */

	/* Minimum path(s) from Albireo */
	/* -- getting the min value -- */
	min_K = 1; /* Only one option */

	/* Checking the paths */
	/* Path 1 */
	if( min_A && min_D && min_F && min_J){
		vortex = A + D + F + J;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 2 */
	if( min_A && min_D && min_F && min_I && min_K){
		vortex = A + D + F + I + K;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 3 */
	if( min_A && min_D && min_G && min_K){
		vortex = A + D + G + K;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 4 */
	if( min_A && min_E && min_J ){
		vortex = A + E + J;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 5 */
	if( min_A && min_E && min_I && min_K){
		vortex = A + E + I + K;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 6 */
	if( min_B && min_F && min_J){
		vortex = B + F + J;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 7 */
	if( min_B && min_F && min_I && min_K){
		vortex = B + F + I + K;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 8 */
	if( min_B && min_G && min_K ){
		vortex = B + G + K;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Path 9 */
	if( min_C && min_H && min_K){
		vortex = C + H + K;
		if ( vortex%6 == 0){
			mul6 = 1;
		}
	}

	/* Minimum path(s) from Deneb */
	if( mul6 == 1 ){
		custo_min = 0;
	}

	printf("%d\n", custo_min);
	return 0;
}