#include <bits/stdc++.h>
#include <math.h>
using namespace std;

#define FOR(cont,max)			for(int (cont)=0;		(cont)<(int)(max);(cont)++)
#define FOR2(cont,start,max)	for(int (cont)=(start);	(cont)<(int)(max);(cont)++)
#define ABS(x)					(((x)> 0 ) ? (x) :-(x))
#define MAX(x,y)				(((x)>(y)) ? (x) : (y))
#define MIN(x,y)				(((x)<(y)) ? (x) : (y))
#define BETWEEN(x,a,b)			(((x)>=(a)) && ((x)<(b)))
#define SWAP(a,b)				int _temp_=(a);(a)=(b);(b)=_temp_;
#define RAND(max)				(rand()%(max))
#define RAND2(min,max)			(min)+(rand()%((max)-(min)))

struct uFind{
	const int size;
	int cnt,*id,*sz;
	uFind(int n):cnt{n},size{n}{
		id=new int[n];
		sz=new int[n];
		FOR(i,n){
			id[i]=i;
			sz[i]=1;
		}
	};
	~uFind(){
		delete[] id;
		delete[] sz;
	}
	int find(int p){
		if(id[p]==p)return p;
		return id[p]=find(id[p]);
	}
	bool connected(int a,int b){
		return find(a)==find(b);
	}
	void merge(int a,int b){
		int i=find(a);
		int j=find(b);
		if(i==j)return;
		if(sz[i]>sz[j]){
			id[j]=i;
		}
		else{
			id[i]=j;
			if(sz[i]==sz[j])sz[j]++;
		}
		cnt--;
	}
};


//programa teste, le um grafo com n vértices, m arestas e faz o queries sobre ele para ver se dois vertices são conexos
int main(){
	int n,x,y;
	scanf(" %d %d",&n,&m,&o);
	uFind(n) u;
	FOR(i,m){
		scanf(" %d %d",&x,&y);
		u.merge(x,y);
	}
	FOR(i,o){
		scanf(" %d %d",&x,&y);
		if(u.connected(x,y))printf("Caso %d: Sim\n",i+1);
		else                printf("Caso %d: Não\n",i+1);
	}
	return 0;
}
