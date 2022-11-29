#include <iostream>
#include "definitivo/Arbol_B+.h"

using namespace std;



int main(){
    BPlusTree tree(2);
    tree.add("hola");
    tree.add("sol");
    tree.add("basura");
    tree.add("recolector");
    tree.add("ola");
    tree.add("batidora");
    tree.add("batman");
    tree.add("batimovil");
    tree.add("girasol");
    tree.add("rosa");
    tree.add("melano");
    
    tree.add("asdfasf");
    tree.add("batimohjljhklvil");
    tree.add("asdf");
    tree.add("rolacion");
    tree.add("aukhmelasdfsafano");
    cout << endl << endl;
    tree.path(tree.getRaiz());
    cout << endl << endl;
    
    cout << endl << "fin" << endl;
    cout << endl;

    if(tree.search(tree.getRaiz(), "un")){
        cout << "si lo encontro" << endl;
    }


    cout << endl << "fin" << endl;
    cout << "Cantidad de nodos " << tree.getCantidad_nodos() <<endl;
    cout << "Wrd : " << tree.getWrd().size() << endl;

    for(string s : tree.getWrd()){
        cout << s << endl;
    }

    /*Bloque* bloque = new Bloque(2);
    Bloque* bloque2 = new Bloque(2);

    Nodo* nuevo = new Nodo(); nuevo->data = "Hola";
    Nodo* nuevo1 = new Nodo(); nuevo1->data = "emer";
    Nodo* nuevo2 = new Nodo(); nuevo2->data = "alo";
    Nodo* nuevo3 = new Nodo(); nuevo3->data = "sol";

    Nodo* nuevo7 = new Nodo(); nuevo7->data = "jala";
    Nodo* nuevo8 = new Nodo(); nuevo8->data = "jolo";
    Nodo* nuevo9 = new Nodo(); nuevo9->data = "pum";
    Nodo* nuevo10 = new Nodo(); nuevo10->data = "sal";
    //Nodo* nuevo11 = new Nodo(); nuevo11->data = "emergencia";

    Nodo* nuevo4 = new Nodo(); nuevo4->data = "kkk";

    bloque->addNodo(nuevo);
    bloque->addNodo(nuevo1);
    bloque->addNodo(nuevo2);
    bloque->addNodo(nuevo3);

    bloque2->addNodo(nuevo7);
    bloque2->addNodo(nuevo8);
    bloque2->addNodo(nuevo9);
    //bloque2->addNodo(nuevo10);

    //bloque->setBloqueAntecesor(bloque2);

    bloque = tree.divisionCel(bloque, nuevo4);
    bloque->nodos[0]->left = tree.divisionCel(bloque->nodos[0]->left, nuevo10);
    //bloque->nodos[0]->left = tree.divisionCel(bloque->nodos[0]->left, nuevo10);

    Nodo* nuevo5 = new Nodo(); nuevo5->data = "alopecia";

    bloque->addNodo(nuevo5);

    tree.path(bloque);    

    cout << endl << "fin" << endl;

    cout << endl;

    tree.path(bloque2);


    /*
    vector<int> vec = {1,2,3,4};

    cout << vec[0] << " "<< vec[1] << endl;

    vec.insert(vec.begin(),400);

    cout << vec[0] << " "<< vec[1]<< " "<< vec[2];*/
    
};