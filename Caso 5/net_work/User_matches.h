#include <iostream>
#include "../grafo/grafo_N/grafo.h"


#ifndef USER_MATCHES
#define USER_MATCHES 1

class User_matches {

    private:
        Grafo *grafo;
        int arc;
        int pID;

    public:
        User_matches(){
            grafo = new Grafo(true);
            grafo->addNode(0,"YO","sin");
            pID = 0;
            arc = 0;
        }

        void generate(int id, string nick, string fecha, int pImportancia){
            //cout << "ID DEL USUARIO; " << pID << endl;
            grafo->addNode(pID, nick, fecha);    
            this->generate_relacion(arc, pID, pImportancia);
            pID++;
            //generate_relacion();
                    
        }

        bool is_in(int pID){
            grafo->is_in(pID);
        }

        void generate_relacion(int pID_1, int pID_2, int pImportancia){
            grafo->addArcInt(pID_1, pID_2, pImportancia);
        }


        void getRelaciones(){
            //grafo->path(); // devuelve un vector
            grafo->printCounters(); //Para ver las relaciones en formato print
        }

        void getTop10Mathc(){
            //grafo->diez_primeros();
            grafo->diez_primeros();
        }

        

};

#endif