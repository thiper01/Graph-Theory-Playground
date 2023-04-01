#include <iostream>
using namespace std;

#include "TGrafoMatriz.cpp"

int main()
{
    // Cria um objeto para um Grafo com 4 v�rtices
    // Armazendo em uma lista de adPjac�ncia
    TGrafo g(8);
    // insere as arestas do grafo
    g.insereA(0, 1);
    g.insereA(0, 2);
    g.insereA(0, 4);
    g.insereA(1, 3);
    g.insereA(1, 4);
    g.insereA(2, 5);
    g.insereA(2, 6);
    g.insereA(3, 7);
    g.insereA(4, 7);
    g.insereA(5, 4);
    g.insereA(5, 6);
    g.insereA(6, 7);
    // mostra o grafo preenchido
    g.show();

    g.percorrerProfundidade();
    g.percorrerLargura();
    
    return 0;
}