#include <iostream>
#include <vector>
#include "../arbol/definitivo/Arbol_B+.h"
#include <sstream> 


using namespace std;

#define matches_ 5  //Cantidad minima de matches para recomendar a alguien 

#define orden 4

#ifndef MATCHER
#define MATCHER 1

class Matcher{
    private:
        BPlusTree *oferta = NULL; //SOLO SE LLENA UNA VEZ
        BPlusTree *demanda = NULL; 
        vector<string> ofer;
        vector<string> demand;

        //Arbol_B_plus arboles[2] = {new Arbol_B_Plus_S, new Arbol_B_Plus_S};

    public:
        //Se tiene una cadena de texto
        //Se utliliza el arbol b+ para ordenar el texto
        //Se compara con el de la otra persona
        Matcher(){
            oferta = new BPlusTree(orden);
            demanda = new BPlusTree(orden);
        }

        vector<string> getVecOferta(){
            return this->ofer;
        }

        vector<string> getVecDemanda(){
            return this->demand;
        }

        void generate_Arbol_demanda_String(string pString){
            //Genera un arbol b+ a partir de un string  

            stringstream X(pString); 
            string var;  
        

            while (getline(X, var, ' ')) { // METE LAS PALABRAS EN ..?
                if(var.size() > 0){
                    //cout << var << endl;
                    demand.push_back(var);
                    demanda->add(var);
                    //arbol_b_plus.add(var); // AÑADE LAS PALABRAS AL ARBOL B+
                }          
            }  
            demand = demanda->getWrd();
            /*for(auto var : demand) // PARA VER LAS PALABRAS SEPARADAS OBTENIDAS DEL STRING
            {
                cout << var << endl;
            }
            cout << "Demanda" << endl << endl;*/

        }

        void generate_Arbol_oferta_String(string pString){
            //Genera un arbol b+ a partir de un string  

            stringstream X(pString); 
            string var;  
         
            while (getline(X, var, ' ')) { // METE LAS PALABRAS EN ..?
                if(var.size() > 0){
                    //cout << var << endl;
                    //ofer.push_back(var);
                    oferta->add(var);
                    //arbol_b_plus.add(var); // AÑADE LAS PALABRAS AL ARBOL B+
                }          
            }  
            ofer = oferta->getWrd();

            /*for(auto var : ofer) // PARA VER LAS PALABRAS SEPARADAS OBTENIDAS DEL STRING
            {
                cout << var << endl;
            }
            cout << "oferta" << endl << endl;*/

        }

        BPlusTree* getArbolDemanda(){
            return this->demanda;
        }

        BPlusTree* getArbolOferta(){
            return this->oferta;
        }


        int match(vector<string> pPalabras, BPlusTree* pArbol){
            //cout << "arbol e: " << pArbol << endl;
            int matches = 0;
            for(int i = 0; i < pPalabras.size(); i++){
                //cout << pPalabras[i] << endl;
                //cout << "raiz:" << pArbol->getRaiz() << endl;
                if(pArbol->search(pArbol->getRaiz(),pPalabras[i])){ // palabra x / pal

                    matches += 1;
                }
            }
            //cout << "Matches: " << matches << endl;
            if(matches > pPalabras.size()/matches_){
                return matches;
            }

            return 0;
        }
};

#endif