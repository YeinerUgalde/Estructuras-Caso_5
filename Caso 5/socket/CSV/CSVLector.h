#include <iostream>
#include <fstream>
#include <sstream>
#include "..\..\usuario\Usuario.h"
#include <vector>

using namespace std;

class CSVLector {
    private:
        vector<Usuario*> usuarios;
        string ruta;
        string fileName;

    public:
        void setRuta(string pRuta){
            this->ruta = pRuta;
        }

        void setFileName(string filename){
            this->fileName = filename;
        }

        bool leer(){
            try
            {
                ifstream archivo(ruta+"/"+fileName+".csv");
                if(!archivo){
                    return false;
                }
                string linea;
                

                char delimitador = ','; //Delimitador dentro de csv

                getline(archivo, linea);

                while (getline(archivo,linea))
                {

                    //cout << linea << endl;
                    
                    if(linea.size() == 0){
                        continue;
                    }
                    stringstream stream(linea); 
               
                    string nombre, password ,demanda, oferta, publish_date; //Se generar las instancias tipo string                    

                    getline(stream, nombre, delimitador); //Obtenemos los valores en el orden de las instancias
                    getline(stream, password, delimitador);
                    getline(stream, demanda, delimitador);
                    getline(stream, oferta, delimitador);
                    getline(stream, publish_date, delimitador);

                    Usuario *usuario = new Usuario(); // Se crea un nuevo objeto del tipo joya y añaden sus atributos
                    usuario->setNickName(nombre);
                    usuario->setPassWord(password);
                    usuario->setDemanda(demanda);
                    usuario->setOferta(oferta);
                    usuario->setRegisterDate(publish_date);

                    usuarios.push_back(usuario); //Se añade el puntero a joya al vector de joyas para luego ser consultado

                }

                archivo.close(); // Se cierra el aricho csv
                return true; // Retorna true si se logra leer el archivo
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n'; //Para el control de excepciones
                cout << "erorr" << endl;
            }
            return false; //Retorna false en caso de que no se logre acceder al archivo o algun error en el mismo
            
        }

        bool createCSV(string filename, vector<string> datos){
            this->fileName = filename;
            ifstream archivo(ruta+"/"+fileName+".csv");
            if(archivo){
                return false;
            }
            archivo.close();

            ofstream myFile(ruta+"/"+fileName+".csv");
            
            for(int i = 0; i < datos.size(); i++){
                if(i+1 < datos.size()){
                    myFile << datos[i] << ",";
                }else{
                     myFile << datos[i];
                }
            }            
            myFile << "\n";
   
            myFile.close();

            return true;
        }

        bool addUser_to_CSV(Usuario* pUser){
            ifstream archivo(ruta+"/"+fileName+".csv");
            if(!archivo){
                return false;
            }
            archivo.close();

            ofstream myFile;
            myFile.open(ruta+"/"+fileName+".csv",std::ios_base::app);
            
            myFile << pUser->getNick() << ",";
            myFile << pUser->getPassWord() << ",";
            myFile << pUser->getDemanda()<< ",";
            myFile << pUser->getOferta()<< ",";
            myFile << pUser->getRegister_Date();
            myFile << "\n";
            
            myFile.close();

            return true;



        }

        vector<Usuario*> getUsuarios(){ //para consultar las joyas anteriormente seleccionadas
            return this->usuarios;
        }

};

 