/***********************************************************************
*  EXERCICIO DE PROGRAMACAO - LAB03
*  PAD: ALAN RICARDO GOMES 	RA: 145103
*
*  CHECKLIST: 
*  --- Apenas variaveis simples
*  --- Apenas desvios condicionais
*  --- Sem estruturas de repeticao aninhadas
*  --- Apenas stdio.h
*
*  ENTRADA: 
*  --- 4 numeros inteiros
*      --- A segundo menor joia presente no cofre 
*      --- O menor valor de joia em falta no universo
*      --- O segundo menor valor de joia em falta no universo
*      --- O valor da ordem de pagamento
*
*  SAIDA:
*  --- Lista contendo formato do pagamento
*    --- qtd de joias    valor da joia 
*
*  ALGORITMO: Descobrir qual a maior joia que ainda seja menor que o valor
*  da ordem de pagamento. Descobrir qual a maior joia que ainda seja menor 
*  que o ultimo valor encontrado. Se esses valores forem iguais, a joia 
*  estara em falta no universo e sera necessario utilizar uma de menor valor.
*  Caso contrario, utilizar o maximo possivel de joias desse valor e repetir
*  esse processo ateh o montante restante nao for maior que o valor da segunda
*  menor joia disponivel. Se ainda restar um montante, pagar com joias de 1 
*  galactonio real.
*
*  Compilar with gcc lab03.c -o lab03 -Wall -Werror -ansi -pedantic -lm 
*
************************************************************************/	

#include <stdio.h>

int main(){
	long snd_smaller, smallest_out, snd_smallest_out;
	long payment;
	long r_pg, r_pa;

	long c_jewellery = 1;
	long c_out, temp_out_n; 
	long rest; 

	long quo;

	/* read variables */
	scanf("%ld", &snd_smaller); 
	scanf("%ld", &smallest_out); 
	scanf("%ld", &snd_smallest_out); 
	scanf("%ld", &payment); 

	rest = payment;
	r_pg = snd_smaller;
	r_pa = snd_smallest_out - smallest_out;
	temp_out_n = ((payment - smallest_out)/r_pa);
	temp_out_n++;
	c_out = smallest_out + (temp_out_n -1)*r_pa;

	while (rest >= r_pg){
		c_jewellery *= r_pg;
		rest = rest/r_pg;
	}

	rest = payment;

	/* While my amount is greater than the second smaller jewellery */
	while( rest > snd_smaller ){

		/* Make the current out jewellery the closest possible to the current jewellery*/
		if( c_out > c_jewellery && c_out > smallest_out){
			temp_out_n = ((c_jewellery - smallest_out)/r_pa);
			temp_out_n++;
			c_out = smallest_out + (temp_out_n -1)*r_pa;
			if(c_out < smallest_out) 
				c_out = smallest_out;
		}

		/* quotient about how many current jewelleries I could use */
		quo = rest/c_jewellery;

		if( c_out == c_jewellery || quo == 0){ /* jewellery is out */
			c_jewellery = c_jewellery/r_pg;
		}

		/* When c_out is smaller than c_jewellery or already reached its bottom */
		else if ( (c_out < c_jewellery || c_out == smallest_out) && quo != 0 ){
			printf("%ld %ld\n", quo, c_jewellery);
			rest = rest%(quo*c_jewellery);
			c_jewellery = c_jewellery/r_pg;
		}
		
	}
	if ( rest != 0 ){
		printf("%ld %d\n", rest, 1);
	}
	return 0;
}