#include <iostream>
#include "CSVLector.h"
#include <vector>
#include "..\..\usuario\Usuario.h"

using namespace std;

int main(){
    CSVLector lector;
    lector.setRuta("C:/Users/Yeiner/OneDrive/Escritorio/Caso 5/socket/CSV");
    lector.setFileName("Registro");
 
    vector<string> datos;
    datos.push_back("nickName");
    datos.push_back("passWord");
    datos.push_back("demanda");
    datos.push_back("oferta");
    datos.push_back("registerDate");

    lector.createCSV("Registro",datos);

    /*Usuario *usuario = new Usuario();
    usuario->setNickName("Elgoleadordelasele");
    usuario->setDemanda("Hola esta es mi demanda");
    usuario->setOferta("Hola esta es mi oferta");
    usuario->setTime();

    Usuario *usuario2 = new Usuario();
    usuario2->setNickName("otros");
    usuario2->setDemanda("Hola esta es mi demanda");
    usuario2->setOferta("Hola esta es mi oferta");
    usuario2->setTime();

    Usuario *usuario3 = new Usuario();
    usuario3->setNickName("tercero");
    usuario3->setDemanda("Hola esta es mi demanda");
    usuario3->setOferta("Hola esta es mi oferta");
    usuario3->setTime();*/

    /*lector.addUser_to_CSV(usuario);
    lector.addUser_to_CSV(usuario2);
    lector.addUser_to_CSV(usuario3);*/


    lector.leer();
    
    vector<Usuario*> usuarios = lector.getUsuarios();
    cout << usuarios.size() << endl;
    for(Usuario* usuario: usuarios){
        if(usuario){
            cout << usuario->getNick();    
            cout << usuario->getPassWord()<< endl;
        }
        
    }

    cout << "fin" << endl;





    return 0;
};