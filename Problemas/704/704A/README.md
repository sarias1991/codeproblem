# Problema 704A

En este link esta como se define el problema [Problem - 704A - Thor](https://codeforces.com/contest/704/problem/A "Thor")  

aqui vamos a explicar como se resolvio el problema.  

se definen las funciones de BITree, las estandar, y una funcion similar a la construccion de BITree pero con un arreglo de puros ceros.  
```cpp
int getSum(int *BITree, int index) { 
	int sum = 0; 
	index = index + 1; 
 
	while (index>0) { 
		sum += BITree[index];  
		index -= index & (-index); 
    } 
    return sum; 
} 
  
void updateBIT(int *BITree, int n, int index, int val) { 
 
    index = index + 1; 
  
    while (index <= n) { 
    BITree[index] += val;
    index += index & (-index); 
    } 
} 
  
 
int *constructBITree(int *arr, int n) { 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0; 
  
    for (int i=0; i<n; i++) 
        updateBIT(BITree, n, i, arr[i]); 
 
  
    return BITree; 
} 
 
int *constructBITreeZeros(int n) { 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0;
 
    return BITree; 
} 
```
se crean las variables n, para la cantidad de aplicaciones, q para la cantidad de consultas, tipo para saber que tipo de accion hace thor, entre esta esta que la aplicacion genere una notificacion, que thor lea todas las notificaciones de la aplicacion x y que thor lea las primeras t notificaciones (esta permitido re leer las notificaciones), nuestro puntero BITree, en donde tenemos el arreglo donde lleva las cantidad de notificacion no leidas, evento es el momento en donde se crea una notificacion, se crea el evento, ordenado y sirve para saber cuantos eventos se han hecho todas las aplicaciones, leido son todas las notificaciones que a leido thor, ahora tenemos un vector y dentro de vector cada espacio es una cola donde guarda el momento en donde se creo la notificacion con la variable evento, ahora tenemos un cola llamada eventos, donde se guarda el evento que se genero y la aplicacion quien genero el evento en un pair, y finalmente y no tan imporante es el vector nevento, el arreglo de respuesta donde se agrega las notificaciones no leidas, para que se vea mas bien esteticamente y no imprima por pantalla al mismo tiempo que input, se creo este vector.  

```cpp
	int n,q,tipo,app,*BITree,evento=0,leido = 0;
	scanf("%d %d",&n,&q);
 
	vector<queue<int> > aplicaciones(n);
	queue<pair<int,int> > eventos;
	vector<int> neventos(q);
	BITree = constructBITreeZeros(n);
```
con el for se lee las consultas hechas, el tipo 1, agrega un evento a la appliacion app, en el vector de apliaciones, en la cola de eventos se indica que la aplicacion app creo un evento y guarda la informacion el la cola como (evento,app), el evento aumenta en 1 y en el BITree se actualiza con el indice de la aplicacion y agregando 1 a sus notificaciones.  

en el tipo 2, se indica que aplicacion tengo que leer todas sus notificaciones, entonces actualizo el BITree dando el indice de la aplicacion y la cantidad de notificaciones que se van a leer sabiendo que lo que se va a leer seria la cola completa de la aplicacion, usando la opcion size de la cola me dice cuantas notificaciones se van a leer, y despues saco todas las notificaciones de la aplicacion app.  

en el tipo 3, hay una variable leido, donde se guarda las primeras maximas notificaciones que se a leido en orden, si el valor de leido es mayor que app entonces ya e leido mas de lo que me dice thor, por lo que no se hace nada en esta intancia, pero si app es mayor que leido, significa que tengo que leer mas notificaciones, en este caso si app es distinto de 0 y la cantidad de notificacion no leidos es mayor a 0 entonces entra a un bucle para revisar los eventos de la cola, entonces reviso si en la cola de eventos, si se leyo esa notificacion o no, si no se leyo el evento, se actualiza el BITree y se le entrega el indice de la aplicacion y se le resta -1, se saca del vector de aplicaciones la notificacion, se saca de eventos indice del evento y la aplicacion quien creo la notificacion de la cola, y app disminuye en 1.  

finalmente y sin importar el tipo, se guarda las notificacion no leida en cada iteracion, para que cuando termine todos los input, imprima las respuesta de las notificaciones no leidas por thor.  
```cpp
	for(int i=0;i<q;i++){
		scanf("%d %d",&tipo,&app);
 
		if(tipo==1){
			aplicaciones[app-1].push(evento);
			eventos.push(make_pair(evento,app-1));
			evento++;
			updateBIT(BITree,n,app-1,1);
		}else if(tipo==2) {
			updateBIT(BITree,n,app-1,-1*aplicaciones[app-1].size());
			while(!aplicaciones[app-1].empty()) aplicaciones[app-1].pop();
		} else if(tipo==3) {
			leido = (leido >= app) ? leido : app; 
			while(app!=0 && getSum(BITree,n-1)>0){
				if(eventos.front().first<leido) {
					if(aplicaciones[eventos.front().second].front() ==  eventos.front().first) {
						updateBIT(BITree,n,eventos.front().second,-1);
						aplicaciones[eventos.front().second].pop();
						eventos.pop();
						app--;
					} else {
						eventos.pop();
						app--;
					}
				} else break;
			}
		}
		neventos[i] = getSum(BITree,n-1);
	}
	for(int i=0;i<neventos.size();i++) printf("%d\n", neventos[i]);
```
finalemnte asi queda el codigo completo:  

```cpp
#include <bits/stdc++.h>
#include <vector>
#include <queue>
 
using namespace std;
 
int getSum(int *BITree, int index) { 
	int sum = 0; 
	index = index + 1; 
 
	while (index>0) { 
		sum += BITree[index];  
		index -= index & (-index); 
    } 
    return sum; 
} 
  
void updateBIT(int *BITree, int n, int index, int val) { 
 
    index = index + 1; 
  
    while (index <= n) { 
    BITree[index] += val;
    index += index & (-index); 
    } 
} 
  
 
int *constructBITree(int *arr, int n) { 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0; 
  
    for (int i=0; i<n; i++) 
        updateBIT(BITree, n, i, arr[i]); 
 
  
    return BITree; 
} 
 
int *constructBITreeZeros(int n) { 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0;
 
    return BITree; 
} 
 
int main(int argc, char const *argv[]) {
	int n,q,tipo,app,*BITree,evento=0,leido = 0;
	scanf("%d %d",&n,&q);
 
	vector<queue<int> > aplicaciones(n);
	queue<pair<int,int> > eventos;
	vector<int> neventos(q);
	BITree = constructBITreeZeros(n);
 
	for(int i=0;i<q;i++){
		scanf("%d %d",&tipo,&app);
 
		if(tipo==1){
			aplicaciones[app-1].push(evento);
			eventos.push(make_pair(evento,app-1));
			evento++;
			updateBIT(BITree,n,app-1,1);
		}else if(tipo==2) {
			updateBIT(BITree,n,app-1,-1*aplicaciones[app-1].size());
			while(!aplicaciones[app-1].empty()) aplicaciones[app-1].pop();
		} else if(tipo==3) {
			leido = (leido >= app) ? leido : app; 
			while(app!=0 && getSum(BITree,n-1)>0){
				if(eventos.front().first<leido) {
					if(aplicaciones[eventos.front().second].front() ==  eventos.front().first) {
						updateBIT(BITree,n,eventos.front().second,-1);
						aplicaciones[eventos.front().second].pop();
						eventos.pop();
						app--;
					} else {
						eventos.pop();
						app--;
					}
				} else break;
			}
		}
		neventos[i] = getSum(BITree,n-1);
	}
	for(int i=0;i<neventos.size();i++) printf("%d\n", neventos[i]);
	return 0;
}
```