# Problema 100499Jv2

En este link esta como se define el problema [Problem - 100499J Healthy Recipes](https://codeforces.com/gym/100499/problem/J "Healthy Recipes")  

aqui vamos a explicar como se resolvio el problema.  

primero esta la variable de t que eson la cantidad de test que se va a ser, y por cada test existe n platos, y hay que conseguir que que la suma de los platos de m calorias, y ver cuantos combinaciones de k platos se pueden hacer de forma diferente, se tiene otra variable de menu_xCal es cuantos platos distintos se puede hacer con x Calorias ,se sabe que la maxima cantidad de calorias es de 10000, un vector menu con 10001 espacios, en donde el valor del indice 0 se tiene 1 plato por asi decirlo, y cada indice indica cuantos platos se puede hacer con esa cantidad de calorias con los platos.  

en este ejercicio se ocupa menu_xCal variable tipo long double, por que en las pruebas, que no se pueden realizar se produce overflow por lo que con esto se arregla.  

```cpp
	int n,m,k,*a,t,maxCal = 10000;
	long double menu_xCal;
	vector<long double> menu(maxCal+1,0);
	menu[0] = 1;

	scanf("%d",&t);
```
se ingresa los datos de cada test, su n cantidad de platos, sus m calorias a consumir y las k combinaciones sin repetir, y cada valor de calorias de cada plato a[j].  

despues se llama a la funcion calcular menu, para saber cuantas combinaciones de platos se puede hacer con i calorias.  
  
```cpp
	for(int i = 0; i < t; i++) {
		scanf("%d %d %d",&n,&m,&k);
		a = (int *) malloc(n*sizeof(int));
		for(int j = 0; j < n; j++) {
			scanf("%d",&a[j]); 
		}

		menu_xCal = calcular_menu(a,n,m,k,menu);
```
la funcion recive como parametros la calorias por plato, cantidad de platos que existe, la cantidad de calorias que se quiere consumir, la combinacion sin repetir de platos y menu como parametros.  

se cre un parametro al inicio en indice maximo de calorias es 0.  

despues un for que recorre cada plato que del arreglo platos, para despues recorrer desde la cantidad maxima de calorias hasta llegar a 0.  

una condicion donde si el menu con x calorias no existe ningun plato entonces que continue con el siguiente numero.  

otra condicion en donde el valor de calorias del plato junto con la calorias de indice x si es menor o igual a la cantidad de calorias entonces se agrega al menu la combinacion del plato que se agrega y el anterior del menu.  

finalmente se retorna la cantidad de combinaciones de i Calorias.  
```cpp
long double calcular_menu(int *platos,int canPla,int cantCal,int varPla,vector<long double> menu) {
	int indMax = 0;

	for(int indpl = 0; indpl<canPla; indpl++) {
		for(int x = indMax; x>=0;x--) {
			if(menu[x]==0) continue;
			if(platos[indpl] + x <= cantCal) {
				indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
				menu[platos[indpl]+x] += (long double) menu[x];
			}
		}
	}
	return menu[cantCal];
}
```
finalmente si la cantidad de combinaciones es mayor o igual a k entonces es suficiente cantidad de combinaciones, en caso conntrario se indica la cantidad de combinaciones que se pueden crear.  

y se libera la memoria de a, para seguir con la siguiente iteracion.  
```cpp
		if(menu_xCal>=k) {
			printf("ENOUGH\n");
		} else {
			printf("%.0Lf\n", menu_xCal);
		}
		free(a);
```
finalemnte asi queda el codigo completo:

```cpp
#include <bits/stdc++.h>
#include <vector>

using namespace std;

long double calcular_menu(int *platos,int canPla,int cantCal,int varPla,vector<long double> menu) {
	int indMax = 0;

	for(int indpl = 0; indpl<canPla; indpl++) {
		for(int x = indMax; x>=0;x--) {
			if(menu[x]==0) continue;
			if(platos[indpl] + x <= cantCal) {
				indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
				menu[platos[indpl]+x] += (long double) menu[x];
			}
		}
	}
	return menu[cantCal];
}


int main(int argc, char const *argv[]) {
	
	int n,m,k,*a,t,maxCal = 10000;
	long double menu_xCal;
	vector<long double> menu(maxCal+1,0);
	menu[0] = 1;

	scanf("%d",&t);
	for(int i = 0; i < t; i++) {
		scanf("%d %d %d",&n,&m,&k);
		a = (int *) malloc(n*sizeof(int));
		for(int j = 0; j < n; j++) {
			scanf("%d",&a[j]); 
		}

		menu_xCal = calcular_menu(a,n,m,k,menu);

		if(menu_xCal>=k) {
			printf("ENOUGH\n");
		} else {
			printf("%.0Lf\n", menu_xCal);
		}
		free(a);
	}
	return 0;
}
```