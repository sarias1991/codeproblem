# Problema 820

En este link esta como se define el problema [Problem - 820 Internet Bandwidth](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=761 "Internet Bandwidth")  

aqui vamos a explicar como se resolvio el problema.  

n son la cantidad de nodos que hay en la red, el nodo inicial, el nodo final, la cantidad de aristas, y el flujo de red c de aristas entre nodos (s-t), el flujo maximo.
```cpp
	int n,inicio,final,aristas,s,t,c,flujoMaximo,red=1;	
	vector<int> respuesta;
```
aqui se ingresa por pantalla la cantidad de nodos en el grafo, por cada iteracion, si el n es 0 se termina de iterar, conexiones es una matriz de nxn donde estan el flujo entre nodos, la matriz se inicializa en 0, despues se ingresa por pantalla el nodo inicial, nodo final y la cantidad de aristas que tiene el grafo.  

finalmente se agrega a la matriz de conexiones la el flujo que puede pasar entre esos dos nodos, nodo s al nodo t puede pasar un flujo de c, y ya que es una red de internet tambien se puede el inverso, el nodo t al nodo s con el flujo de c.  

se utiliza la funcion maxflow, con los parametros nodo de inicio, nodo final, la cantidad de nodos en el grafo, y los flujos entre nodos.  
```cpp
	while(true) {
		cin >> n;
		if(n==0) break;

		vector<vector<int> > conexiones(n,vector<int>(n,0));

		cin >> inicio >> final >> aristas;

		for(int i=0;i<aristas;i++) {
			cin >> s >> t >> c;
			conexiones[s-1][t-1] += c;
			conexiones[t-1][s-1] += c;
		}

		flujoMaximo = maxflow(inicio-1,final-1,n,conexiones);
```
se crean las variables,flujo_ruta,nodo1 y nodo2 que es para decir que voy del nodo1 al nodo2, y flujo maximo que puede llegar al nodo final que se inicializa en 0, ya que si no existe una ruta para llegar no hay flujo.  

ruta, aqui se guarda el indice i es el nodo i+1 y quien es su padre para crear una ruta del nodo final hasta el nodo inicial.  

despues la funcion bfs que es una funcion de busqueda, si existe una ruta de nodo inicial al nodo final retorna true en caso contrario false. se explicara despues el dfs.  

el flujo pensamos que es el mayor posible que se puede y usamos el mayor valor practico.  

un for el cual crea un camino desde el nodo_f->padre->padre->padre->nodo_i. y revisamos cuanto es el flujo maximo que puede ir por esa ruta.  

despues de saber el flujo maximo que puede ir por esa ruta, restamos a todos el flujo de la ruta, y por asi decirlo se elimina esa ruta. y le sumamos el flujo de esa ruta al flujo maximo.  

para despues hacer lo mismo de nuevo, para encontrar otra ruta de forma de llegar desde el nodo inicial hasta el nodo final.  
```cpp
int maxflow(int nodo_i,int nodo_f,int n,vector<vector<int> >& conexiones){
	int flujoMaximo = 0, flujo_ruta,nodo1,nodo2;
	vector<int> ruta(n,-1);

	while(bfs(nodo_i,nodo_f,n,ruta,conexiones)) {
		flujo_ruta = 2147483647;

		for(nodo2 = nodo_f;nodo2!=nodo_i;nodo2=ruta[nodo2]) {
			nodo1 = ruta[nodo2];
			flujo_ruta = (flujo_ruta>conexiones[nodo1][nodo2]) ? conexiones[nodo1][nodo2] : flujo_ruta;
		}

		for(nodo2 = nodo_f;nodo2!=nodo_i;nodo2=ruta[nodo2]) {
			nodo1 = ruta[nodo2];
			conexiones[nodo1][nodo2] -= flujo_ruta;
			conexiones[nodo2][nodo1] += flujo_ruta;
		}

		flujoMaximo+= flujo_ruta;
	}
	
	return flujoMaximo;
}
```
la funcion bfs, se le entrega el nodo inicial, el nodo final, la cantidad de nodos, una referencia de ruta y una referencia de conexiones.  

se inicializa un nodo, un vector de si el nodo a sido visitado o no, una cola vacia, que se le agrega el nodo inicial, y se coloca el nodo inicial como visitado o sea true.  

ahora revisamos en la cola si no esta vacia entonces se itera hasta que este vacia.  

se saca el nodo de la cola, y revisamos sus conexiones que tiene con los otros nodos.  

si no esta visitado y el valor entre el nodo y el nodo i es mayor a 0, se agrega a la cola, se coloca el nodo i como visitado y colocamos que el nodo i tiene como padre el nodo que sacamos de la cola, si llegamos de alguna forma al nodo final entonces tenemos un camino desde el nodo inicial al nodo final. y retorna true.  
```cpp
bool bfs(int nodo_i,int nodo_f,int n,vector<int>& ruta,vector<vector<int> >& conexiones) {
	int nodo;

	vector<bool> visitado(n,false);

	queue<int> cola;
	cola.push(nodo_i);
	visitado[nodo_i] = true;

	while(!cola.empty()) {
		nodo = cola.front();
		cola.pop();

		for(int i=0;i<n;i++) {
			if(!visitado[i] && (conexiones[nodo][i] > 0)) {
				cola.push(i);
				ruta[i] = nodo;
				visitado[i] = true;
			}
		}
	}
	return visitado[nodo_f];
}
```
finalemnte asi queda el codigo completo:  

```cpp
#include <bits/stdc++.h>
#include <vector>

using namespace std;

bool bfs(int nodo_i,int nodo_f,int n,vector<int>& ruta,vector<vector<int> >& conexiones) {
	int nodo;

	vector<bool> visitado(n,false);

	queue<int> cola;
	cola.push(nodo_i);
	visitado[nodo_i] = true;

	while(!cola.empty()) {
		nodo = cola.front();
		cola.pop();

		for(int i=0;i<n;i++) {
			if(!visitado[i] && (conexiones[nodo][i] > 0)) {
				cola.push(i);
				ruta[i] = nodo;
				visitado[i] = true;
			}
		}
	}
	return visitado[nodo_f];
}


int maxflow(int nodo_i,int nodo_f,int n,vector<vector<int> >& conexiones){
	int flujoMaximo = 0, flujo_ruta,nodo1,nodo2;
	vector<int> ruta(n,-1);

	while(bfs(nodo_i,nodo_f,n,ruta,conexiones)) {
		flujo_ruta = 2147483647;

		for(nodo2 = nodo_f;nodo2!=nodo_i;nodo2=ruta[nodo2]) {
			nodo1 = ruta[nodo2];
			flujo_ruta = (flujo_ruta>conexiones[nodo1][nodo2]) ? conexiones[nodo1][nodo2] : flujo_ruta;
		}

		for(nodo2 = nodo_f;nodo2!=nodo_i;nodo2=ruta[nodo2]) {
			nodo1 = ruta[nodo2];
			conexiones[nodo1][nodo2] -= flujo_ruta;
			conexiones[nodo2][nodo1] += flujo_ruta;
		}

		flujoMaximo+= flujo_ruta;
	}
	
	return flujoMaximo;
}



int main(int argc, char const *argv[]) {
	int n,inicio,final,aristas,s,t,c,flujoMaximo,red=1;	
	vector<int> respuesta;
	
	while(true) {
		cin >> n;
		if(n==0) break;

		vector<vector<int> > conexiones(n,vector<int>(n,0));

		cin >> inicio >> final >> aristas;

		for(int i=0;i<aristas;i++) {
			cin >> s >> t >> c;
			conexiones[s-1][t-1] += c;
			conexiones[t-1][s-1] += c;
		}

		flujoMaximo = maxflow(inicio-1,final-1,n,conexiones);
		respuesta.push_back(flujoMaximo);
	}
	for(int i=0;i<respuesta.size();i++) {
		cout << "Network " << i+1 << endl;
		cout << "The bandwidth is " << respuesta[i] << "." << endl;
		cout << endl;
	}
	return 0;
}
```