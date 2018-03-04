#include <stdio.h> 

int main(){
	int dir_f[1000], dist_f[1000], dir_m[1000], dist_m[1000], dir_rev[1000], dist_rev[1000];
	int n_femea, n_macho;

	/* Variaveis de compatibilidade */
	int rotacaof1, dir_1, dir_2, incompativel, rev_incompativel;
	int virada_femea, virada_macho, diferenca;
	float proporcao, valor_abs;
	int rotacaof3;

	int i, j;

	/* Fase 1 - variaveis */
	float posX, posY, delta_pos, tolerancia = 0.0001;
	float fatorX, fatorY, yOK, xOK;
	int fase1_definida = 0;

	/* Fase 2 - variaveis */
	int fase2f, fase2m;
	int fase2_definida = 0;

	/* Fase 3 - variaveis */
	int fase3f, fase3m;

	/* Leitura */
	scanf("%d %d", &n_femea, &n_macho);

	for ( i = 0; i < n_femea; i++ ){
		scanf("%d %d", &dir_f[i], &dist_f[i]);
	}
	for ( i = 0; i < n_macho; i++ ){
		scanf("%d %d", &dir_m[i], &dist_m[i]);
		dir_rev[n_macho-1-i] = dir_m[i];
		dist_rev[n_macho-1-i] = dist_m[i];
	}
	/* Inicializacao de variaveis */
	posX = 0;
	posY = 0;
	delta_pos = 0;
	tolerancia = 0.0001;
	xOK = 0;
	yOK = 0;
	fase1_definida = 0;
	fase2_definida = 0;

	for ( i = 0; i < n_femea; i++ ){
		/* Define primeira fase femea*/
		if( fase1_definida == 0 ){
			/* [...]começa a primeira fase da dança da fêmea, que termina quando ela volta, após alguns passos, 
			ao ponto de partida da dança*/
			fatorX = 0;
			fatorY = 0;
			xOK = 0;
			yOK = 0;

			switch(dir_f[i]){
				case 0:
					fatorY = 1;
					break;
				case 1: 
					fatorY = 0.7071;
					fatorX = 0.7071;
					break;
				case 2:
					fatorX = 1;
					break;		
				case 3:
					fatorY = -0.7071;
					fatorX = 0.7071;
					break;
				case 4:
					fatorY = -1;
					break;
				case 5: 
					fatorY = -0.7071;
					fatorX = -0.7071;
					break;
				case 6:
					fatorX = -1;
					break;
				case 7: 
					fatorY = 0.7071;
					fatorX = -0.7071;
					break;
			}
			posY = posY + ((float)dist_f[i])*fatorY;
			posX = posX + ((float)dist_f[i])*fatorX;

			delta_pos = posY;
			if( delta_pos < 0 )
				delta_pos = - delta_pos;
			if( delta_pos < tolerancia ){
				yOK = 1;
			}
			delta_pos = posX;
			if( delta_pos < 0 )
				delta_pos = - delta_pos;
			if( delta_pos < tolerancia ){
				xOK = 1;
			}
			if( xOK == 1 && yOK == 1 ){
				fase1_definida = 1;
				fase2f = i + 1;
			}	
		}
		if( fase2_definida == 0 && fase1_definida == 1){
			if( dir_f[i+1] == (dir_f[i]+4)%8 && dist_f[i+1] > dist_f[i] ){
				fase2_definida = 1;
				fase3f = i + 2;
			}
		}
	}

	posX = 0;
	posY = 0;
	delta_pos = 0;
	tolerancia = 0.0001;
	xOK = 0;
	yOK = 0;
	fase1_definida = 0;
	 fase2_definida = 0;

	for ( i = 0; i < n_macho; i++ ){
		/* Define primeira fase femea*/
		if( fase1_definida == 0 ){
			/* [...]começa a primeira fase da dança da fêmea, que termina quando ela volta, após alguns passos, 
			ao ponto de partida da dança*/
			fatorX = 0;
			fatorY = 0;
			xOK = 0;
			yOK = 0;

			switch(dir_m[i]){
				case 0:
					fatorY = 1;
					break;
				case 1: 
					fatorY = 0.7071;
					fatorX = 0.7071;
					break;
				case 2:
					fatorX = 1;
					break;		
				case 3:
					fatorY = -0.7071;
					fatorX = 0.7071;
					break;
				case 4:
					fatorY = -1;
					break;
				case 5: 
					fatorY = -0.7071;
					fatorX = -0.7071;
					break;
				case 6:
					fatorX = -1;
					break;
				case 7: 
					fatorY = 0.7071;
					fatorX = -0.7071;
					break;
			}
			posY = posY + (float)dist_m[i]*fatorY;
			posX = posX + (float)dist_m[i]*fatorX;

			delta_pos = posY;
			if( delta_pos < 0 )
				delta_pos = - delta_pos;
			if( delta_pos < tolerancia ){
				yOK = 1;
			}
			delta_pos = posX;
			if( delta_pos < 0 )
				delta_pos = - delta_pos;
			if( delta_pos < tolerancia ){
				xOK = 1;
			}
			if( xOK == 1 && yOK == 1 ){
				fase1_definida = 1;
				fase2m = i + 1;
			}	
		}
		if( fase2_definida == 0 ){
			if( dir_m[i+1] == (dir_m[i]+4)%8 && dist_m[i+1] > dist_m[i] ){
				fase2_definida = 1;
				fase3m = i + 2;
			}
		}
	}

	incompativel = 0;
	rev_incompativel = 0;

	/* Verificacao de compatibilidade fase 1 */
	/* Na primeira fase, a dança do macho deve ter a mesma forma da dança da fêmea, 
	não importando se for rotacionada no espaço. O macho deve fazer sempre passos maiores do que os da fêmea, 
	mas mantendo a proporcionalidade entre as amplitudes dos passos sucessivos. 
	Os ângulos entre passos também devem ser preservados.*/
	rotacaof1 = dir_m[0] - dir_f[0];
	proporcao = dist_m[0]/dist_f[0];
	
	if( rotacaof1 <= -4 ) 
		rotacaof1 = rotacaof1 + 8;

	for ( i = 0; i < fase2f; i ++ ){
		dir_1 = dir_f[i];

		if( rotacaof1 <= 0 ){
			dir_2 = (dir_1 + rotacaof1 + 8)%8;
		}
		else {
			dir_2 = (rotacaof1 + dir_1)%8;
		}

		if( dir_2 != dir_m[i] || ((dist_m[i]/dist_f[i]) - proporcao) > tolerancia){
			incompativel = 1;
		}
	}

	/* Verificacao de compatibilidade fase 2 */
	/* A segunda fase é mais livre. O macho só não pode ultrapassar a quantidade de passos da fêmea nesta fase. 
	O macho marca da mesma maneira que a fêmea a separação entre a segunda e a terceira fases.*/
	if( incompativel == 0 ){
		if( fase3f - fase2f < fase3m - fase2m )
			incompativel = 1;
	}

	/* Verificacao de compatibilidade fase 3 */ 
	/* Na terceira fase, voltam a ser relevantes para a fêmea as proporções entre as amplitudes dos passos dentro dessa fase, 
	mas os ângulos não precisam mais ser mantidos com tanta precisão: a fêmea não se incomodará se o macho errar o ângulo em até 
	60°, para mais ou para menos, a cada virada. O macho também sai voando ao final da sua terceira fase. 
	A fêmea rejeita machos cujo número de passos na terceira fase não coincida com o número de passos de sua própria 
	terceira fase. */
	proporcao = (float) dist_m[fase3m]/ (float)dist_f[fase3f];
	if( n_femea - fase3f != n_macho - fase3m )
		incompativel = 1;

	if( incompativel == 0 ){
		for ( i = fase3f, j = fase3m; i < n_femea; i++, j ++ ){
			
			/* virada */
			if( i < n_femea - 1 ){
				virada_femea = dir_f[i + 1] - dir_f[i];
				virada_macho = dir_m[j + 1] - dir_m[j];

				/* Tratamento dos valores de virada*/
				if ( virada_femea <= -4 )
					virada_femea = virada_femea + 8;
				if ( virada_femea > 4 )
					virada_femea = virada_femea - 8;
				if( virada_macho <= -4 )
					virada_macho = virada_macho + 8;
				if( virada_macho > 4 )
					virada_macho = virada_macho - 8;

				diferenca = virada_macho - virada_femea;

				if ( diferenca <= -4 )
					diferenca = diferenca + 8;
				if ( diferenca > 4 )
					diferenca = diferenca - 8;
				if ( diferenca < 0 )
					diferenca = - diferenca;
				if ( diferenca > 1 ){
					incompativel = 1;
				}
			}

			/* proporcao */
			valor_abs = (float) dist_m[j]/(float)dist_f[i];
			valor_abs = valor_abs - proporcao;
			if ( valor_abs > tolerancia ){
				incompativel = 1;
			}
		}
	}

	if( incompativel == 1 ){
		posX = 0;
		posY = 0;
		delta_pos = 0;
		tolerancia = 0.0001;
		xOK = 0;
		yOK = 0;
		for ( i = 0; i < n_macho; i++ ){
			/* Define primeira fase femea*/
			if( fase1_definida == 0 ){
				/* [...]começa a primeira fase da dança da fêmea, que termina quando ela volta, após alguns passos, 
				ao ponto de partida da dança*/
				fatorX = 0;
				fatorY = 0;
				xOK = 0;
				yOK = 0;

				switch(dir_rev[i]){
					case 0:
						fatorY = 1;
						break;
					case 1: 
						fatorY = 0.7071;
						fatorX = 0.7071;
						break;
					case 2:
						fatorX = 1;
						break;		
					case 3:
						fatorY = -0.7071;
						fatorX = 0.7071;
						break;
					case 4:
						fatorY = -1;
						break;
					case 5: 
						fatorY = -0.7071;
						fatorX = -0.7071;
						break;
					case 6:
						fatorX = -1;
						break;
					case 7: 
						fatorY = 0.7071;
						fatorX = -0.7071;
						break;
				}
				posY = posY + dist_rev[i]*fatorY;
				posX = posX + dist_rev[i]*fatorX;

				delta_pos = posY;
				if( delta_pos < 0 )
					delta_pos = - delta_pos;
				if( delta_pos < tolerancia ){
					yOK = 1;
				}
				delta_pos = posX;
				if( delta_pos < 0 )
					delta_pos = - delta_pos;
				if( delta_pos < tolerancia ){
					xOK = 1;
				}
				if( xOK == 1 && yOK == 1 ){
					fase1_definida = 1;
					fase2m = i + 1;
				}	
			}
			if( fase2_definida == 0 ){
				if( dir_rev[i+1] == (dir_rev[i]+4)%8 && dist_rev[i+1] > dist_rev[i] ){
					fase2_definida = 1;
					fase3m = i + 2;
				}
			}
		}

		rotacaof1 = dir_rev[0] - dir_f[0];
		proporcao = dist_rev[0]/dist_f[0];
		
		if( rotacaof1 <= -4 ) 
			rotacaof1 = rotacaof1 + 8;

		for ( i = 0; i < fase2f; i ++ ){
			dir_1 = dir_f[i];

			if( rotacaof1 <= 0 ){
				dir_2 = (dir_1 + rotacaof1 + 8)%8;
			}
			else {
				dir_2 = (rotacaof1 + dir_1)%8;
			}

			if( dir_2 != dir_rev[i] || ((dist_rev[i]/dist_f[i]) - proporcao) > tolerancia){
				rev_incompativel = 1;
			}
		}

		/* Verificacao de compatibilidade fase 2 */
		/* A segunda fase é mais livre. O macho só não pode ultrapassar a quantidade de passos da fêmea nesta fase. 
		O macho marca da mesma maneira que a fêmea a separação entre a segunda e a terceira fases.*/
		if( rev_incompativel == 0 ){
			if( fase3f - fase2f < fase3m - fase2m )
				rev_incompativel = 1;
		}


		/* Verificacao de compatibilidade fase 3 */ 
		/* Na terceira fase, voltam a ser relevantes para a fêmea as proporções entre as amplitudes dos passos dentro dessa fase, 
		mas os ângulos não precisam mais ser mantidos com tanta precisão: a fêmea não se incomodará se o macho errar o ângulo em até 
		60°, para mais ou para menos, a cada virada. O macho também sai voando ao final da sua terceira fase. 
		A fêmea rejeita machos cujo número de passos na terceira fase não coincida com o número de passos de sua própria 
		terceira fase. */
		proporcao = (float) dist_rev[fase3m]/ (float)dist_f[fase3f];
		if( n_femea - fase3f != n_macho - fase3m )
			rev_incompativel = 1;

		if( rev_incompativel == 0 ){
			for ( i = fase3f, j = fase3m; i < n_femea; i++, j ++ ){
				
				/* virada */
				if( i < n_femea - 1 ){
					virada_femea = dir_f[i + 1] - dir_f[i];
					virada_macho = dir_rev[j + 1] - dir_rev[j];

					/* Tratamento dos valores de virada*/
					if ( virada_femea <= -4 )
						virada_femea = virada_femea + 8;
					if ( virada_femea > 4 )
						virada_femea = virada_femea - 8;
					if( virada_macho <= -4 )
						virada_macho = virada_macho + 8;
					if( virada_macho > 4 )
						virada_macho = virada_macho - 8;

					diferenca = virada_macho - virada_femea;

					if ( diferenca <= -4 )
						diferenca = diferenca + 8;
					if ( diferenca > 4 )
						diferenca = diferenca - 8;
					if ( diferenca < 0 )
						diferenca = - diferenca;
					if ( diferenca > 1 ){
						rev_incompativel = 1;
					}
				}

				/* proporcao */
				valor_abs = dist_rev[j]/dist_f[i];
				valor_abs = valor_abs - proporcao;
				if ( valor_abs > tolerancia ){
					rev_incompativel = 1;
				}
			}
		}
	}

	if( incompativel == 0)
		printf("Compatibilidade natural.\n");
	else if ( rev_incompativel == 0 )
		printf("Reverso tem compatibilidade.\n");
	else
		printf("Incompatibilidade total.\n");

	return 0;
}