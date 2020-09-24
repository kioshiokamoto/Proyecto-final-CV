#include "cilindro.h"
#include <iostream>
using namespace std;
float TwicePi = 2.0f * M_PI;
float Radio= 1.0;
void cilindro::init(int segx, int segy)
{
    numVertices = segx * (segy+1) + 2;
                //mallas + //ambas bases
    numIndices = 6*segx * (segy+1);
    for (int i = 0; i < numVertices; i++) { vertices.push_back(QVector3D()); } // std::vector::push_back()
    for (int i = 0; i < numVertices; i++) { normals.push_back(QVector3D()); } // the end of a vector and
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); } // increases the vector size by 1

    //vertices de las bases:
    vertices[0]=QVector3D(0.0,-1.0,0.0); //centro de la base
    normals[0] = QVector3D(0.0,-1.0,0.0);
    vertices[1]=QVector3D(0.0,1.0,0.0); // punto mas alto
    normals[1] = QVector3D(0.0,1.0,0.0);
    int cont=2; // se han usado 2 del total de vertices
    float altura = -1.0;
    //vertices de las bases:
    while(cont< numVertices){
        for(int i=cont; i<cont+segx; i++){
            float x = Radio*(cos((i-2) * TwicePi / segx));
            float y = altura;
            float z = Radio*(sin((i-2) * TwicePi / segx));
            vertices[i] = QVector3D(x, y, z);
            //normals[i] = QVector3D::normal(vertices[i],QVector3D(1, 0.5, 0));
            normals[i] = QVector3D(x, y, z);
        }
        altura = altura +(2.0/segy);
        cont = cont +segx; //salta a la siguiente base
    }
    //llenando indices de la primera base:
    cont = 2;
    for(int i=cont; i<cont+segx; i++){
        if(i==cont+segx-1){
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=cont;
            //normals[i] = QVector3D(0, -1, 0);
        }else{
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=i+1;
            //normals[i] = QVector3D(0, -1, 0);
        }


    }
    cont = segx*3; //se han llenado cont indices
    int j=2+segx; //indice de la siguiente base
    int aux = 2;
    int cont1=0;

    //indices de los triangulos que forman las mallas del cono
    while(cont< numIndices){
        segy--;
        for(int i=aux; i<aux+segx; i++){
            if(j+1==aux+2*segx){
                indices[6 *(i-aux)+cont] = aux;
                indices[6 * (i-aux)+cont + 1] = i;
                indices[6 * (i-aux)+cont + 2] = j;
                indices[6 * (i-aux)+cont + 3] = aux;
                indices[6 * (i-aux)+cont + 4] = i + 1;
                indices[6 * (i-aux)+cont + 5] = j;
                j++;
                cont1 = cont1+6;
            }else{
                indices[6 *(i-aux)+cont] = i;
                indices[6 * (i-aux)+cont + 1] = i + 1;
                indices[6 * (i-aux)+cont + 2] = j;
                indices[6 * (i-aux)+cont + 3] = j + 1;
                indices[6 * (i-aux)+cont + 4] = i + 1;
                indices[6 * (i-aux)+cont + 5] = j;
                j++;
                cont1 = cont1+6;
            }
        }
        cont = cont + cont1;
        aux = aux+segx;
        cont1=0;
        for(int i=aux; i<aux+segx; i++){
            if(segy==0){
                //ultima base con tringulos
                if(i==aux+segx-1){
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = aux;
                    cont1= cont1+3;
                    cont = cont + cont1;
                   /* normals[1] = QVector3D(0, 1, 0);
                    normals[i] = QVector3D(0, 1, 0);
                    normals[aux] = QVector3D(0, 1, 0);*/
                }else{
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = i+1;
                    cont1= cont1+3;
                    //normals[i] = QVector3D(0, 1, 0);
                }

            }
        }




    }
}
cilindro::cilindro(int segx, int segy)
{
    init(segx,segy);
}

cilindro::cilindro()
{
    init(3,3);
}
//accessors
int cilindro::getNumVertices() { return numVertices; }
int cilindro::getNumIndices() { return numIndices; }
vector<int> cilindro::getIndices() { return indices; }
vector<QVector3D> cilindro::getVertices() { return vertices; }
vector<QVector3D> cilindro::getNormals() { return normals; }
