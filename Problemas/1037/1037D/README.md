# Problema 1037D

En este link esta como se define el problema [problem 1037D - Valid BFS?](https://codeforces.com/problemset/problem/1037/D "Valid BFS?")  

aqui vamos a explicar como se resolvio el problema.  

aqui tenemos las variables que vamos a usar, para la cantidad de nodos usamos la variable n y para guardar las conexiones bidireccionales x y, lo guardamos en un map para las conexiones, y tenemos 3 colas, la cola de la respuesta a, una cola el cual mantiene los nodos que aun no conectamos como v y q es una cola donde tenemos el valor del nodo que estamos, y asi capturamos los datos:    
```cpp
int n,x,y,aux;
queue<int> q,v,a;
map<int,map<int,bool> > grafo;
scanf("%d",&n);
for(int i=0;i<n-1;i++){
	scanf("%d %d",&x,&y);
	grafo[x][y] = true;
	grafo[y][x] = true;
}
for(int i=0;i<n;i++){
	scanf("%d",&aux);
	a.push(aux);
}
```

despues hay una condicion, se debe que empiezar en el nodo 1 entonces en la cola a, el primer valor tiene que ser 1, por lo que si no imprime "No"  
```cpp
if(a.front()!=1) {
		printf("%s\n","No");
}
```
en el caso que el primer elemento de la cola a sea 1, se agrega a la cola q y se saca el elemento de de la cola a 
```cp
else {
	q.push(1);
	a.pop();
	#sigue el codigo aqui
}
```
dentro del else tenemos la condicion para terminar que la cola a este vacia
```cp
while(!a.empty()){
	#sigue el codigo aqui
}
```
ahora tenemos que ver si existe conexiones con el primer nodo de la cola q, entonces usamos el grafo y revisamos que conexiones tiene con el nodo y si tiene conexion, entonces revisamos si existe conexion del nodo el cual nos encontramos con el valor de nodo de la cola a, si existe, se elimina esa conexion de forma bidirecional y se agrega a la cola v de espera de nodos que tenemos que seguir buscado, y eliminar el elemento del frente de la cola a, en caso contrario, de no encontrar conexion con en nodo de la cola a significa que eso no es un BFS y imprimimos un "No" y dejamos de buscar, ahora si el grafo en el primer nodo de la cola q no tiene conexiones, eliminamos el primer nodo q y agregamos el primer nodo de la cola de espera v, lo agregamos a la cola q y lo sacamos de la cola v.  
```cp
if(grafo[q.front()].size()>0) {
	if(grafo[q.front()].find(a.front()) != grafo[q.front()].end()) {
		grafo[q.front()].erase(a.front());
		grafo[a.front()].erase(q.front());
		v.push(a.front());
		a.pop();

	} else {
		printf("%s\n","No");
		break;					
	}
} else {
	q.pop();
	q.push(v.front());
	v.pop();
}
```
y en el caso de sacar todos los elementos de la cola a, entonces por fin sabemos que el BFS es valido con las condiciones que dio el problema  
```cp
if(a.empty()) printf("%s\n","Yes");
```

finalmente asi queda el codigo  
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <queue>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {
	int n,x,y,aux;
	queue<int> q,v,a;
	map<int,map<int,bool> > grafo;
	scanf("%d",&n);
	for(int i=0;i<n-1;i++){
		scanf("%d %d",&x,&y);
		grafo[x][y] = true;
		grafo[y][x] = true;
	}
	for(int i=0;i<n;i++){
		scanf("%d",&aux);
		a.push(aux);
	}

	if(a.front()!=1) {
		printf("%s\n","No");
	} else {
		q.push(1);
		a.pop();
		while(!a.empty()){
			if(grafo[q.front()].size()>0) {
				if(grafo[q.front()].find(a.front()) != grafo[q.front()].end()) {
					grafo[q.front()].erase(a.front());
					grafo[a.front()].erase(q.front());
					v.push(a.front());
					a.pop();

				} else {
					printf("%s\n","No");
					break;					
				}

			} else {
				q.pop();
				q.push(v.front());
				v.pop();
			}
			
		}
	}
	if(a.empty()) printf("%s\n","Yes");
	return 0;
}
```