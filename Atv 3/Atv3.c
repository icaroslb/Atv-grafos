#include <stdio.h>
#include <stdlib.h>

typedef struct Aresta {
	int x, y, pos;
	double peso;
}aresta;

typedef struct Vertice {
	int pos;
	double peso;
	aresta *naHeap;
}vertice;

typedef struct Heap {
	aresta **h;
	int quant;
}heap;

typedef struct Grafo {
	int x;
	double peso;
	struct Grafo *prox;
}grafo;

void inserirHeap (heap *, aresta *, vertice *);
aresta* removerHeap (heap *, vertice *);
void subirHeap(heap *, int, vertice *);
void descerHeap(heap *, int, vertice *);
void trocar(heap *, int, int, vertice *);

int main () {
	int quant, x, y;
	double peso;
	heap *h;
	vertice *v;
	grafo *g, *aux;
	aresta *ares, *novaAres;
	
	while(!scanf("n=%d", &quant)){getchar();}
	while(getchar() != ':'){}
	getchar();
	
	h = (heap*)malloc(sizeof(heap));
	h->h = (aresta**)malloc(sizeof(aresta*)*(quant+1));
	h->quant = 0;
	
	v = (vertice*)malloc(sizeof(vertice)*(quant+1));
	g = (grafo*)malloc(sizeof(grafo)*(quant+1));
	for(int i = 0; i < (quant+1); i++){
		v[i].pos = -1;
		v[i].peso = -1.0;
		v[i].naHeap = NULL;
		
		g[i].x = i;
		g[i].prox = NULL;
	}
	
	while(scanf("%d %d %lf", &x, &y, &peso) != EOF){
		aux = (grafo*)malloc(sizeof(grafo));
		aux->x = y;
		aux->peso = peso;
		aux->prox = g[x].prox;
		g[x].prox = aux;
	}
	
	ares = (aresta*)malloc(sizeof(aresta));
	ares->x = 1;
	ares->y = 1;
	ares->peso = 0.0;
	inserirHeap(h, ares, v);
	
	while(h->quant > 0){
		ares = removerHeap(h, v);
		x = ares->y;
		v[x].peso = ares->peso;
		aux = g+x;
		while(aux->prox != NULL){
			aux = aux->prox;
			y = aux->x;
			peso = aux->peso;
			if(v[y].peso == -1.0){
				if(v[y].naHeap == NULL){
					novaAres = (aresta*)malloc(sizeof(aresta));
					novaAres->x = x;
					novaAres->y = y;
					novaAres->peso = peso+ares->peso;
					v[y].naHeap = novaAres;
					inserirHeap(h, novaAres, v);
				}else{
					if((v[y].naHeap)->peso > peso+ares->peso){
						(v[y].naHeap)->peso = peso+ares->peso;
						(v[y].naHeap)->x = x;
						subirHeap(h, v[y].pos, v);
					}
				}
			}
		}
		
	}
	for(int i = 1; i < (quant+1); i++){
		if(v[i].peso != -1.0){
			printf("%d %.3lf\n", i, v[i].peso);
		}else{
			printf("%d %s\n", i, "INFINITO");
		}
	}
	
	return EXIT_SUCCESS;
}

void inserirHeap (heap *h, aresta *novo, vertice *v) {
	h->quant += 1;
	novo->pos = h->quant;
	v[novo->y].pos = h->quant;
	(h->h)[h->quant] = novo;
	subirHeap(h, h->quant, v);
}

aresta* removerHeap (heap *h, vertice *v) {
	aresta *liberar = (h->h)[1];
	
	(h->h)[1] = (h->h)[h->quant];
	h->quant -= 1;
	descerHeap(h, 1, v);
	
	return liberar;
}

void subirHeap(heap *h, int pos, vertice *v){
	if(pos == 1){
		return;
	}else{
		int pai = pos/2;
		
		if(((h->h)[pai])->peso > ((h->h)[pos])->peso){
			trocar(h, pos, pai, v);
			subirHeap(h, pai, v);
		}
	}
}

void descerHeap(heap *h, int pos, vertice *v){
	if(pos > h->quant){
		return;
	}else{
		int p = pos, e = pos*2, d = (pos*2)+1, menor;
		
		if(e < h->quant && ((h->h)[p])->peso > ((h->h)[e])->peso){
			menor = e;
		}else{
			menor = p;
		}
		if(d < h->quant && ((h->h)[menor])->peso > ((h->h)[d])->peso){
			menor = d;
		}
		if(menor == p){
			return;
		}else{
			trocar(h, p, menor, v);
			descerHeap(h, menor, v);
		}
	}
}

void trocar(heap *h, int pos1, int pos2, vertice *v){
	aresta *aux = (h->h)[pos1];
	
	(h->h)[pos1] = (h->h)[pos2];
	((h->h)[pos1])->pos = pos1;
	(h->h)[pos2] = aux;
	((h->h)[pos2])->pos = pos2;
	
	v[((h->h)[pos1])->y].pos = pos1;
	v[((h->h)[pos2])->y].pos = pos2;
}
