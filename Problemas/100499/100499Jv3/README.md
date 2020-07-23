# Problema 100499Jv3

En este link esta como se define el problema [Problem - 100499J Healthy Recipes](https://codeforces.com/gym/100499/problem/J "Healthy Recipes")  

aqui vamos a explicar como se resolvio el problema.  

primero esta la variable de t que eson la cantidad de test que se va a ser, y por cada test existe n platos, y hay que conseguir que que la suma de los platos de m calorias, y ver cuantos combinaciones de k platos se pueden hacer de forma diferente, se tiene otra variable de menu_xCal es cuantos platos distintos se puede hacer con x Calorias.  

en este ejercicio se ocupa menu_xCal variable tipo long double, por que en las pruebas, que no se pueden realizar se produce overflow por lo que con esto se arregla.  

```cpp
	int n,m,k,*a,t,maxCal = 10000;
	long double menu_xCal;

	scanf("%d",&t);
```
se ingresa los datos de cada test, su n cantidad de platos, sus m calorias a consumir y las k conbinaciones sin repetir, y cada valor de calorias de cada plato a[j].  

se crea un arreglo menu, sabiendo que la maxima cantidad de calorias es de 10000, se crea un menu con 10001 espacios, en donde el valor del indice 0 se tiene 1 plato por asi decirlo, y cada indice indica cuantos platos se puede hacer con esa cantidad de calorias con los platos.  

despues se llama a la funcion recursiva calcular_menu, para saber cuantas combinaciones de platos se puede hacer con i calorias.  
  
```cpp
	for(int i = 0; i < t; i++) {
		scanf("%d %d %d",&n,&m,&k);
		a = (int *) malloc(n*sizeof(int));
		for(int j = 0; j < n; j++) {
			scanf("%d",&a[j]); 
		}
		long double *menu = (long double *) calloc(maxCal+1,sizeof(long double));
		menu[0] = 1;

		menu_xCal = calcular_menu(a,n,m,k,0,0,0,menu);
```
la funcion recive como parametros la calorias por plato, cantidad de platos que existe, la cantidad de calorias que se quiere consumir, la combinacion sin repetir de platos, el indice del plato en cual me encuentro en el instante t de la recursion, el x variable que se mueve en el instante t de la recursion, el valor maximo de indice del menu y asi no recorrer todo el arreglo del menu y el puntero menu como parametros.  

una condicion de que si recorre todos los platos entonces ya cree todo el menu por lo que regresa la cantidad de combinaciones de la cantidad de calorias que se quiere consumir.  

una condicion es si x es igual a 0 entonces hace lo siguiente:  

condicion en donde el valor de calorias del plato junto con la calorias de indice x si es menor o igual a la cantidad de calorias entonces se agrega al menu la combinacion del plato que se agrega y el anterior del menu.  

y vuelve a llamar a la funcion recursiva.    

una condicion es si x es distinto a 0 entonces hace lo siguiente:  

condicion en donde el valor de calorias del plato junto con la calorias de indice x si es menor o igual a la cantidad de calorias entonces se agrega al menu la combinacion del plato que se agrega y el anterior del menu.  

y vuelve a llamar a la funcion recursiva.    
```cpp
long double calcular_menu(int *platos,int canPla,int cantCal,int varPla,int indpl,int x,int indMax,long double *menu) {
	if(x == indMax && (canPla == indpl)) return menu[cantCal];
	if(x == 0) {
		if(platos[indpl] + x <= cantCal) {
			indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
			menu[platos[indpl]+x] += (long double) menu[x];
		}
		return calcular_menu(platos,canPla,cantCal,varPla,indpl+1,indMax,indMax,menu);
	} else if (x != 0) {
		if(platos[indpl] + x <= cantCal) {
			indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
			menu[platos[indpl]+x] += (long double) menu[x];
		}
		return calcular_menu(platos,canPla,cantCal,varPla,indpl,x-1,indMax,menu);
	}
}
```
finalmente si la cantidad de combinaciones es mayor o igual a k entonces es suficiente cantidad de combinaciones, en caso conntrario se indica la cantidad de combinaciones que se pueden crear.  

y se libera la memoria de menu y a, para seguir con la siguiente iteracion.  
```cpp
		if(menu_xCal>=k) {
			printf("ENOUGH\n");
		} else {
			printf("%.0Lf\n", menu_xCal);
		}
		free(menu);
		free(a);
```
finalemnte asi queda el codigo completo:

```cpp
#include <bits/stdc++.h>
#include <vector>

using namespace std;

long double calcular_menu(int *platos,int canPla,int cantCal,int varPla,int indpl,int x,int indMax,long double *menu) {
	if(x == indMax && (canPla == indpl)) return menu[cantCal];
	if(x == 0) {
		if(platos[indpl] + x <= cantCal) {
			indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
			menu[platos[indpl]+x] += (long double) menu[x];
		}
		return calcular_menu(platos,canPla,cantCal,varPla,indpl+1,indMax,indMax,menu);
	} else if (x != 0) {
		if(platos[indpl] + x <= cantCal) {
			indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
			menu[platos[indpl]+x] += (long double) menu[x];
		}
		return calcular_menu(platos,canPla,cantCal,varPla,indpl,x-1,indMax,menu);
	}
}


int main(int argc, char const *argv[]) {
	
	int n,m,k,*a,t,maxCal = 10000;
	long double menu_xCal;

	scanf("%d",&t);
	for(int i = 0; i < t; i++) {
		scanf("%d %d %d",&n,&m,&k);
		a = (int *) malloc(n*sizeof(int));
		for(int j = 0; j < n; j++) {
			scanf("%d",&a[j]); 
		}
		long double *menu = (long double *) calloc(maxCal+1,sizeof(long double));
		menu[0] = 1;

		menu_xCal = calcular_menu(a,n,m,k,0,0,0,menu);

		if(menu_xCal>=k) {
			printf("ENOUGH\n");
		} else {
			printf("%.0Lf\n", menu_xCal);
		}
		free(menu);
		free(a);
	}
	return 0;
}
```