/*
Autor: Prof. Dr. Ivan CArlos Alc�ntara de Oliveira
Data da Cria��o: 22/02/2022.
Implementa��o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza��o de um grafo dirigido.
*/
#include <iostream>

using namespace std;
#include "pilhaClasse.h"
#include "filaCircularClasse.h"
// Defini��o de uma classe para armezanar um grafo
// como Matriz de adjac�ncia
// Para usar esse arquivo, basta fazer a inclus�o
// no seu programa "#include "TGrafoMatriz.cpp"
class TGrafo
{
private:
    int n;     // quantidade de v�rtices
    int m;     // quantidade de arestas
    int **adj; // matriz de adjac�ncia
    
public:
    TGrafo(int n);
    void insereA(int v, int w);
    void removeA(int v, int w);
    void show();
    void percorrerProfundidade();
    void percorrerLargura();
    ~TGrafo();
};

// Construtor do TGrafo, respons�vel por
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafo::TGrafo(int n)
{   
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0;
    // aloca da matriz do TGrafo
    int **adjac = new int *[n];
    for (int i = 0; i < n; i++)
        adjac[i] = new int[n];
    adj = adjac;
    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafo::~TGrafo()
{
    n = 0;
    m = 0;
    delete[] * adj;
    cout << "espa�o liberado";
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafo::insereA(int v, int w)
{
    // testa se nao temos a aresta
    if (adj[v][w] == 0)
    {
        adj[v][w] = 1;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w)
{
    // testa se temos a aresta
    if (adj[v][w] == 1)
    {
        adj[v][w] = 0;
        m--; // atualiza qtd arestas
    }
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafo::show()
{
    cout << "Numero de vertices n: " << n << endl;
    cout << "Numero de arestas m: " << m << "\n\n";

    cout << "    0 1 2 3 4 5 6 7";
    for (int i = 0; i < n; i++)
    {
        cout << "\n";
        cout << i << " | ";
        for (int w = 0; w < n; w++){
            if (adj[i][w] == 1)
                cout << "1"
                     << " ";
            else
                cout << "0"
                     << " ";
                       }
    }
    cout << "\n\nfim da impressao do grafo." << endl;

}

void TGrafo::percorrerProfundidade(){

    cout << "\n==========/-/========= PERCORRENDO GRAFO (PROFUNDIDADE) ==========/-/=========\n";
    
    int marcadosCount = 0;
    int marcados[n]; //vetor dos marcados
    for(int j = 0; j < n; j++){ //inicializa tudo com 0
        marcados[j] = 0;
    }
    int nNode, mNode;
    Pilha* pilha = new Pilha();

    //1. Visita-se um nó n previamente selecionado;
    nNode = 0;
    //2. Marca o nó n;
    marcados[0] = 1;
    cout << "\nMARCANDO NÓ => " << 0;
    //3. Empilha n em uma pilha P;
    pilha->push(nNode);
    //4. Enquanto a pilha P não estiver vazia;
    while(pilha->isEmpty() == false){
        // 4.1 O nó n é desempilhado da pilha P; (n <- pop(P) (atribuição))
        cout << "\nRemovendo o elemento do topo da pilha " << pilha->topo();  
        pilha->pop();
        if(pilha->isEmpty() == false){
            nNode = pilha->topo();
        }
        //4.2 Para cada nó m não marcado e adjacente a n faça
        for(int i = 0; i < n; i++){
            cout << "\nVerificando: " << nNode << "-->" << i << " = " << adj[nNode][i];
            if(adj[nNode][i] == 1 and marcados[i] == 0){
                //4.2.1 O nó m é visitado;
                mNode = i;
                //4.2.2 O nó n é colocado na pilha P;
                pilha->push(nNode);
                //4.2.3 O nó m é marcado;
                cout << "\nMARCANDO NÓ => " << i;
                marcados[i] = 1;
                i = -1; //Reinicia o contador, colocando "-1" pois o for já sobe somando, então para 0, precisa ser -1
                //4.2.4 Troca o valor de n para m (n <- m (atribuição)).
                nNode = mNode;
            }
            
        }
        
    }

    cout << "\n\n ==========/-/========= FIM DO PERCURSO (PROFUNDIDADE)  ==========/-/========= \n";

}

void TGrafo::percorrerLargura(){

    cout << "\n==========/-/========= PERCORRENDO GRAFO (LARGURA) ==========/-/=========\n";

    int marcadosCount = 0;
    int marcados[n]; //vetor dos marcados
    for(int j = 0; j < n; j++){ //inicializa tudo com 0
        marcados[j] = 0;
    }
    int nNode, mNode;
    FilaCircular* fila = new FilaCircular();
    //1. Visita-se um nó n previamente selecionado;
    nNode = 0;
    //2. Marca o nó n;
    cout << "\nMARCANDO NÓ => " << 0;
    marcados[0] = 1;
    //3. Inserir n em uma fila F;
    fila->enqueue(nNode);
    //4. Enquanto a fila F não estiver vazia;
    while(fila->qIsEmpty() == false){
        //4.1 Retira um elemento da fila F e atribui ao nó n;
        cout << "\nRemovendo o elemento do topo da fila " << fila->front();  
        nNode = fila->front();
        fila->dequeue();
        ////4.2 Para cada nó m não marcado e adjacente a n faça
        for(int i = 0; i < n; i++){
            cout << "\nVerificando: " << nNode << "-->" << i << " = " << adj[nNode][i];
            if(adj[nNode][i] == 1 and marcados[i] == 0){
                //4.2.1 O nó m é visitado;
                mNode = i;
                //4.2.2 O nó m é colocado na fila F;
                fila->enqueue(mNode);
                //4.2.3 O nó m é marcado;
                cout << "\nMARCANDO NÓ =====================> " << i;
                marcados[i] = 1; 
               
            }
        }
    }

    cout << "\n\n ==========/-/========= FIM DO PERCURSO (LARGURA) ==========/-/========= \n";
}

