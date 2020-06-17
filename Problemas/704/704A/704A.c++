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