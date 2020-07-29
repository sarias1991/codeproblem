# Problema 721C

En este link esta como se define el problema [Problem - 721C Journey](https://codeforces.com/contest/721/problem/C "Journey")  

aqui vamos a explicar como se resolvio el problema.  

n son la cantidad de lugares, m son cuantas formas hay de llegar de un punto a otro y cuanto demora y T es el tiempo maximo que tiene para hacer el viaje a esos lugares, u -> v : t o sea se puede ir de un nodo u al v y se tarda t en tiempo, la cantidad de visitas, el nodos en el cual me encuentro, y mi ubicacion actual.  

un nodo respuesta para saber el recorrido que tengo que tomar para visitar la mayor cantidad de lugares posibles.  

un mapa donde me dice las conexiones que tiene los lugares y cuanto cuesta en tiempo.  

aqui se agregan los datos de n, m y T.  

despues se crea un vector de vectores, se llama dp de programacion dinamica, y la posicion en el cual me encuentro.  

aqui se agrega las aristas de los nodos y sus pesos a el mapa.  
```cpp
	int n,m,T,u,v,t,cantvisitada=0,nodos,ubiActual;
	vector<int> respuesta;
	unordered_map<int, unordered_map<int,int> > mapa;

	cin >> n >> m >> T;

	vector<vector<int> > dp(n+1,vector<int>(n+1,inf));
	vector<vector<int> > posicion(n+1,vector<int>(n+1,inf));

	for(int i=0;i<m;i++) {
		cin >> u >> v >> t;
		mapa[u][v] = t;
	}
```
aqui se agrega todos los datos al vector de programacion dinamica y se encuentra los parametros nodo 1, contador 1, tiempo 0, pr o ubicacion actual 1, el tiempo maximo, el vector por referencia, posicion por referencia y mapa por referencia.  
```cpp
	dfs(1,1,0,1,T,dp,posicion,mapa);
```
se le entrega como parametros al nodo al cual voy, contador de pasos, el tiempo transcurrido, el nodo de donde provengo, el tiempo maximo, el vector dp, el vector posicion y el mata los ultimos tres pasados por referencia.  

una condicion, se verifica el tiempo, si el tiempo es mayor que el tiempo maximo o el tiempo en ese nodo es menor que el tiempo actual, hace un retorn y no sigue con el codigo.  

ahora agregamos a la posicion dinamica en el nodo y el contador el tiempo t que por obligacion es menor que T y agregamos de que posicion nos encontramos o ubicacion actual al vector de posiciones.  

ahora se usa un for para recorrer todas las rutas de el nodo del mapa y hacemos otro dfs(nodo siguiente, amenta el contador en 1, se le suma el tiempo de ir del nodo actual al nodo siguiente, el nodo del cual vengo, el tiempo maximo, el dp,posicion, mapa), hasta recorrer todo las aristas.  
```cpp
void dfs(int nodo,int contador,int t,int pr,int T,vector<vector<int> >& dp,vector<vector<int> >& posicion,unordered_map<int,unordered_map<int,int> >& mapa) {
	if(t> T || t>= dp[nodo][contador]) return;
	dp[nodo][contador] = t;
	posicion[nodo][contador] = pr;
	for(auto it = mapa[nodo].begin();it!=mapa[nodo].end();it++) {
		dfs(it->first,contador+1,t+it->second,nodo,T,dp,posicion,mapa);
	}
}

```
aqui se busca la cantidad maxima de visitas a los lugares donde el dp para llegar al nodo n y el tiempo que se demora si es mayor a T no se considera en caso contrario, se verifica si es el maximo.
```cpp
	for(int i=1;i<=n;i++) {
		if(dp[n][i]<=T) {
			cantvisitada = (i >= cantvisitada) ? i : cantvisitada; 
		}
	}
```
se agrega a la respuesta el nodo n, el nodos en el cual estoy, y en que posicion estoy ubiActual es la cantidad de lugares que e visitado.  

entonces con el vector posicion del nodo en el que me encuentro y la ubicacion actual, me regresa el nodo anterior para llegar, y se agrega el vector de respuesta, y se le resta 1 a la ubiActual.  
```cpp
	respuesta.push_back(n);
	nodos = n;
	ubiActual = cantvisitada;
	while(nodos!=1) {
		nodos = posicion[nodos][ubiActual];
		respuesta.push_back(nodos);
		ubiActual--;
	}
```
entonces tenemos del n hasta el 1 como respuesta pero empieza desde el 1 hasta el n, se invierte el vector respuesta, la cantidad de lugares visitados y un salto de linea, y despues se muestra por pantalla la respuesta de los lugares al cual hay que visitar.  
```cpp
	reverse(respuesta.begin(),respuesta.end());
	cout << cantvisitada << endl;
	for(int i=0;i<respuesta.size();i++) {
		cout << respuesta[i] << " ";
	}
	cout << endl;
```
finalemnte asi queda el codigo completo:

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>

using namespace std;

int inf = 1000000000+1;

void dfs(int nodo,int contador,int t,int pr,int T,vector<vector<int> >& dp,vector<vector<int> >& posicion,unordered_map<int,unordered_map<int,int> >& mapa) {
	if(t> T || t>= dp[nodo][contador]) return;
	dp[nodo][contador] = t;
	posicion[nodo][contador] = pr;
	for(auto it = mapa[nodo].begin();it!=mapa[nodo].end();it++) {
		dfs(it->first,contador+1,t+it->second,nodo,T,dp,posicion,mapa);
	}
}


int main(int argc, char const *argv[]) {
	int n,m,T,u,v,t,cantvisitada=0,nodos,ubiActual;
	vector<int> respuesta;
	unordered_map<int, unordered_map<int,int> > mapa;

	cin >> n >> m >> T;

	vector<vector<int> > dp(n+1,vector<int>(n+1,inf));
	vector<vector<int> > posicion(n+1,vector<int>(n+1,inf));

	for(int i=0;i<m;i++) {
		cin >> u >> v >> t;
		mapa[u][v] = t;
	}

	dfs(1,1,0,1,T,dp,posicion,mapa);
	for(int i=1;i<=n;i++) {
		if(dp[n][i]<=T) {
			cantvisitada = (i >= cantvisitada) ? i : cantvisitada; 
		}
	}
	respuesta.push_back(n);
	nodos = n;
	ubiActual = cantvisitada;
	while(nodos!=1) {
		nodos = posicion[nodos][ubiActual];
		respuesta.push_back(nodos);
		ubiActual--;
	}

	reverse(respuesta.begin(),respuesta.end());
	cout << cantvisitada << endl;
	for(int i=0;i<respuesta.size();i++) {
		cout << respuesta[i] << " ";
	}
	cout << endl;

	return 0;
}
```