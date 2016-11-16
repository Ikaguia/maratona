#ifndef BATATA_DEF
#define BATATA_DEF

#include <bits/stdc++.h>
#include <math.h>
using namespace std;

#define FOR(cont,max)			for(int (cont)=0;		(cont)<(int)(max);(cont)++)
#define FOR2(cont,start,max)	for(int (cont)=(start);	(cont)<(int)(max);(cont)++)
#define BETWEEN(x,a,b)			(((x)>=(a)) && ((x)<(b)))
#define SWAP(a,b)				int _temp_=(a);(a)=(b);(b)=_temp_;
#define RAND(max)				(rand()%(max))
#define RAND2(min,max)			(min)+(rand()%((max)-(min)))
#define LOG(x)					(31 - __builtin_clz(x))

using ii=pair<int,int>;
#define ff first
#define ss second

#endif //BATATA_DEF