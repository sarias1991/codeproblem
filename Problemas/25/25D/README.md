# Problema 25D

En este link esta como se define el problema [Problem - 25D Roads not only in Berland](https://codeforces.com/problemset/problem/25/D "Roads not only in Berland")  

aqui vamos a explicar como se resolvio el problema.  

se creo una estructura, donde se guardaba el nodo, el padre y su destino, si tenia alguno
```cpp
struct calles {
	int ubi;
	int destino;
	int padre;
};
```
se definen las funciones de disjoint set union, las estandar, el buscar y unir dos conjuntos de elementos
```cpp
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
```
ahora vamos inizializar las variables a usar, se necesita guardad la cantidad de nodos que hay en el grafo en la variable n, y se tienen n-1 aristas, inicializamos el grafo donde cada nodo es su propio padre, por lo que no estan conectados, y despues con n-1 aristas,intentamos unir los nodos, sin que haya un ciclo, y como hacemos eso, si la funcion buscar(a) es igual a buscar(b) siendo a y b numeros, entonces se mete en una vector de conflictos, mientras que si son distintos, se pueden unir, aqui estan todas las variables y auxiliares que se usaron

```cpp
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
```
ahora creamos un conjunto, donde los numeros repetidos, no van a ingresar, ya que ya pertenece a el conjunto, entonces primero con la funcion buscar(i), e i siendo todos los nodos que existen [1,...,n], entonces busca los padres, si hay solo 1 entonces significa que todos estan conectados y no hay que hacer nada mas, pero en caso de que haya mas que uno, eso significa que hay conjuntos que no estan conectados, y hay que conectarlos con la funcion union(i,i+1), asi se puede dos conjuntos y representado al padre, se unen esos dos y hacen un solo conjunto y se guarda en respuestas
```cpp
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
```
finalmente, se hace un print de los uniones que tenian problemas, ya que eran redundantes y se cambian por las uniones de donde queda un solo conjunto
```cpp
printf("%ld\n", respuesta.size());
if(respuesta.size()>0){
	for(int i=0;i<respuesta.size();i++) {
		printf("%d %d %d %d\n",conflicto[i].ubi,conflicto[i].destino,respuesta[i].ubi,respuesta[i].destino);
	}
}
```
finalemnte asi queda el codigo completo:

```cpp
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
```
