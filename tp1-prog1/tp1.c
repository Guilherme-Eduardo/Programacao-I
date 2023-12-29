//Includes de bibliotecas
#include <stdio.h>						
#include <time.h>
#include <stdlib.h>
#include "racionais.h"

int main (){
								//Declaracao de variaveis e struct's
	srand (0);
    	int i, n, max;
	struct racional r1, r2, soma, sub, multi, div;
	do {
		printf ("Informe um valor n: 0 < n < 100: ");
		scanf ("%d", &n);
	} while (n > 100 ||  n < 0);

	do {
		printf ("Informe um valor de MAX: 0 < MAX < 30: ");
		scanf ("%d", &max);
	} while (max > 30 || max < 0);
								
	for (i = 1; i <= n; i++) {
		printf ("%d: ", i);
		r1 = sorteia_r (max);
		r2 = sorteia_r (max);
		imprime_r (r1);
		imprime_r (r2);
		if (!valido_r (r1) || !valido_r (r2)) {		//Verifica se o den eh nulo
			printf (" NUMERO INVALIDO\n ");
			return 1;		
		}
		else {
			soma = soma_r (r1, r2);
			sub = subtrai_r (r1, r2);
			multi = multiplica_r (r1, r2);
			div = divide_r (r1, r2);
			if (!valido_r (div)) {			//Verifica a divisao por den nulo
				printf (" DIVISAO INVALIDA\n ");
				return 1;
			}
			imprime_r (soma);
			imprime_r (sub);
			imprime_r (multi);
			imprime_r (div);
			printf ("\n");	
		}
	}
	
    return 0;
}
