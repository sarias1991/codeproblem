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