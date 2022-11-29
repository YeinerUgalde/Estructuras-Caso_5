#include <iostream>
#include "../grafo_N/grafo.h"

using namespace std;

    class CierreTransitivo {
        private:
            Grafo grafo;

        public:
            CierreTransitivo (Grafo pGrafo){
                this->grafo = pGrafo;
            }

            int[][] multiplicarMatrices(int pMat[][], int pLen){
                int nuevaMatriz[pLen][pLen]
                for (int a = 0; a < pLen; a++) {
                   
                    for (int i = 0; i < pLen; i++) {
                        int suma = 0;
                       
                        for (int j = 0; j < pLen; j++) {
                            if (pMat[i][j] || pMat[j][a]){}
                                suma = 1;
                                break;
                                //suma += pMat[i][j] * pMat[j][a];
                        }
                      
                        nuevaMatriz[i][a] = suma;
                    }
                }
                
                return nuevaMatriz;
            }

            void recorrerCierre(int pMatriz[][]){
                len = pMatriz.length;
                for (int i = 0; i < len; i++){
                    int nuevaMatriz = multiplicarMatrices(pMatriz,len);

                }
            }



    } ;