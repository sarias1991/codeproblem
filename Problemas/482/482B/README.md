# Problema 482B

En este link esta como se define el problema [Problem - 482 - Interesting Array](https://codeforces.com/contest/482/problem/B "Interesting Array")  

aqui vamos a explicar como se resolvio el problema.  

se creo una estructura, restricion el cual tiene 3 numeros enteros, el indice a la izquierda o menor llamado l, el indice a la derecha o mayor llamado r y el valor final de todos los indices del l al r con la operacion binaria and tiene que ser igual a q 
```cpp
struct restricion {
	int l;
	int r;
	int q;
};
```
se definen las funciones de segment tree o arbol de segmento, las estandar modificados para el ejercicio, donde la operacion que se usa es AND como operacion binaria, y una consulta por rango donde los elementos del arreglo[l] & arreglo[l+1] & .... & arreglo[r-1] & arreglo[r] te devuelve el valor de un rango entre l y r uniondolos por la operacion binaria AND
```cpp
int mitad(int in,int fin) {
	return in + (fin-in)/2;
}

int obtenerAndUtil(int *st, int ss, int se, int qs, int qe, int si) { 
	if (qs <= ss && qe >= se) 
		return st[si]; 

	if (se < qs || ss > qe) 
		return 2147483647; 

	int mid = mitad(ss, se); 
	return obtenerAndUtil(st, ss, mid, qs, qe, 2*si+1) & 
		obtenerAndUtil(st, mid+1, se, qs, qe, 2*si+2); 
} 

int obtenerAnd(int *st, int n, int qs, int qe)  { 
	if (qs < 0 || qe > n-1 || qs > qe) { 
		cout<<"Invalid Input"; 
		return -1; 
	} 

	return obtenerAndUtil(st, 0, n-1, qs, qe, 0); 
} 

int construirSegmentTreeUtil(int *arreglo, int inicio, int final, int *segmentTree, int indice) {
	if(inicio == final) {
		segmentTree[indice] = arreglo[inicio];
		return arreglo[inicio];
	}

	int medio = mitad(inicio,final);
	segmentTree[indice] = construirSegmentTreeUtil(arreglo,inicio,medio,segmentTree,indice*2+1) & construirSegmentTreeUtil(arreglo,medio+1,final,segmentTree,indice*2+2);
	
	
	return segmentTree[indice];
}

int *construirSegmentTree(int *arreglo, int n) {
	int x = (int)(ceil(log2(n)));
	int tamano_max = 2*(int)pow(2,x)-1;

	int *st = new int[tamano_max];

	construirSegmentTreeUtil(arreglo,0,n-1,st,0);	

	return st;
}
```
aqui se inicializan las variables que vamos a usar, n para el tamaño de el arreglo, m para la cantidad de restricciones, un puntero para el segment_tree, el tamaño del segment tree(tamanoST), el puntero del arreglo donde van a estar el valor que tiene que tener para intentar cumplir las restriciones, y un puntero a posiciones, un estructura resticiones, un bool si es o no interesante con valor por defecto true, un vector de todas las restriciones.  
  
se le da el valor por consola m y n  
  
se crea un arreglo de largo n y valores 0's  
  
se agregan las m lineas de restricciones por consola  

```cpp
	int n,m,*segment_tree,tamanoST,*arreg,*pos;
	struct restricion aux;
	bool interesting = true;
	vector<struct restricion> restriciones;
	scanf("%d %d",&n,&m);

	arreg = (int *) calloc(n,sizeof(int));

	for(int i=0;i<m;i++) {
		scanf("%d %d %d",&aux.l,&aux.r,&aux.q);
		aux.l--;
		restriciones.push_back(aux);
	}

```
en el problema se dice que el valor de la restricion q va a estar entre los valores $[0,2^{30}]$ por lo que vamos a ver los 30 bits que tiene cada restricion, con el primer for, y pos es un arreglo en donde se indica donde empieza la restricion el valor l y donde termina el valor r, usamos pos[l]++ para decir que exite ese bit y en los siguientes, y el pos[r]-- donde significa que termina, pero se puede acumular.  

el segundo for es donde pos[l], ...., por[r] se agrega el tamaño de bit a el arreglo y para el siguiente bit se liberan las posiciones y se repite para el siguiente bit hasta llegar al bit 30  
```cpp
	for(int bit=0;bit<=30;bit++) {
		pos = (int *) calloc(n+1,sizeof(int));
		for(int i=0;i<m;i++) {
			if((restriciones[i].q>>bit & 1)){
				pos[restriciones[i].l]++;
				pos[restriciones[i].r]--;
			}
		} 
		for(int i=0;i<n;i++) {
			if(i>0) {
				pos[i]+=pos[i-1];
			}
			if(pos[i]>0) {
				arreg[i] |= (1<<bit);
			}
		}
		free(pos);
	}
```
ya teniendo el arreglo listo, se ejecuta la contruccion de arbol de segmento, y eso hace que las consultas sea realmente rapidida, y se usa la funcion de check restriciones, el cual se le entrega el arbol de segmento para hacer rapido consultas, las restriciones y el tamaño del arreglo n.  
```cpp
	segment_tree = construirSegmentTree(arreg,n);
	tamanoST = 2*(int)pow(2,(int)(ceil(log2(n))))-1;
	interesting = checkResctriciones(segment_tree,restriciones,n);
```
aqui la funcion checkRestriciones, entrega un bool donde si se cumplen todas las restriciones entrega un true, si no se cumple las restriciones, retorna un false, con el arbol de consulta y la fucion algo estandar de obtenerAnd, entrega el valor acumulado de el rango entre el l y el r, y revisa si es igual a la restricion q.  
```cpp
bool checkResctriciones(int *segmentTree,vector<struct restricion> todasRestriciones,int n) {
	for(int i=0;i<todasRestriciones.size();i++){
		int acumulador = obtenerAnd(segmentTree,n,todasRestriciones[i].l,todasRestriciones[i].r-1);
		if(!(acumulador == todasRestriciones[i].q)) return false;
	}
	return true;
}
```
finalmente si interesting es true, imprime por pantalla "YES" y el arreglo.  

si interesting es false, imprime por pantalla "NO"  
```cpp
	if(interesting) {
		printf("YES\n");
		for(int i=0;i<n;i++) printf("%d ",(arreg[i]!=-1)? arreg[i] : 0 );
		printf("\n");
	} else {
		printf("NO\n");
	}

```

finalemnte asi queda el codigo completo:

```cpp
#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct restricion {
	int l;
	int r;
	int q;
};

int mitad(int in,int fin) {
	return in + (fin-in)/2;
}

int obtenerAndUtil(int *st, int ss, int se, int qs, int qe, int si) { 
	if (qs <= ss && qe >= se) 
		return st[si]; 

	if (se < qs || ss > qe) 
		return 2147483647; 

	int mid = mitad(ss, se); 
	return obtenerAndUtil(st, ss, mid, qs, qe, 2*si+1) & 
		obtenerAndUtil(st, mid+1, se, qs, qe, 2*si+2); 
} 

int obtenerAnd(int *st, int n, int qs, int qe)  { 
	if (qs < 0 || qe > n-1 || qs > qe) { 
		cout<<"Invalid Input"; 
		return -1; 
	} 

	return obtenerAndUtil(st, 0, n-1, qs, qe, 0); 
} 

int construirSegmentTreeUtil(int *arreglo, int inicio, int final, int *segmentTree, int indice) {
	if(inicio == final) {
		segmentTree[indice] = arreglo[inicio];
		return arreglo[inicio];
	}

	int medio = mitad(inicio,final);
	segmentTree[indice] = construirSegmentTreeUtil(arreglo,inicio,medio,segmentTree,indice*2+1) & construirSegmentTreeUtil(arreglo,medio+1,final,segmentTree,indice*2+2);
	
	
	return segmentTree[indice];
}

int *construirSegmentTree(int *arreglo, int n) {
	int x = (int)(ceil(log2(n)));
	int tamano_max = 2*(int)pow(2,x)-1;

	int *st = new int[tamano_max];

	construirSegmentTreeUtil(arreglo,0,n-1,st,0);	

	return st;
}

bool checkResctriciones(int *segmentTree,vector<struct restricion> todasRestriciones,int n) {
	for(int i=0;i<todasRestriciones.size();i++){
		int acumulador = obtenerAnd(segmentTree,n,todasRestriciones[i].l,todasRestriciones[i].r-1);
		if(!(acumulador == todasRestriciones[i].q)) return false;
	}
	return true;
}



int main(int argc, char const *argv[]) {	
	int n,m,*segment_tree,tamanoST,*arreg,*pos;
	struct restricion aux;
	bool interesting = true;
	vector<struct restricion> restriciones;
	scanf("%d %d",&n,&m);

	arreg = (int *) calloc(n,sizeof(int));

	for(int i=0;i<m;i++) {
		scanf("%d %d %d",&aux.l,&aux.r,&aux.q);
		aux.l--;
		restriciones.push_back(aux);
	}

	for(int bit=0;bit<=30;bit++) {
		pos = (int *) calloc(n+1,sizeof(int));
		for(int i=0;i<m;i++) {
			if((restriciones[i].q>>bit & 1)){
				pos[restriciones[i].l]++;
				pos[restriciones[i].r]--;
			}
		} 
		for(int i=0;i<n;i++) {
			if(i>0) {
				pos[i]+=pos[i-1];
			}
			if(pos[i]>0) {
				arreg[i] |= (1<<bit);
			}
		}
		free(pos);
	}

	segment_tree = construirSegmentTree(arreg,n);
	tamanoST = 2*(int)pow(2,(int)(ceil(log2(n))))-1;
	interesting = checkResctriciones(segment_tree,restriciones,n);

	if(interesting) {
		printf("YES\n");
		for(int i=0;i<n;i++) printf("%d ",(arreg[i]!=-1)? arreg[i] : 0 );
		printf("\n");
	} else {
		printf("NO\n");
	}

	return 0;
}
```