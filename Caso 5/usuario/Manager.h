#include <iostream>
#include "Registro.h"
#include "../net_work/NetWork.h"
#include <bits/stdc++.h>
//#include "../grafo/algoritmosGrafos/cierreTransitivo.h"

using namespace std;

class Manager{
    private:
        Usuario *usuario;
        NetWork *netWork;
    public:
        void setNet(NetWork *pNet){
            this->netWork = pNet;
        }

        void menuInteraccion(){
            int eleccion;
            cout << "1. ver Matches" << endl;
            cout << "2. ver mi oferta" << endl;
            cout << "3. ver mi demanda" << endl;
            cout << "4. ver top 10 Matches" << endl;
            cout << "5. volver al menu" << endl;
            cout << "9. salir" << endl << ": ";
            cin >> eleccion;
            cout << endl;            
            if(eleccion == 1){

                vector<Usuario*> usuarios = netWork->getUsuarios();    
                for(Usuario *user : usuarios){
                    if(user->getNick() == usuario->getNick()){
                        continue;
                    }
                    //cout << user->getNick() << endl;
                    //cout << user->getDemandaTree() << " : "<< user->getOfertaTree() << endl;
                    if(!user->getDemandaTree()->getRaiz() && !user->getOfertaTree()->getRaiz()){
                        user->initMatcher();
                    }  
                    if (user->getDemanda().size()>0){
                        //cout << "tiene demanda" << endl;
                        this->usuario->tryMatchOferta(user);
                    }
                    if(user->getOferta().size()>0){
                        //cout << "tiene oferta" << endl;
                        this->usuario->tryMatchDemanda(user);
                    }
                    
                }
                //this->usuario->pathMatch();
                cout << endl;
                menuInteraccion();
                return;
            }
                
            else if(eleccion == 2){
                cout << "La oferta es :" << endl;
                cout << this->usuario->getOferta() << endl;
                cout << endl;
                menuInteraccion();
                return;
            }
            else if(eleccion == 3){
                cout << "La demanda es :" << endl;
                cout << this->usuario->getDemanda() << endl;
                cout << endl;
                menuInteraccion();
                return;
            }
            else if(eleccion == 4){
                cout << "Los diez primeros matches son: " << endl;
                usuario->getTop10();

                cout << endl;
                menuInteraccion();
                return;
            }
            else if(eleccion == 5){
                cout << "Volviendo al menu... " << endl << endl;;                
                menu();
                return;
            }
            else if(eleccion == 9){
                cout << "Saliendo del prograna.." << endl;
                return;            
            }
            else{
                //menuInteraccion();
                cout << "Sin eleccion" << endl;
                return;
            }
                
            
        }
        void menu(){
            int eleccion = 0;
            cout << "1. Registrarse" << endl;
            cout << "2. Iniciar sesion" << endl;            
            cout << "3. Ver comercio Circular" << endl;
            cout << "4. Ver la cadena mas larga" << endl;
            cout << "9. Salir" << endl << ": ";
            cin >>  eleccion;
            cout << endl; 
            if(eleccion == 1){
                Registro registro;
                this->usuario = registro.registro();
                netWork->addUsuario(usuario);
                menuInteraccion();  
                return;         
            }
                            
            else if(eleccion == 2){
                string nick,passWord;
                cout << "Digite su nombre de usuario" << endl << ": ";
                cin >> nick;
                cout << endl; 
                this->usuario = netWork->findUser(nick);
                if(this->usuario){  

                    cout << "Digite su passWord" << endl << ": ";
                    cin >> passWord;
                    cout << endl;   
                    if(passWord == this->usuario->getPassWord()){
                        usuario->initMatcher();
                        menuInteraccion();   
                        return;
                    }
                          
                }
                cout << "Error: No se encontro el usuario digitado" << endl;
                cout << "Vuelva a intentarlo" << endl;
                menu();
                
            }

            else if(eleccion == 3){
                cout << "Comercio circular " << endl;   
                this->netWork->getComercioCirucular();
                menu();  
                return;       
            }

            else if(eleccion == 4){
                cout << "Cadena de valor mas larga " << endl;   
                this->netWork->getCadenaDeValorMasLarga();
                menu();  
                return;       
            }

            else if (eleccion == 9){
                cout << "No se selecciono ninguna de las opcciones" << endl;
                cout << "Saliendo del programa.." << endl;
                  
                return;      
            }
            else if(!eleccion){
                cout << "sin eleccion" << endl;
                return;
            }
        }
};