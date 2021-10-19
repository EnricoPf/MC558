#include "trilha_euleriana_ra233895.hpp"

#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>

#include "grafo.hpp"
using namespace std;

//##----------------Kosaraju-------------------##

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

void find_way(Grafo G, int* trilha){
    list <int>* adj = G.vizinhos;
    vector<int> circuit;
    unordered_map<int,int> edge_counter;
    stack<int> curr_trail;
    int curr_v,next_v;
    for (int i = 0; i < G.V;i++){
        edge_counter[i] = adj[i].size();
    }
    curr_v = 0;
    curr_trail.push(0);
    while (!curr_trail.empty()){
        if (edge_counter[curr_v]){
            curr_trail.push(curr_v);
            next_v = adj[curr_v].back();
            edge_counter[curr_v]--;
            adj[curr_v].pop_back();  
            curr_v = next_v;
        }else{
            circuit.push_back(curr_v);
            curr_v = curr_trail.top();
            curr_trail.pop();
        }
    }
    int k = 0;
    for (int i=circuit.size()-1; i>=0; i--)
    {
        trilha[k] = circuit[i];
        k++;
    }
    return;
}

bool trilha_euleriana(int n, int m, Grafo G, int* origem, int* destino, int* trilha, string &mensagem, int RA){
    //n - numero de vertices, m - numero de arestas
    list<int>::iterator j;    
    int k = 0;
    vector<int> entrada(n,0);
    vector<int> saida(n,0);
    for (int i = 0; i < n; i++){
        for (j = G.vizinhos[i].begin(); j != G.vizinhos[i].end();j++){
            saida[i]++;
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
            cout << mensagem << endl;
            return false;
        }
    }
    //se G não for fortemente conexo, mostrar "Erro: Grafo não eh fortemente conexo." e interromper conexão
    if (!(testaComponentes(G))){
        cout << mensagem << endl;
        return false;
    }
    //caso nenhum dos dois, imprimir uma trilha fechada euleriana começando e terminando em v, construida em tempo linear
    //usar o vetor trilha, preciso achar uma trilha euleriana ainda
    find_way(G,trilha);
    for (int i = 0; i < (G.V+1);i++){
        cout << trilha[i];
    }
    return true;
}