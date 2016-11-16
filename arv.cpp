#include "def.cpp"
#include "grafo.cpp"

enum arvConfigBit{
	precalc_anc,
	precalc_lca,
	store_lca,
	arvConfigSize
};
typedef bitset<arvConfigSize> arvConfig;

template <class T> class arvNodo{
public:
	T val;
	int height;
	vector<int> filhos;
	vector<int> ancs;
	arvNodo(int n):height{-1},ancs{vector<int>(n,-1)}{};
};

template <class T> class arv{
public:
	const size_t cont;
	const int root;
	arvConfig cfg;
	vector<arvNodo<T> > nodos;
	int **lcaV;//vetor para salvar resultados de buscas de lca

	arv(const grafo<T> &g,const arvConfig &config,int rt):
		cont{g.vertices.size()},
		root{rt},
		cfg{config},
		nodos{vector<arvNodo<T> >(cont,arvNodo<T>(LOG(cont)))}{
		initNode(root,0,root,g);
		init();
	};
	arv(const vector<vector<int> > &v,const vector<T> &vals,const arvConfig &config,int rt):
		cont{v.size()},
		root{rt},
		cfg{config},
		nodos{vector<arvNodo<T> >(cont,arvNodo<T>(LOG(cont)))}{
		initNode(root,0,root,v,vals);
		init();
	};
	~arv(){
		if(lcaV){
			FOR(i,cont)delete[] lcaV[i];
			delete[] lcaV;
		}
	}
	void initNode(int i,int h,int p,const grafo<T> &g){
		if(nodos[i].height!=-1)return;
		nodos[i].val=g.vertices[i];
		nodos[i].height=h;
		nodos[i].ancs[0]=p;
		for(auto j:g.arestas){
			if(j.ff==i){
				nodos[i].filhos.push_back(j.ss);
				initNode(j.ss,h+1,i,g);
			}
			if(j.ss==i){
				nodos[i].filhos.push_back(j.ff);
				initNode(j.ff,h+1,i,g);
			}
		}
	}
	void initNode(int i,int h,int p,const vector<vector<int> > &v,const vector<T> &vals){
		if(nodos[i].height!=-1)return;
		nodos[i].val=vals[i];
		nodos[i].height=h;
		nodos[i].ancs[0]=p;
		for(auto j:v[i]){
			nodos[i].filhos.push_back(j);
			initNode(j,h+1,i,v,vals);
		}
	}
	void init(){
		if(cfg[precalc_anc]){
			FOR(i,cont)getIJancestor(i,LOG(cont));
		}
		if(cfg[precalc_lca] || cfg[store_lca]){
			cfg[store_lca]=true;
			lcaV = new int*[cont];
			FOR(i,cont){
				lcaV[i] = new int[cont];
				if(cfg[precalc_lca])FOR(j,cont)lcaV[i][j]=lca(i,j);
				else                FOR(j,cont)lcaV[i][j]=-1;
			}
		}
	}
	int getIJancestor(int i,int j){
		if(nodos[i].ancs[j]!=-1)return nodos[i].ancs[j];
		return nodos[i].ancs[j]=getIJancestor(getIJancestor(i,j-1),j-1);
	};
	int getINancestor(int i,int n){
		if(1<<LOG(n)==n)return getIJancestor(i,LOG(n));
		return getINancestor(getIJancestor(i,LOG(n)),n-(1<<LOG(n)));
	};
	int lca(int i,int j){
		int _i=i,_j=j;
		if(cfg[store_lca] && lcaV[i][j]!=-1)return lcaV[i][j];
		if     (nodos[i].height>nodos[j].height)i=getINancestor(i,nodos[i].height-nodos[j].height);
		else if(nodos[j].height>nodos[i].height)j=getINancestor(j,nodos[j].height-nodos[i].height);
		if(i==j){
			if(cfg[store_lca])return lcaV[_i][_j]=i;
			return i;
		}
		int try1,try2,k=log(cont);
		while(k>=0){
			try1 = getIJancestor(i,k);
			try2 = getIJancestor(j,k);
			if(try1!=try2){
				i=try1;
				j=try2;
			}
			k--;
		}
		if(cfg[store_lca])return lcaV[_i][_j]=getIJancestor(i,0);
		return getIJancestor(i,0);
	};
};

int main(){
	vector<vector<int> > v(15);
	v[ 0]={ 1, 2};

	v[ 1]={ 3, 4};
	v[ 2]={ 5, 6};

	v[ 3]={ 7, 8};
	v[ 4]={ 9,10};
	v[ 5]={11,12};
	v[ 6]={13,14};

	v[ 7]={};
	v[ 8]={};
	v[ 9]={};
	v[10]={};
	v[11]={};
	v[12]={};
	v[13]={};
	v[14]={};
	vector<int> v2={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	arv<int> a(v,v2,arvConfig(4),0);
	int x,y;
	while(cin >> x >> y)cout << a.lca(x,y) << endl;
	return 0;
}

//           0
//    1              2
// 3     4       5        6
//7 8   9 10   11 12    13 14