#include <iostream>
#include "../grafo/grafo_N/grafo.h"
#include "../usuario/Usuario.h"
#include "../socket/CSV/CSVLector.h"


class NetWork {

    private:
        Grafo *usuarios;
        vector<Usuario*> usuariosVec;
        CSVLector lector;
        int pID = 0;

    public:
        NetWork(){
            usuarios = new Grafo(true);
        }
        vector<Usuario*> getUsuarios(){
            return this->usuariosVec;
        }

        void generate_relacion(int pID_1, int pID_2, int pImportancia){
            usuarios->addArcInt(pID_1, pID_2, pImportancia);
        }

        void generate_usuarios(vector<Usuario*> pUsuarios){
            for (int i = 0; i < pUsuarios.size(); i++){
                Usuario *usuario1 = pUsuarios[i];
                usuarios->addNode(i, usuario1->getNick(), usuario1->getRegister_Date());
            }
            cout << "size: " << pUsuarios.size() << endl;
            for (int i = 0; i < pUsuarios.size(); i++)
            {
                Usuario *usuario1 = pUsuarios[i];
                if(!usuario1->getDemandaTree()->getRaiz() && !usuario1->getOfertaTree()->getRaiz()){
                    usuario1->initMatcher();
                } 
                
                
                //cout << "Usuario: "  << usuario1->getNick() << " ID: " << i << endl;
                for(int j = 0; j < pUsuarios.size(); j++){
                    Usuario *usuario2 = pUsuarios[j];

                    if(usuario1->getNick() == usuario2->getNick()){
                        continue;
                    }

                    if(!usuario2->getDemandaTree()->getRaiz() && !usuario2->getOfertaTree()->getRaiz()){
                        usuario2->initMatcher();
                    }  

                    if (usuario2->getDemanda().size()>0){
                        //cout << "tiene demanda" << endl;
                        int importancia = usuario1->tryMatchOferta2(usuario2);
                        if(importancia){
                            this->generate_relacion(i,j,importancia);
                        }
                    }
                    if(usuario2->getOferta().size()>0){
                        //cout << "tiene oferta" << endl;
                        int importancia = usuario1->tryMatchDemanda2(usuario2);
                        if(importancia){
                            this->generate_relacion(i,j,importancia);
                        }
                    }   
                }
            }         
        }

       


        void getRelaciones(){
            //usuarios.path(); // devuelve un vector
            usuarios->printCounters(); //Para ver las relaciones en formato print
        }

        void init(string ruta, string fileName){
            vector<string> data = {"nickName","passWord","demanda","oferta","registerDate"}; //Ver si cambiar
            lector.setRuta(ruta);
            lector.setFileName(fileName);
            lector.createCSV(fileName,data);
            lector.leer();
            usuariosVec = lector.getUsuarios();

            this->generate_usuarios(usuariosVec);
        }

        void addUsuario(Usuario *usuario){
            lector.addUser_to_CSV(usuario);
        }

        Usuario* findUser(string pNick){
            for(Usuario* usuario: usuariosVec){
                if(usuario->getNick() == pNick){
                    return usuario;
                }                
            }
            return NULL;
        }


        void getComercioCirucular(){
            //usuarios->cierreTransitivo();
            usuarios->getCierreTransitivo();
        }

        void getCadenaDeValorMasLarga(){
            usuarios->cadenaMasLarga();
        }

};