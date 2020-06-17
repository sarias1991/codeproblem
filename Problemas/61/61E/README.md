# Problema 61E

En este link esta como se define el problema [Problem - 61E - Enemy is weak](https://codeforces.com/contest/61/problem/E "Enemy is weak")  

aqui vamos a explicar como se resolvio el problema.   

se definen las funciones de BITree, las estandar.  
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
  
 
int *constructBITree(vector<int> arr, int n) { 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0; 
  
    for (int i=0; i<n; i++) 
        updateBIT(BITree, n, i, arr[i]); 
 
  
    return BITree; 
}
```
se crea la variable n que es el numero de enemigos y la fue que es la fuerza de cada soldado, los dos puntero BITree y la cantidad de debilidades que tiene el ejercito enemigo, tambien se crea el vector de pares, la fuerzas ya escaladas, gr, le que guarda las sumas de cada BITree y zeros.  
```cpp
	int n,fue,*BITree1,*BITree2;
	long long debilidad = 0;
 
	scanf("%d",&n);
	
	vector<pair<int,int> > fuerza_indice(n); //a_arreglo con indice
	vector<int> fuerzas(n); //el a_arreglo pero escalado 
	vector<long long> gr(n);
	vector<long long> le(n);
	vector<int> zeros(n,0);
```
para despues ingresar los valores por consola la cual guarda su fuerza que esta en la consola y su indice en que posicion se agrego.  

despues se ordena el vector fuerza_indice, de menor a mayor.  

y con el for siguiente se reescala, ya que el valor no importa perce por lo que se crea un vector de fuerzas 0 a n-1, donde el valor mayor tiene el mismo lugar que el valor escalado y al mismo tiempo cuenta como indices.  
```cpp
	for(int i=0;i<n;i++) {
		scanf("%d",&fue);
		fuerza_indice[i] =make_pair(fue,i);
	}

	sort(fuerza_indice.begin(),fuerza_indice.end());
	for(int i=0;i<n;i++) {
		fuerzas[fuerza_indice[i].second] = i;
	}
```
Se crean dos arboles BITree con zeros en todos los indices, gr en posicion i toma el valor de la suma de todos las fuerzas del 0 a el indice de fuerzas en la poscion i, le en posicion n-1-i  toma el valor de la suma de todos las fuerzas de 0 a el indice de fuerzas en la poscion n-1-i.  

el BITree1 se empieza a acumular el valor de 1, y se le resta -1 a la poscion de fuerzas en el indice i.  

ahora si el valor de fuerzas en la posicion n-1-i es menor que n-1 entonces se agrega un 1 en la posicion de mas 1 de el valor de fuerzas de posicion de n-1-i.  
```cpp
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
```
se hace la sumatoria de todas las debilidades y printea cuantas debilidades tiene el enemigo.  
```cpp
	for(int i = 0;i<n;i++) debilidad += gr[i]*le[i];
	printf("%lld\n",debilidad); 
```
finalemnte asi queda el codigo completo:  

```cpp
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
```