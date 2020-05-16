#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <queue>

using namespace std;

struct nodo {
	int contador = 0;
	vector<int> conexion;
};

void print(queue<int> cola) {
	while(!cola.empty()){
		printf("%d\n",cola.front() );
		cola.pop();
	}

}

bool is_conexion(vector<nodo> gra,int nodo1,int nodo2){
	for(int i=0;i<gra[nodo1-1].conexion.size();i++){
		if(gra[nodo1-1].conexion[i]==nodo2-1) return true;
	}
	return false;
}

int main(int argc, char const *argv[]) {
	int n,x,y,aux;
	queue<int> q,v,a;
	vector<nodo> grafo;
	scanf("%d",&n);
	grafo.reserve(n);
	for(int i=0;i<n-1;i++){
		scanf("%d %d",&x,&y);
		grafo[x-1].conexion.push_back(y-1);
		grafo[y-1].conexion.push_back(x-1);

	}
	for(int i=0;i<n;i++){
		scanf("%d",&aux);
		a.push(aux);
	}
	//print(a);

	if(a.front()!=1) {
		printf("%s\n","No");
	} else {
		q.push(1);
		a.pop();
		while(!a.empty()){
			if(is_conexion(grafo,q.front(),a.front())) {
				grafo[aux-1].contador++;
				v.push(a.front());
				a.pop();
			} else {
				printf("%s\n","False");
			}
			if(grafo[q.front()-1].contador == grafo[q.front()-1].conexion.size()){
				q.pop();
				q.push(v.front());
				v.pop();
			}
		}
	}
	if(a.empty()) printf("%s\n","Yes");

	return 0;
}