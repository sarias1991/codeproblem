#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <queue>
#include <set>
#include <iterator> 

using namespace std;

struct calles {
	int ubi;
	int destino;
	int padre;
};

int buscar(struct calles *autopistas,int al) {
	if(autopistas[al].padre == al) return al;
	else return buscar(autopistas,autopistas[al].padre);
}

void uniones(struct calles *autopistas,int al,int bl) {
	int yraiz,xraiz;
	xraiz = buscar(autopistas,al);
	yraiz = buscar(autopistas,bl);
	autopistas[xraiz].padre = yraiz;
	autopistas[xraiz].destino =bl;
}

int main(int argc, char const *argv[]) {
	int n,a,b;
	struct calles *cls,aux;
	vector<struct calles> conflicto,respuesta;
	set <int> padres;
	set <int> :: iterator itr;
	scanf("%d",&n);
	cls = (struct calles *) malloc((n+1)*sizeof(struct calles));
	for(int i=0;i<n+1;i++) {
		cls[i].ubi = i;
		cls[i].destino = -1;
		cls[i].padre = i;
	}
	for(int i=0;i<n-1;i++) {
		scanf("%d %d",&a,&b);
		if(buscar(cls,a)!=buscar(cls,b)) {
			uniones(cls,a,b);	
		} else {
			aux.ubi = a;
			aux.destino = b;
			aux.padre =a;
			conflicto.push_back(aux);
		}
		
	}
	
	for(int i=1;i<n+1;i++) {
		padres.insert(buscar(cls,i));
	}
	for(itr = padres.begin(); itr != padres.end();) { 
		aux.ubi = *itr;
		++itr;
		if(itr == padres.end()) break;
		aux.destino = *itr;
		aux.padre = *itr;
		respuesta.push_back(aux);
	}

	printf("%ld\n", respuesta.size());
	if(respuesta.size()>0){
		for(int i=0;i<respuesta.size();i++) {
			printf("%d %d %d %d\n",conflicto[i].ubi,conflicto[i].destino,respuesta[i].ubi,respuesta[i].destino);
		}
	}
	



	return 0;
}