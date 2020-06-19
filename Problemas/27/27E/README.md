# Problema 27E

En este link esta como se define el problema [Problem - 27E Number With The Given Amount Of Divisors](https://codeforces.com/contest/27/problem/E "Number With The Given Amount Of Divisors")  

aqui vamos a explicar como se resolvio el problema.  

variable global, por que solo 10 primos y no mas, por que si usamos los 10 primeros primos todos elevados a uno (2 * 3 * 5 * 7 * ... * 29) eso crea 2 elevado a 10 divisores, o sea 1024 divisores, y la cantidad de divisores son entre 1 a 1000 por lo que no se necesitan mas numeros primos.
```cpp
long double primos[] = {2,3,5,7,11,13,17,19,23,29};
```

se crea las variables n que es la cantidad de divisores que tiene el, una variable valor minimo (valMin) 1e18, ocupe long long int y unsigned long long int, pero al multiplicar los valores primos puede causar overflow, por lo que el long long int se vuelve negativo y eso lo haria el valor minimo, mientras que el unsigned long long int se vuelve 0 por el overflow, para evitar esto se ocupa long double que tiene 16 bytes y se le entrega la cantidad de divisores n por consola.   

se llama a la funcion recursiva entregandole como parametros el valor 1 la cantidad de divisores acumulados 1, el indice en la posicion de numero primo en el que se encuentra y su valor minimo, y retorna el valor minimo con esa cantidad de divisores.  

y finalmente imprimen el valor minimo con esa cantidad de divisores.  
```cpp
	int n;
	long double valMin = 1000000000000000000;
	scanf("%d",&n);

	valMin = backtraking(1,1,0,n,valMin);

	printf("%lld\n", (long long int)valMin );
```
y finalmente tenemos la funcion recursiva, el valor, la cantidad de divisores (cantdiv), indice, que se modifica en cada iteracion, el valor de cantidad de divisores que se necesita (n) y el valor minimo, que cambia si se tiene una mejor opcion.   

ahora creamos una variable llamada potencia, el donde guarda la potencia del valor de primo del indice.  

el candicion si la cantidad de divisores igual a la cantidad que nos piden retorna el valor acumulado.  

la condicion de que no puede pasar el indice 10 ya que el arreglo primos solo tiene 10 elementos, indices de [0,..,9], en ese caso retorna el valor minimo (valMin).  

el for que cada cantidad de divisores anteriores se multiplica de la potencia del primo sea si tenemos una potencia de 3 elevado a 3 entonces tenemos 4 veces mas la cantidad de divisores como ejemplo para que se entienda mas el valor de 54 tiene 8 divisores 1,2,3,6,9,18,27,54.  

la condicion como guardamos el valor minimo de la recursion, entonces si se pasa el valor es mayor al valor minimo guardado, entonces no necesitamos seguir.  

potencia el cual guarda la potencia de algun primos.  

y la asignacion de valMin, esto hace que si el valor que encontramos es menor que el valor minimo que tenimos sobrescribe el valor minimo al mas bajo.  

y retorna el valor minimo encontrado.  
```cpp
long double backtraking(long double valor,int cantdiv,int indice,int n,long double valMin) {
	long double potencia = 1;
	if(cantdiv==n) return valor;
	if(indice==10) return valMin;
	for(int i = 0;(i+2)*cantdiv<=n;i++) {
		if(valor > valMin) break;
		potencia = potencia * primos[indice];
		valMin = min(valMin,backtraking(valor*potencia,(i+2)*cantdiv,indice+1,n,valMin));
	}
	
	return valMin;
}
```
finalemnte asi queda el codigo completo:

```cpp
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

long double primos[] = {2,3,5,7,11,13,17,19,23,29};

long double backtraking(long double valor,int cantdiv,int indice,int n,long double valMin) {
	long double potencia = 1;
	if(cantdiv==n) return valor;
	if(indice==10) return valMin;
	for(int i = 0;(i+2)*cantdiv<=n;i++) {
		if(valor > valMin) break;
		potencia = potencia * primos[indice];
		valMin = min(valMin,backtraking(valor*potencia,(i+2)*cantdiv,indice+1,n,valMin));
	}
	
	return valMin;
}

int main(int argc, char const *argv[]) {
	int n;
	long double valMin = 1000000000000000000;
	scanf("%d",&n);

	valMin = backtraking(1,1,0,n,valMin);

	printf("%lld\n", (long long int)valMin );
	return 0;
}
```