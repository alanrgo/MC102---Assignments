/*  Laboratório 07: Hipótese de Sapir–Whorf 
 *  Arquivo de Cabeçalho: lab07.h   
 *  Descrição:   Este arquivo contém a função para transformar uma string em letras minúsculas e o cabeçalho das funções 
 *               a serem implementadas neste laboratório. Cada função contém uma breve descrição sobre o seu objetivo, 
 *               a saída esperada e uma pequena explicação dos parâmetros de entrada.
 *
 *  Comando de compilacao: gcc lab07.c -o lab07 -Wall -Werror -ansi -pedantic
 */

#include <stdio.h>
#include <string.h>
#include "lab07.h"

/* Define o quantidade maxima de palavras no vetor */
#define QTD_MAX 12500
/* Define o tamanho maximo que uma palavra pode ter */
#define TAM_PALAVRA 20
/* Define quantidade maxima de frases */
#define QTD_MAX_FRASES 50
/* Define quantidade maxima de palavras por frase */
#define QTD_MAX_PALAVRAS_FRASE 250

void imprime_frase(char frase[], int tam){
	int i = 0;

	for (i = 0; i < tam; i ++ ){
		printf("%c", frase[i]);
	}
}

int adiciona_em_lista(char lista_de_palavras[][TAM_PALAVRA + 1], char palavra[], int n_palavras){
	strncpy( lista_de_palavras[ (n_palavras) ], palavra, strlen(palavra));
	n_palavras++;
	return n_palavras;
}

int verifica_em_lista( char lista_de_palavras[][TAM_PALAVRA + 1], char palavra[], int n_palavras){
	int i; 

	for ( i = 0; i < n_palavras; i ++ ){
		if( strcmp(lista_de_palavras[i], palavra) == 0 )
			return i;
	}
	return -1;
}

void imprime_lista (char lista_de_palavras[][TAM_PALAVRA + 1], int ocorrencias[], int n_palavras){
	int i;
	for ( i = 0 ; i < n_palavras; i ++ ) printf("%s ", lista_de_palavras[i]);
	printf("\n");
	for ( i = 0 ; i < n_palavras; i ++ ) printf("%d ", ocorrencias[i]);
	printf("\n");
}

int saida(char palavra[], char marcador[], int simultanea, int total ){
	int porcentagem = (int)(((float)simultanea/(float)total)*100); 
	if( porcentagem != 0){
		printf("<%s> se relaciona com <%s> em %d %% das ocorrencias.\n", palavra, marcador, porcentagem );
		return porcentagem;
	}
	return 0;
}

void saida_err(char palavra[]){
	printf("<%s> nao se relacionou com nenhum marcador temporal.\n", palavra);
}

int main(){
	/* Vetor de ocorrencias do tamanho do numero maximo de palavras possiveis */
	int ocorrencias[QTD_MAX];
	/* Matriz de palavras encontradas no texto */
	char lista_de_palavras[QTD_MAX][TAM_PALAVRA + 1];
	int n_palavras = 0;
	/* Matriz de marcadores temporais */
	char marcVetor[N_MARCADORES][TAM_MARCADORES];
	/* Matriz de ocorrencias */
	int matriz_ocorrencias[QTD_MAX_FRASES][QTD_MAX_PALAVRAS_FRASE];
	/* Vetor que armazena indice dos marcadores na lista */
	int indiceMarc[11];
	int porcentagem[11];
	/* Variaveis de leitura */
	char frase[250 + 1], palavra[TAM_PALAVRA + 1], c;
	int n_frases, i, j, k, indice_temp, indice_p_lista, pos_temp;
	int p_palavras;
	int ocorrencia_simultanea[11];
	/* Marcadores */
	int fim_de_leitura;
	int existe_simultanea;
	int maior_perc;

	/* Inicializando marcadores */
	strcpy(marcVetor[0], "ontem");
	strcpy(marcVetor[1], "hoje");
	strcpy(marcVetor[2], "amanha");
	strcpy(marcVetor[3], "agora");
	strcpy(marcVetor[4], "logo");
	strcpy(marcVetor[5], "cedo");
	strcpy(marcVetor[6], "tarde");
	strcpy(marcVetor[7], "breve");
	strcpy(marcVetor[8], "nunca");
	strcpy(marcVetor[9], "sempre");
	strcpy(marcVetor[10], "jamais");

	scanf("%d\n", &n_frases);

	/* Inicializa indices */
	for ( i = 0; i < N_MARCADORES; i++){
		indiceMarc[i] = -1;
	}

	for ( i = 0; i < n_frases; i ++ ){
		j = 0;

		/* Le frase */
		do {
			scanf("%c",&c);
			frase[j] = c;
			j++;
		} while (c != '\n' && c != '\0');

		indice_temp = 0;
		fim_de_leitura = 0;
		indice_temp = proxima_palavra( frase, palavra, indice_temp );

		while (!fim_de_leitura){
			/* Essa palavra ja existe na lista? */
			indice_p_lista = verifica_em_lista(lista_de_palavras, palavra, n_palavras);
			if( indice_p_lista != -1 ){
				matriz_ocorrencias[i][indice_p_lista]++;
				ocorrencias[indice_p_lista]++;
				/* printf("A palavra %s esta na posicao %d\n", palavra, indice_p_lista);*/
			}
			else {
				n_palavras = adiciona_em_lista(lista_de_palavras, palavra, n_palavras); /* Adiciona e atualiza o numero de palavras */
				/* printf("A palavra %s esta na posicao %d\n", palavra, n_palavras-1); */
				indice_p_lista = n_palavras -1;
				matriz_ocorrencias[i][indice_p_lista] = 1;
				ocorrencias[indice_p_lista] = 1;
			}
			
			/* Essa palavra eh um marcador? */ 
			pos_temp = verifica_marcador(marcVetor, palavra);
			/* printf("posTemp: %d\n", pos_temp); */
			if( pos_temp != -1)
				indiceMarc[pos_temp] = indice_p_lista; /* guarda o indice do marcador na lista */

			if( indice_temp == -1)
				fim_de_leitura = 1;
			else 
				indice_temp = proxima_palavra( frase, palavra, indice_temp );
			/*printf("palavra lida %s\n", palavra);*/
		}
	}


	scanf("%d\n", &p_palavras);
	for ( i = 0; i < p_palavras; i++){
		
		/* Le palavra */
		j = 0;
		do {
			scanf("%c",&c);
			if( c == '\n' || c == '\0'){
				palavra[j] = '\0';
			}
			else {
				palavra[j] = c;
			}
			j++;

		} while (c != '\n' && c != '\0');
		indice_p_lista = verifica_em_lista(lista_de_palavras, palavra, n_palavras);
		/*printf("INFO: palavra <%s> escolhida para comparacao. Seu indice eh %d na lista \n", palavra, indice_p_lista);
		printf("Ocorrencia total da palavra <%s>: %d\n", palavra, ocorrencias[indice_p_lista]);*/

		j = 0;
		maior_perc = 0;
		while ( j < N_MARCADORES ) {
			ocorrencia_simultanea[j] = 0;
			/*if( indiceMarc[j] >= 0)
				printf("Marcador: <%s>. Indice na lista: %d. Ocorrencias totais: %d \n", marcVetor[j], indiceMarc[j], ocorrencias[indiceMarc[j]]);
			*/
			for ( k = 0; k < n_frases; k ++ ){
				/*printf("<%s>:%d :: %d; <%s>:%d :: %d\n", marcVetor[j], i, matriz_ocorrencias[i][indiceMarc[j]], palavra, i, matriz_ocorrencias[i][indice_p_lista]);*/
				if( matriz_ocorrencias[k][indiceMarc[j]] != 0 && matriz_ocorrencias[k][indice_p_lista] != 0){
					ocorrencia_simultanea[j]++;
				}
			}
			porcentagem[j] = (int)(((float)ocorrencia_simultanea[j]/(float)ocorrencias[indice_p_lista])*100);
			if( maior_perc < porcentagem[j])
				maior_perc = porcentagem[j];
			j++;
		}
		existe_simultanea = 0;
		for ( j = 0; j < N_MARCADORES; j ++ ){
			if( maior_perc == porcentagem[j] && maior_perc != 0) {
				existe_simultanea = 1;
				saida(palavra, marcVetor[j], ocorrencia_simultanea[j], ocorrencias[indice_p_lista]);
			}
		}
		if( !existe_simultanea )
			saida_err(palavra);
	}

	/* Imprime lista de palavras */
	imprime_lista(lista_de_palavras, ocorrencias, n_palavras);

	return 0;
}

int proxima_palavra(char frase[], char palavra[], int inicio){
		int i = 0; 
		while( frase[inicio + i] != '\n' && frase[inicio + i] != '\0' && frase[inicio+i] != ' ' ){
			palavra[i] = frase[ inicio + i ];
			i++;
		}
		if( i == 0 )
			return -1;
		palavra[i] = '\0';
		minusculas(palavra);
		if( frase[inicio+i] == '\0' || frase[inicio + i] == '\n') /* Definindo o fim da frase */
			return -1;
		return inicio+i+1;

}

int verifica_marcador(char marcVetor[][TAM_MARCADORES], char palavra[]){
	int i; 

	for ( i = 0; i < N_MARCADORES; i ++ ){
		if( strcmp(marcVetor[i], palavra) == 0 )
			return i;
	}
	return -1;
}