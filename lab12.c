/* Laboratorio 12 
 * Nome: Alan Ricardo Gomes 	RA: 145103
 * 
 * Entrada:
 * 		n_muralhas: 	numero de muralhas no labirinto
 *    	(2n-1) linhas 
 *			lista posicoes de passagens ou barreiras ateh chegar a um \n
 * Saida:
 * 		Caminho da parte mais externa do labrinto ateh a parte mais interna
 * Algoritmo:
 *		A partir do destino, o algoritmo percorre o labirinto ateh encontrar a entrada. 
 *		O criterio de parada acontece quando eu passo pela camada mais externa, chamando
 *		a funcao com corredor < 0. Quando isso acontece, o caminho eh encontrado 
 *		Quando nao acontece, eu ando somente pelas passagens permitidas entre as barreiras. 
 *		
 * gcc lab12.c -o lab12 -Wall -Werror -ansi -pedantic
*/

#include <stdio.h> 

int atoi(char * str ){
	int tam = 0;
	int i, sum = 0, mult = 1;

	while(str[tam] != '\0') tam++;

	for ( i = tam - 1; i >= 0; i -- ){
		sum = sum + mult*(str[i]-48);
		mult*=10;
	}
	return sum;
}

/* Tokeniza string */
int strtok (char * str, char *palavra, int inicio){
	char * pointer;
	int j = 0, out = -1;

	pointer = str + inicio;


	while ( *pointer != ' ' && * pointer != '\n' && *pointer != '\0' ){
		palavra[j++] = *pointer;
		pointer++;
	}
	palavra[j] = '\0';
	
	if( *pointer == '\n' || *pointer == '\0')
		out = -1;
	else 
		out = inicio + j + 1;
	return out;
}



int andaLab(int camadas[][360], int * tam_camada, int corr, int graus, char pass, int n){
	int B[2]; /* id das barreiras mais proximas da passagem */
	int i, j; 
	int P[360], np = 0; /* id das passagens da muralha mais interna */
	int P_ext[360], np_ex = 0; /* id das passagens da muralha mais externa */
	int offset; 

	/*printf("Caminhando no corredor %d\n", corr);
	printf("\tEntrada %c pelo grau %d\n", pass, graus);*/
	B[0] = -1;
	B[1] = -1;

	if( corr == -1 ){
		printf("%c %d\n", pass, graus);
		return 1;
	}

	i = 0;
	while( camadas[corr][i] < graus && i < tam_camada[corr]) i++;
	/*printf("\ti = %d\n", i);*/
	B[0] = camadas[corr][(i+tam_camada[corr]-1)%tam_camada[corr]];
	B[1] = camadas[corr][(i)%tam_camada[corr]];


	offset = 360 - B[0];


	/*printf("\toffset: %d\n", offset);

	printf("\tB[0] = %d\n\tB[1] = %d\n", B[0], B[1] );*/


	/* Se houver mais ou igual a duas barreiras */
	for ( i = 0, j = 0; i < tam_camada[corr+1] && B[0] != B[1]; i++ ){
		if ( (B[0]+offset)%360 < (camadas[corr+1][i]+offset)%360 && (B[1]+offset)%360 > (camadas[corr+1][i]+offset)%360 ){
			if ( (pass == 'E' && graus != camadas[corr+1][i]) || pass == 'S'){
				P[j++] = camadas[corr+1][i];
				np++;
			}
		}
	}
	i = 0;

	/* Se houver uma ou menos barreiras */
	while ( B[0] == B[1] && i < tam_camada[corr+1]) {
		P[i] = camadas[corr+1][i];
		np++;
		i++;
	}

	/* Se houver mais ou igual a duas barreiras */
	for ( i = 0, j = 0; i < tam_camada[corr-1] && B[0] != B[1]; i++ ){
		if ( (B[0]+offset)%360 < (camadas[corr-1][i]+offset)%360 && (B[1]+offset)%360 > (camadas[corr-1][i]+offset)%360 ){
			if ( (pass == 'S' && graus != camadas[corr-1][i]) || pass == 'E'){
				P_ext[j++] = camadas[corr-1][i];
				np_ex++;
			}
		}
	}
	
	i = 0;

	/* Se houver uma ou menos barreiras */
	while ( B[0] == B[1] && i < tam_camada[corr-1]) {
		P_ext[i] = camadas[corr-1][i];
		np_ex++;
		i++;
	}


	/*printf("P: " );
	for ( i = 0 ; i < np; i ++ ) {
		printf("%d ", P[i]);
	}
	printf("\n");
	printf("P_ext: " );
	for ( i = 0 ; i < np_ex; i ++ ) {
		printf("%d ", P_ext[i]);
	}
	printf("\n"); */

	if( np == 0 && np_ex == 0 ){
		return 0;
	}

	if( np_ex != 0 ){
		for ( i = 0; i < np_ex; i ++ ){
			if ( andaLab(camadas, tam_camada, corr-2, P_ext[i], 'E', n) == 1 ){
				printf("%c %d\n", pass, graus);
				return 1;
			}
		}
	}
	if( np != 0 ){
		for ( i = 0; i < np; i ++ ){
			if ( andaLab(camadas, tam_camada, corr+2, P[i], 'S', n) == 1 ){
				/* Saida = Saida + pass + graus */
				printf("%c %d\n", pass, graus);
				return 1;
			}
		}
	}
	return 0;
}

void start(int camadas[][360], int * tam_camada, int n ){
	int i;
	for ( i = 0; i < tam_camada[n-1]; i ++ ){
		andaLab(camadas, tam_camada, n-2, camadas[n-1][i], 'E', n);
	}
	return;
}

int main () {
	char aux[1440], c, palavra[4];
	int n_muralhas, i, j, aux_inicio, camadas[20][360], tam_camada[20];

	scanf("%d\n", &n_muralhas);

	for ( i = 0; i < (2*n_muralhas - 1); i++ ){
		
		/* Leitura de linha */
		j = 0;
		do{
			scanf("%c", &c);
			aux[j++] = c;
		} while( c != '\n' && c!= '\0');
		aux[j] = '\0';

		/* Estruturando informacoes a partir da string */
		
		aux_inicio = 0; tam_camada[i] = 0; j = 0;
		
		do {
			aux_inicio = strtok(aux, palavra, aux_inicio);
			camadas[i][j++] = atoi(palavra);
			tam_camada[i]++;
		}while(aux_inicio != -1);
	}
	/*for ( i = 0; i < 2*n_muralhas-1; i++) printf("%d ", tam_camada[i]);
	printf("\n");*/

	start(camadas, tam_camada, 2*n_muralhas-1);

	return 0;
}