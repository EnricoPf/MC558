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

//##Implementação modificada do algoritmo de Kosaraju, que possui complexidade O(V+E) para encontrar componentes fortemente conexos, se houver mais de um CFC, o grafo inteiro não é fortemente conexo
//Preenche o stack com vertices em ordem de finalização crescente 
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
//obtem a transposta do grafo
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
//Realiza uma busca em profundidade (Depth-first), marcando os vértices como visitados
void DFS(Grafo G, int v, bool visitados[]){
    visitados[v] = true;
    list<int>::iterator i;
    for (i = G.vizinhos[v].begin(); i != G.vizinhos[v].end(); i++){
        if (visitados[*i] == false)
            DFS(G, *i, visitados);
    }
}
//Função que encontra e identifica a presença de Componentes fortemente conectados
bool testaComponentes(Grafo G){
    stack<int> pilha;
    //Marca todos os vertices como não visitados
    bool *visitados = new bool[G.V];
    for (int i = 0; i < G.V; i++){
        visitados[i] = false;
    }
    //Preenche vertices no stack de acordo com tempo de finalização
    for (int i = 0; i < G.V; i++){
        if (visitados[i] == false){
            preenche(G, i, visitados, pilha);
        }
    }
    //Cria o grafo transposto
    Grafo gt = obterGrafoTransposto(G);
    //Marca todos como não visitados para a segunda DFS
    for (int i = 0; i < G.V; i++)
        visitados[i] = false;
    //contador para o numero de vezes que foram encontrados Componentes Fortemente Conexos
    int n_vezes = 0;
    //Processa or vertices na ordem na pilhas
    while (!pilha.empty()){
        int v = pilha.top();
        pilha.pop();
        // encontra cada componente fortemente conexa
        if (visitados[v] == false){
            DFS(gt, v, visitados);
            //aqui ele trocaria de linha
            n_vezes++;
        }
    }
    //se apenas um CFC foi encontrado, o grafo é inteiro fortemente conexo, se não, não
    if (n_vezes == 1)
        return true;
    return false;
}

//#-------------------------------------------------------------------------#

void find_way(Grafo G, int* trilha){
    //copia a lista de adjacencias do grafo para adj
    list <int>* adj = new list<int>[G.V];
    list<int>::iterator j;    
    for (int i = 0; i < G.V; i++){
        for (j = G.vizinhos[i].begin(); j != G.vizinhos[i].end();j++){
            adj[i].push_front(*j);
        }
    }
    //circuito é onde salvaremos a trilha durante o processamento     
    vector<int> circuit;
    //edge_counter representa o numero de arestas saindo de um vertice
    unordered_map<int,int> edge_counter;
    stack<int> curr_trail;
    int curr_v,next_v;
    //contamos o numero total de arestas
    for (int i = 0; i < G.V;i++){
        edge_counter[i] = adj[i].size();
    }
    //começamos no vertice 0 e colocamos ele na trilha atual
    curr_v = 0;
    curr_trail.push(0);
    while (!curr_trail.empty()){
        //se houver quaisquer arestas sobrando partindo do vertice atual
        if (edge_counter[curr_v]){
            //adiciona-o a trilha atual
            curr_trail.push(curr_v);
            //acha o proximo vertice a partir da aresta
            next_v = adj[curr_v].back();
            //marca a aresta como indisponivel e a remove
            edge_counter[curr_v]--;
            adj[curr_v].pop_back();  
            //avança para o próximo vertice
            curr_v = next_v;
        }else{
            //backtracking para encontrar o resto da trilha 
            circuit.push_back(curr_v);
            curr_v = curr_trail.top();
            curr_trail.pop();
        }
    }
    //desinverte a ordem de circuito e passa para o vetor trilha
    for (int i=circuit.size()-1; i>=0; i--)
    {
        trilha[k] = circuit[i];
    }
    return;
}

bool trilha_euleriana(int n, int m, Grafo G, int* origem, int* destino, int* trilha, string &mensagem, int RA){
    //n - numero de vertices, m - numero de arestas
    list<int>::iterator j;    
    int k = 0;
    vector<int> entrada(n,0);
    vector<int> saida(n,0);
    //itera sobre a lista de adjacencia para achar o grau de entrada e saida
    for (int i = 0; i < n; i++){
        for (j = G.vizinhos[i].begin(); j != G.vizinhos[i].end();j++){
            saida[i]++;
            entrada[*j]++;
            k++;
        }
    }
    //se existir u e V(G) tal que grau de entrada de u != grau de saida, mostrar "Erro: Existe vértice inviável." e interromper execução    
    for (int i = 0; i < n; i++){
        if (entrada[i] != saida[i]){
            mensagem = "Erro: Existe vértice inviável.";
            return false;
        }
    }
    //se G não for fortemente conexo, mostrar "Erro: Grafo não eh fortemente conexo." e interromper conexão
    if (!(testaComponentes(G))){
        mensagem = "Erro: Grafo não eh fortemente conexo.";
        return false;
    }
    //caso nenhum dos dois, imprimir uma trilha fechada euleriana começando e terminando em v, construida em tempo linear
    //usar o vetor trilha, preciso achar uma trilha euleriana ainda
    find_way(G,trilha);
    for (int i = 0; i < (G.M);i++){
        origem[i] = trilha[i];
        destino[i] = trilha[i+1];
    }
    return true;
}