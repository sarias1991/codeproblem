#include <bits/stdc++.h>
#include <vector>

using namespace std;

int calcular_menu(int *platos,int canPla,int cantCal,int varPla,vector<int> menu) {
	int indMax = 0;

	for(int indpl = 0; indpl<canPla; indpl++) {
		for(int x = indMax; x>=0;x--) {
			if(menu[x]==0) continue;
			if(platos[indpl] + x <= cantCal) {
				indMax = (indMax >= (platos[indpl] + x)) ? indMax :  (platos[indpl] + x);
				menu[platos[indpl]+x] += menu[x];
				if(menu[platos[indpl]+x] > varPla) {
					menu[platos[indpl]+x] = varPla;
				}
			}
		}
	}
	return menu[cantCal];
}


int main(int argc, char const *argv[]) {
	
	int n,m,k,*a,t,maxCal = 10000,menu_xCal;
	vector<int> menu(maxCal+1,0);
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
			printf("%d\n", menu_xCal);
		}
		free(a);
	}
	return 0;
}