#include <stdio.h> 

void printMap(int row, int col, char map[300][300]){
	int i, j;
	for ( i = 0; i < row; i ++){
		for (j = 0; j < col; j++ ){
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main(){
	char a, b;
	int w, h;
	char map[300][300];
	int i, j;

	int passo_i, passo_j, soma, total = 0, ha_vizinho, ha_vizinho_visitado, armadilha;

	scanf("%c%c\n%d %d \n", &a, &b, &w, &h);

	for ( i = 0; i < h; i ++){
		for (j = 0; j < w; j++ ){
			scanf("%c ", &(map[i][j]));
		}
	}

	for ( i = 0; i < h; i++){
		for (j=0; j < w; j++ ){
			if( map[i][j] == '1'){
				passo_i = i;
				passo_j = j;

				soma = 1;
				do{
					map[passo_i][passo_j] = '*';
					ha_vizinho = 1;

					/* Se ha vizinho ponto, nao soma ilha */
					if( passo_j - 1 >= 0 && passo_i + 1 < h && map[passo_i + 1][passo_j -1] == '.' ){ /* Esq-inf*/
						soma = 0;
					}
					if( passo_j - 1 >= 0 && map[passo_i][passo_j -1] == '.'){ /* Esquerda */
						soma = 0;
					}
					if ( passo_i - 1 >= 0 && passo_j - 1 >= 0 && map[passo_i -1][passo_j -1] == '.'){ /* Esq-sup */
						soma = 0;
					}
					if ( passo_i - 1 >= 0 && map[passo_i -1][passo_j] == '.'){ /* Cima */
						soma = 0;
					}
					if ( passo_i -1 >= 0 && passo_j + 1 < w && map[passo_i - 1][passo_j + 1] == '.'){ /* Dir-sup */
						soma = 0;
					}
					if( passo_j + 1 < w && map[passo_i][passo_j + 1 ] == '.' ){ /* Direita */
						soma = 0;
					}
					if( passo_i + 1 < h  && passo_j + 1 < w && map[passo_i + 1][passo_j + 1] == '.' ){ /* Dir-inf */
						soma = 0;
					}
					if( passo_i + 1 < h && map[passo_i + 1][passo_j] == '.' ){ /* Baixo */
						soma = 0;
					}
					
					/* Pega o proximo passo */
					/* Cima */
					if ( passo_i - 1 >= 0 && map[passo_i - 1][passo_j] == '1' ){
						passo_i = passo_i -1;
					}
					/* Esq-sup*/
					else if( passo_i - 1 >= 0 && passo_j - 1 >= 0 && map[passo_i -1][passo_j -1] == '1' ){
						passo_i = passo_i - 1;
						passo_j = passo_j - 1;
					}
					/* Esq */
					else if ( passo_j - 1 >= 0 && map[passo_i][passo_j -1] == '1' ){
						passo_j = passo_j - 1;
					}
					/* Esq-inf */
					else if ( passo_j - 1 >= 0 && passo_i + 1 < h && map[passo_i + 1][passo_j -1] == '1' ){
						passo_j = passo_j - 1;
						passo_i = passo_i + 1;
					}
					/* Baixo */
					else if (passo_i + 1 < h && map[passo_i + 1][passo_j] == '1' ){
						passo_i = passo_i + 1;
					}
					/* Dir-Inf*/
					/*else if (passo_i + 1 < h && passo_j + 1 < w && map[passo_i + 1][passo_j + 1] == '1' ){
						passo_j = passo_j + 1;
						passo_i = passo_i + 1;
					}*/
					/* Dir*/
					/*else if (passo_j + 1 < w && map[passo_i][passo_j + 1] == '1') {
						passo_j = passo_j + 1;
					}*/
					/* Dir-Sup*/
					/*else if (passo_j + 1 < w && passo_i - 1 >= 0 && map[passo_i - 1][passo_j + 1] == '1') {
						passo_j = passo_j + 1;
						passo_i = passo_i - 1;
					}*/
					/* Cima */
					/*else if (passo_i - 1 >= 0 && map[passo_i - 1][passo_j] == '1' ) {
						passo_i = passo_i - 1;
					}*/
					else {
						ha_vizinho = 0;
					}
					/*printMap(h, w, map);*/

				}while(ha_vizinho == 1);

				/* Eh uma ilha independente? */
				if( soma == 1 ){
					total = total + 1;
					/*printf("(%d, %d)\n", passo_i, passo_j);
					printMap(h, w, map);*/
				}

				/* Volta o caminho */
				do{
					ha_vizinho_visitado = 1;
					map[passo_i][passo_j] = '.';

					/* Ordem reversa aqui */
					/* Baixo */
					if ( passo_i + 1 < h && map[passo_i + 1][passo_j] == '*') {
						passo_i = passo_i + 1;
					}
					/* Dir- Inf */
					else if ( passo_i + 1 < h && passo_j + 1 < w && map[passo_i + 1][passo_j + 1] == '*'  ){
						passo_i = passo_i + 1;
						passo_j = passo_j + 1;
					}
					/* Direita */
					else if( passo_j + 1 < w && map[passo_i][passo_j + 1] == '*' ){
						passo_j = passo_j + 1;
					}
					/* Dir-Sup*/
					else if ( passo_j + 1 < w && passo_i - 1 >= 0 && map[passo_i - 1][passo_j + 1] == '*'){
						passo_i = passo_i - 1;
						passo_j = passo_j + 1;
					}
					/* Cima */
					else if ( passo_i - 1 >= 0 && map[passo_i - 1][passo_j] == '*' ){
						passo_i = passo_i -1;
					}
					/* Esq-Inf*/
					/*else if ( passo_j - 1 >= 0 && passo_i + 1 < h && map[passo_i + 1][passo_j -1] == '*' ) {
						passo_i = passo_i + 1;
						passo_j = passo_j - 1;
					} */
					/* Esq */
					/*else if ( passo_j - 1 >= 0 && map[passo_i][passo_j -1] == '*' ) {
						passo_j = passo_j - 1;
					}*/
					/* Esq-sup */
					/*else if ( passo_i - 1 >= 0 && passo_j - 1 >= 0 && map[passo_i -1][passo_j -1] == '*') {
						passo_i = passo_i - 1;
						passo_j = passo_j - 1;
					}*/
					else {
						ha_vizinho_visitado = 0;
					}
					/*printMap(h, w, map);*/
				}while (ha_vizinho_visitado == 1 );

			}
		}
	}
	printf("%d\n", total);

	return 0;
}