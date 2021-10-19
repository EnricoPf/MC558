/*
trilha_euleriana_principal

Arquio principal para a execução do primeiro trabalho prático de MC558.
Qulquer dúvida ou problema com o código, mandar um e-mail para:
hismael.costa@gmail.com
*/

#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stack>
#include <vector>


using namespace std;

// Implementação de grafo utilizando lista de adjacência
class Grafo{

public:
    list<int> *vizinhos; // Lista contendo as arestas
	int V; // Quantidade de vértices
    int M; // Quantidade de arestas

	Grafo(int V, int M); 
	void adicionarAresta(int v1, int v2); 
	bool existeAresta(int v1, int v2); 
};

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
void find_way(Grafo G, int* trilha){
    list <int>* adj (G.vizinhos);
    vector<int> circuit;
    unordered_map<int,int> edge_counter;
    stack<int> curr_trail;
    int curr_v,next_v;
    for (int i = 0; i < G.M;i++){
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

bool trilha_euleriana(int n, int m, Grafo G, int* origem, int* destino, int* trilha, string mensagem, int RA){
    //n - numero de vertices, m - numero de arestas
    list<int>::iterator j;    
    int k = 0;
    vector<int> entrada(n,0);
    vector<int> saida(n,0);
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
    //usar o vetor trilha, preciso achar uma trilha euleriana ainda
    find_way(G,trilha);
    for (int i = 0; i < (G.M+1);i++){
        cout << trilha[i];
    }
    return true;
}



// Verifica se a trilha que o algoritmo encontrou é uma trilha euleriana.
bool verificarTrilha(int n, int m, int origem[], int destino[], Grafo g1){

    if (g1.M != m){ // Quantidade de arestas deve ser a mesma
        return false;
    }else{
        for(int i=0; i<m; i++){
            // Para cada posição i nos vetores origem e destino, verifica se existe
            // a aresta (origem[i], destino[i]) em G.
            int o_i = origem[i];
            int d_i = destino[i];

            if (!g1.existeAresta(o_i, d_i)){ 
                return false;
            }
        } 

        if (destino[m-1] != origem[0]){
            return false;
        }
    }
    return true;
}

// Leitura de um arquivo txt e retorno do grafo descrito neste arquivo.
Grafo criarGrafo(string file){
    ifstream inFile(file.c_str());
    string line;

    // Caso exista algum problema na leitura, um erro será disparado.
    if(!inFile.is_open()){
        cout << "Erro: Problema na leitura do grafo." << endl;
        return Grafo(0,0);
    }

    getline(inFile, line);
    istringstream ss(line); 
    
    // Identificação da quantidade de vértices e arestas contidos na primeira linha do arquivo.
    int n, m;
    ss >> n >> m;

    // Criação do objeto tipo Grafo.
    Grafo grafo(n,m);

    while (getline(inFile, line)){
        istringstream ss(line);     
        int v1, v2;
        ss >>  v1 >> v2;
        // Criação das arestas contidas nas demais linhas do arquivo.
        grafo.adicionarAresta(v1, v2);
    }

    return grafo;
}

int main(){
    string file = "grafo1.txt";

	Grafo grafo = criarGrafo(file);

    //Inicializem as variáveis
    int origem[grafo.M]; // Lista contendo os vértices de origem de cada aresta na trilha.
    int destino[grafo.M]; // Lista contendo os vértices de destino de cada aresta na trilha.
    int trilha[grafo.M+1]; // Lista contendo a ordem dos vértices na trilha.
    string mensagem; // String que retorna algum erro no momento da criação da trilha.
    int RA = 233895; // RA do aluno que deve ser preenchido na função que irá criar.

    if(!(trilha_euleriana(grafo.V, grafo.M, grafo, origem, destino, trilha, mensagem, RA))){
        return 0;
    }

    if (RA == -1){
        cout << "Erro: RA informado eh invalido." << endl;
    }
    //n/V - vertices, m/M - arestas
    //Função verificar trilha não funciona portanto foi ignorada
    if (verificarTrilha(grafo.V, grafo.M, origem, destino, grafo)){
        cout << "Trilha valida possível." << endl;
    }

    //caso nenhum dos dois, imprimir uma trilha fechada euleriana começando e terminando em v, construida em tempo linear
    // Mostrar a trilha gerada
    
	return 0;
}