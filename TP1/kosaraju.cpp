#include <iostream>
#include <stack>
#include <list>

using namespace std;

class Grafo
{
private:
    
    // bem parecida com a função preenche

public:
    int V;          // número de vértices
    list<int> *adj; // lista de adjacência
    // construtor
    Grafo(int V)
    {
        this->V = V;
        adj = new list<int>[V]; // cria as listas
    }

    // adiciona arestas
    void adicionarAresta(int i, int j)
    {
        // adiciona "j" à lista de adjacência de "i"
        adj[i].push_back(j);
    }

    // obtém o grafo transposto
};

//#------------------------------------------------------------------------------------------------------#

void preenche(Grafo G, int v, bool visitados[], stack<int> &pilha){
        // marca o vértice atual como visitado
        visitados[v] = true;

        // percorre os adjacentes de v
        list<int>::iterator i;
        for (i = G.adj[v].begin(); i != G.adj[v].end(); i++)
        {
            if (visitados[*i] == false)
                preenche(G, *i, visitados, pilha);
        }
        pilha.push(v);
}

Grafo obterGrafoTransposto(Grafo G)
{
    Grafo grafo_transposto(G.V);

    for (int v = 0; v < G.V; v++)
    {
        list<int>::iterator i;
        for (i = G.adj[v].begin(); i != G.adj[v].end(); i++)
        {
            // insere no novo grafo
            grafo_transposto.adj[*i].push_back(v);
        }
    }

    return grafo_transposto;
}

void DFS(Grafo G, int v, bool visitados[])
{
    // marca o vértice atual como visitado
    visitados[v] = true;

    // imprime o vértice
    cout << v << " ";

    // percorre os adjacentes de v
    list<int>::iterator i;
    for (i = G.adj[v].begin(); i != G.adj[v].end(); i++)
    {
        if (visitados[*i] == false)
            DFS(G, *i, visitados);
    }
}

void imprimirComponentes(Grafo G)
{
    stack<int> pilha;
    bool *visitados = new bool[G.V];

    // marca todos como não visitados
    for (int i = 0; i < G.V; i++)
        visitados[i] = false;

    // preenche a pilha
    for (int i = 0; i < G.V; i++)
    {
        if (visitados[i] == false)
            preenche(G, i, visitados, pilha);
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



int main(int argc, char *argv[])
{
    Grafo g(4);

    g.adicionarAresta(0, 1);
    g.adicionarAresta(1, 2);
    g.adicionarAresta(2, 3);
    g.adicionarAresta(3, 0);

    imprimirComponentes(g);

    return 0;
}