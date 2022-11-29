#ifndef _ARCO_
#define _ARCO_ 1

#include "INodo.h"

using namespace std;

class Arco {
    private:
        INodo* origen;
        INodo* destino;
        int peso;

    public:
        Arco(INodo* pOrigen, INodo* pDestino, int pPeso) {
            this->origen = pOrigen;
            this->destino = pDestino;
            this->peso = pPeso;
        }

        INodo* getOrigen() {
            return this->origen;
        }

        INodo* getDestino() {
            return this->destino;
        }

        int getPeso() {
            return this->peso;
        }
};

#endif