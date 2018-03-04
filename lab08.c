/* gcc lab08.c -o lab08 -lm -Wall -Werror -ansi -pedantic */

#include "lab08.h"
#include <math.h>


#define max_points      500
#define max_operations  60000
#define max_style       256

#define M_PI 3.14159265358979323846

int main(){
	/* Variaveis para armazenar todas as operacoes */
	int    op_n[1];
	double op_p[max_operations][2];
	char   op_s[max_operations];
	/* Variaveis que armazenam um poligono */
	int    n[1];
	double p[max_points][2];
	char   s[max_style];
	/* Variaveis que armazenam um poligono copiado */
	int    n_copia[1];
	double p_copia[max_points][2];
	double rad;
	double x, y;

	int i, j;

	/* Lendo as operacoes */
	scan_svg(op_n,op_p,op_s);
	/* Operacoes armazenadas em (op_n,op_p,op_s) */
	
	/* Polígonos */
	scan_svg(n,p,s);
	/*print_svg(n,p,s);*/
	while(n[0]>=0){
		
		/* Operacoes de transformacao do poligono aqui */
		for ( i = 0; i < op_n[0]; i++ ){
			/*printf("%c ",op_s[i]);*/
			/*printf("(%.1f , %.1f)\n",op_p[i][0],op_p[i][1]);*/
			if ( op_s[i] == 'S' ){
				for ( j = 0; j < n_copia[0]; j ++ ){
					p_copia[j][0] = p_copia[j][0]*op_p[i][0];
					p_copia[j][1] = p_copia[j][1]*op_p[i][1];
				}
			}
			else if( op_s[i] == 'T' ){
				for ( j = 0; j < n_copia[0]; j ++ ){ /* Faz a mudanca em todos os pontos do poligono */
					p_copia[j][0] = p_copia[j][0] + op_p[i][0];
					p_copia[j][1] = p_copia[j][1] + op_p[i][1];
				}
			}			
			else if(op_s[i]=='R'){
				rad = op_p[i][0]*(M_PI/180.0);
				while (rad < 0 ) rad+=2*M_PI;
				for ( j = 0; j < n_copia[0]; j ++ ){/* Faz a mudanca em todos os pontos do poligono */
					x = p_copia[j][0];
					y = p_copia[j][1];
					p_copia[j][0] = x*cos(rad) - y*sin(rad);
					p_copia[j][1] = x*sin(rad) + y*cos(rad);
				}
			}
			else if ( op_s[i] == 'C' ){	
				if( i != 0 ){

					print_svg(n_copia,p_copia,s);

				}
				n_copia[0] = n[0];
				for ( j = 0; j < n_copia[0]; j ++ ){
					p_copia[j][0] = p[j][0];
					p_copia[j][1] = p[j][1];
				}

			}
			else
				printf("\n");
			if( i == op_n[0] - 1 )
				print_svg(n_copia,p_copia,s);
		}
		
		scan_svg(n,p,s);
	}
	
	close_svg();
	return 0;
}