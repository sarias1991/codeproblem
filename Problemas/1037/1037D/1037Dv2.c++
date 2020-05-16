#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <queue>
#include <map>

using namespace std;



void print(queue<int> cola) {
	while(!cola.empty()){
		printf("%d\n",cola.front() );
		cola.pop();
	}

}

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