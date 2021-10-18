#include "trilha_euleriana_ra233895.h"

#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
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
    list<int>::iterator i;
    for (i = G.vizinhos[v].begin(); i != G.vizinhos[v].end(); i++){
        if (visitados[*i] == false)
            DFS(G, *i, visitados);
    }
}

bool testaComponentes(Grafo G){
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
    Grafo gt = obterGrafoTransposto(G);
    for (int i = 0; i < G.V; i++)
        visitados[i] = false;

    int reis = 0;
    while (!pilha.empty()){
        int v = pilha.top();
        pilha.pop();
        // imprime cada componente fortemente conexa
        if (visitados[v] == false){
            DFS(gt, v, visitados);
            //aqui ele trocaria de linha
            reis++;
        }
    }
    if (reis == 1)
        return true;
    return false;
}

//#-------------------------------------------------------------------------#

bool trilha_euleriana(int n, int m, Grafo G, int origem[], int destino[], int trilha[], string mensagem, int RA){
    //n - numero de vertices, m - numero de arestas
    list<int>::iterator j;    
    int k = 0;
    int entrada [n];
    int saida [n];
    for (int i = 0; i < n; i++){
        entrada[i] = 0;
        saida[i] = 0;
    }
    for (int i = 0; i < n; i++){
        for (j = G.vizinhos[i].begin(); j != G.vizinhos[i].end();j++){
            origem[k] = i;
            saida[i]++;
            destino[k] = *j;
            entrada[*j]++;
            k++;
        }
    }
    /* Trecho pra imprimir as arestars - DEBUG
    for (int a = 0; a < k; a++){
        cout<<origem[a] << ' ' << destino[a] << endl;
    }*/

    //se existir u e V(G) tal que grau de entrada de u != grau de saida, mostrar "Erro: Existe vértice inviável." e interromper execução    
    for (int i = 0; i < n; i++){
        if (entrada[i] != saida[i]){
            mensagem = "Erro: Existe vértice inviável.";
            cout << mensagem << endl;
            return false;
        }
    }
    //se G não for fortemente conexo, mostrar "Erro: Grafo não eh fortemente conexo." e interromper conexão
    if (!(testaComponentes(G))){
        mensagem = "Erro: Grafo não eh fortemente conexo.";
        cout << mensagem << endl;
        return false;
    }
    //caso nenhum dos dois, imprimir uma trilha fechada euleriana começando e terminando em v, construida em tempo linear
    return true;
}