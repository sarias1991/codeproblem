#include <bits/stdc++.h>
#include <algorithm>
#include <vector>

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
  

int *constructBITree(vector<int> arr, int n) { 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0; 
  
    for (int i=0; i<n; i++) 
        updateBIT(BITree, n, i, arr[i]); 
 
  
    return BITree; 
} 

int main(int argc, char const *argv[]) {
	int n,fue,*BITree1,*BITree2;
	long long debilidad = 0;

	scanf("%d",&n);
	
	vector<pair<int,int> > fuerza_indice(n); //a_arreglo con indice
	vector<int> fuerzas(n); //el a_arreglo pero escalado 
	vector<long long> gr(n);
	vector<long long> le(n);
	vector<int> zeros(n,0);

	for(int i=0;i<n;i++) {
		scanf("%d",&fue);
		fuerza_indice[i] =make_pair(fue,i);
	}

	sort(fuerza_indice.begin(),fuerza_indice.end());
	for(int i=0;i<n;i++) {
		fuerzas[fuerza_indice[i].second] = i;
	}

	BITree1 = constructBITree(zeros,n);
	BITree2 = constructBITree(zeros,n);
	for(int i=0;i<n;i++) {
		gr[i] = (long long)getSum(BITree1,fuerzas[i]);
		le[n-1-i] = (long long)getSum(BITree2,fuerzas[n-1-i]);

		updateBIT(BITree1, n, 0, 1);
		updateBIT(BITree1, n, fuerzas[i], -1);
		if(fuerzas[n-1-i]<n-1) {
			updateBIT(BITree2, n, fuerzas[n-1-i]+1, 1);
		}
	}

	for(int i = 0;i<n;i++) debilidad += gr[i]*le[i];
	printf("%lld\n",debilidad); 





	return 0;
}





