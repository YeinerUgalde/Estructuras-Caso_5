#include <iostream>

#include <string>
#include <sstream>
#include <ctime>

#include "Usuario.h"


using namespace std;

#ifndef REGISTRO
#define REGISTRO 1

class Registro{
    private:
        Usuario* usuario;

        struct tm* time_path;
        time_t time_mod = time(NULL);

    public:

        string createNickName(){
            string nick;
            cout << "Digite el nombre del usuario: ";
            cin >> nick;
            cout << endl;

            if (nick.length() < 10){
                cout << "El nombre del usuario debe de ser mayor a 10 caracteres" << endl;
                return createNickName();
            }
            if (nick.length() > 30){
                cout << "El nombre del usario debe de ser meno a 30 caracteres" << endl;
                return createNickName();
            }

            return nick;

        }
        string createPassWord(){
            string passWord;
            string passWordConfirm;
            cout << "Digite su passWord: ";
            cin >> passWord;
            cout << "\nDigite su contraseña nuevamente: ";
            cin >> passWordConfirm;
            cout << endl;

            if (passWord.length() > 20){
                cout << "La contraseña es demasiado grande" << endl;
                cout << "La contraseña debe de contener menos de 20 caracteres" << endl;
                return createPassWord();

            }

            if (passWord != passWordConfirm){
                cout << "Las contraseñas no coinciden" << endl;
                cout << "Vuelva a intentarlo" << endl;
                return createPassWord();
            }

            return passWord;                        
        }
        int Eleccion(){
            string eleccion;
            int result;

            getline(cin,eleccion);

            stringstream  parser;
            parser << eleccion;
            
            parser >> result;

            return result;


        }
        void objetivo(){
            cout << "Digite el numero conrrespondiente" << endl;
            cout << "1. Demanda" << endl;
            cout << "2. Oferta" << endl;
            cout << "3. Ambas" << endl;
            int eleccion = Eleccion();
            string msg;
            switch (eleccion)
            {
            case 1:
                cout << "Demanda" << endl;
                
                cout << "Digite su demanda: \n";
                getline(cin, msg);

                if(msg.length() > 250){
                    cout << "\nLa demanda no debe de contener mas de 250 caracteres" << endl;
                    cout << "Vuelva a intentarlo" << endl;
                    return objetivo();
                }
                this->usuario->setDemanda(msg);
              
                break;
            case 2:
                cout << "Oferta" << endl;                
               
                cout << "Digite su Oferta: \n";
                getline(cin, msg);
             
                if(msg.length() > 250){
                    cout << "\nLa oferta no debe de contener mas de 250 caracteres" << endl;
                    cout << "Vuelva a intentarlo" << endl;
                    return objetivo();
                }

                this->usuario->setOferta(msg);
            
                break;       
            case 3:
                cout << "Ambas"  << endl;
                
                cout << "Digite su demanda: ";
                getline(cin, msg);
                
                if(msg.length() > 250){
                    cout << "\nLa demanda no debe de contener mas de 250 caracteres" << endl;
                    cout << "Vuelva a intentarlo" << endl;
                    return objetivo();
                }

                this->usuario->setDemanda(msg);
                                       
                cout << "Digite su Oferta: ";
                getline(cin, msg);

                if(msg.length() > 250){
                    cout << "\nLa oferta no debe de contener mas de 250 caracteres" << endl;
                    cout << "Vuelva a intentarlo" << endl;
                    return objetivo();
                }

                this->usuario->setOferta(msg);
           
                break;            
            default:
                cout << "Debe de elegir alguna de las opciones anteriores" << endl;
                cout << "Vuelva a intentarlo" << endl;
                return objetivo();
                break;
            }


        }

    
        Usuario* registro(){

            usuario = new Usuario();

            usuario->setTime();

            string nickName = this->createNickName();
            string passWord = this->createPassWord();
            this->objetivo();

            usuario->setNickName(nickName);
            usuario->setPassWord(passWord);

            usuario->initMatcher();

            return usuario;
            
        }
};

#endif