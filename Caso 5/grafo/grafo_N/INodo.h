//#include "../../usuario/Usuario.h"
#include <iostream>

using namespace std;

#ifndef _INODO_
#define _INODO_ 1

class INodo {
    public:
        int getId() {
            return id;
        }

        void setId(int pId) {
            this->id = pId;
        }

        void setFecha(string pFecha){
            this->fecha =  pFecha;
        }
        
        void setNick(string pNombre){
            this->nick = pNombre;
        }

        string getFecha(){
            return this->fecha;
        }
        string getNick(){
            return this->nick;
        }
        
    protected:
        int id;
        string nick;
        string fecha;
        //Usuario *usuario;

};

#endif
