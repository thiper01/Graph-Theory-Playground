/*
   Fila Circular
   Desenvolvimento com Classe
   cria��o: 28/02/2022.
   prof. Dr. Ivan Carlos Alc�ntara de Oliveira
*/
#include <iostream>
using namespace std;

// defini��o de um novo tipo de dado
typedef int Elem;

// constante que indica o Tamanho alocado para a Fila
const int TAM_FILA = 100;

// Classe que representa a fila circular est�tica e sequencial
class FilaCircular {
	private:
		int inicio, fim, qtde;
		Elem e[TAM_FILA];
	public:
		FilaCircular();
		~FilaCircular(){};
		bool qIsEmpty();
		bool qIsFull();
		void enqueue(Elem e);
		Elem dequeue();
		Elem front();
		Elem rear();
		int size();	
};

// Construtor que Inicia a fila vazia
FilaCircular::FilaCircular(){
  inicio = fim = qtde = 0;
}

// verifica se a fila est� vazia
bool FilaCircular::qIsEmpty(){
  if (qtde == 0)
   return true;
  else
   return false;
}
// Verifica se a fila est� cheia
bool FilaCircular::qIsFull(){
  if (qtde == TAM_FILA)
   return true;
  else
   return false;
}
// insere um elemento no final da fila
void FilaCircular::enqueue ( Elem e ){
  if (! qIsFull( )){
    this->e[this->fim++] = e;
    this->fim = this->fim % TAM_FILA;
    this->qtde++;
  }
  else 
    cout << "oveflow - Estouro de Fila";
}
// remove um elemento do final da fila
Elem FilaCircular::dequeue( ){
  Elem aux;
  if (! qIsEmpty( )){
   aux =  this->e[ this->inicio];
   this->inicio = ++this->inicio % TAM_FILA;
   this->qtde--;
   return aux;
  }else{
    cout << "underflow - Esvaziamento de Fila";
    return -1;
  }
}
// retorna quem est� no in�cio da fila
// caso a fila n�o esteja vazia
Elem FilaCircular::front(){
  if (! qIsEmpty())
   return e[inicio];
  else{
    cout << "underflow - Esvaziamento de Fila";
    return -1;
  }	
}
// retorna quem est� no final da fila caso ela n�o esteja vazia
Elem FilaCircular::rear(){
  if (! qIsEmpty()){
   int final = this->fim - 1;
   return this->e[final];
  }else{
    cout << "underflow - Esvaziamento de Fila";
    return -1;
  }	
}

// Retorna o total de elementos da fila
int FilaCircular::size(){
	return qtde;
}

