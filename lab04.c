/***********************************************************************
*  EXERCICIO DE PROGRAMACAO - LAB04
*  PAD: ALAN RICARDO GOMES 	RA: 145103
*
*  CHECKLIST: 
*  --- Apenas variaveis simples
*  --- Apenas desvios condicionais
*  --- Menos que 20 variaveis
*  --- Apenas stdio.h
*
*  ENTRADA: 
*  --- n
*  --- i1 j1 posicoes da nave 1 no tabuleiro
*  --- i2 j2 posicoes da nave 2 no tabuleiro
*  --- i3 j3 posicoes da nave 3 no tabuleiro
*  --- i4 j4 posicoes da nave 4 no tabuleiro
*  --- i5 j5 posicoes da nave 5 no tabuleiro
*  --- k posicao j da nave mestra
*
*  SAIDA:
*  --- 10 tabuleiros referentes as interacoes das pecas
*
*  ALGORITMO: 
*  1) Imprime campo, pecas ou laser, tendo a certeza que nao sera impresso dois simbolos diferentes para o mesmo espaco.
*  2) Atualiza o tabuleiro: a) aumenta o tamanho do laser, b) move as naves quando possivel, c) verifica se o laser 
*  atingiu alguma nave. 
*  3) Repete 1 e 2 ateh termos 10 iteracoes no total
*
*  Compilar with gcc lab04.c -o lab04 -Wall -Werror -ansi -pedantic
*
************************************************************************/	

#include <stdio.h>

int main(){
	int n;
	int i1, j1, i2, j2, i3, j3, i4, j4, i5, j5;
	int k;
	int i, j;
	int min_i_ship;

	/* game controller */
	int laser_height = 0;
	int iterations = 0;
	int printed = 0;
	int side_ships = 0;

	scanf("%d\n", &n);
	scanf("%d %d\n", &i1, &j1);
	scanf("%d %d\n", &i2, &j2);
	scanf("%d %d\n", &i3, &j3);
	scanf("%d %d\n", &i4, &j4);
	scanf("%d %d\n", &i5, &j5);
	scanf("%d", &k);

	iterations = 1;
	while( iterations <= 10) {
		/* Imprime campo */
		for ( i = 1; i <= n; i ++ ){
			for ( j = 1; j <= n; j ++ ){
				/* Flags */
				printed = 0;

				/* Se tivermos uma nave */
				if (i == i1 && j == j1 ){
					printf("* ");
					printed = 1;
				}
				if (i == i2 && j == j2 ){
					printf("* ");
					printed = 1;
				}
				if (i == i3 && j == j3  ){
					printf("* ");
					printed = 1;
				}
				if (i == i4 && j == j4  ){
					printf("* ");
					printed = 1;
				}
				if (i == i5 && j == j5 ){
					printf("* ");
					printed = 1;
				}

				/* Se for a posicao da nave mestra */
				if( i == n && j == k ){
					printf("X ");
					printed = 1;
				}

				/* Imprime laser */
				if( j == k && i <= n-1 && i >= n - laser_height  ){
					printf("| ");
					printed = 1;
				}

				if( printed == 0 )
					printf(". ");
			}
			printf("\n");
		}
		printf("\n");

		/* update variables */
		laser_height++;

		if(laser_height >= n-1){
			laser_height = n-1;
		}

		iterations++;

		/* Move naves */
		if ( iterations > 1 ){
			/* Move para a direita*/
			if( (iterations-1)%4 == 1 || (iterations-1)%4 == 0){
				
				/* Nave 1 */
				side_ships = 0;
				if( j2 > j1 && i2 == i1 ){/* Se a nave 2 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 > j1 && i3 == i1 ){/* Se a nave 3 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 > j1 && i4 == i1 ){/* Se a nave 4 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 > j1 && i5 == i1 ){/* Se a nave 5 estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < n - j1){
					j1 = j1 + 1;
				}

				/* Nave 2 */
				side_ships = 0;
				if( j1 > j2 && i2 == i1 ){/* Se a nave 1 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 > j2 && i3 == i2 ){/* Se a nave 3 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 > j2 && i4 == i2 ){/* Se a nave 4 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 > j2 && i5 == i2 ){/* Se a nave 5 estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < n - j2){
					j2 = j2 + 1;
				}

				/* Nave 3 */
				side_ships = 0;
				if( j1 > j3 && i1 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j2 > j3 && i2 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 > j3 && i4 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 > j3 && i5 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < n - j3){
					j3 = j3 + 1;
				}

				/* Nave 4 */
				side_ships = 0;
				if( j1 > j4 && i1 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j2 > j4 && i2 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 > j4 && i3 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 > j4 && i5 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < n - j4){
					j4 = j4 + 1;
				}

				/* Nave 5 */
				side_ships = 0;
				if( j1 > j5 && i1 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j2 > j5 && i2 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 > j5 && i3 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 > j5 && i4 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < n - j5){
					j5 = j5 + 1;
				}

			}
			if( (iterations-1)%4 == 2 || (iterations-1)%4 == 3){

				/* Nave 1 */
				side_ships = 0;
				if( j2 < j1 && i2 == i1 ){/* Se a nave 2 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 < j1 && i3 == i1 ){/* Se a nave 3 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 < j1 && i4 == i1 ){/* Se a nave 4 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 < j1 && i5 == i1 ){/* Se a nave 5 estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < j1 - 1){
					j1 = j1 - 1;
				}

				/* Nave 2 */
				side_ships = 0;
				if( j1 < j2 && i2 == i1 ){/* Se a nave 1 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 < j2 && i3 == i2 ){/* Se a nave 3 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 < j2 && i4 == i2 ){/* Se a nave 4 estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 < j2 && i5 == i2 ){/* Se a nave 5 estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < j2 -1){
					j2 = j2 - 1;
				}

				/* Nave 3 */
				side_ships = 0;
				if( j1 < j3 && i1 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j2 < j3 && i2 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 < j3 && i4 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 < j3 && i5 == i3 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < j3 - 1){
					j3 = j3 - 1;
				}

				/* Nave 4 */
				side_ships = 0;
				if( j1 < j4 && i1 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j2 < j4 && i2 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 < j4 && i3 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j5 < j4 && i5 == i4 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < j4 - 1){
					j4 = j4 - 1;
				}

				/* Nave 5 */
				side_ships = 0;
				if( j1 < j5 && i1 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j2 < j5 && i2 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j3 < j5 && i3 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( j4 < j5 && i4 == i5 ){/* Se a nave estiver a direita na mesma linha */
					side_ships++;
				}
				if( side_ships < j5 - 1){
					j5 = j5 - 1;
				}

			}
		}

		/* Checa se alguma nave foi atingida */
		/* A nave um foi atingida? */
		min_i_ship = -1;
		if( j1 == k && i1 >= n - laser_height){
			if(min_i_ship < i1)
				min_i_ship = i1;
			i1 = -1;
		}
		if( j2 == k && i2 >= n - laser_height){
			if(min_i_ship < i2)
				min_i_ship = i2;
			i2 = -1;
		}
		if( j3 == k && i3 >= n - laser_height){
			if(min_i_ship < i3)
				min_i_ship = i3;
			i3 = -1;
		}
		if( j4 == k && i4 >= n - laser_height){
			if(min_i_ship < i4)
				min_i_ship = i4;
			i4 = -1;
		}
		if( j5 == k && i5 >= n - laser_height){
			if(min_i_ship < i5)
				min_i_ship = i5;
			i5 = -1;
		}
		if(min_i_ship != -1){
			laser_height = n - min_i_ship -1;
		}
	}
	return 0;
}