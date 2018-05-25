#include <stdio.h>
#include <stdlib.h>

typedef struct Arv{
	float peso;
	int x, y;
	struct Arv *maior, *menor, *pai;
} arv;

typedef struct Viz{
	int val;
	struct Viz *prox;
}viz;

typedef struct Grafo{
	int val, quant;
	viz *prox;
} grafo;


grafo** iniGrafo(int);
void adiArv(arv **, arv *);
arv* proxArv(arv *);
void retiArv(arv *);

int main(){
	int quant, x, y, inseridos = 0;
	float peso, resul = 0;
	grafo **graf, *aux, *libe;
	arv *arvo = NULL, *novo, *ant;
	viz *vizProx, *auxViz;
	
	while(!scanf("n=%d", &quant)){getchar();}
	while(getchar() != ':'){}
	getchar();
	
	graf = iniGrafo(quant);
	
	while(scanf("%d %d %f", &x, &y, &peso) != EOF){
		novo = (arv*)malloc(sizeof(arv));
		novo->peso = peso;
		novo->x = x-1;
		novo->y = y-1;
		novo->pai = NULL;
		novo->menor = NULL;
		novo->maior = NULL;
		adiArv(&arvo, novo);
	}
	
	novo = arvo;
	while(novo->menor != NULL){
		novo = novo->menor;
	}
	quant -= 1;
	while(inseridos < quant){
		x = novo->x;
		y = novo->y;
		peso = novo->peso;
		if(graf[x]->val != graf[y]->val){
			resul = resul + peso;
			if(graf[x]->quant >= graf[y]->quant){
				vizProx = graf[y]->prox;
				graf[x]->quant += graf[y]->quant;
				libe = graf[y];
				while(vizProx != NULL){
					graf[vizProx->val] = graf[x];
					if(vizProx->prox == NULL){
						auxViz = vizProx;
					}
					vizProx = vizProx->prox;
				}
				auxViz->prox = graf[x]->prox;
				graf[x]->prox = libe->prox;
			}else{
				vizProx = graf[x]->prox;
				graf[y]->quant += graf[x]->quant;
				libe = graf[x];
				while(vizProx != NULL){
					graf[vizProx->val] = graf[y];
					if(vizProx->prox == NULL){
						auxViz = vizProx;
					}
					vizProx = vizProx->prox;
				}
				auxViz->prox = graf[y]->prox;
				graf[y]->prox = libe->prox;
			}
			free(libe);
			inseridos += 1;
		}
		ant = novo;
		novo = proxArv(novo);
		retiArv(ant);
	}
	printf("%.1f\n", resul);
	return EXIT_SUCCESS;
}

grafo** iniGrafo(int quant){
	grafo **graf, *aux;
	viz *vert;
	
	graf = (grafo**)malloc(sizeof(grafo)*quant);
	for(int i = 0; i < quant; i++){
		aux = (grafo*)malloc(sizeof(graf));
		aux->val = i;
		aux->quant = 1;
		vert = (viz*)malloc(sizeof(viz));
		vert->val = i;
		vert->prox = NULL;
		aux->prox = vert;
		graf[i] = aux;
	}
	return graf;
}

void adiArv(arv ** arvo, arv *novo){	
	if(*arvo == NULL){
		*arvo = novo;
		novo->pai = NULL;
	}else{
		arv *aux = *arvo, *ant = NULL;
		
		while(aux != NULL){
			ant = aux;
			if(novo->peso < aux->peso){
				aux = aux->menor;
			}else{
				aux = aux->maior;
			}
		}
		
		novo->pai = ant;
		if(novo->peso < ant->peso){
			ant->menor = novo;
		}else{
			ant->maior = novo;
		}
	}
}

arv* proxArv(arv *ant){
	arv *aux;
	
	if(ant->maior != NULL){
		ant = ant->maior;
		while(ant->menor != NULL){
			ant = ant->menor;
		}
	}else{
		aux = ant->pai;
		while(aux != NULL && aux->maior == ant){
			ant = aux;
			aux = aux->pai;
		}
		if(aux != NULL){
			ant = aux;
		}
	}
	
	
	return ant;
}

void retiArv(arv *reti){	
	if(reti->pai != NULL){
		(reti->pai)->menor = reti->maior;
		if(reti->maior != NULL){
			(reti->maior)->pai = reti->pai;
		}
	}else{
		(reti->maior)->pai = NULL;
	}
	
	free(reti);
}
