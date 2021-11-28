/*
arvore_precedencia_ra
Neste arquivo voce deve implementar sua rotina de criaçao da trilha
*/

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include "grafo.hpp"
#include "arvore_precedencia_ra233895.hpp"
#define INF 0x3f3f3f3f

using namespace std;

bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int *pred, int *dist)
{
    //inicializamos o vetor de visitados com o estado inicial de cada vetor sendo não visitado
    vector<bool> visitados(n, false);
    //colocamos o estado inicial do predecessor de cada nó como não valido e a distância da origem até cada nó como sendo infinito
    for (int i = 0; i < n; i++)
    {
        pred[i] = -1;
        dist[i] = INF;
    }
    //começamos com a origem da árvore no nó 0, e a distancia de 0 até ele mesmo é 0
    dist[0] = 0;
    //usamos uma fila de prioridade, ou um heap, para organizar os vértices, em que as operações são de complexidade, no maximo, O(log(V))
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push(make_pair(dist[0], 0));
    //Aqui temos uma implementação do algoritmo de Dijsktra
    //Que itera uma vez em cada vértice e aresta, através do heap
    //Portanto tem complexidade O((|V| + |E|)* log(V))
    while (!fila.empty())
    {
        //tiramos o nó que estiver no topo do heap e salvamos seu indice em u
        pair<int, int> top = fila.top();
        int u = top.second;
        fila.pop();
        //Se o vértice ainda não tiver sido visitado, entramos nesse if
        if (visitados[u] == false)
        {
            visitados[u] = true;

            list<pair<int, int>>::iterator curr;
            //iteramos entre todos os vértices adjacentes ao vértice atual e damos relax no caminho deles
            for (curr = g.adj[u].begin(); curr != g.adj[u].end(); curr++)
            {
                int v = (*curr).first;
                int weight = (*curr).second;
                //Como essa porção do código passa por todos os vértices alcançaveis por arestas
                //Fazemos o teste se há algum peso inválido aqui, se ele estiver fora do intervalo (0,W)
                if ((weight < 0) || (weight > W)){
                    mensagem = "Erro: Existe peso fora do intervalo.";
                    return false;
                }

                //relax (u,v)
                if (dist[v] > (dist[u] + weight))
                {
                    pred[v] = u;
                    dist[v] = dist[u] + weight;
                    fila.push(make_pair(dist[v], v));
                }
            }
        }
    }
    //se tudo correu sem erro, retorna true
    return true;
}