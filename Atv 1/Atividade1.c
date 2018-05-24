#include <stdio.h>
#include <stdlib.h>

#define NAOATINGIDO 0
#define ATINGIDO 1
#define TERMINADO 2

typedef struct Vizinhos{
	int chave;
	struct Vizinhos *prox;
}vizinhos;

typedef struct Grafo{
	int chave, cor;
	struct Vizinhos *viz;
}grafo;

typedef struct Arvore{
	int chave;
	struct Arvore *maior, *menor, *pai;
}arvore;

arvore* bLargura(grafo *, int);
void inserirArvore(arvore *, arvore *);
void percorrer(grafo *, arvore *);
arvore* proximo(arvore *);


int main(){
	int n = 0;
	int x = 0, y = 0, entrada;
	arvore *arv;
	char c;
	
	while(getchar() != 'n'){}
	getchar();
	while((c = getchar()) != '\n'){n = (n*10)+(c-48);}
	while(getchar()!= ':'){}

	grafo graf[n], *auxGraf;
	for(int i = 0; i < n; i++){
		auxGraf = (grafo*)malloc(sizeof(grafo));
		auxGraf->chave = i + 1;
		auxGraf->cor = NAOATINGIDO;
		auxGraf->viz = NULL;
		graf[i] = *auxGraf;
	}
	
	getchar();
	vizinhos *auxViz;
	for(entrada = getchar(); entrada != EOF; entrada = getchar()){
		do{
			x = (x * 10) + (entrada - 48);
		}while((entrada = getchar()) != ' ');
		while((entrada = getchar()) != '\n'){
			y = (y * 10) + (entrada - 48);
		}
		auxViz = (graf[x-1]).viz;
		(graf[x-1]).viz = (vizinhos*)malloc(sizeof(vizinhos));
		(graf[x-1]).viz->chave = y;
		(graf[x-1]).viz->prox = auxViz;
		
		auxViz = (graf[y-1]).viz;
		(graf[y-1]).viz = (vizinhos*)malloc(sizeof(vizinhos));
		(graf[y-1]).viz->chave = x;
		(graf[y-1]).viz->prox = auxViz;
		x = 0; y = 0;
	}
	for(int i = 0; i < n; i++){
		if((graf[i]).cor != TERMINADO){
			arv = bLargura(graf, i);
			percorrer(graf, arv);
		}
	}
	return EXIT_SUCCESS;
}

arvore* bLargura(grafo *graf, int ini){
	vizinhos *atual = NULL, *fut = NULL, *aux = NULL, *novo = NULL, *liberar = NULL;
	arvore *arv, *auxArv;
	graf[ini].cor = ATINGIDO;
	atual = (vizinhos*)malloc(sizeof(vizinhos));
	atual->chave = ini + 1;
	atual->prox = NULL;
	
	arv = (arvore*)malloc(sizeof(arvore));
	arv->chave = ini + 1;
	arv->pai = NULL;
	arv->maior = NULL;
	arv->menor = NULL;
	
	while(atual != NULL){
		aux = (graf[(atual->chave)-1]).viz;
		while(aux != NULL){
			if((graf[(aux->chave)-1]).cor == NAOATINGIDO){
				(graf[(aux->chave)-1]).cor = ATINGIDO;
				auxArv = (arvore*)malloc(sizeof(arvore));
				auxArv->chave = aux->chave;
				auxArv->maior = NULL;
				auxArv->menor = NULL;
				inserirArvore(arv, auxArv);
				
				novo = (vizinhos*)malloc(sizeof(vizinhos));
				novo->chave = aux->chave;
				novo->prox = fut;
				fut = novo;
			}
			aux = aux->prox;
		}
		liberar = atual;
		atual = atual->prox;
		free(liberar);
		
		if(atual == NULL){
			atual = fut;
			fut = NULL;
		}
	}
	
	return arv;
}

void inserirArvore(arvore *arv, arvore *novo){
	arvore *ant;
	
	while(arv != NULL){
		ant = arv;
		if(arv->chave < novo->chave){
			arv = arv->maior;
		}else{
			arv = arv->menor;
		}
	}
	novo->pai = ant;
	if(ant->chave < novo->chave){
		ant->maior = novo;
	}else{
		ant->menor = novo;
	}
}

void percorrer(grafo *graf, arvore *arv){
	arvore *aux1 = arv, *aux2;
	
	while(aux1->menor != NULL){
		aux1 = arv->menor;
	}
	
	printf("%d", aux1->chave);
	do{
		aux2 = aux1;
		aux1 = proximo(aux1);
		if(aux1 != NULL){
			(graf[(aux1->chave)-1]).cor = TERMINADO;
			printf(" %d", aux1->chave);
		}
		if(aux2 != NULL && aux2->maior != NULL && aux2->pai == NULL){(aux2->maior)->pai = NULL;}
		free(aux2);
	}while(aux1 != NULL);
	printf("\n");
}


arvore* proximo(arvore *arv){
	arvore *aux;
	
	if(arv != NULL){
		if(arv->maior != NULL){
			aux = arv->maior;
			while(aux->menor != NULL){
				aux = aux->menor;
			}
		}else{
			aux = arv->pai;
			while(aux != NULL && aux->maior == arv){
				arv = aux;
				aux = aux->pai;
			}
		}
	}	
	return aux;
}
