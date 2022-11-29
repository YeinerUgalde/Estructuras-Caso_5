
#include <vector>
#include <iostream>
#include "NodoGrafo.h"
#include "INodo.h"
#include <map>
#include <queue>
#include "Arco.h"
#include <string.h>

using namespace std;

#ifndef _GRAFO_
#define _GRAFO_ 1

class Grafo {
    private:
        vector<NodoGrafo*> listaNodos;
        bool esDirigido = true;
        std::map<int,NodoGrafo*> hashNodos;


        void resetNodes() {
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                actual->procesado = false;
                actual->visitado = false;
            }
        }

        NodoGrafo* findNotVisited() {
            NodoGrafo* result = nullptr;
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                if (!actual->visitado) {
                    result = actual;
                    break;
                }
            }
            return result;
        }

    public:
        Grafo(bool pDirigido) {
            this->esDirigido =  pDirigido;
        }

        int getSize() {
            return this->listaNodos.size();
        }

        vector<NodoGrafo*> getListaNodos(){
            return this->listaNodos;
        }


        void addNodeInt(int pId) {
            INodo* nodo = new INodo();
            nodo->setId(pId);
            NodoGrafo* nuevoNodo = new NodoGrafo(nodo);
            this->listaNodos.push_back(nuevoNodo);
            hashNodos.insert(pair<int,NodoGrafo*>(nodo->getId(),nuevoNodo));
        }

        //void addNode(int pId, Usuario *pUsuario) {
        void addNode(int pId, string pNick, string pFecha) {
            INodo* nodo = new INodo();
            nodo->setId(pId);
            nodo->setNick(pNick);
            nodo->setFecha(pFecha);

            NodoGrafo* nuevoNodo = new NodoGrafo(nodo);
            this->listaNodos.push_back(nuevoNodo);
            hashNodos.insert(pair<int,NodoGrafo*>(nodo->getId(),nuevoNodo));
        }

        void addNode(INodo* pNodo) {
            NodoGrafo* nuevoNodo = new NodoGrafo(pNodo);
            this->listaNodos.push_back(nuevoNodo);
            hashNodos.insert(pair<int,NodoGrafo*>(pNodo->getId(),nuevoNodo));
        }

        void addArc(INodo* pOrigen, INodo* pDestino) {
            this->addArc(pOrigen, pDestino, 0);
        }

        void addArc(INodo* pOrigen, INodo* pDestino, int pPeso) {
            Arco* newArc = new Arco(pOrigen, pDestino, pPeso);

            getNodo(pOrigen->getId())->addArc(newArc);
            //pOrigen->addArc(newArc);
            if (!this->esDirigido) {
                Arco* reverseArc =  new Arco(pDestino, pOrigen , pPeso);
                getNodo(pDestino->getId())->addArc(reverseArc);
                //pDestino->addArc(reverseArc);
            }
        }

        void addArcInt(int pOrigen, int pDestino, int pPeso) {
            INodo* origen = getNodo(pOrigen)->getInfo();
            INodo* destino = getNodo(pDestino)->getInfo();
            Arco* newArc = new Arco(origen, destino, pPeso);

            getNodo(pOrigen)->addArc(newArc);
            //pOrigen->addArc(newArc);
            if (!this->esDirigido) {
                Arco* reverseArc =  new Arco(destino, origen , pPeso);
                getNodo(pDestino)->addArc(reverseArc);
                //pDestino->addArc(reverseArc);
            }
        }

        
      
      
     
        NodoGrafo* getNodo(int pId) { 
            return hashNodos.at(pId);
        }

        vector<INodo> deepPath(INodo* pOrigen) {  //recorrido en profundidad
            vector<INodo> result;

            return result;
        } 

        vector<INodo*> broadPath(INodo* pOrigen) {
            vector<INodo*> result;
            queue<NodoGrafo*> nodosProcesados;
            int visitados = 0;
            
            resetNodes();

            NodoGrafo* puntoPartida = this->getNodo(pOrigen->getId());
            nodosProcesados.push(puntoPartida);
            puntoPartida->procesado = true;
            
            do {
                while (!nodosProcesados.empty()) {
                    NodoGrafo* actual = nodosProcesados.front();
                    nodosProcesados.pop();

                    actual->visitado = true;
                    visitados++;
                    result.push_back(actual->getInfo());

                    vector<Arco*> *adyacentes = actual->getArcs();

                    for (int indiceArcos=0; indiceArcos<adyacentes->size(); ++indiceArcos) {
                        Arco* arco = adyacentes->at(indiceArcos);
                        NodoGrafo* adyacente = (NodoGrafo*)arco->getDestino();
                        if (!adyacente->procesado) {
                            nodosProcesados.push(adyacente);
                            adyacente->procesado = true;
                        }
                    }
                }

                if (visitados<this->getSize()) {
                    puntoPartida = this->findNotVisited();
                    nodosProcesados.push(puntoPartida);
                    puntoPartida->procesado = true;
                }
            } while (visitados<this->getSize()); 

            return result;
        }


        vector<INodo> path(INodo* pOrigen, INodo* pDestino) { // debe retornar un camino, el primero que encuentre estre el nodo oriegn y destino
            // en caso de que no haya camino, result se retorna vacío
            vector<INodo> result;

            return result;
        }        

        void diez_primeros(){
            int i = 1;
            NodoGrafo* primmero = *(listaNodos.begin());
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                if(actual == listaNodos[0]){
                    continue;
                }
                cout << i << ": " << actual->getInfo()->getNick() << endl;
                if(i >= 10){
                    break;
                }
                i++;
                
            }
        }

        void diez_primeros2(int pID){
            NodoGrafo* actual = listaNodos[pID];
            vector<Arco*>* arcos = actual->getArcs();
            vector<Arco*> finalV;
            bool con = false;
            for(int i = 0; i < arcos->size(); i++){
                Arco *arco = arcos[0][i];
                int pos = (finalV.size());


                for(int j = finalV.size(); j >= 0; j--){
            
                    if(j-1 < 0){
                        break;
                    }                    
                    Arco arco2 = finalV[0][j-1];
                    /*if(arco->getDestino()->getId() == arco2.getDestino()->getId()){
                        con = true;
                    }*/
                    if(arco->getPeso() >= arco2.getPeso()){
                        pos = j-1;
                    }
                    //cout << "peso: " << arco->getPeso() << " : " <<  arco2.getPeso() << endl;
                    

                }     
                if(con){
                    con = false;
                    continue;
                }
                
                if(finalV.size() > 0 && !is_in(&finalV, arco->getDestino()->getId())){
                    //cout << "pos: " << pos << endl;   
                    finalV.insert(finalV.begin()+pos, arco);
                }
                else if(!is_in(&finalV, arco->getDestino()->getId())){
                    finalV.push_back(arco);
                }        
                
                if(i >= 10){
                    break;
                }
            }
            int i = 1;
            for(Arco* arc : finalV){
                cout << i++ << " : " << arc->getDestino()->getNick() << " : importancia = " << arc->getPeso() << endl; 
            }

        }
        bool is_in(vector<NodoGrafo*> *nodos, int pID){
            for(NodoGrafo* nodo : *nodos){
                if(nodo->getInfo()->getId() == pID){
                    return true;
                }
            }
            return false;

        }

        bool is_in(vector<Arco*> *nodos, int pID){
            for(Arco* nodo : *nodos){
                if(nodo->getDestino()->getId() == pID){
                    return true;
                }
            }
            return false;

        }

        bool is_in(int pID){
            NodoGrafo* nodo = listaNodos[0];
            vector<Arco*> *arcos = nodo->getArcs();
            for(Arco* arco : *arcos){
                if(arco->getDestino()->getId()==pID){
                    return true;
                }
            }                                                                
            return false;
        }

        vector<NodoGrafo*>* camino1(int caminoActual, vector<NodoGrafo*> *camino, int pIDestino){
            NodoGrafo* actual = listaNodos[caminoActual];
            vector<Arco*>* arcos = actual->getArcs();
            if(is_in(camino, actual->getInfo()->getId())){
                return NULL;
            }
            camino->push_back(actual);
            
            //cout << "camino 1: " << arcos->size() << endl;
            for(int i = 0; i < arcos->size(); i++){
                Arco *arco = arcos[0][i];
                //cout << pIDestino << " : " << arco->getDestino()->getId() << endl;
                if(pIDestino == arco->getDestino()->getId() && camino->size() >= 2){
                    //cout << "Lo encontro" << endl;
                    //cout << camino->size() << endl;
                    return camino;
                }

                else if(pIDestino != arco->getDestino()->getId()){
        
                    camino1(arco->getDestino()->getId(), camino, pIDestino);
            
                }

                
            }
            //cout << "NULL" << endl;
            return NULL;
        }

        vector<vector<NodoGrafo*>> cierreTransitivo(){
            vector<vector<NodoGrafo*>> cierres;
            for(NodoGrafo* user : listaNodos){
                
                int pID = user->getInfo()->getId();
                vector<Arco*> *arcos = user->getArcs();
                for(Arco* nuevoArc : *arcos){
                    INodo *nodo = nuevoArc->getDestino();

                    vector<NodoGrafo*> *nodos = new vector<NodoGrafo*>();
                    vector<NodoGrafo*> *nodos2 = camino1(nodo->getId(),nodos,pID);
                    //vector<NodoGrafo*> *nodos2 = camino1(7,nodos,9);

                    if(nodos2 != NULL && nodos2->size()>=2){
                        nodos = nodos2;                   
                        nodos->push_back(user);
                        cierres.push_back(*nodos);
                    }
                }
            }
            return cierres;
        }

        void getCierreTransitivo(){
            vector<vector<NodoGrafo*>> cierres = cierreTransitivo();
            for(vector<NodoGrafo*> vec : cierres){
                cout << "------------------------" << endl;
                for (NodoGrafo* nodo : vec){
                    cout << nodo->getInfo()->getNick() << "--> ";
                }
                cout << vec[0]->getInfo()->getNick() <<endl;
                
            }
            cout << "------------------------" << endl;
        }



        void printCounters() {
            for (std::vector<NodoGrafo*>::iterator current = listaNodos.begin() ; current != listaNodos.end(); ++current) {
                NodoGrafo* actual = (*current);
                cout << actual->getInfo()->getId() << " tiene " << actual->getArcs()->size() << endl;
            }
        }

        bool is_related(int pOrigen, int pID){
            NodoGrafo* actual = listaNodos[pOrigen];
            vector<Arco*>* arcos = actual->getArcs();
            //cout << "arcos: " << arcos->size() << endl;
  
            
            for(int i = 0; i < arcos->size(); i++){
                Arco *arco = arcos[0][i];
                //cout << pID << " : "<< arco->getDestino()->getId()<< endl;
                if(pID == arco->getDestino()->getId()){
                    return true;
                }
            }
            return false;
        }


        void cadenaMasLarga(){
            vector<vector<NodoGrafo*>> cierres = cierreTransitivo();
            vector<NodoGrafo*> longest;
            int largo = 0;
            for(vector<NodoGrafo*> vec : cierres){            
                if(vec.size() > largo){
                    largo = vec.size();
                    longest = vec;
                }                              
            }
            if(!longest.size()){
                cout << " sin cadena " << endl;
            }
            cout << "La cadena mas larga es: " << endl;
            cout << "-----------------------" << endl;
            for(NodoGrafo* user : longest){
                cout << user->getInfo()->getNick() << "--> ";
            }   
            cout << longest[0]->getInfo()->getNick() << endl;
            cout << "-----------------------" << endl;
            

        }
};

#endif