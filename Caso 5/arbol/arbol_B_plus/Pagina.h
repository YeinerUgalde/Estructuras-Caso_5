#include <vector>
#include <iostream>


using namespace std;
#ifndef PAGINA
#define PAGINA 1

struct Nodo {
  string nick;
  string oferta;
  string demanda;
  int id;

  Pagina *leftPage = NULL;
  Pagina *rightPage = NULL;
};

lass Pagina{
  private:
    int cant_nodos;
    int size = 0;
    bool rightPagina = false;
    
  public:
    vector<Nodo*> nodos;
    bool hoja = false;

    Pagina(int pCant){
      this->cant_nodos = pCant;
    }
    void addNodo(Nodo *pNodo){
      if(this->size < this->cant_nodos){
        nodos.push_back(pNodo);
        size++;
      }                    
    }
    int getSize(){
        return this->size;
    }

    void setRightPagina(){
      this->rightPagina = true;
    }

    bool is_RightPagina(){
      return this->rightPagina;
    }
 
};
#endif