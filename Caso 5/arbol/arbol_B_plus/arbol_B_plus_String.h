#include <iostream>
#include <vector>

using namespace std;

typedef struct Nodo Nodo;
typedef class Pagina Pagina;

struct Nodo {
  string nick;
  string oferta;
  string demanda;
  int id;

  Pagina *leftPage = NULL;
  Pagina *rightPage = NULL;
  
};

class Pagina{
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
    bool addNodo(Nodo *pNodo){
      if(this->size < this->cant_nodos){
        nodos.push_back(pNodo);
        size++;

        cout << "page size: " << size << endl;
        return true;
      }             
      return false;       
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



#ifndef ARBOL_B_PLUS
#define ARBOL_B_PLUS 1
class Arbol_B_Plus_S{
    
    private:
      int orden;
      Pagina *raiz = NULL;

    public:

      Arbol_B_Plus_S(int pOrden){
        this->orden = pOrden;
      }

      Nodo* createNodo(int pID){
        Nodo *newNode = new Nodo();
        newNode->id = pID;
        newNode->leftPage = NULL;
        newNode->rightPage = NULL;
        return newNode;
      }
      Nodo* search2(int pID, Pagina *pPagina){
        Nodo *nodo = NULL;
        Pagina* root = pPagina;
        
        while(root != NULL){     
          cout << "cant: " << root->getSize()<< endl;
          for(int i = 0; i<root->getSize(); i++){
            nodo = root->nodos[i];
            cout << pID << " : "<< nodo->id << endl;
            if(pID == nodo->id){
              return nodo;
            }

            else if(pID > nodo->id && i >= root->getSize()-1){
              cout << "mayor" << endl;
          
              root = nodo->rightPage;
              if(root == NULL){
                return NULL;
              }
              break;
            }
            
            else if(pID < nodo->id ){
              cout << "menor" << endl;
          
              root = nodo->leftPage; 
              if(root == NULL){
                return NULL;
              }
              break;
            }
          }

        }

        
        cout << "No se encontro el nodo" << endl;
        

        return nodo;

      }

      Nodo* search(int pID){
        Nodo *nodo = NULL;
        Pagina* root = this->raiz;
        
        while(root != NULL){     
          cout << "cant: " << root->getSize()<< endl;
          for(int i = 0; i<root->getSize(); i++){
            nodo = root->nodos[i];
            cout << pID << " : "<< nodo->id << endl;
            if(pID == nodo->id){
              return nodo;
            }

            //else if(pID > nodo->id && i >= root->getSize()-1){
            else if(pID > nodo->id){
              cout << "mayor" << endl;
              ;
              if(i >= root->getSize()-1){
                root = nodo->rightPage;
                if(root == NULL){
                  return NULL;
                }
              }else{
                cout << nodo->rightPage << " " << nodo->id << endl;
                search2(pID,nodo->rightPage);
              }
              
              //break;
            }
            
            else if(pID < nodo->id ){
              cout << "menor" << endl;
              cout << nodo->leftPage << endl;
              root = nodo->leftPage; 
              if(root == NULL){
                return NULL;
              }
              break;
            }
          }

        }

        
        cout << "No se encontro el nodo" << endl;
        

        return nodo;

      }
      int getMitad(int pNum){
        if(pNum % 2){
          return (pNum/2)+1;
        }
        return pNum/2;
      }

      Pagina *division(Pagina *pPagina, Nodo* pNodo){
        Pagina *root = pPagina;
        
        int mitad = getMitad(root->getSize());
        if(pNodo->id < root->nodos[mitad]->id){
          mitad-=1;
        }
  
        Nodo *nodo = root->nodos[mitad]; // El nodo de la mitad
        nodo->leftPage = new Pagina(this->orden);
        nodo->rightPage = new Pagina(this->orden);

        cout << "midad: " << nodo->id << endl;

        for(int i = 0; i < mitad; i++){
          nodo->leftPage->addNodo(root->nodos[i]);
          cout << root->nodos[i]->id << endl;
        }

        for(int i = mitad; i < mitad*2; i++){
          nodo->rightPage->addNodo(root->nodos[i]);
          cout << root->nodos[i]->id << endl;
        }

        cout << "segundo" << endl;

        if (pNodo->id < nodo->id){
          nodo->leftPage->addNodo(pNodo);
        }
        else{
          nodo->rightPage->addNodo(pNodo);
        }

        Pagina *pagina = new Pagina(this->orden);
        pagina->addNodo(nodo);
        this->raiz = pagina;
        
        return pagina;
      }

      Pagina* insert(Pagina *pRaiz, int pID, bool pHoja, Nodo* nodoAnt, Pagina* paginaAnt){
        if(pRaiz == NULL){
          cout << "null" << endl;

          pRaiz = new Pagina(this->orden);
          pRaiz->addNodo(this->createNodo(pID));
          if(pHoja){
            pRaiz->hoja = true;
          }
          return pRaiz;
          

        }else if (!pHoja){
          cout << "raiz" << endl;

          Nodo *nodo;
          for(int i = 0; i < pRaiz->getSize(); i++){
            nodo = pRaiz->nodos[i];

            if (pID > nodo->id && i >= pRaiz->getSize()-1){
              Pagina *pagina = nodo->rightPage;
              nodo->rightPage = insert(pagina, pID, pRaiz->hoja, nodo, pRaiz);
              nodo->rightPage->setRightPagina();
              pRaiz->nodos[i] = nodo;
              //pagina = new Pagina(this->orden);
            }else if(pID < nodo->id){
              Pagina *pagina = nodo->leftPage;
              nodo->leftPage = insert(pagina, pID, pRaiz->hoja, nodo, pRaiz);
              pRaiz->nodos[i] = nodo;
              break;
              //pagina = new Pagina(this->orden);

            } //Evaluar en caso de igualdad     


          }
          

        }else if(pHoja){
          
          cout << pID << endl;
          bool add = false;

          if(pRaiz->getSize() < this->orden){
            Nodo *nodo;
            for(int i = 0; i < pRaiz->getSize(); i++){
              nodo = pRaiz->nodos[i];
           
              if(pID > nodo->id && i >= pRaiz->getSize()-1){
                
                if(nodo->rightPage == NULL){
                  nodo->rightPage =  new Pagina(this->orden);
                  nodo->rightPage->setRightPagina();
                }
                add = nodo->rightPage->addNodo(createNodo(pID));
                
                
                
              }
              else if(pID < nodo->id){
             
                if(nodo->leftPage == NULL){
                  nodo->leftPage = new Pagina(this->orden);
                }
                add = nodo->leftPage->addNodo(createNodo(pID));
                break;
                
              }
            }

          }
          if(!add){
            Pagina *root;
            Nodo* nodo1;
            for(int i = 0; i < pRaiz->getSize(); i++){
              nodo1 = pRaiz->nodos[i];           
              if(pID > nodo1->id && i >= pRaiz->getSize()-1){
                root = nodo1->rightPage;
                nodoAnt = nodo1;
                paginaAnt = pRaiz;
                break;
              }
              if(pID < nodo1->id){
                root = nodo1->leftPage;
                nodoAnt = nodo1;
                paginaAnt = pRaiz;
                break;
              }
            }

            int mitad = getMitad(root->getSize());
            if(pID < root->nodos[mitad]->id){
              mitad-=1;
            }
  
            Nodo *nodo = root->nodos[mitad]; // El nodo de la mitad
            if(nodo->leftPage == NULL){
              cout << "left: "<< nodo->id << endl<< endl;
              nodo->leftPage = new Pagina(this->orden);
            }
            if(nodo->rightPage == NULL){
              nodo->rightPage = new Pagina(this->orden);
            }
            
    
            cout << "midad: " << nodo->id << endl;

            for(int i = 1; i < mitad; i++){
              nodo->leftPage->addNodo(root->nodos[i]);
              cout << root->nodos[i]->id << endl;
            }

            for(int i = mitad; i < mitad*2; i++){
              nodo->rightPage->addNodo(root->nodos[i]);
              cout << root->nodos[i]->id << endl;
            }

            cout << "segundo" << endl;

            if(pID < nodo->id){
              nodo->leftPage->addNodo(createNodo(pID));
            }else{
              nodo->rightPage->addNodo(createNodo(pID));
            }
            cout << "pag: " << root->is_RightPagina() << endl;
            if(root->is_RightPagina()){
              //cout << nodoAnt->rightPage << endl;
              //nodoAnt->rightPage = NULL;
            }
            else{
              //cout << "2" << endl;
              //nodoAnt->leftPage = NULL;
            }
            if(paginaAnt->getSize() < this->orden){
              cout << "nor: " << paginaAnt->getSize() << endl;
              paginaAnt->addNodo(nodo);
            }else{
              cout << "div" << endl<< endl;
              paginaAnt = division(paginaAnt, nodo);
            }
            
            
          
          }
        }

      }

      void replace(){

      }

      void delet(){

      }

      void vew(){

      }

      int getProfundidad(){
        return 0;
      }

      void add(int pID){
        //Pagina *pRaiz, int pID, bool pHoja, Nodo* nodoAnt, Pagina* paginaAnt
        if(this->raiz == NULL){
          raiz = insert(this->raiz,pID,false,NULL,NULL);
          return;
        }
        insert(this->raiz,pID,true,NULL,NULL);
      }





};


#endif // MACRO
