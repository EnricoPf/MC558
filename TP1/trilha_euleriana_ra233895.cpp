#include "trilha_euleriana_ra233895.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Grafo::Grafo(int V, int M)
{
    this->V = V;
    this->M = M;
    vizinhos = new list<int>[V];
}

// Criação da aresta (v1, v2) em G.
void Grafo::adicionarAresta(int v1, int v2)
{
    vizinhos[v1].push_back(v2);
}

// Verifica se existe aresta (v1, v2) em G e retorna true se existe e false caso contrário.
bool Grafo::existeAresta(int v1, int v2)
{
    if (find(vizinhos[v1].begin(), vizinhos[v1].end(), v2) != vizinhos[v1].end())
        return true;
    return false;
}

bool trilha_euleriana(int n, int m, Grafo G, int origem[], int destino[], int trilha[], string mensagem, int RA){
    //n - numero de vertices, m - numero de arestas
    //se existir u e V(G) tal que grau de entrada de u != grau de saida, mostrar "Erro: Existe vértice inviável." e interromper execução    
    cout<<"Chegou aqui, n = " << n << endl;
    int i;
    list<int>::iterator j;
    int k = 0;
    for (int i = 0; i < n; i++){
        j = G.vizinhos[i].begin();
        while (j!= G.vizinhos[i].end()){
            origem[k] = i;
            destino[k] = *j;
            k++;
            ++j;
        }
    }
    cout<<"Chegou aqui, k = " << k << endl;
    for (int a = 0; a < k; a++){
        cout<<origem[a] << ' ' << destino[a] << endl;
    }

    //se G não for fortemente conexo, mostrar "Erro: Grafo não eh fortemente conexo." e interromper conexão
    //caso nenhum dos dois, imprimir uma trilha fechada euleriana começando e terminando em v, construida em trilha linear
    return 0;
}