// Fernando Bertholino - 41906861 – 06G
// Gabriel Vitor - 41908961 – 06G
// Thiago Perissinotti - 41903447 – 06G
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TGrafoMatriz.cpp"

#define menu "\nMenu Grafos - Pinheiros:\n1 - Ler dados do  Bairro\n2 - Mostrar Localidades\n3 - Mostrar Ligações\n4 - Mostrar Locais Alcançados Diretamente por Origem\n5 - Mostrar Locais que Alcançam Origem Diretamente;\n6 - Determinar rota mínima\n7 - Montar Estrutura de Custo Mínimo\n8 - Encerrar\nDigite uma opcao: "

vector<string> readTextFile(ifstream &file, vector<string> words, int *n) // Método para ler o txt e guardar em um vetor de strings
{
    string line;
    string space_delimiter = " ";
    size_t pos = 0;
    getline(file, line);
    *n = stoi(line);
    while (getline(file, line))
    {
        while ((pos = line.find(space_delimiter)) != string::npos)
        {
            words.push_back(line.substr(0, pos));
            line.erase(0, pos + space_delimiter.length());
        }
        if (!line.empty())
        {
            words.push_back(line.erase(line.size() - 1));
        }
    }
    return words;
}

int main()
{
    ifstream vertices("localidade.txt"), arestas("ligacao.txt"); // arquivos txt
    vector<string> verticesLista{}, arestasLista{};              // vetores com as informações do txt
    int verticesQtd, arestasQtd;                                 // inteiros para guardar a quantidade de vertices e arestas total
    TGrafo *grafo;                                               // inicializa o grafo
    bool grafoExiste = false;                                    // booleana para verificar se o grafo foi criado ou não
    int local, metrica;                                          // inteiros para gerenciar as opções
    int origem, destino;

    while (true)
    {
        int option;
        cout << menu; // imprime o menu definido lá em cima no "#define"
        cin >> option;

        if (option == 1 and grafoExiste == false)
        { // metodo para ler os grafos
            arestasLista = readTextFile(arestas, arestasLista, &arestasQtd);
            verticesLista = readTextFile(vertices, verticesLista, &verticesQtd);
            grafo = new TGrafo(verticesQtd);

            for (int j = 1; j < verticesLista.size(); j = j + 2) // loop para ir adicionando os apelidos na lista dos apelidos (os indices se relacionam com os vertices)
            {
                grafo->adicionarApelido(verticesLista[j]);
            }

            for (int i = 0; i < arestasLista.size(); i = i + 4) // loop para guardar as informações da aresta
            {
                grafo->insereA(stoi(arestasLista[i]) - 1, stoi(arestasLista[i + 1]) - 1, stod(arestasLista[i + 2]), stoi(arestasLista[i + 3])); // pegando i -1 para iniciar no indice 0, ao invés do 1
            }
            grafoExiste = true;
            grafo->floyd();
            cout << "\nGRAFO CRIADO COM SUCESSO!\n";
        }
        else if (option == 1 and grafoExiste)
        { // verifica se o grafo já foi criado
            cout << "\nGrafo já foi criado!\n";
        }
        else if (option == 2 and grafoExiste)
        { // imprimir as localidades
            grafo->imprimirLocalidades();
        }
        else if (option == 3 and grafoExiste)
        { // imprimi as ligacoes
            cout << "\nSelecione uma metrica a ser apresentada:\n";
            cout << "1 - Distancia (Em kilometros) \n2 - Tempo (Em minutos)" << endl;
            cin >> metrica; // escolhe a metrica, se deseja em distancia ou tempo
            if (metrica == 1 or metrica == 2)
            {
                grafo->imprimirLigacoes(metrica);
            }
            else
            {
                cout << "\nNÃO EXISTE ESSA METRICA!\n";
            }
        }
        else if (option == 4 and grafoExiste)
        { // Mostrar Locais Alcançados Diretamente por Origem
            grafo->imprimirLocalidades();
            cout << "\n Escolha um local da lista: \n";
            cin >> local; // escolhe localidade que deseja escolher
            grafo->localSucessores(local - 1);
        }
        else if (option == 5 and grafoExiste)
        {
            grafo->imprimirLocalidades();
            cout << "\n Escolha um local da lista: \n";
            cin >> local; // escolhe localidade que deseja escolher
            grafo->localAntecessores(local - 1);
        }
        else if (option == 6 and grafoExiste)
        {
            grafo->imprimirLocalidades();
            cout << "\n Escolha um local para a origem: \n";
            cin >> origem; // escolhe localidade que deseja escolher
            cout << "\n Escolha um local para o destino: \n";
            cin >> destino;
            cout << "\nSelecione uma metrica a ser apresentada:\n";
            cout << "1 - Distancia (Em kilometros) \n2 - Tempo (Em minutos)" << endl;
            cin >> metrica; // escolhe a metrica, se deseja em distancia ou tempo
            if (metrica == 1 or metrica == 2)
            {
                grafo->caminhoMinimo(origem - 1, destino - 1, metrica);
            }
            else
            {
                cout << "\nNÃO EXISTE ESSA METRICA!\n";
            }
        }
        else if (option == 7 and grafoExiste)
        {
            cout << "\nSelecione uma metrica a ser apresentada:\n";
            cout << "1 - Distancia (Em kilometros) \n2 - Tempo (Em minutos)" << endl;
            cin >> metrica; // escolhe a metrica, se deseja em distancia ou tempo
            if (metrica == 1 or metrica == 2)
            {
                grafo->prim(metrica);
            }
            else
            {
                cout << "\nNÃO EXISTE ESSA METRICA!\n";
            }
        }
        else if (option == 8)
        {
            cout << "\nFim do programa.\n";
            return 0;
        }
        else if (grafoExiste == false)
        {
            cout << "\nLeia os dados primeiros para iniciar um grafo!\n";
        }

        else
        {
            cout << "\nOpcao invalida" << endl;
        }
    }
    return 0;
}