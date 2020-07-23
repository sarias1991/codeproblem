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