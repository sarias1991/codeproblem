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