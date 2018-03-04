#include "lab09.h"
#include <stdio.h>
#include <string.h>

#define TAM_COL 3

int devolveIndiceReg( char *tok ){
	int indice = -1;
	if ( !strcmp(tok, "R1")){
		indice = 1;
	}
	else if ( !strcmp(tok, "R1")){
		indice = 1;
	}
	else if ( !strcmp(tok, "R2")){
		indice = 2;
	}
	else if ( !strcmp(tok, "R3")){
		indice = 3;
	}
	else if ( !strcmp(tok, "R4")){
		indice = 4;
	}
	else if ( !strcmp(tok, "R5")){
		indice = 5;
	}
	else if ( !strcmp(tok, "R6")){
		indice = 6;
	}
	else if ( !strcmp(tok, "R7")){
		indice = 7;
	}
	else if ( !strcmp(tok, "R8")){
		indice = 8;
	}
	else if ( !strcmp(tok, "R9")){
		indice = 9;
	}
	else if ( !strcmp(tok, "R10")){
		indice = 10;
	}
	else if ( !strcmp(tok, "R11")){
		indice = 11;
	}
	else if ( !strcmp(tok, "R12")){
		indice = 12;
	}
	return indice;
}

int atoi( char * tok ){
	int len, i;
	int multiplicador = 1;
	int soma = 0;
	int c_int;
	int negativo = 0;

	len = strlen(tok);
	if( *((char *) tok) == '-')
		negativo = 1;
	
	for ( i = len - 1; i >= negativo; i -- ){
		c_int = *((char *) tok + i)-48;
		soma = soma + multiplicador*c_int;
		multiplicador = multiplicador*10;
	}
	if( negativo )
		soma = -soma;
	return soma;
}

void mov(int *rd, int *ro, int *pc){
	/* printf("Arguments: %d, %d, %d\n", *rd, *ro, *pc); */
	*rd = *ro;
	return;
}

void moc(int *rd, int n, int *pc){
	/* printf("Arguments: %d, %d, %d\n", *rd, n, *pc); */
	*rd = n;
	return;
}

void add(int *rd, int *ro, int *pc){
	/* printf("Arguments: %d, %d, %d\n", *rd, *ro, *pc); */
	*rd = *rd + *ro;
	return;
}

/* Implementa instrução ADC
 * Recebe um apontador para um registrador, um inteiro n e um apontador para o Program Counter
 * Não retorna nada
 */
void adc(int *rd, int n, int *pc){
	/* printf("Arguments: %d, %d, %d\n", *rd, n, *pc);*/
	*rd = *rd + n;
	return;
}

/* Implementa instrução SUB
 * Recebe dois apontadores para registradores e um apontador para o Program Counter
 * Não retorna nada
 */
void sub(int *rd, int *ro, int *pc){
	/* printf("Arguments: %d, %d, %d\n", *rd, *ro, *pc);*/
	*rd = *rd - *ro;
	return;
}

/* Implementa instrução SUC
 * Recebe um apontador para um registrador, um inteiro n e um apontador para o Program Counter
 * Não retorna nada
 */
void suc(int *rd, int n, int *pc){
	/* printf("Arguments: %d, %d, %d\n", *rd, n, *pc);*/
	*rd = *rd - n;
	return;
}

/* Implementa instrução JMP
 * Recebe um apontador para um registrador, um inteiro n e um apontador para o Program Counter
 * Não retorna nada
 */
void jmp(int *rd, int n, int *pc){
	/*printf("Arguments: %d, %d, %d\n", *rd, n, *pc);*/
	if ( *rd >= 0 )
		*pc = *pc + n - 1; /* -1 eh fator de correcao */
	return;
}


/* Implementa instrução PTN
 * Recebe um inteiro valor e um apontador para o Program Counter
 * Não retorna nada
 */
void ptn(int valor, int *pc){
	printf("%d ", valor);
	return;
}

/* Implementa instrução PTC
 * Recebe um inteiro valor e um apontador para o Program Counter
 * Não retorna nada
 */
void ptc(int valor, int *pc){
	printf("%c", valor);
	return;
}

int main(){
	/* Variaveis de sistema */
	int n, R[12], PC = 0; 

	/* Contadores */
	int contador = 0, i = 0;

	/* Variaveis temporarias de leitura */
	char linha[151], c;
	char *delimitadores = " \t\r\v\f\n";
	char *tok;
	int mne, p1, p2;

	/* Matriz de instrucoes */
	int matriz[151][3];

	/* Le numero */
	contador = 0;
	do {
		scanf("%c", &c);
		/* O endereco recebe c como conteudo */
		*( linha + contador ) = c;
		if( c == '\n' || c == ' ')
			*( linha + contador ) = '\0';
		contador++;
	} while ( c != '\0' && c != '\n');
	n = atoi(linha);

	/* Para cada linha */
	for ( i = 0; i < n; i++ ){
		/* Le linha */
		contador = 0;
		do {
			scanf("%c", &c);
			/* O endereco recebe c como conteudo */
			*( (char *)linha + contador ) = c;
			if( c == '\n')
				*( (char *)linha + contador ) = '\0';
			contador++;
		} while ( c != '\0' && c != '\n' );

		/* tokeniza linha */
		tok = strtok(linha, delimitadores);
		while( tok != NULL ){			
			/* Parse codigo */
			if (!strcmp(tok, "MOV")){
				*( (int *)matriz + PC*TAM_COL ) = 0;

				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 2) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/*printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2);*/

				/* Atualiza PC */
				PC = PC + 1;

			}
			else if ( !strcmp( tok, "MOC") ){
				*( (int *)matriz + PC*TAM_COL ) = 1;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  

				*( (int *)matriz + PC*TAM_COL + 2) = atoi(tok); /* matriz[PC][2] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/*printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2);*/

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if ( !strcmp( tok, "ADD" ) ){
				*( (int *)matriz + PC*TAM_COL ) = 2;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 2) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2); */

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if( !strcmp( tok, "ADC" )){
				*( (int *)matriz + PC*TAM_COL ) = 3;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 2) = atoi(tok); /* matriz[PC][2] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2); */

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if( !strcmp( tok, "SUB" )){
				*( (int *)matriz + PC*TAM_COL ) = 4;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 2) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2);*/

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if( !strcmp( tok, "SUC" )){
				*( (int *)matriz + PC*TAM_COL ) = 5;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 2) = atoi(tok); /* matriz[PC][2] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2); */

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if( !strcmp( tok, "JMP" )){
				*( (int *)matriz + PC*TAM_COL ) = 6;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Le parametro 2 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 2) = atoi(tok); /* matriz[PC][2] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2); */

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if( !strcmp( tok, "PTN" )){
				*( (int *)matriz + PC*TAM_COL ) = 7;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				*( (int *)matriz + PC*TAM_COL + 2) = 0; /* matriz[PC][2] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2); */

				/* Atualiza PC */
				PC = PC + 1;
			}
			else if ( !strcmp( tok, "PTC")){
				*( (int *)matriz + PC*TAM_COL ) = 8;
				/* Le parametro 1 */
				tok = strtok(NULL, delimitadores);
				if ( *( (char *)tok + strlen(tok) - 1) == '\n') { 
					*( (char *)tok + strlen(tok) - 1) = '\0';
				}  
				*( (int *)matriz + PC*TAM_COL + 1) = devolveIndiceReg(tok); /* matriz[PC][1] */
				
				/* Mostra linha */
				mne = *( (int *)matriz + PC*TAM_COL );
				p1 = *( (int *)matriz + PC*TAM_COL + 1);
				p2 = *( (int *)matriz + PC*TAM_COL + 2);
				/* printf("%d: ( %d, %d, %d)\n", PC, mne, p1, p2); */

				/* Atualiza PC */
				PC = PC + 1;
			}
			tok = strtok(NULL, delimitadores);
		}
	}

	/* Roda o programa */
	for( i = 0; i < PC; i++ ){
		mne = *( (int *) matriz + i*TAM_COL );
		p1 = *( (int *) matriz + i*TAM_COL + 1 ); 
		p2 = *( (int *) matriz + i*TAM_COL + 2 );
		/*printf("mne: %d\n", mne);
		printf("p1: %d\n", p1);
		printf("p2: %d\n", p2);*/
		if( mne == 0 ){ /*mov*/
			mov( ((int *)R + (p1 - 1)), ((int *)R+(p2-1)), &i );
			/*printf("R[%d]: %d\n", p1, *((int *)R + (p1 - 1)));*/
		}
		else if ( mne == 1 ){/*moc*/
			moc( ((int *)R + (p1 - 1)), p2, &i );
			/*printf("R[%d]: %d\n", p1, *((int *)R + (p1 - 1)));*/
		}
		else if( mne == 2 ){ /* add */
			add( ((int *)R + (p1 - 1)), ((int *)R+(p2-1)), &i );
		}
		else if ( mne == 3 ){ /* adc */
			adc( ((int *)R + (p1 - 1)), p2, &i );
		}
		else if ( mne == 4 ) { /* sub */
			sub( ((int *)R + (p1 - 1)), ((int *)R+(p2-1)), &i );
		}
		else if ( mne == 5 ) { /* suc */
			suc( ((int *)R + (p1 - 1)), p2, &i );
		}
		else if ( mne == 6 ){ /*jmp */
			jmp( ((int *)R + (p1 - 1)), p2, &i);

		}
		else if ( mne == 7 ){ /* ptn */
			ptn ( *((int *)R + (p1 - 1)), &i );
		}
		else if ( mne == 8 ){ /* ptc */
			ptc ( *((int *)R + (p1 - 1)), &i );
		}

	}
	printf("\n");

	return 0;
}