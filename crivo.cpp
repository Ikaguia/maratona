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

void sieveEuler(vector<int>& out,int n);
void sieveErathostenes(vector<int>& out,int n);
void sieveErathostenes2(vector<int>& out,int n);

int main(){
	vector<int> v;
	int x,n;
	scanf(" %d %d\n",&x,&n);
	if     (x==1)sieveEuler(v,n);
	else if(x==2)sieveErathostenes2(v,n);
	else		 sieveErathostenes(v,n);
	//cout << "Primes = {";
	//for(auto i:v)cout << i << ", ";
	//cout << "}\n";
}

void sieveEuler(vector<int>& out,int n){
	bool v[n+1];

	v[2]=true;
	for(int j=3;j<=n;j+=2)v[j]=true;
	for(int j=4;j<=n;j+=2)v[j]=false;

	for(int i=2;i*i<=n;){
		if(v[i]){
			out.push_back(i);
			v[i]=false;
			while(i<=n && !v[i])i++;
			for(int j=i;j*j<=n;j++){
				if(v[j]){
					v[i*j]=false;
				}
			}
		}
	}
	for(int i=out[out.size()-1]+1;i<=n;i++){
		if(v[i])out.push_back(i);
	}
}

void sieveErathostenes(vector<int>& out,int n){
	bool v[n+1];

	out.push_back(2);
	for(int j=3;j<=n;j+=2)v[j]=true;
	for(int j=4;j<=n;j+=2)v[j]=false;

	int i;
	for(i=3;i*i<=n;i+=2){
		if(v[i]){
			out.push_back(i);
			for(int j=i*i;j<=n;j+=i){
				v[j]=false;
			}
		}
	}
	for(;i<=n;i++){
		if(v[i])out.push_back(i);
	}
}

struct node{
	node(int max,int x,node* point[]):val{x},del{false},next{NULL}{
		//cout << "constructor node max " << max << " x " << val << endl;
		if(x<max)next = new node(max,x+1,point);
		//cout << "node " << val << " = " << this << " next = " << next << endl;
		point[x]=this;
	}
	int val;
	bool del;
	node* next;
};

void deleteNode(node* n){
	delete n->next;
	delete n;
}

void sieveErathostenes2(vector<int>& out,int n){
	node* point[n+1];
	node* first = new node(n,2,point);
	//cout << "finished constructor" << endl;

	out.push_back(2);
	//cout << "deleting mod 2" << endl;
	for(int j=4;j<=n;j+=2){
		point[j-1]->next = point[j]->next;
		delete point[j];
		point[j]=NULL;
	}
	//cout << "deleted mod 2" << endl;

	auto i=point[3];
	while(1){
		//cout << "i = " << i->val << endl;
		out.push_back(i->val);
		//cout << "out += i" << endl;
		if(!(i->next))break;
		//cout << i << " -> next = " << i->next << endl;
		i=i->next;
		if((i->val * i->val) > n)continue;
		//cout << i << endl;
		//cout << "i = " << i->val << endl;
		auto j=i;
		//cout << j << endl;
		//cout << "j = " << j->val << endl;
		while(j->val * j->val <= n){
			//cout << "j = " << j->val << endl;
			//cout << "deleting point[" << i->val << "*" << j->val << "]" << endl;
			int del=i->val*j->val;
			point[del]->del=true;
			point[del]=NULL;
			//cout << "deleted point[" << i->val << "*" << j->val << "]" << endl;
			j=j->next;
		}
		for(auto x=point[3];x->next;x=x->next){
			if(x->next->del){
				auto temp = x->next;
				x->next = x->next->next;
				delete temp;
			}
		}
	}
	deleteNode(first);
}

