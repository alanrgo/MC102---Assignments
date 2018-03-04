/*********************************************************
* RA: 145103  	Nome: ALAN RICARDO GOMES
*
* == LAB 11 == 
* Entrada: 
*  	-> n 		numero inteiro 
* Saida: 
*   -> Sim ou Nao, onde SIM significa que eu posso ganhar o jogo
* 
* Ao receber o valor de n, eh chamada uma funcao recursiva.
* Caso o numero recebido por essa funcao seja 42, eu ganho o jogo.
* Caso  seja menor, eu perco o jogo. 
* Caso n recebido seja multiplo de 2, eu removo metade de n e 
* invoco a mesma funcao. 
* Caso seja multiplo de 3 ou 4, e eu ja nao tenha encontrado uma 
* estrategia valida para ganhar o jogo, eu pego os dois ultimos digitos
* e removo o numero de Gremlins equivalente a multiplacao deles e reinvoco a funcao
* Caso eu nao tenha encontrado algum resultado positivo pra nenhum dos casos
* eu tento removendo 42 de n e reinvoco a funcao
*********************************************************/

#include <stdio.h> 

int primeiroUltimoDig(int n){
	return n%10;
}

int segundoUltimoDig( int n ){
	return (n/10)%10;
}

int removeGremlin(int n){
	int resultado = 0;
	int dig1 = 0, dig2 = 0;

	if( n > 42 ){
		if ( n % 2 == 0 ) {
			resultado = removeGremlin(n - (n/2));		
		}
		if ( !resultado && ( n%3 == 0 || n%4 == 0 ) ){
			
			dig1 = primeiroUltimoDig(n);
			dig2 = segundoUltimoDig(n);
			if ( dig1*dig2 != 0 )
				resultado = removeGremlin( n - dig1*dig2 );
		} 
		if( !resultado && ( n%5 == 0) ){
			resultado = removeGremlin(n - 42);
		}
	}
	if ( n == 42 )
		resultado = 1;
	if ( n < 42 )
		resultado = 0;
	return resultado;
}

int main(){
	int n, resultado;
	scanf("%d", &n);
	resultado = removeGremlin(n);
	
	if ( resultado == 0 ) 
		printf( "Nao\n" );
	else 
		printf( "Sim\n" );
	return 0;
}