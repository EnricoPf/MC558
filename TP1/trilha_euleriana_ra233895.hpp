#ifndef trilha_euleriana_ra233895
#define trilha_euleriana_ra233895

#include <string.h>
#include <stdbool.h>
#include <list>
#include <string>

using namespace std;

// Implementação de grafo utilizando lista de adjacência
class Grafo
{
public:
    list<int> *vizinhos; // Lista contendo as arestas
    int V;               // Quantidade de vértices
    int M;               // Quantidade de arestas

    Grafo(int V, int M);
    void adicionarAresta(int v1, int v2);
    bool existeAresta(int v1, int v2);
};

bool trilha_euleriana(int n, int m, Grafo G, int* origem, int* destino, int* trilha, string mensagem, int RA);

#endif