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

using namespace std;

// Implementação de grafo utilizando lista de adjacência
class Grafo{
	list<int> *vizinhos; // Lista contendo as arestas

public:
	int V; // Quantidade de vértices
    int M; // Quantidade de arestas

	Grafo(int V, int M); 
	void adicionarAresta(int v1, int v2); 
	bool existeAresta(int v1, int v2); 
};

Grafo::Grafo(int V, int M){
	this->V = V; 
    this->M = M;
	vizinhos = new list<int>[V]; 
}

// Criação da aresta (v1, v2) em G.
void Grafo::adicionarAresta(int v1, int v2){
	vizinhos[v1].push_back(v2);
}

// Verifica se existe aresta (v1, v2) em G e retorna true se existe e false caso contrário.
bool Grafo::existeAresta(int v1, int v2){
	if(find(vizinhos[v1].begin(), vizinhos[v1].end(), v2) != vizinhos[v1].end())
		return true;
	return false;
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
    string file = "nome-do-arquivo.txt";
    int origem[]; // Lista contendo os vértices de origem de cada aresta na trilha.
    int destino[]; // Lista contendo os vértices de destino de cada aresta na trilha.
    int trilha[]; // Lista contendo a ordem dos vértices na trilha.
    string mensagem; // String que retorna algum erro no momento da criação da trilha.
    int RA = -1; // RA do aluno que deve ser preenchido na função que irá criar.

	Grafo grafo = criarGrafo(file);

    trilha_euleriana(int n, int m, int origem[], int destino[], int trilha[], string mensagem, int RA)

    if (RA == -1){
        cout<<"Erro: RA informado eh invalido."<<endl;
    }

    if (verificarTrilha(n, m, origem, destino, grafo)){
        // Mostrar a trilha gerada
    }
	return 0;
}