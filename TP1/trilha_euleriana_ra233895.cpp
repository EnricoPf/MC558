#include "trilha_euleriana_ra233895.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
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

//##----------------Kosaraju-------------------##pragma endregion

void preenche(Grafo G, int v, bool visitados[], stack<int> &pilha){
        visitados[v] = true;
        list<int>::iterator i;
        for (i = G.vizinhos[v].begin(); i != G.vizinhos[v].end(); i++)
        {
            if (visitados[*i] == false)
                preenche(G, *i, visitados, pilha);
        }
        pilha.push(v);
}

Grafo obterGrafoTransposto(Grafo G){
    Grafo grafo_transposto(G.V,G.M);
    for (int v = 0; v < G.V; v++)
    {
        list<int>::iterator i;
        for (i = G.vizinhos[v].begin(); i != G.vizinhos[v].end(); i++){
            grafo_transposto.vizinhos[*i].push_back(v);
        }
    }
    return grafo_transposto;
}

void DFS(Grafo G, int v, bool visitados[]){
    visitados[v] = true;
    cout << v << " ";
    list<int>::iterator i;
    for (i = G.vizinhos[v].begin(); i != G.vizinhos[v].end(); i++){
        if (visitados[*i] == false)
            DFS(G, *i, visitados);
    }
}

void imprimirComponentes(Grafo G){
    stack<int> pilha;
    bool *visitados = new bool[G.V];

    for (int i = 0; i < G.V; i++){
        visitados[i] = false;
    }
    for (int i = 0; i < G.V; i++){
        if (visitados[i] == false){
            preenche(G, i, visitados, pilha);
        }
    }

    // cria o grafo transposto
    Grafo gt = obterGrafoTransposto(G);

    // marca todos como não visitados novamente
    for (int i = 0; i < G.V; i++)
        visitados[i] = false;

    // processa os vértices de acordo com a pilha
    while (!pilha.empty())
    {
        // obtém o elemento do topo
        int v = pilha.top();

        // remove o elemento
        pilha.pop();

        // imprime cada componente fortemente conexa
        if (visitados[v] == false)
        {
            DFS(gt, v, visitados);
            cout << "\n";
        }
    }
}

//#-------------------------------------------------------------------------#

bool trilha_euleriana(int n, int m, Grafo G, int origem[], int destino[], int trilha[], string mensagem, int RA){
    //n - numero de vertices, m - numero de arestas
    cout<<"Chegou aqui, n = " << n << endl;
    list<int>::iterator j;
    int k = 0;
    int saida[m], entrada[m];
    for (int i = 0; i < n; i++){
        j = G.vizinhos[i].begin();
        while (j!= G.vizinhos[i].end()){
            origem[k] = i;
            saida[i]++;
            destino[k] = *j;
            entrada[*j]++;
            k++;
            ++j;
        }
    }
    cout << "Chegou aqui, k = " << k << endl;
    for (int a = 0; a < k; a++){
        cout<<origem[a] << ' ' << destino[a] << endl;
    }
    //se existir u e V(G) tal que grau de entrada de u != grau de saida, mostrar "Erro: Existe vértice inviável." e interromper execução    
    for (int i = 0; i < n; i++){
        if (entrada[i] != saida[i]){
            mensagem = "Erro: Existe vértice inviável.";
            cout << mensagem << endl;
            return false;
        }
    }
    //se G não for fortemente conexo, mostrar "Erro: Grafo não eh fortemente conexo." e interromper conexão

    //caso nenhum dos dois, imprimir uma trilha fechada euleriana começando e terminando em v, construida em tempo linear
    return 0;
}