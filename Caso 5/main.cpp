#include <iostream>
#include <sstream> 

#include "usuario/Manager.h"
#include "usuario/Usuario.h"
#include "usuario/Registro.h"

using namespace std;
int main(){
 
  NetWork *netWork = new NetWork();
  netWork->init("C:/Users/Yeiner/OneDrive/Escritorio/Caso 5 - copia","Registro");
  //netWork->generate_usuarios(netWork->getUsuarios());

  Manager manager;
  manager.setNet(netWork);
  manager.menu();

  cout << "fin" << endl;
  //g++ main.cpp -o main.exe
  ///main.exe
}


