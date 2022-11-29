#include <iostream>
#include <ctime>
#include "../match/matcher.h"
#include "../net_work/User_matches.h"


using namespace std;

#ifndef USUARIO
#define USUARIO 1

class Usuario {
    private:

        struct tm *time_path;
        time_t register_date;
        
        string demanda;
        string oferta;

        string nickName;

        string registerDate;

        string passWord;   

        User_matches matches;     

        Matcher matcher;

        int id = 0;

    public:
        Usuario(){
            
        }
        void setNickName(string pNick){
            this->nickName = pNick;
            
        }
        
        void setPassWord(string pPassWord){
            this->passWord = pPassWord;
        }

        void setRegisterDate(string pRegister){
            this->registerDate = pRegister;
        }

        void setDemanda(string pDemanda){
            this->demanda = pDemanda;
        }

        void setOferta(string pOferta){
            this->oferta = pOferta;
        }

        void setTime(){
            time_t time_mod = time(NULL);
            time_path = localtime(&time_mod);
            register_date = mktime(time_path);            
            
        }

        void initMatcher(){
            if(demanda.size() > 0){
                this->matcher.generate_Arbol_demanda_String(this->demanda);
            }
            if(oferta.size() > 0){
                this->matcher.generate_Arbol_oferta_String(this->oferta);
            } 
            //cout << demanda.size() << endl;
            //cout << oferta.size() << endl;
            cout << endl;
        }

        int tryMatchOferta(Usuario *pUsuario){
            int importancia = matcher.match(matcher.getVecOferta(), pUsuario->getDemandaTree());
            

            if(importancia){
                
                if(!matches.is_in(pUsuario->getID())){
                    matches.generate(pUsuario->getID(),pUsuario->getNick(), pUsuario->getRegister_Date(),importancia);
                }
                
                cout << "importancia: " << importancia << endl;                
                cout << "match con: "<< pUsuario->getNick() << "--- Quiza su demanda te interese!!"<< endl;
                cout << "demanda: " << pUsuario->getDemanda() << endl;
                cout << "El usuario se registro: " << registerDate << endl;
                cout << "---------------------------------------------------------"<< endl;
                return importancia;
            }
            return 0;
        }   

        int tryMatchDemanda(Usuario *pUsuario){
            int importancia = matcher.match(matcher.getVecDemanda(), pUsuario->getOfertaTree());            
            
            if(importancia){    
                if(!matches.is_in(pUsuario->getID())){
                    matches.generate(pUsuario->getID(),pUsuario->getNick(), pUsuario->getRegister_Date(),importancia); 
                }                            
                cout << "importancia: " << importancia << endl;
                cout << "match con: "<< pUsuario->getNick() << "--- Quiza su oferta te interese!!" << endl;
                cout << "Oferta: " << pUsuario->getOferta() << endl;
                cout << "El usuario se registro: " << registerDate << endl;
                cout << "---------------------------------------------------------"<< endl;
                return importancia;
            }
            return 0;
        }


        int tryMatchOferta2(Usuario *pUsuario){
            int importancia = matcher.match(matcher.getVecOferta(), pUsuario->getDemandaTree());
            

            if(importancia){
                matches.generate(pUsuario->getID(),pUsuario->getNick(), pUsuario->getRegister_Date(),importancia);
                return importancia;
            }
            return 0;
        }   

        int tryMatchDemanda2(Usuario *pUsuario){
            int importancia = matcher.match(matcher.getVecDemanda(), pUsuario->getOfertaTree());            
            
            if(importancia){                
                matches.generate(pUsuario->getID(),pUsuario->getNick(), pUsuario->getRegister_Date(),importancia); 
                return importancia;
            }
            return 0;
        }

        void pathMatch(){
            matches.getRelaciones();
        }

        void getTop10(){
            matches.getTop10Mathc();
        }


        int getID(){
            return this->id;
        }


        string getNick(){
            return this->nickName;
        }
        
        string getPassWord(){
            return this->passWord;
        }

        string getDemanda(){
            return this->demanda;
        }

        string getOferta(){
            return this->oferta;
        }

        string getRegister_Date(){
            return ctime(&register_date);
        }

        BPlusTree* getDemandaTree(){
            return this->matcher.getArbolDemanda();
        }

        BPlusTree* getOfertaTree(){
            return this->matcher.getArbolOferta();
        }

};


#endif 