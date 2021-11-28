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
// rvore_precedencia(grafo.V, grafo.M, grafo.W, grafo, &mensagem, RA, dist, pred)
bool arvore_precedencia(int n, int m, int W, Grafo g, string &mensagem, int RA, int *pred, int *dist)
{
    vector<bool> visitados(n, false);
    for (int i = 0; i < n; i++)
    {
        pred[i] = -1;
        dist[i] = INF;
    }
    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push(make_pair(dist[0], 0));

    while (!fila.empty())
    {
        pair<int, int> top = fila.top();
        int u = top.second;
        fila.pop();

        if (visitados[u] == false)
        {
            visitados[u] = true;

            list<pair<int, int>>::iterator curr;

            for (curr = g.adj[u].begin(); curr != g.adj[u].end(); curr++)
            {
                int v = (*curr).first;
                int weight = (*curr).second;

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
    return true;
}