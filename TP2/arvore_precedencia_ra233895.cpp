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


using namespace std;
// rvore_precedencia(grafo.V, grafo.M, grafo.W, grafo, &mensagem, RA, dist, pred)
bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int *pred, int *dist)
{
    vector<bool> visitados(n, false);
    for (int i = 0; i < n; i++)
    {
        pred[i] = -1;
        dist[i] = (W*n)+1;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    for (int origem = 0; origem < n; origem++){
        dist[origem] = 0;

        fila.push(make_pair(dist[origem], origem));

        while (!fila.empty())
        {
            pair<int, int> p = fila.top();
            int u = p.second;
            fila.pop();

            if (visitados[u] == false)
            {
                visitados[u] = true;
                list<pair<int, int>>::iterator it;

                for (it = g.adj[u].begin(); it != g.adj[u].end(); it++)
                {
                    // obtém o vértice adjacente e o custo da aresta
                    int v = it->first;
                    int custo_aresta = it->second;

                    if ((custo_aresta < 0) || (custo_aresta > W)){
                        mensagem = "Erro: Existe peso fora do intervalo.";
                        return false;
                    }

                    // relax(u, v)
                    if (dist[v] > (dist[u] + custo_aresta))
                    {
                        // atualiza a distância de "v" e insere na fila
                        pred[v] = u;
                        dist[v] = dist[u] + custo_aresta;
                        fila.push(make_pair(dist[v], v));
                    }
                }
            }
        }
    }
    return true;
}