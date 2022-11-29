#include <iostream>
#include <sstream> 

#include "usuario/Manager.h"
#include "usuario/Usuario.h"
#include "usuario/Registro.h"

using namespace std;
int main(){
 
  NetWork *netWork = new NetWork();
  netWork->init("C:/Users/Yeiner/OneDrive/Escritorio/Caso_5_git/Estructuras-Caso_5/Caso 5","Registro");
  //C:\Users\Yeiner\OneDrive\Escritorio\Caso_5_git\Estructuras-Caso_5\Caso 5
  //netWork->generate_usuarios(netWork->getUsuarios());

  Manager manager;
  manager.setNet(netWork);
  manager.menu();

  cout << "fin" << endl;
  //g++ main.cpp -o main.exe
  ///main.exe
}


