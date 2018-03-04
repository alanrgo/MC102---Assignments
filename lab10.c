#include "lab10.h"
#include <stdio.h> 
#include <stdlib.h>

#define INF 2147483647


typedef struct {
	unsigned short int id; 
	unsigned short int intensidade;
	unsigned short int n_notas;
	unsigned short int * duracao;
	unsigned short int * comeco;
	unsigned short int * fim;
	unsigned short int * frequencia;
} Tabela;

typedef struct {
	TpEvento *ev;
	struct NoEvento * prox;
} NoEvento;


/* Funcoes relacionadas a lista de tempos */
unsigned short int *criaListaTempo(unsigned short int size){
	unsigned short int *nova_lista = (unsigned short int *)malloc(sizeof(unsigned short int)*size);
	return nova_lista;
}

unsigned short int insereElemento(unsigned short int vetor[], unsigned short int *size, unsigned short int elemento){
	int i, index = *size, existe = 0;
	*size = *size + 1;
	for ( i = 0; i < *size - 1  && elemento >= vetor[i]; i ++ ){
		if ( vetor[i] == elemento )
			existe = 1;
	}
	index = i;
	for ( i = *size -2; i >= index && !existe; i--){
		vetor[i+1] = vetor[i];
	}
	if( !existe)
		vetor[index] = elemento;
	else 
		*size = *size -1;
	return index;
}
/* Fim das funcoes relacionadas a lista de tempos */

TpEvento * criaEvento(unsigned short int deltaTime, unsigned char canal, unsigned char key, unsigned char velocity){
	TpEvento * novo_evento = (TpEvento *) malloc (sizeof (TpEvento));
	if( novo_evento != NULL ){
		novo_evento -> deltaTime = deltaTime;
		novo_evento -> canal = canal;
		novo_evento -> key = key;
		novo_evento -> velocity = velocity;
	}
	return novo_evento;
}


int main (){
	unsigned short int canais;
	unsigned short int * numCanais; 
	unsigned short int i, j, k, l, m, soma = 0, aux_tempo, trechoId, index_temp, index_evento, tempo_final, deltaTime;
	unsigned short int **seq;
	unsigned short int *tempos, t_size = 0;
	unsigned short int conta_tempo;
	int pausa_criada;
	Tabela *tabelas;
	TpEvento * eventos, * aux;


	scanf("%hu\n", &canais);
	
	numCanais = (unsigned short int *) malloc(sizeof(unsigned short int)*canais);

	if( numCanais != NULL ){

		/* Leitura do vetor canais */
		for ( i = 0; i < canais; i ++ ){
			scanf("%hu", &(numCanais[i]));
		}

		/* leitura de numero de notas de trechos */
		scanf("%hu %hu", &j, &k);

		/* Cria um vetor de ponteiros */
		seq = (unsigned short int **)malloc(sizeof(unsigned short int *)*canais);
		tabelas = (Tabela *) malloc (sizeof (Tabela)*k);
		for ( i = 0; i < k; i ++ ){
			scanf("%hu\n", &(trechoId));
			tabelas[trechoId - 1].id = trechoId;
			trechoId = trechoId - 1;
			scanf("%hu %hu", &(tabelas[trechoId].intensidade), &(tabelas[trechoId].n_notas));
			tabelas[trechoId].comeco = (unsigned short int *) malloc(sizeof(unsigned short int)*tabelas[trechoId].n_notas);
			tabelas[trechoId].duracao =  (unsigned short int *) malloc(sizeof(unsigned short int)*tabelas[trechoId].n_notas);
			tabelas[trechoId].fim = (unsigned short int *) malloc(sizeof(unsigned short int)*tabelas[trechoId].n_notas); 
			tabelas[trechoId].frequencia = (unsigned short int *) malloc(sizeof(unsigned short int)*tabelas[trechoId].n_notas); 
			
			for( l = 0; l < tabelas[trechoId].n_notas; l++){
				scanf("%hu ", &(tabelas[trechoId].duracao[l]));
				scanf("%hu ", &(tabelas[trechoId].frequencia[l]));
			}
		}

		/* Leitura da sequencia de trechos */
		for ( i = 0; i < canais; i ++ ){
			seq[i] = (unsigned short int *)malloc(sizeof(unsigned short int)*j);
			for ( l = 0; l < j && seq[i] != NULL; l++ ){
				scanf("%hu", &(seq[i][l]));
			}
		}

		/* Imprimir valores */ 
		/*printf("-- Canais: -- \n");
		for ( i = 0 ; i < canais; i++ ){
			printf("%hu ", numCanais[i]);
		}

		printf("\n-- Notas de trecho -- \n");
		printf("%hu %hu\n", j, k);

		for ( i = 0; i < k; i ++ ){
			printf("\n-- Imprimindo tabela %d -- \n", i);
			for( l = 0; l < tabelas[i].n_notas; l++){
				printf("(%hu, %hu) ", tabelas[i].duracao[l],tabelas[i].frequencia[l] );
			}
			printf("\n");
		}
		printf("\n");*/

		for ( i = 0; i < canais; i ++ ){
			for ( l = 0; l < j && seq[i] != NULL; l++ ){
				/*printf("%hu ", seq[i][l]);*/
				trechoId = seq[i][l] - 1;
				soma = soma + tabelas[trechoId].n_notas;
			}
			/* printf("\n");*/
		}
		/*printf("\n");
		printf("soma: %hu\n", soma);*/

		tempos = criaListaTempo(soma);

		for ( i = 0; i < canais; i++ ){
			aux_tempo = 0;
			for ( l = 0; l < j; l++ ){
				trechoId = seq[i][l] - 1;
				for ( m = 0; m < tabelas[trechoId].n_notas; m++){
					tabelas[trechoId].comeco[m] = aux_tempo;
					aux_tempo = aux_tempo + tabelas[trechoId].duracao[m];
					tabelas[trechoId].fim[m] = aux_tempo;
					/* printf("(%hu %hu) ", tabelas[trechoId].comeco[m], tabelas[trechoId].fim[m]);*/
					insereElemento(tempos, &t_size, aux_tempo);
				}
				/*printf("\n");*/
			}
		}

		index_temp = 0;
		index_evento = 0;
		aux_tempo = 0;
		eventos = (TpEvento *) malloc(sizeof(TpEvento)*t_size*canais*2);
		while ( index_temp != t_size  ){
			tempo_final = tempos[index_temp];
			deltaTime = tempo_final - aux_tempo;
			for ( i = 0; i < canais; i ++ ){
				conta_tempo = 0;
				for ( l = 0; l < j; l ++ ){
					trechoId = seq[i][l] - 1;
					for ( m = 0; m < tabelas[trechoId].n_notas; m++ ){
						tabelas[trechoId].comeco[m] = conta_tempo;
						conta_tempo =  conta_tempo + tabelas[trechoId].duracao[m];
						tabelas[trechoId].fim[m] = conta_tempo;
						if ( tabelas[trechoId].fim[m] >= tempo_final && tabelas[trechoId].comeco[m] <= aux_tempo && tabelas[trechoId].frequencia[m] != 128){
							/* Cria Eventos de Inicio */
							/*printf("\n--- Criando evento %hu no canal %hu\n", index_evento, i);
							printf("\ttrechoId: %hu\n\t freq: %hu\n\tintensidade: %hu\n", trechoId, tabelas[trechoId].frequencia[m], tabelas[trechoId].intensidade);
							printf("\ttempo_final: %hu e aux_tempo: %hu\n", tempo_final, aux_tempo);*/

							aux = criaEvento( 0, i, tabelas[trechoId].frequencia[m], tabelas[trechoId].intensidade );
							eventos[index_evento] = *aux;
							index_evento++;
						}
					}
					
				}
			}
			pausa_criada = 0;
			for( i = 0; i < canais; i ++ ){
				conta_tempo = 0;
				for ( l = 0; l < j; l ++ ){
					trechoId = seq[i][l] - 1;
					for ( m = 0; m < tabelas[trechoId].n_notas && !pausa_criada; m++ ){
						tabelas[trechoId].comeco[m] = conta_tempo;
						conta_tempo =  conta_tempo + tabelas[trechoId].duracao[m];
						tabelas[trechoId].fim[m] = conta_tempo;
						if ( tabelas[trechoId].fim[m] >= tempo_final && tabelas[trechoId].comeco[m] <= aux_tempo && tabelas[trechoId].frequencia[m] != 128){
							/* Cria Eventos de Fim */
							/*printf("\n--- Criando evento %hu de pausa no canal %hu. dT: %hu \n", index_evento, i, deltaTime);
							printf("\ttempo_final: %hu e aux_tempo: %hu\n", tempo_final, aux_tempo);
							printf("\ttrechoId: %hu\n\t freq: %hu\n\tintensidade: %hu\n", trechoId, tabelas[trechoId].frequencia[m], tabelas[trechoId].intensidade);*/
							aux = criaEvento( deltaTime, i, tabelas[trechoId].frequencia[m], 0 );
							eventos[index_evento] = *aux;
							index_evento++;
							pausa_criada = 1;

						}
					}
				}
			}
			aux_tempo = tempo_final;
			index_temp ++;
		}
		saida(0, canais, numCanais, index_evento, eventos);
	}


	/* Free */
	/* Para cada tabela */
		/* Free vetor comeco */
		/* Free vetor fim */
		/* Free vetor frequencia */
	/* Para cada canal */
		/* Free cada vetor sequencia */

	return 0;
}