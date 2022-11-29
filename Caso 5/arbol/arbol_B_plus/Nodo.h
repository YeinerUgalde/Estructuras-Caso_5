#include <iostream>
#include "Pagina.h"

using namespace std;

#ifndef NODO
#define NODO 1

struct Nodo {
  string nick;
  string oferta;
  string demanda;
  int id;

  Pagina *leftPage = NULL;
  Pagina *rightPage = NULL;
  
};

#endif