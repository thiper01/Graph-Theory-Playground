/*
Autor: Prof. Dr. Ivan CArlos Alc�ntara de Oliveira
Data da Cria��o: 22/02/2022.
Implementa��o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza��o de um grafo dirigido.
*/
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;
#define INFINITY std::numeric_limits<int>::max()

// Defini��o de uma classe para armezanar um grafo
// como Matriz de adjac�ncia
// Para usar esse arquivo, basta fazer a inclus�o
// no seu programa "#include "TGrafoMatriz.cpp"

struct Aresta // criação do struct para conseguir guardar as informações
{
    bool isLigado;
    double distancia;
    int tempo;
};

class TGrafo
{
private:
    int n;        // quantidade de v�rtices
    int m;        // quantidade de arestas
    Aresta **adj; // Define a matriz como matriz de structs, com os pontos e os atriutos do vertices
    vector<string> apelidos{}; // vetor de string para guardar os apelidos
    int **distTempo, **rota;
    double **distDist;

public:
    TGrafo(int n);
    TGrafo();
    void insereA(int v, int w, double d, int t);
    void removeA(int v, int w);
    void show();
    void show2();
    void imprimirLocalidades();
    void imprimirLigacoes(int metrica);
    int getQtdVertices();
    void adicionarApelido(string apelido);
    void localSucessores(int local);
    void localAntecessores(int local);
    void prim(int metrica);
    void floyd();
    void caminhoMinimo(int origem, int destino, int metrica);
    double getByMetrica(int i, int j, int metrica);
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
    Aresta **adjac = new Aresta *[n];
    double **distanciaDistancia = new double *[n];
    int **distanciaTempo = new int *[n];
    int **rotasMatriz = new int *[n];
    for (int i = 0; i < n; i++){
        adjac[i] = new Aresta[n];
        distanciaDistancia[i] = new double[n];
        distanciaTempo[i] = new int[n];
        rotasMatriz[i] = new int[n];
    }
      
    adj = adjac;
    distDist = distanciaDistancia;
    distTempo = distanciaTempo;
    rota = rotasMatriz;

    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            adj[i][j].isLigado = 0;
            distDist[i][j] = 0;
            distTempo[i][j] = 0;
            rota[i][j] = 0;
        }
           

}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafo::~TGrafo()
{
    n = 0;
    m = 0;
    delete[] * adj;
    cout << "espaco liberado";
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafo::insereA(int v, int w, double d, int t)
{
    // testa se nao temos a aresta
    if (adj[v][w].isLigado == 0)
    {
        adj[v][w].isLigado = 1;
        adj[v][w].distancia = d;
        adj[v][w].tempo = t;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w)
{
    // testa se temos a aresta
    if (adj[v][w].isLigado == 1)
    {
        adj[v][w].isLigado = 0;
        m--; // atualiza qtd arestas
    }
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafo::show()
{
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\n";
        for (int w = 0; w < n; w++)
            if (adj[i][w].isLigado == 1)
                cout << "Adj[" << i << "," << w << "]= 1"
                     << " ";
            else
                cout << "Adj[" << i << "," << w << "]= 0"
                     << " ";
    }
    cout << "\nfim da impressao do grafo." << endl;
}

void TGrafo::show2()
{
    cout << "Numero de vertices n: " << n << endl;
    cout << "Numero de arestas m: " << m << "\n\n";

    cout << "    ";
    for(int i = 0; i < n; i++){
        cout << i << " ";
    }
    for (int i = 0; i < n; i++)
    {
        cout << "\n";
        cout << i << " | ";
        for (int w = 0; w < n; w++)
        {
            if (adj[i][w].isLigado == 1)
                cout << adj[i][w].distancia
                     << " ";
            else
                cout << "∞"
                     << " ";
        }
    }
    cout << "\n\nfim da impressao do grafo." << endl;
}

//Método para adicionar o apelido no vetor de string
void TGrafo::adicionarApelido(string apelido)
{
    apelidos.push_back(apelido);
}

// método para retornar a quantidade de vertices (GetVertices)
int TGrafo::getQtdVertices()
{
    return n;
}

double TGrafo::getByMetrica(int i, int j, int metrica){
    if(metrica == 1){
        return adj[i][j].distancia;
    }
    else{
        return adj[i][j].tempo;
    }
}

// métodos para imprimir as localidades
void TGrafo::imprimirLocalidades()
{   
    cout << "\n IMPRIMINDO LOCALIDADES:\n";
    for (int i = 0; i < n; i++) //imprime todos os vertices, juntamente com o seu indice que relaciona com o seu numero
    {
        cout << i + 1 << " - " << apelidos[i] << endl; // somando i+1 para pegar o indice, pois a lista começa no "1", mas o indice começa no 0;
    }
}

void TGrafo::imprimirLigacoes(int metrica)
{
    cout << "\n IMPRIMINDO LOCALIDADES:\n";
    //verifica a métrica
    if (metrica == 1) 
    {
        cout << "PARTIDA \t  -----------> \t  CHEGADA \t DISTANCIA (em kilometros)" << endl;
        //loop duplo para percorrer a matriz
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++)
            {
                if (adj[i][j].isLigado == 1) // verifica se ta ligado
                {
                    if (apelidos[i].length() < 7)
                    {
                        cout << apelidos[i] << " \t\t\t ---> \t ";
                    }else if (apelidos[i].length() < 15)
                    {
                        cout << apelidos[i] << " \t\t ---> \t ";
                    }else
                    {
                        cout << apelidos[i] << " \t ---> \t ";
                    }                    

                    if (apelidos[j].length() < 6)
                    {
                       cout << apelidos[j] << " \t\t\t " << adj[i][j].distancia << " km" << endl;
                    }else if (apelidos[j].length() < 14)
                    {
                        cout << apelidos[j] << " \t\t " << adj[i][j].distancia << " km" << endl;
                    }else
                    {
                        cout << apelidos[j] << " \t " << adj[i][j].distancia << " km" << endl;
                    }
                }
            }
        }
    }
    else{
        cout << "PARTIDA  ----------->  CHEGADA     TEMPO (em minutos)" << endl;
        //loop duplo para percorrer a matriz
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj[i][j].isLigado == 1)// verifica se ta ligado
                {
                    cout << apelidos[i] << " \t ---> \t " << apelidos[j] << " \t " << adj[i][j].tempo << " min" << endl;
                }
            }
        }
    }
}

// método para imprimir os sucessores do seguinte local:
void TGrafo::localSucessores(int local)
{
    //verifica se o vertice existe
    if(local < 0 or local > n-1)
    {
        cout << "\nNÃO EXISTE ESSA LOCALIDADE\n";
    }
    else
    {
        
        int contador = 0;//contador para verificar se não terá nenhuma ligação
        cout << "Locais acessados pelo seguinte local: " << apelidos[local] << endl;
        cout << "LOCAL                   DISTANCIA                   TEMPO" << endl;
        //loop para percorrer a lista HORIZONTALMENTE a matriz do local escolhido, verificados todos que são possiveis acessar pelo local escolhido
        for (int i = 0; i < n; i++)
        {
            if (adj[local][i].isLigado == 1)
            {
                cout << apelidos[i] << "   " << adj[local][i].distancia << "   " << adj[local][i].tempo << endl;
            }
            else
            {
                contador++;
            }
            //verifica se não tem nenhuma ligação
            if (contador == n)
            {
                cout << "\nNÃO É POSSÍVEL ACESSAR NENHUMA LOCALIDADE A PARTIR DESSE\n";
            }
        }
    }
}

void TGrafo::localAntecessores(int local)
{   
    //verifica se o vertice existe
    if(local < 0 or local > n-1)
    {
        cout << "\nNÃO EXISTE ESSA LOCALIDADE\n";
    }
    else
    {
        int contador = 0; //contador para verificar se não terá nenhuma ligação
        cout << "Locais que acessam o seguinte local: " << apelidos[local] << endl;
        cout << "LOCAL                   DISTANCIA                   TEMPO" << endl;
        //loop para percorrer a lista VERTICALMENTE a matriz do local escolhido, verificados todos que acessam o locao escolhido
        for (int i = 0; i < n; i++)
        {
            if (adj[i][local].isLigado == 1)
            {
                cout << apelidos[i] << "   " << adj[i][local].distancia << "   " << adj[i][local].tempo << endl;
            }
            else
            {
                contador++;
            }
            //verifica se não tem nenhuma ligação
            if (contador == n+1)
            {
                cout << "\nNENHUMA LOCALIDADE ACESSA ESTÁ LOCALIDADE\n";
            }
        }
    }
}

void TGrafo::floyd()
{   
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rota[i][j] = i;
            if (i == j)
            {
                distDist[i][j] = 0;
                distTempo[i][j] = 0;
            }
            else if (adj[i][j].isLigado != 0)
            {
                distDist[i][j] = getByMetrica(i,j,1);
                distTempo[i][j] = getByMetrica(i,j,2);
            }
            else
            {
                distDist[i][j] = INFINITY;
                distTempo[i][j] = INFINITY;
            }
            if (i != j)
            {
                if (distDist[i][j] < INFINITY)
                {
                    rota[i][j] = j;
                }
                else
                {
                    rota[i][j] = 0;
                }
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j && distDist[i][j] > distDist[i][k] + distDist[k][j] && distDist[i][k] != INFINITY && distDist[k][j] != INFINITY)
                {
                    distDist[i][j] = distDist[i][k] + distDist[k][j];
                    distTempo[i][j] = distTempo[i][k] + distTempo[k][j];
                    rota[i][j] = rota[i][k];
                }
            }
        }
    }

}

void TGrafo::caminhoMinimo(int origem, int destino, int metrica){
    cout << "ROTA: " << rota[origem][destino] << endl;
    int aux = origem;
    cout << "\nMelhor rota de " << apelidos[origem] << " para " << apelidos[destino] << ":" <<endl;
    cout << "(" << origem+1;
    while(aux != destino){
        if(rota[aux][destino] != 0){
            cout << ", " << rota[aux][destino]+1;
            aux = rota[aux][destino];
        }
        else{
            cout << " CAMINHO INTERROMPIDO!" << endl;
            cout << "Nao e possivel chegar nessa localidade a partir dessa origem" << endl;
            return;
        }
    }
    cout << ")" << endl;

    if(metrica == 1){
        cout << "\nCusto do caminho (em kilometros) : " << distDist[origem][destino];
    }
    else{
        cout << "\nCusto do caminho (em minutos): " << distTempo[origem][destino];
    }

}

void TGrafo::prim(int metrica){
    cout << "\nINICANDO METODO PRIM:\n";
    vector<int> T = {0};    //Vertices passado
    vector<int> E;          //Vetor com os vertices.
    int valor;              //Valor do custo para auxiliar na escolha
    double custo = 0;          //Custo do caminho iniciado como zero
    int k, i, vext, vint;   //Criando variaveis

    //procedimento PRIM (T);
    while(T.size() != n){
        valor = INFINITY;   //Inicialmente o valor é maximo
        //para todo k  T faça      para todo vértice k pertencente a árvore T
        for(k = 0; k < T.size(); k++){  //Percorre todos os vertices de T
            //para todo i  V - T faça       procura a aresta menor aresta em V-T
            for(i = 0; i < n; i++){ //Verifica todas as ligações do vertice de T sendo analisado
                if ( find(T.begin(), T.end(), i) == T.end() ){ //Verifica se o vertice já não está em T. Caso esteja, ja ha caminho e desconsidera
                    if(adj[T[k]][i].isLigado == 1){            //caso tenha ligação
                        if(getByMetrica(T[k], i, metrica) < valor){    //verifica se o valor é maior
                            valor = getByMetrica(T[k], i, metrica);    //troca o valor
                            vint = T[k];                       //define vertice interno
                            vext = i;                          //define vertice externo
                        }
                    }
                }
            }
        }
        custo += getByMetrica(vint, vext, metrica); //Adiciona o custo ao total7
        T.push_back(vext);  //Adiciona o vertice externo para os ja verificado
        E.push_back(vint);  //Define o vertice origem
        E.push_back(vext);  //Define o vertice de destino

    }
    cout << "\nCaminho de custo minimo:\n";
    for(i = 0; i < E.size() ;  i+=2){ // todas as ligações que devem ser consideradas
        cout << "(" << E[i]+1<< "," << E[i+1]+1 << ")"; 
    }

    cout << "\nQuantidade de ligações: " << T.size();

    cout << "\nCusto final: " << custo << endl;

}
