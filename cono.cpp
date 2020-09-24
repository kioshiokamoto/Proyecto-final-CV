#include "cono.h"
#include <iostream>
using namespace std;
float twicePi = 2.0f * M_PI;
float radio= 1.0;
cono::cono(int segx, int segy)
{
    init(segx,segy);
}

cono::cono()
{
    init(3,1);
}
float cono::toRadians(float degrees){
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}
void cono::init(int segx, int segy){
    numVertices = segx * segy + 2;
                //mallas + //ambas bases
    numIndices = 6*segx * segy;
    for (int i = 0; i < numVertices; i++) { vertices.push_back(QVector3D()); } // std::vector::push_back()
    for (int i = 0; i < numVertices; i++) { normals.push_back(QVector3D()); } // the end of a vector and
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); } // increases the vector size by 1

    //vertices de las bases:
    vertices[0]=QVector3D(0.0,-1.0,0.0); //centro de la base
    normals[0] = QVector3D(0.0,-1.0,0.0);
    vertices[1]=QVector3D(0.0,1.0,0.0); // punto mas alto
    normals[1] = QVector3D(0.0,1.0,0.0);
    int cont=2; // se han usado 2 del total de vertices
    float escala = 1.0;
    float altura = -1.0;
    //vertices de las bases:
    while(cont< numVertices){
        for(int i=cont; i<cont+segx; i++){
            float x = radio*(cos((i-2) * twicePi / segx))*escala;
            float y = altura;
            float z = radio*(sin((i-2) * twicePi / segx))*escala;
            vertices[i] = QVector3D(x, y, z);
            normals[i] = QVector3D(x, y, z);
            //normals[i] = QVector3D::normal(vertices[i],QVector3D(0, 1, 0));
        }
        altura = altura +(2.0/segy);
        escala = escala - (1.0/segy); //halla el tamaño de la siguiente base
        cont = cont +segx; //salta a la siguiente base
    }
    //llenando indices de la primera base:
    cont = 2;
    for(int i=cont; i<cont+segx; i++){
        if(i==cont+segx-1){
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=cont;
        }else{
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=i+1;
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
            if(segy==0){
                //ultima base
                if(i==aux+segx-1){
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = aux;
                    cont1= cont1+3;
                }else{
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = i+1;
                    cont1= cont1+3;
                }

            }else{
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
        }
        aux = aux+segx;
        cont = cont + cont1;
        cont1=0;
    }

}/*
void cono::init(int segx, int segy){
    numVertices = segx * segy + 2;
                //mallas + //ambas bases
    numIndices = 6*segx * segy;
    for (int i = 0; i < numVertices; i++) { vertices.push_back(QVector3D()); } // std::vector::push_back()
    for (int i = 0; i < numVertices; i++) { normals.push_back(QVector3D()); } // the end of a vector and
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); } // increases the vector size by 1

    //vertices de las bases:
    vertices[0]=QVector3D(0.0,1.0,0.0); // punto mas alto
    vertices[1]=QVector3D(0.0,-1.0,0.0); //centro base
    int cont=2; // se han usado 2 del total de vertices
    float escala = (1.0/segy);
    float altura = 1.0 - (2.0/segy);
    //vertices de las bases:
    while(cont< numVertices){
        for(int i=cont; i<cont+segx; i++){
            float x = radio*(cos((i-2) * twicePi / segx))*escala;
            float y = altura;
            float z = radio*(sin((i-2) * twicePi / segx))*escala;
            vertices[i] = QVector3D(x, y, z);
        }
        altura = altura -(2.0/segy);
        escala = escala + (1.0/segy); //halla el tamaño de la siguiente base
        cont = cont +segx; //salta a la siguiente base
    }
    //llenando indices de la primera base:
    cont = 2;
    for(int i=cont; i<cont+segx; i++){
        if(i==cont+segx-1){
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=cont;
        }else{
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=i+1;
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
            if(segy==0){
                //ultima base
                if(i==aux+segx-1){
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = aux;
                    cont1= cont1+3;
                }else{
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = i+1;
                    cont1= cont1+3;
                }

            }else{
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
        }
        aux = aux+segx;
        cont = cont + cont1;
        cont1=0;
    }

}

*/
//accessors
int cono::getNumVertices() { return numVertices; }
int cono::getNumIndices() { return numIndices; }
std::vector<int> cono::getIndices() { return indices; }
std::vector<QVector3D> cono::getVertices() { return vertices; }
std::vector<QVector3D> cono::getNormals() { return normals; }
