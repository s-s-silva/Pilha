/*
 * stefanie_lab06.c
 * AED1 - Lab 06
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct info{
	int conteudo;
	struct info *ant;
};
typedef struct info tipoinfo;

struct pilha{
	int tampilha;
	tipoinfo *topo;
};
typedef struct pilha tipopilha;

void inicia(tipopilha *pilhaAux){
	pilhaAux->tampilha =0;
	pilhaAux->topo = NULL;
};

void empilha (tipopilha *pilhaAux, int num){
	tipoinfo *aux = (tipoinfo*)malloc(sizeof(tipoinfo));
	aux->conteudo = num;

	if(pilhaAux->tampilha == 0){
		pilhaAux->topo = aux;
		aux->ant = NULL;
		pilhaAux->tampilha ++;
	}
	else{
		aux->ant = pilhaAux->topo;
		pilhaAux->topo = aux;
		pilhaAux->tampilha++;
	}
};

void imprime (tipopilha *pilhaAux){
	tipoinfo *aux = pilhaAux->topo;
	 while (aux != NULL){
        printf("%d", aux->conteudo);
        aux = aux->ant;
    }
};

int desempilha(tipopilha *pilhaAux){
    //RETIRADA APENAS DO TOPO!
    tipoinfo *no = (tipoinfo*)malloc(sizeof(tipoinfo));
    tipoinfo *aux = pilhaAux->topo;

    if(pilhaAux->tampilha == 0)
        exit(1);
    //-----------Retirada do último elemento--------------
    if(pilhaAux->tampilha == 1){
        aux->ant = NULL;
        pilhaAux->topo = NULL;
    }
    //-----------Retirada de qualquer outro elemento------
    else{
        pilhaAux->topo = aux->ant;
        aux->ant = pilhaAux->topo->ant;
    }
    pilhaAux->tampilha --;
};

int valorpilha (tipopilha *pilhaAux){ //Passa todos os valores da pilha para uma variável

    int i=0, valor=0;
    double exp, pot, tam;
    tam = pilhaAux->tampilha;

    for(i=0; i<= tam-1; i++){
        exp = tam- i;
        pot = pow(10, exp -1 );
        valor = valor + ((pilhaAux->topo->conteudo)*(pot));
        desempilha(&*pilhaAux);
    }
    return valor;
}

int complemento(tipopilha *pilhaAux, int bin){
    int i=0, cont=0, aux, resto =0;
    double exp, pot;
    aux = bin;

    //-----------TAMANHO DO NÚMERO BINÁRIO------------
    do
       {
           cont = cont + 1;
           aux = aux / 10;
       }
    while (aux != 0);

    //-----------CONVERSÃO-------------

    for(i=0; i<=cont-1; i++){
        resto = bin % 10;
        bin = bin /10;
        if (resto == 0)
            empilha(&*pilhaAux, 1);
        else
            empilha(&*pilhaAux, 0);
    }

};
int binparadec(tipopilha *pilhaAux, int bin){
    int cont=0, aux, i, dec, resto =0, p;
    double exp, pot;
    aux = bin;

    //-------------TAMANHO DO NÚMERO BINÁRIO-------------
    do
       {
           cont = cont + 1;
           aux = aux / 10;
       }
    while (aux != 0);

    //-------------TRANSFORMAÇÃO DE BIN PARA DEC-------------
    for(i=0; i<=cont; i++){
        p = pow(2, i);
        resto = bin % 10;
        bin = bin /10;
        dec = dec + (resto * p);
    }
    return dec;

};

int main(){
    int L, N, i=0,resto = 0;
    double pot=0, exp = 0;

	tipopilha minhapilha;
	inicia(&minhapilha);

	scanf("%d", &L);
	if (L < 1 || L>100)
        exit(1);
     for (i = 0; i<L; i++){
            scanf("%d", &N);
            printf("%d ", N);

            //---------DECIMAL PARA BINÁRIO (Nbin)----------

            while (N != 0){
            resto = N%2;
            N = N / 2;
                if (resto == 0)
                    empilha(&minhapilha, 0);
                else
                    empilha(&minhapilha, 1);
            }
            imprime(&minhapilha);

            //---------BINÁRIO COMPLEMENTO (Ntransfbin)----------

            complemento(&minhapilha, valorpilha(&minhapilha));
            printf(" ");
            imprime(&minhapilha);

            //---------BINÁRIO PARA DECIMAL (Ntransfdec)------------
            printf(" %d\n",binparadec(&minhapilha, valorpilha(&minhapilha)) );


    }

	return 0;
}
