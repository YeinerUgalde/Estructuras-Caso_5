#include <iostream>
#include <vector>

//String dato 

//Bloque_0[orden]; bloque_0[0] = dato

//String otroDato;
//                                   |t|
//bloque_0[0] =           |da| | | |  -  |to| | | |
//         |otroDato| | | |

//String tucan

//                                   |t|
//                        |da| | | |  -  |to| tu| | |
//         |otroDato| | | |                      |tucan| | | |


using namespace std;

typedef struct Nodo Nodo;
typedef class Bloque Bloque;

#ifndef NODO
#define NODO 1
struct Nodo{
    string data;    

    bool haveChild;

    Bloque* left = NULL;
    Bloque* right = NULL;    

};
#endif

#ifndef BLOQUE
#define BLOQUE 1
class Bloque{
    private: 
        int size;
        int orden;
        Nodo *antecesor = NULL; //Nodo del cual proviene el bloque;
        Bloque *bloqueAntecesor = NULL;

        

    public:
        vector<Nodo*> nodos;

        Bloque(int pOrden){
            //this->nodos = new vector<Nodo*>
            this->orden = pOrden;
            size = 0;
        }
        
        void setNodoAntecesor(Nodo *pNodo){
            if(this->antecesor == NULL){
                this->antecesor = pNodo;
            }            
        }

         void setBloqueAntecesor(Bloque *pBloque){
            if(this->bloqueAntecesor == NULL){
                this->bloqueAntecesor = pBloque;
            }            
        }

        Bloque *getBloqueAntecesor(){
            return this->bloqueAntecesor;
        }

        bool addNodo(Nodo *pNodo){
            if(size <= (orden*2)-1){  // size = 3 ; orden = 3 (2*2-1)
                nodos.push_back(pNodo);
                size++;
                return true;
            }
            return false;
        }

        void insertN(int pID, Nodo* pNodo){
            if(size <= (orden*2)-1){  
                nodos.insert(nodos.begin()+pID, pNodo);
                size++;
            }
        }

        int getSize(){
            return this->size;
        }

        bool is_Hoja(){
            for(auto var : nodos){  
                if(var->left){
                    return false;
                }
                if(var->right){
                    return false;
                }
            }
            return true;
        }

};
#endif

#ifndef BPLUSTREE
#define BPLUSTREE 1

class BPlusTree{
    private:
        int orden;
        int cantidad_nodos;
        Bloque *raiz = NULL;
        vector<string> wrd;   

    public:

        BPlusTree(int pOrden){
            this->orden = pOrden;   
            this->cantidad_nodos = 0;      

        }
        int getCantidad_nodos(){
            return this->cantidad_nodos;
        }

        vector<string> getWrd(){
            return this->wrd;
        }

        bool search(Bloque *root, string pString){
            
            for(auto var : root->nodos){
                //cout << var->data << " : " << root->getSize() << endl;                
                if(var->data == pString){
                    //cout << "Encontrado" << endl;
                    return true;
                }
                else if(compare(var->data, pString)){
                    if(var->right != NULL){
                        return search(var->right, pString);
                    }
                    
                }else{
                    if(var->left != NULL){
                        return search(var->left, pString);
                    }
                    
                }
            }
            return false;
        }

        void path(Bloque* root){
            if(root != NULL){
                for(auto var : root->nodos){
                    cout << var->data << endl;
                    if(var->left != NULL){
                        cout << "izquierda: " << var->data << endl;
                        path(var->left);
                    }
                    if(var->right != NULL){
                        cout << "derecha: "<< var->data << endl;
                        path(var->right);
                    }
                }
                
            }
        }

        Nodo *createNodo(string pString){
            Nodo *nodo = new Nodo();
            nodo->data = pString;
            this->cantidad_nodos+=1;
            this->wrd.push_back(nodo->data);
            return nodo;
        }

        int getMitad(int pNum){
            return (pNum/2);
        }  

        string getStringSlice(string pString){
            string nuevoString = "";
            if(pString.size() <= 1){
                return pString;
            }
            for(int i = 0; i < (pString.size())/2 ; i++){
                nuevoString+=pString[i];
            }
            return nuevoString;
        }

        bool compare(string pString_1, string pString_2){
            if (pString_2.size() < pString_1.size()){
                return false;
            }
            int size = pString_1.size();
            int cont = 0;
            for (int i = 0; i < size; i++){
                if (pString_1[i] == pString_2[i]){
                    cont++;
                }
            }
            if (cont >= size){
                return true;
            }
            return false;
        }

        Bloque* divisionCel(Bloque *root, Nodo *pNodo){
            int mitad = getMitad(root->getSize());
            Nodo *nodo = root->nodos[mitad]; // REVISAR SI LA MITAD PARA NUMEROS IMPARES MENORES ES CORRECTA

            if(!nodo->left)nodo->left = new Bloque(this->orden); //SI TIENEN OBJETOS NO SE TOCAN
            if(!nodo->right)nodo->right = new Bloque(this->orden);

            //if(nodo->left->getSize() >= this->orden)cout << "izquierda con: " << nodo->left->getSize() <<endl; // BORRAR DESPUES
            //if(nodo->right->getSize() >= this->orden)cout << "derecha con: " << nodo->right->getSize() <<endl; //
            
            //Traspasar los nodos;
            Nodo *nuevo = new Nodo();
            nuevo->data = nodo->data;
            nodo->right->insertN(0,nuevo);
            nodo->data = getStringSlice(nodo->data); //CORTA EL PREFIJO A LA MITAD

            for(int i = 0; i < mitad; i++){ // si mitad = 2; i = 0, i = 1;
                if(nodo->left->getSize() < this->orden*2 && !compare(nodo->data,root->nodos[i]->data)){ 
                    nodo->left->addNodo(root->nodos[i]);
                }else if(compare(nodo->data,root->nodos[i]->data)){
                    if(nodo->right->getSize() < this->orden*2){
                        nodo->right->addNodo(root->nodos[i]);
                    }else{
                        nodo->left->setBloqueAntecesor(root);
                        nodo->right = divisionCel(nodo->right, root->nodos[i]);
                    }
                }else{
                    nodo->left->setBloqueAntecesor(root);
                    nodo->left = divisionCel(nodo->left, root->nodos[i]);
                }   
            }

            //if(root) // POR EL MOMENTO NO SE VALIDA LA COPIA EN LOS HIJOS
            
            for(int i = mitad+1; i < root->getSize();i++){ // si mitad = 2; i = 3;
                if(compare(nodo->data,root->nodos[i]->data) && nodo->right->getSize() < this->orden*2){
                    nodo->right->addNodo(root->nodos[i]);
                }else if(nodo->left->getSize() < this->orden*2){
                    nodo->left->addNodo(root->nodos[i]);
                }else{
                    nodo->left->setBloqueAntecesor(root);
                    nodo->left = divisionCel(nodo->left, root->nodos[i]);
                }
            }
            


            //---Logica para ver si va a la derecha o izquierda
            if (compare(nodo->data,pNodo->data)){
                nodo->right->addNodo(pNodo);
                
            }else{
                nodo->left->addNodo(pNodo);
            }
            
            //-------------------------------------------------

            Bloque* bloque;
            if(root->getBloqueAntecesor()){
                bloque = root->getBloqueAntecesor();

            }else{
                bloque = new Bloque(this->orden);

            }

            if(bloque->getSize() < (this->orden*2)){                
                bloque->addNodo(nodo); //NODO MITAD

            }else{
                bloque = divisionCel(bloque, nodo);
            }
            this->cantidad_nodos++;
            this->wrd.push_back(nodo->data);
            return bloque;
        }

        Bloque* insert(Bloque* root, Nodo* pNodo){
            
            if(root == NULL){
                root = new Bloque(this->orden);
                root->addNodo(pNodo);
                return root;
            }
            if(root->is_Hoja()){
                if(root->getSize() < this->orden*2){
                    root->addNodo(pNodo);
                }else{
                    root = divisionCel(root, pNodo);
                }
            }else{
                for(int i = 0; i < root->getSize(); i++){
                    if(compare(root->nodos[i]->data, pNodo->data) && i >= root->getSize()-1){
                        root->nodos[i]->right = insert(root->nodos[i]->right, pNodo);
                    } 
                }
                root->nodos[0]->left = insert(root->nodos[0]->left, pNodo); // Que el compare devuelva la cantidad de veces coincididas
                                                                            // Y evaluar el mejor candidato con respecto a esas conincidencia                                                       
            }
            return root;            
        }

        void add(string pString){
            Nodo *nodo = createNodo(pString);
            raiz = insert(raiz, nodo);
        }

        Bloque *getRaiz(){
            return this->raiz;
        }

};

#endif