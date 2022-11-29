#include <iostream>
#include <vector>
#include "../../usuario/Usuario.h"
 
using namespace std;

#ifndef COMERCIOCICULAR
#define COMERCIOCICULLAR 1

class ComercioCircular{
    private:
        vector<Usuario*> usuarios;
    public:
        ComercioCircular(){

        }

        void setUsuarios(vector<Usuario*> pUsuarios){
            this->usuarios = pUsuarios;
        }

        vector<Usuario*> getUsuarios(){

        }



        void printComercioCirucular(vector<Usuario*> pUsuarios){
            
        }
        


};

#endif
