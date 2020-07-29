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