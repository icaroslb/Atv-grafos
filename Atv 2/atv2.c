#include <stdio.h>
#include <stdlib.h>

typedef struct Arv{
	float peso;
	int x, y;
	struct Arv *maior, *menor, *pai;
} arv;

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
	grafo **graf, *aux;
	arv *arvo = NULL, *novo, *ant;
	
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
	
	while(inseridos < quant){
		x = novo->x;
		y = novo->y;
		peso = novo->peso;
		//printf("%d %d %.1f\n", graf[x].val, graf[y].val, resul + peso);
		/*if(graf[x]->val != graf[y]->val){
			printf("%d %d %d %d\n", graf[x]->val, graf[y]->val, x, y);
			resul = resul + peso;
			graf[x]->quant += graf[y]->quant;
			aux = graf[y];
			graf[y] = graf[x];
			free(aux);
			printf("%d %d %d %d\n\n", graf[x]->val, graf[y]->val, x, y);
			//inseridos += 1;
		}*/
		ant = novo;
		novo = proxArv(novo);
		retiArv(ant);
		inseridos += 1;
	}
	printf("%.1f\n", resul);
	return EXIT_SUCCESS;
}

grafo** iniGrafo(int quant){
	grafo **graf, *aux;
	
	graf = (grafo**)malloc(sizeof(grafo)*quant);
	for(int i = 0; i < quant; i++){
		aux = (grafo*)malloc(sizeof(graf));
		aux->val = i;
		aux->quant = 0;
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
