#include "def.cpp"

enum grafoConfigBit{
	precalc_dist,
	grafoConfigSize
};
typedef bitset<grafoConfigSize> grafoConfig;

template <class T> class grafo{
	const int cont;
	grafoConfig cfg;
	vector<T> vertices;
	vector<ii> arestas;
	grafo(int n,grafoConfig config):
		cont{n},
		vertices{vector<T>(n)},
		cfg{config}{
		;;
	};
};
