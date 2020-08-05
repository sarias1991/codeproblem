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