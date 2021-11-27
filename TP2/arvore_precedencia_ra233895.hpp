#ifndef ARVORE_PRECEDENCIA_HPP
#define ARVORE_PRECEDENCIA_HPP

using namespace std;

#include <string.h>
#include <stdbool.h>
#include <list>
#include <string>
#include "grafo.hpp"

bool arvore_precedencia (int n, int m, int W, Grafo g, string &mensagem, int RA, int* pred, int* dist);
#endif